/**
 * @file scanner_tests.cpp
 * @author gpollice
 * @brief basic scanner tests
 * @version 0.1
 * @date 2022-07-04
 * @see https://stackoverflow.com/questions/44515370/how-to-override-error-reporting-in-c-target-of-antlr4
 * @see https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#test-cases-and-sections
 * @see https://github.com/catchorg/Catch2/blob/devel/docs/test-cases-and-sections.md
 * @see https://github.com/catchorg/Catch2/blob/devel/docs/assertions.md
 */
#include <catch2/catch_test_macros.hpp>
#include "antlr4-runtime.h"
#include "WPLLexer.h"
#include "test_error_handlers.h"

/****************** Positive tests ******************/

TEST_CASE("Scanner operator tests", "[front-end]")
{
  antlr4::ANTLRInputStream input("<- / = > < - * ~ + ~=");
  WPLLexer lexer(&input);
  lexer.removeErrorListeners();
  lexer.addErrorListener(new TestErrorListener());
  CHECK(lexer.nextToken()->getType() == lexer.ASSIGN);
  CHECK(lexer.nextToken()->getType() == lexer.DIVIDE);
  CHECK(lexer.nextToken()->getType() == lexer.EQUAL);
  CHECK(lexer.nextToken()->getType() == lexer.GREATER);
  CHECK(lexer.nextToken()->getType() == lexer.LESS);
  CHECK(lexer.nextToken()->getType() == lexer.MINUS);
  CHECK(lexer.nextToken()->getType() == lexer.MULTIPLY);
  CHECK(lexer.nextToken()->getType() == lexer.NOT);
  CHECK(lexer.nextToken()->getType() == lexer.PLUS);
  CHECK(lexer.nextToken()->getType() == lexer.NOT_EQUAL);
}

TEST_CASE("Scanner punctuation tests", "[front-end")
{
  antlr4::ANTLRInputStream input("();");
  WPLLexer lexer(&input);
  lexer.removeErrorListeners();
  lexer.addErrorListener(new TestErrorListener());
  CHECK(lexer.nextToken()->getType() == lexer.LPAR);
  CHECK(lexer.nextToken()->getType() == lexer.RPAR);
  CHECK(lexer.nextToken()->getType() == lexer.SEMICOLON);
}

TEST_CASE("Boolean constants, variables, integers, and white space", "[front-end]")
{
  antlr4::ANTLRInputStream input("\n \t \r true false hello 1234 0 EXF");
  WPLLexer lexer(&input);
  lexer.removeErrorListeners();
  lexer.addErrorListener(new TestErrorListener());
  CHECK(lexer.nextToken()->getType() == lexer.TRUE);
  CHECK(lexer.nextToken()->getType() == lexer.FALSE);
  CHECK(lexer.nextToken()->getType() == lexer.VARIABLE);
  CHECK(lexer.nextToken()->getType() == lexer.INTEGER);
  CHECK(lexer.nextToken()->getType() == lexer.INTEGER);
  CHECK(lexer.nextToken()->getType() == lexer.VARIABLE);
  CHECK(lexer.nextToken()->getType() == lexer.EOF);
}

TEST_CASE("Types", "[front-end]")
{

  SECTION("INT")
  {
    antlr4::ANTLRInputStream input("int");
    WPLLexer lexer(&input);
    lexer.removeErrorListeners();
    lexer.addErrorListener(new TestErrorListener());

    CHECK(lexer.nextToken()->getType() == lexer.TYPE_INT);
    CHECK(lexer.nextToken()->getType() == lexer.EOF);
  }

  SECTION("STR")
  {
    antlr4::ANTLRInputStream input("str");
    WPLLexer lexer(&input);
    lexer.removeErrorListeners();
    lexer.addErrorListener(new TestErrorListener());

    CHECK(lexer.nextToken()->getType() == lexer.TYPE_STR);
    CHECK(lexer.nextToken()->getType() == lexer.EOF);
  }
}

/****************** Negative tests ******************/

TEST_CASE("Invalid lexemes", "[front-end]")
{
  antlr4::ANTLRInputStream input("`");
  WPLLexer lexer(&input);
  lexer.removeErrorListeners();
  lexer.addErrorListener(new TestErrorListener());

  // The next assertion works if we do not have our test error listener
  // CHECK_FALSE(lexer.nextToken()->getType() != lexer.EOF);
  CHECK_THROWS(lexer.nextToken());
}