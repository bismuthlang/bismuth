#include "SemanticVisitor.h"

std::variant<CompilationUnitNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::CompilationUnitContext *ctx)
{
    // Enter initial scope
    stmgr->enterScope(StopType::NONE);

    std::vector<ExternNode *> externs;

    std::vector<std::pair<WPLParser::DefineProcContext *, TypeProgram *>> progs;
    std::vector<std::pair<WPLParser::DefineFuncContext *, TypeInvoke *>> funcs;
    std::vector<std::pair<WPLParser::DefineStructContext *, TypeStruct *>> structs;
    std::vector<std::pair<WPLParser::DefineEnumContext *, TypeSum *>> enums;

    std::vector<DefinitionNode> defs;

    for (auto e : ctx->defs)
    {
        if (WPLParser::DefineProgramContext *progCtx = dynamic_cast<WPLParser::DefineProgramContext *>(e))
        {
            std::string id = progCtx->defineProc()->name->getText();

            std::optional<SymbolContext> opt = stmgr->lookup(id);

            if (opt)
            {
                return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of program " + id);
            }

            TypeProgram *progType = new TypeProgram();
            Symbol *progSym = new Symbol(id, progType, true, true);
            symBindings->bind(progCtx->defineProc(), progSym);
            stmgr->addSymbol(progSym);

            progs.push_back({progCtx->defineProc(), progType});
        }
        else if (WPLParser::DefineFunctionContext *fnCtx = dynamic_cast<WPLParser::DefineFunctionContext *>(e))
        {
            std::string id = fnCtx->defineFunc()->name->getText();

            std::optional<SymbolContext> opt = stmgr->lookup(id);

            if (opt)
            {
                return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of function " + id);
            }

            TypeInvoke *funcType = new TypeInvoke();
            Symbol *sym = new Symbol(id, funcType, true, true);
            symBindings->bind(fnCtx->defineFunc(), sym);
            stmgr->addSymbol(sym);

            funcs.push_back({fnCtx->defineFunc(), funcType});
        }
        else if (WPLParser::DefineStructContext *prodCtx = dynamic_cast<WPLParser::DefineStructContext *>(e))
        {
            std::string id = prodCtx->name->getText();

            std::optional<SymbolContext> opt = stmgr->lookup(id);

            if (opt)
            {
                return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of struct " + id);
            }

            TypeStruct *structType = new TypeStruct(id);
            Symbol *sym = new Symbol(id, structType, true, true);
            symBindings->bind(prodCtx, sym);
            stmgr->addSymbol(sym);

            structs.push_back({prodCtx, structType});
        }
        else if (WPLParser::DefineEnumContext *sumCtx = dynamic_cast<WPLParser::DefineEnumContext *>(e))
        {
            std::string id = sumCtx->name->getText();

            std::optional<SymbolContext> opt = stmgr->lookup(id);

            if (opt)
            {
                return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of enum " + id);
            }

            TypeSum *ty = new TypeSum(id);
            Symbol *sym = new Symbol(id, ty, true, true);
            symBindings->bind(sumCtx, sym);
            stmgr->addSymbol(sym);

            enums.push_back({sumCtx, ty});
        }
        else
        {
            std::variant<TypedNode *, ErrorChain *> opt = anyOpt2VarError<TypedNode>(errorHandler, e->accept(this));
            if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
            {
                (*e)->addError(ctx->getStart(), "Failed to typecheck definition.");
                return *e;
            }

            errorHandler.addError(ctx->getStart(), "Unhandled case");
        }
    }

    // Visit externs first; they will report any errors if they have any.
    for (auto e : ctx->externs)
    {
        std::variant<ExternNode *, ErrorChain *> extOpt = this->visitCtx(e);

        if (ErrorChain **e = std::get_if<ErrorChain *>(&extOpt))
        {
            (*e)->addError(ctx->getStart(), "108");
            return *e;
        }

        externs.push_back(std::get<ExternNode *>(extOpt));
    }

    // Auto forward decl

    // FIXME: ERROR CHECK!
    for (auto e : progs)
    {
        getProgramSymbol(e.first);
    }
    for (auto e : funcs)
    {
        getFunctionSymbol(e.first);
    }
    for (auto e : structs)
    {
        std::variant<TypedNode *, ErrorChain *> opt = anyOpt2VarError<TypedNode>(errorHandler, e.first->accept(this));
    }
    for (auto e : enums)
    {
        std::variant<TypedNode *, ErrorChain *> opt = anyOpt2VarError<TypedNode>(errorHandler, e.first->accept(this));
    }

    // Visit the statements contained in the unit
    for (auto e : ctx->defs)
    {
        // e->accept(this);
        if (WPLParser::DefineProgramContext *fnCtx = dynamic_cast<WPLParser::DefineProgramContext *>(e))
        {
            std::variant<ProgramDefNode *, ErrorChain *> progOpt = visitInvokeable(fnCtx->defineProc()); // e->accept(this);

            if (ErrorChain **e = std::get_if<ErrorChain *>(&progOpt))
            {
                (*e)->addError(ctx->getStart(), "Failed to typecheck program.");
                return *e;
            }

            defs.push_back(std::get<ProgramDefNode *>(progOpt));
        }
        else if (WPLParser::DefineFunctionContext *fnCtx = dynamic_cast<WPLParser::DefineFunctionContext *>(e))
        {
            std::variant<LambdaConstNode *, ErrorChain *> opt = visitCtx(fnCtx->defineFunc());

            if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
            {
                (*e)->addError(ctx->getStart(), "Failed to typecheck function.");
                return *e;
            }

            defs.push_back(std::get<LambdaConstNode *>(opt));
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
            errorHandler.addError(ctx->getStart(), "When compiling with no-runtime, main is reserved!");
        }

        // Check that program is invokeable and correctly defined.
        {
            std::optional<SymbolContext> opt = stmgr->lookup("program");
            if (!opt)
            {
                errorHandler.addError(ctx->getStart(), "When compiling with no-runtime, program() must be defined!");
            }
            else
            {
                Symbol *sym = opt.value().second;

                if (const TypeInvoke *inv = dynamic_cast<const TypeInvoke *>(sym->type))
                {
                    if (inv->getParamTypes().size() != 0)
                    {
                        errorHandler.addError(ctx->getStart(), "When compiling with no-runtime, program must not require arguments!");
                    }

                    {
                        std::optional<const Type *> retOpt = inv->getReturnType();

                        if (!retOpt || !dynamic_cast<const TypeInt *>(retOpt.value()))
                        {
                            errorHandler.addError(ctx->getStart(), "When compiling with no-runtime, program() must return INT");
                        }
                    }
                }
                else
                {
                    errorHandler.addError(ctx->getStart(), "When compiling with no-runtime, program() must be an invokable!");
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

        errorHandler.addError(ctx->getStart(), "Uninferred types in context: " + details.str());
    }
    // Return UNDEFINED as this should be viewed as a statement and not something assignable
    return new CompilationUnitNode(externs, defs);
}

std::variant<InvocationNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::InvocationContext *ctx)
{
    std::variant<TypedNode *, ErrorChain *> typeOpt = (ctx->lam) ? TNVariantCast<LambdaConstNode>(visitCtx(ctx->lam)) : TNVariantCast<FieldAccessNode>(visitCtx(ctx->field, true));
    if (ErrorChain **e = std::get_if<ErrorChain *>(&typeOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to generate expression to invoke.");
        return *e;
    }

    TypedNode *tn = std::get<TypedNode *>(typeOpt);

    // const Type *type = tn->getType();
    for (auto iArgs : ctx->inv_args())
    {

        std::string name = (ctx->lam) ? "lambda " : ctx->field->getText();

        if (const TypeInvoke *invokeable = dynamic_cast<const TypeInvoke *>(tn->getType()))
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
                (!invokeable->isVariadic() && fnParams.size() != iArgs->args.size()) || (invokeable->isVariadic() && fnParams.size() > iArgs->args.size()))
            {
                std::ostringstream errorMsg;
                errorMsg << "Invocation of " << name << " expected " << fnParams.size() << " argument(s), but got " << iArgs->args.size();
                return errorHandler.addError(ctx->getStart(), errorMsg.str());
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
            for (unsigned int i = 0; i < iArgs->args.size(); i++)
            {
                // Get the type of the current argument
                // const Type *providedType = any2Type(iArgs->args.at(i)->accept(this));
                std::variant<TypedNode *, ErrorChain *> providedOpt = anyOpt2VarError<TypedNode>(errorHandler, iArgs->args.at(i)->accept(this));

                if (ErrorChain **e = std::get_if<ErrorChain *>(&providedOpt))
                {
                    (*e)->addError(iArgs->args.at(i)->getStart(), "Unable to generate argument.");
                    return *e;
                }

                TypedNode *provided = std::get<TypedNode *>(providedOpt);

                args.push_back(provided);

                const Type *providedType = provided->getType();

                // If the invokable is variadic and has no specified type parameters, then we can
                // skip over subsequent checks--we just needed to run type checking on each parameter.
                if (invokeable->isVariadic() && i >= fnParams.size()) //&& fnParams.size() == 0)
                {
                    if (dynamic_cast<const TypeBottom *>(providedType) || dynamic_cast<const TypeAbsurd *>(providedType) || dynamic_cast<const TypeUnit *>(providedType))
                    {
                        errorHandler.addError(ctx->getStart(), "Cannot provide " + providedType->toString() + " to a function.");
                    }
                    continue;
                }

                // Loop up the expected type. This is either the type at the
                // ith index OR the last type specified by the function
                // if i > fnParams.size() as that would imply we are
                // checking a variadic
                const Type *expectedType = fnParams.at(
                    i < fnParams.size() ? i : (fnParams.size() - 1)); // FIXME: ternary NEVER FULLY evaluated DUE TO CONTINUE!

                actualTypes.push_back(expectedType);

                // If the types do not match, report an error.
                if (providedType->isNotSubtype(expectedType))
                {
                    std::ostringstream errorMsg;
                    errorMsg << "Argument " << i << " provided to " << name << " expected " << expectedType->toString() << " but got " << providedType->toString();

                    errorHandler.addError(ctx->getStart(), errorMsg.str());
                }
            }

            tn = new InvocationNode(tn, args, actualTypes, ctx->getStart());
            // return new InvocationNode(tn, args, actualTypes, ctx->getStart());
        }
        else
        {
            // Symbol was not an invokeable type, so report an error & return UNDEFINED.
            return errorHandler.addError(ctx->getStart(), "Can only invoke PROC and FUNC, not " + name + " : " + tn->getType()->toString());
        }
    }
    // return new InvocationNode(tn, args, actualTypes, ctx->getStart());
    return (InvocationNode *)tn;
}

std::variant<LambdaConstNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::DefineFuncContext *ctx)
{
    std::variant<Symbol *, ErrorChain *> funcSymOpt = getFunctionSymbol(ctx);

    if (ErrorChain **e = std::get_if<ErrorChain *>(&funcSymOpt))
    {
        return *e;
    }

    Symbol *funcSym = std::get<Symbol *>(funcSymOpt);
    stmgr->addSymbol(funcSym);

    std::variant<LambdaConstNode *, ErrorChain *> lamOpt = visitCtx(ctx->lam);

    if (ErrorChain **e = std::get_if<ErrorChain *>(&lamOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to generate lambda.");
        return *e;
    }

    LambdaConstNode *lam = std::get<LambdaConstNode *>(lamOpt);

    lam->type = const_cast<TypeInvoke *>(dynamic_cast<const TypeInvoke *>(funcSym->type)); // FIXME: DO BETTER! NEEDED B/C OF NAME RES!

    lam->name = funcSym->getIdentifier(); // Not really needed.
    return lam;
}

std::variant<InitProductNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::InitProductContext *ctx)
{
    std::string name = ctx->v->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(name);

    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Cannot initialize undefined product: " + name);
    }

    Symbol *sym = opt.value().second;

    // TODO: METHODIZE WITH INVOKE?

    if (const TypeStruct *product = dynamic_cast<const TypeStruct *>(sym->type))
    {
        std::vector<std::pair<std::string, const Type *>> elements = product->getElements();
        if (elements.size() != ctx->exprs.size())
        {
            std::ostringstream errorMsg;
            errorMsg << "Initialization of " << name << " expected " << elements.size() << " argument(s), but got " << ctx->exprs.size();
            return errorHandler.addError(ctx->getStart(), errorMsg.str());
        }

        std::vector<TypedNode *> n;

        bool isValid = true;
        {
            unsigned int i = 0;

            for (auto eleItr : elements)
            {
                std::variant<TypedNode *, ErrorChain *> opt = anyOpt2VarError<TypedNode>(errorHandler, ctx->exprs.at(i)->accept(this));

                if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
                {
                    (*e)->addError(ctx->exprs.at(i)->getStart(), "Unable to generate expression.");
                    return *e;
                }

                TypedNode *tn = std::get<TypedNode *>(opt);

                n.push_back(tn);
                const Type *providedType = tn->getType();

                if (providedType->isNotSubtype(eleItr.second))
                {
                    std::ostringstream errorMsg;
                    errorMsg << "Product init. argument " << i << " provided to " << name << " expected " << eleItr.second->toString() << " but got " << providedType->toString();

                    errorHandler.addError(ctx->getStart(), errorMsg.str());
                    isValid = false;
                }

                i++;
            }
        }

        if (!isValid)
        {
            return errorHandler.addError(ctx->getStart(), "Invalid parameters passed to product init.");
        }

        return new InitProductNode(product, n, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot initialize non-product type " + name + " : " + sym->type->toString());
}

std::variant<InitBoxNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::InitBoxContext *ctx)
{
    const Type *storeType = any2Type(ctx->ty->accept(this));

    if (isLinear(storeType))
    {
        return errorHandler.addError(ctx->ty->getStart(), "Cannot create a box with a linear type!");
    }

    // TODO: METHODIZE WITH INVOKE AND INIT PRODUCT?
    std::variant<TypedNode *, ErrorChain *> opt = anyOpt2VarError<TypedNode>(errorHandler, ctx->expr->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
    {
        (*e)->addError(ctx->expr->getStart(), "Unable to generate expression in init box.");
        return *e;
    }

    TypedNode *tn = std::get<TypedNode *>(opt);

    const Type *providedType = tn->getType();

    if (isLinear(providedType))
    {
        return errorHandler.addError(ctx->expr->getStart(), "Cannot create a box with a linear type!");
    }

    if (providedType->isNotSubtype(storeType))
    {
        std::ostringstream errorMsg;
        errorMsg << "Initialize box expected " << storeType->toString() << ", but got " << providedType->toString() << ".";

        return errorHandler.addError(ctx->getStart(), errorMsg.str());
    }

    return new InitBoxNode(new TypeBox(storeType), tn, ctx->getStart());
}

std::variant<ArrayAccessNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::ArrayAccessContext *ctx, bool is_rvalue)
{
    /*
     * Check that we are provided an INT for the index.
     */
    std::variant<TypedNode *, ErrorChain *> exprOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->index->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&exprOpt))
    {
        (*e)->addError(ctx->index->getStart(), "Unable to typecheck array access index.");
        return *e;
    }

    TypedNode *expr = std::get<TypedNode *>(exprOpt);

    const Type *exprType = expr->getType();
    if (exprType->isNotSubtype(Types::INT))
    {
        return errorHandler.addError(ctx->getStart(), "Array access index expected type INT but got " + exprType->toString());
    }

    /*
     * Look up the symbol and check that it is defined.
     */

    std::variant<FieldAccessNode *, ErrorChain *> opt = visitCtx(ctx->field, false); // Always have to load the array field
    if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
    {
        (*e)->addError(ctx->field->getStart(), "Cannot access value from undefined array: " + ctx->field->getText());
        return *e;
    }

    /*
     * Check that the symbol is of array type.
     */

    // Symbol *sym = opt.value();
    FieldAccessNode *field = std::get<FieldAccessNode *>(opt);

    if (const TypeArray *arr = dynamic_cast<const TypeArray *>(field->getType()))
    {
        return new ArrayAccessNode(field, expr, is_rvalue, ctx->getStart());
    }

    // Report error
    return errorHandler.addError(ctx->getStart(), "Cannot use array access on non-array expression " + ctx->field->getText() + " : " + field->getType()->toString());
}

std::variant<TypedNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::LValueContext *ctx)
{
    // Check if we are a var or an array
    if (ctx->var)
    {
        return TNVariantCast<FieldAccessNode>(visitCtx(ctx->var, false));
    }
    else if (ctx->deref)
    {
        return TNVariantCast<DerefBoxNode>(visitCtx(ctx->deref, false));
    }

    /*
     * As we are not a var, we must be an array access, so we must visit that context.
     */
    return TNVariantCast<ArrayAccessNode>(this->visitCtx(ctx->array, false));
}

std::variant<IConstExprNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::IConstExprContext *ctx)
{
    return new IConstExprNode(std::stoi(ctx->i->getText()), ctx->getStart());
}

std::variant<StringConstNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::SConstExprContext *ctx)
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

    return new StringConstNode(out, ctx->getStart());
}

/**
 * @brief Typechecks Unary Expressions
 *
 * @param ctx The UnaryExpressionContext to type check
 * @return const Type* Returns the type of the inner expression if valid; UNDEFINED otherwise.
 */
std::variant<UnaryExprNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::UnaryExprContext *ctx)
{
    // Lookup the inner type
    std::variant<TypedNode *, ErrorChain *> innerNodeOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->ex->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&innerNodeOpt))
    {
        (*e)->addError(ctx->ex->getStart(), "Failed to generate unary expression.");
        return *e;
    }

    TypedNode *innerNode = std::get<TypedNode *>(innerNodeOpt);

    const Type *innerType = innerNode->getType();

    // Switch on the operation so we can ensure that the type and operation are compatable.
    switch (ctx->op->getType())
    {
    case WPLParser::MINUS:
        if (innerType->isNotSubtype(Types::INT))
        {
            return errorHandler.addError(ctx->getStart(), "INT expected in unary minus, but got " + innerType->toString());
        }
        return new UnaryExprNode(UNARY_MINUS, innerNode, ctx->getStart());
    case WPLParser::NOT:
        if (innerType->isNotSubtype(Types::BOOL))
        {
            return errorHandler.addError(ctx->getStart(), "BOOL expected in unary not, but got " + innerType->toString());
        }
        return new UnaryExprNode(UNARY_NOT, innerNode, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "605");
}

/**
 * @brief Visits a Binary Arithmetic Expression ensuring LHS and RHS are INT.
 *
 * @param ctx The BinaryArithExprContext to Visit
 * @return const Type* INT if lhs and rhs are INT; UNDEFINED otherwise.
 */
std::variant<BinaryArithNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::BinaryArithExprContext *ctx)
{
    auto leftOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->left->accept(this));
    if (ErrorChain **e = std::get_if<ErrorChain *>(&leftOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to generate LHS of Binary Arithmetic Expression.");
        return *e;
    }

    auto left = std::get<TypedNode *>(leftOpt);

    if (left->getType()->isNotSubtype(Types::INT))
    {
        return errorHandler.addError(ctx->getStart(), "INT left expression expected, but was " + left->getType()->toString());
    }

    auto rightOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->right->accept(this));
    if (ErrorChain **e = std::get_if<ErrorChain *>(&rightOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to generate RHS of binary arithmetic expression.");
        return *e;
    }

    auto right = std::get<TypedNode *>(rightOpt);

    if (right->getType()->isNotSubtype(Types::INT))
    {
        return errorHandler.addError(ctx->getStart(), "INT right expression expected, but was " + right->getType()->toString());
    }

    return new BinaryArithNode(
        ctx->MULTIPLY() ? BINARY_ARITH_MULT : ctx->DIVIDE() ? BINARY_ARITH_DIV
                                          : ctx->PLUS()     ? BINARY_ARITH_PLUS
                                                            : BINARY_ARITH_MINUS,
        left,
        right,
        ctx->getStart());
}

std::variant<EqExprNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::EqExprContext *ctx)
{
    std::variant<TypedNode *, ErrorChain *> rhsOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->right->accept(this));
    std::variant<TypedNode *, ErrorChain *> lhsOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->left->accept(this));

    // FIXME: DO BETTER AND ALLOW BRANCHING ERROR MSGS?

    if (ErrorChain **e = std::get_if<ErrorChain *>(&rhsOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to generate RHS.");
        return *e;
    }

    if (ErrorChain **e = std::get_if<ErrorChain *>(&lhsOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to generate LHS.");
        return *e;
    }

    TypedNode *lhs = std::get<TypedNode *>(lhsOpt);
    TypedNode *rhs = std::get<TypedNode *>(rhsOpt);

    if (rhs->getType()->isNotSubtype(lhs->getType()))
    {
        errorHandler.addError(ctx->getStart(), "Both sides of '=' must have the same type");
    }

    // Note: As per C spec, arrays cannot be compared
    if (dynamic_cast<const TypeArray *>(lhs->getType()) || dynamic_cast<const TypeArray *>(rhs->getType()))
    {
        errorHandler.addError(ctx->getStart(), "Cannot perform equality operation on arrays; they are always seen as unequal!");
    }

    return new EqExprNode(
        ctx->EQUAL() ? EQUAL_OP : NOT_EQUAL_OP,
        lhs, rhs, ctx->getStart());
}

/**
 * @brief Visits a Logical And Expression ensuring LHS and RHS are BOOL.
 *
 * @param ctx The LogAndExprContext to Visit
 * @return const Type* BOOL if lhs and rhs are BOOL; UNDEFINED otherwise.
 */
std::variant<LogAndExprNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::LogAndExprContext *ctx)
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
        std::variant<TypedNode *, ErrorChain *> nodeOpt = anyOpt2VarError<TypedNode>(errorHandler, e->accept(this));

        if (ErrorChain **er = std::get_if<ErrorChain *>(&nodeOpt))
        {
            (*er)->addError(e->getStart(), "Unable to generate expression in logical and");
            return *er;
        }

        TypedNode *node = std::get<TypedNode *>(nodeOpt);
        const Type *type = node->getType();

        if (type->isNotSubtype(Types::BOOL))
        {
            errorHandler.addError(e->getStart(), "BOOL expression expected, but was " + type->toString());
        }
        else
        {
            nodes.push_back(node);
        }
    }
    return new LogAndExprNode(nodes, ctx->getStart());
}

/**
 * @brief Visits a Logical Or Expression ensuring LHS and RHS are BOOL.
 *
 * @param ctx The LogOrExprContext to Visit
 * @return const Type* BOOL if lhs and rhs are BOOL; UNDEFINED otherwise.
 */
std::variant<LogOrExprNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::LogOrExprContext *ctx)
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
        std::variant<TypedNode *, ErrorChain *> nodeOpt = anyOpt2VarError<TypedNode>(errorHandler, e->accept(this));

        if (ErrorChain **e = std::get_if<ErrorChain *>(&nodeOpt))
        {
            (*e)->addError(ctx->getStart(), "794");
            return *e;
        }

        TypedNode *node = std::get<TypedNode *>(nodeOpt);
        const Type *type = node->getType();

        if (type->isNotSubtype(Types::BOOL))
        {
            errorHandler.addError(e->getStart(), "BOOL expression expected, but was " + type->toString());
        }
        else
        {
            nodes.push_back(node);
        }
    }
    return new LogOrExprNode(nodes, ctx->getStart());
}

/**
 * @brief Visits a FieldAccessExprContext---Currently limited to array lengths
 *
 * @param ctx the FieldAccessExprContext to visit
 * @return const Type* INT if correctly used to test array length; UNDEFINED if any errors.
 */
std::variant<FieldAccessNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::FieldAccessExprContext *ctx, bool is_rvalue)
{
    // Determine the type of the expression we are visiting
    std::optional<SymbolContext> opt = stmgr->lookup(ctx->VARIABLE().at(0)->getText());
    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Undefined variable reference: " + ctx->VARIABLE().at(0)->getText());
    }
    Symbol *sym = opt.value().second;

    if (opt.value().first == LINEAR_SCOPE) // FIXME: WILL NEED TO IMPL THIS BETTER!
    {
        if (!is_rvalue)
        {
            errorHandler.addError(ctx->getStart(), "Cannot redefine linear variable!");
        }

        if (!stmgr->removeSymbol(sym))
        {
            errorHandler.addError(ctx->getStart(), "Failed to unbind local var: " + sym->toString());
        }
    }

    std::vector<std::pair<std::string, const Type *>> a;

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
            }
            else
            {
                return errorHandler.addError(ctx->getStart(), "Cannot access " + fieldName + " on " + ty->toString());
            }
        }
        else if (i + 1 == ctx->fields.size() && dynamic_cast<const TypeArray *>(ty) && ctx->fields.at(i)->getText() == "length")
        {
            a.push_back({"length",
                         Types::INT});

            break; // Shouldn't be needed, but is here anyways
        }
        else
        {
            return errorHandler.addError(ctx->getStart(), "Cannot access " + fieldName + " on " + ty->toString());
        }
    }
    return new FieldAccessNode(ctx->getStart(), sym, is_rvalue, a);
}

std::variant<DerefBoxNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::DereferenceExprContext *ctx, bool is_rvalue)
{
    std::variant<TypedNode *, ErrorChain *> exprOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->expr->accept(this));

    // Determine the type of the expression we are visiting
    if (ErrorChain **e = std::get_if<ErrorChain *>(&exprOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to typecheck dereference expression.");
        return *e;
    }

    TypedNode *expr = std::get<TypedNode *>(exprOpt);

    const Type *exprType = expr->getType();
    if (const TypeBox *box = dynamic_cast<const TypeBox *>(exprType))
    {
        return new DerefBoxNode(box, expr, is_rvalue, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Dereference expected Box<T> but got " + exprType->toString());
}

// Passthrough to expression
std::variant<TypedNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::ParenExprContext *ctx)
{
    std::variant<TypedNode *, ErrorChain *> opt = anyOpt2VarError<TypedNode>(errorHandler, ctx->ex->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
    {
        (*e)->addError(ctx->getStart(), "892");
        return *e;
    }

    return std::get<TypedNode *>(opt);
}

/**
 * @brief Visits a BinaryRelational Expression ensuring both lhs and rhs are INT.
 *
 * @param ctx The BinaryRelExprContext to visit.
 * @return const Type* BOOL if lhs and rhs INT; UNDEFINED otherwise.
 */
std::variant<BinaryRelNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::BinaryRelExprContext *ctx)
{
    auto leftOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->left->accept(this));
    if (ErrorChain **e = std::get_if<ErrorChain *>(&leftOpt))
    {
        (*e)->addError(ctx->getStart(), "616");
        return *e;
    }

    auto left = std::get<TypedNode *>(leftOpt);

    if (left->getType()->isNotSubtype(Types::INT))
    {
        return errorHandler.addError(ctx->getStart(), "INT left expression expected, but was " + left->getType()->toString());
    }

    auto rightOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->right->accept(this));
    if (ErrorChain **e = std::get_if<ErrorChain *>(&rightOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to typecheck RHS of binary relation expression.");
        return *e;
    }

    auto right = std::get<TypedNode *>(rightOpt);

    if (right->getType()->isNotSubtype(Types::INT))
    {
        return errorHandler.addError(ctx->getStart(), "INT right expression expected, but was " + right->getType()->toString());
    }

    return new BinaryRelNode(
        ctx->LESS() ? BINARY_Rel_LESS : ctx->LESS_EQ() ? BINARY_Rel_LESS_EQ
                                    : ctx->GREATER()   ? BINARY_Rel_GREATER
                                                       : BINARY_Rel_GREATER_EQ,
        left,
        right,
        ctx->getStart());
}

/**
 * @brief Visits a condition's expression ensuring that it is of type BOOL.
 *
 * @param ctx The ConditionContext to visit
 * @return const Type* Always returns UNDEFINED as to prevent assignments
 */
std::variant<TypedNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::ConditionContext *ctx)
{
    // auto conditionType = any2Type(ctx->ex->accept(this));
    std::variant<TypedNode *, ErrorChain *> condOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->ex->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&condOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to typecheck condition expression.");
        return *e;
    }

    TypedNode *cond = std::get<TypedNode *>(condOpt);
    const Type *conditionType = cond->getType();

    if (conditionType->isNotSubtype(Types::BOOL))
    {
        return errorHandler.addError(ctx->getStart(), "Condition expected BOOL, but was given " + conditionType->toString());
    }

    return cond;
}

std::variant<SelectAlternativeNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::SelectAlternativeContext *ctx)
{
    return errorHandler.addError(ctx->getStart(), "COMP ERROR");
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

    for (auto param : ctx->params)
    {
        std::string name = param->name->getText();

        auto prevUse = map.find(name);
        if (prevUse != map.end())
        {
            errorHandler.addError(param->getStart(), "Re-use of previously defined parameter " + name + ".");
        }
        else
        {
            map.insert({name, param});
        }

        ParameterNode pn = this->visitCtx(param);
        paramList.push_back(pn);
    }

    return paramList;
}

ParameterNode SemanticVisitor::visitCtx(WPLParser::ParameterContext *ctx)
{
    return ParameterNode(any2Type(ctx->ty->accept(this)), ctx->name->getText()); // FIXME: WHAT AB ERRORS?
}

const Type *SemanticVisitor::visitCtx(WPLParser::AssignmentContext *ctx)
{
    errorHandler.addError(ctx->getStart(), "Assignment should never be visited directly during type checking!");
    return Types::UNIT;
}

std::variant<ExternNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::ExternStatementContext *ctx)
{

    bool variadic = ctx->variadic || ctx->ELLIPSIS();

    std::string id = ctx->name->getText();

    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (opt)
    {
        return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of " + id);
    }

    std::optional<ParameterListNode> tyOpt = (ctx->paramList) ? this->visitCtx(ctx->paramList)
                                                              : ParameterListNode();

    if (!tyOpt)
    {
        return errorHandler.addError(ctx->getStart(), "Failed to genrate parameters for extern!");
    }

    const Type *retType = ctx->ty ? any2Type(ctx->ty->accept(this))
                                  : Types::UNIT;

    ExternNode *node = new ExternNode(id, tyOpt.value(), retType, variadic, ctx->getStart());

    stmgr->addSymbol(node->getSymbol());

    return node;
};

std::variant<AssignNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::AssignStatementContext *ctx)
{
    // This one is the update one!

    // Determine the expression type
    std::variant<TypedNode *, ErrorChain *> exprOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->a->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&exprOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to typecheck assignment.");
        return *e;
    }

    TypedNode *expr = std::get<TypedNode *>(exprOpt);
    const Type *exprType = expr->getType();

    if (isGuarded(exprType))
    {
        return errorHandler.addError(ctx->getStart(), "Cannot assign guarded resource to another identifier!");
    }

    // Determine the expected type
    std::variant<TypedNode *, ErrorChain *> varOpt = this->visitCtx(ctx->to);

    if (ErrorChain **e = std::get_if<ErrorChain *>(&varOpt))
    {
        (*e)->addError(ctx->getStart(), "Cannot assign to undefined variable: " + ctx->to->getText());
        return *e;
    }

    TypedNode *var = std::get<TypedNode *>(varOpt);

    const Type *type = var->getType();

    // Make sure that the types are compatible. Inference automatically managed here.
    if (exprType->isNotSubtype(type))
    {
        return errorHandler.addError(ctx->getStart(), "Assignment statement expected " + type->toString() + " but got " + exprType->toString());
    }

    // Return UNDEFINED because this is a statement, and UNDEFINED cannot be assigned to anything
    return new AssignNode(var, expr, ctx->getStart());
}

std::variant<VarDeclNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::VarDeclStatementContext *ctx)
{
    std::vector<AssignmentNode *> a;

    for (auto e : ctx->assignments)
    {
        // Needs to happen in case we have vars
        const Type *assignType = this->visitCtx(ctx->typeOrVar());

        if (e->a && stmgr->isGlobalScope())
        {
            if (!(dynamic_cast<WPLParser::BConstExprContext *>(e->a) ||
                  dynamic_cast<WPLParser::IConstExprContext *>(e->a) ||
                  dynamic_cast<WPLParser::SConstExprContext *>(e->a)))
            {
                errorHandler.addError(e->a->getStart(), "Global variables must be assigned explicit constants or initialized at runtime!");
            }

            if (dynamic_cast<const TypeSum *>(assignType))
            {
                errorHandler.addError(e->a->getStart(), "Sums cannot be initialized at a global level");
            }
        }

        // std::vector<Symbol *> s;

        for (auto var : e->VARIABLE())
        {
            std::string id = var->getText();

            std::optional<Symbol *> symOpt = stmgr->lookupInCurrentScope(id);

            if (symOpt)
            {
                return errorHandler.addError(e->getStart(), "Redeclaration of " + id);
            }
            else
            {
                // if (!(e->a))
                //     return errorHandler.addCodegenError(ctx->getStart(), "FALSE!");
                std::optional<TypedNode *> exprOpt = std::nullopt;

                if (e->a)
                {
                    std::variant<TypedNode *, ErrorChain *> exprOptO = anyOpt2VarError<TypedNode>(errorHandler, e->a->accept(this));

                    if (ErrorChain **e = std::get_if<ErrorChain *>(&exprOptO))
                    {
                        (*e)->addError(ctx->getStart(), "Unable to typecheck assignment.");
                        return *e;
                    }

                    exprOpt = std::get<TypedNode *>(exprOptO);
                }
                // std::variant<TypedNode *, ErrorChain *> exprOpt = (e->a) ? anyOpt2VarError<TypedNode>(e->a->accept(this)) : std::nullopt;

                const Type *newAssignType = this->visitCtx(ctx->typeOrVar()); // Needed to ensure vars get their own inf type

                const Type *exprType = exprOpt ? exprOpt.value()->getType() : newAssignType;

                if (isGuarded(exprType)) // TODO: Use syntactic sugar to separate out declarations from assignments. Also could use it to make select statements work better!
                {
                    return errorHandler.addError(ctx->getStart(), "Cannot assign guarded resource to another identifier!");
                }

                // Note: This automatically performs checks to prevent issues with setting VAR = VAR
                if (e->a && exprType->isNotSubtype(newAssignType))
                {
                    return errorHandler.addError(e->getStart(), "Expression of type " + exprType->toString() + " cannot be assigned to " + newAssignType->toString());
                }

                const Type *newExprType = (dynamic_cast<const TypeInfer *>(newAssignType) && e->a) ? exprType : newAssignType;

                Symbol *symbol = new Symbol(id, newExprType, false, stmgr->isGlobalScope()); // Done with exprType for later inferencing purposes
                stmgr->addSymbol(symbol);

                a.push_back(new AssignmentNode({symbol}, exprOpt)); // FIXME: Inefficient but needed for linears
            }
        }
        // a.push_back(new AssignmentNode(s, exprOpt));
    }
    return new VarDeclNode(a, ctx->getStart());
}

std::variant<MatchStatementNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::MatchStatementContext *ctx)
{
    std::variant<TypedNode *, ErrorChain *> condOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->check->ex->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&condOpt))
    {
        (*e)->addError(ctx->getStart(), "1174");
        return *e;
    }

    TypedNode *cond = std::get<TypedNode *>(condOpt);

    if (const TypeSum *sumType = dynamic_cast<const TypeSum *>(cond->getType()))
    {
        std::vector<std::pair<Symbol *, TypedNode *>> cases;

        std::set<const Type *> foundCaseTypes = {};
        // TODO: Maybe make so these can return values?

        DeepRestData *restDat = new DeepRestData(ctx->rest);
        std::deque<DeepRestData *> *rest = restBindings->getBinding(ctx).value_or(new std::deque<DeepRestData *>());
        rest->push_front(restDat);

        for (auto b : ctx->cases)
        {
            bindRestData(b->eval, rest);
        }

        std::variant<ConditionalData, ErrorChain *> branchOpt = checkBranch<WPLParser::MatchAlternativeContext>(
            ctx,
            ctx->cases,
            restDat, // ctx->rest,
            false,
            [this, ctx, &cases, sumType, &foundCaseTypes](WPLParser::MatchAlternativeContext *altCtx) -> std::variant<TypedNode *, ErrorChain *>
            {
                const Type *caseType = any2Type(altCtx->type()->accept(this));

                if (!sumType->contains(caseType))
                {
                    errorHandler.addError(altCtx->type()->getStart(), "Impossible case for " + sumType->toString() + " to act as " + caseType->toString());
                }

                if (foundCaseTypes.count(caseType))
                {
                    errorHandler.addError(altCtx->type()->getStart(), "Duplicate case in match");
                }
                else
                {
                    foundCaseTypes.insert(caseType); // FIXME: DO BETTER TRACKING OF SATISFYING RQMTS. Right now, can pass check for having all cases due to having invalid ones!!
                }

                stmgr->enterScope(StopType::NONE);
                Symbol *local = new Symbol(altCtx->name->getText(), caseType, false, false);
                stmgr->addSymbol(local);

                std::variant<TypedNode *, ErrorChain *> tnOpt = anyOpt2VarError<TypedNode>(errorHandler, altCtx->eval->accept(this));
                // this->safeExitScope(altCtx);
                stmgr->exitScope();

                if (ErrorChain **e = std::get_if<ErrorChain *>(&tnOpt))
                {
                    (*e)->addError(ctx->getStart(), "1236");
                    return *e;
                }

                if (dynamic_cast<WPLParser::ProgDefContext *>(altCtx->eval) ||
                    dynamic_cast<WPLParser::VarDeclStatementContext *>(altCtx->eval) ||
                    dynamic_cast<WPLParser::FuncDefContext *>(altCtx->eval))
                {
                    return errorHandler.addError(altCtx->getStart(), "Dead code: definition as select alternative.");
                }

                TypedNode *ans = std::get<TypedNode *>(tnOpt);

                cases.push_back({local, ans});

                return ans;
            });

        // for (WPLParser::MatchAlternativeContext *altCtx : ctx->cases)
        // {
        // }

        if (foundCaseTypes.size() != sumType->getCases().size())
        {
            return errorHandler.addError(ctx->getStart(), "Match statement did not cover all cases needed for " + sumType->toString());
        }

        if (ErrorChain **e = std::get_if<ErrorChain *>(&branchOpt))
        {
            (*e)->addError(ctx->getStart(), "Failed to typecheck match statement.");
            return *e;
        }

        ConditionalData dat = std::get<ConditionalData>(branchOpt);

        return new MatchStatementNode(sumType, cond, cases, restDat->post, ctx->getStart());
    }

    return errorHandler.addError(ctx->check->getStart(), "Can only case on Sum Types, not " + cond->getType()->toString());
}

/**
 * @brief Type checks a Loops
 *
 * @param ctx The LoopStatementContext to type check
 * @return const Type* UNDEFINED as this is a statement.
 */
std::variant<WhileLoopNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::ProgramLoopContext *ctx)
{
    std::variant<TypedNode *, ErrorChain *> checkOpt = this->visitCtx(ctx->check); // Visiting check will make sure we have a boolean condition

    if (ErrorChain **e = std::get_if<ErrorChain *>(&checkOpt))
    {
        (*e)->addError(ctx->getStart(), "1309");
        return *e;
    }

    std::vector<Symbol *> syms = stmgr->getAvaliableLinears();

    std::vector<const TypeChannel *> to_fix;

    for (Symbol *orig : syms)
    {
        if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(orig->type))
        {
            channel->getProtocol()->guard();
            to_fix.push_back(channel);
        }
    }

    std::variant<BlockNode *, ErrorChain *> blkOpt = safeVisitBlock(ctx->block(), true);

    if (ErrorChain **e = std::get_if<ErrorChain *>(&blkOpt))
    {
        (*e)->addError(ctx->getStart(), "1330");
        return *e;
    }

    for (auto c : to_fix) // This shouldn't break anything...
    {
        c->getProtocol()->unguard();
    }

    // Return UNDEFINED because this is a statement, and UNDEFINED cannot be assigned to anything
    return new WhileLoopNode(std::get<TypedNode *>(checkOpt), std::get<BlockNode *>(blkOpt), ctx->getStart());
}

std::variant<ConditionalStatementNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::ConditionalStatementContext *ctx)
{
    // Automatically handles checking that we have a valid condition
    std::variant<TypedNode *, ErrorChain *> condOpt = this->visitCtx(ctx->check);

    if (ErrorChain **e = std::get_if<ErrorChain *>(&condOpt))
    {
        (*e)->addError(ctx->getStart(), "1350");
        return *e;
    }

    std::vector<WPLParser::BlockContext *> blksCtx = {ctx->trueBlk};
    if (ctx->falseBlk)
        blksCtx.push_back(ctx->falseBlk);

    DeepRestData *restDat = new DeepRestData(ctx->rest);
    std::deque<DeepRestData *> *rest = restBindings->getBinding(ctx).value_or(new std::deque<DeepRestData *>());
    rest->push_front(restDat); // Is deque so that way we keep things reversed

    for (auto b : blksCtx)
    {
        for (auto c : b->stmts)
        {
            bindRestData(c, rest);
        }
    }

    std::variant<ConditionalData, ErrorChain *> branchOpt = checkBranch<WPLParser::BlockContext>(
        ctx,
        blksCtx,
        restDat, // ctx->rest,
        blksCtx.size() == 1,
        [this](WPLParser::BlockContext *blk) -> std::variant<TypedNode *, ErrorChain *>
        {
            return TNVariantCast<BlockNode>(this->visitCtx(blk));
        });

    if (ErrorChain **e = std::get_if<ErrorChain *>(&branchOpt))
        return errorHandler.addError(ctx->getStart(), "Failed to generate one or more cases in if statement.");

    ConditionalData dat = std::get<ConditionalData>(branchOpt);

    if (ctx->falseBlk)
    {
        return new ConditionalStatementNode(ctx->getStart(), std::get<TypedNode *>(condOpt), (BlockNode *)dat.cases.at(0), restDat->post, (BlockNode *)dat.cases.at(1));
    }

    return new ConditionalStatementNode(ctx->getStart(), std::get<TypedNode *>(condOpt), (BlockNode *)dat.cases.at(0), restDat->post);
}

std::variant<SelectStatementNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::SelectStatementContext *ctx)
{
    // Define a recursive fn which takes ctx->cases as arg, then processes first vs rest?
    if (ctx->cases.size() < 1)
    {
        return errorHandler.addError(ctx->getStart(), "Select statement expected at least one alternative, but was given 0!");
    }

    DeepRestData *restDat = new DeepRestData(ctx->rest);
    std::deque<DeepRestData *> *rest = restBindings->getBinding(ctx).value_or(new std::deque<DeepRestData *>());
    rest->push_front(restDat); // Is deque so that way we keep things reversed

    for (auto b : ctx->cases)
    {
        bindRestData(b->eval, rest);
    }

    unsigned int case_count = 0;

    std::vector<SelectAlternativeNode *> alts;

    std::variant<ConditionalData, ErrorChain *> branchOpt = checkBranch<WPLParser::SelectAlternativeContext>(
        ctx,
        ctx->cases,
        restDat, // ctx->rest,
        true,
        [this, ctx, &case_count, &alts](WPLParser::SelectAlternativeContext *e) -> std::variant<TypedNode *, ErrorChain *>
        {
            /*
             *  Just make sure that we don't try to define functions and stuff in a select as that doesn't make sense (and would cause codegen issues as it stands).
             */
            if (dynamic_cast<WPLParser::ProgDefContext *>(e->eval) || // FIXME: DO BETTER, THERE MAY BE A LOT LIKE THIS!
                dynamic_cast<WPLParser::VarDeclStatementContext *>(e->eval) ||
                dynamic_cast<WPLParser::FuncDefContext *>(e->eval))
            {
                return errorHandler.addError(e->getStart(), "Dead code: definition as select alternative.");
            }

            for (unsigned int i = 0; i < case_count; i++)
            {
                std::variant<TypedNode *, ErrorChain *> checkOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->cases.at(i)->check->accept(this));
                if (ErrorChain **e = std::get_if<ErrorChain *>(&checkOpt))
                {
                    (*e)->addError(ctx->getStart(), "1319"); // FIXME: BETTER ERROR MSG, AND THIS IS AN INNEFICIENT MANNER TO ENSURE LINEARS ARE USED CORRECTLY DUE TO CASE EXPRESSIONS
                    return *e;
                }
            }

            case_count++;

            std::variant<TypedNode *, ErrorChain *> checkOpt = anyOpt2VarError<TypedNode>(errorHandler, e->check->accept(this));
            if (ErrorChain **e = std::get_if<ErrorChain *>(&checkOpt))
            {
                (*e)->addError(ctx->getStart(), "1535");
                return *e;
            }

            TypedNode *check = std::get<TypedNode *>(checkOpt);
            const Type *checkType = check->getType();

            if (!dynamic_cast<const TypeBool *>(checkType))
            {
                return errorHandler.addError(ctx->getStart(), "Select alternative expected BOOL but got " + checkType->toString());
            }

            stmgr->enterScope(StopType::NONE); // For safe exit + scoping... //FIXME: verify...

            std::variant<TypedNode *, ErrorChain *> evalOpt = anyOpt2VarError<TypedNode>(errorHandler, e->eval->accept(this));

            if (ErrorChain **e = std::get_if<ErrorChain *>(&evalOpt))
            {
                (*e)->addError(ctx->getStart(), "1559");
                return *e;
            }

            SelectAlternativeNode *ans = new SelectAlternativeNode(check, std::get<TypedNode *>(evalOpt), ctx->getStart());
            alts.push_back(ans);
            return ans; // FIXME: DONT DO PUSH BACK AND RETURN!
        });

    if (ErrorChain **e = std::get_if<ErrorChain *>(&branchOpt))
    {
        (*e)->addError(ctx->getStart(), "Failed to typecheck select statement.");
        return *e;
    }

    ConditionalData dat = std::get<ConditionalData>(branchOpt);
    return new SelectStatementNode(ctx->getStart(), alts, restDat->post);
}

std::variant<ReturnNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::ReturnStatementContext *ctx)
{
    /*
     * Lookup the @RETURN symbol which can ONLY be defined by entering FUNC/PROC
     */
    std::optional<SymbolContext> symOpt = stmgr->lookup("@RETURN");

    // If we don't have the symbol, we're not in a place that we can return from.
    if (!symOpt)
    {
        return errorHandler.addError(ctx->getStart(), "Cannot use return outside of FUNC or PROC");
    }

    Symbol *sym = symOpt.value().second;

    // If the return statement has an expression...
    if (ctx->expression())
    {
        // Evaluate the expression type
        std::variant<TypedNode *, ErrorChain *> valOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->expression()->accept(this));

        if (ErrorChain **e = std::get_if<ErrorChain *>(&valOpt))
        {
            (*e)->addError(ctx->getStart(), "1646");
            return *e;
        }

        TypedNode *val = std::get<TypedNode *>(valOpt);

        const Type *valType = val->getType();

        // If the type of the return symbol is a BOT, then we must be in a PROC and, thus, we cannot return anything
        if (const TypeUnit *b = dynamic_cast<const TypeUnit *>(sym->type))
        {
            return errorHandler.addError(ctx->getStart(), "PROC cannot return value, yet it was given a " + valType->toString() + " to return!");
        }

        // As the return type is not a BOT, we have to make sure that it is the correct type to return

        if (valType->isNotSubtype(sym->type))
        {
            return errorHandler.addError(ctx->getStart(), "Expected return type of " + sym->type->toString() + " but got " + valType->toString());
        }

        std::pair<const Type *, TypedNode *> ans = {sym->type, val};

        return new ReturnNode(ctx->getStart(), ans);
    }

    // We do not have an expression to return, so make sure that the return type is also a BOT.
    if (dynamic_cast<const TypeUnit *>(sym->type))
    {
        return new ReturnNode(ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Expected to return a " + sym->type->toString() + " but recieved nothing.");
}

std::variant<ExitNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::ExitStatementContext *ctx)
{
    std::optional<SymbolContext> symOpt = stmgr->lookup("@EXIT");

    // If we don't have the symbol, we're not in a place that we can return from.
    if (!symOpt)
    {
        return errorHandler.addError(ctx->getStart(), "Cannot use exit outside of program");
    }

    return new ExitNode(ctx->getStart());
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

std::variant<LambdaConstNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::LambdaConstExprContext *ctx)
{
    std::optional<ParameterListNode> paramTypeOpt = visitCtx(ctx->parameterList());

    if (!paramTypeOpt)
        return errorHandler.addError(ctx->getStart(), "1716");

    ParameterListNode params = paramTypeOpt.value();
    std::vector<Symbol *> ps;

    const Type *retType = ctx->ret ? any2Type(ctx->ret->accept(this))
                                   : Types::UNIT;

    stmgr->enterScope(StopType::GLOBAL);
    stmgr->addSymbol(new Symbol("@RETURN", retType, false, false));

    for (ParameterNode param : params)
    {
        Symbol *paramSymbol = new Symbol(param.name, param.type, false, false);
        stmgr->addSymbol(paramSymbol);

        ps.push_back(paramSymbol);
    }

    std::variant<BlockNode *, ErrorChain *> blkOpt = this->safeVisitBlock(ctx->block(), false);

    if (ErrorChain **e = std::get_if<ErrorChain *>(&blkOpt))
    {
        (*e)->addError(ctx->getStart(), "1741");
        return *e;
    }
    BlockNode *blk = std::get<BlockNode *>(blkOpt);

    // If we have a return type, make sure that we return as the last statement in the FUNC. The type of the return is managed when we visited it.
    if (!endsInReturn(blk))
    {
        errorHandler.addError(ctx->getStart(), "Lambda must end in return statement");
    }
    safeExitScope(ctx);
    return new LambdaConstNode(ctx->getStart(), ps, retType, blk);
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

    for (auto e : ctx->type()) // FIXME: ADD TEST CASES LIKE THIS FOR STRUCT + ENUM!! (LINEAR CHECK?)
    {
        const Type *caseType = any2Type(e->accept(this));
        std::cout << "1640 " << caseType->toString() << std::endl;

        if (isLinear(caseType))
        {
            errorHandler.addError(e->getStart(), "Unable to store linear type, " + caseType->toString() + ", in non-linear container.");
            return Types::ABSURD;
        }

        cases.insert(caseType);
    }

    if (cases.size() != ctx->type().size())
    {
        errorHandler.addError(ctx->getStart(), "Duplicate arguments to enum type, or failed to generate types");
        return Types::ABSURD;
    }

    const TypeSum *sum = new TypeSum(cases);

    return sum;
}

std::variant<DefineEnumNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::DefineEnumContext *ctx)
{
    std::string id = ctx->name->getText();
    // std::optional<SymbolContext> opt = stmgr->lookup(id);
    std::optional<Symbol *> opt = symBindings->getBinding(ctx);
    if (!opt && stmgr->lookup(id))
    {
        return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of " + id);
    }

    Symbol *sym = opt.value_or(
        new Symbol(id, new TypeSum(id), true, true));

    if (const TypeSum *sumTy = dynamic_cast<const TypeSum *>(sym->type))
    {
        if (!sumTy->isDefined())
        {
            std::set<const Type *, TypeCompare> cases = {};

            for (auto e : ctx->cases)
            {
                const Type *caseType = any2Type(e->accept(this));
                std::cout << "1676 " << caseType->toString() << std::endl;
                if (isLinear(caseType))
                {
                    return errorHandler.addError(e->getStart(), "Unable to store linear type, " + caseType->toString() + ", in non-linear container.");
                }

                cases.insert(caseType);
            }

            if (cases.size() != ctx->cases.size())
            {
                return errorHandler.addError(ctx->getStart(), "Duplicate arguments to enum type, or failed to generate types");
            }

            sumTy->define(cases);

            stmgr->addSymbol(sym);
        }
        return new DefineEnumNode(id, sumTy, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Expected enum/sum, but got: " + sym->type->toString());
}

std::variant<DefineStructNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::DefineStructContext *ctx)
{
    std::string id = ctx->name->getText();
    std::optional<Symbol *> opt = symBindings->getBinding(ctx);
    // std::optional<SymbolContext> opt = stmgr->lookup(id);
    if (!opt && stmgr->lookup(id))
    {
        return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of " + id);
    }

    Symbol *sym = opt.value_or(
        new Symbol(id, new TypeStruct(id), true, true));

    if (const TypeStruct *structType = dynamic_cast<const TypeStruct *>(sym->type))
    {
        if (!structType->isDefined())
        {
            LinkedMap<std::string, const Type *> el;

            for (WPLParser::StructCaseContext *caseCtx : ctx->cases)
            {
                std::string caseName = caseCtx->name->getText();
                if (el.lookup(caseName))
                {
                    return errorHandler.addError(caseCtx->getStart(), "Unsupported redeclaration of " + caseName);
                }
                const Type *caseTy = any2Type(caseCtx->ty->accept(this));

                if (isLinear(caseTy))
                {
                    return errorHandler.addError(caseCtx->getStart(), "Unable to store linear type, " + caseTy->toString() + ", in non-linear container.");
                }

                el.insert({caseName, caseTy});
            }
            structType->define(el);
            stmgr->addSymbol(sym);
        } // FIXME: ERROR HANDLE IF DEFINED?
        // FIXME: TRY USING FUNC DEFS AS TYPES! (FUNCS DONT SEEM TO WORK WITH PREDECL IN ENUMS!)
        return new DefineStructNode(id, structType, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Expected struct/product, but got: " + sym->type->toString());
}

const Type *SemanticVisitor::visitCtx(WPLParser::CustomTypeContext *ctx)
{
    std::string name = ctx->VARIABLE()->getText();

    std::optional<SymbolContext> opt = stmgr->lookup(name);
    if (!opt)
    {
        errorHandler.addError(ctx->getStart(), "Undefined type: " + name); // TODO: address inefficiency in var decl where this is called multiple times
        return Types::ABSURD;
    }

    Symbol *sym = opt.value().second;

    if (!sym->type || !sym->isDefinition)
    {
        errorHandler.addError(ctx->getStart(), "Cannot use: " + name + " as a type.");
        return Types::ABSURD;
    }

    return sym->type;
}

const Type *SemanticVisitor::visitCtx(WPLParser::ArrayTypeContext *ctx)
{
    const Type *subType = any2Type(ctx->ty->accept(this));

    // Undefined type errors handled below

    int len = std::stoi(ctx->len->getText());

    if (len < 1)
    {
        errorHandler.addError(ctx->getStart(), "Cannot initialize array with a size of less than 1!");
    }

    const Type *arr = new TypeArray(subType, len);
    return arr;
}
const Type *SemanticVisitor::visitCtx(WPLParser::BaseTypeContext *ctx)
{
    if (ctx->TYPE_INT())
    {
        return Types::INT;
    }
    else if (ctx->TYPE_BOOL())
    {
        return Types::BOOL;
    }
    else if (ctx->TYPE_STR())
    {
        return Types::STR;
    }
    else if (ctx->TYPE_UNIT())
    {
        return Types::UNIT;
    }

    errorHandler.addError(ctx->getStart(), "Unknown type: " + ctx->getText());
    return Types::ABSURD;
}

std::variant<BooleanConstNode *, ErrorChain *> SemanticVisitor::visitCtx(WPLParser::BooleanConstContext *ctx)
{
    return new BooleanConstNode(ctx->TRUE() ? true : false, ctx->getStart());
}

const Type *SemanticVisitor::visitCtx(WPLParser::ChannelTypeContext *ctx)
{
    const ProtocolSequence *proto = dynamic_cast<const ProtocolSequence *>(any2Protocol(ctx->proto->accept(this)));

    return new TypeChannel(proto);
}

const Type *SemanticVisitor::visitCtx(WPLParser::BoxTypeContext *ctx)
{
    const Type *inner = any2Type(ctx->ty->accept(this));

    if (isLinear(inner))
    {
        errorHandler.addError(ctx->ty->getStart(), "Cannot box a linear resource.");
        return Types::ABSURD;
    }

    return new TypeBox(inner);
}

const Type *SemanticVisitor::visitCtx(WPLParser::ProgramTypeContext *ctx)
{
    const ProtocolSequence *proto = dynamic_cast<const ProtocolSequence *>(any2Protocol(ctx->proto->accept(this)));
    return new TypeProgram(new TypeChannel(proto)); // FIXME: SEEMS A BIT ODD TO INC CHANNEL IN PROGRAM?
}

std::variant<ProgramSendNode *, ErrorChain *> SemanticVisitor::TvisitProgramSend(WPLParser::ProgramSendContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Could not find channel: " + id);
    }

    Symbol *sym = opt.value().second;

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        std::variant<TypedNode *, ErrorChain *> tnOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->expr->accept(this));
        if (ErrorChain **e = std::get_if<ErrorChain *>(&tnOpt))
        {
            (*e)->addError(ctx->getStart(), "1975");
            return *e;
        }

        TypedNode *tn = std::get<TypedNode *>(tnOpt);
        const Type *ty = tn->getType();

        std::optional<const Type *> canSend = channel->getProtocol()->send(ty);

        if (!canSend)
        {
            return errorHandler.addError(ctx->getStart(), "Failed to send " + ty->toString() + " over channel " + sym->toString());
        }
        return new ProgramSendNode(sym, tn, canSend.value(), ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot send on non-channel: " + id);
}

std::variant<ProgramRecvNode *, ErrorChain *> SemanticVisitor::TvisitAssignableRecv(WPLParser::AssignableRecvContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Could not find channel: " + id);
    }

    Symbol *sym = opt.value().second;

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {

        std::optional<const Type *> ty = channel->getProtocol()->recv();
        if (!ty)
        {
            return errorHandler.addError(ctx->getStart(), "Failed to recv over channel: " + sym->toString());
        }

        return new ProgramRecvNode(sym, ty.value(), ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot recv on non-channel: " + id);
}

std::variant<ChannelCaseStatementNode *, ErrorChain *> SemanticVisitor::TvisitProgramCase(WPLParser::ProgramCaseContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Could not find channel: " + id);
    }

    Symbol *sym = opt.value().second;
    // stmgr->removeSymbol(sym);

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        std::set<const ProtocolSequence *, ProtocolCompare> opts = {};

        for (auto alt : ctx->protoAlternative())
        {
            opts.insert(toSequence(any2Protocol(alt->check->accept(this))));
        }

        if (!channel->getProtocol()->isExtChoice(opts)) // Ensures we have all cases. //TODO: LOG THESE ERRORS BETTER
        {
            return errorHandler.addError(ctx->getStart(), "Failed to case over channel: " + sym->toString());
        }

        DeepRestData *restDat = new DeepRestData(ctx->rest);
        std::deque<DeepRestData *> *rest = restBindings->getBinding(ctx).value_or(new std::deque<DeepRestData *>());
        rest->push_front(restDat); // Is deque so that way we keep things reversed

        for (auto b : ctx->protoAlternative())
        {
            bindRestData(b->eval, rest);
        }

        const ProtocolSequence *savedRest = channel->getProtocolCopy();

        // FIXME: TEST PROTOCOLS THAT HAVE STUFF FOLLOWING CHOICE!
        std::variant<ConditionalData, ErrorChain *> branchOpt = checkBranch<WPLParser::ProtoAlternativeContext>(
            ctx,
            ctx->protoAlternative(),
            restDat,
            false,
            [this, savedRest, channel](WPLParser::ProtoAlternativeContext *alt) -> std::variant<TypedNode *, ErrorChain *>
            {
                const ProtocolSequence *proto = toSequence(any2Protocol(alt->check->accept(this)));

                proto->append(savedRest->getCopy());
                channel->setProtocol(proto);

                std::variant<TypedNode *, ErrorChain *> optEval = anyOpt2VarError<TypedNode>(errorHandler, alt->eval->accept(this));
                return optEval;
            });

        if (ErrorChain **e = std::get_if<ErrorChain *>(&branchOpt))
        {
            (*e)->addError(ctx->getStart(), "Failed to typecheck external choice.");
            return *e;
        }

        ConditionalData dat = std::get<ConditionalData>(branchOpt);

        return new ChannelCaseStatementNode(sym, dat.cases, restDat->post, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot case on non-channel: " + id);
}
std::variant<ProgramProjectNode *, ErrorChain *> SemanticVisitor::TvisitProgramProject(WPLParser::ProgramProjectContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Could not find channel: " + id);
    }

    Symbol *sym = opt.value().second;

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        const ProtocolSequence *ps = toSequence(any2Protocol(ctx->sel->accept(this)));
        unsigned int projectIndex = channel->getProtocol()->project(ps);

        if (!projectIndex)
        {
            return errorHandler.addError(ctx->getStart(), "Failed to project over channel: " + sym->toString() + " vs " + ps->toString());
        }

        return new ProgramProjectNode(sym, projectIndex, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot project on non-channel: " + id);
}
std::variant<ProgramContractNode *, ErrorChain *> SemanticVisitor::TvisitProgramContract(WPLParser::ProgramContractContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Could not find channel: " + id);
    }

    Symbol *sym = opt.value().second;

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        if (!channel->getProtocol()->contract())
        {
            return errorHandler.addError(ctx->getStart(), "Failed to contract: " + id);
        }
        stmgr->addSymbol(sym); // Makes sure we enforce weakening rules...

        /*
        c : |?-int|
        while true {
            {
                int c = ...
                more(c) ... will this break? I guess not...

            }

        }



        */
        return new ProgramContractNode(sym, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot contract on non-channel: " + id);
}
std::variant<ProgramWeakenNode *, ErrorChain *> SemanticVisitor::TvisitProgramWeaken(WPLParser::ProgramWeakenContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);

    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Could not find channel: " + id);
    }

    Symbol *sym = opt.value().second;

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        if (!channel->getProtocol()->weaken())
        {
            return errorHandler.addError(ctx->getStart(), "Failed to weaken: " + id + " against " + channel->toString());
        }
        return new ProgramWeakenNode(sym, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot weaken on non-channel: " + id);
}
std::variant<ProgramAcceptNode *, ErrorChain *> SemanticVisitor::TvisitProgramAccept(WPLParser::ProgramAcceptContext *ctx)
{
    std::string id = ctx->VARIABLE()->getText();
    std::optional<SymbolContext> opt = stmgr->lookup(id);
    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Unbound identifier: " + id);
    }

    Symbol *sym = opt.value().second;

    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(sym->type))
    {
        std::optional<const ProtocolSequence *> acceptOpt = channel->getProtocol()->acceptLoop();
        if (!acceptOpt)
        {
            return errorHandler.addError(ctx->getStart(), "Cannot accept on " + channel->toString());
        }

        std::vector<Symbol *> syms = stmgr->getAvaliableLinears();
        // FIXME: DO BETTER B/C HERE WE TRY TO ASSIGN TO THE VAR WE MANUALLY NEED TO ASSIGN? NO BC IT FAILS CHECK!

        std::vector<const TypeChannel *> to_fix;

        for (Symbol *orig : syms)
        {
            if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(orig->type))
            {
                channel->getProtocol()->guard();
                to_fix.push_back(channel);
            }
        }
        const ProtocolSequence *restProto = channel->getProtocol();

        channel->setProtocol(acceptOpt.value());
        stmgr->addSymbol(sym);

        std::variant<BlockNode *, ErrorChain *> blkOpt = safeVisitBlock(ctx->block(), true);

        channel->setProtocol(restProto);
        for (auto c : to_fix)
        {
            c->getProtocol()->unguard();
        }

        if (ErrorChain **e = std::get_if<ErrorChain *>(&blkOpt))
        {
            (*e)->addError(ctx->getStart(), "2255");
            return *e;
        }

        return new ProgramAcceptNode(sym, std::get<BlockNode *>(blkOpt), ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot accept: " + sym->toString());
}
std::variant<ProgramExecNode *, ErrorChain *> SemanticVisitor::TvisitAssignableExec(WPLParser::AssignableExecContext *ctx)
{
    std::variant<TypedNode *, ErrorChain *> opt = anyOpt2VarError<TypedNode>(errorHandler, ctx->prog->accept(this));
    if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
    {
        (*e)->addError(ctx->getStart(), "Failed to typecheck exec");
        return *e;
    }
    // Symbol *sym = opt.value().second;
    TypedNode *prog = std::get<TypedNode *>(opt);

    if (const TypeProgram *inv = dynamic_cast<const TypeProgram *>(prog->getType()))
    {
        return new ProgramExecNode(
            prog,
            new TypeChannel(toSequence(inv->getChannelType()->getProtocol()->getInverse())),
            ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot exec: " + prog->getType()->toString());
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
        errorHandler.addError(ctx->getStart(), "Duplicate protocols in choice");
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
        errorHandler.addError(ctx->getStart(), "Duplicate protocols in choice");
        // FIXME: RETURN ERROR??
    }

    return new ProtocolIChoice(opts);
}