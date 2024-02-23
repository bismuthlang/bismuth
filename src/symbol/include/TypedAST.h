#pragma once

#include "Symbol.h" //Should give us symbols and yyues...
#include <variant>
#include <functional> // std::function


#include "antlr4-runtime.h" //For token

using namespace std;
using llvm::Value;

// TODO: HAVE COMPILER ADD COMMENTS TO DOCUMENT COMPLEX TYPES?

class TypedASTVisitor;


class ProtocolOpNode
{
private:
    bool inCloseable;

public:
    ProtocolOpNode(bool _inCloseable) : inCloseable(_inCloseable) 
    {}

    bool isInCloseable() const { return inCloseable; }
};

class TypedNode
{
public:
    antlr4::Token *token; // Location of node
    TypedNode(antlr4::Token *tok) : token(tok) {}

    virtual ~TypedNode() = default;

    virtual const Type *getType() = 0;

    virtual std::string toString() const = 0;  

    virtual std::any accept(TypedASTVisitor *a) = 0;

    antlr4::Token *getStart() { return token; }
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

class TypedASTVisitor
{
public:
    virtual ~TypedASTVisitor() = default;

    // virtual std::optional<Value *> visit(TSelectAlternativeNode *n) = 0;
    virtual std::optional<Value *> visit(TSelectStatementNode *n) = 0;
    virtual std::optional<Value *> visit(TBlockNode *n) = 0;
    virtual std::optional<Value *> visit(TLambdaConstNode *n) = 0;
    virtual std::optional<Value *> visit(TProgramDefNode *n) = 0;
    virtual std::optional<Value *> visit(TConditionalStatementNode *n) = 0;
    virtual std::optional<Value *> visit(TReturnNode *n) = 0;
    virtual std::optional<Value *> visit(TProgramSendNode *n) = 0;
    virtual std::optional<Value *> visit(TProgramRecvNode *n) = 0;
    virtual std::optional<Value *> visit(TProgramIsPresetNode *n) = 0; 
    virtual std::optional<Value *> visit(TProgramContractNode *n) = 0;
    virtual std::optional<Value *> visit(TProgramWeakenNode *n) = 0;
    virtual std::optional<Value *> visit(TProgramCancelNode *n) = 0; 
    virtual std::optional<Value *> visit(TProgramExecNode *n) = 0;
    virtual std::optional<Value *> visit(TProgramAcceptNode *n) = 0;
    virtual std::optional<Value *> visit(TProgramAcceptWhileNode *n) = 0; 
    virtual std::optional<Value *> visit(TProgramAcceptIfNode *n) = 0; 
    virtual std::optional<Value *> visit(TDefineEnumNode *n) = 0;
    virtual std::optional<Value *> visit(TDefineStructNode *n) = 0;
    virtual std::optional<Value *> visit(TDefineTemplateNode *n) = 0; 
    virtual std::optional<Value *> visit(TInitProductNode *n) = 0;
    virtual std::optional<Value *> visit(TArrayRValue *n) = 0; 
    virtual std::optional<Value *> visit(TInitBoxNode *n) = 0; 
    virtual std::optional<Value *> visit(TDerefBoxNode *n) = 0; 
    virtual std::optional<Value *> visit(TWhileLoopNode *n) = 0;
    virtual std::optional<Value *> visit(TExternNode *n) = 0;
    virtual std::optional<Value *> visit(TInvocationNode *n) = 0;
    virtual std::optional<Value *> visit(TFieldAccessNode *n) = 0;
    virtual std::optional<Value *> visit(TIdentifier *n) = 0; 
    virtual std::optional<Value *> visit(TPathNode *n) = 0; 
    virtual std::optional<Value *> visit(TArrayAccessNode *n) = 0;
    virtual std::optional<Value *> visit(TDynArrayAccessNode *n) = 0; 
    virtual std::optional<Value *> visit(TAssignNode *n) = 0;
    virtual std::optional<Value *> visit(TBinaryRelNode *n) = 0;
    virtual std::optional<Value *> visit(TBinaryArithNode *n) = 0;
    virtual std::optional<Value *> visit(TEqExprNode *n) = 0;
    virtual std::optional<Value *> visit(TUnaryExprNode *n) = 0;
    virtual std::optional<Value *> visit(TLogAndExprNode *n) = 0;
    virtual std::optional<Value *> visit(TLogOrExprNode *n) = 0;
    virtual std::optional<Value *> visit(TStringConstNode *n) = 0;
    virtual std::optional<Value *> visit(TBooleanConstNode *n) = 0;
    virtual std::optional<Value *> visit(TInt32ConstExprNode *n) = 0;
    virtual std::optional<Value *> visit(TInt64ConstExprNode *n) = 0;
    virtual std::optional<Value *> visit(TIntU32ConstExprNode *n) = 0;
    virtual std::optional<Value *> visit(TIntU64ConstExprNode *n) = 0;
    virtual std::optional<Value *> visit(TCompilationUnitNode *n) = 0;
    virtual std::optional<Value *> visit(TVarDeclNode *n) = 0;
    virtual std::optional<Value *> visit(TMatchStatementNode *n) = 0;
    virtual std::optional<Value *> visit(TExitNode *n) = 0;
    virtual std::optional<Value *> visit(TChannelCaseStatementNode *n) = 0;
    virtual std::optional<Value *> visit(TProgramProjectNode *n) = 0;
    virtual std::optional<Value *> visit(TExprCopyNode *n) = 0; 
    virtual std::optional<Value *> visit(TAsChannelNode *n) = 0; 
    std::optional<Value *> visit(CompCodeWrapper *n);  // TODO: why don't we directly call the generator? 

    // virtual std::optional<Value

    // private:
    std::any any_visit(TSelectAlternativeNode *n) { return this->visit(n); }
    std::any any_visit(TSelectStatementNode *n) { return this->visit(n); }
    std::any any_visit(TBlockNode *n) { return this->visit(n); }
    std::any any_visit(TLambdaConstNode *n) { return this->visit(n); }
    std::any any_visit(TProgramDefNode *n) { return this->visit(n); }
    std::any any_visit(TConditionalStatementNode *n) { return this->visit(n); }
    std::any any_visit(TReturnNode *n) { return this->visit(n); }
    std::any any_visit(TProgramSendNode *n) { return this->visit(n); }
    std::any any_visit(TProgramRecvNode *n) { return this->visit(n); }
    std::any any_visit(TProgramIsPresetNode *n) { return this->visit(n); }
    std::any any_visit(TProgramContractNode *n) { return this->visit(n); }
    std::any any_visit(TProgramWeakenNode *n) { return this->visit(n); }
    std::any any_visit(TProgramCancelNode *n) { return this->visit(n); }
    std::any any_visit(TProgramExecNode *n) { return this->visit(n); }
    std::any any_visit(TProgramAcceptNode *n) { return this->visit(n); }
    std::any any_visit(TProgramAcceptWhileNode *n) { return this->visit(n); }
    std::any any_visit(TProgramAcceptIfNode *n) { return this->visit(n); }
    std::any any_visit(TDefineEnumNode *n) { return this->visit(n); }
    std::any any_visit(TDefineTemplateNode *n) { return this->visit(n); }
    std::any any_visit(TDefineStructNode *n) { return this->visit(n); }
    std::any any_visit(TInitProductNode *n) { return this->visit(n); }
    std::any any_visit(TArrayRValue *n) { return this->visit(n); }
    std::any any_visit(TInitBoxNode *n) { return this->visit(n); }
    std::any any_visit(TDerefBoxNode *n) { return this->visit(n); }
    std::any any_visit(TWhileLoopNode *n) { return this->visit(n); }
    std::any any_visit(TExternNode *n) { return this->visit(n); }
    std::any any_visit(TInvocationNode *n) { return this->visit(n); }
    std::any any_visit(TFieldAccessNode *n) { return this->visit(n); }
    std::any any_visit(TIdentifier *n) { return this->visit(n); }
    std::any any_visit(TPathNode *n) { return this->visit(n); }
    std::any any_visit(TArrayAccessNode *n) { return this->visit(n); }
    std::any any_visit(TDynArrayAccessNode *n) { return this->visit(n); }
    std::any any_visit(TAssignNode *n) { return this->visit(n); }
    std::any any_visit(TBinaryRelNode *n) { return this->visit(n); }
    std::any any_visit(TBinaryArithNode *n) { return this->visit(n); }
    std::any any_visit(TEqExprNode *n) { return this->visit(n); }
    std::any any_visit(TUnaryExprNode *n) { return this->visit(n); }
    std::any any_visit(TLogAndExprNode *n) { return this->visit(n); }
    std::any any_visit(TLogOrExprNode *n) { return this->visit(n); }
    std::any any_visit(TStringConstNode *n) { return this->visit(n); }
    std::any any_visit(TBooleanConstNode *n) { return this->visit(n); }
    std::any any_visit(TInt32ConstExprNode *n) { return this->visit(n); }
    std::any any_visit(TInt64ConstExprNode *n) { return this->visit(n); }
    std::any any_visit(TIntU32ConstExprNode *n) { return this->visit(n); }
    std::any any_visit(TIntU64ConstExprNode *n) { return this->visit(n); }
    std::any any_visit(TCompilationUnitNode *n) { return this->visit(n); }
    std::any any_visit(TVarDeclNode *n) { return this->visit(n); }
    std::any any_visit(TMatchStatementNode *n) { return this->visit(n); }
    std::any any_visit(TExitNode *n) { return this->visit(n); }
    std::any any_visit(TChannelCaseStatementNode *n) { return this->visit(n); }
    std::any any_visit(TProgramProjectNode *n) { return this->visit(n); }
    std::any any_visit(TExprCopyNode *n) {return this->visit(n); }
    std::any any_visit(TAsChannelNode *n) { return this->visit(n); }
    std::any any_visit(CompCodeWrapper *n) { return this->visit(n); }

    std::any visit(std::any n) { return "FIXME"; }
    std::any accept(TypedNode *n)
    {
        return n->accept(this);
        // return dynamic_cast<T>(n->accept(this)); // Hacky, but completely safe
        // return n->accept(this);
    }
};

inline std::optional<Value *> AcceptType(TypedASTVisitor *visitor, TypedNode *n)
{
    return any_cast<std::optional<Value *>>(n->accept(visitor));
}

class TSelectAlternativeNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }

    std::string toString() const override {
        return "SEL ALT";
    }
};

class TSelectStatementNode : public TypedNode
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
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }

    std::string toString() const override {
        return "SEL STMT NODE";
    }
};

class TBlockNode : public TypedNode
{
public:
    vector<TypedNode *> exprs;

    TBlockNode(vector<TypedNode *> e, antlr4::Token *tok) : TypedNode(tok)
    {
        exprs = e;
    }

    vector<TypedNode *> getExprs() { return exprs; }

    const TypeUnit *getType() override { return Types::UNIT; } // PLAN: Change this to allow for more functional style? 
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }

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

class TLambdaConstNode : public DefinitionNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TProgramDefNode : public DefinitionNode
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
        // type = new TypeFunc(paramTypes, retType);
    }

    const TypeProgram *getType() override
    {
        return type;
    }

    std::string toString() const override {
        return "PROG DEF";
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TConditionalStatementNode : public TypedNode
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
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TReturnNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TExitNode : public TypedNode
{
public:
    TExitNode(antlr4::Token *tok) : TypedNode(tok)
    {
    }

    const TypeUnit *getType() override { return Types::UNIT; } // FIXME: DO BETTER

    std::string toString() const override {
        return "EXIT NODE";
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TProgramSendNode : public TypedNode, public ProtocolOpNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TProgramRecvNode : public TypedNode, public ProtocolOpNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};


class TProgramIsPresetNode : public TypedNode, public ProtocolOpNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};
class TProgramContractNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TProgramWeakenNode : public TypedNode // FIXME: COMBINE THIS WITH PREV AND USE ENUM FOR OP?
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};


class TProgramCancelNode : public TypedNode // FIXME: COMBINE THIS WITH PREV AND USE ENUM FOR OP?
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TProgramExecNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TProgramAcceptNode : public TypedNode, public ProtocolOpNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TProgramAcceptWhileNode : public TypedNode, public ProtocolOpNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};


class TProgramAcceptIfNode : public TypedNode, public ProtocolOpNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TDefineEnumNode : public DefinitionNode
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
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};


class TDefineTemplateNode : public DefinitionNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TDefineStructNode : public DefinitionNode
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


    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TInitProductNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};


class TArrayRValue : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TInitBoxNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }

    const TypeBox *getType() override { return boxType; }
};

class TDerefBoxNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }

    const Type *getType() override { return boxType->getInnerType(); }
};

class TWhileLoopNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TExternNode : public TypedNode
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
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TInvocationNode : public TypedNode
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

    const Type *getType() override
    {
        return dynamic_cast<const TypeFunc *>(fn->getType())->getReturnType();
    }

    std::string toString() const override {
        return "INVOKE NODE " + fn->toString();
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};


class TPathNode: public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TIdentifier : public TypedNode 
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};


class TFieldAccessNode : public TypedNode
{
private:
    // Symbol *symbol;
    // const Type * symType; 
    TIdentifier * id; 
    const Type * resultType; 


public:
    bool is_rvalue;
    vector<pair<string, const Type *>> accesses;

    TFieldAccessNode(antlr4::Token *tok, TIdentifier * i, bool rv, vector<pair<string, const Type *>> r = {}) 
        : TypedNode(tok)
        , id(i)
        // , symbol(s)
        // , symType(st)
        , is_rvalue(rv)
        , accesses(r)
    {
        resultType = r.empty() ? id->getType() : r.at(r.size() - 1).second;
    }

    const Type *getType() override { return resultType; }

    const Type * getResultantType() { return resultType; }

    const Type * getSymbolType() { return id->getType(); }

    TIdentifier * getIdentifier() { return id; }

    // Symbol * getSymbol() { return symbol; }


    std::string toString() const override {
        return "FIELD ACCESS NODE "; // + symbol->toString();
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};


class TArrayAccessNode : public TypedNode
{
public:
    TFieldAccessNode *field;
    TypedNode *indexExpr;
    bool is_rvalue;

    TArrayAccessNode(TFieldAccessNode *f, TypedNode *i, bool r, antlr4::Token *tok) : TypedNode(tok)
    {
        field = f;
        indexExpr = i;
        is_rvalue = r;
    }

    // TODO: allow for modulo get so that way we can access fields more directly?
    const Type *getType() override
    {
        const Type * arrayType = dynamic_cast<const TypeArray *>(field->getType())->getValueType(); // FIXME: POTENTIAL ERROR?

        if(!is_rvalue)
        {
            return arrayType;
        }

        std::set<const Type *, TypeCompare> cases = {Types::UNIT, arrayType};
        return new TypeSum(cases);
    }

    const TypeSum* getRValueType() {
        const Type * arrayType = dynamic_cast<const TypeArray *>(field->getType())->getValueType(); // FIXME: POTENTIAL ERROR?
        std::set<const Type *, TypeCompare> cases = {Types::UNIT, arrayType};
        return new TypeSum(cases);
    }

    uint32_t length() const {
        return dynamic_cast<const TypeArray *>(field->getType())->getLength();
    }

    std::string toString() const override {
        return "Array Access Node";
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TDynArrayAccessNode : public TypedNode
{
public:
    TFieldAccessNode *field;
    TypedNode *indexExpr;
    bool is_rvalue;

    TDynArrayAccessNode(TFieldAccessNode *f, TypedNode *i, bool r, antlr4::Token *tok) : TypedNode(tok)
    {
        field = f;
        indexExpr = i;
        is_rvalue = r;
    }

    // TODO: allow for modulo get so that way we can access fields more directly?
    const Type *getType() override
    {
        const Type * arrayType = dynamic_cast<const TypeDynArray *>(field->getType())->getValueType(); // FIXME: POTENTIAL ERROR?

        if(!is_rvalue)
        {
            return arrayType;
        }

        std::set<const Type *, TypeCompare> cases = {Types::UNIT, arrayType};
        return new TypeSum(cases);
    }

    const TypeSum* getRValueType() {
        const Type * arrayType = dynamic_cast<const TypeDynArray *>(field->getType())->getValueType(); // FIXME: POTENTIAL ERROR?
        std::set<const Type *, TypeCompare> cases = {Types::UNIT, arrayType};
        return new TypeSum(cases);
    }

    std::string toString() const override {
        return "Dynamic Array Access Node";
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TAssignNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

enum BinaryRelOperator
{
    BINARY_Rel_LESS,
    BINARY_Rel_LESS_EQ,
    BINARY_Rel_GREATER,
    BINARY_Rel_GREATER_EQ
};

class TBinaryRelNode : public TypedNode
{
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

enum BinaryArithOperator
{
    BINARY_ARITH_PLUS,
    BINARY_ARITH_MINUS,
    BINARY_ARITH_MULT,
    BINARY_ARITH_DIV,
    BINARY_ARITH_MOD
};

class TBinaryArithNode : public TypedNode
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
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

enum EqExprOperator
{
    EQUAL_OP,
    NOT_EQUAL_OP
};

class TEqExprNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

enum UnaryOperator
{
    UNARY_MINUS,
    UNARY_NOT
};

class TUnaryExprNode : public TypedNode
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
            return Types::DYN_INT;
        case UNARY_NOT:
            return Types::DYN_BOOL;
        }
    }

    std::string toString() const override {
        return "UNARY";
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TLogAndExprNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TLogOrExprNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TStringConstNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TBooleanConstNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TInt32ConstExprNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TInt64ConstExprNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TIntU32ConstExprNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TIntU64ConstExprNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

/////////////////////


class TCompilationUnitNode
{
public:
    vector<TExternNode *> externs;
    vector<DefinitionNode *> defs;

    TCompilationUnitNode(vector<TExternNode *> e, vector<DefinitionNode *> d)
    {
        externs = e;
        defs = d;
    }

    std::any accept(TypedASTVisitor *a) { return a->any_visit(this); }
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

class TVarDeclNode : public TypedNode
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


    std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TMatchStatementNode : public TypedNode
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

    std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }

    const TypeUnit *getType() override
    {
        return Types::UNIT; // PLAN: Change this to allow for a more functional style syntax?
    }

    std::string toString() const override {
        return "MATCH STMT NODE";
    }
};

class TChannelCaseStatementNode : public TypedNode, public ProtocolOpNode
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

    std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }

    const TypeUnit *getType() override
    {
        return Types::UNIT;
    }

    std::string toString() const override {
        return "CASE CHANNEL NODE";
    }

};

class TProgramProjectNode : public TypedNode // FIXME: DO BETTER, VERY SIMILAR TO SEND
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
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }

    std::string toString() const override {
        return "PROJECT NODE";
    }
};

class TExprCopyNode : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TAsChannelNode : public TypedNode 
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
    virtual std::any accept(TypedASTVisitor * a) override { return a ->any_visit(this); }
};


class CompCodeWrapper : public TypedNode
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

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};


/**************************************************
 *
 * UTILITIES
 *
 **************************************************/
inline bool
endsInReturn(TypedNode *n);

inline bool endsInReturn(vector<TypedNode *> n)
{
    if (n.size() == 0)
        return false;
    return endsInReturn(n.at(n.size() - 1));
}

inline bool endsInReturn(TypedNode *n)
{
    if (dynamic_cast<TReturnNode *>(n))
        return true;
    if (dynamic_cast<TExitNode *>(n))
        return true;

    if (TBlockNode *bn = dynamic_cast<TBlockNode *>(n))
    {
        return endsInReturn(bn->exprs);
    }

    if (TConditionalStatementNode *cn = dynamic_cast<TConditionalStatementNode *>(n))
    {
        if(cn->post.size())
            return endsInReturn(cn->post);
        
        if(cn->falseOpt) 
        {
            return endsInReturn(cn->falseOpt.value()) && endsInReturn(cn->trueBlk);
        }

        return false; 
    }

    if (TMatchStatementNode *cn = dynamic_cast<TMatchStatementNode *>(n))
    {
        if(cn->post.size())
            return endsInReturn(cn->post);
        
        for(auto branch : cn->cases)
            if(!endsInReturn(branch.second))
                return false; 
        return true; 
    }

    if (TSelectStatementNode *cn = dynamic_cast<TSelectStatementNode *>(n))
    {
        if(cn->post.size())
            return endsInReturn(cn->post);
        
        for(auto branch : cn->nodes)
            if(!endsInReturn(branch))
                return false; 
        return true; 
    }

    if(TSelectAlternativeNode * cn = dynamic_cast<TSelectAlternativeNode*>(n))
    {
        return endsInReturn(cn->eval);
    }
    
    return false;
}

inline bool
endsInBranch(TypedNode *n);

inline bool endsInBranch(vector<TypedNode *> n)
{
    if (n.size() == 0)
        return false;
    return endsInBranch(n.at(n.size() - 1));
}

inline bool endsInBranch(TypedNode *n)
{
    if (TBlockNode *bn = dynamic_cast<TBlockNode *>(n))
    {
        return endsInBranch(bn->exprs);
    }

    // FIXME: DO THESE BETTER!
    if (TConditionalStatementNode *cn = dynamic_cast<TConditionalStatementNode *>(n))
    {
        return true; 
    }

    if (TMatchStatementNode *cn = dynamic_cast<TMatchStatementNode *>(n))
    {
        return true; 
    }

    if (TSelectStatementNode *cn = dynamic_cast<TSelectStatementNode *>(n))
    {
        return true; 
    }

    if (TSelectAlternativeNode *cn = dynamic_cast<TSelectAlternativeNode *>(n))
    {
        return endsInBranch(cn->eval);
        // return true; 
    }

    if(TChannelCaseStatementNode * sn = dynamic_cast<TChannelCaseStatementNode*>(n))
    {
        return true; 
    }

    return false;
}