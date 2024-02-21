/**
 * @file Compile.cpp
 * @author Alex Friedman (https://ahfriedman.com)
 * @brief File to handle running the compiler
 * @version 0.1
 * @date 2024-02-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Compile.h"

std::filesystem::path getRelativePath(std::filesystem::path& currentPath, std::filesystem::path& given)
{
    return given.string().starts_with(currentPath.string()) 
        ? std::filesystem::relative(given, currentPath)
        : given; 
}


std::vector<std::string> pathToIdentifierSteps(std::filesystem::path& relPath)//std::filesystem::path& currentPath, std::filesystem::path& given)
{
    std::vector<std::string> parts; 

    for(auto it : relPath)
    {
        parts.push_back(it);
    }

    return parts; 
} 

int compile(std::string argSrcPath, std::string argBuildPath, std::string outputFileName, std::vector<std::string> inputFileName, bool demoMode, bool isVerbose, DisplayMode toStringMode, bool printOutput, bool noCode, CompileType compileWith)
{
    // FIXME: ENABLE SEPARATELY?
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    auto TargetTriple = llvm::sys::getDefaultTargetTriple();

    std::string Error;
    auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

    // Print an error and exit if we couldn't find the requested target.
    // This generally occurs if we've forgotten to initialise the
    // TargetRegistry or we have a bogus target triple.
    if (!Target)
    {
        std::cerr << Error << std::endl;
        return 1;
    }

    auto CPU = "generic";
    auto Features = "";

    llvm::TargetOptions opt;
    auto RM = llvm::Optional<llvm::Reloc::Model>();
    auto TheTargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

    // TODO: need to verify canonical src starts with current path? maybe? probably not
    auto currentPath = std::filesystem::current_path();
    auto providedSrc = currentPath / argSrcPath;

    std::error_code pathEc;
    auto canonicalSrc = std::filesystem::canonical(providedSrc, pathEc);
    if (pathEc)
    {
        std::cerr << pathEc.message() << std::endl;
        return -1;
    }

    // TODO: a bit inefficient in teh case that build is "" as we already calculated src
    auto providedDst = currentPath / (argBuildPath == "" ? argSrcPath : (std::string)argBuildPath);
    auto canonicalDst = std::filesystem::canonical(providedDst, pathEc);
    if (pathEc)
    {
        std::cerr << pathEc.message() << std::endl;
        return -1;
    }

    if (inputFileName.empty())
    {
        std::cerr << "No files to compile were provided." << std::endl;
        std::exit(-1);
    }

    /******************************************************************
     * Now that we have the input, we can perform the first stage:
     * 1. Create the lexer from the input.
     * 2. Create the parser with the lexer's token stream as input.
     * 3. Parse the input and get the parse tree for then exit stage.
     * 4. TBD: handle errors
     ******************************************************************/

    /*******************************************************************
     * Prepare Input
     * ================================================================
     *
     * To do this, we  must first check if we were given a string
     * input or file(s). To make both cases easy to handle later on,
     * we create a vector of input streams/output file pairs.
     *******************************************************************/
    std::set<std::filesystem::path> visitedPaths; // TODO: verify & do better, Tracking that we dont have duplicate paths
    std::vector<CompilerInput> inputs;

    bool useOutputFileName = outputFileName != "-.ll";

    // For each file name, make sure the file exist. If so, create an input stream to it
    // and set its output filename to be the provided name (if we are compiling just
    // one file, and a name was provided), or the file's name but with the extension
    // extension replaced with .ll
    for (auto fileName : inputFileName)
    {
        auto providedPath = canonicalSrc / fileName;
        auto canonicalPath = std::filesystem::canonical(providedPath, pathEc);
        if (pathEc)
        {
            std::cerr << pathEc.message() << std::endl;
            return -1;
        }

        if (visitedPaths.contains(canonicalPath))
        {
            std::cerr << "File provided to compiler multiple times: " << fileName << " at " << canonicalPath << std::endl;
            return -1;
        }

        visitedPaths.insert(canonicalPath);

        std::filesystem::path relInputPath = getRelativePath(canonicalSrc, std::filesystem::path(canonicalPath).replace_extension(""));

        // FIXME: DETERMINE OUTPUT FILE NAME!
        // FIXME: CURRENTLY, THIS ADDS SRCPATH To errors! Need to only do relative to src!!

        std::cout << "CAN. SRC " << canonicalSrc << std::endl;
        std::cout << "CAN. PAH " << canonicalPath << std::endl;
        std::cout << "CAN. DST " << canonicalDst << std::endl;
        std::cout << "FUL. DST " << (canonicalDst / fileName) << std::endl;
        std::cout << "REL. INP " << relInputPath << std::endl;
        std::cout << "FLE. NME " << fileName << std::endl;
        auto a = new antlr4::ANTLRFileStream();
        a->loadFromFile(canonicalPath);
        inputs.push_back(
            CompilerInput(
                a,
                canonicalDst / fileName,
                // (!(inputFileName.size() > 1) && useOutputFileName)
                //   ? outputFileName
                //   : fileName.substr(0, fileName.find_last_of('.')),
                pathToIdentifierSteps(relInputPath)));
    }

    bool isValid = true;
    STManager *stm = new STManager();

    // For each input...
    for (auto input : inputs)
    {
        std::cout << "2253" << input.inputStream->getSourceName() << std::endl;
        /*******************************************************************
         * Create the Lexer from the input.
         * ================================================================
         *
         * Run the lexer on the input
         *******************************************************************/
        BismuthLexer lexer(input.inputStream); // TODO: Do there need to be leer errors -> Doesn't seem like it?
        antlr4::CommonTokenStream tokens(&lexer);

        /*******************************************************************
         * Create + Run the Parser
         * ================================================================
         *
         * Run the parser on our previously generated tokens
         *******************************************************************/
        BismuthParser parser(&tokens);
        parser.removeErrorListeners();
        BismuthSyntaxErrorListener *syntaxListener = new BismuthSyntaxErrorListener();
        parser.addErrorListener(syntaxListener);
        // delete syntaxListener;

        // Run The parser
        BismuthParser::CompilationUnitContext *tree = NULL;
        tree = parser.compilationUnit();

        if (syntaxListener->hasErrors(0)) // Want to see all errors.
        {
            std::cerr << syntaxListener->errorList() << std::endl;
            isValid = false; // Shouldn't be needed
            return -1;
        }

        /*
         * Sets up compiler flags. These need to be sent to the visitors.
         */

        int flags = (demoMode) ? CompilerFlags::DEMO_MODE : 0;

        std::cout << "316 ";
        for (auto s : input.pathSteps)
        {
            std::cout << s << "::";
        }
        std::cout << std::endl;

        /*******************************************************************
         * Semantic Analysis
         * ================================================================
         *
         * Perform semantic analysis and populate the symbol table
         * and bind nodes to Symbols using the property manager. If
         * there are any errors we print them out and exit.
         *******************************************************************/
        SemanticVisitor *sv = new SemanticVisitor(stm, toStringMode, flags);
        auto TypedOpt = sv->visitCtx(tree, input.pathSteps); // FIXME: DO BETTER W/ NAME TO SHOW THIS IS TOP LEVEL UNIT

        if (sv->hasErrors(0)) // Want to see all errors
        {
            std::cerr << "Semantic analysis completed for " << input.outputPath << " with errors: " << std::endl;
            std::cerr << sv->getErrors() << std::endl;
            isValid = false;
            continue;
        }

        if (std::holds_alternative<ErrorChain *>(TypedOpt))
        {
            // SHouldn't be possible, but somehow it cah happen....?)
            std::cerr << "Failed to generate Typed AST" << std::endl;
            std::cerr << std::get<ErrorChain *>(TypedOpt)->toString() << std::endl;
            isValid = false;
            continue;
        }

        TCompilationUnitNode *cu = std::get<TCompilationUnitNode *>(TypedOpt); // TypedOpt.value();

        if (isVerbose)
        {
            std::cout << "Semantic analysis completed for " << input.outputPath << " without errors. Starting code generation..." << std::endl;
        }

        /*******************************************************************
         * Code Generation
         * ================================================================
         *
         * If we have yet to receive any errors for the file, then
         * generate code for it.
         *******************************************************************/
        CodegenVisitor *cv = new CodegenVisitor("BismuthProgram", toStringMode, flags);
        cv->visitCompilationUnit(cu);
        if (cv->hasErrors(0)) // Want to see all errors
        {
            std::cerr << cv->getErrors() << std::endl;
            isValid = false;
            continue;
        }

        // Print out the module contents.
        llvm::Module *module = cv->getModule();

        if (printOutput)
        {
            std::cout << std::endl
                      << std::endl;
            cv->modPrint();
        }

        // Dump the code to an output file
        if (!noCode)
        {
            std::string irFileName = input.outputPath.replace_extension(".ll");
            std::cout << "outpath " << input.outputPath << std::endl;
            std::error_code ec;
            llvm::raw_fd_ostream irFileStream(irFileName, ec);
            module->print(irFileStream, nullptr);
            irFileStream.flush();

            if (ec)
            {
                std::cerr << ec.message() << std::endl;
                return -1;
            }
        }

        if (isVerbose)
        {
            std::cout << "Code generation completed for " << input.outputPath << "." << std::endl;
        }

        if (compileWith != none)
        {
            module->setDataLayout(TheTargetMachine->createDataLayout());

            std::string Filename = input.outputPath.replace_extension(".o");
            std::cout << "Filename " << Filename << std::endl;
            std::error_code EC;
            llvm::raw_fd_ostream dest(Filename, EC, llvm::sys::fs::OF_None);

            if (EC)
            {
                std::cerr << "Could not open file: " << EC.message() << std::endl;
                return 1;
            }

            llvm::legacy::PassManager pass;
            auto FileType = llvm::CGFT_ObjectFile;

            if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType))
            {
                std::cerr << "TheTargetMachine can't emit a file of this type" << std::endl;
                return 1;
            }

            pass.run(*module);
            dest.flush();

            std::cout << "Wrote " << Filename << std::endl;
        }
    }

    if (isValid && compileWith != none)
    {
        std::ostringstream cmd;

        switch (compileWith)
        {
        case clang:
        case clangll:
            cmd << "clang++ ";
            break;
        case gcc:
            cmd << "g++ ";
            break;
        case none:
            return -1; // Not even possible
        }

        std::string ext = compileWith == clangll ? ".ll" : ".o";
        for (auto input : inputs)
        {
            std::cout << "477!!! " << input.outputPath << std::endl;
            cmd << input.outputPath.replace_extension(ext) << " ";
        }

        // cmd << "./runtime.o -no-pie ";
        cmd << "./bdwgc/libgc.a ./bdwgc/libgccpp.a ./build/bin/runtime/libbismuth_runtime_archive.a -no-pie";

        if (useOutputFileName)
        {
            cmd << "-o " << outputFileName;
        }
        std::cout << cmd.str() << std::endl;

        std::cout << exec(cmd.str()) << std::endl;
    }

    return 0;
}