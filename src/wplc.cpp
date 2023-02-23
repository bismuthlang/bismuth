/**
 * @file wplc.cpp
 * @author ahfriedman & gpollice
 * @brief
 * @version 0.1
 * @date 2022-09-07
 *
 * @copyright Copyright (c) 2022
 */

#include "wplc.h"

llvm::cl::OptionCategory WPLCOptions("wplc Options");
static llvm::cl::list<std::string>
    inputFileName(llvm::cl::Positional,
                  llvm::cl::desc("<input files>"),
                  // llvm::cl::init("-")
                  llvm::cl::ZeroOrMore,
                  llvm::cl::cat(WPLCOptions));

static llvm::cl::opt<bool>
    printOutput("p",
                llvm::cl::desc("Print the IR"),
                llvm::cl::cat(WPLCOptions));

static llvm::cl::opt<std::string>
    inputString("s",
                llvm::cl::desc("Take input from a string, Do not use an input file if -s is used"),
                llvm::cl::value_desc("input string"),
                llvm::cl::init("-"),
                llvm::cl::cat(WPLCOptions));

static llvm::cl::opt<std::string>
    outputFileName("o",
                   llvm::cl::desc("supply alternate output file"),
                   llvm::cl::value_desc("output file"),
                   llvm::cl::init("-.ll"),
                   llvm::cl::cat(WPLCOptions));

static llvm::cl::opt<bool>
    noCode("nocode",
           llvm::cl::desc("Do not generate any output file"),
           llvm::cl::cat(WPLCOptions));

static llvm::cl::opt<bool>
    noRuntime("no-runtime",
              llvm::cl::desc("Program will not use the WPL runtime; Compiler will automatically treat program() as the entry point."),
              llvm::cl::cat(WPLCOptions));

static llvm::cl::opt<bool>
    isVerbose("verbose",
              llvm::cl::desc("If true, compiler will print out status messages; if false (default), compiler will only print errors."),
              llvm::cl::init(false),
              llvm::cl::cat(WPLCOptions));

enum CompileType
{
  none,
  clang,
  gcc
};

static llvm::cl::opt<CompileType>
    compileWith("compile",
                llvm::cl::desc("If set, will compile to an executable with the specified compiler."),
                llvm::cl::values(
                    clEnumVal(none, "Will not generate an executable"),
                    clEnumVal(clang, "Will generate an executable using clang++"),
                    clEnumVal(gcc, "Will generate an executable using g++")),
                llvm::cl::init(none),
                llvm::cl::cat(WPLCOptions));
/**
 * @brief Main compiler driver.
 */
int main(int argc, const char *argv[])
{
  /******************************************************************
   * Commandline handling from the llvm::cl classes.
   * @see https://llvm.org/docs/CommandLine.html
   * ******************************************************************/
  llvm::cl::HideUnrelatedOptions(WPLCOptions);
  // Note: Sub zero font
  llvm::cl::SetVersionPrinter([](llvm::raw_ostream &o)
                              { o << R""""( 
      ______   ______     __     ______     __    __    
     /\  == \ /\  == \   /\ \   /\  ___\   /\ "-./  \   
     \ \  _-/ \ \  __<   \ \ \  \ \___  \  \ \ \-./\ \  
      \ \_\    \ \_\ \_\  \ \_\  \/\_____\  \ \_\ \ \_\ 
       \/_/     \/_/ /_/   \/_/   \/_____/   \/_/  \/_/ 
     ===================================================
     Process Calculus Compiler - Created by Alex Friedman
     Website: https://ahfriedman.com
     Version: Pre-Alpha 1.0


       )""""; });
  llvm::cl::ParseCommandLineOptions(argc, argv);

  // FIXME: ENABLE SEPARATLEY?
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

  if (inputFileName.empty() && inputString == "-")
  {
    std::cerr << "Please enter a file or an input string to compile." << std::endl;
    std::exit(-1);
  }

  if (!inputFileName.empty() && inputString != "-")
  {
    std::cerr << "You can only have an input file or and input string, but not both" << std::endl;
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
  std::vector<std::pair<antlr4::ANTLRInputStream *, std::string>> inputs;

  bool useOutputFileName = outputFileName != "-.ll";

  // Case 1: We were given input files
  if (!inputFileName.empty())
  {
    // For each file name, make sure the file exist. If so, create an input stream to it
    // and set its output filename to be the provided name (if we are compiling just
    // one file, and a name was provided), or the file's name but with the .wpl
    // extension replaced with .ll
    for (auto fileName : inputFileName)
    {
      std::fstream *inStream = new std::fstream(fileName);

      if (inStream->fail())
      {
        std::cerr << "Error loading file: " << fileName << ". Does it exist?" << std::endl;
        std::exit(-1);
      }

      // TODO: THIS DOESN'T WORK IF NOT GIVEN A PROPER FILE EXTENSION
      inputs.push_back({new antlr4::ANTLRInputStream(*inStream),
                        (!(inputFileName.size() > 1) && useOutputFileName) ? outputFileName : fileName.substr(0, fileName.find_last_of('.'))});
    }
  }
  else
  {
    // As we were given a string input, create a new String input with the output file
    inputs.push_back({new antlr4::ANTLRInputStream(inputString),
                      outputFileName});
  }

  bool isValid = true;

  // For each input...
  for (auto input : inputs)
  {
    /*******************************************************************
     * Create the Lexer from the input.
     * ================================================================
     *
     * Run the lexer on the input
     *******************************************************************/
    WPLLexer lexer(input.first);
    antlr4::CommonTokenStream tokens(&lexer);

    /*******************************************************************
     * Create + Run the Parser
     * ================================================================
     *
     * Run the parser on our previously generated tokens
     *******************************************************************/
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLSyntaxErrorListener *syntaxListener = new WPLSyntaxErrorListener();
    parser.addErrorListener(syntaxListener);
    // delete syntaxListener;

    // Run The parser
    WPLParser::CompilationUnitContext *tree = NULL;
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

    int flags = (noRuntime) ? CompilerFlags::NO_RUNTIME : 0;

    /*******************************************************************
     * Semantic Analysis
     * ================================================================
     *
     * Perform semantic analysis and populate the symbol table
     * and bind nodes to Symbols using the property manager. If
     * there are any errors we print them out and exit.
     *******************************************************************/
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, flags);
    auto TypedOpt = sv->visitCtx(tree); // FIXME: DO BETTER W/ NAME TO SHOW THIS IS TOP LEVEL UNIT

    if (sv->hasErrors(0)) // Want to see all errors
    {
      std::cerr << "Semantic analysis completed for " << input.second << " with errors: " << std::endl;
      std::cerr << sv->getErrors() << std::endl;
      isValid = false;
      continue;
    }

    if (std::holds_alternative<ErrorChain *>(TypedOpt)) 
    {
      //SHouldn't be possible, but somehow it cah happen....?)
      std::cerr << "Failed to generate Typed AST" << std::endl;
      std::cerr << std::get<ErrorChain *>(TypedOpt)->toString() << std::endl;
      isValid = false;
      continue;
    }

    CompilationUnitNode *cu = std::get<CompilationUnitNode *>(TypedOpt); // TypedOpt.value();

    if (isVerbose)
    {
      std::cout << "Semantic analysis completed for " << input.second << " without errors. Starting code generation..." << std::endl;
    }
    /*******************************************************************
     * Code Generation
     * ================================================================
     *
     * If we have yet to recieve any errors for the file, then
     * generate code for it.
     *******************************************************************/
    CodegenVisitor *cv = new CodegenVisitor("WPLC.ll", flags);
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
      std::string irFileName = input.second + ".ll";
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
      if (noRuntime)
      {
        std::cout << "Code generation completed for " << input.second << ".wpl; program does NOT support runtime." << std::endl;
      }
      else
      {
        std::cout << "Code generation completed for " << input.second << ".wpl; program may require runtime." << std::endl;
      }
    }

    if (compileWith != none)
    {
      module->setDataLayout(TheTargetMachine->createDataLayout());

      std::string Filename = input.second + ".o";
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
      cmd << "clang++ ";
      break;
    case gcc:
      cmd << "g++ ";
      break;
    case none:
      return -1; // Not even possible
    }

    for (auto input : inputs)
    {
      cmd << input.second << ".o ";
    }

    // cmd << "./runtime.o -no-pie ";
    cmd << "./bdwgc/libgc.a ./bdwgc/libgccpp.a ./build/bin/runtime/libwpl_runtime_archive.a -no-pie";

    if (useOutputFileName)
    {
      cmd << "-o " << outputFileName;
    }

    std::cout << exec(cmd.str()) << std::endl;
  }

  return 0;
}
