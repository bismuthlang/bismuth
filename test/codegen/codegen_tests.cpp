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
    REQUIRE(std::holds_alternative<TCompilationUnitNode*>(cuOpt)); //cuOpt.has_value());

    CodegenVisitor *cv = new CodegenVisitor("BismuthProgram", 0);
    cv->visitCompilationUnit(std::get<TCompilationUnitNode*>(cuOpt));//cuOpt.value());
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

TEST_CASE("programs/test1 - General Overview", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test1.bismuth"))),
        "cd7b2e97d3985da2b7b5c1f6710a693ebe3bf398750aff372404fffcaf4f0a59");
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
        "1e77cdbb2c8b341f564705c632588e2912ae53f65e4d95270056677a05c0dbb4");
}

TEST_CASE("programs/test3 - If w/o else", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test3.bismuth"))),
        "dcdb52c5e81bdea66c9d8f39f887ad31fd3bdfc9a00debae58351cbd4df0288b");
}

TEST_CASE("programs/test4a - Use and redeclaration of parameters", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test4a.bismuth"))),
        "016e3d4b2a2e7ba2a856f7559baf2288ec1cdff8cd2ec68a84f7e8b44c0bb736");
}

TEST_CASE("programs/test5 - Nested ifs and if equality", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test5.bismuth"))),
        "17122f11e5d63a0fe090055e6c97699ac5a948a4c0fb1dfdc7ad304c36d9d249");
}

TEST_CASE("programs/test6 - Basic Select with Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test6.bismuth"))),
        "8113827ef3d63bbb9fd419f5e2173afe1d53e825dcbbb37e17b2f25eb335475b");
}

TEST_CASE("programs/testSelectBlock1 - Basic Select with Blocks that Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock1.bismuth"))),
        "49ba002df2043abd15c217bcaede0dc07042a813f2cde61cb13fa33d75c6a128");
}

TEST_CASE("programs/testSelectBlock1-fn - Basic Select with Blocks that Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock1-fn.bismuth"))),
        "5a4ca460a84b69d6256e325239dec7fbbbd1d9f4fb1d5370b04400a57e4a9c3a");
}

TEST_CASE("programs/test6a (CAFE!) - Basic Nested Selects, LEQ, GEQ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test6a.bismuth"))),
        "1d7253d6c544a805f8cebf3641f2af585c46160bde1cf8247ba027d848214cb8");//"cafe2b3e17335a03444e7c3e1be095eaea8cb901741e8c0d8f1f79a17a8fe6c4");
}

TEST_CASE("programs/testSelectBlock2 - Select with blocks that don't return", "[codegen]")
{
    // NOTE: Should be same as test6a
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock2.bismuth"))),
        "f464bb890dd2bf60cfdda17dd184df622fa9c3aa5f78f24423b222b1943fd2aa");
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
        "ba5c7395a9ccdf6d70e7dd3ec38e48790a564f72cd29ba3fecc4e26a90232e15");
}

TEST_CASE("programs/test11 - Expressions in decl (let*) ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test11.bismuth"))),
        "41c62713e8d6b46c6e96fdb5fa91c1f0227ac0f93475d4f1398e577088d87f83");
}

TEST_CASE("programs/test12 - Scopes & Prime Finder Example! ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test12.bismuth"))),
        "c68e036b92b535b5c8b7fa63b208d3330eaa7a7e8d01e26f841ed308c0f6fbcd");
}

TEST_CASE("programs/test13 - Recursive Fibonacci", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test13.bismuth"))),
        "7b47fb0b7ec3726205c1cfb0c5518b6523e5f2d35d14be5b7d479fd27465e244");
}

TEST_CASE("programs/adv/LambdaDef", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/LambdaDef.bismuth"))),
        "330558013ea1186dad36a1876d768407526f01b957680c87e477dc61698e0a03");
}

TEST_CASE("programs/test-shortcircuit - Basic Short Circuit (and)", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-shortcircuit.bismuth"))),
        "31085f579d72a15b9e2b549d0d945f7dff4c9b1cb4e3f93381133a27ce3ad0c1");
}

TEST_CASE("programs/test-shortcircuit-rt - Basic Short Circuit (and + or) w/ Runtime", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-shortcircuit-rt.bismuth"))),
        "1cdf395315514e34f8298b676bdfa0be9571ece5d501a75816f682f5b334bac7");
}

TEST_CASE("programs/test-arrayAssign - Assigning one array to another and editing arrays in functions", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-arrayAssign.bismuth"))),
        "b5e681a9802a301b11cc2b033ec9774fef8762c9203f95aeffeb5dc176afdad6");
}

// FIXME: RENAME AS WE DONT HAVE PROC ANYMORE!
TEST_CASE("programs/externProc - Declaring an external proc", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/externProc.bismuth"))),
        "88ae3894d80a15b80b1047a7a08a2954b655c1aef2f5488390db16771cb4e013");
}

TEST_CASE("programs/test14a - Test nested/more complex shorting", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test14a.bismuth"))), 
        "acdd50a217489539546e04a6c977c86e185e070e5a1a97672846b256ca860b2c");
}

TEST_CASE("programs/17 - var inf in decl", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test17.bismuth"))),
        "8dc8b9ced3851e1a3f3f72c107ca6d85e1c0a2bb110bc9288400ceb2ca94577d");
}

TEST_CASE("programs/test18 - Parody", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test18.bismuth"))),
        "2df855f46312c7740e97cfe3955f6954db1912cb04eb50851a7aeb2d767bc883");
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
        "0cd21f2d04102f9c56fadefc48311508cf7f4c5e5b13fa158e549d3083d5720d");
}

TEST_CASE("paper/links2", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links2.bismuth"))),
        "f2ad6e1f177f59882fb54b0464d796dcda343823b5adc45946a0b5eb1be80067");
}

TEST_CASE("paper/links3", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links3.bismuth"))),
        "290b0f39eec6442b46b87dd5b836cd475f928c01fbbf8805938cebeaff8a3489");
}

TEST_CASE("paper/links4", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links4.bismuth"))),
        "75f82d658b99a5816cdf4c531e7d7c640be1f77c3de56d8eb9491b230ef0dbc9");
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
        "b9b3001aa97180f58a271e05768d44af009f5af93b3f1d0c555b6e6302eb73d0");
}

TEST_CASE("programs/TBox2 - Parody + Clone w/ boxes", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TBox2.bismuth"))),
        "c7e55263101b68aea4394a6cf8f458471f9b7ee6cc2edce4bb77a0f98ca9e183");
}

TEST_CASE("programs/TStruct - Parody + Clone w/ Struct Boxes ", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStruct.bismuth"))),
        "7b7cadf954c1066f9b7cfb857222b8a35037584871de83b7c103f05c9de67aff");
}

TEST_CASE("programs/TStructEnum - Parody + Clone w/ Enum Struct Boxes ", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructEnum.bismuth"))),
        "a9952ebc97f9353a291d7eec7f0dd3105c61bd3c1d6a5d43e72e653c2f50e676");
}

TEST_CASE("programs/TStructEnumGC - Parody + Clone w/ Enum Struct Boxes + GC ", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructEnumGC.bismuth"))),
        "d08d20479b4ec36f5c5f0633cb21e09141a44bf9d3a2bb947ff70ef57a67e875");
}

TEST_CASE("programs/TArray - Parody + Clone w/ Array", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TArray.bismuth"))),
        "e3fac3c8656e5cec6b141f017bbacb014549603db92f558fe7cc47a113358d42");
}
TEST_CASE("programs/TArray2 - Parody + Clone w/ Array Double box", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TArray2.bismuth"))),
        "ff4615ebe1e4421c46b075f9446badced90d0ee3be4410597588552443c69082");
}

TEST_CASE("programs/TStructEnumArray - Parody + Clone w/ Struct Enum Array", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructEnumArray.bismuth"))),
        "9c729f42f3dd01148258a24c930253a40293b8eff3f09ee68a3bed91272d1bea");
}

TEST_CASE("programs/loop - Basic GC with boxes in loops based on example", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/loop.bismuth"))),
        "7727655235f992144ba2241c8f2b815af840a37a295574a2592ef272b82e6620");
}

TEST_CASE("programs/GC-test - Basic GC w/ Send", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/GC-test.bismuth"))),
        "e5f5cfa7638e2c611c403746d9f4e19711c87a1bcd58fbbec2b7ae2bf9d0f234");
}

TEST_CASE("programs/TStructGC - Basic GC w/ Send and Structs", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructGC.bismuth"))),
        "257eeacb12f851a80e7b416943177ee427daf0f752b31a0de5a628296733fe7d");
}

TEST_CASE("programs/TStructCopy - Basic test of copy", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructCopy.bismuth"))),
        "039170bd7be999a994cc6d11d61811181880f3a036943e49e9b248b94015b501");
}

TEST_CASE("programs/db/db - Basic DB 1", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db.bismuth"))),
        "16b9c7b147b3ee3aa8c084dfd210925319a15468497b67733da05dd0353c2656");
}

TEST_CASE("programs/db/db2 - Basic DB 2", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db2.bismuth"))),
        "b11773c6986564bcc7f782cfce7f9492f9568359423595cef11f8271cf64420a");
}

TEST_CASE("programs/db/db3 - Basic DB 3", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db3.bismuth"))),
        "4e7b73797a694ba6a334b626aefdb39c5725165ebecb46875ba0886c8ea33aed");
}

TEST_CASE("programs/db/db4 - Basic DB 4", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db4.bismuth"))),
        "0d55d8ffb578d77f818b518cfc3861345b170186a3bc47f4b907651e33a381bf");
}

TEST_CASE("programs/db/db5-if - Basic DB 5 - AcceptIf", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db5-if.bismuth"))),
        "002a510c42e113419bb4bdb16dc57a6fc4e0cbbb436b737707f26c8dbcf022d2");
}

TEST_CASE("programs/db/db5-if-present - Basic DB 5 - AcceptIf and is_present", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db5-if-present.bismuth"))),
        "f2e071f24ebc1f81a0be1e4350f8e0d50231886d203e55c67944a1c175f89181");
}

TEST_CASE("programs/db/db5-if-present-else - Basic DB 5 - AcceptIf with else and is_present", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db5-if-present-else.bismuth"))),
        "82b0e01a510caff830d4eb96f79180f0e3755694e24710a40c2c53b2a1d81fda");
}

TEST_CASE("programs/db/db5-while-present - Basic DB 5 - AcceptWhile and is_present", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db5-while-present.bismuth"))),
        "ec647dcaea639ea7db636790cd4c5b897c2ee6cb5781a3b909421dff1113d102");
}

TEST_CASE("programs/bt - Basic Binary Tree", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/bt.bismuth"))),
        "9a2a2ef101e836c1ad9f06e55924e2cf355d874f9fc5e53dfa41c96f842b58eb");
}

TEST_CASE("programs/bt-walker1 - Basic Binary Tree w/ walker", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/bt-walker1.bismuth"))),
        "5a79067569aa30698c14dae7e72f71e00dae8a17d7642eb21e956935167c5cf6");
}

TEST_CASE("programs/parity-check - Parity Check 1", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/parity-check.bismuth"))),
        "ef0252eee1d37ed28524c61e9476311d0c06664a4c3c44cc3c6d982dedab764f");
}

TEST_CASE("programs/parity-check - Parity Check 2", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/parity-check2.bismuth"))),
        "1e9d023732849f65af9438ac76e7b144e485d9480cf7521f2fbe1729b14ba2fd");
}

TEST_CASE("programs/parity-check - Parity Check 2a", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/parity-check2a.bismuth"))),
        "1e729f74c241fea286bd1d10e56cead332afcd3007ae2e58a5adbea31c1744cf");
}


TEST_CASE("programs/adder - Add Stream", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adder.bismuth"))),
        "5b197be58b320967d601d8aeb5ef6b544c4e69b1f371a46ed9c49fb4f3062a6a");
}

TEST_CASE("programs/adder2 - Add Stream 2", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adder2.bismuth"))),
        "7ce6e8ee62e90176cec9ad6b2504adc7cc6949535ea4cd1c0514340c27174352");
}

TEST_CASE("programs/adder3 - Add Stream 3", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adder3.bismuth"))),
        "2afda1f4ac120325c69981c93a3a0e5f47085e1d03c20348bd75e45e20652383");
}

TEST_CASE("programs/adder4 - Add Stream 3 but out of order and higher-order channel", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adder4.bismuth"))),
        "7e5ef2cba7f9905e43de9c236e50be2695478345142e851f19a419bbfb6e8293");
}

TEST_CASE("programs/adder5 - Add Stream 4 but using fn that returns linear variable", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adder5.bismuth"))),
        "1574f9660cfbe9b5338e3f1bc4d1c45cdbbd7b05661c74599696dfd5de0c4d12");
}

TEST_CASE("programs/nested_struct - Definitions within definitions", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/nested_struct.bismuth"))),
        "8c0207b60fd885331411b85d6c1ca6191d05ab14f01f925b8fe2830df7619244");
}

/************************************
 * Example C-Level Tests
 ************************************/
TEST_CASE("C Level Positive Test #2", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/CLevel/CPositive2.bismuth"))),
        "1f21906d3e151e00040a5de7da0bc29bdf0260014da982496486a421771f3900");
}

/************************************
 * Example B-Level Tests
 ************************************/
TEST_CASE("B Level Positive Test #1", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/BLevel/BPositive1.bismuth"))),
        "396fbbfad2e409c23dbf864e32a23e208b838912acc0ca71a5231d62200fc9a1");
}

TEST_CASE("B Level Positive Test #2", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/BLevel/BPositive2.bismuth"))),
        "8814d7a37c545656c217992b522212aaac064cf9a7bd9c1fcd689adb57124675");
}

/************************************
 * Example A-Level Tests
 ************************************/
TEST_CASE("A Level Positive Test #1", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive1.bismuth"))),
        "62addf4c9014d15a31a06c8fc9583f1b65b568516753f90517fdd8845a90975c");
}

TEST_CASE("A Level Positive Test #2 - If", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive2.bismuth"))),
        "508ff0731da2a615cb8012cb884cd4c6077cfd2da32ebb84c5b33650712d3d84");
}

TEST_CASE("A Level Positive Test #3 - Select", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive3.bismuth"))),
        "8dc469b5a311ec97a28324d628c43e0fc5d13810355637a148f957e6d4386eb7");
}
