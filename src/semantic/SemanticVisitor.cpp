#include "SemanticVisitor.h"

std::variant<TCompilationUnitNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::CompilationUnitContext *ctx)
{
    // Enter initial scope
    stmgr->enterScope(StopType::NONE);

    std::vector<TExternNode *> externs;

    std::vector<std::pair<BismuthParser::DefineProgramContext *, TypeProgram *>> progs;
    std::vector<std::pair<BismuthParser::DefineFunctionContext *, TypeFunc *>> funcs;
    std::vector<std::pair<BismuthParser::DefineStructContext *, TypeStruct *>> structs;
    std::vector<std::pair<BismuthParser::DefineEnumContext *, TypeSum *>> enums;

    std::vector<DefinitionNode> defs;

    for (auto e : ctx->defs)
    {
        if (BismuthParser::DefineProgramContext *progCtx = dynamic_cast<BismuthParser::DefineProgramContext *>(e))
        {
            std::string id = progCtx->name->getText();

            std::optional<Symbol *> opt = stmgr->lookup(id);

            if (opt)
            {
                return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of program " + id);
            }

            TypeProgram *progType = new TypeProgram();
            Symbol *progSym = new Symbol(id, progType, true, true);
            symBindings->bind(progCtx, progSym);
            stmgr->addSymbol(progSym);

            progs.push_back({progCtx, progType});
        }
        else if (BismuthParser::DefineFunctionContext *fnCtx = dynamic_cast<BismuthParser::DefineFunctionContext *>(e))
        {
            std::string id = fnCtx->name->getText();

            std::optional<Symbol *> opt = stmgr->lookup(id);

            if (opt)
            {
                return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of function " + id);
            }

            TypeFunc *funcType = new TypeFunc();
            Symbol *sym = new Symbol(id, funcType, true, true);
            symBindings->bind(fnCtx, sym);
            stmgr->addSymbol(sym);

            funcs.push_back({fnCtx, funcType});
        }
        else if (BismuthParser::DefineStructContext *prodCtx = dynamic_cast<BismuthParser::DefineStructContext *>(e))
        {
            std::string id = prodCtx->name->getText();

            std::optional<Symbol *> opt = stmgr->lookup(id);

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
        else if (BismuthParser::DefineEnumContext *sumCtx = dynamic_cast<BismuthParser::DefineEnumContext *>(e))
        {
            std::string id = sumCtx->name->getText();

            std::optional<Symbol *> opt = stmgr->lookup(id);

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
                (*e)->addError(ctx->getStart(), "Failed to type check definition");
                return *e;
            }

            errorHandler.addError(ctx->getStart(), "Unhandled case");
        }
    }

    // Visit externs first; they will report any errors if they have any.
    for (auto e : ctx->externs)
    {
        std::variant<TExternNode *, ErrorChain *> extOpt = this->visitCtx(e);

        if (ErrorChain **e = std::get_if<ErrorChain *>(&extOpt))
        {
            (*e)->addError(ctx->getStart(), "Error in definition of extern");
            return *e;
        }
        TExternNode *node = std::get<TExternNode *>(extOpt);

        if (flags & CompilerFlags::DEMO_MODE)
        {
            if (!(node->getSymbol()->getIdentifier() == "printf" && node->getType()->getParamTypes().size() == 1 && node->getType()->getParamTypes().at(0)->isSubtype(Types::DYN_STR) && node->getType()->getReturnType()->isSubtype(Types::DYN_INT) && node->getType()->isVariadic()))
            {
                errorHandler.addError(e->getStart(), "Unsupported extern; only 'extern int func printf(str, ...)' supported in demo mode");
            }
        }

        externs.push_back(node);
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
        // std::variant<TypedNode *, ErrorChain *> opt =
        anyOpt2VarError<TypedNode>(errorHandler, e.first->accept(this));
    }
    for (auto e : enums)
    {
        // std::variant<TypedNode *, ErrorChain *> opt =
        anyOpt2VarError<TypedNode>(errorHandler, e.first->accept(this));
    }

    // Visit the statements contained in the unit
    for (auto e : ctx->defs)
    {
        if (BismuthParser::DefineProgramContext *progCtx = dynamic_cast<BismuthParser::DefineProgramContext *>(e))
        {
            std::variant<TProgramDefNode *, ErrorChain *> progOpt = visitCtx(progCtx);

            if (ErrorChain **e = std::get_if<ErrorChain *>(&progOpt))
            {
                (*e)->addError(ctx->getStart(), "Failed to type check program");
                return *e;
            }

            defs.push_back(std::get<TProgramDefNode *>(progOpt));
        }
        else if (BismuthParser::DefineFunctionContext *fnCtx = dynamic_cast<BismuthParser::DefineFunctionContext *>(e))
        {
            std::variant<TLambdaConstNode *, ErrorChain *> opt = visitCtx(fnCtx);

            if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
            {
                (*e)->addError(ctx->getStart(), "Failed to type check function");
                return *e;
            }

            defs.push_back(std::get<TLambdaConstNode *>(opt));
        }
    }

    /*******************************************
     * Extra checks depending on compiler flags
     *******************************************/

    if (flags & CompilerFlags::DEMO_MODE)
    {
        /**********************************************************
         * As there is no runtime, we need to make sure that
         * there is NO main block and that we have a program block
         **********************************************************/

        if (stmgr->lookup("main"))
        {
            errorHandler.addError(ctx->getStart(), "When compiling in demo mode, main is reserved!");
        }

        std::optional<Symbol *> opt = stmgr->lookup("program");
        if (!opt)
        {
            errorHandler.addError(ctx->getStart(), "When compiling with no-runtime, 'program :: * : Channel<-int>' must be defined");
        }
        else
        {
            Symbol *sym = opt.value();
            std::optional<const TypeProgram *> progOpt = type_cast<TypeProgram>(sym->type);
            if (progOpt)
            {
                const TypeProgram *inv = progOpt.value();
                // FIXME: DO SUBTYPING BETTER!
                if (!(new TypeChannel(inv->getProtocol()))->isSubtype(new TypeChannel(new ProtocolSequence(false, {new ProtocolSend(false, Types::DYN_INT)}))))
                {
                    errorHandler.addError(ctx->getStart(), "Program must recognize a channel of protocol -int, not " + inv->toString());
                }
            }
            else
            {
                errorHandler.addError(ctx->getStart(), "When compiling in demo, 'program :: * : Channel<-int>' is required");
            }
        }
    }

    std::vector<Symbol *> uninf = stmgr->getCurrentScope().value()->getSymbols(SymbolLookupFlags::UNINFERRED_TYPE); // TODO: shouldn't ever be an issue, but still.

    // If there are any uninferred symbols, then add it as a compiler error as we won't be able to resolve them
    // due to the var leaving the scope
    if (uninf.size() > 0)
    {
        std::ostringstream details;

        for (auto e : uninf)
        {
            details << e->toString() << "; ";
        }

        errorHandler.addError(ctx->getStart(), "230 Uninferred types in context: " + details.str());
    }
    // Return UNDEFINED as this should be viewed as a statement and not something assignable
    return new TCompilationUnitNode(externs, defs);
}

std::variant<TInvocationNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::InvocationContext *ctx)
{
    std::variant<TypedNode *, ErrorChain *> typeOpt = (ctx->lam) ? TNVariantCast<TLambdaConstNode>(visitCtx(ctx->lam)) : TNVariantCast<TFieldAccessNode>(visitCtx(ctx->field, true));
    if (ErrorChain **e = std::get_if<ErrorChain *>(&typeOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to generate expression to invoke");
        return *e;
    }

    TypedNode *tn = std::get<TypedNode *>(typeOpt);

    // const Type *type = tn->getType();
    for (auto iArgs : ctx->inv_args())
    {

        std::string name = (ctx->lam) ? "lambda " : ctx->field->getText();
        std::optional<const TypeFunc *> funcTyOpt = type_cast<TypeFunc>(tn->getType());
        if (funcTyOpt)
        {
            const TypeFunc *funcTy = funcTyOpt.value();
            /*
             * The symbol is something we can invoke, so check that we provide it with valid parameters
             */
            std::vector<const Type *> fnParams = funcTy->getParamTypes();

            /*
             *  If the symbol is NOT a variadic and the number of arguments we provide
             *      are not the same as the number in the function's definition
             *  OR the symbol IS a variadic and the number of arguments in the
             *      function's definition is greater than the number we provide,
             *
             * THEN we have an error as we do not provide a valid number of arguments
             * to allow for this invocation.
             */
            if (
                (!funcTy->isVariadic() && fnParams.size() != iArgs->args.size()) || (funcTy->isVariadic() && fnParams.size() > iArgs->args.size()))
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
                std::variant<TypedNode *, ErrorChain *> providedOpt = anyOpt2VarError<TypedNode>(errorHandler, iArgs->args.at(i)->accept(this));

                if (ErrorChain **e = std::get_if<ErrorChain *>(&providedOpt))
                {
                    (*e)->addError(iArgs->args.at(i)->getStart(), "Unable to generate argument");
                    return *e;
                }

                TypedNode *provided = std::get<TypedNode *>(providedOpt);

                args.push_back(provided);

                const Type *providedType = provided->getType();

                // If the function is variadic and has no specified type parameters, then we can
                // skip over subsequent checks--we just needed to run type checking on each parameter.
                if (funcTy->isVariadic() && i >= fnParams.size()) //&& fnParams.size() == 0)
                {
                    if (type_cast<TypeBottom>(providedType) || type_cast<TypeAbsurd>(providedType) || type_cast<TypeUnit>(providedType))
                    {
                        errorHandler.addError(ctx->getStart(), "Cannot provide " + providedType->toString() + " to a function");
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

            tn = new TInvocationNode(tn, args, actualTypes, ctx->getStart());
            // return new TInvocationNode(tn, args, actualTypes, ctx->getStart());
        }
        else
        {
            // Symbol was not an function type, so report an error & return UNDEFINED.
            return errorHandler.addError(ctx->getStart(), "Can only invoke functions, not " + name + " : " + tn->getType()->toString());
        }
    }
    // return new TInvocationNode(tn, args, actualTypes, ctx->getStart());
    return (TInvocationNode *)tn;
}

std::variant<TLambdaConstNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::DefineFunctionContext *ctx)
{
    std::variant<Symbol *, ErrorChain *> funcSymOpt = getFunctionSymbol(ctx);

    if (ErrorChain **e = std::get_if<ErrorChain *>(&funcSymOpt))
    {
        return *e;
    }

    Symbol *funcSym = std::get<Symbol *>(funcSymOpt);
    stmgr->addSymbol(funcSym);

    std::variant<TLambdaConstNode *, ErrorChain *> lamOpt = visitCtx(ctx->lam);

    if (ErrorChain **e = std::get_if<ErrorChain *>(&lamOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to generate lambda");
        return *e;
    }

    TLambdaConstNode *lam = std::get<TLambdaConstNode *>(lamOpt);

    lam->type = const_cast<TypeFunc *>(dynamic_cast<const TypeFunc *>(funcSym->type)); // FIXME: DO BETTER! NEEDED B/C OF NAME RES!

    lam->name = funcSym->getIdentifier(); // Not really needed.
    return lam;
}

std::variant<TInitProductNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::InitProductContext *ctx)
{
    std::string name = ctx->v->getText();
    std::optional<Symbol *> opt = stmgr->lookup(name);

    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Cannot initialize undefined product: " + name);
    }

    Symbol *sym = opt.value();

    // TODO: METHODIZE WITH INVOKE?

    std::optional<const TypeStruct *> productOpt = type_cast<TypeStruct>(sym->type);
    if (productOpt)
    {
        const TypeStruct *product = productOpt.value();
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
                    (*e)->addError(ctx->exprs.at(i)->getStart(), "Unable to generate expression");
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
            return errorHandler.addError(ctx->getStart(), "Invalid parameters passed to product init");
        }

        return new TInitProductNode(product, n, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot initialize non-product type " + name + " : " + sym->type->toString());
}

std::variant<TInitBoxNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::InitBoxContext *ctx)
{
    std::variant<const Type *, ErrorChain *> storeTypeOpt = anyOpt2VarError<const Type>(errorHandler, ctx->ty->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&storeTypeOpt))
    {
        (*e)->addError(ctx->getStart(), "Failed to generate the type to store in the box");
        return *e;
    }

    const Type *storeType = std::get<const Type *>(storeTypeOpt);

    if (storeType->isLinear())
    {
        return errorHandler.addError(ctx->ty->getStart(), "Cannot create a box with a linear type!");
    }

    // TODO: METHODIZE WITH INVOKE AND INIT PRODUCT?
    std::variant<TypedNode *, ErrorChain *> opt = anyOpt2VarError<TypedNode>(errorHandler, ctx->expr->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
    {
        (*e)->addError(ctx->expr->getStart(), "Unable to generate expression in init box");
        return *e;
    }

    TypedNode *tn = std::get<TypedNode *>(opt);

    const Type *providedType = tn->getType();

    if (providedType->isLinear())
    {
        return errorHandler.addError(ctx->expr->getStart(), "Cannot create a box with a linear type!");
    }

    if (providedType->isNotSubtype(storeType))
    {
        std::ostringstream errorMsg;
        errorMsg << "Initialize box expected " << storeType->toString() << ", but got " << providedType->toString() << "";

        return errorHandler.addError(ctx->getStart(), errorMsg.str());
    }

    return new TInitBoxNode(new TypeBox(storeType), tn, ctx->getStart());
}

std::variant<TArrayAccessNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::ArrayAccessContext *ctx, bool is_rvalue)
{
    /*
     * Check that we are provided an INT for the index.
     */
    std::variant<TypedNode *, ErrorChain *> exprOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->index->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&exprOpt))
    {
        (*e)->addError(ctx->index->getStart(), "Unable to type check array access index");
        return *e;
    }

    TypedNode *expr = std::get<TypedNode *>(exprOpt);

    const Type *exprType = expr->getType();
    if (exprType->isNotSubtype(Types::DYN_INT))
    {
        return errorHandler.addError(ctx->getStart(), "Array access index expected type INT but got " + exprType->toString());
    }

    /*
     * Look up the symbol and check that it is defined.
     */

    std::variant<TFieldAccessNode *, ErrorChain *> opt = visitCtx(ctx->field, false); // Always have to load the array field
    if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
    {
        (*e)->addError(ctx->field->getStart(), "Cannot access value from undefined array: " + ctx->field->getText());
        return *e;
    }

    /*
     * Check that the symbol is of array type.
     */
    TFieldAccessNode *field = std::get<TFieldAccessNode *>(opt);

    if (type_cast<TypeArray>(field->getType()))
    {
        return new TArrayAccessNode(field, expr, is_rvalue, ctx->getStart());
    }

    // Report error
    return errorHandler.addError(ctx->getStart(), "Cannot use array access on non-array expression " + ctx->field->getText() + " : " + field->getType()->toString());
}

std::variant<TypedNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::LValueContext *ctx)
{
    // Check if we are a var or an array
    if (ctx->var)
    {
        return TNVariantCast<TFieldAccessNode>(visitCtx(ctx->var, false));
    }
    else if (ctx->deref)
    {
        return TNVariantCast<TDerefBoxNode>(visitCtx(ctx->deref, false));
    }

    /*
     * As we are not a var, we must be an array access, so we must visit that context.
     */
    return TNVariantCast<TArrayAccessNode>(this->visitCtx(ctx->array, false));
}

std::variant<TIntConstExprNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::IConstExprContext *ctx)
{
    return new TIntConstExprNode(std::stoi(ctx->i->getText()), ctx->getStart());
}

std::variant<TStringConstNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::SConstExprContext *ctx)
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

    return new TStringConstNode(out, ctx->getStart());
}

/**
 * @brief Typechecks Unary Expressions
 *
 * @param ctx The UnaryExpressionContext to type check
 * @return const Type* Returns the type of the inner expression if valid; UNDEFINED otherwise.
 */
std::variant<TUnaryExprNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::UnaryExprContext *ctx)
{
    // Lookup the inner type
    std::variant<TypedNode *, ErrorChain *> innerNodeOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->ex->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&innerNodeOpt))
    {
        (*e)->addError(ctx->ex->getStart(), "Failed to generate unary expression");
        return *e;
    }

    TypedNode *innerNode = std::get<TypedNode *>(innerNodeOpt);

    const Type *innerType = innerNode->getType();

    // Switch on the operation so we can ensure that the type and operation are compatable.
    switch (ctx->op->getType())
    {
    case BismuthParser::MINUS:
        if (innerType->isNotSubtype(Types::DYN_INT))
        {
            return errorHandler.addError(ctx->getStart(), "INT expected in unary minus, but got " + innerType->toString());
        }
        return new TUnaryExprNode(UNARY_MINUS, innerNode, ctx->getStart());
    case BismuthParser::NOT:
        if (innerType->isNotSubtype(Types::DYN_BOOL))
        {
            return errorHandler.addError(ctx->getStart(), "BOOL expected in unary not, but got " + innerType->toString());
        }
        return new TUnaryExprNode(UNARY_NOT, innerNode, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "605");
}

/**
 * @brief Visits a Binary Arithmetic Expression ensuring LHS and RHS are INT.
 *
 * @param ctx The BinaryArithExprContext to Visit
 * @return const Type* INT if lhs and rhs are INT; UNDEFINED otherwise.
 */
std::variant<TBinaryArithNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::BinaryArithExprContext *ctx)
{
    auto leftOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->left->accept(this));
    if (ErrorChain **e = std::get_if<ErrorChain *>(&leftOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to generate LHS of Binary Arithmetic Expression");
        return *e;
    }

    auto left = std::get<TypedNode *>(leftOpt);

    if (left->getType()->isNotSubtype(Types::DYN_INT))
    {
        return errorHandler.addError(ctx->getStart(), "INT left expression expected, but was " + left->getType()->toString());
    }

    auto rightOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->right->accept(this));
    if (ErrorChain **e = std::get_if<ErrorChain *>(&rightOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to generate RHS of binary arithmetic expression");
        return *e;
    }

    auto right = std::get<TypedNode *>(rightOpt);

    if (right->getType()->isNotSubtype(Types::DYN_INT))
    {
        return errorHandler.addError(ctx->getStart(), "INT right expression expected, but was " + right->getType()->toString());
    }

    return new TBinaryArithNode(
        ctx->MULTIPLY() ? BINARY_ARITH_MULT : ctx->DIVIDE() ? BINARY_ARITH_DIV
                                          : ctx->MOD()      ? BINARY_ARITH_MOD
                                          : ctx->PLUS()     ? BINARY_ARITH_PLUS
                                                            : BINARY_ARITH_MINUS,
        left,
        right,
        ctx->getStart());
}

std::variant<TEqExprNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::EqExprContext *ctx)
{
    std::variant<TypedNode *, ErrorChain *> rhsOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->right->accept(this));
    std::variant<TypedNode *, ErrorChain *> lhsOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->left->accept(this));

    // FIXME: DO BETTER AND ALLOW BRANCHING ERROR MSGS?

    if (ErrorChain **e = std::get_if<ErrorChain *>(&rhsOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to generate RHS");
        return *e;
    }

    if (ErrorChain **e = std::get_if<ErrorChain *>(&lhsOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to generate LHS");
        return *e;
    }

    TypedNode *lhs = std::get<TypedNode *>(lhsOpt);
    TypedNode *rhs = std::get<TypedNode *>(rhsOpt);

    if (rhs->getType()->isNotSubtype(lhs->getType()))
    {
        errorHandler.addError(ctx->getStart(), "Both sides of '=' must have the same type");
    }

    // Note: As per C spec, arrays cannot be compared
    if (type_cast<TypeArray>(lhs->getType()) || type_cast<TypeArray>(rhs->getType()))
    {
        errorHandler.addError(ctx->getStart(), "Cannot perform equality operation on arrays; they are always seen as unequal!");
    }

    return new TEqExprNode(
        ctx->EQUAL() ? EQUAL_OP : NOT_EQUAL_OP,
        lhs, rhs, ctx->getStart());
}

/**
 * @brief Visits a Logical And Expression ensuring LHS and RHS are BOOL.
 *
 * @param ctx The LogAndExprContext to Visit
 * @return const Type* BOOL if lhs and rhs are BOOL; UNDEFINED otherwise.
 */
std::variant<TLogAndExprNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::LogAndExprContext *ctx)
{
    std::vector<BismuthParser::ExpressionContext *> toVisit = ctx->exprs;
    std::vector<BismuthParser::ExpressionContext *> toGen;

    while (toVisit.size() > 0)
    {
        BismuthParser::ExpressionContext *curr = toVisit.at(0);
        toVisit.erase(toVisit.begin());

        if (BismuthParser::LogAndExprContext *orCtx = dynamic_cast<BismuthParser::LogAndExprContext *>(curr))
        {
            toVisit.insert(toVisit.end(), orCtx->exprs.begin(), orCtx->exprs.end());
        }
        else
        {
            toGen.push_back(curr);
        }
    }

    std::vector<TypedNode *> nodes;

    for (BismuthParser::ExpressionContext *e : toGen)
    {
        std::variant<TypedNode *, ErrorChain *> nodeOpt = anyOpt2VarError<TypedNode>(errorHandler, e->accept(this));

        if (ErrorChain **er = std::get_if<ErrorChain *>(&nodeOpt))
        {
            (*er)->addError(e->getStart(), "Unable to generate expression in logical and");
            return *er;
        }

        TypedNode *node = std::get<TypedNode *>(nodeOpt);
        const Type *type = node->getType();

        if (type->isNotSubtype(Types::DYN_BOOL))
        {
            errorHandler.addError(e->getStart(), "BOOL expression expected, but was " + type->toString());
        }
        else
        {
            nodes.push_back(node);
        }
    }
    return new TLogAndExprNode(nodes, ctx->getStart());
}

/**
 * @brief Visits a Logical Or Expression ensuring LHS and RHS are BOOL.
 *
 * @param ctx The LogOrExprContext to Visit
 * @return const Type* BOOL if lhs and rhs are BOOL; UNDEFINED otherwise.
 */
std::variant<TLogOrExprNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::LogOrExprContext *ctx)
{
    std::vector<BismuthParser::ExpressionContext *> toVisit = ctx->exprs;
    std::vector<BismuthParser::ExpressionContext *> toGen;

    while (toVisit.size() > 0)
    {
        BismuthParser::ExpressionContext *curr = toVisit.at(0);
        toVisit.erase(toVisit.begin());

        if (BismuthParser::LogOrExprContext *orCtx = dynamic_cast<BismuthParser::LogOrExprContext *>(curr))
        {
            toVisit.insert(toVisit.end(), orCtx->exprs.begin(), orCtx->exprs.end());
        }
        else
        {
            toGen.push_back(curr);
        }
    }

    std::vector<TypedNode *> nodes;

    for (BismuthParser::ExpressionContext *e : toGen)
    {
        std::variant<TypedNode *, ErrorChain *> nodeOpt = anyOpt2VarError<TypedNode>(errorHandler, e->accept(this));

        if (ErrorChain **e = std::get_if<ErrorChain *>(&nodeOpt))
        {
            (*e)->addError(ctx->getStart(), "794");
            return *e;
        }

        TypedNode *node = std::get<TypedNode *>(nodeOpt);
        const Type *type = node->getType();

        if (type->isNotSubtype(Types::DYN_BOOL))
        {
            errorHandler.addError(e->getStart(), "BOOL expression expected, but was " + type->toString());
        }
        else
        {
            nodes.push_back(node);
        }
    }
    return new TLogOrExprNode(nodes, ctx->getStart());
}

/**
 * @brief Visits a FieldAccessExprContext---Currently limited to array lengths
 *
 * @param ctx the FieldAccessExprContext to visit
 * @return const Type* INT if correctly used to test array length; UNDEFINED if any errors.
 */
std::variant<TFieldAccessNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::FieldAccessExprContext *ctx, bool is_rvalue)
{
    // Determine the type of the expression we are visiting
    std::optional<Symbol *> opt = stmgr->lookup(ctx->VARIABLE().at(0)->getText());
    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Undefined variable reference: " + ctx->VARIABLE().at(0)->getText());
    }
    Symbol *sym = opt.value();

    if (sym->type->isLinear())
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

        std::optional<const TypeStruct *> sOpt = type_cast<TypeStruct>(ty);
        if (sOpt)
        {
            const TypeStruct *s = sOpt.value();
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
        else if (i + 1 == ctx->fields.size() && type_cast<TypeArray>(ty) && ctx->fields.at(i)->getText() == "length")
        {
            a.push_back({"length",
                         Types::DYN_INT});

            break; // Shouldn't be needed, but is here anyways
        }
        // else if (i + 1 == ctx->fields.size() && ctx->fields.at(i)->getText() == "is_present")
        // {
        //     std::optional<const TypeChannel *> channelOpt = type_cast<TypeChannel>(ty);
        //     if (channelOpt)
        //     {
        //         const TypeChannel *channel = channelOpt.value();
        //         if (channel->getProtocol()->isOCorGuarded())
        //         {
        //             a.push_back({"is_present",
        //                          Types::DYN_BOOL}); // TODO: would be a linear fn, but then cant require we use it... maybe should be functional style? idk
        //             break;                      // Shouldn't be needed, but is here anyways
        //         }
        //     }
        //     return errorHandler.addError(ctx->getStart(), "Cannot access " + fieldName + " on " + ty->toString());
        // }
        else
        {
            return errorHandler.addError(ctx->getStart(), "Cannot access " + fieldName + " on " + ty->toString());
        }
    }
    return new TFieldAccessNode(ctx->getStart(), sym, is_rvalue, a);
}

std::variant<TDerefBoxNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::DereferenceExprContext *ctx, bool is_rvalue)
{
    std::variant<TypedNode *, ErrorChain *> exprOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->expr->accept(this));

    // Determine the type of the expression we are visiting
    if (ErrorChain **e = std::get_if<ErrorChain *>(&exprOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to type check dereference expression");
        return *e;
    }

    TypedNode *expr = std::get<TypedNode *>(exprOpt);

    const Type *exprType = expr->getType();
    std::optional<const TypeBox *> boxOpt = type_cast<TypeBox>(exprType);
    if (boxOpt)
    {
        return new TDerefBoxNode(boxOpt.value(), expr, is_rvalue, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Dereference expected Box<T> but got " + exprType->toString());
}

// Passthrough to expression
std::variant<TypedNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::ParenExprContext *ctx)
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
std::variant<TBinaryRelNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::BinaryRelExprContext *ctx)
{
    auto leftOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->left->accept(this));
    if (ErrorChain **e = std::get_if<ErrorChain *>(&leftOpt))
    {
        (*e)->addError(ctx->getStart(), "616");
        return *e;
    }

    auto left = std::get<TypedNode *>(leftOpt);

    if (left->getType()->isNotSubtype(Types::DYN_INT))
    {
        return errorHandler.addError(ctx->getStart(), "INT left expression expected, but was " + left->getType()->toString());
    }

    auto rightOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->right->accept(this));
    if (ErrorChain **e = std::get_if<ErrorChain *>(&rightOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to type check RHS of binary relation expression");
        return *e;
    }

    auto right = std::get<TypedNode *>(rightOpt);

    if (right->getType()->isNotSubtype(Types::DYN_INT))
    {
        return errorHandler.addError(ctx->getStart(), "INT right expression expected, but was " + right->getType()->toString());
    }

    return new TBinaryRelNode(
        ctx->LESS() ? BINARY_Rel_LESS : ctx->LESS_EQ() ? BINARY_Rel_LESS_EQ
                                    : ctx->GREATER()   ? BINARY_Rel_GREATER
                                                       : BINARY_Rel_GREATER_EQ,
        left,
        right,
        ctx->getStart());
}

std::variant<TSelectAlternativeNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::SelectAlternativeContext *ctx)
{
    return errorHandler.addError(ctx->getStart(), "COMP ERROR");
}

/**
 * @brief Constructs a TypeFunc based on the parameter types and assumes a return type of BOT.
 *
 * @param ctx The ParameterListContext to process.
 * @return const Type* TypeFunc representing the parameter types.
 */
std::optional<ParameterListNode> SemanticVisitor::visitCtx(BismuthParser::ParameterListContext *ctx)
{
    std::map<std::string, BismuthParser::ParameterContext *> map;

    ParameterListNode paramList;

    for (auto param : ctx->params)
    {
        std::string name = param->name->getText();

        auto prevUse = map.find(name);
        if (prevUse != map.end())
        {
            errorHandler.addError(param->getStart(), "Re-use of previously defined parameter " + name);
        }
        else
        {
            map.insert({name, param});
        }

        // ParameterNode pn = this->visitCtx(param);
        std::variant<ParameterNode, ErrorChain *> pnOpt = this->visitCtx(param);

        if (ErrorChain **e = std::get_if<ErrorChain *>(&pnOpt))
        {
            (*e)->addError(ctx->getStart(), "Failed to generate case type");
            return std::nullopt;
        }

        ParameterNode pn = std::get<ParameterNode>(pnOpt);

        paramList.push_back(pn);
    }

    return paramList;
}

std::variant<ParameterNode, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::ParameterContext *ctx)
{
    std::variant<const Type *, ErrorChain *> paramTypeOpt = anyOpt2VarError<const Type>(errorHandler, ctx->ty->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&paramTypeOpt))
    {
        (*e)->addError(ctx->getStart(), "Failed to generate case type");
        return *e;
    }

    const Type *paramType = std::get<const Type *>(paramTypeOpt);
    return ParameterNode(paramType, ctx->name->getText());
}

const Type *SemanticVisitor::visitCtx(BismuthParser::AssignmentContext *ctx)
{
    errorHandler.addError(ctx->getStart(), "Assignment should never be visited directly during type checking!");
    return Types::UNIT;
}

std::variant<TExternNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::ExternStatementContext *ctx)
{
    bool variadic = ctx->variadic || ctx->ELLIPSIS();

    std::string id = ctx->name->getText();

    std::optional<Symbol *> opt = stmgr->lookup(id);

    if (opt)
    {
        return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of " + id);
    }

    std::optional<ParameterListNode> tyOpt = (ctx->paramList) ? this->visitCtx(ctx->paramList)
                                                              : ParameterListNode();

    if (!tyOpt)
    {
        return errorHandler.addError(ctx->getStart(), "Failed to generate parameters for extern!");
    }

    std::variant<const Type *, ErrorChain *> retTypeOpt = ctx->ret ? anyOpt2VarError<const Type>(errorHandler, ctx->ret->accept(this))
                                                                   : (const Type *)Types::UNIT;

    if (ErrorChain **e = std::get_if<ErrorChain *>(&retTypeOpt))
    {
        (*e)->addError(ctx->getStart(), "Error generating return type");
        return *e;
    }

    const Type *retType = std::get<const Type *>(retTypeOpt);

    TExternNode *node = new TExternNode(id, tyOpt.value(), retType, variadic, ctx->getStart());

    stmgr->addSymbol(node->getSymbol());

    return node;
};

std::variant<TAssignNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::AssignStatementContext *ctx)
{
    // This one is the update one!

    // Determine the expected type
    std::variant<TypedNode *, ErrorChain *> varOpt = this->visitCtx(ctx->to);

    if (ErrorChain **e = std::get_if<ErrorChain *>(&varOpt))
    {
        (*e)->addError(ctx->getStart(), "Cannot assign to undefined variable: " + ctx->to->getText());
        return *e;
    }

    TypedNode *var = std::get<TypedNode *>(varOpt);



    // Determine the expression type
    std::variant<TypedNode *, ErrorChain *> exprOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->a->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&exprOpt))
    {
        (*e)->addError(ctx->getStart(), "Unable to type check assignment");
        return *e;
    }

    TypedNode *expr = std::get<TypedNode *>(exprOpt);
    const Type *exprType = expr->getType();

    if (exprType->isGuarded())
    {
        return errorHandler.addError(ctx->getStart(), "Cannot assign guarded resource to another identifier");
    }

    const Type *type = var->getType();

    // Make sure that the types are compatible. Inference automatically managed here.
    if (exprType->isNotSubtype(type))
    {
        return errorHandler.addError(ctx->getStart(), "Assignment statement expected " + type->toString() + " but got " + exprType->toString());
    }

    return new TAssignNode(var, expr, ctx->getStart());
}

std::variant<TVarDeclNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::VarDeclStatementContext *ctx)
{
    std::vector<AssignmentNode *> a;

    for (auto e : ctx->assignments)
    {
        // Needs to happen in case we have vars
        // const Type *assignType = this->visitCtx(ctx->typeOrVar());

        std::variant<const Type *, ErrorChain *> assignTypeOpt = this->visitCtx(ctx->typeOrVar());

        if (ErrorChain **e = std::get_if<ErrorChain *>(&assignTypeOpt))
        {
            (*e)->addError(ctx->getStart(), "Error generating assign type");
            return *e;
        }

        const Type *assignType = std::get<const Type *>(assignTypeOpt);
        const Type *origType = assignType->getCopy();

        if (e->a && stmgr->isGlobalScope())
        {
            if (!(dynamic_cast<BismuthParser::BConstExprContext *>(e->a) ||
                  dynamic_cast<BismuthParser::IConstExprContext *>(e->a) ||
                  dynamic_cast<BismuthParser::SConstExprContext *>(e->a)))
            {
                errorHandler.addError(e->a->getStart(), "Global variables must be assigned explicit constants or initialized at runtime!");
            }

            if (type_cast<TypeSum>(assignType))
            {
                errorHandler.addError(e->a->getStart(), "Sums cannot be initialized at a global level");
            }
        }

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
                        (*e)->addError(ctx->getStart(), "Unable to type check assignment");
                        return *e;
                    }

                    exprOpt = std::get<TypedNode *>(exprOptO);
                }
                // std::variant<TypedNode *, ErrorChain *> exprOpt = (e->a) ? anyOpt2VarError<TypedNode>(e->a->accept(this)) : std::nullopt;

                const Type *newAssignType = origType->getCopy(); // this->visitCtx(ctx->typeOrVar()); // Needed to ensure vars get their own inf type

                const Type *exprType = exprOpt ? exprOpt.value()->getType() : newAssignType;

                if (exprType->isGuarded()) // TODO: Use syntactic sugar to separate out declarations from assignments. Also could use it to make select statements work better!
                {
                    return errorHandler.addError(ctx->getStart(), "Cannot assign guarded resource to another identifier");
                }

                // Note: This automatically performs checks to prevent issues with setting VAR = VAR
                if (e->a && exprType->isNotSubtype(newAssignType))
                {
                    return errorHandler.addError(e->getStart(), "Expression of type " + exprType->toString() + " cannot be assigned to " + newAssignType->toString());
                }

                const Type *newExprType = (dynamic_cast<const TypeInfer *>(newAssignType) && e->a) ? exprType : newAssignType;

                Symbol *symbol = new Symbol(id, newExprType, false, stmgr->isGlobalScope()); // Done with exprType for later type inference purposes
                stmgr->addSymbol(symbol);

                // This is somewhat inefficient to have to repeat this for every single value, but needed if for linears and if we aren't purely FP.  
                a.push_back(new AssignmentNode({symbol}, exprOpt)); // FIXME: Does assignment node need to be list?
            }
        }
        // a.push_back(new AssignmentNode(s, exprOpt));
    }
    return new TVarDeclNode(a, ctx->getStart());
}

std::variant<TMatchStatementNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::MatchStatementContext *ctx)
{
    std::variant<TypedNode *, ErrorChain *> condOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->check->ex->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&condOpt))
    {
        (*e)->addError(ctx->getStart(), "1174");
        return *e;
    }

    TypedNode *cond = std::get<TypedNode *>(condOpt);

    std::optional<const TypeSum *> sumTypeOpt = type_cast<TypeSum>(cond->getType());
    if (sumTypeOpt)
    {
        const TypeSum *sumType = sumTypeOpt.value();
        std::vector<std::pair<Symbol *, TypedNode *>> cases;

        std::set<const Type *> foundCaseTypes = {};
        // TODO: Maybe make so these can return values?

        std::variant<ConditionalData, ErrorChain *> branchOpt = checkBranch<BismuthParser::MatchStatementContext, BismuthParser::MatchAlternativeContext>(
            ctx,
            [this, ctx](std::deque<DeepRestData *> *rest) {
                for (auto b : ctx->matchAlternative())
                {
                    bindRestData(b->eval, rest);
                }
            },
            ctx->matchAlternative(),
            false,
            [this, ctx, &cases, sumType, &foundCaseTypes](BismuthParser::MatchAlternativeContext *altCtx) -> std::variant<TypedNode *, ErrorChain *>
            {
                std::variant<const Type *, ErrorChain *> caseTypeOpt = anyOpt2VarError<const Type>(errorHandler, altCtx->type()->accept(this));

                if (ErrorChain **e = std::get_if<ErrorChain *>(&caseTypeOpt))
                {
                    (*e)->addError(ctx->getStart(), "Failed to generate case type");
                    return *e;
                }

                const Type *caseType = std::get<const Type *>(caseTypeOpt);

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
                    foundCaseTypes.insert(caseType);
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

                if (dynamic_cast<BismuthParser::TypeDefContext *>(altCtx->eval) ||
                    dynamic_cast<BismuthParser::VarDeclStatementContext *>(altCtx->eval))
                {
                    return errorHandler.addError(altCtx->getStart(), "Dead code: definition as select alternative");
                }

                TypedNode *ans = std::get<TypedNode *>(tnOpt);

                cases.push_back({local, ans});

                return ans;
            });

        if (foundCaseTypes.size() != sumType->getCases().size())
        {
            return errorHandler.addError(ctx->getStart(), "Match statement did not cover all cases needed for " + sumType->toString());
        }

        if (ErrorChain **e = std::get_if<ErrorChain *>(&branchOpt))
        {
            (*e)->addError(ctx->getStart(), "Failed to type check match statement");
            return *e;
        }

        ConditionalData dat = std::get<ConditionalData>(branchOpt);

        return new TMatchStatementNode(sumType, cond, cases, dat.post, ctx->getStart());
    }

    return errorHandler.addError(ctx->check->getStart(), "Can only case on Sum Types, not " + cond->getType()->toString());
}

/**
 * @brief Type checks a Loops
 *
 * @param ctx The LoopStatementContext to type check
 * @return const Type* UNDEFINED as this is a statement.
 */
std::variant<TWhileLoopNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::ProgramLoopContext *ctx)
{
    std::variant<TypedNode *, ErrorChain *> checkOpt = this->visitCtx(ctx->check); // Visiting check will make sure we have a boolean condition

    if (ErrorChain **e = std::get_if<ErrorChain *>(&checkOpt))
    {
        (*e)->addError(ctx->getStart(), "1309");
        return *e;
    }

    stmgr->guard();

    std::variant<TBlockNode *, ErrorChain *> blkOpt = safeVisitBlock(ctx->block(), true);

    if (ErrorChain **e = std::get_if<ErrorChain *>(&blkOpt))
    {
        (*e)->addError(ctx->getStart(), "1330");
        return *e;
    }

    if (!stmgr->unguard())
    {
        return errorHandler.addError(ctx->getStart(), "Could not unguard resources in scope");
    }

    // Return UNDEFINED because this is a statement, and UNDEFINED cannot be assigned to anything
    return new TWhileLoopNode(std::get<TypedNode *>(checkOpt), std::get<TBlockNode *>(blkOpt), ctx->getStart());
}

std::variant<TConditionalStatementNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::ConditionalStatementContext *ctx)
{
    // Automatically handles checking that we have a valid condition
    std::variant<TypedNode *, ErrorChain *> condOpt = this->visitCtx(ctx->check);

    if (ErrorChain **e = std::get_if<ErrorChain *>(&condOpt))
    {
        (*e)->addError(ctx->getStart(), "1350");
        return *e;
    }

    std::vector<BismuthParser::BlockContext *> blksCtx = {ctx->trueBlk};
    if (ctx->falseBlk)
        blksCtx.push_back(ctx->falseBlk);

    std::variant<ConditionalData, ErrorChain *> branchOpt = checkBranch<BismuthParser::ConditionalStatementContext, BismuthParser::BlockContext>(
        ctx,
        [this, blksCtx](std::deque<DeepRestData *> *rest) {
            for (auto b : blksCtx)
            {
                for (auto c : b->stmts)
                {
                    bindRestData(c, rest);
                }
            }
        },
        blksCtx,
        blksCtx.size() == 1,
        [this](BismuthParser::BlockContext *blk) -> std::variant<TypedNode *, ErrorChain *>
        {
            // Scopes automatically handled, have to use false bc we can't have the block autoscope otherwise we might throw an error before we get the chance to realize that we use all linears.
            return TNVariantCast<TBlockNode>(this->safeVisitBlock(blk, false));
        });

    if (ErrorChain **e = std::get_if<ErrorChain *>(&branchOpt))
        return errorHandler.addError(ctx->getStart(), "Failed to generate one or more cases in if statement");

    ConditionalData dat = std::get<ConditionalData>(branchOpt);

    if (ctx->falseBlk)
    {
        return new TConditionalStatementNode(ctx->getStart(), std::get<TypedNode *>(condOpt), (TBlockNode *)dat.cases.at(0), dat.post, (TBlockNode *)dat.cases.at(1));
    }

    return new TConditionalStatementNode(ctx->getStart(), std::get<TypedNode *>(condOpt), (TBlockNode *)dat.cases.at(0), dat.post);
}

std::variant<TSelectStatementNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::SelectStatementContext *ctx)
{
    // Define a recursive fn which takes ctx->cases as arg, then processes first vs rest?
    if (ctx->cases.size() < 1)
    {
        return errorHandler.addError(ctx->getStart(), "Select statement expected at least one alternative, but was given 0!");
    }

    unsigned int case_count = 0;

    std::vector<TSelectAlternativeNode *> alts;

    std::variant<ConditionalData, ErrorChain *> branchOpt = checkBranch<BismuthParser::SelectStatementContext, BismuthParser::SelectAlternativeContext>(
        ctx,
        [this, ctx](std::deque<DeepRestData *> *rest) {
            for (auto b : ctx->cases)
            {
                bindRestData(b->eval, rest);
            }
        },
        ctx->cases,
        true,
        [this, ctx, &case_count, &alts](BismuthParser::SelectAlternativeContext *e) -> std::variant<TypedNode *, ErrorChain *>
        {
            /*
             *  Just make sure that we don't try to define functions and stuff in a select as that doesn't make sense (and would cause codegen issues as it stands).
             */
            if (dynamic_cast<BismuthParser::TypeDefContext *>(e->eval) || // FIXME: DO BETTER, THERE MAY BE A LOT LIKE THIS!
                dynamic_cast<BismuthParser::VarDeclStatementContext *>(e->eval))
            {
                return errorHandler.addError(e->getStart(), "Dead code: definition as select alternative");
            }

            for (unsigned int i = 0; i < case_count; i++)
            {
                std::variant<TypedNode *, ErrorChain *> checkOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->cases.at(i)->check->accept(this));
                if (ErrorChain **e = std::get_if<ErrorChain *>(&checkOpt))
                {
                    (*e)->addError(ctx->getStart(), "1319"); // FIXME: BETTER ERROR MSG, AND THIS IS AN INEFFICIENT MANNER TO ENSURE LINEAR RESOURCES ARE USED CORRECTLY DUE TO CASE EXPRESSIONS
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

            if (checkType->isNotSubtype(Types::DYN_BOOL))
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

            TSelectAlternativeNode *ans = new TSelectAlternativeNode(check, std::get<TypedNode *>(evalOpt), ctx->getStart());
            alts.push_back(ans);
            return ans; // FIXME: DONT DO PUSH BACK AND RETURN!
        });

    if (ErrorChain **e = std::get_if<ErrorChain *>(&branchOpt))
    {
        (*e)->addError(ctx->getStart(), "Failed to type check select statement");
        return *e;
    }

    ConditionalData dat = std::get<ConditionalData>(branchOpt);
    return new TSelectStatementNode(ctx->getStart(), alts, dat.post);
}

std::variant<TReturnNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::ReturnStatementContext *ctx)
{
    /*
     * Lookup the @RETURN symbol which can ONLY be defined by entering FUNC/PROC
     */
    std::optional<Symbol *> symOpt = stmgr->lookup("@RETURN");

    // If we don't have the symbol, we're not in a place that we can return from.
    if (!symOpt)
    {
        return errorHandler.addError(ctx->getStart(), "Cannot use return outside of FUNC or PROC");
    }

    Symbol *sym = symOpt.value();

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
        if (sym->type->isSubtype(Types::UNIT))
        {
            return errorHandler.addError(ctx->getStart(), "PROC cannot return value, yet it was given a " + valType->toString() + " to return!");
        }

        // As the return type is not a BOT, we have to make sure that it is the correct type to return

        if (valType->isNotSubtype(sym->type))
        {
            return errorHandler.addError(ctx->getStart(), "Expected return type of " + sym->type->toString() + " but got " + valType->toString());
        }

        std::pair<const Type *, TypedNode *> ans = {sym->type, val};

        return new TReturnNode(ctx->getStart(), ans);
    }

    // We do not have an expression to return, so make sure that the return type is also a BOT.
    if (sym->type->isSubtype(Types::UNIT))
    {
        return new TReturnNode(ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Expected to return a " + sym->type->toString() + " but received nothing");
}

std::variant<TExitNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::ExitStatementContext *ctx)
{
    std::optional<Symbol *> symOpt = stmgr->lookup("@EXIT");

    // If we don't have the symbol, we're not in a place that we can return from.
    if (!symOpt)
    {
        return errorHandler.addError(ctx->getStart(), "Cannot use exit outside of program");
    }

    return new TExitNode(ctx->getStart());
}

std::variant<const Type *, ErrorChain *>
SemanticVisitor::visitCtx(BismuthParser::TypeOrVarContext *ctx)
{
    // If we don't have a type context, then we know that we must be doing inference
    if (!(ctx->type()))
    {
        const Type *ans = new TypeInfer();
        return ans;
    }

    // If we do have a type, then visit that context.
    // std::any temp = this->visit(ctx->type());

    return anyOpt2VarError<const Type>(errorHandler, ctx->type()->accept(this));
}

std::variant<TLambdaConstNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::LambdaConstExprContext *ctx)
{
    std::optional<ParameterListNode> paramTypeOpt = visitCtx(ctx->parameterList());

    if (!paramTypeOpt)
        return errorHandler.addError(ctx->getStart(), "1716");

    ParameterListNode params = paramTypeOpt.value();
    std::vector<Symbol *> ps;

    std::variant<const Type *, ErrorChain *> retTypeOpt = ctx->ret ? anyOpt2VarError<const Type>(errorHandler, ctx->ret->accept(this))
                                                                   : (const Type *)Types::UNIT;

    if (ErrorChain **e = std::get_if<ErrorChain *>(&retTypeOpt))
    {
        (*e)->addError(ctx->getStart(), "Error generating return type");
        return *e;
    }

    const Type *retType = std::get<const Type *>(retTypeOpt);

    stmgr->enterScope(StopType::GLOBAL);
    stmgr->addSymbol(new Symbol("@RETURN", retType, false, false));

    for (ParameterNode param : params)
    {
        Symbol *paramSymbol = new Symbol(param.name, param.type, false, false);
        stmgr->addSymbol(paramSymbol);

        ps.push_back(paramSymbol);
    }

    std::variant<TBlockNode *, ErrorChain *> blkOpt = this->safeVisitBlock(ctx->block(), false);

    if (ErrorChain **e = std::get_if<ErrorChain *>(&blkOpt))
    {
        (*e)->addError(ctx->getStart(), "1741");
        return *e;
    }
    TBlockNode *blk = std::get<TBlockNode *>(blkOpt);

    // If we have a return type, make sure that we return as the last statement in the FUNC. The type of the return is managed when we visited it.
    if (!endsInReturn(blk))
    {
        errorHandler.addError(ctx->getStart(), "Lambda must end in return statement");
    }
    safeExitScope(ctx);
    return new TLambdaConstNode(ctx->getStart(), ps, retType, blk);
}

std::variant<const TypeFunc *, ErrorChain *>
SemanticVisitor::visitCtx(BismuthParser::LambdaTypeContext *ctx)
{
    std::vector<const Type *> params;

    for (auto param : ctx->paramTypes)
    {
        std::variant<const Type *, ErrorChain *> typeOpt = anyOpt2VarError<const Type>(errorHandler, param->accept(this));

        if (ErrorChain **e = std::get_if<ErrorChain *>(&typeOpt))
        {
            (*e)->addError(ctx->getStart(), "Failed to generate parameter type");
            return *e; // TODO: ALLOW MULTIPLE ERRORS/BRANCHING?
        }

        const Type *type = std::get<const Type *>(typeOpt);

        params.push_back(type);
    }

    std::variant<const Type *, ErrorChain *> returnTypeOpt = anyOpt2VarError<const Type>(errorHandler, ctx->returnType->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&returnTypeOpt))
    {
        (*e)->addError(ctx->getStart(), "Failed to generate return type");
        return *e;
    }

    const Type *returnType = std::get<const Type *>(returnTypeOpt);

    return new TypeFunc(params, returnType);
}

std::variant<const TypeSum *, ErrorChain *>
SemanticVisitor::visitCtx(BismuthParser::SumTypeContext *ctx)
{
    std::set<const Type *, TypeCompare> cases = {};

    for (auto e : ctx->type()) // FIXME: ADD TEST CASES LIKE THIS FOR STRUCT + ENUM!! (LINEAR CHECK?)
    {
        std::variant<const Type *, ErrorChain *> caseTypeOpt = anyOpt2VarError<const Type>(errorHandler, e->accept(this));

        if (ErrorChain **e = std::get_if<ErrorChain *>(&caseTypeOpt))
        {
            (*e)->addError(ctx->getStart(), "Failed to generate case type");
            return *e;
        }

        const Type *caseType = std::get<const Type *>(caseTypeOpt);

        if (caseType->isLinear())
        {
            return errorHandler.addError(e->getStart(), "Unable to store linear type, " + caseType->toString() + ", in non-linear container");
        }

        cases.insert(caseType);
    }

    if (cases.size() != ctx->type().size())
    {
        return errorHandler.addError(ctx->getStart(), "Duplicate arguments to enum type, or failed to generate types");
    }

    return new TypeSum(cases);
}

std::variant<TDefineEnumNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::DefineEnumContext *ctx)
{
    std::string id = ctx->name->getText();
    // std::optional<Symbol *> opt = stmgr->lookup(id);
    std::optional<Symbol *> opt = symBindings->getBinding(ctx);
    if (!opt && stmgr->lookup(id))
    {
        return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of " + id);
    }

    Symbol *sym = opt.value_or(
        new Symbol(id, new TypeSum(id), true, true));

    std::optional<const TypeSum *> sumTyOpt = type_cast<TypeSum>(sym->type);
    if (sumTyOpt)
    {
        const TypeSum *sumTy = sumTyOpt.value();
        if (!sumTy->isDefined())
        {
            std::set<const Type *, TypeCompare> cases = {};

            for (auto e : ctx->cases)
            {
                std::variant<const Type *, ErrorChain *> caseTypeOpt = anyOpt2VarError<const Type>(errorHandler, e->accept(this));

                if (ErrorChain **e = std::get_if<ErrorChain *>(&caseTypeOpt))
                {
                    (*e)->addError(ctx->getStart(), "Failed to generate case type");
                    return *e;
                }

                const Type *caseType = std::get<const Type *>(caseTypeOpt);

                if (caseType->isLinear())
                {
                    return errorHandler.addError(e->getStart(), "Unable to store linear type, " + caseType->toString() + ", in non-linear container");
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
        return new TDefineEnumNode(id, sumTy, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Expected enum/sum, but got: " + sym->type->toString());
}

std::variant<TDefineStructNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::DefineStructContext *ctx)
{
    std::string id = ctx->name->getText();
    std::optional<Symbol *> opt = symBindings->getBinding(ctx);
    // std::optional<Symbol*> opt = stmgr->lookup(id);
    if (!opt && stmgr->lookup(id))
    {
        return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of " + id);
    }

    Symbol *sym = opt.value_or(
        new Symbol(id, new TypeStruct(id), true, true));

    std::optional<const TypeStruct *> structTypeOpt = type_cast<TypeStruct>(sym->type);
    if (structTypeOpt)
    {
        const TypeStruct *structType = structTypeOpt.value();
        if (!structType->isDefined())
        {
            LinkedMap<std::string, const Type *> el;

            for (BismuthParser::StructCaseContext *caseCtx : ctx->cases)
            {
                std::string caseName = caseCtx->name->getText();
                if (el.lookup(caseName))
                {
                    return errorHandler.addError(caseCtx->getStart(), "Unsupported redeclaration of " + caseName);
                }

                std::variant<const Type *, ErrorChain *> caseTyOpt = anyOpt2VarError<const Type>(errorHandler, caseCtx->ty->accept(this));

                if (ErrorChain **e = std::get_if<ErrorChain *>(&caseTyOpt))
                {
                    (*e)->addError(ctx->getStart(), "Failed to generate case type");
                    return *e;
                }

                const Type *caseTy = std::get<const Type *>(caseTyOpt);

                if (caseTy->isLinear())
                {
                    return errorHandler.addError(caseCtx->getStart(), "Unable to store linear type, " + caseTy->toString() + ", in non-linear container");
                }

                el.insert({caseName, caseTy});
            }
            structType->define(el);
            stmgr->addSymbol(sym);
        }
        return new TDefineStructNode(id, structType, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Expected struct/product, but got: " + sym->type->toString());
}

std::variant<const Type *, ErrorChain *>
SemanticVisitor::visitCtx(BismuthParser::CustomTypeContext *ctx)
{
    std::string name = ctx->VARIABLE()->getText();

    std::optional<Symbol *> opt = stmgr->lookup(name);
    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Undefined type: " + name); // TODO: address inefficiency in var decl where this is called multiple times
    }

    Symbol *sym = opt.value();

    if (!sym->type || !sym->isDefinition)
    {
        return errorHandler.addError(ctx->getStart(), "Cannot use: " + name + " as a type");
    }

    return sym->type;
}

std::variant<const TypeArray *, ErrorChain *>
SemanticVisitor::visitCtx(BismuthParser::ArrayTypeContext *ctx)
{
    std::variant<const Type *, ErrorChain *> innerOpt = anyOpt2VarError<const Type>(errorHandler, ctx->ty->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&innerOpt))
    {
        (*e)->addError(ctx->getStart(), "Failed to generate array type");
        return *e;
    }

    const Type *inner = std::get<const Type *>(innerOpt);

    // Undefined type errors handled below

    int len = std::stoi(ctx->len->getText());

    if (len < 1)
    {
        errorHandler.addError(ctx->getStart(), "Cannot initialize array with a size of less than 1!");
    }

    return new TypeArray(inner, len);
}

std::variant<const Type *, ErrorChain *>
SemanticVisitor::visitCtx(BismuthParser::BaseTypeContext *ctx)
{
    if (ctx->TYPE_INT())
    {
        return (const Type *)Types::DYN_INT;
    }
    else if (ctx->TYPE_BOOL())
    {
        return (const Type *)Types::DYN_BOOL;
    }
    else if (ctx->TYPE_STR())
    {
        return (const Type *)Types::DYN_STR;
    }
    else if (ctx->TYPE_UNIT())
    {
        return (const Type *)Types::UNIT;
    }

    return errorHandler.addError(ctx->getStart(), "Unknown type: " + ctx->getText());
}

std::variant<TBooleanConstNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::BooleanConstContext *ctx)
{
    return new TBooleanConstNode(ctx->TRUE() ? true : false, ctx->getStart());
}

std::variant<const TypeChannel *, ErrorChain *>
SemanticVisitor::visitCtx(BismuthParser::ChannelTypeContext *ctx)
{
    ProtocolVisitor *protoVisitor = new ProtocolVisitor(errorHandler, this);
    std::variant<const ProtocolSequence *, ErrorChain *> protoOpt = protoVisitor->visitProto(ctx->proto); // TODO: how to prevent calls to bad overrides? ie, protocolvisitor visit type ctx?
    delete protoVisitor;

    if (ErrorChain **e = std::get_if<ErrorChain *>(&protoOpt))
    {
        (*e)->addError(ctx->getStart(), "Failed to generate channel protocol");
        return *e;
    }

    const ProtocolSequence *proto = std::get<const ProtocolSequence *>(protoOpt);

    return new TypeChannel(proto);
}

std::variant<const TypeBox *, ErrorChain *>
SemanticVisitor::visitCtx(BismuthParser::BoxTypeContext *ctx)
{
    std::variant<const Type *, ErrorChain *> innerOpt = anyOpt2VarError<const Type>(errorHandler, ctx->ty->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&innerOpt))
    {
        (*e)->addError(ctx->getStart(), "Failed to generate type inside box");
        return *e;
    }

    const Type *inner = std::get<const Type *>(innerOpt);

    if (inner->isLinear())
    {
        return errorHandler.addError(ctx->ty->getStart(), "Cannot box a linear resource");
    }

    return new TypeBox(inner);
}

std::variant<const TypeProgram *, ErrorChain *>
SemanticVisitor::visitCtx(BismuthParser::ProgramTypeContext *ctx)
{
    ProtocolVisitor *protoVisitor = new ProtocolVisitor(errorHandler, this);                              // TODO: methodize?
    std::variant<const ProtocolSequence *, ErrorChain *> protoOpt = protoVisitor->visitProto(ctx->proto); // TODO: how to prevent calls to bad overrides? ie, protocolvisitor visit type ctx?
    delete protoVisitor;

    if (ErrorChain **e = std::get_if<ErrorChain *>(&protoOpt))
    {
        (*e)->addError(ctx->getStart(), "Failed to generate protocol type for program");
        return *e;
    }

    // TODO: perhaps change these to smart pointers?
    const ProtocolSequence *proto = std::get<const ProtocolSequence *>(protoOpt);

    return new TypeProgram(proto);
}

std::variant<TProgramSendNode *, ErrorChain *> SemanticVisitor::TvisitProgramSend(BismuthParser::ProgramSendContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<Symbol *> opt = stmgr->lookup(id);

    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Could not find channel: " + id);
    }

    Symbol *sym = opt.value();

    std::optional<const TypeChannel *> channelOpt = type_cast<TypeChannel>(sym->type);
    if (channelOpt)
    {
        const TypeChannel *channel = channelOpt.value();
        std::variant<TypedNode *, ErrorChain *> tnOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->expr->accept(this));
        if (ErrorChain **e = std::get_if<ErrorChain *>(&tnOpt))
        {
            (*e)->addError(ctx->getStart(), "1975");
            return *e;
        }

        TypedNode *tn = std::get<TypedNode *>(tnOpt);
        const Type *ty = tn->getType();

        bool inCloseable = channel->getProtocol()->isInCloseable(); 
        std::optional<const Type *> canSend = channel->getProtocol()->send(ty);

        if (!canSend)
        {
            return errorHandler.addError(ctx->getStart(), "Failed to send " + ty->toString() + " over channel " + sym->toString());
        }
        return new TProgramSendNode(sym, inCloseable, tn, canSend.value(), ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot send on non-channel: " + id);
}

std::variant<TProgramRecvNode *, ErrorChain *> SemanticVisitor::TvisitAssignableRecv(BismuthParser::AssignableRecvContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<Symbol *> opt = stmgr->lookup(id);

    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Could not find channel: " + id);
    }

    Symbol *sym = opt.value();

    std::optional<const TypeChannel *> channelOpt = type_cast<TypeChannel>(sym->type);

    if (channelOpt)
    {
        const TypeChannel *channel = channelOpt.value();
        bool closeState = channel->getProtocol()->isInCloseable(); 
        std::optional<RecvMetadata> ty = channel->getProtocol()->recv();
        if (!ty)
        {
            return errorHandler.addError(ctx->getStart(), "Failed to recv over channel: " + sym->toString());
        }

        return new TProgramRecvNode(sym, ty.value(), closeState, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot recv on non-channel: " + id);
}

std::variant<TProgramIsPresetNode *, ErrorChain *> SemanticVisitor::TvisitAssignableIsPresent(BismuthParser::AssignableIsPresentContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<Symbol *> opt = stmgr->lookup(id);

    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Could not find channel: " + id);
    }

    Symbol *sym = opt.value();

    std::optional<const TypeChannel *> channelOpt = type_cast<TypeChannel>(sym->type);

    if (channelOpt)
    {
        const TypeChannel *channel = channelOpt.value();
        bool isInCloseable = channel->getProtocol()->isInCloseable(); 
        if (!channel->getProtocol()->isOC(true))
        {
            return errorHandler.addError(ctx->getStart(), "is_present() could not be applied to " + sym->toString() + " as it is not a ! loop");
        }

        return new TProgramIsPresetNode(sym, isInCloseable, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot recv on non-channel: " + id);
}

std::variant<TChannelCaseStatementNode *, ErrorChain *> SemanticVisitor::TvisitProgramCase(BismuthParser::ProgramCaseContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<Symbol *> opt = stmgr->lookup(id);

    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Could not find channel: " + id);
    }

    Symbol *sym = opt.value();
    // stmgr->removeSymbol(sym);

    std::optional<const TypeChannel *> channelOpt = type_cast<TypeChannel>(sym->type);
    if (channelOpt)
    {
        const TypeChannel *channel = channelOpt.value();
        std::set<const ProtocolSequence *, ProtocolCompare> opts = {};
        std::set<std::pair<const ProtocolSequence *, BismuthParser::StatementContext *>, ProtocolCompareInv> optsI = {};

        for (auto alt : ctx->protoAlternative())
        {
            // TODO: SEEMS WRONG TO PERFORM ERROR CHECKS HERE AS, BY DEF, COULD ONLY ERROR SHOULD HIGHER-LEVEL PROTO FAIL, BUT I GUESS MAYBE USEFUL IF WE LATER ADD INF!
            ProtocolVisitor *protoVisitor = new ProtocolVisitor(errorHandler, this);
            std::variant<const ProtocolSequence *, ErrorChain *> protoOpt = protoVisitor->visitProto(alt->check); // TODO: how to prevent calls to bad overrides? ie, ProtocolVisitor visit type ctx?
            delete protoVisitor;

            if (ErrorChain **e = std::get_if<ErrorChain *>(&protoOpt))
            {
                (*e)->addError(ctx->getStart(), "Failed to generate protocol type in channel case statement");
                return *e;
            }

            const ProtocolSequence *a = std::get<const ProtocolSequence *>(protoOpt);

            opts.insert(a);
            optsI.insert({a->getInverse(), alt->eval}); // Double inverses to ensure order same for both sides (server & client)
        }

        std::vector<const ProtocolSequence *> sequences = {};
        std::vector<BismuthParser::StatementContext *> alternatives = {};


        for (auto itr : optsI)
        {
            sequences.push_back(itr.first->getInverse());
            alternatives.push_back(itr.second);
        }

        bool isInCloseable = channel->getProtocol()->isInCloseable(); 

        if(ctx->protoElse() && !isInCloseable)
        {
            return errorHandler.addError(ctx->protoElse()->getStart(), "Dead code - An else block can only apply to choices in a lossy protocol");
        }
        // if(ctx->protoElse())
        // {
        //     if(!isInCloseable)
        //     {
        //         return errorHandler.addError(ctx->protoElse()->getStart(), "Dead code - An else block can only apply to choices in a lossy protocol");
        //     }

        //     const ProtocolSequence * copySeq = channel->getProtocol()->getCopy();

        //     if(!copySeq->cancel())
        //     {
        //         return errorHandler.addError(ctx->protoElse()->getStart(), "Failed to close protocol marked as closed. Please report this error as this is likely a compiler bug.");
        //     }

        //     sequences.push_back(copySeq);
        //     alternatives.push_back(ctx->protoElse()->statement());
        // }

        if (!channel->getProtocol()->isExtChoice(opts)) // Ensures we have all cases. //TODO: LOG THESE ERRORS BETTER
        {
            return errorHandler.addError(ctx->getStart(), "Failed to case over channel: " + sym->toString());
        }

        const ProtocolSequence *savedRest = channel->getProtocolCopy();

        for(auto proto : sequences)
        {
            proto->append(savedRest->getCopy());
        }

        if(ctx->protoElse())
        {
            sequences.push_back(savedRest->getCopy());
            alternatives.push_back(ctx->protoElse()->statement());
        }

        unsigned int branch = 0;
        std::variant<ConditionalData, ErrorChain *> branchOpt = checkBranch<BismuthParser::ProgramCaseContext, BismuthParser::StatementContext>(
            ctx,
            [this, ctx](std::deque<DeepRestData *> *rest) {
                for (auto b : ctx->protoAlternative())
                {
                    bindRestData(b->eval, rest);
                }
            },
            alternatives,
            // false,
            (isInCloseable && !ctx->protoElse()),
            [this, savedRest, sequences, &branch, id](BismuthParser::StatementContext *alt) -> std::variant<TypedNode *, ErrorChain *>
            {
                const ProtocolSequence *proto = sequences.at(branch++);

                std::optional<Symbol *> opt = stmgr->lookup(id);

                if (!opt)
                {
                    return errorHandler.addError(alt->getStart(), "Could not find channel: " + id);
                }

                Symbol *sym = opt.value();
                std::optional<const TypeChannel *> channelOpt = type_cast<TypeChannel>(sym->type);
                if (channelOpt)
                {
                    const TypeChannel *channel = channelOpt.value();
                    channel->setProtocol(proto);
                    std::variant<TypedNode *, ErrorChain *> optEval = anyOpt2VarError<TypedNode>(errorHandler, alt->accept(this));
                    return optEval;
                }

                return errorHandler.addError(alt->getStart(), "FAILED; COMPILER ERROR");
            });

        if (ErrorChain **e = std::get_if<ErrorChain *>(&branchOpt))
        {
            (*e)->addError(ctx->getStart(), "Failed to type check external choice");
            return *e;
        }

        ConditionalData dat = std::get<ConditionalData>(branchOpt);

        return new TChannelCaseStatementNode(sym, isInCloseable, ctx->protoElse(), dat.cases, dat.post, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot case on non-channel: " + id);
}
std::variant<TProgramProjectNode *, ErrorChain *> SemanticVisitor::TvisitProgramProject(BismuthParser::ProgramProjectContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<Symbol *> opt = stmgr->lookup(id);

    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Could not find channel: " + id);
    }

    Symbol *sym = opt.value();

    std::optional<const TypeChannel *> channelOpt = type_cast<TypeChannel>(sym->type);
    if (channelOpt)
    {
        const TypeChannel *channel = channelOpt.value();

        ProtocolVisitor *protoVisitor = new ProtocolVisitor(errorHandler, this);
        std::variant<const ProtocolSequence *, ErrorChain *> protoOpt = protoVisitor->visitProto(ctx->sel); // TODO: how to prevent calls to bad overrides? ie, ProtocolVisitor visit type ctx?
        delete protoVisitor;

        if (ErrorChain **e = std::get_if<ErrorChain *>(&protoOpt))
        {
            (*e)->addError(ctx->getStart(), "Failed to generate protocol type in project statement");
            return *e;
        }

        const ProtocolSequence *ps = std::get<const ProtocolSequence *>(protoOpt);

        unsigned int projectIndex = channel->getProtocol()->project(ps);

        if (!projectIndex)
        {
            return errorHandler.addError(ctx->getStart(), "Failed to project over channel: " + sym->toString() + " vs " + ps->toString());
        }

        return new TProgramProjectNode(sym, projectIndex, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot project on non-channel: " + id);
}
std::variant<TProgramContractNode *, ErrorChain *> SemanticVisitor::TvisitProgramContract(BismuthParser::ProgramContractContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<Symbol *> opt = stmgr->lookup(id);

    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Could not find channel: " + id);
    }

    Symbol *sym = opt.value();

    std::optional<const TypeChannel *> channelOpt = type_cast<TypeChannel>(sym->type);
    if (channelOpt)
    {
        const TypeChannel *channel = channelOpt.value();
        if (!channel->getProtocol()->contract())
        {
            return errorHandler.addError(ctx->getStart(), "Failed to contract: " + id);
        }
        // stmgr->addSymbol(sym); // Makes sure we enforce weakening rules...

        /*
        c : |?-int|
        while true {
            {
                int c = ...
                more(c) ... will this break? I guess not...

            }

        }



        */
        return new TProgramContractNode(sym, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot contract on non-channel: " + id);
}

std::variant<TProgramWeakenNode *, ErrorChain *> SemanticVisitor::TvisitProgramWeaken(BismuthParser::ProgramWeakenContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<Symbol *> opt = stmgr->lookup(id);

    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Could not find channel: " + id);
    }

    Symbol *sym = opt.value();

    std::optional<const TypeChannel *> channelOpt = type_cast<TypeChannel>(sym->type);
    if (channelOpt)
    {
        const TypeChannel *channel = channelOpt.value();
        if (!channel->getProtocol()->weaken())
        {
            return errorHandler.addError(ctx->getStart(), "Failed to weaken: " + id + " against " + channel->toString());
        }
        return new TProgramWeakenNode(sym, ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot weaken on non-channel: " + id);
}

std::variant<TProgramCancelNode *, ErrorChain *> SemanticVisitor::TvisitProgramCancel(BismuthParser::ProgramCancelContext *ctx)
{
    std::string id = ctx->channel->getText();
    std::optional<Symbol *> opt = stmgr->lookup(id);

    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Could not find channel: " + id);
    }

    Symbol *sym = opt.value();

    std::optional<const TypeChannel *> channelOpt = type_cast<TypeChannel>(sym->type);
    if (channelOpt)
    {
        const TypeChannel *channel = channelOpt.value();
        std::optional<const ProtocolClose *> closeOpt = channel->getProtocol()->cancel();

        if (!closeOpt)
        {
            return errorHandler.addError(ctx->getStart(), "Failed to cancel: " + id + " : "  + channel->toString());
        }
        return new TProgramCancelNode(sym, closeOpt.value()->getCloseNumber(), ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot cancel on non-channel: " + id); // TODO : better error messages (expected type XYZ but got)
}

std::variant<TProgramAcceptNode *, ErrorChain *> SemanticVisitor::TvisitProgramAccept(BismuthParser::ProgramAcceptContext *ctx)
{
    std::string id = ctx->VARIABLE()->getText();
    std::optional<Symbol *> opt = stmgr->lookup(id);
    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Unbound identifier: " + id);
    }

    Symbol *sym = opt.value();

    std::optional<const TypeChannel *> channelOpt = type_cast<TypeChannel>(sym->type);
    if (channelOpt)
    {
        const TypeChannel *channel = channelOpt.value();
        bool isInCloseable = channel->getProtocol()->isInCloseable(); 
        std::optional<const ProtocolSequence *> acceptOpt = channel->getProtocol()->acceptLoop();
        if (!acceptOpt)
        {
            return errorHandler.addError(ctx->getStart(), "Cannot accept on " + channel->toString());
        }
        const ProtocolSequence *postC = channel->getProtocolCopy();
        postC->guard();

        stmgr->guard();

        channel->setProtocol(acceptOpt.value());

        // stmgr->addSymbol(sym);

        std::variant<TBlockNode *, ErrorChain *> blkOpt = safeVisitBlock(ctx->block(), true);
        std::vector<Symbol *> lins = stmgr->getLinears(SymbolLookupFlags::PENDING_LINEAR);

        // If there are any uninferred symbols, then add it as a compiler error as we won't be able to resolve them
        // due to the var leaving the scope
        if (lins.size() > 0)
        {
            std::ostringstream details;

            for (auto e : lins)
            {
                details << e->toString() << "; ";
            }

            errorHandler.addError(ctx->getStart(), "2114 Unused linear types in context: " + details.str());
        }

        channel->setProtocol(postC);
        if (!stmgr->unguard())
        {
            return errorHandler.addError(ctx->getStart(), "Could not unguard resources in scope");
        }

        if (ErrorChain **e = std::get_if<ErrorChain *>(&blkOpt))
        {
            (*e)->addError(ctx->getStart(), "2255");
            return *e;
        }

        return new TProgramAcceptNode(sym, isInCloseable, std::get<TBlockNode *>(blkOpt), ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot accept: " + sym->toString());
}

std::variant<TProgramAcceptWhileNode *, ErrorChain *> SemanticVisitor::TvisitProgramAcceptWhile(BismuthParser::ProgramAcceptWhileContext *ctx)
{
    std::string id = ctx->VARIABLE()->getText();
    std::optional<Symbol *> opt = stmgr->lookup(id);
    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Unbound identifier: " + id);
    }

    Symbol *sym = opt.value();

    std::optional<const TypeChannel *> channelOpt = type_cast<TypeChannel>(sym->type);
    if (channelOpt)
    {
        const TypeChannel *channel = channelOpt.value();
        std::variant<TypedNode *, ErrorChain *> condOpt = this->visitCondition(ctx->ex);

        if (ErrorChain **e = std::get_if<ErrorChain *>(&condOpt))
        {
            (*e)->addError(ctx->getStart(), "1350");
            return *e;
        }

        bool isInCloseable = channel->getProtocol()->isInCloseable(); 
        std::optional<const ProtocolSequence *> acceptOpt = channel->getProtocol()->acceptWhileLoop();
        if (!acceptOpt)
        {
            return errorHandler.addError(ctx->getStart(), "Cannot accept on " + channel->toString());
        }
        const ProtocolSequence *postC = channel->getProtocolCopy();
        postC->guard();

        stmgr->guard();
        channel->setProtocol(acceptOpt.value());

        std::variant<TBlockNode *, ErrorChain *> blkOpt = safeVisitBlock(ctx->block(), true);
        std::vector<Symbol *> lins = stmgr->getLinears(SymbolLookupFlags::PENDING_LINEAR);

        // If there are any uninferred symbols, then add it as a compiler error as we won't be able to resolve them
        // due to the var leaving the scope
        if (lins.size() > 0)
        {
            std::ostringstream details;

            for (auto e : lins)
            {
                details << e->toString() << "; ";
            }

            errorHandler.addError(ctx->getStart(), "2196 Unused linear types in context: " + details.str());
        }

        channel->setProtocol(postC);
        if (!stmgr->unguard())
        {
            return errorHandler.addError(ctx->getStart(), "Could not unguard resources in scope");
        }

        if (ErrorChain **e = std::get_if<ErrorChain *>(&blkOpt))
        {
            (*e)->addError(ctx->getStart(), "2255");
            return *e;
        }

        return new TProgramAcceptWhileNode(sym, isInCloseable, std::get<TypedNode *>(condOpt), std::get<TBlockNode *>(blkOpt), ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot accept: " + sym->toString());
}

std::variant<TProgramAcceptIfNode *, ErrorChain *> SemanticVisitor::TvisitProgramAcceptIf(BismuthParser::ProgramAcceptIfContext *ctx)
{
    std::string id = ctx->VARIABLE()->getText();
    std::optional<Symbol *> opt = stmgr->lookup(id);
    if (!opt)
    {
        return errorHandler.addError(ctx->getStart(), "Unbound identifier: " + id);
    }

    Symbol *sym = opt.value();

    std::optional<const TypeChannel *> channelOpt = type_cast<TypeChannel>(sym->type);
    if (channelOpt)
    {
        const TypeChannel *channel = channelOpt.value();
        std::variant<TypedNode *, ErrorChain *> condOpt = this->visitCondition(ctx->check);

        if (ErrorChain **e = std::get_if<ErrorChain *>(&condOpt))
        {
            (*e)->addError(ctx->getStart(), "1350");
            return *e;
        }

        bool isInCloseable = channel->getProtocol()->isInCloseable();
        std::optional<const ProtocolSequence *> acceptOpt = channel->getProtocol()->acceptIf();
        if (!acceptOpt)
        {
            return errorHandler.addError(ctx->getStart(), "Cannot accept on " + channel->toString());
        }

        std::vector<BismuthParser::BlockContext *> blksCtx = {ctx->trueBlk};
        if (ctx->falseBlk)
            blksCtx.push_back(ctx->falseBlk);


        unsigned int idx = 0;

        std::variant<ConditionalData, ErrorChain *> branchOpt = checkBranch<BismuthParser::ProgramAcceptIfContext, BismuthParser::BlockContext>(
            ctx,
            [this, blksCtx](std::deque<DeepRestData *> *rest) {
                for (auto b : blksCtx) // TODO: Methodize this w/ other conditions?
                {
                    for (auto c : b->stmts)
                    {
                        bindRestData(c, rest);
                    }
                }
            },
            blksCtx,
            blksCtx.size() == 1, // TODO: VERIFY
            [this, &idx, id, acceptOpt](BismuthParser::BlockContext *blk) -> std::variant<TypedNode *, ErrorChain *>
            {
                if (idx == 0)
                {
                    idx++;
                    std::optional<Symbol *> opt = stmgr->lookup(id);

                    if (!opt) // FIXME: FIND BETTER WAY TO MAP AND CHANGE CHANNEL VALUES IN SPECIFIC BRANCHES
                    {
                        return errorHandler.addError(blk->getStart(), "Could not find channel: " + id);
                    }

                    Symbol *sym = opt.value();
                    std::optional<const TypeChannel *> channelOpt = type_cast<TypeChannel>(sym->type);
                    if (channelOpt)
                    {
                        const TypeChannel *channel = channelOpt.value();
                        channel->setProtocol(acceptOpt.value());
                        return TNVariantCast<TBlockNode>(this->safeVisitBlock(blk, false));
                    }

                    return errorHandler.addError(blk->getStart(), "FAILED; COMPILER ERROR");
                }
                return TNVariantCast<TBlockNode>(this->safeVisitBlock(blk, false));
            });

        if (ErrorChain **e = std::get_if<ErrorChain *>(&branchOpt))
            return errorHandler.addError(ctx->getStart(), "Failed to generate one or more branches in acceptIf");

        ConditionalData dat = std::get<ConditionalData>(branchOpt);
        if (ctx->falseBlk)
        {
            return new TProgramAcceptIfNode(ctx->getStart(), isInCloseable, sym, std::get<TypedNode *>(condOpt), (TBlockNode *)dat.cases.at(0), dat.post, (TBlockNode *)dat.cases.at(1));
        }

        return new TProgramAcceptIfNode(ctx->getStart(), isInCloseable, sym, std::get<TypedNode *>(condOpt), (TBlockNode *)dat.cases.at(0), dat.post);
    }

    return errorHandler.addError(ctx->getStart(), "Cannot accept: " + sym->toString());
}

std::variant<TProgramExecNode *, ErrorChain *> SemanticVisitor::TvisitAssignableExec(BismuthParser::AssignableExecContext *ctx)
{
    std::variant<TypedNode *, ErrorChain *> opt = anyOpt2VarError<TypedNode>(errorHandler, ctx->prog->accept(this));
    if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
    {
        (*e)->addError(ctx->getStart(), "Failed to type check exec");
        return *e;
    }
    // Symbol *sym = opt.value();
    TypedNode *prog = std::get<TypedNode *>(opt);

    std::optional<const TypeProgram *> invOpt = type_cast<TypeProgram>(prog->getType());
    if (invOpt)
    {
        const TypeProgram *inv = invOpt.value();
        return new TProgramExecNode(
            prog,
            new TypeChannel(inv->getProtocol()->getInverse()),
            ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Cannot exec: " + prog->getType()->toString());
}

std::variant<TExprCopyNode *, ErrorChain *> SemanticVisitor::TvisitCopyExpr(BismuthParser::CopyExprContext *ctx)
{
    std::variant<TypedNode *, ErrorChain *> tnOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->expr->accept(this));
    if (ErrorChain **e = std::get_if<ErrorChain *>(&tnOpt))
    {
        (*e)->addError(ctx->getStart(), "Failed to type check copy expression");
        return *e;
    }

    TypedNode *tn = std::get<TypedNode *>(tnOpt);
    const Type *ty = tn->getType();

    if (ty->isLinear())
    {
        return errorHandler.addError(ctx->getStart(), "Cannot perform a copy on a linear type: " + ty->toString());
    }

    return new TExprCopyNode(tn, ctx->getStart());
}

std::variant<TAsChannelNode *, ErrorChain *> SemanticVisitor::TvisitAsChannelExpr(BismuthParser::AsChannelExprContext *ctx)
{
    std::variant<TypedNode *, ErrorChain *> tnOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->expr->accept(this));
    if (ErrorChain **e = std::get_if<ErrorChain *>(&tnOpt))
    {
        (*e)->addError(ctx->getStart(), "Failed to type check copy expression");
        return *e;
    }

    TypedNode *tn = std::get<TypedNode *>(tnOpt);

    return new TAsChannelNode(tn, ctx->getStart());
}


template <RestRuleContext R, typename T>
inline std::variant<SemanticVisitor::ConditionalData, ErrorChain *> SemanticVisitor::checkBranch(
    R *ctx,
    std::function<void(std::deque<DeepRestData *> *)> forwardBindings, 
    std::vector<T *> ctxCases,
    bool checkRestIndependently,
    std::function<std::variant<TypedNode *, ErrorChain *>(T *)> typeCheck)
{

    DeepRestData *restDat = new DeepRestData(ctx->rest);
    std::deque<DeepRestData *> *rest = new std::deque<DeepRestData *>();
    std::optional<std::deque<DeepRestData *> *> bindings = restBindings->getBinding(ctx);
    if (bindings.has_value())
    {
        for (auto a : *bindings.value())
            rest->push_back(a);
    }

    
    rest->push_front(restDat);

    forwardBindings(rest); 



    std::optional<std::deque<DeepRestData *> *> deepRest = restBindings->getBinding(ctx);

    std::vector<TypedNode *> cases;

    STManager *origStmgr = this->stmgr;

    const auto checkCase = [&](antlr4::Token * branchToken, bool checkRest, std::string branchErrorMessage, std::string subsequentErrorMessage) -> std::optional<ErrorChain *>{
        if(checkRest)
        {
            for (auto s : restDat->ctxRest)
            {
                std::variant<TypedNode *, ErrorChain *> rOpt = anyOpt2VarError<TypedNode>(errorHandler, s->accept(this));

                if (ErrorChain **e = std::get_if<ErrorChain *>(&rOpt))
                {
                    (*e)->addError(branchToken, branchErrorMessage);
                    return *e;
                }

                if (!restDat->isGenerated)
                {
                    restDat->post.push_back(std::get<TypedNode *>(rOpt));
                }
            }

            restDat->isGenerated = true;
        }

        // FIXME: WILL NEED TO RUN THIS CHECK ON EACH ITERATION!
        if (deepRest && !endsInReturn(restDat->post) && !endsInBranch(restDat->post))
        {
            for (auto r : *(deepRest.value()))
            {
                for (auto s : r->ctxRest)
                {
                    std::variant<TypedNode *, ErrorChain *> rOpt = anyOpt2VarError<TypedNode>(errorHandler, s->accept(this));

                    if (ErrorChain **e = std::get_if<ErrorChain *>(&rOpt))
                    {
                        (*e)->addError(ctx->getStart(), subsequentErrorMessage); // "Failed to type check when no branch followed"
                        return *e;
                    }

                    if (!r->isGenerated)
                    {
                        r->post.push_back(std::get<TypedNode *>(rOpt));
                    }
                }
                r->isGenerated = true;
            }
        }

        safeExitScope(ctx); // FIXME: MAKE THIS ABLE TO TRIP ERROR?

        std::vector<Symbol *> lins = stmgr->getLinears(SymbolLookupFlags::PENDING_LINEAR);

        // If there are any uninferred symbols, then add it as a compiler error as we won't be able to resolve them
        // due to the var leaving the scope
        if (lins.size() > 0)
        {
            std::ostringstream details;

            for (auto e : lins)
            {
                details << e->toString() << "; ";
            }
            // SUM TYPE: ALLOW OPS THAT COULD BE POSSIBLE BOTH WAYS?
            // But problem here is that we need the whole environment to converge.... and not just subtypes, but exactly the same.... but then why would the channels be allowed to be sums>

            errorHandler.addError(branchToken, "588 Unused linear types in context: " + details.str());
        }

        return std::nullopt; 
    };

    for (unsigned int i = 0; i < ctxCases.size(); i++)
    {
        auto alt = ctxCases.at(i);

        if (checkRestIndependently || i + 1 < ctxCases.size())
        {
            std::optional<STManager *> optSTCopy = origStmgr->getCopy();
            if (!optSTCopy)
                return errorHandler.addError(alt->getStart(), "Failed to copy symbol table; this is likely a compiler error");
            this->stmgr = optSTCopy.value(); // TODO: DELETE RESOURCE?
        }
        else
        {
            this->stmgr = origStmgr;
        }

        stmgr->enterScope(StopType::NONE);
        std::variant<TypedNode *, ErrorChain *> optEval = typeCheck(alt);

        if (ErrorChain **e = std::get_if<ErrorChain *>(&optEval))
        {
            (*e)->addError(ctx->getStart(), "2083");
            return *e;
        }

        TypedNode *caseNode = std::get<TypedNode *>(optEval);
        cases.push_back(caseNode);

        std::optional<ErrorChain *> errorOpt = checkCase(alt->getStart(), !endsInReturn(caseNode) && !endsInBranch(caseNode), "Failed to type check code following branch", "Failed to type check when no branch followed");
        if(errorOpt) return errorOpt.value();
    }

    if (checkRestIndependently)
    {
        this->stmgr = origStmgr;

        stmgr->enterScope(StopType::NONE); // Why? This doesnt make sense.. oh it does, but should ideally refactor!

        std::optional<ErrorChain *> errorOpt = checkCase(ctx->getStart(), true, "Failed to type check code when conditional skipped over", "Failed to type check when skipped over and no branch followed");
        if(errorOpt) return errorOpt.value();
    }

    return ConditionalData(cases, restDat->post);
}
