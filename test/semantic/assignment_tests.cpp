#include <catch2/catch_test_macros.hpp>
#include "antlr4-runtime.h"
#include "WPLLexer.h"
#include "WPLParser.h"
#include "WPLErrorHandler.h"
#include "SemanticVisitor.h"

#include "test_error_handlers.h"

TEST_CASE("Basic Assignments", "[semantic]")
{
  SECTION("Basic Int Test")
  {
    antlr4::ANTLRInputStream input("int a <- 2;");
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

    std::optional<Symbol *> opt = stmgr->lookup("a");

    CHECK(opt.has_value());
    CHECK(opt.value()->type->isSubtype(Types::INT));
  }
}

TEST_CASE("Assignment: Int Expr", "[semantic]")
{
  antlr4::ANTLRInputStream input("int a; {a <- 2 * (2 / 4 + 3 - -2);}");
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

  std::optional<Symbol *> opt = stmgr->lookup("a");

  CHECK(opt.has_value());
  CHECK(opt.value()->type->isSubtype(Types::INT));
}

TEST_CASE("Assignment: Bool const", "[semantic]")
{
  antlr4::ANTLRInputStream input("boolean a <- false;");
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

  std::optional<Symbol *> opt = stmgr->lookup("a");

  CHECK(opt.has_value());
  CHECK(opt.value()->type->isSubtype(Types::BOOL));
}

TEST_CASE("Assignment: Bool expr", "[semantic]")
{
  antlr4::ANTLRInputStream input("boolean a; {a <- (false | true) & ~false;}");
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

  std::optional<Symbol *> opt = stmgr->lookup("a");

  CHECK(opt.has_value());
  CHECK(opt.value()->type->isSubtype(Types::BOOL));
}

TEST_CASE("Assignment: String const", "[semantic]")
{
  antlr4::ANTLRInputStream input("str a <- \"Hello world!\";");
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

  std::optional<Symbol *> opt = stmgr->lookup("a");

  CHECK(opt.has_value());
  CHECK(opt.value()->type->isSubtype(Types::STR));
}


TEST_CASE("Inequal array lengths 1", "[semantic][conditional]")
{
  antlr4::ANTLRInputStream input(
    R""""(
      int [3] a; 
      int [5] b; 

      a <- b;
    )""""
  );
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
  CHECK(sv->hasErrors(ERROR));
}

TEST_CASE("Inequal array lengths 2", "[semantic][conditional]")
{
  antlr4::ANTLRInputStream input(
    R""""(
      int [5] a; 
      int [3] b; 

      a <- b;
    )""""
  );
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
  CHECK(sv->hasErrors(ERROR));
}