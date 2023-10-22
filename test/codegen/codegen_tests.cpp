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
    SemanticVisitor *sv = new SemanticVisitor(stm, DisplayMode::C_STYLE, 0);
    auto cuOpt = sv->visitCtx(tree);
    REQUIRE_FALSE(sv->hasErrors(0));
    REQUIRE(std::holds_alternative<TCompilationUnitNode*>(cuOpt)); //cuOpt.has_value());

    CodegenVisitor *cv = new CodegenVisitor("BismuthProgram", DisplayMode::C_STYLE, 0);
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
    SemanticVisitor *sv = new SemanticVisitor(stm, DisplayMode::C_STYLE, 0);
    auto cuOpt = sv->visitCtx(tree);

    REQUIRE(sv->hasErrors(0));
}

TEST_CASE("programs/test1 - General Overview", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test1.bismuth"))),
        "b166f64d6c74d59ebf7a6ef3ba136fa8c54024770638395b68db8c173d45799a");
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
        "1abbbeebd776ceb36249113d91e03ef0bbc174ecc07f166c7ecd17366e127eac");
}

TEST_CASE("programs/test3 - If w/o else", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test3.bismuth"))),
        "94d5d08a4be7073f2845fd0e484de907685eb9fc353461fc53c679f119e9bd32");
}

TEST_CASE("programs/test4a - Use and redeclaration of parameters", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test4a.bismuth"))),
        "c2556d63b8890711ea7460a7d7d60b1725d570fff9a2e76420d824116f991b07");
}

TEST_CASE("programs/test5 - Nested ifs and if equality", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test5.bismuth"))),
        "0b48b770df50b51ec516312ac24623170a4bc7aa02384710a674f24226b4749d");
}

TEST_CASE("programs/test6 - Basic Select with Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test6.bismuth"))),
        "50cd6a051114a88f3e7ee627104943b193fdb5a8b03673a2864e1729cb7f6cc5");
}

TEST_CASE("programs/testSelectBlock1 - Basic Select with Blocks that Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock1.bismuth"))),
        "8dd9b23650bd91b93d328a0e1436ac833cf7e90ff0cc43f2c426a2242c876f8e");
}

TEST_CASE("programs/testSelectBlock1-fn - Basic Select with Blocks that Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock1-fn.bismuth"))),
        "eece8bc56de35fe56f307c6c09f74211c3205b48525595883d148f26790cf0a4");
}

TEST_CASE("programs/test6a (CAFE!) - Basic Nested Selects, LEQ, GEQ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test6a.bismuth"))),
        "5e194e3b825e0da68747a0c466811e649841ebfc5f4b45a4f4dd6a744b8c820e");//"cafe2b3e17335a03444e7c3e1be095eaea8cb901741e8c0d8f1f79a17a8fe6c4");
}

TEST_CASE("programs/testSelectBlock2 - Select with blocks that don't return", "[codegen]")
{
    // NOTE: Should be same as test6a
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock2.bismuth"))),
        "314cffb8f31b63cfddbe2b756c3b92131f595af0f2c5f867168f62694934d7b8");
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
        "f223f24ed3270b44a7b77fa95fa145e4b9c51b81003fdabd0af0650d3196f14b");
}

TEST_CASE("programs/test11 - Expressions in decl (let*) ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test11.bismuth"))),
        "a5208935b893f1b01f8a0b491816bf3c658a8444404b1a513a66b190a9b64014");
}

TEST_CASE("programs/test12 - Scopes & Prime Finder Example! ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test12.bismuth"))),
        "37bc90365a15d544a3db2fb6fc7704a8ab7b31fd8c68d80199656a7ba89e23be");
}

TEST_CASE("programs/test13 - Recursive Fibonacci", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test13.bismuth"))),
        "87a3e9b45b4c32bbb51cf41831428475b7313028958725ee89eebaca6082c9e8");
}

TEST_CASE("programs/adv/LambdaDef", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/LambdaDef.bismuth"))),
        "0f9ad19acfd416ce69f1b423cc0a7532b7cf806e5468f378126eb10413081afb");
}

TEST_CASE("programs/test-shortcircuit - Basic Short Circuit (and)", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-shortcircuit.bismuth"))),
        "089842dbe23ea05526b6736667ea24cb88554d12e167e8a11ac5703ccba78880");
}

TEST_CASE("programs/test-shortcircuit-rt - Basic Short Circuit (and + or) w/ Runtime", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-shortcircuit-rt.bismuth"))),
        "d08aaae5cb44110528effe572fc9f6159e2f3e8d52acdfdc3764c42222582d8f");
}

TEST_CASE("programs/test-arrayAssign - Assigning one array to another and editing arrays in functions", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-arrayAssign.bismuth"))),
        "ededc082a6d11fc6f7f2fc0b6b72d23c32e8b06e854e667658cadbef46c0987a");
}

// FIXME: RENAME AS WE DONT HAVE PROC ANYMORE!
TEST_CASE("programs/externProc - Declaring an external proc", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/externProc.bismuth"))),
        "66d4750115b4eb234b4ff731512b20c1ce36d39264bfa27df0f11587d686ea6e");
}

TEST_CASE("programs/test14a - Test nested/more complex shorting", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test14a.bismuth"))), 
        "069d2acfcc68a356cc7dabdddee1beedd3010e4698beab7e9547920597fa97a2");
}

TEST_CASE("programs/17 - var inf in decl", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test17.bismuth"))),
        "ecd436e46549221d6db0a3a65b2eba7fa4b29450fc5bad753879361dff29e37e");
}

TEST_CASE("programs/test18 - Parody", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test18.bismuth"))),
        "7fb3deb5bf652ae42c489488db0bacfb29af9cba521e7edd089dbf44a014a58f");
}

TEST_CASE("programs/Lambda1 - Basic lambda Test", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda1.bismuth"))),
        "9ce8b4c8bcb6f49cafdc7905e72e0626eb5069bbc53c25fe194f94ed940c8a76");
}

TEST_CASE("programs/Lambda2 - Basic lambda Test w/ return", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2.bismuth"))),
        "8ef05d57f9d1dce2ab4bfc910e8f758f29bd15d46da26ae5dd0d27ed41b60f4b");
}

TEST_CASE("programs/Lambda3 - Basic lambda Test w/ return and same name", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda3.bismuth"))),
        "9da13866d5113cd0f379ae60cceb6f55dd6121a83a8d6023d6244b4f650c7cac");
}

TEST_CASE("programs/externLambda", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/externLambda.bismuth"))),
        "8ebad02a01073b7a0dfcc4ca465a4eef4c1cc404b85b731522e7c517f0e93cf0");
}

TEST_CASE("programs/enum1 - Basic Enum 1", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum1.bismuth"))),
        "3d7ec32220960f5357711d54e61196492f3e4eb0f57d0eb35bd0030af084e167");
}

TEST_CASE("programs/enum2 - Basic Enum 2 - double cast", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum2.bismuth"))),
        "efd1431664f8a73d134248c4cc4aaee42a6fbfd2760adac4c38b896c051862bc");
}

TEST_CASE("programs/enumAssign - Same a  Enum 2 but with assignments outside of decl", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumAssign.bismuth"))),
        "f381dfd03b3dd7e3018d305646087ab26d5af2bd3ea0056cebba0d277ef0bf3a");
}

TEST_CASE("programs/enumAssign2 - Returning lambdas, functions, and enums", "[codegen][enum][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumAssign2.bismuth"))),
        "38c39065040b4a6dac8b2dd276dfd39247799b4d718a1b80b50dd637ac6331eb");
}

TEST_CASE("programs/enum3", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum3.bismuth"))),
        "7c8f7d414fefd8f2d453fcf82fb142197e1a51e55b5ae491f5103073d404215d");
}

TEST_CASE("programs/adv/StructTest2", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest2.bismuth"))),
        "7598cdc542ab0ab4ba285bd16f629db78eaf386b8fcf2436c2848cf804948c42");
}

TEST_CASE("programs/adv/StructTest3", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3.bismuth"))),
        "bde48cb2b553eaf1cc043d99a417da1c50875b66286f7d81117a6267eb042808");
}

TEST_CASE("programs/adv/StructTest3a - nested fields", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3a.bismuth"))),
        "057bcf2ca45046d3edcaf0e8a6ae62ca49271946d2413276023bb4f1128df9f9");
}

TEST_CASE("programs/adv/StructTest3b - nested fields", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3b.bismuth"))),
        "88c6d253a9e9ae2f661f3466c1acd4f44b0682a3b4d8eea9c35c14fb6be7739d");
}

TEST_CASE("programs/adv/StructTest4", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest4.bismuth"))),
        "1464becd054c0c38fdd00f713b0a11936d78cd4ecbf84f8f2a8ad4210214dcd7");
}

TEST_CASE("programs/adv/NestedEnum", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/NestedEnum.bismuth"))),
        "1cab373a6a78bede3be82f26367cc4e8ae89ac899d700009339a3cae2fade7c8");
}

TEST_CASE("programs/dangerLambda-Program - lambdas with duplicate function names", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/dangerLambda-Program.bismuth"))),
        "8fe861422a057ce1a6bc9a8d8149d74a8a99c9776f3511653f89b3749903c24d");
}

TEST_CASE("programs/dangerLambda-Lambda - lambdas with duplicate function names", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/dangerLambda-Lambda.bismuth"))),
        "caea2fe13e5b4245248178b6e6d7bf0afbdebe4640e561de21eb86ca8840da69");
}

TEST_CASE("programs/adv/enumPassing - passing non-enum as enum argument", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassing.bismuth"))),
        "072b25ca39c54411c00392d6a1ef1308f369e228ceafcc467c17ffd5c88e879f");
}

TEST_CASE("programs/adv/enumPassing-fn - passing non-enum as enum argument", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassing-fn.bismuth"))),
        "1458917159da5ea724a6f338dc254ec59701506155fefeb9e987a63eff04abea");
}

TEST_CASE("programs/Lambda2a - More nested lambdas", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2a.bismuth"))),
        "9f5a80cee77fd41645521043541e3e2ecfd7ed00357b55e217bb8774bf4332f5");
}

TEST_CASE("programs/adv/enumPassingInf - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassingInf.bismuth"))),
        "e9fe2f7229a7d5aecd7469ffd2ff8c3763cb1750450c91917f68c2aecb15d0b0");
}

TEST_CASE("programs/adv/enumPassingInf-fn - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassingInf-fn.bismuth"))),
        "acedd92da4f5098603ff6f006077c3501e035244575cfff0f71dbbb01fb48ba2");
}

TEST_CASE("programs/Lambda2b - More nested lambdas", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2b.bismuth"))),
        "56b383e75a0785b42d6ddfe4ef8a0959ed50288c669b0c15eb719258d0a4d35b");
}

TEST_CASE("Out of order function", "[codegen][program]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ooof.bismuth"))),
        "ec92315e12097b17131fdfbc4bf93725b1bbfd35abd86399a2022997fb17dbba");
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
        "f6c74de5eb0966c57ad598d54ba3f362b3d7669b796b9d1caa75b6a2e68920c0");
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
        "802e1124ffc93512a1e35bf4c310ed85ceace0f2c3101b8ced405aeebd7caf1f");
}

TEST_CASE("programs/cancelable/DoubleCancel - Basic two blocks with cancel", "[codegen][cancel]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/cancelable/DoubleCancel.bismuth"))),
        "8f8f321feb60738d4d754befd37b8c9558e1de717eec503941eb77986d4af621");
}

TEST_CASE("programs/cancelable/BranchCancel1 - Basic cancel w/ branch and repetition", "[codegen][cancel]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/cancelable/BranchCancel1.bismuth"))),
        "0"); // 
}


/************************************
 * Example C-Level Tests
 ************************************/
TEST_CASE("C Level Positive Test #2", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/CLevel/CPositive2.bismuth"))),
        "134930cec016a9e0d4d76c6de01f96e185c9b0d86f86f672c02c1e881aeefc21");
}

/************************************
 * Example B-Level Tests
 ************************************/
TEST_CASE("B Level Positive Test #1", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/BLevel/BPositive1.bismuth"))),
        "708ecd4ad20400d6fa7a84f4de1f7403e3d54e91657e4f3d23754eb34838449c");
}

TEST_CASE("B Level Positive Test #2", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/BLevel/BPositive2.bismuth"))),
        "fa5f972670354fcf246f6985d33b789a7f6a792626e99388af027bc49bd97b3c");
}

/************************************
 * Example A-Level Tests
 ************************************/
TEST_CASE("A Level Positive Test #1", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive1.bismuth"))),
        "797ca653f181a2d7af8f5e58d5f00f96616ca7a27416148d7040546cc06fabc2");
}

TEST_CASE("A Level Positive Test #2 - If", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive2.bismuth"))),
        "a58d1a3f2c0d54d04d4b104f9fb65a2c8546dd90ff4df5b40e2b1b6a7e4ab777");
}

TEST_CASE("A Level Positive Test #3 - Select", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive3.bismuth"))),
        "93224a27f41078d400b2c4cd190cf6bbd69e85fb98594f1190ac983a854a596d");
}
