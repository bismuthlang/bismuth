
// Generated from Bismuth.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  BismuthLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, VariadicParam = 25, 
    ASSIGN = 26, MINUS = 27, NOT = 28, MULTIPLY = 29, DIVIDE = 30, MOD = 31, 
    PLUS = 32, LESS = 33, LESS_EQ = 34, GREATER_EQ = 35, GREATER = 36, EQUAL = 37, 
    NOT_EQUAL = 38, BIT_NOT = 39, BIT_AND = 40, BIT_OR = 41, LOG_AND = 42, 
    LOG_OR = 43, BIT_XOR = 44, MAPS_TO = 45, LPAR = 46, RPAR = 47, LBRC = 48, 
    RBRC = 49, LSQB = 50, RSQB = 51, SEMICOLON = 52, COLON = 53, QUOTE = 54, 
    COMMA = 55, ELLIPSIS = 56, DEC_LITERAL = 57, HEX_LITERAL = 58, BIN_LITERAL = 59, 
    TYPE_INT = 60, TYPE_I32 = 61, TYPE_U32 = 62, TYPE_I64 = 63, TYPE_U64 = 64, 
    TYPE_BOOL = 65, TYPE_STR = 66, TYPE_UNIT = 67, TYPE_VAR = 68, TYPE_BOX = 69, 
    TYPE_PROGRAM = 70, TYPE_CHANNEL = 71, PROG = 72, FUNC = 73, ENUM = 74, 
    STRUCT = 75, IF = 76, ELSE = 77, WHILE = 78, RETURN = 79, SELECT = 80, 
    EXTERN = 81, MATCH = 82, DEFINE = 83, EXIT = 84, EXEC = 85, COPY = 86, 
    IMPORT = 87, EXTERNAL_CHOICE = 88, INTERNAL_CHOICE = 89, CLOSEABLE = 90, 
    FALSE = 91, TRUE = 92, STRING = 93, VARIABLE = 94, INLINE_COMMENT = 95, 
    STD_COMMENT = 96, WS = 97
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

