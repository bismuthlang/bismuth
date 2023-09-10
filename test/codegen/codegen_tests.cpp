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
        "ceb5543a0f7344ba85c52bae230c4aefd8a94b8e5f4e613597702ab379e908ce");
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
        "dd74a6265ae9f82a381e36078c5c762e073222a8bf6bfe20fec943e7b8f98a71");
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
        "b72e217b49959d37023f204782f3d050359530916cf71f4cff7a46bf7d276656");
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

TEST_CASE("programs/Lambda1 - Basic lambda Test", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda1.bismuth"))),
        "ea5513071243b58fe3f66625c5905e0b7ce1fcc8d19b72bbf5cffd9c14f3241e");
}

TEST_CASE("programs/Lambda2 - Basic lambda Test w/ return", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2.bismuth"))),
        "a5c7330117b1b53b43bc7b8b579c0aa907bbf67e32d81832e7f09e1fcf899882");
}

TEST_CASE("programs/Lambda3 - Basic lambda Test w/ return and same name", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda3.bismuth"))),
        "b0a5ac3a84e0609c5b1726ad79eed2b1f66027d5c7d0511344d251e6aa28a894");
}

TEST_CASE("programs/externLambda", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/externLambda.bismuth"))),
        "8d7f99bf750437b94a49b547319eb3be6e5451b1ef3d7e37ffd3d22d6756a8b5");
}

TEST_CASE("programs/enum1 - Basic Enum 1", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum1.bismuth"))),
        "2895bdc931e0b04411f07d68c68dfafaf1954739a85c2407498f15dec1d42a52");
}

TEST_CASE("programs/enum2 - Basic Enum 2 - double cast", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum2.bismuth"))),
        "beaf0eca70dd8f511e5222ca5a8093b557a756832e3c3cc20f79352b5d95e092");
}

TEST_CASE("programs/enumAssign - Same a  Enum 2 but with assignments outside of decl", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumAssign.bismuth"))),
        "a95113fc82a92d9be20aef560fca395373feaf2eb88cd222bfc72d987a7684a5");
}

TEST_CASE("programs/enumAssign2 - Returning lambdas, functions, and enums", "[codegen][enum][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumAssign2.bismuth"))),
        "b9e8ed285116efa884e4e410bcd7c22f0cc31c18da51ddcfd545fb59c8be1315");
}

TEST_CASE("programs/enum3", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum3.bismuth"))),
        "fabd4fe1b6aae44b0ff0a1725b5dda76391c14a0ce07fc78cfb3e546a0ea3a17");
}

TEST_CASE("programs/adv/StructTest2", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest2.bismuth"))),
        "e51323fa85a8770a0eac5ad637897cbba190df3d75a568799aa5314f18a07023");
}

TEST_CASE("programs/adv/StructTest3", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3.bismuth"))),
        "03fff61e60f432cd80f2705a4ebdc02931cff03ce09d0dcc3bea6e3d09e7e3a0");
}

TEST_CASE("programs/adv/StructTest3a - nested fields", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3a.bismuth"))),
        "f1c76030d283825603b9af7d0ca9e350237252c13b63f5933e79ad6399ae0a29");
}

TEST_CASE("programs/adv/StructTest3b - nested fields", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3b.bismuth"))),
        "711f7b34b5db909669d337e09641d67bd66b43a74e2f9a975e6445d08f7fb369");
}

TEST_CASE("programs/adv/StructTest4", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest4.bismuth"))),
        "d0f20c6ef540ee9201b61b1336b137d19d7c1f4ad4ebff226401e969594ba913");
}

TEST_CASE("programs/adv/NestedEnum", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/NestedEnum.bismuth"))),
        "f1478d3202034bdeeb11d1a9cca935c9f100a011945fe858bf3eb253b660e3ff");
}

TEST_CASE("programs/dangerLambda-Program - lambdas with duplicate function names", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/dangerLambda-Program.bismuth"))),
        "0f586211d9736dfdad23f1376e2b31bd4b0cdf47be21702a97cf739ccca8f4c8");
}

TEST_CASE("programs/dangerLambda-Lambda - lambdas with duplicate function names", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/dangerLambda-Lambda.bismuth"))),
        "8d3f2337463b6bcb62852bcdd65218e8438fe1f851fdc9de292b0eec5e3d9039");
}

TEST_CASE("programs/adv/enumPassing - passing non-enum as enum argument", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassing.bismuth"))),
        "5445fa306f85e8953f9e7fa2b3ce6826674de6d2bcf61ec51313d71207680300");
}

TEST_CASE("programs/adv/enumPassing-fn - passing non-enum as enum argument", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassing-fn.bismuth"))),
        "35dffb874918450d62a7bc795637984586f27c60c42d51a0621984dc18313d9f");
}

TEST_CASE("programs/Lambda2a - More nested lambdas", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2a.bismuth"))),
        "04f2b125bc67fa92d8025ec191283b262dee5b2193ada2b160b5cbc4a506f3d2");
}

TEST_CASE("programs/adv/enumPassingInf - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassingInf.bismuth"))),
        "da95d956f96793c5f1f1c295004f8b0a62be3af36bd77e3eaefee2b199ebca5e");
}

TEST_CASE("programs/adv/enumPassingInf-fn - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassingInf-fn.bismuth"))),
        "2e6199f900e43c1e74d77be6387c6504e936b308ac1bdea7a9ab03b111a4b694");
}

TEST_CASE("programs/Lambda2b - More nested lambdas", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2b.bismuth"))),
        "6b44077ae04e19b510a9b6cb47b879186996b6605075fe01ebb84dd8f8dbeadd");
}

TEST_CASE("Out of order function", "[codegen][program]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ooof.bismuth"))),
        "f352767e1f71a80a12dd667b7090da8037b329a86fa34a29ec27848824f8af5f");
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
        "50e7ca458b80f07fea189e08dd4773b9fcf9f0eb8a095b9e89c415215b58579f");
}

TEST_CASE("paper/links", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links.bismuth"))),
        "74570eee263b5817a7693c53aae6ea22197e6b3136f417108c4c0f6a1885f1ce");
}

TEST_CASE("paper/links2", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links2.bismuth"))),
        "e9145e630f32139daba01610ef3aebeeeae8799c7556ec87f80eeb6c66ed4507");
}

TEST_CASE("paper/links3", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links3.bismuth"))),
        "3723b6527a033a44c8787f9596c1986dc0652ea69aedf725bb49950ee2af63eb");
}

TEST_CASE("paper/links4", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links4.bismuth"))),
        "22ec98f6ecb6520b4128974cf32d964b0fca15e2a3b643030162d85e254ca3a4");
}

TEST_CASE("programs/doubleArg1c2 - weakening and loops", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/doubleArg1c2.bismuth"))),
        "1d20ca026de3897c4aa64ce9545adacf89b97799c4a30fcdf2aaf0464ad782f2");
}

TEST_CASE("programs/enumedit", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumedit.bismuth"))),
        "44e08fc9ff114660ac8cc5dc58be66e982e8cd33d2d989d025f61b82e752b9e0");
}

TEST_CASE("programs/TBox - Parody + Clone w/ boxes", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TBox.bismuth"))),
        "5e863270446cb4a7c029588be745eed69cf2fbe2c786d1ac7d3ab0c22c3a3ba5");
}

TEST_CASE("programs/TBox2 - Parody + Clone w/ boxes", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TBox2.bismuth"))),
        "3e77737208a88429fa003f8f320f9f8b950e155f71862335cd4ea95b6aff5640");
}

TEST_CASE("programs/TStruct - Parody + Clone w/ Struct Boxes ", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStruct.bismuth"))),
        "c5135d51ca668a9edee53d4128b24b7a9cf76a05e0c182af56e04463f0e66b7b");
}

TEST_CASE("programs/TStructEnum - Parody + Clone w/ Enum Struct Boxes ", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructEnum.bismuth"))),
        "b6c7a56f30d766a49d3320d0c5376cf33b21022b4d5a1f2bfdf65b9ebdf56f5b");
}

TEST_CASE("programs/TStructEnumGC - Parody + Clone w/ Enum Struct Boxes + GC ", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructEnumGC.bismuth"))),
        "0c1cd4f71a078a5473b0ad3af6dcace77fe2d444691272b3824ece9bd38cb6f1");
}

TEST_CASE("programs/TArray - Parody + Clone w/ Array", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TArray.bismuth"))),
        "ecb51dfc8c9b462e219b4f75199dc888bd065f4b18dc1b0d986cd4b398b0708f");
}
TEST_CASE("programs/TArray2 - Parody + Clone w/ Array Double box", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TArray2.bismuth"))),
        "26f2ca452884c47688c78c3502742531c16e586f7e2d7fecd03c5459beb55320");
}

TEST_CASE("programs/TStructEnumArray - Parody + Clone w/ Struct Enum Array", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructEnumArray.bismuth"))),
        "d50c7cb760d6538040a734d6db980e2401de91ea8c89c3edb1a3633bf654d736");
}

TEST_CASE("programs/TStructEnumArrayBlock - TStructEnumArray with blocks to mess with control flow", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructEnumArrayBlock.bismuth"))),
        "c85d7a2abf1cda05652145962a9726294897f757b1332b44aee7f88b3b823d7f");
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
        "381062c171d639435cbf37039eb9cf834525fbdd19edb85d07888537116f142d");
}

TEST_CASE("programs/TStructCopy - Basic test of copy", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructCopy.bismuth"))),
        "dcb236013d66d32d90f9244eaae943e682ec7cecf9d9f19e9742cbe014486d77");
}

TEST_CASE("programs/db/db - Basic DB 1", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db.bismuth"))),
        "8f5f62d7dd8ad55e7e7747e0903626f9a4d1cd01520e06eb13fc1a12d851f889");
}

TEST_CASE("programs/db/db2 - Basic DB 2", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db2.bismuth"))),
        "37d2f34e59462560f2eb14c5c1368a6ae718dcc3b8446ca05bc70450b4fec86f");
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
        "f095966819c9edfabf28dddbb404fef41d6b12f6d1d4d8bc3ccd7d827af3343c");
}

TEST_CASE("programs/db/db5-if - Basic DB 5 - AcceptIf", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db5-if.bismuth"))),
        "c12396829d1a512ccebb7443a47eb448b7f41a1c380d5ded67fe8237a02883eb");
}

TEST_CASE("programs/db/db5-if-present - Basic DB 5 - AcceptIf and is_present", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db5-if-present.bismuth"))),
        "b64f24005d2f4ccb3260db7b1f11c852727b593ab6aba21723699568a3700fe3");
}

TEST_CASE("programs/db/db5-if-present-else - Basic DB 5 - AcceptIf with else and is_present", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db5-if-present-else.bismuth"))),
        "7ef604f62ff56e462f587776a73be9db08c86197afad15d2d7c30c059ede319f");
}

TEST_CASE("programs/db/db5-while-present - Basic DB 5 - AcceptWhile and is_present", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db5-while-present.bismuth"))),
        "535c2b7ba4834e5ac68f5ed6ccadb453de66308861702741ad2af71e757ccd91");
}

TEST_CASE("programs/bt - Basic Binary Tree", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/bt.bismuth"))),
        "a3a5c186f928b3f4b6bd595f71beb11760adc245ce1bd06af198b585c3f350c6");
}

TEST_CASE("programs/bt-walker1 - Basic Binary Tree w/ walker", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/bt-walker1.bismuth"))),
        "590ec84dfae19dd0113189bd0907f2f7b2c220e87bb1ea2d428ba308f2c10ff9");
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
        "d7fdacc9a86d980c7a9f02771de161b6470621ea403db11cb7fac9f1ff831ad5");
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

TEST_CASE("programs/asChannel-int - Convert an int into stream", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/asChannel-int.bismuth"))),
        "b1c56efe4a81d2e0af27e2b304d1ff434631cf32418c41aa32e963e6e4e5bead");
}

TEST_CASE("programs/asChannel-array - Convert an array into stream", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/asChannel-array.bismuth"))),
        "48a955cb0abaf3d36c6ddefd816b1b806adcf5613eb70aea75d6a1a79baca7cf");
}

TEST_CASE("programs/asChannel-channel - Convert regular channel into stream", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/asChannel-channel.bismuth"))),
        "b9dc91ff94405612881c8601b57c9f7fba027d07ae813d62132eca1b7ef5246b");
}

TEST_CASE("programs/cancelable/BasicCancel - Basic cancel block with two recv", "[codegen][cancel]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/cancelable/BasicCancel.bismuth"))),
        "a382c3f24071358d130812498af4d2e4e0c9306e03e403a5d694c6564af6e097");
}

TEST_CASE("programs/cancelable/DoubleCancel - Basic two blocks with cancel", "[codegen][cancel]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/cancelable/DoubleCancel.bismuth"))),
        "55b6c24a78e750c651030420ec5fb5339b7fb14eec6d14fbf1b863e6031eeff8");
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
