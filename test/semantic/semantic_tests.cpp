#include <catch2/catch_test_macros.hpp>
#include "antlr4-runtime.h"
#include "WPLLexer.h"
#include "WPLParser.h"
#include "WPLErrorHandler.h"
#include "SemanticVisitor.h"

#include "test_error_handlers.h"

TEST_CASE("Development Semantic tests", "[semantic]")
{
  antlr4::ANTLRInputStream input("42;");
  WPLLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  SemanticVisitor *sv = new SemanticVisitor(new STManager(), new PropertyManager());
  sv->visitCompilationUnit(tree);                                                    
  // if (sv->hasErrors(ERROR)) {
  //   CHECK("foo" == sv->getErrors());
  // }
  CHECK_FALSE(sv->hasErrors(ERROR));
}


TEST_CASE("Invalid Array Semantics", "[semantic]")
{
  antlr4::ANTLRInputStream input("int [0] a;");
  WPLLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);
  SemanticVisitor *sv = new SemanticVisitor(new STManager(), new PropertyManager());
  sv->visitCompilationUnit(tree);                                                    
  REQUIRE(sv->hasErrors(ERROR));
}
TEST_CASE("Bool Const Tests", "[semantic]")
{
  antlr4::ANTLRInputStream input("false; true;");
  WPLLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  WPLParser::CompilationUnitContext *tree = NULL;

  REQUIRE_NOTHROW(tree = parser.compilationUnit());
  REQUIRE(tree != NULL);

  SemanticVisitor *sv = new SemanticVisitor(new STManager(), new PropertyManager());
  sv->visitCompilationUnit(tree);

  CHECK_FALSE(sv->hasErrors(ERROR));
}

TEST_CASE("Type from compilationUnit", "[semantic]")
{
  antlr4::ANTLRInputStream input("int"); // We should get filtered out here
  WPLLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  WPLParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(new TestErrorListener());
  WPLParser::CompilationUnitContext *tree = NULL;
  REQUIRE_THROWS(tree = parser.compilationUnit());
  REQUIRE(tree == NULL);
}

//FIXME: FIND A WAY TO RE-ENABLE!
// TEST_CASE("Visit Type - INT", "[semantic]")
// {
//   antlr4::ANTLRInputStream input("int"); // We shouldn't get filtered out here
//   WPLLexer lexer(&input);
//   antlr4::CommonTokenStream tokens(&lexer);
//   WPLParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());
//   WPLParser::TypeContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.type());
//   REQUIRE(tree != NULL);

//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   SemanticVisitor *sv = new SemanticVisitor(stmgr, new PropertyManager());

//   const Type *ty = std::any_cast<const Type *>(tree->accept(sv));//sv->visit(tree));

//   REQUIRE(ty->isSubtype(Types::INT));
// }


TEST_CASE("Test Type Equality - Subtypes", "[semantic]")
{
  Type *TOP = new Type();
  Type *INT = new TypeInt();
  Type *BOOL = new TypeBool();
  Type *STR = new TypeStr();
  Type *BOT = new TypeBot();

  SECTION("Top Type tests")
  {
    REQUIRE(TOP->isSubtype(TOP));

    REQUIRE(TOP->isNotSubtype(INT));
    REQUIRE_FALSE(TOP->isSubtype(INT));

    REQUIRE(TOP->isNotSubtype(BOOL));
    REQUIRE_FALSE(TOP->isSubtype(BOOL));

    REQUIRE(TOP->isNotSubtype(STR));

    REQUIRE(TOP->isNotSubtype(BOT));
  }

  SECTION("Int Type tests")
  {
    REQUIRE(INT->isSubtype(TOP));
    REQUIRE_FALSE(INT->isNotSubtype(TOP));

    REQUIRE(INT->isSubtype(INT));
    // REQUIRE(INT->isNotSubtype(TypeInt()));

    REQUIRE(INT->isNotSubtype(BOOL));

    REQUIRE(INT->isNotSubtype(STR));

    REQUIRE(INT->isNotSubtype(BOT));
  }

  SECTION("Bool Type Tests")
  {
    REQUIRE(BOOL->isSubtype(TOP));
    REQUIRE(BOOL->isNotSubtype(INT));
    REQUIRE(BOOL->isNotSubtype(STR));
    REQUIRE(BOOL->isSubtype(BOOL));
    REQUIRE(BOOL->isNotSubtype(BOT));
  }

  SECTION("Str Type Tests")
  {
    REQUIRE(STR->isSubtype(TOP));
    REQUIRE(STR->isNotSubtype(INT));
    REQUIRE(STR->isSubtype(STR));
    REQUIRE(STR->isNotSubtype(BOOL));
    REQUIRE(STR->isNotSubtype(BOT));
  }

  SECTION("Bot Type Tests")
  {
    REQUIRE(BOT->isSubtype(TOP));
    REQUIRE_FALSE(BOT->isSubtype(INT));
    REQUIRE_FALSE(BOT->isSubtype(STR));
    REQUIRE_FALSE(BOT->isSubtype(BOOL));
    REQUIRE_FALSE(BOT->isSubtype(BOT));
  }
  // Why is PL easier to read in mono fonts?
}

TEST_CASE("Test Type Equality - Supertype", "[semantic]")
{
  Type *TOP = new Type();
  Type *INT = new TypeInt();
  Type *BOOL = new TypeBool();
  Type *STR = new TypeStr();
  Type *BOT = new TypeBot();

  SECTION("Top Type tests")
  {
    REQUIRE(TOP->isSupertype(TOP));
    REQUIRE_FALSE(TOP->isNotSupertype(TOP));

    REQUIRE(TOP->isSupertype(INT));
    REQUIRE_FALSE(TOP->isNotSupertype(INT));

    REQUIRE(TOP->isSupertype(BOOL));
    REQUIRE_FALSE(TOP->isNotSupertype(BOOL));

    REQUIRE(TOP->isSupertype(STR));

    REQUIRE(TOP->isSupertype(BOT));
  }

  SECTION("Int Type tests")
  {
    REQUIRE(INT->isNotSupertype(TOP));
    REQUIRE_FALSE(INT->isSupertype(TOP));

    REQUIRE(INT->isSupertype(INT));
    // REQUIRE(INT->isSupertype(TypeInt()));

    REQUIRE(INT->isNotSupertype(BOOL));

    REQUIRE(INT->isNotSupertype(STR));

    REQUIRE(INT->isNotSupertype(BOT));
  }

  SECTION("Bool Type Tests")
  {
    REQUIRE(BOOL->isNotSupertype(TOP));
    REQUIRE(BOOL->isNotSupertype(INT));
    REQUIRE(BOOL->isNotSupertype(STR));
    REQUIRE(BOOL->isSupertype(BOOL));
    REQUIRE(BOOL->isNotSupertype(BOT));
  }

  SECTION("Str Type Tests")
  {
    REQUIRE(STR->isNotSupertype(TOP));
    REQUIRE(STR->isNotSupertype(INT));
    REQUIRE(STR->isSupertype(STR));
    REQUIRE(STR->isNotSupertype(BOOL));
    REQUIRE(STR->isNotSupertype(BOT));
  }

  SECTION("Bot Type Tests")
  {
    REQUIRE(BOT->isNotSupertype(TOP));
    REQUIRE(BOT->isNotSupertype(INT));
    REQUIRE(BOT->isNotSupertype(STR));
    REQUIRE(BOT->isNotSupertype(BOOL));
    REQUIRE(BOT->isNotSupertype(BOT));
  }
  // Why is PL easier to read in mono fonts?
}