#include <catch2/catch_test_macros.hpp>
#include "antlr4-runtime.h"
#include "WPLLexer.h"
#include "WPLParser.h"
#include "WPLErrorHandler.h"
#include "SemanticVisitor.h"

#include "CodegenVisitor.h"

#include "test_error_handlers.h"

TEST_CASE("programs/test4 - Don't allow void to be sent to fn", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test4.wpl");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
  sv->visitCompilationUnit(tree);

  // if(sv->hasErrors(0))
  // {
  //     CHECK("foo" == sv->getErrors());
  // }
  REQUIRE(sv->hasErrors(0));
}

// TEST_CASE("programs/test9Err - Test assign var to array", "[semantic]")
// {
//   std::fstream *inStream = new std::fstream("/home/shared/programs/test9Err.wpl");
//   antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//   WPLLexer lexer(input);
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   STManager *stm = new STManager();
//   PropertyManager *pm = new PropertyManager();
//   SemanticVisitor *sv = new SemanticVisitor(stm, pm);
//   sv->visitCompilationUnit(tree);

//   // if(sv->hasErrors(0))
//   // {
//   //     CHECK("foo" == sv->getErrors());
//   // }
//   REQUIRE(sv->hasErrors(0));

// }

// TEST_CASE("programs/test11Err - Prevent global exprs", "[semantic]")
// {
//   std::fstream *inStream = new std::fstream("/home/shared/programs/test11err.wpl");
//   antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//   WPLLexer lexer(input);
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   STManager *stm = new STManager();
//   PropertyManager *pm = new PropertyManager();
//   SemanticVisitor *sv = new SemanticVisitor(stm, pm);
//   sv->visitCompilationUnit(tree);

//   // if(sv->hasErrors(0))
//   // {
//   //     CHECK("foo" == sv->getErrors());
//   // }
//   REQUIRE(sv->hasErrors(0));

// }

TEST_CASE("programs/doubleArg1 - Prevent Argument reuse in func", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/doubleArg1.wpl");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
  sv->visitCompilationUnit(tree);

  // if(sv->hasErrors(0))
  // {
  //     CHECK("foo" == sv->getErrors());
  // }
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/doubleArg2 - Prevent Argument reuse in extern", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/doubleArg2.prism");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
  sv->visitCompilationUnit(tree);

  // if(sv->hasErrors(0))
  // {
  //     CHECK("foo" == sv->getErrors());
  // }
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/doubleArg3 - Prevent Argument reuse in func and that we don't crash", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/doubleArg3.prism");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
  sv->visitCompilationUnit(tree);

  // if(sv->hasErrors(0))
  // {
  //     CHECK("foo" == sv->getErrors());
  // }
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/test15 - No array equalities", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test15.wpl");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);

  // Any errors should be syntax errors.
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, new PropertyManager());

  sv->visitCompilationUnit(tree);

  CHECK_FALSE(sv->hasErrors(0));
}

TEST_CASE("programs/test16 - overwrite lhs var", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test16.prism");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/test16a - overwrite lhs var - other way", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test16a.prism");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/test16c - overwrite rhs var", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test16c.prism");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/test16c-1 - overwrite rhs var - bubble up!", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test16c-1.prism");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/test16c-2 - overwrite rhs var", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test16c-2.prism");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/test16d - chain var", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test16d.prism");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/test16e - chain var 2", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test16e.prism");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));

  // TODO: WHEN OPTIONAL TYPES
}

TEST_CASE("programs/test16f - var loop", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test16f.prism");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
  sv->visitCompilationUnit(tree);
  REQUIRE_FALSE(sv->hasErrors(0)); // FIXME: SHOULD WE COMPILE THESE?
}

TEST_CASE("programs/test17 - var inf in decl", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/test17.prism");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
  sv->visitCompilationUnit(tree);
  REQUIRE_FALSE(sv->hasErrors(0));

  // FIXME: REQUIRE dd078039953b6a079ba980b9e1194ea063a9cf8c44194aece3adb115125877f3?
}

TEST_CASE("Test program() should return int warning", "[semantic][conditional]")
{
  antlr4::ANTLRInputStream input(
      R""""(
      proc program () {

      }
    )"""");
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, new PropertyManager());

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, new PropertyManager());

  sv->visitCompilationUnit(tree);
  CHECK_FALSE(sv->hasErrors(ERROR));
  CHECK(sv->hasErrors(CRITICAL_WARNING));
}

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Dead code in if/else", "[semantic][program][conditional]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    define program :: c : Channel<-int> = {

    if true then {
        return 0; 

        int a; 
    } else {
        return 1;

        int b; 
    }
}
    )"""");
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Dead code in select", "[semantic][program][select]")
{
  antlr4::ANTLRInputStream input(
      R""""(
# int func program () {
define func program (int idk) : int { # FIXME: MAKE THROW ERROR B/C THIS MAKES MAIN PROG IMPOSSIBLE # FIXME: MAKE IT SO WE CAN HAVE ZERO ARGS?

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, new PropertyManager());

  sv->visitCompilationUnit(tree);
  REQUIRE_FALSE(sv->hasErrors(ERROR));
}

//   // TODO: WHEN USING OPTIONALS FOR getLLVMTYPE?


// TEST_CASE("Uninferred", "[semantic][program]") //FIXME: IMPL WHEN WE HAVE VAR TYPES DECL?
// {
//   antlr4::ANTLRInputStream input(
//       R""""(
//     var a; 
//     define program :: c : Channel<-int> = {
//         return 0;
//     }
//     )"""");
//   WPLLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   PropertyManager *pm = new PropertyManager();
//   SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

//   sv->visitCompilationUnit(tree);
//   REQUIRE(sv->hasErrors(ERROR));


// }

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
//   WPLLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   PropertyManager *pm = new PropertyManager();
//   SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
  // CodegenVisitor *cv = new CodegenVisitor(pm, "test", CompilerFlags::NO_RUNTIME);
  // cv->visitCompilationUnit(tree);
  // REQUIRE(cv->hasErrors(0));
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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
  // CodegenVisitor *cv = new CodegenVisitor(pm, "test", CompilerFlags::NO_RUNTIME);
  // cv->visitCompilationUnit(tree);
  // REQUIRE(cv->hasErrors(0));
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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Out of order function w/ forward declaration", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
extern int func printf(...);

# extern proc foo();  # FIXME: DELETE PROC?
extern int func foo(str a); # FIXME CHANGE SYNTAX OF THIS/FUNC TO MATCH?

# str a := "hello";

define program :: c : Channel<-int> = {
    printf("hey!!"); 
    foo(); 
    # return 0;
    c.send(0)
}

# proc foo() {
define func foo (str a) : int {
    printf("a = %s\n", a);
    return 0; # FIXME: REMOVE NEED FOR RETURN HERE?
}
    )"""");
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
//   WPLLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   PropertyManager *pm = new PropertyManager();
//   SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

//FIXME: TEST EXTERN PROGRAMS?

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

  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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

//   WPLLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   PropertyManager *pm = new PropertyManager();
//   SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

//   sv->visitCompilationUnit(tree);
//   REQUIRE(sv->hasErrors(ERROR));
// }

//UNUSED: SEEMS REDUNDANT
// TEST_CASE("Forward Decl with wrong arg type", "[semantic][program][function][forward-decl]")
// {
//   antlr4::ANTLRInputStream input(
//       R""""(
// extern int func printf(...);

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

//   WPLLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   PropertyManager *pm = new PropertyManager();
//   SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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

  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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

  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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

  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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

  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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

  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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

  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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

  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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

  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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

  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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

  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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

  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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

  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}

TEST_CASE("Equals Different types", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> = {
    var a := "hello" = 1; 
    return 0;
}
    )"""");

  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(ERROR));
}
//FIXME: DUPLICATE ALL TESTS WITH FUNCS AND PROCS!
TEST_CASE("Function return wrong type", "[semantic][program]")
{
  antlr4::ANTLRInputStream input(
      R""""(
    define program :: c : Channel<-int> = {
      return "hey"; 
    }
    )"""");
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
//   WPLLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   PropertyManager *pm = new PropertyManager();

//   SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

  sv->visitCompilationUnit(tree);
  REQUIRE_FALSE(sv->hasErrors(ERROR));
}

TEST_CASE("Nested Local Functions - Disallow Local vars 3 - p2f", "[semantic][program][local-function]")
{
  //FIXME: WE FAIL TO GEN TYPED AST ON THIS!!!
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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

  sv->visitCompilationUnit(tree);
  REQUIRE_FALSE(sv->hasErrors(ERROR));
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

      # FIXME: THIS DOESNT WORK!!
      # define foo :: io : Channel<-Channel<+int>> = {
      #  Channel<+int> ans := exec other; 
      #   io.send(ans); 
      # }

      define foo :: io : Channel<-int> = {
        Channel<+int> c := exec other; 
        int ans := c.recv(); 
        io.send(ans)
      }

      c.send(0)
    }
    )"""");
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

  sv->visitCompilationUnit(tree);
  REQUIRE_FALSE(sv->hasErrors(ERROR));
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
//   WPLLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   PropertyManager *pm = new PropertyManager();

//   SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
//   WPLLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   PropertyManager *pm = new PropertyManager();

//   SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
//   WPLLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   PropertyManager *pm = new PropertyManager();

//   SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
                boolean b => printf("boolean: %s\n", (boolean b) : str { if b then { return "true"; } return "false"; }(b));
            }
        }
        str s => printf("str: %s\n", s);
    }

    return 0; 
}
    )"""");
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
                boolean b => printf("boolean: %s\n", (boolean b) : str { if b then { return "true"; } return "false"; }(b));
            }
        }
        str s => printf("str: %s\n", s);
    }

    return 0; 
}
    )"""");
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
//   WPLLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   PropertyManager *pm = new PropertyManager();

//   SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

//   sv->visitCompilationUnit(tree);
//   REQUIRE(sv->hasErrors(ERROR));
// }

// TEST_CASE("Global sum def", "[semantic][program][sum]")
// {
//   antlr4::ANTLRInputStream input(
//       R""""(
// (int + boolean) b := false; 
//     )"""");
//   WPLLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   PropertyManager *pm = new PropertyManager();

//   SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
//   WPLLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   PropertyManager *pm = new PropertyManager();

//   SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
            if b then {
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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

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
  WPLLexer lexer(&input);
  // lexer.removeErrorListeners();
  // lexer.addErrorListener(new TestErrorListener());
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());

  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  REQUIRE(tree->getText() != "");

  STManager *stmgr = new STManager();
  PropertyManager *pm = new PropertyManager();

  SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

  sv->visitCompilationUnit(tree);
  REQUIRE_FALSE(sv->hasErrors(ERROR));
}

/*********************************
 * C-Level Example tests
 *********************************/
// TEST_CASE("C Level Negative Test #1", "[semantic]")
// {
//   std::fstream *inStream = new std::fstream("/home/shared/programs/CLevel/CNegative1.wpl");
//   antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//   WPLLexer lexer(input);
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   WPLSyntaxErrorListener *syntaxListener = new WPLSyntaxErrorListener();
//   parser.addErrorListener(syntaxListener);

//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(syntaxListener->hasErrors(0));

//   STManager *stm = new STManager();
//   PropertyManager *pm = new PropertyManager();
//   SemanticVisitor *sv = new SemanticVisitor(stm, pm);
//   sv->visitCompilationUnit(tree);
//   REQUIRE(sv->hasErrors(0));

// }

// TEST_CASE("C Level Negative Test #2", "[semantic]")
// {
//   std::fstream *inStream = new std::fstream("/home/shared/programs/CLevel/CNegative2.wpl");
//   antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//   WPLLexer lexer(input);
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   WPLSyntaxErrorListener *syntaxListener = new WPLSyntaxErrorListener();
//   parser.addErrorListener(syntaxListener);

//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(syntaxListener->hasErrors(0));

//   STManager *stm = new STManager();
//   PropertyManager *pm = new PropertyManager();
//   SemanticVisitor *sv = new SemanticVisitor(stm, pm);
//   sv->visitCompilationUnit(tree);
//   REQUIRE(sv->hasErrors(0));
//   // std::cout << sv->getErrors() << std::endl;

// }

/*********************************
 * B-Level Example tests
 *********************************/
TEST_CASE("B Level Negative Test #1", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/BLevel/BNegative1.prism");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

TEST_CASE("B Level Negative Test #2", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/BLevel/BNegative2.prism");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}

/*********************************
 * A-Level Example tests
 *********************************/
// TEST_CASE("A Level Negative Test #1", "[semantic]")
// {
//   std::fstream *inStream = new std::fstream("/home/shared/programs/ALevel/ANegative1.wpl");
//   antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//   WPLLexer lexer(input);
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   WPLParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   STManager *stm = new STManager();
//   PropertyManager *pm = new PropertyManager();
//   SemanticVisitor *sv = new SemanticVisitor(stm, pm);
//   sv->visitCompilationUnit(tree);
//   REQUIRE(sv->hasErrors(0));
// }

TEST_CASE("A Level Negative Test #2", "[semantic]")
{
  std::fstream *inStream = new std::fstream("/home/shared/programs/ALevel/ANegative2.prism");
  antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

  WPLLexer lexer(input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  STManager *stm = new STManager();
  PropertyManager *pm = new PropertyManager();
  SemanticVisitor *sv = new SemanticVisitor(stm, pm);
  sv->visitCompilationUnit(tree);
  REQUIRE(sv->hasErrors(0));
}