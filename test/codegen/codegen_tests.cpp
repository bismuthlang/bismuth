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
    auto cuOpt = sv->visitCtx(tree);
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
    PropertyManager *pm = new PropertyManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, pm, 0);
    auto cuOpt = sv->visitCtx(tree);
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
        "f530104e0f03b92c698dc1158eb23b098450f0181a5329d91765ce017aa99a78");
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
        "0b5259d83691e49b3da07715ef71ebdbcf81eac33d8706aaaba751092ad21c85");
}

TEST_CASE("programs/test3 - If w/o else", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test3.prism"))),
        "27ab1608ab4af17a721e3a04699ac6ad2150d92b9af3e6d01e52c08a48c23ba3");
}

TEST_CASE("programs/test4a - Use and redeclaration of parameters", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test4a.prism"))),
        "cd2b9732384afe1df97b862176d366235a181821deec5b809026fc54a7846829");
}

TEST_CASE("programs/test5 - Nested ifs and if equality", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test5.prism"))),
        "0c4cdf9328c0789654fa19b29b710435a50a96a8c04053c80a6bf88c06197924");
}

TEST_CASE("programs/test6 - Basic Select with Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test6.prism"))),
        "9c4afefdf832d2a68b1b17843ee6be428f10f2efa1bfb5726df965b206ae2618");
}

TEST_CASE("programs/testSelectBlock1 - Basic Select with Blocks that Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock1.prism"))),
        "644905252adfe086ffa91cd2f8f17906dd6cb661a68d84c8e32eef9f90b1dc9a");
}

TEST_CASE("programs/testSelectBlock1-fn - Basic Select with Blocks that Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock1-fn.prism"))),
        "5a74faba1bd8ab0e8d9c413ab1cbe235efb5b4dad20ffdb37dbd65fe3a4ecfcc");
}

TEST_CASE("programs/test6a (CAFE!) - Basic Nested Selects, LEQ, GEQ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test6a.prism"))),
        "674b89dddfd237255658b0ccd5a1f06100b03c37f7672ce85c1ab9ed3a1bfb03");//"cafe2b3e17335a03444e7c3e1be095eaea8cb901741e8c0d8f1f79a17a8fe6c4");
}

TEST_CASE("programs/testSelectBlock2 - Select with blocks that don't return", "[codegen]")
{
    // NOTE: Should be same as test6a
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock2.prism"))),
        "5735a8684b33ae3524c5c74297884590bbdda0ab17cf381dc253756bf8a185c2");
}

TEST_CASE("programs/test7 - Test String equality + Nested Loops", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test7.prism"))),
        "bb83fd6aacd38262f6430f3f8e1936ec074ac4b786986af1cb6744b1d342e10b");
}

TEST_CASE("programs/test8 - Nested Loops", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test8.prism"))),
        "771ee31ff9fb8bad479d2017b510383e894c552949eef5e7b2edb45016c757a0");
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
        "9631c5e2bf46a19bf325101a7a8936e7916fa4e71664c6203c0d93b2954f7d5b");
}

TEST_CASE("programs/test12 - Scopes & Prime Finder Example! ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test12.prism"))),
        "cfe326056e3288f290c716d67dfbe1584bf15a7195ae779582cf500342600fd2");
}

TEST_CASE("programs/test13 - Recursive Fibonacci", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test13.prism"))),
        "59a00ace1ee4b262c599f4f3371692ead9bed2d94f8149e70cc0de8a5a602e77");
}

TEST_CASE("programs/LambdaDef", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/LambdaDef.prism"))),
        "c4d8a894800f401d280872711cdba7d74efb331b7135a62416bdf80a23c7a39e");
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
        "3d277bd91c84456e99253a7c0ce6362b06115c149d1e3708e8e2bd735506a751");
}

TEST_CASE("programs/test-shortcircuit-rt - Basic Short Circuit (and + or) w/ Runtime", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-shortcircuit-rt.prism"))),
        "718d9fefdcad4fb4fcafe8858b6cb9eee0b496f13ff9988a4975839cdce1787b");
}

TEST_CASE("programs/test-arrayAssign - Assigning one array to another and editing arrays in functions", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-arrayAssign.prism"))),
        "2d08305bb5ab66613f01658f3c84a1baa815a76394ab7dcedeb05bd46b80a5fe");
}

TEST_CASE("programs/externProc - Declaring an external proc", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/externProc.prism"))),
        "2ec3a7a53ea5eda937a58b3b0f8285c17798b9f9788cf8dc6aab73fb83305cf2");
}

TEST_CASE("programs/test14a - Test nested/more complex shorting", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test14a.prism"))),
        "7aa1cefa82309d80085d8625bf762f4a4395687bd2a209978e51e67ef2416900");
}

TEST_CASE("programs/test18 - Parody", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test18.prism"))),
        "d191be8650f86694b21bb26c6d10b23408fc6cdc52a51375587b7652aeae1c88");
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
        "6824578f20994fa224a8388b0d06b7b5d4ce7068b0acb31a87cb85b10b763f01");
}

TEST_CASE("programs/Lambda2 - Basic lambda Test w/ return", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2.prism"))),
        "6245ed2cb9691aeb2b6e6ad5dde5b802b99ec782a7ea30d4892b3500a4892e54");
}

TEST_CASE("programs/Lambda3 - Basic lambda Test w/ return and same name", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda3.prism"))),
        "a7f1a7edced935d59784e1f94dc3e0164f22801df88f990dd4a0b019ce6ad1b5");
}

TEST_CASE("programs/externLambda", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/externLambda.prism"))),
        "ad29e8be60ab72fe9733a5a21e6b890d28b378f68e4afc257b6cf14804abc4ea");
}

TEST_CASE("programs/enum1 - Basic Enum 1", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum1.prism"))),
        "ccfe43082382782aa6882c1117507b140d2bca92d95552625449c36ab0dd6efa");
}

TEST_CASE("programs/enum2 - Basic Enum 2", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum2.prism"))),
        "1629ab26d49e6ab30e266062de6363bedcb6f4b739dd61ebd7910ce2896366a7");
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

TEST_CASE("programs/adv/StructTest2", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest2.prism"))),
        "7a28397a995dfdf6d71dbb8b2ba4f2f69501affacaacbc87d13f327300cbab22");
}

TEST_CASE("programs/adv/StructTest3", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3.prism"))),
        "c7ae5ac119a2695ec9cceb73805ea14bc73b7842c7d13f93921589ae16914e24");
}

TEST_CASE("programs/adv/StructTest3a - nested fields", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3a.prism"))),
        "1fbb5dd4aa0770bd2b87f928dd2e5ecdcab5ea40bb95b29bc21d21b63f60e51d");
}

TEST_CASE("programs/adv/StructTest3b - nested fields", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3b.prism"))),
        "47624462e8d1ba6285d888f31660eaec8627f4c433eaf1b87f12e01635abd670");
}

TEST_CASE("programs/adv/StructTest4", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest4.prism"))),
        "306f7348d79ba9fdf3d39956ee6ee51841dddbdabadb717b53fdbd8218cdbea6");
}

TEST_CASE("programs/adv/NestedEnum", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/NestedEnum.prism"))),
        "9b61cbf31790496ddd1da29db6d7f412ac8e8890ad822ef7230bf32740899407");
}

TEST_CASE("programs/dangerLambda-Program - lambdas with dupl function names", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/dangerLambda-Program.prism"))),
        "001fca9d3b16e3585533651bf7ecfea291c82ca75b8944f1f7f3632f9c0ce8b4");
}

TEST_CASE("programs/dangerLambda-Lambda - lambdas with dupl function names", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/dangerLambda-Lambda.prism"))),
        "061bdac7cfee0e6d3020753a1589bd2d2fe3e2675ab3163693f43fea4e6e2a6e");
}

TEST_CASE("programs/adv/enumPassing - passing non-enum as enum argument", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassing.prism"))),
        "62a55efa86670bf703a2b3b631324913e9889ab14c1093253339c39d542be692");
}

TEST_CASE("programs/adv/enumPassing-fn - passing non-enum as enum argument", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassing-fn.prism"))),
        "a292c164f0df04f937666448ee2f9656acc7a5ce88613f8a83e3867124d8cc6c");
}

TEST_CASE("programs/Lambda2a - More nested lambdas", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2a.prism"))),
        "60a5d0ae9d9b3ca1685dc832cbb6af29f866ec7636e362d6f2c7c589ae28a6cf");
}

TEST_CASE("programs/adv/enumPassingInf - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassingInf.prism"))),
        "d52b07b7f7cd541e940ff40bce8c3555b736a81edab9bec7e06bd2ce8aebb2ce");
}

TEST_CASE("programs/adv/enumPassingInf-fn - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassingInf-fn.prism"))),
        "2815f6d330fcb0beb1e26d697b0a6ff974709b97e181cabfa3abea7255668e59");
}

TEST_CASE("programs/Lambda2b - More nested lambdas", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2b.prism"))),
        "3aaa9e6b9b46f5507bdb0141e8636a3a933bc1115f035ba8c8c925d4ff9f7c67");
}

TEST_CASE("Out of order function", "[codegen][program]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ooof.prism"))),
        "924fa174aa7af0a4bd6d50f1bb714b7bda880e659af7fb48aef8b4bd71d2ae23");

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

TEST_CASE("programs/example", "[codegen][program]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/example.prism"))),
        "5f1d293aa27d53a8529682cb7897aa09362cd21386ed5286ba0d6ddb3d70fd58");
}

TEST_CASE("programs/SendChannel", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/SendChannel.prism"))),
        "81b67092a7809c55c5f7cd722500f218d0f2aabac404ce387144fb7bd5213980");
}

TEST_CASE("paper/links", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links.prism"))),
        "4b3bbaaa90ae72843a5c9dbb83060f87f8b706c71ad3f5a96b4243cf781dabba");
}

TEST_CASE("paper/links2", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links2.prism"))),
        "ff1f300a0bea0f2b2b3f0fdf912e39ceaec535574ff6e997be2e9bd09355e044");
}

TEST_CASE("paper/links3", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links3.prism"))),
        "0d410f51540bd4bb5d454a2e1722f12c6bedb68bae01f4cd4430b9468ebae33c");
}

TEST_CASE("paper/links4", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links4.prism"))),
        "aeef8dbc5af048a0fa0c2ce89823fc0f20d580e5a39e05daa8b7dcf0cb108050");
}

TEST_CASE("programs/doubleArg1c2 - weakening and loops", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/doubleArg1c2.prism"))),
        "934363ce86c090a7e6eecebee73f905e9c6932b8c0304844833bf6527fd0e17c");
}

TEST_CASE("programs/enumedit", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumedit.prism"))),
        "1f8c6c11009233f442b2f7fcb7b32624451021f632d057b6c3a0772446b676dc");
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
        "6658736efcf313c287ba9d024e7c3bf601847cedf376ede555a24a16e112c044");
}

/************************************
 * Example B-Level Tests
 ************************************/
TEST_CASE("B Level Positive Test #1", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/BLevel/BPositive1.prism"))),
        "77759d4ad763b26d7629bddef9915d89cbc0ebf298c1c52f88be9ca162095f9c");
}

TEST_CASE("B Level Positive Test #2", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/BLevel/BPositive2.prism"))),
        "0513e3e9542f0aee31d77928179692bbb40e1ea2beaf6565c305762a95f4dad7");
}

/************************************
 * Example A-Level Tests
 ************************************/
TEST_CASE("A Level Positive Test #1", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive1.prism"))),
        "5054c569847ebfb9f8ee5595509b250a6da6c5d666482c34baddaac500043209");
}

TEST_CASE("A Level Positive Test #2", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive2.prism"))),
        "274e9b13e41b0c6202eb2cefb1401fb917e7711a9dfd796e19ea24f1868ffa69");
}

