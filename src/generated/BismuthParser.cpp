
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
      "compilationUnit", "structCase", "genericTemplate", "genericEntry", 
      "genericSpecifier", "defineType", "externStatement", "pathElement", 
      "path", "importStatement", "inv_args", "expression", "lambdaConstExpr", 
      "block", "condition", "selectAlternative", "matchAlternative", "protoAlternative", 
      "protoElse", "parameterList", "parameter", "assignment", "statement", 
      "assignmentStatement", "variableDeclaration", "shiftOp", "typeOrVar", 
      "protocol", "subProtocol", "protoBranch", "type", "integerValue", 
      "booleanConst"
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
      "'exit'", "'exec'", "'copy'", "'import'", "'ExternalChoice'", "'InternalChoice'", 
      "'Cancelable'", "'false'", "'true'"
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
      "DEFINE", "EXIT", "EXEC", "COPY", "IMPORT", "EXTERNAL_CHOICE", "INTERNAL_CHOICE", 
      "CLOSEABLE", "FALSE", "TRUE", "STRING", "VARIABLE", "INLINE_COMMENT", 
      "STD_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,97,848,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,1,0,1,0,1,0,5,0,70,8,0,10,
  	0,12,0,73,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,5,2,86,8,2,
  	10,2,12,2,89,9,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,5,3,98,8,3,10,3,12,3,101,
  	9,3,3,3,103,8,3,1,3,1,3,3,3,107,8,3,1,4,1,4,1,4,1,4,5,4,113,8,4,10,4,
  	12,4,116,9,4,1,4,1,4,1,5,1,5,1,5,3,5,123,8,5,1,5,1,5,1,5,1,5,4,5,129,
  	8,5,11,5,12,5,130,1,5,1,5,1,5,1,5,1,5,3,5,138,8,5,1,5,1,5,5,5,142,8,5,
  	10,5,12,5,145,9,5,1,5,1,5,1,5,1,5,3,5,151,8,5,1,5,1,5,1,5,1,5,1,5,3,5,
  	158,8,5,1,5,1,5,1,5,1,5,1,5,3,5,165,8,5,1,5,3,5,168,8,5,1,6,1,6,1,6,1,
  	6,1,6,1,6,3,6,176,8,6,1,6,3,6,179,8,6,1,6,1,6,1,6,3,6,184,8,6,1,6,1,6,
  	1,7,1,7,3,7,190,8,7,1,8,1,8,1,8,5,8,195,8,8,10,8,12,8,198,9,8,1,9,1,9,
  	1,9,1,9,3,9,204,8,9,1,9,3,9,207,8,9,1,10,1,10,1,10,1,10,5,10,213,8,10,
  	10,10,12,10,216,9,10,3,10,218,8,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,5,11,231,8,11,10,11,12,11,234,9,11,1,11,3,11,237,
  	8,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,5,11,250,
  	8,11,10,11,12,11,253,9,11,3,11,255,8,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,3,11,296,8,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,4,11,327,8,11,11,11,12,11,
  	328,1,11,1,11,1,11,4,11,334,8,11,11,11,12,11,335,1,11,1,11,1,11,4,11,
  	341,8,11,11,11,12,11,342,5,11,345,8,11,10,11,12,11,348,9,11,1,12,1,12,
  	1,12,1,12,1,12,3,12,355,8,12,1,12,1,12,1,13,1,13,5,13,361,8,13,10,13,
  	12,13,364,9,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,3,14,373,8,14,1,15,
  	1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,17,1,17,3,17,386,8,17,1,17,
  	1,17,1,17,1,18,1,18,1,18,1,18,1,19,1,19,1,19,5,19,398,8,19,10,19,12,19,
  	401,9,19,3,19,403,8,19,1,20,1,20,1,20,1,21,1,21,1,21,5,21,411,8,21,10,
  	21,12,21,414,9,21,1,21,1,21,3,21,418,8,21,1,22,1,22,1,22,3,22,423,8,22,
  	1,22,1,22,3,22,427,8,22,1,22,1,22,1,22,1,22,1,22,3,22,434,8,22,1,22,5,
  	22,437,8,22,10,22,12,22,440,9,22,1,22,1,22,1,22,5,22,445,8,22,10,22,12,
  	22,448,9,22,1,22,1,22,5,22,452,8,22,10,22,12,22,455,9,22,1,22,1,22,1,
  	22,1,22,5,22,461,8,22,10,22,12,22,464,9,22,1,22,1,22,5,22,468,8,22,10,
  	22,12,22,471,9,22,1,22,1,22,1,22,1,22,5,22,477,8,22,10,22,12,22,480,9,
  	22,1,22,5,22,483,8,22,10,22,12,22,486,9,22,1,22,1,22,3,22,490,8,22,1,
  	22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,502,8,22,1,22,1,
  	22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,512,8,22,1,22,1,22,1,22,1,22,1,
  	22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,4,22,526,8,22,11,22,12,22,527,1,
  	22,3,22,531,8,22,1,22,1,22,5,22,535,8,22,10,22,12,22,538,9,22,1,22,1,
  	22,1,22,1,22,4,22,544,8,22,11,22,12,22,545,1,22,1,22,3,22,550,8,22,3,
  	22,552,8,22,1,22,5,22,555,8,22,10,22,12,22,558,9,22,1,22,1,22,1,22,1,
  	22,3,22,564,8,22,1,22,1,22,3,22,568,8,22,1,22,1,22,1,22,1,22,1,22,3,22,
  	575,8,22,1,22,1,22,1,22,1,22,1,22,3,22,582,8,22,1,22,1,22,1,22,1,22,1,
  	22,3,22,589,8,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,
  	22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,613,8,
  	22,1,22,5,22,616,8,22,10,22,12,22,619,9,22,1,22,1,22,1,22,1,22,1,22,3,
  	22,626,8,22,1,22,1,22,1,22,1,22,1,22,3,22,633,8,22,1,22,1,22,3,22,637,
  	8,22,3,22,639,8,22,1,23,1,23,1,23,1,23,1,24,1,24,1,24,1,24,5,24,649,8,
  	24,10,24,12,24,652,9,24,1,25,1,25,1,25,1,25,1,25,1,25,1,25,3,25,661,8,
  	25,1,26,1,26,3,26,665,8,26,1,27,1,27,1,27,5,27,670,8,27,10,27,12,27,673,
  	9,27,1,27,1,27,1,27,1,27,5,27,679,8,27,10,27,12,27,682,9,27,1,27,1,27,
  	1,27,3,27,687,8,27,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,
  	1,28,1,28,1,28,4,28,702,8,28,11,28,12,28,703,1,28,1,28,1,28,1,28,1,28,
  	1,28,1,28,4,28,713,8,28,11,28,12,28,714,1,28,1,28,1,28,1,28,1,28,1,28,
  	1,28,3,28,724,8,28,1,29,1,29,1,29,1,29,3,29,730,8,29,1,30,1,30,1,30,1,
  	30,1,30,1,30,5,30,738,8,30,10,30,12,30,741,9,30,3,30,743,8,30,1,30,1,
  	30,1,30,1,30,1,30,3,30,750,8,30,1,30,1,30,1,30,1,30,5,30,756,8,30,10,
  	30,12,30,759,9,30,3,30,761,8,30,1,30,1,30,1,30,1,30,3,30,767,8,30,1,30,
  	1,30,1,30,1,30,1,30,1,30,5,30,775,8,30,10,30,12,30,778,9,30,3,30,780,
  	8,30,1,30,1,30,1,30,1,30,1,30,3,30,787,8,30,1,30,1,30,1,30,1,30,1,30,
  	4,30,794,8,30,11,30,12,30,795,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,
  	1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,3,30,816,8,30,1,30,
  	1,30,1,30,5,30,821,8,30,10,30,12,30,824,9,30,1,30,1,30,1,30,1,30,1,30,
  	1,30,1,30,1,30,1,30,1,30,1,30,5,30,837,8,30,10,30,12,30,840,9,30,1,31,
  	1,31,3,31,844,8,31,1,32,1,32,1,32,2,671,680,2,22,60,33,0,2,4,6,8,10,12,
  	14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,
  	60,62,64,0,10,2,0,27,28,39,39,1,0,29,31,2,0,27,27,32,32,1,0,33,36,2,0,
  	40,41,44,44,1,0,37,38,1,0,60,67,1,0,57,59,1,0,61,64,1,0,91,92,980,0,71,
  	1,0,0,0,2,76,1,0,0,0,4,81,1,0,0,0,6,106,1,0,0,0,8,108,1,0,0,0,10,167,
  	1,0,0,0,12,169,1,0,0,0,14,187,1,0,0,0,16,191,1,0,0,0,18,199,1,0,0,0,20,
  	208,1,0,0,0,22,295,1,0,0,0,24,349,1,0,0,0,26,358,1,0,0,0,28,372,1,0,0,
  	0,30,374,1,0,0,0,32,378,1,0,0,0,34,385,1,0,0,0,36,390,1,0,0,0,38,402,
  	1,0,0,0,40,404,1,0,0,0,42,407,1,0,0,0,44,638,1,0,0,0,46,640,1,0,0,0,48,
  	644,1,0,0,0,50,660,1,0,0,0,52,664,1,0,0,0,54,686,1,0,0,0,56,723,1,0,0,
  	0,58,729,1,0,0,0,60,815,1,0,0,0,62,841,1,0,0,0,64,845,1,0,0,0,66,70,3,
  	18,9,0,67,70,3,12,6,0,68,70,3,10,5,0,69,66,1,0,0,0,69,67,1,0,0,0,69,68,
  	1,0,0,0,70,73,1,0,0,0,71,69,1,0,0,0,71,72,1,0,0,0,72,74,1,0,0,0,73,71,
  	1,0,0,0,74,75,5,0,0,1,75,1,1,0,0,0,76,77,3,60,30,0,77,78,5,94,0,0,78,
  	79,1,0,0,0,79,80,5,52,0,0,80,3,1,0,0,0,81,82,5,33,0,0,82,87,3,6,3,0,83,
  	84,5,55,0,0,84,86,3,6,3,0,85,83,1,0,0,0,86,89,1,0,0,0,87,85,1,0,0,0,87,
  	88,1,0,0,0,88,90,1,0,0,0,89,87,1,0,0,0,90,91,5,36,0,0,91,5,1,0,0,0,92,
  	102,5,94,0,0,93,94,5,53,0,0,94,99,3,60,30,0,95,96,5,55,0,0,96,98,3,60,
  	30,0,97,95,1,0,0,0,98,101,1,0,0,0,99,97,1,0,0,0,99,100,1,0,0,0,100,103,
  	1,0,0,0,101,99,1,0,0,0,102,93,1,0,0,0,102,103,1,0,0,0,103,107,1,0,0,0,
  	104,105,5,1,0,0,105,107,5,94,0,0,106,92,1,0,0,0,106,104,1,0,0,0,107,7,
  	1,0,0,0,108,109,5,33,0,0,109,114,3,60,30,0,110,111,5,55,0,0,111,113,3,
  	60,30,0,112,110,1,0,0,0,113,116,1,0,0,0,114,112,1,0,0,0,114,115,1,0,0,
  	0,115,117,1,0,0,0,116,114,1,0,0,0,117,118,5,36,0,0,118,9,1,0,0,0,119,
  	120,5,74,0,0,120,122,5,94,0,0,121,123,3,4,2,0,122,121,1,0,0,0,122,123,
  	1,0,0,0,123,124,1,0,0,0,124,125,5,50,0,0,125,128,3,60,30,0,126,127,5,
  	55,0,0,127,129,3,60,30,0,128,126,1,0,0,0,129,130,1,0,0,0,130,128,1,0,
  	0,0,130,131,1,0,0,0,131,132,1,0,0,0,132,133,5,51,0,0,133,168,1,0,0,0,
  	134,135,5,75,0,0,135,137,5,94,0,0,136,138,3,4,2,0,137,136,1,0,0,0,137,
  	138,1,0,0,0,138,139,1,0,0,0,139,143,5,50,0,0,140,142,3,2,1,0,141,140,
  	1,0,0,0,142,145,1,0,0,0,143,141,1,0,0,0,143,144,1,0,0,0,144,146,1,0,0,
  	0,145,143,1,0,0,0,146,168,5,51,0,0,147,148,5,72,0,0,148,150,5,94,0,0,
  	149,151,3,4,2,0,150,149,1,0,0,0,150,151,1,0,0,0,151,152,1,0,0,0,152,153,
  	5,2,0,0,153,154,5,94,0,0,154,155,5,53,0,0,155,157,3,54,27,0,156,158,5,
  	3,0,0,157,156,1,0,0,0,157,158,1,0,0,0,158,159,1,0,0,0,159,160,3,26,13,
  	0,160,168,1,0,0,0,161,162,5,73,0,0,162,164,5,94,0,0,163,165,3,4,2,0,164,
  	163,1,0,0,0,164,165,1,0,0,0,165,166,1,0,0,0,166,168,3,24,12,0,167,119,
  	1,0,0,0,167,134,1,0,0,0,167,147,1,0,0,0,167,161,1,0,0,0,168,11,1,0,0,
  	0,169,170,5,81,0,0,170,171,5,73,0,0,171,172,5,94,0,0,172,178,5,46,0,0,
  	173,175,3,38,19,0,174,176,5,25,0,0,175,174,1,0,0,0,175,176,1,0,0,0,176,
  	179,1,0,0,0,177,179,5,56,0,0,178,173,1,0,0,0,178,177,1,0,0,0,179,180,
  	1,0,0,0,180,183,5,47,0,0,181,182,5,45,0,0,182,184,3,60,30,0,183,181,1,
  	0,0,0,183,184,1,0,0,0,184,185,1,0,0,0,185,186,5,52,0,0,186,13,1,0,0,0,
  	187,189,5,94,0,0,188,190,3,8,4,0,189,188,1,0,0,0,189,190,1,0,0,0,190,
  	15,1,0,0,0,191,196,3,14,7,0,192,193,5,2,0,0,193,195,3,14,7,0,194,192,
  	1,0,0,0,195,198,1,0,0,0,196,194,1,0,0,0,196,197,1,0,0,0,197,17,1,0,0,
  	0,198,196,1,0,0,0,199,200,5,87,0,0,200,203,3,16,8,0,201,202,5,4,0,0,202,
  	204,5,94,0,0,203,201,1,0,0,0,203,204,1,0,0,0,204,206,1,0,0,0,205,207,
  	5,52,0,0,206,205,1,0,0,0,206,207,1,0,0,0,207,19,1,0,0,0,208,217,5,46,
  	0,0,209,214,3,22,11,0,210,211,5,55,0,0,211,213,3,22,11,0,212,210,1,0,
  	0,0,213,216,1,0,0,0,214,212,1,0,0,0,214,215,1,0,0,0,215,218,1,0,0,0,216,
  	214,1,0,0,0,217,209,1,0,0,0,217,218,1,0,0,0,218,219,1,0,0,0,219,220,5,
  	47,0,0,220,21,1,0,0,0,221,222,6,11,-1,0,222,223,5,46,0,0,223,224,3,22,
  	11,0,224,225,5,47,0,0,225,296,1,0,0,0,226,236,5,48,0,0,227,228,3,22,11,
  	0,228,229,5,55,0,0,229,231,1,0,0,0,230,227,1,0,0,0,231,234,1,0,0,0,232,
  	230,1,0,0,0,232,233,1,0,0,0,233,235,1,0,0,0,234,232,1,0,0,0,235,237,3,
  	22,11,0,236,232,1,0,0,0,236,237,1,0,0,0,237,238,1,0,0,0,238,296,5,49,
  	0,0,239,296,5,94,0,0,240,296,3,16,8,0,241,242,7,0,0,0,242,296,3,22,11,
  	22,243,244,3,16,8,0,244,245,5,6,0,0,245,254,5,46,0,0,246,251,3,22,11,
  	0,247,248,5,55,0,0,248,250,3,22,11,0,249,247,1,0,0,0,250,253,1,0,0,0,
  	251,249,1,0,0,0,251,252,1,0,0,0,252,255,1,0,0,0,253,251,1,0,0,0,254,246,
  	1,0,0,0,254,255,1,0,0,0,255,256,1,0,0,0,256,257,5,47,0,0,257,296,1,0,
  	0,0,258,259,5,29,0,0,259,296,3,22,11,12,260,261,5,69,0,0,261,262,5,33,
  	0,0,262,263,3,60,30,0,263,264,5,36,0,0,264,265,5,6,0,0,265,266,5,46,0,
  	0,266,267,3,22,11,0,267,268,5,47,0,0,268,296,1,0,0,0,269,296,3,64,32,
  	0,270,296,3,62,31,0,271,296,5,93,0,0,272,296,3,24,12,0,273,274,5,94,0,
  	0,274,275,5,7,0,0,275,276,5,46,0,0,276,296,5,47,0,0,277,278,5,94,0,0,
  	278,279,5,8,0,0,279,280,5,46,0,0,280,296,5,47,0,0,281,282,5,85,0,0,282,
  	296,3,22,11,4,283,284,5,86,0,0,284,285,5,46,0,0,285,286,3,22,11,0,286,
  	287,5,47,0,0,287,296,1,0,0,0,288,289,5,86,0,0,289,296,3,22,11,2,290,291,
  	5,9,0,0,291,292,5,46,0,0,292,293,3,22,11,0,293,294,5,47,0,0,294,296,1,
  	0,0,0,295,221,1,0,0,0,295,226,1,0,0,0,295,239,1,0,0,0,295,240,1,0,0,0,
  	295,241,1,0,0,0,295,243,1,0,0,0,295,258,1,0,0,0,295,260,1,0,0,0,295,269,
  	1,0,0,0,295,270,1,0,0,0,295,271,1,0,0,0,295,272,1,0,0,0,295,273,1,0,0,
  	0,295,277,1,0,0,0,295,281,1,0,0,0,295,283,1,0,0,0,295,288,1,0,0,0,295,
  	290,1,0,0,0,296,346,1,0,0,0,297,298,10,21,0,0,298,299,7,1,0,0,299,345,
  	3,22,11,22,300,301,10,20,0,0,301,302,7,2,0,0,302,345,3,22,11,21,303,304,
  	10,19,0,0,304,305,3,50,25,0,305,306,3,22,11,20,306,345,1,0,0,0,307,308,
  	10,18,0,0,308,309,7,3,0,0,309,345,3,22,11,19,310,311,10,17,0,0,311,312,
  	7,4,0,0,312,345,3,22,11,18,313,314,10,16,0,0,314,315,7,5,0,0,315,345,
  	3,22,11,16,316,317,10,28,0,0,317,345,3,20,10,0,318,319,10,27,0,0,319,
  	320,5,48,0,0,320,321,3,22,11,0,321,322,5,49,0,0,322,345,1,0,0,0,323,326,
  	10,24,0,0,324,325,5,5,0,0,325,327,5,94,0,0,326,324,1,0,0,0,327,328,1,
  	0,0,0,328,326,1,0,0,0,328,329,1,0,0,0,329,345,1,0,0,0,330,333,10,15,0,
  	0,331,332,5,42,0,0,332,334,3,22,11,0,333,331,1,0,0,0,334,335,1,0,0,0,
  	335,333,1,0,0,0,335,336,1,0,0,0,336,345,1,0,0,0,337,340,10,14,0,0,338,
  	339,5,43,0,0,339,341,3,22,11,0,340,338,1,0,0,0,341,342,1,0,0,0,342,340,
  	1,0,0,0,342,343,1,0,0,0,343,345,1,0,0,0,344,297,1,0,0,0,344,300,1,0,0,
  	0,344,303,1,0,0,0,344,307,1,0,0,0,344,310,1,0,0,0,344,313,1,0,0,0,344,
  	316,1,0,0,0,344,318,1,0,0,0,344,323,1,0,0,0,344,330,1,0,0,0,344,337,1,
  	0,0,0,345,348,1,0,0,0,346,344,1,0,0,0,346,347,1,0,0,0,347,23,1,0,0,0,
  	348,346,1,0,0,0,349,350,5,46,0,0,350,351,3,38,19,0,351,354,5,47,0,0,352,
  	353,5,45,0,0,353,355,3,60,30,0,354,352,1,0,0,0,354,355,1,0,0,0,355,356,
  	1,0,0,0,356,357,3,26,13,0,357,25,1,0,0,0,358,362,5,50,0,0,359,361,3,44,
  	22,0,360,359,1,0,0,0,361,364,1,0,0,0,362,360,1,0,0,0,362,363,1,0,0,0,
  	363,365,1,0,0,0,364,362,1,0,0,0,365,366,5,51,0,0,366,27,1,0,0,0,367,368,
  	5,46,0,0,368,369,3,22,11,0,369,370,5,47,0,0,370,373,1,0,0,0,371,373,3,
  	22,11,0,372,367,1,0,0,0,372,371,1,0,0,0,373,29,1,0,0,0,374,375,3,22,11,
  	0,375,376,5,53,0,0,376,377,3,44,22,0,377,31,1,0,0,0,378,379,3,60,30,0,
  	379,380,5,94,0,0,380,381,5,10,0,0,381,382,3,44,22,0,382,33,1,0,0,0,383,
  	386,5,94,0,0,384,386,3,54,27,0,385,383,1,0,0,0,385,384,1,0,0,0,386,387,
  	1,0,0,0,387,388,5,10,0,0,388,389,3,44,22,0,389,35,1,0,0,0,390,391,5,77,
  	0,0,391,392,5,10,0,0,392,393,3,44,22,0,393,37,1,0,0,0,394,399,3,40,20,
  	0,395,396,5,55,0,0,396,398,3,40,20,0,397,395,1,0,0,0,398,401,1,0,0,0,
  	399,397,1,0,0,0,399,400,1,0,0,0,400,403,1,0,0,0,401,399,1,0,0,0,402,394,
  	1,0,0,0,402,403,1,0,0,0,403,39,1,0,0,0,404,405,3,60,30,0,405,406,5,94,
  	0,0,406,41,1,0,0,0,407,412,5,94,0,0,408,409,5,55,0,0,409,411,5,94,0,0,
  	410,408,1,0,0,0,411,414,1,0,0,0,412,410,1,0,0,0,412,413,1,0,0,0,413,417,
  	1,0,0,0,414,412,1,0,0,0,415,416,5,26,0,0,416,418,3,22,11,0,417,415,1,
  	0,0,0,417,418,1,0,0,0,418,43,1,0,0,0,419,639,3,10,5,0,420,422,3,48,24,
  	0,421,423,5,52,0,0,422,421,1,0,0,0,422,423,1,0,0,0,423,639,1,0,0,0,424,
  	426,3,46,23,0,425,427,5,52,0,0,426,425,1,0,0,0,426,427,1,0,0,0,427,639,
  	1,0,0,0,428,429,5,76,0,0,429,430,3,28,14,0,430,433,3,26,13,0,431,432,
  	5,77,0,0,432,434,3,26,13,0,433,431,1,0,0,0,433,434,1,0,0,0,434,438,1,
  	0,0,0,435,437,3,44,22,0,436,435,1,0,0,0,437,440,1,0,0,0,438,436,1,0,0,
  	0,438,439,1,0,0,0,439,639,1,0,0,0,440,438,1,0,0,0,441,442,5,80,0,0,442,
  	446,5,50,0,0,443,445,3,30,15,0,444,443,1,0,0,0,445,448,1,0,0,0,446,444,
  	1,0,0,0,446,447,1,0,0,0,447,449,1,0,0,0,448,446,1,0,0,0,449,453,5,51,
  	0,0,450,452,3,44,22,0,451,450,1,0,0,0,452,455,1,0,0,0,453,451,1,0,0,0,
  	453,454,1,0,0,0,454,639,1,0,0,0,455,453,1,0,0,0,456,457,5,82,0,0,457,
  	458,3,28,14,0,458,462,5,50,0,0,459,461,3,32,16,0,460,459,1,0,0,0,461,
  	464,1,0,0,0,462,460,1,0,0,0,462,463,1,0,0,0,463,465,1,0,0,0,464,462,1,
  	0,0,0,465,469,5,51,0,0,466,468,3,44,22,0,467,466,1,0,0,0,468,471,1,0,
  	0,0,469,467,1,0,0,0,469,470,1,0,0,0,470,639,1,0,0,0,471,469,1,0,0,0,472,
  	473,5,82,0,0,473,478,3,28,14,0,474,475,5,41,0,0,475,477,3,32,16,0,476,
  	474,1,0,0,0,477,480,1,0,0,0,478,476,1,0,0,0,478,479,1,0,0,0,479,484,1,
  	0,0,0,480,478,1,0,0,0,481,483,3,44,22,0,482,481,1,0,0,0,483,486,1,0,0,
  	0,484,482,1,0,0,0,484,485,1,0,0,0,485,639,1,0,0,0,486,484,1,0,0,0,487,
  	489,5,79,0,0,488,490,3,22,11,0,489,488,1,0,0,0,489,490,1,0,0,0,490,491,
  	1,0,0,0,491,639,5,52,0,0,492,639,5,84,0,0,493,639,5,11,0,0,494,639,3,
  	26,13,0,495,496,5,94,0,0,496,497,5,12,0,0,497,498,5,46,0,0,498,499,3,
  	22,11,0,499,501,5,47,0,0,500,502,5,52,0,0,501,500,1,0,0,0,501,502,1,0,
  	0,0,502,639,1,0,0,0,503,504,5,78,0,0,504,505,3,28,14,0,505,506,3,26,13,
  	0,506,639,1,0,0,0,507,508,5,13,0,0,508,511,5,46,0,0,509,512,3,48,24,0,
  	510,512,3,46,23,0,511,509,1,0,0,0,511,510,1,0,0,0,512,513,1,0,0,0,513,
  	514,5,52,0,0,514,515,3,28,14,0,515,516,5,52,0,0,516,517,3,44,22,0,517,
  	518,5,47,0,0,518,519,3,26,13,0,519,639,1,0,0,0,520,521,5,94,0,0,521,522,
  	5,14,0,0,522,523,5,46,0,0,523,525,3,34,17,0,524,526,3,34,17,0,525,524,
  	1,0,0,0,526,527,1,0,0,0,527,525,1,0,0,0,527,528,1,0,0,0,528,530,1,0,0,
  	0,529,531,3,36,18,0,530,529,1,0,0,0,530,531,1,0,0,0,531,532,1,0,0,0,532,
  	536,5,47,0,0,533,535,3,44,22,0,534,533,1,0,0,0,535,538,1,0,0,0,536,534,
  	1,0,0,0,536,537,1,0,0,0,537,639,1,0,0,0,538,536,1,0,0,0,539,540,5,15,
  	0,0,540,543,5,94,0,0,541,542,5,41,0,0,542,544,3,34,17,0,543,541,1,0,0,
  	0,544,545,1,0,0,0,545,543,1,0,0,0,545,546,1,0,0,0,546,551,1,0,0,0,547,
  	549,5,41,0,0,548,550,3,36,18,0,549,548,1,0,0,0,549,550,1,0,0,0,550,552,
  	1,0,0,0,551,547,1,0,0,0,551,552,1,0,0,0,552,556,1,0,0,0,553,555,3,44,
  	22,0,554,553,1,0,0,0,555,558,1,0,0,0,556,554,1,0,0,0,556,557,1,0,0,0,
  	557,639,1,0,0,0,558,556,1,0,0,0,559,560,5,94,0,0,560,563,5,48,0,0,561,
  	564,5,94,0,0,562,564,3,54,27,0,563,561,1,0,0,0,563,562,1,0,0,0,564,565,
  	1,0,0,0,565,567,5,49,0,0,566,568,5,52,0,0,567,566,1,0,0,0,567,568,1,0,
  	0,0,568,639,1,0,0,0,569,570,5,16,0,0,570,571,5,46,0,0,571,572,5,94,0,
  	0,572,574,5,47,0,0,573,575,5,52,0,0,574,573,1,0,0,0,574,575,1,0,0,0,575,
  	639,1,0,0,0,576,577,5,17,0,0,577,578,5,46,0,0,578,579,5,94,0,0,579,581,
  	5,47,0,0,580,582,5,52,0,0,581,580,1,0,0,0,581,582,1,0,0,0,582,639,1,0,
  	0,0,583,584,5,18,0,0,584,585,5,46,0,0,585,586,5,94,0,0,586,588,5,47,0,
  	0,587,589,5,52,0,0,588,587,1,0,0,0,588,589,1,0,0,0,589,639,1,0,0,0,590,
  	591,5,19,0,0,591,592,5,46,0,0,592,593,5,94,0,0,593,594,5,47,0,0,594,639,
  	3,26,13,0,595,596,5,20,0,0,596,597,5,46,0,0,597,598,5,94,0,0,598,599,
  	5,55,0,0,599,600,3,22,11,0,600,601,5,47,0,0,601,602,3,26,13,0,602,639,
  	1,0,0,0,603,604,5,21,0,0,604,605,5,46,0,0,605,606,5,94,0,0,606,607,5,
  	55,0,0,607,608,3,22,11,0,608,609,5,47,0,0,609,612,3,26,13,0,610,611,5,
  	77,0,0,611,613,3,26,13,0,612,610,1,0,0,0,612,613,1,0,0,0,613,617,1,0,
  	0,0,614,616,3,44,22,0,615,614,1,0,0,0,616,619,1,0,0,0,617,615,1,0,0,0,
  	617,618,1,0,0,0,618,639,1,0,0,0,619,617,1,0,0,0,620,621,5,22,0,0,621,
  	622,5,46,0,0,622,623,5,94,0,0,623,625,5,47,0,0,624,626,5,52,0,0,625,624,
  	1,0,0,0,625,626,1,0,0,0,626,639,1,0,0,0,627,628,5,23,0,0,628,629,5,46,
  	0,0,629,630,5,94,0,0,630,632,5,47,0,0,631,633,5,52,0,0,632,631,1,0,0,
  	0,632,633,1,0,0,0,633,639,1,0,0,0,634,636,3,22,11,0,635,637,5,52,0,0,
  	636,635,1,0,0,0,636,637,1,0,0,0,637,639,1,0,0,0,638,419,1,0,0,0,638,420,
  	1,0,0,0,638,424,1,0,0,0,638,428,1,0,0,0,638,441,1,0,0,0,638,456,1,0,0,
  	0,638,472,1,0,0,0,638,487,1,0,0,0,638,492,1,0,0,0,638,493,1,0,0,0,638,
  	494,1,0,0,0,638,495,1,0,0,0,638,503,1,0,0,0,638,507,1,0,0,0,638,520,1,
  	0,0,0,638,539,1,0,0,0,638,559,1,0,0,0,638,569,1,0,0,0,638,576,1,0,0,0,
  	638,583,1,0,0,0,638,590,1,0,0,0,638,595,1,0,0,0,638,603,1,0,0,0,638,620,
  	1,0,0,0,638,627,1,0,0,0,638,634,1,0,0,0,639,45,1,0,0,0,640,641,3,22,11,
  	0,641,642,5,26,0,0,642,643,3,22,11,0,643,47,1,0,0,0,644,645,3,52,26,0,
  	645,650,3,42,21,0,646,647,5,55,0,0,647,649,3,42,21,0,648,646,1,0,0,0,
  	649,652,1,0,0,0,650,648,1,0,0,0,650,651,1,0,0,0,651,49,1,0,0,0,652,650,
  	1,0,0,0,653,654,5,36,0,0,654,655,5,36,0,0,655,661,5,36,0,0,656,657,5,
  	36,0,0,657,661,5,36,0,0,658,659,5,33,0,0,659,661,5,33,0,0,660,653,1,0,
  	0,0,660,656,1,0,0,0,660,658,1,0,0,0,661,51,1,0,0,0,662,665,3,60,30,0,
  	663,665,5,68,0,0,664,662,1,0,0,0,664,663,1,0,0,0,665,53,1,0,0,0,666,671,
  	3,56,28,0,667,668,5,52,0,0,668,670,3,56,28,0,669,667,1,0,0,0,670,673,
  	1,0,0,0,671,672,1,0,0,0,671,669,1,0,0,0,672,687,1,0,0,0,673,671,1,0,0,
  	0,674,675,5,46,0,0,675,680,3,56,28,0,676,677,5,52,0,0,677,679,3,56,28,
  	0,678,676,1,0,0,0,679,682,1,0,0,0,680,681,1,0,0,0,680,678,1,0,0,0,681,
  	683,1,0,0,0,682,680,1,0,0,0,683,684,5,47,0,0,684,687,1,0,0,0,685,687,
  	3,56,28,0,686,666,1,0,0,0,686,674,1,0,0,0,686,685,1,0,0,0,687,55,1,0,
  	0,0,688,689,5,32,0,0,689,724,3,60,30,0,690,691,5,27,0,0,691,724,3,60,
  	30,0,692,693,5,24,0,0,693,724,3,54,27,0,694,695,5,28,0,0,695,724,3,54,
  	27,0,696,697,5,88,0,0,697,698,5,33,0,0,698,701,3,58,29,0,699,700,5,55,
  	0,0,700,702,3,58,29,0,701,699,1,0,0,0,702,703,1,0,0,0,703,701,1,0,0,0,
  	703,704,1,0,0,0,704,705,1,0,0,0,705,706,5,36,0,0,706,724,1,0,0,0,707,
  	708,5,89,0,0,708,709,5,33,0,0,709,712,3,58,29,0,710,711,5,55,0,0,711,
  	713,3,58,29,0,712,710,1,0,0,0,713,714,1,0,0,0,714,712,1,0,0,0,714,715,
  	1,0,0,0,715,716,1,0,0,0,716,717,5,36,0,0,717,724,1,0,0,0,718,719,5,90,
  	0,0,719,720,5,33,0,0,720,721,3,54,27,0,721,722,5,36,0,0,722,724,1,0,0,
  	0,723,688,1,0,0,0,723,690,1,0,0,0,723,692,1,0,0,0,723,694,1,0,0,0,723,
  	696,1,0,0,0,723,707,1,0,0,0,723,718,1,0,0,0,724,57,1,0,0,0,725,730,3,
  	54,27,0,726,727,5,94,0,0,727,728,5,53,0,0,728,730,3,54,27,0,729,725,1,
  	0,0,0,729,726,1,0,0,0,730,59,1,0,0,0,731,732,6,30,-1,0,732,816,7,6,0,
  	0,733,742,5,46,0,0,734,739,3,60,30,0,735,736,5,55,0,0,736,738,3,60,30,
  	0,737,735,1,0,0,0,738,741,1,0,0,0,739,737,1,0,0,0,739,740,1,0,0,0,740,
  	743,1,0,0,0,741,739,1,0,0,0,742,734,1,0,0,0,742,743,1,0,0,0,743,744,1,
  	0,0,0,744,745,5,47,0,0,745,749,5,45,0,0,746,750,3,60,30,0,747,748,5,46,
  	0,0,748,750,5,47,0,0,749,746,1,0,0,0,749,747,1,0,0,0,750,816,1,0,0,0,
  	751,760,5,46,0,0,752,757,3,60,30,0,753,754,5,55,0,0,754,756,3,60,30,0,
  	755,753,1,0,0,0,756,759,1,0,0,0,757,755,1,0,0,0,757,758,1,0,0,0,758,761,
  	1,0,0,0,759,757,1,0,0,0,760,752,1,0,0,0,760,761,1,0,0,0,761,762,1,0,0,
  	0,762,766,5,45,0,0,763,767,3,60,30,0,764,765,5,46,0,0,765,767,5,47,0,
  	0,766,763,1,0,0,0,766,764,1,0,0,0,767,768,1,0,0,0,768,816,5,47,0,0,769,
  	770,5,46,0,0,770,779,5,46,0,0,771,776,3,60,30,0,772,773,5,55,0,0,773,
  	775,3,60,30,0,774,772,1,0,0,0,775,778,1,0,0,0,776,774,1,0,0,0,776,777,
  	1,0,0,0,777,780,1,0,0,0,778,776,1,0,0,0,779,771,1,0,0,0,779,780,1,0,0,
  	0,780,781,1,0,0,0,781,782,5,47,0,0,782,786,5,45,0,0,783,787,3,60,30,0,
  	784,785,5,46,0,0,785,787,5,47,0,0,786,783,1,0,0,0,786,784,1,0,0,0,787,
  	788,1,0,0,0,788,816,5,47,0,0,789,790,5,46,0,0,790,793,3,60,30,0,791,792,
  	5,32,0,0,792,794,3,60,30,0,793,791,1,0,0,0,794,795,1,0,0,0,795,793,1,
  	0,0,0,795,796,1,0,0,0,796,797,1,0,0,0,797,798,5,47,0,0,798,816,1,0,0,
  	0,799,800,5,71,0,0,800,801,5,33,0,0,801,802,3,54,27,0,802,803,5,36,0,
  	0,803,816,1,0,0,0,804,805,5,70,0,0,805,806,5,33,0,0,806,807,3,54,27,0,
  	807,808,5,36,0,0,808,816,1,0,0,0,809,810,5,69,0,0,810,811,5,33,0,0,811,
  	812,3,60,30,0,812,813,5,36,0,0,813,816,1,0,0,0,814,816,3,16,8,0,815,731,
  	1,0,0,0,815,733,1,0,0,0,815,751,1,0,0,0,815,769,1,0,0,0,815,789,1,0,0,
  	0,815,799,1,0,0,0,815,804,1,0,0,0,815,809,1,0,0,0,815,814,1,0,0,0,816,
  	838,1,0,0,0,817,822,10,10,0,0,818,819,5,55,0,0,819,821,3,60,30,0,820,
  	818,1,0,0,0,821,824,1,0,0,0,822,820,1,0,0,0,822,823,1,0,0,0,823,825,1,
  	0,0,0,824,822,1,0,0,0,825,826,5,45,0,0,826,837,3,60,30,11,827,828,10,
  	13,0,0,828,829,5,48,0,0,829,830,5,57,0,0,830,837,5,49,0,0,831,832,10,
  	12,0,0,832,833,5,48,0,0,833,837,5,49,0,0,834,835,10,2,0,0,835,837,3,8,
  	4,0,836,817,1,0,0,0,836,827,1,0,0,0,836,831,1,0,0,0,836,834,1,0,0,0,837,
  	840,1,0,0,0,838,836,1,0,0,0,838,839,1,0,0,0,839,61,1,0,0,0,840,838,1,
  	0,0,0,841,843,7,7,0,0,842,844,7,8,0,0,843,842,1,0,0,0,843,844,1,0,0,0,
  	844,63,1,0,0,0,845,846,7,9,0,0,846,65,1,0,0,0,98,69,71,87,99,102,106,
  	114,122,130,137,143,150,157,164,167,175,178,183,189,196,203,206,214,217,
  	232,236,251,254,295,328,335,342,344,346,354,362,372,385,399,402,412,417,
  	422,426,433,438,446,453,462,469,478,484,489,501,511,527,530,536,545,549,
  	551,556,563,567,574,581,588,612,617,625,632,636,638,650,660,664,671,680,
  	686,703,714,723,729,739,742,749,757,760,766,776,779,786,795,815,822,836,
  	838,843
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
    setState(71);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 72) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 72)) & ((1ULL << (BismuthParser::PROG - 72))
      | (1ULL << (BismuthParser::FUNC - 72))
      | (1ULL << (BismuthParser::ENUM - 72))
      | (1ULL << (BismuthParser::STRUCT - 72))
      | (1ULL << (BismuthParser::EXTERN - 72))
      | (1ULL << (BismuthParser::IMPORT - 72)))) != 0)) {
      setState(69);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case BismuthParser::IMPORT: {
          setState(66);
          antlrcpp::downCast<CompilationUnitContext *>(_localctx)->importStatementContext = importStatement();
          antlrcpp::downCast<CompilationUnitContext *>(_localctx)->imports.push_back(antlrcpp::downCast<CompilationUnitContext *>(_localctx)->importStatementContext);
          break;
        }

        case BismuthParser::EXTERN: {
          setState(67);
          antlrcpp::downCast<CompilationUnitContext *>(_localctx)->externStatementContext = externStatement();
          antlrcpp::downCast<CompilationUnitContext *>(_localctx)->externs.push_back(antlrcpp::downCast<CompilationUnitContext *>(_localctx)->externStatementContext);
          break;
        }

        case BismuthParser::PROG:
        case BismuthParser::FUNC:
        case BismuthParser::ENUM:
        case BismuthParser::STRUCT: {
          setState(68);
          antlrcpp::downCast<CompilationUnitContext *>(_localctx)->defineTypeContext = defineType();
          antlrcpp::downCast<CompilationUnitContext *>(_localctx)->defs.push_back(antlrcpp::downCast<CompilationUnitContext *>(_localctx)->defineTypeContext);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(73);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(74);
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
    setState(76);
    antlrcpp::downCast<StructCaseContext *>(_localctx)->ty = type(0);
    setState(77);
    antlrcpp::downCast<StructCaseContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
    setState(79);
    match(BismuthParser::SEMICOLON);
   
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
  enterRule(_localctx, 4, BismuthParser::RuleGenericTemplate);
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
    setState(81);
    match(BismuthParser::LESS);
    setState(82);
    antlrcpp::downCast<GenericTemplateContext *>(_localctx)->genericEntryContext = genericEntry();
    antlrcpp::downCast<GenericTemplateContext *>(_localctx)->gen.push_back(antlrcpp::downCast<GenericTemplateContext *>(_localctx)->genericEntryContext);
    setState(87);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BismuthParser::COMMA) {
      setState(83);
      match(BismuthParser::COMMA);
      setState(84);
      antlrcpp::downCast<GenericTemplateContext *>(_localctx)->genericEntryContext = genericEntry();
      antlrcpp::downCast<GenericTemplateContext *>(_localctx)->gen.push_back(antlrcpp::downCast<GenericTemplateContext *>(_localctx)->genericEntryContext);
      setState(89);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(90);
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
  enterRule(_localctx, 6, BismuthParser::RuleGenericEntry);
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
    setState(106);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BismuthParser::VARIABLE: {
        _localctx = _tracker.createInstance<BismuthParser::GenericTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(92);
        antlrcpp::downCast<GenericTypeContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
        setState(102);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::COLON) {
          setState(93);
          match(BismuthParser::COLON);
          setState(94);
          antlrcpp::downCast<GenericTypeContext *>(_localctx)->typeContext = type(0);
          antlrcpp::downCast<GenericTypeContext *>(_localctx)->supTy.push_back(antlrcpp::downCast<GenericTypeContext *>(_localctx)->typeContext);
          setState(99);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
          while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
              setState(95);
              match(BismuthParser::COMMA);
              setState(96);
              antlrcpp::downCast<GenericTypeContext *>(_localctx)->typeContext = type(0);
              antlrcpp::downCast<GenericTypeContext *>(_localctx)->supTy.push_back(antlrcpp::downCast<GenericTypeContext *>(_localctx)->typeContext); 
            }
            setState(101);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
          }
        }
        break;
      }

      case BismuthParser::T__0: {
        _localctx = _tracker.createInstance<BismuthParser::GenericSessionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(104);
        match(BismuthParser::T__0);
        setState(105);
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
  enterRule(_localctx, 8, BismuthParser::RuleGenericSpecifier);
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
    setState(108);
    match(BismuthParser::LESS);
    setState(109);
    antlrcpp::downCast<GenericSpecifierContext *>(_localctx)->typeContext = type(0);
    antlrcpp::downCast<GenericSpecifierContext *>(_localctx)->subst.push_back(antlrcpp::downCast<GenericSpecifierContext *>(_localctx)->typeContext);
    setState(114);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BismuthParser::COMMA) {
      setState(110);
      match(BismuthParser::COMMA);
      setState(111);
      antlrcpp::downCast<GenericSpecifierContext *>(_localctx)->typeContext = type(0);
      antlrcpp::downCast<GenericSpecifierContext *>(_localctx)->subst.push_back(antlrcpp::downCast<GenericSpecifierContext *>(_localctx)->typeContext);
      setState(116);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(117);
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
  enterRule(_localctx, 10, BismuthParser::RuleDefineType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(167);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BismuthParser::ENUM: {
        _localctx = _tracker.createInstance<BismuthParser::DefineEnumContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(119);
        match(BismuthParser::ENUM);
        setState(120);
        antlrcpp::downCast<DefineEnumContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
        setState(122);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::LESS) {
          setState(121);
          genericTemplate();
        }
        setState(124);
        match(BismuthParser::LSQB);
        setState(125);
        antlrcpp::downCast<DefineEnumContext *>(_localctx)->typeContext = type(0);
        antlrcpp::downCast<DefineEnumContext *>(_localctx)->cases.push_back(antlrcpp::downCast<DefineEnumContext *>(_localctx)->typeContext);
        setState(128); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(126);
          match(BismuthParser::COMMA);
          setState(127);
          antlrcpp::downCast<DefineEnumContext *>(_localctx)->typeContext = type(0);
          antlrcpp::downCast<DefineEnumContext *>(_localctx)->cases.push_back(antlrcpp::downCast<DefineEnumContext *>(_localctx)->typeContext);
          setState(130); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == BismuthParser::COMMA);
        setState(132);
        match(BismuthParser::RSQB);
        break;
      }

      case BismuthParser::STRUCT: {
        _localctx = _tracker.createInstance<BismuthParser::DefineStructContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(134);
        match(BismuthParser::STRUCT);
        setState(135);
        antlrcpp::downCast<DefineStructContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
        setState(137);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::LESS) {
          setState(136);
          genericTemplate();
        }
        setState(139);
        match(BismuthParser::LSQB);
        setState(143);
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
          setState(140);
          antlrcpp::downCast<DefineStructContext *>(_localctx)->structCaseContext = structCase();
          antlrcpp::downCast<DefineStructContext *>(_localctx)->cases.push_back(antlrcpp::downCast<DefineStructContext *>(_localctx)->structCaseContext);
          setState(145);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(146);
        match(BismuthParser::RSQB);
        break;
      }

      case BismuthParser::PROG: {
        _localctx = _tracker.createInstance<BismuthParser::DefineProgramContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(147);
        match(BismuthParser::PROG);
        setState(148);
        antlrcpp::downCast<DefineProgramContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
        setState(150);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::LESS) {
          setState(149);
          genericTemplate();
        }
        setState(152);
        match(BismuthParser::T__1);
        setState(153);
        antlrcpp::downCast<DefineProgramContext *>(_localctx)->channelName = match(BismuthParser::VARIABLE);
        setState(154);
        match(BismuthParser::COLON);
        setState(155);
        antlrcpp::downCast<DefineProgramContext *>(_localctx)->proto = protocol();
        setState(157);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::T__2) {
          setState(156);
          match(BismuthParser::T__2);
        }
        setState(159);
        block();
        break;
      }

      case BismuthParser::FUNC: {
        _localctx = _tracker.createInstance<BismuthParser::DefineFunctionContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(161);
        match(BismuthParser::FUNC);
        setState(162);
        antlrcpp::downCast<DefineFunctionContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
        setState(164);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::LESS) {
          setState(163);
          genericTemplate();
        }
        setState(166);
        antlrcpp::downCast<DefineFunctionContext *>(_localctx)->lam = lambdaConstExpr();
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
  enterRule(_localctx, 12, BismuthParser::RuleExternStatement);
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
    setState(169);
    match(BismuthParser::EXTERN);
    setState(170);
    match(BismuthParser::FUNC);
    setState(171);
    antlrcpp::downCast<ExternStatementContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
    setState(172);
    match(BismuthParser::LPAR);
    setState(178);
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
        setState(173);
        antlrcpp::downCast<ExternStatementContext *>(_localctx)->paramList = parameterList();
        setState(175);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::VariadicParam) {
          setState(174);
          antlrcpp::downCast<ExternStatementContext *>(_localctx)->variadic = match(BismuthParser::VariadicParam);
        }
        break;
      }

      case BismuthParser::ELLIPSIS: {
        setState(177);
        match(BismuthParser::ELLIPSIS);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(180);
    match(BismuthParser::RPAR);
    setState(183);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BismuthParser::MAPS_TO) {
      setState(181);
      match(BismuthParser::MAPS_TO);
      setState(182);
      antlrcpp::downCast<ExternStatementContext *>(_localctx)->ret = type(0);
    }
    setState(185);
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
  enterRule(_localctx, 14, BismuthParser::RulePathElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(187);
    antlrcpp::downCast<PathElementContext *>(_localctx)->id = match(BismuthParser::VARIABLE);
    setState(189);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      setState(188);
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
  enterRule(_localctx, 16, BismuthParser::RulePath);

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
    setState(191);
    antlrcpp::downCast<PathContext *>(_localctx)->pathElementContext = pathElement();
    antlrcpp::downCast<PathContext *>(_localctx)->eles.push_back(antlrcpp::downCast<PathContext *>(_localctx)->pathElementContext);
    setState(196);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(192);
        match(BismuthParser::T__1);
        setState(193);
        antlrcpp::downCast<PathContext *>(_localctx)->pathElementContext = pathElement();
        antlrcpp::downCast<PathContext *>(_localctx)->eles.push_back(antlrcpp::downCast<PathContext *>(_localctx)->pathElementContext); 
      }
      setState(198);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
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
  enterRule(_localctx, 18, BismuthParser::RuleImportStatement);
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
    setState(199);
    match(BismuthParser::IMPORT);
    setState(200);
    path();
    setState(203);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BismuthParser::T__3) {
      setState(201);
      match(BismuthParser::T__3);
      setState(202);
      antlrcpp::downCast<ImportStatementContext *>(_localctx)->alias = match(BismuthParser::VARIABLE);
    }
    setState(206);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BismuthParser::SEMICOLON) {
      setState(205);
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
  enterRule(_localctx, 20, BismuthParser::RuleInv_args);
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
    setState(208);
    match(BismuthParser::LPAR);
    setState(217);
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
      setState(209);
      antlrcpp::downCast<Inv_argsContext *>(_localctx)->expressionContext = expression(0);
      antlrcpp::downCast<Inv_argsContext *>(_localctx)->args.push_back(antlrcpp::downCast<Inv_argsContext *>(_localctx)->expressionContext);
      setState(214);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == BismuthParser::COMMA) {
        setState(210);
        match(BismuthParser::COMMA);
        setState(211);
        antlrcpp::downCast<Inv_argsContext *>(_localctx)->expressionContext = expression(0);
        antlrcpp::downCast<Inv_argsContext *>(_localctx)->args.push_back(antlrcpp::downCast<Inv_argsContext *>(_localctx)->expressionContext);
        setState(216);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(219);
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
  size_t startState = 22;
  enterRecursionRule(_localctx, 22, BismuthParser::RuleExpression, precedence);

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
    setState(295);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ParenExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(222);
      match(BismuthParser::LPAR);
      setState(223);
      antlrcpp::downCast<ParenExprContext *>(_localctx)->ex = expression(0);
      setState(224);
      match(BismuthParser::RPAR);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ArrayExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(226);
      match(BismuthParser::LBRC);
      setState(236);
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
        setState(232);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(227);
            antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->expressionContext = expression(0);
            antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->elements.push_back(antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->expressionContext);
            setState(228);
            match(BismuthParser::COMMA); 
          }
          setState(234);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
        }
        setState(235);
        antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->expressionContext = expression(0);
        antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->elements.push_back(antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->expressionContext);
      }
      setState(238);
      match(BismuthParser::RBRC);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<IdentifierExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(239);
      match(BismuthParser::VARIABLE);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PathExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(240);
      path();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(241);
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
      setState(242);
      antlrcpp::downCast<UnaryExprContext *>(_localctx)->ex = expression(22);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<InitProductContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(243);
      path();
      setState(244);
      match(BismuthParser::T__5);
      setState(245);
      match(BismuthParser::LPAR);
      setState(254);
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
        setState(246);
        antlrcpp::downCast<InitProductContext *>(_localctx)->expressionContext = expression(0);
        antlrcpp::downCast<InitProductContext *>(_localctx)->exprs.push_back(antlrcpp::downCast<InitProductContext *>(_localctx)->expressionContext);
        setState(251);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == BismuthParser::COMMA) {
          setState(247);
          match(BismuthParser::COMMA);
          setState(248);
          antlrcpp::downCast<InitProductContext *>(_localctx)->expressionContext = expression(0);
          antlrcpp::downCast<InitProductContext *>(_localctx)->exprs.push_back(antlrcpp::downCast<InitProductContext *>(_localctx)->expressionContext);
          setState(253);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(256);
      match(BismuthParser::RPAR);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<DerefContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(258);
      match(BismuthParser::MULTIPLY);
      setState(259);
      antlrcpp::downCast<DerefContext *>(_localctx)->expr = expression(12);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<InitBoxContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(260);
      match(BismuthParser::TYPE_BOX);
      setState(261);
      match(BismuthParser::LESS);
      setState(262);
      antlrcpp::downCast<InitBoxContext *>(_localctx)->ty = type(0);
      setState(263);
      match(BismuthParser::GREATER);
      setState(264);
      match(BismuthParser::T__5);
      setState(265);
      match(BismuthParser::LPAR);
      setState(266);
      antlrcpp::downCast<InitBoxContext *>(_localctx)->expr = expression(0);
      setState(267);
      match(BismuthParser::RPAR);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<BConstExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(269);
      booleanConst();
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<IConstExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(270);
      antlrcpp::downCast<IConstExprContext *>(_localctx)->i = integerValue();
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<SConstExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(271);
      antlrcpp::downCast<SConstExprContext *>(_localctx)->s = match(BismuthParser::STRING);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<LambdaExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(272);
      lambdaConstExpr();
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<AssignableRecvContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(273);
      antlrcpp::downCast<AssignableRecvContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(274);
      match(BismuthParser::T__6);
      setState(275);
      match(BismuthParser::LPAR);
      setState(276);
      match(BismuthParser::RPAR);
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<AssignableIsPresentContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(277);
      antlrcpp::downCast<AssignableIsPresentContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(278);
      match(BismuthParser::T__7);
      setState(279);
      match(BismuthParser::LPAR);
      setState(280);
      match(BismuthParser::RPAR);
      break;
    }

    case 15: {
      _localctx = _tracker.createInstance<AssignableExecContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(281);
      match(BismuthParser::EXEC);
      setState(282);
      antlrcpp::downCast<AssignableExecContext *>(_localctx)->prog = expression(4);
      break;
    }

    case 16: {
      _localctx = _tracker.createInstance<CopyExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(283);
      match(BismuthParser::COPY);
      setState(284);
      match(BismuthParser::LPAR);
      setState(285);
      antlrcpp::downCast<CopyExprContext *>(_localctx)->expr = expression(0);
      setState(286);
      match(BismuthParser::RPAR);
      break;
    }

    case 17: {
      _localctx = _tracker.createInstance<CopyExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(288);
      match(BismuthParser::COPY);
      setState(289);
      antlrcpp::downCast<CopyExprContext *>(_localctx)->expr = expression(2);
      break;
    }

    case 18: {
      _localctx = _tracker.createInstance<AsChannelExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(290);
      match(BismuthParser::T__8);
      setState(291);
      match(BismuthParser::LPAR);
      setState(292);
      antlrcpp::downCast<AsChannelExprContext *>(_localctx)->expr = expression(0);
      setState(293);
      match(BismuthParser::RPAR);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(346);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(344);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<BinaryArithExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(297);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(298);
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
          setState(299);
          antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->right = expression(22);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<BinaryArithExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(300);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(301);
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
          setState(302);
          antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->right = expression(21);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<BinaryArithExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(303);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(304);
          shiftOp();
          setState(305);
          antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->right = expression(20);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BinaryRelExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(307);

          if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
          setState(308);
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
          setState(309);
          antlrcpp::downCast<BinaryRelExprContext *>(_localctx)->right = expression(19);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BinaryArithExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(310);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(311);
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
          setState(312);
          antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->right = expression(18);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<EqExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(313);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(314);
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
          setState(315);
          antlrcpp::downCast<EqExprContext *>(_localctx)->right = expression(16);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<CallExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->expr = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(316);

          if (!(precpred(_ctx, 28))) throw FailedPredicateException(this, "precpred(_ctx, 28)");
          setState(317);
          inv_args();
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<ArrayAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->expr = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(318);

          if (!(precpred(_ctx, 27))) throw FailedPredicateException(this, "precpred(_ctx, 27)");
          setState(319);
          match(BismuthParser::LBRC);
          setState(320);
          antlrcpp::downCast<ArrayAccessContext *>(_localctx)->index = expression(0);
          setState(321);
          match(BismuthParser::RBRC);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<FieldAccessExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->expr = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(323);

          if (!(precpred(_ctx, 24))) throw FailedPredicateException(this, "precpred(_ctx, 24)");
          setState(326); 
          _errHandler->sync(this);
          alt = 1;
          do {
            switch (alt) {
              case 1: {
                    setState(324);
                    match(BismuthParser::T__4);
                    setState(325);
                    antlrcpp::downCast<FieldAccessExprContext *>(_localctx)->variableToken = match(BismuthParser::VARIABLE);
                    antlrcpp::downCast<FieldAccessExprContext *>(_localctx)->fields.push_back(antlrcpp::downCast<FieldAccessExprContext *>(_localctx)->variableToken);
                    break;
                  }

            default:
              throw NoViableAltException(this);
            }
            setState(328); 
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
          } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<LogAndExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->exprs.push_back(previousContext);
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(330);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(333); 
          _errHandler->sync(this);
          alt = 1;
          do {
            switch (alt) {
              case 1: {
                    setState(331);
                    match(BismuthParser::LOG_AND);
                    setState(332);
                    antlrcpp::downCast<LogAndExprContext *>(_localctx)->expressionContext = expression(0);
                    antlrcpp::downCast<LogAndExprContext *>(_localctx)->exprs.push_back(antlrcpp::downCast<LogAndExprContext *>(_localctx)->expressionContext);
                    break;
                  }

            default:
              throw NoViableAltException(this);
            }
            setState(335); 
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
          } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<LogOrExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->exprs.push_back(previousContext);
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(337);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(340); 
          _errHandler->sync(this);
          alt = 1;
          do {
            switch (alt) {
              case 1: {
                    setState(338);
                    match(BismuthParser::LOG_OR);
                    setState(339);
                    antlrcpp::downCast<LogOrExprContext *>(_localctx)->expressionContext = expression(0);
                    antlrcpp::downCast<LogOrExprContext *>(_localctx)->exprs.push_back(antlrcpp::downCast<LogOrExprContext *>(_localctx)->expressionContext);
                    break;
                  }

            default:
              throw NoViableAltException(this);
            }
            setState(342); 
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
          } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
          break;
        }

        default:
          break;
        } 
      }
      setState(348);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
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
  enterRule(_localctx, 24, BismuthParser::RuleLambdaConstExpr);
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
    setState(349);
    match(BismuthParser::LPAR);
    setState(350);
    parameterList();
    setState(351);
    match(BismuthParser::RPAR);
    setState(354);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BismuthParser::MAPS_TO) {
      setState(352);
      match(BismuthParser::MAPS_TO);
      setState(353);
      antlrcpp::downCast<LambdaConstExprContext *>(_localctx)->ret = type(0);
    }
    setState(356);
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
  enterRule(_localctx, 26, BismuthParser::RuleBlock);
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
    setState(358);
    match(BismuthParser::LSQB);
    setState(362);
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
      | (1ULL << (BismuthParser::FALSE - 64))
      | (1ULL << (BismuthParser::TRUE - 64))
      | (1ULL << (BismuthParser::STRING - 64))
      | (1ULL << (BismuthParser::VARIABLE - 64)))) != 0)) {
      setState(359);
      antlrcpp::downCast<BlockContext *>(_localctx)->statementContext = statement();
      antlrcpp::downCast<BlockContext *>(_localctx)->stmts.push_back(antlrcpp::downCast<BlockContext *>(_localctx)->statementContext);
      setState(364);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(365);
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
  enterRule(_localctx, 28, BismuthParser::RuleCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(372);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(367);
      match(BismuthParser::LPAR);
      setState(368);
      antlrcpp::downCast<ConditionContext *>(_localctx)->ex = expression(0);
      setState(369);
      match(BismuthParser::RPAR);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(371);
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
  enterRule(_localctx, 30, BismuthParser::RuleSelectAlternative);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(374);
    antlrcpp::downCast<SelectAlternativeContext *>(_localctx)->check = expression(0);
    setState(375);
    match(BismuthParser::COLON);
    setState(376);
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
  enterRule(_localctx, 32, BismuthParser::RuleMatchAlternative);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(378);
    antlrcpp::downCast<MatchAlternativeContext *>(_localctx)->check = type(0);
    setState(379);
    antlrcpp::downCast<MatchAlternativeContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
    setState(380);
    match(BismuthParser::T__9);
    setState(381);
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
  enterRule(_localctx, 34, BismuthParser::RuleProtoAlternative);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(385);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BismuthParser::VARIABLE: {
        setState(383);
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
        setState(384);
        antlrcpp::downCast<ProtoAlternativeContext *>(_localctx)->check = protocol();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(387);
    match(BismuthParser::T__9);
    setState(388);
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
  enterRule(_localctx, 36, BismuthParser::RuleProtoElse);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(390);
    match(BismuthParser::ELSE);
    setState(391);
    match(BismuthParser::T__9);
    setState(392);
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
  enterRule(_localctx, 38, BismuthParser::RuleParameterList);
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
    setState(402);
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
      setState(394);
      antlrcpp::downCast<ParameterListContext *>(_localctx)->parameterContext = parameter();
      antlrcpp::downCast<ParameterListContext *>(_localctx)->params.push_back(antlrcpp::downCast<ParameterListContext *>(_localctx)->parameterContext);
      setState(399);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == BismuthParser::COMMA) {
        setState(395);
        match(BismuthParser::COMMA);
        setState(396);
        antlrcpp::downCast<ParameterListContext *>(_localctx)->parameterContext = parameter();
        antlrcpp::downCast<ParameterListContext *>(_localctx)->params.push_back(antlrcpp::downCast<ParameterListContext *>(_localctx)->parameterContext);
        setState(401);
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
  enterRule(_localctx, 40, BismuthParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(404);
    antlrcpp::downCast<ParameterContext *>(_localctx)->ty = type(0);
    setState(405);
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
  enterRule(_localctx, 42, BismuthParser::RuleAssignment);
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
    setState(407);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->variableToken = match(BismuthParser::VARIABLE);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->v.push_back(antlrcpp::downCast<AssignmentContext *>(_localctx)->variableToken);
    setState(412);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(408);
        match(BismuthParser::COMMA);
        setState(409);
        antlrcpp::downCast<AssignmentContext *>(_localctx)->variableToken = match(BismuthParser::VARIABLE);
        antlrcpp::downCast<AssignmentContext *>(_localctx)->v.push_back(antlrcpp::downCast<AssignmentContext *>(_localctx)->variableToken); 
      }
      setState(414);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    }
    setState(417);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BismuthParser::ASSIGN) {
      setState(415);
      match(BismuthParser::ASSIGN);
      setState(416);
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
  enterRule(_localctx, 44, BismuthParser::RuleStatement);
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
    setState(638);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<BismuthParser::TypeDefContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(419);
      defineType();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<BismuthParser::VarDeclStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(420);
      variableDeclaration();
      setState(422);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(421);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<BismuthParser::AssignStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(424);
      assignmentStatement();
      setState(426);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(425);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<BismuthParser::ConditionalStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(428);
      match(BismuthParser::IF);
      setState(429);
      antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->check = condition();
      setState(430);
      antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->trueBlk = block();
      setState(433);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
      case 1: {
        setState(431);
        match(BismuthParser::ELSE);
        setState(432);
        antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->falseBlk = block();
        break;
      }

      default:
        break;
      }
      setState(438);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(435);
          antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->rest.push_back(antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->statementContext); 
        }
        setState(440);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
      }
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<BismuthParser::SelectStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(441);
      match(BismuthParser::SELECT);
      setState(442);
      match(BismuthParser::LSQB);
      setState(446);
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
        setState(443);
        antlrcpp::downCast<SelectStatementContext *>(_localctx)->selectAlternativeContext = selectAlternative();
        antlrcpp::downCast<SelectStatementContext *>(_localctx)->cases.push_back(antlrcpp::downCast<SelectStatementContext *>(_localctx)->selectAlternativeContext);
        setState(448);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(449);
      match(BismuthParser::RSQB);
      setState(453);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(450);
          antlrcpp::downCast<SelectStatementContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<SelectStatementContext *>(_localctx)->rest.push_back(antlrcpp::downCast<SelectStatementContext *>(_localctx)->statementContext); 
        }
        setState(455);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
      }
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<BismuthParser::MatchStatementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(456);
      match(BismuthParser::MATCH);
      setState(457);
      antlrcpp::downCast<MatchStatementContext *>(_localctx)->check = condition();
      setState(458);
      match(BismuthParser::LSQB);
      setState(462);
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
        setState(459);
        matchAlternative();
        setState(464);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(465);
      match(BismuthParser::RSQB);
      setState(469);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(466);
          antlrcpp::downCast<MatchStatementContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<MatchStatementContext *>(_localctx)->rest.push_back(antlrcpp::downCast<MatchStatementContext *>(_localctx)->statementContext); 
        }
        setState(471);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
      }
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<BismuthParser::MatchStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(472);
      match(BismuthParser::MATCH);
      setState(473);
      antlrcpp::downCast<MatchStatementContext *>(_localctx)->check = condition();
      setState(478);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(474);
          match(BismuthParser::BIT_OR);
          setState(475);
          matchAlternative(); 
        }
        setState(480);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
      }
      setState(484);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(481);
          antlrcpp::downCast<MatchStatementContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<MatchStatementContext *>(_localctx)->rest.push_back(antlrcpp::downCast<MatchStatementContext *>(_localctx)->statementContext); 
        }
        setState(486);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
      }
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<BismuthParser::ReturnStatementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(487);
      match(BismuthParser::RETURN);
      setState(489);
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
        setState(488);
        expression(0);
      }
      setState(491);
      match(BismuthParser::SEMICOLON);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<BismuthParser::ExitStatementContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(492);
      match(BismuthParser::EXIT);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<BismuthParser::SkipStatementContext>(_localctx);
      enterOuterAlt(_localctx, 10);
      setState(493);
      match(BismuthParser::T__10);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<BismuthParser::BlockStatementContext>(_localctx);
      enterOuterAlt(_localctx, 11);
      setState(494);
      block();
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramSendContext>(_localctx);
      enterOuterAlt(_localctx, 12);
      setState(495);
      antlrcpp::downCast<ProgramSendContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(496);
      match(BismuthParser::T__11);
      setState(497);
      match(BismuthParser::LPAR);
      setState(498);
      antlrcpp::downCast<ProgramSendContext *>(_localctx)->expr = expression(0);
      setState(499);
      match(BismuthParser::RPAR);
      setState(501);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(500);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramLoopContext>(_localctx);
      enterOuterAlt(_localctx, 13);
      setState(503);
      match(BismuthParser::WHILE);
      setState(504);
      antlrcpp::downCast<ProgramLoopContext *>(_localctx)->check = condition();
      setState(505);
      block();
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<BismuthParser::ForStatementContext>(_localctx);
      enterOuterAlt(_localctx, 14);
      setState(507);
      match(BismuthParser::T__12);
      setState(508);
      match(BismuthParser::LPAR);
      setState(511);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
      case 1: {
        setState(509);
        antlrcpp::downCast<ForStatementContext *>(_localctx)->decl = variableDeclaration();
        break;
      }

      case 2: {
        setState(510);
        antlrcpp::downCast<ForStatementContext *>(_localctx)->assign = assignmentStatement();
        break;
      }

      default:
        break;
      }
      setState(513);
      match(BismuthParser::SEMICOLON);
      setState(514);
      antlrcpp::downCast<ForStatementContext *>(_localctx)->check = condition();
      setState(515);
      match(BismuthParser::SEMICOLON);
      setState(516);
      antlrcpp::downCast<ForStatementContext *>(_localctx)->expr = statement();
      setState(517);
      match(BismuthParser::RPAR);
      setState(518);
      antlrcpp::downCast<ForStatementContext *>(_localctx)->blk = block();
      break;
    }

    case 15: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramCaseContext>(_localctx);
      enterOuterAlt(_localctx, 15);
      setState(520);
      antlrcpp::downCast<ProgramCaseContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(521);
      match(BismuthParser::T__13);
      setState(522);
      match(BismuthParser::LPAR);
      setState(523);
      antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext = protoAlternative();
      antlrcpp::downCast<ProgramCaseContext *>(_localctx)->opts.push_back(antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext);
      setState(525); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(524);
        antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext = protoAlternative();
        antlrcpp::downCast<ProgramCaseContext *>(_localctx)->opts.push_back(antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext);
        setState(527); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << BismuthParser::T__23)
        | (1ULL << BismuthParser::MINUS)
        | (1ULL << BismuthParser::NOT)
        | (1ULL << BismuthParser::PLUS)
        | (1ULL << BismuthParser::LPAR))) != 0) || ((((_la - 88) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 88)) & ((1ULL << (BismuthParser::EXTERNAL_CHOICE - 88))
        | (1ULL << (BismuthParser::INTERNAL_CHOICE - 88))
        | (1ULL << (BismuthParser::CLOSEABLE - 88))
        | (1ULL << (BismuthParser::VARIABLE - 88)))) != 0));
      setState(530);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::ELSE) {
        setState(529);
        protoElse();
      }
      setState(532);
      match(BismuthParser::RPAR);
      setState(536);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(533);
          antlrcpp::downCast<ProgramCaseContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<ProgramCaseContext *>(_localctx)->rest.push_back(antlrcpp::downCast<ProgramCaseContext *>(_localctx)->statementContext); 
        }
        setState(538);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx);
      }
      break;
    }

    case 16: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramCaseContext>(_localctx);
      enterOuterAlt(_localctx, 16);
      setState(539);
      match(BismuthParser::T__14);
      setState(540);
      antlrcpp::downCast<ProgramCaseContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(543); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(541);
                match(BismuthParser::BIT_OR);
                setState(542);
                antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext = protoAlternative();
                antlrcpp::downCast<ProgramCaseContext *>(_localctx)->opts.push_back(antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(545); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(551);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx)) {
      case 1: {
        setState(547);
        match(BismuthParser::BIT_OR);
        setState(549);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
        case 1: {
          setState(548);
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
      setState(556);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(553);
          antlrcpp::downCast<ProgramCaseContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<ProgramCaseContext *>(_localctx)->rest.push_back(antlrcpp::downCast<ProgramCaseContext *>(_localctx)->statementContext); 
        }
        setState(558);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx);
      }
      break;
    }

    case 17: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramProjectContext>(_localctx);
      enterOuterAlt(_localctx, 17);
      setState(559);
      antlrcpp::downCast<ProgramProjectContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(560);
      match(BismuthParser::LBRC);
      setState(563);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case BismuthParser::VARIABLE: {
          setState(561);
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
          setState(562);
          antlrcpp::downCast<ProgramProjectContext *>(_localctx)->sel = protocol();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(565);
      match(BismuthParser::RBRC);
      setState(567);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(566);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 18: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramContractContext>(_localctx);
      enterOuterAlt(_localctx, 18);
      setState(569);
      match(BismuthParser::T__15);
      setState(570);
      match(BismuthParser::LPAR);
      setState(571);
      antlrcpp::downCast<ProgramContractContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(572);
      match(BismuthParser::RPAR);
      setState(574);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(573);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 19: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramContractContext>(_localctx);
      enterOuterAlt(_localctx, 19);
      setState(576);
      match(BismuthParser::T__16);
      setState(577);
      match(BismuthParser::LPAR);
      setState(578);
      antlrcpp::downCast<ProgramContractContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(579);
      match(BismuthParser::RPAR);
      setState(581);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(580);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 20: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramWeakenContext>(_localctx);
      enterOuterAlt(_localctx, 20);
      setState(583);
      match(BismuthParser::T__17);
      setState(584);
      match(BismuthParser::LPAR);
      setState(585);
      antlrcpp::downCast<ProgramWeakenContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(586);
      match(BismuthParser::RPAR);
      setState(588);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(587);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 21: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramAcceptContext>(_localctx);
      enterOuterAlt(_localctx, 21);
      setState(590);
      match(BismuthParser::T__18);
      setState(591);
      match(BismuthParser::LPAR);
      setState(592);
      antlrcpp::downCast<ProgramAcceptContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(593);
      match(BismuthParser::RPAR);
      setState(594);
      block();
      break;
    }

    case 22: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramAcceptWhileContext>(_localctx);
      enterOuterAlt(_localctx, 22);
      setState(595);
      match(BismuthParser::T__19);
      setState(596);
      match(BismuthParser::LPAR);
      setState(597);
      antlrcpp::downCast<ProgramAcceptWhileContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(598);
      match(BismuthParser::COMMA);
      setState(599);
      antlrcpp::downCast<ProgramAcceptWhileContext *>(_localctx)->ex = expression(0);
      setState(600);
      match(BismuthParser::RPAR);
      setState(601);
      block();
      break;
    }

    case 23: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramAcceptIfContext>(_localctx);
      enterOuterAlt(_localctx, 23);
      setState(603);
      match(BismuthParser::T__20);
      setState(604);
      match(BismuthParser::LPAR);
      setState(605);
      antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(606);
      match(BismuthParser::COMMA);
      setState(607);
      antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->check = expression(0);
      setState(608);
      match(BismuthParser::RPAR);
      setState(609);
      antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->trueBlk = block();
      setState(612);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx)) {
      case 1: {
        setState(610);
        match(BismuthParser::ELSE);
        setState(611);
        antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->falseBlk = block();
        break;
      }

      default:
        break;
      }
      setState(617);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(614);
          antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->rest.push_back(antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->statementContext); 
        }
        setState(619);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx);
      }
      break;
    }

    case 24: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramCloseContext>(_localctx);
      enterOuterAlt(_localctx, 24);
      setState(620);
      match(BismuthParser::T__21);
      setState(621);
      match(BismuthParser::LPAR);
      setState(622);
      antlrcpp::downCast<ProgramCloseContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(623);
      match(BismuthParser::RPAR);
      setState(625);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(624);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 25: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramCancelContext>(_localctx);
      enterOuterAlt(_localctx, 25);
      setState(627);
      match(BismuthParser::T__22);
      setState(628);
      match(BismuthParser::LPAR);
      setState(629);
      antlrcpp::downCast<ProgramCancelContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(630);
      match(BismuthParser::RPAR);
      setState(632);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(631);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 26: {
      _localctx = _tracker.createInstance<BismuthParser::ExpressionStatementContext>(_localctx);
      enterOuterAlt(_localctx, 26);
      setState(634);
      expression(0);
      setState(636);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(635);
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
  enterRule(_localctx, 46, BismuthParser::RuleAssignmentStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(640);
    antlrcpp::downCast<AssignmentStatementContext *>(_localctx)->to = expression(0);
    setState(641);
    match(BismuthParser::ASSIGN);
    setState(642);
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
  enterRule(_localctx, 48, BismuthParser::RuleVariableDeclaration);
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
    setState(644);
    antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->ty = typeOrVar();
    setState(645);
    antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignmentContext = assignment();
    antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignments.push_back(antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignmentContext);
    setState(650);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BismuthParser::COMMA) {
      setState(646);
      match(BismuthParser::COMMA);
      setState(647);
      antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignmentContext = assignment();
      antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignments.push_back(antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignmentContext);
      setState(652);
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
  enterRule(_localctx, 50, BismuthParser::RuleShiftOp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(660);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(653);
      match(BismuthParser::GREATER);
      setState(654);
      match(BismuthParser::GREATER);
      setState(655);
      match(BismuthParser::GREATER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(656);
      match(BismuthParser::GREATER);
      setState(657);
      match(BismuthParser::GREATER);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(658);
      match(BismuthParser::LESS);
      setState(659);
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
  enterRule(_localctx, 52, BismuthParser::RuleTypeOrVar);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(664);
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
        setState(662);
        type(0);
        break;
      }

      case BismuthParser::TYPE_VAR: {
        enterOuterAlt(_localctx, 2);
        setState(663);
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
  enterRule(_localctx, 54, BismuthParser::RuleProtocol);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(686);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(666);
      antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext = subProtocol();
      antlrcpp::downCast<ProtocolContext *>(_localctx)->protos.push_back(antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext);
      setState(671);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx);
      while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1 + 1) {
          setState(667);
          match(BismuthParser::SEMICOLON);
          setState(668);
          antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext = subProtocol();
          antlrcpp::downCast<ProtocolContext *>(_localctx)->protos.push_back(antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext); 
        }
        setState(673);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(674);
      match(BismuthParser::LPAR);
      setState(675);
      antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext = subProtocol();
      antlrcpp::downCast<ProtocolContext *>(_localctx)->protos.push_back(antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext);
      setState(680);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx);
      while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1 + 1) {
          setState(676);
          match(BismuthParser::SEMICOLON);
          setState(677);
          antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext = subProtocol();
          antlrcpp::downCast<ProtocolContext *>(_localctx)->protos.push_back(antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext); 
        }
        setState(682);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx);
      }
      setState(683);
      match(BismuthParser::RPAR);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(685);
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
  enterRule(_localctx, 56, BismuthParser::RuleSubProtocol);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(723);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BismuthParser::PLUS: {
        _localctx = _tracker.createInstance<BismuthParser::RecvTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(688);
        match(BismuthParser::PLUS);
        setState(689);
        antlrcpp::downCast<RecvTypeContext *>(_localctx)->ty = type(0);
        break;
      }

      case BismuthParser::MINUS: {
        _localctx = _tracker.createInstance<BismuthParser::SendTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(690);
        match(BismuthParser::MINUS);
        setState(691);
        antlrcpp::downCast<SendTypeContext *>(_localctx)->ty = type(0);
        break;
      }

      case BismuthParser::T__23: {
        _localctx = _tracker.createInstance<BismuthParser::WnProtoContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(692);
        match(BismuthParser::T__23);
        setState(693);
        antlrcpp::downCast<WnProtoContext *>(_localctx)->proto = protocol();
        break;
      }

      case BismuthParser::NOT: {
        _localctx = _tracker.createInstance<BismuthParser::OcProtoContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(694);
        match(BismuthParser::NOT);
        setState(695);
        antlrcpp::downCast<OcProtoContext *>(_localctx)->proto = protocol();
        break;
      }

      case BismuthParser::EXTERNAL_CHOICE: {
        _localctx = _tracker.createInstance<BismuthParser::ExtChoiceProtoContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(696);
        match(BismuthParser::EXTERNAL_CHOICE);
        setState(697);
        match(BismuthParser::LESS);
        setState(698);
        antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoBranchContext = protoBranch();
        antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoOpts.push_back(antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoBranchContext);
        setState(701); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(699);
          match(BismuthParser::COMMA);
          setState(700);
          antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoBranchContext = protoBranch();
          antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoOpts.push_back(antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoBranchContext);
          setState(703); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == BismuthParser::COMMA);
        setState(705);
        match(BismuthParser::GREATER);
        break;
      }

      case BismuthParser::INTERNAL_CHOICE: {
        _localctx = _tracker.createInstance<BismuthParser::IntChoiceProtoContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(707);
        match(BismuthParser::INTERNAL_CHOICE);
        setState(708);
        match(BismuthParser::LESS);
        setState(709);
        antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoBranchContext = protoBranch();
        antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoOpts.push_back(antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoBranchContext);
        setState(712); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(710);
          match(BismuthParser::COMMA);
          setState(711);
          antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoBranchContext = protoBranch();
          antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoOpts.push_back(antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoBranchContext);
          setState(714); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == BismuthParser::COMMA);
        setState(716);
        match(BismuthParser::GREATER);
        break;
      }

      case BismuthParser::CLOSEABLE: {
        _localctx = _tracker.createInstance<BismuthParser::CloseableProtoContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(718);
        match(BismuthParser::CLOSEABLE);
        setState(719);
        match(BismuthParser::LESS);
        setState(720);
        antlrcpp::downCast<CloseableProtoContext *>(_localctx)->proto = protocol();
        setState(721);
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
  enterRule(_localctx, 58, BismuthParser::RuleProtoBranch);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(729);
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
        setState(725);
        protocol();
        break;
      }

      case BismuthParser::VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(726);
        antlrcpp::downCast<ProtoBranchContext *>(_localctx)->lbl = match(BismuthParser::VARIABLE);
        setState(727);
        match(BismuthParser::COLON);
        setState(728);
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
  size_t startState = 60;
  enterRecursionRule(_localctx, 60, BismuthParser::RuleType, precedence);

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
    setState(815);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 93, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<BaseTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(732);
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
      setState(733);
      match(BismuthParser::LPAR);
      setState(742);
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
        setState(734);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
        setState(739);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == BismuthParser::COMMA) {
          setState(735);
          match(BismuthParser::COMMA);
          setState(736);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
          setState(741);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(744);
      match(BismuthParser::RPAR);
      setState(745);
      match(BismuthParser::MAPS_TO);
      setState(749);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx)) {
      case 1: {
        setState(746);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->returnType = type(0);
        break;
      }

      case 2: {
        setState(747);
        match(BismuthParser::LPAR);
        setState(748);
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
      setState(751);
      match(BismuthParser::LPAR);
      setState(760);
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
        setState(752);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
        setState(757);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == BismuthParser::COMMA) {
          setState(753);
          match(BismuthParser::COMMA);
          setState(754);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
          setState(759);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(762);
      match(BismuthParser::MAPS_TO);
      setState(766);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 88, _ctx)) {
      case 1: {
        setState(763);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->returnType = type(0);
        break;
      }

      case 2: {
        setState(764);
        match(BismuthParser::LPAR);
        setState(765);
        match(BismuthParser::RPAR);
        break;
      }

      default:
        break;
      }
      setState(768);
      match(BismuthParser::RPAR);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<LambdaTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(769);
      match(BismuthParser::LPAR);
      setState(770);
      match(BismuthParser::LPAR);
      setState(779);
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
        setState(771);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
        setState(776);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == BismuthParser::COMMA) {
          setState(772);
          match(BismuthParser::COMMA);
          setState(773);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
          setState(778);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(781);
      match(BismuthParser::RPAR);
      setState(782);
      match(BismuthParser::MAPS_TO);
      setState(786);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 91, _ctx)) {
      case 1: {
        setState(783);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->returnType = type(0);
        break;
      }

      case 2: {
        setState(784);
        match(BismuthParser::LPAR);
        setState(785);
        match(BismuthParser::RPAR);
        break;
      }

      default:
        break;
      }
      setState(788);
      match(BismuthParser::RPAR);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<SumTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(789);
      match(BismuthParser::LPAR);
      setState(790);
      type(0);
      setState(793); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(791);
        match(BismuthParser::PLUS);
        setState(792);
        type(0);
        setState(795); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == BismuthParser::PLUS);
      setState(797);
      match(BismuthParser::RPAR);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChannelTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(799);
      match(BismuthParser::TYPE_CHANNEL);
      setState(800);
      match(BismuthParser::LESS);
      setState(801);
      antlrcpp::downCast<ChannelTypeContext *>(_localctx)->proto = protocol();
      setState(802);
      match(BismuthParser::GREATER);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ProgramTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(804);
      match(BismuthParser::TYPE_PROGRAM);
      setState(805);
      match(BismuthParser::LESS);
      setState(806);
      antlrcpp::downCast<ProgramTypeContext *>(_localctx)->proto = protocol();
      setState(807);
      match(BismuthParser::GREATER);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<BoxTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(809);
      match(BismuthParser::TYPE_BOX);
      setState(810);
      match(BismuthParser::LESS);
      setState(811);
      antlrcpp::downCast<BoxTypeContext *>(_localctx)->ty = type(0);
      setState(812);
      match(BismuthParser::GREATER);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<CustomTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(814);
      path();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(838);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 96, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(836);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 95, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<LambdaTypeContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->paramTypes.push_back(previousContext);
          pushNewRecursionContext(newContext, startState, RuleType);
          setState(817);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(822);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == BismuthParser::COMMA) {
            setState(818);
            match(BismuthParser::COMMA);
            setState(819);
            antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
            antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
            setState(824);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
          setState(825);
          match(BismuthParser::MAPS_TO);
          setState(826);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->returnType = type(11);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<ArrayTypeContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->ty = previousContext;
          pushNewRecursionContext(newContext, startState, RuleType);
          setState(827);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(828);
          match(BismuthParser::LBRC);
          setState(829);
          antlrcpp::downCast<ArrayTypeContext *>(_localctx)->len = match(BismuthParser::DEC_LITERAL);
          setState(830);
          match(BismuthParser::RBRC);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<DynArrayTypeContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->ty = previousContext;
          pushNewRecursionContext(newContext, startState, RuleType);
          setState(831);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(832);
          match(BismuthParser::LBRC);
          setState(833);
          match(BismuthParser::RBRC);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<TemplatedTypeContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->ty = previousContext;
          pushNewRecursionContext(newContext, startState, RuleType);
          setState(834);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(835);
          genericSpecifier();
          break;
        }

        default:
          break;
        } 
      }
      setState(840);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 96, _ctx);
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
  enterRule(_localctx, 62, BismuthParser::RuleIntegerValue);
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
    setState(841);
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
    setState(843);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 97, _ctx)) {
    case 1: {
      setState(842);
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
  enterRule(_localctx, 64, BismuthParser::RuleBooleanConst);
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
    setState(845);
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
    case 11: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);
    case 30: return typeSempred(antlrcpp::downCast<TypeContext *>(context), predicateIndex);

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
