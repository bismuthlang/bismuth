
// Generated from Bismuth.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  BismuthLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, VariadicParam = 24, ASSIGN = 25, 
    MINUS = 26, NOT = 27, MULTIPLY = 28, DIVIDE = 29, MOD = 30, PLUS = 31, 
    LESS = 32, LESS_EQ = 33, GREATER_EQ = 34, GREATER = 35, EQUAL = 36, 
    NOT_EQUAL = 37, BIT_NOT = 38, BIT_AND = 39, BIT_OR = 40, LOG_AND = 41, 
    LOG_OR = 42, BIT_XOR = 43, MAPS_TO = 44, LPAR = 45, RPAR = 46, LBRC = 47, 
    RBRC = 48, LSQB = 49, RSQB = 50, SEMICOLON = 51, COLON = 52, QUOTE = 53, 
    COMMA = 54, ELLIPSIS = 55, DEC_LITERAL = 56, HEX_LITERAL = 57, BIN_LITERAL = 58, 
    TYPE_INT = 59, TYPE_I32 = 60, TYPE_U32 = 61, TYPE_I64 = 62, TYPE_U64 = 63, 
    TYPE_BOOL = 64, TYPE_STR = 65, TYPE_UNIT = 66, TYPE_VAR = 67, TYPE_BOX = 68, 
    TYPE_PROGRAM = 69, TYPE_CHANNEL = 70, PROG = 71, FUNC = 72, ENUM = 73, 
    STRUCT = 74, IF = 75, FOR = 76, ELSE = 77, WHILE = 78, RETURN = 79, 
    SELECT = 80, EXTERN = 81, MATCH = 82, DEFINE = 83, EXIT = 84, EXEC = 85, 
    COPY = 86, IMPORT = 87, TRAIT = 88, IMPL = 89, AUTO = 90, IMPLS = 91, 
    EXTERNAL_CHOICE = 92, INTERNAL_CHOICE = 93, CLOSEABLE = 94, FALSE = 95, 
    TRUE = 96, STRING = 97, VARIABLE = 98, INLINE_COMMENT = 99, STD_COMMENT = 100, 
    WS = 101
  };

  explicit BismuthLexer(antlr4::CharStream *input);

  ~BismuthLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

