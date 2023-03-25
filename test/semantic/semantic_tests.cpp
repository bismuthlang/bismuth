#include <catch2/catch_test_macros.hpp>
#include "antlr4-runtime.h"
#include "BismuthLexer.h"
#include "BismuthParser.h"
#include "BismuthErrorHandler.h"
#include "SemanticVisitor.h"

#include "test_error_handlers.h"

TEST_CASE("Test Type Equality - Subtypes", "[semantic]")
{
  Type *TOP = new Type();
  Type *INT = new TypeInt();
  Type *BOOL = new TypeBool();
  Type *STR = new TypeStr();
  Type *BOT = new TypeBottom();
  Type* UNIT = new TypeUnit(); 
  Type* ABSD = new TypeAbsurd(); 

  SECTION("Top Type tests")
  {
    REQUIRE(TOP->isSubtype(TOP));

    REQUIRE(TOP->isNotSubtype(INT));
    REQUIRE_FALSE(TOP->isSubtype(INT));

    REQUIRE(TOP->isNotSubtype(BOOL));
    REQUIRE_FALSE(TOP->isSubtype(BOOL));

    REQUIRE(TOP->isNotSubtype(STR));

    REQUIRE(TOP->isNotSubtype(BOT));

    REQUIRE(TOP->isNotSubtype(UNIT));
    REQUIRE(TOP->isNotSubtype(ABSD));
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

    REQUIRE(INT->isNotSubtype(UNIT));
    REQUIRE(INT->isNotSubtype(ABSD));
  }

  SECTION("Bool Type Tests")
  {
    REQUIRE(BOOL->isSubtype(TOP));
    REQUIRE(BOOL->isNotSubtype(INT));
    REQUIRE(BOOL->isNotSubtype(STR));
    REQUIRE(BOOL->isSubtype(BOOL));
    REQUIRE(BOOL->isNotSubtype(BOT));
    REQUIRE(BOOL->isNotSubtype(UNIT));
    REQUIRE(BOOL->isNotSubtype(ABSD));
  }

  SECTION("Str Type Tests")
  {
    REQUIRE(STR->isSubtype(TOP));
    REQUIRE(STR->isNotSubtype(INT));
    REQUIRE(STR->isSubtype(STR));
    REQUIRE(STR->isNotSubtype(BOOL));
    REQUIRE(STR->isNotSubtype(BOT));
    REQUIRE(STR->isNotSubtype(UNIT));
    REQUIRE(STR->isNotSubtype(ABSD));
  }

  SECTION("Bot Type Tests")
  {
    REQUIRE(BOT->isSubtype(TOP));
    REQUIRE_FALSE(BOT->isSubtype(INT)); //FIXME: THESE SEEM WRONG.... MAYBE?
    REQUIRE_FALSE(BOT->isSubtype(STR));
    REQUIRE_FALSE(BOT->isSubtype(BOOL));
    REQUIRE_FALSE(BOT->isSubtype(BOT));
    REQUIRE_FALSE(BOT->isSubtype(UNIT));
    REQUIRE_FALSE(BOT->isSubtype(ABSD));
  }

  SECTION("Unit Type Tests")
  {
    REQUIRE(UNIT->isSubtype(TOP));
    REQUIRE_FALSE(UNIT->isSubtype(INT));
    REQUIRE_FALSE(UNIT->isSubtype(STR));
    REQUIRE_FALSE(UNIT->isSubtype(BOOL));
    REQUIRE_FALSE(UNIT->isSubtype(BOT));
    REQUIRE(UNIT->isSubtype(UNIT));
    REQUIRE_FALSE(UNIT->isSubtype(ABSD));
  }

  SECTION("Absurd Type Tests")
  {
    REQUIRE(ABSD->isSubtype(TOP));
    REQUIRE_FALSE(ABSD->isSubtype(INT));
    REQUIRE_FALSE(ABSD->isSubtype(STR));
    REQUIRE_FALSE(ABSD->isSubtype(BOOL));
    REQUIRE_FALSE(ABSD->isSubtype(BOT));
    REQUIRE_FALSE(ABSD->isSubtype(UNIT));
    REQUIRE_FALSE(ABSD->isSubtype(ABSD));
  }
  // Why is PL easier to read in mono fonts?
}

TEST_CASE("Test Type Equality - Supertype", "[semantic]")
{
  Type *TOP = new Type();
  Type *INT = new TypeInt();
  Type *BOOL = new TypeBool();
  Type *STR = new TypeStr();
  Type *BOT = new TypeBottom();
  Type* UNIT = new TypeUnit(); 
  Type* ABSD = new TypeAbsurd(); 

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

    REQUIRE(TOP->isSupertype(UNIT));
    REQUIRE(TOP->isSupertype(ABSD));
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

    REQUIRE(INT->isNotSupertype(UNIT));
    REQUIRE(INT->isNotSupertype(ABSD));
  }

  SECTION("Bool Type Tests")
  {
    REQUIRE(BOOL->isNotSupertype(TOP));
    REQUIRE(BOOL->isNotSupertype(INT));
    REQUIRE(BOOL->isNotSupertype(STR));
    REQUIRE(BOOL->isSupertype(BOOL));
    REQUIRE(BOOL->isNotSupertype(BOT));
    REQUIRE(BOOL->isNotSupertype(UNIT));
    REQUIRE(BOOL->isNotSupertype(ABSD));
  }

  SECTION("Str Type Tests")
  {
    REQUIRE(STR->isNotSupertype(TOP));
    REQUIRE(STR->isNotSupertype(INT));
    REQUIRE(STR->isSupertype(STR));
    REQUIRE(STR->isNotSupertype(BOOL));
    REQUIRE(STR->isNotSupertype(BOT));
    REQUIRE(STR->isNotSupertype(UNIT));
    REQUIRE(STR->isNotSupertype(ABSD));
  }

  SECTION("Bot Type Tests")
  {
    REQUIRE(BOT->isNotSupertype(TOP));
    REQUIRE(BOT->isNotSupertype(INT));
    REQUIRE(BOT->isNotSupertype(STR));
    REQUIRE(BOT->isNotSupertype(BOOL));
    REQUIRE(BOT->isNotSupertype(BOT));
    REQUIRE(BOT->isNotSupertype(UNIT));
    REQUIRE(BOT->isNotSupertype(ABSD));
  }

  SECTION("Unit Type Tests")
  {
    REQUIRE(UNIT->isNotSupertype(TOP));
    REQUIRE(UNIT->isNotSupertype(INT));
    REQUIRE(UNIT->isNotSupertype(STR));
    REQUIRE(UNIT->isNotSupertype(BOOL));
    REQUIRE(UNIT->isNotSupertype(BOT));
    REQUIRE(UNIT->isSubtype(UNIT));
    REQUIRE(UNIT->isNotSupertype(ABSD));
  }

  SECTION("Absurd Type Tests")
  {
    REQUIRE(ABSD->isNotSupertype(TOP));
    REQUIRE(ABSD->isNotSupertype(INT));
    REQUIRE(ABSD->isNotSupertype(STR));
    REQUIRE(ABSD->isNotSupertype(BOOL));
    REQUIRE(ABSD->isNotSupertype(BOT));
    REQUIRE(ABSD->isNotSupertype(UNIT));
    REQUIRE(ABSD->isNotSupertype(ABSD));
  }
  // Why is PL easier to read in mono fonts?
}