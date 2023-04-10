#pragma once

#include "Symbol.h" //Should give us symbols and yyues...
#include <variant>

#include "antlr4-runtime.h" //For token

using namespace std;
using llvm::Value;

// TODO: HAVE COMPILER ADD COMMENTS TO DOCUMENT COMPLEX TYPES?

class TypedASTVisitor;

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
class TProgramContractNode;
class TProgramWeakenNode;
class TProgramExecNode;
class TProgramAcceptNode;
class TProgramAcceptWhileNode; 
class TDefineEnumNode;
class TDefineStructNode;
class TInitProductNode;
class TInitBoxNode;
class TDerefBoxNode;
class TWhileLoopNode;
class TExternNode;
class TInvocationNode;
class TFieldAccessNode;
class TArrayAccessNode;
class TAssignNode;
class TBinaryRelNode;
class TBinaryArithNode;
class TEqExprNode;
class TUnaryExprNode;
class TLogAndExprNode;
class TLogOrExprNode;
class TStringConstNode;
class TBooleanConstNode;
class TIntConstExprNode;
class TCompilationUnitNode;

class TVarDeclNode;
class TMatchStatementNode;
class TExitNode;

class TChannelCaseStatementNode;
class TProgramProjectNode;

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
    virtual std::optional<Value *> visit(TProgramContractNode *n) = 0;
    virtual std::optional<Value *> visit(TProgramWeakenNode *n) = 0;
    virtual std::optional<Value *> visit(TProgramExecNode *n) = 0;
    virtual std::optional<Value *> visit(TProgramAcceptNode *n) = 0;
    virtual std::optional<Value *> visit(TProgramAcceptWhileNode *n) = 0; 
    // virtual std::optional<Value *> visit(TDefineEnumNode *n) = 0;
    // virtual std::optional<Value *> visit(TDefineStructNode *n) = 0;
    virtual std::optional<Value *> visit(TInitProductNode *n) = 0;
    virtual std::optional<Value *> visit(TInitBoxNode *n) = 0; 
    virtual std::optional<Value *> visit(TDerefBoxNode *n) = 0; 
    virtual std::optional<Value *> visit(TWhileLoopNode *n) = 0;
    virtual std::optional<Value *> visit(TExternNode *n) = 0;
    virtual std::optional<Value *> visit(TInvocationNode *n) = 0;
    virtual std::optional<Value *> visit(TFieldAccessNode *n) = 0;
    virtual std::optional<Value *> visit(TArrayAccessNode *n) = 0;
    virtual std::optional<Value *> visit(TAssignNode *n) = 0;
    virtual std::optional<Value *> visit(TBinaryRelNode *n) = 0;
    virtual std::optional<Value *> visit(TBinaryArithNode *n) = 0;
    virtual std::optional<Value *> visit(TEqExprNode *n) = 0;
    virtual std::optional<Value *> visit(TUnaryExprNode *n) = 0;
    virtual std::optional<Value *> visit(TLogAndExprNode *n) = 0;
    virtual std::optional<Value *> visit(TLogOrExprNode *n) = 0;
    virtual std::optional<Value *> visit(TStringConstNode *n) = 0;
    virtual std::optional<Value *> visit(TBooleanConstNode *n) = 0;
    virtual std::optional<Value *> visit(TIntConstExprNode *n) = 0;
    virtual std::optional<Value *> visit(TCompilationUnitNode *n) = 0;
    virtual std::optional<Value *> visit(TVarDeclNode *n) = 0;
    virtual std::optional<Value *> visit(TMatchStatementNode *n) = 0;
    virtual std::optional<Value *> visit(TExitNode *n) = 0;
    virtual std::optional<Value *> visit(TChannelCaseStatementNode *n) = 0;
    virtual std::optional<Value *> visit(TProgramProjectNode *n) = 0;

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
    std::any any_visit(TProgramContractNode *n) { return this->visit(n); }
    std::any any_visit(TProgramWeakenNode *n) { return this->visit(n); }
    std::any any_visit(TProgramExecNode *n) { return this->visit(n); }
    std::any any_visit(TProgramAcceptNode *n) { return this->visit(n); }
    std::any any_visit(TProgramAcceptWhileNode *n) { return this->visit(n); }
    std::any any_visit(TDefineEnumNode *n) { return this->visit(n); }
    std::any any_visit(TDefineStructNode *n) { return this->visit(n); }
    std::any any_visit(TInitProductNode *n) { return this->visit(n); }
    std::any any_visit(TInitBoxNode *n) { return this->visit(n); }
    std::any any_visit(TDerefBoxNode *n) { return this->visit(n); }
    std::any any_visit(TWhileLoopNode *n) { return this->visit(n); }
    std::any any_visit(TExternNode *n) { return this->visit(n); }
    std::any any_visit(TInvocationNode *n) { return this->visit(n); }
    std::any any_visit(TFieldAccessNode *n) { return this->visit(n); }
    std::any any_visit(TArrayAccessNode *n) { return this->visit(n); }
    std::any any_visit(TAssignNode *n) { return this->visit(n); }
    std::any any_visit(TBinaryRelNode *n) { return this->visit(n); }
    std::any any_visit(TBinaryArithNode *n) { return this->visit(n); }
    std::any any_visit(TEqExprNode *n) { return this->visit(n); }
    std::any any_visit(TUnaryExprNode *n) { return this->visit(n); }
    std::any any_visit(TLogAndExprNode *n) { return this->visit(n); }
    std::any any_visit(TLogOrExprNode *n) { return this->visit(n); }
    std::any any_visit(TStringConstNode *n) { return this->visit(n); }
    std::any any_visit(TBooleanConstNode *n) { return this->visit(n); }
    std::any any_visit(TIntConstExprNode *n) { return this->visit(n); }
    std::any any_visit(TCompilationUnitNode *n) { return this->visit(n); }
    std::any any_visit(TVarDeclNode *n) { return this->visit(n); }
    std::any any_visit(TMatchStatementNode *n) { return this->visit(n); }
    std::any any_visit(TExitNode *n) { return this->visit(n); }
    std::any any_visit(TChannelCaseStatementNode *n) { return this->visit(n); }
    std::any any_visit(TProgramProjectNode *n) { return this->visit(n); }

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

    ParameterNode(const Type *t, string n)
    {
        type = t;
        name = n; // FIXME: DO WE NEED A CLASS HERE OR JUST STRUCT? OR EVEN A TYPEDEF
    }
};

typedef vector<ParameterNode> ParameterListNode;

class TLambdaConstNode : public TypedNode
{
    // private:

public:
    string name;
    vector<Symbol *> paramSymbols;
    const Type *retType;
    TBlockNode *block;
    TypeInvoke *type;

    TLambdaConstNode(antlr4::Token *tok, vector<Symbol *> p, const Type *r, TBlockNode *b, string n = "LAM") : TypedNode(tok)
    {
        // paramList = p;
        paramSymbols = p;
        retType = r;
        block = b;

        name = n;

        vector<const Type *> paramTypes;

        for (Symbol *p : paramSymbols)
        {
            paramTypes.push_back(p->type);
        }

        type = new TypeInvoke(paramTypes, retType);
    }

    const TypeInvoke *getType() override
    {
        return type;
    }

    std::string toString() const override {
        return "LAMBDA CONST";
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TProgramDefNode : public TypedNode
{
private:
    const TypeProgram *type;

public:
    string name;
    Symbol *channelSymbol;
    // TypeChannel * channelType;
    TBlockNode *block;

    TProgramDefNode(string n, Symbol *cn, TBlockNode *b, const TypeProgram *ty, antlr4::Token *tok) : TypedNode(tok)
    {
        name = n;
        channelSymbol = cn;
        // channelType = ct;
        block = b;
        type = ty;
        // type = new TypeInvoke(paramTypes, retType);
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

class TProgramSendNode : public TypedNode
{
public:
    Symbol *sym;
    TypedNode *expr;
    const Type *lType; // Tracks type send expects. Needed for sums

    TProgramSendNode(Symbol *s, TypedNode *e, const Type *l, antlr4::Token *tok) : TypedNode(tok)
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

class TProgramRecvNode : public TypedNode
{
public:
    Symbol *sym;
    const Type *ty;

    TProgramRecvNode(Symbol *s, const Type *t, antlr4::Token *tok) : TypedNode(tok)
    {
        sym = s;
        // expr = e;
        ty = t;
    }

    const Type *getType() override { return ty; }

    std::string toString() const override {
        return "RECV NODE";
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

class TProgramAcceptNode : public TypedNode
{
public:
    Symbol *sym;
    TBlockNode *blk;

    TProgramAcceptNode(Symbol *s, TBlockNode *b, antlr4::Token *tok) : TypedNode(tok)
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

class TProgramAcceptWhileNode : public TypedNode
{
public:
    Symbol *sym;
    TypedNode *cond;
    TBlockNode *blk;

    TProgramAcceptWhileNode(Symbol *s, TypedNode *c, TBlockNode *b, antlr4::Token *tok) : TypedNode(tok)
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

class TDefineEnumNode : public TypedNode
{
public:
    string name;
    const TypeSum *sum;

    TDefineEnumNode(string n, const TypeSum *s, antlr4::Token *tok) : TypedNode(tok)
    {
        name = n;
        // cases = c;
        sum = s;
    }


    std::string toString() const override {
        return "DEF ENUM NODE";
    }

    const TypeUnit *getType() override { return Types::UNIT; }
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TDefineStructNode : public TypedNode
{
public:
    string name;
    const TypeStruct *product;

    TDefineStructNode(string n, const TypeStruct *p, antlr4::Token *tok) : TypedNode(tok)
    {
        name = n;
        // cases = c;
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
    const TypeInvoke *ty; // FIXME: isn't REALLY NEEDED EXCEPT FOR MAKING CASTS EASIER

public:
    TExternNode(std::string id, ParameterListNode p, const Type *r, bool v, antlr4::Token *tok) : TypedNode(tok)
    {
        vector<const Type *> paramTypes;

        for (ParameterNode param : p)
        {
            paramTypes.push_back(param.type);
        }

        ty = new TypeInvoke(paramTypes, r, v);
        sym = new Symbol(id, ty, true, true);
    }

    const TypeInvoke *getType() override
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
        return dynamic_cast<const TypeInvoke *>(fn->getType())->getReturnType();
    }

    std::string toString() const override {
        return "INVOKE NODE";
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TFieldAccessNode : public TypedNode
{
private:
    const Type *type;

public:
    Symbol *symbol;
    vector<pair<string, const Type *>> accesses;
    bool is_rvalue;

    TFieldAccessNode(antlr4::Token *tok, Symbol *f, bool rv, vector<pair<string, const Type *>> r = {}) : TypedNode(tok)
    {
        symbol = f;
        is_rvalue = rv;
        accesses = r;

        if (r.empty())
        {
            type = symbol->type;
        }
        else
        {
            type = r.at(r.size() - 1).second;
        }
    }

    const Type *getType() override
    {
        return type;
    }

    std::string toString() const override {
        return "FIELD ACCESS NODE";
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

    const Type *getType() override
    {
        return dynamic_cast<const TypeArray *>(field->getType())->getValueType(); // FIXME: POTENTIAL ERROR?
    }

    std::string toString() const override {
        return "Array Access Node";
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

    const TypeBool *getType() override { return Types::BOOL; }

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
    BINARY_ARITH_DIV
};

class TBinaryArithNode : public TypedNode
{
public:
    BinaryArithOperator op;
    TypedNode *lhs;
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

    const TypeInt *getType() override { return Types::INT; }
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

    const TypeBool *getType() override { return Types::BOOL; }

    std::string toString() const override {
        return "EQEXPR";
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
            return Types::INT;
        case UNARY_NOT:
            return Types::BOOL;
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

    const TypeBool *getType() override { return Types::BOOL; }

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

    const TypeBool *getType() override { return Types::BOOL; }

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

    const TypeStr *getType() override { return Types::STR; }

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

    const TypeBool *getType() override { return Types::BOOL; }

    std::string toString() const override {
        return "BOOL CONST";
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class TIntConstExprNode : public TypedNode
{
public:
    int value;

    TIntConstExprNode(int v, antlr4::Token *tok) : TypedNode(tok)
    {
        value = v;
    }

    const TypeInt *getType() override { return Types::INT; }

    std::string toString() const override {
        return "I CONST";
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

/////////////////////

typedef variant<TDefineEnumNode *, TDefineStructNode *, TProgramDefNode *, TLambdaConstNode *> DefinitionNode;

class TCompilationUnitNode
{
public:
    vector<TExternNode *> externs;
    vector<DefinitionNode> defs;

    TCompilationUnitNode(vector<TExternNode *> e, vector<DefinitionNode> d)
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

class TChannelCaseStatementNode : public TypedNode
{
public:
    // TypedNode *checkExpr;
    Symbol *sym;
    vector<TypedNode *> cases;
    vector<TypedNode *> post;

    TChannelCaseStatementNode(Symbol *c, vector<TypedNode *> v, vector<TypedNode *> p, antlr4::Token *tok) : TypedNode(tok)
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

    // FIXME: DO THESE BETTER!
    if (TConditionalStatementNode *cn = dynamic_cast<TConditionalStatementNode *>(n))
    {
        // if(cn->post.size())
        return endsInReturn(cn->post);
    }

    if (TMatchStatementNode *cn = dynamic_cast<TMatchStatementNode *>(n))
    {
        // if(cn->post.size())
        return endsInReturn(cn->post);
    }

    if (TSelectStatementNode *cn = dynamic_cast<TSelectStatementNode *>(n))
    {
        // if(cn->post.size())
        return endsInReturn(cn->post);
    }

    if(TSelectAlternativeNode * cn = dynamic_cast<TSelectAlternativeNode*>(n))
    {
        return endsInReturn(cn->eval);
    }

    // if(TMatchStatementNode * cn = dynamic_cast<TMatchStatementNode *>(n))
    // {
    //     // if(cn->post.size())
    //     return endsInReturn(cn->post);
    // }

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

    // if(TMatchStatementNode * cn = dynamic_cast<TMatchStatementNode *>(n))
    // {
    //     // if(cn->post.size())
    //     return endsInReturn(cn->post);
    // }

    return false;
}