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
#include "BismuthLexer.h"
#include "BismuthParser.h"
#include "BismuthErrorHandler.h"
#include "SemanticVisitor.h"
#include "CodegenVisitor.h"
#include "HashUtils.h"
#include "CompilerFlags.h"

void EnsureCompilesTo(antlr4::ANTLRInputStream *input, string hash)
{
    BismuthLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    BismuthParser parser(&tokens);
    parser.removeErrorListeners();
    BismuthParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, 0);
    auto cuOpt = sv->visitCtx(tree);
    REQUIRE_FALSE(sv->hasErrors(0));
    REQUIRE(std::holds_alternative<CompilationUnitNode*>(cuOpt)); //cuOpt.has_value());

    CodegenVisitor *cv = new CodegenVisitor("BismuthProgram", 0);
    cv->visitCompilationUnit(std::get<CompilationUnitNode*>(cuOpt));//cuOpt.value());
    REQUIRE_FALSE(cv->hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv->getModule()) == hash);
}

void EnsureErrors(antlr4::ANTLRInputStream *input)
{
    BismuthLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    BismuthParser parser(&tokens);
    parser.removeErrorListeners();
    BismuthParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, 0);
    auto cuOpt = sv->visitCtx(tree);

    REQUIRE(sv->hasErrors(0));
}
// FIXME: REMOVE NO RUNTIME
TEST_CASE("programs/test1 - General Overview", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test1.bismuth"))),
        "e924aba0c9dc1aec315058b1cc5d9cbb1ec6f4690281d1295a55a1fb0413cc7d");
}

TEST_CASE("programs/test1a", "[codegen]")
{
    EnsureErrors(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test1a.bismuth"))));
}

TEST_CASE("programs/test2 - Scopes, multiple assignments, equality (non-arrays)", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test2.bismuth"))),
        "d960ec3adaf7e3db41b7af853208c3bc794c3143658ab959bf2d4c62746db9b0");
}

TEST_CASE("programs/test3 - If w/o else", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test3.bismuth"))),
        "4c9b159d3f7157d535dd2c93da7d2d1aa93f1413888c382a889bcb5515ad4aca");
}

TEST_CASE("programs/test4a - Use and redeclaration of parameters", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test4a.bismuth"))),
        "c035a02790b32548d08cecd14ab26943085a733bf5d9bd7236d77b69a999fc0a");
}

TEST_CASE("programs/test5 - Nested ifs and if equality", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test5.bismuth"))),
        "69f48883f0bb3f09285e00ab330bdd9e203019c1cbe7bd2f3e163dd66715f0ec");
}

TEST_CASE("programs/test6 - Basic Select with Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test6.bismuth"))),
        "b3aa939b881a8c46b6b10e646e1fb7ee85dd4cd1b2fd3ff5dad07bfaa6b6baa4");
}

TEST_CASE("programs/testSelectBlock1 - Basic Select with Blocks that Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock1.bismuth"))),
        "b9d5d3ce4b52b1ac0981b2414b97621e090f1e6c442ce91420003f6deb21833b");
}

TEST_CASE("programs/testSelectBlock1-fn - Basic Select with Blocks that Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock1-fn.bismuth"))),
        "d092ab0d012ffb3cacb7838d13cc446e65d6c341bc2acca15eff743f9cc7c7fb");
}

TEST_CASE("programs/test6a (CAFE!) - Basic Nested Selects, LEQ, GEQ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test6a.bismuth"))),
        "da043d54ee98593b9ba89dde35bda6ab8fbd8a5b0e01d773fcb1fd456bde32cb");//"cafe2b3e17335a03444e7c3e1be095eaea8cb901741e8c0d8f1f79a17a8fe6c4");
}

TEST_CASE("programs/testSelectBlock2 - Select with blocks that don't return", "[codegen]")
{
    // NOTE: Should be same as test6a
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock2.bismuth"))),
        "8c63b79f3ef7bda116711af51992e9cbe1a579b7a6ca5732f9b86e4d0c3601a1");
}

TEST_CASE("programs/test7 - Test String equality + Nested Loops", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test7.bismuth"))),
        "00079ce6f50b837d383f1ea96807142a65ece9b0dffe747e8c81419b13e944bd");
}

TEST_CASE("programs/test8 - Nested Loops", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test8.bismuth"))),
        "3c1e166ca647c9c1311088cd0f931689e36ae351f0f15298b63f53018bbf6f38");
}

TEST_CASE("programs/test11 - Expressions in decl (let*) ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test11.bismuth"))),
        "d5dc54d24e1bb556df93cbc6e0d060da4c6af21ebcf6a4169273ebf1af65da50");
}

TEST_CASE("programs/test12 - Scopes & Prime Finder Example! ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test12.bismuth"))),
        "64a93c0bfa70e443ec19004017d43d083402d27f43c52f74e7119fd27ab9fe7e");
}

TEST_CASE("programs/test13 - Recursive Fibonacci", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test13.bismuth"))),
        "3ea49235a9149b4fd2be493d25344810d5b43a741921d1195dc223cdbebafd69");
}

TEST_CASE("programs/adv/LambdaDef", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/LambdaDef.bismuth"))),
        "cdde3db3c5cbfd66c15cca74c06451458547ef82cdd3246492b845be25391ea0");
}

TEST_CASE("programs/test-shortcircuit - Basic Short Circuit (and)", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-shortcircuit.bismuth"))),
        "d3a11c1824ca7f5a4edb5b41b9897c70b3e489b1439f14b93a7726e135ee97ac");
}

TEST_CASE("programs/test-shortcircuit-rt - Basic Short Circuit (and + or) w/ Runtime", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-shortcircuit-rt.bismuth"))),
        "b8dc56fa5b1811eeeb81a1909aca8753d474561d106be03a950715d461bf51e1");
}

TEST_CASE("programs/test-arrayAssign - Assigning one array to another and editing arrays in functions", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-arrayAssign.bismuth"))),
        "b5e681a9802a301b11cc2b033ec9774fef8762c9203f95aeffeb5dc176afdad6");
}

TEST_CASE("programs/externProc - Declaring an external proc", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/externProc.bismuth"))),
        "544ab1ac6c968c7c98f8487c687b737dbd56bf1929da47ccfcff31bf5394feb2");
}

TEST_CASE("programs/test14a - Test nested/more complex shorting", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test14a.bismuth"))),
        "7b82d83c0fefb224d3a97f1971835f186232671e1d40331d40febfba0d34de41");
}

TEST_CASE("programs/test18 - Parody", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test18.bismuth"))),
        "c0119e03e335bdb87d7360333ec7da01ab55890802c8820033066bec88788fa5");
}

TEST_CASE("programs/forwardWrongArg - Forward Declaration w/ wrong arg name", "[codegen]")
{
    EnsureErrors(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/forwardWrongArg.bismuth"))));
}

TEST_CASE("programs/forwardWrongArg2 - Function syntax on process", "[codegen]")
{
    std::fstream *inStream = new std::fstream("/home/shared/programs/forwardWrongArg2.bismuth");
    antlr4::ANTLRInputStream *input = new antlr4::ANTLRInputStream(*inStream);

    BismuthLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    BismuthParser parser(&tokens);
    parser.removeErrorListeners();
    BismuthParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager *stm = new STManager();
    SemanticVisitor *sv = new SemanticVisitor(stm, 0);
    auto cuOpt = sv->visitCtx(tree);

    REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/Lambda1 - Basic lambda Test", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda1.bismuth"))),
        "a48f54af9e20ecdfa58f1bc7008979db6aec6878609fa714f549365d780ce7b9");
}

TEST_CASE("programs/Lambda2 - Basic lambda Test w/ return", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2.bismuth"))),
        "bb17743f7fd8af8ec38a0d18e24c1eac156d657a83492031ea4cb21ea1385949");
}

TEST_CASE("programs/Lambda3 - Basic lambda Test w/ return and same name", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda3.bismuth"))),
        "4477627f4d231f38194ace91b9baf910ab2b62ce5dbbc65c5562829786b0445e");
}

TEST_CASE("programs/externLambda", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/externLambda.bismuth"))),
        "65d7f5ce2cde89cadb49ad7e0b95b058a85a27c10b9342a1e78630468603903c");
}

TEST_CASE("programs/enum1 - Basic Enum 1", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum1.bismuth"))),
        "763c8100ff0905d08d6aed303eb9ae254c974407768dc9fbaef7c9da7ca8e92a");
}

TEST_CASE("programs/enum2 - Basic Enum 2 - double cast", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum2.bismuth"))),
        "810b35f512aedb2fc1fd62943c40540e416653f5d395b1f0f4f17dffa6cd09d7");
}

TEST_CASE("programs/enumAssign - Same a  Enum 2 but with assignments outside of decl", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumAssign.bismuth"))),
        "e6c8801905838695d1bda3c7e050122f40a2a041a4232e3a1c80787fb7ba138d");
}

TEST_CASE("programs/enumAssign2 - Returning lambdas, functions, and enums", "[codegen][enum][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumAssign2.bismuth"))),
        "3a12ee45c9f8bd91bfe887ebce266376eadf3381830c8cb5cf5891e9ced6d8aa");
}

TEST_CASE("programs/enum3", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum3.bismuth"))),
        "a741dba5c9292682a3a7201f6dccbe6bcd12e45fdd08d2a10b05da169142da78");
}

TEST_CASE("programs/adv/StructTest2", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest2.bismuth"))),
        "4db0f2286d0312eb6cf29fcd551ee03e444547064ebe9396300a389c4d0dbcc6");
}

TEST_CASE("programs/adv/StructTest3", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3.bismuth"))),
        "99d15b5a4bff1917b4d4f70d540025e6852eeb64d38921cffe43caec07a57701");
}

TEST_CASE("programs/adv/StructTest3a - nested fields", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3a.bismuth"))),
        "556d6db48e032142d647634ef271662f3412498f1ae42dc9d71efeb8d9d46e12");
}

TEST_CASE("programs/adv/StructTest3b - nested fields", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3b.bismuth"))),
        "3c929637635039cc2c8bb69f1c45680fbbe612a211c312159372c061bec6b00d");
}

TEST_CASE("programs/adv/StructTest4", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest4.bismuth"))),
        "ccfbf57063a59d18f1e8e4195f5219837b729dbf203b9f1bb755bca712f37050");
}

TEST_CASE("programs/adv/NestedEnum", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/NestedEnum.bismuth"))),
        "cb34bf2298c8274805ee9d181510acbddb6b4aa32ed8ed3170214b0d35fd43d2");
}

TEST_CASE("programs/dangerLambda-Program - lambdas with duplicate function names", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/dangerLambda-Program.bismuth"))),
        "7882b98e906b7940d8287897d6da0c8628ff3228120d368d95bd02b333ba5c9d");
}

TEST_CASE("programs/dangerLambda-Lambda - lambdas with duplicate function names", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/dangerLambda-Lambda.bismuth"))),
        "b74417c2d8cc515d3ace17995a291c3dda18725821217cb226a90465d991b4f4");
}

TEST_CASE("programs/adv/enumPassing - passing non-enum as enum argument", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassing.bismuth"))),
        "a614d4b87f14e71df9b1feade1ea3d12f8d27b6e14fe4db9ce1c57fea9471f76");
}

TEST_CASE("programs/adv/enumPassing-fn - passing non-enum as enum argument", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassing-fn.bismuth"))),
        "380d9ca5f50617934a81082258e603ccbf0a788bf8b7f84df9f6631442bbd516");
}

TEST_CASE("programs/Lambda2a - More nested lambdas", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2a.bismuth"))),
        "8b5f5279022525c732b694bd7d37d7323e2e34713adc2354e4b3652e78f449a4");
}

TEST_CASE("programs/adv/enumPassingInf - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassingInf.bismuth"))),
        "8dc7252035284ad9216742f6e150cc376b4a0fa630e1f085c47f41d4f180b9a7");
}

TEST_CASE("programs/adv/enumPassingInf-fn - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassingInf-fn.bismuth"))),
        "a13b983d7bbed83e2ada8a1bc9d0bd1a646631b9928c9b77fbef3444d344f056");
}

TEST_CASE("programs/Lambda2b - More nested lambdas", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2b.bismuth"))),
        "19e8480116cdfc653e5e10cd2c78290daf48985ab505d63de50b895776ccde88");
}

TEST_CASE("Out of order function", "[codegen][program]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ooof.bismuth"))),
        "3d0f86623f4d1bf6e857becf47475e106aaa73ee27e8105a61817518f2961f48");
}

TEST_CASE("programs/example", "[codegen][program]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/example.bismuth"))),
        "567e9b12de1834da95185e5533c517c09148c74fb0d3f1b7c79a99c6952b9e41");
}

TEST_CASE("programs/SendChannel", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/SendChannel.bismuth"))),
        "dde4461b8f52e8299d8bea102ecd4a63c8e7412c56d74db874a3aafa1afb6e44");
}

TEST_CASE("paper/links", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links.bismuth"))),
        "bc05f2f1d3d3d41398b2e137b9a5ab0608300cbcd049dff5eeb08e7f7f745c0b");
}

TEST_CASE("paper/links2", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links2.bismuth"))),
        "e349dcd0fe96fffac88721bd4a2b329c89247d184ac340be1bf317dc2e778277");
}

TEST_CASE("paper/links3", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links3.bismuth"))),
        "59191f536676f5ee77103b6fef255e053bcdd829c76b8ed81e47b1c65cbb4138");
}

TEST_CASE("paper/links4", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links4.bismuth"))),
        "a975cb1e7c092bee6c985101fc71a58a802bc9b08da3ca6379a42bf94eaf9bdd");
}

TEST_CASE("programs/doubleArg1c2 - weakening and loops", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/doubleArg1c2.bismuth"))),
        "f0442fe747fff7ab10d187b72d21950c809a1c39dfebb97bed0d80f242bdb9fe");
}

TEST_CASE("programs/enumedit", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumedit.bismuth"))),
        "167f5e90ed8ec3142cd664c555ebb253c37d2acc39a7e0b43f346cbc9b1ac6a3");
}

TEST_CASE("programs/TBox - Parody + Clone w/ boxes", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TBox.bismuth"))),
        "2966ba092c30e85bfeed8ed3df1464aae4cb3255e8a6cf51668f4bc9e8256974");
}

TEST_CASE("programs/TStruct - Parody + Clone w/ Struct Boxes ", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStruct.bismuth"))),
        "5be010fecfba6d6a45e2258e2983affa5a13026d897d253d6e45f286028dcb34");
}

TEST_CASE("programs/TStructEnum - Parody + Clone w/ Enum Struct Boxes ", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructEnum.bismuth"))),
        "020b5f800e25cf725e95be0b98fe07f110ff04e5553b062860e71bebec96d1f0");
}

TEST_CASE("programs/loop - Basic GC with boxes in loops based on example", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/loop.bismuth"))),
        "c01529e2f8f5540e2e25ae47e8a9f784d94d2446ce60244902fe1da964f713e9");
}

TEST_CASE("programs/GC-test - Basic GC w/ Send", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/GC-test.bismuth"))),
        "4961a24485194590afaa69fb222b662881a1a79eb97a27a78dd78890c639c9af");
}

TEST_CASE("programs/TStructGC - Basic GC w/ Send and Structs", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructGC.bismuth"))),
        "dc1fe2a258977539416a6b0edd588790d3e05f0875d4d41f0f6a8260630ca4af");
}
/************************************
 * Example C-Level Tests
 ************************************/
TEST_CASE("C Level Positive Test #2", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/CLevel/CPositive2.bismuth"))),
        "7d58301030c4f328b84753f57acfe0cdb94b4abae63088327c653ad3859d6cf7");
}

/************************************
 * Example B-Level Tests
 ************************************/
TEST_CASE("B Level Positive Test #1", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/BLevel/BPositive1.bismuth"))),
        "351de154d74d97942665f3005a6fb2b55418c5d9086986d441d4ff1f31911864");
}

TEST_CASE("B Level Positive Test #2", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/BLevel/BPositive2.bismuth"))),
        "22a43a88c13da41b2b7f6a863fe84823feb453e5f93f91bf50d6c6f84bb71a2c");
}

/************************************
 * Example A-Level Tests
 ************************************/
TEST_CASE("A Level Positive Test #1", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive1.bismuth"))),
        "516859c91ce4af7e04ffcd78e5a0d2b1c7b247d7cc13f2bde5a197f4b6b564e0");
}

TEST_CASE("A Level Positive Test #2 - If", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive2.bismuth"))),
        "52a548a0f9a6e652a26ee7a8abc3c07d531a0bef14141707f92a9717fa359c05");
}

TEST_CASE("A Level Positive Test #3 - Select", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive3.bismuth"))),
        "72bb25c93d65ff774af3d84c1dfac8eaaaa382779143ae29ce2149c675d6c9d4");
}
