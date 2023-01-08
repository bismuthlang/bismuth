/**
 * @file codegen_tests.cpp
 * @author gpollice & ahfriedman
 * @brief Basic tests for code generation
 * @version 0.1
 * @date 2022-08-05
 */
#include <catch2/catch_test_macros.hpp>
#include "antlr4-runtime.h"
#include "WPLLexer.h"
#include "WPLParser.h"
#include "WPLErrorHandler.h"
#include "SemanticVisitor.h"
#include "CodegenVisitor.h"
#include "HashUtils.h"
#include "CompilerFlags.h"

//FIXME: REMOVE NO RUNTIME 
TEST_CASE("Development Codegen Tests", "[codegen]")
{
    antlr4::ANTLRInputStream input("define program :: c : Channel<-int> = { c.send(-1) }");
    WPLLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());
    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "cecbb03bb006f8ecf4e2c26f2002f3ca4e32da8bc74314405ef37da147ad2df2");
}

TEST_CASE("programs/test1 - General Overview", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/test1.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "61b8248a0a19ddaffe7c76567451b884bd47c6064c9193d1895f356dd84faa9b");
}

TEST_CASE("programs/test1a", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/test1a.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE(sv->hasErrors(0));

    // CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll");
    // cv->visitCompilationUnit(cuOpt.value());

    // REQUIRE_FALSE(cv->hasErrors(0));

    // REQUIRE(llvmIrToSHA256(cv->getModule()) == "e0f894f1b6dd6613bd18eee553f5d6c8896228b4e4a21400b5dd6f1433ab0670");
}

TEST_CASE("programs/test2 - Scopes, multiple assignments, equality (non-arrays)", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/test2.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "371c38f7ba67c50ac1ed90ec21808dd7287076e2ec27967982453112effe2eab");
}

TEST_CASE("programs/test3 - If w/o else", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/test3.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "b707071f5babbaa7ef5ec3fc83789e39005823a32f7e90162df63d6399b3c68d");
}

TEST_CASE("programs/test4a - Use and redeclaration of parameters", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/test4a.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "dcc5b894465e160455774da7e7169133a05ec7e595e72cb81a9c068fc3db0d73");
}

TEST_CASE("programs/test5 - Nested ifs and if equality", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/test5.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "b9c39606c29424eed14e72a29f68e1b5b2dcb98e3c66af1eddec758e5843b1b6");
}

TEST_CASE("programs/test6 - Basic Select with Return", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/test6.wpl");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "686f9e63c3f0c7f09de2dbc0ca6a6e8ae5161be63048a68814c74c5164c33305");
}

TEST_CASE("programs/testSelectBlock1 - Basic Select with Blocks that Return", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/testSelectBlock1.wpl");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    // NOTE: THIS SHOULD BE THE SAME AS test6!!!
    REQUIRE(llvmIrToSHA256(cv->getModule()) == "686f9e63c3f0c7f09de2dbc0ca6a6e8ae5161be63048a68814c74c5164c33305");
}

TEST_CASE("programs/test6a (CAFE!) - Basic Nested Selects, LEQ, GEQ", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/test6a.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "cafe2b3e17335a03444e7c3e1be095eaea8cb901741e8c0d8f1f79a17a8fe6c4");
}

TEST_CASE("programs/testSelectBlock2 - Select with blocks that don't return", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/testSelectBlock2.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    // NOTE: Should be same as test6a
    REQUIRE(llvmIrToSHA256(cv->getModule()) == "aab19eeabfaa6d2a6837e91b816f8b2b668e7597d8be5915e7eaa837b8bc6fae");
}

TEST_CASE("programs/test7 - Test String equality + Nested Loops", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/test7.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "cad97e5c713948d5c36f848c5ac3f43eb3bf6d69ede56b6d7453e20ee57ebac9");
}

TEST_CASE("programs/test8 - Nested Loops", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/test8.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "ad105752e5a6a363aed01d596c1b0257749b0afd3eda4d0f6e2e04deec6530ed");
}

// TEST_CASE("programs/test9i - Global Integers", "[codegen]")
// {
//     std::fstream *inStream = new std::fstream("/home/shared/programs/test9i.wpl");
//     antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//     WPLLexer lexer(input);
//     antlr4::CommonTokenStream tokens(&lexer);
//     WPLParser parser(&tokens);
//     parser.removeErrorListeners();
//     WPLParser::CompilationUnitContext *tree = NULL;
//     REQUIRE_NOTHROW(tree = parser.compilationUnit());
//     REQUIRE(tree != NULL);
//     STManager *stm = new STManager();
//     PropertyManager *pm = new PropertyManager();
//     SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
//     std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
//     REQUIRE(cuOpt.has_value());

//     REQUIRE_FALSE(sv->hasErrors(0));

//     CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "328e5295eaad33348eee23da5f8302153e778c8bb631707f37fd4d03daae7cfa");
// }

// TEST_CASE("programs/test9iv - Global Integer Inference", "[codegen]")
// {
//     std::fstream *inStream = new std::fstream("/home/shared/programs/test9iv.wpl");
//     antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//     WPLLexer lexer(input);
//     antlr4::CommonTokenStream tokens(&lexer);
//     WPLParser parser(&tokens);
//     parser.removeErrorListeners();
//     WPLParser::CompilationUnitContext *tree = NULL;
//     REQUIRE_NOTHROW(tree = parser.compilationUnit());
//     REQUIRE(tree != NULL);
//     STManager *stm = new STManager();
//     PropertyManager *pm = new PropertyManager();
//     SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
//     std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
//     REQUIRE(cuOpt.has_value());

//     REQUIRE_FALSE(sv->hasErrors(0));

//     CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "328e5295eaad33348eee23da5f8302153e778c8bb631707f37fd4d03daae7cfa");
// }

// TEST_CASE("programs/test9b - Global Booleans", "[codegen]")
// {
//     std::fstream *inStream = new std::fstream("/home/shared/programs/test9b.wpl");
//     antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//     WPLLexer lexer(input);
//     antlr4::CommonTokenStream tokens(&lexer);
//     WPLParser parser(&tokens);
//     parser.removeErrorListeners();
//     WPLParser::CompilationUnitContext *tree = NULL;
//     REQUIRE_NOTHROW(tree = parser.compilationUnit());
//     REQUIRE(tree != NULL);
//     STManager *stm = new STManager();
//     PropertyManager *pm = new PropertyManager();
//     SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
//     std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
//     REQUIRE(cuOpt.has_value());

//     REQUIRE_FALSE(sv->hasErrors(0));

//     CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "d871755f7c89cd02ee76c67541ec1935a2117a1e3f23cc86a09573fa1ef8422c");
// }

// TEST_CASE("programs/test9bv - Global Boolean Inference", "[codegen]")
// {
//     std::fstream *inStream = new std::fstream("/home/shared/programs/test9bv.wpl");
//     antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//     WPLLexer lexer(input);
//     antlr4::CommonTokenStream tokens(&lexer);
//     WPLParser parser(&tokens);
//     parser.removeErrorListeners();
//     WPLParser::CompilationUnitContext *tree = NULL;
//     REQUIRE_NOTHROW(tree = parser.compilationUnit());
//     REQUIRE(tree != NULL);
//     STManager *stm = new STManager();
//     PropertyManager *pm = new PropertyManager();
//     SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
//     std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
//     REQUIRE(cuOpt.has_value());

//     REQUIRE_FALSE(sv->hasErrors(0));

//     CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "d871755f7c89cd02ee76c67541ec1935a2117a1e3f23cc86a09573fa1ef8422c");
// }

// TEST_CASE("programs/test9s - Global Strings", "[codegen]")
// {
//     std::fstream *inStream = new std::fstream("/home/shared/programs/test9s.wpl");
//     antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//     WPLLexer lexer(input);
//     antlr4::CommonTokenStream tokens(&lexer);
//     WPLParser parser(&tokens);
//     parser.removeErrorListeners();
//     WPLParser::CompilationUnitContext *tree = NULL;
//     REQUIRE_NOTHROW(tree = parser.compilationUnit());
//     REQUIRE(tree != NULL);
//     STManager *stm = new STManager();
//     PropertyManager *pm = new PropertyManager();
//     SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
//     std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
//     REQUIRE(cuOpt.has_value());

//     REQUIRE_FALSE(sv->hasErrors(0));

//     CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "4b20b6db3a31f068485c29786b8ca97704cff2931829462517cf402811ed711a");
// }

// TEST_CASE("programs/test9sv - Global String Inference", "[codegen]")
// {
//     std::fstream *inStream = new std::fstream("/home/shared/programs/test9sv.wpl");
//     antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//     WPLLexer lexer(input);
//     antlr4::CommonTokenStream tokens(&lexer);
//     WPLParser parser(&tokens);
//     parser.removeErrorListeners();
//     WPLParser::CompilationUnitContext *tree = NULL;
//     REQUIRE_NOTHROW(tree = parser.compilationUnit());
//     REQUIRE(tree != NULL);
//     STManager *stm = new STManager();
//     PropertyManager *pm = new PropertyManager();
//     SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
//     std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
//     REQUIRE(cuOpt.has_value());

//     REQUIRE_FALSE(sv->hasErrors(0));

//     CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "4b20b6db3a31f068485c29786b8ca97704cff2931829462517cf402811ed711a");
// }

// TEST_CASE("programs/test9ba - Global Boolean Array", "[codegen]")
// {
//     std::fstream *inStream = new std::fstream("/home/shared/programs/test9ba.wpl");
//     antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//     WPLLexer lexer(input);
//     antlr4::CommonTokenStream tokens(&lexer);
//     WPLParser parser(&tokens);
//     parser.removeErrorListeners();
//     WPLParser::CompilationUnitContext *tree = NULL;
//     REQUIRE_NOTHROW(tree = parser.compilationUnit());
//     REQUIRE(tree != NULL);
//     STManager *stm = new STManager();
//     PropertyManager *pm = new PropertyManager();
//     SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
//     std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
//     REQUIRE(cuOpt.has_value());

//     REQUIRE_FALSE(sv->hasErrors(0));

//     CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "b6b98b36e98caffd2ef053023bd97db39bfc12c3a2c38b90bffacb8fb1436097");
// }

// TEST_CASE("programs/test9ia - Global Integer Array", "[codegen]")
// {
//     std::fstream *inStream = new std::fstream("/home/shared/programs/test9ia.wpl");
//     antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//     WPLLexer lexer(input);
//     antlr4::CommonTokenStream tokens(&lexer);
//     WPLParser parser(&tokens);
//     parser.removeErrorListeners();
//     WPLParser::CompilationUnitContext *tree = NULL;
//     REQUIRE_NOTHROW(tree = parser.compilationUnit());
//     REQUIRE(tree != NULL);
//     STManager *stm = new STManager();
//     PropertyManager *pm = new PropertyManager();
//     SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
//     std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
//     REQUIRE(cuOpt.has_value());

//     REQUIRE_FALSE(sv->hasErrors(0));

//     CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "0b667384676913d1b0aee9853fd9be42eabea34887e18cd1de6b54c5cf1823ca");
// }

// TEST_CASE("programs/test9sa - Global String Array - FLAWED", "[codegen]")
// {
//     std::fstream *inStream = new std::fstream("/home/shared/programs/test9sa.wpl");
//     antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//     WPLLexer lexer(input);
//     antlr4::CommonTokenStream tokens(&lexer);
//     WPLParser parser(&tokens);
//     parser.removeErrorListeners();
//     WPLParser::CompilationUnitContext *tree = NULL;
//     REQUIRE_NOTHROW(tree = parser.compilationUnit());
//     REQUIRE(tree != NULL);
//     STManager *stm = new STManager();
//     PropertyManager *pm = new PropertyManager();
//     SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
//     std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
//     REQUIRE(cuOpt.has_value());

//     REQUIRE_FALSE(sv->hasErrors(0));

//     CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "9e5834e13db9f511e072a26b22de0bee49ae44d914fc08ecb86f9b14f1c4fdc1");
// }

// TEST_CASE("programs/test9sa-1 - Global String Array - CORRECT", "[codegen]")
// {
//     std::fstream *inStream = new std::fstream("/home/shared/programs/test9sa-1.wpl");
//     antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//     WPLLexer lexer(input);
//     antlr4::CommonTokenStream tokens(&lexer);
//     WPLParser parser(&tokens);
//     parser.removeErrorListeners();
//     WPLParser::CompilationUnitContext *tree = NULL;
//     REQUIRE_NOTHROW(tree = parser.compilationUnit());
//     REQUIRE(tree != NULL);
//     STManager *stm = new STManager();
//     PropertyManager *pm = new PropertyManager();
//     SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
//     std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
//     REQUIRE(cuOpt.has_value());

//     REQUIRE_FALSE(sv->hasErrors(0));

//     CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "b7e94a1425ecfbc8a9b99dbc9160cb966bfcd7ae69e13bee2cf4702d310d9f0c");
// }

TEST_CASE("programs/test11 - Expressions in decl (let*) ", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/test11.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "9e1b331472a316541239a93687ac5794b3e1639454edcef5346da26ab774d694");
}

TEST_CASE("programs/test12 - Scopes & Prime Finder Example! ", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/test12.wpl");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "209c1960ddf81cfa4490c2d8a0501577b799bdacc5d829ce2530f094559ed915");
}

TEST_CASE("programs/test13 - Recursive Fibonacci", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/test13.wpl");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "fd2a506796e162de9e1a00a12e154827fa25a34833b68c68aa83750e3c4ab657");
}

// TEST_CASE("programs/test-runtime - Basic runtime tests", "[codegen]")
// {
//     // NOTE: tested linking each runtime function locally
//     std::fstream *inStream = new std::fstream("/home/shared/programs/test-runtime.wpl");
//     antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//     WPLLexer lexer(input);
//     antlr4::CommonTokenStream tokens(&lexer);
//     WPLParser parser(&tokens);
//     parser.removeErrorListeners();
//     WPLParser::CompilationUnitContext *tree = NULL;
//     REQUIRE_NOTHROW(tree = parser.compilationUnit());
//     REQUIRE(tree != NULL);
//     STManager *stm = new STManager();
//     PropertyManager *pm = new PropertyManager();
//     SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
//     std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
//     REQUIRE(cuOpt.has_value());

//     REQUIRE_FALSE(sv->hasErrors(0));

//     CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "6c84e861ca345b6cf3b11cf5abe99daed731acac1e48a302ac8efe6640cad7b6");
// }

TEST_CASE("programs/test-shortcircuit - Basic Short Circuit (and)", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/test-shortcircuit.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "7c2396be13623687194b4199b8fa3abadafddb89b1a4e36240455010c7914d1f");
}

TEST_CASE("programs/test-shortcircuit-rt - Basic Short Circuit (and + or) w/ Runtime", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/test-shortcircuit-rt.wpl");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "2309d18c37760ca695b7acd1fe81c7bf428ea5e44764f35e6c993780a3815459");
}

TEST_CASE("programs/test-arrayAssign - Assigning one array to another and editing arrays in functions", "[codegen]")
{
    // WPL is pass by value!

    std::fstream *inStream = new std::fstream("/home/shared/programs/test-arrayAssign.wpl");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "ea6cf3bb36fb69f95ea73e48f616f5dc4415f3184579cfe08d668d3722e865e3");
}

TEST_CASE("programs/externProc - Declaring an external proc", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/externProc.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "d2bd88d75c3fcb9a3a4d2c449ced75bca5a9e0abb8475449b6c7b4e7d14cd208");
}

TEST_CASE("programs/test14a - Test nested/more complex shorting", "[codegen]")
{
    // TODO: MANY OF THE SHORT CIRCUITING CASES COULD BE OPTIMIZED!!! -> Done?
    std::fstream *inStream = new std::fstream("/home/shared/programs/test14a.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "18befe8b4fb8d570eafe45e73d2437c499accadd56aa8bc9a653abd90cb6ebce");
}

TEST_CASE("programs/test18 - Parody", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/test18.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "5b81e72524788ad415f3be54356a81cba2d97249b0e67a3f98ca06fdb0c5609d");
}

// TEST_CASE("programs/test19 - Editing Global String and Using Across Inv", "[codegen]")
// {
//     std::fstream *inStream = new std::fstream("/home/shared/programs/test19.wpl");
//     antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//     WPLLexer lexer(input);
//     antlr4::CommonTokenStream tokens(&lexer);
//     WPLParser parser(&tokens);
//     parser.removeErrorListeners();
//     WPLParser::CompilationUnitContext *tree = NULL;
//     REQUIRE_NOTHROW(tree = parser.compilationUnit());
//     REQUIRE(tree != NULL);
//     STManager *stm = new STManager();
//     PropertyManager *pm = new PropertyManager();
//     SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
//     std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
//     REQUIRE(cuOpt.has_value());

//     REQUIRE_FALSE(sv->hasErrors(0));

//     CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "bd911e955a6da1d18d92cf4ca430456daa8ea8c4c8601f778e0f8bb83178222e");
// }

// TEST_CASE("programs/testGlobalAndLocal - Parody", "[codegen]")
// {
//     std::fstream *inStream = new std::fstream("/home/shared/programs/testGlobalAndLocal.wpl");
//     antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//     WPLLexer lexer(input);
//     antlr4::CommonTokenStream tokens(&lexer);
//     WPLParser parser(&tokens);
//     parser.removeErrorListeners();
//     WPLParser::CompilationUnitContext *tree = NULL;
//     REQUIRE_NOTHROW(tree = parser.compilationUnit());
//     REQUIRE(tree != NULL);
//     STManager *stm = new STManager();
//     PropertyManager *pm = new PropertyManager();
//     SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
//     std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
//     REQUIRE(cuOpt.has_value());

//     REQUIRE_FALSE(sv->hasErrors(0));

//     CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "f9b33450b1f1522122b1dffbf07819f959e08aac6ccdfc112cac7c25690a5c78");
// }

TEST_CASE("programs/forwardWrongArg - Forward Declaration w/ wrong arg name", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/forwardWrongArg.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE(sv->hasErrors(0));

    // CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    // cv->visitCompilationUnit(cuOpt.value());

    // REQUIRE(cv->hasErrors(0));

    // REQUIRE(llvmIrToSHA256(cv->getModule()) == "c1698114ebca6c348ee9f7ae41ea95a8d0377d0eda8f21711d3bb5501bee49ba");
}

TEST_CASE("programs/forwardWrongArg2 - Function syntax on process", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/forwardWrongArg2.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE(sv->hasErrors(0));

    // CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    // cv->visitCompilationUnit(cuOpt.value());

    // REQUIRE(cv->hasErrors(0));
}

TEST_CASE("programs/Lambda1 - Basic lambda Test", "[codegen][lambda]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/Lambda1.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "7f85ab3efb00ae5989d8993b35f32b6ba719a3167210e5dbb7ed438ba5135524");
}

TEST_CASE("programs/Lambda2 - Basic lambda Test w/ return", "[codegen][lambda]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/Lambda2.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "fc18974a336ba7f64c2b1f4ad7087c558ea8be6a242ce29613f2b3039b09c331");
}

TEST_CASE("programs/Lambda3 - Basic lambda Test w/ return and same name", "[codegen][lambda]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/Lambda3.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "779b9d305874f74e23f2b26bb232e087786227f6cf36ebe40bf2166b6bedfc65");
}

TEST_CASE("programs/externLambda", "[codegen][lambda]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/externLambda.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "b5235ff4d234116c2b168d6a11f2930bdfa53b07ab36e7af895ef52cba31913a");
}

TEST_CASE("programs/enum1 - Basic Enum 1", "[codegen][enum]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/enum1.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "2613567a29a7f41d945623f61c09ab5da66dc87dcc58046474fcf210004dd966");
}

TEST_CASE("programs/enum2 - Basic Enum 2", "[codegen][enum]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/enum2.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "81bf96b4ed3ebfba61974be24713eb5db1490ffa2f7b3f0d173fa2cd591fe6fd");
}

TEST_CASE("programs/enumAssign - Same a  Enum 2 but with assignmens outside of decl", "[codegen][enum]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/enumAssign.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "d28141fda4ffe2943a80619005d1b53a485b8edeb1b0a6a9d7b5e6efb6d9186d");
}

TEST_CASE("programs/enumAssign2 - Returning lambdas, functions, and enums", "[codegen][enum][lambda]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/enumAssign2.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "638573525dadddca5f5e924e4cafc22b1a16e6228aa39fce3a701db7e72abe87");
}

TEST_CASE("programs/enum3", "[codegen][enum]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/enum3.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "1cfe785dbe04efbe834cf809d64497a8da6b54f1851d41d0196eb6e03b3419b3");
}

TEST_CASE("programs/StructTest2", "[codegen][struct]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/adv/StructTest2.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "1b8654f1a5acc793c11543a1e703eb114d365a7993ff4ebe1f829b8e2d55e046");
}

TEST_CASE("programs/StructTest3", "[codegen][struct]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/adv/StructTest3.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "9f0e0ab4de7f68b4857f04b637f71fe5cf3cdbe1825ab4b1c5b70f57ee8f2dff");
}

TEST_CASE("programs/StructTest3a - nested fields", "[codegen][struct]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/adv/StructTest3a.wpl");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "58c43527727e01ae069ff43a95d8d62aed6e850d3f9693c3cb7c74efdab41b13");
}

TEST_CASE("programs/StructTest3b - nested fields", "[codegen][struct]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/adv/StructTest3b.wpl");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "f29652970edd86dff1e5cd7e80d41a43fbfe1b47f993eb7f5fb0fb06a2563d41");
}

TEST_CASE("programs/StructTest4", "[codegen][struct]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/adv/StructTest4.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "9ea2917093166ce5ad6ad7cbf80991f7dba2e95ae9a3dac4c472be5d9ad979b1");
}

TEST_CASE("programs/adv/NestedEnum", "[codegen][struct]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/adv/NestedEnum.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "9b61cbf31790496ddd1da29db6d7f412ac8e8890ad822ef7230bf32740899407");
}

TEST_CASE("programs/dangerLambda - lambdas with dupl function names", "[codegen][struct]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/dangerLambda.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "c1d7ec0503975ede149360b32780003757deccf84c78862ad7bbc0d54e5e2f65");
}

TEST_CASE("programs/adv/enumPassing - passing non-enum as enum argument", "[codegen][struct]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/adv/enumPassing.wpl");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "3a8deea38620a5392962e96679b5c4e6f2e7564d369fa712eb211d5af150ae97");
}

TEST_CASE("programs/Lambda2a - More nested lambdas", "[codegen][lambda]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/Lambda2a.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "eb35fcbfd512ee2a1551e2b5c6449a8567868f0386a0d3eaf6160a9aa309f300");
}

TEST_CASE("programs/adv/enumPassingInf - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/adv/enumPassingInf.wpl");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "98b014e6ea9ae1f277bcd10f6e4a326fe5dd24cc966c9985d30e78507dc83c5d");
}

TEST_CASE("programs/Lambda2b - More nested lambdas", "[codegen][struct]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/Lambda2b.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "0719e2fade9d1a1a872b187aaac045fa4d15ebe1dfc27ca1c3afd9b37290bf6e");
}

TEST_CASE("Out of order function", "[codegen][program]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/ooof.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    // lexer.removeErrorListeners();
    // lexer.addErrorListener(new TestErrorListener());
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    //   parser.addErrorListener(new TestErrorListener()); //FIXME: SHOULD WE TEST THESE HERE?

    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    REQUIRE(tree->getText() != "");

    STManager *stmgr = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());
    REQUIRE_FALSE(sv->hasErrors(ERROR));
    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());
    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "64619d22222218e680ba738a540068053b6f865e7a1624f9826593fe81123069");
}
// FIXME: TRY REDECL OF ENUM IE. SETTING IT AGAIN
TEST_CASE("programs/example", "[codegen][program]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/example.wpl");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    // lexer.removeErrorListeners();
    // lexer.addErrorListener(new TestErrorListener());
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    //   parser.addErrorListener(new TestErrorListener()); //FIXME: SHOULD WE TEST THESE HERE?

    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    REQUIRE(tree->getText() != "");

    STManager *stmgr = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stmgr, pm);

    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());
    REQUIRE_FALSE(sv->hasErrors(ERROR));
    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());
    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "468c29659808773d4cf880d99d88374e1d02640e6bc970c12215db998af32a8c");
}

/************************************
 * Example C-Level Tests
 ************************************/
// TEST_CASE("C Level Positive Test #1", "[codegen]")
// {
//     std::fstream *inStream = new std::fstream("/home/shared/programs/CLevel/CPositive1.wpl");
//     antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

//     WPLLexer lexer(input);
//     antlr4::CommonTokenStream tokens(&lexer);
//     WPLParser parser(&tokens);
//     parser.removeErrorListeners();
//     WPLParser::CompilationUnitContext *tree = NULL;
//     REQUIRE_NOTHROW(tree = parser.compilationUnit());
//     REQUIRE(tree != NULL);
//     STManager *stm = new STManager();
//     PropertyManager *pm = new PropertyManager();
//     SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
//     std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
//     REQUIRE(cuOpt.has_value());

//     REQUIRE_FALSE(sv->hasErrors(0));

//     CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "fdf9d19f4d205022b83770d7ec87c120a51d65fc5719eaad7d3a65d955aee64c");
// }

TEST_CASE("C Level Positive Test #2", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/CLevel/CPositive2.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "48cb77e5507b649f1419b5103f57370503c760eaffc0af03d8cb2fc1a09a537c");
}

/************************************
 * Example B-Level Tests
 ************************************/
TEST_CASE("B Level Positive Test #1", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/BLevel/BPositive1.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "7922bda2b9a5f69ef4e0040d7fa5eac21c9c50a93a9e6fd45cd7a1bb1aa43aea");
}

TEST_CASE("B Level Positive Test #2", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/BLevel/BPositive2.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "52024c89f56d4b8f79c1cbfc20a778f87c0ded0890dc40f9aeed25310a27a6ff");
}

/************************************
 * Example A-Level Tests
 ************************************/
TEST_CASE("A Level Positive Test #1", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/ALevel/APositive1.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "2f0c3eee9fe38237070d46f6cad1c8c11511932b4e70b5f44dd1259168101bf8");
}

TEST_CASE("A Level Positive Test #2", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/ALevel/APositive2.prism");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    WPLLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    WPLParser parser(&tokens);
    parser.removeErrorListeners();
    WPLParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());

    REQUIRE_FALSE(sv->hasErrors(0));

    CodegenVisitor *cv = new CodegenVisitor(pm, "WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());

    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "274e9b13e41b0c6202eb2cefb1401fb917e7711a9dfd796e19ea24f1868ffa69");
}
