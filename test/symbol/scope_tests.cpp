/**
 * @file scope_tests.cpp
 * @author Alex Friedman (ahfriedman.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <catch2/catch_test_macros.hpp>
#include "Scope.h"
#include <iostream>

// TEST_CASE("Check symbol return from add", "[symbol]") {
//   Scope* scope = new Scope();
//   Symbol* s = scope->addSymbol("a", Types::DYN_BOOL);
//   CHECK(s->identifier == "a");
//   Symbol* s2 = scope->addSymbol("b", TYPES::DYN_INT);
//   // Check same values
//   CHECK("b" == s2->identifier);
//   CHECK(Types::DYN_INT == s2->type);
//   // Uncomment the next in order to see what a scope string looks like.
//   // CHECK(scope->toString() == "foo");
// }

TEST_CASE("Find existing element", "[symbol") {
  Scope* scope = new Scope();
  Symbol* s = new Symbol("a", Types::DYN_BOOL, false, false);
  CHECK(scope->addSymbol(s));

  auto s1 = scope->lookup("a");

  CHECK(s1.has_value());

  CHECK(s1.value() == s);
}

TEST_CASE("Look for non-existent element", "[symbol]") {
  Scope* scope = new Scope();
  CHECK(scope->addSymbol(new Symbol("a", Types::DYN_BOOL, false, false)));
  CHECK(!(scope->lookup("b").has_value()));
}

TEST_CASE("Duplicate symbol", "[symbol]") {
  Scope* scope = new Scope();
  CHECK(scope->addSymbol(new Symbol("a", Types::DYN_BOOL, false, false)));
  CHECK(!(scope->addSymbol(new Symbol("a", Types::DYN_INT, false, false))));
}