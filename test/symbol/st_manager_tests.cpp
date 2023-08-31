#include <catch2/catch_test_macros.hpp>
#include "Context.h"

TEST_CASE("add a scope", "[symbol]") {
  Context mgr;
  CHECK(mgr.scopeCount() == 0);
  Scope& s = mgr.enterScope();
  CHECK(mgr.scopeCount() == 1);
  Scope* s1 = mgr.getCurrentScope().value();
  CHECK(&s == s1);
  CHECK(0 == s1->getId());
}

TEST_CASE("multiple scopes", "[symbol]") {
  Context mgr;
  Scope &s1 = mgr.enterScope();
  CHECK(0 == s1.getId());
  Scope &s2 = mgr.enterScope();
  CHECK(1 == s2.getId());
  CHECK(0 == s2.getParent().value()->getId());
  Scope &s3 = mgr.enterScope();
  CHECK(1 == s3.getParent().value()->getId());
  Scope* temp = mgr.exitScope().value();
  CHECK(s3.getId() == temp->getId());
  Scope &s4 = mgr.enterScope();
  CHECK(1 == s4.getParent().value()->getId());
  CHECK(3 == s4.getId());
}

TEST_CASE("multiple scopes with symbols", "[symbol]") {
  Context mgr;
  Scope &s1 = mgr.enterScope();
  CHECK(0 == s1.getId());
  mgr.addSymbol(new Symbol("a", Types::DYN_BOOL, false, false));
  mgr.addSymbol(new Symbol("b", Types::DYN_INT, false, false));
  CHECK(mgr.lookup("a").value()->type->isSubtype(Types::DYN_BOOL));
  CHECK(!mgr.lookup("x").has_value());
  Scope &s2 = mgr.enterScope();
  mgr.addSymbol(new Symbol("a", Types::DYN_INT, false, false));
  mgr.addSymbol(new Symbol("c", Types::DYN_INT, false, false));
  CHECK(mgr.lookup("a").value()->type->isSubtype(Types::DYN_INT));
  Scope &s3 = mgr.enterScope();
  CHECK(2 == s3.getId());
  mgr.addSymbol(new Symbol("c", Types::DYN_BOOL, false, false));
  mgr.addSymbol(new Symbol("d", Types::DYN_INT, false, false));
  CHECK(mgr.lookup("b").value()->type->isSubtype(Types::DYN_INT));
  CHECK(mgr.lookup("c").value()->type->isSubtype(Types::DYN_BOOL));
  mgr.exitScope();
  Scope &s4 = mgr.enterScope();
  CHECK(s4.getParent() == &s2);
  mgr.addSymbol(new Symbol("a", Types::DYN_INT, false, false));
  mgr.addSymbol(new Symbol("avar", Types::DYN_BOOL, false, false));
  CHECK(mgr.lookup("c").value()->type->isSubtype(Types::DYN_INT));
  CHECK(!mgr.lookup("d").has_value());
  // Uncomment the following to see the symbol table string
  // CHECK(mgr.toString() == "foo");
}