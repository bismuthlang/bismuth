/**
 * @file bismuthc.cpp
 * @brief
 * @version 0.1
 * @date 2022-09-07
 *
 * @copyright Copyright (c) 2022
 */

#include "bismuthc.h"

llvm::cl::OptionCategory CLIOptions("Bismuth CLI Options");
static llvm::cl::list<std::string>
    inputFileName(llvm::cl::Positional,
                  llvm::cl::desc("<input files>"),
                  // llvm::cl::init("-")
                  llvm::cl::ZeroOrMore,
                  llvm::cl::cat(CLIOptions));

static llvm::cl::opt<bool>
    printOutput("p",
                llvm::cl::desc("Print the IR"),
                llvm::cl::cat(CLIOptions));

static llvm::cl::opt<std::string>
    outputFileName("o",
                   llvm::cl::desc("supply alternate output file"),
                   llvm::cl::value_desc("output file"),
                   llvm::cl::init("-.ll"),
                   llvm::cl::cat(CLIOptions));

static llvm::cl::opt<bool>
    noCode("nocode",
           llvm::cl::desc("Do not generate any output file"),
           llvm::cl::cat(CLIOptions));

static llvm::cl::opt<bool>
    demoMode("demo-mode",
             llvm::cl::desc("Demo mode for web editor: main programs required & limited imports"),
             llvm::cl::cat(CLIOptions));

static llvm::cl::opt<bool>
    isVerbose("verbose",
              llvm::cl::desc("If true, compiler will print out status messages; if false (default), compiler will only print errors."),
              llvm::cl::init(false),
              llvm::cl::cat(CLIOptions));

// If not specified, the compiler will use the file's fully qualified path as its 
// path. Otherwise, the specified path will be removed from the beginning of the generated FQNs 
// (equivalent to running the name mangling out of the TLD specified)/
static llvm::cl::opt<std::string>
    argSrcPath("src-path",
                llvm::cl::desc("Specifies the directory to look for source files in. Commonly used as ./src when compiling with multiple modules."),
                llvm::cl::value_desc("source path"),
                llvm::cl::init("."),
                llvm::cl::cat(CLIOptions));

// If not specified, the compiler will build generated files into the same directory as 
// as the source files. Otherwise, the generated files will be placed in the mirrored locations
// within the specified build path. 
static llvm::cl::opt<std::string>
    argBuildPath("build-path",
                llvm::cl::desc("Specifies the directory to write generated files to."),
                llvm::cl::value_desc("output directory"),
                llvm::cl::init(""),
                llvm::cl::cat(CLIOptions));   
                           

enum CompileType
{
  none,
  clang,
  gcc,
  clangll,
};

static llvm::cl::opt<CompileType>
    compileWith("compile",
                llvm::cl::desc("If set, will compile to an executable with the specified compiler."),
                llvm::cl::values(
                    clEnumVal(none, "Will not generate an executable"),
                    clEnumVal(clang, "Will generate an executable using clang++"),
                    clEnumVal(gcc, "Will generate an executable using g++"),
                    clEnumVal(clangll, "Will generate an executable using clang++ on the .ll files (will still attempt to generate object files)")),
                llvm::cl::init(none),
                llvm::cl::cat(CLIOptions));

static llvm::cl::opt<DisplayMode>
    toStringMode("display-mode",
                llvm::cl::desc("Determines how types should be rendered in compiler messages (error, warning, debug, info, etc)"),
                llvm::cl::values(
                    clEnumVal(C_STYLE, "Displays types as they would be written in the code"),
                    clEnumVal(MATH_STYLE, "Renders types using mathematical notation common in theory")),
                llvm::cl::init(C_STYLE),
                llvm::cl::cat(CLIOptions));                
/**
 * @brief Main compiler driver.
 */
int main(int argc, const char *argv[])
{
  /******************************************************************
   * Command line handling from the llvm::cl classes.
   * @see https://llvm.org/docs/CommandLine.html
   * ******************************************************************/
  llvm::cl::HideUnrelatedOptions(CLIOptions);
  // Note: Sub zero font
  llvm::cl::SetVersionPrinter([](llvm::raw_ostream &o)
                              { o << R""""( 
 ______     __     ______     __    __     __  __     ______   __  __    
/\  == \   /\ \   /\  ___\   /\ "-./  \   /\ \/\ \   /\__  _\ /\ \_\ \   
\ \  __<   \ \ \  \ \___  \  \ \ \-./\ \  \ \ \_\ \  \/_/\ \/ \ \  __ \  
 \ \_____\  \ \_\  \/\_____\  \ \_\ \ \_\  \ \_____\    \ \_\  \ \_\ \_\ 
  \/_____/   \/_/   \/_____/   \/_/  \/_/   \/_____/     \/_/   \/_/\/_/ 
=========================================================================
Bismuth Process Calculus Compiler - Created by Alex Friedman (https://ahfriedman.com)
Website: https://bismuth-lang.org
Version: Pre-Alpha 1.3.3 @ )"""" << GIT_COMMIT_HASH <<  R""""(

ChangeLog
=========
1.3.4 - XXX: 
  - Added u32, i64, and u64
  - Added ability to specify integer values in hex via 0x and binary via 0b prefixes
  - Added for loops
  - Added toChannel function to convert ty -> Channel<!+ty>
  - Added --display-mode to enable error messages to show types as they would appear in-code instead of mathematical representation
  - Now displaying number of errors on compile failure

  - Fixed bug where nested control flow would incorrectly process use of linear resources
  - Fixed typos in generated IR files, error messages, and compiler internals

  - Removed CLI feature -s to supply input string instead of file location; makes more sense to re-add in future as REPL.
  - Added new error type for internal/compiler errors. 
  - Improved efficiency of IPC by removing state to eliminate additional lookup step
  - Refactored code internals to promote compile speed (of Bismuth, not the Bismuth compiler)
  - Added ProtocolVisitor.cpp/.h and moved code relating to visiting protocols to there from SemanticVisitor.cpp/.h

1.3.3 - 2023-06-04:
  - Added ability to nest all type defs (struct, enum) in addition to programs and functions. 
  - Improved syntax, particularly of externs.
1.3.2 - 2023-06-04:
  - Added is_present function on ! protocols 
  - Added acceptIf to allow for better control over ! loops. 
  - Added copy(e) to allow for deep copying any non-linear e
  - Added changelog to version (temporary location)

)""""; });
  llvm::cl::ParseCommandLineOptions(argc, argv);

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
  auto providedSrc = currentPath / (std::string) argSrcPath; 
  
  std::error_code pathEc; 
  auto canonicalSrc = std::filesystem::canonical(providedSrc, pathEc);
  if (pathEc)
  {
    std::cerr << pathEc.message() << std::endl;
    return -1;
  }

  // TODO: a bit inefficient in teh case that build is "" as we already calculated src
  auto providedDst = currentPath / (argBuildPath == "" ?  (std::string) argSrcPath :  (std::string) argBuildPath); 
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
  std::set<std::filesystem::path> visitedPaths; // TODO: verufy & do better, Tracking that we dont have duplicate paths 
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

    if(visitedPaths.contains(canonicalPath))
    {
      std::cerr << "File provided to compiler multiple times: " << fileName << " at " << canonicalPath << std::endl; 
      return -1; 
    }

    visitedPaths.insert(canonicalPath);


    std::filesystem::path relInputPath = getRelativePath(canonicalSrc,  std::filesystem::path(canonicalPath).replace_extension("")); 

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
    // TODO: THIS DOESN'T WORK IF NOT GIVEN A PROPER FILE EXTENSION
    inputs.push_back(
      CompilerInput(
        a,
        canonicalDst / fileName, 
        // (!(inputFileName.size() > 1) && useOutputFileName) 
        //   ? outputFileName 
        //   : fileName.substr(0, fileName.find_last_of('.')),
        pathToIdentifierSteps(relInputPath) // FIXME: WRONG
    ));
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
    for(auto s : input.pathSteps)
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
      std::cout << "outpath "<< input.outputPath << std::endl; 
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
