#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include "antlr4-runtime.h"
#include "BismuthLexer.h"
#include "BismuthParser.h"
#include "BismuthErrorHandler.h"
#include "SemanticVisitor.h"

#include "test_error_handlers.h"

/*
 * FIXME: Make conditional tests more robust!
 */ 

using Catch::Matchers::ContainsSubstring;

void EnsureErrorsWithMessage(antlr4::ANTLRInputStream *input, std::string message);
// {
//   BismuthLexer lexer(input);
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   STManager *stm = new STManager();
//   SemanticVisitor *sv = new SemanticVisitor(stm, 0);
//   auto cuOpt = sv->visitCtx(tree);

//   REQUIRE(sv->hasErrors(0));
//   REQUIRE_THAT(sv->getErrors(), ContainsSubstring(message));
// }

void EnsureErrorsWithMessage(std::string program, std::string message);
// {
//   antlr4::ANTLRInputStream input(program);
//   EnsureErrorsWithMessage(&input, message);
// }


TEST_CASE("Inference If Errors - 1", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
define program :: c : Channel<-int> {
  var a; 
  
  if(1 < 2) {
    a := true; 
  } else {
    a := 10; 
  }

  c.send(0)
}
      )"""",
      "Assignment statement expected {VAR/BOOL} but got INT"
    );
}

TEST_CASE("Inference If - 1", "[semantic]")
{
  antlr4::ANTLRInputStream input(
      R""""(
define program :: c : Channel<-int> {
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
define program :: c : Channel<-int> {
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