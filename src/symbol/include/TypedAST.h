#pragma once

#include "Symbol.h" //Should give us symbols and yyues...
#include <variant>

using namespace std;

template <class T>
class TypedASTVisitor;

class TypedNode
{
public:
    virtual ~TypedNode() = default;

    virtual const Type *getType() = 0;

    // virtual void accept(visitor &v) = 0;
    virtual std::any accept(TypedASTVisitor<std::any> *a) = 0;
};


class SelectAlternativeNode;
class SelectStatementNode; 
class ConditionNode; 
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

template <class T>
class TypedASTVisitor
{
public:
    virtual ~TypedASTVisitor() = 0;
    virtual T visit(SelectAlternativeNode *n);
    virtual T visit(SelectStatementNode *n);
    virtual T visit(ConditionNode* n);
    virtual T visit(BlockNode *n);
    virtual T visit(LambdaConstNode *n);
    virtual T visit(ProgramDefNode *n);
    virtual T visit(ConditionalStatementNode *n);
    virtual T visit(ReturnNode *n);
    virtual T visit(ProgramSendNode *n);
    virtual T visit(ProgramRecvNode *n);
    virtual T visit(ProgramContractNode *n);
    virtual T visit(ProgramWeakenNode *n);
    virtual T visit(ProgramExecNode *n);
    virtual T visit(ProgramAcceptNode *n);
    virtual T visit(DefineEnumNode *n);
    virtual T visit(DefineStructNode *n);
    virtual T visit(InitProductNode *n);
    virtual T visit(WhileLoopNode *n);
    virtual T visit(ExternNode *n);
    virtual T visit(InvocationNode *n);
    virtual T visit(FieldAccessNode *n);
    virtual T visit(VariableIDNode *n);
    virtual T visit(ArrayAccessNode *n);
    virtual T visit(AssignNode *n);
    virtual T visit(BinaryRelNode *n);
    virtual T visit(BinaryArithNode *n);
    virtual T visit(EqExprNode *n);
    virtual T visit(UnaryExprNode *n);
    virtual T visit(LogAndExprNode *n);
    virtual T visit(LogOrExprNode *n);
    virtual T visit(StringConstNode *n);
    virtual T visit(BooleanConstNode *n);
    virtual T visit(IConstExprNode *n);
    virtual T visit(CompilationUnitNode *n);

    T accept(TypedNode *n) {
        return dynamic_cast<T>(n->accept(this)); //Hacky, but completley safe
    }
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

    // template <class T>
    // virtual void accept(TypedASTVisitor<T> v)
    // {

    // }

    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    vector<Symbol*> paramSymbols;
    const Type *retType;
    BlockNode *block;

    LambdaConstNode(vector<Symbol*> p, const Type *r, BlockNode *b)
    {
        // paramList = p;
        paramSymbols = p; 
        retType = r;
        block = b;

        vector<const Type *> paramTypes;

        for (Symbol* p : paramSymbols)
        {
            paramTypes.push_back(p->type);
        }

        type = new TypeInvoke(paramTypes, retType);
    }

    const TypeInvoke *getType() override
    {
        return type;
    }
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
};

class ProgramDefNode : public TypedNode
{
private:
    const TypeProgram *type;

public:
    string name;
    Symbol * channelSymbol;
    // TypeChannel * channelType;
    BlockNode *block;

    ProgramDefNode(string n, Symbol* cn, BlockNode *b, const TypeProgram *ty)
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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

    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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
    virtual std::any accept(TypedASTVisitor<std::any> *a) override { return a->visit(this); }
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

    std::any accept(TypedASTVisitor<std::any> *a) { return a->visit(this); }
};