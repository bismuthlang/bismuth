#include "SemanticVisitor.h"

std::optional<CompilationUnitNode *> SemanticVisitor::visitCtx(WPLParser::CompilationUnitContext *ctx)
{
    // Enter initial scope
    stmgr->enterScope(StopType::NONE);

    std::vector<ExternNode *> externs;
    std::vector<DefinitionNode> defs;

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

            if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(ty))
            {
                const TypeProgram *funcType = new TypeProgram(channel, false);
                Symbol *funcSymbol = new Symbol(id, funcType, true, true);
                // FIXME: test name collisions with externs
                stmgr->addSymbol(funcSymbol);
            }
            else
            {
                errorHandler.addSemanticError(ctx->getStart(), "Process expected channel but got " + ty->toString());
            }
        }
        else if (WPLParser::DefineFunctionContext *fnCtx = dynamic_cast<WPLParser::DefineFunctionContext *>(e))
        {
            std::string id = fnCtx->defineFunc()->name->getText();

            std::optional<SymbolContext> opt = stmgr->lookup(id);

            if (opt)
            {
                errorHandler.addSemanticError(ctx->getStart(), "Unsupported redeclaration of program " + id);
                // return Types::UNDEFINED;
            }

            // FIXME: DUPLICATED FROM visitCtx(WPLParser::DefineFuncContext *ctx)!!!!

            std::optional<ParameterListNode> paramTypeOpt = visitCtx(fnCtx->defineFunc()->lam->parameterList());

            if (!paramTypeOpt)
                return {}; // FIXME: DO BETTER?

            ParameterListNode params = paramTypeOpt.value(); // FIXME: WHY NO POINTER?
            std::vector<const Type *> ps;

            for (ParameterNode param : params) //(unsigned int i = 0; i < ctx->parameterList()->params.size(); i++)
            {
                ps.push_back(param.type);
            }

            // const Type *retType = any2Type(fnCtx->defineFunc()->lam->ret->accept(this));

            const Type *retType = fnCtx->defineFunc()->lam->ret ? any2Type(fnCtx->defineFunc()->lam->ret->accept(this)) // this->visitCtx(ctx->ty)
                                                                : Types::UNDEFINED;

            Symbol *funcSym = new Symbol(id, new TypeInvoke(ps, retType), true, true); // FIXME: DO BETTER

            stmgr->addSymbol(funcSym);
            bindings->bind(fnCtx->defineFunc(), funcSym);
        }
        else
        {
            std::optional<TypedNode *> opt = anyOpt2Val<TypedNode *>(e->accept(this));
            if (!opt)
            {
                return {};
            } // FIXME: DO BETTER

            if (dynamic_cast<WPLParser::DefineStructContext *>(e)) // FIXME: DO BETTER
            {
                defs.push_back(dynamic_cast<DefineStructNode *>(opt.value()));
            }
            else if (dynamic_cast<WPLParser::DefineEnumContext *>(e))
            {
                defs.push_back(dynamic_cast<DefineEnumNode *>(opt.value()));
            }
            else
            {
                errorHandler.addSemanticError(ctx->getStart(), "Unhandled case");
            }
        }
    }

    // Visit externs first; they will report any errors if they have any.
    for (auto e : ctx->extens)
    {
        std::optional<ExternNode *> extOpt = this->visitCtx(e);
        if (!extOpt)
            return {}; // FIXME: DO BETTER
        externs.push_back(extOpt.value());
    }

    // Auto forward decl

    // Visit the statements contained in the unit
    for (auto e : ctx->defs)
    {
        // e->accept(this);
        if (WPLParser::DefineProgramContext *fnCtx = dynamic_cast<WPLParser::DefineProgramContext *>(e))
        {
            std::optional<ProgramDefNode *> progOpt = visitInvokeable(fnCtx->defineProc()); // e->accept(this);
            if (!progOpt)
                return {}; // FIXME: DO BETTER
            defs.push_back(progOpt.value());
        }
        else if (WPLParser::DefineFunctionContext *fnCtx = dynamic_cast<WPLParser::DefineFunctionContext *>(e))
        {
            std::optional<LambdaConstNode *> opt = visitCtx(fnCtx->defineFunc());

            if (!opt)
                return {}; // FIXME: DO BETTER

            defs.push_back(opt.value());
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
    return new CompilationUnitNode(externs, defs);
}

std::optional<InvocationNode *> SemanticVisitor::visitCtx(WPLParser::InvocationContext *ctx)
{
    std::optional<TypedNode *> typeOpt = (ctx->lam) ? (std::optional<TypedNode *>)visitCtx(ctx->lam) : (std::optional<TypedNode *>)visitCtx(ctx->field, true); // FIXME: DO BETTER, PRESERVE TYPE, MAYBE VARIADIC
    if (!typeOpt)
        return {}; // FIXME: DO BETTER

    TypedNode *tn = typeOpt.value();

    const Type *type = tn->getType();

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
            return {}; // TODO: Could change this to the return type to catch more errors?
        }

        std::vector<TypedNode *> args;
        std::vector<const Type *> actualTypes;
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
            // const Type *providedType = any2Type(ctx->args.at(i)->accept(this));
            std::optional<TypedNode *> providedOpt = anyOpt2Val<TypedNode *>(ctx->args.at(i)->accept(this));

            if (!providedOpt)
                return {}; // FIXME: DO BETTER

            TypedNode *provided = providedOpt.value();
            args.push_back(provided);

            const Type *providedType = provided->getType();

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
                i < fnParams.size() ? i : (fnParams.size() - 1)); // FIXME: TURNARY NEVER FULLY EVALED DUE TO CONTINUE!

            actualTypes.push_back(expectedType);

            // If the types do not match, report an error.
            if (providedType->isNotSubtype(expectedType))
            {
                std::ostringstream errorMsg;
                errorMsg << "Argument " << i << " provided to " << name << " expected " << expectedType->toString() << " but got " << providedType->toString();

                errorHandler.addSemanticError(ctx->getStart(), errorMsg.str());
            }
        }

        // Return the type of the invokable or BOT if it has none.
        // return invokeable->getReturnType(); //.has_value() ? invokeable->getReturnType().value() : Types::UNDEFINED;
        return new InvocationNode(tn, args, actualTypes);
    }

    // Symbol was not an invokeable type, so report an error & return UNDEFINED.
    errorHandler.addSemanticError(ctx->getStart(), "Can only invoke PROC and FUNC, not " + name + " : " + type->toString());
    return {};
}

std::optional<LambdaConstNode *> SemanticVisitor::visitCtx(WPLParser::DefineFuncContext *ctx)
{
    // FIXME: HANDLE REDECLS HERE INSTEAD OF AT TOP LEVEL? -> need to do something to prevent dupl issues!!

    std::optional<Symbol *> funcSymOpt = [this, ctx]() -> std::optional<Symbol *>
    {
        std::optional<Symbol *> opt = bindings->getBinding(ctx);
        if (opt)
            return opt.value();

        std::optional<ParameterListNode> paramTypeOpt = visitCtx(ctx->lam->parameterList());

        if (!paramTypeOpt)
            return {}; // FIXME: DO BETTER?

        ParameterListNode params = paramTypeOpt.value(); // FIXME: WHY NO POINTER?
        std::vector<const Type *> ps;

        for (ParameterNode param : params) //(unsigned int i = 0; i < ctx->parameterList()->params.size(); i++)
        {
            ps.push_back(param.type);
        }

        // const Type *retType = any2Type(ctx->lam->ret->accept(this));
        const Type *retType = ctx->lam->ret ? any2Type(ctx->lam->ret->accept(this)) // this->visitCtx(ctx->ty)
                                            : Types::UNDEFINED;

        Symbol *sym = new Symbol(ctx->name->getText(), new TypeInvoke(ps, retType), true, false); // FIXME: DO BETTER;

        stmgr->addSymbol(sym);

        return sym;
    }();

    if (!funcSymOpt)
        return {};

    Symbol *funcSym = funcSymOpt.value();

    // stmgr->addSymbol(funcSym);

    std::optional<LambdaConstNode *> lamOpt = visitCtx(ctx->lam);

    if (!lamOpt)
        return {};

    LambdaConstNode *lam = lamOpt.value();

    lam->type = const_cast<TypeInvoke *>(dynamic_cast<const TypeInvoke *>(funcSym->type)); // FIXME: DO BETTER! NEEDED B/C OF NAME RES!

    lam->name = funcSym->getIdentifier(); // Not really needed.
    return lam;
}

std::optional<InitProductNode *> SemanticVisitor::visitCtx(WPLParser::InitProductContext *ctx)
{
    std::string name = ctx->v->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(name);

    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Cannot initialize undefined product: " + name);
        return {};
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
            return {}; // TODO: Could change this to the return type to catch more errors?
        }

        std::vector<TypedNode *> n;

        {
            unsigned int i = 0;

            for (auto eleItr : elements)
            {
                std::optional<TypedNode *> opt = anyOpt2Val<TypedNode *>(ctx->exprs.at(i)->accept(this));

                if (!opt)
                    return {}; // FIXME: DO BETTER

                TypedNode *tn = opt.value();

                n.push_back(tn);
                const Type *providedType = tn->getType();

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

        // return sym->type;
        return new InitProductNode(product, n); // FIXME: SHOULD NOT RETURN THIS IF THE ARGS FAIL!!
    }

    errorHandler.addSemanticError(ctx->getStart(), "Cannot initialize non-product type " + name + " : " + sym->type->toString());
    return {};
}

std::optional<ArrayAccessNode *> SemanticVisitor::visitCtx(WPLParser::ArrayAccessContext *ctx, bool is_rvalue)
{
    /*
     * Check that we are provided an INT for the index.
     */
    std::optional<TypedNode *> exprOpt = anyOpt2Val<TypedNode *>(ctx->index->accept(this));
    if (!exprOpt)
        return {}; // FIXME: DO BETTER
    TypedNode *expr = exprOpt.value();

    const Type *exprType = expr->getType(); // any2Type(ctx->index->accept(this));
    if (exprType->isNotSubtype(Types::INT))
    {
        errorHandler.addSemanticError(ctx->getStart(), "Array access index expected type INT but got " + exprType->toString());
    }

    /*
     * Look up the symbol and check that it is defined.
     */

    // const Type *type = any2Type(ctx->field->accept(this));
    // std::optional<Symbol *> opt = bindings->getBinding(ctx->field->VARIABLE().at(ctx->field->VARIABLE().size() - 1));
    std::optional<FieldAccessNode *> opt = visitCtx(ctx->field, false); // Always have to load the array field
    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Cannot access value from undefined array: " + ctx->field->getText());
        return {};
    }

    /*
     * Check that the symbol is of array type.
     */

    // Symbol *sym = opt.value();
    FieldAccessNode *field = opt.value();

    if (const TypeArray *arr = dynamic_cast<const TypeArray *>(field->getType())) // FIXME: Verify that the symbol type matches the return type ?
    {
        // return arr->getValueType(); // Return type of array
        return new ArrayAccessNode(field, expr, is_rvalue); // FIXME: THIS SHOULD NOT HAPPEN IF INDEX CHECK FAILS!
    }

    // Report error
    errorHandler.addSemanticError(ctx->getStart(), "Cannot use array access on non-array expression " + ctx->field->getText() + " : " + field->getType()->toString());
    return {};
}

std::optional<TypedNode *> SemanticVisitor::visitCtx(WPLParser::ArrayOrVarContext *ctx)
{
    // FIXME: WHEN WE SWITCH VAR TO FIELD ACCESS, MAY BE ABLE TO DELETE VAR NODE!

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
            return {};
        }

        // Otherwise, get the symbol's value
        Symbol *symbol = opt.value().second;

        // Bind the larger context to the symbol, and return the symbol's type.
        // bindings->bind(ctx, symbol);
        return new VariableIDNode(symbol, false);
    }

    /*
     * As we are not a var, we must be an array access, so we must visit that context.
     */
    // const Type *arrType = this->visitCtx(ctx->array);

    // // Lookup the binding of the array
    // std::optional<Symbol *> binding = bindings->getBinding(ctx->array);

    // // If we didn't get a binding, report an error.
    // if (!binding)
    // {
    //     errorHandler.addSemanticError(ctx->array->getStart(), "Could not correctly bind to array access!");
    //     return Types::UNDEFINED;
    // }

    // // Otherwise, bind this context to the same binding as the array access, and return its type.
    // bindings->bind(ctx, binding.value());
    return this->visitCtx(ctx->array, false);
}

std::optional<IConstExprNode *> SemanticVisitor::visitCtx(WPLParser::IConstExprContext *ctx)
{
    return new IConstExprNode(std::stoi(ctx->i->getText()));
    // return Types::INT;
}

std::optional<StringConstNode *> SemanticVisitor::visitCtx(WPLParser::SConstExprContext *ctx)
{
    // TODO: do this better, ensure that we can only escape these chars...
    std::string full(ctx->s->getText());
    std::string actual = full.substr(1, full.length() - 2);

    std::vector<std::pair<std::regex, std::string>> replacements;

    // Reference of all escape characters: https://en.cppreference.com/w/cpp/language/escape
    std::regex SQ("\\\\'");
    std::regex DQ("\\\\\"");
    std::regex QM("\\\\\\?");
    std::regex SL("\\\\\\\\");
    std::regex AB("\\\\a");
    std::regex BS("\\\\b");
    std::regex FF("\\\\f");
    std::regex NL("\\\\n");
    std::regex CR("\\\\r");
    std::regex HT("\\\\t");
    std::regex VT("\\\\v");

    replacements.push_back({SQ, "\'"});
    replacements.push_back({DQ, "\""});
    replacements.push_back({QM, "\?"});
    replacements.push_back({AB, "\a"});
    replacements.push_back({BS, "\b"});
    replacements.push_back({FF, "\f"});
    replacements.push_back({NL, "\n"});
    replacements.push_back({CR, "\r"});
    replacements.push_back({HT, "\t"});
    replacements.push_back({VT, "\v"});
    replacements.push_back({SL, "\\"});

    std::string out = actual;

    for (auto e : replacements)
    {
        out = regex_replace(out, e.first, e.second);
    }

    return new StringConstNode(out);
}

/**
 * @brief Typechecks Unary Expressions
 *
 * @param ctx The UnaryExpressionContext to type check
 * @return const Type* Returns the type of the inner expression if valid; UNDEFINED otherwise.
 */
std::optional<UnaryExprNode *> SemanticVisitor::visitCtx(WPLParser::UnaryExprContext *ctx)
{
    // Lookup the inner type
    std::optional<TypedNode *> innerNodeOpt = anyOpt2Val<TypedNode *>(ctx->ex->accept(this));
    if (!innerNodeOpt)
        return {};

    TypedNode *innerNode = innerNodeOpt.value();

    const Type *innerType = innerNode->getType();

    // Switch on the operation so we can ensure that the type and operation are compatable.
    switch (ctx->op->getType())
    {
    case WPLParser::MINUS:
        if (innerType->isNotSubtype(Types::INT))
        {
            errorHandler.addSemanticError(ctx->getStart(), "INT expected in unary minus, but got " + innerType->toString());
            return {};
        }
        return new UnaryExprNode(UNARY_MINUS, innerNode);
    case WPLParser::NOT:
        if (innerType->isNotSubtype(Types::BOOL))
        {
            errorHandler.addSemanticError(ctx->getStart(), "BOOL expected in unary not, but got " + innerType->toString());
            return {};
        }
        return new UnaryExprNode(UNARY_NOT, innerNode);
    }

    return {}; // FIXME: ERROR?
}

/**
 * @brief Visits a Binary Arithmetic Expression ensuring LHS and RHS are INT.
 *
 * @param ctx The BinaryArithExprContext to Visit
 * @return const Type* INT if lhs and rhs are INT; UNDEFINED otherwise.
 */
std::optional<BinaryArithNode *> SemanticVisitor::visitCtx(WPLParser::BinaryArithExprContext *ctx)
{
    bool valid = true;

    auto leftOpt = anyOpt2Val<TypedNode *>(ctx->left->accept(this));
    if (!leftOpt)
        return {}; // FIXME: THROW ERROR?

    auto left = leftOpt.value();

    if (left->getType()->isNotSubtype(Types::INT))
    {
        errorHandler.addSemanticError(ctx->getStart(), "INT left expression expected, but was " + left->getType()->toString());
        valid = false;
    }

    auto rightOpt = anyOpt2Val<TypedNode *>(ctx->right->accept(this));
    if (!rightOpt)
        return {}; // FIXME: DO BETTER

    auto right = rightOpt.value();

    if (right->getType()->isNotSubtype(Types::INT))
    {
        errorHandler.addSemanticError(ctx->getStart(), "INT right expression expected, but was " + right->getType()->toString());
        valid = false;
    }

    if (valid)
        return new BinaryArithNode(
            ctx->MULTIPLY() ? BINARY_ARITH_MULT : ctx->DIVIDE() ? BINARY_ARITH_DIV
                                              : ctx->PLUS()     ? BINARY_ARITH_PLUS
                                                                : BINARY_ARITH_MINUS,
            left,
            right);

    return {};
}

std::optional<EqExprNode *> SemanticVisitor::visitCtx(WPLParser::EqExprContext *ctx)
{
    std::optional<TypedNode *> rhsOpt = anyOpt2Val<TypedNode *>(ctx->right->accept(this));
    std::optional<TypedNode *> lhsOpt = anyOpt2Val<TypedNode *>(ctx->left->accept(this));

    // FIXME: BAD ACCESS

    TypedNode *lhs = lhsOpt.value();
    TypedNode *rhs = rhsOpt.value();

    if (rhs->getType()->isNotSubtype(lhs->getType()))
    {
        errorHandler.addSemanticError(ctx->getStart(), "Both sides of '=' must have the same type");
        // return Types::UNDEFINED;
    }

    // Note: As per C spec, arrays cannot be compared
    if (dynamic_cast<const TypeArray *>(lhs->getType()) || dynamic_cast<const TypeArray *>(rhs->getType()))
    {
        errorHandler.addSemanticError(ctx->getStart(), "Cannot perform equality operation on arrays; they are always seen as unequal!");
    }

    // return Types::BOOL;
    return new EqExprNode(
        ctx->EQUAL() ? EQUAL_OP : NOT_EQUAL_OP,
        lhs, rhs);
}

/**
 * @brief Visits a Logical And Expression ensuring LHS and RHS are BOOL.
 *
 * @param ctx The LogAndExprContext to Visit
 * @return const Type* BOOL if lhs and rhs are BOOL; UNDEFINED otherwise.
 */
std::optional<LogAndExprNode *> SemanticVisitor::visitCtx(WPLParser::LogAndExprContext *ctx)
{
    std::vector<WPLParser::ExpressionContext *> toVisit = ctx->exprs;
    std::vector<WPLParser::ExpressionContext *> toGen;

    while (toVisit.size() > 0)
    {
        WPLParser::ExpressionContext *curr = toVisit.at(0);
        toVisit.erase(toVisit.begin());

        if (WPLParser::LogAndExprContext *orCtx = dynamic_cast<WPLParser::LogAndExprContext *>(curr))
        {
            toVisit.insert(toVisit.end(), orCtx->exprs.begin(), orCtx->exprs.end());
        }
        else
        {
            toGen.push_back(curr);
        }
    }

    std::vector<TypedNode *> nodes;

    for (WPLParser::ExpressionContext *e : toGen)
    {
        // const Type *type = any2Type(e->accept(this));
        std::optional<TypedNode *> nodeOpt = anyOpt2Val<TypedNode *>(e->accept(this));
        if (!nodeOpt)
        {
            // FIXME: DO WE NEED TO THROW ERROR? OR IS IT ALREADY HANDLED
        }
        else
        {
            TypedNode *node = nodeOpt.value();
            const Type *type = node->getType();

            if (type->isNotSubtype(Types::BOOL))
            {
                errorHandler.addSemanticError(e->getStart(), "BOOL expression expected, but was " + type->toString());
            }
            else
            {
                nodes.push_back(node);
            }
        }
    }
    return new LogAndExprNode(nodes);
}

/**
 * @brief Visits a Logical Or Expression ensuring LHS and RHS are BOOL.
 *
 * @param ctx The LogOrExprContext to Visit
 * @return const Type* BOOL if lhs and rhs are BOOL; UNDEFINED otherwise.
 */
std::optional<LogOrExprNode *> SemanticVisitor::visitCtx(WPLParser::LogOrExprContext *ctx)
{
    std::vector<WPLParser::ExpressionContext *> toVisit = ctx->exprs;
    std::vector<WPLParser::ExpressionContext *> toGen;

    while (toVisit.size() > 0)
    {
        WPLParser::ExpressionContext *curr = toVisit.at(0);
        toVisit.erase(toVisit.begin());

        if (WPLParser::LogOrExprContext *orCtx = dynamic_cast<WPLParser::LogOrExprContext *>(curr))
        {
            toVisit.insert(toVisit.end(), orCtx->exprs.begin(), orCtx->exprs.end());
        }
        else
        {
            toGen.push_back(curr);
        }
    }

    std::vector<TypedNode *> nodes;

    for (WPLParser::ExpressionContext *e : toGen)
    {
        // const Type *type = any2Type(e->accept(this));
        std::optional<TypedNode *> nodeOpt = anyOpt2Val<TypedNode *>(e->accept(this));
        if (!nodeOpt)
        {
            // FIXME: DO WE NEED TO THROW ERROR? OR IS IT ALREADY HANDLED
        }
        else
        {
            TypedNode *node = nodeOpt.value();
            const Type *type = node->getType();

            if (type->isNotSubtype(Types::BOOL))
            {
                errorHandler.addSemanticError(e->getStart(), "BOOL expression expected, but was " + type->toString());
            }
            else
            {
                nodes.push_back(node);
            }
        }
    }
    return new LogOrExprNode(nodes);
}

/**
 * @brief Visits a FieldAccessExprContext---Currently limited to array lengths
 *
 * @param ctx the FieldAccessExprContext to visit
 * @return const Type* INT if correctly used to test array length; UNDEFINED if any errors.
 */
std::optional<FieldAccessNode *> SemanticVisitor::visitCtx(WPLParser::FieldAccessExprContext *ctx, bool is_rvalue)
{
    // Determine the type of the expression we are visiting
    std::optional<SymbolContext> opt = stmgr->lookup(ctx->VARIABLE().at(0)->getText());
    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Undefined variable reference: " + ctx->VARIABLE().at(0)->getText());
        return {};
    }
    Symbol *sym = opt.value().second;

    if (opt.value().first == LINEAR_SCOPE) //FIXME: WILL NEED TO IMPL THIS BETTER!
    {
        
        if (!is_rvalue)
        {
            errorHandler.addSemanticError(ctx->getStart(), "Cannot redefine linear variable!");
        }
        
        if(!stmgr->removeSymbol(sym)) {
            errorHandler.addSemanticError(ctx->getStart(), "Failed to unbind local var!");
        }


    }

    std::vector<std::pair<std::string, const Type *>> a;
    // bindings->bind(ctx->VARIABLE().at(0), sym);

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
                a.push_back({fieldName,
                             ty});
                // Symbol *bnd = new Symbol("", ty, false, false);
                // bindings->bind(ctx->VARIABLE().at(i), bnd); // FIXME: DO BETTER
            }
            else
            {
                errorHandler.addSemanticError(ctx->getStart(), "Cannot access " + fieldName + " on " + ty->toString());
                return {};
            }
        }
        else if (i + 1 == ctx->fields.size() && dynamic_cast<const TypeArray *>(ty) && ctx->fields.at(i)->getText() == "length")
        {
            bindings->bind(ctx->VARIABLE().at(i), new Symbol("", Types::INT, false, false)); // FIXME: DO BETTER
            // return Types::INT;

            a.push_back({"length",
                         Types::INT});

            break; // FIXME: SHOULDNT BE NEEDED, BUT PROBS IS BC OF LOOP WEIRDNESSES?
        }
        else
        {
            errorHandler.addSemanticError(ctx->getStart(), "Cannot access " + fieldName + " on " + ty->toString());
            return {};
        }
    }

    // errorHandler.addSemanticError(ctx->getStart(), "Unsupported operation on " + ty->toString());

    return new FieldAccessNode(sym, is_rvalue, a);
}

// Passthrough to expression
std::optional<TypedNode *> SemanticVisitor::visitCtx(WPLParser::ParenExprContext *ctx) { return anyOpt2Val<TypedNode *>(ctx->ex->accept(this)); }

/**
 * @brief Visits a BinaryRelational Expression ensuring both lhs and rhs are INT.
 *
 * @param ctx The BinaryRelExprContext to visit.
 * @return const Type* BOOL if lhs and rhs INT; UNDEFINED otherwise.
 */
std::optional<BinaryRelNode *> SemanticVisitor::visitCtx(WPLParser::BinaryRelExprContext *ctx)
{
    bool valid = true;

    auto leftOpt = anyOpt2Val<TypedNode *>(ctx->left->accept(this));
    if (!leftOpt)
        return {}; // FIXME: THROW ERROR?

    auto left = leftOpt.value();

    if (left->getType()->isNotSubtype(Types::INT))
    {
        errorHandler.addSemanticError(ctx->getStart(), "INT left expression expected, but was " + left->getType()->toString());
        valid = false;
    }

    auto rightOpt = anyOpt2Val<TypedNode *>(ctx->right->accept(this));
    if (!rightOpt)
        return {}; // FIXME: DO BETTER

    auto right = rightOpt.value();

    if (right->getType()->isNotSubtype(Types::INT))
    {
        errorHandler.addSemanticError(ctx->getStart(), "INT right expression expected, but was " + right->getType()->toString());
        valid = false;
    }

    if (valid)
        return new BinaryRelNode(
            ctx->LESS() ? BINARY_Rel_LESS : ctx->LESS_EQ() ? BINARY_Rel_LESS_EQ
                                        : ctx->GREATER()   ? BINARY_Rel_GREATER
                                                           : BINARY_Rel_GREATER_EQ,
            left,
            right);

    return {};
}

/**
 * @brief Visits a condition's expression ensuring that it is of type BOOL.
 *
 * @param ctx The ConditionContext to visit
 * @return const Type* Always returns UNDEFINED as to prevent assignments
 */
std::optional<ConditionNode *> SemanticVisitor::visitCtx(WPLParser::ConditionContext *ctx)
{
    // auto conditionType = any2Type(ctx->ex->accept(this));
    std::optional<TypedNode *> condOpt = anyOpt2Val<TypedNode *>(ctx->ex->accept(this));

    if (!condOpt)
        return {}; // FIXME: DO BETTER

    TypedNode *cond = condOpt.value();
    const Type *conditionType = cond->getType();

    if (conditionType->isNotSubtype(Types::BOOL))
    {
        errorHandler.addSemanticError(ctx->getStart(), "Condition expected BOOL, but was given " + conditionType->toString());
        return {};
    }

    return new ConditionNode(cond); // FIXME: THIS SEEMS KIND OF POINTLESS...
}

std::optional<SelectAlternativeNode *> SemanticVisitor::visitCtx(WPLParser::SelectAlternativeContext *ctx)
{
    errorHandler.addSemanticError(ctx->getStart(), "COMP ERROR");
    return {}; // FIXME: REMOVE?
}

/**
 * @brief Constructs a TypeInvoke based on the parameter types and assumes a return type of BOT.
 *
 * @param ctx The ParameterListContext to process.
 * @return const Type* TypeInvoke representing the parameter types.
 */
std::optional<ParameterListNode> SemanticVisitor::visitCtx(WPLParser::ParameterListContext *ctx)
{
    std::map<std::string, WPLParser::ParameterContext *> map;

    ParameterListNode paramList;

    // if (ctx->params)
    // {
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

        ParameterNode pn = this->visitCtx(param); // FIXME: WHAT SHOULD BE POINTERS?
        paramList.push_back(pn);
    }
    // }
    return paramList;
}

ParameterNode SemanticVisitor::visitCtx(WPLParser::ParameterContext *ctx)
{
    return ParameterNode(any2Type(ctx->ty->accept(this)), ctx->name->getText()); // FIXME: WHAT AB ERRORS?
}

const Type *SemanticVisitor::visitCtx(WPLParser::AssignmentContext *ctx)
{
    errorHandler.addSemanticError(ctx->getStart(), "Assignment should never be visited directly during type checking!");
    return Types::UNDEFINED;
}

std::optional<ExternNode *> SemanticVisitor::visitCtx(WPLParser::ExternStatementContext *ctx)
{

    bool variadic = ctx->variadic || ctx->ELLIPSIS();

    std::string id = ctx->name->getText();

    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Unsupported redeclaration of " + id);
        return {};
        // return Types::UNDEFINED;
    }

    std::optional<ParameterListNode> tyOpt = (ctx->paramList) ? this->visitCtx(ctx->paramList)
                                                              : ParameterListNode();

    const Type *retType = ctx->ty ? any2Type(ctx->ty->accept(this)) // this->visitCtx(ctx->ty)
                                  : Types::UNDEFINED;

    ExternNode *node = new ExternNode(id, tyOpt.value(), retType, variadic); // FIXME: BAD OPT ACCESS!

    // const TypeInvoke *funcType = (ctx->ty) ? new TypeInvoke(procType->getParamTypes(), retType, variadic, true)
    //                                        : new TypeInvoke(procType->getParamTypes(), variadic, true);

    // Symbol *funcSymbol = new Symbol(id, funcType, true, true);

    stmgr->addSymbol(node->getSymbol());
    // bindings->bind(ctx, funcSymbol);

    return node;
};

std::optional<AssignNode *> SemanticVisitor::visitCtx(WPLParser::AssignStatementContext *ctx)
{
    // This one is the update one!

    // Determine the expression type
    std::optional<TypedNode *> exprOpt = anyOpt2Val<TypedNode *>(ctx->a->accept(this));

    if (!exprOpt)
        return {}; // FIXME: DO BETTER?

    TypedNode *expr = exprOpt.value();
    const Type *exprType = expr->getType();

    // Determine the expected type
    std::optional<TypedNode *> varOpt = this->visitCtx(ctx->to);

    // If we actually have a type... (prevents things like null ptrs)
    if (!varOpt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Cannot assign to undefined variable: " + ctx->to->getText());
        return {};
    }

    TypedNode *var = varOpt.value();

    const Type *type = var->getType();

    // Make sure that the types are compatible. Inference automatically managed here.
    if (exprType->isNotSubtype(type))
    {
        errorHandler.addSemanticError(ctx->getStart(), "Assignment statement expected " + type->toString() + " but got " + exprType->toString());
        return {};
    }

    // Return UNDEFINED because this is a statement, and UNDEFINED cannot be assigned to anything
    return new AssignNode(var, expr);
}

std::optional<VarDeclNode *> SemanticVisitor::visitCtx(WPLParser::VarDeclStatementContext *ctx)
{
    std::vector<AssignmentNode *> a;

    for (auto e : ctx->assignments)
    {
        // Needs to happen in case we have vars
        const Type *assignType = this->visitCtx(ctx->typeOrVar());
        // auto exprType = (e->a) ? any2Type(e->a->accept(this)) : assignType;

        std::optional<TypedNode *> exprOpt = (e->a) ? anyOpt2Val<TypedNode *>(e->a->accept(this)) : std::nullopt;

        const Type *exprType = exprOpt ? exprOpt.value()->getType() : assignType;

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

        std::vector<Symbol *> s;

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

                // FIXME: BAD OPT ACCESS
                // const Type *newExprType = (dynamic_cast<const TypeInfer *>(newAssignType) && e->a) ? anyOpt2Val<TypedNode *>(e->a->accept(this)).value()->getType() : newAssignType;
                std::optional<const Type *> newExprTypeOpt = [this, e, newAssignType]() -> std::optional<const Type *>
                {
                    // const Type *newExprType = newAssignType;
                    if (dynamic_cast<const TypeInfer *>(newAssignType) && e->a)
                    {
                        std::optional<TypedNode *> opt = anyOpt2Val<TypedNode *>(e->a->accept(this));

                        if (!opt)
                            return std::nullopt; // FIXME: DO BETTER

                        TypedNode *tn = opt.value();

                        return tn->getType();
                    }

                    return newAssignType;
                }();

                if (!newExprTypeOpt)
                    return {}; // FIXME: DO BETTER

                const Type *newExprType = newExprTypeOpt.value();

                Symbol *symbol = new Symbol(id, newExprType, false, stmgr->isGlobalScope()); // Done with exprType for later inferencing purposes
                stmgr->addSymbol(symbol);

                // bindings->bind(var, symbol);
                s.push_back(symbol);
            }
        }
        a.push_back(new AssignmentNode(s, exprOpt));
    }
    // FIXME: SHOULDNT RETURN IF ERRORS!!
    //  Return UNDEFINED because this is a statement, and UNDEFINED cannot be assigned to anything
    //  return Types::UNDEFINED;
    return new VarDeclNode(a);
}

std::optional<MatchStatementNode *> SemanticVisitor::visitCtx(WPLParser::MatchStatementContext *ctx)
{
    std::optional<TypedNode *> condOpt = anyOpt2Val<TypedNode *>(ctx->check->ex->accept(this));

    if (!condOpt)
        return {}; // FIXME: DO BETTER

    TypedNode *cond = condOpt.value();

    if (const TypeSum *sumType = dynamic_cast<const TypeSum *>(cond->getType()))
    {
        std::vector<std::pair<Symbol *, TypedNode *>> cases;

        std::set<const Type *> foundCaseTypes = {};
        // TODO: Maybe make so these can return values?

        std::vector<Symbol *> syms = stmgr->getAvaliableLinears(); // FIXME: WILL TRY TO REBIND VAR WE JUST BOUND TO NEW CHAN VALUE!
        // stmgr->deleteAvaliableLinears();

        std::vector<std::pair<const TypeChannel *, const ProtocolSequence *>> to_fix; // FIXME: DO BETTER!
        for (Symbol *orig : syms)
        {
            // FIXME: DO BETTER, WONT WORK WITH VALUES!
            if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(orig->type))
            {
                to_fix.push_back({channel, channel->getProtocolCopy()});
                // channel->setProtocol(protoOpt.value());
                // stmgr->addSymbol(orig);
            }
        }

        for (WPLParser::MatchAlternativeContext *altCtx : ctx->cases)
        {
            // stmgr->enterScope(StopType::NONE); // FIXME: THIS SORT OF THING HAS ISSUES WITH ALLOWING FOR REDCLS OF VARS IN VARIOIUS SCOPES!!! (THIS EFFECTIVLEY FLATTENS THINGS)

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

            stmgr->enterScope(StopType::NONE); // Once for the case variable, and once to ensure all linears used //FIXME: VERIFY THIS CANT BE DONE ALL IN ONE!

            for (auto pair : to_fix)
            {
                // FIXME: MAY NEED TO RE-BIND SYMBOL HERE AS WELL! IF NOT, WHY DO WE REBIND ABOVE?
                pair.first->setProtocol(pair.second->getCopy());
            }

            stmgr->enterScope(StopType::NONE);
            // stmgr->enterScope(StopType::LINEAR); // FIXME: COMMENT WHAT THIS DOES AND VERIFY WITH NEW CHANGES!
            Symbol *local = new Symbol(altCtx->name->getText(), caseType, false, false); // FIXME: DO WE EVER CHECK THIS NAME IS UNIQUE? THIS MAY MATTER NOW W/ LINEARS? IDK MAYBE NOT
            stmgr->addSymbol(local);

            // bindings->bind(altCtx->VARIABLE(), local);

            std::optional<TypedNode *> tnOpt = anyOpt2Val<TypedNode *>(altCtx->eval->accept(this));
            this->safeExitScope(altCtx);

            if (!tnOpt)
                return {}; // FIXME: DO BETTER

            if (dynamic_cast<WPLParser::ProgDefContext *>(altCtx->eval) ||
                dynamic_cast<WPLParser::VarDeclStatementContext *>(altCtx->eval) ||
                dynamic_cast<WPLParser::FuncDefContext *>(altCtx->eval))
            {
                errorHandler.addSemanticError(altCtx->getStart(), "Dead code: definition as select alternative.");
            }

            cases.push_back({local, tnOpt.value()});

            // For tracking linear stuff //FIXMEL TRACK RETURN/EXIT
            for (auto s : ctx->rest)
            {
                s->accept(this); // FIXME: DO BETTER
            }
            safeExitScope(ctx);
        }

        if (foundCaseTypes.size() != sumType->getCases().size())
        {
            errorHandler.addSemanticError(ctx->getStart(), "Match statement did not cover all cases needed for " + sumType->toString());
        }

        std::vector<TypedNode *> restVec; // FIXME: DO BETTER
        bool valid = true;

        // Need to re-add symbols for fallthrough case. Really seems like this all could be done more efficiently, though...
        for (auto pair : to_fix)
        {
            // FIXME: MAY NEED TO RE-BIND SYMBOL HERE AS WELL!
            pair.first->setProtocol(pair.second->getCopy());
        }

        for (auto s : ctx->rest)
        {
            std::optional<TypedNode *> tnOpt = anyOpt2Val<TypedNode *>(s->accept(this));
            if (!tnOpt)
                valid = false; // FIXME: THIS ISNT GOOD ENOUGH MAYBE BC COULD FAIL FAISE? IDK
            else
                restVec.push_back(tnOpt.value());
        }

        if (!valid)
            return {}; // FIXME: DO BETTER

        // FIXME: DO WE NEED A SAFE EXIT HERE?

        // bindings->bind(ctx->check, new Symbol(ctx->check->ex->getText(), sumType, false, false));
        return new MatchStatementNode(sumType, cond, cases, restVec);
    }

    errorHandler.addSemanticError(ctx->check->getStart(), "Can only case on Sum Types, not " + cond->getType()->toString());
    return {};
}

/**
 * @brief Type checks a Loops
 *
 * @param ctx The LoopStatementContext to type check
 * @return const Type* UNDEFINED as this is a statement.
 */
std::optional<WhileLoopNode *> SemanticVisitor::visitCtx(WPLParser::ProgramLoopContext *ctx)
{
    std::optional<ConditionNode *> checkOpt = this->visitCtx(ctx->check); // Visiting check will make sure we have a boolean condition

    if (!checkOpt)
        return {}; // FIXME: DO BETTER

    std::vector<Symbol *> syms = stmgr->getAvaliableLinears();

    stmgr->enterScope(StopType::LINEAR); // TODO: DO BETTER

    std::vector<std::pair<const TypeChannel *, const ProtocolSequence *>> to_fix;

    for (Symbol *orig : syms)
    {
        if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(orig->type))
        {
            std::optional<const ProtocolSequence *> protoOpt = channel->getProtocol()->shearLoop();
            if (protoOpt)
            {
                // stmgr->addSymbol(new Symbol(orig->getIdentifier(), new TypeChannel(protoOpt.value()), false, false));
                to_fix.push_back({channel, channel->getProtocol()});
                channel->setProtocol(protoOpt.value());
                stmgr->addSymbol(orig);
            }
        }
    }

    // FIXME: CANT DO THIS ANYMORE B/C NEED BLOCKS AS PART OF AST!!!
    std::optional<BlockNode *> blkOpt = this->visitCtx(ctx->block()); // Visiting block to make sure everything type checks there as well

    safeExitScope(ctx);

    if (!blkOpt)
        return {}; // FIXME: DO BETTER, ALSO THERE ARE A LOT OF THESE BEFORE SAFE EXIT. WILL SUCH THINGS CAUSE PROBLEMS?

    for (auto pair : to_fix)
    {
        pair.first->setProtocol(pair.second);
    }

    // Return UNDEFINED because this is a statement, and UNDEFINED cannot be assigned to anything
    // return Types::UNDEFINED;
    return new WhileLoopNode(checkOpt.value(), blkOpt.value());
}

std::optional<ConditionalStatementNode *> SemanticVisitor::visitCtx(WPLParser::ConditionalStatementContext *ctx)
{
    // Automatically handles checking that we have a valid condition
    std::optional<ConditionNode *> condOpt = this->visitCtx(ctx->check);

    if (!condOpt)
        return {}; // FIXME: DO BETTER

    std::vector<TypedNode *> restVec; // FIXME: DO BETTER
    bool valid = true;
    bool restGenerated = false;

    std::vector<Symbol *> syms = stmgr->getAvaliableLinears();                    // FIXME: WILL TRY TO REBIND VAR WE JUST BOUND TO NEW CHAN VALUE!
    std::vector<std::pair<const TypeChannel *, const ProtocolSequence *>> to_fix; // FIXME: DO BETTER!
    for (Symbol *orig : syms)
    {
        // FIXME: DO BETTER, WONT WORK WITH VALUES!
        if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(orig->type))
        {
            to_fix.push_back({channel, channel->getProtocolCopy()});
            // channel->setProtocol(protoOpt.value());
            // stmgr->addSymbol(orig);
        }
    }
    // stmgr->deleteAvaliableLinears();                           // FIXME: UNSAFE

    // Type check the then/true block
    stmgr->enterScope(StopType::NONE); // FIXME: THIS SORT OF THING HAS ISSUES WITH ALLOWING FOR REDCLS OF VARS IN VARIOIUS SCOPES!!! (THIS EFFECTIVLEY FLATTENS THINGS) -> No???
    for (auto pair : to_fix)
    {
        // FIXME: MAY NEED TO RE-BIND SYMBOL HERE AS WELL!
        pair.first->setProtocol(pair.second->getCopy());
    }

    // for (const Symbol *orig : syms)    // FIXME: VERIFY GOOD ENOUGH; ELSEWHERE HAS OTHER CHECKS!
    // {
    //     // FIXME: DO BETTER!!!!! WONT WORK FOR NON-CHANNELS! AND ALSO WONT WORK FOR VALUES!!!
    //     if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(orig->type))
    //     {
    //         stmgr->addSymbol(new Symbol(orig->getIdentifier(), channel->getCopy(), false, false));
    //     }
    // }
    std::optional<BlockNode *> trueOpt = this->visitCtx(ctx->trueBlk);
    if (!trueOpt)
        return {}; // FIXME: DO BETTER

    BlockNode *trueBlk = trueOpt.value();
    if (!endsInReturn(trueBlk))
    {
        restGenerated = true;

        for (auto s : ctx->rest)
        {
            std::optional<TypedNode *> tnOpt = anyOpt2Val<TypedNode *>(s->accept(this));
            if (!tnOpt)
                valid = false; // FIXME: THIS ISNT GOOD ENOUGH MAYBE BC COULD FAIL FAISE? IDK
            else
                restVec.push_back(tnOpt.value());
        }
    }
    safeExitScope(ctx);

    // If we have an else block, then type check it
    if (ctx->falseBlk)
    {
        // FIXME: VERIFY GOOD ENOUGH, METHODIZE
        stmgr->enterScope(StopType::NONE); // FIXME: THIS SORT OF THING HAS ISSUES WITH ALLOWING FOR REDCLS OF VARS IN VARIOIUS SCOPES!!! (THIS EFFECTIVLEY FLATTENS THINGS)
        for (auto pair : to_fix)
        {
            // FIXME: MAY NEED TO RE-BIND SYMBOL HERE AS WELL!
            pair.first->setProtocol(pair.second->getCopy());
        }

        std::optional<BlockNode *> falseOpt = this->visitCtx(ctx->falseBlk);

        if (!falseOpt)
            return {}; // FIXME: DO BETTER{}

        BlockNode *falseBlk = falseOpt.value();

        if (!endsInReturn(falseBlk))
        {
            for (auto s : ctx->rest)
            {
                std::optional<TypedNode *> tnOpt = anyOpt2Val<TypedNode *>(s->accept(this));
                if (!tnOpt)
                    valid = false;       // FIXME: THIS ISNT GOOD ENOUGH MAYBE BC COULD FAIL FAISE? IDK
                else if (!restGenerated) // FIXME: DO OPTIMIZATIONS IF THIS ISNT NEEDED!
                    restVec.push_back(tnOpt.value());
            }
            restGenerated = true;
        }
        safeExitScope(ctx);

        if (!valid)
            return {};

        return new ConditionalStatementNode(condOpt.value(), trueBlk, restVec, falseBlk);
    }

    // Type check the then/true block
    stmgr->enterScope(StopType::NONE); // FIXME: THIS SORT OF THING HAS ISSUES WITH ALLOWING FOR REDCLS OF VARS IN VARIOIUS SCOPES!!! (THIS EFFECTIVLEY FLATTENS THINGS)
    for (auto pair : to_fix)
    {
        // FIXME: MAY NEED TO RE-BIND SYMBOL HERE AS WELL!
        pair.first->setProtocol(pair.second->getCopy());
    }

    for (auto s : ctx->rest)
    {
        std::optional<TypedNode *> tnOpt = anyOpt2Val<TypedNode *>(s->accept(this));
        if (!tnOpt)
            valid = false; // FIXME: THIS ISNT GOOD ENOUGH MAYBE BC COULD FAIL FAISE? IDK
        else if (!restGenerated)
            restVec.push_back(tnOpt.value());
    }
    restGenerated = true;
    safeExitScope(ctx);

    return new ConditionalStatementNode(condOpt.value(), trueBlk, restVec);
    // Return UNDEFINED because this is a statement, and UNDEFINED cannot be assigned to anything
    // return Types::UNDEFINED;
}

std::optional<SelectStatementNode *> SemanticVisitor::visitCtx(WPLParser::SelectStatementContext *ctx)
{

    if (ctx->cases.size() < 1)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Select statement expected at least one alternative, but was given 0!");
        // return Types::UNDEFINED; // Shouldn't matter as the for loop won't have anything to do
        return {};
    }

    std::vector<Symbol *> syms = stmgr->getAvaliableLinears(); // FIXME: WILL TRY TO REBIND VAR WE JUST BOUND TO NEW CHAN VALUE!

    std::vector<std::pair<const TypeChannel *, const ProtocolSequence *>> to_fix; // FIXME: DO BETTER!
    for (Symbol *orig : syms)
    {
        // FIXME: DO BETTER, WONT WORK WITH VALUES!
        if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(orig->type))
        {
            to_fix.push_back({channel, channel->getProtocol()}); // NOTE HOW THIS ONE ISNT A COPY!
        }
    }

    /*
     *  Now to test the select cases.... which can be a bit complicated
     */

    std::vector<SelectAlternativeNode *> alts;
    // Here we just need to visit each of the individual cases; they each handle their own logic.
    for (auto e : ctx->cases)
    {
        // Enter the scope (needed as we may define variables or do other stuff)
        // stmgr->enterScope(StopType::LINEAR);
        // Accept the evaluation context

        // Safe exit the scope
        // this->safeExitScope(e);

        /*
         *  Just make sure that we don't try to define functions and stuff in a select as that doesn't make sense (and would cause codegen issues as it stands).
         */
        if (dynamic_cast<WPLParser::ProgDefContext *>(e->eval) || // FIXME: DO BETTER, THERE MAY BE A LOT LIKE THIS!
            dynamic_cast<WPLParser::VarDeclStatementContext *>(e->eval) ||
            dynamic_cast<WPLParser::FuncDefContext *>(e->eval))
        {
            errorHandler.addSemanticError(e->getStart(), "Dead code: definition as select alternative.");
        }

        // Confirm that the check type is a boolean
        std::optional<TypedNode *> checkOpt = anyOpt2Val<TypedNode *>(e->check->accept(this));
        if (!checkOpt)
            return {}; // FIXME: DO BETTER

        TypedNode *check = checkOpt.value();
        const Type *checkType = check->getType();

        if (!dynamic_cast<const TypeBool *>(checkType))
        {
            errorHandler.addSemanticError(ctx->getStart(), "Select alternative expected BOOL but got " + checkType->toString());
            return {};
        }

        stmgr->enterScope(StopType::NONE); // For safe exit + scoping... //FIXME: verify...

        for (auto pair : to_fix)
        {
            // FIXME: MAY NEED TO RE-BIND SYMBOL HERE AS WELL! IF NOT, WHY DO WE REBIND ABOVE?
            pair.first->setProtocol(pair.second->getCopy());
        }

        std::optional<TypedNode *> evalOpt = anyOpt2Val<TypedNode *>(e->eval->accept(this)); // FIXME: So these are all wrong b/c like, we return optionals
        if (!evalOpt)
            return {}; // FIXME: DO BETTER

        // For tracking linear stuff //FIXMEL TRACK RETURN/EXIT
        TypedNode *eval = evalOpt.value();

        if (!endsInReturn(eval))
        {
            for (auto s : ctx->rest)
            {
                s->accept(this); // FIXME: DO BETTER
            }
        }
        safeExitScope(ctx);

        // std::optional<SelectAlternativeNode *> altOpt = this->visitCtx(e);
        // if (!altOpt)
        //     return {}; // FIXME: DO BETTER?

        alts.push_back(new SelectAlternativeNode(check, eval));
    }

    /*
     * Last, we test the rest block.... (bc theoretical use of linears in cond?) //FIXME: USE THEORY TO DETERMINE IF LINEARS CAN BE USED IN THINGS LIKE CONDITIONS AND THUS IF WE CAN SIMPLIFY SOME OF THE CHECKS!
     */

    std::vector<TypedNode *> restVec; // FIXME: DO BETTER
    bool valid = true;

    // Need to re-add symbols for fallthrough case. Really seems like this all could be done more efficiently, though...
    for (auto pair : to_fix)
    {
        // FIXME: MAY NEED TO RE-BIND SYMBOL HERE AS WELL!
        pair.first->setProtocol(pair.second->getCopy());
    }

    for (auto s : ctx->rest)
    {
        std::optional<TypedNode *> tnOpt = anyOpt2Val<TypedNode *>(s->accept(this));
        if (!tnOpt)
            valid = false; // FIXME: THIS ISNT GOOD ENOUGH MAYBE BC COULD FAIL FAISE? IDK
        else
            restVec.push_back(tnOpt.value());
    }

    if (!valid)
        return {}; // FIXME: DO BETTER

    // FIXME: DO WE NEED A SAFE EXIT HERE?

    // Return UNDEFINED because this is a statement, and UNDEFINED cannot be assigned to anything
    // return Types::UNDEFINED;
    return new SelectStatementNode(alts, restVec);
}

std::optional<ReturnNode *> SemanticVisitor::visitCtx(WPLParser::ReturnStatementContext *ctx)
{
    /*
     * Lookup the @RETURN symbol which can ONLY be defined by entering FUNC/PROC
     */
    std::optional<SymbolContext> symOpt = stmgr->lookup("@RETURN");

    // If we don't have the symbol, we're not in a place that we can return from.
    if (!symOpt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Cannot use return outside of FUNC or PROC");
        return {};
    }

    Symbol *sym = symOpt.value().second;

    // If the return statement has an expression...
    if (ctx->expression())
    {
        // Evaluate the expression type
        std::optional<TypedNode *> valOpt = anyOpt2Val<TypedNode *>(ctx->expression()->accept(this));

        if (!valOpt)
            return {}; // FIXME: DO BETTER

        TypedNode *val = valOpt.value();

        const Type *valType = val->getType();

        // If the type of the return symbol is a BOT, then we must be in a PROC and, thus, we cannot return anything
        if (const TypeBot *b = dynamic_cast<const TypeBot *>(sym->type))
        {
            errorHandler.addSemanticError(ctx->getStart(), "PROC cannot return value, yet it was given a " + valType->toString() + " to return!");
            return {};
        }

        // As the return type is not a BOT, we have to make sure that it is the correct type to return

        if (valType->isNotSubtype(sym->type))
        {
            errorHandler.addSemanticError(ctx->getStart(), "Expected return type of " + sym->type->toString() + " but got " + valType->toString());
            return {};
        }

        std::pair<const Type *, TypedNode *> ans = {sym->type, val};
        // Valid return statement; return UNDEFINED as its a statement.
        return new ReturnNode(ans); // FIXME: VERIFY CORRETC TYPE
    }

    // We do not have an expression to return, so make sure that the return type is also a BOT.
    if (const TypeBot *b = dynamic_cast<const TypeBot *>(sym->type))
    {
        return new ReturnNode();
    }

    errorHandler.addSemanticError(ctx->getStart(), "Expected to return a " + sym->type->toString() + " but recieved nothing.");
    return {};
}

std::optional<ExitNode *> SemanticVisitor::visitCtx(WPLParser::ExitStatementContext *ctx)
{
    // FIXME: ADD TESTS FOR EXIT FOR EACH RETURN TEST!!!

    std::optional<SymbolContext> symOpt = stmgr->lookup("@EXIT");

    // If we don't have the symbol, we're not in a place that we can return from.
    if (!symOpt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Cannot use exit outside of program");
        return {};
    }

    return new ExitNode();
}

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

std::optional<LambdaConstNode *> SemanticVisitor::visitCtx(WPLParser::LambdaConstExprContext *ctx)
{
    // FIXME: VERIFY THIS IS ALWAYS SAFE!!!
    std::optional<ParameterListNode> paramTypeOpt = visitCtx(ctx->parameterList());

    if (!paramTypeOpt)
        return {}; // FIXME: DO BETTER?

    ParameterListNode params = paramTypeOpt.value();
    std::vector<Symbol *> ps;

    // const Type *retType = any2Type(ctx->ret->accept(this));
    const Type *retType = ctx->ret ? any2Type(ctx->ret->accept(this)) // this->visitCtx(ctx->ty)
                                   : Types::UNDEFINED;

    // const TypeInvoke *funcType = new TypeInvoke(paramType->getParamTypes(), retType);

    stmgr->enterScope(StopType::GLOBAL);
    stmgr->addSymbol(new Symbol("@RETURN", retType, false, false));

    for (ParameterNode param : params) //(unsigned int i = 0; i < ctx->parameterList()->params.size(); i++)
    {
        // const Type *ty = funcType->getParamTypes().at(i);
        // auto param = ctx->parameterList()->params.at(i);

        Symbol *paramSymbol = new Symbol(param.name, param.type, false, false); // new Symbol(param->name->getText(), ty, false, false);
        stmgr->addSymbol(paramSymbol);

        ps.push_back(paramSymbol);
        // bindings->bind(param, paramSymbol);
    }

    std::optional<BlockNode *> blkOpt = this->safeVisitBlock(ctx->block(), false);

    if (!blkOpt)
        return {};
    BlockNode *blk = blkOpt.value();

    // If we have a return type, make sure that we return as the last statement in the FUNC. The type of the return is managed when we visited it.
    if (!endsInReturn(blk)) // ctx->block()->stmts.size() == 0 || !dynamic_cast<WPLParser::ReturnStatementContext *>(ctx->block()->stmts.at(ctx->block()->stmts.size() - 1)))
    {
        // FIXME: DO THIS CHECK BETTER WITH BLOCK NODE?
        errorHandler.addSemanticError(ctx->getStart(), "Lambda must end in return statement");
    }
    safeExitScope(ctx);

    // Symbol *funcSymbol = new Symbol("@LAMBDA", funcType, false, false);
    // bindings->bind(ctx, funcSymbol);

    // return funcType;
    return new LambdaConstNode(ps, retType, blk);
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

    for (auto e : ctx->type()) // FIXME: ADD TEST CASES LIKE THIS FOR STRUCT + ENUM!!
    {
        const Type *caseType = any2Type(e->accept(this));

        if (dynamic_cast<const TypeChannel *>(caseType)) // FIXME: DO BETTER LINEAR CHECK!
        {
            errorHandler.addSemanticError(e->getStart(), "Unable to store linear type, " + caseType->toString() + ", in non-linear container.");
            return {};
        }

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

std::optional<DefineEnumNode *> SemanticVisitor::visitCtx(WPLParser::DefineEnumContext *ctx)
{
    std::string id = ctx->name->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);
    if (opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Unsupported redeclaration of " + id);
        return {};
    }

    std::set<const Type *, TypeCompare> cases = {};

    for (auto e : ctx->cases)
    {
        const Type *caseType = any2Type(e->accept(this));

        if (dynamic_cast<const TypeChannel *>(caseType)) // FIXME: DO BETTER LINEAR CHECK!
        {
            errorHandler.addSemanticError(e->getStart(), "Unable to store linear type, " + caseType->toString() + ", in non-linear container.");
            return {};
        }

        cases.insert(caseType);
    }

    if (cases.size() != ctx->cases.size())
    {
        errorHandler.addSemanticError(ctx->getStart(), "Duplicate arguments to enum type, or failed to generate types");
        return {};
    }

    TypeSum *sum = new TypeSum(cases, id); // FIXME: SHOULD THIS BE CONST?
    Symbol *enumSym = new Symbol(id, sum, true, true);

    stmgr->addSymbol(enumSym);
    // bindings->bind(ctx, enumSym);

    // return Types::UNDEFINED;
    return new DefineEnumNode(id, sum);
}

std::optional<DefineStructNode *> SemanticVisitor::visitCtx(WPLParser::DefineStructContext *ctx)
{
    std::string id = ctx->name->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);
    if (opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Unsupported redeclaration of " + id);
        return {};
    }

    LinkedMap<std::string, const Type *> el;

    for (WPLParser::StructCaseContext *caseCtx : ctx->cases)
    {
        std::string caseName = caseCtx->name->getText();
        if (el.lookup(caseName))
        {
            errorHandler.addSemanticError(caseCtx->getStart(), "Unsupported redeclaration of " + caseName);
            return {};
        }
        const Type *caseTy = any2Type(caseCtx->ty->accept(this));

        if (dynamic_cast<const TypeChannel *>(caseTy)) // FIXME: DO BETTER LINEAR CHECK!
        {
            errorHandler.addSemanticError(caseCtx->getStart(), "Unable to store linear type, " + caseTy->toString() + ", in non-linear container.");
            return {};
        }

        el.insert({caseName, caseTy});
    }

    TypeStruct *product = new TypeStruct(el, id); // FIXME: SHOULD THIS BE CONST?
    Symbol *prodSym = new Symbol(id, product, true, true);
    stmgr->addSymbol(prodSym);
    // bindings->bind(ctx, prodSym);

    // return Types::UNDEFINED;
    return new DefineStructNode(id, product);

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
std::optional<BooleanConstNode *> SemanticVisitor::visitCtx(WPLParser::BooleanConstContext *ctx)
{
    return new BooleanConstNode(ctx->TRUE() ? true : false);
}

const Type *SemanticVisitor::visitCtx(WPLParser::ChannelTypeContext *ctx)
{
    const ProtocolSequence *proto = dynamic_cast<const ProtocolSequence *>(any2Protocol(ctx->proto->accept(this)));

    return new TypeChannel(proto);
}

const Type *SemanticVisitor::visitCtx(WPLParser::ProgramTypeContext *ctx)
{
    const ProtocolSequence *proto = dynamic_cast<const ProtocolSequence *>(any2Protocol(ctx->proto->accept(this)));
    return new TypeProgram(new TypeChannel(proto), true); // FIXME: SEEMS A BIT ODD TO INC CHANNEL IN PROGRAM?
}

std::optional<ProgramSendNode *> SemanticVisitor::TvisitProgramSend(WPLParser::ProgramSendContext *ctx)
{
    // FIXME: HAVE TO POTENTIALLY DELETE FROM CONTEXT OTHER VAR
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Could not find channel: " + id);
        return {};
    }

    Symbol *sym = opt.value().second;
    bindings->bind(ctx->VARIABLE(), sym); // For Channel

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        std::optional<TypedNode *> tnOpt = anyOpt2Val<TypedNode *>(ctx->expr->accept(this));
        if (!tnOpt)
            return {}; // FIXME: DO BETTER

        TypedNode *tn = tnOpt.value();
        const Type *ty = tn->getType();

        std::optional<const Type *> canSend = channel->getProtocol()->send(ty);

        if (!canSend)
        {
            errorHandler.addSemanticError(ctx->getStart(), "Failed to send " + ty->toString() + " over channel " + sym->toString());
            return {};
        }
        return new ProgramSendNode(sym, tn, canSend.value());
    }

    errorHandler.addSemanticError(ctx->getStart(), "Cannot send on non-channel: " + id);
    return {};
}

std::optional<ProgramRecvNode *> SemanticVisitor::TvisitAssignableRecv(WPLParser::AssignableRecvContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Could not find channel: " + id);
        return {};
    }

    Symbol *sym = opt.value().second;

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {

        std::optional<const Type *> ty = channel->getProtocol()->recv();
        if (!ty)
        {
            errorHandler.addSemanticError(ctx->getStart(), "Failed to recv over channel: " + sym->toString());
            return {};
        }

        // bindings->bind(ctx->VARIABLE(), sym);                          // For Channel
        // bindings->bind(ctx, new Symbol("", ty.value(), false, false)); // FIXME: DO BETTER, DONE SO WE CAN DO CORRECT BITCAST
        return new ProgramRecvNode(sym, ty.value());
    }

    errorHandler.addSemanticError(ctx->getStart(), "Cannot recv on non-channel: " + id);
    return {};
}

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

        std::vector<Symbol *> syms = stmgr->getAvaliableLinears(); // FIXME: WILL TRY TO REBIND VAR WE JUST BOUND TO NEW CHAN VALUE!
        stmgr->deleteAvaliableLinears();                           // FIXME: UNSAFE

        for (auto alt : ctx->protoAlternative())
        {
            const ProtocolSequence *proto = toSequence(any2Protocol(alt->check->accept(this)));
            stmgr->enterScope(StopType::NONE); // FIXME: THIS SORT OF THING HAS ISSUES WITH ALLOWING FOR REDCLS OF VARS IN VARIOIUS SCOPES!!! (THIS EFFECTIVLEY FLATTENS THINGS)

            proto->append(channel->getProtocolCopy());
            stmgr->addSymbol(new Symbol(id, new TypeChannel(proto), false, false));

            for (const Symbol *orig : syms)
            {
                // FIXME: DO BETTER!!!!! WONT WORK FOR NON-CHANNELS! AND ALSO WONT WORK FOR VALUES!!!
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
std::optional<ProgramSendNode*> SemanticVisitor::TvisitProgramProject(WPLParser::ProgramProjectContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Could not find channel: " + id);
        return {}; 
    }

    Symbol *sym = opt.value().second;

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        const ProtocolSequence *ps = toSequence(any2Protocol(ctx->sel->accept(this)));
        unsigned int projectIndex = channel->getProtocol()->project(ps); 

        if (!projectIndex)
        {
            errorHandler.addSemanticError(ctx->getStart(), "Failed to project over channel: " + sym->toString() + " vs " + ps->toString());
            return {};
        }

        return new ProgramSendNode(sym, new IConstExprNode(projectIndex), Types::UNDEFINED); //FIXME: DO BETTER TYPE!
        // return ty.value();
        // return Types::UNDEFINED;
    }

    errorHandler.addSemanticError(ctx->getStart(), "Cannot project on non-channel: " + id);
    return {};
}
std::optional<ProgramContractNode *> SemanticVisitor::TvisitProgramContract(WPLParser::ProgramContractContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Could not find channel: " + id);
        return {};
    }

    Symbol *sym = opt.value().second;
    // bindings->bind(ctx->VARIABLE(), sym);

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        if (!channel->getProtocol()->contract())
        {
            errorHandler.addSemanticError(ctx->getStart(), "Failed to contract: " + id);
            return {};
        }
        return new ProgramContractNode(sym);
    }

    errorHandler.addSemanticError(ctx->getStart(), "Cannot contract on non-channel: " + id);
    return {};
}
std::optional<ProgramWeakenNode *> SemanticVisitor::TvisitProgramWeaken(WPLParser::ProgramWeakenContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Could not find channel: " + id);
        return {};
    }

    Symbol *sym = opt.value().second;
    bindings->bind(ctx->VARIABLE(), sym);

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        if (!channel->getProtocol()->weaken())
        {
            errorHandler.addSemanticError(ctx->getStart(), "Failed to weaken: " + id + " against " + channel->toString());
            return {};
        }
        return new ProgramWeakenNode(sym);
    }

    errorHandler.addSemanticError(ctx->getStart(), "Cannot weaken on non-channel: " + id);
    return {};
}
std::optional<ProgramAcceptNode *> SemanticVisitor::TvisitProgramAccept(WPLParser::ProgramAcceptContext *ctx)
{
    std::string id = ctx->VARIABLE()->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);
    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Unbound identifier: " + id);
        return {};
    }

    Symbol *sym = opt.value().second;
    // bindings->bind(ctx->VARIABLE(), sym);

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        std::optional<const ProtocolSequence *> acceptOpt = channel->getProtocol()->acceptLoop();
        if (!acceptOpt)
        {
            errorHandler.addSemanticError(ctx->getStart(), "Cannot accept on " + channel->toString());
            return {};
        }

        std::vector<Symbol *> syms = stmgr->getAvaliableLinears();
        // FIXME: DO BETTER B/C HERE WE TRY TO ASSIGN TO THE VAR WE MANUALLY NEED TO ASSIGN? NO BC IT FAILS CHECK!

        stmgr->enterScope(StopType::LINEAR); // TODO: DO BETTER

        std::vector<std::pair<const TypeChannel *, const ProtocolSequence *>> to_fix;

        for (Symbol *orig : syms)
        {
            if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(orig->type))
            {
                std::optional<const ProtocolSequence *> protoOpt = channel->getProtocol()->shearLoop();
                if (protoOpt)
                {
                    // Symbol * tempSym = new Symbol(orig->getIdentifier(), new TypeChannel(protoOpt.value()), false, false);
                    // tempSym->val = orig->val;
                    // stmgr->addSymbol(tempSym);

                    to_fix.push_back({channel, channel->getProtocol()});
                    channel->setProtocol(protoOpt.value());
                    stmgr->addSymbol(orig);
                }
            }
        }
        to_fix.push_back({channel, channel->getProtocol()});
        channel->setProtocol(acceptOpt.value());
        stmgr->addSymbol(sym);
        // stmgr->addSymbol(new Symbol(id, new TypeChannel(acceptOpt.value()), false, false));

        std::optional<BlockNode *> blkOpt = this->visitCtx(ctx->block());

        safeExitScope(ctx);

        for (auto pair : to_fix)
        {
            pair.first->setProtocol(pair.second);
        }

        if (!blkOpt)
            return {}; // FIXME: DO BETTER

        return new ProgramAcceptNode(sym, blkOpt.value());
        // return Types::UNDEFINED;
        // return new TypeChannel(toSequence(inv->getChannelType()->getProtocol()->getInverse()));
    }

    errorHandler.addSemanticError(ctx->getStart(), "Cannot accept: " + sym->toString());
    return {};
}
std::optional<ProgramExecNode *> SemanticVisitor::TvisitAssignableExec(WPLParser::AssignableExecContext *ctx)
{
    std::string id = ctx->VARIABLE()->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);
    if (!opt)
    {
        errorHandler.addSemanticError(ctx->getStart(), "Unbound identifier: " + id);
        return {};
    }

    Symbol *sym = opt.value().second;
    // bindings->bind(ctx->VARIABLE(), sym);

    if (const TypeProgram *inv = dynamic_cast<const TypeProgram *>(sym->type))
    {
        return new ProgramExecNode(
            sym,
            new TypeChannel(toSequence(inv->getChannelType()->getProtocol()->getInverse())));
    }

    // FIXME: DO BETTER
    errorHandler.addSemanticError(ctx->getStart(), "Cannot exec: " + sym->toString());
    // return Types::UNDEFINED;
    return {};
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