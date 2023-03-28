#include <catch2/catch_test_macros.hpp>
#include "antlr4-runtime.h"
#include "BismuthLexer.h"
#include "BismuthParser.h"
#include "BismuthErrorHandler.h"
#include "SemanticVisitor.h"

#include "test_error_handlers.h"

/*
 * FIXME: Make conditional tests more robust!
 */ 


TEST_CASE("Inference If Errors - 1", "[semantic]")
{
  antlr4::ANTLRInputStream input(
      R""""(
      define program :: c : Channel<-int> = {
        var a; 
        
        if(1 < 2) {
          a := true; 
        } else {
          a := 10; 
        }

        c.send(0)
      }
      )""""
    );
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

  CHECK(sv->hasErrors(0));
}

TEST_CASE("Inference If - 1", "[semantic]")
{
  antlr4::ANTLRInputStream input(
      R""""(
      define program :: c : Channel<-int> = {
        var a; 
        
        if(1 < 2) {
          var a := false; 
        } else {
          a := 10; 
        }

        c.send(0)
      }
      )""""
    );
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

TEST_CASE("Inference If - 2", "[semantic]")
{
  antlr4::ANTLRInputStream input(
      R""""(
      define program :: c : Channel<-int> = {
        var a; 
        
        if(1 < 2) {
          a := false; 
        } else {
          var a := 10; 
        }

        c.send(0)
      }
      )""""
    );
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


// TEST_CASE("No Array Equality 1", "[semantic][conditional]")
// {
//   antlr4::ANTLRInputStream input(
//     R""""(
//       int [5] a; 
//       int [5] b; 

//       boolean test := a = b; 
//     )""""
//   );
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
//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   CHECK(sv->hasErrors(ERROR));
// }

// TEST_CASE("No Array Equality 2", "[semantic][conditional]")
// {
//   antlr4::ANTLRInputStream input(
//     R""""(
//       int [5] a; 
//       int [5] b; 

//       boolean test := a ~= b; 
//     )""""
//   );
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
//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   CHECK(sv->hasErrors(ERROR));
// }