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
#include <catch2/matchers/catch_matchers_string.hpp>

#include "antlr4-runtime.h"
#include "BismuthLexer.h"
#include "BismuthParser.h"
#include "BismuthErrorHandler.h"
#include "SemanticVisitor.h"
#include "CodegenVisitor.h"
#include "HashUtils.h"
#include "CompilerFlags.h"

using Catch::Matchers::Equals;

void ExpectOutput(string file)
{
    auto stream = std::fstream("../../" + file);
    auto input = antlr4::ANTLRInputStream(stream);
    BismuthLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    BismuthParser parser(&tokens);
    parser.removeErrorListeners();
    BismuthParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager stm = STManager();
    SemanticVisitor sv = SemanticVisitor(&stm, DisplayMode::C_STYLE, 0);
    auto cuOpt = sv.visitCtx(tree);
    REQUIRE_FALSE(sv.hasErrors(0));
    REQUIRE(std::holds_alternative<TCompilationUnitNode*>(cuOpt)); //cuOpt.has_value());

    CodegenVisitor cv = CodegenVisitor("BismuthProgram", DisplayMode::C_STYLE, 0);
    TCompilationUnitNode * node = std::get<TCompilationUnitNode*>(cuOpt);
    cv.visitCompilationUnit(*node);//cuOpt.value());
    REQUIRE_FALSE(cv.hasErrors(0));

    std::string module_str;
    llvm::raw_string_ostream OS(module_str);
    OS << *cv.getModule();
    OS.flush();

    auto log_stream = std::fstream("../../" + file + ".expected.ll");
    std::ostringstream log_str_stream;
    log_str_stream << log_stream.rdbuf();
    // REQUIRE(module_str == log_str_stream.str());
    REQUIRE_THAT(module_str, Equals(log_str_stream.str())); 
//    return sstr.str();

    // REQUIRE(llvmIrToSHA256(cv.getModule()) == hash);
}

void EnsureCompilesTo(antlr4::ANTLRInputStream input, string hash)
{
    BismuthLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    BismuthParser parser(&tokens);
    parser.removeErrorListeners();
    BismuthParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager stm = STManager();
    SemanticVisitor sv = SemanticVisitor(&stm, DisplayMode::C_STYLE, 0);
    auto cuOpt = sv.visitCtx(tree);
    REQUIRE_FALSE(sv.hasErrors(0));
    REQUIRE(std::holds_alternative<TCompilationUnitNode*>(cuOpt)); //cuOpt.has_value());

    CodegenVisitor cv = CodegenVisitor("BismuthProgram", DisplayMode::C_STYLE, 0);
    TCompilationUnitNode * node = std::get<TCompilationUnitNode*>(cuOpt);
    cv.visitCompilationUnit(*node);//cuOpt.value());
    REQUIRE_FALSE(cv.hasErrors(0));

    REQUIRE(llvmIrToSHA256(cv.getModule()) == hash);
}

void EnsureErrors(antlr4::ANTLRInputStream input)
{
    BismuthLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    BismuthParser parser(&tokens);
    parser.removeErrorListeners();
    BismuthParser::CompilationUnitContext *tree = NULL;
    REQUIRE_NOTHROW(tree = parser.compilationUnit());
    REQUIRE(tree != NULL);
    STManager stm = STManager();
    SemanticVisitor sv = SemanticVisitor(&stm, DisplayMode::C_STYLE, 0);
    auto cuOpt = sv.visitCtx(tree);

    REQUIRE(sv.hasErrors(0));
}

TEST_CASE("programs/test1 - General Overview", "[codegen]")
{
    auto stream = std::fstream("../../programs/test1.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "3f62f6bac641013772415de0d8fc0fd5f3c6e9fff28808fa8451c627a0154f16");
}

TEST_CASE("programs/test1a", "[codegen]")
{
    auto stream = std::fstream("../../programs/test1a.bismuth");
    EnsureErrors(antlr4::ANTLRInputStream(stream));
}

TEST_CASE("programs/test2 - Scopes, multiple assignments, equality (non-arrays)", "[codegen]")
{
    ExpectOutput("programs/test2.bismuth");
}

TEST_CASE("programs/test3 - If w/o else", "[codegen]")
{
    ExpectOutput("programs/test3.bismuth");
}

TEST_CASE("programs/test4a - Use and redeclaration of parameters", "[codegen]")
{
    ExpectOutput("programs/test4a.bismuth");
}

TEST_CASE("programs/test5 - Nested ifs and if equality", "[codegen]")
{
    ExpectOutput("programs/test5.bismuth");
}

TEST_CASE("programs/test6 - Basic Select with Return", "[codegen]")
{
    ExpectOutput("programs/test6.bismuth");
}

TEST_CASE("programs/testSelectBlock1 - Basic Select with Blocks that Return", "[codegen]")
{
    ExpectOutput("programs/testSelectBlock1.bismuth");
}

TEST_CASE("programs/testSelectBlock1-fn - Basic Select with Blocks that Return", "[codegen]")
{
    ExpectOutput("programs/testSelectBlock1-fn.bismuth"); 
}

TEST_CASE("programs/test6a (CAFE!) - Basic Nested Selects, LEQ, GEQ", "[codegen]")
{
    ExpectOutput("programs/test6a.bismuth");
}

TEST_CASE("programs/testSelectBlock2 - Select with blocks that don't return", "[codegen]")
{
    // NOTE: Should be same as test6a
    ExpectOutput("programs/testSelectBlock2.bismuth");
}

TEST_CASE("programs/test7 - Test String equality + Nested Loops", "[codegen]")
{
    auto stream = std::fstream("../../programs/test7.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "d205a48dcc3498f6435aa6e5e2016cea7553718a3d6b49d54496f4e579512b34");
}

TEST_CASE("programs/test8 - Nested Loops", "[codegen]")
{
    ExpectOutput("programs/test8.bismuth");
}

TEST_CASE("programs/test11 - Expressions in decl (let*) ", "[codegen]")
{
    ExpectOutput("../../programs/test11.bismuth");
}

TEST_CASE("programs/test12 - Scopes & Prime Finder Example! ", "[codegen]")
{
    ExpectOutput("programs/test12.bismuth");
}

TEST_CASE("programs/test13 - Recursive Fibonacci", "[codegen]")
{
    ExpectOutput("programs/test13.bismuth");
}

TEST_CASE("programs/adv/LambdaDef", "[codegen]")
{
    auto stream = std::fstream("../../programs/adv/LambdaDef.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "a60ff5ce79402ac8fa39f841f6adb74a2373fab9fe979bb950908ecd7c680c0e");
}

TEST_CASE("programs/test-shortcircuit - Basic Short Circuit (and)", "[codegen]")
{
    ExpectOutput("programs/test-shortcircuit.bismuth");
}

TEST_CASE("programs/test-shortcircuit-rt - Basic Short Circuit (and + or) w/ Runtime", "[codegen]")
{
    ExpectOutput("programs/test-shortcircuit-rt.bismuth");
}

TEST_CASE("programs/test-arrayAssign - Assigning one array to another and editing arrays in functions", "[codegen]")
{
    auto stream = std::fstream("../../programs/test-arrayAssign.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "6639eaebf54412bc4221acb7e8c303a5681b0060f3111495c37530e76aa156c0");
}

// FIXME: RENAME AS WE DONT HAVE PROC ANYMORE!
TEST_CASE("programs/externProc - Declaring an external proc", "[codegen]")
{
    ExpectOutput("programs/externProc.bismuth");
}

TEST_CASE("programs/test14a - Test nested/more complex shorting", "[codegen]")
{
    ExpectOutput("programs/test14a.bismuth");
}

TEST_CASE("programs/17 - var inf in decl", "[codegen]")
{
    ExpectOutput("programs/test17.bismuth");
}

TEST_CASE("programs/test18 - Parody", "[codegen]")
{
    auto stream = std::fstream("../../programs/test18.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "7fb3deb5bf652ae42c489488db0bacfb29af9cba521e7edd089dbf44a014a58f");
}

TEST_CASE("programs/Lambda1 - Basic lambda Test", "[codegen][lambda]")
{
    ExpectOutput("programs/Lambda1.bismuth");
}

TEST_CASE("programs/Lambda2 - Basic lambda Test w/ return", "[codegen][lambda]")
{
    ExpectOutput("programs/Lambda2.bismuth");
}

TEST_CASE("programs/Lambda3 - Basic lambda Test w/ return and same name", "[codegen][lambda]")
{
    auto stream = std::fstream("../../programs/Lambda3.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "d3ded95a6887573b51bde92bb60b72bcd625b32b4b7ce4852ab3e2f355576b96");
}

TEST_CASE("programs/externLambda", "[codegen][lambda]")
{
    auto stream = std::fstream("../../programs/externLambda.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "8ebad02a01073b7a0dfcc4ca465a4eef4c1cc404b85b731522e7c517f0e93cf0");
}

TEST_CASE("programs/enum1 - Basic Enum 1", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/enum1.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "02499636cbaee6916dabf3d117d2e0e0de36d12633e4654d1caaf035eecac954");
}

TEST_CASE("programs/enum2 - Basic Enum 2 - double cast", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/enum2.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "5ac261ea03d1be20b7328850b7397b425386f76429af9e1f302df9ebceda4f29");
}

TEST_CASE("programs/enumAssign - Same a  Enum 2 but with assignments outside of decl", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/enumAssign.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "b64fc9cc04f4d992a5bd05f1771132c1d96e1363fd6fe131928d1dc4776744b8");
}

TEST_CASE("programs/enumAssign2 - Returning lambdas, functions, and enums", "[codegen][enum][lambda]")
{
    auto stream = std::fstream("../../programs/enumAssign2.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "2d002078a73da2b21af0b78e6748c07c28f94d382d8010cf8de0c941552e8067");
}

TEST_CASE("programs/enum3", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/enum3.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "92f925b85752b4a4cf423522e1c0441d443d20cb8618df80183ee013286fd0f6");
}

TEST_CASE("programs/adv/StructTest2", "[codegen][struct]")
{
    auto stream = std::fstream("../../programs/adv/StructTest2.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "7598cdc542ab0ab4ba285bd16f629db78eaf386b8fcf2436c2848cf804948c42");
}

TEST_CASE("programs/adv/StructTest3", "[codegen][struct]")
{
    auto stream = std::fstream("../../programs/adv/StructTest3.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "80e210cd119ba7460d24f5bf2d74d039fb9d7d42ecbae4ad4d9e5f7bdae5bede");
}

TEST_CASE("programs/adv/StructTest3a - nested fields", "[codegen][struct]")
{
    auto stream = std::fstream("../../programs/adv/StructTest3a.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "62d9681016ac7b288b71019c5a90f7ee97ea6d960dcad430531441391c70d545");
}

TEST_CASE("programs/adv/StructTest3b - nested fields", "[codegen][struct]")
{
    auto stream = std::fstream("../../programs/adv/StructTest3b.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "6346532262b50983f60de58a0b1b2f876950045fa53ef69c2d712091202b33fa");
}

TEST_CASE("programs/adv/StructTest4", "[codegen][struct]")
{
    auto stream = std::fstream("../../programs/adv/StructTest4.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "1464becd054c0c38fdd00f713b0a11936d78cd4ecbf84f8f2a8ad4210214dcd7");
}

TEST_CASE("programs/adv/NestedEnum", "[codegen][struct]")
{
    auto stream = std::fstream("../../programs/adv/NestedEnum.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "c834c171a67acadce5336face78547a8010cfd283594a31aacf7f3e330f06975");
}

TEST_CASE("programs/dangerLambda-Program - lambdas with duplicate function names", "[codegen][struct]")
{
    ExpectOutput("programs/dangerLambda-Program.bismuth");
}

TEST_CASE("programs/dangerLambda-Lambda - lambdas with duplicate function names", "[codegen][struct]")
{
    auto stream = std::fstream("../../programs/dangerLambda-Lambda.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "c65e79e226d0bb05fce0d467ace5c65dde8241cefdbac45a5bdc97033404ec0b");
}

TEST_CASE("programs/adv/enumPassing - passing non-enum as enum argument", "[codegen][struct]")
{
    auto stream = std::fstream("../../programs/adv/enumPassing.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "9a6147644ed5c0bf801340ff927d2a7d1ba43d01a3c61f0efd951a6e4ff3c542");
}

TEST_CASE("programs/adv/enumPassing-fn - passing non-enum as enum argument", "[codegen][struct]")
{
    auto stream = std::fstream("../../programs/adv/enumPassing-fn.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "5d9e665a2400efcef812c95005f75d146a7ae54b096d560aa41fba5fbfb588e7");
}

TEST_CASE("programs/Lambda2a - More nested lambdas", "[codegen][lambda]")
{
    ExpectOutput("programs/Lambda2a.bismuth");
}

TEST_CASE("programs/adv/enumPassingInf - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    auto stream = std::fstream("../../programs/adv/enumPassingInf.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "411607c66135c0db20b703a58ac28d525e905e0582b233c561dbf92a7a8808fc");
}

TEST_CASE("programs/adv/enumPassingInf-fn - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    auto stream = std::fstream("../../programs/adv/enumPassingInf-fn.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "49f9366ef5d4ac1f8d588431ca9f04a5efe7983959b577c1307416a9134619de");
}

TEST_CASE("programs/Lambda2b - More nested lambdas", "[codegen][struct]")
{
    ExpectOutput("programs/Lambda2b.bismuth");
}

TEST_CASE("Out of order function", "[codegen][program]")
{
    ExpectOutput("programs/ooof.bismuth");
}

TEST_CASE("programs/example", "[codegen][program]")
{
    auto stream = std::fstream("../../programs/example.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "623a79e0098f08b494043d0490a776686c21fb69405c1d795c57efdcb67fc71f");
}

TEST_CASE("programs/SendChannel", "[codegen][linear-types]")
{
    ExpectOutput("programs/SendChannel.bismuth");
}

TEST_CASE("paper/links", "[codegen][linear-types]")
{
    ExpectOutput("paper/links.bismuth");
}

TEST_CASE("paper/links2", "[codegen][linear-types]")
{
    ExpectOutput("paper/links2.bismuth");
}

TEST_CASE("paper/links3", "[codegen][linear-types]")
{
    ExpectOutput("paper/links3.bismuth");
}

TEST_CASE("paper/links4", "[codegen][linear-types]")
{
    ExpectOutput("paper/links4.bismuth");
}

TEST_CASE("programs/doubleArg1c2 - weakening and loops", "[codegen][linear-types]")
{
    ExpectOutput("programs/doubleArg1c2.bismuth");
}

TEST_CASE("programs/enumedit", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/enumedit.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "7c0d836acbadcadc17be9eca1f71a619b8ec1d78ea5567c0d89e40af8d0eea6c");
}

TEST_CASE("programs/TBox - Parody + Clone w/ boxes", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/TBox.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "7dda01623a703aa3f79640e0ba6bec2faea21f744f96f74e95148df60ddea3f0");
}

TEST_CASE("programs/TBox2 - Parody + Clone w/ boxes", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/TBox2.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "56e5e59e9b8b311fe8ff3dd3963f0c5ae91e0e75e316af23c395c1bf5c23d0bf");
}

TEST_CASE("programs/TStruct - Parody + Clone w/ Struct Boxes ", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/TStruct.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "af8ed21ebfd19643aeeeb6a004ae630c5e289089dd0bedef5623447fc52a52cc");
}

TEST_CASE("programs/TStructEnum - Parody + Clone w/ Enum Struct Boxes ", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/TStructEnum.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "60fbf2fed2f03e8f6e81ec206d621f74f21bc21b6b2ef08740129e82664ece6f");
}

TEST_CASE("programs/TStructEnumGC - Parody + Clone w/ Enum Struct Boxes + GC ", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/TStructEnumGC.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "96a659b6844ec3def3b280ab7caff2fda6a8061259d894bfbd983418a7f419e1");
}

TEST_CASE("programs/TArray - Parody + Clone w/ Array", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/TArray.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "bb269027cd553f4685f2ed9dd64f338c76f3f717d28eb0295114f628939f3f28");
}
TEST_CASE("programs/TArray2 - Parody + Clone w/ Array Double box", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/TArray2.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "b5e4f1ac9cc7c02c92b4f0fc81d8389cae81afc84e6578d4fd4e1471dc047f81");
}

TEST_CASE("programs/TStructEnumArray - Parody + Clone w/ Struct Enum Array", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/TStructEnumArray.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "bf8c5292b4531a888f9d4347fa20cf8ea4a675934c5c1cf5d9095935b09553e7");
}

// TEST_CASE("programs/TStructEnumArrayBlock - TStructEnumArray with blocks to mess with control flow", "[codegen][enum]")
// {
//     auto stream = std::fstream("../../programs/TStructEnumArrayBlock.bismuth");
//     EnsureCompilesTo(
//         antlr4::ANTLRInputStream(stream),
//         "c85d7a2abf1cda05652145962a9726294897f757b1332b44aee7f88b3b823d7f");
// }

TEST_CASE("programs/loop - Basic GC with boxes in loops based on example", "[codegen][enum]")
{
    ExpectOutput("programs/loop.bismuth");
}

TEST_CASE("programs/GC-test - Basic GC w/ Send", "[codegen][enum]")
{
    ExpectOutput("programs/GC-test.bismuth");
}

TEST_CASE("programs/TStructGC - Basic GC w/ Send and Structs", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/TStructGC.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "02698fcd137c5a151a46d119d4b4990aed5b8ae6c057348740d5b719bd31e4ed");
}

TEST_CASE("programs/TStructCopy - Basic test of copy", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/TStructCopy.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "d4b33b46f536a4fffc7ec4c959afc5f2cfb46ae0f5a4621365bbf45b1ce47c2a");
}

TEST_CASE("programs/db/db - Basic DB 1", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/db/db.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "45c97eb4fa2367e9855724642d8afe3186ed75b0802e76de57db10923a2aa571");
}

TEST_CASE("programs/db/db2 - Basic DB 2", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/db/db2.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "e57d059dfcbae73f62d7c5a742355a20db54005d4523172b7fe61c3a79e34562");
}

TEST_CASE("programs/db/db3 - Basic DB 3", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/db/db3.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "5d228f4f1b6b018de4da09237788eb4ffba1b405f9a66e4be460d0ace0445f83");
}

TEST_CASE("programs/db/db4 - Basic DB 4", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/db/db4.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "a6d0d53262e7896b7777f51733faf7091acc07b85077a4954ea8613bc2a9f296");
}

TEST_CASE("programs/db/db5-if - Basic DB 5 - AcceptIf", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/db/db5-if.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "6e0efba029366c392b322e4037f15382d3dc10daf8a1c4e85a37623ea46e0201");
}

TEST_CASE("programs/db/db5-if-present - Basic DB 5 - AcceptIf and is_present", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/db/db5-if-present.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "82c23e4480440aa88cff2c8cdff99170b6aaa7d4c47d634a5b1869f9243bdbfc");
}

TEST_CASE("programs/db/db5-if-present-else - Basic DB 5 - AcceptIf with else and is_present", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/db/db5-if-present-else.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "163233f427cd6c2153f09477b9e5f6afc7e7c73999e644843b7561aef519dcd2");
}

TEST_CASE("programs/db/db5-if-present-else-lbl - Basic DB 5 - AcceptIf with else and is_present and labels", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/db/db5-if-present-else-lbl.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "62ac662f518885727443ee48a2aba551bbc79ca95a54e6f1550cef100fcf6f73");
}

TEST_CASE("programs/db/db5-while-present - Basic DB 5 - AcceptWhile and is_present", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/db/db5-while-present.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "f8cd8aab6cffbe4aca4d42c0b88c28ed386ed34ca78bf2eef4f5871e4290b26c");
}

TEST_CASE("programs/db/db-labels - DB with labels to test parsing bug in 1.3.4", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/db/db-labels.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "9787b77cba18eba4a6fe8a1f9efb6686887f57340c869bf4f4204142e652563e");
}

TEST_CASE("programs/bt - Basic Binary Tree", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/bt.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "26c95917b8106115569aec55bc226dc29b5605ab4b56cf8dea6e0db60ee14d5b");
}

TEST_CASE("programs/bt-walker1 - Basic Binary Tree w/ walker", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/bt-walker1.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "a956abe6c8fcda2733589f787521e0eeb150b4448f55cc41af6d39875825090d");
}

TEST_CASE("programs/parity-check - Parity Check 1", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/parity-check.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "72d8705a4883679ad6a164e9b6db709cd85e8bd14de8c39cc8e4fff4cc1470a0");
}

TEST_CASE("programs/parity-check - Parity Check 2", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/parity-check2.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "a5815fbd4e40e4f18ddd6b530c62486d2629c07dff8cf744e80b65dc860ccbc1");
}

TEST_CASE("programs/parity-check - Parity Check 2a", "[codegen][enum]")
{
    auto stream = std::fstream("../../programs/parity-check2a.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "d36b0e1e131e7e5e7a07c06edc1a86b2b51c72380de816ff0a64ed8173752992");
}


TEST_CASE("programs/adder - Add Stream", "[codegen]")
{
    ExpectOutput("programs/adder.bismuth");
}

TEST_CASE("programs/adder2 - Add Stream 2", "[codegen]")
{
    ExpectOutput("programs/adder2.bismuth");
}

TEST_CASE("programs/adder3 - Add Stream 3", "[codegen]")
{
    ExpectOutput("programs/adder3.bismuth");
}

TEST_CASE("programs/adder4 - Add Stream 3 but out of order and higher-order channel", "[codegen]")
{
    ExpectOutput("programs/adder4.bismuth");
}

TEST_CASE("programs/adder5 - Add Stream 4 but using fn that returns linear variable", "[codegen]")
{
    ExpectOutput("programs/adder5.bismuth");
}

TEST_CASE("programs/nested_struct - Definitions within definitions", "[codegen]")
{
    auto stream = std::fstream("../../programs/nested_struct.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "4d7bc765856fb666a703e19901f6e9fc908f3ab26fbe2742df0408acc561fb0a");
}

TEST_CASE("programs/asChannel-int - Convert an int into stream", "[codegen]")
{
    auto stream = std::fstream("../../programs/asChannel-int.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "6a16488e47843b55af7a7bb1e5f29c1e569418f661606df7196f386061763a23");
}

TEST_CASE("programs/asChannel-array - Convert an array into stream", "[codegen]")
{
    auto stream = std::fstream("../../programs/asChannel-array.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "afaa96f5447a3c48adfcb6516a857ed945c764f55ab97f4946b9d4b5a1bc7b26");
}

TEST_CASE("programs/asChannel-channel - Convert regular channel into stream", "[codegen]")
{
    auto stream = std::fstream("../../programs/asChannel-channel.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "5770206895e10c63776ef3a8ff55967347bca9db5b4edb416d158860c75e2775");
}

TEST_CASE("programs/cancelable/BasicCancel - Basic cancel block with two recv", "[codegen][cancel]")
{
    auto stream = std::fstream("../../programs/cancelable/BasicCancel.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "05186fc6f50aef9b513a346c457fd716f9c9705cab9b7ddedc4862637f7aefc7");
}

TEST_CASE("programs/cancelable/DoubleCancel - Basic two blocks with cancel", "[codegen][cancel]")
{
    auto stream = std::fstream("../../programs/cancelable/DoubleCancel.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "e3e782b6a0f263cee293a40c0d415ffa304862d73bc518b39505b0dd68d4207c");
}

TEST_CASE("programs/cancelable/BranchCancel1 - Basic cancel w/ branch and repetition", "[codegen][cancel]")
{
    auto stream = std::fstream("../../programs/cancelable/BranchCancel1.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "76c7229839d3db33e1a6d8bf3912d49f34bcd3155eb39fa23b9ad224cfa1f62c"); // FIXME: QUITE LIMITED & NEEDS IMPROVEMENTS!
}

TEST_CASE("programs/BasicForLoop - Basic For loop ", "[codegen][cancel]")
{
    auto stream = std::fstream("../../programs/BasicForLoop.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "66ee44669728ed700a85a9823f2f240afc64262fbd08ec2f8c4abda6b22d52dd"); // FIXME: QUITE LIMITED & NEEDS IMPROVEMENTS!
}

TEST_CASE("programs/generics/Arrays - Non-recursive generic function used for dyn array utils", "[codegen][generic]")
{
    auto stream = std::fstream("../../programs/generics/Arrays.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "d5dc0ab70f918d87d7731c99eb149c639b64c25a34ff954c9c2fe3c2e1b19a12"); 
}


TEST_CASE("programs/generics/inv - Various generic functions including nested", "[codegen][generic]")
{
    auto stream = std::fstream("../../programs/generics/inv.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "6120dbb49139880092cc6c60e0db4100982b75a9fcc3a6b875d19830059f4b3c"); 
}

TEST_CASE("programs/generics/Lists - Various complex generic structures including recursive", "[codegen][generic]")
{
    auto stream = std::fstream("../../programs/generics/Lists.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "63f891cda9e80a7e41e577b84490171356854c84ea531882a783d0671ad23c11"); 
}

TEST_CASE("programs/generics/Optional - Optional as a means to test templated sum type", "[codegen][generic]")
{
    auto stream = std::fstream("../../programs/generics/Optional.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "406731ff15472ffc3c9e9dd71d9d08e08985de0fddc219018fc2de59e094bf1c"); 
}

TEST_CASE("programs/generics/recfunctemplate - Recursive templated functions", "[codegen][generic]")
{
    auto stream = std::fstream("../../programs/generics/recfunctemplate.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "0ce78bb4b0b746a703d869cd97d4d02f6e1bd2e723a6b79ed21022c94983c70d"); 
}

TEST_CASE("programs/generics/ReferenceGeneric - Co-dependent structs", "[codegen][generic]")
{
    auto stream = std::fstream("../../programs/generics/ReferenceGeneric.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "7632d226bf1087a674e91b6e4f8765f9ffc86e14ef2f57a533ccdad04904e7d9"); 
}


TEST_CASE("programs/generics/ReferenceGenericS - Co-dependent structs", "[codegen][generic]")
{
    auto stream = std::fstream("../../programs/generics/ReferenceGenericS.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "950b9c5cf40bd673a8250726ae932b20089332f552fae683d85a402f471e054c"); 
}

TEST_CASE("programs/generics/GenericProg - Generic Program", "[codegen][generic]")
{
    auto stream = std::fstream("../../programs/generics/GenericProg.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        "4d1e7ff027a665ed171e1e338f9a1d2e3fe0c972b854219acf505a7b5670c86c"); 
}


TEST_CASE("programs/inferint - Infer the type of a number", "[codegen][infer integers]")
{
    // TODO: technically we should do this as a semantic test---just to be sure
    ExpectOutput("programs/inferint.bismuth");
}


TEST_CASE("programs/cursed - Binary Operators, Functions with inferred returns, and inference of ints through array matching", "[codegen]")
{
    std::string hash = "d1358a7bd97341b3c542f1fefab2147c0df9d9a9acabe488912f09454009ff19";
    auto stream = std::fstream("../../programs/cursed/cursed.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream),
        hash); 

    auto stream2 = std::fstream("../../programs/cursed/cursed-no-ret.bismuth");
    EnsureCompilesTo(
        antlr4::ANTLRInputStream(stream2),
        hash);
}

/************************************
 * Example C-Level Tests
 ************************************/
TEST_CASE("C Level Positive Test #2", "[codegen]")
{
    ExpectOutput("programs/CLevel/CPositive2.bismuth");
}

/************************************
 * Example B-Level Tests
 ************************************/
TEST_CASE("B Level Positive Test #1", "[codegen]")
{
    ExpectOutput("programs/BLevel/BPositive1.bismuth");
}

TEST_CASE("B Level Positive Test #2", "[codegen]")
{
    ExpectOutput("programs/BLevel/BPositive2.bismuth");
}

/************************************
 * Example A-Level Tests
 ************************************/
TEST_CASE("A Level Positive Test #1", "[codegen]")
{
    ExpectOutput("programs/ALevel/APositive1.bismuth");
}

TEST_CASE("A Level Positive Test #2 - If", "[codegen]")
{
    ExpectOutput("programs/ALevel/APositive2.bismuth");
}

TEST_CASE("A Level Positive Test #3 - Select", "[codegen]")
{
    ExpectOutput("../../programs/ALevel/APositive3.bismuth");
}
