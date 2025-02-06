
// Generated from Bismuth.g4 by ANTLR 4.10.1


#include "BismuthLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct BismuthLexerStaticData final {
  BismuthLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  BismuthLexerStaticData(const BismuthLexerStaticData&) = delete;
  BismuthLexerStaticData(BismuthLexerStaticData&&) = delete;
  BismuthLexerStaticData& operator=(const BismuthLexerStaticData&) = delete;
  BismuthLexerStaticData& operator=(BismuthLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag bismuthlexerLexerOnceFlag;
BismuthLexerStaticData *bismuthlexerLexerStaticData = nullptr;

void bismuthlexerLexerInitialize() {
  assert(bismuthlexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<BismuthLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "T__16", 
      "T__17", "T__18", "T__19", "T__20", "T__21", "T__22", "T__23", "VariadicParam", 
      "ASSIGN", "MINUS", "NOT", "MULTIPLY", "DIVIDE", "MOD", "PLUS", "LESS", 
      "LESS_EQ", "GREATER_EQ", "GREATER", "EQUAL", "NOT_EQUAL", "BIT_NOT", 
      "BIT_AND", "BIT_OR", "LOG_AND", "LOG_OR", "BIT_XOR", "MAPS_TO", "LPAR", 
      "RPAR", "LBRC", "RBRC", "LSQB", "RSQB", "SEMICOLON", "COLON", "QUOTE", 
      "COMMA", "ELLIPSIS", "DEC_LITERAL", "DEC_DIGIT", "HEX_LITERAL", "HEX_DIGIT", 
      "BIN_LITERAL", "BIN_DIGIT", "TYPE_INT", "TYPE_I32", "TYPE_U32", "TYPE_I64", 
      "TYPE_U64", "TYPE_BOOL", "TYPE_STR", "TYPE_UNIT", "TYPE_VAR", "TYPE_BOX", 
      "TYPE_PROGRAM", "TYPE_CHANNEL", "PROG", "FUNC", "ENUM", "STRUCT", 
      "IF", "ELSE", "WHILE", "RETURN", "SELECT", "EXTERN", "MATCH", "DEFINE", 
      "EXIT", "EXEC", "COPY", "IMPORT", "EXTERNAL_CHOICE", "INTERNAL_CHOICE", 
      "CLOSEABLE", "FALSE", "TRUE", "STRING", "VARIABLE", "ESCAPE_STRING", 
      "SAFE_STRING", "INLINE_COMMENT", "STD_COMMENT", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,97,725,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,
  	7,49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,
  	7,56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,
  	7,63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,
  	7,70,2,71,7,71,2,72,7,72,2,73,7,73,2,74,7,74,2,75,7,75,2,76,7,76,2,77,
  	7,77,2,78,7,78,2,79,7,79,2,80,7,80,2,81,7,81,2,82,7,82,2,83,7,83,2,84,
  	7,84,2,85,7,85,2,86,7,86,2,87,7,87,2,88,7,88,2,89,7,89,2,90,7,90,2,91,
  	7,91,2,92,7,92,2,93,7,93,2,94,7,94,2,95,7,95,2,96,7,96,2,97,7,97,2,98,
  	7,98,2,99,7,99,2,100,7,100,2,101,7,101,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
  	0,1,1,1,1,1,1,1,2,1,2,1,3,1,3,1,3,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,6,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,
  	7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,10,1,10,1,10,
  	1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,
  	1,15,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,17,
  	1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,
  	1,20,1,21,1,21,1,21,1,21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,
  	1,23,1,23,1,24,1,24,5,24,353,8,24,10,24,12,24,356,9,24,1,24,1,24,1,24,
  	1,24,1,25,1,25,1,25,1,26,1,26,1,27,1,27,1,28,1,28,1,29,1,29,1,30,1,30,
  	1,31,1,31,1,32,1,32,1,33,1,33,1,33,1,34,1,34,1,34,1,35,1,35,1,36,1,36,
  	1,36,1,37,1,37,1,37,1,38,1,38,1,39,1,39,1,40,1,40,1,41,1,41,1,41,1,42,
  	1,42,1,42,1,43,1,43,1,44,1,44,1,44,1,45,1,45,1,46,1,46,1,47,1,47,1,48,
  	1,48,1,49,1,49,1,50,1,50,1,51,1,51,1,52,1,52,1,53,1,53,1,54,1,54,1,55,
  	1,55,1,55,1,55,1,56,4,56,435,8,56,11,56,12,56,436,1,57,1,57,1,58,1,58,
  	1,58,1,58,4,58,445,8,58,11,58,12,58,446,1,59,1,59,1,60,1,60,1,60,1,60,
  	4,60,455,8,60,11,60,12,60,456,1,61,1,61,1,62,1,62,1,62,1,62,1,63,1,63,
  	1,63,1,63,1,64,1,64,1,64,1,64,1,65,1,65,1,65,1,65,1,66,1,66,1,66,1,66,
  	1,67,1,67,1,67,1,67,1,67,1,67,1,67,1,67,1,68,1,68,1,68,1,68,1,69,1,69,
  	1,69,1,69,1,69,1,70,1,70,1,70,1,70,1,71,1,71,1,71,1,71,1,72,1,72,1,72,
  	1,72,1,72,1,72,1,72,1,72,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,74,
  	1,74,1,74,1,74,1,74,1,75,1,75,1,75,1,75,1,75,1,76,1,76,1,76,1,76,1,76,
  	1,77,1,77,1,77,1,77,1,77,1,77,1,77,1,78,1,78,1,78,1,79,1,79,1,79,1,79,
  	1,79,1,80,1,80,1,80,1,80,1,80,1,80,1,81,1,81,1,81,1,81,1,81,1,81,1,81,
  	1,82,1,82,1,82,1,82,1,82,1,82,1,82,1,83,1,83,1,83,1,83,1,83,1,83,1,83,
  	1,84,1,84,1,84,1,84,1,84,1,84,1,85,1,85,1,85,1,85,1,85,1,85,1,85,1,86,
  	1,86,1,86,1,86,1,86,1,87,1,87,1,87,1,87,1,87,1,88,1,88,1,88,1,88,1,88,
  	1,89,1,89,1,89,1,89,1,89,1,89,1,89,1,90,1,90,1,90,1,90,1,90,1,90,1,90,
  	1,90,1,90,1,90,1,90,1,90,1,90,1,90,1,90,1,91,1,91,1,91,1,91,1,91,1,91,
  	1,91,1,91,1,91,1,91,1,91,1,91,1,91,1,91,1,91,1,92,1,92,1,92,1,92,1,92,
  	1,92,1,92,1,92,1,92,1,92,1,92,1,93,1,93,1,93,1,93,1,93,1,93,1,94,1,94,
  	1,94,1,94,1,94,1,95,1,95,1,95,5,95,669,8,95,10,95,12,95,672,9,95,1,95,
  	1,95,1,96,1,96,5,96,678,8,96,10,96,12,96,681,9,96,1,97,1,97,1,97,1,98,
  	1,98,1,99,1,99,5,99,690,8,99,10,99,12,99,693,9,99,1,99,3,99,696,8,99,
  	1,99,1,99,1,100,1,100,1,100,1,100,1,100,1,100,1,100,1,100,1,100,5,100,
  	709,8,100,10,100,12,100,712,9,100,1,100,1,100,1,100,1,100,1,100,1,101,
  	4,101,720,8,101,11,101,12,101,721,1,101,1,101,2,691,710,0,102,1,1,3,2,
  	5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,
  	16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,
  	55,28,57,29,59,30,61,31,63,32,65,33,67,34,69,35,71,36,73,37,75,38,77,
  	39,79,40,81,41,83,42,85,43,87,44,89,45,91,46,93,47,95,48,97,49,99,50,
  	101,51,103,52,105,53,107,54,109,55,111,56,113,57,115,0,117,58,119,0,121,
  	59,123,0,125,60,127,61,129,62,131,63,133,64,135,65,137,66,139,67,141,
  	68,143,69,145,70,147,71,149,72,151,73,153,74,155,75,157,76,159,77,161,
  	78,163,79,165,80,167,81,169,82,171,83,173,84,175,85,177,86,179,87,181,
  	88,183,89,185,90,187,91,189,92,191,93,193,94,195,0,197,0,199,95,201,96,
  	203,97,1,0,11,2,0,9,9,32,32,1,0,48,57,3,0,48,57,65,70,97,102,1,0,48,49,
  	2,0,65,90,97,122,4,0,48,57,65,90,95,95,97,122,2,0,34,34,92,92,1,1,10,
  	10,1,0,42,42,1,0,47,47,3,0,9,10,12,13,32,32,732,0,1,1,0,0,0,0,3,1,0,0,
  	0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,
  	1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,
  	0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,
  	0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,
  	1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,
  	0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,
  	0,69,1,0,0,0,0,71,1,0,0,0,0,73,1,0,0,0,0,75,1,0,0,0,0,77,1,0,0,0,0,79,
  	1,0,0,0,0,81,1,0,0,0,0,83,1,0,0,0,0,85,1,0,0,0,0,87,1,0,0,0,0,89,1,0,
  	0,0,0,91,1,0,0,0,0,93,1,0,0,0,0,95,1,0,0,0,0,97,1,0,0,0,0,99,1,0,0,0,
  	0,101,1,0,0,0,0,103,1,0,0,0,0,105,1,0,0,0,0,107,1,0,0,0,0,109,1,0,0,0,
  	0,111,1,0,0,0,0,113,1,0,0,0,0,117,1,0,0,0,0,121,1,0,0,0,0,125,1,0,0,0,
  	0,127,1,0,0,0,0,129,1,0,0,0,0,131,1,0,0,0,0,133,1,0,0,0,0,135,1,0,0,0,
  	0,137,1,0,0,0,0,139,1,0,0,0,0,141,1,0,0,0,0,143,1,0,0,0,0,145,1,0,0,0,
  	0,147,1,0,0,0,0,149,1,0,0,0,0,151,1,0,0,0,0,153,1,0,0,0,0,155,1,0,0,0,
  	0,157,1,0,0,0,0,159,1,0,0,0,0,161,1,0,0,0,0,163,1,0,0,0,0,165,1,0,0,0,
  	0,167,1,0,0,0,0,169,1,0,0,0,0,171,1,0,0,0,0,173,1,0,0,0,0,175,1,0,0,0,
  	0,177,1,0,0,0,0,179,1,0,0,0,0,181,1,0,0,0,0,183,1,0,0,0,0,185,1,0,0,0,
  	0,187,1,0,0,0,0,189,1,0,0,0,0,191,1,0,0,0,0,193,1,0,0,0,0,199,1,0,0,0,
  	0,201,1,0,0,0,0,203,1,0,0,0,1,205,1,0,0,0,3,213,1,0,0,0,5,216,1,0,0,0,
  	7,218,1,0,0,0,9,221,1,0,0,0,11,223,1,0,0,0,13,230,1,0,0,0,15,236,1,0,
  	0,0,17,248,1,0,0,0,19,258,1,0,0,0,21,261,1,0,0,0,23,266,1,0,0,0,25,272,
  	1,0,0,0,27,276,1,0,0,0,29,282,1,0,0,0,31,288,1,0,0,0,33,293,1,0,0,0,35,
  	300,1,0,0,0,37,307,1,0,0,0,39,314,1,0,0,0,41,326,1,0,0,0,43,335,1,0,0,
  	0,45,341,1,0,0,0,47,348,1,0,0,0,49,350,1,0,0,0,51,361,1,0,0,0,53,364,
  	1,0,0,0,55,366,1,0,0,0,57,368,1,0,0,0,59,370,1,0,0,0,61,372,1,0,0,0,63,
  	374,1,0,0,0,65,376,1,0,0,0,67,378,1,0,0,0,69,381,1,0,0,0,71,384,1,0,0,
  	0,73,386,1,0,0,0,75,389,1,0,0,0,77,392,1,0,0,0,79,394,1,0,0,0,81,396,
  	1,0,0,0,83,398,1,0,0,0,85,401,1,0,0,0,87,404,1,0,0,0,89,406,1,0,0,0,91,
  	409,1,0,0,0,93,411,1,0,0,0,95,413,1,0,0,0,97,415,1,0,0,0,99,417,1,0,0,
  	0,101,419,1,0,0,0,103,421,1,0,0,0,105,423,1,0,0,0,107,425,1,0,0,0,109,
  	427,1,0,0,0,111,429,1,0,0,0,113,434,1,0,0,0,115,438,1,0,0,0,117,440,1,
  	0,0,0,119,448,1,0,0,0,121,450,1,0,0,0,123,458,1,0,0,0,125,460,1,0,0,0,
  	127,464,1,0,0,0,129,468,1,0,0,0,131,472,1,0,0,0,133,476,1,0,0,0,135,480,
  	1,0,0,0,137,488,1,0,0,0,139,492,1,0,0,0,141,497,1,0,0,0,143,501,1,0,0,
  	0,145,505,1,0,0,0,147,513,1,0,0,0,149,521,1,0,0,0,151,526,1,0,0,0,153,
  	531,1,0,0,0,155,536,1,0,0,0,157,543,1,0,0,0,159,546,1,0,0,0,161,551,1,
  	0,0,0,163,557,1,0,0,0,165,564,1,0,0,0,167,571,1,0,0,0,169,578,1,0,0,0,
  	171,584,1,0,0,0,173,591,1,0,0,0,175,596,1,0,0,0,177,601,1,0,0,0,179,606,
  	1,0,0,0,181,613,1,0,0,0,183,628,1,0,0,0,185,643,1,0,0,0,187,654,1,0,0,
  	0,189,660,1,0,0,0,191,665,1,0,0,0,193,675,1,0,0,0,195,682,1,0,0,0,197,
  	685,1,0,0,0,199,687,1,0,0,0,201,699,1,0,0,0,203,719,1,0,0,0,205,206,5,
  	83,0,0,206,207,5,101,0,0,207,208,5,115,0,0,208,209,5,115,0,0,209,210,
  	5,105,0,0,210,211,5,111,0,0,211,212,5,110,0,0,212,2,1,0,0,0,213,214,5,
  	58,0,0,214,215,5,58,0,0,215,4,1,0,0,0,216,217,5,61,0,0,217,6,1,0,0,0,
  	218,219,5,97,0,0,219,220,5,115,0,0,220,8,1,0,0,0,221,222,5,46,0,0,222,
  	10,1,0,0,0,223,224,5,58,0,0,224,225,5,58,0,0,225,226,5,105,0,0,226,227,
  	5,110,0,0,227,228,5,105,0,0,228,229,5,116,0,0,229,12,1,0,0,0,230,231,
  	5,46,0,0,231,232,5,114,0,0,232,233,5,101,0,0,233,234,5,99,0,0,234,235,
  	5,118,0,0,235,14,1,0,0,0,236,237,5,46,0,0,237,238,5,105,0,0,238,239,5,
  	115,0,0,239,240,5,95,0,0,240,241,5,112,0,0,241,242,5,114,0,0,242,243,
  	5,101,0,0,243,244,5,115,0,0,244,245,5,101,0,0,245,246,5,110,0,0,246,247,
  	5,116,0,0,247,16,1,0,0,0,248,249,5,97,0,0,249,250,5,115,0,0,250,251,5,
  	67,0,0,251,252,5,104,0,0,252,253,5,97,0,0,253,254,5,110,0,0,254,255,5,
  	110,0,0,255,256,5,101,0,0,256,257,5,108,0,0,257,18,1,0,0,0,258,259,5,
  	61,0,0,259,260,5,62,0,0,260,20,1,0,0,0,261,262,5,115,0,0,262,263,5,107,
  	0,0,263,264,5,105,0,0,264,265,5,112,0,0,265,22,1,0,0,0,266,267,5,46,0,
  	0,267,268,5,115,0,0,268,269,5,101,0,0,269,270,5,110,0,0,270,271,5,100,
  	0,0,271,24,1,0,0,0,272,273,5,102,0,0,273,274,5,111,0,0,274,275,5,114,
  	0,0,275,26,1,0,0,0,276,277,5,46,0,0,277,278,5,99,0,0,278,279,5,97,0,0,
  	279,280,5,115,0,0,280,281,5,101,0,0,281,28,1,0,0,0,282,283,5,111,0,0,
  	283,284,5,102,0,0,284,285,5,102,0,0,285,286,5,101,0,0,286,287,5,114,0,
  	0,287,30,1,0,0,0,288,289,5,109,0,0,289,290,5,111,0,0,290,291,5,114,0,
  	0,291,292,5,101,0,0,292,32,1,0,0,0,293,294,5,117,0,0,294,295,5,110,0,
  	0,295,296,5,102,0,0,296,297,5,111,0,0,297,298,5,108,0,0,298,299,5,100,
  	0,0,299,34,1,0,0,0,300,301,5,119,0,0,301,302,5,101,0,0,302,303,5,97,0,
  	0,303,304,5,107,0,0,304,305,5,101,0,0,305,306,5,110,0,0,306,36,1,0,0,
  	0,307,308,5,97,0,0,308,309,5,99,0,0,309,310,5,99,0,0,310,311,5,101,0,
  	0,311,312,5,112,0,0,312,313,5,116,0,0,313,38,1,0,0,0,314,315,5,97,0,0,
  	315,316,5,99,0,0,316,317,5,99,0,0,317,318,5,101,0,0,318,319,5,112,0,0,
  	319,320,5,116,0,0,320,321,5,87,0,0,321,322,5,104,0,0,322,323,5,105,0,
  	0,323,324,5,108,0,0,324,325,5,101,0,0,325,40,1,0,0,0,326,327,5,97,0,0,
  	327,328,5,99,0,0,328,329,5,99,0,0,329,330,5,101,0,0,330,331,5,112,0,0,
  	331,332,5,116,0,0,332,333,5,73,0,0,333,334,5,102,0,0,334,42,1,0,0,0,335,
  	336,5,99,0,0,336,337,5,108,0,0,337,338,5,111,0,0,338,339,5,115,0,0,339,
  	340,5,101,0,0,340,44,1,0,0,0,341,342,5,99,0,0,342,343,5,97,0,0,343,344,
  	5,110,0,0,344,345,5,99,0,0,345,346,5,101,0,0,346,347,5,108,0,0,347,46,
  	1,0,0,0,348,349,5,63,0,0,349,48,1,0,0,0,350,354,5,44,0,0,351,353,7,0,
  	0,0,352,351,1,0,0,0,353,356,1,0,0,0,354,352,1,0,0,0,354,355,1,0,0,0,355,
  	357,1,0,0,0,356,354,1,0,0,0,357,358,5,46,0,0,358,359,5,46,0,0,359,360,
  	5,46,0,0,360,50,1,0,0,0,361,362,5,58,0,0,362,363,5,61,0,0,363,52,1,0,
  	0,0,364,365,5,45,0,0,365,54,1,0,0,0,366,367,5,33,0,0,367,56,1,0,0,0,368,
  	369,5,42,0,0,369,58,1,0,0,0,370,371,5,47,0,0,371,60,1,0,0,0,372,373,5,
  	37,0,0,373,62,1,0,0,0,374,375,5,43,0,0,375,64,1,0,0,0,376,377,5,60,0,
  	0,377,66,1,0,0,0,378,379,5,60,0,0,379,380,5,61,0,0,380,68,1,0,0,0,381,
  	382,5,62,0,0,382,383,5,61,0,0,383,70,1,0,0,0,384,385,5,62,0,0,385,72,
  	1,0,0,0,386,387,5,61,0,0,387,388,5,61,0,0,388,74,1,0,0,0,389,390,5,33,
  	0,0,390,391,5,61,0,0,391,76,1,0,0,0,392,393,5,126,0,0,393,78,1,0,0,0,
  	394,395,5,38,0,0,395,80,1,0,0,0,396,397,5,124,0,0,397,82,1,0,0,0,398,
  	399,5,38,0,0,399,400,5,38,0,0,400,84,1,0,0,0,401,402,5,124,0,0,402,403,
  	5,124,0,0,403,86,1,0,0,0,404,405,5,94,0,0,405,88,1,0,0,0,406,407,5,45,
  	0,0,407,408,5,62,0,0,408,90,1,0,0,0,409,410,5,40,0,0,410,92,1,0,0,0,411,
  	412,5,41,0,0,412,94,1,0,0,0,413,414,5,91,0,0,414,96,1,0,0,0,415,416,5,
  	93,0,0,416,98,1,0,0,0,417,418,5,123,0,0,418,100,1,0,0,0,419,420,5,125,
  	0,0,420,102,1,0,0,0,421,422,5,59,0,0,422,104,1,0,0,0,423,424,5,58,0,0,
  	424,106,1,0,0,0,425,426,5,34,0,0,426,108,1,0,0,0,427,428,5,44,0,0,428,
  	110,1,0,0,0,429,430,5,46,0,0,430,431,5,46,0,0,431,432,5,46,0,0,432,112,
  	1,0,0,0,433,435,3,115,57,0,434,433,1,0,0,0,435,436,1,0,0,0,436,434,1,
  	0,0,0,436,437,1,0,0,0,437,114,1,0,0,0,438,439,7,1,0,0,439,116,1,0,0,0,
  	440,441,5,48,0,0,441,442,5,120,0,0,442,444,1,0,0,0,443,445,3,119,59,0,
  	444,443,1,0,0,0,445,446,1,0,0,0,446,444,1,0,0,0,446,447,1,0,0,0,447,118,
  	1,0,0,0,448,449,7,2,0,0,449,120,1,0,0,0,450,451,5,48,0,0,451,452,5,98,
  	0,0,452,454,1,0,0,0,453,455,3,123,61,0,454,453,1,0,0,0,455,456,1,0,0,
  	0,456,454,1,0,0,0,456,457,1,0,0,0,457,122,1,0,0,0,458,459,7,3,0,0,459,
  	124,1,0,0,0,460,461,5,105,0,0,461,462,5,110,0,0,462,463,5,116,0,0,463,
  	126,1,0,0,0,464,465,5,105,0,0,465,466,5,51,0,0,466,467,5,50,0,0,467,128,
  	1,0,0,0,468,469,5,117,0,0,469,470,5,51,0,0,470,471,5,50,0,0,471,130,1,
  	0,0,0,472,473,5,105,0,0,473,474,5,54,0,0,474,475,5,52,0,0,475,132,1,0,
  	0,0,476,477,5,117,0,0,477,478,5,54,0,0,478,479,5,52,0,0,479,134,1,0,0,
  	0,480,481,5,98,0,0,481,482,5,111,0,0,482,483,5,111,0,0,483,484,5,108,
  	0,0,484,485,5,101,0,0,485,486,5,97,0,0,486,487,5,110,0,0,487,136,1,0,
  	0,0,488,489,5,115,0,0,489,490,5,116,0,0,490,491,5,114,0,0,491,138,1,0,
  	0,0,492,493,5,85,0,0,493,494,5,110,0,0,494,495,5,105,0,0,495,496,5,116,
  	0,0,496,140,1,0,0,0,497,498,5,118,0,0,498,499,5,97,0,0,499,500,5,114,
  	0,0,500,142,1,0,0,0,501,502,5,66,0,0,502,503,5,111,0,0,503,504,5,120,
  	0,0,504,144,1,0,0,0,505,506,5,80,0,0,506,507,5,114,0,0,507,508,5,111,
  	0,0,508,509,5,103,0,0,509,510,5,114,0,0,510,511,5,97,0,0,511,512,5,109,
  	0,0,512,146,1,0,0,0,513,514,5,67,0,0,514,515,5,104,0,0,515,516,5,97,0,
  	0,516,517,5,110,0,0,517,518,5,110,0,0,518,519,5,101,0,0,519,520,5,108,
  	0,0,520,148,1,0,0,0,521,522,5,112,0,0,522,523,5,114,0,0,523,524,5,111,
  	0,0,524,525,5,103,0,0,525,150,1,0,0,0,526,527,5,102,0,0,527,528,5,117,
  	0,0,528,529,5,110,0,0,529,530,5,99,0,0,530,152,1,0,0,0,531,532,5,101,
  	0,0,532,533,5,110,0,0,533,534,5,117,0,0,534,535,5,109,0,0,535,154,1,0,
  	0,0,536,537,5,115,0,0,537,538,5,116,0,0,538,539,5,114,0,0,539,540,5,117,
  	0,0,540,541,5,99,0,0,541,542,5,116,0,0,542,156,1,0,0,0,543,544,5,105,
  	0,0,544,545,5,102,0,0,545,158,1,0,0,0,546,547,5,101,0,0,547,548,5,108,
  	0,0,548,549,5,115,0,0,549,550,5,101,0,0,550,160,1,0,0,0,551,552,5,119,
  	0,0,552,553,5,104,0,0,553,554,5,105,0,0,554,555,5,108,0,0,555,556,5,101,
  	0,0,556,162,1,0,0,0,557,558,5,114,0,0,558,559,5,101,0,0,559,560,5,116,
  	0,0,560,561,5,117,0,0,561,562,5,114,0,0,562,563,5,110,0,0,563,164,1,0,
  	0,0,564,565,5,115,0,0,565,566,5,101,0,0,566,567,5,108,0,0,567,568,5,101,
  	0,0,568,569,5,99,0,0,569,570,5,116,0,0,570,166,1,0,0,0,571,572,5,101,
  	0,0,572,573,5,120,0,0,573,574,5,116,0,0,574,575,5,101,0,0,575,576,5,114,
  	0,0,576,577,5,110,0,0,577,168,1,0,0,0,578,579,5,109,0,0,579,580,5,97,
  	0,0,580,581,5,116,0,0,581,582,5,99,0,0,582,583,5,104,0,0,583,170,1,0,
  	0,0,584,585,5,100,0,0,585,586,5,101,0,0,586,587,5,102,0,0,587,588,5,105,
  	0,0,588,589,5,110,0,0,589,590,5,101,0,0,590,172,1,0,0,0,591,592,5,101,
  	0,0,592,593,5,120,0,0,593,594,5,105,0,0,594,595,5,116,0,0,595,174,1,0,
  	0,0,596,597,5,101,0,0,597,598,5,120,0,0,598,599,5,101,0,0,599,600,5,99,
  	0,0,600,176,1,0,0,0,601,602,5,99,0,0,602,603,5,111,0,0,603,604,5,112,
  	0,0,604,605,5,121,0,0,605,178,1,0,0,0,606,607,5,105,0,0,607,608,5,109,
  	0,0,608,609,5,112,0,0,609,610,5,111,0,0,610,611,5,114,0,0,611,612,5,116,
  	0,0,612,180,1,0,0,0,613,614,5,69,0,0,614,615,5,120,0,0,615,616,5,116,
  	0,0,616,617,5,101,0,0,617,618,5,114,0,0,618,619,5,110,0,0,619,620,5,97,
  	0,0,620,621,5,108,0,0,621,622,5,67,0,0,622,623,5,104,0,0,623,624,5,111,
  	0,0,624,625,5,105,0,0,625,626,5,99,0,0,626,627,5,101,0,0,627,182,1,0,
  	0,0,628,629,5,73,0,0,629,630,5,110,0,0,630,631,5,116,0,0,631,632,5,101,
  	0,0,632,633,5,114,0,0,633,634,5,110,0,0,634,635,5,97,0,0,635,636,5,108,
  	0,0,636,637,5,67,0,0,637,638,5,104,0,0,638,639,5,111,0,0,639,640,5,105,
  	0,0,640,641,5,99,0,0,641,642,5,101,0,0,642,184,1,0,0,0,643,644,5,67,0,
  	0,644,645,5,97,0,0,645,646,5,110,0,0,646,647,5,99,0,0,647,648,5,101,0,
  	0,648,649,5,108,0,0,649,650,5,97,0,0,650,651,5,98,0,0,651,652,5,108,0,
  	0,652,653,5,101,0,0,653,186,1,0,0,0,654,655,5,102,0,0,655,656,5,97,0,
  	0,656,657,5,108,0,0,657,658,5,115,0,0,658,659,5,101,0,0,659,188,1,0,0,
  	0,660,661,5,116,0,0,661,662,5,114,0,0,662,663,5,117,0,0,663,664,5,101,
  	0,0,664,190,1,0,0,0,665,670,3,107,53,0,666,669,3,195,97,0,667,669,3,197,
  	98,0,668,666,1,0,0,0,668,667,1,0,0,0,669,672,1,0,0,0,670,668,1,0,0,0,
  	670,671,1,0,0,0,671,673,1,0,0,0,672,670,1,0,0,0,673,674,3,107,53,0,674,
  	192,1,0,0,0,675,679,7,4,0,0,676,678,7,5,0,0,677,676,1,0,0,0,678,681,1,
  	0,0,0,679,677,1,0,0,0,679,680,1,0,0,0,680,194,1,0,0,0,681,679,1,0,0,0,
  	682,683,5,92,0,0,683,684,9,0,0,0,684,196,1,0,0,0,685,686,8,6,0,0,686,
  	198,1,0,0,0,687,691,5,35,0,0,688,690,9,0,0,0,689,688,1,0,0,0,690,693,
  	1,0,0,0,691,692,1,0,0,0,691,689,1,0,0,0,692,695,1,0,0,0,693,691,1,0,0,
  	0,694,696,7,7,0,0,695,694,1,0,0,0,696,697,1,0,0,0,697,698,6,99,0,0,698,
  	200,1,0,0,0,699,700,5,47,0,0,700,701,5,42,0,0,701,710,1,0,0,0,702,709,
  	3,201,100,0,703,704,5,47,0,0,704,709,8,8,0,0,705,706,8,8,0,0,706,709,
  	5,47,0,0,707,709,8,9,0,0,708,702,1,0,0,0,708,703,1,0,0,0,708,705,1,0,
  	0,0,708,707,1,0,0,0,709,712,1,0,0,0,710,711,1,0,0,0,710,708,1,0,0,0,711,
  	713,1,0,0,0,712,710,1,0,0,0,713,714,5,42,0,0,714,715,5,47,0,0,715,716,
  	1,0,0,0,716,717,6,100,0,0,717,202,1,0,0,0,718,720,7,10,0,0,719,718,1,
  	0,0,0,720,721,1,0,0,0,721,719,1,0,0,0,721,722,1,0,0,0,722,723,1,0,0,0,
  	723,724,6,101,0,0,724,204,1,0,0,0,13,0,354,436,446,456,668,670,679,691,
  	695,708,710,721,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  bismuthlexerLexerStaticData = staticData.release();
}

}

BismuthLexer::BismuthLexer(CharStream *input) : Lexer(input) {
  BismuthLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *bismuthlexerLexerStaticData->atn, bismuthlexerLexerStaticData->decisionToDFA, bismuthlexerLexerStaticData->sharedContextCache);
}

BismuthLexer::~BismuthLexer() {
  delete _interpreter;
}

std::string BismuthLexer::getGrammarFileName() const {
  return "Bismuth.g4";
}

const std::vector<std::string>& BismuthLexer::getRuleNames() const {
  return bismuthlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& BismuthLexer::getChannelNames() const {
  return bismuthlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& BismuthLexer::getModeNames() const {
  return bismuthlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& BismuthLexer::getVocabulary() const {
  return bismuthlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView BismuthLexer::getSerializedATN() const {
  return bismuthlexerLexerStaticData->serializedATN;
}

const atn::ATN& BismuthLexer::getATN() const {
  return *bismuthlexerLexerStaticData->atn;
}




void BismuthLexer::initialize() {
  std::call_once(bismuthlexerLexerOnceFlag, bismuthlexerLexerInitialize);
}
