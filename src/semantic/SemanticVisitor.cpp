#include "SemanticVisitor.h"

const Type *SemanticVisitor::visitCtx(WPLParser::CompilationUnitContext *ctx)
{
    // Enter initial scope
    stmgr->enterScope(StopType::NONE);

    for (auto e : ctx->defs)
    {
        if (WPLParser::DefineProgramContext *fnCtx = dynamic_cast<WPLParser::DefineProgramContext *>(e))
        {
            std::string id = fnCtx->defineProc()->name->getText();

            std::optional<SymbolContext> opt = stmgr->lookup(id);

            if (opt)
            {
                errorHandler.addSemanticError(ctx->getStart(), "Unsupported redeclaration of program " + id);
                // return Types::UNDEFINED;
            }

            const Type *ty = any2Type(fnCtx->defineProc()->ty->accept(this));

            // FIXME: NEED TO DEAL WITH CHANNEL TYPE BETTER!
            // const Protocol *channelType = any2Protocol(fnCtx->defineProc()->ty->accept(this));
            if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(ty))
            {
                const TypeProgram *funcType = new TypeProgram(channel, false);
                Symbol *funcSymbol = new Symbol(id, funcType, true, true);
                // FIXME: test name collisions with externs
                stmgr->addSymbol(funcSymbol);
                bindings->bind(fnCtx->defineProc(), funcSymbol);
            }
            else
            {
                errorHandler.addSemanticError(ctx->getStart(), "Process expected channel!");
            }
            // errorHandler.addSemanticCritWarning(ctx->getStart(), "Currently, only FUNC, PROC, EXTERN, and variable declarations allowed at top-level. Not: " + e->getText());
        }
        else
        {
            e->accept(this);
        }
    }

    // Visit externs first; they will report any errors if they have any.
    for (auto e : ctx->extens)
    {
        this->visitCtx(e);
    }

    // Auto forward decl

    // Visit the statements contained in the unit
    for (auto e : ctx->defs)
    {
        // e->accept(this);
        if (WPLParser::DefineProgramContext *fnCtx = dynamic_cast<WPLParser::DefineProgramContext *>(e))
        {
            e->accept(this);
        }
    }

    /*******************************************
     * Extra checks depending on compiler flags
     *******************************************/

    if (flags & CompilerFlags::NO_RUNTIME)
    {
        /**********************************************************
         * As there is no runtime, we need to make sure that
         * there is NO main block and that we have a program block
         **********************************************************/

        if (stmgr->lookup("main"))
        {
            errorHandler.addSemanticError(ctx->getStart(), "When compiling with no-runtime, main is reserved!");
        }

        // Check that program is invokeable and correctly defined.
        {
            std::optional<SymbolContext> opt = stmgr->lookup("program");
            if (!opt)
            {
                errorHandler.addSemanticError(ctx->getStart(), "When compiling with no-runtime, program() must be defined!");
            }
            else
            {
                Symbol *sym = opt.value().second;

                if (const TypeInvoke *inv = dynamic_cast<const TypeInvoke *>(sym->type))
                {
                    if (inv->getParamTypes().size() != 0)
                    {
                        errorHandler.addSemanticError(ctx->getStart(), "When compiling with no-runtime, program must not require arguments!");
                    }

                    {
                        std::optional<const Type *> retOpt = inv->getReturnType();

                        if (!retOpt || !dynamic_cast<const TypeInt *>(retOpt.value()))
                        {
                            errorHandler.addSemanticError(ctx->getStart(), "When compiling with no-runtime, program() must return INT");
                        }
                    }
                }
                else
                {
                    errorHandler.addSemanticError(ctx->getStart(), "When compiling with no-runtime, program() must be an invokable!");
                }
            }
        }
    }

    std::vector<const Symbol *> uninf = stmgr->getCurrentScope().value()->getUninferred(); // TODO: shouldn't ever be an issue, but still.

    // If there are any uninferred symbols, then add it as a compiler error as we won't be able to resolve them
    // due to the var leaving the scope
    if (uninf.size() > 0)
    {
        std::ostringstream details;

        for (auto e : uninf)
        {
            details << e->toString() << "; ";
        }

        errorHandler.addSemanticError(ctx->getStart(), "Uninferred types in context: " + details.str());
    }
    // Return UNDEFINED as this should be viewed as a statement and not something assignable
    return Types::UNDEFINED;
}

const Type *SemanticVisitor::visitCtx(WPLParser::InvocationContext *ctx)
{
    const Type *type = [this](WPLParser::InvocationContext *ctx) // Huh, interesting how we probably can't get the ctx from this
    {
        if (ctx->lam)
            return visitCtx(ctx->lam);

        /*
         * Look up the symbol to make sure that it is defined
         */

        const Type *type = any2Type(ctx->field->accept(this));
        std::optional<Symbol *> opt = bindings->getBinding(ctx->field->VARIABLE().at(ctx->field->VARIABLE().size() - 1)); // FIXME: Verify that the symbol type matches the return type ?

        if (!opt)
        {
            errorHandler.addSemanticError(ctx->getStart(), "Cannot invoke undefined function: " + ctx->field->getText());
            return Types::UNDEFINED;
        }

        /*
         * Given that the symbol is defined, check that it is a FUNC/PROC (something that we can invoke)
         */
        Symbol *sym = opt.value();

        // Bind the symbol
        bindings->bind(ctx, sym);

        return sym->type;
    }(ctx);

    std::string name = (ctx->lam) ? "lambda " : ctx->field->getText();

    if (const TypeInvoke *invokeable = dynamic_cast<const TypeInvoke *>(type))
    {
        /*
         * The symbol is something we can invoke, so check that we provide it with valid parameters
         */
        std::vector<const Type *> fnParams = invokeable->getParamTypes();

        /*
         *  If the symbol is NOT a variadic and the number of arguments we provide
         *      are not the same as the number in the invokable's definition
         *  OR the symbol IS a variadic and the number of arguments in the
         *      invokable's definition is greater than the number we provide,
         *
         * THEN we have an error as we do not provide a valid number of arguments
         * to allow for this invocation.
         */
        if (
            (!invokeable->isVariadic() && fnParams.size() != ctx->args.size()) || (invokeable->isVariadic() && fnParams.size() > ctx->args.size()))
        {
            std::ostringstream errorMsg;
            errorMsg << "Invocation of " << name << " expected " << fnParams.size() << " argument(s), but got " << ctx->args.size();
            errorHandler.addSemanticError(ctx->getStart(), errorMsg.str());
            return Types::UNDEFINED; // TODO: Could change this to the return type to catch more errors?
        }

        /*
         * Now that we have a valid number of parameters, we can make sure that
         * they have the correct types as per our arguments.
         *
         * To do this, we first loop through the number of parameters that WE provide
         * as this should be AT LEAST the same number as in the definition.
         */
        for (unsigned int i = 0; i < ctx->args.size(); i++)
        {
            // Get the type of the current argument
            const Type *providedType = any2Type(ctx->args.at(i)->accept(this));

            // If the invokable is variadic and has no specified type parameters, then we can
            // skip over subsequent checks--we just needed to run type checking on each parameter.
            if (invokeable->isVariadic() && i >= fnParams.size()) //&& fnParams.size() == 0)
            {
                if (dynamic_cast<const TypeBot *>(providedType))
                {
                    errorHandler.addSemanticError(ctx->getStart(), "Cannot provide " + providedType->toString() + " to a function.");
                }
                continue;
            }

            // Loop up the expected type. This is either the type at the
            // ith index OR the last type specified by the function
            // if i > fnParams.size() as that would imply we are
            // checking a variadic
            const Type *expectedType = fnParams.at(
                i < fnParams.size() ? i : (fnParams.size() - 1));

            // If the types do not match, report an error.
            if (providedType->isNotSubtype(expectedType))
            {
                std::ostringstream errorMsg;
                errorMsg << "Argument " << i << " provided to " << name << " expected " << expectedType->toString() << " but got " << providedType->toString();

                errorHandler.addSemanticError(ctx->getStart(), errorMsg.str());
            }
        }

        // Return the type of the invokable or BOT if it has none.
        return invokeable->getReturnType(); //.has_value() ? invokeable->getReturnType().value() : Types::UNDEFINED;
    }

    // Symbol was not an invokeable type, so report an error & return UNDEFINED.
    errorHandler.addSemanticError(ctx->getStart(), "Can only invoke PROC and FUNC, not " + name + " : " + type->toString());
    return Types::UNDEFINED;
}

const Type *SemanticVisitor::visitCtx(WPLParser::InitProductContext *ctx)
{
    std::string name = ctx->v->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(name);

    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Cannot initialize undefined product: " + name);
        return Types::UNDEFINED;
    }

    Symbol *sym = opt.value().second;

    // TODO: METHODIZE WITH INVOKE?
    bindings->bind(ctx, sym);

    if (const TypeStruct *product = dynamic_cast<const TypeStruct *>(sym->type))
    {
        std::vector<std::pair<std::string, const Type *>> elements = product->getElements();
        if (elements.size() != ctx->exprs.size())
        {
            std::ostringstream errorMsg;
            errorMsg << "Initialization of " << name << " expected " << elements.size() << " argument(s), but got " << ctx->exprs.size();
            errorHandler.addSemanticError(ctx->getStart(), errorMsg.str());
            return Types::UNDEFINED; // TODO: Could change this to the return type to catch more errors?
        }

        {
            unsigned int i = 0;

            for (auto eleItr : elements)
            {
                const Type *providedType = any2Type(ctx->exprs.at(i)->accept(this));

                if (providedType->isNotSubtype(eleItr.second))
                {
                    std::ostringstream errorMsg;
                    errorMsg << "Product init. argument " << i << " provided to " << name << " expected " << eleItr.second->toString() << " but got " << providedType->toString();

                    errorHandler.addSemanticError(ctx->getStart(), errorMsg.str());
                }
                // FIXME: WHAT HAPPENS IF VAR PASSED TO THIS?
                i++;
            }
        }

        return sym->type;
    }

    errorHandler.addSemanticError(ctx->getStart(), "Cannot initialize non-product type " + name + " : " + sym->type->toString());
    return Types::UNDEFINED;
}

const Type *SemanticVisitor::visitCtx(WPLParser::ArrayAccessContext *ctx)
{
    /*
     * Check that we are provided an INT for the index.
     */

    const Type *exprType = any2Type(ctx->index->accept(this));
    if (exprType->isNotSubtype(Types::INT))
    {
        errorHandler.addSemanticError(ctx->getStart(), "Array access index expected type INT but got " + exprType->toString());
    }

    /*
     * Look up the symbol and check that it is defined.
     */

    const Type *type = any2Type(ctx->field->accept(this));
    std::optional<Symbol *> opt = bindings->getBinding(ctx->field->VARIABLE().at(ctx->field->VARIABLE().size() - 1));

    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Cannot access value from undefined array: " + ctx->field->getText());
        return Types::UNDEFINED;
    }

    /*
     * Check that the symbol is of array type.
     */

    Symbol *sym = opt.value();
    if (const TypeArray *arr = dynamic_cast<const TypeArray *>(sym->type)) // FIXME: Verify that the symbol type matches the return type ?
    {
        bindings->bind(ctx, sym);
        return arr->getValueType(); // Return type of array
    }

    // Report error
    errorHandler.addSemanticError(ctx->getStart(), "Cannot use array access on non-array expression " + ctx->field->getText() + " : " + type->toString());
    return Types::UNDEFINED;
}

const Type *SemanticVisitor::visitCtx(WPLParser::ArrayOrVarContext *ctx)
{
    // Check if we are a var or an array
    if (ctx->var)
    {
        /*
         * Based on starter; Same as VAR
         *
         * Get the variable name and look it up in the symbol table
         */
        std::string id = ctx->var->getText();
        std::optional<SymbolContext> opt = stmgr->lookup(id);

        // If we can't find the variable, report an error as it is undefined.
        if (!opt)
        {
            errorHandler.addSemanticError(ctx->getStart(), "Undefined variable in expression: " + id);
            return Types::UNDEFINED;
        }

        // Otherwise, get the symbol's value
        Symbol *symbol = opt.value().second;

        // Bind the larger context to the symbol, and return the symbol's type.
        bindings->bind(ctx, symbol);
        return symbol->type;
    }

    /*
     * As we are not a var, we must be an array access, so we must visit that context.
     */
    const Type *arrType = this->visitCtx(ctx->array);

    // Lookup the binding of the array
    std::optional<Symbol *> binding = bindings->getBinding(ctx->array);

    // If we didn't get a binding, report an error.
    if (!binding)
    {
        errorHandler.addSemanticError(ctx->array->getStart(), "Could not correctly bind to array access!");
        return Types::UNDEFINED;
    }

    // Otherwise, bind this context to the same binding as the array access, and return its type.
    bindings->bind(ctx, binding.value());
    return arrType;
}

const Type *SemanticVisitor::visitCtx(WPLParser::IConstExprContext *ctx) { return Types::INT; }

const Type *SemanticVisitor::visitCtx(WPLParser::ArrayAccessExprContext *ctx) { return this->visitCtx(ctx->arrayAccess()); }

const Type *SemanticVisitor::visitCtx(WPLParser::SConstExprContext *ctx) { return Types::STR; }

/**
 * @brief Typechecks Unary Expressions
 *
 * @param ctx The UnaryExpressionContext to type check
 * @return const Type* Returns the type of the inner expression if valid; UNDEFINED otherwise.
 */
const Type *SemanticVisitor::visitCtx(WPLParser::UnaryExprContext *ctx)
{
    // Lookup the inner type
    const Type *innerType = any2Type(ctx->ex->accept(this));

    // Switch on the operation so we can ensure that the type and operation are compatable.
    switch (ctx->op->getType())
    {
    case WPLParser::MINUS:
        if (innerType->isNotSubtype(Types::INT))
        {
            errorHandler.addSemanticError(ctx->getStart(), "INT expected in unary minus, but got " + innerType->toString());
            return Types::UNDEFINED;
        }
        break;
    case WPLParser::NOT:
        if (innerType->isNotSubtype(Types::BOOL))
        {
            errorHandler.addSemanticError(ctx->getStart(), "BOOL expected in unary not, but got " + innerType->toString());
            return Types::UNDEFINED;
        }
        break;
    }

    return innerType;
}

/**
 * @brief Visits a Binary Arithmetic Expression ensuring LHS and RHS are INT.
 *
 * @param ctx The BinaryArithExprContext to Visit
 * @return const Type* INT if lhs and rhs are INT; UNDEFINED otherwise.
 */
const Type *SemanticVisitor::visitCtx(WPLParser::BinaryArithExprContext *ctx)
{
    // Based on starter
    bool valid = true;

    auto left = any2Type(ctx->left->accept(this));
    if (left->isNotSubtype(Types::INT))
    {
        errorHandler.addSemanticError(ctx->getStart(), "INT left expression expected, but was " + left->toString());
        valid = false;
    }

    auto right = any2Type(ctx->right->accept(this));
    if (right->isNotSubtype(Types::INT))
    {
        errorHandler.addSemanticError(ctx->getStart(), "INT right expression expected, but was " + right->toString());
        valid = false;
    }

    return (valid) ? Types::INT : Types::UNDEFINED;
}

const Type *SemanticVisitor::visitCtx(WPLParser::EqExprContext *ctx)
{
    auto right = any2Type(ctx->right->accept(this));
    auto left = any2Type(ctx->left->accept(this));
    if (right->isNotSubtype(left))
    {
        errorHandler.addSemanticError(ctx->getStart(), "Both sides of '=' must have the same type");
        return Types::UNDEFINED;
    }

    // Note: As per C spec, arrays cannot be compared
    if (dynamic_cast<const TypeArray *>(left) || dynamic_cast<const TypeArray *>(right))
    {
        errorHandler.addSemanticError(ctx->getStart(), "Cannot perform equality operation on arrays; they are always seen as unequal!");
    }

    return Types::BOOL;
}

/**
 * @brief Visits a Logical And Expression ensuring LHS and RHS are BOOL.
 *
 * @param ctx The LogAndExprContext to Visit
 * @return const Type* BOOL if lhs and rhs are BOOL; UNDEFINED otherwise.
 */
const Type *SemanticVisitor::visitCtx(WPLParser::LogAndExprContext *ctx)
{
    bool valid = true;

    for (auto e : ctx->exprs)
    {
        const Type *type = any2Type(e->accept(this));
        if (type->isNotSubtype(Types::BOOL))
        {
            errorHandler.addSemanticError(e->getStart(), "BOOL expression expected, but was " + type->toString());
            valid = false;
        }
    }

    return (valid) ? Types::BOOL : Types::UNDEFINED;
}

/**
 * @brief Visits a Logical Or Expression ensuring LHS and RHS are BOOL.
 *
 * @param ctx The LogOrExprContext to Visit
 * @return const Type* BOOL if lhs and rhs are BOOL; UNDEFINED otherwise.
 */
const Type *SemanticVisitor::visitCtx(WPLParser::LogOrExprContext *ctx)
{
    bool valid = true;

    for (auto e : ctx->exprs)
    {
        const Type *type = any2Type(e->accept(this));
        if (type->isNotSubtype(Types::BOOL))
        {
            errorHandler.addSemanticError(e->getStart(), "BOOL expression expected, but was " + type->toString());
            valid = false;
        }
    }

    return (valid) ? Types::BOOL : Types::UNDEFINED;
}

// Passthrough to visitInvocation
const Type *SemanticVisitor::visitCtx(WPLParser::CallExprContext *ctx) { return this->visitCtx(ctx->call); }

/**
 * @brief Visits a FieldAccessExprContext---Currently limited to array lengths
 *
 * @param ctx the FieldAccessExprContext to visit
 * @return const Type* INT if correctly used to test array length; UNDEFINED if any errors.
 */
const Type *SemanticVisitor::visitCtx(WPLParser::FieldAccessExprContext *ctx)
{
    // Determine the type of the expression we are visiting
    std::optional<SymbolContext> opt = stmgr->lookup(ctx->VARIABLE().at(0)->getText());
    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Undefined variable reference: " + ctx->VARIABLE().at(0)->getText());
        return Types::UNDEFINED;
    }

    Symbol *sym = opt.value().second;
    bindings->bind(ctx->VARIABLE().at(0), sym);

    const Type *ty = sym->type;

    for (unsigned int i = 1; i < ctx->fields.size(); i++)
    {
        std::string fieldName = ctx->fields.at(i)->getText();

        if (const TypeStruct *s = dynamic_cast<const TypeStruct *>(ty))
        {
            std::optional<const Type *> eleOpt = s->get(fieldName);
            if (eleOpt)
            {
                ty = eleOpt.value();
                Symbol *bnd = new Symbol("", ty, false, false);
                bindings->bind(ctx->VARIABLE().at(i), bnd); // FIXME: DO BETTER
            }
            else
            {
                errorHandler.addSemanticError(ctx->getStart(), "Cannot access " + fieldName + " on " + ty->toString());
                return Types::UNDEFINED;
            }
        }
        else if (i + 1 == ctx->fields.size() && dynamic_cast<const TypeArray *>(ty) && ctx->fields.at(i)->getText() == "length")
        {
            bindings->bind(ctx->VARIABLE().at(i), new Symbol("", Types::INT, false, false)); // FIXME: DO BETTER
            return Types::INT;
        }
        else
        {
            errorHandler.addSemanticError(ctx->getStart(), "Cannot access " + fieldName + " on " + ty->toString());
            return Types::UNDEFINED;
        }
    }

    // errorHandler.addSemanticError(ctx->getStart(), "Unsupported operation on " + ty->toString());

    return ty;
}

// Passthrough to expression
const Type *SemanticVisitor::visitCtx(WPLParser::ParenExprContext *ctx) { return any2Type(ctx->ex->accept(this)); }

/**
 * @brief Visits a BinaryRelational Expression ensuring both lhs and rhs are INT.
 *
 * @param ctx The BinaryRelExprContext to visit.
 * @return const Type* BOOL if lhs and rhs INT; UNDEFINED otherwise.
 */
const Type *SemanticVisitor::visitCtx(WPLParser::BinaryRelExprContext *ctx)
{
    // Based on starter
    bool valid = true;

    auto left = any2Type(ctx->left->accept(this));

    if (left->isNotSubtype(Types::INT))
    {
        errorHandler.addSemanticError(ctx->getStart(), "INT left expression expected, but was " + left->toString());
        valid = false;
    }

    auto right = any2Type(ctx->right->accept(this));

    if (right->isNotSubtype(Types::INT))
    {
        errorHandler.addSemanticError(ctx->getStart(), "INT right expression expected, but was " + right->toString() + " in " + ctx->getText());
        valid = false;
    }
    return valid ? Types::BOOL : Types::UNDEFINED;
}

// This here basically means that we don't need to do anything for booleanConst, but I'll leave it just in case
const Type *SemanticVisitor::visitCtx(WPLParser::BConstExprContext *ctx) { return Types::BOOL; }

const Type *SemanticVisitor::visitCtx(WPLParser::BlockContext *ctx)
{
    return this->safeVisitBlock(ctx, true);
}

/**
 * @brief Visits a condition's expression ensuring that it is of type BOOL.
 *
 * @param ctx The ConditionContext to visit
 * @return const Type* Always returns UNDEFINED as to prevent assignments
 */
const Type *SemanticVisitor::visitCtx(WPLParser::ConditionContext *ctx)
{
    auto conditionType = any2Type(ctx->ex->accept(this));

    if (conditionType->isNotSubtype(Types::BOOL))
    {
        errorHandler.addSemanticError(ctx->getStart(), "Condition expected BOOL, but was given " + conditionType->toString());
    }

    return Types::UNDEFINED;
}

const Type *SemanticVisitor::visitCtx(WPLParser::SelectAlternativeContext *ctx)
{
    // Enter the scope (needed as we may define variables or do other stuff)
    stmgr->enterScope(StopType::LINEAR);
    // Accept the evaluation context
    ctx->eval->accept(this);
    // Safe exit the scope
    this->safeExitScope(ctx);

    /*
     *  Just make sure that we don't try to define functions and stuff in a select as that doesn't make sense (and would cause codegen issues as it stands).
     */
    if (dynamic_cast<WPLParser::ProgDefContext *>(ctx->eval) ||
        dynamic_cast<WPLParser::VarDeclStatementContext *>(ctx->eval))
    {
        errorHandler.addSemanticError(ctx->getStart(), "Dead code: definition as select alternative.");
    }

    // Confirm that the check type is a boolean
    const Type *checkType = any2Type(ctx->check->accept(this));

    if (const TypeBool *b = dynamic_cast<const TypeBool *>(checkType))
    {
    }
    else
    {
        errorHandler.addSemanticError(ctx->getStart(), "Select alternative expected BOOL but got " + checkType->toString());
    }

    // Return UNDEFINED as its a statement.
    return Types::UNDEFINED;
}

/**
 * @brief Constructs a TypeInvoke based on the parameter types and assumes a return type of BOT.
 *
 * @param ctx The ParameterListContext to process.
 * @return const Type* TypeInvoke representing the parameter types.
 */
const Type *SemanticVisitor::visitCtx(WPLParser::ParameterListContext *ctx)
{
    std::vector<const Type *> params;
    std::map<std::string, WPLParser::ParameterContext *> map;

    for (auto param : ctx->params)
    {
        std::string name = param->name->getText();

        auto prevUse = map.find(name);
        if (prevUse != map.end())
        {
            errorHandler.addSemanticError(param->getStart(), "Re-use of previously defined parameter " + name + ".");
        }
        else
        {
            map.insert({name, param});
        }

        const Type *type = this->visitCtx(param);
        params.push_back(type);
    }

    const Type *type = new TypeInvoke(params); // Needs to be two separate lines b/c of how C++ handles returns?
    return type;
}

// Passthrough to visit the inner expression
const Type *SemanticVisitor::visitCtx(WPLParser::ParameterContext *ctx) { return any2Type(ctx->ty->accept(this)); }

const Type *SemanticVisitor::visitCtx(WPLParser::AssignmentContext *ctx)
{
    errorHandler.addSemanticError(ctx->getStart(), "Assignment should never be visited directly during type checking!");
    return Types::UNDEFINED;
}

const Type *SemanticVisitor::visitCtx(WPLParser::ExternStatementContext *ctx)
{

    bool variadic = ctx->variadic || ctx->ELLIPSIS();

    std::string id = ctx->name->getText();

    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Unsupported redeclaration of " + id);
        // return Types::UNDEFINED;
    }

    const Type *ty = (ctx->paramList) ? this->visitCtx(ctx->paramList)
                                      : new TypeInvoke();

    const TypeInvoke *procType = dynamic_cast<const TypeInvoke *>(ty); // Always true, but needs separate statement to make C happy.

    const Type *retType = ctx->ty ? any2Type(ctx->ty->accept(this)) // this->visitCtx(ctx->ty)
                                  : Types::UNDEFINED;

    const TypeInvoke *funcType = (ctx->ty) ? new TypeInvoke(procType->getParamTypes(), retType, variadic, true)
                                           : new TypeInvoke(procType->getParamTypes(), variadic, true);

    Symbol *funcSymbol = new Symbol(id, funcType, true, true);

    stmgr->addSymbol(funcSymbol);
    bindings->bind(ctx, funcSymbol);

    return Types::UNDEFINED;
};

const Type *SemanticVisitor::visitCtx(WPLParser::ProgDefContext *ctx)
{
    std::cout << "744 Codegen is dumb" << std::endl; 
    return this->visitInvokeable(ctx->defineProc());
}

const Type *SemanticVisitor::visitCtx(WPLParser::AssignStatementContext *ctx)
{
    // This one is the update one!

    // Determine the expression type
    const Type *exprType = any2Type(ctx->a->accept(this));

    // Determine the expected type
    const Type *type = this->visitCtx(ctx->to);

    // If we actually have a type... (prevents things like null ptrs)
    if (type)
    {
        // Make sure that the types are compatible. Inference automatically managed here.
        if (exprType->isNotSubtype(type))
        {
            errorHandler.addSemanticError(ctx->getStart(), "Assignment statement expected " + type->toString() + " but got " + exprType->toString());
        }
    }
    else
    {
        errorHandler.addSemanticError(ctx->getStart(), "Cannot assign to undefined variable: " + ctx->to->getText());
    }

    // Return UNDEFINED because this is a statement, and UNDEFINED cannot be assigned to anything
    return Types::UNDEFINED;
}

const Type *SemanticVisitor::visitCtx(WPLParser::VarDeclStatementContext *ctx)
{
    for (auto e : ctx->assignments)
    {
        // Needs to happen in case we have vars
        const Type *assignType = this->visitCtx(ctx->typeOrVar());
        auto exprType = (e->a) ? any2Type(e->a->accept(this)) : assignType;

        if (e->a && stmgr->isGlobalScope())
        {
            if (!(dynamic_cast<WPLParser::BConstExprContext *>(e->a) ||
                  dynamic_cast<WPLParser::IConstExprContext *>(e->a) ||
                  dynamic_cast<WPLParser::SConstExprContext *>(e->a)))
            {
                errorHandler.addSemanticError(e->a->getStart(), "Global variables must be assigned explicit constants or initialized at runtime!");
            }

            if (dynamic_cast<const TypeSum *>(assignType))
            {
                errorHandler.addSemanticError(e->a->getStart(), "Sums cannot be initialized at a global level");
            }
        }

        // Note: This automatically performs checks to prevent issues with setting VAR = VAR
        if (e->a && exprType->isNotSubtype(assignType))
        {
            errorHandler.addSemanticError(e->getStart(), "Expression of type " + exprType->toString() + " cannot be assigned to " + assignType->toString());
        }

        for (auto var : e->VARIABLE())
        {
            std::string id = var->getText();

            std::optional<Symbol *> symOpt = stmgr->lookupInCurrentScope(id);

            if (symOpt)
            {
                errorHandler.addSemanticError(e->getStart(), "Redeclaration of " + id);
            }
            else
            {
                // Needed to ensure vars get their own inf type
                const Type *newAssignType = this->visitCtx(ctx->typeOrVar());
                const Type *newExprType = (dynamic_cast<const TypeInfer *>(newAssignType) && e->a) ? any2Type(e->a->accept(this)) : newAssignType;
                Symbol *symbol = new Symbol(id, newExprType, false, stmgr->isGlobalScope()); // Done with exprType for later inferencing purposes
                stmgr->addSymbol(symbol);
                bindings->bind(var, symbol);
            }
        }
    }
    // Return UNDEFINED because this is a statement, and UNDEFINED cannot be assigned to anything
    return Types::UNDEFINED;
}

const Type *SemanticVisitor::visitCtx(WPLParser::MatchStatementContext *ctx)
{
    const Type *condType = any2Type(ctx->check->ex->accept(this));

    if (const TypeSum *sumType = dynamic_cast<const TypeSum *>(condType))
    {
        std::set<const Type *> foundCaseTypes = {};
        // TODO: Maybe make so these can return values?

        for (WPLParser::MatchAlternativeContext *altCtx : ctx->cases)
        {
            const Type *caseType = any2Type(altCtx->type()->accept(this));

            if (!sumType->contains(caseType))
            {
                errorHandler.addSemanticError(altCtx->type()->getStart(), "Impossible case for " + sumType->toString() + " to act as " + caseType->toString());
            }

            if (foundCaseTypes.count(caseType))
            {
                errorHandler.addSemanticError(altCtx->type()->getStart(), "Duplicate case in match");
            }
            else
            {
                foundCaseTypes.insert(caseType); // FIXME: DO BETTER TRACKING OF SATISFYING RQMTS. Right now, can pass check for having all cases due to having invalid ones!!
            }

            stmgr->enterScope(StopType::LINEAR);
            Symbol *local = new Symbol(altCtx->name->getText(), caseType, false, false);
            stmgr->addSymbol(local);
            bindings->bind(altCtx->VARIABLE(), local);

            altCtx->eval->accept(this);
            this->safeExitScope(altCtx);

            if (dynamic_cast<WPLParser::ProgDefContext *>(altCtx->eval) ||
                dynamic_cast<WPLParser::VarDeclStatementContext *>(altCtx->eval))
            {
                errorHandler.addSemanticError(altCtx->getStart(), "Dead code: definition as select alternative.");
            }
        }

        if (foundCaseTypes.size() != sumType->getCases().size())
        {
            errorHandler.addSemanticError(ctx->getStart(), "Match statement did not cover all cases needed for " + sumType->toString());
        }

        bindings->bind(ctx->check, new Symbol(ctx->check->ex->getText(), sumType, false, false));
        return Types::UNDEFINED;
    }

    errorHandler.addSemanticError(ctx->check->getStart(), "Can only case on Sum Types, not " + condType->toString());
    return Types::UNDEFINED;
}

/**
 * @brief Type checks a Loops
 *
 * @param ctx The LoopStatementContext to type check
 * @return const Type* UNDEFINED as this is a statement.
 */
const Type *SemanticVisitor::visitCtx(WPLParser::ProgramLoopContext *ctx)
{
    this->visitCtx(ctx->check); // Visiting check will make sure we have a boolean condition

    std::vector<const Symbol *> syms = stmgr->getAvaliableLinears();

    stmgr->enterScope(StopType::LINEAR); // TODO: DO BETTER

    for (const Symbol *orig : syms)
    {
        if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(orig->type))
        {
            std::optional<const ProtocolSequence *> protoOpt = channel->getProtocol()->shearLoop();
            if (protoOpt)
            {

                stmgr->addSymbol(new Symbol(orig->getIdentifier(), new TypeChannel(protoOpt.value()), false, false));
            }
        }
    }

    this->visitCtx(ctx->block()); // Visiting block to make sure everything type checks there as well

    safeExitScope(ctx);

    // Return UNDEFINED because this is a statement, and UNDEFINED cannot be assigned to anything
    return Types::UNDEFINED;
}

const Type *SemanticVisitor::visitCtx(WPLParser::ConditionalStatementContext *ctx)
{
    // Automatically handles checking that we have a valid condition
    this->visitCtx(ctx->check);

    // Type check the then/true block
    this->visitCtx(ctx->trueBlk);

    // If we have an else block, then type check it
    if (ctx->falseBlk)
    {
        this->visitCtx(ctx->falseBlk);
    }

    // Return UNDEFINED because this is a statement, and UNDEFINED cannot be assigned to anything
    return Types::UNDEFINED;
}

const Type *SemanticVisitor::visitCtx(WPLParser::SelectStatementContext *ctx)
{

    if (ctx->cases.size() < 1)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Select statement expected at least one alternative, but was given 0!");
        return Types::UNDEFINED; // Shouldn't matter as the for loop won't have anything to do
    }
    // Here we just need to visit each of the individual cases; they each handle their own logic.
    for (auto e : ctx->cases)
    {
        this->visitCtx(e);
    }

    // Return UNDEFINED because this is a statement, and UNDEFINED cannot be assigned to anything
    return Types::UNDEFINED;
}

// Passthrough to visit invocation
const Type *SemanticVisitor::visitCtx(WPLParser::CallStatementContext *ctx) { return this->visitCtx(ctx->call); }

const Type *SemanticVisitor::visitCtx(WPLParser::ReturnStatementContext *ctx)
{
    /*
     * Lookup the @RETURN symbol which can ONLY be defined by entering FUNC/PROC
     */
    std::optional<SymbolContext> symOpt = stmgr->lookup("@RETURN");

    // If we don't have the symbol, we're not in a place that we can return from.
    if (!symOpt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Cannot use return outside of FUNC or PROC");
        return Types::UNDEFINED;
    }

    Symbol *sym = symOpt.value().second;
    bindings->bind(ctx, sym);

    // If the return statement has an expression...
    if (ctx->expression())
    {
        // Evaluate the expression type
        const Type *valType = any2Type(ctx->expression()->accept(this));

        // If the type of the return symbol is a BOT, then we must be in a PROC and, thus, we cannot return anything
        if (const TypeBot *b = dynamic_cast<const TypeBot *>(sym->type))
        {
            errorHandler.addSemanticError(ctx->getStart(), "PROC cannot return value, yet it was given a " + valType->toString() + " to return!");
            return Types::UNDEFINED;
        }

        // As the return type is not a BOT, we have to make sure that it is the correct type to return

        if (valType->isNotSubtype(sym->type))
        {
            errorHandler.addSemanticError(ctx->getStart(), "Expected return type of " + sym->type->toString() + " but got " + valType->toString());
            return Types::UNDEFINED;
        }

        // Valid return statement; return UNDEFINED as its a statement.
        return Types::UNDEFINED;
    }
    else
    {
        // We do not have an expression to return, so make sure that the return type is also a BOT.
        if (const TypeBot *b = dynamic_cast<const TypeBot *>(sym->type))
        {
            return Types::UNDEFINED;
        }

        errorHandler.addSemanticError(ctx->getStart(), "Expected to return a " + sym->type->toString() + " but recieved nothing.");
        return Types::UNDEFINED;
    }

    errorHandler.addSemanticError(ctx->getStart(), "Unknown case");
    return Types::UNDEFINED;
}

// Passthrough to visitBlock
const Type *SemanticVisitor::visitCtx(WPLParser::BlockStatementContext *ctx) { return this->visitCtx(ctx->block()); }

const Type *SemanticVisitor::visitCtx(WPLParser::TypeOrVarContext *ctx)
{
    // If we don't have a type context, then we know that we must be doing inference
    if (!(ctx->type()))
    {
        const Type *ans = new TypeInfer();
        return ans;
    }

    // If we do have a type, then visit that context.
    // std::any temp = this->visit(ctx->type());

    const Type *type = any2Type(ctx->type()->accept(this));
    return type;
}

const Type *SemanticVisitor::visitCtx(WPLParser::LambdaConstExprContext *ctx)
{
    // FIXME: VERIFY THIS IS ALWAYS SAFE!!!
    const TypeInvoke *paramType = dynamic_cast<const TypeInvoke *>(visitCtx(ctx->parameterList()));
    const Type *retType = any2Type(ctx->ret->accept(this));

    const TypeInvoke *funcType = new TypeInvoke(paramType->getParamTypes(), retType);

    stmgr->enterScope(StopType::GLOBAL);
    stmgr->addSymbol(new Symbol("@RETURN", retType, false, false));

    for (unsigned int i = 0; i < ctx->parameterList()->params.size(); i++)
    {
        const Type *ty = funcType->getParamTypes().at(i);
        auto param = ctx->parameterList()->params.at(i);

        Symbol *paramSymbol = new Symbol(param->name->getText(), ty, false, false);

        stmgr->addSymbol(paramSymbol);

        bindings->bind(param, paramSymbol);
    }

    this->safeVisitBlock(ctx->block(), false);

    // If we have a return type, make sure that we return as the last statement in the FUNC. The type of the return is managed when we visited it.
    if (ctx->block()->stmts.size() == 0 || !dynamic_cast<WPLParser::ReturnStatementContext *>(ctx->block()->stmts.at(ctx->block()->stmts.size() - 1)))
    {
        errorHandler.addSemanticError(ctx->getStart(), "Lambda must end in return statement");
    }
    safeExitScope(ctx);

    Symbol *funcSymbol = new Symbol("@LAMBDA", funcType, false, false);
    bindings->bind(ctx, funcSymbol);

    return funcType;
}

const Type *SemanticVisitor::visitCtx(WPLParser::LambdaTypeContext *ctx)
{
    std::vector<const Type *> params;

    for (auto param : ctx->paramTypes)
    {
        // const Type *type = this->visitCtx(param);
        const Type *type = any2Type(param->accept(this));
        params.push_back(type);
    }

    const Type *returnType = any2Type(ctx->returnType->accept(this));

    const Type *lamType = new TypeInvoke(params, returnType);

    return lamType;
}

const Type *SemanticVisitor::visitCtx(WPLParser::SumTypeContext *ctx)
{
    std::set<const Type *, TypeCompare> cases = {};

    for (auto e : ctx->type())
    {
        const Type *caseType = any2Type(e->accept(this));
        cases.insert(caseType);
    }

    if (cases.size() != ctx->type().size())
    {
        errorHandler.addSemanticError(ctx->getStart(), "Duplicate arguments to enum type, or failed to generate types");
        return Types::UNDEFINED;
    }

    const TypeSum *sum = new TypeSum(cases);

    return sum;
}

const Type *SemanticVisitor::visitCtx(WPLParser::DefineEnumContext *ctx)
{
    std::string id = ctx->name->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);
    if (opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Unsupported redeclaration of " + id);
        return Types::UNDEFINED;
    }

    std::set<const Type *, TypeCompare> cases = {};

    for (auto e : ctx->cases)
    {
        const Type *caseType = any2Type(e->accept(this));
        cases.insert(caseType);
    }

    if (cases.size() != ctx->cases.size())
    {
        errorHandler.addSemanticError(ctx->getStart(), "Duplicate arguments to enum type, or failed to generate types");
        return Types::UNDEFINED;
    }

    const TypeSum *sum = new TypeSum(cases, id);
    Symbol *enumSym = new Symbol(id, sum, true, true);

    stmgr->addSymbol(enumSym);
    bindings->bind(ctx, enumSym);

    return Types::UNDEFINED;
}

const Type *SemanticVisitor::visitCtx(WPLParser::DefineStructContext *ctx)
{
    std::string id = ctx->name->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);
    if (opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Unsupported redeclaration of " + id);
        return Types::UNDEFINED;
    }

    LinkedMap<std::string, const Type *> el;

    for (WPLParser::StructCaseContext *caseCtx : ctx->cases)
    {
        std::string caseName = caseCtx->name->getText();
        if (el.lookup(caseName))
        {
            errorHandler.addSemanticError(ctx->getStart(), "Unsupported redeclaration of " + caseName);
            return Types::UNDEFINED;
        }
        const Type *caseTy = any2Type(caseCtx->ty->accept(this));

        el.insert({caseName, caseTy});
    }

    const TypeStruct *product = new TypeStruct(el, id);
    Symbol *prodSym = new Symbol(id, product, true, true);
    stmgr->addSymbol(prodSym);
    bindings->bind(ctx, prodSym);

    return Types::UNDEFINED;

    // FIXME: TRY USING FUNC DEFS AS TYPES!
}

const Type *SemanticVisitor::visitCtx(WPLParser::CustomTypeContext *ctx)
{
    std::string name = ctx->VARIABLE()->getText();

    std::optional<SymbolContext> opt = stmgr->lookup(name);
    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Undefined type: " + name); // TODO: address inefficiency in var decl where this is called multiple times
        return Types::UNDEFINED;
    }

    Symbol *sym = opt.value().second;

    if (!sym->type || !sym->isDefinition)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Cannot use: " + name + " as a type.");
        return Types::UNDEFINED;
    }

    bindings->bind(ctx, sym); // FIXME: DO BETTER
    return sym->type;
}

const Type *SemanticVisitor::visitCtx(WPLParser::ArrayTypeContext *ctx)
{
    const Type *subType = any2Type(ctx->ty->accept(this));

    // Undefined type errors handled below

    int len = std::stoi(ctx->len->getText());

    if (len < 1)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Cannot initialize array with a size of less than 1!");
    }

    const Type *arr = new TypeArray(subType, len);
    return arr;
}
const Type *SemanticVisitor::visitCtx(WPLParser::BaseTypeContext *ctx)
{

    const Type *ty = Types::UNDEFINED;
    bool valid = false;

    if (ctx->TYPE_INT())
    {
        ty = Types::INT;
        valid = true;
    }
    else if (ctx->TYPE_BOOL())
    {
        ty = Types::BOOL;
        valid = true;
    }
    else if (ctx->TYPE_STR())
    {
        ty = Types::STR;
        valid = true;
    }

    if (!valid)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Unknown type: " + ctx->getText());
        return Types::UNDEFINED;
    }

    return ty;
}

// Should never be needed due to how BConstExpr works, but leaving here just in case.
const Type *SemanticVisitor::visitCtx(WPLParser::BooleanConstContext *ctx) { return Types::BOOL; }

const Type *SemanticVisitor::visitCtx(WPLParser::ChannelTypeContext *ctx)
{
    const ProtocolSequence *proto = dynamic_cast<const ProtocolSequence *>(any2Protocol(ctx->proto->accept(this)));

    return new TypeChannel(proto);
}

const Type *SemanticVisitor::TvisitProgramSend(WPLParser::ProgramSendContext *ctx)
{
    // FIXME: HAVE TO POTENTIALLY DELETE FROM CONTEXT OTHER VAR
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Could not find channel: " + id);
        return Types::UNDEFINED;
    }

    Symbol *sym = opt.value().second;
    bindings->bind(ctx->VARIABLE(), sym); //For Channel 

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        const Type *ty = any2Type(ctx->expr->accept(this));

        if (!channel->getProtocol()->send(ty))
        {
            errorHandler.addSemanticError(ctx->getStart(), "Failed to send " + ty->toString() + " over channel " + sym->toString());
        }
        return Types::UNDEFINED;
    }

    errorHandler.addSemanticError(ctx->getStart(), "Cannot send on non-channel: " + id);
    return Types::UNDEFINED;
}

const Type *SemanticVisitor::TvisitAssignableRecv(WPLParser::AssignableRecvContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Could not find channel: " + id);
        return Types::UNDEFINED;
    }

    Symbol *sym = opt.value().second;

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {

        std::optional<const Type *> ty = channel->getProtocol()->recv();
        if (!ty)
        {
            errorHandler.addSemanticError(ctx->getStart(), "Failed to recv over channel: " + sym->toString());
            return Types::UNDEFINED;
        }

        bindings->bind(ctx->VARIABLE(), sym); //For Channel 
        bindings->bind(ctx, new Symbol("", ty.value(), false, false)); //FIXME: DO BETTER, DONE SO WE CAN DO CORRECT BITCAST
        return ty.value();
    }

    errorHandler.addSemanticError(ctx->getStart(), "Cannot recv on non-channel: " + id);
    return Types::UNDEFINED;
}
// const Type *SemanticVisitor::TvisitProgramLoop(WPLParser::ProgramLoopContext *ctx) { errorHandler.addSemanticError(ctx->getStart(), "UNIMPLEMENTED"); return Types::UNDEFINED; }
const Type *SemanticVisitor::TvisitProgramCase(WPLParser::ProgramCaseContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Could not find channel: " + id);
        return Types::UNDEFINED;
    }

    Symbol *sym = opt.value().second;

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        std::set<const ProtocolSequence *, ProtocolCompare> opts = {};

        // FIXME: REDO SO WE DON'T HAVE TO DO THIS MULTIPLE TIMES (VISITING)
        for (auto alt : ctx->protoAlternative())
        {
            opts.insert(toSequence(any2Protocol(alt->check->accept(this))));
        }

        if (!channel->getProtocol()->isExtChoice(opts))
        {
            errorHandler.addSemanticError(ctx->getStart(), "Failed to case over channel: " + sym->toString());
            return Types::UNDEFINED;
        }

        std::vector<const Symbol *> syms = stmgr->getAvaliableLinears(); // FIXME: WILL TRY TO REBIND VAR WE JUST BOUND TO NEW CHAN VALUE!
        stmgr->deleteAvaliableLinears();                                 // FIXME: UNSAFE

        for (auto alt : ctx->protoAlternative())
        {
            const ProtocolSequence *proto = toSequence(any2Protocol(alt->check->accept(this)));
            stmgr->enterScope(StopType::NONE); // FIXME: THIS SORT OF THING HAS ISSUES WITH ALLOWING FOR REDCLS OF VARS IN VARIOIUS SCOPES!!! (THIS EFFECTIVLEY FLATTENS THINGS)

            proto->append(channel->getProtocolCopy());
            stmgr->addSymbol(new Symbol(id, new TypeChannel(proto), false, false));

            for (const Symbol *orig : syms)
            {
                // FIXME: DO BETTER!!!!! WONT WORK FOR NON-CHANNELS!
                if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(orig->type))
                {
                    stmgr->addSymbol(new Symbol(orig->getIdentifier(), channel->getCopy(), false, false));
                }
            }

            alt->eval->accept(this);

            for (auto s : ctx->rest)
            {
                s->accept(this);
            }

            safeExitScope(ctx);
        }

        return Types::UNDEFINED;
        // return ty.value();
    }

    errorHandler.addSemanticError(ctx->getStart(), "Cannot case on non-channel: " + id);
    return Types::UNDEFINED;
}
const Type *SemanticVisitor::TvisitProgramProject(WPLParser::ProgramProjectContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Could not find channel: " + id);
        return Types::UNDEFINED;
    }

    Symbol *sym = opt.value().second;

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        const ProtocolSequence *ps = toSequence(any2Protocol(ctx->sel->accept(this)));
        if (!channel->getProtocol()->project(ps))
        {
            errorHandler.addSemanticError(ctx->getStart(), "Failed to project over channel: " + sym->toString() + " vs " + ps->toString());
            return Types::UNDEFINED;
        }

        // return ty.value();
        return Types::UNDEFINED;
    }

    errorHandler.addSemanticError(ctx->getStart(), "Cannot project on non-channel: " + id);
    return Types::UNDEFINED;
}
const Type *SemanticVisitor::TvisitProgramContract(WPLParser::ProgramContractContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Could not find channel: " + id);
        return Types::UNDEFINED;
    }

    Symbol *sym = opt.value().second;

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        if (!channel->getProtocol()->contract())
        {
            errorHandler.addSemanticError(ctx->getStart(), "Failed to contract weaken: " + id);
        }
        return Types::UNDEFINED;
    }

    errorHandler.addSemanticError(ctx->getStart(), "Cannot contract on non-channel: " + id);
    return Types::UNDEFINED;
}
const Type *SemanticVisitor::TvisitProgramWeaken(WPLParser::ProgramWeakenContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Could not find channel: " + id);
        return Types::UNDEFINED;
    }

    Symbol *sym = opt.value().second;

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        if (!channel->getProtocol()->weaken())
        {
            errorHandler.addSemanticError(ctx->getStart(), "Failed to weaken: " + id + " against " + channel->toString());
        }
        return Types::UNDEFINED;
    }

    errorHandler.addSemanticError(ctx->getStart(), "Cannot weaken on non-channel: " + id);
    return Types::UNDEFINED;
}
const Type *SemanticVisitor::TvisitProgramAccept(WPLParser::ProgramAcceptContext *ctx)
{
    std::string id = ctx->VARIABLE()->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);
    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Unbound identifier: " + id);
        return Types::UNDEFINED;
    }

    Symbol *sym = opt.value().second;

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        std::optional<const ProtocolSequence *> acceptOpt = channel->getProtocol()->acceptLoop();
        if (!acceptOpt)
        {
            errorHandler.addSemanticError(ctx->getStart(), "Cannot accept on " + channel->toString());
            return Types::UNDEFINED;
        }

        std::vector<const Symbol *> syms = stmgr->getAvaliableLinears();
        // FIXME: DO BETTER B/C HERE WE TRY TO ASSIGN TO THE VAR WE MANUALLY NEED TO ASSIGN? NO BC IT FAILS CHECK!

        stmgr->enterScope(StopType::LINEAR); // TODO: DO BETTER

        for (const Symbol *orig : syms)
        {
            if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(orig->type))
            {
                std::optional<const ProtocolSequence *> protoOpt = channel->getProtocol()->shearLoop();
                if (protoOpt)
                {

                    stmgr->addSymbol(new Symbol(orig->getIdentifier(), new TypeChannel(protoOpt.value()), false, false));
                }
            }
        }

        stmgr->addSymbol(new Symbol(id, new TypeChannel(acceptOpt.value()), false, false));

        this->visitCtx(ctx->block());

        safeExitScope(ctx);

        return Types::UNDEFINED;
        // return new TypeChannel(toSequence(inv->getChannelType()->getProtocol()->getInverse()));
    }

    errorHandler.addSemanticError(ctx->getStart(), "Cannot accept: " + sym->toString());
    return Types::UNDEFINED;
}
const Type *SemanticVisitor::TvisitAssignableExec(WPLParser::AssignableExecContext *ctx)
{
    std::string id = ctx->VARIABLE()->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);
    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Unbound identifier: " + id);
        return Types::UNDEFINED;
    }

    Symbol *sym = opt.value().second;

    if (const TypeProgram *inv = dynamic_cast<const TypeProgram *>(sym->type))
    {
        return new TypeChannel(toSequence(inv->getChannelType()->getProtocol()->getInverse()));
    }

    // FIXME: DO BETTER
    errorHandler.addSemanticError(ctx->getStart(), "Cannot exec: " + sym->toString());
    return Types::UNDEFINED;
}

/*************************************************************
 *
 * Protocols
 *
 *************************************************************/

const Protocol *SemanticVisitor::visitProto(WPLParser::ProtocolContext *ctx)
{
    std::vector<const Protocol *> steps;

    for (auto e : ctx->protos)
    {
        steps.push_back(any2Protocol(e->accept(this)));
    }

    return new ProtocolSequence(steps);
}

const Protocol *SemanticVisitor::visitProto(WPLParser::RecvTypeContext *ctx)
{
    const Type *ty = any2Type(ctx->ty->accept(this));
    return new ProtocolRecv(ty);
}

const Protocol *SemanticVisitor::visitProto(WPLParser::SendTypeContext *ctx)
{
    const Type *ty = any2Type(ctx->ty->accept(this));
    return new ProtocolSend(ty);
}

const Protocol *SemanticVisitor::visitProto(WPLParser::WnProtoContext *ctx)
{
    const Protocol *proto = any2Protocol(ctx->proto->accept(this));
    return new ProtocolWN(toSequence(proto));
}

const Protocol *SemanticVisitor::visitProto(WPLParser::OcProtoContext *ctx)
{
    const Protocol *proto = any2Protocol(ctx->proto->accept(this));
    return new ProtocolOC(toSequence(proto));
}

const Protocol *SemanticVisitor::visitProto(WPLParser::ExtChoiceProtoContext *ctx)
{
    std::set<const ProtocolSequence *, ProtocolCompare> opts = {};

    for (auto e : ctx->protoOpts)
    {
        opts.insert(toSequence(any2Protocol(e->accept(this))));
    }

    if (ctx->protoOpts.size() != opts.size())
    {
        errorHandler.addSemanticError(ctx->getStart(), "Duplicate protocols in choice");
        // FIXME: RETURN ERROR??
    }

    // return new Protocol(steps);
    return new ProtocolEChoice(opts);
}
const Protocol *SemanticVisitor::visitProto(WPLParser::IntChoiceProtoContext *ctx)
{
    // std::vector<const ProtocolSequence *> opts;
    std::set<const ProtocolSequence *, ProtocolCompare> opts = {};

    for (auto e : ctx->protoOpts)
    {
        opts.insert(toSequence(any2Protocol(e->accept(this))));
    }

    if (ctx->protoOpts.size() != opts.size())
    {
        errorHandler.addSemanticError(ctx->getStart(), "Duplicate protocols in choice");
        // FIXME: RETURN ERROR??
    }

    return new ProtocolIChoice(opts);
}