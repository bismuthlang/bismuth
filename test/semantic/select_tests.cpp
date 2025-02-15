#include <catch2/catch_test_macros.hpp>
#include "BismuthLexer.h"
#include "BismuthParser.h"
#include "BismuthErrorHandler.h"
#include "SemanticVisitor.h"

#include "test_error_handlers.h"

/*
 * : Make select tests more robust
 */

TEST_CASE("Basic select", "[semantic][conditional]")
{
  antlr4::ANTLRInputStream input(
    R""""(
      prog program :: c : -int = {
      select {
        false : {int a := 2;}


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
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();
  SemanticVisitor sv = SemanticVisitor(&stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);

  CHECK_FALSE(sv.hasErrors(ERROR));
}


TEST_CASE("Select without any cases", "[semantic][conditional]")
{
  antlr4::ANTLRInputStream input(
    R""""(
      prog program :: c : -int = {
      select {
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
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();
  SemanticVisitor sv = SemanticVisitor(&stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);

  REQUIRE(sv.hasErrors(ERROR));
}



TEST_CASE("Basic select inf error 1", "[semantic][conditional]")
{
  antlr4::ANTLRInputStream input(
    R""""(
      prog program :: c : -int = {
      var a; 

      select {
        false : {a := true;} 
        true : {a := 10;}
        

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
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();
  SemanticVisitor sv = SemanticVisitor(&stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);
  CHECK(sv.hasErrors(ERROR));
}

TEST_CASE("Basic select inf 1", "[semantic][conditional]")
{
  antlr4::ANTLRInputStream input(
    R""""(
      prog program :: c : -int = {
      var a; 

      select {
        false : {boolean a := true;} 
        true : {a := 10; }
        

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
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();
  SemanticVisitor sv = SemanticVisitor(&stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);

  CHECK_FALSE(sv.hasErrors(ERROR));
}

TEST_CASE("Basic select inf 2", "[semantic][conditional]")
{
  antlr4::ANTLRInputStream input(
    R""""(
      prog program :: c : -int = {
      var a; 

      select {
        false : {a := true;} 
        true : {int a := 10; }
        

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
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();
  SemanticVisitor sv = SemanticVisitor(&stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);

  // std::cout << sv.getErrors() << std::endl; 
  CHECK_FALSE(sv.hasErrors(ERROR));
}

TEST_CASE("Basic select inf 3", "[semantic][conditional]")
{
  antlr4::ANTLRInputStream input(
    R""""(
      prog program :: c : -int = {
      var a; 

      select {
        false : a := 11; 
        true : a := 10; 
        

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
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();
  SemanticVisitor sv = SemanticVisitor(&stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);

  CHECK_FALSE(sv.hasErrors(ERROR));
}



TEST_CASE("Basic select - Dead Code - var", "[semantic][conditional]")
{
  antlr4::ANTLRInputStream input(
    R""""(
      prog program :: c : -int = {
      select {
        false : int a := 2;


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
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();
  SemanticVisitor sv = SemanticVisitor(&stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);

  REQUIRE(sv.hasErrors(ERROR));
}

TEST_CASE("Basic select - Dead Code - proc", "[semantic][conditional]")
{
  antlr4::ANTLRInputStream input(
    R""""(
      prog program :: c : -int = {
      select {
        false : func foo (int a) -> int {return a;}


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
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();
  SemanticVisitor sv = SemanticVisitor(&stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);

  REQUIRE(sv.hasErrors(ERROR));
}

TEST_CASE("Basic select - Dead Code - func", "[semantic][conditional]")
{
  antlr4::ANTLRInputStream input(
    R""""(
      prog program :: c : -int = {
      select {
        false : prog foo :: c : -int = {c.send(0)}


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
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();
  SemanticVisitor sv = SemanticVisitor(&stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);

  REQUIRE(sv.hasErrors(ERROR));
}

TEST_CASE("Wrong case Type in Select", "[semantic][conditional]")
{
  antlr4::ANTLRInputStream input(
    R""""(
      prog program :: c : -int = {
      var a; 

      select {
        "hey" : a := 11; 
        10 : a := 10; 
        

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
  REQUIRE(tree->getText() != "");

  STManager stmgr = STManager();
  SemanticVisitor sv = SemanticVisitor(&stmgr, DisplayMode::C_STYLE);

  sv.visitCompilationUnit(tree);

  REQUIRE(sv.hasErrors(ERROR));
}
