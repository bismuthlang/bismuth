
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
      "'Channel'", "'func'", "'enum'", "'struct'", "'if'", "'else'", "'while'", 
      "'return'", "'select'", "'extern'", "'match'", "'define'", "'exit'", 
      "'exec'", "'copy'", "'import'", "'ExternalChoice'", "'InternalChoice'", 
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
      "TYPE_BOX", "TYPE_PROGRAM", "TYPE_CHANNEL", "FUNC", "ENUM", "STRUCT", 
      "IF", "ELSE", "WHILE", "RETURN", "SELECT", "EXTERN", "MATCH", "DEFINE", 
      "EXIT", "EXEC", "COPY", "IMPORT", "EXTERNAL_CHOICE", "INTERNAL_CHOICE", 
      "CLOSEABLE", "FALSE", "TRUE", "STRING", "VARIABLE", "INLINE_COMMENT", 
      "STD_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,96,851,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,1,0,1,0,1,0,5,0,70,8,0,10,
  	0,12,0,73,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,5,2,86,8,2,
  	10,2,12,2,89,9,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,5,3,98,8,3,10,3,12,3,101,
  	9,3,3,3,103,8,3,1,3,1,3,3,3,107,8,3,1,4,1,4,1,4,1,4,5,4,113,8,4,10,4,
  	12,4,116,9,4,1,4,1,4,1,5,1,5,1,5,1,5,3,5,124,8,5,1,5,1,5,1,5,1,5,4,5,
  	130,8,5,11,5,12,5,131,1,5,1,5,1,5,1,5,1,5,1,5,3,5,140,8,5,1,5,1,5,5,5,
  	144,8,5,10,5,12,5,147,9,5,1,5,1,5,1,5,1,5,3,5,153,8,5,1,5,1,5,1,5,1,5,
  	1,5,3,5,160,8,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,168,8,5,1,5,3,5,171,8,5,1,
  	6,1,6,1,6,1,6,1,6,1,6,3,6,179,8,6,1,6,3,6,182,8,6,1,6,1,6,1,6,3,6,187,
  	8,6,1,6,1,6,1,7,1,7,3,7,193,8,7,1,8,1,8,1,8,5,8,198,8,8,10,8,12,8,201,
  	9,8,1,9,1,9,1,9,1,9,3,9,207,8,9,1,9,3,9,210,8,9,1,10,1,10,1,10,1,10,5,
  	10,216,8,10,10,10,12,10,219,9,10,3,10,221,8,10,1,10,1,10,1,11,1,11,1,
  	11,1,11,1,11,1,11,1,11,1,11,1,11,5,11,234,8,11,10,11,12,11,237,9,11,1,
  	11,3,11,240,8,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,
  	11,5,11,253,8,11,10,11,12,11,256,9,11,3,11,258,8,11,1,11,1,11,1,11,1,
  	11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,
  	11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,
  	11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,299,8,11,1,11,1,11,1,11,1,
  	11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,
  	11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,4,11,330,8,
  	11,11,11,12,11,331,1,11,1,11,1,11,4,11,337,8,11,11,11,12,11,338,1,11,
  	1,11,1,11,4,11,344,8,11,11,11,12,11,345,5,11,348,8,11,10,11,12,11,351,
  	9,11,1,12,1,12,1,12,1,12,1,12,3,12,358,8,12,1,12,1,12,1,13,1,13,5,13,
  	364,8,13,10,13,12,13,367,9,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,3,14,
  	376,8,14,1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,17,1,17,3,17,
  	389,8,17,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,19,1,19,1,19,5,19,401,8,
  	19,10,19,12,19,404,9,19,3,19,406,8,19,1,20,1,20,1,20,1,21,1,21,1,21,5,
  	21,414,8,21,10,21,12,21,417,9,21,1,21,1,21,3,21,421,8,21,1,22,1,22,1,
  	22,3,22,426,8,22,1,22,1,22,3,22,430,8,22,1,22,1,22,1,22,1,22,1,22,3,22,
  	437,8,22,1,22,5,22,440,8,22,10,22,12,22,443,9,22,1,22,1,22,1,22,5,22,
  	448,8,22,10,22,12,22,451,9,22,1,22,1,22,5,22,455,8,22,10,22,12,22,458,
  	9,22,1,22,1,22,1,22,1,22,5,22,464,8,22,10,22,12,22,467,9,22,1,22,1,22,
  	5,22,471,8,22,10,22,12,22,474,9,22,1,22,1,22,1,22,1,22,5,22,480,8,22,
  	10,22,12,22,483,9,22,1,22,5,22,486,8,22,10,22,12,22,489,9,22,1,22,1,22,
  	3,22,493,8,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,
  	505,8,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,515,8,22,1,22,1,
  	22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,4,22,529,8,22,11,
  	22,12,22,530,1,22,3,22,534,8,22,1,22,1,22,5,22,538,8,22,10,22,12,22,541,
  	9,22,1,22,1,22,1,22,1,22,4,22,547,8,22,11,22,12,22,548,1,22,1,22,3,22,
  	553,8,22,3,22,555,8,22,1,22,5,22,558,8,22,10,22,12,22,561,9,22,1,22,1,
  	22,1,22,1,22,3,22,567,8,22,1,22,1,22,3,22,571,8,22,1,22,1,22,1,22,1,22,
  	1,22,3,22,578,8,22,1,22,1,22,1,22,1,22,1,22,3,22,585,8,22,1,22,1,22,1,
  	22,1,22,1,22,3,22,592,8,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,
  	22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,
  	22,616,8,22,1,22,5,22,619,8,22,10,22,12,22,622,9,22,1,22,1,22,1,22,1,
  	22,1,22,3,22,629,8,22,1,22,1,22,1,22,1,22,1,22,3,22,636,8,22,1,22,1,22,
  	3,22,640,8,22,3,22,642,8,22,1,23,1,23,1,23,1,23,1,24,1,24,1,24,1,24,5,
  	24,652,8,24,10,24,12,24,655,9,24,1,25,1,25,1,25,1,25,1,25,1,25,1,25,3,
  	25,664,8,25,1,26,1,26,3,26,668,8,26,1,27,1,27,1,27,5,27,673,8,27,10,27,
  	12,27,676,9,27,1,27,1,27,1,27,1,27,5,27,682,8,27,10,27,12,27,685,9,27,
  	1,27,1,27,1,27,3,27,690,8,27,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,
  	1,28,1,28,1,28,1,28,1,28,4,28,705,8,28,11,28,12,28,706,1,28,1,28,1,28,
  	1,28,1,28,1,28,1,28,4,28,716,8,28,11,28,12,28,717,1,28,1,28,1,28,1,28,
  	1,28,1,28,1,28,3,28,727,8,28,1,29,1,29,1,29,1,29,3,29,733,8,29,1,30,1,
  	30,1,30,1,30,1,30,1,30,5,30,741,8,30,10,30,12,30,744,9,30,3,30,746,8,
  	30,1,30,1,30,1,30,1,30,1,30,3,30,753,8,30,1,30,1,30,1,30,1,30,5,30,759,
  	8,30,10,30,12,30,762,9,30,3,30,764,8,30,1,30,1,30,1,30,1,30,3,30,770,
  	8,30,1,30,1,30,1,30,1,30,1,30,1,30,5,30,778,8,30,10,30,12,30,781,9,30,
  	3,30,783,8,30,1,30,1,30,1,30,1,30,1,30,3,30,790,8,30,1,30,1,30,1,30,1,
  	30,1,30,4,30,797,8,30,11,30,12,30,798,1,30,1,30,1,30,1,30,1,30,1,30,1,
  	30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,3,30,819,8,
  	30,1,30,1,30,1,30,5,30,824,8,30,10,30,12,30,827,9,30,1,30,1,30,1,30,1,
  	30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,5,30,840,8,30,10,30,12,30,843,9,
  	30,1,31,1,31,3,31,847,8,31,1,32,1,32,1,32,2,674,683,2,22,60,33,0,2,4,
  	6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,
  	54,56,58,60,62,64,0,10,2,0,27,28,39,39,1,0,29,31,2,0,27,27,32,32,1,0,
  	33,36,2,0,40,41,44,44,1,0,37,38,1,0,60,67,1,0,57,59,1,0,61,64,1,0,90,
  	91,983,0,71,1,0,0,0,2,76,1,0,0,0,4,81,1,0,0,0,6,106,1,0,0,0,8,108,1,0,
  	0,0,10,170,1,0,0,0,12,172,1,0,0,0,14,190,1,0,0,0,16,194,1,0,0,0,18,202,
  	1,0,0,0,20,211,1,0,0,0,22,298,1,0,0,0,24,352,1,0,0,0,26,361,1,0,0,0,28,
  	375,1,0,0,0,30,377,1,0,0,0,32,381,1,0,0,0,34,388,1,0,0,0,36,393,1,0,0,
  	0,38,405,1,0,0,0,40,407,1,0,0,0,42,410,1,0,0,0,44,641,1,0,0,0,46,643,
  	1,0,0,0,48,647,1,0,0,0,50,663,1,0,0,0,52,667,1,0,0,0,54,689,1,0,0,0,56,
  	726,1,0,0,0,58,732,1,0,0,0,60,818,1,0,0,0,62,844,1,0,0,0,64,848,1,0,0,
  	0,66,70,3,18,9,0,67,70,3,12,6,0,68,70,3,10,5,0,69,66,1,0,0,0,69,67,1,
  	0,0,0,69,68,1,0,0,0,70,73,1,0,0,0,71,69,1,0,0,0,71,72,1,0,0,0,72,74,1,
  	0,0,0,73,71,1,0,0,0,74,75,5,0,0,1,75,1,1,0,0,0,76,77,3,60,30,0,77,78,
  	5,93,0,0,78,79,1,0,0,0,79,80,5,52,0,0,80,3,1,0,0,0,81,82,5,33,0,0,82,
  	87,3,6,3,0,83,84,5,55,0,0,84,86,3,6,3,0,85,83,1,0,0,0,86,89,1,0,0,0,87,
  	85,1,0,0,0,87,88,1,0,0,0,88,90,1,0,0,0,89,87,1,0,0,0,90,91,5,36,0,0,91,
  	5,1,0,0,0,92,102,5,93,0,0,93,94,5,53,0,0,94,99,3,60,30,0,95,96,5,55,0,
  	0,96,98,3,60,30,0,97,95,1,0,0,0,98,101,1,0,0,0,99,97,1,0,0,0,99,100,1,
  	0,0,0,100,103,1,0,0,0,101,99,1,0,0,0,102,93,1,0,0,0,102,103,1,0,0,0,103,
  	107,1,0,0,0,104,105,5,1,0,0,105,107,5,93,0,0,106,92,1,0,0,0,106,104,1,
  	0,0,0,107,7,1,0,0,0,108,109,5,33,0,0,109,114,3,60,30,0,110,111,5,55,0,
  	0,111,113,3,60,30,0,112,110,1,0,0,0,113,116,1,0,0,0,114,112,1,0,0,0,114,
  	115,1,0,0,0,115,117,1,0,0,0,116,114,1,0,0,0,117,118,5,36,0,0,118,9,1,
  	0,0,0,119,120,5,82,0,0,120,121,5,73,0,0,121,123,5,93,0,0,122,124,3,4,
  	2,0,123,122,1,0,0,0,123,124,1,0,0,0,124,125,1,0,0,0,125,126,5,50,0,0,
  	126,129,3,60,30,0,127,128,5,55,0,0,128,130,3,60,30,0,129,127,1,0,0,0,
  	130,131,1,0,0,0,131,129,1,0,0,0,131,132,1,0,0,0,132,133,1,0,0,0,133,134,
  	5,51,0,0,134,171,1,0,0,0,135,136,5,82,0,0,136,137,5,74,0,0,137,139,5,
  	93,0,0,138,140,3,4,2,0,139,138,1,0,0,0,139,140,1,0,0,0,140,141,1,0,0,
  	0,141,145,5,50,0,0,142,144,3,2,1,0,143,142,1,0,0,0,144,147,1,0,0,0,145,
  	143,1,0,0,0,145,146,1,0,0,0,146,148,1,0,0,0,147,145,1,0,0,0,148,171,5,
  	51,0,0,149,150,5,82,0,0,150,152,5,93,0,0,151,153,3,4,2,0,152,151,1,0,
  	0,0,152,153,1,0,0,0,153,154,1,0,0,0,154,155,5,2,0,0,155,156,5,93,0,0,
  	156,157,5,53,0,0,157,159,3,60,30,0,158,160,5,3,0,0,159,158,1,0,0,0,159,
  	160,1,0,0,0,160,161,1,0,0,0,161,162,3,26,13,0,162,171,1,0,0,0,163,164,
  	5,82,0,0,164,165,5,72,0,0,165,167,5,93,0,0,166,168,3,4,2,0,167,166,1,
  	0,0,0,167,168,1,0,0,0,168,169,1,0,0,0,169,171,3,24,12,0,170,119,1,0,0,
  	0,170,135,1,0,0,0,170,149,1,0,0,0,170,163,1,0,0,0,171,11,1,0,0,0,172,
  	173,5,80,0,0,173,174,5,72,0,0,174,175,5,93,0,0,175,181,5,46,0,0,176,178,
  	3,38,19,0,177,179,5,25,0,0,178,177,1,0,0,0,178,179,1,0,0,0,179,182,1,
  	0,0,0,180,182,5,56,0,0,181,176,1,0,0,0,181,180,1,0,0,0,182,183,1,0,0,
  	0,183,186,5,47,0,0,184,185,5,53,0,0,185,187,3,60,30,0,186,184,1,0,0,0,
  	186,187,1,0,0,0,187,188,1,0,0,0,188,189,5,52,0,0,189,13,1,0,0,0,190,192,
  	5,93,0,0,191,193,3,8,4,0,192,191,1,0,0,0,192,193,1,0,0,0,193,15,1,0,0,
  	0,194,199,3,14,7,0,195,196,5,2,0,0,196,198,3,14,7,0,197,195,1,0,0,0,198,
  	201,1,0,0,0,199,197,1,0,0,0,199,200,1,0,0,0,200,17,1,0,0,0,201,199,1,
  	0,0,0,202,203,5,86,0,0,203,206,3,16,8,0,204,205,5,4,0,0,205,207,5,93,
  	0,0,206,204,1,0,0,0,206,207,1,0,0,0,207,209,1,0,0,0,208,210,5,52,0,0,
  	209,208,1,0,0,0,209,210,1,0,0,0,210,19,1,0,0,0,211,220,5,46,0,0,212,217,
  	3,22,11,0,213,214,5,55,0,0,214,216,3,22,11,0,215,213,1,0,0,0,216,219,
  	1,0,0,0,217,215,1,0,0,0,217,218,1,0,0,0,218,221,1,0,0,0,219,217,1,0,0,
  	0,220,212,1,0,0,0,220,221,1,0,0,0,221,222,1,0,0,0,222,223,5,47,0,0,223,
  	21,1,0,0,0,224,225,6,11,-1,0,225,226,5,46,0,0,226,227,3,22,11,0,227,228,
  	5,47,0,0,228,299,1,0,0,0,229,239,5,48,0,0,230,231,3,22,11,0,231,232,5,
  	55,0,0,232,234,1,0,0,0,233,230,1,0,0,0,234,237,1,0,0,0,235,233,1,0,0,
  	0,235,236,1,0,0,0,236,238,1,0,0,0,237,235,1,0,0,0,238,240,3,22,11,0,239,
  	235,1,0,0,0,239,240,1,0,0,0,240,241,1,0,0,0,241,299,5,49,0,0,242,299,
  	5,93,0,0,243,299,3,16,8,0,244,245,7,0,0,0,245,299,3,22,11,22,246,247,
  	3,16,8,0,247,248,5,6,0,0,248,257,5,46,0,0,249,254,3,22,11,0,250,251,5,
  	55,0,0,251,253,3,22,11,0,252,250,1,0,0,0,253,256,1,0,0,0,254,252,1,0,
  	0,0,254,255,1,0,0,0,255,258,1,0,0,0,256,254,1,0,0,0,257,249,1,0,0,0,257,
  	258,1,0,0,0,258,259,1,0,0,0,259,260,5,47,0,0,260,299,1,0,0,0,261,262,
  	5,29,0,0,262,299,3,22,11,12,263,264,5,69,0,0,264,265,5,33,0,0,265,266,
  	3,60,30,0,266,267,5,36,0,0,267,268,5,6,0,0,268,269,5,46,0,0,269,270,3,
  	22,11,0,270,271,5,47,0,0,271,299,1,0,0,0,272,299,3,64,32,0,273,299,3,
  	62,31,0,274,299,5,92,0,0,275,299,3,24,12,0,276,277,5,93,0,0,277,278,5,
  	7,0,0,278,279,5,46,0,0,279,299,5,47,0,0,280,281,5,93,0,0,281,282,5,8,
  	0,0,282,283,5,46,0,0,283,299,5,47,0,0,284,285,5,84,0,0,285,299,3,22,11,
  	4,286,287,5,85,0,0,287,288,5,46,0,0,288,289,3,22,11,0,289,290,5,47,0,
  	0,290,299,1,0,0,0,291,292,5,85,0,0,292,299,3,22,11,2,293,294,5,9,0,0,
  	294,295,5,46,0,0,295,296,3,22,11,0,296,297,5,47,0,0,297,299,1,0,0,0,298,
  	224,1,0,0,0,298,229,1,0,0,0,298,242,1,0,0,0,298,243,1,0,0,0,298,244,1,
  	0,0,0,298,246,1,0,0,0,298,261,1,0,0,0,298,263,1,0,0,0,298,272,1,0,0,0,
  	298,273,1,0,0,0,298,274,1,0,0,0,298,275,1,0,0,0,298,276,1,0,0,0,298,280,
  	1,0,0,0,298,284,1,0,0,0,298,286,1,0,0,0,298,291,1,0,0,0,298,293,1,0,0,
  	0,299,349,1,0,0,0,300,301,10,21,0,0,301,302,7,1,0,0,302,348,3,22,11,22,
  	303,304,10,20,0,0,304,305,7,2,0,0,305,348,3,22,11,21,306,307,10,19,0,
  	0,307,308,3,50,25,0,308,309,3,22,11,20,309,348,1,0,0,0,310,311,10,18,
  	0,0,311,312,7,3,0,0,312,348,3,22,11,19,313,314,10,17,0,0,314,315,7,4,
  	0,0,315,348,3,22,11,18,316,317,10,16,0,0,317,318,7,5,0,0,318,348,3,22,
  	11,16,319,320,10,28,0,0,320,348,3,20,10,0,321,322,10,27,0,0,322,323,5,
  	48,0,0,323,324,3,22,11,0,324,325,5,49,0,0,325,348,1,0,0,0,326,329,10,
  	24,0,0,327,328,5,5,0,0,328,330,5,93,0,0,329,327,1,0,0,0,330,331,1,0,0,
  	0,331,329,1,0,0,0,331,332,1,0,0,0,332,348,1,0,0,0,333,336,10,15,0,0,334,
  	335,5,42,0,0,335,337,3,22,11,0,336,334,1,0,0,0,337,338,1,0,0,0,338,336,
  	1,0,0,0,338,339,1,0,0,0,339,348,1,0,0,0,340,343,10,14,0,0,341,342,5,43,
  	0,0,342,344,3,22,11,0,343,341,1,0,0,0,344,345,1,0,0,0,345,343,1,0,0,0,
  	345,346,1,0,0,0,346,348,1,0,0,0,347,300,1,0,0,0,347,303,1,0,0,0,347,306,
  	1,0,0,0,347,310,1,0,0,0,347,313,1,0,0,0,347,316,1,0,0,0,347,319,1,0,0,
  	0,347,321,1,0,0,0,347,326,1,0,0,0,347,333,1,0,0,0,347,340,1,0,0,0,348,
  	351,1,0,0,0,349,347,1,0,0,0,349,350,1,0,0,0,350,23,1,0,0,0,351,349,1,
  	0,0,0,352,353,5,46,0,0,353,354,3,38,19,0,354,357,5,47,0,0,355,356,5,53,
  	0,0,356,358,3,60,30,0,357,355,1,0,0,0,357,358,1,0,0,0,358,359,1,0,0,0,
  	359,360,3,26,13,0,360,25,1,0,0,0,361,365,5,50,0,0,362,364,3,44,22,0,363,
  	362,1,0,0,0,364,367,1,0,0,0,365,363,1,0,0,0,365,366,1,0,0,0,366,368,1,
  	0,0,0,367,365,1,0,0,0,368,369,5,51,0,0,369,27,1,0,0,0,370,371,5,46,0,
  	0,371,372,3,22,11,0,372,373,5,47,0,0,373,376,1,0,0,0,374,376,3,22,11,
  	0,375,370,1,0,0,0,375,374,1,0,0,0,376,29,1,0,0,0,377,378,3,22,11,0,378,
  	379,5,53,0,0,379,380,3,44,22,0,380,31,1,0,0,0,381,382,3,60,30,0,382,383,
  	5,93,0,0,383,384,5,10,0,0,384,385,3,44,22,0,385,33,1,0,0,0,386,389,5,
  	93,0,0,387,389,3,54,27,0,388,386,1,0,0,0,388,387,1,0,0,0,389,390,1,0,
  	0,0,390,391,5,10,0,0,391,392,3,44,22,0,392,35,1,0,0,0,393,394,5,76,0,
  	0,394,395,5,10,0,0,395,396,3,44,22,0,396,37,1,0,0,0,397,402,3,40,20,0,
  	398,399,5,55,0,0,399,401,3,40,20,0,400,398,1,0,0,0,401,404,1,0,0,0,402,
  	400,1,0,0,0,402,403,1,0,0,0,403,406,1,0,0,0,404,402,1,0,0,0,405,397,1,
  	0,0,0,405,406,1,0,0,0,406,39,1,0,0,0,407,408,3,60,30,0,408,409,5,93,0,
  	0,409,41,1,0,0,0,410,415,5,93,0,0,411,412,5,55,0,0,412,414,5,93,0,0,413,
  	411,1,0,0,0,414,417,1,0,0,0,415,413,1,0,0,0,415,416,1,0,0,0,416,420,1,
  	0,0,0,417,415,1,0,0,0,418,419,5,26,0,0,419,421,3,22,11,0,420,418,1,0,
  	0,0,420,421,1,0,0,0,421,43,1,0,0,0,422,642,3,10,5,0,423,425,3,48,24,0,
  	424,426,5,52,0,0,425,424,1,0,0,0,425,426,1,0,0,0,426,642,1,0,0,0,427,
  	429,3,46,23,0,428,430,5,52,0,0,429,428,1,0,0,0,429,430,1,0,0,0,430,642,
  	1,0,0,0,431,432,5,75,0,0,432,433,3,28,14,0,433,436,3,26,13,0,434,435,
  	5,76,0,0,435,437,3,26,13,0,436,434,1,0,0,0,436,437,1,0,0,0,437,441,1,
  	0,0,0,438,440,3,44,22,0,439,438,1,0,0,0,440,443,1,0,0,0,441,439,1,0,0,
  	0,441,442,1,0,0,0,442,642,1,0,0,0,443,441,1,0,0,0,444,445,5,79,0,0,445,
  	449,5,50,0,0,446,448,3,30,15,0,447,446,1,0,0,0,448,451,1,0,0,0,449,447,
  	1,0,0,0,449,450,1,0,0,0,450,452,1,0,0,0,451,449,1,0,0,0,452,456,5,51,
  	0,0,453,455,3,44,22,0,454,453,1,0,0,0,455,458,1,0,0,0,456,454,1,0,0,0,
  	456,457,1,0,0,0,457,642,1,0,0,0,458,456,1,0,0,0,459,460,5,81,0,0,460,
  	461,3,28,14,0,461,465,5,50,0,0,462,464,3,32,16,0,463,462,1,0,0,0,464,
  	467,1,0,0,0,465,463,1,0,0,0,465,466,1,0,0,0,466,468,1,0,0,0,467,465,1,
  	0,0,0,468,472,5,51,0,0,469,471,3,44,22,0,470,469,1,0,0,0,471,474,1,0,
  	0,0,472,470,1,0,0,0,472,473,1,0,0,0,473,642,1,0,0,0,474,472,1,0,0,0,475,
  	476,5,81,0,0,476,481,3,28,14,0,477,478,5,41,0,0,478,480,3,32,16,0,479,
  	477,1,0,0,0,480,483,1,0,0,0,481,479,1,0,0,0,481,482,1,0,0,0,482,487,1,
  	0,0,0,483,481,1,0,0,0,484,486,3,44,22,0,485,484,1,0,0,0,486,489,1,0,0,
  	0,487,485,1,0,0,0,487,488,1,0,0,0,488,642,1,0,0,0,489,487,1,0,0,0,490,
  	492,5,78,0,0,491,493,3,22,11,0,492,491,1,0,0,0,492,493,1,0,0,0,493,494,
  	1,0,0,0,494,642,5,52,0,0,495,642,5,83,0,0,496,642,5,11,0,0,497,642,3,
  	26,13,0,498,499,5,93,0,0,499,500,5,12,0,0,500,501,5,46,0,0,501,502,3,
  	22,11,0,502,504,5,47,0,0,503,505,5,52,0,0,504,503,1,0,0,0,504,505,1,0,
  	0,0,505,642,1,0,0,0,506,507,5,77,0,0,507,508,3,28,14,0,508,509,3,26,13,
  	0,509,642,1,0,0,0,510,511,5,13,0,0,511,514,5,46,0,0,512,515,3,48,24,0,
  	513,515,3,46,23,0,514,512,1,0,0,0,514,513,1,0,0,0,515,516,1,0,0,0,516,
  	517,5,52,0,0,517,518,3,28,14,0,518,519,5,52,0,0,519,520,3,44,22,0,520,
  	521,5,47,0,0,521,522,3,26,13,0,522,642,1,0,0,0,523,524,5,93,0,0,524,525,
  	5,14,0,0,525,526,5,46,0,0,526,528,3,34,17,0,527,529,3,34,17,0,528,527,
  	1,0,0,0,529,530,1,0,0,0,530,528,1,0,0,0,530,531,1,0,0,0,531,533,1,0,0,
  	0,532,534,3,36,18,0,533,532,1,0,0,0,533,534,1,0,0,0,534,535,1,0,0,0,535,
  	539,5,47,0,0,536,538,3,44,22,0,537,536,1,0,0,0,538,541,1,0,0,0,539,537,
  	1,0,0,0,539,540,1,0,0,0,540,642,1,0,0,0,541,539,1,0,0,0,542,543,5,15,
  	0,0,543,546,5,93,0,0,544,545,5,41,0,0,545,547,3,34,17,0,546,544,1,0,0,
  	0,547,548,1,0,0,0,548,546,1,0,0,0,548,549,1,0,0,0,549,554,1,0,0,0,550,
  	552,5,41,0,0,551,553,3,36,18,0,552,551,1,0,0,0,552,553,1,0,0,0,553,555,
  	1,0,0,0,554,550,1,0,0,0,554,555,1,0,0,0,555,559,1,0,0,0,556,558,3,44,
  	22,0,557,556,1,0,0,0,558,561,1,0,0,0,559,557,1,0,0,0,559,560,1,0,0,0,
  	560,642,1,0,0,0,561,559,1,0,0,0,562,563,5,93,0,0,563,566,5,48,0,0,564,
  	567,5,93,0,0,565,567,3,54,27,0,566,564,1,0,0,0,566,565,1,0,0,0,567,568,
  	1,0,0,0,568,570,5,49,0,0,569,571,5,52,0,0,570,569,1,0,0,0,570,571,1,0,
  	0,0,571,642,1,0,0,0,572,573,5,16,0,0,573,574,5,46,0,0,574,575,5,93,0,
  	0,575,577,5,47,0,0,576,578,5,52,0,0,577,576,1,0,0,0,577,578,1,0,0,0,578,
  	642,1,0,0,0,579,580,5,17,0,0,580,581,5,46,0,0,581,582,5,93,0,0,582,584,
  	5,47,0,0,583,585,5,52,0,0,584,583,1,0,0,0,584,585,1,0,0,0,585,642,1,0,
  	0,0,586,587,5,18,0,0,587,588,5,46,0,0,588,589,5,93,0,0,589,591,5,47,0,
  	0,590,592,5,52,0,0,591,590,1,0,0,0,591,592,1,0,0,0,592,642,1,0,0,0,593,
  	594,5,19,0,0,594,595,5,46,0,0,595,596,5,93,0,0,596,597,5,47,0,0,597,642,
  	3,26,13,0,598,599,5,20,0,0,599,600,5,46,0,0,600,601,5,93,0,0,601,602,
  	5,55,0,0,602,603,3,22,11,0,603,604,5,47,0,0,604,605,3,26,13,0,605,642,
  	1,0,0,0,606,607,5,21,0,0,607,608,5,46,0,0,608,609,5,93,0,0,609,610,5,
  	55,0,0,610,611,3,22,11,0,611,612,5,47,0,0,612,615,3,26,13,0,613,614,5,
  	76,0,0,614,616,3,26,13,0,615,613,1,0,0,0,615,616,1,0,0,0,616,620,1,0,
  	0,0,617,619,3,44,22,0,618,617,1,0,0,0,619,622,1,0,0,0,620,618,1,0,0,0,
  	620,621,1,0,0,0,621,642,1,0,0,0,622,620,1,0,0,0,623,624,5,22,0,0,624,
  	625,5,46,0,0,625,626,5,93,0,0,626,628,5,47,0,0,627,629,5,52,0,0,628,627,
  	1,0,0,0,628,629,1,0,0,0,629,642,1,0,0,0,630,631,5,23,0,0,631,632,5,46,
  	0,0,632,633,5,93,0,0,633,635,5,47,0,0,634,636,5,52,0,0,635,634,1,0,0,
  	0,635,636,1,0,0,0,636,642,1,0,0,0,637,639,3,22,11,0,638,640,5,52,0,0,
  	639,638,1,0,0,0,639,640,1,0,0,0,640,642,1,0,0,0,641,422,1,0,0,0,641,423,
  	1,0,0,0,641,427,1,0,0,0,641,431,1,0,0,0,641,444,1,0,0,0,641,459,1,0,0,
  	0,641,475,1,0,0,0,641,490,1,0,0,0,641,495,1,0,0,0,641,496,1,0,0,0,641,
  	497,1,0,0,0,641,498,1,0,0,0,641,506,1,0,0,0,641,510,1,0,0,0,641,523,1,
  	0,0,0,641,542,1,0,0,0,641,562,1,0,0,0,641,572,1,0,0,0,641,579,1,0,0,0,
  	641,586,1,0,0,0,641,593,1,0,0,0,641,598,1,0,0,0,641,606,1,0,0,0,641,623,
  	1,0,0,0,641,630,1,0,0,0,641,637,1,0,0,0,642,45,1,0,0,0,643,644,3,22,11,
  	0,644,645,5,26,0,0,645,646,3,22,11,0,646,47,1,0,0,0,647,648,3,52,26,0,
  	648,653,3,42,21,0,649,650,5,55,0,0,650,652,3,42,21,0,651,649,1,0,0,0,
  	652,655,1,0,0,0,653,651,1,0,0,0,653,654,1,0,0,0,654,49,1,0,0,0,655,653,
  	1,0,0,0,656,657,5,36,0,0,657,658,5,36,0,0,658,664,5,36,0,0,659,660,5,
  	36,0,0,660,664,5,36,0,0,661,662,5,33,0,0,662,664,5,33,0,0,663,656,1,0,
  	0,0,663,659,1,0,0,0,663,661,1,0,0,0,664,51,1,0,0,0,665,668,3,60,30,0,
  	666,668,5,68,0,0,667,665,1,0,0,0,667,666,1,0,0,0,668,53,1,0,0,0,669,674,
  	3,56,28,0,670,671,5,52,0,0,671,673,3,56,28,0,672,670,1,0,0,0,673,676,
  	1,0,0,0,674,675,1,0,0,0,674,672,1,0,0,0,675,690,1,0,0,0,676,674,1,0,0,
  	0,677,678,5,46,0,0,678,683,3,56,28,0,679,680,5,52,0,0,680,682,3,56,28,
  	0,681,679,1,0,0,0,682,685,1,0,0,0,683,684,1,0,0,0,683,681,1,0,0,0,684,
  	686,1,0,0,0,685,683,1,0,0,0,686,687,5,47,0,0,687,690,1,0,0,0,688,690,
  	3,56,28,0,689,669,1,0,0,0,689,677,1,0,0,0,689,688,1,0,0,0,690,55,1,0,
  	0,0,691,692,5,32,0,0,692,727,3,60,30,0,693,694,5,27,0,0,694,727,3,60,
  	30,0,695,696,5,24,0,0,696,727,3,54,27,0,697,698,5,28,0,0,698,727,3,54,
  	27,0,699,700,5,87,0,0,700,701,5,33,0,0,701,704,3,58,29,0,702,703,5,55,
  	0,0,703,705,3,58,29,0,704,702,1,0,0,0,705,706,1,0,0,0,706,704,1,0,0,0,
  	706,707,1,0,0,0,707,708,1,0,0,0,708,709,5,36,0,0,709,727,1,0,0,0,710,
  	711,5,88,0,0,711,712,5,33,0,0,712,715,3,58,29,0,713,714,5,55,0,0,714,
  	716,3,58,29,0,715,713,1,0,0,0,716,717,1,0,0,0,717,715,1,0,0,0,717,718,
  	1,0,0,0,718,719,1,0,0,0,719,720,5,36,0,0,720,727,1,0,0,0,721,722,5,89,
  	0,0,722,723,5,33,0,0,723,724,3,54,27,0,724,725,5,36,0,0,725,727,1,0,0,
  	0,726,691,1,0,0,0,726,693,1,0,0,0,726,695,1,0,0,0,726,697,1,0,0,0,726,
  	699,1,0,0,0,726,710,1,0,0,0,726,721,1,0,0,0,727,57,1,0,0,0,728,733,3,
  	54,27,0,729,730,5,93,0,0,730,731,5,53,0,0,731,733,3,54,27,0,732,728,1,
  	0,0,0,732,729,1,0,0,0,733,59,1,0,0,0,734,735,6,30,-1,0,735,819,7,6,0,
  	0,736,745,5,46,0,0,737,742,3,60,30,0,738,739,5,55,0,0,739,741,3,60,30,
  	0,740,738,1,0,0,0,741,744,1,0,0,0,742,740,1,0,0,0,742,743,1,0,0,0,743,
  	746,1,0,0,0,744,742,1,0,0,0,745,737,1,0,0,0,745,746,1,0,0,0,746,747,1,
  	0,0,0,747,748,5,47,0,0,748,752,5,45,0,0,749,753,3,60,30,0,750,751,5,46,
  	0,0,751,753,5,47,0,0,752,749,1,0,0,0,752,750,1,0,0,0,753,819,1,0,0,0,
  	754,763,5,46,0,0,755,760,3,60,30,0,756,757,5,55,0,0,757,759,3,60,30,0,
  	758,756,1,0,0,0,759,762,1,0,0,0,760,758,1,0,0,0,760,761,1,0,0,0,761,764,
  	1,0,0,0,762,760,1,0,0,0,763,755,1,0,0,0,763,764,1,0,0,0,764,765,1,0,0,
  	0,765,769,5,45,0,0,766,770,3,60,30,0,767,768,5,46,0,0,768,770,5,47,0,
  	0,769,766,1,0,0,0,769,767,1,0,0,0,770,771,1,0,0,0,771,819,5,47,0,0,772,
  	773,5,46,0,0,773,782,5,46,0,0,774,779,3,60,30,0,775,776,5,55,0,0,776,
  	778,3,60,30,0,777,775,1,0,0,0,778,781,1,0,0,0,779,777,1,0,0,0,779,780,
  	1,0,0,0,780,783,1,0,0,0,781,779,1,0,0,0,782,774,1,0,0,0,782,783,1,0,0,
  	0,783,784,1,0,0,0,784,785,5,47,0,0,785,789,5,45,0,0,786,790,3,60,30,0,
  	787,788,5,46,0,0,788,790,5,47,0,0,789,786,1,0,0,0,789,787,1,0,0,0,790,
  	791,1,0,0,0,791,819,5,47,0,0,792,793,5,46,0,0,793,796,3,60,30,0,794,795,
  	5,32,0,0,795,797,3,60,30,0,796,794,1,0,0,0,797,798,1,0,0,0,798,796,1,
  	0,0,0,798,799,1,0,0,0,799,800,1,0,0,0,800,801,5,47,0,0,801,819,1,0,0,
  	0,802,803,5,71,0,0,803,804,5,33,0,0,804,805,3,54,27,0,805,806,5,36,0,
  	0,806,819,1,0,0,0,807,808,5,70,0,0,808,809,5,33,0,0,809,810,3,54,27,0,
  	810,811,5,36,0,0,811,819,1,0,0,0,812,813,5,69,0,0,813,814,5,33,0,0,814,
  	815,3,60,30,0,815,816,5,36,0,0,816,819,1,0,0,0,817,819,3,16,8,0,818,734,
  	1,0,0,0,818,736,1,0,0,0,818,754,1,0,0,0,818,772,1,0,0,0,818,792,1,0,0,
  	0,818,802,1,0,0,0,818,807,1,0,0,0,818,812,1,0,0,0,818,817,1,0,0,0,819,
  	841,1,0,0,0,820,825,10,10,0,0,821,822,5,55,0,0,822,824,3,60,30,0,823,
  	821,1,0,0,0,824,827,1,0,0,0,825,823,1,0,0,0,825,826,1,0,0,0,826,828,1,
  	0,0,0,827,825,1,0,0,0,828,829,5,45,0,0,829,840,3,60,30,11,830,831,10,
  	13,0,0,831,832,5,48,0,0,832,833,5,57,0,0,833,840,5,49,0,0,834,835,10,
  	12,0,0,835,836,5,48,0,0,836,840,5,49,0,0,837,838,10,2,0,0,838,840,3,8,
  	4,0,839,820,1,0,0,0,839,830,1,0,0,0,839,834,1,0,0,0,839,837,1,0,0,0,840,
  	843,1,0,0,0,841,839,1,0,0,0,841,842,1,0,0,0,842,61,1,0,0,0,843,841,1,
  	0,0,0,844,846,7,7,0,0,845,847,7,8,0,0,846,845,1,0,0,0,846,847,1,0,0,0,
  	847,63,1,0,0,0,848,849,7,9,0,0,849,65,1,0,0,0,98,69,71,87,99,102,106,
  	114,123,131,139,145,152,159,167,170,178,181,186,192,199,206,209,217,220,
  	235,239,254,257,298,331,338,345,347,349,357,365,375,388,402,405,415,420,
  	425,429,436,441,449,456,465,472,481,487,492,504,514,530,533,539,548,552,
  	554,559,566,570,577,584,591,615,620,628,635,639,641,653,663,667,674,683,
  	689,706,717,726,732,742,745,752,760,763,769,779,782,789,798,818,825,839,
  	841,846
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
    while (((((_la - 80) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 80)) & ((1ULL << (BismuthParser::EXTERN - 80))
      | (1ULL << (BismuthParser::DEFINE - 80))
      | (1ULL << (BismuthParser::IMPORT - 80)))) != 0)) {
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

        case BismuthParser::DEFINE: {
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

tree::TerminalNode* BismuthParser::DefineStructContext::DEFINE() {
  return getToken(BismuthParser::DEFINE, 0);
}

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

tree::TerminalNode* BismuthParser::DefineEnumContext::DEFINE() {
  return getToken(BismuthParser::DEFINE, 0);
}

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

tree::TerminalNode* BismuthParser::DefineProgramContext::DEFINE() {
  return getToken(BismuthParser::DEFINE, 0);
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

BismuthParser::TypeContext* BismuthParser::DefineProgramContext::type() {
  return getRuleContext<BismuthParser::TypeContext>(0);
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

tree::TerminalNode* BismuthParser::DefineFunctionContext::DEFINE() {
  return getToken(BismuthParser::DEFINE, 0);
}

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
    setState(170);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<BismuthParser::DefineEnumContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(119);
      match(BismuthParser::DEFINE);
      setState(120);
      match(BismuthParser::ENUM);
      setState(121);
      antlrcpp::downCast<DefineEnumContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
      setState(123);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::LESS) {
        setState(122);
        genericTemplate();
      }
      setState(125);
      match(BismuthParser::LSQB);
      setState(126);
      antlrcpp::downCast<DefineEnumContext *>(_localctx)->typeContext = type(0);
      antlrcpp::downCast<DefineEnumContext *>(_localctx)->cases.push_back(antlrcpp::downCast<DefineEnumContext *>(_localctx)->typeContext);
      setState(129); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(127);
        match(BismuthParser::COMMA);
        setState(128);
        antlrcpp::downCast<DefineEnumContext *>(_localctx)->typeContext = type(0);
        antlrcpp::downCast<DefineEnumContext *>(_localctx)->cases.push_back(antlrcpp::downCast<DefineEnumContext *>(_localctx)->typeContext);
        setState(131); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == BismuthParser::COMMA);
      setState(133);
      match(BismuthParser::RSQB);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<BismuthParser::DefineStructContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(135);
      match(BismuthParser::DEFINE);
      setState(136);
      match(BismuthParser::STRUCT);
      setState(137);
      antlrcpp::downCast<DefineStructContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
      setState(139);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::LESS) {
        setState(138);
        genericTemplate();
      }
      setState(141);
      match(BismuthParser::LSQB);
      setState(145);
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
        setState(142);
        antlrcpp::downCast<DefineStructContext *>(_localctx)->structCaseContext = structCase();
        antlrcpp::downCast<DefineStructContext *>(_localctx)->cases.push_back(antlrcpp::downCast<DefineStructContext *>(_localctx)->structCaseContext);
        setState(147);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(148);
      match(BismuthParser::RSQB);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<BismuthParser::DefineProgramContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(149);
      match(BismuthParser::DEFINE);
      setState(150);
      antlrcpp::downCast<DefineProgramContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
      setState(152);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::LESS) {
        setState(151);
        genericTemplate();
      }
      setState(154);
      match(BismuthParser::T__1);
      setState(155);
      antlrcpp::downCast<DefineProgramContext *>(_localctx)->channelName = match(BismuthParser::VARIABLE);
      setState(156);
      match(BismuthParser::COLON);
      setState(157);
      antlrcpp::downCast<DefineProgramContext *>(_localctx)->ty = type(0);
      setState(159);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::T__2) {
        setState(158);
        match(BismuthParser::T__2);
      }
      setState(161);
      block();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<BismuthParser::DefineFunctionContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(163);
      match(BismuthParser::DEFINE);
      setState(164);
      match(BismuthParser::FUNC);
      setState(165);
      antlrcpp::downCast<DefineFunctionContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
      setState(167);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::LESS) {
        setState(166);
        genericTemplate();
      }
      setState(169);
      antlrcpp::downCast<DefineFunctionContext *>(_localctx)->lam = lambdaConstExpr();
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

tree::TerminalNode* BismuthParser::ExternStatementContext::COLON() {
  return getToken(BismuthParser::COLON, 0);
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
    setState(172);
    match(BismuthParser::EXTERN);
    setState(173);
    match(BismuthParser::FUNC);
    setState(174);
    antlrcpp::downCast<ExternStatementContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
    setState(175);
    match(BismuthParser::LPAR);
    setState(181);
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
        setState(176);
        antlrcpp::downCast<ExternStatementContext *>(_localctx)->paramList = parameterList();
        setState(178);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BismuthParser::VariadicParam) {
          setState(177);
          antlrcpp::downCast<ExternStatementContext *>(_localctx)->variadic = match(BismuthParser::VariadicParam);
        }
        break;
      }

      case BismuthParser::ELLIPSIS: {
        setState(180);
        match(BismuthParser::ELLIPSIS);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(183);
    match(BismuthParser::RPAR);
    setState(186);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BismuthParser::COLON) {
      setState(184);
      match(BismuthParser::COLON);
      setState(185);
      antlrcpp::downCast<ExternStatementContext *>(_localctx)->ret = type(0);
    }
    setState(188);
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
    setState(190);
    antlrcpp::downCast<PathElementContext *>(_localctx)->id = match(BismuthParser::VARIABLE);
    setState(192);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      setState(191);
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
    setState(194);
    antlrcpp::downCast<PathContext *>(_localctx)->pathElementContext = pathElement();
    antlrcpp::downCast<PathContext *>(_localctx)->eles.push_back(antlrcpp::downCast<PathContext *>(_localctx)->pathElementContext);
    setState(199);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(195);
        match(BismuthParser::T__1);
        setState(196);
        antlrcpp::downCast<PathContext *>(_localctx)->pathElementContext = pathElement();
        antlrcpp::downCast<PathContext *>(_localctx)->eles.push_back(antlrcpp::downCast<PathContext *>(_localctx)->pathElementContext); 
      }
      setState(201);
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
    setState(202);
    match(BismuthParser::IMPORT);
    setState(203);
    path();
    setState(206);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BismuthParser::T__3) {
      setState(204);
      match(BismuthParser::T__3);
      setState(205);
      antlrcpp::downCast<ImportStatementContext *>(_localctx)->alias = match(BismuthParser::VARIABLE);
    }
    setState(209);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BismuthParser::SEMICOLON) {
      setState(208);
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
    setState(211);
    match(BismuthParser::LPAR);
    setState(220);
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
      setState(212);
      antlrcpp::downCast<Inv_argsContext *>(_localctx)->expressionContext = expression(0);
      antlrcpp::downCast<Inv_argsContext *>(_localctx)->args.push_back(antlrcpp::downCast<Inv_argsContext *>(_localctx)->expressionContext);
      setState(217);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == BismuthParser::COMMA) {
        setState(213);
        match(BismuthParser::COMMA);
        setState(214);
        antlrcpp::downCast<Inv_argsContext *>(_localctx)->expressionContext = expression(0);
        antlrcpp::downCast<Inv_argsContext *>(_localctx)->args.push_back(antlrcpp::downCast<Inv_argsContext *>(_localctx)->expressionContext);
        setState(219);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(222);
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
    setState(298);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ParenExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(225);
      match(BismuthParser::LPAR);
      setState(226);
      antlrcpp::downCast<ParenExprContext *>(_localctx)->ex = expression(0);
      setState(227);
      match(BismuthParser::RPAR);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ArrayExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(229);
      match(BismuthParser::LBRC);
      setState(239);
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
        setState(235);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(230);
            antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->expressionContext = expression(0);
            antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->elements.push_back(antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->expressionContext);
            setState(231);
            match(BismuthParser::COMMA); 
          }
          setState(237);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
        }
        setState(238);
        antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->expressionContext = expression(0);
        antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->elements.push_back(antlrcpp::downCast<ArrayExpressionContext *>(_localctx)->expressionContext);
      }
      setState(241);
      match(BismuthParser::RBRC);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<IdentifierExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(242);
      match(BismuthParser::VARIABLE);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PathExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(243);
      path();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(244);
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
      setState(245);
      antlrcpp::downCast<UnaryExprContext *>(_localctx)->ex = expression(22);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<InitProductContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(246);
      path();
      setState(247);
      match(BismuthParser::T__5);
      setState(248);
      match(BismuthParser::LPAR);
      setState(257);
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
        setState(249);
        antlrcpp::downCast<InitProductContext *>(_localctx)->expressionContext = expression(0);
        antlrcpp::downCast<InitProductContext *>(_localctx)->exprs.push_back(antlrcpp::downCast<InitProductContext *>(_localctx)->expressionContext);
        setState(254);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == BismuthParser::COMMA) {
          setState(250);
          match(BismuthParser::COMMA);
          setState(251);
          antlrcpp::downCast<InitProductContext *>(_localctx)->expressionContext = expression(0);
          antlrcpp::downCast<InitProductContext *>(_localctx)->exprs.push_back(antlrcpp::downCast<InitProductContext *>(_localctx)->expressionContext);
          setState(256);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(259);
      match(BismuthParser::RPAR);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<DerefContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(261);
      match(BismuthParser::MULTIPLY);
      setState(262);
      antlrcpp::downCast<DerefContext *>(_localctx)->expr = expression(12);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<InitBoxContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(263);
      match(BismuthParser::TYPE_BOX);
      setState(264);
      match(BismuthParser::LESS);
      setState(265);
      antlrcpp::downCast<InitBoxContext *>(_localctx)->ty = type(0);
      setState(266);
      match(BismuthParser::GREATER);
      setState(267);
      match(BismuthParser::T__5);
      setState(268);
      match(BismuthParser::LPAR);
      setState(269);
      antlrcpp::downCast<InitBoxContext *>(_localctx)->expr = expression(0);
      setState(270);
      match(BismuthParser::RPAR);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<BConstExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(272);
      booleanConst();
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<IConstExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(273);
      antlrcpp::downCast<IConstExprContext *>(_localctx)->i = integerValue();
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<SConstExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(274);
      antlrcpp::downCast<SConstExprContext *>(_localctx)->s = match(BismuthParser::STRING);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<LambdaExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(275);
      lambdaConstExpr();
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<AssignableRecvContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(276);
      antlrcpp::downCast<AssignableRecvContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(277);
      match(BismuthParser::T__6);
      setState(278);
      match(BismuthParser::LPAR);
      setState(279);
      match(BismuthParser::RPAR);
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<AssignableIsPresentContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(280);
      antlrcpp::downCast<AssignableIsPresentContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(281);
      match(BismuthParser::T__7);
      setState(282);
      match(BismuthParser::LPAR);
      setState(283);
      match(BismuthParser::RPAR);
      break;
    }

    case 15: {
      _localctx = _tracker.createInstance<AssignableExecContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(284);
      match(BismuthParser::EXEC);
      setState(285);
      antlrcpp::downCast<AssignableExecContext *>(_localctx)->prog = expression(4);
      break;
    }

    case 16: {
      _localctx = _tracker.createInstance<CopyExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(286);
      match(BismuthParser::COPY);
      setState(287);
      match(BismuthParser::LPAR);
      setState(288);
      antlrcpp::downCast<CopyExprContext *>(_localctx)->expr = expression(0);
      setState(289);
      match(BismuthParser::RPAR);
      break;
    }

    case 17: {
      _localctx = _tracker.createInstance<CopyExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(291);
      match(BismuthParser::COPY);
      setState(292);
      antlrcpp::downCast<CopyExprContext *>(_localctx)->expr = expression(2);
      break;
    }

    case 18: {
      _localctx = _tracker.createInstance<AsChannelExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(293);
      match(BismuthParser::T__8);
      setState(294);
      match(BismuthParser::LPAR);
      setState(295);
      antlrcpp::downCast<AsChannelExprContext *>(_localctx)->expr = expression(0);
      setState(296);
      match(BismuthParser::RPAR);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(349);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(347);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<BinaryArithExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(300);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(301);
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
          setState(302);
          antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->right = expression(22);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<BinaryArithExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(303);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(304);
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
          setState(305);
          antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->right = expression(21);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<BinaryArithExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(306);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(307);
          shiftOp();
          setState(308);
          antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->right = expression(20);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BinaryRelExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(310);

          if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
          setState(311);
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
          setState(312);
          antlrcpp::downCast<BinaryRelExprContext *>(_localctx)->right = expression(19);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BinaryArithExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(313);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(314);
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
          setState(315);
          antlrcpp::downCast<BinaryArithExprContext *>(_localctx)->right = expression(18);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<EqExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(316);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(317);
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
          setState(318);
          antlrcpp::downCast<EqExprContext *>(_localctx)->right = expression(16);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<CallExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->expr = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(319);

          if (!(precpred(_ctx, 28))) throw FailedPredicateException(this, "precpred(_ctx, 28)");
          setState(320);
          inv_args();
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<ArrayAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->expr = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(321);

          if (!(precpred(_ctx, 27))) throw FailedPredicateException(this, "precpred(_ctx, 27)");
          setState(322);
          match(BismuthParser::LBRC);
          setState(323);
          antlrcpp::downCast<ArrayAccessContext *>(_localctx)->index = expression(0);
          setState(324);
          match(BismuthParser::RBRC);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<FieldAccessExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->expr = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(326);

          if (!(precpred(_ctx, 24))) throw FailedPredicateException(this, "precpred(_ctx, 24)");
          setState(329); 
          _errHandler->sync(this);
          alt = 1;
          do {
            switch (alt) {
              case 1: {
                    setState(327);
                    match(BismuthParser::T__4);
                    setState(328);
                    antlrcpp::downCast<FieldAccessExprContext *>(_localctx)->variableToken = match(BismuthParser::VARIABLE);
                    antlrcpp::downCast<FieldAccessExprContext *>(_localctx)->fields.push_back(antlrcpp::downCast<FieldAccessExprContext *>(_localctx)->variableToken);
                    break;
                  }

            default:
              throw NoViableAltException(this);
            }
            setState(331); 
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
          setState(333);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(336); 
          _errHandler->sync(this);
          alt = 1;
          do {
            switch (alt) {
              case 1: {
                    setState(334);
                    match(BismuthParser::LOG_AND);
                    setState(335);
                    antlrcpp::downCast<LogAndExprContext *>(_localctx)->expressionContext = expression(0);
                    antlrcpp::downCast<LogAndExprContext *>(_localctx)->exprs.push_back(antlrcpp::downCast<LogAndExprContext *>(_localctx)->expressionContext);
                    break;
                  }

            default:
              throw NoViableAltException(this);
            }
            setState(338); 
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
          setState(340);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(343); 
          _errHandler->sync(this);
          alt = 1;
          do {
            switch (alt) {
              case 1: {
                    setState(341);
                    match(BismuthParser::LOG_OR);
                    setState(342);
                    antlrcpp::downCast<LogOrExprContext *>(_localctx)->expressionContext = expression(0);
                    antlrcpp::downCast<LogOrExprContext *>(_localctx)->exprs.push_back(antlrcpp::downCast<LogOrExprContext *>(_localctx)->expressionContext);
                    break;
                  }

            default:
              throw NoViableAltException(this);
            }
            setState(345); 
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
          } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
          break;
        }

        default:
          break;
        } 
      }
      setState(351);
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

tree::TerminalNode* BismuthParser::LambdaConstExprContext::COLON() {
  return getToken(BismuthParser::COLON, 0);
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
    setState(352);
    match(BismuthParser::LPAR);
    setState(353);
    parameterList();
    setState(354);
    match(BismuthParser::RPAR);
    setState(357);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BismuthParser::COLON) {
      setState(355);
      match(BismuthParser::COLON);
      setState(356);
      antlrcpp::downCast<LambdaConstExprContext *>(_localctx)->ret = type(0);
    }
    setState(359);
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
    setState(361);
    match(BismuthParser::LSQB);
    setState(365);
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
      | (1ULL << (BismuthParser::IF - 64))
      | (1ULL << (BismuthParser::WHILE - 64))
      | (1ULL << (BismuthParser::RETURN - 64))
      | (1ULL << (BismuthParser::SELECT - 64))
      | (1ULL << (BismuthParser::MATCH - 64))
      | (1ULL << (BismuthParser::DEFINE - 64))
      | (1ULL << (BismuthParser::EXIT - 64))
      | (1ULL << (BismuthParser::EXEC - 64))
      | (1ULL << (BismuthParser::COPY - 64))
      | (1ULL << (BismuthParser::FALSE - 64))
      | (1ULL << (BismuthParser::TRUE - 64))
      | (1ULL << (BismuthParser::STRING - 64))
      | (1ULL << (BismuthParser::VARIABLE - 64)))) != 0)) {
      setState(362);
      antlrcpp::downCast<BlockContext *>(_localctx)->statementContext = statement();
      antlrcpp::downCast<BlockContext *>(_localctx)->stmts.push_back(antlrcpp::downCast<BlockContext *>(_localctx)->statementContext);
      setState(367);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(368);
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
    setState(375);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(370);
      match(BismuthParser::LPAR);
      setState(371);
      antlrcpp::downCast<ConditionContext *>(_localctx)->ex = expression(0);
      setState(372);
      match(BismuthParser::RPAR);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(374);
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
    setState(377);
    antlrcpp::downCast<SelectAlternativeContext *>(_localctx)->check = expression(0);
    setState(378);
    match(BismuthParser::COLON);
    setState(379);
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
    setState(381);
    antlrcpp::downCast<MatchAlternativeContext *>(_localctx)->check = type(0);
    setState(382);
    antlrcpp::downCast<MatchAlternativeContext *>(_localctx)->name = match(BismuthParser::VARIABLE);
    setState(383);
    match(BismuthParser::T__9);
    setState(384);
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
    setState(388);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BismuthParser::VARIABLE: {
        setState(386);
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
        setState(387);
        antlrcpp::downCast<ProtoAlternativeContext *>(_localctx)->check = protocol();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(390);
    match(BismuthParser::T__9);
    setState(391);
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
    setState(393);
    match(BismuthParser::ELSE);
    setState(394);
    match(BismuthParser::T__9);
    setState(395);
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
    setState(405);
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
      setState(397);
      antlrcpp::downCast<ParameterListContext *>(_localctx)->parameterContext = parameter();
      antlrcpp::downCast<ParameterListContext *>(_localctx)->params.push_back(antlrcpp::downCast<ParameterListContext *>(_localctx)->parameterContext);
      setState(402);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == BismuthParser::COMMA) {
        setState(398);
        match(BismuthParser::COMMA);
        setState(399);
        antlrcpp::downCast<ParameterListContext *>(_localctx)->parameterContext = parameter();
        antlrcpp::downCast<ParameterListContext *>(_localctx)->params.push_back(antlrcpp::downCast<ParameterListContext *>(_localctx)->parameterContext);
        setState(404);
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
    setState(407);
    antlrcpp::downCast<ParameterContext *>(_localctx)->ty = type(0);
    setState(408);
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
    setState(410);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->variableToken = match(BismuthParser::VARIABLE);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->v.push_back(antlrcpp::downCast<AssignmentContext *>(_localctx)->variableToken);
    setState(415);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(411);
        match(BismuthParser::COMMA);
        setState(412);
        antlrcpp::downCast<AssignmentContext *>(_localctx)->variableToken = match(BismuthParser::VARIABLE);
        antlrcpp::downCast<AssignmentContext *>(_localctx)->v.push_back(antlrcpp::downCast<AssignmentContext *>(_localctx)->variableToken); 
      }
      setState(417);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    }
    setState(420);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BismuthParser::ASSIGN) {
      setState(418);
      match(BismuthParser::ASSIGN);
      setState(419);
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
    setState(641);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<BismuthParser::TypeDefContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(422);
      defineType();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<BismuthParser::VarDeclStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(423);
      variableDeclaration();
      setState(425);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(424);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<BismuthParser::AssignStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(427);
      assignmentStatement();
      setState(429);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(428);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<BismuthParser::ConditionalStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(431);
      match(BismuthParser::IF);
      setState(432);
      antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->check = condition();
      setState(433);
      antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->trueBlk = block();
      setState(436);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
      case 1: {
        setState(434);
        match(BismuthParser::ELSE);
        setState(435);
        antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->falseBlk = block();
        break;
      }

      default:
        break;
      }
      setState(441);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(438);
          antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->rest.push_back(antlrcpp::downCast<ConditionalStatementContext *>(_localctx)->statementContext); 
        }
        setState(443);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
      }
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<BismuthParser::SelectStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(444);
      match(BismuthParser::SELECT);
      setState(445);
      match(BismuthParser::LSQB);
      setState(449);
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
        setState(446);
        antlrcpp::downCast<SelectStatementContext *>(_localctx)->selectAlternativeContext = selectAlternative();
        antlrcpp::downCast<SelectStatementContext *>(_localctx)->cases.push_back(antlrcpp::downCast<SelectStatementContext *>(_localctx)->selectAlternativeContext);
        setState(451);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(452);
      match(BismuthParser::RSQB);
      setState(456);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(453);
          antlrcpp::downCast<SelectStatementContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<SelectStatementContext *>(_localctx)->rest.push_back(antlrcpp::downCast<SelectStatementContext *>(_localctx)->statementContext); 
        }
        setState(458);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
      }
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<BismuthParser::MatchStatementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(459);
      match(BismuthParser::MATCH);
      setState(460);
      antlrcpp::downCast<MatchStatementContext *>(_localctx)->check = condition();
      setState(461);
      match(BismuthParser::LSQB);
      setState(465);
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
        setState(462);
        matchAlternative();
        setState(467);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(468);
      match(BismuthParser::RSQB);
      setState(472);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(469);
          antlrcpp::downCast<MatchStatementContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<MatchStatementContext *>(_localctx)->rest.push_back(antlrcpp::downCast<MatchStatementContext *>(_localctx)->statementContext); 
        }
        setState(474);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
      }
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<BismuthParser::MatchStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(475);
      match(BismuthParser::MATCH);
      setState(476);
      antlrcpp::downCast<MatchStatementContext *>(_localctx)->check = condition();
      setState(481);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(477);
          match(BismuthParser::BIT_OR);
          setState(478);
          matchAlternative(); 
        }
        setState(483);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
      }
      setState(487);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(484);
          antlrcpp::downCast<MatchStatementContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<MatchStatementContext *>(_localctx)->rest.push_back(antlrcpp::downCast<MatchStatementContext *>(_localctx)->statementContext); 
        }
        setState(489);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
      }
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<BismuthParser::ReturnStatementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(490);
      match(BismuthParser::RETURN);
      setState(492);
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
        setState(491);
        expression(0);
      }
      setState(494);
      match(BismuthParser::SEMICOLON);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<BismuthParser::ExitStatementContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(495);
      match(BismuthParser::EXIT);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<BismuthParser::SkipStatementContext>(_localctx);
      enterOuterAlt(_localctx, 10);
      setState(496);
      match(BismuthParser::T__10);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<BismuthParser::BlockStatementContext>(_localctx);
      enterOuterAlt(_localctx, 11);
      setState(497);
      block();
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramSendContext>(_localctx);
      enterOuterAlt(_localctx, 12);
      setState(498);
      antlrcpp::downCast<ProgramSendContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(499);
      match(BismuthParser::T__11);
      setState(500);
      match(BismuthParser::LPAR);
      setState(501);
      antlrcpp::downCast<ProgramSendContext *>(_localctx)->expr = expression(0);
      setState(502);
      match(BismuthParser::RPAR);
      setState(504);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(503);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramLoopContext>(_localctx);
      enterOuterAlt(_localctx, 13);
      setState(506);
      match(BismuthParser::WHILE);
      setState(507);
      antlrcpp::downCast<ProgramLoopContext *>(_localctx)->check = condition();
      setState(508);
      block();
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<BismuthParser::ForStatementContext>(_localctx);
      enterOuterAlt(_localctx, 14);
      setState(510);
      match(BismuthParser::T__12);
      setState(511);
      match(BismuthParser::LPAR);
      setState(514);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
      case 1: {
        setState(512);
        antlrcpp::downCast<ForStatementContext *>(_localctx)->decl = variableDeclaration();
        break;
      }

      case 2: {
        setState(513);
        antlrcpp::downCast<ForStatementContext *>(_localctx)->assign = assignmentStatement();
        break;
      }

      default:
        break;
      }
      setState(516);
      match(BismuthParser::SEMICOLON);
      setState(517);
      antlrcpp::downCast<ForStatementContext *>(_localctx)->check = condition();
      setState(518);
      match(BismuthParser::SEMICOLON);
      setState(519);
      antlrcpp::downCast<ForStatementContext *>(_localctx)->expr = statement();
      setState(520);
      match(BismuthParser::RPAR);
      setState(521);
      antlrcpp::downCast<ForStatementContext *>(_localctx)->blk = block();
      break;
    }

    case 15: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramCaseContext>(_localctx);
      enterOuterAlt(_localctx, 15);
      setState(523);
      antlrcpp::downCast<ProgramCaseContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(524);
      match(BismuthParser::T__13);
      setState(525);
      match(BismuthParser::LPAR);
      setState(526);
      antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext = protoAlternative();
      antlrcpp::downCast<ProgramCaseContext *>(_localctx)->opts.push_back(antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext);
      setState(528); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(527);
        antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext = protoAlternative();
        antlrcpp::downCast<ProgramCaseContext *>(_localctx)->opts.push_back(antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext);
        setState(530); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << BismuthParser::T__23)
        | (1ULL << BismuthParser::MINUS)
        | (1ULL << BismuthParser::NOT)
        | (1ULL << BismuthParser::PLUS)
        | (1ULL << BismuthParser::LPAR))) != 0) || ((((_la - 87) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 87)) & ((1ULL << (BismuthParser::EXTERNAL_CHOICE - 87))
        | (1ULL << (BismuthParser::INTERNAL_CHOICE - 87))
        | (1ULL << (BismuthParser::CLOSEABLE - 87))
        | (1ULL << (BismuthParser::VARIABLE - 87)))) != 0));
      setState(533);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::ELSE) {
        setState(532);
        protoElse();
      }
      setState(535);
      match(BismuthParser::RPAR);
      setState(539);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(536);
          antlrcpp::downCast<ProgramCaseContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<ProgramCaseContext *>(_localctx)->rest.push_back(antlrcpp::downCast<ProgramCaseContext *>(_localctx)->statementContext); 
        }
        setState(541);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx);
      }
      break;
    }

    case 16: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramCaseContext>(_localctx);
      enterOuterAlt(_localctx, 16);
      setState(542);
      match(BismuthParser::T__14);
      setState(543);
      antlrcpp::downCast<ProgramCaseContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(546); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(544);
                match(BismuthParser::BIT_OR);
                setState(545);
                antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext = protoAlternative();
                antlrcpp::downCast<ProgramCaseContext *>(_localctx)->opts.push_back(antlrcpp::downCast<ProgramCaseContext *>(_localctx)->protoAlternativeContext);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(548); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(554);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx)) {
      case 1: {
        setState(550);
        match(BismuthParser::BIT_OR);
        setState(552);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
        case 1: {
          setState(551);
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
      setState(559);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(556);
          antlrcpp::downCast<ProgramCaseContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<ProgramCaseContext *>(_localctx)->rest.push_back(antlrcpp::downCast<ProgramCaseContext *>(_localctx)->statementContext); 
        }
        setState(561);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx);
      }
      break;
    }

    case 17: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramProjectContext>(_localctx);
      enterOuterAlt(_localctx, 17);
      setState(562);
      antlrcpp::downCast<ProgramProjectContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(563);
      match(BismuthParser::LBRC);
      setState(566);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case BismuthParser::VARIABLE: {
          setState(564);
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
          setState(565);
          antlrcpp::downCast<ProgramProjectContext *>(_localctx)->sel = protocol();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(568);
      match(BismuthParser::RBRC);
      setState(570);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(569);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 18: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramContractContext>(_localctx);
      enterOuterAlt(_localctx, 18);
      setState(572);
      match(BismuthParser::T__15);
      setState(573);
      match(BismuthParser::LPAR);
      setState(574);
      antlrcpp::downCast<ProgramContractContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(575);
      match(BismuthParser::RPAR);
      setState(577);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(576);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 19: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramContractContext>(_localctx);
      enterOuterAlt(_localctx, 19);
      setState(579);
      match(BismuthParser::T__16);
      setState(580);
      match(BismuthParser::LPAR);
      setState(581);
      antlrcpp::downCast<ProgramContractContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(582);
      match(BismuthParser::RPAR);
      setState(584);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(583);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 20: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramWeakenContext>(_localctx);
      enterOuterAlt(_localctx, 20);
      setState(586);
      match(BismuthParser::T__17);
      setState(587);
      match(BismuthParser::LPAR);
      setState(588);
      antlrcpp::downCast<ProgramWeakenContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(589);
      match(BismuthParser::RPAR);
      setState(591);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(590);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 21: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramAcceptContext>(_localctx);
      enterOuterAlt(_localctx, 21);
      setState(593);
      match(BismuthParser::T__18);
      setState(594);
      match(BismuthParser::LPAR);
      setState(595);
      antlrcpp::downCast<ProgramAcceptContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(596);
      match(BismuthParser::RPAR);
      setState(597);
      block();
      break;
    }

    case 22: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramAcceptWhileContext>(_localctx);
      enterOuterAlt(_localctx, 22);
      setState(598);
      match(BismuthParser::T__19);
      setState(599);
      match(BismuthParser::LPAR);
      setState(600);
      antlrcpp::downCast<ProgramAcceptWhileContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(601);
      match(BismuthParser::COMMA);
      setState(602);
      antlrcpp::downCast<ProgramAcceptWhileContext *>(_localctx)->ex = expression(0);
      setState(603);
      match(BismuthParser::RPAR);
      setState(604);
      block();
      break;
    }

    case 23: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramAcceptIfContext>(_localctx);
      enterOuterAlt(_localctx, 23);
      setState(606);
      match(BismuthParser::T__20);
      setState(607);
      match(BismuthParser::LPAR);
      setState(608);
      antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(609);
      match(BismuthParser::COMMA);
      setState(610);
      antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->check = expression(0);
      setState(611);
      match(BismuthParser::RPAR);
      setState(612);
      antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->trueBlk = block();
      setState(615);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx)) {
      case 1: {
        setState(613);
        match(BismuthParser::ELSE);
        setState(614);
        antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->falseBlk = block();
        break;
      }

      default:
        break;
      }
      setState(620);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(617);
          antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->rest.push_back(antlrcpp::downCast<ProgramAcceptIfContext *>(_localctx)->statementContext); 
        }
        setState(622);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx);
      }
      break;
    }

    case 24: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramCloseContext>(_localctx);
      enterOuterAlt(_localctx, 24);
      setState(623);
      match(BismuthParser::T__21);
      setState(624);
      match(BismuthParser::LPAR);
      setState(625);
      antlrcpp::downCast<ProgramCloseContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(626);
      match(BismuthParser::RPAR);
      setState(628);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(627);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 25: {
      _localctx = _tracker.createInstance<BismuthParser::ProgramCancelContext>(_localctx);
      enterOuterAlt(_localctx, 25);
      setState(630);
      match(BismuthParser::T__22);
      setState(631);
      match(BismuthParser::LPAR);
      setState(632);
      antlrcpp::downCast<ProgramCancelContext *>(_localctx)->channel = match(BismuthParser::VARIABLE);
      setState(633);
      match(BismuthParser::RPAR);
      setState(635);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(634);
        match(BismuthParser::SEMICOLON);
      }
      break;
    }

    case 26: {
      _localctx = _tracker.createInstance<BismuthParser::ExpressionStatementContext>(_localctx);
      enterOuterAlt(_localctx, 26);
      setState(637);
      expression(0);
      setState(639);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BismuthParser::SEMICOLON) {
        setState(638);
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
    setState(643);
    antlrcpp::downCast<AssignmentStatementContext *>(_localctx)->to = expression(0);
    setState(644);
    match(BismuthParser::ASSIGN);
    setState(645);
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
    setState(647);
    antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->ty = typeOrVar();
    setState(648);
    antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignmentContext = assignment();
    antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignments.push_back(antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignmentContext);
    setState(653);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BismuthParser::COMMA) {
      setState(649);
      match(BismuthParser::COMMA);
      setState(650);
      antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignmentContext = assignment();
      antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignments.push_back(antlrcpp::downCast<VariableDeclarationContext *>(_localctx)->assignmentContext);
      setState(655);
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
    setState(663);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(656);
      match(BismuthParser::GREATER);
      setState(657);
      match(BismuthParser::GREATER);
      setState(658);
      match(BismuthParser::GREATER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(659);
      match(BismuthParser::GREATER);
      setState(660);
      match(BismuthParser::GREATER);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(661);
      match(BismuthParser::LESS);
      setState(662);
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
    setState(667);
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
        setState(665);
        type(0);
        break;
      }

      case BismuthParser::TYPE_VAR: {
        enterOuterAlt(_localctx, 2);
        setState(666);
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
    setState(689);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(669);
      antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext = subProtocol();
      antlrcpp::downCast<ProtocolContext *>(_localctx)->protos.push_back(antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext);
      setState(674);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx);
      while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1 + 1) {
          setState(670);
          match(BismuthParser::SEMICOLON);
          setState(671);
          antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext = subProtocol();
          antlrcpp::downCast<ProtocolContext *>(_localctx)->protos.push_back(antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext); 
        }
        setState(676);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(677);
      match(BismuthParser::LPAR);
      setState(678);
      antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext = subProtocol();
      antlrcpp::downCast<ProtocolContext *>(_localctx)->protos.push_back(antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext);
      setState(683);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx);
      while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1 + 1) {
          setState(679);
          match(BismuthParser::SEMICOLON);
          setState(680);
          antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext = subProtocol();
          antlrcpp::downCast<ProtocolContext *>(_localctx)->protos.push_back(antlrcpp::downCast<ProtocolContext *>(_localctx)->subProtocolContext); 
        }
        setState(685);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx);
      }
      setState(686);
      match(BismuthParser::RPAR);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(688);
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
    setState(726);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BismuthParser::PLUS: {
        _localctx = _tracker.createInstance<BismuthParser::RecvTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(691);
        match(BismuthParser::PLUS);
        setState(692);
        antlrcpp::downCast<RecvTypeContext *>(_localctx)->ty = type(0);
        break;
      }

      case BismuthParser::MINUS: {
        _localctx = _tracker.createInstance<BismuthParser::SendTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(693);
        match(BismuthParser::MINUS);
        setState(694);
        antlrcpp::downCast<SendTypeContext *>(_localctx)->ty = type(0);
        break;
      }

      case BismuthParser::T__23: {
        _localctx = _tracker.createInstance<BismuthParser::WnProtoContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(695);
        match(BismuthParser::T__23);
        setState(696);
        antlrcpp::downCast<WnProtoContext *>(_localctx)->proto = protocol();
        break;
      }

      case BismuthParser::NOT: {
        _localctx = _tracker.createInstance<BismuthParser::OcProtoContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(697);
        match(BismuthParser::NOT);
        setState(698);
        antlrcpp::downCast<OcProtoContext *>(_localctx)->proto = protocol();
        break;
      }

      case BismuthParser::EXTERNAL_CHOICE: {
        _localctx = _tracker.createInstance<BismuthParser::ExtChoiceProtoContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(699);
        match(BismuthParser::EXTERNAL_CHOICE);
        setState(700);
        match(BismuthParser::LESS);
        setState(701);
        antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoBranchContext = protoBranch();
        antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoOpts.push_back(antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoBranchContext);
        setState(704); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(702);
          match(BismuthParser::COMMA);
          setState(703);
          antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoBranchContext = protoBranch();
          antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoOpts.push_back(antlrcpp::downCast<ExtChoiceProtoContext *>(_localctx)->protoBranchContext);
          setState(706); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == BismuthParser::COMMA);
        setState(708);
        match(BismuthParser::GREATER);
        break;
      }

      case BismuthParser::INTERNAL_CHOICE: {
        _localctx = _tracker.createInstance<BismuthParser::IntChoiceProtoContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(710);
        match(BismuthParser::INTERNAL_CHOICE);
        setState(711);
        match(BismuthParser::LESS);
        setState(712);
        antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoBranchContext = protoBranch();
        antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoOpts.push_back(antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoBranchContext);
        setState(715); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(713);
          match(BismuthParser::COMMA);
          setState(714);
          antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoBranchContext = protoBranch();
          antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoOpts.push_back(antlrcpp::downCast<IntChoiceProtoContext *>(_localctx)->protoBranchContext);
          setState(717); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == BismuthParser::COMMA);
        setState(719);
        match(BismuthParser::GREATER);
        break;
      }

      case BismuthParser::CLOSEABLE: {
        _localctx = _tracker.createInstance<BismuthParser::CloseableProtoContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(721);
        match(BismuthParser::CLOSEABLE);
        setState(722);
        match(BismuthParser::LESS);
        setState(723);
        antlrcpp::downCast<CloseableProtoContext *>(_localctx)->proto = protocol();
        setState(724);
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
    setState(732);
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
        setState(728);
        protocol();
        break;
      }

      case BismuthParser::VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(729);
        antlrcpp::downCast<ProtoBranchContext *>(_localctx)->lbl = match(BismuthParser::VARIABLE);
        setState(730);
        match(BismuthParser::COLON);
        setState(731);
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
    setState(818);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 93, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<BaseTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(735);
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
      setState(736);
      match(BismuthParser::LPAR);
      setState(745);
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
        setState(737);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
        setState(742);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == BismuthParser::COMMA) {
          setState(738);
          match(BismuthParser::COMMA);
          setState(739);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
          setState(744);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(747);
      match(BismuthParser::RPAR);
      setState(748);
      match(BismuthParser::MAPS_TO);
      setState(752);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx)) {
      case 1: {
        setState(749);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->returnType = type(0);
        break;
      }

      case 2: {
        setState(750);
        match(BismuthParser::LPAR);
        setState(751);
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
      setState(754);
      match(BismuthParser::LPAR);
      setState(763);
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
        setState(755);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
        setState(760);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == BismuthParser::COMMA) {
          setState(756);
          match(BismuthParser::COMMA);
          setState(757);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
          setState(762);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(765);
      match(BismuthParser::MAPS_TO);
      setState(769);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 88, _ctx)) {
      case 1: {
        setState(766);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->returnType = type(0);
        break;
      }

      case 2: {
        setState(767);
        match(BismuthParser::LPAR);
        setState(768);
        match(BismuthParser::RPAR);
        break;
      }

      default:
        break;
      }
      setState(771);
      match(BismuthParser::RPAR);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<LambdaTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(772);
      match(BismuthParser::LPAR);
      setState(773);
      match(BismuthParser::LPAR);
      setState(782);
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
        setState(774);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
        setState(779);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == BismuthParser::COMMA) {
          setState(775);
          match(BismuthParser::COMMA);
          setState(776);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
          setState(781);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(784);
      match(BismuthParser::RPAR);
      setState(785);
      match(BismuthParser::MAPS_TO);
      setState(789);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 91, _ctx)) {
      case 1: {
        setState(786);
        antlrcpp::downCast<LambdaTypeContext *>(_localctx)->returnType = type(0);
        break;
      }

      case 2: {
        setState(787);
        match(BismuthParser::LPAR);
        setState(788);
        match(BismuthParser::RPAR);
        break;
      }

      default:
        break;
      }
      setState(791);
      match(BismuthParser::RPAR);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<SumTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(792);
      match(BismuthParser::LPAR);
      setState(793);
      type(0);
      setState(796); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(794);
        match(BismuthParser::PLUS);
        setState(795);
        type(0);
        setState(798); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == BismuthParser::PLUS);
      setState(800);
      match(BismuthParser::RPAR);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChannelTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(802);
      match(BismuthParser::TYPE_CHANNEL);
      setState(803);
      match(BismuthParser::LESS);
      setState(804);
      antlrcpp::downCast<ChannelTypeContext *>(_localctx)->proto = protocol();
      setState(805);
      match(BismuthParser::GREATER);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ProgramTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(807);
      match(BismuthParser::TYPE_PROGRAM);
      setState(808);
      match(BismuthParser::LESS);
      setState(809);
      antlrcpp::downCast<ProgramTypeContext *>(_localctx)->proto = protocol();
      setState(810);
      match(BismuthParser::GREATER);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<BoxTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(812);
      match(BismuthParser::TYPE_BOX);
      setState(813);
      match(BismuthParser::LESS);
      setState(814);
      antlrcpp::downCast<BoxTypeContext *>(_localctx)->ty = type(0);
      setState(815);
      match(BismuthParser::GREATER);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<CustomTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(817);
      path();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(841);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 96, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(839);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 95, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<LambdaTypeContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->paramTypes.push_back(previousContext);
          pushNewRecursionContext(newContext, startState, RuleType);
          setState(820);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(825);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == BismuthParser::COMMA) {
            setState(821);
            match(BismuthParser::COMMA);
            setState(822);
            antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext = type(0);
            antlrcpp::downCast<LambdaTypeContext *>(_localctx)->paramTypes.push_back(antlrcpp::downCast<LambdaTypeContext *>(_localctx)->typeContext);
            setState(827);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
          setState(828);
          match(BismuthParser::MAPS_TO);
          setState(829);
          antlrcpp::downCast<LambdaTypeContext *>(_localctx)->returnType = type(11);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<ArrayTypeContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->ty = previousContext;
          pushNewRecursionContext(newContext, startState, RuleType);
          setState(830);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(831);
          match(BismuthParser::LBRC);
          setState(832);
          antlrcpp::downCast<ArrayTypeContext *>(_localctx)->len = match(BismuthParser::DEC_LITERAL);
          setState(833);
          match(BismuthParser::RBRC);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<DynArrayTypeContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->ty = previousContext;
          pushNewRecursionContext(newContext, startState, RuleType);
          setState(834);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(835);
          match(BismuthParser::LBRC);
          setState(836);
          match(BismuthParser::RBRC);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<TemplatedTypeContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->ty = previousContext;
          pushNewRecursionContext(newContext, startState, RuleType);
          setState(837);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(838);
          genericSpecifier();
          break;
        }

        default:
          break;
        } 
      }
      setState(843);
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
    setState(844);
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
    setState(846);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 97, _ctx)) {
    case 1: {
      setState(845);
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
    setState(848);
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
