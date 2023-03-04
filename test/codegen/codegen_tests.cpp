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
        "415be2ce27e73540b328ab05f7d987706b1bc7305d6b2dd5e70555781aaf6987");
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
        "af53832c31eaf8652ac114582dd868d13e74927762f4af2f1d400afc3a5d59a4");
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
        "2992d3f3809c2abb3bcf1132fca191f04243979b8da9f8c87064397bdbcbe9bf");
}

TEST_CASE("programs/test5 - Nested ifs and if equality", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test5.prism"))),
        "622869192aca287b5ae72b5405dc9770d270da8b0e891f64dc11bc02d80b708d");
}

TEST_CASE("programs/test6 - Basic Select with Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test6.prism"))),
        "e1158cff65c37995d9ba1c00dd10791482ca277cf642ae487698aa956214b675");
}

TEST_CASE("programs/testSelectBlock1 - Basic Select with Blocks that Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock1.prism"))),
        "51b4dfed1451e17d3eae47007c4a244df5ab15bba7e6c4628c373ec0c69790f5");
}

TEST_CASE("programs/testSelectBlock1-fn - Basic Select with Blocks that Return", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock1-fn.prism"))),
        "b6e15986faeb5f829c3ed521cc3cf1f3cd372a494e0fd22dc44f327dce461308");
}

TEST_CASE("programs/test6a (CAFE!) - Basic Nested Selects, LEQ, GEQ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test6a.prism"))),
        "b3db6d234feea09d25c09cda9211d844a8469268b94d209b54a66ee1fda70f21");//"cafe2b3e17335a03444e7c3e1be095eaea8cb901741e8c0d8f1f79a17a8fe6c4");
}

TEST_CASE("programs/testSelectBlock2 - Select with blocks that don't return", "[codegen]")
{
    // NOTE: Should be same as test6a
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/testSelectBlock2.prism"))),
        "1459d21fe2cb8fa1058424bea5ef3be3a1a1dd4d97dc2561a4597221f8b8d408");
}

TEST_CASE("programs/test7 - Test String equality + Nested Loops", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test7.prism"))),
        "da940a5f52f7aa5fc7c39c6c413bac2e53263fc70fa0ca829e794f53145be5c3");
}

TEST_CASE("programs/test8 - Nested Loops", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test8.prism"))),
        "d92d22dac1a93253c939b39f15e4424852e938deb63fa15d86f952b3952b2172");
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
        "59d7588c8b4be0b964dca8e16cb9d9789044d55725b38194be0c484ebad3c481");
}

TEST_CASE("programs/test12 - Scopes & Prime Finder Example! ", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test12.prism"))),
        "e0bff826a7faf334b6b7f2a18bb043ac9cb8fa0fa9ffc119d620ccaedf18848d");
}

TEST_CASE("programs/test13 - Recursive Fibonacci", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test13.prism"))),
        "41f8f39372b13576d98fe0046731194085a7ef2f7f8ab9704ed6ef478ef1f95f");
}

TEST_CASE("programs/adv/LambdaDef", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/LambdaDef.prism"))),
        "cd84f09094e376bd739dfc717c9238432519acf5ef516fcf83043929b0dc7f79");
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
        "73a4dd9e35e5661231a84fe837b788a8c34ac29627383363586e7d29d4475e43");
}

TEST_CASE("programs/test-shortcircuit-rt - Basic Short Circuit (and + or) w/ Runtime", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-shortcircuit-rt.prism"))),
        "4e05ae4967e419d953ab239aff7559813b44a1ae6498d790ea38c88e2edb4900");
}

TEST_CASE("programs/test-arrayAssign - Assigning one array to another and editing arrays in functions", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test-arrayAssign.prism"))),
        "e29a5085d61a320b84053092f1f4f35e6116cf558dc537c026c12683311daf51");
}

TEST_CASE("programs/externProc - Declaring an external proc", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/externProc.prism"))),
        "3b6a1ebaa5528806093451a07b8534d689f61c7e8ee73ce1f326eee723e74138");
}

TEST_CASE("programs/test14a - Test nested/more complex shorting", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test14a.prism"))),
        "f638bd6436bc260b4c76f483a3e0f8e3199a45e09ebed0cdca9f35b235f0978a");
}

TEST_CASE("programs/test18 - Parody", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/test18.prism"))),
        "ce3e033ecc420dd2358792f7a0aa6da05f68f531d383febaf066612ecb8861ad");
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
        "63c45fdcadce7ce1f1ffc831c02b48ca69b9534f052aa70a335f4fff177058c4");
}

TEST_CASE("programs/Lambda2 - Basic lambda Test w/ return", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2.prism"))),
        "3bf49ea90712b5d059cf6656f023e5ac15bef128c6efb9e6921089022b48fbaf");
}

TEST_CASE("programs/Lambda3 - Basic lambda Test w/ return and same name", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda3.prism"))),
        "1d39ca927685e22ac7b14e3f3c46b5eff92b92bb979c9a4448cf46b13446afa3");
}

TEST_CASE("programs/externLambda", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/externLambda.prism"))),
        "1b3ccc3e68c565ccd812d37d4b2841bf9fd801fcb8f28c49de58bcf8f47babdc");
}

TEST_CASE("programs/enum1 - Basic Enum 1", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum1.prism"))),
        "a42b57453552706aad51cd5830bd3d0b3b6e84aa19ac27a432450dd88c87ff13");
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
        "bd241994232085c70b063764d3a4748aadab357216cef4374c0bca33c0e20a6b");
}

TEST_CASE("programs/enumAssign2 - Returning lambdas, functions, and enums", "[codegen][enum][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumAssign2.prism"))),
        "e262d62d5c1ef840d184fcb6cd525a88c98cb3ebfe36d1cd5a81c42bb2cecb00");
}

TEST_CASE("programs/enum3", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enum3.prism"))),
        "36260f88b385f071d2838b2f743413af7363ff39238aadce412f5fe88cc43dfa");
}

TEST_CASE("programs/adv/StructTest2", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest2.prism"))),
        "8bb35ff9c2fd1fea53b4368ce5bf3c10a11174d38bd15f88800c6ac42ca577f4");
}

TEST_CASE("programs/adv/StructTest3", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3.prism"))),
        "cd01f43c830e5343e0b17200324158d90dd32e13efed9e435692ed94aea233c8");
}

TEST_CASE("programs/adv/StructTest3a - nested fields", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3a.prism"))),
        "db29deb7800a9bfdace39ff48c3d6b48252173a9770808b05b7f7593c24fb015");
}

TEST_CASE("programs/adv/StructTest3b - nested fields", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest3b.prism"))),
        "a0a030b79819269512d50f562ff4b29b7a165760dc9b10c053157c811b145784");
}

TEST_CASE("programs/adv/StructTest4", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/StructTest4.prism"))),
        "32631bd5eea0649ee8a09a99716afa02fa1121e8c084180cdc86af8c5b307427");
}

TEST_CASE("programs/adv/NestedEnum", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/NestedEnum.prism"))),
        "99bfc25c5c7fe842c5cbd0078ffc9a3507eebe1cdc458c086df5ca43db7b3e96");
}

TEST_CASE("programs/dangerLambda-Program - lambdas with dupl function names", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/dangerLambda-Program.prism"))),
        "9a70c6533dbb16365eb5baae2f19ff89fc72e2de44ad88df875a9d647c3089c1");
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
        "606306c66c12b0de47a94eb01db9718f6916e21007cf02724d054b39386174cd");
}

TEST_CASE("programs/adv/enumPassing-fn - passing non-enum as enum argument", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassing-fn.prism"))),
        "2ffb92824d162035e66080ba3bc59e8c4994029ef24d26700a54e6a59df8c979");
}

TEST_CASE("programs/Lambda2a - More nested lambdas", "[codegen][lambda]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2a.prism"))),
        "16cc65827ceb397bc0f1c99af418dc81a37b78df96de4c85408d07271881d816");
}

TEST_CASE("programs/adv/enumPassingInf - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassingInf.prism"))),
        "6cd54c06e5bc45fe0dd70e5276341fca0934a4a0f11b1c6a2d0d01f373897b3d");
}

TEST_CASE("programs/adv/enumPassingInf-fn - Enum passing with Type Inference", "[codegen][enum][type-inf]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/adv/enumPassingInf-fn.prism"))),
        "1e22662e7fd9c5ecbf2a13cda93a221c26fed21d855d5c9c6d0971cd9c50d64f");
}

TEST_CASE("programs/Lambda2b - More nested lambdas", "[codegen][struct]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/Lambda2b.prism"))),
        "d316878e4f8ee8ca29be1e7e28c1c5f71090080e4b97cec8fcdeaaa39b3e795a");
}

TEST_CASE("Out of order function", "[codegen][program]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ooof.prism"))),
        "666f41868e4c247efc9209510c4307b49702ce9d967cbe7e9c6858b6ad63cfb8");

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
        "1c071c51694d1c57e85d55bd484b651cbb1cad3d417841b2441844405afd82cf");
}

TEST_CASE("programs/SendChannel", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/SendChannel.prism"))),
        "57b73830c46f97a2aac3c55036681eef24384ed6210a9560c50326c742d72f78");
}

TEST_CASE("paper/links", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links.prism"))),
        "8afbf3ea9b748a97e9434264b250191f27f356f9498266341d06cf1cc2ee143f");
}

TEST_CASE("paper/links2", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links2.prism"))),
        "152aaf8ee2c7f3401e73cf85baa578e6a66707710df60ca4bf4a1ca9c13296e8");
}

TEST_CASE("paper/links3", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links3.prism"))),
        "1afbc3347fc948b2c93d894a8d57206d67572fe5ace6121b5cc5f6859344995e");
}

TEST_CASE("paper/links4", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/paper/links4.prism"))),
        "5b7a1cd44234ce005ff1610fec15d8c68bd676df2fccb52cbb0ebf166ad28653");
}

TEST_CASE("programs/doubleArg1c2 - weakening and loops", "[codegen][linear-types]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/doubleArg1c2.prism"))),
        "8bc18d76e13d127eaf3bc1bc3da646bbe2268ebf7148223ed769a6f500b40b46");
}

TEST_CASE("programs/enumedit", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/enumedit.prism"))),
        "88c1cc1075d8c0b562697ad3b2dd060d9e67fd49753e48913112642b01fc19f3");
}

TEST_CASE("programs/TBox - Parody + Clone w/ boxes", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TBox.prism"))),
        "274bb2bba6c91dbc24790bcdc4e35a520aea784ade07e8560cf79b19594a339c");
}

TEST_CASE("programs/TStruct - Parody + Clone w/ Struct Boxes ", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStruct.prism"))),
        "baf6e007ca836ec49afaafeec76b993d06242e166d06d807f3c5ddce8eeb2053");
}

TEST_CASE("programs/TStructEnum - Parody + Clone w/ Enum Struct Boxes ", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructEnum.prism"))),
        "9cf823c8fe1ffb661f72a5d54a20da85f3142ebe753138c3233d2230e35b4e87");
}

TEST_CASE("programs/loop - Basic GC with boxes in loops based on example", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/loop.prism"))),
        "b1d81501ea0b2158489a3905a3f185d8c9ac43088f9681e80ae6c9768c5396d2");
}

// TEST_CASE("programs/loop - Basic GC with boxes in loops based on example", "[codegen][enum]")
// {
//     EnsureCompilesTo(
//         new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/loop.prism"))),
//         "b1d81501ea0b2158489a3905a3f185d8c9ac43088f9681e80ae6c9768c5396d2");
// }

TEST_CASE("programs/GC-test - Basic GC w/ Send", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/GC-test.prism"))),
        "c738317d75486cc6ebb892ccea8de93f8dff561a1cb41b2e01c59c26fb847d2d");
}

TEST_CASE("programs/TStructGC - Basic GC w/ Send and Structs", "[codegen][enum]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/TStructGC.prism"))),
        "b57b7dc794ffaee50b9ad0c2c0a041e3c3d959c19c0a30ce67330719024316c4");
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
        "8ed8362341e3ade5afb69cbdd17869ac2ba012c355ff997ffd064647fa26f6ff");
}

/************************************
 * Example B-Level Tests
 ************************************/
TEST_CASE("B Level Positive Test #1", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/BLevel/BPositive1.prism"))),
        "c4cce320f9b1cba817e830e9e34b90db6aa651a2f7021f2483d495c64e5060bb");
}

TEST_CASE("B Level Positive Test #2", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/BLevel/BPositive2.prism"))),
        "66804c0cff90330168e1c72b4c761e5d6fee8bd6249a71cc86dd8fc4fb9999ad");
}

/************************************
 * Example A-Level Tests
 ************************************/
TEST_CASE("A Level Positive Test #1", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive1.prism"))),
        "7a0d3342785b78cffa33ad1c1bbbecd7bd7367463705b97a0bc3a831d732f899");
}

TEST_CASE("A Level Positive Test #2 - If", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive2.prism"))),
        "ecfc5bb3a1c80dfbb6a081db21981d480c5bc8a7554ea97c1b448bfa32873279");
}

TEST_CASE("A Level Positive Test #3 - Select", "[codegen]")
{
    EnsureCompilesTo(
        new antlr4::ANTLRInputStream(*(new std::fstream("/home/shared/programs/ALevel/APositive3.prism"))),
        "3e4bbb78e55db74faabe73e8cfc7ac1d99ebbdb47db4709ea202dea539fa7206");
}
