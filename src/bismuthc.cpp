/**
 * @file bismuthc.cpp
 * @brief
 * @version 0.1
 * @date 2022-09-07
 *
 * @copyright Copyright (c) 2022
 */

#include "bismuthc.h"
#include "llvm/Support/CommandLine.h"

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
Version: Pre-Alpha 1.3.6 @ )"""" << GIT_COMMIT_HASH
                                    << R""""(

ChangeLog
=========
1.3.7 - 2025-02-09: 
BREAKING 
  - Entry point changed from `program` to `main`

Features
  - Syntax improvements: removed the `define` keyword, added `prog` keyword, and now specification of `Channel` in programs is implicit
  - Added in "error-flows" which allows error messages to be displayed in a tree to get a better sense of how an error originated

Compiler Internals
  - Refactored various visitors
  - Improved some error messages

1.3.6 - 2025-01-03: 
BREAKING (Compiler Internals)
  - Sum types and internal/external choices now have their tag value determined by the `C_STYLE` internal representation of the type instead of the LLVM-IR string representation due to introduction of opaque pointers
  - Per upgrading LLVM, a new docker image has been introduced. For older builds, be sure to specify the v1.3.5 tag to continue development.
 
Features
  - Added support for Nix via flakes
  - Improved documentation for getting started with and using Bismuth codebase

Compiler Internals
  - Updated from LLVM-12 to LLVM-19
  - Updated from Clang-14 to Clang-19 (docker) or GCC (Nix)
  - Test cases now use files instead of hashes to make identifying changes easier

Outstanding Issues
  - Due to minor differences between Clang and GCC, not all test cases pass on GCC  (see 0789b91)
  - Coverage is only supported via Docker image and clang; some instabilities with coverage appear to occasionally occur

1.3.5 - 2024-12-22: 
Bugs
  - Corrects array accesses to use unsigned numbers instead of signed
  - Addresses several small bugs with inferring integer types & improves handling of generics

1.3.4 - 2024-05-03: 
Features
  - Added ability to use labels for describing internal and external choice alternatives
  - Added dynamically sized arrays
  - Added `Cancelable<>` session type modality
  - Return statements can be omitted in functions that return `Unit`. 
  - Added Logical & Arithmetic Right Bit Shift, Left Bit Shift, Bit XOR/AND/OR
  - Added imports, basic name mangling, and generics/templates
  - Added `u32`, `i64`, and `u64` (`int` and `i32` are now interchangeable)
  - Added ability to specify integer values in hex via 0x and binary via 0b prefixes
  - Added for loops
  - Added `toChannel` function to convert `ty` -> `Channel<!+ty>` or `ty[]` -> `Channel<!+ty>` in the case of arrays
  - Added `--display-mode` CLI option to enable error messages to show types as they would appear in-code instead of mathematical representation
  - Now displaying number of errors on compile failure

Bugs 
  - Fixed bug wherein `T_1 -> T_2[]` is ambiguous by allowing `(T_1 -> T_2)[]`
  - Improved syntax and handling of l-values to enable expressions like improved syntax to allow *(expr).<field> syntax, 
  - Fixed bug where nested control flow would incorrectly process use of linear resources
  - Fixed typos in generated IR files, error messages, and compiler internals

Compiler Internals
  - Reorganized compiler internals to separate CLI elements and support generics
  - Refactored symbol/allocation handling by connecting them to FQNs instead of symbols
  - Reorganized compilation order to conduct codegen after all of semantic analysis
  - Removed CLI feature `-s` to supply input string instead of file location; makes more sense to re-add in future as REPL.
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

    compileFiles(
        argSrcPath, 
        argBuildPath, 
        outputFileName, 
        inputFileName, 
        demoMode, 
        isVerbose, 
        toStringMode, 
        printOutput, 
        noCode, 
        compileWith
    );
    
    return 0;
}
