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
    SemanticVisitor *sv = new SemanticVisitor(stm, 0);
    auto cuOpt = sv->visitCtx(tree);
    REQUIRE_FALSE(sv->hasErrors(0));
    REQUIRE(std::holds_alternative<CompilationUnitNode*>(cuOpt)); //cuOpt.has_value());

    CodegenVisitor *cv = new CodegenVisitor("WPLC.ll", 0);
    cv->visitCompilationUnit(std::get<CompilationUnitNode*>(cuOpt));//cuOpt.value());
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
    SemanticVisitor *sv = new SemanticVisitor(stm, 0);
    auto cuOpt = sv->visitCtx(tree);
    // REQUIRE(cuOpt.has_value());

    REQUIRE(sv->hasErrors(0));

    // CodegenVisitor *cv = new CodegenVisitor("WPLC.ll");
    // cv->visitCompilationUnit(cuOpt.value());

    // REQUIRE_FALSE(cv->hasErrors(0));

    // REQUIRE(llvmIrToSHA256(cv->getModule()) == "e0f894f1b6dd6613bd18eee553f5d6c8896228b4e4a21400b5dd6f1433ab0670");
}
// FIXME: REMOVE NO RUNTIME
TEST_CASE("programs/test1 - General Overview", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test1.prism"))),
        "120bfd1cdfa2ad3cf4f3c0f9a32f634ce3d5c37faea413e289d852175aa4ecbe");
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
        "6683a60131367487c7eae33159235522bef12d3536c77e20caa4878c7001ecca");
}

TEST_CASE("programs/test3 - If w/o else", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test3.prism"))),
        "d27d0d239006b6d256cd621f7f0eb6f11e597cd913bad1f920c28a28eb88290e");
}

TEST_CASE("programs/test4a - Use and redeclaration of parameters", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test4a.prism"))),
        "99f62b05638b50310f4c241bcec6b499be3dedda69437194f1a685533b433682");
}

TEST_CASE("programs/test5 - Nested ifs and if equality", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test5.prism"))),
        "ea70afc1a192517e83a3a81b97a85e2d6c6aa7e3a11da6767c1644b65366f48b");
}

TEST_CASE("programs/test6 - Basic Select with Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test6.prism"))),
        "64779e8c3d35e3d826ecd0aee79502d8acbd66c698202f6ce1b93ed146b33988");
}

TEST_CASE("programs/testSelectBlock1 - Basic Select with Blocks that Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock1.prism"))),
        "e3cf21446b4886027c0b532cc72ec107621db8fa05040fdce39a03121a81f1ac");
}

TEST_CASE("programs/testSelectBlock1-fn - Basic Select with Blocks that Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock1-fn.prism"))),
        "dba4f521bba2746c5b24468ebe6fabaa4f8545dccc2259a6e63aee71647b39e9");
}

TEST_CASE("programs/test6a (CAFE!) - Basic Nested Selects, LEQ, GEQ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test6a.prism"))),
        "d66941abbd2184e34dcad3d141a2c7588ebb27bca3c68a0c2565c0a69c1ec966");//"cafe2b3e17335a03444e7c3e1be095eaea8cb901741e8c0d8f1f79a17a8fe6c4");
}

TEST_CASE("programs/testSelectBlock2 - Select with blocks that don't return", "[codegen]")
{
    // NOTE: Should be same as test6a
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock2.prism"))),
        "1c7e513d8af2698387ebbccd0e9c855012156e7a7bbe50d0ca7b2b5cedf371c2");
}

TEST_CASE("programs/test7 - Test String equality + Nested Loops", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test7.prism"))),
        "e0e8c046f7092d511209c7f5c8af8c5b9098bf5f54001943a534312d0812b272");
}

TEST_CASE("programs/test8 - Nested Loops", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test8.prism"))),
        "eef4a5c06e7b8069fe579ea62e28550962c7d55bbf43e698d7a00694e74d6ffc");
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
        "f61ac2abc28a01f969a9acfdf8590d541715aca937855ea2b0d18c474fc2a2df");
}

TEST_CASE("programs/test12 - Scopes & Prime Finder Example! ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test12.prism"))),
        "da48612fb4ba14b53ec735d961ae6ae72d87b163da83a49e7e0fa01cb2d2e359");
}

TEST_CASE("programs/test13 - Recursive Fibonacci", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test13.prism"))),
        "60dffce621f97e64894ed90a772ae3188cbe339abcc04bfe8c8346148c53781a");
}

TEST_CASE("programs/adv/LambdaDef", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/LambdaDef.prism"))),
        "030f09035e11ea4abb5c2fbbae1addace769561434177e3950eac5f9c40bb6f8");
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
//     SemanticVisitor *sv = new SemanticVisitor(stm, 0);
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
        "145aa8b0291762f7d1c1a7c7a3ec3388267397fb9725f17cf651adb556d5b19e");
}

TEST_CASE("programs/test-shortcircuit-rt - Basic Short Circuit (and + or) w/ Runtime", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-shortcircuit-rt.prism"))),
        "6307b88aed4deb57126db95f9eeec4ea01b0e4a34e07c175dee8578d0dc9994a");
}

TEST_CASE("programs/test-arrayAssign - Assigning one array to another and editing arrays in functions", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-arrayAssign.prism"))),
        "4a7e47d638e77636c6cbb900cd5c528b826d41d28d7783870fe94d86b1819dc3");
}

TEST_CASE("programs/externProc - Declaring an external proc", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/externProc.prism"))),
        "5f28e760349c16a65e398083fc1850c72dcf7c09ae4849eff6c6c3506217175e");
}

TEST_CASE("programs/test14a - Test nested/more complex shorting", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test14a.prism"))),
        "a9cdf50496b70243db3a6a83f86a10604a5ce5ac82384db9d08dd8245897aebb");
}

TEST_CASE("programs/test18 - Parody", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test18.prism"))),
        "cc420ec4425a0b05b881b7656f12bc0ac95e8fe9c0bbc79df7260cddc751be0b");
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
//     SemanticVisitor *sv = new SemanticVisitor(stm, 0);
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
//     SemanticVisitor *sv = new SemanticVisitor(stm, 0);
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
    SemanticVisitor *sv = new SemanticVisitor(stm, 0);
    auto cuOpt = sv->visitCtx(tree);
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
        "c7e7de6baadcb15ccd50506c0437b06f0354e1ce4f78457a20947a2c77f8adc0");
}

TEST_CASE("programs/Lambda2 - Basic lambda Test w/ return", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2.prism"))),
        "abcac310481a3d4fb85b92979f0a62694534b13e7cd1630bf9390b5fef63003e");
}

TEST_CASE("programs/Lambda3 - Basic lambda Test w/ return and same name", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda3.prism"))),
        "ecbd956c2fe83c4ae1c594594b122160f1fde3c03daea80f18ba11ce7c513f14");
}

TEST_CASE("programs/externLambda", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/externLambda.prism"))),
        "ede6af214cf081c63f67b2a7f3c649c0bf06927a04693e40e49c4ae03813e1a3");
}

TEST_CASE("programs/enum1 - Basic Enum 1", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum1.prism"))),
        "2f50d070919a8a423de226316d5901d91038ff88ddceaf86dd60d42ecd6429d8");
}

TEST_CASE("programs/enum2 - Basic Enum 2", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum2.prism"))),
        "57585471e0c206d25df999471586fe66161e97c6732cca186cc72f4f2ba6108c");
}

TEST_CASE("programs/enumAssign - Same a  Enum 2 but with assignmens outside of decl", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumAssign.prism"))),
        "362aa715e10bce1099557ae4535b067701ac1e0c536c4e6c7e557224ccaab64f");
}

TEST_CASE("programs/enumAssign2 - Returning lambdas, functions, and enums", "[codegen][enum][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumAssign2.prism"))),
        "1808e7b553d8453b264e268ba8f4e85670896cac506ef18ceafd977a725b8c1e");
}

TEST_CASE("programs/enum3", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum3.prism"))),
        "8df48edafa85c53ca6890ac8fc125c6b4bd4ff88a2639a16370ee2a91c248c2b");
}

TEST_CASE("programs/adv/StructTest2", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest2.prism"))),
        "e920efb12e0b2d13fae7bae7b0c23856f9e9b79d16c566769a7c4c86be381840");
}

TEST_CASE("programs/adv/StructTest3", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3.prism"))),
        "ef93c8d196614072a6d8b312776aac538118101854d4a524049b736711ba6e7c");
}

TEST_CASE("programs/adv/StructTest3a - nested fields", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3a.prism"))),
        "d67fab9e78e520fca3f9982b750593f18d8cbfa63e18763004327a9e9feea5c3");
}

TEST_CASE("programs/adv/StructTest3b - nested fields", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3b.prism"))),
        "76dbe82e84082590f6408f7be171f6c59dbc243b5e2d26874460c2e7ca30af1c");
}

TEST_CASE("programs/adv/StructTest4", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest4.prism"))),
        "0c25e790b66e34b206e54a6253d0965d750c336db540769e7b63adcbeedc38f0");
}

TEST_CASE("programs/adv/NestedEnum", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/NestedEnum.prism"))),
        "0b5ccdaaeeb9056d802fa98f976cdf6521f00673457e522372c32e83c28ef3db");
}

TEST_CASE("programs/dangerLambda-Program - lambdas with dupl function names", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/dangerLambda-Program.prism"))),
        "d943a5276d61176a96eb928b64745cfb12c4449e4f6471b7abc8a91fc81bd37b");
}

TEST_CASE("programs/dangerLambda-Lambda - lambdas with dupl function names", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/dangerLambda-Lambda.prism"))),
        "9fb6efc04666ab8bdda949587e652d9d0936a01212a528099d1c3574ed9e4d31");
}

TEST_CASE("programs/adv/enumPassing - passing non-enum as enum argument", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassing.prism"))),
        "87a766869632aed792be6bf6c7a1ae01a629b2235a2ae5faa1bfdfc177832a80");
}

TEST_CASE("programs/adv/enumPassing-fn - passing non-enum as enum argument", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassing-fn.prism"))),
        "ee4f26ffa1af77325af282cb74328dfd5422a7a978ed043c456b9b78b4dd2a56");
}

TEST_CASE("programs/Lambda2a - More nested lambdas", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2a.prism"))),
        "609e01cf969c5f8373bf6794c28151e40d75488c3c766ac325c6bc4314fe78bb");
}

TEST_CASE("programs/adv/enumPassingInf - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassingInf.prism"))),
        "c53080c37b667f045d8ff895effd5b5f252c19fd6debe8541b3523a564071dd3");
}

TEST_CASE("programs/adv/enumPassingInf-fn - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassingInf-fn.prism"))),
        "146c04a075d6d9a1e14fc8bd2501a3f0f7048e8f15aa41dd7e19923e9bf2ce1c");
}

TEST_CASE("programs/Lambda2b - More nested lambdas", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2b.prism"))),
        "fbc24fc723ba0ee2b26ca078ccd6521c5fa759a6c5bd15111cd96cdb60953fb6");
}

TEST_CASE("Out of order function", "[codegen][program]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ooof.prism"))),
        "3ecfe748501d0747871f4d5e2f6bbefd7cca4edd32eeecc0d8ea853fd51810d3");

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
    SemanticVisitor *sv = new SemanticVisitor(stmgr);

    std::optional<CompilationUnitNode *> cuOpt = sv->visitCtx(tree);
    REQUIRE(cuOpt.has_value());
    REQUIRE_FALSE(sv->hasErrors(ERROR));
    CodegenVisitor *cv = new CodegenVisitor("WPLC.ll", 0);
    cv->visitCompilationUnit(cuOpt.value());
    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == "64619d22222218e680ba738a540068053b6f865e7a1624f9826593fe81123069");
    */
}

TEST_CASE("programs/example", "[codegen][program]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/example.prism"))),
        "cfa61fd35f853efa090e7055f8840bf29309faad1291fdd5045b3836ea478baa");
}

TEST_CASE("programs/SendChannel", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/SendChannel.prism"))),
        "54ee0e92e8a80fd25c54753a6bac6531d3df398bcc4987a2b72c6f59a10874ad");
}

TEST_CASE("paper/links", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links.prism"))),
        "77f845d8f5c873596c357d4c1a2749f8b8288cb1f5fa5ee8903e11c8e6bd8faf");
}

TEST_CASE("paper/links2", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links2.prism"))),
        "fe3d8f7a6113f5a49d3aef64e8e5d2815f7857f4e4abec2b7b10bfe7d5bd6a96");
}

TEST_CASE("paper/links3", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links3.prism"))),
        "dba91de7807c4660d7c50e578a4d8c55bcfdbe304d962e6efc0a77af7e965140");
}

TEST_CASE("paper/links4", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links4.prism"))),
        "72f09a3d1950d825fdcac670e8c5f2342049d7ee1f5810285309358a7807a16c");
}

TEST_CASE("programs/doubleArg1c2 - weakening and loops", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/doubleArg1c2.prism"))),
        "7b90710c0d62740b7f58c3bba6beb98ecae74134b29e238527ff51daba98d1d9");
}

TEST_CASE("programs/enumedit", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumedit.prism"))),
        "51458818a67f34d4c0bdb9139d53a99566904c67663b5420be363801a7efd0e8");
}

TEST_CASE("programs/TBox - Parody + Clone w/ boxes", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TBox.prism"))),
        "5863355704ff14592af7a40d80b13636b0b5f133108226526e8bd2be59ae3864");
}

TEST_CASE("programs/TStruct - Parody + Clone w/ Struct Boxes ", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStruct.prism"))),
        "10c4f0f330f0cd16b27fe81228e41ee7ed93aab2e36565c6375b1177fee094fb");
}

TEST_CASE("programs/TStructEnum - Parody + Clone w/ Enum Struct Boxes ", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructEnum.prism"))),
        "56d8817f37bcae89fbac4d73ca8bb7b39c656d440c4e9ec2bffc7d838ad6f49a");
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
//     SemanticVisitor *sv = new SemanticVisitor(stm, 0);
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
        "2a28ef1737b9831aeb098f9e999a57e94ac50061f251bd6698aa22905fe0ddc0");
}

/************************************
 * Example B-Level Tests
 ************************************/
TEST_CASE("B Level Positive Test #1", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/BLevel/BPositive1.prism"))),
        "e3b8a784accd28e1ec2d81d1c0b24da8c806f2f567c586a09514a20cc3413b00");
}

TEST_CASE("B Level Positive Test #2", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/BLevel/BPositive2.prism"))),
        "241b52fcd1f63df2f5dbdc03d6dd3d539a623051499dd9c8a05e5eb3c2511285");
}

/************************************
 * Example A-Level Tests
 ************************************/
TEST_CASE("A Level Positive Test #1", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive1.prism"))),
        "c60521beef0edfb37522e404b3ce3a830307df706bd0a7fc0d33ed840b39aca8");
}

TEST_CASE("A Level Positive Test #2", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive2.prism"))),
        "a87e3a8114373cac98b947720cdc309d1f4a422f085e1d5c1df50a4796a792f4");
}
