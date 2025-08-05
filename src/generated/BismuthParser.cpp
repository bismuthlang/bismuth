
// Generated from Bismuth.g4 by ANTLR 4.10.1


#include "BismuthListener.h"
#include "BismuthVisitor.h"

#include "BismuthParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct BismuthParserStaticData final {
  BismuthParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  BismuthParserStaticData(const BismuthParserStaticData&) = delete;
  BismuthParserStaticData(BismuthParserStaticData&&) = delete;
  BismuthParserStaticData& operator=(const BismuthParserStaticData&) = delete;
  BismuthParserStaticData& operator=(BismuthParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag bismuthParserOnceFlag;
BismuthParserStaticData *bismuthParserStaticData = nullptr;

void bismuthParserInitialize() {
  assert(bismuthParserStaticData == nullptr);
  auto staticData = std::make_unique<BismuthParserStaticData>(
    std::vector<std::string>{
      "compilationUnit", "structCase", "traitEntry", "genericTemplate", 
      "genericEntry", "genericSpecifier", "defineType", "inherentTraitSpec", 
      "externStatement", "pathElement", "path", "importStatement", "inv_args", 
      "expression", "lambdaConstExpr", "block", "condition", "selectAlternative", 
      "matchAlternative", "protoAlternative", "protoElse", "parameterList", 
      "parameter", "assignment", "statement", "assignmentStatement", "variableDeclaration", 
      "shiftOp", "typeOrVar", "protocol", "subProtocol", "protoBranch", 
      "type", "integerValue", "booleanConst"
    },
    std::vector<std::string>{
      "", "'Session'", "'::'", "'='", "'as'", "'.'", "'::init'", "'.recv'", 
      "'.is_present'", "'asChannel'", "'=>'", "'skip'", "'.send'", "'for'", 
      "'.case'", "'offer'", "'more'", "'unfold'", "'weaken'", "'accept'", 
      "'acceptWhile'", "'acceptIf'", "'close'", "'cancel'", "'\\u003F'", 
      "", "':='", "'-'", "'!'", "'*'", "'/'", "'%'", "'+'", "'<'", "'<='", 
      "'>='", "'>'", "'=='", "'!='", "'~'", "'&'", "'|'", "'&&'", "'||'", 
      "'^'", "'->'", "'('", "')'", "'['", "']'", "'{'", "'}'", "';'", "':'", 
      "'\"'", "','", "'...'", "", "", "", "'int'", "'i32'", "'u32'", "'i64'", 
      "'u64'", "'boolean'", "'str'", "'Unit'", "'var'", "'Box'", "'Program'", 
      "'Channel'", "'prog'", "'func'", "'enum'", "'struct'", "'if'", "'else'", 
      "'while'", "'return'", "'select'", "'extern'", "'match'", "'define'", 
      "'exit'", "'exec'", "'copy'", "'import'", "'trait'", "'impl'", "'auto'", 
      "'impls'", "'ExternalChoice'", "'InternalChoice'", "'Cancelable'", 
      "'false'", "'true'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "VariadicParam", "ASSIGN", "MINUS", 
      "NOT", "MULTIPLY", "DIVIDE", "MOD", "PLUS", "LESS", "LESS_EQ", "GREATER_EQ", 
      "GREATER", "EQUAL", "NOT_EQUAL", "BIT_NOT", "BIT_AND", "BIT_OR", "LOG_AND", 
      "LOG_OR", "BIT_XOR", "MAPS_TO", "LPAR", "RPAR", "LBRC", "RBRC", "LSQB", 
      "RSQB", "SEMICOLON", "COLON", "QUOTE", "COMMA", "ELLIPSIS", "DEC_LITERAL", 
      "HEX_LITERAL", "BIN_LITERAL", "TYPE_INT", "TYPE_I32", "TYPE_U32", 
      "TYPE_I64", "TYPE_U64", "TYPE_BOOL", "TYPE_STR", "TYPE_UNIT", "TYPE_VAR", 
      "TYPE_BOX", "TYPE_PROGRAM", "TYPE_CHANNEL", "PROG", "FUNC", "ENUM", 
      "STRUCT", "IF", "ELSE", "WHILE", "RETURN", "SELECT", "EXTERN", "MATCH", 
      "DEFINE", "EXIT", "EXEC", "COPY", "IMPORT", "TRAIT", "IMPL", "AUTO", 
      "IMPLS", "EXTERNAL_CHOICE", "INTERNAL_CHOICE", "CLOSEABLE", "FALSE", 
      "TRUE", "STRING", "VARIABLE", "INLINE_COMMENT", "STD_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,101,882,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,1,0,1,
  	0,1,0,5,0,74,8,0,10,0,12,0,77,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,2,1,2,
  	1,2,1,3,1,3,1,3,1,3,5,3,93,8,3,10,3,12,3,96,9,3,1,3,1,3,1,4,1,4,1,4,1,
  	4,1,4,5,4,105,8,4,10,4,12,4,108,9,4,3,4,110,8,4,1,4,1,4,3,4,114,8,4,1,
  	5,1,5,1,5,1,5,5,5,120,8,5,10,5,12,5,123,9,5,1,5,1,5,1,6,1,6,1,6,3,6,130,
  	8,6,1,6,1,6,1,6,1,6,4,6,136,8,6,11,6,12,6,137,1,6,1,6,1,6,1,6,1,6,3,6,
  	145,8,6,1,6,1,6,5,6,149,8,6,10,6,12,6,152,9,6,1,6,1,6,3,6,156,8,6,1,6,
  	1,6,1,6,3,6,161,8,6,1,6,1,6,1,6,1,6,1,6,3,6,168,8,6,1,6,1,6,1,6,1,6,1,
  	6,3,6,175,8,6,1,6,1,6,1,6,1,6,3,6,181,8,6,1,6,1,6,5,6,185,8,6,10,6,12,
  	6,188,9,6,1,6,3,6,191,8,6,1,7,1,7,1,7,3,7,196,8,7,1,7,1,7,4,7,200,8,7,
  	11,7,12,7,201,1,8,1,8,1,8,1,8,1,8,1,8,3,8,210,8,8,1,8,3,8,213,8,8,1,8,
  	1,8,1,8,3,8,218,8,8,1,8,1,8,1,9,1,9,3,9,224,8,9,1,10,1,10,1,10,5,10,229,
  	8,10,10,10,12,10,232,9,10,1,11,1,11,1,11,1,11,3,11,238,8,11,1,11,3,11,
  	241,8,11,1,12,1,12,1,12,1,12,5,12,247,8,12,10,12,12,12,250,9,12,3,12,
  	252,8,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,5,13,
  	265,8,13,10,13,12,13,268,9,13,1,13,3,13,271,8,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,5,13,284,8,13,10,13,12,13,287,9,13,
  	3,13,289,8,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	3,13,330,8,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,4,13,361,8,13,11,13,12,13,362,1,13,1,13,1,13,4,13,
  	368,8,13,11,13,12,13,369,1,13,1,13,1,13,4,13,375,8,13,11,13,12,13,376,
  	5,13,379,8,13,10,13,12,13,382,9,13,1,14,1,14,1,14,1,14,1,14,3,14,389,
  	8,14,1,14,1,14,1,15,1,15,5,15,395,8,15,10,15,12,15,398,9,15,1,15,1,15,
  	1,16,1,16,1,16,1,16,1,16,3,16,407,8,16,1,17,1,17,1,17,1,17,1,18,1,18,
  	1,18,1,18,1,18,1,19,1,19,3,19,420,8,19,1,19,1,19,1,19,1,20,1,20,1,20,
  	1,20,1,21,1,21,1,21,5,21,432,8,21,10,21,12,21,435,9,21,3,21,437,8,21,
  	1,22,1,22,1,22,1,23,1,23,1,23,5,23,445,8,23,10,23,12,23,448,9,23,1,23,
  	1,23,3,23,452,8,23,1,24,1,24,1,24,3,24,457,8,24,1,24,1,24,3,24,461,8,
  	24,1,24,1,24,1,24,1,24,1,24,3,24,468,8,24,1,24,5,24,471,8,24,10,24,12,
  	24,474,9,24,1,24,1,24,1,24,5,24,479,8,24,10,24,12,24,482,9,24,1,24,1,
  	24,5,24,486,8,24,10,24,12,24,489,9,24,1,24,1,24,1,24,1,24,5,24,495,8,
  	24,10,24,12,24,498,9,24,1,24,1,24,5,24,502,8,24,10,24,12,24,505,9,24,
  	1,24,1,24,1,24,1,24,5,24,511,8,24,10,24,12,24,514,9,24,1,24,5,24,517,
  	8,24,10,24,12,24,520,9,24,1,24,1,24,3,24,524,8,24,1,24,1,24,1,24,1,24,
  	1,24,1,24,1,24,1,24,1,24,1,24,3,24,536,8,24,1,24,1,24,1,24,1,24,1,24,
  	1,24,1,24,1,24,3,24,546,8,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,
  	1,24,1,24,1,24,1,24,4,24,560,8,24,11,24,12,24,561,1,24,3,24,565,8,24,
  	1,24,1,24,5,24,569,8,24,10,24,12,24,572,9,24,1,24,1,24,1,24,1,24,4,24,
  	578,8,24,11,24,12,24,579,1,24,1,24,3,24,584,8,24,3,24,586,8,24,1,24,5,
  	24,589,8,24,10,24,12,24,592,9,24,1,24,1,24,1,24,1,24,3,24,598,8,24,1,
  	24,1,24,3,24,602,8,24,1,24,1,24,1,24,1,24,1,24,3,24,609,8,24,1,24,1,24,
  	1,24,1,24,1,24,3,24,616,8,24,1,24,1,24,1,24,1,24,1,24,3,24,623,8,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,3,24,647,8,24,1,24,5,24,650,8,24,
  	10,24,12,24,653,9,24,1,24,1,24,1,24,1,24,1,24,3,24,660,8,24,1,24,1,24,
  	1,24,1,24,1,24,3,24,667,8,24,1,24,1,24,3,24,671,8,24,3,24,673,8,24,1,
  	25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,5,26,683,8,26,10,26,12,26,686,9,
  	26,1,27,1,27,1,27,1,27,1,27,1,27,1,27,3,27,695,8,27,1,28,1,28,3,28,699,
  	8,28,1,29,1,29,1,29,5,29,704,8,29,10,29,12,29,707,9,29,1,29,1,29,1,29,
  	1,29,5,29,713,8,29,10,29,12,29,716,9,29,1,29,1,29,1,29,3,29,721,8,29,
  	1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,4,30,
  	736,8,30,11,30,12,30,737,1,30,1,30,1,30,1,30,1,30,1,30,1,30,4,30,747,
  	8,30,11,30,12,30,748,1,30,1,30,1,30,1,30,1,30,1,30,1,30,3,30,758,8,30,
  	1,31,1,31,1,31,1,31,3,31,764,8,31,1,32,1,32,1,32,1,32,1,32,1,32,5,32,
  	772,8,32,10,32,12,32,775,9,32,3,32,777,8,32,1,32,1,32,1,32,1,32,1,32,
  	3,32,784,8,32,1,32,1,32,1,32,1,32,5,32,790,8,32,10,32,12,32,793,9,32,
  	3,32,795,8,32,1,32,1,32,1,32,1,32,3,32,801,8,32,1,32,1,32,1,32,1,32,1,
  	32,1,32,5,32,809,8,32,10,32,12,32,812,9,32,3,32,814,8,32,1,32,1,32,1,
  	32,1,32,1,32,3,32,821,8,32,1,32,1,32,1,32,1,32,1,32,4,32,828,8,32,11,
  	32,12,32,829,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,
  	32,1,32,1,32,1,32,1,32,1,32,1,32,3,32,850,8,32,1,32,1,32,1,32,5,32,855,
  	8,32,10,32,12,32,858,9,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,
  	1,32,1,32,5,32,871,8,32,10,32,12,32,874,9,32,1,33,1,33,3,33,878,8,33,
  	1,34,1,34,1,34,2,705,714,2,26,64,35,0,2,4,6,8,10,12,14,16,18,20,22,24,
  	26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,0,10,
  	2,0,27,28,39,39,1,0,29,31,2,0,27,27,32,32,1,0,33,36,2,0,40,41,44,44,1,
  	0,37,38,1,0,60,67,1,0,57,59,1,0,61,64,1,0,95,96,1018,0,75,1,0,0,0,2,80,
  	1,0,0,0,4,85,1,0,0,0,6,88,1,0,0,0,8,113,1,0,0,0,10,115,1,0,0,0,12,190,
  	1,0,0,0,14,192,1,0,0,0,16,203,1,0,0,0,18,221,1,0,0,0,20,225,1,0,0,0,22,
  	233,1,0,0,0,24,242,1,0,0,0,26,329,1,0,0,0,28,383,1,0,0,0,30,392,1,0,0,
  	0,32,406,1,0,0,0,34,408,1,0,0,0,36,412,1,0,0,0,38,419,1,0,0,0,40,424,
  	1,0,0,0,42,436,1,0,0,0,44,438,1,0,0,0,46,441,1,0,0,0,48,672,1,0,0,0,50,
  	674,1,0,0,0,52,678,1,0,0,0,54,694,1,0,0,0,56,698,1,0,0,0,58,720,1,0,0,
  	0,60,757,1,0,0,0,62,763,1,0,0,0,64,849,1,0,0,0,66,875,1,0,0,0,68,879,
  	1,0,0,0,70,74,3,22,11,0,71,74,3,16,8,0,72,74,3,12,6,0,73,70,1,0,0,0,73,
  	71,1,0,0,0,73,72,1,0,0,0,74,77,1,0,0,0,75,73,1,0,0,0,75,76,1,0,0,0,76,
  	78,1,0,0,0,77,75,1,0,0,0,78,79,5,0,0,1,79,1,1,0,0,0,80,81,3,64,32,0,81,
  	82,5,98,0,0,82,83,1,0,0,0,83,84,5,52,0,0,84,3,1,0,0,0,85,86,5,98,0,0,
  	86,87,3,64,32,0,87,5,1,0,0,0,88,89,5,33,0,0,89,94,3,8,4,0,90,91,5,55,
  	0,0,91,93,3,8,4,0,92,90,1,0,0,0,93,96,1,0,0,0,94,92,1,0,0,0,94,95,1,0,
  	0,0,95,97,1,0,0,0,96,94,1,0,0,0,97,98,5,36,0,0,98,7,1,0,0,0,99,109,5,
  	98,0,0,100,101,5,53,0,0,101,106,3,64,32,0,102,103,5,55,0,0,103,105,3,
  	64,32,0,104,102,1,0,0,0,105,108,1,0,0,0,106,104,1,0,0,0,106,107,1,0,0,
  	0,107,110,1,0,0,0,108,106,1,0,0,0,109,100,1,0,0,0,109,110,1,0,0,0,110,
  	114,1,0,0,0,111,112,5,1,0,0,112,114,5,98,0,0,113,99,1,0,0,0,113,111,1,
  	0,0,0,114,9,1,0,0,0,115,116,5,33,0,0,116,121,3,64,32,0,117,118,5,55,0,
  	0,118,120,3,64,32,0,119,117,1,0,0,0,120,123,1,0,0,0,121,119,1,0,0,0,121,
  	122,1,0,0,0,122,124,1,0,0,0,123,121,1,0,0,0,124,125,5,36,0,0,125,11,1,
  	0,0,0,126,127,5,74,0,0,127,129,5,98,0,0,128,130,3,6,3,0,129,128,1,0,0,
  	0,129,130,1,0,0,0,130,131,1,0,0,0,131,132,5,50,0,0,132,135,3,64,32,0,
  	133,134,5,55,0,0,134,136,3,64,32,0,135,133,1,0,0,0,136,137,1,0,0,0,137,
  	135,1,0,0,0,137,138,1,0,0,0,138,139,1,0,0,0,139,140,5,51,0,0,140,191,
  	1,0,0,0,141,142,5,75,0,0,142,144,5,98,0,0,143,145,3,6,3,0,144,143,1,0,
  	0,0,144,145,1,0,0,0,145,146,1,0,0,0,146,150,5,50,0,0,147,149,3,2,1,0,
  	148,147,1,0,0,0,149,152,1,0,0,0,150,148,1,0,0,0,150,151,1,0,0,0,151,153,
  	1,0,0,0,152,150,1,0,0,0,153,155,5,51,0,0,154,156,3,14,7,0,155,154,1,0,
  	0,0,155,156,1,0,0,0,156,191,1,0,0,0,157,158,5,72,0,0,158,160,5,98,0,0,
  	159,161,3,6,3,0,160,159,1,0,0,0,160,161,1,0,0,0,161,162,1,0,0,0,162,163,
  	5,2,0,0,163,164,5,98,0,0,164,165,5,53,0,0,165,167,3,58,29,0,166,168,5,
  	3,0,0,167,166,1,0,0,0,167,168,1,0,0,0,168,169,1,0,0,0,169,170,3,30,15,
  	0,170,191,1,0,0,0,171,172,5,73,0,0,172,174,5,98,0,0,173,175,3,6,3,0,174,
  	173,1,0,0,0,174,175,1,0,0,0,175,176,1,0,0,0,176,191,3,28,14,0,177,178,
  	5,88,0,0,178,180,5,98,0,0,179,181,3,6,3,0,180,179,1,0,0,0,180,181,1,0,
  	0,0,181,182,1,0,0,0,182,186,5,50,0,0,183,185,3,4,2,0,184,183,1,0,0,0,
  	185,188,1,0,0,0,186,184,1,0,0,0,186,187,1,0,0,0,187,189,1,0,0,0,188,186,
  	1,0,0,0,189,191,5,51,0,0,190,126,1,0,0,0,190,141,1,0,0,0,190,157,1,0,
  	0,0,190,171,1,0,0,0,190,177,1,0,0,0,191,13,1,0,0,0,192,195,5,91,0,0,193,
  	196,5,90,0,0,194,196,3,20,10,0,195,193,1,0,0,0,195,194,1,0,0,0,196,199,
  	1,0,0,0,197,198,5,55,0,0,198,200,3,20,10,0,199,197,1,0,0,0,200,201,1,
  	0,0,0,201,199,1,0,0,0,201,202,1,0,0,0,202,15,1,0,0,0,203,204,5,81,0,0,
  	204,205,5,73,0,0,205,206,5,98,0,0,206,212,5,46,0,0,207,209,3,42,21,0,
  	208,210,5,25,0,0,209,208,1,0,0,0,209,210,1,0,0,0,210,213,1,0,0,0,211,
  	213,5,56,0,0,212,207,1,0,0,0,212,211,1,0,0,0,213,214,1,0,0,0,214,217,
  	5,47,0,0,215,216,5,45,0,0,216,218,3,64,32,0,217,215,1,0,0,0,217,218,1,
  	0,0,0,218,219,1,0,0,0,219,220,5,52,0,0,220,17,1,0,0,0,221,223,5,98,0,
  	0,222,224,3,10,5,0,223,222,1,0,0,0,223,224,1,0,0,0,224,19,1,0,0,0,225,
  	230,3,18,9,0,226,227,5,2,0,0,227,229,3,18,9,0,228,226,1,0,0,0,229,232,
  	1,0,0,0,230,228,1,0,0,0,230,231,1,0,0,0,231,21,1,0,0,0,232,230,1,0,0,
  	0,233,234,5,87,0,0,234,237,3,20,10,0,235,236,5,4,0,0,236,238,5,98,0,0,
  	237,235,1,0,0,0,237,238,1,0,0,0,238,240,1,0,0,0,239,241,5,52,0,0,240,
  	239,1,0,0,0,240,241,1,0,0,0,241,23,1,0,0,0,242,251,5,46,0,0,243,248,3,
  	26,13,0,244,245,5,55,0,0,245,247,3,26,13,0,246,244,1,0,0,0,247,250,1,
  	0,0,0,248,246,1,0,0,0,248,249,1,0,0,0,249,252,1,0,0,0,250,248,1,0,0,0,
  	251,243,1,0,0,0,251,252,1,0,0,0,252,253,1,0,0,0,253,254,5,47,0,0,254,
  	25,1,0,0,0,255,256,6,13,-1,0,256,257,5,46,0,0,257,258,3,26,13,0,258,259,
  	5,47,0,0,259,330,1,0,0,0,260,270,5,48,0,0,261,262,3,26,13,0,262,263,5,
  	55,0,0,263,265,1,0,0,0,264,261,1,0,0,0,265,268,1,0,0,0,266,264,1,0,0,
  	0,266,267,1,0,0,0,267,269,1,0,0,0,268,266,1,0,0,0,269,271,3,26,13,0,270,
  	266,1,0,0,0,270,271,1,0,0,0,271,272,1,0,0,0,272,330,5,49,0,0,273,330,
  	5,98,0,0,274,330,3,20,10,0,275,276,7,0,0,0,276,330,3,26,13,22,277,278,
  	3,20,10,0,278,279,5,6,0,0,279,288,5,46,0,0,280,285,3,26,13,0,281,282,
  	5,55,0,0,282,284,3,26,13,0,283,281,1,0,0,0,284,287,1,0,0,0,285,283,1,
  	0,0,0,285,286,1,0,0,0,286,289,1,0,0,0,287,285,1,0,0,0,288,280,1,0,0,0,
  	288,289,1,0,0,0,289,290,1,0,0,0,290,291,5,47,0,0,291,330,1,0,0,0,292,
  	293,5,29,0,0,293,330,3,26,13,12,294,295,5,69,0,0,295,296,5,33,0,0,296,
  	297,3,64,32,0,297,298,5,36,0,0,298,299,5,6,0,0,299,300,5,46,0,0,300,301,
  	3,26,13,0,301,302,5,47,0,0,302,330,1,0,0,0,303,330,3,68,34,0,304,330,
  	3,66,33,0,305,330,5,97,0,0,306,330,3,28,14,0,307,308,5,98,0,0,308,309,
  	5,7,0,0,309,310,5,46,0,0,310,330,5,47,0,0,311,312,5,98,0,0,312,313,5,
  	8,0,0,313,314,5,46,0,0,314,330,5,47,0,0,315,316,5,85,0,0,316,330,3,26,
  	13,4,317,318,5,86,0,0,318,319,5,46,0,0,319,320,3,26,13,0,320,321,5,47,
  	0,0,321,330,1,0,0,0,322,323,5,86,0,0,323,330,3,26,13,2,324,325,5,9,0,
  	0,325,326,5,46,0,0,326,327,3,26,13,0,327,328,5,47,0,0,328,330,1,0,0,0,
  	329,255,1,0,0,0,329,260,1,0,0,0,329,273,1,0,0,0,329,274,1,0,0,0,329,275,
  	1,0,0,0,329,277,1,0,0,0,329,292,1,0,0,0,329,294,1,0,0,0,329,303,1,0,0,
  	0,329,304,1,0,0,0,329,305,1,0,0,0,329,306,1,0,0,0,329,307,1,0,0,0,329,
  	311,1,0,0,0,329,315,1,0,0,0,329,317,1,0,0,0,329,322,1,0,0,0,329,324,1,
  	0,0,0,330,380,1,0,0,0,331,332,10,21,0,0,332,333,7,1,0,0,333,379,3,26,
  	13,22,334,335,10,20,0,0,335,336,7,2,0,0,336,379,3,26,13,21,337,338,10,
  	19,0,0,338,339,3,54,27,0,339,340,3,26,13,20,340,379,1,0,0,0,341,342,10,
  	18,0,0,342,343,7,3,0,0,343,379,3,26,13,19,344,345,10,17,0,0,345,346,7,
  	4,0,0,346,379,3,26,13,18,347,348,10,16,0,0,348,349,7,5,0,0,349,379,3,
  	26,13,16,350,351,10,28,0,0,351,379,3,24,12,0,352,353,10,27,0,0,353,354,
  	5,48,0,0,354,355,3,26,13,0,355,356,5,49,0,0,356,379,1,0,0,0,357,360,10,
  	24,0,0,358,359,5,5,0,0,359,361,5,98,0,0,360,358,1,0,0,0,361,362,1,0,0,
  	0,362,360,1,0,0,0,362,363,1,0,0,0,363,379,1,0,0,0,364,367,10,15,0,0,365,
  	366,5,42,0,0,366,368,3,26,13,0,367,365,1,0,0,0,368,369,1,0,0,0,369,367,
  	1,0,0,0,369,370,1,0,0,0,370,379,1,0,0,0,371,374,10,14,0,0,372,373,5,43,
  	0,0,373,375,3,26,13,0,374,372,1,0,0,0,375,376,1,0,0,0,376,374,1,0,0,0,
  	376,377,1,0,0,0,377,379,1,0,0,0,378,331,1,0,0,0,378,334,1,0,0,0,378,337,
  	1,0,0,0,378,341,1,0,0,0,378,344,1,0,0,0,378,347,1,0,0,0,378,350,1,0,0,
  	0,378,352,1,0,0,0,378,357,1,0,0,0,378,364,1,0,0,0,378,371,1,0,0,0,379,
  	382,1,0,0,0,380,378,1,0,0,0,380,381,1,0,0,0,381,27,1,0,0,0,382,380,1,
  	0,0,0,383,384,5,46,0,0,384,385,3,42,21,0,385,388,5,47,0,0,386,387,5,45,
  	0,0,387,389,3,64,32,0,388,386,1,0,0,0,388,389,1,0,0,0,389,390,1,0,0,0,
  	390,391,3,30,15,0,391,29,1,0,0,0,392,396,5,50,0,0,393,395,3,48,24,0,394,
  	393,1,0,0,0,395,398,1,0,0,0,396,394,1,0,0,0,396,397,1,0,0,0,397,399,1,
  	0,0,0,398,396,1,0,0,0,399,400,5,51,0,0,400,31,1,0,0,0,401,402,5,46,0,
  	0,402,403,3,26,13,0,403,404,5,47,0,0,404,407,1,0,0,0,405,407,3,26,13,
  	0,406,401,1,0,0,0,406,405,1,0,0,0,407,33,1,0,0,0,408,409,3,26,13,0,409,
  	410,5,53,0,0,410,411,3,48,24,0,411,35,1,0,0,0,412,413,3,64,32,0,413,414,
  	5,98,0,0,414,415,5,10,0,0,415,416,3,48,24,0,416,37,1,0,0,0,417,420,5,
  	98,0,0,418,420,3,58,29,0,419,417,1,0,0,0,419,418,1,0,0,0,420,421,1,0,
  	0,0,421,422,5,10,0,0,422,423,3,48,24,0,423,39,1,0,0,0,424,425,5,77,0,
  	0,425,426,5,10,0,0,426,427,3,48,24,0,427,41,1,0,0,0,428,433,3,44,22,0,
  	429,430,5,55,0,0,430,432,3,44,22,0,431,429,1,0,0,0,432,435,1,0,0,0,433,
  	431,1,0,0,0,433,434,1,0,0,0,434,437,1,0,0,0,435,433,1,0,0,0,436,428,1,
  	0,0,0,436,437,1,0,0,0,437,43,1,0,0,0,438,439,3,64,32,0,439,440,5,98,0,
  	0,440,45,1,0,0,0,441,446,5,98,0,0,442,443,5,55,0,0,443,445,5,98,0,0,444,
  	442,1,0,0,0,445,448,1,0,0,0,446,444,1,0,0,0,446,447,1,0,0,0,447,451,1,
  	0,0,0,448,446,1,0,0,0,449,450,5,26,0,0,450,452,3,26,13,0,451,449,1,0,
  	0,0,451,452,1,0,0,0,452,47,1,0,0,0,453,673,3,12,6,0,454,456,3,52,26,0,
  	455,457,5,52,0,0,456,455,1,0,0,0,456,457,1,0,0,0,457,673,1,0,0,0,458,
  	460,3,50,25,0,459,461,5,52,0,0,460,459,1,0,0,0,460,461,1,0,0,0,461,673,
  	1,0,0,0,462,463,5,76,0,0,463,464,3,32,16,0,464,467,3,30,15,0,465,466,
  	5,77,0,0,466,468,3,30,15,0,467,465,1,0,0,0,467,468,1,0,0,0,468,472,1,
  	0,0,0,469,471,3,48,24,0,470,469,1,0,0,0,471,474,1,0,0,0,472,470,1,0,0,
  	0,472,473,1,0,0,0,473,673,1,0,0,0,474,472,1,0,0,0,475,476,5,80,0,0,476,
  	480,5,50,0,0,477,479,3,34,17,0,478,477,1,0,0,0,479,482,1,0,0,0,480,478,
  	1,0,0,0,480,481,1,0,0,0,481,483,1,0,0,0,482,480,1,0,0,0,483,487,5,51,
  	0,0,484,486,3,48,24,0,485,484,1,0,0,0,486,489,1,0,0,0,487,485,1,0,0,0,
  	487,488,1,0,0,0,488,673,1,0,0,0,489,487,1,0,0,0,490,491,5,82,0,0,491,
  	492,3,32,16,0,492,496,5,50,0,0,493,495,3,36,18,0,494,493,1,0,0,0,495,
  	498,1,0,0,0,496,494,1,0,0,0,496,497,1,0,0,0,497,499,1,0,0,0,498,496,1,
  	0,0,0,499,503,5,51,0,0,500,502,3,48,24,0,501,500,1,0,0,0,502,505,1,0,
  	0,0,503,501,1,0,0,0,503,504,1,0,0,0,504,673,1,0,0,0,505,503,1,0,0,0,506,
  	507,5,82,0,0,507,512,3,32,16,0,508,509,5,41,0,0,509,511,3,36,18,0,510,
  	508,1,0,0,0,511,514,1,0,0,0,512,510,1,0,0,0,512,513,1,0,0,0,513,518,1,
  	0,0,0,514,512,1,0,0,0,515,517,3,48,24,0,516,515,1,0,0,0,517,520,1,0,0,
  	0,518,516,1,0,0,0,518,519,1,0,0,0,519,673,1,0,0,0,520,518,1,0,0,0,521,
  	523,5,79,0,0,522,524,3,26,13,0,523,522,1,0,0,0,523,524,1,0,0,0,524,525,
  	1,0,0,0,525,673,5,52,0,0,526,673,5,84,0,0,527,673,5,11,0,0,528,673,3,
  	30,15,0,529,530,5,98,0,0,530,531,5,12,0,0,531,532,5,46,0,0,532,533,3,
  	26,13,0,533,535,5,47,0,0,534,536,5,52,0,0,535,534,1,0,0,0,535,536,1,0,
  	0,0,536,673,1,0,0,0,537,538,5,78,0,0,538,539,3,32,16,0,539,540,3,30,15,
  	0,540,673,1,0,0,0,541,542,5,13,0,0,542,545,5,46,0,0,543,546,3,52,26,0,
  	544,546,3,50,25,0,545,543,1,0,0,0,545,544,1,0,0,0,546,547,1,0,0,0,547,
  	548,5,52,0,0,548,549,3,32,16,0,549,550,5,52,0,0,550,551,3,48,24,0,551,
  	552,5,47,0,0,552,553,3,30,15,0,553,673,1,0,0,0,554,555,5,98,0,0,555,556,
  	5,14,0,0,556,557,5,46,0,0,557,559,3,38,19,0,558,560,3,38,19,0,559,558,
  	1,0,0,0,560,561,1,0,0,0,561,559,1,0,0,0,561,562,1,0,0,0,562,564,1,0,0,
  	0,563,565,3,40,20,0,564,563,1,0,0,0,564,565,1,0,0,0,565,566,1,0,0,0,566,
  	570,5,47,0,0,567,569,3,48,24,0,568,567,1,0,0,0,569,572,1,0,0,0,570,568,
  	1,0,0,0,570,571,1,0,0,0,571,673,1,0,0,0,572,570,1,0,0,0,573,574,5,15,
  	0,0,574,577,5,98,0,0,575,576,5,41,0,0,576,578,3,38,19,0,577,575,1,0,0,
  	0,578,579,1,0,0,0,579,577,1,0,0,0,579,580,1,0,0,0,580,585,1,0,0,0,581,
  	583,5,41,0,0,582,584,3,40,20,0,583,582,1,0,0,0,583,584,1,0,0,0,584,586,
  	1,0,0,0,585,581,1,0,0,0,585,586,1,0,0,0,586,590,1,0,0,0,587,589,3,48,
  	24,0,588,587,1,0,0,0,589,592,1,0,0,0,590,588,1,0,0,0,590,591,1,0,0,0,
  	591,673,1,0,0,0,592,590,1,0,0,0,593,594,5,98,0,0,594,597,5,48,0,0,595,
  	598,5,98,0,0,596,598,3,58,29,0,597,595,1,0,0,0,597,596,1,0,0,0,598,599,
  	1,0,0,0,599,601,5,49,0,0,600,602,5,52,0,0,601,600,1,0,0,0,601,602,1,0,
  	0,0,602,673,1,0,0,0,603,604,5,16,0,0,604,605,5,46,0,0,605,606,5,98,0,
  	0,606,608,5,47,0,0,607,609,5,52,0,0,608,607,1,0,0,0,608,609,1,0,0,0,609,
  	673,1,0,0,0,610,611,5,17,0,0,611,612,5,46,0,0,612,613,5,98,0,0,613,615,
  	5,47,0,0,614,616,5,52,0,0,615,614,1,0,0,0,615,616,1,0,0,0,616,673,1,0,
  	0,0,617,618,5,18,0,0,618,619,5,46,0,0,619,620,5,98,0,0,620,622,5,47,0,
  	0,621,623,5,52,0,0,622,621,1,0,0,0,622,623,1,0,0,0,623,673,1,0,0,0,624,
  	625,5,19,0,0,625,626,5,46,0,0,626,627,5,98,0,0,627,628,5,47,0,0,628,673,
  	3,30,15,0,629,630,5,20,0,0,630,631,5,46,0,0,631,632,5,98,0,0,632,633,
  	5,55,0,0,633,634,3,26,13,0,634,635,5,47,0,0,635,636,3,30,15,0,636,673,
  	1,0,0,0,637,638,5,21,0,0,638,639,5,46,0,0,639,640,5,98,0,0,640,641,5,
  	55,0,0,641,642,3,26,13,0,642,643,5,47,0,0,643,646,3,30,15,0,644,645,5,
  	77,0,0,645,647,3,30,15,0,646,644,1,0,0,0,646,647,1,0,0,0,647,651,1,0,
  	0,0,648,650,3,48,24,0,649,648,1,0,0,0,650,653,1,0,0,0,651,649,1,0,0,0,
  	651,652,1,0,0,0,652,673,1,0,0,0,653,651,1,0,0,0,654,655,5,22,0,0,655,
  	656,5,46,0,0,656,657,5,98,0,0,657,659,5,47,0,0,658,660,5,52,0,0,659,658,
  	1,0,0,0,659,660,1,0,0,0,660,673,1,0,0,0,661,662,5,23,0,0,662,663,5,46,
  	0,0,663,664,5,98,0,0,664,666,5,47,0,0,665,667,5,52,0,0,666,665,1,0,0,
  	0,666,667,1,0,0,0,667,673,1,0,0,0,668,670,3,26,13,0,669,671,5,52,0,0,
  	670,669,1,0,0,0,670,671,1,0,0,0,671,673,1,0,0,0,672,453,1,0,0,0,672,454,
  	1,0,0,0,672,458,1,0,0,0,672,462,1,0,0,0,672,475,1,0,0,0,672,490,1,0,0,
  	0,672,506,1,0,0,0,672,521,1,0,0,0,672,526,1,0,0,0,672,527,1,0,0,0,672,
  	528,1,0,0,0,672,529,1,0,0,0,672,537,1,0,0,0,672,541,1,0,0,0,672,554,1,
  	0,0,0,672,573,1,0,0,0,672,593,1,0,0,0,672,603,1,0,0,0,672,610,1,0,0,0,
  	672,617,1,0,0,0,672,624,1,0,0,0,672,629,1,0,0,0,672,637,1,0,0,0,672,654,
  	1,0,0,0,672,661,1,0,0,0,672,668,1,0,0,0,673,49,1,0,0,0,674,675,3,26,13,
  	0,675,676,5,26,0,0,676,677,3,26,13,0,677,51,1,0,0,0,678,679,3,56,28,0,
  	679,684,3,46,23,0,680,681,5,55,0,0,681,683,3,46,23,0,682,680,1,0,0,0,
  	683,686,1,0,0,0,684,682,1,0,0,0,684,685,1,0,0,0,685,53,1,0,0,0,686,684,
  	1,0,0,0,687,688,5,36,0,0,688,689,5,36,0,0,689,695,5,36,0,0,690,691,5,
  	36,0,0,691,695,5,36,0,0,692,693,5,33,0,0,693,695,5,33,0,0,694,687,1,0,
  	0,0,694,690,1,0,0,0,694,692,1,0,0,0,695,55,1,0,0,0,696,699,3,64,32,0,
  	697,699,5,68,0,0,698,696,1,0,0,0,698,697,1,0,0,0,699,57,1,0,0,0,700,705,
  	3,60,30,0,701,702,5,52,0,0,702,704,3,60,30,0,703,701,1,0,0,0,704,707,
  	1,0,0,0,705,706,1,0,0,0,705,703,1,0,0,0,706,721,1,0,0,0,707,705,1,0,0,
  	0,708,709,5,46,0,0,709,714,3,60,30,0,710,711,5,52,0,0,711,713,3,60,30,
  	0,712,710,1,0,0,0,713,716,1,0,0,0,714,715,1,0,0,0,714,712,1,0,0,0,715,
  	717,1,0,0,0,716,714,1,0,0,0,717,718,5,47,0,0,718,721,1,0,0,0,719,721,
  	3,60,30,0,720,700,1,0,0,0,720,708,1,0,0,0,720,719,1,0,0,0,721,59,1,0,
  	0,0,722,723,5,32,0,0,723,758,3,64,32,0,724,725,5,27,0,0,725,758,3,64,
  	32,0,726,727,5,24,0,0,727,758,3,58,29,0,728,729,5,28,0,0,729,758,3,58,
  	29,0,730,731,5,92,0,0,731,732,5,33,0,0,732,735,3,62,31,0,733,734,5,55,
  	0,0,734,736,3,62,31,0,735,733,1,0,0,0,736,737,1,0,0,0,737,735,1,0,0,0,
  	737,738,1,0,0,0,738,739,1,0,0,0,739,740,5,36,0,0,740,758,1,0,0,0,741,
  	742,5,93,0,0,742,743,5,33,0,0,743,746,3,62,31,0,744,745,5,55,0,0,745,
  	747,3,62,31,0,746,744,1,0,0,0,747,748,1,0,0,0,748,746,1,0,0,0,748,749,
  	1,0,0,0,749,750,1,0,0,0,750,751,5,36,0,0,751,758,1,0,0,0,752,753,5,94,
  	0,0,753,754,5,33,0,0,754,755,3,58,29,0,755,756,5,36,0,0,756,758,1,0,0,
  	0,757,722,1,0,0,0,757,724,1,0,0,0,757,726,1,0,0,0,757,728,1,0,0,0,757,
  	730,1,0,0,0,757,741,1,0,0,0,757,752,1,0,0,0,758,61,1,0,0,0,759,764,3,
  	58,29,0,760,761,5,98,0,0,761,762,5,53,0,0,762,764,3,58,29,0,763,759,1,
  	0,0,0,763,760,1,0,0,0,764,63,1,0,0,0,765,766,6,32,-1,0,766,850,7,6,0,
  	0,767,776,5,46,0,0,768,773,3,64,32,0,769,770,5,55,0,0,770,772,3,64,32,
  	0,771,769,1,0,0,0,772,775,1,0,0,0,773,771,1,0,0,0,773,774,1,0,0,0,774,
  	777,1,0,0,0,775,773,1,0,0,0,776,768,1,0,0,0,776,777,1,0,0,0,777,778,1,
  	0,0,0,778,779,5,47,0,0,779,783,5,45,0,0,780,784,3,64,32,0,781,782,5,46,
  	0,0,782,784,5,47,0,0,783,780,1,0,0,0,783,781,1,0,0,0,784,850,1,0,0,0,
  	785,794,5,46,0,0,786,791,3,64,32,0,787,788,5,55,0,0,788,790,3,64,32,0,
  	789,787,1,0,0,0,790,793,1,0,0,0,791,789,1,0,0,0,791,792,1,0,0,0,792,795,
  	1,0,0,0,793,791,1,0,0,0,794,786,1,0,0,0,794,795,1,0,0,0,795,796,1,0,0,
  	0,796,800,5,45,0,0,797,801,3,64,32,0,798,799,5,46,0,0,799,801,5,47,0,
  	0,800,797,1,0,0,0,800,798,1,0,0,0,801,802,1,0,0,0,802,850,5,47,0,0,803,
  	804,5,46,0,0,804,813,5,46,0,0,805,810,3,64,32,0,806,807,5,55,0,0,807,
  	809,3,64,32,0,808,806,1,0,0,0,809,812,1,0,0,0,810,808,1,0,0,0,810,811,
  	1,0,0,0,811,814,1,0,0,0,812,810,1,0,0,0,813,805,1,0,0,0,813,814,1,0,0,
  	0,814,815,1,0,0,0,815,816,5,47,0,0,816,820,5,45,0,0,817,821,3,64,32,0,
  	818,819,5,46,0,0,819,821,5,47,0,0,820,817,1,0,0,0,820,818,1,0,0,0,821,
  	822,1,0,0,0,822,850,5,47,0,0,823,824,5,46,0,0,824,827,3,64,32,0,825,826,
  	5,32,0,0,826,828,3,64,32,0,827,825,1,0,0,0,828,829,1,0,0,0,829,827,1,
  	0,0,0,829,830,1,0,0,0,830,831,1,0,0,0,831,832,5,47,0,0,832,850,1,0,0,
  	0,833,834,5,71,0,0,834,835,5,33,0,0,835,836,3,58,29,0,836,837,5,36,0,
  	0,837,850,1,0,0,0,838,839,5,70,0,0,839,840,5,33,0,0,840,841,3,58,29,0,
  	841,842,5,36,0,0,842,850,1,0,0,0,843,844,5,69,0,0,844,845,5,33,0,0,845,
  	846,3,64,32,0,846,847,5,36,0,0,847,850,1,0,0,0,848,850,3,20,10,0,849,
  	765,1,0,0,0,849,767,1,0,0,0,849,785,1,0,0,0,849,803,1,0,0,0,849,823,1,
  	0,0,0,849,833,1,0,0,0,849,838,1,0,0,0,849,843,1,0,0,0,849,848,1,0,0,0,
  	850,872,1,0,0,0,851,856,10,10,0,0,852,853,5,55,0,0,853,855,3,64,32,0,
  	854,852,1,0,0,0,855,858,1,0,0,0,856,854,1,0,0,0,856,857,1,0,0,0,857,859,
  	1,0,0,0,858,856,1,0,0,0,859,860,5,45,0,0,860,871,3,64,32,11,861,862,10,
  	13,0,0,862,863,5,48,0,0,863,864,5,57,0,0,864,871,5,49,0,0,865,866,10,
  	12,0,0,866,867,5,48,0,0,867,871,5,49,0,0,868,869,10,2,0,0,869,871,3,10,
  	5,0,870,851,1,0,0,0,870,861,1,0,0,0,870,865,1,0,0,0,870,868,1,0,0,0,871,
  	874,1,0,0,0,872,870,1,0,0,0,872,873,1,0,0,0,873,65,1,0,0,0,874,872,1,
  	0,0,0,875,877,7,7,0,0,876,878,7,8,0,0,877,876,1,0,0,0,877,878,1,0,0,0,
  	878,67,1,0,0,0,879,880,7,9,0,0,880,69,1,0,0,0,103,73,75,94,106,109,113,
  	121,129,137,144,150,155,160,167,174,180,186,190,195,201,209,212,217,223,
  	230,237,240,248,251,266,270,285,288,329,362,369,376,378,380,388,396,406,
  	419,433,436,446,451,456,460,467,472,480,487,496,503,512,518,523,535,545,
  	561,564,570,579,583,585,590,597,601,608,615,622,646,651,659,666,670,672,
  	684,694,698,705,714,720,737,748,757,763,773,776,783,791,794,800,810,813,
  	820,829,849,856,870,872,877
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  bismuthParserStaticData = staticData.release();
}

}

BismuthParser::BismuthParser(TokenStream *input) : BismuthParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

BismuthParser::BismuthParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  BismuthParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *bismuthParserStaticData->atn, bismuthParserStaticData->decisionToDFA, bismuthParserStaticData->sharedContextCache, options);
}

BismuthParser::~BismuthParser() {
  delete _interpreter;
}

const atn::ATN& BismuthParser::getATN() const {
  return *bismuthParserStaticData->atn;
}

std::string BismuthParser::getGrammarFileName() const {
  return "Bismuth.g4";
}

const std::vector<std::string>& BismuthParser::getRuleNames() const {
  return bismuthParserStaticData->ruleNames;
}

const dfa::Vocabulary& BismuthParser::getVocabulary() const {
  return bismuthParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView BismuthParser::getSerializedATN() const {
  return bismuthParserStaticData->serializedATN;
}


//----------------- CompilationUnitContext ------------------------------------------------------------------

BismuthParser::CompilationUnitContext::CompilationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::CompilationUnitContext::EOF() {
  return getToken(BismuthParser::EOF, 0);
}

std::vector<BismuthParser::ImportStatementContext *> BismuthParser::CompilationUnitContext::importStatement() {
  return getRuleContexts<BismuthParser::ImportStatementContext>();
}

BismuthParser::ImportStatementContext* BismuthParser::CompilationUnitContext::importStatement(size_t i) {
  return getRuleContext<BismuthParser::ImportStatementContext>(i);
}

std::vector<BismuthParser::ExternStatementContext *> BismuthParser::CompilationUnitContext::externStatement() {
  return getRuleContexts<BismuthParser::ExternStatementContext>();
}

BismuthParser::ExternStatementContext* BismuthParser::CompilationUnitContext::externStatement(size_t i) {
  return getRuleContext<BismuthParser::ExternStatementContext>(i);
}

std::vector<BismuthParser::DefineTypeContext *> BismuthParser::CompilationUnitContext::defineType() {
  return getRuleContexts<BismuthParser::DefineTypeContext>();
}

BismuthParser::DefineTypeContext* BismuthParser::CompilationUnitContext::defineType(size_t i) {
  return getRuleContext<BismuthParser::DefineTypeContext>(i);
}


size_t BismuthParser::CompilationUnitContext::getRuleIndex() const {
  return BismuthParser::RuleCompilationUnit;
}

void BismuthParser::CompilationUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompilationUnit(this);
}

void BismuthParser::CompilationUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompilationUnit(this);
}


std::any BismuthParser::CompilationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitCompilationUnit(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::CompilationUnitContext* BismuthParser::compilationUnit() {
  CompilationUnitContext *_localctx = _tracker.createInstance<CompilationUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, BismuthParser::RuleCompilationUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(75);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 72) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 72)) & ((1ULL << (BismuthParser::PROG - 72))
      | (1ULL << (BismuthParser::FUNC - 72))
      | (1ULL << (BismuthParser::ENUM - 72))
      | (1ULL << (BismuthParser::STRUCT - 72))
      | (1ULL << (BismuthParser::EXTERN - 72))
      | (1ULL << (BismuthParser::IMPORT - 72))
      | (1ULL << (BismuthParser::TRAIT - 72)))) != 0)) {
      setState(73);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case BismuthParser::IMPORT: {
          setState(70);
          antlrcpp::downCast<CompilationUnitContext *>(_localctx)->importStatementContext = importStatement();
          antlrcpp::downCast<CompilationUnitContext *>(_localctx)->imports.push_back(antlrcpp::downCast<CompilationUnitContext *>(_localctx)->importStatementContext);
          break;
        }

        case BismuthParser::EXTERN: {
          setState(71);
          antlrcpp::downCast<CompilationUnitContext *>(_localctx)->externStatementContext = externStatement();
          antlrcpp::downCast<CompilationUnitContext *>(_localctx)->externs.push_back(antlrcpp::downCast<CompilationUnitContext *>(_localctx)->externStatementContext);
          break;
        }

        case BismuthParser::PROG:
        case BismuthParser::FUNC:
        case BismuthParser::ENUM:
        case BismuthParser::STRUCT:
        case BismuthParser::TRAIT: {
          setState(72);
          antlrcpp::downCast<CompilationUnitContext *>(_localctx)->defineTypeContext = defineType();
          antlrcpp::downCast<CompilationUnitContext *>(_localctx)->defs.push_back(antlrcpp::downCast<CompilationUnitContext *>(_localctx)->defineTypeContext);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(77);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(78);
    match(BismuthParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructCaseContext ------------------------------------------------------------------

BismuthParser::StructCaseContext::StructCaseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::StructCaseContext::SEMICOLON() {
  return getToken(BismuthParser::SEMICOLON, 0);
}

BismuthParser::TypeContext* BismuthParser::StructCaseContext::type() {
  return getRuleContext<BismuthParser::TypeContext>(0);
}

tree::TerminalNode* BismuthParser::StructCaseContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}


size_t BismuthParser::StructCaseContext::getRuleIndex() const {
  return BismuthParser::RuleStructCase;
}

void BismuthParser::StructCaseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructCase(this);
}

void BismuthParser::StructCaseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructCase(this);
}


std::any BismuthParser::StructCaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitStructCase(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::StructCaseContext* BismuthParser::structCase() {
  StructCaseContext *_localctx = _tracker.createInstance<StructCaseContext>(_ctx, getState());
  enterRule(_localctx, 2, BismuthParser::RuleStructCase);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(80);
    antlrcpp::downCast<StructCaseContext *>(_localctx)->ty = type(0);
    setState(81);
    antlrcpp::downCast<StructCaseContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
    setState(83);
    match(BismuthParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TraitEntryContext ------------------------------------------------------------------

BismuthParser::TraitEntryContext::TraitEntryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::TraitEntryContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

BismuthParser::TypeContext* BismuthParser::TraitEntryContext::type() {
  return getRuleContext<BismuthParser::TypeContext>(0);
}


size_t BismuthParser::TraitEntryContext::getRuleIndex() const {
  return BismuthParser::RuleTraitEntry;
}

void BismuthParser::TraitEntryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTraitEntry(this);
}

void BismuthParser::TraitEntryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTraitEntry(this);
}


std::any BismuthParser::TraitEntryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitTraitEntry(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::TraitEntryContext* BismuthParser::traitEntry() {
  TraitEntryContext *_localctx = _tracker.createInstance<TraitEntryContext>(_ctx, getState());
  enterRule(_localctx, 4, BismuthParser::RuleTraitEntry);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(85);
    antlrcpp::downCast<TraitEntryContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
    setState(86);
    antlrcpp::downCast<TraitEntryContext *>(_localctx)->ty = type(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GenericTemplateContext ------------------------------------------------------------------

BismuthParser::GenericTemplateContext::GenericTemplateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::GenericTemplateContext::LESS() {
  return getToken(BismuthParser::LESS, 0);
}

tree::TerminalNode* BismuthParser::GenericTemplateContext::GREATER() {
  return getToken(BismuthParser::GREATER, 0);
}

std::vector<BismuthParser::GenericEntryContext *> BismuthParser::GenericTemplateContext::genericEntry() {
  return getRuleContexts<BismuthParser::GenericEntryContext>();
}

BismuthParser::GenericEntryContext* BismuthParser::GenericTemplateContext::genericEntry(size_t i) {
  return getRuleContext<BismuthParser::GenericEntryContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::GenericTemplateContext::COMMA() {
  return getTokens(BismuthParser::COMMA);
}

tree::TerminalNode* BismuthParser::GenericTemplateContext::COMMA(size_t i) {
  return getToken(BismuthParser::COMMA, i);
}


size_t BismuthParser::GenericTemplateContext::getRuleIndex() const {
  return BismuthParser::RuleGenericTemplate;
}

void BismuthParser::GenericTemplateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGenericTemplate(this);
}

void BismuthParser::GenericTemplateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGenericTemplate(this);
}


std::any BismuthParser::GenericTemplateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitGenericTemplate(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::GenericTemplateContext* BismuthParser::genericTemplate() {
  GenericTemplateContext *_localctx = _tracker.createInstance<GenericTemplateContext>(_ctx, getState());
  enterRule(_localctx, 6, BismuthParser::RuleGenericTemplate);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    match(BismuthParser::LESS);
    setState(89);
    antlrcpp::downCast<GenericTemplateContext *>(_localctx)->genericEntryContext = genericEntry();
    antlrcpp::downCast<GenericTemplateContext *>(_localctx)->gen.push_back(antlrcpp::downCast<GenericTemplateContext *>(_localctx)->genericEntryContext);
    setState(94);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BismuthParser::COMMA) {
      setState(90);
      match(BismuthParser::COMMA);
      setState(91);
      antlrcpp::downCast<GenericTemplateContext *>(_localctx)->genericEntryContext = genericEntry();
      antlrcpp::downCast<GenericTemplateContext *>(_localctx)->gen.push_back(antlrcpp::downCast<GenericTemplateContext *>(_localctx)->genericEntryContext);
      setState(96);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(97);
    match(BismuthParser::GREATER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GenericEntryContext ------------------------------------------------------------------

BismuthParser::GenericEntryContext::GenericEntryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t BismuthParser::GenericEntryContext::getRuleIndex() const {
  return BismuthParser::RuleGenericEntry;
}

void BismuthParser::GenericEntryContext::copyFrom(GenericEntryContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- GenericTypeContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::GenericTypeContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

tree::TerminalNode* BismuthParser::GenericTypeContext::COLON() {
  return getToken(BismuthParser::COLON, 0);
}

std::vector<BismuthParser::TypeContext *> BismuthParser::GenericTypeContext::type() {
  return getRuleContexts<BismuthParser::TypeContext>();
}

BismuthParser::TypeContext* BismuthParser::GenericTypeContext::type(size_t i) {
  return getRuleContext<BismuthParser::TypeContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::GenericTypeContext::COMMA() {
  return getTokens(BismuthParser::COMMA);
}

tree::TerminalNode* BismuthParser::GenericTypeContext::COMMA(size_t i) {
  return getToken(BismuthParser::COMMA, i);
}

BismuthParser::GenericTypeContext::GenericTypeContext(GenericEntryContext *ctx) { copyFrom(ctx); }

void BismuthParser::GenericTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGenericType(this);
}
void BismuthParser::GenericTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGenericType(this);
}

std::any BismuthParser::GenericTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitGenericType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- GenericSessionContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::GenericSessionContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

BismuthParser::GenericSessionContext::GenericSessionContext(GenericEntryContext *ctx) { copyFrom(ctx); }

void BismuthParser::GenericSessionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGenericSession(this);
}
void BismuthParser::GenericSessionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGenericSession(this);
}

std::any BismuthParser::GenericSessionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitGenericSession(this);
  else
    return visitor->visitChildren(this);
}
BismuthParser::GenericEntryContext* BismuthParser::genericEntry() {
  GenericEntryContext *_localctx = _tracker.createInstance<GenericEntryContext>(_ctx, getState());
  enterRule(_localctx, 8, BismuthParser::RuleGenericEntry);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(113);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BismuthParser::VARIABLE: {
        _localctx = _tracker.createInstance<BismuthParser::GenericTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(99);
        antlrcpp::downCast<GenericTypeContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
        setState(109);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::COLON) {
          setState(100);
          match(BismuthParser::COLON);
          setState(101);
          antlrcpp::downCast<GenericTypeContext *>(_localctx)->typeContext = type(0);
          antlrcpp::downCast<GenericTypeContext *>(_localctx)->supTy.push_back(antlrcpp::downCast<GenericTypeContext *>(_localctx)->typeContext);
          setState(106);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
          while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
              setState(102);
              match(BismuthParser::COMMA);
              setState(103);
              antlrcpp::downCast<GenericTypeContext *>(_localctx)->typeContext = type(0);
              antlrcpp::downCast<GenericTypeContext *>(_localctx)->supTy.push_back(antlrcpp::downCast<GenericTypeContext *>(_localctx)->typeContext); 
            }
            setState(108);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
          }
        }
        break;
      }

      case BismuthParser::T__0: {
        _localctx = _tracker.createInstance<BismuthParser::GenericSessionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(111);
        match(BismuthParser::T__0);
        setState(112);
        antlrcpp::downCast<GenericSessionContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GenericSpecifierContext ------------------------------------------------------------------

BismuthParser::GenericSpecifierContext::GenericSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::GenericSpecifierContext::LESS() {
  return getToken(BismuthParser::LESS, 0);
}

tree::TerminalNode* BismuthParser::GenericSpecifierContext::GREATER() {
  return getToken(BismuthParser::GREATER, 0);
}

std::vector<BismuthParser::TypeContext *> BismuthParser::GenericSpecifierContext::type() {
  return getRuleContexts<BismuthParser::TypeContext>();
}

BismuthParser::TypeContext* BismuthParser::GenericSpecifierContext::type(size_t i) {
  return getRuleContext<BismuthParser::TypeContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::GenericSpecifierContext::COMMA() {
  return getTokens(BismuthParser::COMMA);
}

tree::TerminalNode* BismuthParser::GenericSpecifierContext::COMMA(size_t i) {
  return getToken(BismuthParser::COMMA, i);
}


size_t BismuthParser::GenericSpecifierContext::getRuleIndex() const {
  return BismuthParser::RuleGenericSpecifier;
}

void BismuthParser::GenericSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGenericSpecifier(this);
}

void BismuthParser::GenericSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGenericSpecifier(this);
}


std::any BismuthParser::GenericSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitGenericSpecifier(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::GenericSpecifierContext* BismuthParser::genericSpecifier() {
  GenericSpecifierContext *_localctx = _tracker.createInstance<GenericSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 10, BismuthParser::RuleGenericSpecifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(115);
    match(BismuthParser::LESS);
    setState(116);
    antlrcpp::downCast<GenericSpecifierContext *>(_localctx)->typeContext = type(0);
    antlrcpp::downCast<GenericSpecifierContext *>(_localctx)->subst.push_back(antlrcpp::downCast<GenericSpecifierContext *>(_localctx)->typeContext);
    setState(121);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BismuthParser::COMMA) {
      setState(117);
      match(BismuthParser::COMMA);
      setState(118);
      antlrcpp::downCast<GenericSpecifierContext *>(_localctx)->typeContext = type(0);
      antlrcpp::downCast<GenericSpecifierContext *>(_localctx)->subst.push_back(antlrcpp::downCast<GenericSpecifierContext *>(_localctx)->typeContext);
      setState(123);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(124);
    match(BismuthParser::GREATER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefineTypeContext ------------------------------------------------------------------

BismuthParser::DefineTypeContext::DefineTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t BismuthParser::DefineTypeContext::getRuleIndex() const {
  return BismuthParser::RuleDefineType;
}

void BismuthParser::DefineTypeContext::copyFrom(DefineTypeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DefineStructContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::DefineStructContext::STRUCT() {
  return getToken(BismuthParser::STRUCT, 0);
}

tree::TerminalNode* BismuthParser::DefineStructContext::LSQB() {
  return getToken(BismuthParser::LSQB, 0);
}

tree::TerminalNode* BismuthParser::DefineStructContext::RSQB() {
  return getToken(BismuthParser::RSQB, 0);
}

tree::TerminalNode* BismuthParser::DefineStructContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

BismuthParser::GenericTemplateContext* BismuthParser::DefineStructContext::genericTemplate() {
  return getRuleContext<BismuthParser::GenericTemplateContext>(0);
}

BismuthParser::InherentTraitSpecContext* BismuthParser::DefineStructContext::inherentTraitSpec() {
  return getRuleContext<BismuthParser::InherentTraitSpecContext>(0);
}

std::vector<BismuthParser::StructCaseContext *> BismuthParser::DefineStructContext::structCase() {
  return getRuleContexts<BismuthParser::StructCaseContext>();
}

BismuthParser::StructCaseContext* BismuthParser::DefineStructContext::structCase(size_t i) {
  return getRuleContext<BismuthParser::StructCaseContext>(i);
}

BismuthParser::DefineStructContext::DefineStructContext(DefineTypeContext *ctx) { copyFrom(ctx); }

void BismuthParser::DefineStructContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefineStruct(this);
}
void BismuthParser::DefineStructContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefineStruct(this);
}

std::any BismuthParser::DefineStructContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitDefineStruct(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DefineEnumContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::DefineEnumContext::ENUM() {
  return getToken(BismuthParser::ENUM, 0);
}

tree::TerminalNode* BismuthParser::DefineEnumContext::LSQB() {
  return getToken(BismuthParser::LSQB, 0);
}

tree::TerminalNode* BismuthParser::DefineEnumContext::RSQB() {
  return getToken(BismuthParser::RSQB, 0);
}

tree::TerminalNode* BismuthParser::DefineEnumContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

std::vector<BismuthParser::TypeContext *> BismuthParser::DefineEnumContext::type() {
  return getRuleContexts<BismuthParser::TypeContext>();
}

BismuthParser::TypeContext* BismuthParser::DefineEnumContext::type(size_t i) {
  return getRuleContext<BismuthParser::TypeContext>(i);
}

BismuthParser::GenericTemplateContext* BismuthParser::DefineEnumContext::genericTemplate() {
  return getRuleContext<BismuthParser::GenericTemplateContext>(0);
}

std::vector<tree::TerminalNode *> BismuthParser::DefineEnumContext::COMMA() {
  return getTokens(BismuthParser::COMMA);
}

tree::TerminalNode* BismuthParser::DefineEnumContext::COMMA(size_t i) {
  return getToken(BismuthParser::COMMA, i);
}

BismuthParser::DefineEnumContext::DefineEnumContext(DefineTypeContext *ctx) { copyFrom(ctx); }

void BismuthParser::DefineEnumContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefineEnum(this);
}
void BismuthParser::DefineEnumContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefineEnum(this);
}

std::any BismuthParser::DefineEnumContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitDefineEnum(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DefineProgramContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::DefineProgramContext::PROG() {
  return getToken(BismuthParser::PROG, 0);
}

tree::TerminalNode* BismuthParser::DefineProgramContext::COLON() {
  return getToken(BismuthParser::COLON, 0);
}

BismuthParser::BlockContext* BismuthParser::DefineProgramContext::block() {
  return getRuleContext<BismuthParser::BlockContext>(0);
}

std::vector<tree::TerminalNode *> BismuthParser::DefineProgramContext::VARIABLE() {
  return getTokens(BismuthParser::VARIABLE);
}

tree::TerminalNode* BismuthParser::DefineProgramContext::VARIABLE(size_t i) {
  return getToken(BismuthParser::VARIABLE, i);
}

BismuthParser::ProtocolContext* BismuthParser::DefineProgramContext::protocol() {
  return getRuleContext<BismuthParser::ProtocolContext>(0);
}

BismuthParser::GenericTemplateContext* BismuthParser::DefineProgramContext::genericTemplate() {
  return getRuleContext<BismuthParser::GenericTemplateContext>(0);
}

BismuthParser::DefineProgramContext::DefineProgramContext(DefineTypeContext *ctx) { copyFrom(ctx); }

void BismuthParser::DefineProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefineProgram(this);
}
void BismuthParser::DefineProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefineProgram(this);
}

std::any BismuthParser::DefineProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitDefineProgram(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DefineTraitContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::DefineTraitContext::TRAIT() {
  return getToken(BismuthParser::TRAIT, 0);
}

tree::TerminalNode* BismuthParser::DefineTraitContext::LSQB() {
  return getToken(BismuthParser::LSQB, 0);
}

tree::TerminalNode* BismuthParser::DefineTraitContext::RSQB() {
  return getToken(BismuthParser::RSQB, 0);
}

tree::TerminalNode* BismuthParser::DefineTraitContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

BismuthParser::GenericTemplateContext* BismuthParser::DefineTraitContext::genericTemplate() {
  return getRuleContext<BismuthParser::GenericTemplateContext>(0);
}

std::vector<BismuthParser::TraitEntryContext *> BismuthParser::DefineTraitContext::traitEntry() {
  return getRuleContexts<BismuthParser::TraitEntryContext>();
}

BismuthParser::TraitEntryContext* BismuthParser::DefineTraitContext::traitEntry(size_t i) {
  return getRuleContext<BismuthParser::TraitEntryContext>(i);
}

BismuthParser::DefineTraitContext::DefineTraitContext(DefineTypeContext *ctx) { copyFrom(ctx); }

void BismuthParser::DefineTraitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefineTrait(this);
}
void BismuthParser::DefineTraitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefineTrait(this);
}

std::any BismuthParser::DefineTraitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitDefineTrait(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DefineFunctionContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::DefineFunctionContext::FUNC() {
  return getToken(BismuthParser::FUNC, 0);
}

tree::TerminalNode* BismuthParser::DefineFunctionContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

BismuthParser::LambdaConstExprContext* BismuthParser::DefineFunctionContext::lambdaConstExpr() {
  return getRuleContext<BismuthParser::LambdaConstExprContext>(0);
}

BismuthParser::GenericTemplateContext* BismuthParser::DefineFunctionContext::genericTemplate() {
  return getRuleContext<BismuthParser::GenericTemplateContext>(0);
}

BismuthParser::DefineFunctionContext::DefineFunctionContext(DefineTypeContext *ctx) { copyFrom(ctx); }

void BismuthParser::DefineFunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefineFunction(this);
}
void BismuthParser::DefineFunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefineFunction(this);
}

std::any BismuthParser::DefineFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitDefineFunction(this);
  else
    return visitor->visitChildren(this);
}
BismuthParser::DefineTypeContext* BismuthParser::defineType() {
  DefineTypeContext *_localctx = _tracker.createInstance<DefineTypeContext>(_ctx, getState());
  enterRule(_localctx, 12, BismuthParser::RuleDefineType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(190);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BismuthParser::ENUM: {
        _localctx = _tracker.createInstance<BismuthParser::DefineEnumContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(126);
        match(BismuthParser::ENUM);
        setState(127);
        antlrcpp::downCast<DefineEnumContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
        setState(129);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::LESS) {
          setState(128);
          genericTemplate();
        }
        setState(131);
        match(BismuthParser::LSQB);
        setState(132);
        antlrcpp::downCast<DefineEnumContext *>(_localctx)->typeContext = type(0);
        antlrcpp::downCast<DefineEnumContext *>(_localctx)->cases.push_back(antlrcpp::downCast<DefineEnumContext *>(_localctx)->typeContext);
        setState(135); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(133);
          match(BismuthParser::COMMA);
          setState(134);
          antlrcpp::downCast<DefineEnumContext *>(_localctx)->typeContext = type(0);
          antlrcpp::downCast<DefineEnumContext *>(_localctx)->cases.push_back(antlrcpp::downCast<DefineEnumContext *>(_localctx)->typeContext);
          setState(137); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == BismuthParser::COMMA);
        setState(139);
        match(BismuthParser::RSQB);
        break;
      }

      case BismuthParser::STRUCT: {
        _localctx = _tracker.createInstance<BismuthParser::DefineStructContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(141);
        match(BismuthParser::STRUCT);
        setState(142);
        antlrcpp::downCast<DefineStructContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
        setState(144);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::LESS) {
          setState(143);
          genericTemplate();
        }
        setState(146);
        match(BismuthParser::LSQB);
        setState(150);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (((((_la - 46) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 46)) & ((1ULL << (BismuthParser::LPAR - 46))
          | (1ULL << (BismuthParser::TYPE_INT - 46))
          | (1ULL << (BismuthParser::TYPE_I32 - 46))
          | (1ULL << (BismuthParser::TYPE_U32 - 46))
          | (1ULL << (BismuthParser::TYPE_I64 - 46))
          | (1ULL << (BismuthParser::TYPE_U64 - 46))
          | (1ULL << (BismuthParser::TYPE_BOOL - 46))
          | (1ULL << (BismuthParser::TYPE_STR - 46))
          | (1ULL << (BismuthParser::TYPE_UNIT - 46))
          | (1ULL << (BismuthParser::TYPE_BOX - 46))
          | (1ULL << (BismuthParser::TYPE_PROGRAM - 46))
          | (1ULL << (BismuthParser::TYPE_CHANNEL - 46))
          | (1ULL << (BismuthParser::VARIABLE - 46)))) != 0)) {
          setState(147);
          antlrcpp::downCast<DefineStructContext *>(_localctx)->structCaseContext = structCase();
          antlrcpp::downCast<DefineStructContext *>(_localctx)->cases.push_back(antlrcpp::downCast<DefineStructContext *>(_localctx)->structCaseContext);
          setState(152);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(153);
        match(BismuthParser::RSQB);
        setState(155);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::IMPLS) {
          setState(154);
          inherentTraitSpec();
        }
        break;
      }

      case BismuthParser::PROG: {
        _localctx = _tracker.createInstance<BismuthParser::DefineProgramContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(157);
        match(BismuthParser::PROG);
        setState(158);
        antlrcpp::downCast<DefineProgramContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
        setState(160);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::LESS) {
          setState(159);
          genericTemplate();
        }
        setState(162);
        match(BismuthParser::T__1);
        setState(163);
        antlrcpp::downCast<DefineProgramContext *>(_localctx)->channelName = match(BismuthParser::VARIABLE);
        setState(164);
        match(BismuthParser::COLON);
        setState(165);
        antlrcpp::downCast<DefineProgramContext *>(_localctx)->proto = protocol();
        setState(167);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::T__2) {
          setState(166);
          match(BismuthParser::T__2);
        }
        setState(169);
        block();
        break;
      }

      case BismuthParser::FUNC: {
        _localctx = _tracker.createInstance<BismuthParser::DefineFunctionContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(171);
        match(BismuthParser::FUNC);
        setState(172);
        antlrcpp::downCast<DefineFunctionContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
        setState(174);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::LESS) {
          setState(173);
          genericTemplate();
        }
        setState(176);
        antlrcpp::downCast<DefineFunctionContext *>(_localctx)->lam = lambdaConstExpr();
        break;
      }

      case BismuthParser::TRAIT: {
        _localctx = _tracker.createInstance<BismuthParser::DefineTraitContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(177);
        match(BismuthParser::TRAIT);
        setState(178);
        antlrcpp::downCast<DefineTraitContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
        setState(180);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::LESS) {
          setState(179);
          genericTemplate();
        }
        setState(182);
        match(BismuthParser::LSQB);
        setState(186);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == BismuthParser::VARIABLE) {
          setState(183);
          traitEntry();
          setState(188);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(189);
        match(BismuthParser::RSQB);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InherentTraitSpecContext ------------------------------------------------------------------

BismuthParser::InherentTraitSpecContext::InherentTraitSpecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::InherentTraitSpecContext::IMPLS() {
  return getToken(BismuthParser::IMPLS, 0);
}

tree::TerminalNode* BismuthParser::InherentTraitSpecContext::AUTO() {
  return getToken(BismuthParser::AUTO, 0);
}

std::vector<BismuthParser::PathContext *> BismuthParser::InherentTraitSpecContext::path() {
  return getRuleContexts<BismuthParser::PathContext>();
}

BismuthParser::PathContext* BismuthParser::InherentTraitSpecContext::path(size_t i) {
  return getRuleContext<BismuthParser::PathContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::InherentTraitSpecContext::COMMA() {
  return getTokens(BismuthParser::COMMA);
}

tree::TerminalNode* BismuthParser::InherentTraitSpecContext::COMMA(size_t i) {
  return getToken(BismuthParser::COMMA, i);
}


size_t BismuthParser::InherentTraitSpecContext::getRuleIndex() const {
  return BismuthParser::RuleInherentTraitSpec;
}

void BismuthParser::InherentTraitSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInherentTraitSpec(this);
}

void BismuthParser::InherentTraitSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInherentTraitSpec(this);
}


std::any BismuthParser::InherentTraitSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitInherentTraitSpec(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::InherentTraitSpecContext* BismuthParser::inherentTraitSpec() {
  InherentTraitSpecContext *_localctx = _tracker.createInstance<InherentTraitSpecContext>(_ctx, getState());
  enterRule(_localctx, 14, BismuthParser::RuleInherentTraitSpec);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(192);
    match(BismuthParser::IMPLS);
    setState(195);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BismuthParser::AUTO: {
        setState(193);
        match(BismuthParser::AUTO);
        break;
      }

      case BismuthParser::VARIABLE: {
        setState(194);
        path();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(199); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(197);
      match(BismuthParser::COMMA);
      setState(198);
      path();
      setState(201); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == BismuthParser::COMMA);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExternStatementContext ------------------------------------------------------------------

BismuthParser::ExternStatementContext::ExternStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::ExternStatementContext::EXTERN() {
  return getToken(BismuthParser::EXTERN, 0);
}

tree::TerminalNode* BismuthParser::ExternStatementContext::FUNC() {
  return getToken(BismuthParser::FUNC, 0);
}

tree::TerminalNode* BismuthParser::ExternStatementContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::ExternStatementContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

tree::TerminalNode* BismuthParser::ExternStatementContext::SEMICOLON() {
  return getToken(BismuthParser::SEMICOLON, 0);
}

tree::TerminalNode* BismuthParser::ExternStatementContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

tree::TerminalNode* BismuthParser::ExternStatementContext::ELLIPSIS() {
  return getToken(BismuthParser::ELLIPSIS, 0);
}

tree::TerminalNode* BismuthParser::ExternStatementContext::MAPS_TO() {
  return getToken(BismuthParser::MAPS_TO, 0);
}

BismuthParser::TypeContext* BismuthParser::ExternStatementContext::type() {
  return getRuleContext<BismuthParser::TypeContext>(0);
}

BismuthParser::ParameterListContext* BismuthParser::ExternStatementContext::parameterList() {
  return getRuleContext<BismuthParser::ParameterListContext>(0);
}

tree::TerminalNode* BismuthParser::ExternStatementContext::VariadicParam() {
  return getToken(BismuthParser::VariadicParam, 0);
}


size_t BismuthParser::ExternStatementContext::getRuleIndex() const {
  return BismuthParser::RuleExternStatement;
}

void BismuthParser::ExternStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExternStatement(this);
}

void BismuthParser::ExternStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExternStatement(this);
}


std::any BismuthParser::ExternStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitExternStatement(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::ExternStatementContext* BismuthParser::externStatement() {
  ExternStatementContext *_localctx = _tracker.createInstance<ExternStatementContext>(_ctx, getState());
  enterRule(_localctx, 16, BismuthParser::RuleExternStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(203);
    match(BismuthParser::EXTERN);
    setState(204);
    match(BismuthParser::FUNC);
    setState(205);
    antlrcpp::downCast<ExternStatementContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
    setState(206);
    match(BismuthParser::LPAR);
    setState(212);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BismuthParser::VariadicParam:
      case BismuthParser::LPAR:
      case BismuthParser::RPAR:
      case BismuthParser::TYPE_INT:
      case BismuthParser::TYPE_I32:
      case BismuthParser::TYPE_U32:
      case BismuthParser::TYPE_I64:
      case BismuthParser::TYPE_U64:
      case BismuthParser::TYPE_BOOL:
      case BismuthParser::TYPE_STR:
      case BismuthParser::TYPE_UNIT:
      case BismuthParser::TYPE_BOX:
      case BismuthParser::TYPE_PROGRAM:
      case BismuthParser::TYPE_CHANNEL:
      case BismuthParser::VARIABLE: {
        setState(207);
        antlrcpp::downCast<ExternStatementContext *>(_localctx)->paramList = parameterList();
        setState(209);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::VariadicParam) {
          setState(208);
          antlrcpp::downCast<ExternStatementContext *>(_localctx)->variadic = match(BismuthParser::VariadicParam);
        }
        break;
      }

      case BismuthParser::ELLIPSIS: {
        setState(211);
        match(BismuthParser::ELLIPSIS);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(214);
    match(BismuthParser::RPAR);
    setState(217);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BismuthParser::MAPS_TO) {
      setState(215);
      match(BismuthParser::MAPS_TO);
      setState(216);
      antlrcpp::downCast<ExternStatementContext *>(_localctx)->ret = type(0);
    }
    setState(219);
    match(BismuthParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PathElementContext ------------------------------------------------------------------

BismuthParser::PathElementContext::PathElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::PathElementContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

BismuthParser::GenericSpecifierContext* BismuthParser::PathElementContext::genericSpecifier() {
  return getRuleContext<BismuthParser::GenericSpecifierContext>(0);
}


size_t BismuthParser::PathElementContext::getRuleIndex() const {
  return BismuthParser::RulePathElement;
}

void BismuthParser::PathElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPathElement(this);
}

void BismuthParser::PathElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPathElement(this);
}


std::any BismuthParser::PathElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitPathElement(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::PathElementContext* BismuthParser::pathElement() {
  PathElementContext *_localctx = _tracker.createInstance<PathElementContext>(_ctx, getState());
  enterRule(_localctx, 18, BismuthParser::RulePathElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(221);
    antlrcpp::downCast<PathElementContext *>(_localctx)->id = match(BismuthParser::VARIABLE);
    setState(223);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      setState(222);
      genericSpecifier();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PathContext ------------------------------------------------------------------

BismuthParser::PathContext::PathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BismuthParser::PathElementContext *> BismuthParser::PathContext::pathElement() {
  return getRuleContexts<BismuthParser::PathElementContext>();
}

BismuthParser::PathElementContext* BismuthParser::PathContext::pathElement(size_t i) {
  return getRuleContext<BismuthParser::PathElementContext>(i);
}


size_t BismuthParser::PathContext::getRuleIndex() const {
  return BismuthParser::RulePath;
}

void BismuthParser::PathContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPath(this);
}

void BismuthParser::PathContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPath(this);
}


std::any BismuthParser::PathContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitPath(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::PathContext* BismuthParser::path() {
  PathContext *_localctx = _tracker.createInstance<PathContext>(_ctx, getState());
  enterRule(_localctx, 20, BismuthParser::RulePath);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(225);
    antlrcpp::downCast<PathContext *>(_localctx)->pathElementContext = pathElement();
    antlrcpp::downCast<PathContext *>(_localctx)->eles.push_back(antlrcpp::downCast<PathContext *>(_localctx)->pathElementContext);
    setState(230);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(226);
        match(BismuthParser::T__1);
        setState(227);
        antlrcpp::downCast<PathContext *>(_localctx)->pathElementContext = pathElement();
        antlrcpp::downCast<PathContext *>(_localctx)->eles.push_back(antlrcpp::downCast<PathContext *>(_localctx)->pathElementContext); 
      }
      setState(232);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportStatementContext ------------------------------------------------------------------

BismuthParser::ImportStatementContext::ImportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::ImportStatementContext::IMPORT() {
  return getToken(BismuthParser::IMPORT, 0);
}

BismuthParser::PathContext* BismuthParser::ImportStatementContext::path() {
  return getRuleContext<BismuthParser::PathContext>(0);
}

tree::TerminalNode* BismuthParser::ImportStatementContext::SEMICOLON() {
  return getToken(BismuthParser::SEMICOLON, 0);
}

tree::TerminalNode* BismuthParser::ImportStatementContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}


size_t BismuthParser::ImportStatementContext::getRuleIndex() const {
  return BismuthParser::RuleImportStatement;
}

void BismuthParser::ImportStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportStatement(this);
}

void BismuthParser::ImportStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportStatement(this);
}


std::any BismuthParser::ImportStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitImportStatement(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::ImportStatementContext* BismuthParser::importStatement() {
  ImportStatementContext *_localctx = _tracker.createInstance<ImportStatementContext>(_ctx, getState());
  enterRule(_localctx, 22, BismuthParser::RuleImportStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(233);
    match(BismuthParser::IMPORT);
    setState(234);
    path();
    setState(237);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BismuthParser::T__3) {
      setState(235);
      match(BismuthParser::T__3);
      setState(236);
      antlrcpp::downCast<ImportStatementContext *>(_localctx)->alias = match(BismuthParser::VARIABLE);
    }
    setState(240);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BismuthParser::SEMICOLON) {
      setState(239);
      match(BismuthParser::SEMICOLON);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Inv_argsContext ------------------------------------------------------------------

BismuthParser::Inv_argsContext::Inv_argsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::Inv_argsContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::Inv_argsContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

std::vector<BismuthParser::ExpressionContext *> BismuthParser::Inv_argsContext::expression() {
  return getRuleContexts<BismuthParser::ExpressionContext>();
}

BismuthParser::ExpressionContext* BismuthParser::Inv_argsContext::expression(size_t i) {
  return getRuleContext<BismuthParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::Inv_argsContext::COMMA() {
  return getTokens(BismuthParser::COMMA);
}

tree::TerminalNode* BismuthParser::Inv_argsContext::COMMA(size_t i) {
  return getToken(BismuthParser::COMMA, i);
}


size_t BismuthParser::Inv_argsContext::getRuleIndex() const {
  return BismuthParser::RuleInv_args;
}

void BismuthParser::Inv_argsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInv_args(this);
}

void BismuthParser::Inv_argsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInv_args(this);
}


std::any BismuthParser::Inv_argsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitInv_args(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::Inv_argsContext* BismuthParser::inv_args() {
  Inv_argsContext *_localctx = _tracker.createInstance<Inv_argsContext>(_ctx, getState());
  enterRule(_localctx, 24, BismuthParser::RuleInv_args);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(242);
    match(BismuthParser::LPAR);
    setState(251);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << BismuthParser::T__8)
      | (1ULL << BismuthParser::MINUS)
      | (1ULL << BismuthParser::NOT)
      | (1ULL << BismuthParser::MULTIPLY)
      | (1ULL << BismuthParser::BIT_NOT)
      | (1ULL << BismuthParser::LPAR)
      | (1ULL << BismuthParser::LBRC)
      | (1ULL << BismuthParser::DEC_LITERAL)
      | (1ULL << BismuthParser::HEX_LITERAL)
      | (1ULL << BismuthParser::BIN_LITERAL))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 69)) & ((1ULL << (BismuthParser::TYPE_BOX - 69))
      | (1ULL << (BismuthParser::EXEC - 69))
      | (1ULL << (BismuthParser::COPY - 69))
      | (1ULL << (BismuthParser::FALSE - 69))
      | (1ULL << (BismuthParser::TRUE - 69))
      | (1ULL << (BismuthParser::STRING - 69))
      | (1ULL << (BismuthParser::VARIABLE - 69)))) != 0)) {
      setState(243);
      antlrcpp::downCast<Inv_argsContext *>(_localctx)->expressionContext = expression(0);
      antlrcpp::downCast<Inv_argsContext *>(_localctx)->args.push_back(antlrcpp::downCast<Inv_argsContext *>(_localctx)->expressionContext);
      setState(248);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == BismuthParser::COMMA) {
        setState(244);
        match(BismuthParser::COMMA);
        setState(245);
        antlrcpp::downCast<Inv_argsContext *>(_localctx)->expressionContext = expression(0);
        antlrcpp::downCast<Inv_argsContext *>(_localctx)->args.push_back(antlrcpp::downCast<Inv_argsContext *>(_localctx)->expressionContext);
        setState(250);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(253);
    match(BismuthParser::RPAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

BismuthParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t BismuthParser::ExpressionContext::getRuleIndex() const {
  return BismuthParser::RuleExpression;
}

void BismuthParser::ExpressionContext::copyFrom(ExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AssignableIsPresentContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::AssignableIsPresentContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::AssignableIsPresentContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

tree::TerminalNode* BismuthParser::AssignableIsPresentContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

BismuthParser::AssignableIsPresentContext::AssignableIsPresentContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::AssignableIsPresentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignableIsPresent(this);
}
void BismuthParser::AssignableIsPresentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignableIsPresent(this);
}

std::any BismuthParser::AssignableIsPresentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitAssignableIsPresent(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CopyExprContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::CopyExprContext::COPY() {
  return getToken(BismuthParser::COPY, 0);
}

tree::TerminalNode* BismuthParser::CopyExprContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::CopyExprContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

BismuthParser::ExpressionContext* BismuthParser::CopyExprContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}

BismuthParser::CopyExprContext::CopyExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::CopyExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCopyExpr(this);
}
void BismuthParser::CopyExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCopyExpr(this);
}

std::any BismuthParser::CopyExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitCopyExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IConstExprContext ------------------------------------------------------------------

BismuthParser::IntegerValueContext* BismuthParser::IConstExprContext::integerValue() {
  return getRuleContext<BismuthParser::IntegerValueContext>(0);
}

BismuthParser::IConstExprContext::IConstExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::IConstExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIConstExpr(this);
}
void BismuthParser::IConstExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIConstExpr(this);
}

std::any BismuthParser::IConstExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitIConstExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayAccessContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ArrayAccessContext::LBRC() {
  return getToken(BismuthParser::LBRC, 0);
}

tree::TerminalNode* BismuthParser::ArrayAccessContext::RBRC() {
  return getToken(BismuthParser::RBRC, 0);
}

std::vector<BismuthParser::ExpressionContext *> BismuthParser::ArrayAccessContext::expression() {
  return getRuleContexts<BismuthParser::ExpressionContext>();
}

BismuthParser::ExpressionContext* BismuthParser::ArrayAccessContext::expression(size_t i) {
  return getRuleContext<BismuthParser::ExpressionContext>(i);
}

BismuthParser::ArrayAccessContext::ArrayAccessContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::ArrayAccessContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayAccess(this);
}
void BismuthParser::ArrayAccessContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayAccess(this);
}

std::any BismuthParser::ArrayAccessContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitArrayAccess(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BinaryArithExprContext ------------------------------------------------------------------

std::vector<BismuthParser::ExpressionContext *> BismuthParser::BinaryArithExprContext::expression() {
  return getRuleContexts<BismuthParser::ExpressionContext>();
}

BismuthParser::ExpressionContext* BismuthParser::BinaryArithExprContext::expression(size_t i) {
  return getRuleContext<BismuthParser::ExpressionContext>(i);
}

tree::TerminalNode* BismuthParser::BinaryArithExprContext::MULTIPLY() {
  return getToken(BismuthParser::MULTIPLY, 0);
}

tree::TerminalNode* BismuthParser::BinaryArithExprContext::DIVIDE() {
  return getToken(BismuthParser::DIVIDE, 0);
}

tree::TerminalNode* BismuthParser::BinaryArithExprContext::MOD() {
  return getToken(BismuthParser::MOD, 0);
}

tree::TerminalNode* BismuthParser::BinaryArithExprContext::PLUS() {
  return getToken(BismuthParser::PLUS, 0);
}

tree::TerminalNode* BismuthParser::BinaryArithExprContext::MINUS() {
  return getToken(BismuthParser::MINUS, 0);
}

BismuthParser::ShiftOpContext* BismuthParser::BinaryArithExprContext::shiftOp() {
  return getRuleContext<BismuthParser::ShiftOpContext>(0);
}

tree::TerminalNode* BismuthParser::BinaryArithExprContext::BIT_AND() {
  return getToken(BismuthParser::BIT_AND, 0);
}

tree::TerminalNode* BismuthParser::BinaryArithExprContext::BIT_OR() {
  return getToken(BismuthParser::BIT_OR, 0);
}

tree::TerminalNode* BismuthParser::BinaryArithExprContext::BIT_XOR() {
  return getToken(BismuthParser::BIT_XOR, 0);
}

BismuthParser::BinaryArithExprContext::BinaryArithExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::BinaryArithExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBinaryArithExpr(this);
}
void BismuthParser::BinaryArithExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBinaryArithExpr(this);
}

std::any BismuthParser::BinaryArithExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitBinaryArithExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdentifierExprContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::IdentifierExprContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

BismuthParser::IdentifierExprContext::IdentifierExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::IdentifierExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifierExpr(this);
}
void BismuthParser::IdentifierExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifierExpr(this);
}

std::any BismuthParser::IdentifierExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitIdentifierExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CallExprContext ------------------------------------------------------------------

BismuthParser::Inv_argsContext* BismuthParser::CallExprContext::inv_args() {
  return getRuleContext<BismuthParser::Inv_argsContext>(0);
}

BismuthParser::ExpressionContext* BismuthParser::CallExprContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}

BismuthParser::CallExprContext::CallExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::CallExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCallExpr(this);
}
void BismuthParser::CallExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCallExpr(this);
}

std::any BismuthParser::CallExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitCallExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FieldAccessExprContext ------------------------------------------------------------------

BismuthParser::ExpressionContext* BismuthParser::FieldAccessExprContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}

std::vector<tree::TerminalNode *> BismuthParser::FieldAccessExprContext::VARIABLE() {
  return getTokens(BismuthParser::VARIABLE);
}

tree::TerminalNode* BismuthParser::FieldAccessExprContext::VARIABLE(size_t i) {
  return getToken(BismuthParser::VARIABLE, i);
}

BismuthParser::FieldAccessExprContext::FieldAccessExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::FieldAccessExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFieldAccessExpr(this);
}
void BismuthParser::FieldAccessExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFieldAccessExpr(this);
}

std::any BismuthParser::FieldAccessExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitFieldAccessExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BinaryRelExprContext ------------------------------------------------------------------

std::vector<BismuthParser::ExpressionContext *> BismuthParser::BinaryRelExprContext::expression() {
  return getRuleContexts<BismuthParser::ExpressionContext>();
}

BismuthParser::ExpressionContext* BismuthParser::BinaryRelExprContext::expression(size_t i) {
  return getRuleContext<BismuthParser::ExpressionContext>(i);
}

tree::TerminalNode* BismuthParser::BinaryRelExprContext::LESS() {
  return getToken(BismuthParser::LESS, 0);
}

tree::TerminalNode* BismuthParser::BinaryRelExprContext::LESS_EQ() {
  return getToken(BismuthParser::LESS_EQ, 0);
}

tree::TerminalNode* BismuthParser::BinaryRelExprContext::GREATER() {
  return getToken(BismuthParser::GREATER, 0);
}

tree::TerminalNode* BismuthParser::BinaryRelExprContext::GREATER_EQ() {
  return getToken(BismuthParser::GREATER_EQ, 0);
}

BismuthParser::BinaryRelExprContext::BinaryRelExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::BinaryRelExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBinaryRelExpr(this);
}
void BismuthParser::BinaryRelExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBinaryRelExpr(this);
}

std::any BismuthParser::BinaryRelExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitBinaryRelExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignableRecvContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::AssignableRecvContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::AssignableRecvContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

tree::TerminalNode* BismuthParser::AssignableRecvContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

BismuthParser::AssignableRecvContext::AssignableRecvContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::AssignableRecvContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignableRecv(this);
}
void BismuthParser::AssignableRecvContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignableRecv(this);
}

std::any BismuthParser::AssignableRecvContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitAssignableRecv(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InitBoxContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::InitBoxContext::TYPE_BOX() {
  return getToken(BismuthParser::TYPE_BOX, 0);
}

tree::TerminalNode* BismuthParser::InitBoxContext::LESS() {
  return getToken(BismuthParser::LESS, 0);
}

tree::TerminalNode* BismuthParser::InitBoxContext::GREATER() {
  return getToken(BismuthParser::GREATER, 0);
}

tree::TerminalNode* BismuthParser::InitBoxContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::InitBoxContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

BismuthParser::TypeContext* BismuthParser::InitBoxContext::type() {
  return getRuleContext<BismuthParser::TypeContext>(0);
}

BismuthParser::ExpressionContext* BismuthParser::InitBoxContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}

BismuthParser::InitBoxContext::InitBoxContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::InitBoxContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitBox(this);
}
void BismuthParser::InitBoxContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitBox(this);
}

std::any BismuthParser::InitBoxContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitInitBox(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LambdaExprContext ------------------------------------------------------------------

BismuthParser::LambdaConstExprContext* BismuthParser::LambdaExprContext::lambdaConstExpr() {
  return getRuleContext<BismuthParser::LambdaConstExprContext>(0);
}

BismuthParser::LambdaExprContext::LambdaExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::LambdaExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLambdaExpr(this);
}
void BismuthParser::LambdaExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLambdaExpr(this);
}

std::any BismuthParser::LambdaExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitLambdaExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AsChannelExprContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::AsChannelExprContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::AsChannelExprContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

BismuthParser::ExpressionContext* BismuthParser::AsChannelExprContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}

BismuthParser::AsChannelExprContext::AsChannelExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::AsChannelExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAsChannelExpr(this);
}
void BismuthParser::AsChannelExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAsChannelExpr(this);
}

std::any BismuthParser::AsChannelExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitAsChannelExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SConstExprContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::SConstExprContext::STRING() {
  return getToken(BismuthParser::STRING, 0);
}

BismuthParser::SConstExprContext::SConstExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::SConstExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSConstExpr(this);
}
void BismuthParser::SConstExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSConstExpr(this);
}

std::any BismuthParser::SConstExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitSConstExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExprContext ------------------------------------------------------------------

BismuthParser::ExpressionContext* BismuthParser::UnaryExprContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}

tree::TerminalNode* BismuthParser::UnaryExprContext::MINUS() {
  return getToken(BismuthParser::MINUS, 0);
}

tree::TerminalNode* BismuthParser::UnaryExprContext::NOT() {
  return getToken(BismuthParser::NOT, 0);
}

tree::TerminalNode* BismuthParser::UnaryExprContext::BIT_NOT() {
  return getToken(BismuthParser::BIT_NOT, 0);
}

BismuthParser::UnaryExprContext::UnaryExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::UnaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpr(this);
}
void BismuthParser::UnaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpr(this);
}

std::any BismuthParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignableExecContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::AssignableExecContext::EXEC() {
  return getToken(BismuthParser::EXEC, 0);
}

BismuthParser::ExpressionContext* BismuthParser::AssignableExecContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}

BismuthParser::AssignableExecContext::AssignableExecContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::AssignableExecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignableExec(this);
}
void BismuthParser::AssignableExecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignableExec(this);
}

std::any BismuthParser::AssignableExecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitAssignableExec(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EqExprContext ------------------------------------------------------------------

std::vector<BismuthParser::ExpressionContext *> BismuthParser::EqExprContext::expression() {
  return getRuleContexts<BismuthParser::ExpressionContext>();
}

BismuthParser::ExpressionContext* BismuthParser::EqExprContext::expression(size_t i) {
  return getRuleContext<BismuthParser::ExpressionContext>(i);
}

tree::TerminalNode* BismuthParser::EqExprContext::EQUAL() {
  return getToken(BismuthParser::EQUAL, 0);
}

tree::TerminalNode* BismuthParser::EqExprContext::NOT_EQUAL() {
  return getToken(BismuthParser::NOT_EQUAL, 0);
}

BismuthParser::EqExprContext::EqExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::EqExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqExpr(this);
}
void BismuthParser::EqExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqExpr(this);
}

std::any BismuthParser::EqExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitEqExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogAndExprContext ------------------------------------------------------------------

std::vector<BismuthParser::ExpressionContext *> BismuthParser::LogAndExprContext::expression() {
  return getRuleContexts<BismuthParser::ExpressionContext>();
}

BismuthParser::ExpressionContext* BismuthParser::LogAndExprContext::expression(size_t i) {
  return getRuleContext<BismuthParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::LogAndExprContext::LOG_AND() {
  return getTokens(BismuthParser::LOG_AND);
}

tree::TerminalNode* BismuthParser::LogAndExprContext::LOG_AND(size_t i) {
  return getToken(BismuthParser::LOG_AND, i);
}

BismuthParser::LogAndExprContext::LogAndExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::LogAndExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogAndExpr(this);
}
void BismuthParser::LogAndExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogAndExpr(this);
}

std::any BismuthParser::LogAndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitLogAndExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogOrExprContext ------------------------------------------------------------------

std::vector<BismuthParser::ExpressionContext *> BismuthParser::LogOrExprContext::expression() {
  return getRuleContexts<BismuthParser::ExpressionContext>();
}

BismuthParser::ExpressionContext* BismuthParser::LogOrExprContext::expression(size_t i) {
  return getRuleContext<BismuthParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::LogOrExprContext::LOG_OR() {
  return getTokens(BismuthParser::LOG_OR);
}

tree::TerminalNode* BismuthParser::LogOrExprContext::LOG_OR(size_t i) {
  return getToken(BismuthParser::LOG_OR, i);
}

BismuthParser::LogOrExprContext::LogOrExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::LogOrExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogOrExpr(this);
}
void BismuthParser::LogOrExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogOrExpr(this);
}

std::any BismuthParser::LogOrExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitLogOrExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayExpressionContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ArrayExpressionContext::LBRC() {
  return getToken(BismuthParser::LBRC, 0);
}

tree::TerminalNode* BismuthParser::ArrayExpressionContext::RBRC() {
  return getToken(BismuthParser::RBRC, 0);
}

std::vector<BismuthParser::ExpressionContext *> BismuthParser::ArrayExpressionContext::expression() {
  return getRuleContexts<BismuthParser::ExpressionContext>();
}

BismuthParser::ExpressionContext* BismuthParser::ArrayExpressionContext::expression(size_t i) {
  return getRuleContext<BismuthParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::ArrayExpressionContext::COMMA() {
  return getTokens(BismuthParser::COMMA);
}

tree::TerminalNode* BismuthParser::ArrayExpressionContext::COMMA(size_t i) {
  return getToken(BismuthParser::COMMA, i);
}

BismuthParser::ArrayExpressionContext::ArrayExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::ArrayExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayExpression(this);
}
void BismuthParser::ArrayExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayExpression(this);
}

std::any BismuthParser::ArrayExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitArrayExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InitProductContext ------------------------------------------------------------------

BismuthParser::PathContext* BismuthParser::InitProductContext::path() {
  return getRuleContext<BismuthParser::PathContext>(0);
}

tree::TerminalNode* BismuthParser::InitProductContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::InitProductContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

std::vector<BismuthParser::ExpressionContext *> BismuthParser::InitProductContext::expression() {
  return getRuleContexts<BismuthParser::ExpressionContext>();
}

BismuthParser::ExpressionContext* BismuthParser::InitProductContext::expression(size_t i) {
  return getRuleContext<BismuthParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::InitProductContext::COMMA() {
  return getTokens(BismuthParser::COMMA);
}

tree::TerminalNode* BismuthParser::InitProductContext::COMMA(size_t i) {
  return getToken(BismuthParser::COMMA, i);
}

BismuthParser::InitProductContext::InitProductContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::InitProductContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitProduct(this);
}
void BismuthParser::InitProductContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitProduct(this);
}

std::any BismuthParser::InitProductContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitInitProduct(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenExprContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ParenExprContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::ParenExprContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

BismuthParser::ExpressionContext* BismuthParser::ParenExprContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}

BismuthParser::ParenExprContext::ParenExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::ParenExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParenExpr(this);
}
void BismuthParser::ParenExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParenExpr(this);
}

std::any BismuthParser::ParenExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitParenExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PathExprContext ------------------------------------------------------------------

BismuthParser::PathContext* BismuthParser::PathExprContext::path() {
  return getRuleContext<BismuthParser::PathContext>(0);
}

BismuthParser::PathExprContext::PathExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::PathExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPathExpr(this);
}
void BismuthParser::PathExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPathExpr(this);
}

std::any BismuthParser::PathExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitPathExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DerefContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::DerefContext::MULTIPLY() {
  return getToken(BismuthParser::MULTIPLY, 0);
}

BismuthParser::ExpressionContext* BismuthParser::DerefContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}

BismuthParser::DerefContext::DerefContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::DerefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeref(this);
}
void BismuthParser::DerefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeref(this);
}

std::any BismuthParser::DerefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitDeref(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BConstExprContext ------------------------------------------------------------------

BismuthParser::BooleanConstContext* BismuthParser::BConstExprContext::booleanConst() {
  return getRuleContext<BismuthParser::BooleanConstContext>(0);
}

BismuthParser::BConstExprContext::BConstExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void BismuthParser::BConstExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBConstExpr(this);
}
void BismuthParser::BConstExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBConstExpr(this);
}

std::any BismuthParser::BConstExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitBConstExpr(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::ExpressionContext* BismuthParser::expression() {
   return expression(0);
}

BismuthParser::ExpressionContext* BismuthParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  BismuthParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  BismuthParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 26;
  enterRecursionRule(_localctx, 26, BismuthParser::RuleExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(329);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ParenExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(256);
      match(BismuthParser::LPAR);
      setState(257);
      antlrcpp::downCast<ParenExprContext *>(_localctx)->ex = expression(0);
      setState(258);
      match(BismuthParser::RPAR);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ArrayExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(260);
      match(BismuthParser::LBRC);
      setState(270);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << BismuthParser::T__8)
        | (1ULL << BismuthParser::MINUS)
        | (1ULL << BismuthParser::NOT)
        | (1ULL << BismuthParser::MULTIPLY)
        | (1ULL << BismuthParser::BIT_NOT)
        | (1ULL << BismuthParser::LPAR)
        | (1ULL << BismuthParser::LBRC)
        | (1ULL << BismuthParser::DEC_LITERAL)
        | (1ULL << BismuthParser::HEX_LITERAL)
        | (1ULL << BismuthParser::BIN_LITERAL))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 69)) & ((1ULL << (BismuthParser::TYPE_BOX - 69))
        | (1ULL << (BismuthParser::EXEC - 69))
        | (1ULL << (BismuthParser::COPY - 69))
        | (1ULL << (BismuthParser::FALSE - 69))
        | (1ULL << (BismuthParser::TRUE - 69))
        | (1ULL << (BismuthParser::STRING - 69))
        | (1ULL << (BismuthParser::VARIABLE - 69)))) != 0)) {
        setState(266);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(261);
            antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->expressionContext = expression(0);
            antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->elements.push_back(antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->expressionContext);
            setState(262);
            match(BismuthParser::COMMA); 
          }
          setState(268);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
        }
        setState(269);
        antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->expressionContext = expression(0);
        antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->elements.push_back(antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->expressionContext);
      }
      setState(272);
      match(BismuthParser::RBRC);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<IdentifierExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(273);
      match(BismuthParser::VARIABLE);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PathExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(274);
      path();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(275);
      antlrcpp::downCast<UnaryExprContext *>(_localctx)->op = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << BismuthParser::MINUS)
        | (1ULL << BismuthParser::NOT)
        | (1ULL << BismuthParser::BIT_NOT))) != 0))) {
        antlrcpp::downCast<UnaryExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(276);
      antlrcpp::downCast<UnaryExprContext *>(_localctx)->ex = expression(22);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<InitProductContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(277);
      path();
      setState(278);
      match(BismuthParser::T__5);
      setState(279);
      match(BismuthParser::LPAR);
      setState(288);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << BismuthParser::T__8)
        | (1ULL << BismuthParser::MINUS)
        | (1ULL << BismuthParser::NOT)
        | (1ULL << BismuthParser::MULTIPLY)
        | (1ULL << BismuthParser::BIT_NOT)
        | (1ULL << BismuthParser::LPAR)
        | (1ULL << BismuthParser::LBRC)
        | (1ULL << BismuthParser::DEC_LITERAL)
        | (1ULL << BismuthParser::HEX_LITERAL)
        | (1ULL << BismuthParser::BIN_LITERAL))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 69)) & ((1ULL << (BismuthParser::TYPE_BOX - 69))
        | (1ULL << (BismuthParser::EXEC - 69))
        | (1ULL << (BismuthParser::COPY - 69))
        | (1ULL << (BismuthParser::FALSE - 69))
        | (1ULL << (BismuthParser::TRUE - 69))
        | (1ULL << (BismuthParser::STRING - 69))
        | (1ULL << (BismuthParser::VARIABLE - 69)))) != 0)) {
        setState(280);
        antlrcpp::downCast<InitProductContext *>(_localctx)->expressionContext = expression(0);
        antlrcpp::downCast<InitProductContext *>(_localctx)->exprs.push_back(antlrcpp::downCast<InitProductContext *>(_localctx)->expressionContext);
        setState(285);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == BismuthParser::COMMA) {
          setState(281);
          match(BismuthParser::COMMA);
          setState(282);
          antlrcpp::downCast<InitProductContext *>(_localctx)->expressionContext = expression(0);
          antlrcpp::downCast<InitProductContext *>(_localctx)->exprs.push_back(antlrcpp::downCast<InitProductContext *>(_localctx)->expressionContext);
          setState(287);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(290);
      match(BismuthParser::RPAR);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<DerefContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(292);
      match(BismuthParser::MULTIPLY);
      setState(293);
      antlrcpp::downCast<DerefContext *>(_localctx)->expr = expression(12);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<InitBoxContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(294);
      match(BismuthParser::TYPE_BOX);
      setState(295);
      match(BismuthParser::LESS);
      setState(296);
      antlrcpp::downCast<InitBoxContext *>(_localctx)->ty = type(0);
      setState(297);
      match(BismuthParser::GREATER);
      setState(298);
      match(BismuthParser::T__5);
      setState(299);
      match(BismuthParser::LPAR);
      setState(300);
      antlrcpp::downCast<InitBoxContext *>(_localctx)->expr = expression(0);
      setState(301);
      match(BismuthParser::RPAR);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<BConstExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(303);
      booleanConst();
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<IConstExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(304);
      antlrcpp::downCast<IConstExprContext *>(_localctx)->i = integerValue();
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<SConstExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(305);
      antlrcpp::downCast<SConstExprContext *>(_localctx)->s = match(BismuthParser::STRING);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<LambdaExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(306);
      lambdaConstExpr();
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<AssignableRecvContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(307);
      antlrcpp::downCast<AssignableRecvContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(308);
      match(BismuthParser::T__6);
      setState(309);
      match(BismuthParser::LPAR);
      setState(310);
      match(BismuthParser::RPAR);
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<AssignableIsPresentContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(311);
      antlrcpp::downCast<AssignableIsPresentContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(312);
      match(BismuthParser::T__7);
      setState(313);
      match(BismuthParser::LPAR);
      setState(314);
      match(BismuthParser::RPAR);
      break;
    }

    case 15: {
      _localctx = _tracker.createInstance<AssignableExecContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(315);
      match(BismuthParser::EXEC);
      setState(316);
      antlrcpp::downCast<AssignableExecContext *>(_localctx)->prog = expression(4);
      break;
    }

    case 16: {
      _localctx = _tracker.createInstance<CopyExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(317);
      match(BismuthParser::COPY);
      setState(318);
      match(BismuthParser::LPAR);
      setState(319);
      antlrcpp::downCast<CopyExprContext *>(_localctx)->expr = expression(0);
      setState(320);
      match(BismuthParser::RPAR);
      break;
    }

    case 17: {
      _localctx = _tracker.createInstance<CopyExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(322);
      match(BismuthParser::COPY);
      setState(323);
      antlrcpp::downCast<CopyExprContext *>(_localctx)->expr = expression(2);
      break;
    }

    case 18: {
      _localctx = _tracker.createInstance<AsChannelExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(324);
      match(BismuthParser::T__8);
      setState(325);
      match(BismuthParser::LPAR);
      setState(326);
      antlrcpp::downCast<AsChannelExprContext *>(_localctx)->expr = expression(0);
      setState(327);
      match(BismuthParser::RPAR);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(380);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(378);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<BinaryArithExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(331);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(332);
          antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << BismuthParser::MULTIPLY)
            | (1ULL << BismuthParser::DIVIDE)
            | (1ULL << BismuthParser::MOD))) != 0))) {
            antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(333);
          antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->right = expression(22);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<BinaryArithExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(334);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(335);
          antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == BismuthParser::MINUS

          || _la == BismuthParser::PLUS)) {
            antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(336);
          antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->right = expression(21);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<BinaryArithExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(337);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(338);
          shiftOp();
          setState(339);
          antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->right = expression(20);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BinaryRelExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(341);

          if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
          setState(342);
          antlrcpp::downCast<BinaryRelExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << BismuthParser::LESS)
            | (1ULL << BismuthParser::LESS_EQ)
            | (1ULL << BismuthParser::GREATER_EQ)
            | (1ULL << BismuthParser::GREATER))) != 0))) {
            antlrcpp::downCast<BinaryRelExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(343);
          antlrcpp::downCast<BinaryRelExprContext *>(_localctx)->right = expression(19);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BinaryArithExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(344);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(345);
          antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << BismuthParser::BIT_AND)
            | (1ULL << BismuthParser::BIT_OR)
            | (1ULL << BismuthParser::BIT_XOR))) != 0))) {
            antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(346);
          antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->right = expression(18);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<EqExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(347);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(348);
          antlrcpp::downCast<EqExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == BismuthParser::EQUAL

          || _la == BismuthParser::NOT_EQUAL)) {
            antlrcpp::downCast<EqExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(349);
          antlrcpp::downCast<EqExprContext *>(_localctx)->right = expression(16);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<CallExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->expr = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(350);

          if (!(precpred(_ctx, 28))) throw FailedPredicateException(this, "precpred(_ctx, 28)");
          setState(351);
          inv_args();
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<ArrayAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->expr = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(352);

          if (!(precpred(_ctx, 27))) throw FailedPredicateException(this, "precpred(_ctx, 27)");
          setState(353);
          match(BismuthParser::LBRC);
          setState(354);
          antlrcpp::downCast<ArrayAccessContext *>(_localctx)->index = expression(0);
          setState(355);
          match(BismuthParser::RBRC);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<FieldAccessExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->expr = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(357);

          if (!(precpred(_ctx, 24))) throw FailedPredicateException(this, "precpred(_ctx, 24)");
          setState(360); 
          _errHandler->sync(this);
          alt = 1;
          do {
            switch (alt) {
              case 1: {
                    setState(358);
                    match(BismuthParser::T__4);
                    setState(359);
                    antlrcpp::downCast<FieldAccessExprContext *>(_localctx)->variableToken = match(BismuthParser::VARIABLE);
                    antlrcpp::downCast<FieldAccessExprContext *>(_localctx)->fields.push_back(antlrcpp::downCast<FieldAccessExprContext *>(_localctx)->variableToken);
                    break;
                  }

            default:
              throw NoViableAltException(this);
            }
            setState(362); 
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
          } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<LogAndExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->exprs.push_back(previousContext);
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(364);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(367); 
          _errHandler->sync(this);
          alt = 1;
          do {
            switch (alt) {
              case 1: {
                    setState(365);
                    match(BismuthParser::LOG_AND);
                    setState(366);
                    antlrcpp::downCast<LogAndExprContext *>(_localctx)->expressionContext = expression(0);
                    antlrcpp::downCast<LogAndExprContext *>(_localctx)->exprs.push_back(antlrcpp::downCast<LogAndExprContext *>(_localctx)->expressionContext);
                    break;
                  }

            default:
              throw NoViableAltException(this);
            }
            setState(369); 
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
          } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<LogOrExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->exprs.push_back(previousContext);
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(371);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(374); 
          _errHandler->sync(this);
          alt = 1;
          do {
            switch (alt) {
              case 1: {
                    setState(372);
                    match(BismuthParser::LOG_OR);
                    setState(373);
                    antlrcpp::downCast<LogOrExprContext *>(_localctx)->expressionContext = expression(0);
                    antlrcpp::downCast<LogOrExprContext *>(_localctx)->exprs.push_back(antlrcpp::downCast<LogOrExprContext *>(_localctx)->expressionContext);
                    break;
                  }

            default:
              throw NoViableAltException(this);
            }
            setState(376); 
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
          } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
          break;
        }

        default:
          break;
        } 
      }
      setState(382);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LambdaConstExprContext ------------------------------------------------------------------

BismuthParser::LambdaConstExprContext::LambdaConstExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::LambdaConstExprContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

BismuthParser::ParameterListContext* BismuthParser::LambdaConstExprContext::parameterList() {
  return getRuleContext<BismuthParser::ParameterListContext>(0);
}

tree::TerminalNode* BismuthParser::LambdaConstExprContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

BismuthParser::BlockContext* BismuthParser::LambdaConstExprContext::block() {
  return getRuleContext<BismuthParser::BlockContext>(0);
}

tree::TerminalNode* BismuthParser::LambdaConstExprContext::MAPS_TO() {
  return getToken(BismuthParser::MAPS_TO, 0);
}

BismuthParser::TypeContext* BismuthParser::LambdaConstExprContext::type() {
  return getRuleContext<BismuthParser::TypeContext>(0);
}


size_t BismuthParser::LambdaConstExprContext::getRuleIndex() const {
  return BismuthParser::RuleLambdaConstExpr;
}

void BismuthParser::LambdaConstExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLambdaConstExpr(this);
}

void BismuthParser::LambdaConstExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLambdaConstExpr(this);
}


std::any BismuthParser::LambdaConstExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitLambdaConstExpr(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::LambdaConstExprContext* BismuthParser::lambdaConstExpr() {
  LambdaConstExprContext *_localctx = _tracker.createInstance<LambdaConstExprContext>(_ctx, getState());
  enterRule(_localctx, 28, BismuthParser::RuleLambdaConstExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(383);
    match(BismuthParser::LPAR);
    setState(384);
    parameterList();
    setState(385);
    match(BismuthParser::RPAR);
    setState(388);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BismuthParser::MAPS_TO) {
      setState(386);
      match(BismuthParser::MAPS_TO);
      setState(387);
      antlrcpp::downCast<LambdaConstExprContext *>(_localctx)->ret = type(0);
    }
    setState(390);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

BismuthParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::BlockContext::LSQB() {
  return getToken(BismuthParser::LSQB, 0);
}

tree::TerminalNode* BismuthParser::BlockContext::RSQB() {
  return getToken(BismuthParser::RSQB, 0);
}

std::vector<BismuthParser::StatementContext *> BismuthParser::BlockContext::statement() {
  return getRuleContexts<BismuthParser::StatementContext>();
}

BismuthParser::StatementContext* BismuthParser::BlockContext::statement(size_t i) {
  return getRuleContext<BismuthParser::StatementContext>(i);
}


size_t BismuthParser::BlockContext::getRuleIndex() const {
  return BismuthParser::RuleBlock;
}

void BismuthParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void BismuthParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


std::any BismuthParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::BlockContext* BismuthParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 30, BismuthParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(392);
    match(BismuthParser::LSQB);
    setState(396);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << BismuthParser::T__8)
      | (1ULL << BismuthParser::T__10)
      | (1ULL << BismuthParser::T__12)
      | (1ULL << BismuthParser::T__14)
      | (1ULL << BismuthParser::T__15)
      | (1ULL << BismuthParser::T__16)
      | (1ULL << BismuthParser::T__17)
      | (1ULL << BismuthParser::T__18)
      | (1ULL << BismuthParser::T__19)
      | (1ULL << BismuthParser::T__20)
      | (1ULL << BismuthParser::T__21)
      | (1ULL << BismuthParser::T__22)
      | (1ULL << BismuthParser::MINUS)
      | (1ULL << BismuthParser::NOT)
      | (1ULL << BismuthParser::MULTIPLY)
      | (1ULL << BismuthParser::BIT_NOT)
      | (1ULL << BismuthParser::LPAR)
      | (1ULL << BismuthParser::LBRC)
      | (1ULL << BismuthParser::LSQB)
      | (1ULL << BismuthParser::DEC_LITERAL)
      | (1ULL << BismuthParser::HEX_LITERAL)
      | (1ULL << BismuthParser::BIN_LITERAL)
      | (1ULL << BismuthParser::TYPE_INT)
      | (1ULL << BismuthParser::TYPE_I32)
      | (1ULL << BismuthParser::TYPE_U32)
      | (1ULL << BismuthParser::TYPE_I64))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (BismuthParser::TYPE_U64 - 64))
      | (1ULL << (BismuthParser::TYPE_BOOL - 64))
      | (1ULL << (BismuthParser::TYPE_STR - 64))
      | (1ULL << (BismuthParser::TYPE_UNIT - 64))
      | (1ULL << (BismuthParser::TYPE_VAR - 64))
      | (1ULL << (BismuthParser::TYPE_BOX - 64))
      | (1ULL << (BismuthParser::TYPE_PROGRAM - 64))
      | (1ULL << (BismuthParser::TYPE_CHANNEL - 64))
      | (1ULL << (BismuthParser::PROG - 64))
      | (1ULL << (BismuthParser::FUNC - 64))
      | (1ULL << (BismuthParser::ENUM - 64))
      | (1ULL << (BismuthParser::STRUCT - 64))
      | (1ULL << (BismuthParser::IF - 64))
      | (1ULL << (BismuthParser::WHILE - 64))
      | (1ULL << (BismuthParser::RETURN - 64))
      | (1ULL << (BismuthParser::SELECT - 64))
      | (1ULL << (BismuthParser::MATCH - 64))
      | (1ULL << (BismuthParser::EXIT - 64))
      | (1ULL << (BismuthParser::EXEC - 64))
      | (1ULL << (BismuthParser::COPY - 64))
      | (1ULL << (BismuthParser::TRAIT - 64))
      | (1ULL << (BismuthParser::FALSE - 64))
      | (1ULL << (BismuthParser::TRUE - 64))
      | (1ULL << (BismuthParser::STRING - 64))
      | (1ULL << (BismuthParser::VARIABLE - 64)))) != 0)) {
      setState(393);
      antlrcpp::downCast<BlockContext *>(_localctx)->statementContext = statement();
      antlrcpp::downCast<BlockContext *>(_localctx)->stmts.push_back(antlrcpp::downCast<BlockContext *>(_localctx)->statementContext);
      setState(398);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(399);
    match(BismuthParser::RSQB);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionContext ------------------------------------------------------------------

BismuthParser::ConditionContext::ConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::ConditionContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::ConditionContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

BismuthParser::ExpressionContext* BismuthParser::ConditionContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}


size_t BismuthParser::ConditionContext::getRuleIndex() const {
  return BismuthParser::RuleCondition;
}

void BismuthParser::ConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCondition(this);
}

void BismuthParser::ConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCondition(this);
}


std::any BismuthParser::ConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitCondition(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::ConditionContext* BismuthParser::condition() {
  ConditionContext *_localctx = _tracker.createInstance<ConditionContext>(_ctx, getState());
  enterRule(_localctx, 32, BismuthParser::RuleCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(406);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(401);
      match(BismuthParser::LPAR);
      setState(402);
      antlrcpp::downCast<ConditionContext *>(_localctx)->ex = expression(0);
      setState(403);
      match(BismuthParser::RPAR);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(405);
      antlrcpp::downCast<ConditionContext *>(_localctx)->ex = expression(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectAlternativeContext ------------------------------------------------------------------

BismuthParser::SelectAlternativeContext::SelectAlternativeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::SelectAlternativeContext::COLON() {
  return getToken(BismuthParser::COLON, 0);
}

BismuthParser::ExpressionContext* BismuthParser::SelectAlternativeContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}

BismuthParser::StatementContext* BismuthParser::SelectAlternativeContext::statement() {
  return getRuleContext<BismuthParser::StatementContext>(0);
}


size_t BismuthParser::SelectAlternativeContext::getRuleIndex() const {
  return BismuthParser::RuleSelectAlternative;
}

void BismuthParser::SelectAlternativeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectAlternative(this);
}

void BismuthParser::SelectAlternativeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectAlternative(this);
}


std::any BismuthParser::SelectAlternativeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitSelectAlternative(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::SelectAlternativeContext* BismuthParser::selectAlternative() {
  SelectAlternativeContext *_localctx = _tracker.createInstance<SelectAlternativeContext>(_ctx, getState());
  enterRule(_localctx, 34, BismuthParser::RuleSelectAlternative);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(408);
    antlrcpp::downCast<SelectAlternativeContext *>(_localctx)->check = expression(0);
    setState(409);
    match(BismuthParser::COLON);
    setState(410);
    antlrcpp::downCast<SelectAlternativeContext *>(_localctx)->eval = statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MatchAlternativeContext ------------------------------------------------------------------

BismuthParser::MatchAlternativeContext::MatchAlternativeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BismuthParser::TypeContext* BismuthParser::MatchAlternativeContext::type() {
  return getRuleContext<BismuthParser::TypeContext>(0);
}

tree::TerminalNode* BismuthParser::MatchAlternativeContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

BismuthParser::StatementContext* BismuthParser::MatchAlternativeContext::statement() {
  return getRuleContext<BismuthParser::StatementContext>(0);
}


size_t BismuthParser::MatchAlternativeContext::getRuleIndex() const {
  return BismuthParser::RuleMatchAlternative;
}

void BismuthParser::MatchAlternativeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMatchAlternative(this);
}

void BismuthParser::MatchAlternativeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMatchAlternative(this);
}


std::any BismuthParser::MatchAlternativeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitMatchAlternative(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::MatchAlternativeContext* BismuthParser::matchAlternative() {
  MatchAlternativeContext *_localctx = _tracker.createInstance<MatchAlternativeContext>(_ctx, getState());
  enterRule(_localctx, 36, BismuthParser::RuleMatchAlternative);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(412);
    antlrcpp::downCast<MatchAlternativeContext *>(_localctx)->check = type(0);
    setState(413);
    antlrcpp::downCast<MatchAlternativeContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
    setState(414);
    match(BismuthParser::T__9);
    setState(415);
    antlrcpp::downCast<MatchAlternativeContext *>(_localctx)->eval = statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProtoAlternativeContext ------------------------------------------------------------------

BismuthParser::ProtoAlternativeContext::ProtoAlternativeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BismuthParser::StatementContext* BismuthParser::ProtoAlternativeContext::statement() {
  return getRuleContext<BismuthParser::StatementContext>(0);
}

tree::TerminalNode* BismuthParser::ProtoAlternativeContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

BismuthParser::ProtocolContext* BismuthParser::ProtoAlternativeContext::protocol() {
  return getRuleContext<BismuthParser::ProtocolContext>(0);
}


size_t BismuthParser::ProtoAlternativeContext::getRuleIndex() const {
  return BismuthParser::RuleProtoAlternative;
}

void BismuthParser::ProtoAlternativeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProtoAlternative(this);
}

void BismuthParser::ProtoAlternativeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProtoAlternative(this);
}


std::any BismuthParser::ProtoAlternativeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitProtoAlternative(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::ProtoAlternativeContext* BismuthParser::protoAlternative() {
  ProtoAlternativeContext *_localctx = _tracker.createInstance<ProtoAlternativeContext>(_ctx, getState());
  enterRule(_localctx, 38, BismuthParser::RuleProtoAlternative);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(419);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BismuthParser::VARIABLE: {
        setState(417);
        antlrcpp::downCast<ProtoAlternativeContext *>(_localctx)->lbl = match(BismuthParser::VARIABLE);
        break;
      }

      case BismuthParser::T__23:
      case BismuthParser::MINUS:
      case BismuthParser::NOT:
      case BismuthParser::PLUS:
      case BismuthParser::LPAR:
      case BismuthParser::EXTERNAL_CHOICE:
      case BismuthParser::INTERNAL_CHOICE:
      case BismuthParser::CLOSEABLE: {
        setState(418);
        antlrcpp::downCast<ProtoAlternativeContext *>(_localctx)->check = protocol();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(421);
    match(BismuthParser::T__9);
    setState(422);
    antlrcpp::downCast<ProtoAlternativeContext *>(_localctx)->eval = statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProtoElseContext ------------------------------------------------------------------

BismuthParser::ProtoElseContext::ProtoElseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::ProtoElseContext::ELSE() {
  return getToken(BismuthParser::ELSE, 0);
}

BismuthParser::StatementContext* BismuthParser::ProtoElseContext::statement() {
  return getRuleContext<BismuthParser::StatementContext>(0);
}


size_t BismuthParser::ProtoElseContext::getRuleIndex() const {
  return BismuthParser::RuleProtoElse;
}

void BismuthParser::ProtoElseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProtoElse(this);
}

void BismuthParser::ProtoElseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProtoElse(this);
}


std::any BismuthParser::ProtoElseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitProtoElse(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::ProtoElseContext* BismuthParser::protoElse() {
  ProtoElseContext *_localctx = _tracker.createInstance<ProtoElseContext>(_ctx, getState());
  enterRule(_localctx, 40, BismuthParser::RuleProtoElse);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(424);
    match(BismuthParser::ELSE);
    setState(425);
    match(BismuthParser::T__9);
    setState(426);
    antlrcpp::downCast<ProtoElseContext *>(_localctx)->eval = statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterListContext ------------------------------------------------------------------

BismuthParser::ParameterListContext::ParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BismuthParser::ParameterContext *> BismuthParser::ParameterListContext::parameter() {
  return getRuleContexts<BismuthParser::ParameterContext>();
}

BismuthParser::ParameterContext* BismuthParser::ParameterListContext::parameter(size_t i) {
  return getRuleContext<BismuthParser::ParameterContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::ParameterListContext::COMMA() {
  return getTokens(BismuthParser::COMMA);
}

tree::TerminalNode* BismuthParser::ParameterListContext::COMMA(size_t i) {
  return getToken(BismuthParser::COMMA, i);
}


size_t BismuthParser::ParameterListContext::getRuleIndex() const {
  return BismuthParser::RuleParameterList;
}

void BismuthParser::ParameterListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameterList(this);
}

void BismuthParser::ParameterListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameterList(this);
}


std::any BismuthParser::ParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitParameterList(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::ParameterListContext* BismuthParser::parameterList() {
  ParameterListContext *_localctx = _tracker.createInstance<ParameterListContext>(_ctx, getState());
  enterRule(_localctx, 42, BismuthParser::RuleParameterList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(436);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 46) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 46)) & ((1ULL << (BismuthParser::LPAR - 46))
      | (1ULL << (BismuthParser::TYPE_INT - 46))
      | (1ULL << (BismuthParser::TYPE_I32 - 46))
      | (1ULL << (BismuthParser::TYPE_U32 - 46))
      | (1ULL << (BismuthParser::TYPE_I64 - 46))
      | (1ULL << (BismuthParser::TYPE_U64 - 46))
      | (1ULL << (BismuthParser::TYPE_BOOL - 46))
      | (1ULL << (BismuthParser::TYPE_STR - 46))
      | (1ULL << (BismuthParser::TYPE_UNIT - 46))
      | (1ULL << (BismuthParser::TYPE_BOX - 46))
      | (1ULL << (BismuthParser::TYPE_PROGRAM - 46))
      | (1ULL << (BismuthParser::TYPE_CHANNEL - 46))
      | (1ULL << (BismuthParser::VARIABLE - 46)))) != 0)) {
      setState(428);
      antlrcpp::downCast<ParameterListContext *>(_localctx)->parameterContext = parameter();
      antlrcpp::downCast<ParameterListContext *>(_localctx)->params.push_back(antlrcpp::downCast<ParameterListContext *>(_localctx)->parameterContext);
      setState(433);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == BismuthParser::COMMA) {
        setState(429);
        match(BismuthParser::COMMA);
        setState(430);
        antlrcpp::downCast<ParameterListContext *>(_localctx)->parameterContext = parameter();
        antlrcpp::downCast<ParameterListContext *>(_localctx)->params.push_back(antlrcpp::downCast<ParameterListContext *>(_localctx)->parameterContext);
        setState(435);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterContext ------------------------------------------------------------------

BismuthParser::ParameterContext::ParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BismuthParser::TypeContext* BismuthParser::ParameterContext::type() {
  return getRuleContext<BismuthParser::TypeContext>(0);
}

tree::TerminalNode* BismuthParser::ParameterContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}


size_t BismuthParser::ParameterContext::getRuleIndex() const {
  return BismuthParser::RuleParameter;
}

void BismuthParser::ParameterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameter(this);
}

void BismuthParser::ParameterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameter(this);
}


std::any BismuthParser::ParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitParameter(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::ParameterContext* BismuthParser::parameter() {
  ParameterContext *_localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
  enterRule(_localctx, 44, BismuthParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(438);
    antlrcpp::downCast<ParameterContext *>(_localctx)->ty = type(0);
    setState(439);
    antlrcpp::downCast<ParameterContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

BismuthParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> BismuthParser::AssignmentContext::VARIABLE() {
  return getTokens(BismuthParser::VARIABLE);
}

tree::TerminalNode* BismuthParser::AssignmentContext::VARIABLE(size_t i) {
  return getToken(BismuthParser::VARIABLE, i);
}

std::vector<tree::TerminalNode *> BismuthParser::AssignmentContext::COMMA() {
  return getTokens(BismuthParser::COMMA);
}

tree::TerminalNode* BismuthParser::AssignmentContext::COMMA(size_t i) {
  return getToken(BismuthParser::COMMA, i);
}

tree::TerminalNode* BismuthParser::AssignmentContext::ASSIGN() {
  return getToken(BismuthParser::ASSIGN, 0);
}

BismuthParser::ExpressionContext* BismuthParser::AssignmentContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}


size_t BismuthParser::AssignmentContext::getRuleIndex() const {
  return BismuthParser::RuleAssignment;
}

void BismuthParser::AssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignment(this);
}

void BismuthParser::AssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignment(this);
}


std::any BismuthParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::AssignmentContext* BismuthParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 46, BismuthParser::RuleAssignment);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(441);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->variableToken = match(BismuthParser::VARIABLE);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->v.push_back(antlrcpp::downCast<AssignmentContext *>(_localctx)->variableToken);
    setState(446);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(442);
        match(BismuthParser::COMMA);
        setState(443);
        antlrcpp::downCast<AssignmentContext *>(_localctx)->variableToken = match(BismuthParser::VARIABLE);
        antlrcpp::downCast<AssignmentContext *>(_localctx)->v.push_back(antlrcpp::downCast<AssignmentContext *>(_localctx)->variableToken); 
      }
      setState(448);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    }
    setState(451);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BismuthParser::ASSIGN) {
      setState(449);
      match(BismuthParser::ASSIGN);
      setState(450);
      antlrcpp::downCast<AssignmentContext *>(_localctx)->a = expression(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

BismuthParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t BismuthParser::StatementContext::getRuleIndex() const {
  return BismuthParser::RuleStatement;
}

void BismuthParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MatchStatementContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::MatchStatementContext::MATCH() {
  return getToken(BismuthParser::MATCH, 0);
}

tree::TerminalNode* BismuthParser::MatchStatementContext::LSQB() {
  return getToken(BismuthParser::LSQB, 0);
}

tree::TerminalNode* BismuthParser::MatchStatementContext::RSQB() {
  return getToken(BismuthParser::RSQB, 0);
}

BismuthParser::ConditionContext* BismuthParser::MatchStatementContext::condition() {
  return getRuleContext<BismuthParser::ConditionContext>(0);
}

std::vector<BismuthParser::MatchAlternativeContext *> BismuthParser::MatchStatementContext::matchAlternative() {
  return getRuleContexts<BismuthParser::MatchAlternativeContext>();
}

BismuthParser::MatchAlternativeContext* BismuthParser::MatchStatementContext::matchAlternative(size_t i) {
  return getRuleContext<BismuthParser::MatchAlternativeContext>(i);
}

std::vector<BismuthParser::StatementContext *> BismuthParser::MatchStatementContext::statement() {
  return getRuleContexts<BismuthParser::StatementContext>();
}

BismuthParser::StatementContext* BismuthParser::MatchStatementContext::statement(size_t i) {
  return getRuleContext<BismuthParser::StatementContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::MatchStatementContext::BIT_OR() {
  return getTokens(BismuthParser::BIT_OR);
}

tree::TerminalNode* BismuthParser::MatchStatementContext::BIT_OR(size_t i) {
  return getToken(BismuthParser::BIT_OR, i);
}

BismuthParser::MatchStatementContext::MatchStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::MatchStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMatchStatement(this);
}
void BismuthParser::MatchStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMatchStatement(this);
}

std::any BismuthParser::MatchStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitMatchStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SkipStatementContext ------------------------------------------------------------------

BismuthParser::SkipStatementContext::SkipStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::SkipStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSkipStatement(this);
}
void BismuthParser::SkipStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSkipStatement(this);
}

std::any BismuthParser::SkipStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitSkipStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExitStatementContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ExitStatementContext::EXIT() {
  return getToken(BismuthParser::EXIT, 0);
}

BismuthParser::ExitStatementContext::ExitStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::ExitStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExitStatement(this);
}
void BismuthParser::ExitStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExitStatement(this);
}

std::any BismuthParser::ExitStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitExitStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConditionalStatementContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ConditionalStatementContext::IF() {
  return getToken(BismuthParser::IF, 0);
}

BismuthParser::ConditionContext* BismuthParser::ConditionalStatementContext::condition() {
  return getRuleContext<BismuthParser::ConditionContext>(0);
}

std::vector<BismuthParser::BlockContext *> BismuthParser::ConditionalStatementContext::block() {
  return getRuleContexts<BismuthParser::BlockContext>();
}

BismuthParser::BlockContext* BismuthParser::ConditionalStatementContext::block(size_t i) {
  return getRuleContext<BismuthParser::BlockContext>(i);
}

tree::TerminalNode* BismuthParser::ConditionalStatementContext::ELSE() {
  return getToken(BismuthParser::ELSE, 0);
}

std::vector<BismuthParser::StatementContext *> BismuthParser::ConditionalStatementContext::statement() {
  return getRuleContexts<BismuthParser::StatementContext>();
}

BismuthParser::StatementContext* BismuthParser::ConditionalStatementContext::statement(size_t i) {
  return getRuleContext<BismuthParser::StatementContext>(i);
}

BismuthParser::ConditionalStatementContext::ConditionalStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::ConditionalStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionalStatement(this);
}
void BismuthParser::ConditionalStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionalStatement(this);
}

std::any BismuthParser::ConditionalStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitConditionalStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ProgramProjectContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ProgramProjectContext::LBRC() {
  return getToken(BismuthParser::LBRC, 0);
}

tree::TerminalNode* BismuthParser::ProgramProjectContext::RBRC() {
  return getToken(BismuthParser::RBRC, 0);
}

std::vector<tree::TerminalNode *> BismuthParser::ProgramProjectContext::VARIABLE() {
  return getTokens(BismuthParser::VARIABLE);
}

tree::TerminalNode* BismuthParser::ProgramProjectContext::VARIABLE(size_t i) {
  return getToken(BismuthParser::VARIABLE, i);
}

BismuthParser::ProtocolContext* BismuthParser::ProgramProjectContext::protocol() {
  return getRuleContext<BismuthParser::ProtocolContext>(0);
}

tree::TerminalNode* BismuthParser::ProgramProjectContext::SEMICOLON() {
  return getToken(BismuthParser::SEMICOLON, 0);
}

BismuthParser::ProgramProjectContext::ProgramProjectContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::ProgramProjectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgramProject(this);
}
void BismuthParser::ProgramProjectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgramProject(this);
}

std::any BismuthParser::ProgramProjectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitProgramProject(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ProgramSendContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ProgramSendContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::ProgramSendContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

tree::TerminalNode* BismuthParser::ProgramSendContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

BismuthParser::ExpressionContext* BismuthParser::ProgramSendContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}

tree::TerminalNode* BismuthParser::ProgramSendContext::SEMICOLON() {
  return getToken(BismuthParser::SEMICOLON, 0);
}

BismuthParser::ProgramSendContext::ProgramSendContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::ProgramSendContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgramSend(this);
}
void BismuthParser::ProgramSendContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgramSend(this);
}

std::any BismuthParser::ProgramSendContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitProgramSend(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ProgramCaseContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ProgramCaseContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::ProgramCaseContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

tree::TerminalNode* BismuthParser::ProgramCaseContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

std::vector<BismuthParser::ProtoAlternativeContext *> BismuthParser::ProgramCaseContext::protoAlternative() {
  return getRuleContexts<BismuthParser::ProtoAlternativeContext>();
}

BismuthParser::ProtoAlternativeContext* BismuthParser::ProgramCaseContext::protoAlternative(size_t i) {
  return getRuleContext<BismuthParser::ProtoAlternativeContext>(i);
}

BismuthParser::ProtoElseContext* BismuthParser::ProgramCaseContext::protoElse() {
  return getRuleContext<BismuthParser::ProtoElseContext>(0);
}

std::vector<BismuthParser::StatementContext *> BismuthParser::ProgramCaseContext::statement() {
  return getRuleContexts<BismuthParser::StatementContext>();
}

BismuthParser::StatementContext* BismuthParser::ProgramCaseContext::statement(size_t i) {
  return getRuleContext<BismuthParser::StatementContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::ProgramCaseContext::BIT_OR() {
  return getTokens(BismuthParser::BIT_OR);
}

tree::TerminalNode* BismuthParser::ProgramCaseContext::BIT_OR(size_t i) {
  return getToken(BismuthParser::BIT_OR, i);
}

BismuthParser::ProgramCaseContext::ProgramCaseContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::ProgramCaseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgramCase(this);
}
void BismuthParser::ProgramCaseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgramCase(this);
}

std::any BismuthParser::ProgramCaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitProgramCase(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockStatementContext ------------------------------------------------------------------

BismuthParser::BlockContext* BismuthParser::BlockStatementContext::block() {
  return getRuleContext<BismuthParser::BlockContext>(0);
}

BismuthParser::BlockStatementContext::BlockStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::BlockStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockStatement(this);
}
void BismuthParser::BlockStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockStatement(this);
}

std::any BismuthParser::BlockStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitBlockStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ProgramLoopContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ProgramLoopContext::WHILE() {
  return getToken(BismuthParser::WHILE, 0);
}

BismuthParser::BlockContext* BismuthParser::ProgramLoopContext::block() {
  return getRuleContext<BismuthParser::BlockContext>(0);
}

BismuthParser::ConditionContext* BismuthParser::ProgramLoopContext::condition() {
  return getRuleContext<BismuthParser::ConditionContext>(0);
}

BismuthParser::ProgramLoopContext::ProgramLoopContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::ProgramLoopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgramLoop(this);
}
void BismuthParser::ProgramLoopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgramLoop(this);
}

std::any BismuthParser::ProgramLoopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitProgramLoop(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ProgramContractContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ProgramContractContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::ProgramContractContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

tree::TerminalNode* BismuthParser::ProgramContractContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

tree::TerminalNode* BismuthParser::ProgramContractContext::SEMICOLON() {
  return getToken(BismuthParser::SEMICOLON, 0);
}

BismuthParser::ProgramContractContext::ProgramContractContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::ProgramContractContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgramContract(this);
}
void BismuthParser::ProgramContractContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgramContract(this);
}

std::any BismuthParser::ProgramContractContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitProgramContract(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ProgramCancelContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ProgramCancelContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::ProgramCancelContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

tree::TerminalNode* BismuthParser::ProgramCancelContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

tree::TerminalNode* BismuthParser::ProgramCancelContext::SEMICOLON() {
  return getToken(BismuthParser::SEMICOLON, 0);
}

BismuthParser::ProgramCancelContext::ProgramCancelContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::ProgramCancelContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgramCancel(this);
}
void BismuthParser::ProgramCancelContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgramCancel(this);
}

std::any BismuthParser::ProgramCancelContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitProgramCancel(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignStatementContext ------------------------------------------------------------------

BismuthParser::AssignmentStatementContext* BismuthParser::AssignStatementContext::assignmentStatement() {
  return getRuleContext<BismuthParser::AssignmentStatementContext>(0);
}

tree::TerminalNode* BismuthParser::AssignStatementContext::SEMICOLON() {
  return getToken(BismuthParser::SEMICOLON, 0);
}

BismuthParser::AssignStatementContext::AssignStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::AssignStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignStatement(this);
}
void BismuthParser::AssignStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignStatement(this);
}

std::any BismuthParser::AssignStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitAssignStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ProgramWeakenContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ProgramWeakenContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::ProgramWeakenContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

tree::TerminalNode* BismuthParser::ProgramWeakenContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

tree::TerminalNode* BismuthParser::ProgramWeakenContext::SEMICOLON() {
  return getToken(BismuthParser::SEMICOLON, 0);
}

BismuthParser::ProgramWeakenContext::ProgramWeakenContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::ProgramWeakenContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgramWeaken(this);
}
void BismuthParser::ProgramWeakenContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgramWeaken(this);
}

std::any BismuthParser::ProgramWeakenContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitProgramWeaken(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ProgramAcceptContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ProgramAcceptContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::ProgramAcceptContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

BismuthParser::BlockContext* BismuthParser::ProgramAcceptContext::block() {
  return getRuleContext<BismuthParser::BlockContext>(0);
}

tree::TerminalNode* BismuthParser::ProgramAcceptContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

BismuthParser::ProgramAcceptContext::ProgramAcceptContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::ProgramAcceptContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgramAccept(this);
}
void BismuthParser::ProgramAcceptContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgramAccept(this);
}

std::any BismuthParser::ProgramAcceptContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitProgramAccept(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SelectStatementContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::SelectStatementContext::SELECT() {
  return getToken(BismuthParser::SELECT, 0);
}

tree::TerminalNode* BismuthParser::SelectStatementContext::LSQB() {
  return getToken(BismuthParser::LSQB, 0);
}

tree::TerminalNode* BismuthParser::SelectStatementContext::RSQB() {
  return getToken(BismuthParser::RSQB, 0);
}

std::vector<BismuthParser::SelectAlternativeContext *> BismuthParser::SelectStatementContext::selectAlternative() {
  return getRuleContexts<BismuthParser::SelectAlternativeContext>();
}

BismuthParser::SelectAlternativeContext* BismuthParser::SelectStatementContext::selectAlternative(size_t i) {
  return getRuleContext<BismuthParser::SelectAlternativeContext>(i);
}

std::vector<BismuthParser::StatementContext *> BismuthParser::SelectStatementContext::statement() {
  return getRuleContexts<BismuthParser::StatementContext>();
}

BismuthParser::StatementContext* BismuthParser::SelectStatementContext::statement(size_t i) {
  return getRuleContext<BismuthParser::StatementContext>(i);
}

BismuthParser::SelectStatementContext::SelectStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::SelectStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectStatement(this);
}
void BismuthParser::SelectStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectStatement(this);
}

std::any BismuthParser::SelectStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitSelectStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TypeDefContext ------------------------------------------------------------------

BismuthParser::DefineTypeContext* BismuthParser::TypeDefContext::defineType() {
  return getRuleContext<BismuthParser::DefineTypeContext>(0);
}

BismuthParser::TypeDefContext::TypeDefContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::TypeDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeDef(this);
}
void BismuthParser::TypeDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeDef(this);
}

std::any BismuthParser::TypeDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitTypeDef(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ProgramCloseContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ProgramCloseContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::ProgramCloseContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

tree::TerminalNode* BismuthParser::ProgramCloseContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

tree::TerminalNode* BismuthParser::ProgramCloseContext::SEMICOLON() {
  return getToken(BismuthParser::SEMICOLON, 0);
}

BismuthParser::ProgramCloseContext::ProgramCloseContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::ProgramCloseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgramClose(this);
}
void BismuthParser::ProgramCloseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgramClose(this);
}

std::any BismuthParser::ProgramCloseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitProgramClose(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExpressionStatementContext ------------------------------------------------------------------

BismuthParser::ExpressionContext* BismuthParser::ExpressionStatementContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}

tree::TerminalNode* BismuthParser::ExpressionStatementContext::SEMICOLON() {
  return getToken(BismuthParser::SEMICOLON, 0);
}

BismuthParser::ExpressionStatementContext::ExpressionStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::ExpressionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionStatement(this);
}
void BismuthParser::ExpressionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionStatement(this);
}

std::any BismuthParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnStatementContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ReturnStatementContext::RETURN() {
  return getToken(BismuthParser::RETURN, 0);
}

tree::TerminalNode* BismuthParser::ReturnStatementContext::SEMICOLON() {
  return getToken(BismuthParser::SEMICOLON, 0);
}

BismuthParser::ExpressionContext* BismuthParser::ReturnStatementContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}

BismuthParser::ReturnStatementContext::ReturnStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::ReturnStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatement(this);
}
void BismuthParser::ReturnStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatement(this);
}

std::any BismuthParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ForStatementContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ForStatementContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

std::vector<tree::TerminalNode *> BismuthParser::ForStatementContext::SEMICOLON() {
  return getTokens(BismuthParser::SEMICOLON);
}

tree::TerminalNode* BismuthParser::ForStatementContext::SEMICOLON(size_t i) {
  return getToken(BismuthParser::SEMICOLON, i);
}

tree::TerminalNode* BismuthParser::ForStatementContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

BismuthParser::ConditionContext* BismuthParser::ForStatementContext::condition() {
  return getRuleContext<BismuthParser::ConditionContext>(0);
}

BismuthParser::StatementContext* BismuthParser::ForStatementContext::statement() {
  return getRuleContext<BismuthParser::StatementContext>(0);
}

BismuthParser::BlockContext* BismuthParser::ForStatementContext::block() {
  return getRuleContext<BismuthParser::BlockContext>(0);
}

BismuthParser::VariableDeclarationContext* BismuthParser::ForStatementContext::variableDeclaration() {
  return getRuleContext<BismuthParser::VariableDeclarationContext>(0);
}

BismuthParser::AssignmentStatementContext* BismuthParser::ForStatementContext::assignmentStatement() {
  return getRuleContext<BismuthParser::AssignmentStatementContext>(0);
}

BismuthParser::ForStatementContext::ForStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::ForStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForStatement(this);
}
void BismuthParser::ForStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForStatement(this);
}

std::any BismuthParser::ForStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitForStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ProgramAcceptWhileContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ProgramAcceptWhileContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::ProgramAcceptWhileContext::COMMA() {
  return getToken(BismuthParser::COMMA, 0);
}

tree::TerminalNode* BismuthParser::ProgramAcceptWhileContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

BismuthParser::BlockContext* BismuthParser::ProgramAcceptWhileContext::block() {
  return getRuleContext<BismuthParser::BlockContext>(0);
}

tree::TerminalNode* BismuthParser::ProgramAcceptWhileContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

BismuthParser::ExpressionContext* BismuthParser::ProgramAcceptWhileContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}

BismuthParser::ProgramAcceptWhileContext::ProgramAcceptWhileContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::ProgramAcceptWhileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgramAcceptWhile(this);
}
void BismuthParser::ProgramAcceptWhileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgramAcceptWhile(this);
}

std::any BismuthParser::ProgramAcceptWhileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitProgramAcceptWhile(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarDeclStatementContext ------------------------------------------------------------------

BismuthParser::VariableDeclarationContext* BismuthParser::VarDeclStatementContext::variableDeclaration() {
  return getRuleContext<BismuthParser::VariableDeclarationContext>(0);
}

tree::TerminalNode* BismuthParser::VarDeclStatementContext::SEMICOLON() {
  return getToken(BismuthParser::SEMICOLON, 0);
}

BismuthParser::VarDeclStatementContext::VarDeclStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::VarDeclStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDeclStatement(this);
}
void BismuthParser::VarDeclStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDeclStatement(this);
}

std::any BismuthParser::VarDeclStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitVarDeclStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ProgramAcceptIfContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ProgramAcceptIfContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::ProgramAcceptIfContext::COMMA() {
  return getToken(BismuthParser::COMMA, 0);
}

tree::TerminalNode* BismuthParser::ProgramAcceptIfContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

tree::TerminalNode* BismuthParser::ProgramAcceptIfContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}

BismuthParser::ExpressionContext* BismuthParser::ProgramAcceptIfContext::expression() {
  return getRuleContext<BismuthParser::ExpressionContext>(0);
}

std::vector<BismuthParser::BlockContext *> BismuthParser::ProgramAcceptIfContext::block() {
  return getRuleContexts<BismuthParser::BlockContext>();
}

BismuthParser::BlockContext* BismuthParser::ProgramAcceptIfContext::block(size_t i) {
  return getRuleContext<BismuthParser::BlockContext>(i);
}

tree::TerminalNode* BismuthParser::ProgramAcceptIfContext::ELSE() {
  return getToken(BismuthParser::ELSE, 0);
}

std::vector<BismuthParser::StatementContext *> BismuthParser::ProgramAcceptIfContext::statement() {
  return getRuleContexts<BismuthParser::StatementContext>();
}

BismuthParser::StatementContext* BismuthParser::ProgramAcceptIfContext::statement(size_t i) {
  return getRuleContext<BismuthParser::StatementContext>(i);
}

BismuthParser::ProgramAcceptIfContext::ProgramAcceptIfContext(StatementContext *ctx) { copyFrom(ctx); }

void BismuthParser::ProgramAcceptIfContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgramAcceptIf(this);
}
void BismuthParser::ProgramAcceptIfContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgramAcceptIf(this);
}

std::any BismuthParser::ProgramAcceptIfContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitProgramAcceptIf(this);
  else
    return visitor->visitChildren(this);
}
BismuthParser::StatementContext* BismuthParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 48, BismuthParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(672);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<BismuthParser::TypeDefContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(453);
      defineType();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<BismuthParser::VarDeclStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(454);
      variableDeclaration();
      setState(456);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(455);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<BismuthParser::AssignStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(458);
      assignmentStatement();
      setState(460);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(459);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<BismuthParser::ConditionalStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(462);
      match(BismuthParser::IF);
      setState(463);
      antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->check = condition();
      setState(464);
      antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->trueBlk = block();
      setState(467);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
      case 1: {
        setState(465);
        match(BismuthParser::ELSE);
        setState(466);
        antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->falseBlk = block();
        break;
      }

      default:
        break;
      }
      setState(472);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(469);
          antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->rest.push_back(antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->statementContext); 
        }
        setState(474);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
      }
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<BismuthParser::SelectStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(475);
      match(BismuthParser::SELECT);
      setState(476);
      match(BismuthParser::LSQB);
      setState(480);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << BismuthParser::T__8)
        | (1ULL << BismuthParser::MINUS)
        | (1ULL << BismuthParser::NOT)
        | (1ULL << BismuthParser::MULTIPLY)
        | (1ULL << BismuthParser::BIT_NOT)
        | (1ULL << BismuthParser::LPAR)
        | (1ULL << BismuthParser::LBRC)
        | (1ULL << BismuthParser::DEC_LITERAL)
        | (1ULL << BismuthParser::HEX_LITERAL)
        | (1ULL << BismuthParser::BIN_LITERAL))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 69)) & ((1ULL << (BismuthParser::TYPE_BOX - 69))
        | (1ULL << (BismuthParser::EXEC - 69))
        | (1ULL << (BismuthParser::COPY - 69))
        | (1ULL << (BismuthParser::FALSE - 69))
        | (1ULL << (BismuthParser::TRUE - 69))
        | (1ULL << (BismuthParser::STRING - 69))
        | (1ULL << (BismuthParser::VARIABLE - 69)))) != 0)) {
        setState(477);
        antlrcpp::downCast<SelectStatementContext *>(_localctx)->selectAlternativeContext = selectAlternative();
        antlrcpp::downCast<SelectStatementContext *>(_localctx)->cases.push_back(antlrcpp::downCast<SelectStatementContext *>(_localctx)->selectAlternativeContext);
        setState(482);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(483);
      match(BismuthParser::RSQB);
      setState(487);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(484);
          antlrcpp::downCast<SelectStatementContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<SelectStatementContext *>(_localctx)->rest.push_back(antlrcpp::downCast<SelectStatementContext *>(_localctx)->statementContext); 
        }
        setState(489);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx);
      }
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<BismuthParser::MatchStatementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(490);
      match(BismuthParser::MATCH);
      setState(491);
      antlrcpp::downCast<MatchStatementContext *>(_localctx)->check = condition();
      setState(492);
      match(BismuthParser::LSQB);
      setState(496);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (((((_la - 46) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 46)) & ((1ULL << (BismuthParser::LPAR - 46))
        | (1ULL << (BismuthParser::TYPE_INT - 46))
        | (1ULL << (BismuthParser::TYPE_I32 - 46))
        | (1ULL << (BismuthParser::TYPE_U32 - 46))
        | (1ULL << (BismuthParser::TYPE_I64 - 46))
        | (1ULL << (BismuthParser::TYPE_U64 - 46))
        | (1ULL << (BismuthParser::TYPE_BOOL - 46))
        | (1ULL << (BismuthParser::TYPE_STR - 46))
        | (1ULL << (BismuthParser::TYPE_UNIT - 46))
        | (1ULL << (BismuthParser::TYPE_BOX - 46))
        | (1ULL << (BismuthParser::TYPE_PROGRAM - 46))
        | (1ULL << (BismuthParser::TYPE_CHANNEL - 46))
        | (1ULL << (BismuthParser::VARIABLE - 46)))) != 0)) {
        setState(493);
        matchAlternative();
        setState(498);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(499);
      match(BismuthParser::RSQB);
      setState(503);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(500);
          antlrcpp::downCast<MatchStatementContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<MatchStatementContext *>(_localctx)->rest.push_back(antlrcpp::downCast<MatchStatementContext *>(_localctx)->statementContext); 
        }
        setState(505);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx);
      }
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<BismuthParser::MatchStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(506);
      match(BismuthParser::MATCH);
      setState(507);
      antlrcpp::downCast<MatchStatementContext *>(_localctx)->check = condition();
      setState(512);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(508);
          match(BismuthParser::BIT_OR);
          setState(509);
          matchAlternative(); 
        }
        setState(514);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx);
      }
      setState(518);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(515);
          antlrcpp::downCast<MatchStatementContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<MatchStatementContext *>(_localctx)->rest.push_back(antlrcpp::downCast<MatchStatementContext *>(_localctx)->statementContext); 
        }
        setState(520);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
      }
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<BismuthParser::ReturnStatementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(521);
      match(BismuthParser::RETURN);
      setState(523);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << BismuthParser::T__8)
        | (1ULL << BismuthParser::MINUS)
        | (1ULL << BismuthParser::NOT)
        | (1ULL << BismuthParser::MULTIPLY)
        | (1ULL << BismuthParser::BIT_NOT)
        | (1ULL << BismuthParser::LPAR)
        | (1ULL << BismuthParser::LBRC)
        | (1ULL << BismuthParser::DEC_LITERAL)
        | (1ULL << BismuthParser::HEX_LITERAL)
        | (1ULL << BismuthParser::BIN_LITERAL))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 69)) & ((1ULL << (BismuthParser::TYPE_BOX - 69))
        | (1ULL << (BismuthParser::EXEC - 69))
        | (1ULL << (BismuthParser::COPY - 69))
        | (1ULL << (BismuthParser::FALSE - 69))
        | (1ULL << (BismuthParser::TRUE - 69))
        | (1ULL << (BismuthParser::STRING - 69))
        | (1ULL << (BismuthParser::VARIABLE - 69)))) != 0)) {
        setState(522);
        expression(0);
      }
      setState(525);
      match(BismuthParser::SEMICOLON);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<BismuthParser::ExitStatementContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(526);
      match(BismuthParser::EXIT);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<BismuthParser::SkipStatementContext>(_localctx);
      enterOuterAlt(_localctx, 10);
      setState(527);
      match(BismuthParser::T__10);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<BismuthParser::BlockStatementContext>(_localctx);
      enterOuterAlt(_localctx, 11);
      setState(528);
      block();
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramSendContext>(_localctx);
      enterOuterAlt(_localctx, 12);
      setState(529);
      antlrcpp::downCast<ProgramSendContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(530);
      match(BismuthParser::T__11);
      setState(531);
      match(BismuthParser::LPAR);
      setState(532);
      antlrcpp::downCast<ProgramSendContext *>(_localctx)->expr = expression(0);
      setState(533);
      match(BismuthParser::RPAR);
      setState(535);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(534);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramLoopContext>(_localctx);
      enterOuterAlt(_localctx, 13);
      setState(537);
      match(BismuthParser::WHILE);
      setState(538);
      antlrcpp::downCast<ProgramLoopContext *>(_localctx)->check = condition();
      setState(539);
      block();
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<BismuthParser::ForStatementContext>(_localctx);
      enterOuterAlt(_localctx, 14);
      setState(541);
      match(BismuthParser::T__12);
      setState(542);
      match(BismuthParser::LPAR);
      setState(545);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
      case 1: {
        setState(543);
        antlrcpp::downCast<ForStatementContext *>(_localctx)->decl = variableDeclaration();
        break;
      }

      case 2: {
        setState(544);
        antlrcpp::downCast<ForStatementContext *>(_localctx)->assign = assignmentStatement();
        break;
      }

      default:
        break;
      }
      setState(547);
      match(BismuthParser::SEMICOLON);
      setState(548);
      antlrcpp::downCast<ForStatementContext *>(_localctx)->check = condition();
      setState(549);
      match(BismuthParser::SEMICOLON);
      setState(550);
      antlrcpp::downCast<ForStatementContext *>(_localctx)->expr = statement();
      setState(551);
      match(BismuthParser::RPAR);
      setState(552);
      antlrcpp::downCast<ForStatementContext *>(_localctx)->blk = block();
      break;
    }

    case 15: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramCaseContext>(_localctx);
      enterOuterAlt(_localctx, 15);
      setState(554);
      antlrcpp::downCast<ProgramCaseContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(555);
      match(BismuthParser::T__13);
      setState(556);
      match(BismuthParser::LPAR);
      setState(557);
      antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext = protoAlternative();
      antlrcpp::downCast<ProgramCaseContext *>(_localctx)->opts.push_back(antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext);
      setState(559); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(558);
        antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext = protoAlternative();
        antlrcpp::downCast<ProgramCaseContext *>(_localctx)->opts.push_back(antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext);
        setState(561); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << BismuthParser::T__23)
        | (1ULL << BismuthParser::MINUS)
        | (1ULL << BismuthParser::NOT)
        | (1ULL << BismuthParser::PLUS)
        | (1ULL << BismuthParser::LPAR))) != 0) || ((((_la - 92) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 92)) & ((1ULL << (BismuthParser::EXTERNAL_CHOICE - 92))
        | (1ULL << (BismuthParser::INTERNAL_CHOICE - 92))
        | (1ULL << (BismuthParser::CLOSEABLE - 92))
        | (1ULL << (BismuthParser::VARIABLE - 92)))) != 0));
      setState(564);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::ELSE) {
        setState(563);
        protoElse();
      }
      setState(566);
      match(BismuthParser::RPAR);
      setState(570);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(567);
          antlrcpp::downCast<ProgramCaseContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<ProgramCaseContext *>(_localctx)->rest.push_back(antlrcpp::downCast<ProgramCaseContext *>(_localctx)->statementContext); 
        }
        setState(572);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx);
      }
      break;
    }

    case 16: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramCaseContext>(_localctx);
      enterOuterAlt(_localctx, 16);
      setState(573);
      match(BismuthParser::T__14);
      setState(574);
      antlrcpp::downCast<ProgramCaseContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(577); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(575);
                match(BismuthParser::BIT_OR);
                setState(576);
                antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext = protoAlternative();
                antlrcpp::downCast<ProgramCaseContext *>(_localctx)->opts.push_back(antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(579); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(585);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx)) {
      case 1: {
        setState(581);
        match(BismuthParser::BIT_OR);
        setState(583);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx)) {
        case 1: {
          setState(582);
          protoElse();
          break;
        }

        default:
          break;
        }
        break;
      }

      default:
        break;
      }
      setState(590);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(587);
          antlrcpp::downCast<ProgramCaseContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<ProgramCaseContext *>(_localctx)->rest.push_back(antlrcpp::downCast<ProgramCaseContext *>(_localctx)->statementContext); 
        }
        setState(592);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx);
      }
      break;
    }

    case 17: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramProjectContext>(_localctx);
      enterOuterAlt(_localctx, 17);
      setState(593);
      antlrcpp::downCast<ProgramProjectContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(594);
      match(BismuthParser::LBRC);
      setState(597);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case BismuthParser::VARIABLE: {
          setState(595);
          antlrcpp::downCast<ProgramProjectContext *>(_localctx)->lbl = match(BismuthParser::VARIABLE);
          break;
        }

        case BismuthParser::T__23:
        case BismuthParser::MINUS:
        case BismuthParser::NOT:
        case BismuthParser::PLUS:
        case BismuthParser::LPAR:
        case BismuthParser::EXTERNAL_CHOICE:
        case BismuthParser::INTERNAL_CHOICE:
        case BismuthParser::CLOSEABLE: {
          setState(596);
          antlrcpp::downCast<ProgramProjectContext *>(_localctx)->sel = protocol();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(599);
      match(BismuthParser::RBRC);
      setState(601);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(600);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 18: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramContractContext>(_localctx);
      enterOuterAlt(_localctx, 18);
      setState(603);
      match(BismuthParser::T__15);
      setState(604);
      match(BismuthParser::LPAR);
      setState(605);
      antlrcpp::downCast<ProgramContractContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(606);
      match(BismuthParser::RPAR);
      setState(608);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(607);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 19: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramContractContext>(_localctx);
      enterOuterAlt(_localctx, 19);
      setState(610);
      match(BismuthParser::T__16);
      setState(611);
      match(BismuthParser::LPAR);
      setState(612);
      antlrcpp::downCast<ProgramContractContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(613);
      match(BismuthParser::RPAR);
      setState(615);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(614);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 20: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramWeakenContext>(_localctx);
      enterOuterAlt(_localctx, 20);
      setState(617);
      match(BismuthParser::T__17);
      setState(618);
      match(BismuthParser::LPAR);
      setState(619);
      antlrcpp::downCast<ProgramWeakenContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(620);
      match(BismuthParser::RPAR);
      setState(622);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(621);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 21: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramAcceptContext>(_localctx);
      enterOuterAlt(_localctx, 21);
      setState(624);
      match(BismuthParser::T__18);
      setState(625);
      match(BismuthParser::LPAR);
      setState(626);
      antlrcpp::downCast<ProgramAcceptContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(627);
      match(BismuthParser::RPAR);
      setState(628);
      block();
      break;
    }

    case 22: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramAcceptWhileContext>(_localctx);
      enterOuterAlt(_localctx, 22);
      setState(629);
      match(BismuthParser::T__19);
      setState(630);
      match(BismuthParser::LPAR);
      setState(631);
      antlrcpp::downCast<ProgramAcceptWhileContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(632);
      match(BismuthParser::COMMA);
      setState(633);
      antlrcpp::downCast<ProgramAcceptWhileContext *>(_localctx)->ex = expression(0);
      setState(634);
      match(BismuthParser::RPAR);
      setState(635);
      block();
      break;
    }

    case 23: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramAcceptIfContext>(_localctx);
      enterOuterAlt(_localctx, 23);
      setState(637);
      match(BismuthParser::T__20);
      setState(638);
      match(BismuthParser::LPAR);
      setState(639);
      antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(640);
      match(BismuthParser::COMMA);
      setState(641);
      antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->check = expression(0);
      setState(642);
      match(BismuthParser::RPAR);
      setState(643);
      antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->trueBlk = block();
      setState(646);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx)) {
      case 1: {
        setState(644);
        match(BismuthParser::ELSE);
        setState(645);
        antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->falseBlk = block();
        break;
      }

      default:
        break;
      }
      setState(651);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(648);
          antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->rest.push_back(antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->statementContext); 
        }
        setState(653);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx);
      }
      break;
    }

    case 24: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramCloseContext>(_localctx);
      enterOuterAlt(_localctx, 24);
      setState(654);
      match(BismuthParser::T__21);
      setState(655);
      match(BismuthParser::LPAR);
      setState(656);
      antlrcpp::downCast<ProgramCloseContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(657);
      match(BismuthParser::RPAR);
      setState(659);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(658);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 25: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramCancelContext>(_localctx);
      enterOuterAlt(_localctx, 25);
      setState(661);
      match(BismuthParser::T__22);
      setState(662);
      match(BismuthParser::LPAR);
      setState(663);
      antlrcpp::downCast<ProgramCancelContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(664);
      match(BismuthParser::RPAR);
      setState(666);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(665);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 26: {
      _localctx = _tracker.createInstance<BismuthParser::ExpressionStatementContext>(_localctx);
      enterOuterAlt(_localctx, 26);
      setState(668);
      expression(0);
      setState(670);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(669);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentStatementContext ------------------------------------------------------------------

BismuthParser::AssignmentStatementContext::AssignmentStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::AssignmentStatementContext::ASSIGN() {
  return getToken(BismuthParser::ASSIGN, 0);
}

std::vector<BismuthParser::ExpressionContext *> BismuthParser::AssignmentStatementContext::expression() {
  return getRuleContexts<BismuthParser::ExpressionContext>();
}

BismuthParser::ExpressionContext* BismuthParser::AssignmentStatementContext::expression(size_t i) {
  return getRuleContext<BismuthParser::ExpressionContext>(i);
}


size_t BismuthParser::AssignmentStatementContext::getRuleIndex() const {
  return BismuthParser::RuleAssignmentStatement;
}

void BismuthParser::AssignmentStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentStatement(this);
}

void BismuthParser::AssignmentStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentStatement(this);
}


std::any BismuthParser::AssignmentStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitAssignmentStatement(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::AssignmentStatementContext* BismuthParser::assignmentStatement() {
  AssignmentStatementContext *_localctx = _tracker.createInstance<AssignmentStatementContext>(_ctx, getState());
  enterRule(_localctx, 50, BismuthParser::RuleAssignmentStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(674);
    antlrcpp::downCast<AssignmentStatementContext *>(_localctx)->to = expression(0);
    setState(675);
    match(BismuthParser::ASSIGN);
    setState(676);
    antlrcpp::downCast<AssignmentStatementContext *>(_localctx)->a = expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

BismuthParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BismuthParser::TypeOrVarContext* BismuthParser::VariableDeclarationContext::typeOrVar() {
  return getRuleContext<BismuthParser::TypeOrVarContext>(0);
}

std::vector<BismuthParser::AssignmentContext *> BismuthParser::VariableDeclarationContext::assignment() {
  return getRuleContexts<BismuthParser::AssignmentContext>();
}

BismuthParser::AssignmentContext* BismuthParser::VariableDeclarationContext::assignment(size_t i) {
  return getRuleContext<BismuthParser::AssignmentContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::VariableDeclarationContext::COMMA() {
  return getTokens(BismuthParser::COMMA);
}

tree::TerminalNode* BismuthParser::VariableDeclarationContext::COMMA(size_t i) {
  return getToken(BismuthParser::COMMA, i);
}


size_t BismuthParser::VariableDeclarationContext::getRuleIndex() const {
  return BismuthParser::RuleVariableDeclaration;
}

void BismuthParser::VariableDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclaration(this);
}

void BismuthParser::VariableDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclaration(this);
}


std::any BismuthParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::VariableDeclarationContext* BismuthParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 52, BismuthParser::RuleVariableDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(678);
    antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->ty = typeOrVar();
    setState(679);
    antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignmentContext = assignment();
    antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignments.push_back(antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignmentContext);
    setState(684);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BismuthParser::COMMA) {
      setState(680);
      match(BismuthParser::COMMA);
      setState(681);
      antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignmentContext = assignment();
      antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignments.push_back(antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignmentContext);
      setState(686);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ShiftOpContext ------------------------------------------------------------------

BismuthParser::ShiftOpContext::ShiftOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> BismuthParser::ShiftOpContext::GREATER() {
  return getTokens(BismuthParser::GREATER);
}

tree::TerminalNode* BismuthParser::ShiftOpContext::GREATER(size_t i) {
  return getToken(BismuthParser::GREATER, i);
}

std::vector<tree::TerminalNode *> BismuthParser::ShiftOpContext::LESS() {
  return getTokens(BismuthParser::LESS);
}

tree::TerminalNode* BismuthParser::ShiftOpContext::LESS(size_t i) {
  return getToken(BismuthParser::LESS, i);
}


size_t BismuthParser::ShiftOpContext::getRuleIndex() const {
  return BismuthParser::RuleShiftOp;
}

void BismuthParser::ShiftOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShiftOp(this);
}

void BismuthParser::ShiftOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShiftOp(this);
}


std::any BismuthParser::ShiftOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitShiftOp(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::ShiftOpContext* BismuthParser::shiftOp() {
  ShiftOpContext *_localctx = _tracker.createInstance<ShiftOpContext>(_ctx, getState());
  enterRule(_localctx, 54, BismuthParser::RuleShiftOp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(694);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(687);
      match(BismuthParser::GREATER);
      setState(688);
      match(BismuthParser::GREATER);
      setState(689);
      match(BismuthParser::GREATER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(690);
      match(BismuthParser::GREATER);
      setState(691);
      match(BismuthParser::GREATER);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(692);
      match(BismuthParser::LESS);
      setState(693);
      match(BismuthParser::LESS);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeOrVarContext ------------------------------------------------------------------

BismuthParser::TypeOrVarContext::TypeOrVarContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BismuthParser::TypeContext* BismuthParser::TypeOrVarContext::type() {
  return getRuleContext<BismuthParser::TypeContext>(0);
}

tree::TerminalNode* BismuthParser::TypeOrVarContext::TYPE_VAR() {
  return getToken(BismuthParser::TYPE_VAR, 0);
}


size_t BismuthParser::TypeOrVarContext::getRuleIndex() const {
  return BismuthParser::RuleTypeOrVar;
}

void BismuthParser::TypeOrVarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeOrVar(this);
}

void BismuthParser::TypeOrVarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeOrVar(this);
}


std::any BismuthParser::TypeOrVarContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitTypeOrVar(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::TypeOrVarContext* BismuthParser::typeOrVar() {
  TypeOrVarContext *_localctx = _tracker.createInstance<TypeOrVarContext>(_ctx, getState());
  enterRule(_localctx, 56, BismuthParser::RuleTypeOrVar);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(698);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BismuthParser::LPAR:
      case BismuthParser::TYPE_INT:
      case BismuthParser::TYPE_I32:
      case BismuthParser::TYPE_U32:
      case BismuthParser::TYPE_I64:
      case BismuthParser::TYPE_U64:
      case BismuthParser::TYPE_BOOL:
      case BismuthParser::TYPE_STR:
      case BismuthParser::TYPE_UNIT:
      case BismuthParser::TYPE_BOX:
      case BismuthParser::TYPE_PROGRAM:
      case BismuthParser::TYPE_CHANNEL:
      case BismuthParser::VARIABLE: {
        enterOuterAlt(_localctx, 1);
        setState(696);
        type(0);
        break;
      }

      case BismuthParser::TYPE_VAR: {
        enterOuterAlt(_localctx, 2);
        setState(697);
        match(BismuthParser::TYPE_VAR);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProtocolContext ------------------------------------------------------------------

BismuthParser::ProtocolContext::ProtocolContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BismuthParser::SubProtocolContext *> BismuthParser::ProtocolContext::subProtocol() {
  return getRuleContexts<BismuthParser::SubProtocolContext>();
}

BismuthParser::SubProtocolContext* BismuthParser::ProtocolContext::subProtocol(size_t i) {
  return getRuleContext<BismuthParser::SubProtocolContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::ProtocolContext::SEMICOLON() {
  return getTokens(BismuthParser::SEMICOLON);
}

tree::TerminalNode* BismuthParser::ProtocolContext::SEMICOLON(size_t i) {
  return getToken(BismuthParser::SEMICOLON, i);
}

tree::TerminalNode* BismuthParser::ProtocolContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

tree::TerminalNode* BismuthParser::ProtocolContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}


size_t BismuthParser::ProtocolContext::getRuleIndex() const {
  return BismuthParser::RuleProtocol;
}

void BismuthParser::ProtocolContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProtocol(this);
}

void BismuthParser::ProtocolContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProtocol(this);
}


std::any BismuthParser::ProtocolContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitProtocol(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::ProtocolContext* BismuthParser::protocol() {
  ProtocolContext *_localctx = _tracker.createInstance<ProtocolContext>(_ctx, getState());
  enterRule(_localctx, 58, BismuthParser::RuleProtocol);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(720);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 83, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(700);
      antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext = subProtocol();
      antlrcpp::downCast<ProtocolContext *>(_localctx)->protos.push_back(antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext);
      setState(705);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx);
      while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1 + 1) {
          setState(701);
          match(BismuthParser::SEMICOLON);
          setState(702);
          antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext = subProtocol();
          antlrcpp::downCast<ProtocolContext *>(_localctx)->protos.push_back(antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext); 
        }
        setState(707);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(708);
      match(BismuthParser::LPAR);
      setState(709);
      antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext = subProtocol();
      antlrcpp::downCast<ProtocolContext *>(_localctx)->protos.push_back(antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext);
      setState(714);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx);
      while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1 + 1) {
          setState(710);
          match(BismuthParser::SEMICOLON);
          setState(711);
          antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext = subProtocol();
          antlrcpp::downCast<ProtocolContext *>(_localctx)->protos.push_back(antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext); 
        }
        setState(716);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx);
      }
      setState(717);
      match(BismuthParser::RPAR);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(719);
      antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext = subProtocol();
      antlrcpp::downCast<ProtocolContext *>(_localctx)->protos.push_back(antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SubProtocolContext ------------------------------------------------------------------

BismuthParser::SubProtocolContext::SubProtocolContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t BismuthParser::SubProtocolContext::getRuleIndex() const {
  return BismuthParser::RuleSubProtocol;
}

void BismuthParser::SubProtocolContext::copyFrom(SubProtocolContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- WnProtoContext ------------------------------------------------------------------

BismuthParser::ProtocolContext* BismuthParser::WnProtoContext::protocol() {
  return getRuleContext<BismuthParser::ProtocolContext>(0);
}

BismuthParser::WnProtoContext::WnProtoContext(SubProtocolContext *ctx) { copyFrom(ctx); }

void BismuthParser::WnProtoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWnProto(this);
}
void BismuthParser::WnProtoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWnProto(this);
}

std::any BismuthParser::WnProtoContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitWnProto(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CloseableProtoContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::CloseableProtoContext::CLOSEABLE() {
  return getToken(BismuthParser::CLOSEABLE, 0);
}

tree::TerminalNode* BismuthParser::CloseableProtoContext::LESS() {
  return getToken(BismuthParser::LESS, 0);
}

tree::TerminalNode* BismuthParser::CloseableProtoContext::GREATER() {
  return getToken(BismuthParser::GREATER, 0);
}

BismuthParser::ProtocolContext* BismuthParser::CloseableProtoContext::protocol() {
  return getRuleContext<BismuthParser::ProtocolContext>(0);
}

BismuthParser::CloseableProtoContext::CloseableProtoContext(SubProtocolContext *ctx) { copyFrom(ctx); }

void BismuthParser::CloseableProtoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCloseableProto(this);
}
void BismuthParser::CloseableProtoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCloseableProto(this);
}

std::any BismuthParser::CloseableProtoContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitCloseableProto(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SendTypeContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::SendTypeContext::MINUS() {
  return getToken(BismuthParser::MINUS, 0);
}

BismuthParser::TypeContext* BismuthParser::SendTypeContext::type() {
  return getRuleContext<BismuthParser::TypeContext>(0);
}

BismuthParser::SendTypeContext::SendTypeContext(SubProtocolContext *ctx) { copyFrom(ctx); }

void BismuthParser::SendTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSendType(this);
}
void BismuthParser::SendTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSendType(this);
}

std::any BismuthParser::SendTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitSendType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntChoiceProtoContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::IntChoiceProtoContext::INTERNAL_CHOICE() {
  return getToken(BismuthParser::INTERNAL_CHOICE, 0);
}

tree::TerminalNode* BismuthParser::IntChoiceProtoContext::LESS() {
  return getToken(BismuthParser::LESS, 0);
}

tree::TerminalNode* BismuthParser::IntChoiceProtoContext::GREATER() {
  return getToken(BismuthParser::GREATER, 0);
}

std::vector<BismuthParser::ProtoBranchContext *> BismuthParser::IntChoiceProtoContext::protoBranch() {
  return getRuleContexts<BismuthParser::ProtoBranchContext>();
}

BismuthParser::ProtoBranchContext* BismuthParser::IntChoiceProtoContext::protoBranch(size_t i) {
  return getRuleContext<BismuthParser::ProtoBranchContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::IntChoiceProtoContext::COMMA() {
  return getTokens(BismuthParser::COMMA);
}

tree::TerminalNode* BismuthParser::IntChoiceProtoContext::COMMA(size_t i) {
  return getToken(BismuthParser::COMMA, i);
}

BismuthParser::IntChoiceProtoContext::IntChoiceProtoContext(SubProtocolContext *ctx) { copyFrom(ctx); }

void BismuthParser::IntChoiceProtoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntChoiceProto(this);
}
void BismuthParser::IntChoiceProtoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntChoiceProto(this);
}

std::any BismuthParser::IntChoiceProtoContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitIntChoiceProto(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RecvTypeContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::RecvTypeContext::PLUS() {
  return getToken(BismuthParser::PLUS, 0);
}

BismuthParser::TypeContext* BismuthParser::RecvTypeContext::type() {
  return getRuleContext<BismuthParser::TypeContext>(0);
}

BismuthParser::RecvTypeContext::RecvTypeContext(SubProtocolContext *ctx) { copyFrom(ctx); }

void BismuthParser::RecvTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRecvType(this);
}
void BismuthParser::RecvTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRecvType(this);
}

std::any BismuthParser::RecvTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitRecvType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OcProtoContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::OcProtoContext::NOT() {
  return getToken(BismuthParser::NOT, 0);
}

BismuthParser::ProtocolContext* BismuthParser::OcProtoContext::protocol() {
  return getRuleContext<BismuthParser::ProtocolContext>(0);
}

BismuthParser::OcProtoContext::OcProtoContext(SubProtocolContext *ctx) { copyFrom(ctx); }

void BismuthParser::OcProtoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOcProto(this);
}
void BismuthParser::OcProtoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOcProto(this);
}

std::any BismuthParser::OcProtoContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitOcProto(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExtChoiceProtoContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ExtChoiceProtoContext::EXTERNAL_CHOICE() {
  return getToken(BismuthParser::EXTERNAL_CHOICE, 0);
}

tree::TerminalNode* BismuthParser::ExtChoiceProtoContext::LESS() {
  return getToken(BismuthParser::LESS, 0);
}

tree::TerminalNode* BismuthParser::ExtChoiceProtoContext::GREATER() {
  return getToken(BismuthParser::GREATER, 0);
}

std::vector<BismuthParser::ProtoBranchContext *> BismuthParser::ExtChoiceProtoContext::protoBranch() {
  return getRuleContexts<BismuthParser::ProtoBranchContext>();
}

BismuthParser::ProtoBranchContext* BismuthParser::ExtChoiceProtoContext::protoBranch(size_t i) {
  return getRuleContext<BismuthParser::ProtoBranchContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::ExtChoiceProtoContext::COMMA() {
  return getTokens(BismuthParser::COMMA);
}

tree::TerminalNode* BismuthParser::ExtChoiceProtoContext::COMMA(size_t i) {
  return getToken(BismuthParser::COMMA, i);
}

BismuthParser::ExtChoiceProtoContext::ExtChoiceProtoContext(SubProtocolContext *ctx) { copyFrom(ctx); }

void BismuthParser::ExtChoiceProtoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExtChoiceProto(this);
}
void BismuthParser::ExtChoiceProtoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExtChoiceProto(this);
}

std::any BismuthParser::ExtChoiceProtoContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitExtChoiceProto(this);
  else
    return visitor->visitChildren(this);
}
BismuthParser::SubProtocolContext* BismuthParser::subProtocol() {
  SubProtocolContext *_localctx = _tracker.createInstance<SubProtocolContext>(_ctx, getState());
  enterRule(_localctx, 60, BismuthParser::RuleSubProtocol);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(757);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BismuthParser::PLUS: {
        _localctx = _tracker.createInstance<BismuthParser::RecvTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(722);
        match(BismuthParser::PLUS);
        setState(723);
        antlrcpp::downCast<RecvTypeContext *>(_localctx)->ty = type(0);
        break;
      }

      case BismuthParser::MINUS: {
        _localctx = _tracker.createInstance<BismuthParser::SendTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(724);
        match(BismuthParser::MINUS);
        setState(725);
        antlrcpp::downCast<SendTypeContext *>(_localctx)->ty = type(0);
        break;
      }

      case BismuthParser::T__23: {
        _localctx = _tracker.createInstance<BismuthParser::WnProtoContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(726);
        match(BismuthParser::T__23);
        setState(727);
        antlrcpp::downCast<WnProtoContext *>(_localctx)->proto = protocol();
        break;
      }

      case BismuthParser::NOT: {
        _localctx = _tracker.createInstance<BismuthParser::OcProtoContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(728);
        match(BismuthParser::NOT);
        setState(729);
        antlrcpp::downCast<OcProtoContext *>(_localctx)->proto = protocol();
        break;
      }

      case BismuthParser::EXTERNAL_CHOICE: {
        _localctx = _tracker.createInstance<BismuthParser::ExtChoiceProtoContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(730);
        match(BismuthParser::EXTERNAL_CHOICE);
        setState(731);
        match(BismuthParser::LESS);
        setState(732);
        antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoBranchContext = protoBranch();
        antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoOpts.push_back(antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoBranchContext);
        setState(735); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(733);
          match(BismuthParser::COMMA);
          setState(734);
          antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoBranchContext = protoBranch();
          antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoOpts.push_back(antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoBranchContext);
          setState(737); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == BismuthParser::COMMA);
        setState(739);
        match(BismuthParser::GREATER);
        break;
      }

      case BismuthParser::INTERNAL_CHOICE: {
        _localctx = _tracker.createInstance<BismuthParser::IntChoiceProtoContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(741);
        match(BismuthParser::INTERNAL_CHOICE);
        setState(742);
        match(BismuthParser::LESS);
        setState(743);
        antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoBranchContext = protoBranch();
        antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoOpts.push_back(antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoBranchContext);
        setState(746); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(744);
          match(BismuthParser::COMMA);
          setState(745);
          antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoBranchContext = protoBranch();
          antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoOpts.push_back(antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoBranchContext);
          setState(748); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == BismuthParser::COMMA);
        setState(750);
        match(BismuthParser::GREATER);
        break;
      }

      case BismuthParser::CLOSEABLE: {
        _localctx = _tracker.createInstance<BismuthParser::CloseableProtoContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(752);
        match(BismuthParser::CLOSEABLE);
        setState(753);
        match(BismuthParser::LESS);
        setState(754);
        antlrcpp::downCast<CloseableProtoContext *>(_localctx)->proto = protocol();
        setState(755);
        match(BismuthParser::GREATER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProtoBranchContext ------------------------------------------------------------------

BismuthParser::ProtoBranchContext::ProtoBranchContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BismuthParser::ProtocolContext* BismuthParser::ProtoBranchContext::protocol() {
  return getRuleContext<BismuthParser::ProtocolContext>(0);
}

tree::TerminalNode* BismuthParser::ProtoBranchContext::COLON() {
  return getToken(BismuthParser::COLON, 0);
}

tree::TerminalNode* BismuthParser::ProtoBranchContext::VARIABLE() {
  return getToken(BismuthParser::VARIABLE, 0);
}


size_t BismuthParser::ProtoBranchContext::getRuleIndex() const {
  return BismuthParser::RuleProtoBranch;
}

void BismuthParser::ProtoBranchContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProtoBranch(this);
}

void BismuthParser::ProtoBranchContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProtoBranch(this);
}


std::any BismuthParser::ProtoBranchContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitProtoBranch(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::ProtoBranchContext* BismuthParser::protoBranch() {
  ProtoBranchContext *_localctx = _tracker.createInstance<ProtoBranchContext>(_ctx, getState());
  enterRule(_localctx, 62, BismuthParser::RuleProtoBranch);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(763);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BismuthParser::T__23:
      case BismuthParser::MINUS:
      case BismuthParser::NOT:
      case BismuthParser::PLUS:
      case BismuthParser::LPAR:
      case BismuthParser::EXTERNAL_CHOICE:
      case BismuthParser::INTERNAL_CHOICE:
      case BismuthParser::CLOSEABLE: {
        enterOuterAlt(_localctx, 1);
        setState(759);
        protocol();
        break;
      }

      case BismuthParser::VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(760);
        antlrcpp::downCast<ProtoBranchContext *>(_localctx)->lbl = match(BismuthParser::VARIABLE);
        setState(761);
        match(BismuthParser::COLON);
        setState(762);
        protocol();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

BismuthParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t BismuthParser::TypeContext::getRuleIndex() const {
  return BismuthParser::RuleType;
}

void BismuthParser::TypeContext::copyFrom(TypeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LambdaTypeContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> BismuthParser::LambdaTypeContext::LPAR() {
  return getTokens(BismuthParser::LPAR);
}

tree::TerminalNode* BismuthParser::LambdaTypeContext::LPAR(size_t i) {
  return getToken(BismuthParser::LPAR, i);
}

std::vector<tree::TerminalNode *> BismuthParser::LambdaTypeContext::RPAR() {
  return getTokens(BismuthParser::RPAR);
}

tree::TerminalNode* BismuthParser::LambdaTypeContext::RPAR(size_t i) {
  return getToken(BismuthParser::RPAR, i);
}

tree::TerminalNode* BismuthParser::LambdaTypeContext::MAPS_TO() {
  return getToken(BismuthParser::MAPS_TO, 0);
}

std::vector<BismuthParser::TypeContext *> BismuthParser::LambdaTypeContext::type() {
  return getRuleContexts<BismuthParser::TypeContext>();
}

BismuthParser::TypeContext* BismuthParser::LambdaTypeContext::type(size_t i) {
  return getRuleContext<BismuthParser::TypeContext>(i);
}

std::vector<tree::TerminalNode *> BismuthParser::LambdaTypeContext::COMMA() {
  return getTokens(BismuthParser::COMMA);
}

tree::TerminalNode* BismuthParser::LambdaTypeContext::COMMA(size_t i) {
  return getToken(BismuthParser::COMMA, i);
}

BismuthParser::LambdaTypeContext::LambdaTypeContext(TypeContext *ctx) { copyFrom(ctx); }

void BismuthParser::LambdaTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLambdaType(this);
}
void BismuthParser::LambdaTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLambdaType(this);
}

std::any BismuthParser::LambdaTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitLambdaType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CustomTypeContext ------------------------------------------------------------------

BismuthParser::PathContext* BismuthParser::CustomTypeContext::path() {
  return getRuleContext<BismuthParser::PathContext>(0);
}

BismuthParser::CustomTypeContext::CustomTypeContext(TypeContext *ctx) { copyFrom(ctx); }

void BismuthParser::CustomTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCustomType(this);
}
void BismuthParser::CustomTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCustomType(this);
}

std::any BismuthParser::CustomTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitCustomType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayTypeContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ArrayTypeContext::LBRC() {
  return getToken(BismuthParser::LBRC, 0);
}

tree::TerminalNode* BismuthParser::ArrayTypeContext::RBRC() {
  return getToken(BismuthParser::RBRC, 0);
}

BismuthParser::TypeContext* BismuthParser::ArrayTypeContext::type() {
  return getRuleContext<BismuthParser::TypeContext>(0);
}

tree::TerminalNode* BismuthParser::ArrayTypeContext::DEC_LITERAL() {
  return getToken(BismuthParser::DEC_LITERAL, 0);
}

BismuthParser::ArrayTypeContext::ArrayTypeContext(TypeContext *ctx) { copyFrom(ctx); }

void BismuthParser::ArrayTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayType(this);
}
void BismuthParser::ArrayTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayType(this);
}

std::any BismuthParser::ArrayTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitArrayType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DynArrayTypeContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::DynArrayTypeContext::LBRC() {
  return getToken(BismuthParser::LBRC, 0);
}

tree::TerminalNode* BismuthParser::DynArrayTypeContext::RBRC() {
  return getToken(BismuthParser::RBRC, 0);
}

BismuthParser::TypeContext* BismuthParser::DynArrayTypeContext::type() {
  return getRuleContext<BismuthParser::TypeContext>(0);
}

BismuthParser::DynArrayTypeContext::DynArrayTypeContext(TypeContext *ctx) { copyFrom(ctx); }

void BismuthParser::DynArrayTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDynArrayType(this);
}
void BismuthParser::DynArrayTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDynArrayType(this);
}

std::any BismuthParser::DynArrayTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitDynArrayType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SumTypeContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::SumTypeContext::LPAR() {
  return getToken(BismuthParser::LPAR, 0);
}

std::vector<BismuthParser::TypeContext *> BismuthParser::SumTypeContext::type() {
  return getRuleContexts<BismuthParser::TypeContext>();
}

BismuthParser::TypeContext* BismuthParser::SumTypeContext::type(size_t i) {
  return getRuleContext<BismuthParser::TypeContext>(i);
}

tree::TerminalNode* BismuthParser::SumTypeContext::RPAR() {
  return getToken(BismuthParser::RPAR, 0);
}

std::vector<tree::TerminalNode *> BismuthParser::SumTypeContext::PLUS() {
  return getTokens(BismuthParser::PLUS);
}

tree::TerminalNode* BismuthParser::SumTypeContext::PLUS(size_t i) {
  return getToken(BismuthParser::PLUS, i);
}

BismuthParser::SumTypeContext::SumTypeContext(TypeContext *ctx) { copyFrom(ctx); }

void BismuthParser::SumTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSumType(this);
}
void BismuthParser::SumTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSumType(this);
}

std::any BismuthParser::SumTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitSumType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BaseTypeContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::BaseTypeContext::TYPE_INT() {
  return getToken(BismuthParser::TYPE_INT, 0);
}

tree::TerminalNode* BismuthParser::BaseTypeContext::TYPE_I32() {
  return getToken(BismuthParser::TYPE_I32, 0);
}

tree::TerminalNode* BismuthParser::BaseTypeContext::TYPE_BOOL() {
  return getToken(BismuthParser::TYPE_BOOL, 0);
}

tree::TerminalNode* BismuthParser::BaseTypeContext::TYPE_STR() {
  return getToken(BismuthParser::TYPE_STR, 0);
}

tree::TerminalNode* BismuthParser::BaseTypeContext::TYPE_UNIT() {
  return getToken(BismuthParser::TYPE_UNIT, 0);
}

tree::TerminalNode* BismuthParser::BaseTypeContext::TYPE_U32() {
  return getToken(BismuthParser::TYPE_U32, 0);
}

tree::TerminalNode* BismuthParser::BaseTypeContext::TYPE_I64() {
  return getToken(BismuthParser::TYPE_I64, 0);
}

tree::TerminalNode* BismuthParser::BaseTypeContext::TYPE_U64() {
  return getToken(BismuthParser::TYPE_U64, 0);
}

BismuthParser::BaseTypeContext::BaseTypeContext(TypeContext *ctx) { copyFrom(ctx); }

void BismuthParser::BaseTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBaseType(this);
}
void BismuthParser::BaseTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBaseType(this);
}

std::any BismuthParser::BaseTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitBaseType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TemplatedTypeContext ------------------------------------------------------------------

BismuthParser::GenericSpecifierContext* BismuthParser::TemplatedTypeContext::genericSpecifier() {
  return getRuleContext<BismuthParser::GenericSpecifierContext>(0);
}

BismuthParser::TypeContext* BismuthParser::TemplatedTypeContext::type() {
  return getRuleContext<BismuthParser::TypeContext>(0);
}

BismuthParser::TemplatedTypeContext::TemplatedTypeContext(TypeContext *ctx) { copyFrom(ctx); }

void BismuthParser::TemplatedTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplatedType(this);
}
void BismuthParser::TemplatedTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplatedType(this);
}

std::any BismuthParser::TemplatedTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitTemplatedType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ProgramTypeContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ProgramTypeContext::TYPE_PROGRAM() {
  return getToken(BismuthParser::TYPE_PROGRAM, 0);
}

tree::TerminalNode* BismuthParser::ProgramTypeContext::LESS() {
  return getToken(BismuthParser::LESS, 0);
}

tree::TerminalNode* BismuthParser::ProgramTypeContext::GREATER() {
  return getToken(BismuthParser::GREATER, 0);
}

BismuthParser::ProtocolContext* BismuthParser::ProgramTypeContext::protocol() {
  return getRuleContext<BismuthParser::ProtocolContext>(0);
}

BismuthParser::ProgramTypeContext::ProgramTypeContext(TypeContext *ctx) { copyFrom(ctx); }

void BismuthParser::ProgramTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgramType(this);
}
void BismuthParser::ProgramTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgramType(this);
}

std::any BismuthParser::ProgramTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitProgramType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ChannelTypeContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::ChannelTypeContext::TYPE_CHANNEL() {
  return getToken(BismuthParser::TYPE_CHANNEL, 0);
}

tree::TerminalNode* BismuthParser::ChannelTypeContext::LESS() {
  return getToken(BismuthParser::LESS, 0);
}

tree::TerminalNode* BismuthParser::ChannelTypeContext::GREATER() {
  return getToken(BismuthParser::GREATER, 0);
}

BismuthParser::ProtocolContext* BismuthParser::ChannelTypeContext::protocol() {
  return getRuleContext<BismuthParser::ProtocolContext>(0);
}

BismuthParser::ChannelTypeContext::ChannelTypeContext(TypeContext *ctx) { copyFrom(ctx); }

void BismuthParser::ChannelTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChannelType(this);
}
void BismuthParser::ChannelTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChannelType(this);
}

std::any BismuthParser::ChannelTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitChannelType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BoxTypeContext ------------------------------------------------------------------

tree::TerminalNode* BismuthParser::BoxTypeContext::TYPE_BOX() {
  return getToken(BismuthParser::TYPE_BOX, 0);
}

tree::TerminalNode* BismuthParser::BoxTypeContext::LESS() {
  return getToken(BismuthParser::LESS, 0);
}

tree::TerminalNode* BismuthParser::BoxTypeContext::GREATER() {
  return getToken(BismuthParser::GREATER, 0);
}

BismuthParser::TypeContext* BismuthParser::BoxTypeContext::type() {
  return getRuleContext<BismuthParser::TypeContext>(0);
}

BismuthParser::BoxTypeContext::BoxTypeContext(TypeContext *ctx) { copyFrom(ctx); }

void BismuthParser::BoxTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoxType(this);
}
void BismuthParser::BoxTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoxType(this);
}

std::any BismuthParser::BoxTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitBoxType(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::TypeContext* BismuthParser::type() {
   return type(0);
}

BismuthParser::TypeContext* BismuthParser::type(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  BismuthParser::TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, parentState);
  BismuthParser::TypeContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 64;
  enterRecursionRule(_localctx, 64, BismuthParser::RuleType, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(849);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 98, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<BaseTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(766);
      antlrcpp::downCast<BaseTypeContext *>(_localctx)->ty = _input->LT(1);
      _la = _input->LA(1);
      if (!(((((_la - 60) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 60)) & ((1ULL << (BismuthParser::TYPE_INT - 60))
        | (1ULL << (BismuthParser::TYPE_I32 - 60))
        | (1ULL << (BismuthParser::TYPE_U32 - 60))
        | (1ULL << (BismuthParser::TYPE_I64 - 60))
        | (1ULL << (BismuthParser::TYPE_U64 - 60))
        | (1ULL << (BismuthParser::TYPE_BOOL - 60))
        | (1ULL << (BismuthParser::TYPE_STR - 60))
        | (1ULL << (BismuthParser::TYPE_UNIT - 60)))) != 0))) {
        antlrcpp::downCast<BaseTypeContext *>(_localctx)->ty = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<LambdaTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(767);
      match(BismuthParser::LPAR);
      setState(776);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 46) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 46)) & ((1ULL << (BismuthParser::LPAR - 46))
        | (1ULL << (BismuthParser::TYPE_INT - 46))
        | (1ULL << (BismuthParser::TYPE_I32 - 46))
        | (1ULL << (BismuthParser::TYPE_U32 - 46))
        | (1ULL << (BismuthParser::TYPE_I64 - 46))
        | (1ULL << (BismuthParser::TYPE_U64 - 46))
        | (1ULL << (BismuthParser::TYPE_BOOL - 46))
        | (1ULL << (BismuthParser::TYPE_STR - 46))
        | (1ULL << (BismuthParser::TYPE_UNIT - 46))
        | (1ULL << (BismuthParser::TYPE_BOX - 46))
        | (1ULL << (BismuthParser::TYPE_PROGRAM - 46))
        | (1ULL << (BismuthParser::TYPE_CHANNEL - 46))
        | (1ULL << (BismuthParser::VARIABLE - 46)))) != 0)) {
        setState(768);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
        setState(773);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == BismuthParser::COMMA) {
          setState(769);
          match(BismuthParser::COMMA);
          setState(770);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
          setState(775);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(778);
      match(BismuthParser::RPAR);
      setState(779);
      match(BismuthParser::MAPS_TO);
      setState(783);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 90, _ctx)) {
      case 1: {
        setState(780);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->returnType = type(0);
        break;
      }

      case 2: {
        setState(781);
        match(BismuthParser::LPAR);
        setState(782);
        match(BismuthParser::RPAR);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<LambdaTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(785);
      match(BismuthParser::LPAR);
      setState(794);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 46) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 46)) & ((1ULL << (BismuthParser::LPAR - 46))
        | (1ULL << (BismuthParser::TYPE_INT - 46))
        | (1ULL << (BismuthParser::TYPE_I32 - 46))
        | (1ULL << (BismuthParser::TYPE_U32 - 46))
        | (1ULL << (BismuthParser::TYPE_I64 - 46))
        | (1ULL << (BismuthParser::TYPE_U64 - 46))
        | (1ULL << (BismuthParser::TYPE_BOOL - 46))
        | (1ULL << (BismuthParser::TYPE_STR - 46))
        | (1ULL << (BismuthParser::TYPE_UNIT - 46))
        | (1ULL << (BismuthParser::TYPE_BOX - 46))
        | (1ULL << (BismuthParser::TYPE_PROGRAM - 46))
        | (1ULL << (BismuthParser::TYPE_CHANNEL - 46))
        | (1ULL << (BismuthParser::VARIABLE - 46)))) != 0)) {
        setState(786);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
        setState(791);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == BismuthParser::COMMA) {
          setState(787);
          match(BismuthParser::COMMA);
          setState(788);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
          setState(793);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(796);
      match(BismuthParser::MAPS_TO);
      setState(800);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 93, _ctx)) {
      case 1: {
        setState(797);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->returnType = type(0);
        break;
      }

      case 2: {
        setState(798);
        match(BismuthParser::LPAR);
        setState(799);
        match(BismuthParser::RPAR);
        break;
      }

      default:
        break;
      }
      setState(802);
      match(BismuthParser::RPAR);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<LambdaTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(803);
      match(BismuthParser::LPAR);
      setState(804);
      match(BismuthParser::LPAR);
      setState(813);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 46) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 46)) & ((1ULL << (BismuthParser::LPAR - 46))
        | (1ULL << (BismuthParser::TYPE_INT - 46))
        | (1ULL << (BismuthParser::TYPE_I32 - 46))
        | (1ULL << (BismuthParser::TYPE_U32 - 46))
        | (1ULL << (BismuthParser::TYPE_I64 - 46))
        | (1ULL << (BismuthParser::TYPE_U64 - 46))
        | (1ULL << (BismuthParser::TYPE_BOOL - 46))
        | (1ULL << (BismuthParser::TYPE_STR - 46))
        | (1ULL << (BismuthParser::TYPE_UNIT - 46))
        | (1ULL << (BismuthParser::TYPE_BOX - 46))
        | (1ULL << (BismuthParser::TYPE_PROGRAM - 46))
        | (1ULL << (BismuthParser::TYPE_CHANNEL - 46))
        | (1ULL << (BismuthParser::VARIABLE - 46)))) != 0)) {
        setState(805);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
        setState(810);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == BismuthParser::COMMA) {
          setState(806);
          match(BismuthParser::COMMA);
          setState(807);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
          setState(812);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(815);
      match(BismuthParser::RPAR);
      setState(816);
      match(BismuthParser::MAPS_TO);
      setState(820);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 96, _ctx)) {
      case 1: {
        setState(817);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->returnType = type(0);
        break;
      }

      case 2: {
        setState(818);
        match(BismuthParser::LPAR);
        setState(819);
        match(BismuthParser::RPAR);
        break;
      }

      default:
        break;
      }
      setState(822);
      match(BismuthParser::RPAR);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<SumTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(823);
      match(BismuthParser::LPAR);
      setState(824);
      type(0);
      setState(827); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(825);
        match(BismuthParser::PLUS);
        setState(826);
        type(0);
        setState(829); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == BismuthParser::PLUS);
      setState(831);
      match(BismuthParser::RPAR);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChannelTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(833);
      match(BismuthParser::TYPE_CHANNEL);
      setState(834);
      match(BismuthParser::LESS);
      setState(835);
      antlrcpp::downCast<ChannelTypeContext *>(_localctx)->proto = protocol();
      setState(836);
      match(BismuthParser::GREATER);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ProgramTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(838);
      match(BismuthParser::TYPE_PROGRAM);
      setState(839);
      match(BismuthParser::LESS);
      setState(840);
      antlrcpp::downCast<ProgramTypeContext *>(_localctx)->proto = protocol();
      setState(841);
      match(BismuthParser::GREATER);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<BoxTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(843);
      match(BismuthParser::TYPE_BOX);
      setState(844);
      match(BismuthParser::LESS);
      setState(845);
      antlrcpp::downCast<BoxTypeContext *>(_localctx)->ty = type(0);
      setState(846);
      match(BismuthParser::GREATER);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<CustomTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(848);
      path();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(872);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 101, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(870);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 100, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<LambdaTypeContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->paramTypes.push_back(previousContext);
          pushNewRecursionContext(newContext, startState, RuleType);
          setState(851);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(856);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == BismuthParser::COMMA) {
            setState(852);
            match(BismuthParser::COMMA);
            setState(853);
            antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
            antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
            setState(858);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
          setState(859);
          match(BismuthParser::MAPS_TO);
          setState(860);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->returnType = type(11);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<ArrayTypeContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->ty = previousContext;
          pushNewRecursionContext(newContext, startState, RuleType);
          setState(861);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(862);
          match(BismuthParser::LBRC);
          setState(863);
          antlrcpp::downCast<ArrayTypeContext *>(_localctx)->len = match(BismuthParser::DEC_LITERAL);
          setState(864);
          match(BismuthParser::RBRC);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<DynArrayTypeContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->ty = previousContext;
          pushNewRecursionContext(newContext, startState, RuleType);
          setState(865);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(866);
          match(BismuthParser::LBRC);
          setState(867);
          match(BismuthParser::RBRC);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<TemplatedTypeContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->ty = previousContext;
          pushNewRecursionContext(newContext, startState, RuleType);
          setState(868);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(869);
          genericSpecifier();
          break;
        }

        default:
          break;
        } 
      }
      setState(874);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 101, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- IntegerValueContext ------------------------------------------------------------------

BismuthParser::IntegerValueContext::IntegerValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::IntegerValueContext::DEC_LITERAL() {
  return getToken(BismuthParser::DEC_LITERAL, 0);
}

tree::TerminalNode* BismuthParser::IntegerValueContext::HEX_LITERAL() {
  return getToken(BismuthParser::HEX_LITERAL, 0);
}

tree::TerminalNode* BismuthParser::IntegerValueContext::BIN_LITERAL() {
  return getToken(BismuthParser::BIN_LITERAL, 0);
}

tree::TerminalNode* BismuthParser::IntegerValueContext::TYPE_I32() {
  return getToken(BismuthParser::TYPE_I32, 0);
}

tree::TerminalNode* BismuthParser::IntegerValueContext::TYPE_U32() {
  return getToken(BismuthParser::TYPE_U32, 0);
}

tree::TerminalNode* BismuthParser::IntegerValueContext::TYPE_I64() {
  return getToken(BismuthParser::TYPE_I64, 0);
}

tree::TerminalNode* BismuthParser::IntegerValueContext::TYPE_U64() {
  return getToken(BismuthParser::TYPE_U64, 0);
}


size_t BismuthParser::IntegerValueContext::getRuleIndex() const {
  return BismuthParser::RuleIntegerValue;
}

void BismuthParser::IntegerValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntegerValue(this);
}

void BismuthParser::IntegerValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntegerValue(this);
}


std::any BismuthParser::IntegerValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitIntegerValue(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::IntegerValueContext* BismuthParser::integerValue() {
  IntegerValueContext *_localctx = _tracker.createInstance<IntegerValueContext>(_ctx, getState());
  enterRule(_localctx, 66, BismuthParser::RuleIntegerValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(875);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << BismuthParser::DEC_LITERAL)
      | (1ULL << BismuthParser::HEX_LITERAL)
      | (1ULL << BismuthParser::BIN_LITERAL))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(877);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 102, _ctx)) {
    case 1: {
      setState(876);
      antlrcpp::downCast<IntegerValueContext *>(_localctx)->ty = _input->LT(1);
      _la = _input->LA(1);
      if (!(((((_la - 61) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 61)) & ((1ULL << (BismuthParser::TYPE_I32 - 61))
        | (1ULL << (BismuthParser::TYPE_U32 - 61))
        | (1ULL << (BismuthParser::TYPE_I64 - 61))
        | (1ULL << (BismuthParser::TYPE_U64 - 61)))) != 0))) {
        antlrcpp::downCast<IntegerValueContext *>(_localctx)->ty = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanConstContext ------------------------------------------------------------------

BismuthParser::BooleanConstContext::BooleanConstContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BismuthParser::BooleanConstContext::TRUE() {
  return getToken(BismuthParser::TRUE, 0);
}

tree::TerminalNode* BismuthParser::BooleanConstContext::FALSE() {
  return getToken(BismuthParser::FALSE, 0);
}


size_t BismuthParser::BooleanConstContext::getRuleIndex() const {
  return BismuthParser::RuleBooleanConst;
}

void BismuthParser::BooleanConstContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanConst(this);
}

void BismuthParser::BooleanConstContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BismuthListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanConst(this);
}


std::any BismuthParser::BooleanConstContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BismuthVisitor*>(visitor))
    return parserVisitor->visitBooleanConst(this);
  else
    return visitor->visitChildren(this);
}

BismuthParser::BooleanConstContext* BismuthParser::booleanConst() {
  BooleanConstContext *_localctx = _tracker.createInstance<BooleanConstContext>(_ctx, getState());
  enterRule(_localctx, 68, BismuthParser::RuleBooleanConst);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(879);
    _la = _input->LA(1);
    if (!(_la == BismuthParser::FALSE

    || _la == BismuthParser::TRUE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool BismuthParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 13: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);
    case 32: return typeSempred(antlrcpp::downCast<TypeContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool BismuthParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 21);
    case 1: return precpred(_ctx, 20);
    case 2: return precpred(_ctx, 19);
    case 3: return precpred(_ctx, 18);
    case 4: return precpred(_ctx, 17);
    case 5: return precpred(_ctx, 16);
    case 6: return precpred(_ctx, 28);
    case 7: return precpred(_ctx, 27);
    case 8: return precpred(_ctx, 24);
    case 9: return precpred(_ctx, 15);
    case 10: return precpred(_ctx, 14);

  default:
    break;
  }
  return true;
}

bool BismuthParser::typeSempred(TypeContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 11: return precpred(_ctx, 10);
    case 12: return precpred(_ctx, 13);
    case 13: return precpred(_ctx, 12);
    case 14: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

void BismuthParser::initialize() {
  std::call_once(bismuthParserOnceFlag, bismuthParserInitialize);
}
