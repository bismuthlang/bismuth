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

class SelectAlternativeNode;
class SelectStatementNode;
class BlockNode;

class LambdaConstNode;
class ProgramDefNode;
class ConditionalStatementNode;
class ReturnNode;
class ProgramSendNode;
class ProgramRecvNode;
class ProgramContractNode;
class ProgramWeakenNode;
class ProgramExecNode;
class ProgramAcceptNode;
class DefineEnumNode;
class DefineStructNode;
class InitProductNode;
class InitBoxNode;
class DerefBoxNode;
class WhileLoopNode;
class ExternNode;
class InvocationNode;
class FieldAccessNode;
class ArrayAccessNode;
class AssignNode;
class BinaryRelNode;
class BinaryArithNode;
class EqExprNode;
class UnaryExprNode;
class LogAndExprNode;
class LogOrExprNode;
class StringConstNode;
class BooleanConstNode;
class IConstExprNode;
class CompilationUnitNode;

class VarDeclNode;
class MatchStatementNode;
class ExitNode;

class ChannelCaseStatementNode;
class ProgramProjectNode;

class TypedASTVisitor
{
public:
    virtual ~TypedASTVisitor() = default;

    // virtual std::optional<Value *> visit(SelectAlternativeNode *n) = 0;
    virtual std::optional<Value *> visit(SelectStatementNode *n) = 0;
    virtual std::optional<Value *> visit(BlockNode *n) = 0;
    virtual std::optional<Value *> visit(LambdaConstNode *n) = 0;
    virtual std::optional<Value *> visit(ProgramDefNode *n) = 0;
    virtual std::optional<Value *> visit(ConditionalStatementNode *n) = 0;
    virtual std::optional<Value *> visit(ReturnNode *n) = 0;
    virtual std::optional<Value *> visit(ProgramSendNode *n) = 0;
    virtual std::optional<Value *> visit(ProgramRecvNode *n) = 0;
    virtual std::optional<Value *> visit(ProgramContractNode *n) = 0;
    virtual std::optional<Value *> visit(ProgramWeakenNode *n) = 0;
    virtual std::optional<Value *> visit(ProgramExecNode *n) = 0;
    virtual std::optional<Value *> visit(ProgramAcceptNode *n) = 0;
    // virtual std::optional<Value *> visit(DefineEnumNode *n) = 0;
    // virtual std::optional<Value *> visit(DefineStructNode *n) = 0;
    virtual std::optional<Value *> visit(InitProductNode *n) = 0;
    virtual std::optional<Value *> visit(InitBoxNode *n) = 0; 
    virtual std::optional<Value *> visit(DerefBoxNode *n) = 0; 
    virtual std::optional<Value *> visit(WhileLoopNode *n) = 0;
    virtual std::optional<Value *> visit(ExternNode *n) = 0;
    virtual std::optional<Value *> visit(InvocationNode *n) = 0;
    virtual std::optional<Value *> visit(FieldAccessNode *n) = 0;
    virtual std::optional<Value *> visit(ArrayAccessNode *n) = 0;
    virtual std::optional<Value *> visit(AssignNode *n) = 0;
    virtual std::optional<Value *> visit(BinaryRelNode *n) = 0;
    virtual std::optional<Value *> visit(BinaryArithNode *n) = 0;
    virtual std::optional<Value *> visit(EqExprNode *n) = 0;
    virtual std::optional<Value *> visit(UnaryExprNode *n) = 0;
    virtual std::optional<Value *> visit(LogAndExprNode *n) = 0;
    virtual std::optional<Value *> visit(LogOrExprNode *n) = 0;
    virtual std::optional<Value *> visit(StringConstNode *n) = 0;
    virtual std::optional<Value *> visit(BooleanConstNode *n) = 0;
    virtual std::optional<Value *> visit(IConstExprNode *n) = 0;
    virtual std::optional<Value *> visit(CompilationUnitNode *n) = 0;
    virtual std::optional<Value *> visit(VarDeclNode *n) = 0;
    virtual std::optional<Value *> visit(MatchStatementNode *n) = 0;
    virtual std::optional<Value *> visit(ExitNode *n) = 0;
    virtual std::optional<Value *> visit(ChannelCaseStatementNode *n) = 0;
    virtual std::optional<Value *> visit(ProgramProjectNode *n) = 0;

    // virtual std::optional<Value

    // private:
    std::any any_visit(SelectAlternativeNode *n) { return this->visit(n); }
    std::any any_visit(SelectStatementNode *n) { return this->visit(n); }
    std::any any_visit(BlockNode *n) { return this->visit(n); }
    std::any any_visit(LambdaConstNode *n) { return this->visit(n); }
    std::any any_visit(ProgramDefNode *n) { return this->visit(n); }
    std::any any_visit(ConditionalStatementNode *n) { return this->visit(n); }
    std::any any_visit(ReturnNode *n) { return this->visit(n); }
    std::any any_visit(ProgramSendNode *n) { return this->visit(n); }
    std::any any_visit(ProgramRecvNode *n) { return this->visit(n); }
    std::any any_visit(ProgramContractNode *n) { return this->visit(n); }
    std::any any_visit(ProgramWeakenNode *n) { return this->visit(n); }
    std::any any_visit(ProgramExecNode *n) { return this->visit(n); }
    std::any any_visit(ProgramAcceptNode *n) { return this->visit(n); }
    std::any any_visit(DefineEnumNode *n) { return this->visit(n); }
    std::any any_visit(DefineStructNode *n) { return this->visit(n); }
    std::any any_visit(InitProductNode *n) { return this->visit(n); }
    std::any any_visit(InitBoxNode *n) { return this->visit(n); }
    std::any any_visit(DerefBoxNode *n) { return this->visit(n); }
    std::any any_visit(WhileLoopNode *n) { return this->visit(n); }
    std::any any_visit(ExternNode *n) { return this->visit(n); }
    std::any any_visit(InvocationNode *n) { return this->visit(n); }
    std::any any_visit(FieldAccessNode *n) { return this->visit(n); }
    std::any any_visit(ArrayAccessNode *n) { return this->visit(n); }
    std::any any_visit(AssignNode *n) { return this->visit(n); }
    std::any any_visit(BinaryRelNode *n) { return this->visit(n); }
    std::any any_visit(BinaryArithNode *n) { return this->visit(n); }
    std::any any_visit(EqExprNode *n) { return this->visit(n); }
    std::any any_visit(UnaryExprNode *n) { return this->visit(n); }
    std::any any_visit(LogAndExprNode *n) { return this->visit(n); }
    std::any any_visit(LogOrExprNode *n) { return this->visit(n); }
    std::any any_visit(StringConstNode *n) { return this->visit(n); }
    std::any any_visit(BooleanConstNode *n) { return this->visit(n); }
    std::any any_visit(IConstExprNode *n) { return this->visit(n); }
    std::any any_visit(CompilationUnitNode *n) { return this->visit(n); }
    std::any any_visit(VarDeclNode *n) { return this->visit(n); }
    std::any any_visit(MatchStatementNode *n) { return this->visit(n); }
    std::any any_visit(ExitNode *n) { return this->visit(n); }
    std::any any_visit(ChannelCaseStatementNode *n) { return this->visit(n); }
    std::any any_visit(ProgramProjectNode *n) { return this->visit(n); }

    std::any visit(std::any n) { return "FIXME"; }
    std::any accept(TypedNode *n)
    {
        return n->accept(this);
        // return dynamic_cast<T>(n->accept(this)); // Hacky, but completley safe
        // return n->accept(this);
    }
};

inline std::optional<Value *> AcceptType(TypedASTVisitor *visitor, TypedNode *n)
{
    return any_cast<std::optional<Value *>>(n->accept(visitor));
}

class SelectAlternativeNode : public TypedNode
{
public:
    TypedNode *check;
    TypedNode *eval;

    SelectAlternativeNode(TypedNode *c, TypedNode *e, antlr4::Token *tok) : TypedNode(tok)
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

class SelectStatementNode : public TypedNode
{
public:
    vector<SelectAlternativeNode *> nodes;
    vector<TypedNode *> post;

    SelectStatementNode(antlr4::Token *tok, vector<SelectAlternativeNode *> n, vector<TypedNode *> p) : TypedNode(tok)
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

class BlockNode : public TypedNode
{
public:
    vector<TypedNode *> exprs;

    BlockNode(vector<TypedNode *> e, antlr4::Token *tok) : TypedNode(tok)
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

class LambdaConstNode : public TypedNode
{
    // private:

public:
    string name;
    vector<Symbol *> paramSymbols;
    const Type *retType;
    BlockNode *block;
    TypeInvoke *type;

    LambdaConstNode(antlr4::Token *tok, vector<Symbol *> p, const Type *r, BlockNode *b, string n = "LAM") : TypedNode(tok)
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

class ProgramDefNode : public TypedNode
{
private:
    const TypeProgram *type;

public:
    string name;
    Symbol *channelSymbol;
    // TypeChannel * channelType;
    BlockNode *block;

    ProgramDefNode(string n, Symbol *cn, BlockNode *b, const TypeProgram *ty, antlr4::Token *tok) : TypedNode(tok)
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

class ConditionalStatementNode : public TypedNode
{
public:
    TypedNode *cond;
    BlockNode *trueBlk;
    std::optional<BlockNode *> falseOpt;

    std::vector<TypedNode *> post;

    ConditionalStatementNode(antlr4::Token *tok, TypedNode *c, BlockNode *t, std::vector<TypedNode *> p, std::optional<BlockNode *> f = {}) : TypedNode(tok)
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

class ReturnNode : public TypedNode
{
public:
    // First is the actual type
    optional<pair<const Type *, TypedNode *>> expr;

    ReturnNode(antlr4::Token *tok, optional<pair<const Type *, TypedNode *>> e = {}) : TypedNode(tok)
    {
        expr = e;
    }

    const TypeUnit *getType() override { return Types::UNIT; }

    std::string toString() const override {
        return "RETURN NODE";
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class ExitNode : public TypedNode
{
public:
    ExitNode(antlr4::Token *tok) : TypedNode(tok)
    {
    }

    const TypeUnit *getType() override { return Types::UNIT; } // FIXME: DO BETTER

    std::string toString() const override {
        return "EXIT NODE";
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class ProgramSendNode : public TypedNode
{
public:
    Symbol *sym;
    TypedNode *expr;
    const Type *lType; // Tracks type send expects. Needed for sums

    ProgramSendNode(Symbol *s, TypedNode *e, const Type *l, antlr4::Token *tok) : TypedNode(tok)
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

class ProgramRecvNode : public TypedNode
{
public:
    Symbol *sym;
    const Type *ty;

    ProgramRecvNode(Symbol *s, const Type *t, antlr4::Token *tok) : TypedNode(tok)
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

class ProgramContractNode : public TypedNode
{
public:
    Symbol *sym;

    ProgramContractNode(Symbol *s, antlr4::Token *tok) : TypedNode(tok)
    {
        sym = s;
    }

    const TypeUnit *getType() override { return Types::UNIT; }

    std::string toString() const override {
        return "CONTRACT NODE";
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class ProgramWeakenNode : public TypedNode // FIXME: COMBINE THIS WITH PREV AND USE ENUM FOR OP?
{
public:
    Symbol *sym;

    ProgramWeakenNode(Symbol *s, antlr4::Token *tok) : TypedNode(tok)
    {
        sym = s;
    }

    const TypeUnit *getType() override { return Types::UNIT; }

    std::string toString() const override {
        return "WEAKEN NODE";
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class ProgramExecNode : public TypedNode
{
public:
    TypedNode *prog;
    TypeChannel *chanType;

    ProgramExecNode(TypedNode *p, TypeChannel *c, antlr4::Token *tok) : TypedNode(tok)
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

class ProgramAcceptNode : public TypedNode
{
public:
    Symbol *sym;
    BlockNode *blk;

    ProgramAcceptNode(Symbol *s, BlockNode *b, antlr4::Token *tok) : TypedNode(tok)
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

class DefineEnumNode : public TypedNode
{
public:
    string name;
    TypeSum *sum;

    DefineEnumNode(string n, TypeSum *s, antlr4::Token *tok) : TypedNode(tok)
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

class DefineStructNode : public TypedNode
{
public:
    string name;
    TypeStruct *product;

    DefineStructNode(string n, TypeStruct *p, antlr4::Token *tok) : TypedNode(tok)
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

class InitProductNode : public TypedNode
{
public:
    const TypeStruct *product;
    vector<TypedNode *> exprs;

    InitProductNode(const TypeStruct *p, vector<TypedNode *> e, antlr4::Token *tok) : TypedNode(tok)
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


class InitBoxNode : public TypedNode
{
public:
    const TypeBox *boxType;
    TypedNode * expr;

    InitBoxNode(const TypeBox *b, TypedNode * e, antlr4::Token *tok) : TypedNode(tok)
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

class DerefBoxNode : public TypedNode
{
public:
    const TypeBox *boxType;
    TypedNode * expr;
    bool is_rvalue; 

    DerefBoxNode(const TypeBox *b, TypedNode * e, bool rv, antlr4::Token *tok) : TypedNode(tok)
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

class WhileLoopNode : public TypedNode
{
public:
    TypedNode *cond;
    BlockNode *blk;

    WhileLoopNode(TypedNode *c, BlockNode *t, antlr4::Token *tok) : TypedNode(tok)
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

class ExternNode : public TypedNode
{
private:
    Symbol *sym;
    const TypeInvoke *ty; // FIXME: ISNT REALLY NEEDED EXCEPT FOR MAKING CASTS EASIER

public:
    ExternNode(std::string id, ParameterListNode p, const Type *r, bool v, antlr4::Token *tok) : TypedNode(tok)
    {
        vector<const Type *> paramTypes;

        for (ParameterNode param : p)
        {
            paramTypes.push_back(param.type);
        }

        ty = new TypeInvoke(paramTypes, r, v, true);
        sym = new Symbol(id, ty, true, true);
    }

    const TypeInvoke *getType() override
    {
        return ty;
    }

    std::string toString() const override {
        return "EXTERN NODE";
    }

    Symbol *getSymbol() { return sym; } // WHY ARENT THINGS LIKE THIS CONST?
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class InvocationNode : public TypedNode
{
public:
    TypedNode *fn;
    vector<TypedNode *> args;
    vector<const Type *> paramType; // Used for sums

    InvocationNode(TypedNode *f, vector<TypedNode *> a, vector<const Type *> p, antlr4::Token *tok) : TypedNode(tok)
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

class FieldAccessNode : public TypedNode
{
private:
    const Type *type;

public:
    Symbol *symbol;
    vector<pair<string, const Type *>> accesses;
    bool is_rvalue;

    FieldAccessNode(antlr4::Token *tok, Symbol *f, bool rv, vector<pair<string, const Type *>> r = {}) : TypedNode(tok)
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

class ArrayAccessNode : public TypedNode
{
public:
    FieldAccessNode *field;
    TypedNode *indexExpr;
    bool is_rvalue;

    ArrayAccessNode(FieldAccessNode *f, TypedNode *i, bool r, antlr4::Token *tok) : TypedNode(tok)
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

class AssignNode : public TypedNode
{
public:
    TypedNode *var; // FIXME: DO THESE FIELDS BETTER (THEIR TYPES AND SUCH)
    TypedNode *val;

    AssignNode(TypedNode *sym, TypedNode *v, antlr4::Token *tok) : TypedNode(tok)
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

class BinaryRelNode : public TypedNode
{
public:
    BinaryRelOperator op;
    TypedNode *lhs;
    TypedNode *rhs;

    BinaryRelNode(BinaryRelOperator o, TypedNode *l, TypedNode *r, antlr4::Token *tok) : TypedNode(tok)
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

class BinaryArithNode : public TypedNode
{
public:
    BinaryArithOperator op;
    TypedNode *lhs;
    TypedNode *rhs;

    BinaryArithNode(BinaryArithOperator o, TypedNode *l, TypedNode *r, antlr4::Token *tok) : TypedNode(tok)
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

class EqExprNode : public TypedNode
{
public:
    EqExprOperator op;
    TypedNode *lhs;
    TypedNode *rhs;

    EqExprNode(EqExprOperator o, TypedNode *l, TypedNode *r, antlr4::Token *tok) : TypedNode(tok)
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

class UnaryExprNode : public TypedNode
{
public:
    UnaryOperator op;
    TypedNode *value;

    UnaryExprNode(UnaryOperator o, TypedNode *v, antlr4::Token *tok) : TypedNode(tok)
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

class LogAndExprNode : public TypedNode
{
public:
    vector<TypedNode *> exprs;

    LogAndExprNode(vector<TypedNode *> e, antlr4::Token *tok) : TypedNode(tok)
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

class LogOrExprNode : public TypedNode
{
public:
    vector<TypedNode *> exprs;

    LogOrExprNode(vector<TypedNode *> e, antlr4::Token *tok) : TypedNode(tok)
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

class StringConstNode : public TypedNode
{
public:
    string value;

    StringConstNode(string s, antlr4::Token *tok) : TypedNode(tok)
    {
        value = s;
    }

    const TypeStr *getType() override { return Types::STR; }

    std::string toString() const override {
        return "StrConst";
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class BooleanConstNode : public TypedNode
{
public:
    bool value;

    BooleanConstNode(bool b, antlr4::Token *tok) : TypedNode(tok)
    {
        value = b;
    }

    const TypeBool *getType() override { return Types::BOOL; }

    std::string toString() const override {
        return "BOOL CONST";
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class IConstExprNode : public TypedNode
{
public:
    int value;

    IConstExprNode(int v, antlr4::Token *tok) : TypedNode(tok)
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

typedef variant<DefineEnumNode *, DefineStructNode *, ProgramDefNode *, LambdaConstNode *> DefinitionNode;

class CompilationUnitNode
{
public:
    vector<ExternNode *> externs;
    vector<DefinitionNode> defs;

    CompilationUnitNode(vector<ExternNode *> e, vector<DefinitionNode> d)
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

class VarDeclNode : public TypedNode
{
public:
    vector<AssignmentNode *> assignments;
    VarDeclNode(vector<AssignmentNode *> a, antlr4::Token *tok) : TypedNode(tok)
    {
        assignments = a;
    }

    const TypeUnit *getType() override { return Types::UNIT; }


    std::string toString() const override {
        return "VAR DECL NODE";
    }


    std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class MatchStatementNode : public TypedNode
{
public:
    const TypeSum *matchType;
    TypedNode *checkExpr;
    vector<pair<Symbol *, TypedNode *>> cases;

    vector<TypedNode *> post;

    MatchStatementNode(const TypeSum *m, TypedNode *e, vector<pair<Symbol *, TypedNode *>> c, std::vector<TypedNode *> p, antlr4::Token *tok) : TypedNode(tok)
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

class ChannelCaseStatementNode : public TypedNode
{
public:
    // TypedNode *checkExpr;
    Symbol *sym;
    vector<TypedNode *> cases;
    vector<TypedNode *> post;

    ChannelCaseStatementNode(Symbol *c, vector<TypedNode *> v, vector<TypedNode *> p, antlr4::Token *tok) : TypedNode(tok)
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

class ProgramProjectNode : public TypedNode // FIXME: DO BETTER, VERY SIMILAR TO SEND
{
public:
    Symbol *sym;
    unsigned int projectIndex;

    ProgramProjectNode(Symbol *s, unsigned int p, antlr4::Token *tok) : TypedNode(tok)
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
    if (dynamic_cast<ReturnNode *>(n))
        return true;
    if (dynamic_cast<ExitNode *>(n))
        return true;

    if (BlockNode *bn = dynamic_cast<BlockNode *>(n))
    {
        return endsInReturn(bn->exprs);
    }

    // FIXME: DO THESE BETTER!
    if (ConditionalStatementNode *cn = dynamic_cast<ConditionalStatementNode *>(n))
    {
        // if(cn->post.size())
        return endsInReturn(cn->post);
    }

    if (MatchStatementNode *cn = dynamic_cast<MatchStatementNode *>(n))
    {
        // if(cn->post.size())
        return endsInReturn(cn->post);
    }

    if (SelectStatementNode *cn = dynamic_cast<SelectStatementNode *>(n))
    {
        // if(cn->post.size())
        return endsInReturn(cn->post);
    }

    if(SelectAlternativeNode * cn = dynamic_cast<SelectAlternativeNode*>(n))
    {
        return endsInReturn(cn->eval);
    }

    // if(MatchStatementNode * cn = dynamic_cast<MatchStatementNode *>(n))
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
    if (BlockNode *bn = dynamic_cast<BlockNode *>(n))
    {
        return endsInBranch(bn->exprs);
    }

    // FIXME: DO THESE BETTER!
    if (ConditionalStatementNode *cn = dynamic_cast<ConditionalStatementNode *>(n))
    {
        return true; 
    }

    if (MatchStatementNode *cn = dynamic_cast<MatchStatementNode *>(n))
    {
        return true; 
    }

    if (SelectStatementNode *cn = dynamic_cast<SelectStatementNode *>(n))
    {
        return true; 
    }

    if (SelectAlternativeNode *cn = dynamic_cast<SelectAlternativeNode *>(n))
    {
        return endsInBranch(cn->eval);
        // return true; 
    }

    if(ChannelCaseStatementNode * sn = dynamic_cast<ChannelCaseStatementNode*>(n))
    {
        return true; 
    }

    // if(MatchStatementNode * cn = dynamic_cast<MatchStatementNode *>(n))
    // {
    //     // if(cn->post.size())
    //     return endsInReturn(cn->post);
    // }

    return false;
}