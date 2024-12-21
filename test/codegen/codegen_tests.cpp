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
    ExpectOutput("programs/test1.bismuth");
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
    ExpectOutput("programs/test7.bismuth");
}

TEST_CASE("programs/test8 - Nested Loops", "[codegen]")
{
    ExpectOutput("programs/test8.bismuth");
}

TEST_CASE("programs/test11 - Expressions in decl (let*) ", "[codegen]")
{
    ExpectOutput("programs/test11.bismuth");
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
    ExpectOutput("programs/adv/LambdaDef.bismuth");
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
    ExpectOutput("programs/test-arrayAssign.bismuth");
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
    ExpectOutput("programs/test18.bismuth");
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
    ExpectOutput("programs/Lambda3.bismuth");
}

TEST_CASE("programs/externLambda", "[codegen][lambda]")
{
    ExpectOutput("programs/externLambda.bismuth");
}

TEST_CASE("programs/enum1 - Basic Enum 1", "[codegen][enum]")
{
    ExpectOutput("programs/enum1.bismuth");
}

TEST_CASE("programs/enum2 - Basic Enum 2 - double cast", "[codegen][enum]")
{
    ExpectOutput("programs/enum2.bismuth");
}

TEST_CASE("programs/enumAssign - Same a  Enum 2 but with assignments outside of decl", "[codegen][enum]")
{
    ExpectOutput("programs/enumAssign.bismuth");
}

TEST_CASE("programs/enumAssign2 - Returning lambdas, functions, and enums", "[codegen][enum][lambda]")
{
    ExpectOutput("programs/enumAssign2.bismuth");;
}

TEST_CASE("programs/enum3", "[codegen][enum]")
{
    ExpectOutput("programs/enum3.bismuth");
}

TEST_CASE("programs/adv/StructTest2", "[codegen][struct]")
{
    ExpectOutput("programs/adv/StructTest2.bismuth");
}

TEST_CASE("programs/adv/StructTest3", "[codegen][struct]")
{
    ExpectOutput("programs/adv/StructTest3.bismuth");
}

TEST_CASE("programs/adv/StructTest3a - nested fields", "[codegen][struct]")
{
    ExpectOutput("programs/adv/StructTest3a.bismuth");
}

TEST_CASE("programs/adv/StructTest3b - nested fields", "[codegen][struct]")
{
    ExpectOutput("programs/adv/StructTest3b.bismuth");
}

TEST_CASE("programs/adv/StructTest4", "[codegen][struct]")
{
    ExpectOutput("programs/adv/StructTest4.bismuth");
}

TEST_CASE("programs/adv/NestedEnum", "[codegen][struct]")
{
    ExpectOutput("programs/adv/NestedEnum.bismuth");
}

TEST_CASE("programs/dangerLambda-Program - lambdas with duplicate function names", "[codegen][struct]")
{
    ExpectOutput("programs/dangerLambda-Program.bismuth");
}

TEST_CASE("programs/dangerLambda-Lambda - lambdas with duplicate function names", "[codegen][struct]")
{
    ExpectOutput("programs/dangerLambda-Lambda.bismuth");
}

TEST_CASE("programs/adv/enumPassing - passing non-enum as enum argument", "[codegen][struct]")
{
    ExpectOutput("programs/adv/enumPassing.bismuth");
}

TEST_CASE("programs/adv/enumPassing-fn - passing non-enum as enum argument", "[codegen][struct]")
{
    ExpectOutput("programs/adv/enumPassing-fn.bismuth");
}

TEST_CASE("programs/Lambda2a - More nested lambdas", "[codegen][lambda]")
{
    ExpectOutput("programs/Lambda2a.bismuth");
}

TEST_CASE("programs/adv/enumPassingInf - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    ExpectOutput("programs/adv/enumPassingInf.bismuth");
}

TEST_CASE("programs/adv/enumPassingInf-fn - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    ExpectOutput("programs/adv/enumPassingInf-fn.bismuth");
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
    ExpectOutput("programs/example.bismuth");
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
    ExpectOutput("programs/enumedit.bismuth");
}

TEST_CASE("programs/TBox - Parody + Clone w/ boxes", "[codegen][enum]")
{
    ExpectOutput("programs/TBox.bismuth");
}

TEST_CASE("programs/TBox2 - Parody + Clone w/ boxes", "[codegen][enum]")
{
    ExpectOutput("programs/TBox2.bismuth");
}

TEST_CASE("programs/TStruct - Parody + Clone w/ Struct Boxes ", "[codegen][enum]")
{
    ExpectOutput("programs/TStruct.bismuth");
}

TEST_CASE("programs/TStructEnum - Parody + Clone w/ Enum Struct Boxes ", "[codegen][enum]")
{
    ExpectOutput("programs/TStructEnum.bismuth");
}

TEST_CASE("programs/TStructEnumGC - Parody + Clone w/ Enum Struct Boxes + GC ", "[codegen][enum]")
{
    ExpectOutput("programs/TStructEnumGC.bismuth");
}

TEST_CASE("programs/TArray - Parody + Clone w/ Array", "[codegen][enum]")
{
    ExpectOutput("programs/TArray.bismuth");
}
TEST_CASE("programs/TArray2 - Parody + Clone w/ Array Double box", "[codegen][enum]")
{
    ExpectOutput("programs/TArray2.bismuth");
}

TEST_CASE("programs/TStructEnumArray - Parody + Clone w/ Struct Enum Array", "[codegen][enum]")
{
    ExpectOutput("programs/TStructEnumArray.bismuth");
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
    ExpectOutput("programs/TStructGC.bismuth");
}

TEST_CASE("programs/TStructCopy - Basic test of copy", "[codegen][enum]")
{
    ExpectOutput("programs/TStructCopy.bismuth");
}

TEST_CASE("programs/db/db - Basic DB 1", "[codegen][enum]")
{
    ExpectOutput("programs/db/db.bismuth");
}

TEST_CASE("programs/db/db2 - Basic DB 2", "[codegen][enum]")
{
    ExpectOutput("programs/db/db2.bismuth");
}

TEST_CASE("programs/db/db3 - Basic DB 3", "[codegen][enum]")
{
    ExpectOutput("programs/db/db3.bismuth");
}

TEST_CASE("programs/db/db4 - Basic DB 4", "[codegen][enum]")
{
    ExpectOutput("programs/db/db4.bismuth");
}

TEST_CASE("programs/db/db5-if - Basic DB 5 - AcceptIf", "[codegen][enum]")
{
    ExpectOutput("programs/db/db5-if.bismuth");
}

TEST_CASE("programs/db/db5-if-present - Basic DB 5 - AcceptIf and is_present", "[codegen][enum]")
{
    ExpectOutput("programs/db/db5-if-present.bismuth");
}

TEST_CASE("programs/db/db5-if-present-else - Basic DB 5 - AcceptIf with else and is_present", "[codegen][enum]")
{
    ExpectOutput("programs/db/db5-if-present-else.bismuth");
}

TEST_CASE("programs/db/db5-if-present-else-lbl - Basic DB 5 - AcceptIf with else and is_present and labels", "[codegen][enum]")
{
    ExpectOutput("programs/db/db5-if-present-else-lbl.bismuth");
}

TEST_CASE("programs/db/db5-while-present - Basic DB 5 - AcceptWhile and is_present", "[codegen][enum]")
{
    ExpectOutput("programs/db/db5-while-present.bismuth");
}

TEST_CASE("programs/db/db-labels - DB with labels to test parsing bug in 1.3.4", "[codegen][enum]")
{
    ExpectOutput("programs/db/db-labels.bismuth");
}

TEST_CASE("programs/bt - Basic Binary Tree", "[codegen][enum]")
{
    ExpectOutput("programs/bt.bismuth");
}

TEST_CASE("programs/bt-walker1 - Basic Binary Tree w/ walker", "[codegen][enum]")
{
    ExpectOutput("programs/bt-walker1.bismuth");
}

TEST_CASE("programs/parity-check - Parity Check 1", "[codegen][enum]")
{
    ExpectOutput("programs/parity-check.bismuth");
}

TEST_CASE("programs/parity-check - Parity Check 2", "[codegen][enum]")
{
    ExpectOutput("programs/parity-check2.bismuth");
}

TEST_CASE("programs/parity-check - Parity Check 2a", "[codegen][enum]")
{
    ExpectOutput("programs/parity-check2a.bismuth");
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
    ExpectOutput("programs/nested_struct.bismuth");
}

TEST_CASE("programs/asChannel-int - Convert an int into stream", "[codegen]")
{
    ExpectOutput("programs/asChannel-int.bismuth");
}

TEST_CASE("programs/asChannel-array - Convert an array into stream", "[codegen]")
{
    ExpectOutput("programs/asChannel-array.bismuth");
}

TEST_CASE("programs/asChannel-channel - Convert regular channel into stream", "[codegen]")
{
    ExpectOutput("programs/asChannel-channel.bismuth");
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
    ExpectOutput("programs/BasicForLoop.bismuth");
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
    ExpectOutput("programs/generics/Lists.bismuth");
}

TEST_CASE("programs/generics/Optional - Optional as a means to test templated sum type", "[codegen][generic]")
{
    ExpectOutput("programs/generics/Optional.bismuth");
}

TEST_CASE("programs/generics/recfunctemplate - Recursive templated functions", "[codegen][generic]")
{
    ExpectOutput("programs/generics/recfunctemplate.bismuth");
}

TEST_CASE("programs/generics/ReferenceGeneric - Co-dependent structs", "[codegen][generic]")
{
    ExpectOutput("programs/generics/ReferenceGeneric.bismuth");
}


TEST_CASE("programs/generics/ReferenceGenericS - Co-dependent structs", "[codegen][generic]")
{
    ExpectOutput("programs/generics/ReferenceGenericS.bismuth");
}

TEST_CASE("programs/generics/GenericProg - Generic Program", "[codegen][generic]")
{
    ExpectOutput("programs/generics/GenericProg.bismuth");
}


TEST_CASE("programs/inferint - Infer the type of a number", "[codegen][infer integers]")
{
    // TODO: technically we should do this as a semantic test---just to be sure
    ExpectOutput("programs/inferint.bismuth");
}


TEST_CASE("programs/cursed - Binary Operators, Functions with inferred returns, and inference of ints through array matching", "[codegen]")
{
    ExpectOutput("programs/cursed/cursed.bismuth");
    ExpectOutput("programs/cursed/cursed-no-ret.bismuth");
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
    ExpectOutput("programs/ALevel/APositive3.bismuth");
}
