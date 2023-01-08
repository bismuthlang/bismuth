#pragma once

#include "Symbol.h" //Should give us symbols and yyues...
#include <variant>

using namespace std;
using llvm::Value;


//FIXME: HAVE COMPILER ADD COMMENTS TO DOCUMENT COMPLEX TYPES?


class TypedASTVisitor;

class TypedNode
{
public:
    virtual ~TypedNode() = default;

    virtual const Type *getType() = 0;

    virtual std::any accept(TypedASTVisitor *a) = 0;
};

class SelectAlternativeNode;
class SelectStatementNode;
class ConditionNode;
class BlockNode;

class LambdaConstNode;
class ProgramDefNode;
class FunctionDefNode;
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
class WhileLoopNode;
class ExternNode;
class InvocationNode;
class FieldAccessNode;
class VariableIDNode;
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

class TypedASTVisitor
{
public:
    virtual ~TypedASTVisitor() = default;

    // virtual std::optional<Value *> visit(SelectAlternativeNode *n) = 0;
    virtual std::optional<Value *> visit(SelectStatementNode *n) = 0;
    virtual std::optional<Value *> visit(ConditionNode *n) = 0;
    virtual std::optional<Value *> visit(BlockNode *n) = 0;
    virtual std::optional<Value *> visit(LambdaConstNode *n) = 0;
    virtual std::optional<Value *> visit(ProgramDefNode *n) = 0;
    // virtual std::optional<Value *> visit(FunctionDefNode *n) = 0; //FIXME
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
    virtual std::optional<Value *> visit(WhileLoopNode *n) = 0;
    virtual std::optional<Value *> visit(ExternNode *n) = 0;
    virtual std::optional<Value *> visit(InvocationNode *n) = 0;
    virtual std::optional<Value *> visit(FieldAccessNode *n) = 0;
    virtual std::optional<Value *> visit(VariableIDNode *n) = 0;
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

    // private: //FIXME: DO SOMETHING FOR THE ONES WE DONT NEED/USE
    std::any any_visit(SelectAlternativeNode *n) { return this->visit(n); }
    std::any any_visit(SelectStatementNode *n) { return this->visit(n); }
    std::any any_visit(ConditionNode *n) { return this->visit(n); }
    std::any any_visit(BlockNode *n) { return this->visit(n); }
    std::any any_visit(LambdaConstNode *n) { return this->visit(n); }
    std::any any_visit(ProgramDefNode *n) { return this->visit(n); }
    std::any any_visit(FunctionDefNode *n) { return this->visit(n); }
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
    std::any any_visit(WhileLoopNode *n) { return this->visit(n); }
    std::any any_visit(ExternNode *n) { return this->visit(n); }
    std::any any_visit(InvocationNode *n) { return this->visit(n); }
    std::any any_visit(FieldAccessNode *n) { return this->visit(n); }
    std::any any_visit(VariableIDNode *n) { return this->visit(n); }
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
    std::any any_visit(MatchStatementNode * n) {return this->visit(n); }
    std::any any_visit(ExitNode *n) { return this->visit(n); }

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

class SelectAlternativeNode : public TypedNode // FIXME: DO BETTER!
{
public:
    TypedNode *check;
    TypedNode *eval;

    SelectAlternativeNode(TypedNode *c, TypedNode *e)
    {
        check = c;
        eval = e;
    }

    const TypeBot *getType() override { return Types::UNDEFINED; }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class SelectStatementNode : public TypedNode
{
public:
    vector<SelectAlternativeNode *> nodes;
    vector<TypedNode*> post;

    SelectStatementNode(vector<SelectAlternativeNode *> n, vector<TypedNode*> p)
    {
        nodes = n;
        post = p; 
    }

    const TypeBot *getType() override { return Types::UNDEFINED; }
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class ConditionNode : public TypedNode // FIXME: DO BETTER
{
public:
    TypedNode *condition;

    ConditionNode(TypedNode *c)
    {
        condition = c;
    }

    const TypeBot *getType() override { return Types::UNDEFINED; } // FIXME: DO BETTER
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

// FIXME: SHOULD THERE BE A EXPRESSION VS STATEMENT DIFFERENCE IN THESE? MAYBE NOT I GUESS B/C TECHNICALLY CALLS COULD HAVE BEEN SORT OF EITHER? BUT NOT ANYMORE? IDK EVERYTHING KIND OF BECOMES EXPR WHEN FUNCTIONAL
class BlockNode : public TypedNode
{
public:
    vector<TypedNode *> exprs;

    BlockNode(vector<TypedNode *> e)
    {
        exprs = e;
    }

    vector<TypedNode *> getExprs() { return exprs; }

    const TypeBot *getType() override { return Types::UNDEFINED; } // FIXME: DO BETTER
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
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

typedef vector<ParameterNode> ParameterListNode; // FIXME: NOT EXACTLY A NODE

class LambdaConstNode : public TypedNode
{
private:
    TypeInvoke *type;

public:
    string name; 
    vector<Symbol *> paramSymbols;
    const Type *retType;
    BlockNode *block;

    LambdaConstNode(vector<Symbol *> p, const Type *r, BlockNode *b, string n="LAM")
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

    ProgramDefNode(string n, Symbol *cn, BlockNode *b, const TypeProgram *ty)
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
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class FunctionDefNode : public TypedNode
{
public:
    Symbol *sym;
    const TypeInvoke *ty; // FIXME: ISNT REALLY NEEDED EXCEPT FOR MAKING CASTS EASIER
    BlockNode *block;

    //FIXME: WHY DO WE REQUIRE PARAM LIST NODE AND SUCH WEHEN WE HAVE TO CREATE THAT MANUALLY AS PART OF TYPECHECK ANYWAYS?
    FunctionDefNode(std::string id, ParameterListNode p, const Type *r, BlockNode * b)//string n, Symbol *cn, BlockNode *b, const TypeProgram *ty)
    {
        vector<const Type *> paramTypes;

        for (ParameterNode param : p)
        {
            paramTypes.push_back(param.type);
        }

        ty = new TypeInvoke(paramTypes, r, false, true);
        sym = new Symbol(id, ty, true, true);

        block = b;
    }

    const TypeInvoke *getType() override
    {
        return ty;
    }
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class ConditionalStatementNode : public TypedNode
{
public:
    ConditionNode *cond;
    BlockNode *trueBlk;
    std::optional<BlockNode *> falseOpt;

    std::vector<TypedNode*> post;

    ConditionalStatementNode(ConditionNode *c, BlockNode *t, std::vector<TypedNode*> p, std::optional<BlockNode *> f = {})
    {
        cond = c;
        trueBlk = t;
        falseOpt = f;
        post = p;
    }

    const TypeBot *getType() override { return Types::UNDEFINED; } // FIXME: DO BETTER
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class ReturnNode : public TypedNode
{
public:
    // First is the actual type
    optional<pair<const Type *, TypedNode *>> expr;

    ReturnNode(optional<pair<const Type *, TypedNode *>> e = {})
    {
        expr = e;
    }

    // const Type *getType() override {
    //     return (expr) ? expr.value()->getType() : Types::UNDEFINED;
    //  } // FIXME: DO BETTER

    const TypeBot *getType() override { return Types::UNDEFINED; } // FIXME: DO BETTER
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class ExitNode : public TypedNode
{
public:

    ExitNode()
    {
    }

    const TypeBot *getType() override { return Types::UNDEFINED; } // FIXME: DO BETTER
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class ProgramSendNode : public TypedNode
{
public:
    Symbol *sym;
    TypedNode *expr;

    ProgramSendNode(Symbol *s, TypedNode *e)
    {
        sym = s;
        expr = e;
    }

    const TypeBot *getType() override { return Types::UNDEFINED; } // FIXME: DO BETTER
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class ProgramRecvNode : public TypedNode
{
public:
    Symbol *sym;
    const Type *ty;

    ProgramRecvNode(Symbol *s, const Type *t)
    {
        sym = s;
        // expr = e;
        ty = t;
    }

    const Type *getType() override { return ty; }
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class ProgramContractNode : public TypedNode
{
public:
    Symbol *sym;

    ProgramContractNode(Symbol *s)
    {
        sym = s;
    }

    const TypeBot *getType() override { return Types::UNDEFINED; } // FIXME: DO BETTER
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class ProgramWeakenNode : public TypedNode // FIXME: COMBINE THIS WITH PREV AND USE ENUM FOR OP?
{
public:
    Symbol *sym;

    ProgramWeakenNode(Symbol *s)
    {
        sym = s;
    }

    const TypeBot *getType() override { return Types::UNDEFINED; } // FIXME: DO BETTER
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class ProgramExecNode : public TypedNode // FIXME: DO BETTER
{
public:
    Symbol *sym;
    TypeChannel *chanType;

    ProgramExecNode(Symbol *s, TypeChannel *c)
    {
        sym = s;
        chanType = c;
    }

    const TypeChannel *getType() override { return chanType; }
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class ProgramAcceptNode : public TypedNode // FIXME: DO BETTER
{
public:
    Symbol *sym;
    BlockNode *blk;

    ProgramAcceptNode(Symbol *s, BlockNode *b)
    {
        sym = s;
        blk = b;
    }

    const TypeBot *getType() override { return Types::UNDEFINED; } // FIXME: DO BETTER
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class DefineEnumNode : public TypedNode
{
public:
    string name;
    TypeSum *sum;

    DefineEnumNode(string n, TypeSum *s)
    {
        name = n;
        // cases = c;
        sum = s;
    }

    const TypeBot *getType() override { return Types::UNDEFINED; } // FIXME: DO BETTER
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class DefineStructNode : public TypedNode
{
public:
    string name;
    TypeStruct *product;

    DefineStructNode(string n, TypeStruct *p)
    {
        name = n;
        // cases = c;
        product = p;
    }

    const TypeBot *getType() override { return Types::UNDEFINED; } // FIXME: DO BETTER
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class InitProductNode : public TypedNode
{
public:
    const TypeStruct *product;
    vector<TypedNode *> exprs;

    InitProductNode(const TypeStruct *p, vector<TypedNode *> e)
    {
        product = p;
        exprs = e;
    }

    const TypeStruct *getType() override { return product; }
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class WhileLoopNode : public TypedNode
{
public:
    ConditionNode *cond;
    BlockNode *blk;

    WhileLoopNode(ConditionNode *c, BlockNode *t)
    {
        cond = c;
        blk = t;
    }

    const TypeBot *getType() override { return Types::UNDEFINED; } // FIXME: DO BETTER
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class ExternNode : public TypedNode
{ // FIXME: DO BETTER
private:
    Symbol *sym;
    const TypeInvoke *ty; // FIXME: ISNT REALLY NEEDED EXCEPT FOR MAKING CASTS EASIER

public:
    ExternNode(std::string id, ParameterListNode p, const Type *r, bool v)
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

    Symbol *getSymbol() { return sym; } // FIXME: WHY ARENT THINGS LIKE THIS CONST?
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class InvocationNode : public TypedNode
{
public:
    TypedNode *fn;
    vector<TypedNode *> args;

    InvocationNode(TypedNode *f, vector<TypedNode *> a)
    {
        fn = f;
        args = a;
    }

    const Type *getType() override
    {
        // FIXME: DO BETTER?

        return dynamic_cast<const TypeInvoke *>(fn->getType())->getReturnType();
    }
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class FieldAccessNode : public TypedNode
{
private:
    const Type *type;

public:
    Symbol *symbol; // FIXME: SHOULD THESE BE SYMBOLS OR SYMBOL CONTEXTS?
    vector<pair<string, const Type *>> accesses;
    bool is_rvalue;

    FieldAccessNode(Symbol *f, bool rv, vector<pair<string, const Type *>> r = {})
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
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class VariableIDNode : public TypedNode // FIXME: DO BETTER
{

public:
    Symbol *symbol;
    bool is_rvalue;

    VariableIDNode(Symbol *f, bool r)
    {
        symbol = f;
        is_rvalue = r;
    }

    const Type *getType() override
    {
        return symbol->type;
    }

    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class ArrayAccessNode : public TypedNode
{
public:
    FieldAccessNode *field;
    TypedNode *indexExpr;
    bool is_rvalue;

    ArrayAccessNode(FieldAccessNode *f, TypedNode *i, bool r)
    {
        field = f;
        indexExpr = i;
        is_rvalue = r;
    }

    const Type *getType() override
    {
        return dynamic_cast<const TypeArray *>(field->getType())->getValueType(); // FIXME: POTENTIAL ERROR?
    }
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class AssignNode : public TypedNode
{
public:
    TypedNode *var; // FIXME: DO THESE FIELDS BETTER (THEIR TYPES AND SUCH)
    TypedNode *val;

    AssignNode(TypedNode *sym, TypedNode *v)
    {
        var = sym;
        val = v;
    }

    const TypeBot *getType() override
    {
        return Types::UNDEFINED; // FIXME: DO BETTER
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

    BinaryRelNode(BinaryRelOperator o, TypedNode *l, TypedNode *r)
    {
        op = o;
        lhs = l;
        rhs = r;
    }

    const TypeBool *getType() override { return Types::BOOL; }
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

    BinaryArithNode(BinaryArithOperator o, TypedNode *l, TypedNode *r)
    {
        op = o;
        lhs = l;
        rhs = r;
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

    EqExprNode(EqExprOperator o, TypedNode *l, TypedNode *r)
    {
        op = o;
        lhs = l;
        rhs = r;
    }

    const TypeBool *getType() override { return Types::BOOL; }
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

    UnaryExprNode(UnaryOperator o, TypedNode *v)
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
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class LogAndExprNode : public TypedNode
{
public:
    vector<TypedNode *> exprs;

    LogAndExprNode(vector<TypedNode *> e)
    {
        exprs = e;
    }

    vector<TypedNode *> getExprs() { return exprs; }

    const TypeBool *getType() override { return Types::BOOL; }
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class LogOrExprNode : public TypedNode
{
public:
    vector<TypedNode *> exprs;

    LogOrExprNode(vector<TypedNode *> e)
    {
        exprs = e;
    }

    vector<TypedNode *> getExprs() { return exprs; }

    const TypeBool *getType() override { return Types::BOOL; }
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class StringConstNode : public TypedNode
{
public:
    string value;

    StringConstNode(string s)
    {
        value = s;
    }

    const TypeStr *getType() override { return Types::STR; }
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class BooleanConstNode : public TypedNode
{
public:
    bool value;

    BooleanConstNode(bool b)
    {
        value = b;
    }

    const TypeBool *getType() override { return Types::BOOL; }
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class IConstExprNode : public TypedNode
{
public:
    int value;

    IConstExprNode(int v)
    {
        value = v;
    }

    const TypeInt *getType() override { return Types::INT; }
    virtual std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

/////////////////////

typedef variant<DefineEnumNode *, DefineStructNode *, ProgramDefNode *, LambdaConstNode*> DefinitionNode;

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
    VarDeclNode(vector<AssignmentNode *> a)
    {
        assignments = a;
    }

    const TypeBot *getType() override
    {
        return Types::UNDEFINED; // FIXME: DO BETTER
    }

    std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }
};

class MatchStatementNode : public TypedNode
{
public:
    const TypeSum * matchType; 
    TypedNode * checkExpr; 
    vector<pair<Symbol *, TypedNode *>> cases; 

    vector<TypedNode*> post;

    MatchStatementNode(const TypeSum * m, TypedNode * e, vector<pair<Symbol *, TypedNode *>> c, std::vector<TypedNode*> p)
    {
        matchType = m; 
        checkExpr = e; 
        cases = c; 
        
        post = p; 
    }

    std::any accept(TypedASTVisitor *a) override { return a->any_visit(this); }

    const TypeBot *getType() override
    {
        return Types::UNDEFINED; // FIXME: DO BETTER
    }
};





/**************************************************
 * 
 * UTILITIES
 * 
 **************************************************/
inline bool endsInReturn(TypedNode * n);

inline bool endsInReturn(vector<TypedNode *> n)
{
    if(n.size() == 0) return false; 
    return endsInReturn(n.at(n.size() - 1));
}

inline bool endsInReturn(TypedNode * n)
{
    if(dynamic_cast<ReturnNode *>(n)) return true; 
    if(dynamic_cast<ExitNode *>(n)) return true; 

    if(BlockNode * bn = dynamic_cast<BlockNode*>(n))
    {
        return endsInReturn(bn->exprs);
        // if(bn->exprs.size() == 0) return false; 
        // return endsInReturn((bn->exprs.at(bn->exprs.size() - 1)));
        // return bn->exprs.size() > 0 && dynamic_cast<ReturnNode *>(bn->exprs.at(bn->exprs.size() - 1));
    }

    //FIXME: DO THESE BETTER!
    if(ConditionalStatementNode * cn = dynamic_cast<ConditionalStatementNode *>(n))
    {
        // if(cn->post.size())
        return endsInReturn(cn->post);
    }

    if(MatchStatementNode * cn = dynamic_cast<MatchStatementNode *>(n))
    {
        // if(cn->post.size())
        return endsInReturn(cn->post);
    }

    if(SelectStatementNode * cn = dynamic_cast<SelectStatementNode *>(n))
    {
        // if(cn->post.size())
        return endsInReturn(cn->post);
    }

    // if(MatchStatementNode * cn = dynamic_cast<MatchStatementNode *>(n))
    // {
    //     // if(cn->post.size())
    //     return endsInReturn(cn->post);
    // }

    return false; 
}   