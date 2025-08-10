#include <catch2/catch_test_macros.hpp>
#include "BismuthLexer.h"
#include "BismuthParser.h"
#include "BismuthErrorHandler.h"
#include "SemanticVisitor.h"

#include "test_error_handlers.h"



void EnsureNoErrors(antlr4::ANTLRInputStream input, bool demoMode=false);

void EnsureNoErrors(std::string program, bool demoMode=false);


void EnsureErrorsWithMessage(antlr4::ANTLRInputStream input, std::string message, bool demoMode=false);

void EnsureErrorsWithMessage(std::string program, std::string message, bool demoMode=false);


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
 EnsureNoErrors(input);
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
  EnsureErrorsWithMessage(input, "Select statement expected at least one alternative, but was given 0!");
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
  EnsureErrorsWithMessage(input, "Assignment statement expected boolean but got int");
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
  EnsureNoErrors(input);
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
  EnsureNoErrors(input);
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
  EnsureNoErrors(input);
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
  EnsureErrorsWithMessage(input, "Dead code: definition as select alternative");
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
  EnsureErrorsWithMessage(input, "Dead code: definition as select alternative");
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
  EnsureErrorsWithMessage(input, "Dead code: definition as select alternative");
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
  EnsureErrorsWithMessage(input, "Select alternative expected boolean but got str");
}
