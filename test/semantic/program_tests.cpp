#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include "antlr4-runtime.h"
#include "BismuthLexer.h"
#include "BismuthParser.h"
#include "BismuthErrorHandler.h"
#include "SemanticVisitor.h"

#include "CodegenVisitor.h"

#include "test_error_handlers.h"

using Catch::Matchers::ContainsSubstring;

void EnsureErrorsWithMessage(antlr4::ANTLRInputStream input, std::string message, int flags=0)
{
  BismuthLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager stm = STManager();
  SemanticVisitor sv = SemanticVisitor(stm, DisplayMode::C_STYLE, flags);
  auto cuOpt = sv.visitCtx(tree);

  REQUIRE(sv.hasErrors(0));
  REQUIRE_THAT(sv.getErrors(), ContainsSubstring(message));
}

void EnsureErrorsWithMessage(std::string program, std::string message, int flags=0)
{
  antlr4::ANTLRInputStream input(program);
  EnsureErrorsWithMessage(input, message, flags);
}

// TODO: does this use excess memory bc we dont free news?
TEST_CASE("programs/test4 - Don't allow void to be sent to fn", "[semantic]")
{
  auto stream = std::fstream("/home/shared/programs/test4.bismuth");
  EnsureErrorsWithMessage(
    antlr4::ANTLRInputStream(stream),
    "Cannot provide Unit to a function"
  );
}

TEST_CASE("programs/doubleArg1 - Prevent Argument reuse in func", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
define func foo (int a, int a, int b) {
  return; 
}
    )"""",
      "Re-use of previously defined parameter a");
}

TEST_CASE("programs/doubleArg2 - Prevent Argument reuse in extern", "[semantic]")
{
  auto stream = std::fstream("/home/shared/programs/doubleArg2.bismuth");
  EnsureErrorsWithMessage(
    antlr4::ANTLRInputStream(stream),
    "Re-use of previously defined parameter a"
  );
}

TEST_CASE("programs/doubleArg3 - Prevent Argument reuse in func and that we don't crash", "[semantic]")
{
  auto stream = std::fstream("/home/shared/programs/doubleArg3.bismuth");
  EnsureErrorsWithMessage(
    antlr4::ANTLRInputStream(stream),
    "Re-use of previously defined parameter a"
  );
}

TEST_CASE("programs/test15 - No array equalities", "[semantic]")
{
  auto stream = std::fstream("/home/shared/programs/test15.bismuth");
  EnsureErrorsWithMessage(
    antlr4::ANTLRInputStream(stream),
    "Cannot perform equality operation on arrays; they are always seen as unequal!"
  );
}

TEST_CASE("Comment EOF", "[semantic]")
{
  antlr4::ANTLRInputStream input(
      "# Hello # there!");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // auto lListener = TestErrorListener();
  // lexer.addErrorListener(&lListener);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  auto listener = TestErrorListener();
  parser.addErrorListener(&listener);

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);

  // Any errors should be syntax errors.
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();
  SemanticVisitor sv = SemanticVisitor(stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);

  CHECK_FALSE(sv.hasErrors(0));
}

TEST_CASE("programs/test16 - overwrite lhs var", "[semantic]")
{
  auto stream = std::fstream("/home/shared/programs/test16.bismuth");
  EnsureErrorsWithMessage(
    antlr4::ANTLRInputStream(stream),
    "Redeclaration of c"
  );
}

TEST_CASE("programs/test16a - overwrite lhs var - other way", "[semantic]")
{
  auto stream = std::fstream("/home/shared/programs/test16a.bismuth");
  EnsureErrorsWithMessage(
    antlr4::ANTLRInputStream(stream),
    "Redeclaration of c"
  );
}

TEST_CASE("programs/test16c - overwrite rhs var", "[semantic]")
{
  auto stream = std::fstream("/home/shared/programs/test16c.bismuth");
  EnsureErrorsWithMessage(
    antlr4::ANTLRInputStream(stream),
    "Redeclaration of c"
  );
}

TEST_CASE("programs/test16c-1 - overwrite rhs var - bubble up!", "[semantic]")
{
  auto stream = std::fstream("/home/shared/programs/test16c-1.bismuth");
  EnsureErrorsWithMessage(
    antlr4::ANTLRInputStream(stream),
    "Redeclaration of c"
  );
}

TEST_CASE("programs/test16c-2 - overwrite rhs var", "[semantic]")
{
  auto stream = std::fstream("/home/shared/programs/test16c-2.bismuth");
  EnsureErrorsWithMessage(
    antlr4::ANTLRInputStream(stream),
    "Redeclaration of c"
  );
}

TEST_CASE("programs/test16d - chain var", "[semantic]")
{
  auto stream = std::fstream("/home/shared/programs/test16d.bismuth");
  EnsureErrorsWithMessage(
    antlr4::ANTLRInputStream(stream),
    "Redeclaration of c"
  );
}

TEST_CASE("programs/test16e - chain var 2", "[semantic]")
{
  auto stream = std::fstream("/home/shared/programs/test16e.bismuth");
  EnsureErrorsWithMessage(
    antlr4::ANTLRInputStream(stream),
    "Uninferred types in context: [b, VAR]; [c, VAR]; [d, VAR]"
  );
}

TEST_CASE("programs/test16f - var loop", "[semantic]")
{
  std::fstream inStream = std::fstream("/home/shared/programs/test16f.bismuth");
  antlr4::ANTLRInputStream input = antlr4::ANTLRInputStream(inStream);

  BismuthLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager stm = STManager();

  SemanticVisitor sv = SemanticVisitor(stm, DisplayMode::C_STYLE);
  sv.visitCompilationUnit(tree);
  REQUIRE_FALSE(sv.hasErrors(0));
}

TEST_CASE("Demo Mode: Program is required", "[semantic][conditional]")
{
  EnsureErrorsWithMessage(
    R""""(
    )"""", 
    "When compiling in demo mode, 'program :: * : Channel<-int>' (the entry point) must be defined", 
    DEMO_MODE
  );
}

TEST_CASE("Demo Mode: Program is wrong type", "[semantic][conditional]")
{
  EnsureErrorsWithMessage(
    R""""(
define func program () {
  return; 
}
    )"""", 
    "When compiling in demo mode identifier 'program' must be defined as 'program :: * : Channel<-int>' (the entry point)", 
    DEMO_MODE
  );
}

TEST_CASE("Demo Mode: Program follows wrong protocol", "[semantic][conditional]")
{
  EnsureErrorsWithMessage(
    R""""(
define program :: c : Channel<-boolean> {
  c.send(false)
}
    )"""", 
    "In demo mode, 'program' must recognize a channel of protocol -int, not -boolean",
    DEMO_MODE
  );
}

TEST_CASE("Dead code in program block", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
    define func program () : int {

        return 1; 

        int a; 

        return 0;
    }
    )"""", 
    "Dead code");
}

TEST_CASE("Dead code in if/else", "[semantic][program][conditional]")
{
  EnsureErrorsWithMessage(
      R""""(
    define func program () : int {

    if true {
        return 0; 

        int a; 
    } else {
        return 1;

        int b; 
    }
}
    )"""", 
    "Dead code");
}

TEST_CASE("Dead code in select", "[semantic][program][select]")
{
  EnsureErrorsWithMessage(
      R""""(
define func foo (int idk) : int {

    select {
        true : {
            return 0;

            int a;
        }

        false : {
            return 1; 

            int b; 
        }
    }

    return 0; 
}
    )"""",
    "Dead code");
}

TEST_CASE("Infer In return", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
    var a; 
    # return a;
    c.send(a)
}
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // auto lListener = TestErrorListener();
  // lexer.addErrorListener(&lListener);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  auto pListener = TestErrorListener(); 
  parser.addErrorListener(&pListener);

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();
  SemanticVisitor sv = SemanticVisitor(stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);
  REQUIRE_FALSE(sv.hasErrors(ERROR));
}

TEST_CASE("Incorrect Argument Pass", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
# proc foo (int a) {
define func foo (int a) : int {

  return -1;
}

define program :: c : Channel<-int> = {
  foo("hello");  
  c.send(0)
}
    )"""", 
    "Argument 0 expected int but got str");
}

TEST_CASE("Invoke on Non-Function (str)", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> = {
  var x := "hey there!"; 
  x();
  c.send(0)
}
    )"""", 
    "Can only invoke functions, not str");
}

// FIXME: TYPE INFERENCE ON FUNCTIONS? AND TEST FUNCTION SUBTYPER!

TEST_CASE("Invoke on Non-Function (int)", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> = {
  var x := 10; 
  x();
  c.send(0)
}
    )"""",
    "Can only invoke functions, not int");
}

TEST_CASE("Redeclaration of function 1", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define func foo () : int {
  return 1;
}

define func foo () : str {
  return "";
}

define program :: c : Channel<-int> = {
  c.send(0)
}
    )"""", 
    "Unsupported redeclaration of foo");
}

TEST_CASE("Copy linear resources", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> = {
  var a := copy c; 
  c.send(0)
}
    )"""", 
    "Cannot perform a copy on a linear type: Channel<-int>");
}

TEST_CASE("Redeclaration of program 1", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define foo :: c : Channel<-int> = {
  c.send(1)
}

define foo :: c : Channel<-str> = {
  c.send("")
}

define program :: c : Channel<-int> = {
  c.send(0)
}
    )"""", 
    "Unsupported redeclaration of foo");
}

// TEST_CASE("Redeclaration of function 2", "[semantic][program]")
// {
//   antlr4::ANTLRInputStream input(
//       R""""(
//     int func foo() {
//       return 1;
//     }

//     proc  foo() {
//       return;
//     }
//     define program :: c : Channel<-int> = {
//       return 0;
//     }
//     )"""");
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // auto lListener = TestErrorListener();
//   // lexer.addErrorListener(&lListener);
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   auto pListener = TestErrorListener(); 
//   parser.addErrorListener(&pListener);

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager stmgr = STManager();
//
//   SemanticVisitor sv = SemanticVisitor(stmgr);

//   sv.visitCompilationUnit(tree);
//   REQUIRE(sv.hasErrors(ERROR));
// }

TEST_CASE("Redeclaration of function 3", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define func foo () : int {
  return 1;
}

define func foo() : int {
  return 1;
}
define program :: c : Channel<-int> = {
  c.send(0)
}
    )"""", 
    "Unsupported redeclaration of foo");
}

TEST_CASE("Redeclaration of program 3", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define foo :: c : Channel<-int> = {
  c.send(1)
}

define foo :: c : Channel<-int> = {
  c.send(1)
}

define program :: c : Channel<-int> = {
  c.send(0)
}
    )"""", 
    "Unsupported redeclaration of foo");
}

TEST_CASE("Redeclaration of function 4", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define func foo () : int {
  return 1;
}

define func foo (int a) : int {
  return 1;
}

define program :: c : Channel<-int> = {
  c.send(0)
}
    )"""", 
    "Unsupported redeclaration of foo");
}

TEST_CASE("Redeclaration of program 4", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define foo :: c : Channel<-int> = {
  c.send(1)
}

define foo :: c : Channel<+int;-int> = {
  int a := c.recv(); 
  c.send(1)
}

define program :: c : Channel<-int> = {
  c.send(0)
}
    )"""", 
    "Unsupported redeclaration of foo");
}

TEST_CASE("Redeclaration in extern", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
extern func foo() : int;
extern func foo(int a) : int;

define program :: c : Channel<-int> = {
  c.send(0)
}
    )"""", 
    "Unsupported redeclaration of foo");
}

TEST_CASE("Out of order function w/ forward declaration", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
extern func printf(...) : int;

extern func foo(str a) : int;

# str a := "hello";

define program :: c : Channel<-int> = {
    printf("hey!!"); 
    foo(); 
    # return 0;
    c.send(0)
}

# proc foo() {
define func foo (str a) {
    printf("a = %s\n", a);
}
    )"""", 
    "Unsupported redeclaration of foo");
}

// UNSED: GLOBAL
// TEST_CASE("Out of order function w/ forward declaration with Out of order global", "[semantic][program]")
// {
//   antlr4::ANTLRInputStream input(
//       R""""(
// extern int func printf(...);

// extern proc foo();

// define program :: c : Channel<-int> = {
//     foo();
//     return 0;
// }

// proc foo() {
//     printf("a = %s\n", a);
// }

// str a := "hello";
//     )"""");
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // auto lListener = TestErrorListener();
//   // lexer.addErrorListener(&lListener);
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   auto pListener = TestErrorListener(); 
//   parser.addErrorListener(&pListener);

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager stmgr = STManager();
//
//   SemanticVisitor sv = SemanticVisitor(stmgr);

//   sv.visitCompilationUnit(tree);
//   REQUIRE(sv.hasErrors(ERROR));
// }

TEST_CASE("Forward Decl with Variadic", "[semantic][program][function][forward-decl]")
{
  EnsureErrorsWithMessage(
      R""""(
extern func printf(...) : int;

extern func foo(int a, ...) : Unit; 

define program :: c : Channel<-int> = {
    foo(); 
    # return 0;
    c.send(0)
}

# proc foo(int a) {
define foo :: c : Channel<+int> = {
    int a := c.recv();
    # printf("a = %s\n", a);
    printf("a = %u\n", a);
  c.send(0)
}

    )"""", 
    "Unsupported redeclaration of foo");
}

TEST_CASE("Forward Decl with wrong num args", "[semantic][program][function][forward-decl]")
{
  EnsureErrorsWithMessage(
      R""""(
extern func printf(...) : int;

extern func foo(str a) : int;


define program :: c : Channel<-int> = {
    foo("hello"); 
    # return 0;
    c.send(0)
}

define func foo (str a, int b) : int {
    printf("a = %s\n", a);
    return 0;
}
    )"""",
    "Unsupported redeclaration of foo");
}

// UNUSED: SEEMS REDUNDANT
// TEST_CASE("Forward Decl with wrong num args and type", "[semantic][program][function][forward-decl]")
// {
//   antlr4::ANTLRInputStream input(
//       R""""(
// extern int func printf(...);

// extern proc foo(int a);

// define program :: c : Channel<-int> = {
//     foo();
//     return 0;
// }

// proc foo(int a, str b) {
//     printf("a = %s\n", a);
// }

// str a := "hello";
//     )"""");

//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // auto lListener = TestErrorListener();
//   // lexer.addErrorListener(&lListener);
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   auto pListener = TestErrorListener(); 
//   parser.addErrorListener(&pListener);

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager stmgr = STManager();
//
//   SemanticVisitor sv = SemanticVisitor(stmgr);

//   sv.visitCompilationUnit(tree);
//   REQUIRE(sv.hasErrors(ERROR));
// }

// UNUSED: SEEMS REDUNDANT
//  TEST_CASE("Forward Decl with wrong arg type", "[semantic][program][function][forward-decl]")
//  {
//    antlr4::ANTLRInputStream input(
//        R""""(
//  extern int func printf(...);

// extern proc foo(int a);

// define program :: c : Channel<-int> = {
//     foo();
//     return 0;
// }

// proc foo(str a) {
//     printf("a = %s\n", a);
// }

// str a := "hello";
//     )"""");

//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // auto lListener = TestErrorListener();
//   // lexer.addErrorListener(&lListener);
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   auto pListener = TestErrorListener(); 
//   parser.addErrorListener(&pListener);

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager stmgr = STManager();
//
//   SemanticVisitor sv = SemanticVisitor(stmgr);

//   sv.visitCompilationUnit(tree);
//   REQUIRE(sv.hasErrors(ERROR));
// }

TEST_CASE("Wrong UnaryNot", "[semantic][program][bool]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> {
    boolean a := ~0; 
    c.send(0)
}
    )"""", 
    "Expression of type int cannot be assigned to boolean");
}

TEST_CASE("Wrong UnaryMinus", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> {
    int a := -"hey"; 
    c.send(0)
}
    )"""", 
    "Signed number (e.g., int or i64) expected in unary minus, but got str");
}

TEST_CASE("Wrong RHS Arithmetic", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> {
    int a := 0 - "hey?"; 
    c.send(0)
}
    )"""", 
    "Operator - cannot be applied between int and str. Expected int - int");
}

TEST_CASE("Wrong LogAnd LHS", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> {
    boolean a := 1 && false; 
    c.send(0)
}
    )"""",
    "boolean expression expected, but was int");
}

TEST_CASE("Wrong LogAnd RHS", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> {
    boolean a := false && 1; 
    c.send(0)
}
    )"""", 
    "boolean expression expected, but was int");
}

TEST_CASE("Wrong LogOr LHS", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> {
    boolean a := 1 || false; 
    c.send(0)
}
    )"""", 
    "Expected boolean but got int");
}

TEST_CASE("Wrong LogOr RHS", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> {
    boolean a := false || 1; 
    c.send(0)
}
    )"""",
    "Expected boolean but got int");
}

TEST_CASE("Field Access - var", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> {
    var a;
    var b := a.length; 
    c.send(0);
}
    )"""", 
    "Cannot access length on VAR");
}

TEST_CASE("Field Access - int", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> {
    int a;
    var b := a.length; 
    c.send(0);
}
    )"""", 
    "Cannot access length on int");
}

// TODO: does it cause errors that we print types as all caps but define them as diff case?

TEST_CASE("ArrayAccess - Wrong Type", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> {
    int [5] a;
    var b := a[true || false];
    c.send(0)
}
    )"""",
    "Array access index expected type u32 but got boolean");
}

TEST_CASE("Field Access - Unsupported/Undefined", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> {
    int [5] a;
    var b := a.testing; 
    c.send(0);
}
    )"""", 
    "Cannot access testing on int[5]");
}

TEST_CASE("Field Access - Undefined Var", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> {
    var b := a.testing; 
    c.send(0);
}
    )"""", 
    "Undefined variable reference: a");
}

TEST_CASE("Equals Different types", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> {
    var a := "hello" == 1; 
    c.send(0);
}
    )"""", 
    "Both sides of '=' must have the same type");
}

TEST_CASE("Assign to undefined", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> = {
  a := 10; 
  c.send(0);
}
    )"""", 
    "Undefined variable reference: a");
}

TEST_CASE("Proc Returning", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
# proc foo() {
define func foo () {
  return 1;
}

define program :: c : Channel<-int> = {
  c.send(0)
}
    )"""", 
    "Expected return type of Unit but got int");
}

TEST_CASE("Function return nothing", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
# int func foo() {
define func foo (int x) : int {
  return;
}
define program :: c : Channel<-int> = {
  # return 0; 
  c.send(0)
}
    )"""",
    "Expected to return a int but received nothing");
}

TEST_CASE("Function return wrong type", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> = {
  c.send("hey"); 
}
    )"""", 
    "Failed to send str over channel [c, Channel<-int>]");
}

TEST_CASE("Nested Local Functions - Disallow Local vars 1", "[semantic][program][local-function]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> = {
  var a := 0; 

  define func foo (Channel<-int> c) : Channel<-int> {
    a := 2; 
    return c; 
  }

  c.send(0)
}
    )"""", 
    "Undefined variable reference: a");
}

TEST_CASE("Nested Local Program - Disallow Local vars 1", "[semantic][program][local-function]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> = {
  var a := 0; 

  define foo :: c : Channel<-int> = {
    c.send(a)
  }

  c.send(0); 
}
    )"""",
    "Undefined variable reference: a");
}

// TEST_CASE("Nested Local Functions - Disallow Local vars 2", "[semantic][program][local-function]")
// {
//   antlr4::ANTLRInputStream input(
//       R""""(
//     define program :: c : Channel<-int> = {
//       var a := 0;

//       proc foo() {
//         var a;
//         a := 2;
//       }

//       return 0;
//     }
//     )"""");
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // auto lListener = TestErrorListener();
//   // lexer.addErrorListener(&lListener);
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   auto pListener = TestErrorListener(); 
//   parser.addErrorListener(&pListener);

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager stmgr = STManager();
//

//   SemanticVisitor sv = SemanticVisitor(stmgr);

//   sv.visitCompilationUnit(tree);
//   REQUIRE_FALSE(sv.hasErrors(ERROR));
// }

TEST_CASE("Nested Local Functions - Disallow Local vars 3 - f2f", "[semantic][program][local-function]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
  define func other (int a) : int {
    var c := 10; 
    return a;
  }

  define func foo (int x) : int {
      return other(x); 
  }

  c.send(0)
}
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // auto lListener = TestErrorListener();
  // lexer.addErrorListener(&lListener);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  auto pListener = TestErrorListener(); 
  parser.addErrorListener(&pListener);

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();

  SemanticVisitor sv = SemanticVisitor(stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);
  REQUIRE_FALSE(sv.hasErrors(ERROR));
}

TEST_CASE("Nested Local Functions - Disallow Local vars 3 - f2p", "[semantic][program][local-function]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
  define func other (int a) : int {
    var c := 10; 
    return a;
  }

  define foo :: c : Channel<+int;-int> = {
    int x := c.recv(); 
    c.send(other(x))
  }

  c.send(0)
}
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // auto lListener = TestErrorListener();
  // lexer.addErrorListener(&lListener);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  auto pListener = TestErrorListener(); 
  parser.addErrorListener(&pListener);

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();

  SemanticVisitor sv = SemanticVisitor(stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);
  REQUIRE_FALSE(sv.hasErrors(ERROR));
}

TEST_CASE("Nested Local Functions - Disallow Local vars 3 - p2f", "[semantic][program][local-function]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
  define other :: io : Channel<-int> = {
    var c := 10; 
    io.send(c)
  }

  define func foo (int y) : int {
      Channel<+int> c := exec other; 
      int x := c.recv(); 
      return x;
  }

  c.send(0)
}
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // auto lListener = TestErrorListener(); 
  // lexer.addErrorListener(&lListener);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  auto pListener = TestErrorListener(); 
  parser.addErrorListener(&pListener);

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();

  SemanticVisitor sv = SemanticVisitor(stmgr, DisplayMode::C_STYLE);

  // sv.visitCompilationUnit(tree);
  // REQUIRE_FALSE(sv.hasErrors(ERROR));
  auto TypedOpt = sv.visitCtx(tree);
  REQUIRE_FALSE(sv.hasErrors(ERROR));
  REQUIRE(std::holds_alternative<TCompilationUnitNode *>(TypedOpt));
}

TEST_CASE("Nested Local Functions - Disallow Local vars 3 - p2p", "[semantic][program][local-function]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
  define other :: io : Channel<-int> = {
    var c := 10; 
    io.send(c)
  }

  define foo :: io : Channel<-int> = {
    Channel<+int> c := exec other; 
    int ans := c.recv(); 
    io.send(ans)
  }

  c.send(0)
}
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  //   // auto lListener = TestErrorListener();
  //   // lexer.addErrorListener(&lListener);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  auto pListener = TestErrorListener(); 
  parser.addErrorListener(&pListener);

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();

  SemanticVisitor sv = SemanticVisitor(stmgr, DisplayMode::C_STYLE);

  auto TypedOpt = sv.visitCtx(tree);
  // sv.visitCompilationUnit(tree);
  REQUIRE_FALSE(sv.hasErrors(ERROR));
  REQUIRE(std::holds_alternative<TCompilationUnitNode *>(TypedOpt));
}

TEST_CASE("Redeclaration - p2p", "[semantic][program][local-function]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> = {
  define other :: io : Channel<-int> = {
    var c := 10; 
    io.send(c)
  }

  define foo :: io : Channel<-Channel<+int>> = {
    Channel<+int> ans := exec other; 
    io.send(ans)
  }

  define foo :: io : Channel<-int> = {
    Channel<+int> c := exec other; 
    int ans := c.recv(); 
    io.send(ans)
  }

  c.send(0)
}
    )"""", 
    "Unsupported redeclaration of foo");
}

TEST_CASE("Redeclaration - p2f", "[semantic][program][local-function]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> = {
  define other :: io : Channel<-int> = {
    var c := 10; 
    io.send(c)
  }

  define foo :: io : Channel<-Channel<+int>> = {
    Channel<+int> ans := exec other; 
    io.send(ans)
  }

  define func foo () {
    return;
  }

  c.send(0)
}
    )"""", 
    "Unsupported redeclaration of foo");
}

TEST_CASE("Redeclaration - f2p", "[semantic][program][local-function]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> = {
  define other :: io : Channel<-int> = {
    var c := 10; 
    io.send(c)
  }

  define func foo () {
    return;
  }

  define foo :: io : Channel<-Channel<+int>> = {
    Channel<+int> ans := exec other; 
    io.send(ans)
  }

  

  c.send(0)
}
    )"""", 
    "Unsupported redeclaration of foo");
}

TEST_CASE("Redeclaration - f2f", "[semantic][program][local-function]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> = {
  define other :: io : Channel<-int> = {
    var c := 10; 
    io.send(c)
  }

  define func foo () {
    return;
  }

  define func foo () {
    return;
  }

  c.send(0)
}
    )"""", 
    "Unsupported redeclaration of foo");
}

// TEST_CASE("Nested Local Functions - Disallow Local vars 4", "[semantic][program][local-function]")
// {
//   antlr4::ANTLRInputStream input(
//       R""""(
//     define program :: c : Channel<-int> = {
//       proc other () {
//         var c := 10;
//       }

//       proc foo() {
//         other();
//         var a := c + 2;
//       }

//       return 0;
//     }
//     )"""");
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // auto lListener = TestErrorListener();
//   // lexer.addErrorListener(&lListener);
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   auto pListener = TestErrorListener(); 
//   parser.addErrorListener(&pListener);

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager stmgr = STManager();
//

//   SemanticVisitor sv = SemanticVisitor(stmgr);

//   sv.visitCompilationUnit(tree);
//   REQUIRE(sv.hasErrors(ERROR));
// }

// TEST_CASE("Nested Local Functions - Disallow Local vars 5", "[semantic][program][local-function]")
// {
//   antlr4::ANTLRInputStream input(
//       R""""(
//     proc other () {
//       var c := 10;
//     }

//     define program :: c : Channel<-int> = {

//       proc foo() {
//           other();
//       }

//       return 0;
//     }
//     )"""");
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // auto lListener = TestErrorListener();
//   // lexer.addErrorListener(&lListener);
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   auto pListener = TestErrorListener(); 
//   parser.addErrorListener(&pListener);

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager stmgr = STManager();
//

//   SemanticVisitor sv = SemanticVisitor(stmgr);

//   sv.visitCompilationUnit(tree);
//   REQUIRE_FALSE(sv.hasErrors(ERROR));
// }

// TEST_CASE("Nested Local Functions - Disallow Local vars 6", "[semantic][program][local-function]")
// {
//   antlr4::ANTLRInputStream input(
//       R""""(
//     proc other () {
//       var c := 10;
//     }

//     define program :: c : Channel<-int> = {

//       proc foo() {
//         other();
//         var a := c + 2;
//       }

//       return 0;
//     }
//     )"""");
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // auto lListener = TestErrorListener();
//   // lexer.addErrorListener(&lListener);
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   auto pListener = TestErrorListener(); 
//   parser.addErrorListener(&pListener);

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager stmgr = STManager();
//

//   SemanticVisitor sv = SemanticVisitor(stmgr);

//   sv.visitCompilationUnit(tree);
//   REQUIRE(sv.hasErrors(ERROR));
// }

TEST_CASE("Nested Enums - Disallow Local Assign", "[semantic][program][enum]")
{
  EnsureErrorsWithMessage(
      R""""(
extern func printf(str s, ...);

define enum Inner {
    int, 
    boolean 
}

define enum Outer {
    Inner, 
    str
}

define program :: c : Channel<-int> = {
    int i := 5; 
    Outer o := i; 

    match o {
        Inner in => {
            match in {
                int i => printf("int: %u\n", i);
                boolean b => printf("boolean: %s\n", (boolean b) : str { if b { return "true"; } return "false"; }(b));
            }
        }
        str s => printf("str: %s\n", s);
    }

    return 0; 
}
    )"""", 
    "Expression of type int cannot be assigned to Outer");
}

TEST_CASE("Nested Enums - Disallow Local Assign with mismatch", "[semantic][program][enum]")
{
  EnsureErrorsWithMessage(
      R""""(
extern func printf(str s, ...);

define enum Inner {
    int, 
    boolean 
}

define enum Outer {
    Inner, 
    str
}

define program :: c : Channel<-int> = {
    (int + boolean) i := 5; 
    Outer o := i; 

    match o {
        Inner in => {
            match in {
                int i => printf("int: %u\n", i);
                boolean b => printf("boolean: %s\n", (boolean b) : str { if b { return "true"; } return "false"; }(b));
            }
        }
        str s => printf("str: %s\n", s);
    }

    return 0; 
}
    )"""", 
    "Expression of type (boolean + int) cannot be assigned to Outer");
}

TEST_CASE("Duplicated enum keys", "[semantic][program][enum]")
{
  EnsureErrorsWithMessage(
      R""""(
define enum Inner {
    int, 
    boolean,
    int
}
    )"""", 
    "Duplicate arguments to enum type, or failed to generate types"); // TODO: BETTER MESSAGE
}

TEST_CASE("Duplicated product keys - 1", "[semantic][program][product]")
{
  EnsureErrorsWithMessage(
      R""""(
define struct Inner {
    int a; 
    boolean a;
    int c;
}
    )"""", 
    "Unsupported redeclaration of a");
}

TEST_CASE("Duplicated product keys - 2", "[semantic][program][product]")
{
  EnsureErrorsWithMessage(
      R""""(
define struct Inner {
    int a; 
    boolean b;
    int a;
}
    )"""", 
    "Unsupported redeclaration of a");
}

// TEST_CASE("Global product def", "[semantic][program][product]")
// {
//   antlr4::ANTLRInputStream input(
//       R""""(
// define struct Inner {
//     int a;
//     boolean b;
//     int c;
// }

// Inner I := I::init(5, false, 6);
//     )"""");
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // auto lListener = TestErrorListener();
//   // lexer.addErrorListener(&lListener);
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   auto pListener = TestErrorListener(); 
//   parser.addErrorListener(&pListener);

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager stmgr = STManager();
//

//   SemanticVisitor sv = SemanticVisitor(stmgr);

//   sv.visitCompilationUnit(tree);
//   REQUIRE(sv.hasErrors(ERROR));
// }

// TEST_CASE("Global sum def", "[semantic][program][sum]")
// {
//   antlr4::ANTLRInputStream input(
//       R""""(
// (int + boolean) b := false;
//     )"""");
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // auto lListener = TestErrorListener();
//   // lexer.addErrorListener(&lListener);
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   auto pListener = TestErrorListener(); 
//   parser.addErrorListener(&pListener);

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager stmgr = STManager();
//

//   SemanticVisitor sv = SemanticVisitor(stmgr);

//   sv.visitCompilationUnit(tree);
//   REQUIRE(sv.hasErrors(ERROR));
// }

// TEST_CASE("Global lambda def", "[semantic][program][lambda]")
// {
//   antlr4::ANTLRInputStream input(
//       R""""(
// var lam := (int a, int b) : int {
//     return a * b;
// };
//     )"""");
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // auto lListener = TestErrorListener();
//   // lexer.addErrorListener(&lListener);
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   auto pListener = TestErrorListener(); 
//   parser.addErrorListener(&pListener);

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager stmgr = STManager();
//

//   SemanticVisitor sv = SemanticVisitor(stmgr);

//   sv.visitCompilationUnit(tree);
//   REQUIRE(sv.hasErrors(ERROR));
// }

TEST_CASE("Bad Enum pass", "[semantic][program][lambda][enum]")
{
  EnsureErrorsWithMessage(
      R""""(
extern func printf(str s, ...) : int;

define func test ((int + boolean + (str + boolean)) sum) : int {
    match sum {
        int i => printf("integer: %u\n", i);
        boolean b => printf("boolean: %s\n", (boolean b) : str {
            if b {
                return "true";
            }

            return "false"; 
        }(b));
         (str + boolean) n => printf("no!\n");
    }

    return 0; 
}


define program :: c : Channel<-int> = {
    test("hey");
    # return 0; 
    c.send(0)
}
    )"""", 
    "Argument 0 expected ((boolean + str) + boolean + int) but got str");
}

TEST_CASE("Channel Assignment 1", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
define foo :: c : Channel<+int> = {
  var b := c; 
  int a := c.recv(); # C is no longer defined
}
    )"""", 
    "Could not find channel: c");
}

TEST_CASE("Channel Assignment 2", "[semantic]")
{
    antlr4::ANTLRInputStream input(
      R""""(
define foo :: c : Channel<+int> = {
  var b := c; 
  int a := b.recv(); # C is no longer defined
}
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // auto lListener = TestErrorListener();
  // lexer.addErrorListener(&lListener);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  auto pListener = TestErrorListener(); 
  parser.addErrorListener(&pListener);

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();

  SemanticVisitor sv = SemanticVisitor(stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);
  REQUIRE_FALSE(sv.hasErrors(ERROR));
}

TEST_CASE("No Weaken in loop", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
define bar :: c : Channel<?(?-int);+int> = {

    int i := 0;

    while i < 5 {
        weaken(c)
        i := i + 1; 
    }

    weaken(c)
    int a := c.recv();
}
    )"""", 
    "Failed to weaken: c against Channel<*?(?(-int));+int>");
}

TEST_CASE("double recv", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
define foo :: c : Channel<-int> = {
    c.send(5)
}

define program :: c : Channel<-int> = {
    var com := exec foo, a, b := com.recv(); 

    c.send(a)
}
    )"""", 
    "Failed to recv over channel: [com, Channel<>]");
}

TEST_CASE("double recv - correct", "[semantic]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define foo :: c : Channel<-int> = {
    c.send(5)
}

define program :: c : Channel<-int> = {
    var com := exec foo, a := com.recv(); 

    c.send(a)
}
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // auto lListener = TestErrorListener(); 
  // lexer.addErrorListener(&lListener);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  auto pListener = TestErrorListener(); 
  parser.addErrorListener(&pListener);

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();

  SemanticVisitor sv = SemanticVisitor(stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);
  REQUIRE_FALSE(sv.hasErrors(ERROR));
}

TEST_CASE("Links3 - 1", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
define foo :: c : Channel<+Channel<ExternalChoice<+int, +boolean>;-str>;+Channel<InternalChoice<-int, -boolean>>> = {
    Channel<ExternalChoice<+int, + boolean>;-str> a := c.recv(); 
    Channel<InternalChoice<-int, -boolean>> b := c.recv(); 
    
    offer a 
        | +int => {
                b[-int]
                b.send(a.recv())
                a.send("5")
            }
        | +boolean => {
                b[-boolean]
                b.send(a.recv())
                a.send("5")
            }

    a.send("5")
}

define bar1 :: c : Channel<InternalChoice<-int, -boolean>;+str> = {
    c[-boolean]
    c.send(false)
    var xyz := c.recv(); 
}

define bar2 :: c : Channel<ExternalChoice<+boolean, +int>> = {
    c.case(
        +boolean => {
            boolean b := c.recv(); 
        }
        +int => {
            int i := c.recv(); 
        }
    )
}

define program :: c : Channel<-int> = {
    Channel<ExternalChoice<+int, +boolean>;-str> l1 := exec bar1; 
    Channel<InternalChoice<-int, -boolean>> l2 := exec bar2; 

    Channel<-Channel<ExternalChoice<+int, +boolean>;-str>;-Channel<InternalChoice<-int, -boolean>>> linker := exec foo; 
    linker.send(l1)
    linker.send(l2)

    c.send(0)
}
    )"""", 
    "Failed to send str over channel [a, Channel<>]");
}

TEST_CASE("Links3 - 2", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
define foo :: c : Channel<+Channel<ExternalChoice<+int, +boolean>;-str>;+Channel<InternalChoice<-int, -boolean>>> = {
    Channel<ExternalChoice<+int, + boolean>;-str> a := c.recv(); 
    Channel<InternalChoice<-int, -boolean>> b := c.recv(); 
    
    offer a 
        | +int => {
                b[-int]
                b.send(a.recv())
            }
        | +boolean => {
                b[-boolean]
                b.send(a.recv())
                a.send("5")
            }

    a.send("5")
}

define bar1 :: c : Channel<InternalChoice<-int, -boolean>;+str> = {
    c[-boolean]
    c.send(false)
    var xyz := c.recv(); 
}

define bar2 :: c : Channel<ExternalChoice<+boolean, +int>> = {
    c.case(
        +boolean => {
            boolean b := c.recv(); 
        }
        +int => {
            int i := c.recv(); 
        }
    )
}

define program :: c : Channel<-int> = {
    Channel<ExternalChoice<+int, +boolean>;-str> l1 := exec bar1; 
    Channel<InternalChoice<-int, -boolean>> l2 := exec bar2; 

    Channel<-Channel<ExternalChoice<+int, +boolean>;-str>;-Channel<InternalChoice<-int, -boolean>>> linker := exec foo; 
    linker.send(l1)
    linker.send(l2)

    c.send(0)
}
    )"""", 
    "Failed to send str over channel [a, Channel<>]");
}

TEST_CASE("Links3 - 3", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
define foo :: c : Channel<+Channel<ExternalChoice<+int, +boolean>;-str>;+Channel<InternalChoice<-int, -boolean>>> = {
    Channel<ExternalChoice<+int, + boolean>;-str> a := c.recv(); 
    Channel<InternalChoice<-int, -boolean>> b := c.recv(); 
    
    offer a 
        | +int => {
                b[-int]
                b.send(a.recv())
                a.send("5")
            }
        | +boolean => {
                b[-boolean]
                b.send(a.recv())
            }

    a.send("5")
}

define bar1 :: c : Channel<InternalChoice<-int, -boolean>;+str> = {
    c[-boolean]
    c.send(false)
    var xyz := c.recv(); 
}

define bar2 :: c : Channel<ExternalChoice<+boolean, +int>> = {
    c.case(
        +boolean => {
            boolean b := c.recv(); 
        }
        +int => {
            int i := c.recv(); 
        }
    )
}

define program :: c : Channel<-int> = {
    Channel<ExternalChoice<+int, +boolean>;-str> l1 := exec bar1; 
    Channel<InternalChoice<-int, -boolean>> l2 := exec bar2; 

    Channel<-Channel<ExternalChoice<+int, +boolean>;-str>;-Channel<InternalChoice<-int, -boolean>>> linker := exec foo; 
    linker.send(l1)
    linker.send(l2)

    c.send(0)
}
    )"""", 
    "Failed to send str over channel [a, Channel<>]");
}

TEST_CASE("Links3 - 4", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
define foo :: c : Channel<+Channel<ExternalChoice<+int, +boolean>;-str>;+Channel<InternalChoice<-int, -boolean>>> = {
    Channel<ExternalChoice<+int, + boolean>;-str> a := c.recv(); 
    Channel<InternalChoice<-int, -boolean>> b := c.recv(); 
    
    offer a 
        | +int => {
                b[-int]
                b.send(a.recv())
            }
        | +boolean => {
                b[-boolean]
                b.send(a.recv())
                a.send("5")
            }

}

define bar1 :: c : Channel<InternalChoice<-int, -boolean>;+str> = {
    c[-boolean]
    c.send(false)
    var xyz := c.recv(); 
}

define bar2 :: c : Channel<ExternalChoice<+boolean, +int>> = {
    c.case(
        +boolean => {
            boolean b := c.recv(); 
        }
        +int => {
            int i := c.recv(); 
        }
    )
}

define program :: c : Channel<-int> = {
    Channel<ExternalChoice<+int, +boolean>;-str> l1 := exec bar1; 
    Channel<InternalChoice<-int, -boolean>> l2 := exec bar2; 

    Channel<-Channel<ExternalChoice<+int, +boolean>;-str>;-Channel<InternalChoice<-int, -boolean>>> linker := exec foo; 
    linker.send(l1)
    linker.send(l2)

    c.send(0)
}
    )"""", 
    "Unused linear types in context: [a, Channel<-str>]");
}

// not all of these are duplicates as some hit different branches. some may be the exact same code though, need to check
TEST_CASE("Links3 - 5", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
define foo :: c : Channel<+Channel<ExternalChoice<+int, +boolean>;-str>;+Channel<InternalChoice<-int, -boolean>>> = {
    Channel<ExternalChoice<+int, + boolean>;-str> a := c.recv(); 
    Channel<InternalChoice<-int, -boolean>> b := c.recv(); 
    
    offer a 
        | +int => {
                b[-int]
                b.send(a.recv())
                a.send("5")
            }
        | +boolean => {
                b[-boolean]
                b.send(a.recv())
            }

}

define bar1 :: c : Channel<InternalChoice<-int, -boolean>;+str> = {
    c[-boolean]
    c.send(false)
    var xyz := c.recv(); 
}

define bar2 :: c : Channel<ExternalChoice<+boolean, +int>> = {
    c.case(
        +boolean => {
            boolean b := c.recv(); 
        }
        +int => {
            int i := c.recv(); 
        }
    )
}

define program :: c : Channel<-int> = {
    Channel<ExternalChoice<+int, +boolean>;-str> l1 := exec bar1; 
    Channel<InternalChoice<-int, -boolean>> l2 := exec bar2; 

    Channel<-Channel<ExternalChoice<+int, +boolean>;-str>;-Channel<InternalChoice<-int, -boolean>>> linker := exec foo; 
    linker.send(l1)
    linker.send(l2)

    c.send(0)
}
    )"""", 
    "Unused linear types in context: [a, Channel<-str>]");
}

TEST_CASE("No assignments of guarded", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> = {

  while true {
    var b;

    b := c; 
  }

  c.send(0)
}
    )"""",
      "Cannot assign guarded resource to another identifier");
}

TEST_CASE("No assignments of guarded in decls", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> = {

  while true {
    var b := c;
  }

  c.send(0)
}
    )"""",
      "Cannot assign guarded resource to another identifier");
}

TEST_CASE("No instancing cancelable", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<?Cancelable<-int>> {
}
    )"""",
      "cannot include looping protocol within cancelable");
}

TEST_CASE("programs/forwardWrongArg - Forward Declaration w/ wrong arg name", "[semantic]")
{
  auto stream = std::fstream("/home/shared/programs/forwardWrongArg.bismuth");
  EnsureErrorsWithMessage(
    antlr4::ANTLRInputStream(stream),
    "Unsupported redeclaration of foo"
  );
}

TEST_CASE("programs/forwardWrongArg2 - Function syntax on process", "[semantic]")
{
  auto stream = std::fstream("/home/shared/programs/forwardWrongArg2.bismuth");
  EnsureErrorsWithMessage(
    antlr4::ANTLRInputStream(stream),
    "Can only invoke functions, not foo"
  );
}


TEST_CASE("Cancel a non-cancelable", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> {
    cancel(c);
}
    )"""",
      "Failed to cancel: c : ");
}

TEST_CASE("While Loop Break I", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
extern func printf(str s, ...) : int; 

define program :: c : Channel<-int> {

  c.send(0)

  var break := exec loopBreaker


  var i := 1
  accept(break) 
  {
    break.send(i)

    i := i + 1
  }
}

define loopBreaker :: c : Channel<?+int> {

  int i := -1

  unfold(c)

  while(c.recv() != 0) # FIXME: Improve error msg, currently just says c DNE, when it does, you just can't use it in non-linear context! In the future, make it so we unfold the while loop so things like this can be done
  {
    printf("looped?\n");
  }

  weaken(c)
}
    )"""",
      "Could not find channel: c");
}


TEST_CASE("Linear returns are prohibited when unused", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
define progFoo :: c : Channel<-int> {
    c.send(20);
}

define func getChannel() : Channel<+int> {
    var c := exec progFoo; 
    return c; 
}

define program :: c : Channel<-int> {

    c.send(0);

    getChannel();
}
    )"""",
      "Evaluation of expression would result in introducing a linear resource that is impossible to use");
}


TEST_CASE("Error message during inference of number reports proper type mismatch", "[semantic][program]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> {
    str[4] arr := [0, 1, 2, 3];
    c.send(0);
}
    )"""", 
    "Expression of type int[4] cannot be assigned to str[4]");
}

/*********************************
 * B-Level Example tests
 *********************************/
TEST_CASE("B Level Negative Test #1", "[semantic]")
{
  auto stream = std::fstream("/home/shared/programs/BLevel/BNegative1.bismuth");
  EnsureErrorsWithMessage(
    antlr4::ANTLRInputStream(stream),
    "Undefined variable reference: getIntArg"
  );
}

TEST_CASE("B Level Negative Test #2", "[semantic]")
{
  auto stream = std::fstream("/home/shared/programs/BLevel/BNegative2.bismuth");
  EnsureErrorsWithMessage(
    antlr4::ANTLRInputStream(stream),
    "Expression of type boolean cannot be assigned to int"
  );
}

/*********************************
 * A-Level Example tests
 *********************************/

TEST_CASE("A Level Negative Test #2", "[semantic]")
{
  auto stream = std::fstream("/home/shared/programs/ALevel/ANegative2.bismuth");
  EnsureErrorsWithMessage(
    antlr4::ANTLRInputStream(stream),
    "Expected 2 argument(s), but got 3"
  );
}