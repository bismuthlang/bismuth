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

void EnsureErrorsWithMessage(antlr4::ANTLRInputStream input, std::string message, bool demoMode=false);

void EnsureErrorsWithMessage(std::string program, std::string message, bool demoMode=false);


void EnsureNoErrors(antlr4::ANTLRInputStream input, bool demoMode=false);

void EnsureNoErrors(std::string program, bool demoMode=false);


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
  EnsureNoErrors(input);
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
  EnsureNoErrors(input);
}