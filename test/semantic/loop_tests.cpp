#include <catch2/catch_test_macros.hpp>
#include "antlr4-runtime.h"
#include "BismuthLexer.h"
#include "BismuthParser.h"
#include "BismuthErrorHandler.h"
#include "SemanticVisitor.h"

#include "test_error_handlers.h"

/*
 * FIXME: test loops more robustly AND REENABLE
 */

void EnsureErrorsWithMessage(antlr4::ANTLRInputStream input, std::string message, bool demoMode=false);

void EnsureErrorsWithMessage(std::string program, std::string message, bool demoMode=false);


void EnsureNoErrors(antlr4::ANTLRInputStream input, bool demoMode=false);

void EnsureNoErrors(std::string program, bool demoMode=false);

TEST_CASE("Undefined Params", "[semantic][loop]")
{
  EnsureErrorsWithMessage(
    R""""(
    func a() {
        while i < 10 {
            sum := sum * 2;
            i := i + 1;
        }
    }
  )"""",
  "Undefined variable reference: i"
  );
}


TEST_CASE("Undefined Params 2", "[semantic][loop]")
{
    EnsureErrorsWithMessage(
    R""""(
    func a() {
       int i := 0;
        while i < 10 {
            sum := sum * 2;
            i := i + 1;
        }
    }
  )"""",
  "Undefined variable reference: sum"
  );
}


TEST_CASE("Check example", "[semantic][loop]")
{
    EnsureNoErrors(
    R""""(
    func a() {
       int i := 0, sum := 1;
        while i < 10 {
            sum := sum * 2;
            i := i + 1;
        }
    }
  )""""
  );
}

// TEST_CASE("Check example - adv", "[semantic][loop]")
// {
//   antlr4::ANTLRInputStream input(
//     "int i := 0, sum := 1;"
//     "while i < 10 {"
//     " sum := sum * 2; "
//     " i := i + 1; "  
//     " str s := \"scope\";"  
//     "}"
//   );
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // auto lListener = TestErrorListener();
//   // lexer.addErrorListener(&lListener);
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   auto pListener = TestErrorListener(); 
//   parser.addErrorListener(&pListener);

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager stmgr = STManager();
//   SemanticVisitor sv = SemanticVisitor(&stmgr);

//   sv.visitCompilationUnit(tree);

//   CHECK_FALSE(sv.hasErrors(ERROR));

//   {
//     std::optional<SymbolContext> opt = stmgr->lookup("a");
//     CHECK_FALSE(opt.has_value());
//   }

//   {
//     std::optional<SymbolContext> opt = stmgr->lookup("i"); //FIXME: CHECK CONTEXT
//     CHECK(opt.has_value());
//     CHECK(opt.value().second->type->isSubtype(Types::DYN_INT));
//   }


//   {
//     std::optional<SymbolContext> opt = stmgr->lookup("sum");
//     CHECK(opt.has_value());
//     CHECK(opt.value().second->type->isSubtype(Types::DYN_INT));
//   }

//   {
//     std::optional<SymbolContext> opt = stmgr->lookup("s");
//     CHECK_FALSE(opt.has_value());
//   }
// }

TEST_CASE("Sit & Spin", "[semantic][loop]")
{
    EnsureNoErrors(R""""(
        func a() {
            while true {
            }
        }
        )""""
    );
}

TEST_CASE("Int condition", "[semantic][loop]")
{
  EnsureErrorsWithMessage(R""""(
        func a() {
            while 1 {
            }
        }
        )"""",
        "Condition expected boolean, but was given int"
    );
}

TEST_CASE("Int condition 2", "[semantic][loop]")
{
    EnsureErrorsWithMessage(R""""(
        func a() {
            while  1 * 3 / 2 {
            }
        }
        )"""",
        "Condition expected boolean, but was given int"
    );
}

TEST_CASE("str condition", "[semantic][loop]")
{
    EnsureErrorsWithMessage(R""""(
        func a() {
            while "This is not a boolean" {
            }
        }
        )"""",
        "Condition expected boolean, but was given str"
    );
}

TEST_CASE("Boolean Expr", "[semantic][loop]")
{
    EnsureNoErrors(R""""(
        func a() {
            while !false && true || false {
            }
        }
        )""""
    );
}
