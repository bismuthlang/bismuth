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

void EnsureErrorsWithMessage(antlr4::ANTLRInputStream input, std::string message, int flags=0);

void EnsureErrorsWithMessage(std::string program, std::string message, int flags=0);


TEST_CASE("Inference If Errors - 1", "[semantic]")
{
  EnsureErrorsWithMessage(
      R""""(
prog program :: c : -int {
  var a; 
  
  if(1 < 2) {
    a := true; 
  } else {
    a := 10; 
  }

  c.send(0)
}
      )"""",
      "Assignment statement expected boolean but got int"
    );
}

TEST_CASE("Inference If - 1", "[semantic]")
{
  antlr4::ANTLRInputStream input(
      R""""(
prog program :: c : -int {
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

  // Any errors should be syntax errors.
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();
  SemanticVisitor sv = SemanticVisitor(&stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);

  CHECK_FALSE(sv.hasErrors(0));
}

TEST_CASE("Inference If - 2", "[semantic]")
{
  antlr4::ANTLRInputStream input(
      R""""(
prog program :: c : -int {
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

  // Any errors should be syntax errors.
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();
  SemanticVisitor sv = SemanticVisitor(&stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);
  
  CHECK_FALSE(sv.hasErrors(0));
}