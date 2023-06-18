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

// TEST_CASE("Undefined Params", "[semantic][loop]")
// {
//   antlr4::ANTLRInputStream input(
//     "while i < 10 {"
//     " sum := sum * 2; "
//     " i := i + 1; "    
//     "}"
//   );
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   CHECK(sv->hasErrors(ERROR));
// }


// TEST_CASE("Undefined Params 2", "[semantic][loop]")
// {
//   antlr4::ANTLRInputStream input(
//     "int i := 0;"
//     "while i < 10 {"
//     " sum := sum * 2; "
//     " i := i + 1; "    
//     "}"
//   );
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   CHECK(sv->hasErrors(ERROR));
// }


// TEST_CASE("Check example", "[semantic][loop]")
// {
//   antlr4::ANTLRInputStream input(
//     "int i := 0, sum := 1;"
//     "while i < 10 {"
//     " sum := sum * 2; "
//     " i := i + 1; "    
//     "}"
//   );
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   CHECK_FALSE(sv->hasErrors(ERROR));
// }

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
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);

//   CHECK_FALSE(sv->hasErrors(ERROR));

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

// TEST_CASE("Sit & Spin", "[semantic][loop]")
// {
//   antlr4::ANTLRInputStream input(
//     "while true {"
//     "}"
//   );
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);
//   CHECK_FALSE(sv->hasErrors(ERROR));
// }

// TEST_CASE("Int condition", "[semantic][loop]")
// {
//   antlr4::ANTLRInputStream input(
//     "while 1 {"
//     "}"
//   );
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);

//   CHECK(sv->hasErrors(ERROR));
// }

// TEST_CASE("Int condition 2", "[semantic][loop]")
// {
//   antlr4::ANTLRInputStream input(
//     "while 1 * 3 / 2 {"
//     "}"
//   );
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);

//   CHECK(sv->hasErrors(ERROR));
// }

// TEST_CASE("str condition", "[semantic][loop]")
// {
//   antlr4::ANTLRInputStream input(
//     "while \"This is not a boolean\" {"
//     "}"
//   );
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);

//   CHECK(sv->hasErrors(ERROR));
// }

// TEST_CASE("Boolean Expr", "[semantic][loop]")
// {
//   antlr4::ANTLRInputStream input(
//     "while ~false & true | false {"
//     "}"
//   );
//   BismuthLexer lexer(&input);
//   // lexer.removeErrorListeners();
//   // lexer.addErrorListener(new TestErrorListener());
//   antlr4::CommonTokenStream tokens(&lexer);
//   BismuthParser parser(&tokens);
//   parser.removeErrorListeners();
//   parser.addErrorListener(new TestErrorListener());

//   BismuthParser::CompilationUnitContext *tree = NULL;
//   REQUIRE_NOTHROW(tree = parser.compilationUnit());
//   REQUIRE(tree != NULL);
//   REQUIRE(tree->getText() != "");

//   STManager *stmgr = new STManager();
//   SemanticVisitor *sv = new SemanticVisitor(stmgr);

//   sv->visitCompilationUnit(tree);

//   CHECK_FALSE(sv->hasErrors(ERROR));
// }
