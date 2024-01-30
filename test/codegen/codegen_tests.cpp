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
        "4d88224546db13f2f2c789787ea7809d1b5f7546075f0b255bc0f497b57c41a4");
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
        "d205a48dcc3498f6435aa6e5e2016cea7553718a3d6b49d54496f4e579512b34");
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
        "a60ff5ce79402ac8fa39f841f6adb74a2373fab9fe979bb950908ecd7c680c0e");
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
        "730e9b41f50f4c3e74564720d82188ba1f6d64290184a54071696cfe94c00b19");
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
        "da72e9c7912794b46ae559788cbcae5e8985468197a140353d44fb10841277e6");
}

TEST_CASE("programs/Lambda3 - Basic lambda Test w/ return and same name", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda3.bismuth"))),
        "d3ded95a6887573b51bde92bb60b72bcd625b32b4b7ce4852ab3e2f355576b96");
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
        "02499636cbaee6916dabf3d117d2e0e0de36d12633e4654d1caaf035eecac954");
}

TEST_CASE("programs/enum2 - Basic Enum 2 - double cast", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum2.bismuth"))),
        "5ac261ea03d1be20b7328850b7397b425386f76429af9e1f302df9ebceda4f29");
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
        "92f925b85752b4a4cf423522e1c0441d443d20cb8618df80183ee013286fd0f6");
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
        "80e210cd119ba7460d24f5bf2d74d039fb9d7d42ecbae4ad4d9e5f7bdae5bede");
}

TEST_CASE("programs/adv/StructTest3a - nested fields", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3a.bismuth"))),
        "62d9681016ac7b288b71019c5a90f7ee97ea6d960dcad430531441391c70d545");
}

TEST_CASE("programs/adv/StructTest3b - nested fields", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3b.bismuth"))),
        "6346532262b50983f60de58a0b1b2f876950045fa53ef69c2d712091202b33fa");
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
        "c834c171a67acadce5336face78547a8010cfd283594a31aacf7f3e330f06975");
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
        "6d46bc6de43fd6066f47a23c302fb1b65b0da64f9db9732c9d8ce237fd29b176");
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
        "e337b6e257789839a5fe382988210a336e80c20cfba038e3af8185c6ec4319dd");
}

TEST_CASE("paper/links2", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links2.bismuth"))),
        "1ee56444a1fb644f6c4c0cf2a5622d7b587fa88b694fafad34eb7b06d21f28a1");
}

TEST_CASE("paper/links3", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links3.bismuth"))),
        "53b2555f6186876cb1f5621d1b4a9bdae6baa1545bfb61b4dc7cea66abaa8467");
}

TEST_CASE("paper/links4", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links4.bismuth"))),
        "838daf453c0b617b3e5ba350b1cbb0c94757f404567923262ab8be02831bb899");
}

TEST_CASE("programs/doubleArg1c2 - weakening and loops", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/doubleArg1c2.bismuth"))),
        "f3363e85bb628436cff3e506a080a0dc1ebc65131b217ca6d286c18568c72723");
}

TEST_CASE("programs/enumedit", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumedit.bismuth"))),
        "7c0d836acbadcadc17be9eca1f71a619b8ec1d78ea5567c0d89e40af8d0eea6c");
}

TEST_CASE("programs/TBox - Parody + Clone w/ boxes", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TBox.bismuth"))),
        "7dda01623a703aa3f79640e0ba6bec2faea21f744f96f74e95148df60ddea3f0");
}

TEST_CASE("programs/TBox2 - Parody + Clone w/ boxes", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TBox2.bismuth"))),
        "56e5e59e9b8b311fe8ff3dd3963f0c5ae91e0e75e316af23c395c1bf5c23d0bf");
}

TEST_CASE("programs/TStruct - Parody + Clone w/ Struct Boxes ", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStruct.bismuth"))),
        "af8ed21ebfd19643aeeeb6a004ae630c5e289089dd0bedef5623447fc52a52cc");
}

TEST_CASE("programs/TStructEnum - Parody + Clone w/ Enum Struct Boxes ", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructEnum.bismuth"))),
        "60fbf2fed2f03e8f6e81ec206d621f74f21bc21b6b2ef08740129e82664ece6f");
}

TEST_CASE("programs/TStructEnumGC - Parody + Clone w/ Enum Struct Boxes + GC ", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructEnumGC.bismuth"))),
        "96a659b6844ec3def3b280ab7caff2fda6a8061259d894bfbd983418a7f419e1");
}

TEST_CASE("programs/TArray - Parody + Clone w/ Array", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TArray.bismuth"))),
        "bb269027cd553f4685f2ed9dd64f338c76f3f717d28eb0295114f628939f3f28");
}
TEST_CASE("programs/TArray2 - Parody + Clone w/ Array Double box", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TArray2.bismuth"))),
        "b5e4f1ac9cc7c02c92b4f0fc81d8389cae81afc84e6578d4fd4e1471dc047f81");
}

TEST_CASE("programs/TStructEnumArray - Parody + Clone w/ Struct Enum Array", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructEnumArray.bismuth"))),
        "bf8c5292b4531a888f9d4347fa20cf8ea4a675934c5c1cf5d9095935b09553e7");
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
        "3a825347023f218c004f76ed1cf14f22a1849c80e4b0bd6b06f2af3245be2207");
}

TEST_CASE("programs/GC-test - Basic GC w/ Send", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/GC-test.bismuth"))),
        "e034828376e96a8d893c7fd82e74200e6db711aea00d6f418aaa63a303e33265");
}

TEST_CASE("programs/TStructGC - Basic GC w/ Send and Structs", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructGC.bismuth"))),
        "02698fcd137c5a151a46d119d4b4990aed5b8ae6c057348740d5b719bd31e4ed");
}

TEST_CASE("programs/TStructCopy - Basic test of copy", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructCopy.bismuth"))),
        "d4b33b46f536a4fffc7ec4c959afc5f2cfb46ae0f5a4621365bbf45b1ce47c2a");
}

TEST_CASE("programs/db/db - Basic DB 1", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db.bismuth"))),
        "45c97eb4fa2367e9855724642d8afe3186ed75b0802e76de57db10923a2aa571");
}

TEST_CASE("programs/db/db2 - Basic DB 2", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db2.bismuth"))),
        "e57d059dfcbae73f62d7c5a742355a20db54005d4523172b7fe61c3a79e34562");
}

TEST_CASE("programs/db/db3 - Basic DB 3", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db3.bismuth"))),
        "5d228f4f1b6b018de4da09237788eb4ffba1b405f9a66e4be460d0ace0445f83");
}

TEST_CASE("programs/db/db4 - Basic DB 4", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db4.bismuth"))),
        "a6d0d53262e7896b7777f51733faf7091acc07b85077a4954ea8613bc2a9f296");
}

TEST_CASE("programs/db/db5-if - Basic DB 5 - AcceptIf", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db5-if.bismuth"))),
        "6e0efba029366c392b322e4037f15382d3dc10daf8a1c4e85a37623ea46e0201");
}

TEST_CASE("programs/db/db5-if-present - Basic DB 5 - AcceptIf and is_present", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db5-if-present.bismuth"))),
        "82c23e4480440aa88cff2c8cdff99170b6aaa7d4c47d634a5b1869f9243bdbfc");
}

TEST_CASE("programs/db/db5-if-present-else - Basic DB 5 - AcceptIf with else and is_present", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db5-if-present-else.bismuth"))),
        "163233f427cd6c2153f09477b9e5f6afc7e7c73999e644843b7561aef519dcd2");
}

TEST_CASE("programs/db/db5-if-present-else-lbl - Basic DB 5 - AcceptIf with else and is_present and labels", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db5-if-present-else-lbl.bismuth"))),
        "62ac662f518885727443ee48a2aba551bbc79ca95a54e6f1550cef100fcf6f73");
}

TEST_CASE("programs/db/db5-while-present - Basic DB 5 - AcceptWhile and is_present", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/db/db5-while-present.bismuth"))),
        "f8cd8aab6cffbe4aca4d42c0b88c28ed386ed34ca78bf2eef4f5871e4290b26c");
}

TEST_CASE("programs/bt - Basic Binary Tree", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/bt.bismuth"))),
        "26c95917b8106115569aec55bc226dc29b5605ab4b56cf8dea6e0db60ee14d5b");
}

TEST_CASE("programs/bt-walker1 - Basic Binary Tree w/ walker", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/bt-walker1.bismuth"))),
        "a956abe6c8fcda2733589f787521e0eeb150b4448f55cc41af6d39875825090d");
}

TEST_CASE("programs/parity-check - Parity Check 1", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/parity-check.bismuth"))),
        "72d8705a4883679ad6a164e9b6db709cd85e8bd14de8c39cc8e4fff4cc1470a0");
}

TEST_CASE("programs/parity-check - Parity Check 2", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/parity-check2.bismuth"))),
        "a5815fbd4e40e4f18ddd6b530c62486d2629c07dff8cf744e80b65dc860ccbc1");
}

TEST_CASE("programs/parity-check - Parity Check 2a", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/parity-check2a.bismuth"))),
        "d36b0e1e131e7e5e7a07c06edc1a86b2b51c72380de816ff0a64ed8173752992");
}


TEST_CASE("programs/adder - Add Stream", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adder.bismuth"))),
        "9af3286a262b30cb770208956bbd6eb7acdf6322c517fe8ac45c02a4f4dd82af");
}

TEST_CASE("programs/adder2 - Add Stream 2", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adder2.bismuth"))),
        "437a9164147debfc52628d6e5daf88871eb5f2235453f158ca56591307c0d02a");
}

TEST_CASE("programs/adder3 - Add Stream 3", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adder3.bismuth"))),
        "78da6beefbc337c1fe84c75a0cf04bb922fd2ecdb0a291279b4384b1c19d5b59");
}

TEST_CASE("programs/adder4 - Add Stream 3 but out of order and higher-order channel", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adder4.bismuth"))),
        "937cc226f7bfb97912c6963fa0d35ae45e91cda6f7bcb1b9be7ca343fa27fe44");
}

TEST_CASE("programs/adder5 - Add Stream 4 but using fn that returns linear variable", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adder5.bismuth"))),
        "a9d4fb31dcf8c99dfb0dbe4ef0b1a93baa62055227f34fe8c0a3a2a5c3573256");
}

TEST_CASE("programs/nested_struct - Definitions within definitions", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/nested_struct.bismuth"))),
        "4d7bc765856fb666a703e19901f6e9fc908f3ab26fbe2742df0408acc561fb0a");
}

TEST_CASE("programs/asChannel-int - Convert an int into stream", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/asChannel-int.bismuth"))),
        "6a16488e47843b55af7a7bb1e5f29c1e569418f661606df7196f386061763a23");
}

TEST_CASE("programs/asChannel-array - Convert an array into stream", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/asChannel-array.bismuth"))),
        "afaa96f5447a3c48adfcb6516a857ed945c764f55ab97f4946b9d4b5a1bc7b26");
}

TEST_CASE("programs/asChannel-channel - Convert regular channel into stream", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/asChannel-channel.bismuth"))),
        "5770206895e10c63776ef3a8ff55967347bca9db5b4edb416d158860c75e2775");
}

TEST_CASE("programs/cancelable/BasicCancel - Basic cancel block with two recv", "[codegen][cancel]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/cancelable/BasicCancel.bismuth"))),
        "05186fc6f50aef9b513a346c457fd716f9c9705cab9b7ddedc4862637f7aefc7");
}

TEST_CASE("programs/cancelable/DoubleCancel - Basic two blocks with cancel", "[codegen][cancel]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/cancelable/DoubleCancel.bismuth"))),
        "e3e782b6a0f263cee293a40c0d415ffa304862d73bc518b39505b0dd68d4207c");
}

TEST_CASE("programs/cancelable/BranchCancel1 - Basic cancel w/ branch and repetition", "[codegen][cancel]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/cancelable/BranchCancel1.bismuth"))),
        "76c7229839d3db33e1a6d8bf3912d49f34bcd3155eb39fa23b9ad224cfa1f62c"); // FIXME: QUITE LIMITED & NEEDS IMPROVEMENTS!
}

TEST_CASE("programs/BasicForLoop - Basic For loop ", "[codegen][cancel]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/BasicForLoop.bismuth"))),
        "66ee44669728ed700a85a9823f2f240afc64262fbd08ec2f8c4abda6b22d52dd"); // FIXME: QUITE LIMITED & NEEDS IMPROVEMENTS!
}

TEST_CASE("programs/generics/Arrays - Non-recursive generic function used for dyn array utils", "[codegen][generic]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/generics/Arrays.bismuth"))),
        "086a73ef2a85a2c41a65c21a2fa33e2c4e83dce7960bb7e0a5047c536ed1ab4e"); 
}


TEST_CASE("programs/generics/inv - Various generic functions including nested", "[codegen][generic]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/generics/inv.bismuth"))),
        "d0edb2f75e11d68d855bfb6e0d73cab64f805ad509bfc707691c22894950e199"); 
}

TEST_CASE("programs/generics/Lists - Various complex generic structures including recursive", "[codegen][generic]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/generics/Lists.bismuth"))),
        "63f891cda9e80a7e41e577b84490171356854c84ea531882a783d0671ad23c11"); 
}

TEST_CASE("programs/generics/Optional - Optional as a means to test templated sum type", "[codegen][generic]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/generics/Optional.bismuth"))),
        "406731ff15472ffc3c9e9dd71d9d08e08985de0fddc219018fc2de59e094bf1c"); 
}

TEST_CASE("programs/generics/recfunctemplate - Recursive templated functions", "[codegen][generic]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/generics/recfunctemplate.bismuth"))),
        "53fa5921bdbc746b98bccc7ce8486729c61c9129674dabce26c1988a42521e58"); 
}

TEST_CASE("programs/generics/ReferenceGeneric - Co-dependent structs", "[codegen][generic]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/generics/ReferenceGeneric.bismuth"))),
        "7632d226bf1087a674e91b6e4f8765f9ffc86e14ef2f57a533ccdad04904e7d9"); 
}


TEST_CASE("programs/generics/ReferenceGenericS - Co-dependent structs", "[codegen][generic]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/generics/ReferenceGenericS.bismuth"))),
        "d576cd106373342467ae7afe7be06aee2cbfbc120830d3d150eb4c372d0f2161"); 
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
