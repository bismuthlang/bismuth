
// Generated from Bismuth.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  BismuthParser : public antlr4::Parser {
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
    TYPE_PROGRAM = 70, TYPE_CHANNEL = 71, FUNC = 72, ENUM = 73, STRUCT = 74, 
    IF = 75, ELSE = 76, WHILE = 77, RETURN = 78, SELECT = 79, EXTERN = 80, 
    MATCH = 81, DEFINE = 82, EXIT = 83, EXEC = 84, COPY = 85, IMPORT = 86, 
    EXTERNAL_CHOICE = 87, INTERNAL_CHOICE = 88, CLOSEABLE = 89, FALSE = 90, 
    TRUE = 91, STRING = 92, VARIABLE = 93, INLINE_COMMENT = 94, STD_COMMENT = 95, 
    WS = 96
  };

  enum {
    RuleCompilationUnit = 0, RuleStructCase = 1, RuleGenericTemplate = 2, 
    RuleGenericEntry = 3, RuleGenericSpecifier = 4, RuleDefineType = 5, 
    RuleExternStatement = 6, RulePathElement = 7, RulePath = 8, RuleImportStatement = 9, 
    RuleInv_args = 10, RuleExpression = 11, RuleLambdaConstExpr = 12, RuleBlock = 13, 
    RuleCondition = 14, RuleSelectAlternative = 15, RuleMatchAlternative = 16, 
    RuleProtoAlternative = 17, RuleProtoElse = 18, RuleParameterList = 19, 
    RuleParameter = 20, RuleAssignment = 21, RuleStatement = 22, RuleAssignmentStatement = 23, 
    RuleVariableDeclaration = 24, RuleShiftOp = 25, RuleTypeOrVar = 26, 
    RuleProtocol = 27, RuleSubProtocol = 28, RuleProtoBranch = 29, RuleType = 30, 
    RuleIntegerValue = 31, RuleBooleanConst = 32
  };

  explicit BismuthParser(antlr4::TokenStream *input);

  BismuthParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~BismuthParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class CompilationUnitContext;
  class StructCaseContext;
  class GenericTemplateContext;
  class GenericEntryContext;
  class GenericSpecifierContext;
  class DefineTypeContext;
  class ExternStatementContext;
  class PathElementContext;
  class PathContext;
  class ImportStatementContext;
  class Inv_argsContext;
  class ExpressionContext;
  class LambdaConstExprContext;
  class BlockContext;
  class ConditionContext;
  class SelectAlternativeContext;
  class MatchAlternativeContext;
  class ProtoAlternativeContext;
  class ProtoElseContext;
  class ParameterListContext;
  class ParameterContext;
  class AssignmentContext;
  class StatementContext;
  class AssignmentStatementContext;
  class VariableDeclarationContext;
  class ShiftOpContext;
  class TypeOrVarContext;
  class ProtocolContext;
  class SubProtocolContext;
  class ProtoBranchContext;
  class TypeContext;
  class IntegerValueContext;
  class BooleanConstContext; 

  class  CompilationUnitContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::ImportStatementContext *importStatementContext = nullptr;
    std::vector<ImportStatementContext *> imports;
    BismuthParser::ExternStatementContext *externStatementContext = nullptr;
    std::vector<ExternStatementContext *> externs;
    BismuthParser::DefineTypeContext *defineTypeContext = nullptr;
    std::vector<DefineTypeContext *> defs;
    CompilationUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<ImportStatementContext *> importStatement();
    ImportStatementContext* importStatement(size_t i);
    std::vector<ExternStatementContext *> externStatement();
    ExternStatementContext* externStatement(size_t i);
    std::vector<DefineTypeContext *> defineType();
    DefineTypeContext* defineType(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompilationUnitContext* compilationUnit();

  class  StructCaseContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::TypeContext *ty = nullptr;
    antlr4::Token *name = nullptr;
    StructCaseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMICOLON();
    TypeContext *type();
    antlr4::tree::TerminalNode *VARIABLE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructCaseContext* structCase();

  class  GenericTemplateContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::GenericEntryContext *genericEntryContext = nullptr;
    std::vector<GenericEntryContext *> gen;
    GenericTemplateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LESS();
    antlr4::tree::TerminalNode *GREATER();
    std::vector<GenericEntryContext *> genericEntry();
    GenericEntryContext* genericEntry(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericTemplateContext* genericTemplate();

  class  GenericEntryContext : public antlr4::ParserRuleContext {
  public:
    GenericEntryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    GenericEntryContext() = default;
    void copyFrom(GenericEntryContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  GenericTypeContext : public GenericEntryContext {
  public:
    GenericTypeContext(GenericEntryContext *ctx);

    antlr4::Token *name = nullptr;
    BismuthParser::TypeContext *typeContext = nullptr;
    std::vector<TypeContext *> supTy;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *COLON();
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  GenericSessionContext : public GenericEntryContext {
  public:
    GenericSessionContext(GenericEntryContext *ctx);

    antlr4::Token *name = nullptr;
    antlr4::tree::TerminalNode *VARIABLE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  GenericEntryContext* genericEntry();

  class  GenericSpecifierContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::TypeContext *typeContext = nullptr;
    std::vector<TypeContext *> subst;
    GenericSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LESS();
    antlr4::tree::TerminalNode *GREATER();
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericSpecifierContext* genericSpecifier();

  class  DefineTypeContext : public antlr4::ParserRuleContext {
  public:
    DefineTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    DefineTypeContext() = default;
    void copyFrom(DefineTypeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DefineStructContext : public DefineTypeContext {
  public:
    DefineStructContext(DefineTypeContext *ctx);

    antlr4::Token *name = nullptr;
    BismuthParser::StructCaseContext *structCaseContext = nullptr;
    std::vector<StructCaseContext *> cases;
    antlr4::tree::TerminalNode *DEFINE();
    antlr4::tree::TerminalNode *STRUCT();
    antlr4::tree::TerminalNode *LSQB();
    antlr4::tree::TerminalNode *RSQB();
    antlr4::tree::TerminalNode *VARIABLE();
    GenericTemplateContext *genericTemplate();
    std::vector<StructCaseContext *> structCase();
    StructCaseContext* structCase(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DefineEnumContext : public DefineTypeContext {
  public:
    DefineEnumContext(DefineTypeContext *ctx);

    antlr4::Token *name = nullptr;
    BismuthParser::TypeContext *typeContext = nullptr;
    std::vector<TypeContext *> cases;
    antlr4::tree::TerminalNode *DEFINE();
    antlr4::tree::TerminalNode *ENUM();
    antlr4::tree::TerminalNode *LSQB();
    antlr4::tree::TerminalNode *RSQB();
    antlr4::tree::TerminalNode *VARIABLE();
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    GenericTemplateContext *genericTemplate();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DefineProgramContext : public DefineTypeContext {
  public:
    DefineProgramContext(DefineTypeContext *ctx);

    antlr4::Token *name = nullptr;
    antlr4::Token *channelName = nullptr;
    BismuthParser::TypeContext *ty = nullptr;
    antlr4::tree::TerminalNode *DEFINE();
    antlr4::tree::TerminalNode *COLON();
    BlockContext *block();
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    TypeContext *type();
    GenericTemplateContext *genericTemplate();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DefineFunctionContext : public DefineTypeContext {
  public:
    DefineFunctionContext(DefineTypeContext *ctx);

    antlr4::Token *name = nullptr;
    BismuthParser::LambdaConstExprContext *lam = nullptr;
    antlr4::tree::TerminalNode *DEFINE();
    antlr4::tree::TerminalNode *FUNC();
    antlr4::tree::TerminalNode *VARIABLE();
    LambdaConstExprContext *lambdaConstExpr();
    GenericTemplateContext *genericTemplate();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  DefineTypeContext* defineType();

  class  ExternStatementContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;
    BismuthParser::ParameterListContext *paramList = nullptr;
    antlr4::Token *variadic = nullptr;
    BismuthParser::TypeContext *ret = nullptr;
    ExternStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXTERN();
    antlr4::tree::TerminalNode *FUNC();
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *ELLIPSIS();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
    ParameterListContext *parameterList();
    antlr4::tree::TerminalNode *VariadicParam();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExternStatementContext* externStatement();

  class  PathElementContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *id = nullptr;
    PathElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    GenericSpecifierContext *genericSpecifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PathElementContext* pathElement();

  class  PathContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::PathElementContext *pathElementContext = nullptr;
    std::vector<PathElementContext *> eles;
    PathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PathElementContext *> pathElement();
    PathElementContext* pathElement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PathContext* path();

  class  ImportStatementContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *alias = nullptr;
    ImportStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    PathContext *path();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *VARIABLE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportStatementContext* importStatement();

  class  Inv_argsContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::ExpressionContext *expressionContext = nullptr;
    std::vector<ExpressionContext *> args;
    Inv_argsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Inv_argsContext* inv_args();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpressionContext() = default;
    void copyFrom(ExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  AssignableIsPresentContext : public ExpressionContext {
  public:
    AssignableIsPresentContext(ExpressionContext *ctx);

    antlr4::Token *channel = nullptr;
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *VARIABLE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CopyExprContext : public ExpressionContext {
  public:
    CopyExprContext(ExpressionContext *ctx);

    BismuthParser::ExpressionContext *expr = nullptr;
    antlr4::tree::TerminalNode *COPY();
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IConstExprContext : public ExpressionContext {
  public:
    IConstExprContext(ExpressionContext *ctx);

    BismuthParser::IntegerValueContext *i = nullptr;
    IntegerValueContext *integerValue();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArrayAccessContext : public ExpressionContext {
  public:
    ArrayAccessContext(ExpressionContext *ctx);

    BismuthParser::ExpressionContext *expr = nullptr;
    BismuthParser::ExpressionContext *index = nullptr;
    antlr4::tree::TerminalNode *LBRC();
    antlr4::tree::TerminalNode *RBRC();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BinaryArithExprContext : public ExpressionContext {
  public:
    BinaryArithExprContext(ExpressionContext *ctx);

    BismuthParser::ExpressionContext *left = nullptr;
    antlr4::Token *op = nullptr;
    BismuthParser::ExpressionContext *right = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *MULTIPLY();
    antlr4::tree::TerminalNode *DIVIDE();
    antlr4::tree::TerminalNode *MOD();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    ShiftOpContext *shiftOp();
    antlr4::tree::TerminalNode *BIT_AND();
    antlr4::tree::TerminalNode *BIT_OR();
    antlr4::tree::TerminalNode *BIT_XOR();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IdentifierExprContext : public ExpressionContext {
  public:
    IdentifierExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *VARIABLE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CallExprContext : public ExpressionContext {
  public:
    CallExprContext(ExpressionContext *ctx);

    BismuthParser::ExpressionContext *expr = nullptr;
    Inv_argsContext *inv_args();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FieldAccessExprContext : public ExpressionContext {
  public:
    FieldAccessExprContext(ExpressionContext *ctx);

    BismuthParser::ExpressionContext *expr = nullptr;
    antlr4::Token *variableToken = nullptr;
    std::vector<antlr4::Token *> fields;
    ExpressionContext *expression();
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BinaryRelExprContext : public ExpressionContext {
  public:
    BinaryRelExprContext(ExpressionContext *ctx);

    BismuthParser::ExpressionContext *left = nullptr;
    antlr4::Token *op = nullptr;
    BismuthParser::ExpressionContext *right = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *LESS();
    antlr4::tree::TerminalNode *LESS_EQ();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *GREATER_EQ();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssignableRecvContext : public ExpressionContext {
  public:
    AssignableRecvContext(ExpressionContext *ctx);

    antlr4::Token *channel = nullptr;
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *VARIABLE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InitBoxContext : public ExpressionContext {
  public:
    InitBoxContext(ExpressionContext *ctx);

    BismuthParser::TypeContext *ty = nullptr;
    BismuthParser::ExpressionContext *expr = nullptr;
    antlr4::tree::TerminalNode *TYPE_BOX();
    antlr4::tree::TerminalNode *LESS();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    TypeContext *type();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LambdaExprContext : public ExpressionContext {
  public:
    LambdaExprContext(ExpressionContext *ctx);

    LambdaConstExprContext *lambdaConstExpr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AsChannelExprContext : public ExpressionContext {
  public:
    AsChannelExprContext(ExpressionContext *ctx);

    BismuthParser::ExpressionContext *expr = nullptr;
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SConstExprContext : public ExpressionContext {
  public:
    SConstExprContext(ExpressionContext *ctx);

    antlr4::Token *s = nullptr;
    antlr4::tree::TerminalNode *STRING();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnaryExprContext : public ExpressionContext {
  public:
    UnaryExprContext(ExpressionContext *ctx);

    antlr4::Token *op = nullptr;
    BismuthParser::ExpressionContext *ex = nullptr;
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *NOT();
    antlr4::tree::TerminalNode *BIT_NOT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssignableExecContext : public ExpressionContext {
  public:
    AssignableExecContext(ExpressionContext *ctx);

    BismuthParser::ExpressionContext *prog = nullptr;
    antlr4::tree::TerminalNode *EXEC();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EqExprContext : public ExpressionContext {
  public:
    EqExprContext(ExpressionContext *ctx);

    BismuthParser::ExpressionContext *left = nullptr;
    antlr4::Token *op = nullptr;
    BismuthParser::ExpressionContext *right = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *EQUAL();
    antlr4::tree::TerminalNode *NOT_EQUAL();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LogAndExprContext : public ExpressionContext {
  public:
    LogAndExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> exprs;
    BismuthParser::ExpressionContext *expressionContext = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LOG_AND();
    antlr4::tree::TerminalNode* LOG_AND(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LogOrExprContext : public ExpressionContext {
  public:
    LogOrExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> exprs;
    BismuthParser::ExpressionContext *expressionContext = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LOG_OR();
    antlr4::tree::TerminalNode* LOG_OR(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArrayExpressionContext : public ExpressionContext {
  public:
    ArrayExpressionContext(ExpressionContext *ctx);

    BismuthParser::ExpressionContext *expressionContext = nullptr;
    std::vector<ExpressionContext *> elements;
    antlr4::tree::TerminalNode *LBRC();
    antlr4::tree::TerminalNode *RBRC();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InitProductContext : public ExpressionContext {
  public:
    InitProductContext(ExpressionContext *ctx);

    BismuthParser::ExpressionContext *expressionContext = nullptr;
    std::vector<ExpressionContext *> exprs;
    PathContext *path();
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenExprContext : public ExpressionContext {
  public:
    ParenExprContext(ExpressionContext *ctx);

    BismuthParser::ExpressionContext *ex = nullptr;
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PathExprContext : public ExpressionContext {
  public:
    PathExprContext(ExpressionContext *ctx);

    PathContext *path();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DerefContext : public ExpressionContext {
  public:
    DerefContext(ExpressionContext *ctx);

    BismuthParser::ExpressionContext *expr = nullptr;
    antlr4::tree::TerminalNode *MULTIPLY();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BConstExprContext : public ExpressionContext {
  public:
    BConstExprContext(ExpressionContext *ctx);

    BooleanConstContext *booleanConst();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  LambdaConstExprContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::TypeContext *ret = nullptr;
    LambdaConstExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAR();
    ParameterListContext *parameterList();
    antlr4::tree::TerminalNode *RPAR();
    BlockContext *block();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LambdaConstExprContext* lambdaConstExpr();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::StatementContext *statementContext = nullptr;
    std::vector<StatementContext *> stmts;
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LSQB();
    antlr4::tree::TerminalNode *RSQB();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  ConditionContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::ExpressionContext *ex = nullptr;
    ConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionContext* condition();

  class  SelectAlternativeContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::ExpressionContext *check = nullptr;
    BismuthParser::StatementContext *eval = nullptr;
    SelectAlternativeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    ExpressionContext *expression();
    StatementContext *statement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectAlternativeContext* selectAlternative();

  class  MatchAlternativeContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::TypeContext *check = nullptr;
    antlr4::Token *name = nullptr;
    BismuthParser::StatementContext *eval = nullptr;
    MatchAlternativeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *VARIABLE();
    StatementContext *statement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MatchAlternativeContext* matchAlternative();

  class  ProtoAlternativeContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *lbl = nullptr;
    BismuthParser::ProtocolContext *check = nullptr;
    BismuthParser::StatementContext *eval = nullptr;
    ProtoAlternativeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    antlr4::tree::TerminalNode *VARIABLE();
    ProtocolContext *protocol();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProtoAlternativeContext* protoAlternative();

  class  ProtoElseContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::StatementContext *eval = nullptr;
    ProtoElseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ELSE();
    StatementContext *statement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProtoElseContext* protoElse();

  class  ParameterListContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::ParameterContext *parameterContext = nullptr;
    std::vector<ParameterContext *> params;
    ParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParameterContext *> parameter();
    ParameterContext* parameter(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterListContext* parameterList();

  class  ParameterContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::TypeContext *ty = nullptr;
    antlr4::Token *name = nullptr;
    ParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *VARIABLE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterContext* parameter();

  class  AssignmentContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *variableToken = nullptr;
    std::vector<antlr4::Token *> v;
    BismuthParser::ExpressionContext *a = nullptr;
    AssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *ASSIGN();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentContext* assignment();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StatementContext() = default;
    void copyFrom(StatementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MatchStatementContext : public StatementContext {
  public:
    MatchStatementContext(StatementContext *ctx);

    BismuthParser::ConditionContext *check = nullptr;
    BismuthParser::StatementContext *statementContext = nullptr;
    std::vector<StatementContext *> rest;
    antlr4::tree::TerminalNode *MATCH();
    antlr4::tree::TerminalNode *LSQB();
    antlr4::tree::TerminalNode *RSQB();
    ConditionContext *condition();
    std::vector<MatchAlternativeContext *> matchAlternative();
    MatchAlternativeContext* matchAlternative(size_t i);
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    std::vector<antlr4::tree::TerminalNode *> BIT_OR();
    antlr4::tree::TerminalNode* BIT_OR(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SkipStatementContext : public StatementContext {
  public:
    SkipStatementContext(StatementContext *ctx);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExitStatementContext : public StatementContext {
  public:
    ExitStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *EXIT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConditionalStatementContext : public StatementContext {
  public:
    ConditionalStatementContext(StatementContext *ctx);

    BismuthParser::ConditionContext *check = nullptr;
    BismuthParser::BlockContext *trueBlk = nullptr;
    BismuthParser::BlockContext *falseBlk = nullptr;
    BismuthParser::StatementContext *statementContext = nullptr;
    std::vector<StatementContext *> rest;
    antlr4::tree::TerminalNode *IF();
    ConditionContext *condition();
    std::vector<BlockContext *> block();
    BlockContext* block(size_t i);
    antlr4::tree::TerminalNode *ELSE();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ProgramProjectContext : public StatementContext {
  public:
    ProgramProjectContext(StatementContext *ctx);

    antlr4::Token *channel = nullptr;
    antlr4::Token *lbl = nullptr;
    BismuthParser::ProtocolContext *sel = nullptr;
    antlr4::tree::TerminalNode *LBRC();
    antlr4::tree::TerminalNode *RBRC();
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    ProtocolContext *protocol();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ProgramSendContext : public StatementContext {
  public:
    ProgramSendContext(StatementContext *ctx);

    antlr4::Token *channel = nullptr;
    BismuthParser::ExpressionContext *expr = nullptr;
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *VARIABLE();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ProgramCaseContext : public StatementContext {
  public:
    ProgramCaseContext(StatementContext *ctx);

    antlr4::Token *channel = nullptr;
    BismuthParser::ProtoAlternativeContext *protoAlternativeContext = nullptr;
    std::vector<ProtoAlternativeContext *> opts;
    BismuthParser::StatementContext *statementContext = nullptr;
    std::vector<StatementContext *> rest;
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *VARIABLE();
    std::vector<ProtoAlternativeContext *> protoAlternative();
    ProtoAlternativeContext* protoAlternative(size_t i);
    ProtoElseContext *protoElse();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    std::vector<antlr4::tree::TerminalNode *> BIT_OR();
    antlr4::tree::TerminalNode* BIT_OR(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BlockStatementContext : public StatementContext {
  public:
    BlockStatementContext(StatementContext *ctx);

    BlockContext *block();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ProgramLoopContext : public StatementContext {
  public:
    ProgramLoopContext(StatementContext *ctx);

    BismuthParser::ConditionContext *check = nullptr;
    antlr4::tree::TerminalNode *WHILE();
    BlockContext *block();
    ConditionContext *condition();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ProgramContractContext : public StatementContext {
  public:
    ProgramContractContext(StatementContext *ctx);

    antlr4::Token *channel = nullptr;
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ProgramCancelContext : public StatementContext {
  public:
    ProgramCancelContext(StatementContext *ctx);

    antlr4::Token *channel = nullptr;
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssignStatementContext : public StatementContext {
  public:
    AssignStatementContext(StatementContext *ctx);

    AssignmentStatementContext *assignmentStatement();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ProgramWeakenContext : public StatementContext {
  public:
    ProgramWeakenContext(StatementContext *ctx);

    antlr4::Token *channel = nullptr;
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ProgramAcceptContext : public StatementContext {
  public:
    ProgramAcceptContext(StatementContext *ctx);

    antlr4::Token *channel = nullptr;
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    BlockContext *block();
    antlr4::tree::TerminalNode *VARIABLE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SelectStatementContext : public StatementContext {
  public:
    SelectStatementContext(StatementContext *ctx);

    BismuthParser::SelectAlternativeContext *selectAlternativeContext = nullptr;
    std::vector<SelectAlternativeContext *> cases;
    BismuthParser::StatementContext *statementContext = nullptr;
    std::vector<StatementContext *> rest;
    antlr4::tree::TerminalNode *SELECT();
    antlr4::tree::TerminalNode *LSQB();
    antlr4::tree::TerminalNode *RSQB();
    std::vector<SelectAlternativeContext *> selectAlternative();
    SelectAlternativeContext* selectAlternative(size_t i);
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TypeDefContext : public StatementContext {
  public:
    TypeDefContext(StatementContext *ctx);

    DefineTypeContext *defineType();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ProgramCloseContext : public StatementContext {
  public:
    ProgramCloseContext(StatementContext *ctx);

    antlr4::Token *channel = nullptr;
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExpressionStatementContext : public StatementContext {
  public:
    ExpressionStatementContext(StatementContext *ctx);

    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ReturnStatementContext : public StatementContext {
  public:
    ReturnStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *RETURN();
    antlr4::tree::TerminalNode *SEMICOLON();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ForStatementContext : public StatementContext {
  public:
    ForStatementContext(StatementContext *ctx);

    BismuthParser::VariableDeclarationContext *decl = nullptr;
    BismuthParser::AssignmentStatementContext *assign = nullptr;
    BismuthParser::ConditionContext *check = nullptr;
    BismuthParser::StatementContext *expr = nullptr;
    BismuthParser::BlockContext *blk = nullptr;
    antlr4::tree::TerminalNode *LPAR();
    std::vector<antlr4::tree::TerminalNode *> SEMICOLON();
    antlr4::tree::TerminalNode* SEMICOLON(size_t i);
    antlr4::tree::TerminalNode *RPAR();
    ConditionContext *condition();
    StatementContext *statement();
    BlockContext *block();
    VariableDeclarationContext *variableDeclaration();
    AssignmentStatementContext *assignmentStatement();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ProgramAcceptWhileContext : public StatementContext {
  public:
    ProgramAcceptWhileContext(StatementContext *ctx);

    antlr4::Token *channel = nullptr;
    BismuthParser::ExpressionContext *ex = nullptr;
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAR();
    BlockContext *block();
    antlr4::tree::TerminalNode *VARIABLE();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VarDeclStatementContext : public StatementContext {
  public:
    VarDeclStatementContext(StatementContext *ctx);

    VariableDeclarationContext *variableDeclaration();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ProgramAcceptIfContext : public StatementContext {
  public:
    ProgramAcceptIfContext(StatementContext *ctx);

    antlr4::Token *channel = nullptr;
    BismuthParser::ExpressionContext *check = nullptr;
    BismuthParser::BlockContext *trueBlk = nullptr;
    BismuthParser::BlockContext *falseBlk = nullptr;
    BismuthParser::StatementContext *statementContext = nullptr;
    std::vector<StatementContext *> rest;
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *VARIABLE();
    ExpressionContext *expression();
    std::vector<BlockContext *> block();
    BlockContext* block(size_t i);
    antlr4::tree::TerminalNode *ELSE();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StatementContext* statement();

  class  AssignmentStatementContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::ExpressionContext *to = nullptr;
    BismuthParser::ExpressionContext *a = nullptr;
    AssignmentStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASSIGN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentStatementContext* assignmentStatement();

  class  VariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::TypeOrVarContext *ty = nullptr;
    BismuthParser::AssignmentContext *assignmentContext = nullptr;
    std::vector<AssignmentContext *> assignments;
    VariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeOrVarContext *typeOrVar();
    std::vector<AssignmentContext *> assignment();
    AssignmentContext* assignment(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableDeclarationContext* variableDeclaration();

  class  ShiftOpContext : public antlr4::ParserRuleContext {
  public:
    ShiftOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> GREATER();
    antlr4::tree::TerminalNode* GREATER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LESS();
    antlr4::tree::TerminalNode* LESS(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ShiftOpContext* shiftOp();

  class  TypeOrVarContext : public antlr4::ParserRuleContext {
  public:
    TypeOrVarContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *TYPE_VAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeOrVarContext* typeOrVar();

  class  ProtocolContext : public antlr4::ParserRuleContext {
  public:
    BismuthParser::SubProtocolContext *subProtocolContext = nullptr;
    std::vector<SubProtocolContext *> protos;
    ProtocolContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SubProtocolContext *> subProtocol();
    SubProtocolContext* subProtocol(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SEMICOLON();
    antlr4::tree::TerminalNode* SEMICOLON(size_t i);
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProtocolContext* protocol();

  class  SubProtocolContext : public antlr4::ParserRuleContext {
  public:
    SubProtocolContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    SubProtocolContext() = default;
    void copyFrom(SubProtocolContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  WnProtoContext : public SubProtocolContext {
  public:
    WnProtoContext(SubProtocolContext *ctx);

    BismuthParser::ProtocolContext *proto = nullptr;
    ProtocolContext *protocol();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CloseableProtoContext : public SubProtocolContext {
  public:
    CloseableProtoContext(SubProtocolContext *ctx);

    BismuthParser::ProtocolContext *proto = nullptr;
    antlr4::tree::TerminalNode *CLOSEABLE();
    antlr4::tree::TerminalNode *LESS();
    antlr4::tree::TerminalNode *GREATER();
    ProtocolContext *protocol();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SendTypeContext : public SubProtocolContext {
  public:
    SendTypeContext(SubProtocolContext *ctx);

    BismuthParser::TypeContext *ty = nullptr;
    antlr4::tree::TerminalNode *MINUS();
    TypeContext *type();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IntChoiceProtoContext : public SubProtocolContext {
  public:
    IntChoiceProtoContext(SubProtocolContext *ctx);

    BismuthParser::ProtoBranchContext *protoBranchContext = nullptr;
    std::vector<ProtoBranchContext *> protoOpts;
    antlr4::tree::TerminalNode *INTERNAL_CHOICE();
    antlr4::tree::TerminalNode *LESS();
    antlr4::tree::TerminalNode *GREATER();
    std::vector<ProtoBranchContext *> protoBranch();
    ProtoBranchContext* protoBranch(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RecvTypeContext : public SubProtocolContext {
  public:
    RecvTypeContext(SubProtocolContext *ctx);

    BismuthParser::TypeContext *ty = nullptr;
    antlr4::tree::TerminalNode *PLUS();
    TypeContext *type();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OcProtoContext : public SubProtocolContext {
  public:
    OcProtoContext(SubProtocolContext *ctx);

    BismuthParser::ProtocolContext *proto = nullptr;
    antlr4::tree::TerminalNode *NOT();
    ProtocolContext *protocol();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExtChoiceProtoContext : public SubProtocolContext {
  public:
    ExtChoiceProtoContext(SubProtocolContext *ctx);

    BismuthParser::ProtoBranchContext *protoBranchContext = nullptr;
    std::vector<ProtoBranchContext *> protoOpts;
    antlr4::tree::TerminalNode *EXTERNAL_CHOICE();
    antlr4::tree::TerminalNode *LESS();
    antlr4::tree::TerminalNode *GREATER();
    std::vector<ProtoBranchContext *> protoBranch();
    ProtoBranchContext* protoBranch(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  SubProtocolContext* subProtocol();

  class  ProtoBranchContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *lbl = nullptr;
    ProtoBranchContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ProtocolContext *protocol();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *VARIABLE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProtoBranchContext* protoBranch();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TypeContext() = default;
    void copyFrom(TypeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LambdaTypeContext : public TypeContext {
  public:
    LambdaTypeContext(TypeContext *ctx);

    std::vector<TypeContext *> paramTypes;
    BismuthParser::TypeContext *typeContext = nullptr;
    BismuthParser::TypeContext *returnType = nullptr;
    std::vector<antlr4::tree::TerminalNode *> LPAR();
    antlr4::tree::TerminalNode* LPAR(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RPAR();
    antlr4::tree::TerminalNode* RPAR(size_t i);
    antlr4::tree::TerminalNode *MAPS_TO();
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CustomTypeContext : public TypeContext {
  public:
    CustomTypeContext(TypeContext *ctx);

    PathContext *path();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArrayTypeContext : public TypeContext {
  public:
    ArrayTypeContext(TypeContext *ctx);

    BismuthParser::TypeContext *ty = nullptr;
    antlr4::Token *len = nullptr;
    antlr4::tree::TerminalNode *LBRC();
    antlr4::tree::TerminalNode *RBRC();
    TypeContext *type();
    antlr4::tree::TerminalNode *DEC_LITERAL();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DynArrayTypeContext : public TypeContext {
  public:
    DynArrayTypeContext(TypeContext *ctx);

    BismuthParser::TypeContext *ty = nullptr;
    antlr4::tree::TerminalNode *LBRC();
    antlr4::tree::TerminalNode *RBRC();
    TypeContext *type();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SumTypeContext : public TypeContext {
  public:
    SumTypeContext(TypeContext *ctx);

    antlr4::tree::TerminalNode *LPAR();
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    antlr4::tree::TerminalNode *RPAR();
    std::vector<antlr4::tree::TerminalNode *> PLUS();
    antlr4::tree::TerminalNode* PLUS(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BaseTypeContext : public TypeContext {
  public:
    BaseTypeContext(TypeContext *ctx);

    antlr4::Token *ty = nullptr;
    antlr4::tree::TerminalNode *TYPE_INT();
    antlr4::tree::TerminalNode *TYPE_I32();
    antlr4::tree::TerminalNode *TYPE_BOOL();
    antlr4::tree::TerminalNode *TYPE_STR();
    antlr4::tree::TerminalNode *TYPE_UNIT();
    antlr4::tree::TerminalNode *TYPE_U32();
    antlr4::tree::TerminalNode *TYPE_I64();
    antlr4::tree::TerminalNode *TYPE_U64();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TemplatedTypeContext : public TypeContext {
  public:
    TemplatedTypeContext(TypeContext *ctx);

    BismuthParser::TypeContext *ty = nullptr;
    GenericSpecifierContext *genericSpecifier();
    TypeContext *type();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ProgramTypeContext : public TypeContext {
  public:
    ProgramTypeContext(TypeContext *ctx);

    BismuthParser::ProtocolContext *proto = nullptr;
    antlr4::tree::TerminalNode *TYPE_PROGRAM();
    antlr4::tree::TerminalNode *LESS();
    antlr4::tree::TerminalNode *GREATER();
    ProtocolContext *protocol();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ChannelTypeContext : public TypeContext {
  public:
    ChannelTypeContext(TypeContext *ctx);

    BismuthParser::ProtocolContext *proto = nullptr;
    antlr4::tree::TerminalNode *TYPE_CHANNEL();
    antlr4::tree::TerminalNode *LESS();
    antlr4::tree::TerminalNode *GREATER();
    ProtocolContext *protocol();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BoxTypeContext : public TypeContext {
  public:
    BoxTypeContext(TypeContext *ctx);

    BismuthParser::TypeContext *ty = nullptr;
    antlr4::tree::TerminalNode *TYPE_BOX();
    antlr4::tree::TerminalNode *LESS();
    antlr4::tree::TerminalNode *GREATER();
    TypeContext *type();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TypeContext* type();
  TypeContext* type(int precedence);
  class  IntegerValueContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *ty = nullptr;
    IntegerValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DEC_LITERAL();
    antlr4::tree::TerminalNode *HEX_LITERAL();
    antlr4::tree::TerminalNode *BIN_LITERAL();
    antlr4::tree::TerminalNode *TYPE_I32();
    antlr4::tree::TerminalNode *TYPE_U32();
    antlr4::tree::TerminalNode *TYPE_I64();
    antlr4::tree::TerminalNode *TYPE_U64();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntegerValueContext* integerValue();

  class  BooleanConstContext : public antlr4::ParserRuleContext {
  public:
    BooleanConstContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *FALSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BooleanConstContext* booleanConst();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);
  bool typeSempred(TypeContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

