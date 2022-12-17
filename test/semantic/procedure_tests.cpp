#include <catch2/catch_test_macros.hpp>
#include "antlr4-runtime.h"
#include "WPLLexer.h"
#include "WPLParser.h"
#include "WPLErrorHandler.h"
#include "SemanticVisitor.h"

#include "test_error_handlers.h"

TEST_CASE("visitbasicProc", "[semantic][proc]")
{
  SECTION("No arguments & empty")
  {
    antlr4::ANTLRInputStream input("proc program () {}");
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

    CHECK_FALSE(sv->hasErrors(ERROR));
  }

  SECTION("1 arg & empty")
  {
    antlr4::ANTLRInputStream input("proc program (int a) {}");
    WPLLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();

    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);

    // Any errors should be syntax errors.
    REQUIRE(tree->getText() != "");

    STManager *stmgr = new STManager();
    SemanticVisitor *sv = new SemanticVisitor(stmgr, new PropertyManager());

    sv->visitCompilationUnit(tree);

    // std::cout << stmgr->toString() << std::endl;
    // std::cout << tree->getText() << std::endl;

    CHECK_FALSE(sv->hasErrors(ERROR));
  }
}