#pragma once

#include "Symbol.h" //Should give us symbols and yyues...
#include <variant>
#include <functional> // std::function

#include "MacroUtils.h"


using namespace std;
using llvm::Value;

// TODO: HAVE COMPILER ADD COMMENTS TO DOCUMENT COMPLEX TYPES?
//
template<typename T, typename R>
class Visitor;

template<typename T>
class AnyVisitor;

class VisitorBase {
  public:
    virtual ~VisitorBase() {}
};

class VisitableBase {
  public:
    virtual std::any Nuaccept_any(VisitorBase&) = 0; // const = 0;
    virtual ~VisitableBase() {}
};

template<typename I>
class Visitable : public VisitableBase {
  public:
    std::any Nuaccept_any(VisitorBase& v) override { // const override
      WRAPPED_DYNAMIC_CAST(MACRO_ARG(AnyVisitor<I> *), visitor, &v);
      WRAPPED_DYNAMIC_CAST(MACRO_ARG(I*), castedThis, this);
      I& ref = *castedThis;
      return visitor->visit_any(ref); // const I&
    }

    template<typename R>
    R Nuaccept(Visitor<I, R> & visitor) { // WAS CONST
      WRAPPED_DYNAMIC_CAST(MACRO_ARG(I*), castedThis, this);
      I& ref = *castedThis;
        return visitor.visit(ref); // const I&
    }
};

template<typename T>
class AnyVisitor : public virtual VisitorBase {
  public:
    virtual std::any visit_any(T& t) = 0; // const T&
};

template<typename T, typename R>
class Visitor : public virtual AnyVisitor<T> {
  public:
    virtual R visit_typed(T& t) = 0; // const T&

    virtual std::any visit_any(T& t) override { // const T&
      return visit_typed(t);
    }

    virtual R visit(T& t) { // const T&
      return any_cast<R>(t.Nuaccept_any(*this));
    }
};
// class TypedASTVisitor;


class ProtocolOpNode
{
private:
    bool inCloseable;

public:
    ProtocolOpNode(bool _inCloseable) : inCloseable(_inCloseable)
    {}

    bool isInCloseable() const { return inCloseable; }
};

class TypedNode// : public Visitable<TypedNode>
{
public:
    antlr4::Token *token; // Location of node
    TypedNode(antlr4::Token *tok) : token(tok) {}

    virtual ~TypedNode() = default;

    virtual const Type *getType() = 0;

    virtual std::string toString() const = 0;

//    virtual std::any accept(TypedASTVisitor &a) = 0;
    virtual std::any accept_any(VisitorBase&) = 0;

    antlr4::Token *getStart() { return token; }

    template<typename R>
    R accept(VisitorBase& visitor){
      return any_cast<R>(accept_any(visitor));
    }

};

class DefinitionNode : public TypedNode
{
private:
    DefinitionSymbol * symbol;

public:
    virtual ~DefinitionNode() = default;
    DefinitionNode(DefinitionSymbol * s, antlr4::Token *tok) : TypedNode(tok), symbol(s) {}

    DefinitionSymbol * getSymbol() { return symbol; }

    VisibilityModifier getVisibility() { return symbol->getVisibility(); }
};

// From C++ Documentation for visitors
template <class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

class TSelectAlternativeNode;
class TSelectStatementNode;
class TBlockNode;

class TLambdaConstNode;
class TProgramDefNode;
class TConditionalStatementNode;
class TReturnNode;
class TProgramSendNode;
class TProgramRecvNode;
class TProgramIsPresetNode;
class TProgramContractNode;
class TProgramWeakenNode;
class TProgramCancelNode;
class TProgramExecNode;
class TProgramAcceptNode;
class TProgramAcceptWhileNode;
class TProgramAcceptIfNode;
class TDefineEnumNode;
class TDefineTemplateNode;
class TDefineStructNode;
class TDefineTraitNode;
class TInitProductNode;
class TArrayRValue;
class TInitBoxNode;
class TDerefBoxNode;
class TWhileLoopNode;
class TExternNode;
class TInvocationNode;
class TFieldAccessNode;
class TPathNode;
class TArrayAccessNode;
class TDynArrayAccessNode;
class TAssignNode;
class TBinaryRelNode;
class TBinaryArithNode;
class TEqExprNode;
class TUnaryExprNode;
class TLogAndExprNode;
class TLogOrExprNode;
class TStringConstNode;
class TBooleanConstNode;
class TInt32ConstExprNode;
class TInt64ConstExprNode;
class TIntU32ConstExprNode;
class TIntU64ConstExprNode;
class TNumConstExprNode; // For numbers we don't yet know the size of
class TCompilationUnitNode;

class TVarDeclNode;
class TMatchStatementNode;
class TExitNode;

class TChannelCaseStatementNode;
class TProgramProjectNode;

class TExprCopyNode;

class TAsChannelNode;

class CompCodeWrapper;

class TIdentifier;

template<typename R>
class NuASTVisitor : public Visitor<TSelectStatementNode, R>
                   , public Visitor<TBlockNode, R>
                   , public Visitor<TLambdaConstNode, R>
                   , public Visitor<TProgramDefNode, R>
                   , public Visitor<TConditionalStatementNode, R>
                   , public Visitor<TReturnNode, R>
                   , public Visitor<TProgramSendNode, R>
                   , public Visitor<TProgramRecvNode, R>
                   , public Visitor<TProgramIsPresetNode, R>
                   , public Visitor<TProgramContractNode, R>
                   , public Visitor<TProgramWeakenNode, R>
                   , public Visitor<TProgramCancelNode, R>
                   , public Visitor<TProgramExecNode, R>
                   , public Visitor<TProgramAcceptNode, R>
                   , public Visitor<TProgramAcceptWhileNode, R>
                  , public Visitor<TProgramAcceptIfNode, R>
                    , public Visitor<TDefineEnumNode, R>
                    , public Visitor<TDefineStructNode, R>
                    , public Visitor<TDefineTraitNode, R>
                    , public Visitor<TDefineTemplateNode, R>
                    , public Visitor<TInitProductNode, R>
                    , public Visitor<TArrayRValue, R>
                    , public Visitor<TInitBoxNode, R>
                    , public Visitor<TDerefBoxNode, R>
                    , public Visitor<TWhileLoopNode, R>
                    , public Visitor<TExternNode, R>
                    , public Visitor<TInvocationNode, R>
                    , public Visitor<TFieldAccessNode, R>
                    , public Visitor<TIdentifier, R>
                    , public Visitor<TPathNode, R>
                    , public Visitor<TArrayAccessNode, R>
                    , public Visitor<TDynArrayAccessNode, R>
                    , public Visitor<TAssignNode, R>
                    , public Visitor<TBinaryRelNode, R>
                    , public Visitor<TBinaryArithNode, R>
                    , public Visitor<TEqExprNode, R>
                    , public Visitor<TUnaryExprNode, R>
                    , public Visitor<TLogAndExprNode, R>
                    , public Visitor<TLogOrExprNode, R>
                    , public Visitor<TStringConstNode, R>
                    , public Visitor<TBooleanConstNode, R>
                    , public Visitor<TInt32ConstExprNode, R>
                    , public Visitor<TInt64ConstExprNode, R>
                    , public Visitor<TIntU32ConstExprNode, R>
                    , public Visitor<TIntU64ConstExprNode, R>
                    , public Visitor<TNumConstExprNode, R>
                    , public Visitor<TCompilationUnitNode, R>
                    , public Visitor<TVarDeclNode, R>
                    , public Visitor<TMatchStatementNode, R>
                    , public Visitor<TExitNode, R>
                    , public Visitor<TChannelCaseStatementNode, R>
                    , public Visitor<TProgramProjectNode, R>
                    , public Visitor<TExprCopyNode, R>
                    , public Visitor<TAsChannelNode, R>
                   ,public Visitor<CompCodeWrapper, R>
{
public:
  R visit_recur(TypedNode & tn) { return any_cast<R>(tn.accept_any(*this)); }
};
class TSelectAlternativeNode : public TypedNode, public Visitable<TSelectAlternativeNode>
{
public:
    TypedNode *check;
    TypedNode *eval;

    TSelectAlternativeNode(TypedNode *c, TypedNode *e, antlr4::Token *tok) : TypedNode(tok)
    {
        check = c;
        eval = e;
    }

    const TypeUnit *getType() override { return Types::UNIT; }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }

    std::string toString() const override {
        return "SEL ALT";
    }
};

class TSelectStatementNode : public TypedNode, public Visitable<TSelectStatementNode>
{
public:
    vector<TSelectAlternativeNode *> nodes;
    vector<TypedNode *> post;

    TSelectStatementNode(antlr4::Token *tok, vector<TSelectAlternativeNode *> n, vector<TypedNode *> p) : TypedNode(tok)
    {
        nodes = n;
        post = p;
    }

    const TypeUnit *getType() override { return Types::UNIT; }
    virtual std::any accept_any(VisitorBase &a) override { return this->Nuaccept_any(a); }

    std::string toString() const override {
        return "SEL STMT NODE";
    }
};

class TBlockNode : public TypedNode, public Visitable<TBlockNode>
{
public:
    vector<TypedNode *> exprs;

    TBlockNode(vector<TypedNode *> e, antlr4::Token *tok) : TypedNode(tok)
    {
        exprs = e;
    }

    vector<TypedNode *> getExprs() { return exprs; }

    const TypeUnit *getType() override { return Types::UNIT; } // PLAN: Change this to allow for more functional style?
    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }

    std::string toString() const override {
        return "BLK NODE";
    }
};

class ParameterNode
{
public:
    const Type *type;
    string name;

    ParameterNode(const Type *t, string n) : type(t), name(n) {}
};

typedef vector<ParameterNode> ParameterListNode;

class TLambdaConstNode : public DefinitionNode, public Visitable<TLambdaConstNode>
{
    // private:

public:
    vector<Symbol *> paramSymbols;
    const Type *retType;
    TBlockNode *block;
    const TypeFunc *type;

    TLambdaConstNode(DefinitionSymbol * sym, vector<Symbol *> p, const Type *r, TBlockNode *b, antlr4::Token *tok) : DefinitionNode(sym, tok)
    {
        // paramList = p;
        paramSymbols = p;
        retType = r;
        block = b;


        vector<const Type *> paramTypes;

        for (Symbol *p : paramSymbols)
        {
            paramTypes.push_back(p->getType());
        }

        // FIXME: REMOVE AS ALREADY CALCULATED?
        type = new TypeFunc(paramTypes, retType);
    }

    const TypeFunc *getType() override
    {
        return type;
    }

    std::string toString() const override {
        return "LAMBDA CONST";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TProgramDefNode : public DefinitionNode, public Visitable<TProgramDefNode>
{
private:
    const TypeProgram *type;

public:
    Symbol *channelSymbol;
    // TypeChannel * channelType;
    TBlockNode *block;

    TProgramDefNode(DefinitionSymbol * sym,  Symbol *cn, TBlockNode *b, const TypeProgram *ty, antlr4::Token *tok) : DefinitionNode(sym, tok)
    {
        channelSymbol = cn;
        // channelType = ct;
        block = b;
        type = ty;
    }

    const TypeProgram *getType() override
    {
        return type;
    }

    std::string toString() const override {
        return "PROG DEF";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TConditionalStatementNode : public TypedNode, public Visitable<TConditionalStatementNode>
{
public:
    TypedNode *cond;
    TBlockNode *trueBlk;
    std::optional<TBlockNode *> falseOpt;

    std::vector<TypedNode *> post;

    TConditionalStatementNode(antlr4::Token *tok, TypedNode *c, TBlockNode *t, std::vector<TypedNode *> p, std::optional<TBlockNode *> f = {}) : TypedNode(tok)
    {
        cond = c;
        trueBlk = t;
        falseOpt = f;
        post = p;
    }

    const TypeUnit *getType() override { return Types::UNIT; } // PLAN: Change this to allow for a more functional style syntax?

    std::string toString() const override {
        return "COND STATEMENT NODE";
    }
    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TReturnNode : public TypedNode, public Visitable<TReturnNode>
{
public:
    // First is the actual type
    optional<pair<const Type *, TypedNode *>> expr;

    TReturnNode(antlr4::Token *tok, optional<pair<const Type *, TypedNode *>> e = {}) : TypedNode(tok)
    {
        expr = e;
    }

    const TypeUnit *getType() override { return Types::UNIT; }

    std::string toString() const override {
        return "RETURN NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TExitNode : public TypedNode, public Visitable<TExitNode>
{
public:
    TExitNode(antlr4::Token *tok) : TypedNode(tok)
    {
    }

    const TypeUnit *getType() override { return Types::UNIT; } // FIXME: DO BETTER

    std::string toString() const override {
        return "EXIT NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TProgramSendNode : public TypedNode, public ProtocolOpNode, public Visitable<TProgramSendNode>
{
public:
    Symbol *sym;
    TypedNode *expr;
    const Type *lType; // Tracks type send expects. Needed for sums

    TProgramSendNode(Symbol *s, bool inCloseable, TypedNode *e, const Type *l, antlr4::Token *tok) : TypedNode(tok), ProtocolOpNode(inCloseable)
    {
        sym = s;
        expr = e;
        lType = l;
    }

    const TypeUnit *getType() override { return Types::UNIT; }

    std::string toString() const override {
        return "SEND NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TProgramRecvNode : public TypedNode, public ProtocolOpNode, public Visitable<TProgramRecvNode>
{
public:
    Symbol *sym;
    RecvMetadata meta;

    TProgramRecvNode(Symbol *s, RecvMetadata m, bool iC, antlr4::Token *tok) : TypedNode(tok), ProtocolOpNode(iC), meta(m)
    {
        sym = s;
    }

    const Type *getType() override {
        if(meta.actingType) return meta.actingType.value();
        return meta.protocolType;
        // return meta.actingType.value_or(meta.protocolType);
     }

    std::string toString() const override {
        return "RECV NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};


class TProgramIsPresetNode : public TypedNode, public ProtocolOpNode, public Visitable<TProgramIsPresetNode>
{
public:
    Symbol *sym;

    TProgramIsPresetNode(Symbol *s, bool inCloseable, antlr4::Token *tok) : TypedNode(tok), ProtocolOpNode(inCloseable)
    {
        sym = s;
    }

    const Type *getType() override { return Types::DYN_BOOL; }

    std::string toString() const override {
        return "IS PRESENT NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};
class TProgramContractNode : public TypedNode, public Visitable<TProgramContractNode>
{
public:
    Symbol *sym;

    TProgramContractNode(Symbol *s, antlr4::Token *tok) : TypedNode(tok)
    {
        sym = s;
    }

    const TypeUnit *getType() override { return Types::UNIT; }

    std::string toString() const override {
        return "CONTRACT NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TProgramWeakenNode : public TypedNode, public Visitable<TProgramWeakenNode> // FIXME: COMBINE THIS WITH PREV AND USE ENUM FOR OP?
{
public:
    Symbol *sym;

    TProgramWeakenNode(Symbol *s, antlr4::Token *tok) : TypedNode(tok)
    {
        sym = s;
    }

    const TypeUnit *getType() override { return Types::UNIT; }

    std::string toString() const override {
        return "WEAKEN NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};


class TProgramCancelNode : public TypedNode, public Visitable<TProgramCancelNode> // FIXME: COMBINE THIS WITH PREV AND USE ENUM FOR OP?
{
public:
    Symbol *sym;
    unsigned int closeNumber;

    TProgramCancelNode(Symbol *s, unsigned int cn, antlr4::Token *tok) : TypedNode(tok)
    {
        sym = s;
        closeNumber = cn;
    }

    const TypeUnit *getType() override { return Types::UNIT; }

    std::string toString() const override {
        return "CANCEL NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TProgramExecNode : public TypedNode, public Visitable<TProgramExecNode>
{
public:
    TypedNode *prog;
    TypeChannel *chanType;

    TProgramExecNode(TypedNode *p, TypeChannel *c, antlr4::Token *tok) : TypedNode(tok)
    {
        prog = p;
        chanType = c;
    }

    const TypeChannel *getType() override { return chanType; }

    std::string toString() const override {
        return "EXEC NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TProgramAcceptNode : public TypedNode, public ProtocolOpNode, public Visitable<TProgramAcceptNode>
{
public:
    Symbol *sym;
    TBlockNode *blk;

    TProgramAcceptNode(Symbol *s, bool inCloseable, TBlockNode *b, antlr4::Token *tok) : TypedNode(tok), ProtocolOpNode(inCloseable)
    {
        sym = s;
        blk = b;
    }

    const TypeUnit *getType() override { return Types::UNIT; }

    std::string toString() const override {
        return "ACCEPT NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TProgramAcceptWhileNode : public TypedNode, public ProtocolOpNode, public Visitable<TProgramAcceptWhileNode>
{
public:
    Symbol *sym;
    TypedNode *cond;
    TBlockNode *blk;

    TProgramAcceptWhileNode(Symbol *s, bool inCloseable, TypedNode *c, TBlockNode *b, antlr4::Token *tok) : TypedNode(tok), ProtocolOpNode(inCloseable)
    {
        sym = s;
        cond = c;
        blk = b;
    }

    const TypeUnit *getType() override { return Types::UNIT; }

    std::string toString() const override {
        return "ACCEPT WHILE NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};


class TProgramAcceptIfNode : public TypedNode, public ProtocolOpNode, public Visitable<TProgramAcceptIfNode>
{
public:
    Symbol *sym;
    TypedNode *cond;
    TBlockNode *trueBlk;
    std::optional<TBlockNode *> falseOpt;
    std::vector<TypedNode *> post;

    TProgramAcceptIfNode(antlr4::Token *tok, bool inCloseable, Symbol *s, TypedNode *c, TBlockNode *t, std::vector<TypedNode *> p, std::optional<TBlockNode *> f = {}) : TypedNode(tok), ProtocolOpNode(inCloseable)
    {
        sym = s;
        cond = c;
        trueBlk = t;
        post = p;
        falseOpt = f;
    }

    const TypeUnit *getType() override { return Types::UNIT; }

    std::string toString() const override {
        return "ACCEPT IF NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TDefineEnumNode : public DefinitionNode, public Visitable<TDefineEnumNode>
{
public:
    const TypeSum *sum;

    TDefineEnumNode(DefinitionSymbol * sym, const TypeSum *s, antlr4::Token *tok) : DefinitionNode(sym, tok)
    {
        sum = s;
    }


    std::string toString() const override {
        return "DEF ENUM NODE";
    }

    const TypeUnit *getType() override { return Types::UNIT; }
    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};


class TDefineTemplateNode : public DefinitionNode, public Visitable<TDefineTemplateNode>
{
private:
    const TypeTemplate * type; // Used to figure out what versions we need to generate
    DefinitionNode * templatedNodes;
    // TypedNode * templatedNodes;

    // TODO track templated names generated?

public:
    TDefineTemplateNode(DefinitionSymbol * sym, const TypeTemplate * t, DefinitionNode * n, antlr4::Token *tok) : DefinitionNode(sym, tok), type(t), templatedNodes(n) //t->toString(DisplayMode::C_STYLE), tok), type(t), templatedNodes(n)
    {}

    std::string toString() const override { return "DEF TEMPLATE NODE"; }

    const TypeTemplate * getType() override { return type; }
    DefinitionNode * getTemplatedNodes() { return templatedNodes; }
    // TypedNode * getTemplatedNodes() { return templatedNodes; }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TDefineStructNode : public DefinitionNode, public Visitable<TDefineStructNode>
{
public:
    const TypeStruct *product;

    TDefineStructNode(DefinitionSymbol * sym, const TypeStruct *p, antlr4::Token *tok) : DefinitionNode(sym, tok)
    {
        product = p;
    }

    const TypeUnit *getType() override { return Types::UNIT; }

    std::string toString() const override {
        return "DEF STRUCT";
    }


    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TInitProductNode : public TypedNode, public Visitable<TInitProductNode>
{
public:
    const TypeStruct *product;
    vector<TypedNode *> exprs;

    TInitProductNode(const TypeStruct *p, vector<TypedNode *> e, antlr4::Token *tok) : TypedNode(tok)
    {
        product = p;
        exprs = e;
    }

    const TypeStruct *getType() override { return product; }

    std::string toString() const override {
        return "INIT PRODUCT";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};


class TArrayRValue : public TypedNode, public Visitable<TArrayRValue>
{
public:
    std::variant<const TypeArray *, const TypeDynArray *> type;
    vector<TypedNode *> exprs;

    TArrayRValue(const TypeArray *p, vector<TypedNode *> e, antlr4::Token *tok) : TypedNode(tok)
    {
        type = p;
        exprs = e;
    }

    TArrayRValue(const TypeDynArray *p, vector<TypedNode *> e, antlr4::Token *tok) : TypedNode(tok)
    {
        type = p;
        exprs = e;
    }

    const Type *getType() override {
        // return type;  // Wish we could do this
        if(std::holds_alternative<const TypeArray *>(type))
            return std::get<const TypeArray *>(type);
        return std::get<const TypeDynArray*>(type);
    }

    std::variant<const TypeArray *, const TypeDynArray*> getTypeVariant() { return type; }

    std::string toString() const override {
        return "ARRAY RVALUE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TInitBoxNode : public TypedNode, public Visitable<TInitBoxNode>
{
public:
    const TypeBox *boxType;
    TypedNode * expr;

    TInitBoxNode(const TypeBox *b, TypedNode * e, antlr4::Token *tok) : TypedNode(tok)
    {
        boxType = b;
        expr = e;
    }

    std::string toString() const override {
        return "INIT BOX";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }

    const TypeBox *getType() override { return boxType; }
};

class TDerefBoxNode : public TypedNode, public Visitable<TDerefBoxNode>
{
public:
    const TypeBox *boxType;
    TypedNode * expr;
    bool is_rvalue;

    TDerefBoxNode(const TypeBox *b, TypedNode * e, bool rv, antlr4::Token *tok) : TypedNode(tok)
    {
        boxType = b;
        expr = e;
        is_rvalue = rv;
    }

    std::string toString() const override {
        return "Deref BOX";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }

    // FIXME: why is this innerType? shouldnt that be separate?
    const Type *getType() override { return boxType->getInnerType(); }
};

class TWhileLoopNode : public TypedNode, public Visitable<TWhileLoopNode>
{
public:
    TypedNode *cond;
    TBlockNode *blk;

    TWhileLoopNode(TypedNode *c, TBlockNode *t, antlr4::Token *tok) : TypedNode(tok)
    {
        cond = c;
        blk = t;
    }

    const TypeUnit *getType() override { return Types::UNIT; }

    std::string toString() const override {
        return "WHILE LOOP";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TExternNode : public TypedNode, public Visitable<TExternNode>
{
private:
    Symbol *sym;
    const TypeFunc *ty; // FIXME: isn't REALLY NEEDED EXCEPT FOR MAKING CASTS EASIER

public:
    TExternNode(Symbol * s, TypeFunc * func, antlr4::Token *tok) : TypedNode(tok), sym(s), ty(func)
    {}

    const TypeFunc *getType() override
    {
        return ty;
    }

    std::string toString() const override {
        return "EXTERN NODE";
    }

    Symbol *getSymbol() { return sym; } // WHY AREN'T THINGS LIKE THIS CONST?
    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TInvocationNode : public TypedNode, public Visitable<TInvocationNode>
{
public:
    TypedNode *fn;
    vector<TypedNode *> args;
    vector<const Type *> paramType; // Used for sums

    TInvocationNode(TypedNode *f, vector<TypedNode *> a, vector<const Type *> p, antlr4::Token *tok) : TypedNode(tok)
    {
        fn = f;
        args = a;

        paramType = p;
    }

    const TypeFunc* getFuncType()
    {
        return dynamic_cast<const TypeFunc *>(fn->getType());
    }

    const Type *getType() override
    {
        return getFuncType()->getReturnType();
    }

    std::string toString() const override {
        return "INVOKE NODE " + fn->toString();
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};


class TPathNode: public TypedNode, public Visitable<TPathNode>
{
public:
    // std::variant<Symbol *, const NameableType *> var; //const TypeProgram *, const TypeFunc *, const TypeStruct *, const TypeSum *> var;
    const Type * ty;
    bool is_rvalue;

public:
    TPathNode(antlr4::Token *tok,
            //   std::variant<Symbol *, const NameableType *> v,
                const Type * t,
                bool rv)
        : TypedNode(tok)
        , ty(t)
        , is_rvalue(rv)
    {
    }

    const Type *getType() override {
        return ty;
    //    return std::visit(overloaded{[](Symbol * sym)
    //             { return sym->getType(); },
    //             [](const NameableType * nt)
    //             { return (const Type *) nt; }},
    //             var);
    }

    std::string toString() const override {
        return "PATH NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TIdentifier : public TypedNode, public Visitable<TIdentifier>
{
private:
    Symbol * sym; // Variant with this + Nameable type?
    bool rvalue;

public:

    TIdentifier(antlr4::Token *tok,
                Symbol * s,
                bool rv)
        : TypedNode(tok)
        , sym(s)
        , rvalue(rv)
    {}

    Symbol * getSymbol() { return sym; }
    const Type *getType() override { return sym->getType(); }

    bool isRValue() { return rvalue; }

    std::string toString() const override {
        return "IDENTIFIER  NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};


class TFieldAccessNode : public TypedNode, public Visitable<TFieldAccessNode>
{
private:
    TypedNode * expr;
    const Type * resultType;


public:
    bool is_rvalue;
    vector<pair<string, const Type *>> accesses;

    TFieldAccessNode(antlr4::Token *tok, TypedNode * e, bool rv, vector<pair<string, const Type *>> r = {})
        : TypedNode(tok)
        , expr(e)
        , is_rvalue(rv)
        , accesses(r)
    {
        // FIXME: assert r is not empty! It cant be by syntax, but still. This is a potential source of errors
        resultType = r.at(r.size() - 1).second;
    }

    const Type *getType() override { return resultType; }

    const Type * getResultantType() { return resultType; }

    // const Type * getSymbolType() { return id->getType(); }
    const Type * getExprType() { return expr->getType(); }

    TypedNode * getExpr() { return expr; }

    std::string toString() const override {
        return "FIELD ACCESS NODE "; // + symbol->toString();
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};


class TArrayAccessNode : public TypedNode, public Visitable<TArrayAccessNode>
{
public:
    TypedNode *expr;
    TypedNode *indexExpr;
    bool is_rvalue;

    TArrayAccessNode(TypedNode *e, TypedNode *i, bool r, antlr4::Token *tok) : TypedNode(tok)
    {
        expr = e;
        indexExpr = i;
        is_rvalue = r;
    }

    const TypeArray * getArrayType() {
        return dynamic_cast<const TypeArray *>(expr->getType()); // FIXME: POTENTIAL ERROR?
    }

    // The stored type of the array
    const Type * getLValueType()
    {
        return getArrayType()->getValueType();
    }

    // TODO: allow for modulo get so that way we can access fields more directly?
    const Type *getType() override
    {
        const Type * arrayType = getLValueType();

        if(!is_rvalue)
        {
            return arrayType;
        }

        std::set<const Type *, TypeCompare> cases = {Types::UNIT, arrayType};
        return new TypeSum(cases);
    }

    const TypeSum* getRValueType() {
        std::set<const Type *, TypeCompare> cases = {Types::UNIT, getLValueType()};
        return new TypeSum(cases);
    }

    uint32_t length() const {
        return dynamic_cast<const TypeArray *>(expr->getType())->getLength();
    }

    std::string toString() const override {
        return "Array Access Node";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TDynArrayAccessNode : public TypedNode, public Visitable<TDynArrayAccessNode>
{
public:
    TypedNode *expr;
    TypedNode *indexExpr;
    bool is_rvalue;

    TDynArrayAccessNode(TypedNode *e, TypedNode *i, bool r, antlr4::Token *tok) : TypedNode(tok)
    {
        expr = e;
        indexExpr = i;
        is_rvalue = r;
    }

    const TypeDynArray * getArrayType()
    {
        return dynamic_cast<const TypeDynArray *>(expr->getType()); // FIXME: POTENTIAL ERROR?
    }

    const Type * getStoredType()
    {
        return getArrayType()->getValueType(); // FIXME: POTENTIAL ERROR?
    }

    // TODO: allow for modulo get so that way we can access fields more directly?
    const Type *getType() override
    {
        const Type * stored_type = getStoredType();

        if(!is_rvalue)
        {
            return stored_type;
        }

        std::set<const Type *, TypeCompare> cases = {Types::UNIT, stored_type};
        return new TypeSum(cases);
    }

    const TypeSum* getRValueType() {
        std::set<const Type *, TypeCompare> cases = {Types::UNIT, getStoredType()};
        return new TypeSum(cases);
    }

    std::string toString() const override {
        return "Dynamic Array Access Node";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TAssignNode : public TypedNode, public Visitable<TAssignNode>
{
public:
    TypedNode *var; // FIXME: DO THESE FIELDS BETTER (THEIR TYPES AND SUCH)
    TypedNode *val;

    TAssignNode(TypedNode *sym, TypedNode *v, antlr4::Token *tok) : TypedNode(tok)
    {
        var = sym;
        val = v;
    }

    const TypeUnit *getType() override { return Types::UNIT; }

    std::string toString() const override {
        return "ASSIGN NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

enum BinaryRelOperator
{
    BINARY_Rel_LESS,
    BINARY_Rel_LESS_EQ,
    BINARY_Rel_GREATER,
    BINARY_Rel_GREATER_EQ
};

class TBinaryRelNode : public TypedNode, public Visitable<TBinaryRelNode> {
public:
    BinaryRelOperator op;
    TypedNode *lhs;
    TypedNode *rhs;

    TBinaryRelNode(BinaryRelOperator o, TypedNode *l, TypedNode *r, antlr4::Token *tok) : TypedNode(tok)
    {
        op = o;
        lhs = l;
        rhs = r;
    }

    const TypeBool *getType() override { return Types::DYN_BOOL; }

    std::string toString() const override {
        return "BINARY REL ";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

enum BinaryArithOperator
{
    BINARY_ARITH_PLUS,
    BINARY_ARITH_MINUS,
    BINARY_ARITH_MULT,
    BINARY_ARITH_DIV,
    BINARY_ARITH_MOD,
    BINARY_LOG_RIGHT_SHIFT,
    BINARY_ARITH_RIGHT_SHIFT,
    BINARY_LEFT_SHIFT,
    BIT_AND,
    BIT_OR,
    BIT_XOR
};

class TBinaryArithNode : public TypedNode, public Visitable<TBinaryArithNode>
{
public:
    BinaryArithOperator op;
    TypedNode *lhs; // Wish we could specify type of TypedNode was a number
    TypedNode *rhs;

    TBinaryArithNode(BinaryArithOperator o, TypedNode *l, TypedNode *r, antlr4::Token *tok) : TypedNode(tok)
    {
        op = o;
        lhs = l;
        rhs = r;
    }

    std::string toString() const override {
        return "BINARY ARITH";
    }

    const Type *getType() override { return lhs->getType(); }
    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

enum EqExprOperator
{
    EQUAL_OP,
    NOT_EQUAL_OP
};

class TEqExprNode : public TypedNode, public Visitable<TEqExprNode>
{
public:
    EqExprOperator op;
    TypedNode *lhs;
    TypedNode *rhs;

    TEqExprNode(EqExprOperator o, TypedNode *l, TypedNode *r, antlr4::Token *tok) : TypedNode(tok)
    {
        op = o;
        lhs = l;
        rhs = r;
    }

    const TypeBool *getType() override { return Types::DYN_BOOL; }

    std::string toString() const override {
        return "EQ EXPR";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

enum UnaryOperator
{
    UNARY_MINUS,
    UNARY_NOT,
    UNARY_BIT_NOT,
};

class TUnaryExprNode : public Visitable<TUnaryExprNode>, public virtual TypedNode
{
public:
    UnaryOperator op;
    TypedNode *value;

    TUnaryExprNode(UnaryOperator o, TypedNode *v, antlr4::Token *tok) : TypedNode(tok)
    {
        op = o;
        value = v;
    }

    const Type *getType() override
    {
        switch (op)
        {
        case UNARY_MINUS:
        case UNARY_BIT_NOT:
            // return Types::DYN_INT;
            return value->getType();
        case UNARY_NOT:
            return Types::DYN_BOOL;
        }
    }

    std::string toString() const override {
        return "UNARY";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TLogAndExprNode : public TypedNode, public Visitable<TLogAndExprNode>
{
public:
    vector<TypedNode *> exprs;

    TLogAndExprNode(vector<TypedNode *> e, antlr4::Token *tok) : TypedNode(tok)
    {
        exprs = e;
    }

    vector<TypedNode *> getExprs() { return exprs; }

    const TypeBool *getType() override { return Types::DYN_BOOL; }

    std::string toString() const override {
        return "LOG AND";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TLogOrExprNode : public TypedNode, public Visitable<TLogOrExprNode>
{
public:
    vector<TypedNode *> exprs;

    TLogOrExprNode(vector<TypedNode *> e, antlr4::Token *tok) : TypedNode(tok)
    {
        exprs = e;
    }

    vector<TypedNode *> getExprs() { return exprs; }

    const TypeBool *getType() override { return Types::DYN_BOOL; }

    std::string toString() const override {
        return "LOG OR";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TStringConstNode : public TypedNode, public Visitable<TStringConstNode>
{
public:
    string value;

    TStringConstNode(string s, antlr4::Token *tok) : TypedNode(tok)
    {
        value = s;
    }

    const TypeStr *getType() override { return Types::DYN_STR; }

    std::string toString() const override {
        return "StrConst";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TBooleanConstNode : public TypedNode, public Visitable<TBooleanConstNode>
{
public:
    bool value;

    TBooleanConstNode(bool b, antlr4::Token *tok) : TypedNode(tok)
    {
        value = b;
    }

    const TypeBool *getType() override { return Types::DYN_BOOL; }

    std::string toString() const override {
        return "Boolean CONST";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TNumConstExprNode : public TypedNode, public Visitable<TNumConstExprNode>
{
public:
    std::string value_str;
    TypeInfer * infTy;

    TNumConstExprNode(std::string s, antlr4::Token *tok) : TypedNode(tok)
    {
        value_str = s;
        infTy = new TypeInfer({
            Types::DYN_INT,
            Types::DYN_U32,
            Types::DYN_I64,
            Types::DYN_U64
        });
    }

    const Type *getType() override
    {
        return infTy;
    }

    std::string toString() const override {
        return "Num CONST";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};


class TInt64ConstExprNode : public TypedNode, public Visitable<TInt64ConstExprNode>
{
public:
    int64_t value;

    TInt64ConstExprNode(int64_t v, antlr4::Token *tok) : TypedNode(tok)
    {
        value = v;
    }

    const TypeI64 *getType() override { return Types::DYN_I64; }

    std::string toString() const override {
        return "i64 CONST";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TIntU32ConstExprNode : public TypedNode, public Visitable<TIntU32ConstExprNode>
{
public:
    uint32_t value;

    TIntU32ConstExprNode(uint32_t v, antlr4::Token *tok) : TypedNode(tok)
    {
        value = v;
    }

    const TypeU32 *getType() override { return Types::DYN_U32; }

    std::string toString() const override {
        return "u32 CONST";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TIntU64ConstExprNode : public TypedNode, public Visitable<TIntU64ConstExprNode>
{
public:
    uint64_t value;

    TIntU64ConstExprNode(uint64_t v, antlr4::Token *tok) : TypedNode(tok)
    {
        value = v;
    }

    const TypeU64 *getType() override { return Types::DYN_U64; }

    std::string toString() const override {
        return "u64 CONST";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};


class TInt32ConstExprNode : public TypedNode, public Visitable<TInt32ConstExprNode>
{
public:
    int32_t value;

    TInt32ConstExprNode(int32_t v, antlr4::Token *tok) : TypedNode(tok)
    {
        value = v;
    }

    const TypeInt *getType() override { return Types::DYN_INT; }

    std::string toString() const override {
        return "i32 CONST";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

/////////////////////


class TCompilationUnitNode : public Visitable<TCompilationUnitNode>
{
public:
    vector<TExternNode *> externs;
    vector<DefinitionNode *> defs;

    TCompilationUnitNode(vector<TExternNode *> e, vector<DefinitionNode *> d)
    {
        externs = e;
        defs = d;
    }
 virtual std::any accept_any(VisitorBase &b) { return this->Nuaccept_any(b); }

//    std::any accept(TypedASTVisitor & a) { return a.any_visit(*this); }
};

class AssignmentNode
{
public:
    vector<Symbol *> syms;
    std::optional<TypedNode *> val; // FIXME: REFACTOR SUCH THAT ASSIGNMENTS ARE DIFF FROM VAR DECL?

    AssignmentNode(vector<Symbol *> s, std::optional<TypedNode *> v)
    {
        syms = s;
        val = v;
    }
};

class TVarDeclNode : public TypedNode, public Visitable<TVarDeclNode>
{
public:
    vector<AssignmentNode *> assignments;
    TVarDeclNode(vector<AssignmentNode *> a, antlr4::Token *tok) : TypedNode(tok)
    {
        assignments = a;
    }

    const TypeUnit *getType() override { return Types::UNIT; }


    std::string toString() const override {
        return "VAR DECL NODE";
    }

    std::any accept_any(VisitorBase &a) override { return this->Nuaccept_any(a); }

};

class TMatchStatementNode : public TypedNode, public Visitable<TMatchStatementNode>
{
public:
    const TypeSum *matchType;
    TypedNode *checkExpr;
    vector<pair<Symbol *, TypedNode *>> cases;

    vector<TypedNode *> post;

    TMatchStatementNode(const TypeSum *m, TypedNode *e, vector<pair<Symbol *, TypedNode *>> c, std::vector<TypedNode *> p, antlr4::Token *tok) : TypedNode(tok)
    {
        matchType = m;
        checkExpr = e;
        cases = c;

        post = p;
    }

  std::any accept_any(VisitorBase &a) override { return this->Nuaccept_any(a); }
    const TypeUnit *getType() override
    {
        return Types::UNIT; // PLAN: Change this to allow for a more functional style syntax?
    }

    std::string toString() const override {
        return "MATCH STMT NODE";
    }
};

class TChannelCaseStatementNode : public TypedNode, public ProtocolOpNode, public Visitable<TChannelCaseStatementNode>
{
public:
    // TypedNode *checkExpr;
    Symbol *sym;
    vector<TypedNode *> cases;
    vector<TypedNode *> post;
    bool hasElseStatement;


    TChannelCaseStatementNode(Symbol *c, bool inCloseable, bool hasElse, vector<TypedNode *> v, vector<TypedNode *> p, antlr4::Token *tok)
        : TypedNode(tok),
          ProtocolOpNode(inCloseable),
          hasElseStatement(hasElse)
    {
        sym = c;
        cases = v;
        post = p;
    }

    std::any accept_any(VisitorBase &a) override { return this->Nuaccept_any(a); }

    const TypeUnit *getType() override
    {
        return Types::UNIT;
    }

    std::string toString() const override {
        return "CASE CHANNEL NODE";
    }

};

class TProgramProjectNode : public TypedNode, public Visitable<TProgramProjectNode> // FIXME: DO BETTER, VERY SIMILAR TO SEND
{
public:
    Symbol *sym;
    unsigned int projectIndex;

    TProgramProjectNode(Symbol *s, unsigned int p, antlr4::Token *tok) : TypedNode(tok)
    {
        sym = s;
        projectIndex = p;
    }

    const TypeUnit *getType() override { return Types::UNIT; }
    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }

    std::string toString() const override {
        return "PROJECT NODE";
    }
};

class TExprCopyNode : public TypedNode, public Visitable<TExprCopyNode>
{
public:
    TypedNode *expr;

    TExprCopyNode(TypedNode *e, antlr4::Token *tok) : TypedNode(tok), expr(e)
    {
        // expr = e;
        // lType = l;
    }

    const Type *getType() override { return expr->getType(); }

    std::string toString() const override {
        return "COPY NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};

class TAsChannelNode : public TypedNode, public Visitable<TAsChannelNode>
{
private:
    const Type* nodeType;

public:
    TypedNode *expr;

    TAsChannelNode(TypedNode *e, antlr4::Token *tok) : TypedNode(tok), expr(e)
    {
        nodeType = new TypeChannel(new ProtocolSequence(false, {
            new ProtocolOC(false, new ProtocolSequence(false, {
                new ProtocolRecv(false, [](TypedNode * expr){
                    const Type * ty = expr->getType();
                    if(const TypeArray * arrayType = dynamic_cast<const TypeArray*>(ty))
                    {
                        return arrayType->getValueType();
                    }
                    return ty;
                }(expr))
            }))
        }));
    }

    const Type* getType() override { return nodeType; }
    std::string toString() const override { return "AsChannel(" + expr->toString() + ")"; }
    virtual std::any accept_any(VisitorBase & a) override { return this->Nuaccept_any(a); }
};


class CompCodeWrapper : public TypedNode, public Visitable<CompCodeWrapper>
{
public:
    std::function<std::optional<Value *>()> generator;

public:
    CompCodeWrapper(std::function<std::optional<Value *>()> gen) : TypedNode(nullptr), generator(gen)
    {
    }

    const TypeUnit *getType() override { return Types::UNIT; } // FIXME: DO BETTER

    std::string toString() const override {
        return "GENERATOR NODE";
    }

    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};







class TDefineTraitNode : public DefinitionNode, public Visitable<TDefineTraitNode>
{
public:
    const TypeTrait *traitSpec;

    TDefineTraitNode(DefinitionSymbol * sym, const TypeTrait *t, antlr4::Token *tok) : DefinitionNode(sym, tok)
    {
        traitSpec = t;
    }

    const TypeUnit *getType() override { return Types::UNIT; }

    std::string toString() const override {
        return "DEF TRAIT";
    }


    virtual std::any accept_any(VisitorBase &b) override { return this->Nuaccept_any(b); }
};


/**************************************************
 *
 * UTILITIES
 *
 **************************************************/
namespace TypedAST {
    bool endsInReturn(vector<TypedNode *> n);
    bool endsInReturn(TypedNode & n);
    bool endsInBranch(vector<TypedNode *> n);
    bool endsInBranch(TypedNode &n);
};
