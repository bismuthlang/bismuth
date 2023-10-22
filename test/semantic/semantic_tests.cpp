#include <catch2/catch_test_macros.hpp>
#include "antlr4-runtime.h"
#include "BismuthLexer.h"
#include "BismuthParser.h"
#include "BismuthErrorHandler.h"
#include "SemanticVisitor.h"

#include "test_error_handlers.h"

TEST_CASE("Test Type Equality - Subtypes", "[semantic]")
{
  Type *TopTy = new Type(false);
  Type *IntTy = new TypeInt(false);
  Type *BoolTy = new TypeBool(false);
  Type *StrTy = new TypeStr(false);
  Type *BotTy = new TypeBottom(false);
  Type* UnitTy = new TypeUnit(false); 
  Type* AbsurdTy = new TypeAbsurd(false); 

  SECTION("Top Type tests")
  {
    REQUIRE(TopTy->isSubtype(TopTy));

    REQUIRE(TopTy->isNotSubtype(IntTy));
    REQUIRE_FALSE(TopTy->isSubtype(IntTy));

    REQUIRE(TopTy->isNotSubtype(BoolTy));
    REQUIRE_FALSE(TopTy->isSubtype(BoolTy));

    REQUIRE(TopTy->isNotSubtype(StrTy));

    REQUIRE(TopTy->isNotSubtype(BotTy));

    REQUIRE(TopTy->isNotSubtype(UnitTy));
    REQUIRE(TopTy->isNotSubtype(AbsurdTy));
  }

  SECTION("Int Type tests")
  {
    REQUIRE(IntTy->isSubtype(TopTy));
    REQUIRE_FALSE(IntTy->isNotSubtype(TopTy));

    REQUIRE(IntTy->isSubtype(IntTy));
    // REQUIRE(IntTy->isNotSubtype(TypeInt()));

    REQUIRE(IntTy->isNotSubtype(BoolTy));

    REQUIRE(IntTy->isNotSubtype(StrTy));

    REQUIRE(IntTy->isNotSubtype(BotTy));

    REQUIRE(IntTy->isNotSubtype(UnitTy));
    REQUIRE(IntTy->isNotSubtype(AbsurdTy));
  }

  SECTION("Bool Type Tests")
  {
    REQUIRE(BoolTy->isSubtype(TopTy));
    REQUIRE(BoolTy->isNotSubtype(IntTy));
    REQUIRE(BoolTy->isNotSubtype(StrTy));
    REQUIRE(BoolTy->isSubtype(BoolTy));
    REQUIRE(BoolTy->isNotSubtype(BotTy));
    REQUIRE(BoolTy->isNotSubtype(UnitTy));
    REQUIRE(BoolTy->isNotSubtype(AbsurdTy));
  }

  SECTION("Str Type Tests")
  {
    REQUIRE(StrTy->isSubtype(TopTy));
    REQUIRE(StrTy->isNotSubtype(IntTy));
    REQUIRE(StrTy->isSubtype(StrTy));
    REQUIRE(StrTy->isNotSubtype(BoolTy));
    REQUIRE(StrTy->isNotSubtype(BotTy));
    REQUIRE(StrTy->isNotSubtype(UnitTy));
    REQUIRE(StrTy->isNotSubtype(AbsurdTy));
  }

  SECTION("Bot Type Tests")
  {
    REQUIRE(BotTy->isSubtype(TopTy));
    REQUIRE_FALSE(BotTy->isSubtype(IntTy)); //FIXME: THESE SEEM WRONG.... MAYBE?
    REQUIRE_FALSE(BotTy->isSubtype(StrTy));
    REQUIRE_FALSE(BotTy->isSubtype(BoolTy));
    REQUIRE_FALSE(BotTy->isSubtype(BotTy));
    REQUIRE_FALSE(BotTy->isSubtype(UnitTy));
    REQUIRE_FALSE(BotTy->isSubtype(AbsurdTy));
  }

  SECTION("Unit Type Tests")
  {
    REQUIRE(UnitTy->isSubtype(TopTy));
    REQUIRE_FALSE(UnitTy->isSubtype(IntTy));
    REQUIRE_FALSE(UnitTy->isSubtype(StrTy));
    REQUIRE_FALSE(UnitTy->isSubtype(BoolTy));
    REQUIRE_FALSE(UnitTy->isSubtype(BotTy));
    REQUIRE(UnitTy->isSubtype(UnitTy));
    REQUIRE_FALSE(UnitTy->isSubtype(AbsurdTy));
  }

  SECTION("Absurd Type Tests")
  {
    REQUIRE(AbsurdTy->isSubtype(TopTy));
    REQUIRE_FALSE(AbsurdTy->isSubtype(IntTy));
    REQUIRE_FALSE(AbsurdTy->isSubtype(StrTy));
    REQUIRE_FALSE(AbsurdTy->isSubtype(BoolTy));
    REQUIRE_FALSE(AbsurdTy->isSubtype(BotTy));
    REQUIRE_FALSE(AbsurdTy->isSubtype(UnitTy));
    REQUIRE_FALSE(AbsurdTy->isSubtype(AbsurdTy));
  }
  // Why is PL easier to read in mono fonts?
}

TEST_CASE("Test Type Equality - Supertype", "[semantic]")
{
  Type *TopTy = new Type(false);
  Type *IntTy = new TypeInt(false);
  Type *BoolTy = new TypeBool(false);
  Type *StrTy = new TypeStr(false);
  Type *BotTy = new TypeBottom(false);
  Type* UnitTy = new TypeUnit(false); 
  Type* AbsurdTy = new TypeAbsurd(false); 

  SECTION("Top Type tests")
  {
    REQUIRE(TopTy->isSupertype(TopTy));
    REQUIRE_FALSE(TopTy->isNotSupertype(TopTy));

    REQUIRE(TopTy->isSupertype(IntTy));
    REQUIRE_FALSE(TopTy->isNotSupertype(IntTy));

    REQUIRE(TopTy->isSupertype(BoolTy));
    REQUIRE_FALSE(TopTy->isNotSupertype(BoolTy));

    REQUIRE(TopTy->isSupertype(StrTy));

    REQUIRE(TopTy->isSupertype(BotTy));

    REQUIRE(TopTy->isSupertype(UnitTy));
    REQUIRE(TopTy->isSupertype(AbsurdTy));
  }

  SECTION("Int Type tests")
  {
    REQUIRE(IntTy->isNotSupertype(TopTy));
    REQUIRE_FALSE(IntTy->isSupertype(TopTy));

    REQUIRE(IntTy->isSupertype(IntTy));
    // REQUIRE(IntTy->isSupertype(TypeInt()));

    REQUIRE(IntTy->isNotSupertype(BoolTy));

    REQUIRE(IntTy->isNotSupertype(StrTy));

    REQUIRE(IntTy->isNotSupertype(BotTy));

    REQUIRE(IntTy->isNotSupertype(UnitTy));
    REQUIRE(IntTy->isNotSupertype(AbsurdTy));
  }

  SECTION("Bool Type Tests")
  {
    REQUIRE(BoolTy->isNotSupertype(TopTy));
    REQUIRE(BoolTy->isNotSupertype(IntTy));
    REQUIRE(BoolTy->isNotSupertype(StrTy));
    REQUIRE(BoolTy->isSupertype(BoolTy));
    REQUIRE(BoolTy->isNotSupertype(BotTy));
    REQUIRE(BoolTy->isNotSupertype(UnitTy));
    REQUIRE(BoolTy->isNotSupertype(AbsurdTy));
  }

  SECTION("Str Type Tests")
  {
    REQUIRE(StrTy->isNotSupertype(TopTy));
    REQUIRE(StrTy->isNotSupertype(IntTy));
    REQUIRE(StrTy->isSupertype(StrTy));
    REQUIRE(StrTy->isNotSupertype(BoolTy));
    REQUIRE(StrTy->isNotSupertype(BotTy));
    REQUIRE(StrTy->isNotSupertype(UnitTy));
    REQUIRE(StrTy->isNotSupertype(AbsurdTy));
  }

  SECTION("Bot Type Tests")
  {
    REQUIRE(BotTy->isNotSupertype(TopTy));
    REQUIRE(BotTy->isNotSupertype(IntTy));
    REQUIRE(BotTy->isNotSupertype(StrTy));
    REQUIRE(BotTy->isNotSupertype(BoolTy));
    REQUIRE(BotTy->isNotSupertype(BotTy));
    REQUIRE(BotTy->isNotSupertype(UnitTy));
    REQUIRE(BotTy->isNotSupertype(AbsurdTy));
  }

  SECTION("Unit Type Tests")
  {
    REQUIRE(UnitTy->isNotSupertype(TopTy));
    REQUIRE(UnitTy->isNotSupertype(IntTy));
    REQUIRE(UnitTy->isNotSupertype(StrTy));
    REQUIRE(UnitTy->isNotSupertype(BoolTy));
    REQUIRE(UnitTy->isNotSupertype(BotTy));
    REQUIRE(UnitTy->isSubtype(UnitTy));
    REQUIRE(UnitTy->isNotSupertype(AbsurdTy));
  }

  SECTION("Absurd Type Tests")
  {
    REQUIRE(AbsurdTy->isNotSupertype(TopTy));
    REQUIRE(AbsurdTy->isNotSupertype(IntTy));
    REQUIRE(AbsurdTy->isNotSupertype(StrTy));
    REQUIRE(AbsurdTy->isNotSupertype(BoolTy));
    REQUIRE(AbsurdTy->isNotSupertype(BotTy));
    REQUIRE(AbsurdTy->isNotSupertype(UnitTy));
    REQUIRE(AbsurdTy->isNotSupertype(AbsurdTy));
  }
  // Why is PL easier to read in mono fonts?
}

// FIXME: MAKE LINEAR SUPERTYPE OF NON-LINEAR