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

#include "BismuthLexer.h"
#include "CompilerFlags.h"
#include "SemanticVisitor.h"
#include "CodegenVisitor.h"
#include "ExecUtils.h"

// #include "llvm/TargetParser/Optional.h"
#include "llvm/Object/ObjectFile.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/TargetSelect.h"

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

std::vector<CompilerInput *> getInputsFromFiles(std::string argSrcPath, std::string argBuildPath, std::vector<std::string> inputFileName)
{
    // TODO: need to verify canonical src starts with current path? maybe? probably not
    auto currentPath = std::filesystem::current_path();
    auto providedSrc = currentPath / argSrcPath;

    std::error_code pathEc;
    auto canonicalSrc = std::filesystem::canonical(providedSrc, pathEc);
    if (pathEc)
    {
        std::cerr << pathEc.message() << std::endl;
        std::exit(-1); // TODO: do something better than exit
    }

    // TODO: a bit inefficient in teh case that build is "" as we already calculated src
    auto providedDst = currentPath / (argBuildPath == "" ? argSrcPath : (std::string)argBuildPath);
    auto canonicalDst = std::filesystem::canonical(providedDst, pathEc);
    if (pathEc)
    {
        std::cerr << pathEc.message() << std::endl;
        std::exit(-1);
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
    std::vector<CompilerInput *> inputs;

    // bool useOutputFileName = outputFileName != "-.ll";

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
            std::exit(-1);
        }

        if (visitedPaths.contains(canonicalPath))
        {
            std::cerr << "File provided to compiler multiple times: " << fileName << " at " << canonicalPath << std::endl;
            std::exit(-1);
        }

        visitedPaths.insert(canonicalPath);

        std::filesystem::path relInputPath = getRelativePath(canonicalSrc, std::filesystem::path(canonicalPath).replace_extension(""));

        auto a = new antlr4::ANTLRFileStream();
        a->loadFromFile(canonicalPath);
        inputs.push_back(
            new FileInput(
                a,
                pathToIdentifierSteps(relInputPath),
                canonicalDst / fileName
        ));
    }

    return inputs; 
}

llvm::TargetMachine * getTargetMachine()
{
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
        std::exit(-1);
    }

    auto CPU = "generic";
    auto Features = "";

    llvm::TargetOptions opt;
    auto RM = std::optional<llvm::Reloc::Model>();
    auto TheTargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);
    return TheTargetMachine; 
}



std::vector<std::pair<BismuthParser::CompilationUnitContext *, CompilerInput *>> Stage_lexParse(std::vector<CompilerInput *> inputs)
{
    bool valid = true;

    std::vector<std::pair<BismuthParser::CompilationUnitContext *, CompilerInput *>> ans;

    for (auto input : inputs)
    {
        /*******************************************************************
         * Create the Lexer from the input.
         * ================================================================
         *
         * Run the lexer on the input
         *******************************************************************/
        BismuthLexer lexer = BismuthLexer(input->getInputStream()); // TODO: Do there need to be lexer errors -> Doesn't seem like it?
        antlr4::CommonTokenStream * tokens = new antlr4::CommonTokenStream(&lexer);

        /*******************************************************************
         * Create + Run the Parser
         * ================================================================
         *
         * Run the parser on our previously generated tokens
         *******************************************************************/
        BismuthParser * parser = new BismuthParser(tokens);
        parser->removeErrorListeners();
        BismuthSyntaxErrorListener *syntaxListener = new BismuthSyntaxErrorListener();
        parser->addErrorListener(syntaxListener);

        // Run The parser
        BismuthParser::CompilationUnitContext * tree = nullptr;
        tree = parser->compilationUnit();

        if (syntaxListener->hasErrors(0)) // Want to see all errors.
        {
            std::cerr << syntaxListener->errorList() << std::endl;
            valid = false; // Shouldn't be needed
        }
        ans.push_back({tree, input});
        delete syntaxListener;
    }
    
    if(!valid) std::exit(-1);

    return ans; 
}

/*******************************************************************
 * Semantic Analysis
 * ================================================================
 *
 * Perform semantic analysis and populate the symbol table
 * and bind nodes to Symbols using the property manager. If
 * there are any errors we print them out and exit.
 *******************************************************************/
std::vector<std::pair<TCompilationUnitNode *, CompilerInput *>> Stage_PSemantic(std::vector<std::pair<BismuthParser::CompilationUnitContext *, CompilerInput *>> inputs, bool demoMode, bool isVerbose, DisplayMode toStringMode)
{
    // auto printErrors = [](ErrorChain *) {
    //     std::cerr << "Semantic analysis completed for " << input->getSourceName() << " with errors: " << std::endl;
    //     std::cerr << sv.getErrors() << std::endl;
    //     valid = false;
    //     // continue;
    // }
    /*
     * Sets up compiler flags. These need to be sent to the visitors.
     */

    int flags = (demoMode) ? CompilerFlags::DEMO_MODE : 0;

    bool valid = true;
    STManager stm = STManager();


    SemanticVisitor sv = SemanticVisitor(&stm, toStringMode, flags);

    // I wish there was an easy way to write programs (perhaps with constraints)
    // which is able to generate the following code, as it really is all algorithmic.
    // Eg, with Type T do XYZ
    std::vector<SemanticVisitor::ImportPhaseClosure> importClosures; 
    for(auto [tree, input] : inputs)
    {
        std::variant<
            SemanticVisitor::ImportPhaseClosure,
            ErrorChain *
        > opt = sv.phasedVisit(tree, input->getPathSteps());

        if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
        {
            // return (*e);
            valid = false; 
        }
        else
        {
            SemanticVisitor::ImportPhaseClosure clos = std::get<SemanticVisitor::ImportPhaseClosure>(opt);
            importClosures.push_back(clos); 
        }
    }

    if(!valid || sv.hasErrors(0))
    {
        std::cerr << sv.getErrors() << std::endl;
        std::exit(-1);
    }

    std::vector<SemanticVisitor::DefineFwdDeclsPhaseClosure> fwdDeclClosures; 
    for(auto importClos : importClosures)
    {
        std::variant<SemanticVisitor::DefineFwdDeclsPhaseClosure, ErrorChain *> opt = importClos(); 

        if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
        {
            // return (*e);
            valid = false; 
        }
        else
        {
            fwdDeclClosures.push_back(std::get<SemanticVisitor::DefineFwdDeclsPhaseClosure>(opt));
        }
    }

    if(!valid || sv.hasErrors(0))
    {
        std::cerr << sv.getErrors() << std::endl;
        std::exit(-1);
    }

    std::vector<SemanticVisitor::PhaseNClosure> nClosures; 
    for(auto fwdClos : fwdDeclClosures)
    {
        nClosures.push_back(
            fwdClos()
        ); 
    }

    if(!valid || sv.hasErrors(0))
    {
        std::cerr << sv.getErrors() << std::endl;
        std::exit(-1);
    }

    // Interesting how when we copy paste, we really would benefit from var renaming
    // to get compiler errors. 

    std::vector<std::pair<TCompilationUnitNode *, CompilerInput *>> ans;
    // for(auto nClos : nClosures)
    for(unsigned int i = 0; i < nClosures.size(); i++)
    {
        auto nClos = nClosures.at(i); 
        CompilerInput * input = inputs.at(i).second; 
        std::variant<TCompilationUnitNode *, ErrorChain *> opt = nClos(); 

        if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
        {
            // return (*e);
            valid = false; 
        }
        else 
        {
            ans.push_back({
                std::get<TCompilationUnitNode *>(opt),
                input
            });
        }
    }

    if(!valid || sv.hasErrors(0))
    {
        std::cerr << sv.getErrors() << std::endl;
        std::exit(-1);
    }

    return ans; 
}

void Stage_CodeGen(std::vector<std::pair<TCompilationUnitNode *, CompilerInput *>> inputs,  std::string outputFileName, bool demoMode, bool isVerbose, DisplayMode toStringMode, bool printOutput, bool noCode, CompileType compileWith)
{
    bool isValid = true;
    bool useOutputFileName = outputFileName != "-.ll";

    /*
     * Sets up compiler flags. These need to be sent to the visitors.
     */
    int flags = (demoMode) ? CompilerFlags::DEMO_MODE : 0;
    auto TheTargetMachine = (compileWith != none)  ? getTargetMachine() : nullptr; 


    for(auto entry : inputs)
    {
        auto [cu, input] = entry; 
        /*******************************************************************
         * Code Generation
         * ================================================================
         *
         * If we have yet to receive any errors for the file, then
         * generate code for it.
         *******************************************************************/
        CodegenVisitor cv = CodegenVisitor("BismuthProgram", toStringMode, flags);
        cv.visitCompilationUnit(*cu);
        if (cv.hasErrors(0)) // Want to see all errors
        {
            std::cerr << cv.getErrors() << std::endl;
            isValid = false;
            continue;
        }

        // Print out the module contents.
        llvm::Module *module = cv.getModule();

        if (printOutput)
        {
            std::cout << std::endl
                      << std::endl;
            cv.modPrint();
        }

        // Dump the code to an output file
        if (!noCode)
        {
            auto irOutOpt = input->getIROut(); 
            if (std::error_code *ec = std::get_if<std::error_code>(&irOutOpt))
            {
                std::cerr << ec->message() << std::endl; 
                return; 
            }
            
            llvm::raw_ostream * stream = std::get<llvm::raw_ostream *>(irOutOpt);

            module->print(*stream, nullptr);
            stream->flush();
        }

        if (isVerbose)
        {
            // should be output.getInputName()
            std::cout << "Code generation completed for " << input->getSourceName() << "." << std::endl;
        }

        if (compileWith != none)
        {
            module->setDataLayout(TheTargetMachine->createDataLayout());

            auto objOutOpt = input->getObjectOut(); 
             if (std::error_code *ec = std::get_if<std::error_code>(&objOutOpt))
            {
                std::cerr << ec->message() << std::endl; 
                return; 
            }

            llvm::raw_pwrite_stream * stream = std::get<llvm::raw_pwrite_stream *>(objOutOpt);

            llvm::legacy::PassManager pass;
            auto FileType = llvm::CodeGenFileType::ObjectFile;

            if (TheTargetMachine->addPassesToEmitFile(pass, *stream, nullptr, FileType))
            {
                std::cerr << "TheTargetMachine can't emit a file of this type" << std::endl;
                return;
            }

            pass.run(*module);
            stream->flush();

            // std::cout << "Wrote " << input.outputPath << std::endl;
        }
        delete cu;
    }

    // TODO: Separate out into separate stage
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
            return; // Not even possible
        }

        std::string ext = compileWith == clangll ? ".ll" : ".o";
        for (auto input : inputs)
        {
            assert(input.second->getOutputPath().has_value()); // TODO: better error!
            cmd << input.second->getOutputPath().value().replace_extension(ext) << " ";
        }

        // cmd << "./runtime.o -no-pie ";
        cmd << "./bdwgc/libgc.a ./bdwgc/libgccpp.a ./build/bin/runtime/libbismuth_runtime_archive.a -no-pie";

        if (useOutputFileName)
        {
            cmd << "-o " << outputFileName;
        }

        exec(cmd.str());
    }

}

int compile(
    std::vector<CompilerInput *> inputs, 
    std::string outputFileName, 
    bool demoMode, 
    bool isVerbose,
    DisplayMode toStringMode, 
    bool printOutput, 
    bool noCode, 
    CompileType compileWith)
{
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

    auto toCodegen = Stage_PSemantic(
        Stage_lexParse(inputs),
        demoMode, 
        isVerbose,
        toStringMode
    );

    Stage_CodeGen(
        toCodegen,
        outputFileName,
        demoMode,
        isVerbose,
        toStringMode,
        printOutput,
        noCode,
        compileWith
    );

    return 0;
}

int compileFiles(std::string argSrcPath, std::string argBuildPath, std::string outputFileName, std::vector<std::string> inputFileName, bool demoMode, bool isVerbose, DisplayMode toStringMode, bool printOutput, bool noCode, CompileType compileWith)
{
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
    std::vector<CompilerInput *> inputs = getInputsFromFiles(argSrcPath, argBuildPath, inputFileName);

    compile(
        inputs,
        outputFileName,
        demoMode,
        isVerbose,
        toStringMode,
        printOutput,
        noCode,
        compileWith
    );

    return 0;
}
