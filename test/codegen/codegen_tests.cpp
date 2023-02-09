/**
 * @file codegen_tests.cpp
 * @author gpollice & ahfriedman
 * @brief Basic tests for code generation
 * @version 0.1
 * @date 2023-02-04
 *
 * @copyright Copyright (c) 2023
 *
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

void EnsureCompilesTo(antlr4::ANTLRInputStream *input, string hash)
{
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

    CodegenVisitor *cv = new CodegenVisitor("WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());
    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == hash);
}

void EnsureErrors(antlr4::ANTLRInputStream *input)
{
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
    // REQUIRE(cuOpt.has_value());

    REQUIRE(sv->hasErrors(0));

    // CodegenVisitor *cv = new CodegenVisitor("WPLC.ll");
    // cv->visitCompilationUnit(cuOpt.value());

    // REQUIRE_FALSE(cv->hasErrors(0));

    // REQUIRE(llvmIrToSHA256(cv->getModule()) == "e0f894f1b6dd6613bd18eee553f5d6c8896228b4e4a21400b5dd6f1433ab0670");
}
// FIXME: REMOVE NO RUNTIME
TEST_CASE("Development Codegen Tests", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream("define program :: c : Channel<-int> = { c.send(-1) }"),
        "cecbb03bb006f8ecf4e2c26f2002f3ca4e32da8bc74314405ef37da147ad2df2");
}

TEST_CASE("programs/test1 - General Overview", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test1.prism"))),
        "61b8248a0a19ddaffe7c76567451b884bd47c6064c9193d1895f356dd84faa9b");
}

TEST_CASE("programs/test1a", "[codegen]")
{
    EnsureErrors(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test1a.prism"))));
}

TEST_CASE("programs/test2 - Scopes, multiple assignments, equality (non-arrays)", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test2.prism"))),
        "371c38f7ba67c50ac1ed90ec21808dd7287076e2ec27967982453112effe2eab");
}

TEST_CASE("programs/test3 - If w/o else", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test3.prism"))),
        "b707071f5babbaa7ef5ec3fc83789e39005823a32f7e90162df63d6399b3c68d");
}

TEST_CASE("programs/test4a - Use and redeclaration of parameters", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test4a.prism"))),
        "dcc5b894465e160455774da7e7169133a05ec7e595e72cb81a9c068fc3db0d73");
}

TEST_CASE("programs/test5 - Nested ifs and if equality", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test5.prism"))),
        "b9c39606c29424eed14e72a29f68e1b5b2dcb98e3c66af1eddec758e5843b1b6");
}

TEST_CASE("programs/test6 - Basic Select with Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test6.prism"))),
        "ca3f3f9c96ae7a947256e1f2207577069fd60bd1cd30cce39f3d0e33ba66b7b8");
}

TEST_CASE("programs/testSelectBlock1 - Basic Select with Blocks that Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock1.prism"))),
        "41e1d6adb20f26fc561d6b0d36033edab33918e16cc8fd1c4361548240758563");
}

TEST_CASE("programs/test6a (CAFE!) - Basic Nested Selects, LEQ, GEQ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test6a.prism"))),
        "cafe2b3e17335a03444e7c3e1be095eaea8cb901741e8c0d8f1f79a17a8fe6c4");
}

TEST_CASE("programs/testSelectBlock2 - Select with blocks that don't return", "[codegen]")
{
    // NOTE: Should be same as test6a
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock2.prism"))),
        "aab19eeabfaa6d2a6837e91b816f8b2b668e7597d8be5915e7eaa837b8bc6fae");
}

TEST_CASE("programs/test7 - Test String equality + Nested Loops", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test7.prism"))),
        "cad97e5c713948d5c36f848c5ac3f43eb3bf6d69ede56b6d7453e20ee57ebac9");
}

TEST_CASE("programs/test8 - Nested Loops", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test8.prism"))),
        "ad105752e5a6a363aed01d596c1b0257749b0afd3eda4d0f6e2e04deec6530ed");
}

// TEST_CASE("programs/test9i - Global Integers", "[codegen]")
// {
//     EnsureCompilesTo(
//         new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test9i.prism"))),
//         "328e5295eaad33348eee23da5f8302153e778c8bb631707f37fd4d03daae7cfa");
// }

// TEST_CASE("programs/test9iv - Global Integer Inference", "[codegen]")
// {
//     EnsureCompilesTo(
//         new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test9iv.prism"))),
//         "328e5295eaad33348eee23da5f8302153e778c8bb631707f37fd4d03daae7cfa");
// }

// TEST_CASE("programs/test9b - Global Booleans", "[codegen]")
// {
//     EnsureCompilesTo(
//         new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test9b.prism"))),
//         "d871755f7c89cd02ee76c67541ec1935a2117a1e3f23cc86a09573fa1ef8422c");
// }

// TEST_CASE("programs/test9bv - Global Boolean Inference", "[codegen]")
// {
//     EnsureCompilesTo(
//         new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test9bv.prism"))),
//         "d871755f7c89cd02ee76c67541ec1935a2117a1e3f23cc86a09573fa1ef8422c");
// }

// TEST_CASE("programs/test9s - Global Strings", "[codegen]")
// {
//     EnsureCompilesTo(
//         new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test9s.prism"))),
//         "4b20b6db3a31f068485c29786b8ca97704cff2931829462517cf402811ed711a");
// }

// TEST_CASE("programs/test9sv - Global String Inference", "[codegen]")
// {
//     EnsureCompilesTo(
//         new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test9sv.prism"))),
//         "4b20b6db3a31f068485c29786b8ca97704cff2931829462517cf402811ed711a");
// }

// TEST_CASE("programs/test9ba - Global Boolean Array", "[codegen]")
// {
//     EnsureCompilesTo(
//         new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test9ba.prism"))),
//         "b6b98b36e98caffd2ef053023bd97db39bfc12c3a2c38b90bffacb8fb1436097");
// }

// TEST_CASE("programs/test9ia - Global Integer Array", "[codegen]")
// {
//     EnsureCompilesTo(
//         new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test9ia.prism"))),
//         "0b667384676913d1b0aee9853fd9be42eabea34887e18cd1de6b54c5cf1823ca");
// }

// TEST_CASE("programs/test9sa - Global String Array - FLAWED", "[codegen]")
// {
//     EnsureCompilesTo(
//         new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test9sa.prism"))),
//         "9e5834e13db9f511e072a26b22de0bee49ae44d914fc08ecb86f9b14f1c4fdc1");
// }

// TEST_CASE("programs/test9sa-1 - Global String Array - CORRECT", "[codegen]")
// {
//     EnsureCompilesTo(
//         new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test9sa-1.prism"))),
//         "b7e94a1425ecfbc8a9b99dbc9160cb966bfcd7ae69e13bee2cf4702d310d9f0c");
// }

TEST_CASE("programs/test11 - Expressions in decl (let*) ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test11.prism"))),
        "9e1b331472a316541239a93687ac5794b3e1639454edcef5346da26ab774d694");
}

TEST_CASE("programs/test12 - Scopes & Prime Finder Example! ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test12.wpl"))),
        "209c1960ddf81cfa4490c2d8a0501577b799bdacc5d829ce2530f094559ed915");
}

TEST_CASE("programs/test13 - Recursive Fibonacci", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test13.prism"))),
        "5810f4c05288eb8c89bb4e1d6c76fa9b427281d14c395dc7d10bfe742d0c1861");
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

//     CodegenVisitor *cv = new CodegenVisitor("WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "6c84e861ca345b6cf3b11cf5abe99daed731acac1e48a302ac8efe6640cad7b6");
// }

TEST_CASE("programs/test-shortcircuit - Basic Short Circuit (and)", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-shortcircuit.prism"))),
        "7c2396be13623687194b4199b8fa3abadafddb89b1a4e36240455010c7914d1f");
}

TEST_CASE("programs/test-shortcircuit-rt - Basic Short Circuit (and + or) w/ Runtime", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-shortcircuit-rt.prism"))),
        "f631a86416e667b8e9050f1673869d54ff07490ca3ed8bf592020861bc0eb7aa");
}

TEST_CASE("programs/test-arrayAssign - Assigning one array to another and editing arrays in functions", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-arrayAssign.prism"))),
        "431a809c5045616658b07247385cad348f27abce4e209c25cc2bdbd893e80a00");
}

TEST_CASE("programs/externProc - Declaring an external proc", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/externProc.prism"))),
        "d2bd88d75c3fcb9a3a4d2c449ced75bca5a9e0abb8475449b6c7b4e7d14cd208");
}

TEST_CASE("programs/test14a - Test nested/more complex shorting", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test14a.prism"))),
        "18befe8b4fb8d570eafe45e73d2437c499accadd56aa8bc9a653abd90cb6ebce");
}

TEST_CASE("programs/test18 - Parody", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test18.prism"))),
        "5b81e72524788ad415f3be54356a81cba2d97249b0e67a3f98ca06fdb0c5609d");
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

//     CodegenVisitor *cv = new CodegenVisitor("WPLC.ll", 0);
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

//     CodegenVisitor *cv = new CodegenVisitor("WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "f9b33450b1f1522122b1dffbf07819f959e08aac6ccdfc112cac7c25690a5c78");
// }

TEST_CASE("programs/forwardWrongArg - Forward Declaration w/ wrong arg name", "[codegen]")
{
    EnsureErrors(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/forwardWrongArg.prism"))));
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
    // REQUIRE(cuOpt.has_value()); //FIXME: DO BETTER

    REQUIRE(sv->hasErrors(0));

    // CodegenVisitor *cv = new CodegenVisitor("WPLC.ll", 0);
    // cv->visitCompilationUnit(cuOpt.value());

    // REQUIRE(cv->hasErrors(0));
}

TEST_CASE("programs/Lambda1 - Basic lambda Test", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda1.prism"))),
        "7f85ab3efb00ae5989d8993b35f32b6ba719a3167210e5dbb7ed438ba5135524");
}

TEST_CASE("programs/Lambda2 - Basic lambda Test w/ return", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2.prism"))),
        "fc18974a336ba7f64c2b1f4ad7087c558ea8be6a242ce29613f2b3039b09c331");
}

TEST_CASE("programs/Lambda3 - Basic lambda Test w/ return and same name", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda3.prism"))),
        "779b9d305874f74e23f2b26bb232e087786227f6cf36ebe40bf2166b6bedfc65");
}

TEST_CASE("programs/externLambda", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/externLambda.prism"))),
        "b5235ff4d234116c2b168d6a11f2930bdfa53b07ab36e7af895ef52cba31913a");
}

TEST_CASE("programs/enum1 - Basic Enum 1", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum1.prism"))),
        "2613567a29a7f41d945623f61c09ab5da66dc87dcc58046474fcf210004dd966");
}

TEST_CASE("programs/enum2 - Basic Enum 2", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum2.prism"))),
        "81bf96b4ed3ebfba61974be24713eb5db1490ffa2f7b3f0d173fa2cd591fe6fd");
}

TEST_CASE("programs/enumAssign - Same a  Enum 2 but with assignmens outside of decl", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumAssign.prism"))),
        "d28141fda4ffe2943a80619005d1b53a485b8edeb1b0a6a9d7b5e6efb6d9186d");
}

TEST_CASE("programs/enumAssign2 - Returning lambdas, functions, and enums", "[codegen][enum][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumAssign2.prism"))),
        "638573525dadddca5f5e924e4cafc22b1a16e6228aa39fce3a701db7e72abe87");
}

TEST_CASE("programs/enum3", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum3.prism"))),
        "1cfe785dbe04efbe834cf809d64497a8da6b54f1851d41d0196eb6e03b3419b3");
}

TEST_CASE("programs/StructTest2", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest2.prism"))),
        "b3612acb210334589484f41abc797d56de37ccdee1fefe53171cdd383aa77922");
}

TEST_CASE("programs/StructTest3", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3.prism"))),
        "c777b29fd45774d88167d589bf36fa35903de8c0a93cf916e6177d0d6da9bd08");
}

TEST_CASE("programs/StructTest3a - nested fields", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3a.prism"))),
        "64ed6c921cd41e9b378526db9423f1c69f2f16817bdb2fb2d9a9e20fd362bdc0");
}

TEST_CASE("programs/StructTest3b - nested fields", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3b.prism"))),
        "07052a2346e10c458cfb5668eccd7e3434911acdeb96bf7dff1366e808a4128d");
}

TEST_CASE("programs/StructTest4", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest4.prism"))),
        "67d5742125f26bd61e747d6bdb91dfa50db755b606b8c4c0cd562c373fd47353");
}

TEST_CASE("programs/adv/NestedEnum", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/NestedEnum.prism"))),
        "9b61cbf31790496ddd1da29db6d7f412ac8e8890ad822ef7230bf32740899407");
}

TEST_CASE("programs/dangerLambda - lambdas with dupl function names", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/dangerLambda.prism"))),
        "c1d7ec0503975ede149360b32780003757deccf84c78862ad7bbc0d54e5e2f65");
}

TEST_CASE("programs/adv/enumPassing - passing non-enum as enum argument", "[codegen][struct]")
{
    // FIXME: VERIFY STRUCT AND ENUM PASSING ARE DONE BY VALUE!!
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassing.prism"))),
        "4e42b4481de60407ae1ba52911afb2a9b49aba1247389e107ca3dc6c43576046");
}

TEST_CASE("programs/adv/enumPassing-fn - passing non-enum as enum argument", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassing-fn.prism"))),
        "1fdd1ac15549cecce7dc247d91edfad679437bb4a5264e1f56461a2463e57b4b");
}

TEST_CASE("programs/Lambda2a - More nested lambdas", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2a.prism"))),
        "eb35fcbfd512ee2a1551e2b5c6449a8567868f0386a0d3eaf6160a9aa309f300");
}

TEST_CASE("programs/adv/enumPassingInf - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassingInf.prism"))),
        "0a0b25e17c9e12c5aef8c961fb332bb37fccf5e86975c3afeb54e7c02f206d0d");
}

TEST_CASE("programs/adv/enumPassingInf-fn - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassingInf-fn.prism"))),
        "a95e82e0ad100fbaa5d1eec188d76e87b2a06b3a774a2ea7f992882eafdc57fb");
}

TEST_CASE("programs/Lambda2b - More nested lambdas", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2b.prism"))),
        "0719e2fade9d1a1a872b187aaac045fa4d15ebe1dfc27ca1c3afd9b37290bf6e");
}

TEST_CASE("Out of order function", "[codegen][program]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ooof.prism"))),
        "64619d22222218e680ba738a540068053b6f865e7a1624f9826593fe81123069");

/*
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
    CodegenVisitor *cv = new CodegenVisitor("WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());
    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "64619d22222218e680ba738a540068053b6f865e7a1624f9826593fe81123069");
    */
}
// FIXME: TRY REDECL OF ENUM IE. SETTING IT AGAIN
TEST_CASE("programs/example", "[codegen][program]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/example.prism"))),
        "4da1572fa31897b387f893bf97d82072d27873f1aa53358e22107f723cc15370");
}

TEST_CASE("programs/SendChannel", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/SendChannel.prism"))),
        "c0400b0725a19a1b62ee5e985c3c10b036c6b497e704d106cafa9568a309c22a");
}

TEST_CASE("paper/links", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links.prism"))),
        "af194957130ef848cb9cc0ba716021a597e877edda6c431aff7397661308c580");
}

TEST_CASE("programs/doubleArg1c2 - weakening and loops", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/doubleArg1c2.prism"))),
        "87798310e70dae9e24b38ca08c61e4f84aa8ae1501394597f1d032f4af39e1fb");
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

//     CodegenVisitor *cv = new CodegenVisitor("WPLC.ll", 0);
//     cv->visitCompilationUnit(cuOpt.value());

//     REQUIRE_FALSE(cv->hasErrors(0));

//     REQUIRE(llvmIrToSHA256(cv->getModule()) == "fdf9d19f4d205022b83770d7ec87c120a51d65fc5719eaad7d3a65d955aee64c");
// }

TEST_CASE("C Level Positive Test #2", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/CLevel/CPositive2.prism"))),
        "48cb77e5507b649f1419b5103f57370503c760eaffc0af03d8cb2fc1a09a537c");
}

/************************************
 * Example B-Level Tests
 ************************************/
TEST_CASE("B Level Positive Test #1", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/BLevel/BPositive1.prism"))),
        "7922bda2b9a5f69ef4e0040d7fa5eac21c9c50a93a9e6fd45cd7a1bb1aa43aea");
}

TEST_CASE("B Level Positive Test #2", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/BLevel/BPositive2.prism"))),
        "52024c89f56d4b8f79c1cbfc20a778f87c0ded0890dc40f9aeed25310a27a6ff");
}

/************************************
 * Example A-Level Tests
 ************************************/
TEST_CASE("A Level Positive Test #1", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive1.prism"))),
        "2f0c3eee9fe38237070d46f6cad1c8c11511932b4e70b5f44dd1259168101bf8");
}

TEST_CASE("A Level Positive Test #2", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive2.prism"))),
        "274e9b13e41b0c6202eb2cefb1401fb917e7711a9dfd796e19ea24f1868ffa69");
}

