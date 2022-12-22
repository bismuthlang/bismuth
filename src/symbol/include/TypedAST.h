#pragma once

#include "Symbol.h" //Should give us symbols and yyues...
#include <variant>

using namespace std;

class TypedNode
{
public:
    virtual ~TypedNode() = default;

    virtual const Type *getType() = 0;
};

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
};

class SelectStatementNode : public TypedNode
{
public:
    vector<SelectAlternativeNode *> nodes;

    SelectStatementNode(vector<SelectAlternativeNode *> n)
    {
        nodes = n;
    }

    const TypeBot *getType() override { return Types::UNDEFINED; }
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
    ParameterListNode paramList;
    const Type *retType;
    BlockNode *block;

    LambdaConstNode(ParameterListNode p, const Type *r, BlockNode *b)
    {
        paramList = p;
        retType = r;
        block = b;

        vector<const Type *> paramTypes;

        for (ParameterNode p : paramList)
        {
            paramTypes.push_back(p.type);
        }

        type = new TypeInvoke(paramTypes, retType);
    }

    const TypeInvoke *getType() override
    {
        return type;
    }
};

class ProgramDefNode : public TypedNode
{
private:
    const TypeProgram *type;

public:
    string name;
    string channelName;
    // TypeChannel * channelType;
    BlockNode *block;

    ProgramDefNode(string n, string cn, BlockNode *b, const TypeProgram *ty)
    {
        name = n;
        channelName = cn;
        // channelType = ct;
        block = b;
        type = ty;
        // type = new TypeInvoke(paramTypes, retType);
    }

    const TypeProgram *getType() override
    {
        return type;
    }
};

class ConditionalStatementNode : public TypedNode
{
public:
    ConditionNode *cond;
    BlockNode *trueBlk;
    std::optional<BlockNode *> falseOpt;

    ConditionalStatementNode(ConditionNode *c, BlockNode *t, std::optional<BlockNode *> f = {})
    {
        cond = c;
        trueBlk = t;
        falseOpt = f;
    }

    const TypeBot *getType() override { return Types::UNDEFINED; } // FIXME: DO BETTER
};

class ReturnNode : public TypedNode
{
public:
    optional<TypedNode *> expr;

    ReturnNode(optional<TypedNode *> e = {})
    {
        expr = e;
    }

    // const Type *getType() override {
    //     return (expr) ? expr.value()->getType() : Types::UNDEFINED;
    //  } // FIXME: DO BETTER

    const TypeBot *getType() override { return Types::UNDEFINED; } // FIXME: DO BETTER
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
};

class FieldAccessNode : public TypedNode
{
private:
    const Type *type;

public:
    Symbol *symbol; // FIXME: SHOULD THESE BE SYMBOLS OR SYMBOL CONTEXTS?
    vector<pair<string, const Type *>> accesses;

    FieldAccessNode(Symbol *f, vector<pair<string, const Type *>> r = {})
    {
        symbol = f;
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
};

class VariableIDNode : public TypedNode // FIXME: DO BETTER
{

public:
    Symbol *symbol;

    VariableIDNode(Symbol *f)
    {
        symbol = f;
    }

    const Type *getType() override
    {
        return symbol->type;
    }
};

class ArrayAccessNode : public TypedNode
{
public:
    FieldAccessNode *field;
    TypedNode *indexExpr;

    ArrayAccessNode(FieldAccessNode *f, TypedNode *i)
    {
        field = f;
        indexExpr = i;
    }

    const Type *getType() override
    {
        return dynamic_cast<const TypeArray *>(field->getType())->getValueType(); // FIXME: POTENTIAL ERROR?
    }
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
};

class EqExprNode : public TypedNode
{
public:
    TypedNode *lhs;
    TypedNode *rhs;

    EqExprNode(TypedNode *l, TypedNode *r)
    {
        lhs = l;
        rhs = r;
    }

    const TypeBool *getType() override { return Types::BOOL; }
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
};

/////////////////////

typedef variant<DefineEnumNode *, DefineStructNode *, ProgramDefNode *> DefinitionNode;

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
};