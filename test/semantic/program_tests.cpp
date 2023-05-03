#include <catch2/catch_test_macros.hpp>
#include "antlr4-runtime.h"
#include "BismuthLexer.h"
#include "BismuthParser.h"
#include "BismuthErrorHandler.h"
#include "SemanticVisitor.h"

#include "CodegenVisitor.h"

#include "test_error_handlers.h"

TEST_CASE("programs/test4 - Don't allow void to be sent to fn", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test4.bismuth");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  BismuthLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  SemanticVisitor *sv = new SemanticVisitor(stm);
  sv->visitCompilationUnit(tree);

  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/doubleArg1 - Prevent Argument reuse in func", "[semantic]")
{

  antlr4::ANTLRInputStream input(
      R""""(
      define func foo (int a, int a, int b) {
    return; 
}
    )"""");

  BismuthLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/doubleArg2 - Prevent Argument reuse in extern", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/doubleArg2.bismuth");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  BismuthLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  SemanticVisitor *sv = new SemanticVisitor(stm);
  sv->visitCompilationUnit(tree);

  // if(sv->hasErrors(0))
  // {
  //     CHECK("foo" == sv->getErrors());
  // }
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/doubleArg3 - Prevent Argument reuse in func and that we don't crash", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/doubleArg3.bismuth");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  BismuthLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stm);
  sv->visitCompilationUnit(tree);

  // if(sv->hasErrors(0))
  // {
  //     CHECK("foo" == sv->getErrors());
  // }
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/test15 - No array equalities", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test15.bismuth");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  BismuthLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stm);
  sv->visitCompilationUnit(tree);

  // if(sv->hasErrors(0))
  // {
  //     CHECK("foo" == sv->getErrors());
  // }
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("Comment EOF", "[semantic]")
{
  antlr4::ANTLRInputStream input(
      "# Hello # there!");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);

  // Any errors should be syntax errors.
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);

  CHECK_FALSE(sv->hasErrors(0));
}

TEST_CASE("programs/test16 - overwrite lhs var", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test16.bismuth");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  BismuthLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/test16a - overwrite lhs var - other way", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test16a.bismuth");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  BismuthLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/test16c - overwrite rhs var", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test16c.bismuth");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  BismuthLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/test16c-1 - overwrite rhs var - bubble up!", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test16c-1.bismuth");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  BismuthLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/test16c-2 - overwrite rhs var", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test16c-2.bismuth");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  BismuthLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/test16d - chain var", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test16d.bismuth");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  BismuthLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/test16e - chain var 2", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test16e.bismuth");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  BismuthLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));

  // TODO: WHEN OPTIONAL TYPES
}

TEST_CASE("programs/test16f - var loop", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test16f.bismuth");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  BismuthLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stm);
  sv->visitCompilationUnit(tree);
  REQUIRE_FALSE(sv->hasErrors(0));
}

//FIXME: REENABLE AGAIN!
/*
TEST_CASE("Test program() should return int warning", "[semantic][conditional]")
{
  antlr4::ANTLRInputStream input(
      R""""(
      define func program () {
        return; # FIXME: DO THESE HAVE TO END IN RETURN?
      }
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  CHECK_FALSE(sv->hasErrors(ERROR));
  CHECK(sv->hasErrors(CRITICAL_WARNING));
}

TEST_CASE("Test program() should not have parameters warning", "[semantic][conditional]")
{
  antlr4::ANTLRInputStream input(
      R""""(
      int func program (int a) {
        return 0;
      }
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  CHECK_FALSE(sv->hasErrors(ERROR));
  CHECK(sv->hasErrors(CRITICAL_WARNING));
}
*/

TEST_CASE("Dead code in program block", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    define program :: c : Channel<-int> = {

        return 1; 

        int a; 

        return 0;
    }
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}
//FIXME: DO THESE TESTS DO ANYTHING? DONT HAVE SENDS!!
TEST_CASE("Dead code in if/else", "[semantic][program][conditional]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    define program :: c : Channel<-int> = {

    if true {
        return 0; 

        int a; 
    } else {
        return 1;

        int b; 
    }
}
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Dead code in select", "[semantic][program][select]")
{
  antlr4::ANTLRInputStream input(
      R""""(
# int func program () {
define func program (int idk) : int { # FIXME: MAKE THROW ERROR B/C THIS MAKES MAIN PROG IMPOSSIBLE

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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
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
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE_FALSE(sv->hasErrors(ERROR));
}

// FIXME: TEST THAT WHEN HAS ERRORS TREE EMPTY?
TEST_CASE("Incorrect Argument Pass", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    # proc foo (int a) {
    define func foo (int a) : int {

      return -1;
    }

    define program :: c : Channel<-int> = {
      foo("hello");  
      c.send(0)
    }
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Invoke on Non-Invokable (str)", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    define program :: c : Channel<-int> = {
      var x := "hey there!"; 
      x();
    }
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

// FIXME: TYPE INFERENCE ON FUNCTIONS? AND TEST FUNCTION SUBTYPER!

TEST_CASE("Invoke on Non-Invokable (int)", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    define program :: c : Channel<-int> = {
      var x := 10; 
      x();
    }
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Redeclaration of function 1", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Copy linear resources", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    define program :: c : Channel<-int> = {
      var a := copy c; 
      c.send(0)
    }
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}


TEST_CASE("Redeclaration of program 1", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
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
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//
//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   REQUIRE(sv->hasErrors(ERROR));
// }

TEST_CASE("Redeclaration of function 3", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Redeclaration of program 3", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Redeclaration of function 4", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    define func foo () : int {
      return 1;
    }

    define func foo (int a) : int {
      return 1;
    }

    define program :: c : Channel<-int> = {
      return 0; 
    }
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Redeclaration of program 4", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Redeclaration in extern", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    extern int func foo();
    extern int func foo(int a);
    
    define program :: c : Channel<-int> = {
      return 0; 
    }
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Out of order function w/ forward declaration", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
extern int func printf(...);

extern int func foo(str a); # FIXME CHANGE SYNTAX OF THIS/FUNC TO MATCH?

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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
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
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//
//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   REQUIRE(sv->hasErrors(ERROR));
// }

TEST_CASE("Forward Decl with Variadic", "[semantic][program][function][forward-decl]")
{
  antlr4::ANTLRInputStream input(
      R""""(
extern int func printf(...);

extern proc foo(int a, ...); 



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

}

# str a := "hello";
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

// FIXME: TEST EXTERN PROGRAMS?

TEST_CASE("Forward Decl with wrong num args", "[semantic][program][function][forward-decl]")
{
  antlr4::ANTLRInputStream input(
      R""""(
extern int func printf(...);

# extern proc foo(int a);
extern int func foo(str a);



define program :: c : Channel<-int> = {
    foo("hello"); 
    # return 0;
    c.send(0)
}

# proc foo(int a, int b) {
define func foo (str a, int b) : int {
    printf("a = %s\n", a);
    return 0;
}

# str a := "hello";
    )"""");

  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
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
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//
//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   REQUIRE(sv->hasErrors(ERROR));
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
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//
//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   REQUIRE(sv->hasErrors(ERROR));
// }

TEST_CASE("Wrong UnaryNot", "[semantic][program][bool]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
    boolean a := ~0; 
    return 0;
}
    )"""");

  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Wrong UnaryMinus", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
    int a := -"hey"; 
    return 0;
}
    )"""");

  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Wrong RHS Arithmetic", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
    int a := 0 - "hey?"; 
    return 0;
}
    )"""");

  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Wrong LogAnd LHS", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
    boolean a := 1 & false; 
    return 0;
}
    )"""");

  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Wrong LogAnd RHS", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
    boolean a := false & 1; 
    return 0;
}
    )"""");

  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Wrong LogOr LHS", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
    boolean a := 1 | false; 
    return 0;
}
    )"""");

  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Wrong LogOr RHS", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
    boolean a := false | 1; 
    return 0;
}
    )"""");

  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Field Access - var", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
    var a;
    var b := a.length; 
    return 0;
}
    )"""");

  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Field Access - int", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
    int a;
    var b := a.length; 
    return 0;
}
    )"""");

  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("ArrayAccess - Wrong Type", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
    int [5] a;
    var b := a[true | false];
    return 0;
}
    )"""");

  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Field Access - Unsupported/Undefined", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
    int [5] a;
    var b := a.testing; 
    return 0;
}
    )"""");

  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Field Access - Undefined Var", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
    var b := a.testing; 
    return 0;
}
    )"""");

  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Equals Different types", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
    var a := "hello" == 1; 
    return 0;
}
    )"""");

  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Assign to undefined", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    define program :: c : Channel<-int> = {
      a := 10; 
      return 0; 
    }
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Proc Returning", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    # proc foo() {
    define func foo () {
      return 1;
    }

    define program :: c : Channel<-int> = {
      c.send(0)
    }
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Function return nothing", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    # int func foo() {
    define func foo (int x) : int {
      return;
    }
    define program :: c : Channel<-int> = {
      # return 0; 
      c.send(0)
    }
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}
// FIXME: DUPLICATE ALL TESTS WITH FUNCS AND PROCS!
TEST_CASE("Function return wrong type", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    define program :: c : Channel<-int> = {
      return "hey"; 
    }
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Nested Local Functions - Disallow Local vars 1", "[semantic][program][local-function]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    define program :: c : Channel<-int> = {
      var a := 0; 

      define func foo (Channel<-int> c) : Channel<-int> {
        a := 2; 
        return c;
      }

      c.send(0)
    }
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Nested Local Program - Disallow Local vars 1", "[semantic][program][local-function]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    define program :: c : Channel<-int> = {
      var a := 0; 

      define foo :: c : Channel<-int> = {
        c.send(a)
      }

      return 0; 
    }
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
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
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//

//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   REQUIRE_FALSE(sv->hasErrors(ERROR));
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
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE_FALSE(sv->hasErrors(ERROR));
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
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE_FALSE(sv->hasErrors(ERROR));
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
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  // sv->visitCompilationUnit(tree);
  // REQUIRE_FALSE(sv->hasErrors(ERROR));
  auto TypedOpt = sv->visitCtx(tree);
  REQUIRE_FALSE(sv->hasErrors(ERROR));
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
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  auto TypedOpt = sv->visitCtx(tree);
  // sv->visitCompilationUnit(tree);
  REQUIRE_FALSE(sv->hasErrors(ERROR));
  REQUIRE(std::holds_alternative<TCompilationUnitNode *>(TypedOpt));
}

TEST_CASE("Redeclaration - p2p", "[semantic][program][local-function]")
{
  antlr4::ANTLRInputStream input(
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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  auto TypedOpt = sv->visitCtx(tree);
  // sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
  // REQUIRE(TypedOpt);
}

TEST_CASE("Redeclaration - p2f", "[semantic][program][local-function]")
{
  antlr4::ANTLRInputStream input(
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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  auto TypedOpt = sv->visitCtx(tree);
  // sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
  // REQUIRE(TypedOpt);
}

TEST_CASE("Redeclaration - f2p", "[semantic][program][local-function]")
{
  antlr4::ANTLRInputStream input(
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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  auto TypedOpt = sv->visitCtx(tree);
  // sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
  // REQUIRE(TypedOpt);
}

TEST_CASE("Redeclaration - f2f", "[semantic][program][local-function]")
{
  antlr4::ANTLRInputStream input(
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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  auto TypedOpt = sv->visitCtx(tree);
  // sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
  // REQUIRE(TypedOpt);
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
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//

//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   REQUIRE(sv->hasErrors(ERROR));
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
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//

//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   REQUIRE_FALSE(sv->hasErrors(ERROR));
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
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//

//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   REQUIRE(sv->hasErrors(ERROR));
// }

TEST_CASE("Nested Enums - Disallow Local Assign", "[semantic][program][enum]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    extern int func printf(str s, ...);

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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Nested Enums - Disallow Local Assign with mismatch", "[semantic][program][enum]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    extern int func printf(str s, ...);

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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Duplicated enum keys", "[semantic][program][enum]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define enum Inner {
    int, 
    boolean,
    int
}
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Duplicated product keys - 1", "[semantic][program][product]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define struct Inner {
    int a; 
    boolean a;
    int c;
}
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Duplicated product keys - 2", "[semantic][program][product]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define struct Inner {
    int a; 
    boolean b;
    int a;
}
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
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
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//

//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   REQUIRE(sv->hasErrors(ERROR));
// }

// TEST_CASE("Global sum def", "[semantic][program][sum]")
// {
//   antlr4::ANTLRInputStream input(
//       R""""(
// (int + boolean) b := false;
//     )"""");
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//

//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   REQUIRE(sv->hasErrors(ERROR));
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
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//

//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   REQUIRE(sv->hasErrors(ERROR));
// }

TEST_CASE("Bad Enum pass", "[semantic][program][lambda][enum]")
{
  antlr4::ANTLRInputStream input(
      R""""(
extern int func printf(str s, ...);

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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Channel Assignment 1", "[semantic]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define foo :: c : Channel<+int> = {
  var b := c; 
  int a := c.recv(); # C is no longer defined
}
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
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
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE_FALSE(sv->hasErrors(ERROR));
}

TEST_CASE("No Weaken in loop", "[semantic]")
{
  antlr4::ANTLRInputStream input(
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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("double recv", "[semantic]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define foo :: c : Channel<-int> = {
    c.send(5)
}

define program :: c : Channel<-int> = {
    var com := exec foo, a, b := com.recv(); 

    c.send(a)
}
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
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
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE_FALSE(sv->hasErrors(ERROR));
}

TEST_CASE("Links3 - 1", "[semantic]")
{
  antlr4::ANTLRInputStream input(
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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Links3 - 2", "[semantic]")
{
  antlr4::ANTLRInputStream input(
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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Links3 - 3", "[semantic]")
{
  antlr4::ANTLRInputStream input(
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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Links3 - 4", "[semantic]")
{
  antlr4::ANTLRInputStream input(
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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Links3 - 5", "[semantic]")
{
  antlr4::ANTLRInputStream input(
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
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("No assignments of guarded", "[semantic]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {

  while true {
    var b;

    b := c; 
  }

  c.send(0)
}
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("No assignments of guarded in decls", "[semantic]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {

  while true {
    var b := c;
  }

  c.send(0)
}
    )"""");
  BismuthLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

/*********************************
 * B-Level Example tests
 *********************************/
TEST_CASE("B Level Negative Test #1", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/BLevel/BNegative1.bismuth");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  BismuthLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("B Level Negative Test #2", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/BLevel/BNegative2.bismuth");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  BismuthLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

/*********************************
 * A-Level Example tests
 *********************************/

TEST_CASE("A Level Negative Test #2", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/ALevel/ANegative2.bismuth");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  BismuthLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  BismuthParser parser(&tokens);
  parser.removeErrorListeners();
  BismuthParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();

  SemanticVisitor *sv = new SemanticVisitor(stm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}