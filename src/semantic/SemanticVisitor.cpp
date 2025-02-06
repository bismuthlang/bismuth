#include "SemanticVisitor.h"

// #define SAFE_DYNAMIC_CAST(id, type, expr, ctx, message)\
//     auto id = dynamic_cast<type>(expr);\
//     if(!id) return errorHandler.addError(ctx, message);
#include "CUtils.h"
#include "CompilerFlags.h"
#include <regex>

#define IMPL_MACRO_CONCAT(a,b) a##b

#define IMPL_DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(type, id, expr, ctx, message, tmp) \
  std::optional<type> tmp = expr; \
  if(!tmp) { \
    return errorHandler.addError(ctx->getStart(), message); \
  } \
  type id = tmp.value(); \

#define IMPL_DEFINE_OR_PROPAGATE_VARIANT_WMSG(type, id, expr, ctx, message, tmp) \
  std::variant<type, ErrorChain*> tmp = expr; \
  if (ErrorChain **e = std::get_if<ErrorChain *>(&tmp)) \
  { \
    return (*e)->addError(ctx->getStart(), message); \
  } \
  type id = std::get<type>(tmp); \

#define IMPL_DEFINE_OR_PROPAGATE_VARIANT(type, id, expr, ctx, tmp) \
  std::variant<type, ErrorChain*> tmp = expr; \
  if (ErrorChain **e = std::get_if<ErrorChain *>(&tmp)) \
  { \
    return (*e)->addErrorAt(ctx->getStart()); \
  } \
  type id = std::get<type>(tmp); \

# define DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(type, id, expr, ctx, message) IMPL_DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(type, id, expr, ctx, message, IMPL_MACRO_CONCAT(id, _COUNTER__))
# define DEFINE_OR_PROPAGATE_VARIANT_WMSG(type, id, expr, ctx, message) IMPL_DEFINE_OR_PROPAGATE_VARIANT_WMSG(type, id, expr, ctx, message, IMPL_MACRO_CONCAT(id, __COUNTER__))
# define DEFINE_OR_PROPAGATE_VARIANT(type, id, expr, ctx) IMPL_DEFINE_OR_PROPAGATE_VARIANT(type, id, expr, ctx, IMPL_MACRO_CONCAT(id, __COUNTER__))

std::optional<ErrorChain *> SemanticVisitor::provisionFwdDeclSymbols(BismuthParser::CompilationUnitContext *ctx)
{
    // Enter initial scope
    for (auto e : ctx->defs)
    {
        // Wastes a bit of memory in allocating type even for duplicates
        std::optional<std::pair<std::string, const Type *>> opt = defineTypeCase<std::optional<std::pair<std::string, const Type *>>>(
            e,
            [](BismuthParser::DefineFunctionContext *ctx) -> std::pair<std::string, const Type *>{
                return {
                    ctx->name->getText(),
                    ctx->genericTemplate() ? (const Type *) new TypeTemplate() : (const Type *) new TypeFunc()
                };
            },

            [](BismuthParser::DefineProgramContext *ctx) -> std::pair<std::string, const Type *>{
                return {
                    ctx->name->getText(),
                    ctx->genericTemplate() ? (const Type *) new TypeTemplate() : (const Type *) new TypeProgram()
                };
            },

            [](BismuthParser::DefineStructContext *ctx) -> std::pair<std::string, const Type *>{
                std::string name = ctx->name->getText();
                return {
                    name,
                    ctx->genericTemplate() ? (const Type *) new TypeTemplate() : (const Type *) new TypeStruct()
                };
            },

            [](BismuthParser::DefineEnumContext *ctx) -> std::pair<std::string, const Type *>{
                std::string name = ctx->name->getText();
                return {
                    name,
                    ctx->genericTemplate() ? (const Type *) new TypeTemplate() : (const Type *) new TypeSum()
                };
            },

            [this](BismuthParser::DefineTypeContext * ctx){
                errorHandler.addCompilerError(ctx->getStart(), "Unhandled case in identifying definitions");
                return std::nullopt;
            }

        );
        if(!opt) continue;

        std::string id = opt.value().first;

        DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(
            DefinitionSymbol*,
            defSym,
            stmgr->addDefinition(VisibilityModifier::PUBLIC, id, opt.value().second, true),
            ctx,
            "Unsupported redeclaration of " + id);

        symBindings.bind(e, defSym);
    }

    // auto templateTy = new TypeTemplate();
    // auto symOpt = stmgr->addDefinition(
    //     VisibilityModifier::PUBLIC,
    //     "push_back",
    //     templateTy,
    //     true).value(); // FIXME: BAD OPT

    // auto genericTy = new TypeGeneric(false, "T");
    // auto templateInfo = TemplateInfo({
    //     std::make_pair("T", genericTy)
    // });

    // TypeFunc * funcTy = new TypeFunc();

    // templateTy->define(templateInfo, funcTy);

    // funcTy->setInvoke(
    //     {new TypeDynArray(genericTy), genericTy },
    //     Types::UNIT
    // );

    // // TLambdaConstNode *lam = std::get<TLambdaConstNode *>(lamOpt);

    // TDefineTemplateNode * templateNode = new TDefineTemplateNode(
    //     symOpt,
    //     templateTy,
    //     lam,
    //     ctx->getStart()
    // );

    return std::nullopt;
}

std::optional<ErrorChain *> SemanticVisitor::defineFwdDeclSymbols(BismuthParser::CompilationUnitContext *ctx)
{
    // Enter initial scope
    // stmgr->enterScope(StopType::NONE);

    // TODO: refactor to use defineAndGetSymbolFor for each, then can remove defineTypeCase and replace with single function call.
    for (auto e : ctx->defs)
    {
        // Wastes a bit of memory in allocating type even for duplicates
        defineAndGetSymbolFor(e, VisibilityModifier::PUBLIC);
    }

    return std::nullopt;
}

std::variant<std::vector<DefinitionNode *>, ErrorChain *> SemanticVisitor::visitFwdDecls(BismuthParser::CompilationUnitContext *ctx)
{
    std::vector<DefinitionNode *> defs;
    for (auto e : ctx->defs)
    {
        // Note: re-applying template symbols happens in each visitor for now!
        if (BismuthParser::DefineProgramContext * progCtx = dynamic_cast<BismuthParser::DefineProgramContext *>(e))
        {
            std::variant<DefinitionNode *, ErrorChain *> progOpt = visitCtx(progCtx);

            if (ErrorChain **e = std::get_if<ErrorChain *>(&progOpt))
            {
                return (*e)->addError(ctx->getStart(), "Failed to type check program");
            }

            defs.push_back(std::get<DefinitionNode *>(progOpt));
        }
        else if (BismuthParser::DefineFunctionContext * fnCtx = dynamic_cast<BismuthParser::DefineFunctionContext *>(e))
        {
            std::variant<DefinitionNode *, ErrorChain *> opt = visitCtx(fnCtx);

            if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
            {
                return (*e)->addError(ctx->getStart(), "Failed to type check function");
            }

            defs.push_back(std::get<DefinitionNode *>(opt));
        }
        else if (BismuthParser::DefineStructContext * structCtx = dynamic_cast<BismuthParser::DefineStructContext *>(e))
        {
            std::variant<DefinitionNode *, ErrorChain *> opt = visitCtx(structCtx);

            if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
            {
                return (*e)->addError(ctx->getStart(), "Failed to type check function");
            }

            defs.push_back(std::get<DefinitionNode *>(opt));
        }
        else if (BismuthParser::DefineEnumContext * enumCtx = dynamic_cast<BismuthParser::DefineEnumContext *>(e))
        {
            std::variant<DefinitionNode *, ErrorChain *> opt = visitCtx(enumCtx);

            if (ErrorChain **e = std::get_if<ErrorChain *>(&opt))
            {
                return (*e)->addError(ctx->getStart(), "Failed to type check function");
            }

            defs.push_back(std::get<DefinitionNode *>(opt));
        }
    }

    return defs;
}

std::variant<std::vector<TExternNode *>, ErrorChain *> SemanticVisitor::visitExterns(BismuthParser::CompilationUnitContext *ctx)
{
    std::vector<TExternNode *> externs;

    // Visit externs first; they will report any errors if they have any.
    for (auto e : ctx->externs)
    {
        std::variant<TExternNode *, ErrorChain *> extOpt = this->visitCtx(e);

        if (ErrorChain **e = std::get_if<ErrorChain *>(&extOpt))
        {
            return (*e)->addError(ctx->getStart(), "Error in definition of extern");
        }
        TExternNode *node = std::get<TExternNode *>(extOpt);

        if (flags & CompilerFlags::DEMO_MODE)
        {
            if (!(node->getSymbol()->getScopedIdentifier() == "printf" && node->getType()->getParamTypes().size() == 1 && node->getType()->getParamTypes().at(0)->isSubtype(Types::DYN_STR) && node->getType()->getReturnType()->isSubtype(Types::DYN_INT) && node->getType()->isVariadic()))
            {
                errorHandler.addError(e->getStart(), "Unsupported extern; only 'extern int func printf(str, ...)' supported in demo mode");
            }
        }

        externs.push_back(node);
    }

    return externs;
}

std::optional<ErrorChain *> SemanticVisitor::postCUVisitChecks(BismuthParser::CompilationUnitContext *ctx)
{
    /*******************************************
     * Extra checks depending on compiler flags
     *******************************************/

    bool demoMode = flags & CompilerFlags::DEMO_MODE;

    std::optional<Symbol *> opt = stmgr->lookup("main");
    if (opt)
    {
        Symbol *sym = opt.value();
        std::optional<const TypeProgram *> progOpt = type_cast<TypeProgram>(sym->getType());
        if (progOpt)
        {
            const TypeProgram *inv = progOpt.value();
            // FIXME: DO SUBTYPING BETTER!
            if (!(TypeChannel(inv->getProtocol())).isSubtype(new TypeChannel(new ProtocolSequence(false, {new ProtocolSend(false, Types::DYN_INT)}))))
            {
                errorHandler.addError(ctx->getStart(), "In demo mode, 'main' must recognize a channel of protocol -int, not " + inv->getProtocol()->toString(toStringMode));
            }
            else
            {
                sym->getIdentifier()->promoteToGlobalMain();
            }
        }
        else if(demoMode)
        {
            errorHandler.addError(ctx->getStart(), "When compiling in demo mode identifier 'main' must be defined as 'prog main :: * : -int' (the entry point)");
        }
    }
    else if(demoMode)
    {
        errorHandler.addError(ctx->getStart(), "When compiling in demo mode, 'prog main :: * : -int' (the entry point) must be defined");
    }

    // Should be impossible
    if(!stmgr->getCurrentScope())
    {
        return errorHandler.addCompilerError(ctx->getStart(), "No current scope for the compilation unit!");
    }

    Scope * scope = stmgr->getCurrentScope().value();

    // Try to unify symbols (really needed for things like nums wherein
    // we know what types are possible to infer, so we can just
    // pick one if the code doesn't make it clear which variant we need)
    for(Symbol * sym : scope->getSymbols(SymbolLookupFlags::UNINFERRED_TYPE))
    {
        // Should always be inferrable
        if(const TypeInfer * inf = dynamic_cast<const TypeInfer *>(sym->getType()))
        {
            inf->unify();
        }
    }

    std::vector<Symbol *> unInf = scope->getSymbols(SymbolLookupFlags::UNINFERRED_TYPE);

    // If there are any uninferred symbols, then add it as an error as we won't be able to resolve them
    // due to the var leaving the scope
    if (unInf.size() > 0)
    {
        std::ostringstream details;

        for (auto e : unInf)
        {
            details << e->toString() << "; ";
        }

        errorHandler.addError(ctx->getStart(), "230 Uninferred types in context: " + details.str());
    }
    return std::nullopt;
}

std::variant<TCompilationUnitNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::CompilationUnitContext *ctx, std::vector<std::string> steps)
{
    auto phasedVisitor0 = phasedVisit(ctx, steps);
    if (ErrorChain **e = std::get_if<ErrorChain *>(&phasedVisitor0))
    {
        return (*e);
    }
    auto phasedVisitor1 = std::get<std::function<std::variant<
            std::function<std::function<std::variant<TCompilationUnitNode *, ErrorChain *>()>()>,
            ErrorChain *
    >()>>(phasedVisitor0);

    auto res1 = phasedVisitor1();
    if (ErrorChain **e = std::get_if<ErrorChain *>(&res1))
    {
        return (*e);
    }
    auto phasedVisitor2 = std::get<
                std::function<
                    std::function<
                        std::variant<TCompilationUnitNode *,
                        ErrorChain *>()>
                    ()>>(res1);

    auto res3 = phasedVisitor2()();
    if (ErrorChain **e = std::get_if<ErrorChain *>(&res3))
    {
        return (*e);
    }

    return std::get<TCompilationUnitNode *>(res3);

    // (
    //     res: (() ->
    //         (
    //             res: (() ->
    //                     (() -> (res: TCompilationUnitNode * + err: ErrorChain *))
    //             )
    //             +
    //             err: ErrorChain *
    //         )
    //     )
    //     +
    //     err: ErrorChain *
    // )
}

std::variant<
    SemanticVisitor::ImportPhaseClosure,
    ErrorChain *
>
SemanticVisitor::phasedVisit(BismuthParser::CompilationUnitContext *ctx, std::vector<std::string> steps)
{
    // Enter initial scope
    Scope * cuScope;
    if(steps.empty())
    {
        stmgr->enterScope(StopType::NONE); // FIXME: DO better, we need to ensure we are branching out of global scope!
        cuScope = stmgr->getCurrentScope().value();
    }
    else
    {
        std::optional<Scope *> scopeOpt = stmgr->getOrProvisionScope(steps, VisibilityModifier::PUBLIC);

        if(!scopeOpt)
        {
            return errorHandler.addCompilerError(ctx->getStart(), "Failed to enter scope for compilation unit!");
        }

        cuScope = scopeOpt.value();

        stmgr->enterScope(cuScope);
    }

    provisionFwdDeclSymbols(ctx);

    return [this, ctx, cuScope]() ->
        std::variant<
            std::function<std::function<std::variant<TCompilationUnitNode *, ErrorChain *>()>()>,
            ErrorChain *
    >{
        stmgr->enterScope(cuScope);
        for(auto i : ctx->imports)
        {
            std::optional<ErrorChain *> errOpt = this->TVisitImportStatement(i);
            if(errOpt)
                return errOpt.value();
        }

        auto externsOpt = visitExterns(ctx);
        if (ErrorChain **e = std::get_if<ErrorChain *>(&externsOpt))
        {
            return (*e);
        }
        std::vector<TExternNode *> externs = std::get<std::vector<TExternNode *>>(externsOpt);

        return [this, ctx, cuScope, externs]() -> std::function<std::variant<TCompilationUnitNode *, ErrorChain *>()>{
            stmgr->enterScope(cuScope);
            // FIXME: ERROR CHECK!
            defineFwdDeclSymbols(ctx);

            return [this, ctx, cuScope, externs]() -> std::variant<TCompilationUnitNode *, ErrorChain *> {
                stmgr->enterScope(cuScope);
                auto nodeOpts = visitFwdDecls(ctx);

                if (ErrorChain **e = std::get_if<ErrorChain *>(&nodeOpts))
                {
                    return (*e);
                }

                std::vector<DefinitionNode *> defs = std::get<std::vector<DefinitionNode *>>(nodeOpts);

                // Visit the statements contained in the unit

                auto errOpt = postCUVisitChecks(ctx);
                if(errOpt) return errOpt.value();

                // Return UNDEFINED as this should be viewed as a statement and not something assignable
                return new TCompilationUnitNode(externs, defs);
            };
        };
    };
}

std::variant<TInvocationNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::CallExprContext *ctx)
{
    // Need RValue
    std::variant<TypedNode *, ErrorChain *> typeOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->expr->accept(this));
    if (ErrorChain **e = std::get_if<ErrorChain *>(&typeOpt))
    {
        return (*e)->addError(ctx->getStart(), "Unable to generate expression to invoke");
    }

    TypedNode *tn = std::get<TypedNode *>(typeOpt);

    std::optional<const TypeFunc *> funcTyOpt = type_cast<TypeFunc>(tn->getType());
    if (!funcTyOpt)
        return errorHandler.addError(ctx->getStart(), "Can only invoke functions, not " + tn->getType()->toString(toStringMode));

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
        (!funcTy->isVariadic() && fnParams.size() != ctx->inv_args()->args.size()) || (funcTy->isVariadic() && fnParams.size() > ctx->inv_args()->args.size()))
    {
        std::ostringstream errorMsg;
        errorMsg << "Expected " << fnParams.size() << " argument(s), but got " << ctx->inv_args()->args.size();
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
    for (unsigned int i = 0; i < ctx->inv_args()->args.size(); i++)
    {
        // Get the type of the current argument
        std::variant<TypedNode *, ErrorChain *> providedOpt = anyOpt2VarError<TypedNode>(errorHandler, ctx->inv_args()->args.at(i)->accept(this));

        if (ErrorChain **e = std::get_if<ErrorChain *>(&providedOpt))
        {
            return (*e)->addError(ctx->inv_args()->args.at(i)->getStart(), "Unable to generate argument");
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
                errorHandler.addError(ctx->getStart(), "Cannot provide " + providedType->toString(toStringMode) + " to a function");
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
            errorMsg << "Argument " << i << " expected " << expectedType->toString(toStringMode) << " but got " << providedType->toString(toStringMode);

            errorHandler.addError(ctx->getStart(), errorMsg.str());
        }
    }

    return new TInvocationNode(tn, args, actualTypes, ctx->getStart());
}

std::variant<TypedNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::ExpressionStatementContext *ctx)
{
    if(!dynamic_cast<BismuthParser::CallExprContext *>(ctx->expression()))
        return errorHandler.addError(ctx->getStart(), "Using an expression as statement in a manner that results in dead code.");

    std::variant<TypedNode *, ErrorChain *> opt = anyOpt2VarError<TypedNode>(errorHandler, ctx->expression()->accept(this));

    if (TypedNode **n = std::get_if<TypedNode *>(&opt))
    {
        if((*n)->getType()->isLinear())
            return errorHandler.addError(ctx->getStart(), "Evaluation of expression would result in introducing a linear resource that is impossible to use."); // TODO: better error.
    }

    return opt;
}

/**
 * @brief Visits a program definition
 *
 * @param ctx The parser rule context
 * @return TProgramDefNode * if successful, ErrorChain * if error
 */
std::variant<DefinitionNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::DefineProgramContext *ctx)
{
    DEFINE_OR_PROPAGATE_VARIANT(
        DefinitionSymbol *,
        defSym,
        defineAndGetSymbolFor(ctx),
        ctx
    );

    auto generateProgram = [this, ctx, defSym](const TypeProgram * progType) -> std::variant<DefinitionNode *, ErrorChain *> {
        std::string funcId = ctx->name->getText();
        // Lookup the function in the current scope and prevent re-declarations

        // Add the symbol to the stmgr and enter the scope.
        if(!stmgr->getCurrentScope()) return errorHandler.addCompilerError(ctx->getStart(), "STManager does not have a current scope!");
        Scope * orig = stmgr->getCurrentScope().value();
        stmgr->enterScope(defSym->getInnerScope());

        Symbol *channelSymbol = stmgr->addSymbol(ctx->channelName->getText(), new TypeChannel(progType->getProtocol()->getCopy()), false).value();
        // In the new scope. set our return type. We use @RETURN as it is not a valid symbol the programmer could write in the language
        stmgr->addSymbol("@EXIT", Types::UNIT, false);

        // Safe visit the program block without creating a new scope (as we are managing the scope)
        DEFINE_OR_PROPAGATE_VARIANT_WMSG(TBlockNode *, blk, this->safeVisitBlock(ctx->block(), false), ctx, "Failed to save visit block");

        // If we have a return type, make sure that we return as the last statement in the FUNC. The type of the return is managed when we visited it.
        // if (ty && (ctx->block()->stmts.size() == 0 || !dynamic_cast<BismuthParser::ReturnStatementContext *>(ctx->block()->stmts.at(ctx->block()->stmts.size() - 1))))
        // {
        //     errorHandler.addError(ctx->getStart(), "Function must end in return statement");
        // }

        // Safe exit the scope.
        safeExitScope(ctx);
        stmgr->enterScope(orig);

        return new TProgramDefNode(defSym, channelSymbol, blk, progType, ctx->getStart());
    };

    if(const TypeTemplate * templateTy = dynamic_cast<const TypeTemplate*>(defSym->getType()))
    {
        if(!templateTy->getValueType())
            return errorHandler.addCompilerError(ctx->getStart(), "template type does not have value type to template");

        if(const TypeProgram * progTy = dynamic_cast<const TypeProgram *>(templateTy->getValueType().value()))
        {
           DEFINE_OR_PROPAGATE_VARIANT(DefinitionNode*, programNode, generateProgram(progTy), ctx);

            return new TDefineTemplateNode(
                defSym,
                templateTy,
                programNode,
                ctx->getStart()
            );
        }
    }
    else if (const TypeProgram *progType = dynamic_cast<const TypeProgram *>(defSym->getType()))
    {
        return generateProgram(progType);
    }

    return errorHandler.addError(ctx->getStart(), "Cannot execute " + defSym->toString());
}

std::variant<DefinitionNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::DefineFunctionContext *ctx)
{
    DEFINE_OR_PROPAGATE_VARIANT(DefinitionSymbol *, defSym, defineAndGetSymbolFor(ctx), ctx);
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(TLambdaConstNode *, lam, visitCtx(ctx->lam, defSym), ctx, "Unable to generate lambda");

    /*
     *  Check if this is a template or not, and handle it accordingly
     */
    if(const TypeTemplate * templateTy = dynamic_cast<const TypeTemplate *>(defSym->getType()))
    {
        TDefineTemplateNode * templateNode = new TDefineTemplateNode(
            defSym,
            templateTy,
            lam,
            ctx->getStart()
        );

        return templateNode;
    }

    return lam;
}

std::variant<TInitProductNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::InitProductContext *ctx)
{
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(const Type *, ty, visitPathType(ctx->path()), ctx, "Unknown type.");
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(
        const TypeStruct *,
        product,
        type_cast<TypeStruct>(ty),
        ctx,
       "Cannot initialize non-product type: " + ty->toString(toStringMode));

    std::vector<std::pair<std::string, const Type *>> elements = product->getElements();
    if (elements.size() != ctx->exprs.size())
    {
        std::ostringstream errorMsg;
        errorMsg << "Initialization of " << ty->toString(toStringMode) << " expected " << elements.size() << " argument(s), but got " << ctx->exprs.size();
        return errorHandler.addError(ctx->getStart(), errorMsg.str());
    }

    std::vector<TypedNode *> n;

    bool isValid = true;
    {
        unsigned int i = 0;

        for (auto eleItr : elements)
        {
           DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, tn, anyOpt2VarError<TypedNode>(errorHandler, ctx->exprs.at(i)->accept(this)), ctx->exprs.at(i), "Unable to generate expression");

            n.push_back(tn);
            const Type *providedType = tn->getType();

            if (providedType->isNotSubtype(eleItr.second))
            {
                std::ostringstream errorMsg;
                errorMsg << "Product init. argument " << i << " provided to " << ty->toString(toStringMode) << " expected " << eleItr.second->toString(toStringMode) << " but got " << providedType->toString(toStringMode);

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

std::variant<TArrayRValue *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::ArrayExpressionContext *ctx)
{
    const Type * innerTy = new TypeInfer();

    vector<TypedNode *> elements;

    for(auto eleCtx : ctx->elements)
    {
        DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, tn,  anyOpt2VarError<TypedNode>(errorHandler, eleCtx->accept(this)), eleCtx, "Unable to generate expression");

        elements.push_back(tn);

        const Type *providedType = tn->getType();

        if (providedType->isNotSubtype(innerTy))
        {
            // PLAN: handle errors better!
            return errorHandler.addError(ctx->getStart(), "Expected " + innerTy->toString(toStringMode) + " but got " + providedType->toString(toStringMode));
        }

    }

    return new TArrayRValue(new TypeArray(innerTy, elements.size()), elements, ctx->getStart());
}

std::variant<TInitBoxNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::InitBoxContext *ctx)
{
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(const Type *, storeType, anyOpt2VarError<const Type>(errorHandler, ctx->ty->accept(this)), ctx, "Failed to generate the type to store in the box");

    if (storeType->isLinear())
    {
        return errorHandler.addError(ctx->ty->getStart(), "Cannot create a box with a linear type!");
    }

    // TODO: METHODIZE WITH INVOKE AND INIT PRODUCT?
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, tn, anyOpt2VarError<TypedNode>(errorHandler, ctx->expr->accept(this)), ctx->expr, "Unable to generate expression in init box");

    const Type *providedType = tn->getType();

    if (providedType->isLinear())
    {
        return errorHandler.addError(ctx->expr->getStart(), "Cannot create a box with a linear type!");
    }

    if (providedType->isNotSubtype(storeType))
    {
        std::ostringstream errorMsg;
        errorMsg << "Initialize box expected " << storeType->toString(toStringMode) << ", but got " << providedType->toString(toStringMode) << "";

        return errorHandler.addError(ctx->getStart(), errorMsg.str());
    }

    return new TInitBoxNode(new TypeBox(storeType), tn, ctx->getStart());
}

std::variant<TypedNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::ArrayAccessContext *ctx, bool is_rvalue)
{
    /*
     * Check that we are provided an int for the index.
     */
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, idxExpr, anyOpt2VarError<TypedNode>(errorHandler, ctx->index->accept(this)), ctx->index, "Unable to type check array access index");

    const Type *idxType = idxExpr->getType();
    if (idxType->isNotSubtype({Types::DYN_INT, Types::DYN_U32}, InferenceMode::QUERY))
    {
        return errorHandler.addError(ctx->getStart(), "Array access index expected type u32 but got " + idxType->toString(toStringMode));
    }

    /*
     * Look up the symbol and check that it is defined.
     */

    DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, node, visitLValue(ctx->expr), ctx->expr, "Cannot access value from undefined array: " + ctx->expr->getText());

    /*
     * Check that the symbol is of array type.
     */
    if (type_cast<TypeArray>(node->getType()))
    {
        return new TArrayAccessNode(node, idxExpr, is_rvalue, ctx->getStart());
    }
    else if(type_cast<TypeDynArray>(node->getType()))
    {
        return new TDynArrayAccessNode(node, idxExpr, is_rvalue, ctx->getStart());
    }

    // Report error
    return errorHandler.addError(ctx->getStart(), "Cannot use array access on non-array expression " + ctx->expr->getText() + " : " + node->getType()->toString(toStringMode));
}

// std::variant<TypedNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::LValueContext *ctx)
// {
//     // Check if we are a var or an array
//     if (ctx->var)
//     {
//         return TNVariantCast<TFieldAccessNode>(visitCtx(ctx->var, false));
//     }
//     else if (ctx->deref)
//     {
//         return TNVariantCast<TDerefBoxNode>(visitCtx(ctx->deref, false));
//     }

//     /*
//      * As we are not a var, we must be an array access, so we must visit that context.
//      */
//     return (this->visitCtx(ctx->array, false));
// }

std::variant<TypedNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::IConstExprContext *ctx)
{

    auto tyModifier = ctx->i->ty ? ctx->i->ty->getText() : "i32";
    std::optional<std::pair<int, std::string>> datOpt = [ctx]() -> std::optional<std::pair<int, std::string>> {
        if(ctx->i->DEC_LITERAL())
            return std::make_optional<std::pair<int, std::string>>({10, ctx->i->DEC_LITERAL()->getText()});
        if(ctx->i->HEX_LITERAL())
            return std::make_optional<std::pair<int, std::string>>({16, ctx->i->HEX_LITERAL()->getText().substr(2)});
        if(ctx->i->BIN_LITERAL())
            return std::make_optional<std::pair<int, std::string>>({2, ctx->i->BIN_LITERAL()->getText().substr(2)});

        return std::nullopt;
    }();

    if(!datOpt) {
        return errorHandler.addCompilerError(ctx->getStart(), "Unable to sort integer into dec, hex, or bin.");
    }

    std::pair<int, std::string> dat = datOpt.value();

    // FIXME: FORWARD BASE!
    if(!ctx->i->ty)
    {
        return TNVariantCast<TNumConstExprNode>(new TNumConstExprNode(dat.second, ctx->getStart()));
    }

    // https://en.cppreference.com/w/cpp/string/basic_string/stol

    std::size_t pos{};
    int base = dat.first;
    std::string text = dat.second;

    if(tyModifier == "i32")
    {
        // TODO: what happens if these fail? Ie, what if num too large?
        int32_t val = static_cast<int32_t>(std::stol(text, &pos, base));
        return TNVariantCast<TInt32ConstExprNode>(new TInt32ConstExprNode(val, ctx->getStart()));
    }
    else if(tyModifier == "u32")
    {
        uint32_t val = static_cast<uint32_t>(std::stoul(text, &pos, base));
        return TNVariantCast<TIntU32ConstExprNode>(new TIntU32ConstExprNode(val, ctx->getStart()));
    }
    else if(tyModifier == "i64")
    {
        int64_t val = static_cast<int64_t>(std::stoll(text, &pos, base));
        return TNVariantCast<TInt64ConstExprNode>(new TInt64ConstExprNode(val, ctx->getStart()));
    }
    else if(tyModifier == "u64")
    {
        uint64_t val = static_cast<uint64_t>(std::stoull(text, &pos, base));
        return TNVariantCast<TIntU64ConstExprNode>(new TIntU64ConstExprNode(val, ctx->getStart()));
    }

    return errorHandler.addCompilerError(ctx->i->getStart(), "Unknown integer type modifier: " + ctx->i->ty->getText());
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
 * @brief Type check Unary Expressions
 *
 * @param ctx The UnaryExpressionContext to type check
 * @return const Type* Returns the type of the inner expression if valid; UNDEFINED otherwise.
 */
std::variant<TUnaryExprNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::UnaryExprContext *ctx)
{
    // Lookup the inner type
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, innerNode, anyOpt2VarError<TypedNode>(errorHandler, ctx->ex->accept(this)), ctx->ex, "Failed to generate unary expression");
    const Type *innerType = innerNode->getType();

    // Switch on the operation so we can ensure that the type and operation are compatable.
    switch (ctx->op->getType())
    {
    case BismuthParser::MINUS:
        if (innerType->isNotSubtype({Types::DYN_INT, Types::DYN_I64}, InferenceMode::QUERY))
        {
            return errorHandler.addError(ctx->getStart(), "Signed number (e.g., int or i64) expected in unary minus, but got " + innerType->toString(toStringMode));
        }
        return new TUnaryExprNode(UNARY_MINUS, innerNode, ctx->getStart());
    case BismuthParser::BIT_NOT:
        if (innerType->isNotSubtype({Types::DYN_INT, Types::DYN_I64, Types::DYN_U32, Types::DYN_U64}, InferenceMode::QUERY))
        {
            return errorHandler.addError(ctx->getStart(), "Signed number (e.g., int or i64) expected in unary not, but got " + innerType->toString(toStringMode));
        }
        return new TUnaryExprNode(UNARY_BIT_NOT, innerNode, ctx->getStart());
    case BismuthParser::NOT:
        if (innerType->isNotSubtype(Types::DYN_BOOL))
        {
            return errorHandler.addError(ctx->getStart(), "boolean expected in unary not, but got " + innerType->toString(toStringMode));
        }
        return new TUnaryExprNode(UNARY_NOT, innerNode, ctx->getStart());
    }

    return errorHandler.addCompilerError(ctx->getStart(), "Unknown operator: " + ctx->op->getText());
}

/**
 * @brief Visits a Binary Arithmetic Expression ensuring LHS and RHS are int.
 *
 * @param ctx The BinaryArithExprContext to Visit
 * @return const Type* int if lhs and rhs are int; UNDEFINED otherwise.
 */
std::variant<TBinaryArithNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::BinaryArithExprContext *ctx)
{
    // TODO: Allow operations on sumtype as syntactic sugar if
    // operation allowed on all elements in the sum?

    std::string opStr = ctx->BIT_AND()  ? "&"
                      : ctx->BIT_OR()   ? "|"
                      : ctx->BIT_XOR()  ? "^"
                      : (ctx->shiftOp() && ctx->shiftOp()->GREATER().size() == 3) ? ">>>"
                    //   : ctx->LOG_RSH()  ? ">>>"
                      : (ctx->shiftOp() && ctx->shiftOp()->GREATER().size() == 2) ? ">>"
                    //   : ctx->ARITH_RSH()? ">>"
                      : (ctx->shiftOp() && ctx->shiftOp()->LESS().size() == 2) ? "<<"
                    //   : ctx->LSH()      ? "<<"
                      : ctx->MULTIPLY() ? "*"
                      : ctx->DIVIDE()   ? "/"
                      : ctx->MOD()      ? "%"
                      : ctx->PLUS()     ? "+"
                                        : "-";

    DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, left, anyOpt2VarError<TypedNode>(errorHandler, ctx->left->accept(this)), ctx, "Unable to generate LHS of Binary Arithmetic Expression");
    if (left->getType()->isNotSubtype({Types::DYN_INT, Types::DYN_U32, Types::DYN_I64, Types::DYN_U64}, InferenceMode::QUERY))
    {
        return errorHandler.addError(ctx->getStart(), "Cannot apply " + opStr + " to " + left->getType()->toString(toStringMode));
    }

    DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, right, anyOpt2VarError<TypedNode>(errorHandler, ctx->right->accept(this)), ctx, "Unable to generate RHS of binary arithmetic expression");
    if (right->getType()->isNotSubtype(left->getType())) // TODO: PROBABLY WONT WORK IF LEFT DONE VIA INFERENCE
    {
        return errorHandler.addError(ctx->getStart(), "Operator " + opStr + " cannot be applied between " + left->getType()->toString(toStringMode) + " and " + right->getType()->toString(toStringMode) + ". Expected " + left->getType()->toString(toStringMode) + " " + opStr + " " + left->getType()->toString(toStringMode));
    }

    return new TBinaryArithNode(
        ctx->BIT_AND()  ? BIT_AND
      : ctx->BIT_OR()   ? BIT_OR
      : ctx->BIT_XOR()  ? BIT_XOR
      : (ctx->shiftOp() && ctx->shiftOp()->GREATER().size() == 3) ? BINARY_LOG_RIGHT_SHIFT
      : (ctx->shiftOp() && ctx->shiftOp()->GREATER().size() == 2) ? BINARY_ARITH_RIGHT_SHIFT
      : (ctx->shiftOp() && ctx->shiftOp()->LESS().size() == 2) ? BINARY_LEFT_SHIFT
      : ctx->MULTIPLY() ? BINARY_ARITH_MULT
      : ctx->DIVIDE()   ? BINARY_ARITH_DIV
      : ctx->MOD()      ? BINARY_ARITH_MOD
      : ctx->PLUS()     ? BINARY_ARITH_PLUS
      : BINARY_ARITH_MINUS,
        left,
        right,
        ctx->getStart());
}

std::variant<TEqExprNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::EqExprContext *ctx)
{
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, rhs, anyOpt2VarError<TypedNode>(errorHandler, ctx->right->accept(this)), ctx, "Unable to generate RHS");
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, lhs, anyOpt2VarError<TypedNode>(errorHandler, ctx->left->accept(this)), ctx, "Unable to generate LHS");

    if (rhs->getType()->isNotSubtype(lhs->getType()))
    {
        errorHandler.addError(ctx->getStart(), "Both sides of '=' must have the same type");
    }

    // FIXME: SHOULD WE BE ABLE TO DO EQUALITY ON POINTERS, STRUCTS, ETC?
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
 * @brief Visits a Logical And Expression ensuring LHS and RHS are boolean.
 *
 * @param ctx The LogAndExprContext to Visit
 * @return const Type* boolean if lhs and rhs are boolean; UNDEFINED otherwise.
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

    for (BismuthParser::ExpressionContext *ectx : toGen)
    {
        DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, node, anyOpt2VarError<TypedNode>(errorHandler, ectx->accept(this)), ectx, "Unable to generate expression in logical and");
        const Type *type = node->getType();

        if (type->isNotSubtype(Types::DYN_BOOL))
        {
            errorHandler.addError(ectx->getStart(), "boolean expression expected, but was " + type->toString(toStringMode));
        }
        else
        {
            nodes.push_back(node);
        }
    }
    return new TLogAndExprNode(nodes, ctx->getStart());
}

/**
 * @brief Visits a Logical Or Expression ensuring LHS and RHS are boolean.
 *
 * @param ctx The LogOrExprContext to Visit
 * @return const Type* boolean if lhs and rhs are boolean; UNDEFINED otherwise.
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
        DEFINE_OR_PROPAGATE_VARIANT(TypedNode *, node, anyOpt2VarError<TypedNode>(errorHandler, e->accept(this)), ctx);

        const Type *type = node->getType();

        if (type->isNotSubtype(Types::DYN_BOOL))
        {
            errorHandler.addError(e->getStart(), "Expected boolean but got " + type->toString(toStringMode));
        }
        else
        {
            nodes.push_back(node);
        }
    }
    return new TLogOrExprNode(nodes, ctx->getStart());
}

std::variant<TPathNode *, ErrorChain*> SemanticVisitor::visitCtx(BismuthParser::PathContext * ctx, bool is_rvalue)
{
    DEFINE_OR_PROPAGATE_VARIANT(const Type *, ty, visitPathType(ctx), ctx);
    return new TPathNode(ctx->getStart(), ty,  is_rvalue); //a.size() == 0 ? is_rvalue : false);
}

/**
 * @brief Visits a FieldAccessExprContext---Currently limited to array lengths
 *
 * @param ctx the FieldAccessExprContext to visit
 * @return const Type* int if correctly used to test array length; UNDEFINED if any errors.
 */
std::variant<TFieldAccessNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::FieldAccessExprContext *ctx, bool is_rvalue)
{
    // FIXME: but it may need to be an rvalue sometimes!
    DEFINE_OR_PROPAGATE_VARIANT(TypedNode *, expr, this->visitLValue(ctx->expr), ctx);

    const Type *ty = expr->getType();
    std::vector<std::pair<std::string, const Type *>> a;

    for (unsigned int i = 0; i < ctx->fields.size(); i++)
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
                return errorHandler.addError(ctx->getStart(), "Cannot access " + fieldName + " on " + ty->toString(toStringMode));
            }
        }
        else if (i + 1 == ctx->fields.size() && (type_cast<TypeArray>(ty) || type_cast<TypeDynArray>(ty)) && ctx->fields.at(i)->getText() == "length")
        {
            a.push_back({"length",
                         Types::DYN_U32});

            break; // Shouldn't be needed, but is here anyways
        }
        else if (i + 1 == ctx->fields.size() && (type_cast<TypeDynArray>(ty)) && ctx->fields.at(i)->getText() == "capacity")
        {
            a.push_back({"capacity",
                         Types::DYN_U32});

            break; // Shouldn't be needed, but is here anyways
        }
        else
        {
            return errorHandler.addError(ctx->getStart(), "Cannot access " + fieldName + " on " + ty->toString(toStringMode));
        }
    }
    return new TFieldAccessNode(ctx->getStart(), expr, is_rvalue, a);
}

std::variant<TIdentifier *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::IdentifierExprContext * ctx, bool is_rvalue)
{
    // Determine the type of the expression we are visiting
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, stmgr->lookup(ctx->VARIABLE()->getText()), ctx, "Undefined variable reference: " + ctx->VARIABLE()->getText());

    if (sym->getType()->isLinear())
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

    return new TIdentifier(ctx->getStart(), sym, is_rvalue);
}

std::variant<TDerefBoxNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::DerefContext *ctx, bool is_rvalue)
{
  DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, expr, anyOpt2VarError<TypedNode>(errorHandler, ctx->expr->accept(this)), ctx, "Unable to type check dereference expression");

  const Type *exprType = expr->getType();
  DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const TypeBox *, box, type_cast<TypeBox>(exprType), ctx,"Dereference expected Box<T> but got " + exprType->toString(toStringMode));

  return new TDerefBoxNode(box, expr, is_rvalue, ctx->getStart());
}

// Passthrough to expression
std::variant<TypedNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::ParenExprContext *ctx)
{
    DEFINE_OR_PROPAGATE_VARIANT(TypedNode *, opt, anyOpt2VarError<TypedNode>(errorHandler, ctx->ex->accept(this)), ctx);
    return opt;
}

/**
 * @brief Visits a BinaryRelational Expression ensuring both lhs and rhs are int.
 *
 * @param ctx The BinaryRelExprContext to visit.
 * @return const Type* boolean if lhs and rhs int; UNDEFINED otherwise.
 */
std::variant<TBinaryRelNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::BinaryRelExprContext *ctx)
{
    std::string opStr = ctx->LESS() ? "<"
                      : ctx->LESS_EQ() ? "<="
                      : ctx->GREATER()   ? ">"
                      : ">=";

    DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, left, anyOpt2VarError<TypedNode>(errorHandler, ctx->left->accept(this)), ctx, "Unable to type check LHS of binary relation expression");

    if (left->getType()->isNotSubtype({Types::DYN_INT, Types::DYN_U32, Types::DYN_I64, Types::DYN_U64}, InferenceMode::QUERY))
    {
        return errorHandler.addError(ctx->getStart(), "Cannot apply " + opStr + " to " + left->getType()->toString(toStringMode) + ". Expected a number.");
    }

    DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, right, anyOpt2VarError<TypedNode>(errorHandler, ctx->right->accept(this)), ctx, "Unable to type check RHS of binary relation expression");

    if (right->getType()->isNotSubtype(left->getType()))
    {
        return errorHandler.addError(ctx->getStart(), "Operator " + opStr + " cannot be applied between " + left->getType()->toString(toStringMode) + " and " + right->getType()->toString(toStringMode) + ". Expected " + left->getType()->toString(toStringMode) + " " + opStr + " " + left->getType()->toString(toStringMode));
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
    return errorHandler.addCompilerError(ctx->getStart(), "(Allegedly) impossible visit to SelectAlternativeContext");
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
    // bool isValid = true;

    ParameterListNode paramList;

    for (auto param : ctx->params)
    {
        std::string name = param->name->getText();

        auto prevUse = map.find(name);
        if (prevUse != map.end())
        {
            errorHandler.addError(param->getStart(), "Re-use of previously defined parameter " + name);
            // isValid = false;
            return std::nullopt;
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
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(const Type *, paramType, anyOpt2VarError<const Type>(errorHandler, ctx->ty->accept(this)), ctx, "Failed to generate case type");
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

    if (stmgr->isBound(id))
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
        return (*e)->addError(ctx->getStart(), "Error generating return type");
    }

    const Type *retType = std::get<const Type *>(retTypeOpt);

    std::vector<const Type *> paramTypes;

    for (ParameterNode param : tyOpt.value())
    {
        paramTypes.push_back(param.type);
    }

    TypeFunc * funcTy = new TypeFunc(
            paramTypes,
            retType,
            variadic
    );

    std::optional<DefinitionSymbol *> symOpt = stmgr->addDefinition(
        VisibilityModifier::PUBLIC_LINK,
        id,
        funcTy,
        true
    );

    if(!symOpt) return errorHandler.addCompilerError(ctx->getStart(), "Could not add definition for " + id);
    Symbol * sym = symOpt.value();

    // TODO: Promoting externs to global is a bit hacky and probably
    // allows them to be referenced by other files (eg  <foo>::<some extern>)
    // which *probably* shouldn't be allowed. Instead, make
    // a separate ExternSymbol class which we would use instead.
    // This would also be more accurate as externs wouldn't belong to a scope per say
    sym->getIdentifier()->promoteToGlobal();

    TExternNode *node = new TExternNode(symOpt.value(), funcTy, ctx->getStart());

    return node;
};

std::variant<TAssignNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::AssignmentStatementContext *ctx)
{
    // This one is the update one!

    // Determine the expected type
    DEFINE_OR_PROPAGATE_VARIANT(TypedNode *, var, this->visitLValue(ctx->to), ctx);

    // Determine the expression type
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, expr, anyOpt2VarError<TypedNode>(errorHandler, ctx->a->accept(this)), ctx, "Unable to type check assignment");
    const Type *exprType = expr->getType();

    if (exprType->isGuarded())
    {
        return errorHandler.addError(ctx->getStart(), "Cannot assign guarded resource to another identifier");
    }

    const Type *type = var->getType();

    // Make sure that the types are compatible. Inference automatically managed here.
    if (exprType->isNotSubtype(type))
    {
        return errorHandler.addError(ctx->getStart(), "Assignment statement expected " + type->toString(toStringMode) + " but got " + exprType->toString(toStringMode));
    }

    return new TAssignNode(var, expr, ctx->getStart());
}

std::variant<TVarDeclNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::VariableDeclarationContext *ctx)
{
  std::vector<AssignmentNode *> a;

  for (auto e : ctx->assignments)
  {
    // Needs to happen in case we have vars
    // const Type *assignType = this->visitCtx(ctx->typeOrVar());

    DEFINE_OR_PROPAGATE_VARIANT_WMSG(const Type *, assignType, this->visitCtx(ctx->typeOrVar()), ctx, "Error generating assign type");
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

      // if (!(e->a))
      //     return errorHandler.addCodegenError(ctx->getStart(), "FALSE!");
      std::optional<TypedNode *> exprOpt = std::nullopt;
      if (e->a)
      {
        std::variant<TypedNode *, ErrorChain *> exprOptO = anyOpt2VarError<TypedNode>(errorHandler, e->a->accept(this));
        if (ErrorChain **e = std::get_if<ErrorChain *>(&exprOptO))
        {
          return (*e)->addError(ctx->getStart(), "Unable to type check assignment");
        }

        exprOpt = std::get<TypedNode *>(exprOptO);
      }

      const Type *newAssignType = origType->getCopy(); // this->visitCtx(ctx->typeOrVar()); // Needed to ensure vars get their own inf type
      const Type *exprType = exprOpt ? exprOpt.value()->getType() : newAssignType;

      if (exprType->isGuarded()) // TODO: Use syntactic sugar to separate out declarations from assignments. Also could use it to make select statements work better!
      {
        return errorHandler.addError(ctx->getStart(), "Cannot assign guarded resource to another identifier");
      }

      // Note: This automatically performs checks to prevent issues with setting VAR = VAR
      if (e->a && exprType->isNotSubtype(newAssignType))
      {
        return errorHandler.addError(e->getStart(), "Expression of type " + exprType->toString(toStringMode) + " cannot be assigned to " + newAssignType->toString(toStringMode));
      }

      const Type *newExprType = (dynamic_cast<const TypeInfer *>(newAssignType) && e->a) ? exprType : newAssignType;

      // Done with exprType for later type inference purposes
      // .value() should be safe as we already checked name uniqueness
      // FIXME: isGlobalScope probably doesnt work anymore with paths and namespaces. Revise it!
      Symbol * symbol = stmgr->addSymbol(id, newExprType, stmgr->isGlobalScope()).value();

      // This is somewhat inefficient to have to repeat this for every single value, but needed if for linear resources and if we aren't purely FP.
      a.push_back(new AssignmentNode({symbol}, exprOpt)); // FIXME: Does assignment node need to be list?
    }
  }
  return new TVarDeclNode(a, ctx->getStart());
}

std::variant<TMatchStatementNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::MatchStatementContext *ctx)
{
  DEFINE_OR_PROPAGATE_VARIANT(TypedNode *, cond, anyOpt2VarError<TypedNode>(errorHandler, ctx->check->ex->accept(this)), ctx);
  DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const TypeSum*, sumType, type_cast<TypeSum>(cond->getType()), ctx->check, "Can only case on Sum Types, not " + cond->getType()->toString(toStringMode));

  std::set<const Type *> foundCaseTypes = {};
  // TODO: Maybe make so these can return values?

  auto branchOpt = checkBranch<BismuthParser::MatchStatementContext, BismuthParser::MatchAlternativeContext, std::pair<Symbol *, TypedNode *>>(
    ctx,
    [this, ctx](std::deque<DeepRestData *> *rest) {
      for (auto b : ctx->matchAlternative())
      {
        bindRestData(b->eval, rest);
      }
    },
    ctx->matchAlternative(),
    false,
    [](std::pair<Symbol *, TypedNode *> pair) -> TypedNode * { return pair.second; },
    [this, ctx, sumType, &foundCaseTypes](BismuthParser::MatchAlternativeContext *altCtx) -> std::variant<std::pair<Symbol *, TypedNode *>, ErrorChain *>
    {
      DEFINE_OR_PROPAGATE_VARIANT_WMSG(const Type *, caseType, anyOpt2VarError<const Type>(errorHandler, altCtx->type()->accept(this)), ctx, "Failed to generate case type");

      if (!sumType->contains(caseType))
      {
        errorHandler.addError(
          altCtx->type()->getStart(),
          "Impossible case for " + sumType->toString(toStringMode) + " to act as " + caseType->toString(toStringMode)
        );
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
      DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, local, stmgr->addSymbol(altCtx->name->getText(), caseType, false), altCtx, "Duplicate case name"); // TODO: may provide duplicate errors to prior checks!

      std::variant<TypedNode *, ErrorChain *> tnOpt = anyOpt2VarError<TypedNode>(errorHandler, altCtx->eval->accept(this));
      // this->safeExitScope(altCtx);
      stmgr->exitScope();

      if (ErrorChain **e = std::get_if<ErrorChain *>(&tnOpt))
      {
        return (*e)->addErrorAt(ctx->getStart());
      }

      if (dynamic_cast<BismuthParser::TypeDefContext *>(altCtx->eval) ||
          dynamic_cast<BismuthParser::VarDeclStatementContext *>(altCtx->eval))
      {
        return errorHandler.addError(altCtx->getStart(), "Dead code: definition as select alternative");
      }

      TypedNode *ans = std::get<TypedNode *>(tnOpt);

      return std::make_pair(local, ans);
    });

  if (foundCaseTypes.size() != sumType->getCases().size())
  {
    return errorHandler.addError(ctx->getStart(), "Match statement did not cover all cases needed for " + sumType->toString(toStringMode));
  }

  if (ErrorChain **e = std::get_if<ErrorChain *>(&branchOpt))
  {
    return (*e)->addError(ctx->getStart(), "Failed to type check match statement");
  }

  ConditionalData<std::pair<Symbol *, TypedNode *>> dat = std::get<ConditionalData<std::pair<Symbol *, TypedNode *>>>(branchOpt);
  return new TMatchStatementNode(sumType, cond, dat.cases, dat.post, ctx->getStart());
}

/**
 * @brief Type checks a Loops
 *
 * @param ctx The LoopStatementContext to type check
 * @return const Type* UNDEFINED as this is a statement.
 */
std::variant<TWhileLoopNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::ProgramLoopContext *ctx)
{
    std::variant<TypedNode *, ErrorChain *> checkOpt;

    stmgr->enterNonlinearScope(
        [this, &checkOpt, ctx](){
            checkOpt = this->visitCtx(ctx->check); // Visiting check will make sure we have a boolean condition
        }
    );

    if (ErrorChain **e = std::get_if<ErrorChain *>(&checkOpt))
    {
        return (*e)->addErrorAt(ctx->getStart());
    }

    stmgr->guard();

    std::variant<TBlockNode *, ErrorChain *> blkOpt = safeVisitBlock(ctx->block(), true);

    if (ErrorChain **e = std::get_if<ErrorChain *>(&blkOpt))
    {
        return (*e)->addErrorAt(ctx->getStart());
    }

    if (!stmgr->unguard())
    {
        return errorHandler.addError(ctx->getStart(), "Could not unguard resources in scope");
    }

    // Return UNDEFINED because this is a statement, and UNDEFINED cannot be assigned to anything
    return new TWhileLoopNode(std::get<TypedNode *>(checkOpt), std::get<TBlockNode *>(blkOpt), ctx->getStart());
}

// Note: this returns a TBlockNode instead of a while loop directly as we need to have multiple statements, and we use desugaring
std::variant<TBlockNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::ForStatementContext *ctx)
{
    std::vector<TypedNode *> exprs;

    // Should this return errors early? Probably not?
    if(ctx->decl)
    {
        std::variant<TVarDeclNode *, ErrorChain *> declOpt = this->visitCtx(ctx->decl);
        if(std::holds_alternative<TVarDeclNode *>(declOpt))
            exprs.push_back(std::get<TVarDeclNode *>(declOpt));
    }
    else
    {
        std::variant<TAssignNode *, ErrorChain *> assignOpt = this->visitCtx(ctx->assign);
        if(std::holds_alternative<TAssignNode *>(assignOpt))
            exprs.push_back(std::get<TAssignNode *>(assignOpt));
    }

    // PLAN: Update to handle better (along with while loops)
    std::variant<TypedNode *, ErrorChain *> checkOpt;
    stmgr->enterNonlinearScope(
        [this, &checkOpt, ctx](){
            checkOpt = this->visitCtx(ctx->check); // Visiting check will make sure we have a boolean condition
        }
    );

    if (ErrorChain **e = std::get_if<ErrorChain *>(&checkOpt))
    {
        return (*e)->addError(ctx->getStart(), "Failed to typecheck condition in for loop");
    }

    stmgr->guard();

    std::variant<TBlockNode *, ErrorChain *> blkOpt = safeVisit(
        {ctx->block(), ctx->expr},
        true);
        //ctx->block(), true);

    if (ErrorChain **e = std::get_if<ErrorChain *>(&blkOpt))
    {
        return (*e)->addErrorAt(ctx->getStart());
    }

    if (!stmgr->unguard())
    {
        return errorHandler.addError(ctx->getStart(), "Could not unguard resources in scope");
    }

    exprs.push_back(new TWhileLoopNode(std::get<TypedNode *>(checkOpt), std::get<TBlockNode *>(blkOpt), ctx->getStart()));

    // Return UNDEFINED because this is a statement, and UNDEFINED cannot be assigned to anything
    return new TBlockNode(exprs, ctx->getStart());
}

std::variant<TConditionalStatementNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::ConditionalStatementContext *ctx)
{
    // Automatically handles checking that we have a valid condition
    std::variant<TypedNode *, ErrorChain *> condOpt = this->visitCtx(ctx->check);

    if (ErrorChain **e = std::get_if<ErrorChain *>(&condOpt))
    {
        return (*e)->addErrorAt(ctx->getStart());
    }
    std::vector<BismuthParser::BlockContext *> blksCtx = {ctx->trueBlk};
    if (ctx->falseBlk)
        blksCtx.push_back(ctx->falseBlk);

    auto branchOpt = checkBranch<BismuthParser::ConditionalStatementContext, BismuthParser::BlockContext, TBlockNode *>(
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
        [](TBlockNode * n) -> TypedNode * { return n; },
        [this](BismuthParser::BlockContext *blk) -> std::variant<TBlockNode *, ErrorChain *>
        {
            // Scopes automatically handled, have to use false bc we can't have the block automatically scope otherwise we might throw an error before we get the chance to realize that we use all linear resources.
            return this->safeVisitBlock(blk, false);
        });

    if (ErrorChain **e = std::get_if<ErrorChain *>(&branchOpt))
        return errorHandler.addError(ctx->getStart(), "Failed to generate one or more cases in if statement");

    ConditionalData<TBlockNode *> dat = std::get<ConditionalData<TBlockNode *>>(branchOpt);

    if (ctx->falseBlk)
    {
        return new TConditionalStatementNode(ctx->getStart(), std::get<TypedNode *>(condOpt), dat.cases.at(0), dat.post, dat.cases.at(1));
    }

    return new TConditionalStatementNode(ctx->getStart(), std::get<TypedNode *>(condOpt), dat.cases.at(0), dat.post);
}

std::variant<TSelectStatementNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::SelectStatementContext *ctx)
{
    // Define a recursive fn which takes ctx->cases as arg, then processes first vs rest?
    if (ctx->cases.size() < 1)
    {
        return errorHandler.addError(ctx->getStart(), "Select statement expected at least one alternative, but was given 0!");
    }

    unsigned int case_count = 0;

    auto branchOpt = checkBranch<BismuthParser::SelectStatementContext, BismuthParser::SelectAlternativeContext, TSelectAlternativeNode *>(
        ctx,
        [this, ctx](std::deque<DeepRestData *> *rest) {
            for (auto b : ctx->cases)
            {
                bindRestData(b->eval, rest);
            }
        },
        ctx->cases,
        true,
        [](TSelectAlternativeNode * n) -> TypedNode * { return n; },
        [this, ctx, &case_count](BismuthParser::SelectAlternativeContext *e) -> std::variant<TSelectAlternativeNode *, ErrorChain *>
        {
            /*
             *  Just make sure that we don't try to functions and stuff in a select as that doesn't make sense (and would cause codegen issues as it stands).
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
                    return (*e)->addErrorAt(ctx->getStart()); // FIXME: THIS IS AN INEFFICIENT MANNER TO ENSURE LINEAR RESOURCES ARE USED CORRECTLY DUE TO CASE EXPRESSIONS
                }
            }

            case_count++;

            DEFINE_OR_PROPAGATE_VARIANT(TypedNode *, check, anyOpt2VarError<TypedNode>(errorHandler, e->check->accept(this)), ctx);
            const Type *checkType = check->getType();

            if (checkType->isNotSubtype(Types::DYN_BOOL))
            {
                return errorHandler.addError(ctx->getStart(), "Select alternative expected boolean but got " + checkType->toString(toStringMode));
            }

            stmgr->enterScope(StopType::NONE); // For safe exit + scoping... //FIXME: verify...

            DEFINE_OR_PROPAGATE_VARIANT(TypedNode *, eval, anyOpt2VarError<TypedNode>(errorHandler, e->eval->accept(this)), ctx);

            return new TSelectAlternativeNode(check, eval, ctx->getStart());
        });

    if (ErrorChain **e = std::get_if<ErrorChain *>(&branchOpt))
    {
        return (*e)->addError(ctx->getStart(), "Failed to type check select statement");
    }

    ConditionalData<TSelectAlternativeNode *> dat = std::get<ConditionalData<TSelectAlternativeNode *>>(branchOpt);
    return new TSelectStatementNode(ctx->getStart(), dat.cases, dat.post);
}

std::variant<TReturnNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::ReturnStatementContext *ctx)
{
    /*
     * Lookup the @RETURN symbol which can ONLY be defined by entering a function
     */
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, stmgr->lookup("@RETURN"), ctx, "Cannot use return outside of a function");

    // If the return statement has an expression...
    if (ctx->expression())
    {
        // Evaluate the expression type
        DEFINE_OR_PROPAGATE_VARIANT(TypedNode *, val, anyOpt2VarError<TypedNode>(errorHandler, ctx->expression()->accept(this)), ctx);

        const Type *valType = val->getType();

        // Check return type.
        // TODO: improve error as if the return type is Unit, then simply return; is valid.
        if (valType->isNotSubtype(sym->getType()))
        {
            return errorHandler.addError(ctx->getStart(), "Expected return type of " + sym->getType()->toString(toStringMode) + " but got " + valType->toString(toStringMode));
        }

        std::pair<const Type *, TypedNode *> ans = {sym->getType(), val};

        return new TReturnNode(ctx->getStart(), ans);
    }

    // We do not have an expression to return, so make sure that the return type is also a BOT.
    if (sym->getType()->isSubtype(Types::UNIT))
    {
        return new TReturnNode(ctx->getStart());
    }

    return errorHandler.addError(ctx->getStart(), "Expected to return a " + sym->getType()->toString(toStringMode) + " but received nothing");
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

std::variant<TLambdaConstNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::LambdaConstExprContext *ctx, std::optional<DefinitionSymbol *> symOpt)
{
    // FIXME: technically could be bad opt access, but should never happen
    DefinitionSymbol * sym = lazy_value_or<DefinitionSymbol *>(symOpt,
        [this]() {return stmgr->addAnonymousDefinition("lambda", new TypeFunc()).value(); });

    if(!stmgr->getCurrentScope()) return errorHandler.addCompilerError(ctx->getStart(), "No current scope in type checking of lambda constexpr!");

    Scope * origScope = stmgr->getCurrentScope().value();
    stmgr->enterScope(sym->getInnerScope()); // FIXME: WITH EARLY RETURNS, WE MIGHT NOT PROPERLY EXIT SCOPES!

    std::optional<ParameterListNode> paramTypeOpt = visitCtx(ctx->parameterList());

    if (!paramTypeOpt)
        return errorHandler.addError(ctx->getStart(), "1716");

    ParameterListNode params = paramTypeOpt.value();
    std::vector<Symbol *> ps;

    std::variant<const Type *, ErrorChain *> retTypeOpt = ctx->ret ? anyOpt2VarError<const Type>(errorHandler, ctx->ret->accept(this))
                                                                   : (const Type *)Types::UNIT;

    if (ErrorChain **e = std::get_if<ErrorChain *>(&retTypeOpt))
    {
        return (*e)->addError(ctx->getStart(), "Error generating return type");
    }

    const Type *retType = std::get<const Type *>(retTypeOpt);

    std::vector<const Type *> paramTypes;

    for (auto p : params)
    {
        paramTypes.push_back(p.type);
    }

    // While we could get a template, only actually have to define if we are visiting it for the first time -> why not refactor this out?
    if(const TypeFunc * funcTy = dynamic_cast<const TypeFunc *>(sym->getType()))
    {
        if(!funcTy->isDefined())
            funcTy->setInvoke(paramTypes, retType, false);
    }

    stmgr->addSymbol("@RETURN", retType, false); // Because of inserting a global stop, this will always go through

    for (ParameterNode param : params)
    {
        ps.push_back(
            stmgr->addSymbol(param.name, param.type, false).value() // TODO: should this be error checked? Based on global stop it should be fine unless duplicates.. but that's likely already caught?
        );
    }

    DEFINE_OR_PROPAGATE_VARIANT(TBlockNode *, blk, this->safeVisitBlock(ctx->block(), false), ctx);

    // If we have a return type, make sure that we return as the last statement in the FUNC. The type of the return is managed when we visited it.
    if (!TypedAST::endsInReturn(*blk))
    {
        if(retType->isNotSubtype(Types::UNIT))
        {
            errorHandler.addError(ctx->getStart(), "Expected function to return type of " + retType->toString(toStringMode) + "; however, no return instruction was provided.");
        }
        else
        {
            // One of the first bits of syntactic sugar in bismuth!
            blk->exprs.push_back(new TReturnNode(nullptr, std::nullopt));
        }
    }
    safeExitScope(ctx);
    stmgr->enterScope(origScope);

    return new TLambdaConstNode(sym, ps, retType, blk, ctx->getStart());
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
            // TODO: ALLOW MULTIPLE ERRORS/BRANCHING?
            return (*e)->addError(ctx->getStart(), "Failed to generate parameter type");
        }

        const Type *type = std::get<const Type *>(typeOpt);

        params.push_back(type);
    }

    std::variant<const Type *, ErrorChain *> returnTypeOpt = anyOpt2VarError<const Type>(errorHandler, ctx->returnType->accept(this));

    if (ErrorChain **e = std::get_if<ErrorChain *>(&returnTypeOpt))
    {
        return (*e)->addError(ctx->getStart(), "Failed to generate return type");
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
        DEFINE_OR_PROPAGATE_VARIANT_WMSG(const Type *, caseType, anyOpt2VarError<const Type>(errorHandler, e->accept(this)), ctx, "Failed to generate case type");

        if (caseType->isLinear())
        {
            return errorHandler.addError(e->getStart(), "Unable to store linear type, " + caseType->toString(toStringMode) + ", in non-linear container");
        }

        cases.insert(caseType);
    }

    if (cases.size() != ctx->type().size())
    {
        return errorHandler.addError(ctx->getStart(), "Duplicate arguments to enum type, or failed to generate types");
    }

    return new TypeSum(cases);
}

std::variant<std::vector<const Type *>, ErrorChain *> SemanticVisitor::TvisitGenericSpecifier(BismuthParser::GenericSpecifierContext *ctx)
{
    std::vector<const Type *> innerTys;

    for(auto a : ctx->subst)
    {
        DEFINE_OR_PROPAGATE_VARIANT_WMSG(const Type *, sub, anyOpt2VarError<const Type>(errorHandler, a->accept(this)), a, "Failed to generate type in template application");
        innerTys.push_back(sub);
    }

    return innerTys;
}

std::variant<const Type *, ErrorChain *>
SemanticVisitor::visitCtx(BismuthParser::TemplatedTypeContext *ctx)
{
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(const Type *, main, anyOpt2VarError<const Type>(errorHandler, ctx->ty->accept(this)), ctx, "Failed to generate case type");

    if(const TypeTemplate * templateTy = dynamic_cast<const TypeTemplate *>(main))
    {
        DEFINE_OR_PROPAGATE_VARIANT(std::vector<const Type *>, innerTys, TvisitGenericSpecifier(ctx->genericSpecifier()), ctx);
        DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const Type*, applied, templateTy->canApplyTemplate(innerTys), ctx, "Failed to apply template. FIXME: Improve this error message!!");
        return applied;
    }

    return errorHandler.addError(ctx->getStart(), "Expected a template type but got: " + main->toString(toStringMode));
}

std::variant<DefinitionNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::DefineEnumContext *ctx)
{
    DEFINE_OR_PROPAGATE_VARIANT(DefinitionSymbol *, sym, defineAndGetSymbolFor(ctx), ctx);

    if (const TypeTemplate *templateTy = dynamic_cast<const TypeTemplate *>(sym->getType()))
    {
        if(!templateTy->getValueType()) return errorHandler.addCompilerError(ctx->getStart(), "Template has no value type");

        const TypeSum * sumTy = dynamic_cast<const TypeSum *>(templateTy->getValueType().value());
        if(!sumTy) return errorHandler.addCompilerError(ctx->getStart(), "Template Type Value expected to be sum, but got: " + templateTy->getValueType().value()->toString(toStringMode));

        if(!stmgr->getCurrentScope()) return errorHandler.addCompilerError(ctx->getStart(), "No current scope in type checking of enum definition!");

        Scope * origScope = stmgr->getCurrentScope().value();
        stmgr->enterScope(sym->getInnerScope());
        TDefineEnumNode * enumNode = new TDefineEnumNode(
            sym,
            sumTy,
            ctx->getStart());

        TDefineTemplateNode * templateNode = new TDefineTemplateNode(
            sym,
            templateTy,
            enumNode,
            ctx->getStart()
        );

        stmgr->enterScope(origScope);

        return templateNode;
    }

    const TypeSum * sumTy = dynamic_cast<const TypeSum *>(sym->getType());
    if(!sumTy) return errorHandler.addCompilerError(ctx->getStart(), "Expected sum type but got: " + sym->getType()->toString(toStringMode));

    TDefineEnumNode * enumNode = new TDefineEnumNode(
        sym,
        sumTy,
        ctx->getStart());

    return enumNode;
}

std::variant<DefinitionNode *, ErrorChain *> SemanticVisitor::visitCtx(BismuthParser::DefineStructContext *ctx)
{
    DEFINE_OR_PROPAGATE_VARIANT(DefinitionSymbol *, sym, defineAndGetSymbolFor(ctx), ctx);

    if (const TypeTemplate *templateTy = dynamic_cast<const TypeTemplate *>(sym->getType()))
    {

        if(!templateTy->getValueType()) return errorHandler.addCompilerError(ctx->getStart(), "Template type does not have a value type");

        const TypeStruct * structTy = dynamic_cast<const TypeStruct *>(templateTy->getValueType().value());
        if(!structTy) return errorHandler.addCompilerError(ctx->getStart(), "Expected template to be applied to a struct type but got: " + templateTy->getValueType().value()->toString(toStringMode));

        TDefineStructNode * structNode = new TDefineStructNode(
            sym,
            structTy,
            ctx->getStart());

        TDefineTemplateNode * templateNode = new TDefineTemplateNode(
            sym,
            templateTy,
            structNode,
            ctx->getStart()
        );

        return templateNode;
    }

    const TypeStruct * structTy = dynamic_cast<const TypeStruct *>(sym->getType());
    if(!structTy) return errorHandler.addCompilerError(ctx->getStart(), "Expected Struct but got: " + sym->getType()->toString(toStringMode));

    TDefineStructNode * structNode = new TDefineStructNode(
        sym,
        structTy,
        ctx->getStart());

    return structNode;
}

std::variant<const Type *, ErrorChain *>
SemanticVisitor::visitPathType(BismuthParser::PathContext *ctx)
{
    if(ctx->eles.size() == 1)
    {
        auto pCtx = ctx->eles.at(0);

        std::string name = pCtx->id->getText();

        DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, stmgr->lookup(name), pCtx, "Undefined type: " + name); // TODO: address inefficiency in var decl where this is called multiple times

        if (!sym->getType() || !sym->isDefinition())
        {
            return errorHandler.addError(pCtx->getStart(), "Cannot use: " + name + " as a type");
        }

        if(!pCtx->genericSpecifier())
        {
          return sym->getType();
        }

        // Copied from templated Type
        if(const TypeTemplate * templateTy = dynamic_cast<const TypeTemplate *>(sym->getType()))
        {
          DEFINE_OR_PROPAGATE_VARIANT(std::vector<const Type *>, innerTys, TvisitGenericSpecifier(pCtx->genericSpecifier()), ctx);
          DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const Type*, applied, templateTy->canApplyTemplate(innerTys), ctx, "Failed to apply template. FIXME: Improve this error message!!");
          return applied;
        }
        return errorHandler.addError(pCtx->genericSpecifier()->getStart(), "Cannot apply generic to non-template type: " + sym->getType()->toString(toStringMode));
    }

    // FIXME: add visibility modifiers & checks!
    Scope * lookupScope = stmgr->getGlobalScope();
    const Type * pathVar;

    for(auto pCtx : ctx->eles)
    {
        std::string stepId = pCtx->id->getText();
        DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, lookupScope->lookup(stepId), pCtx, "Could not find " + stepId + " in " + lookupScope->getIdentifier()->getFullyQualifiedName());
        // if (sym->getType()->isLinear())
        // {
        //     if (!is_rvalue)
        //     {
        //         errorHandler.addError(ctx->getStart(), "Cannot redefine linear variable!");
        //     }

        //     if (!stmgr->removeSymbol(sym))
        //     {
        //         errorHandler.addError(ctx->getStart(), "Failed to unbind local var: " + sym->toString());
        //     }
        // }

        // if(!dynamic_cast<const DefinitionSymbol *>(sym))
        // {
        //     return errorHandler.addError(pCtx->getStart(), sym->toString() + " is not a definition."); // TODO: better error!
        // }

        // if(!dynamic_cast<const NameableType *>(sym->getType()))
        // {
        //     return errorHandler.addError(pCtx->getStart(), sym->toString() + " expected a named type."); // TODO: better error!
        // }

        // TODO: macro to allow above style syntax, and get casted result here?
        // Or, to allow an inline function to return something, and have that apply
        // within the bounds of the outside fn

        auto defSym = dynamic_cast<const DefinitionSymbol *>(sym);
        if(!defSym)
            return errorHandler.addError(
                pCtx->getStart(),
                sym->toString() + " is not a definition."); // TODO: better error! Can only use this on definitions. For instance variables, try .

        const Type * symType = sym->getType();
        auto nt = dynamic_cast<const NameableType *>(symType);
        if(!nt)
            return errorHandler.addError(
                pCtx->getStart(),
                sym->toString() + " expected a named type."); // TODO: better error!

        if(pCtx->genericSpecifier())
        {
            if(const TypeTemplate * templateTy = dynamic_cast<const TypeTemplate *>(symType))
            {
                DEFINE_OR_PROPAGATE_VARIANT(std::vector<const Type *>, innerTys, TvisitGenericSpecifier(pCtx->genericSpecifier()), ctx);
                DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const NameableType *, applied, templateTy->canApplyTemplate(innerTys), pCtx, "Failed to apply template. FIXME: Improve this error message!!");
                symType = applied;
                pathVar = applied;
            }
            else
            {
                return errorHandler.addError(pCtx->genericSpecifier()->getStart(), "Cannot apply generic to non-template type: " + symType->toString(toStringMode));
            }
        }
        else
        {
            pathVar = nt;
        }
        lookupScope = defSym->getInnerScope();
    }

    return pathVar;
}

std::variant<const TypeDynArray *, ErrorChain*>
SemanticVisitor::visitCtx(BismuthParser::DynArrayTypeContext * ctx)
{
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(const Type *, inner, anyOpt2VarError<const Type>(errorHandler, ctx->ty->accept(this)), ctx, "Failed to generate array type");

    return new TypeDynArray(inner);
}

std::variant<const TypeArray *, ErrorChain *>
SemanticVisitor::visitCtx(BismuthParser::ArrayTypeContext *ctx)
{
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(const Type *, inner, anyOpt2VarError<const Type>(errorHandler, ctx->ty->accept(this)), ctx, "Failed to generate array type");

    // Undefined type errors handled below

    int len = std::stoi(ctx->len->getText()); //FIXME: CHANGE, SHOULD DO BETTER EXPRESSION PARSING + BETTER GRAMMAR!

    if (len < 1)
    {
        errorHandler.addError(ctx->getStart(), "Cannot initialize array with a size of less than 1!");
    }

    return new TypeArray(inner, len);
}

std::variant<const Type *, ErrorChain *>
SemanticVisitor::visitCtx(BismuthParser::BaseTypeContext *ctx)
{
    if (ctx->TYPE_INT() || ctx->TYPE_I32())
    {
        return (const Type *)Types::DYN_INT;
    }
    else if(ctx->TYPE_U32())
    {
        return (const Type *)Types::DYN_U32;
    }
    else if(ctx->TYPE_I64())
    {
        return (const Type *)Types::DYN_I64;
    }
    else if(ctx->TYPE_U64())
    {
        return (const Type *)Types::DYN_U64;
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
    return visitProtocolAsChannel(ctx->proto);
}

std::variant<const TypeBox *, ErrorChain *>
SemanticVisitor::visitCtx(BismuthParser::BoxTypeContext *ctx)
{
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(const Type *, inner, anyOpt2VarError<const Type>(errorHandler, ctx->ty->accept(this)), ctx, "Failed to generate type inside box");

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
    std::variant<const ProtocolSequence *, ErrorChain *> protoOpt = protoVisitor->visitProto(ctx->proto); // TODO: how to prevent calls to bad overrides? ie, ProtocolVisitor visit type ctx?
    delete protoVisitor;

    if (ErrorChain **e = std::get_if<ErrorChain *>(&protoOpt))
    {
        return (*e)->addError(ctx->getStart(), "Failed to generate protocol type for program");
    }

    // TODO: perhaps change these to smart pointers?
    const ProtocolSequence *proto = std::get<const ProtocolSequence *>(protoOpt);

    return new TypeProgram(proto);
}

std::variant<TProgramSendNode *, ErrorChain *> SemanticVisitor::TvisitProgramSend(BismuthParser::ProgramSendContext *ctx)
{
    std::string id = ctx->channel->getText();
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, stmgr->lookup(id), ctx, "Could not find channel: " + id);
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const TypeChannel *, channel, type_cast<TypeChannel>(sym->getType()), ctx, "Cannot send on non-channel: " + id);

    DEFINE_OR_PROPAGATE_VARIANT(TypedNode *, tn, anyOpt2VarError<TypedNode>(errorHandler, ctx->expr->accept(this)), ctx);
    const Type *ty = tn->getType();

    bool inCloseable = channel->getProtocol()->isInCloseable();
    std::optional<const Type *> canSend = channel->getProtocol()->send(ty);

    if (!canSend)
    {
      return errorHandler.addError(ctx->getStart(), "Failed to send " + ty->toString(toStringMode) + " over channel " + sym->toString());
    }
    return new TProgramSendNode(sym, inCloseable, tn, canSend.value(), ctx->getStart());
}

std::variant<TProgramRecvNode *, ErrorChain *> SemanticVisitor::TvisitAssignableRecv(BismuthParser::AssignableRecvContext *ctx)
{
    std::string id = ctx->channel->getText();
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, stmgr->lookup(id), ctx, "Could not find channel: " + id);
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const TypeChannel *, channel, type_cast<TypeChannel>(sym->getType()), ctx, "Cannot recv on non-channel: " + id);

    bool closeState = channel->getProtocol()->isInCloseable();
    std::optional<RecvMetadata> ty = channel->getProtocol()->recv();
    if (!ty)
    {
      return errorHandler.addError(ctx->getStart(), "Failed to recv over channel: " + sym->toString());
    }

    return new TProgramRecvNode(sym, ty.value(), closeState, ctx->getStart());
}

std::variant<TProgramIsPresetNode *, ErrorChain *> SemanticVisitor::TvisitAssignableIsPresent(BismuthParser::AssignableIsPresentContext *ctx)
{
    std::string id = ctx->channel->getText();
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, stmgr->lookup(id), ctx, "Could not find channel: " + id);
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const TypeChannel *, channel, type_cast<TypeChannel>(sym->getType()), ctx, "Cannot recv on non-channel: " + id);

    bool isInCloseable = channel->getProtocol()->isInCloseable();
    if (!channel->getProtocol()->isOC(true))
    {
      return errorHandler.addError(ctx->getStart(), "is_present() could not be applied to " + sym->toString() + " as it is not a ! loop");
    }

    return new TProgramIsPresetNode(sym, isInCloseable, ctx->getStart());
}

std::variant<TChannelCaseStatementNode *, ErrorChain *> SemanticVisitor::TvisitProgramCase(BismuthParser::ProgramCaseContext *ctx)
{
    std::string id = ctx->channel->getText();
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, stmgr->lookup(id), ctx, "Could not find channel: " + id);
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const TypeChannel *, channel, type_cast<TypeChannel>(sym->getType()), ctx, "Cannot case on non-channel: " + id);
    std::set<
      std::pair<
        std::variant<const ProtocolSequence *, std::string>,
        BismuthParser::StatementContext *>, ProtocolCompareInv> optsI = {};

    for (auto alt : ctx->protoAlternative())
    {
      if(alt->lbl)
      {
        optsI.insert({
          alt->lbl->getText(),
          alt->eval
        });
        continue;
      }

      // TODO: SEEMS WRONG TO PERFORM ERROR CHECKS HERE AS, BY DEF, COULD ONLY ERROR SHOULD HIGHER-LEVEL PROTO FAIL, BUT I GUESS MAYBE USEFUL IF WE LATER ADD INF!
      ProtocolVisitor *protoVisitor = new ProtocolVisitor(errorHandler, this);
      std::variant<const ProtocolSequence *, ErrorChain *> protoOpt = protoVisitor->visitProto(alt->check); // TODO: how to prevent calls to bad overrides? ie, ProtocolVisitor visit type ctx?
      delete protoVisitor;

      if (ErrorChain **e = std::get_if<ErrorChain *>(&protoOpt))
      {
        return (*e)->addError(ctx->getStart(), "Failed to generate protocol type in channel case statement");
      }

      const ProtocolSequence *a = std::get<const ProtocolSequence *>(protoOpt);

      optsI.insert({
        a->getInverse(), alt->eval}); // Double inverses to ensure order same for both sides (server & client)
    }

    std::vector<std::variant<const ProtocolSequence *, std::string>> branchSequences = {};
    std::vector<BismuthParser::StatementContext *> alternatives = {};

    for (auto itr : optsI)
    {
      std::variant<const ProtocolSequence *, std::string> tmp = itr.first;
      if(std::holds_alternative<const ProtocolSequence *>(tmp))
      {
        branchSequences.push_back(
          std::get<const ProtocolSequence *>(tmp)->getInverse()
        );
        // TODO: delete std::get<const ProtocolSequence *>(tmp)?
      }
      else
      {
        branchSequences.push_back(tmp);
      }
      // branchSequences.push_back(itr.first->getInverse());
      alternatives.push_back(itr.second);
    }

    bool isInCloseable = channel->getProtocol()->isInCloseable();

    if(ctx->protoElse() && !isInCloseable)
    {
      return errorHandler.addError(ctx->protoElse()->getStart(), "Dead code - An else block can only apply to choices in a lossy protocol");
    }

    if(isInCloseable && !ctx->protoElse()) // TODO: see about removing this when we can?
    {
      return errorHandler.addError(ctx->getStart(), "Currently, an else block is required for cases in lossy protocols");
    }

    optional<CaseMetadata> metaOpts = channel->getProtocol()->caseAnalysis(branchSequences);

    if (!metaOpts) // Ensures we have all cases. //TODO: LOG THESE ERRORS BETTER
    {
      return errorHandler.addError(ctx->getStart(), "Failed to case over channel: " + sym->toString());
    }

    CaseMetadata meta = metaOpts.value();

    vector<const ProtocolSequence *> fullSequences = meta.fullSequences; //fullSeqOpts.value();

    if(ctx->protoElse())
    {
      fullSequences.push_back(meta.rest);
      alternatives.push_back(ctx->protoElse()->statement());
    }

    unsigned int branch = 0;
    auto branchOpt = checkBranch<BismuthParser::ProgramCaseContext, BismuthParser::StatementContext, TypedNode *>(
      ctx,
      [this, ctx](std::deque<DeepRestData *> *rest) {
        for (auto b : ctx->protoAlternative())
        {
          bindRestData(b->eval, rest);
        }
      },
      alternatives,
      false, // TODO: make this (isInCloseable && !ctx->protoElse()). The challenge is making it follow the correct protocol in the case when it skips to rest as we don't currently support skipping ops like that
      [](TypedNode * n) -> TypedNode * { return n; },
      [this, fullSequences, &branch, id](BismuthParser::StatementContext *alt) -> std::variant<TypedNode *, ErrorChain *>
      {
        const ProtocolSequence *proto = fullSequences.at(branch++);
        DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, stmgr->lookup(id), alt, "Could find channel: " + id);
        DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const TypeChannel *, channel, type_cast<TypeChannel>(sym->getType()), alt, "Channel identifier does not have a channel type in external choice.");
        channel->setProtocol(proto);
        std::variant<TypedNode *, ErrorChain *> optEval = anyOpt2VarError<TypedNode>(errorHandler, alt->accept(this));
        return optEval;
      });

    if (ErrorChain **e = std::get_if<ErrorChain *>(&branchOpt))
    {
      return (*e)->addError(ctx->getStart(), "Failed to type check external choice");
    }

    ConditionalData<TypedNode *> dat = std::get<ConditionalData<TypedNode *>>(branchOpt);

    return new TChannelCaseStatementNode(sym, isInCloseable, ctx->protoElse(), dat.cases, dat.post, ctx->getStart());
}
std::variant<TProgramProjectNode *, ErrorChain *> SemanticVisitor::TvisitProgramProject(BismuthParser::ProgramProjectContext *ctx)
{
    std::string id = ctx->channel->getText();
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, stmgr->lookup(id), ctx, "Could not find channel: " + id);
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const TypeChannel *, channel, type_cast<TypeChannel>(sym->getType()), ctx, "Cannot project on non-channel: " + id);

    if(ctx->lbl)
    {
      unsigned int projectIndex = channel->getProtocol()->project(ctx->lbl->getText());

      if (!projectIndex)
      {
        return errorHandler.addError(ctx->getStart(), "Failed to project over channel: " + sym->toString() + " vs " + ctx->lbl->getText());
      }

      return new TProgramProjectNode(sym, projectIndex, ctx->getStart());
    }

    ProtocolVisitor *protoVisitor = new ProtocolVisitor(errorHandler, this);
    std::variant<const ProtocolSequence *, ErrorChain *> protoOpt = protoVisitor->visitProto(ctx->sel); // TODO: how to prevent calls to bad overrides? ie, ProtocolVisitor visit type ctx?
    delete protoVisitor;

    if (ErrorChain **e = std::get_if<ErrorChain *>(&protoOpt))
    {
        return (*e)->addError(ctx->getStart(), "Failed to generate protocol type in project statement");
    }

    const ProtocolSequence *ps = std::get<const ProtocolSequence *>(protoOpt);

    unsigned int projectIndex = channel->getProtocol()->project(ps);

    if (!projectIndex)
    {
      return errorHandler.addError(ctx->getStart(), "Failed to project over channel: " + sym->toString() + " vs " + ps->toString(toStringMode));
    }

    return new TProgramProjectNode(sym, projectIndex, ctx->getStart());
}
std::variant<TProgramContractNode *, ErrorChain *> SemanticVisitor::TvisitProgramContract(BismuthParser::ProgramContractContext *ctx)
{
    std::string id = ctx->channel->getText();
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, stmgr->lookup(id), ctx, "Could not find channel: " + id);
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const TypeChannel *, channel, type_cast<TypeChannel>(sym->getType()), ctx, "Cannot contract on non-channel: " + id);
    if (!channel->getProtocol()->contract())
    {
      return errorHandler.addError(ctx->getStart(), "Failed to contract: " + id + " : " + channel->getProtocol()->toString(toStringMode));
    }
        // stmgr ->addSymbol(sym); // Makes sure we enforce weakening rules...

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

std::variant<TProgramWeakenNode *, ErrorChain *> SemanticVisitor::TvisitProgramWeaken(BismuthParser::ProgramWeakenContext *ctx)
{
    std::string id = ctx->channel->getText();
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, stmgr->lookup(id), ctx, "Could not find channel: " + id);
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const TypeChannel *, channel, type_cast<TypeChannel>(sym->getType()), ctx, "Cannot weaken on non-channel: " + id);
    if (!channel->getProtocol()->weaken())
    {
        return errorHandler.addError(ctx->getStart(), "Failed to weaken: " + id + " against " + channel->toString(toStringMode));
    }
    return new TProgramWeakenNode(sym, ctx->getStart());
}

std::variant<TProgramCancelNode *, ErrorChain *> SemanticVisitor::TvisitProgramCancel(BismuthParser::ProgramCancelContext *ctx)
{
    std::string id = ctx->channel->getText();
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, stmgr->lookup(id), ctx, "Could not find channel: " + id);
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const TypeChannel *, channel, type_cast<TypeChannel>(sym->getType()), ctx, "Cannot cancel on non-channel: " + id); // TODO: better error messages (expected type XYZ but got...)
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const ProtocolClose *, proto_post_close, channel->getProtocol()->cancel(), ctx, "Failed to cancel: " + id + " : "  + channel->toString(toStringMode));

    return new TProgramCancelNode(sym, proto_post_close->getCloseNumber(), ctx->getStart());
}

std::variant<TProgramAcceptNode *, ErrorChain *> SemanticVisitor::TvisitProgramAccept(BismuthParser::ProgramAcceptContext *ctx)
{
    std::string id = ctx->VARIABLE()->getText();
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, stmgr->lookup(id), ctx, "Unbound identifier: " + id);
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const TypeChannel*, channel, type_cast<TypeChannel>(sym->getType()), ctx, "Cannot accept: " + sym->toString());
    bool isInCloseable = channel->getProtocol()->isInCloseable();
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const ProtocolSequence *, proto_post_accept, channel->getProtocol()->acceptLoop(), ctx, "Cannot accept on " + channel->toString(toStringMode));

    const ProtocolSequence *postC = channel->getProtocolCopy();
    postC->guard();

    stmgr->guard();

    channel->setProtocol(proto_post_accept);

    std::variant<TBlockNode *, ErrorChain *> blkOpt = safeVisitBlock(ctx->block(), true);
    std::vector<Symbol *> lins = stmgr->getLinears(SymbolLookupFlags::PENDING_LINEAR);

    // If there are any uninferred symbols, then add it as an error as we won't be able to resolve them
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
      return (*e)->addErrorAt(ctx->getStart());
    }

    return new TProgramAcceptNode(sym, isInCloseable, std::get<TBlockNode *>(blkOpt), ctx->getStart());
}

std::variant<TProgramAcceptWhileNode *, ErrorChain *> SemanticVisitor::TvisitProgramAcceptWhile(BismuthParser::ProgramAcceptWhileContext *ctx)
{
    std::string id = ctx->VARIABLE()->getText();
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, stmgr->lookup(id), ctx, "Unbound identifier: " + id);
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const TypeChannel *, channel, type_cast<TypeChannel>(sym->getType()), ctx, "Cannot accept: " + sym->toString());
    DEFINE_OR_PROPAGATE_VARIANT(TypedNode *, condition, this->visitCondition(ctx->ex), ctx);

    bool isInCloseable = channel->getProtocol()->isInCloseable();
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const ProtocolSequence *, proto_post_accept, channel->getProtocol()->acceptWhileLoop(), ctx, "Cannot accept on " + channel->toString(toStringMode));

    const ProtocolSequence *postC = channel->getProtocolCopy();
    postC->guard();

    stmgr->guard();
    channel->setProtocol(proto_post_accept);

    std::variant<TBlockNode *, ErrorChain *> blkOpt = safeVisitBlock(ctx->block(), true);
    std::vector<Symbol *> lins = stmgr->getLinears(SymbolLookupFlags::PENDING_LINEAR);

    // If there are any uninferred symbols, then add it as an error as we won't be able to resolve them
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
      return (*e)->addErrorAt(ctx->getStart());
    }

    return new TProgramAcceptWhileNode(sym, isInCloseable, condition, std::get<TBlockNode *>(blkOpt), ctx->getStart());
}

std::variant<TProgramAcceptIfNode *, ErrorChain *> SemanticVisitor::TvisitProgramAcceptIf(BismuthParser::ProgramAcceptIfContext *ctx)
{
    std::string id = ctx->VARIABLE()->getText();
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, stmgr->lookup(id), ctx, "Unbound identifier: " + id);
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const TypeChannel *, channel, type_cast<TypeChannel>(sym->getType()), ctx, "Cannot accept: " + sym->toString());

    DEFINE_OR_PROPAGATE_VARIANT(TypedNode *, condition, this->visitCondition(ctx->check), ctx);

    bool isInCloseable = channel->getProtocol()->isInCloseable();
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const ProtocolSequence *, proto_post_accept, channel->getProtocol()->acceptIf(), ctx, "Cannot accept on " + channel->toString(toStringMode));

    std::vector<BismuthParser::BlockContext *> blksCtx = {ctx->trueBlk};
    if (ctx->falseBlk)
      blksCtx.push_back(ctx->falseBlk);

    unsigned int idx = 0;
    auto branchOpt = checkBranch<BismuthParser::ProgramAcceptIfContext, BismuthParser::BlockContext, TBlockNode *>(
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
      [](TBlockNode * blk) -> TypedNode * { return (TypedNode*) blk; },
      [this, &idx, id, proto_post_accept](BismuthParser::BlockContext *blk) -> std::variant<TBlockNode *, ErrorChain *>
      {
        if (idx == 0)
        {
          idx++;
          DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Symbol *, sym, stmgr->lookup(id), blk, "Could not find channel: " + id); // FIXME: FIND BETTER WAY TO MAP AND CHANGE CHANNEL VALUES IN SPECIFIC BRANCHES
          DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const TypeChannel *, channel, type_cast<TypeChannel>(sym->getType()), blk, "Channel identifier does not have a channel type in accept if.");
          channel->setProtocol(proto_post_accept);
          return this->safeVisitBlock(blk, false);
        }
      return this->safeVisitBlock(blk, false);
      });

    DEFINE_OR_PROPAGATE_VARIANT_WMSG(ConditionalData<TBlockNode *>, dat, branchOpt, ctx, "Failed to generate one or more branches in acceptIf");

    if (ctx->falseBlk)
    {
      return new TProgramAcceptIfNode(ctx->getStart(), isInCloseable, sym, condition,dat.cases.at(0), dat.post, dat.cases.at(1));
    }

    return new TProgramAcceptIfNode(ctx->getStart(), isInCloseable, sym, condition, dat.cases.at(0), dat.post);
}

std::variant<TProgramExecNode *, ErrorChain *> SemanticVisitor::TvisitAssignableExec(BismuthParser::AssignableExecContext *ctx)
{
    DEFINE_OR_PROPAGATE_VARIANT(TypedNode *, prog, anyOpt2VarError<TypedNode>(errorHandler, ctx->prog->accept(this)), ctx);
    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(const TypeProgram *, inv, type_cast<TypeProgram>(prog->getType()), ctx, "Cannot exec: " + prog->getType()->toString(toStringMode));
    return new TProgramExecNode(
      prog,
      new TypeChannel(inv->getProtocol()->getInverse()),
      ctx->getStart());
}

std::variant<TExprCopyNode *, ErrorChain *> SemanticVisitor::TvisitCopyExpr(BismuthParser::CopyExprContext *ctx)
{
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, tn, anyOpt2VarError<TypedNode>(errorHandler, ctx->expr->accept(this)), ctx, "Failed to type check copy expression");
    const Type *ty = tn->getType();

    if (ty->isLinear())
    {
        return errorHandler.addError(ctx->getStart(), "Cannot perform a copy on a linear type: " + ty->toString(toStringMode));
    }

    return new TExprCopyNode(tn, ctx->getStart());
}

std::variant<TAsChannelNode *, ErrorChain *> SemanticVisitor::TvisitAsChannelExpr(BismuthParser::AsChannelExprContext *ctx)
{
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, tn, anyOpt2VarError<TypedNode>(errorHandler, ctx->expr->accept(this)), ctx, "Failed to type check copy expression");
    return new TAsChannelNode(tn, ctx->getStart());
}

std::optional<ErrorChain *> SemanticVisitor::TVisitImportStatement(BismuthParser::ImportStatementContext * ctx)
{
    if(ctx->path()->eles.size() < 2)
    {
        return errorHandler.addCompilerError(
            ctx->path()->eles.back()->getStart(),
            "Paths must have 2 or more elements in them."
        );
    }

    std::string aliasStr = ctx->alias ? ctx->alias->getText() : ctx->path()->eles.at(ctx->path()->eles.size() - 1)->getText();

    if(stmgr->lookupInCurrentScope(aliasStr))
    {
        return errorHandler.addError(ctx->getStart(), aliasStr + " is already defined."); // TODO: better error
    }

    DEFINE_OR_PROPAGATE_VARIANT(const Type *, ty, visitPathType(ctx->path()), ctx);

    if(const NameableType * nt = dynamic_cast<const NameableType *>(ty))
    {
        if(!nt->hasName())
        {
            return errorHandler.addCompilerError(ctx->getStart(), "Imported type does not have a name");
        }

        stmgr->addAlias(
            aliasStr,
            nt,
            nt->getIdentifier().value()
        );

        return std::nullopt;
    }
    return errorHandler.addError(ctx->getStart(), "Cannot import: " + ty->toString(toStringMode) + ". Can only import named definitions."); // TODO: do better!
}

TemplateInfo SemanticVisitor::TvisitGenericTemplate(BismuthParser::GenericTemplateContext *ctx) {
    std::vector<std::pair<std::string, TypeGeneric *>> syms; // FIXME: SHOULD THIS BE CONST?
    std::map<std::string, antlr4::Token *> visited;

    // TODO: what restrictions should there be on the name of these variables?
    // Implement some function to do all the checking for if an identifier can be used
    for(auto entry : ctx->gen)
    {
        if(dynamic_cast<BismuthParser::GenericSessionContext *>(entry))
            errorHandler.addCompilerError(entry->getStart(), "FIXME: Session Type templates are currently unimplemented.");
        else if(BismuthParser::GenericTypeContext * tyCtx = dynamic_cast<BismuthParser::GenericTypeContext *>(entry))
        {
            if(tyCtx->supTy.size())
                errorHandler.addCompilerError(tyCtx->supTy.at(0)->getStart(), "FIXME: Specifying super types are currently unimplemented for generics");
            else
            {
                std::string idName = tyCtx->name->getText();
                auto prev = visited.find(idName);
                if(prev != visited.end())
                {
                    errorHandler.addError(tyCtx->getStart(),
                        "Redefinition of previously used identifier in template. Previously used at " + tokenToLineChar(prev->second)
                    );
                }
                else
                {
                    syms.push_back({idName, new TypeGeneric(false, idName)}); // FIXME: BETTER IS-LINEAR?
                    visited.insert({idName, tyCtx->getStart()});
                }
            }
        }
        else
            errorHandler.addCompilerError(entry->getStart(), "Unknown case for templates");
    }

    return TemplateInfo(syms);
}

template <RestRuleContext R, typename T, typename Y>
inline std::variant<SemanticVisitor::ConditionalData<Y>, ErrorChain *> SemanticVisitor::checkBranch(
    R *ctx,
    std::function<void(std::deque<DeepRestData *> *)> forwardBindings,
    std::vector<T *> ctxCases,
    bool checkRestIndependently,
    std::function<TypedNode *(Y)> getNode,
    std::function<std::variant<Y, ErrorChain *>(T *)> typeCheck)
{

    DeepRestData *restDat = new DeepRestData(ctx->rest);
    std::deque<DeepRestData *> *rest = new std::deque<DeepRestData *>();
    std::optional<std::deque<DeepRestData *> *> bindings = restBindings.getBinding(ctx);
    if (bindings.has_value())
    {
        for (auto a : *bindings.value())
            rest->push_back(a);
    }

    rest->push_front(restDat);

    forwardBindings(rest);

    std::optional<std::deque<DeepRestData *> *> deepRest = restBindings.getBinding(ctx);

    std::vector<Y> cases;

    // STManager *origStmgr = this->stmgr;

    DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(Scope *, origScope, stmgr->getCurrentScope(), ctx, "Symbol table manager has no current scope at branch!");

    const auto checkCase = [&](auto * branchToken, bool checkRest, std::string branchErrorMessage, std::string subsequentErrorMessage) -> std::optional<ErrorChain *>{
        if(checkRest)
        {
            for (auto s : restDat->ctxRest)
            {
                DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, rest, anyOpt2VarError<TypedNode>(errorHandler, s->accept(this)), branchToken, branchErrorMessage);

                if (!restDat->isGenerated)
                {
                    restDat->post.push_back(rest);
                }
            }

            restDat->isGenerated = true;
        }

        // FIXME: WILL NEED TO RUN THIS CHECK ON EACH ITERATION!
        if (deepRest && !TypedAST::endsInReturn(restDat->post) && !TypedAST::endsInBranch(restDat->post))
        {
            for (auto r : *(deepRest.value()))
            {
                for (auto s : r->ctxRest)
                {
                    DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, rest, anyOpt2VarError<TypedNode>(errorHandler, s->accept(this)), ctx, subsequentErrorMessage); // "Failed to type check when no branch followed"

                    if (!r->isGenerated)
                    {
                        r->post.push_back(rest);
                    }
                }
                r->isGenerated = true;
            }
        }

        // Note: this will throw errors if it fails, but we cannot detect them here
        safeExitScope(ctx);

        std::vector<Symbol *> lins = stmgr->getLinears(SymbolLookupFlags::PENDING_LINEAR);

        // If there are any uninferred symbols, then add it as an error as we won't be able to resolve them
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

            errorHandler.addError(branchToken->getStart(), "588 Unused linear types in context: " + details.str());
        }

        return std::nullopt;
    };

    for (unsigned int i = 0; i < ctxCases.size(); i++)
    {
        auto alt = ctxCases.at(i);

        if (checkRestIndependently || i + 1 < ctxCases.size())
        {
            Scope * scopeCpy = origScope->copyToStop();
            this->stmgr->enterScope(scopeCpy);
        }
        else
        {
            this->stmgr->enterScope(origScope);
        }

        stmgr->enterScope(StopType::NONE);
        DEFINE_OR_PROPAGATE_VARIANT(Y, caseVal, typeCheck(alt), ctx);

        cases.push_back(caseVal);

        TypedNode * caseNode = getNode(caseVal);

        std::optional<ErrorChain *> errorOpt = checkCase(
            alt,
            !TypedAST::endsInReturn(*caseNode) && !TypedAST::endsInBranch(*caseNode),
            "Failed to type check code following branch",
            "Failed to type check when no branch followed"
        );

        if(errorOpt) return errorOpt.value();
    }

    if (checkRestIndependently)
    {
        this->stmgr->enterScope(origScope);

        stmgr->enterScope(StopType::NONE); // Why? This doesn't make sense.. oh it does, but should ideally refactor!

        std::optional<ErrorChain *> errorOpt = checkCase(ctx, true, "Failed to type check code when conditional skipped over", "Failed to type check when skipped over and no branch followed");
        if(errorOpt) return errorOpt.value();
    }

    return ConditionalData<Y>(cases, restDat->post);
}

std::variant<DefinitionSymbol *, ErrorChain *>  SemanticVisitor::defineAndGetSymbolFor(BismuthParser::DefineTypeContext * ctx, VisibilityModifier m)
{
    // TODO: maybe refactor with visitCtx for Lambda?
    auto defineFunction = [this](BismuthParser::DefineFunctionContext *ctx, const TypeFunc *funcType) -> std::optional<ErrorChain *> {
        if(funcType->isDefined()) return std::nullopt;

        DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(ParameterListNode, params, visitCtx(ctx->lam->parameterList()), ctx, "340");

        std::vector<const Type *> ps;

        for (ParameterNode param : params)
        {
            ps.push_back(param.type);
        }

        std::variant<const Type *, ErrorChain *>  retTypeOpt = ctx->lam->ret ? anyOpt2VarError<const Type>(errorHandler, ctx->lam->ret->accept(this))
                            : (const Type*) Types::UNIT;

        if (ErrorChain **e = std::get_if<ErrorChain *>(&retTypeOpt))
        {
            return (*e)->addError(ctx->getStart(), "Error generating return type");
        }

        const Type *retType = std::get<const Type *>(retTypeOpt);

        funcType->setInvoke(ps, retType);

        return std::nullopt;
    };

    auto defineProgram = [this](BismuthParser::DefineProgramContext *ctx, const TypeProgram *progType) -> std::optional<ErrorChain *> {
        if (progType->isDefined()) return std::nullopt;

        DEFINE_OR_PROPAGATE_VARIANT_WMSG(const ProtocolSequence *, proto, visitProtocolAsSeq(ctx->proto), ctx, "Failed to generate channel type for program " + ctx->name->getText());

        progType->setProtocol(proto);
        return std::nullopt;
    };

    auto defineEnum = [this](BismuthParser::DefineEnumContext *ctx, const TypeSum *sumTy) -> std::optional<ErrorChain *> {
        if (sumTy->isDefined()) return std::nullopt;

        std::set<const Type *, TypeCompare> cases = {};

        for (auto e : ctx->cases)
        {
            DEFINE_OR_PROPAGATE_VARIANT_WMSG(const Type *, caseType, anyOpt2VarError<const Type>(errorHandler, e->accept(this)), ctx, "Failed to generate case type");

            if (caseType->isLinear())
            {
                return errorHandler.addError(e->getStart(), "Unable to store linear type, " + caseType->toString(toStringMode) + ", in non-linear container");
            }

            cases.insert(caseType);
        }

        if (cases.size() != ctx->cases.size())
        {
            return errorHandler.addError(ctx->getStart(), "Duplicate arguments to enum type, or failed to generate types");
        }

        sumTy->define(cases);
        return std::nullopt;
    };

    auto defineStruct = [this](BismuthParser::DefineStructContext *ctx, const TypeStruct *structType) -> std::optional<ErrorChain *> {
        if (structType->isDefined()) return std::nullopt;
        LinkedMap<std::string, const Type *> el;

        for (BismuthParser::StructCaseContext *caseCtx : ctx->cases)
        {
            std::string caseName = caseCtx->name->getText();
            if (el.lookup(caseName))
            {
                return errorHandler.addError(caseCtx->getStart(), "Unsupported redeclaration of " + caseName);
            }

            DEFINE_OR_PROPAGATE_VARIANT_WMSG(const Type *, caseTy, anyOpt2VarError<const Type>(errorHandler, caseCtx->ty->accept(this)), ctx, "Failed to generate case type");

            if (caseTy->isLinear())
            {
                return errorHandler.addError(caseCtx->getStart(), "Unable to store linear type, " + caseTy->toString(toStringMode) + ", in non-linear container");
            }

            el.insert({caseName, caseTy});

        }
        structType->define(el);
        return std::nullopt;
    };

    auto defineTemplate = [this, m, defineFunction, defineProgram, defineEnum, defineStruct](BismuthParser::DefineTypeContext *ctx, const TypeTemplate *templateTy, DefinitionSymbol * defSym) -> std::optional<ErrorChain *> {
        if (templateTy->isDefined()) return std::nullopt;

        auto applyTemplate = [this, m, defSym, ctx](TemplateInfo info, std::function<std::optional<ErrorChain *>()> fn) -> std::optional<ErrorChain *> {
            if(!stmgr->getCurrentScope()) return errorHandler.addCompilerError(ctx->getStart(), "No current scope in type checking of define Template!");

            Scope * origScope = stmgr->getCurrentScope().value();
            stmgr->enterScope(defSym->getInnerScope());

            for(auto i : info.templates)
            {
                std::optional<DefinitionSymbol *> symOpt =  stmgr->addDefinition(m, i.first, i.second, false);

                // FIXME: WRITE BETTER ERROR!
                if(!symOpt)
                    return errorHandler.addError(nullptr, "Failed to get template symbol for " + i.first);

            }

            std::optional<ErrorChain *> ans = fn();

            stmgr->enterScope(origScope);
            return ans;
        };

        return defineTypeCase<std::optional<ErrorChain *>>(ctx,
            [this, templateTy, defineFunction, applyTemplate](BismuthParser::DefineFunctionContext * fnCtx) -> std::optional<ErrorChain *> {
                // TODO: get errors from this?
                TemplateInfo info = TvisitGenericTemplate(fnCtx->genericTemplate());

                TypeFunc * funcTy = new TypeFunc();

                templateTy->define(info, funcTy);

                return applyTemplate(info, [defineFunction, fnCtx, funcTy](){
                    return defineFunction(fnCtx, funcTy);
                });
            },

            [this, templateTy, defineProgram, applyTemplate](BismuthParser::DefineProgramContext * ctx) -> std::optional<ErrorChain *> {
                // TODO: get errors from this?
                TemplateInfo info = TvisitGenericTemplate(ctx->genericTemplate());

                TypeProgram * progTy = new TypeProgram();

                templateTy->define(info, progTy);

                return applyTemplate(info, [defineProgram, ctx, progTy](){
                    return defineProgram(ctx, progTy);
                });
            },

            [this, templateTy, defineStruct, applyTemplate](BismuthParser::DefineStructContext * ctx) -> std::optional<ErrorChain *> {
                // TODO: get errors from this?
                TemplateInfo info = TvisitGenericTemplate(ctx->genericTemplate());

                TypeStruct * structTy = new TypeStruct(); //ctx->name->getText());

                // if(templateTy->getIdentifier())
                //     structTy->setIdentifier(templateTy->getIdentifier().value());

                templateTy->define(info, structTy);

                return applyTemplate(info, [defineStruct, ctx, structTy](){
                    return defineStruct(ctx, structTy);
                });
            },

            [this, templateTy, defineEnum, applyTemplate](BismuthParser::DefineEnumContext * ctx) -> std::optional<ErrorChain *> {
                TemplateInfo info = TvisitGenericTemplate(ctx->genericTemplate());

                TypeSum * sumTy = new TypeSum();//ctx->name->getText());

                templateTy->define(info, sumTy);

                return applyTemplate(info, [defineEnum, ctx, sumTy](){
                    return defineEnum(ctx, sumTy);
                });
            },

            [this](BismuthParser::DefineTypeContext * ctx) -> std::optional<ErrorChain *> {
                return errorHandler.addCompilerError(ctx->getStart(), "Attempted to apply a template to an unknown/unimplemented type definition.");
            }
        );
    };

    auto getTemplateSymbol = [this, m, defineTemplate](std::optional<DefinitionSymbol *> opt, std::string symName, BismuthParser::DefineTypeContext* innerCtx) -> std::variant<DefinitionSymbol *, ErrorChain *> {
        DefinitionSymbol * defSym = lazy_value_or<DefinitionSymbol *>(opt,
            [this, m, symName]() {
                DefinitionSymbol * sym = stmgr->addDefinition(m, symName, new TypeTemplate(), false).value(); //should be safe as we checked for redeclarations
                return sym;
            });

        if (const TypeTemplate *templateTy = dynamic_cast<const TypeTemplate *>(defSym->getType()))
        {
            std::optional<ErrorChain *> optErr = defineTemplate(innerCtx, templateTy, defSym);

            if(optErr) return optErr.value();

            return defSym;
        }

        return errorHandler.addError(innerCtx->getStart(), "Expected template but got: " + defSym->getType()->toString(toStringMode));
    };

    // Essentially a type-case
    return defineTypeCase<std::variant<DefinitionSymbol *, ErrorChain *>>(ctx,
        [this, m, defineTemplate, defineFunction](BismuthParser::DefineFunctionContext * fnCtx) -> std::variant<DefinitionSymbol *, ErrorChain *> {

            std::optional<DefinitionSymbol *> opt = symBindings.getBinding(fnCtx);

            if (!opt && stmgr->lookupInCurrentScope(fnCtx->name->getText()))
            {
                return errorHandler.addError(fnCtx->getStart(), "Unsupported redeclaration of " + fnCtx->name->getText());
            }
            bool isTemplate = fnCtx->genericTemplate();

            if(isTemplate)
            {
                DefinitionSymbol *sym = lazy_value_or<DefinitionSymbol *>(opt,
                    [this, m, fnCtx](){
                        return stmgr->addDefinition(
                            m,
                            fnCtx->name->getText(),
                            new TypeTemplate(),
                            false).value(); //should be safe as we checked for redeclarations
                    });

                if (const TypeTemplate *templateTy = dynamic_cast<const TypeTemplate *>(sym->getType()))
                {
                    std::optional<ErrorChain *> optErr = defineTemplate(fnCtx, templateTy, sym);

                    if(optErr) return optErr.value();

                    if(!templateTy->getValueType())
                    {
                        return errorHandler.addCompilerError(fnCtx->getStart(), "Cannot find the type to apply a template to.");
                    }

                    if (const TypeFunc *funcType = dynamic_cast<const TypeFunc *>(templateTy->getValueType().value()))
                    {
                        return sym;
                    }
                    // TODO: print templateTy->getValueType().value()?
                    return errorHandler.addError(fnCtx->getStart(), "Expected function but got: " + sym->getType()->toString(toStringMode));
                }

                return errorHandler.addError(fnCtx->getStart(), "Expected template but got: " + sym->getType()->toString(toStringMode));
            }

            DefinitionSymbol *sym = lazy_value_or<DefinitionSymbol *>(opt,
                [this, m, fnCtx]() {
                    return stmgr->addDefinition(
                        m,
                        fnCtx->name->getText(),
                        new TypeFunc(),
                        false).value(); //should be safe as we checked for redeclarations
                });

            if (const TypeFunc *funcType = dynamic_cast<const TypeFunc *>(sym->getType()))
            {
                std::optional<ErrorChain *> optErr = defineFunction(fnCtx, funcType);

                if(optErr) return optErr.value();
                return sym;
            }

            return errorHandler.addError(fnCtx->getStart(), "Expected function but got: " + sym->getType()->toString(toStringMode));
        },

        [this, m, getTemplateSymbol, defineProgram](BismuthParser::DefineProgramContext * ctx) -> std::variant<DefinitionSymbol *, ErrorChain *> {
            std::optional<DefinitionSymbol *> opt = symBindings.getBinding((BismuthParser::DefineTypeContext *)ctx);

            if (!opt && stmgr->lookupInCurrentScope(ctx->name->getText()))
            {
                return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of " + ctx->name->getText());
            }

            if(ctx->genericTemplate())
            {
                return getTemplateSymbol(opt, ctx->name->getText(), ctx);
            }

            DefinitionSymbol *sym = lazy_value_or<DefinitionSymbol *>(opt,
                [this, m, ctx]() { return stmgr->addDefinition(
                    m,
                    ctx->name->getText(),
                    new TypeProgram(),
                    false).value(); //should be safe as we checked for redeclarations
                });

            if (const TypeProgram *progType = dynamic_cast<const TypeProgram *>(sym->getType()))
            {
                std::optional<ErrorChain *> optErr = defineProgram(ctx, progType);

                if(optErr) return optErr.value();
                return sym;
            }

            return errorHandler.addError(ctx->getStart(), "Expected program but got: " + sym->getType()->toString(toStringMode));
        },

        [this, m, getTemplateSymbol, defineStruct](BismuthParser::DefineStructContext * ctx) -> std::variant<DefinitionSymbol *, ErrorChain *> {
            std::optional<DefinitionSymbol *> opt = symBindings.getBinding(ctx);

            if (!opt && stmgr->lookupInCurrentScope(ctx->name->getText()))
            {
                return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of " + ctx->name->getText());
            }

            std::string name = ctx->name->getText();

            if(ctx->genericTemplate())
            {
                return getTemplateSymbol(opt, name, ctx);
            }

            DefinitionSymbol *sym = lazy_value_or<DefinitionSymbol *>(opt,
                [this, m, name]() { return stmgr->addDefinition(
                    m,
                    name,
                    new TypeStruct(),
                    true) // FIXME: WHY ARE OTHERS true, false? when this is true, true
                    .value(); //should be safe as we checked for redeclarations
                });

            if(const TypeStruct * structTy = dynamic_cast<const TypeStruct *>(sym->getType()))
            {
                std::optional<ErrorChain *> errOpt = defineStruct(ctx, structTy);

                if(errOpt) return errOpt.value();
                return sym;
            }

            return errorHandler.addError(ctx->getStart(), "Expected struct/product but got: " + sym->getType()->toString(toStringMode));
        },

        [this, m, getTemplateSymbol, defineEnum](BismuthParser::DefineEnumContext * ctx) -> std::variant<DefinitionSymbol *, ErrorChain *> {
            std::optional<DefinitionSymbol *> opt = symBindings.getBinding(ctx);

            if (!opt && stmgr->lookupInCurrentScope(ctx->name->getText()))
            {
                return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of " + ctx->name->getText());
            }

            std::string name = ctx->name->getText();

            if(ctx->genericTemplate())
            {
                return getTemplateSymbol(opt, name, ctx);
            }

            DefinitionSymbol *sym = lazy_value_or<DefinitionSymbol *>(opt,
                [this, m, name](){
                    return stmgr->addDefinition(
                        m,
                        name,
                        new TypeSum(),
                        true // TODO: should global be automatic and context sensitive?
                    ).value(); //should be safe as we checked for redeclarations
            });

            if(const TypeSum * sumTy = dynamic_cast<const TypeSum *>(sym->getType()))
            {
                std::optional<ErrorChain *> errOpt = defineEnum(ctx, sumTy);

                if(errOpt) return errOpt.value();
                return sym;
            }

            return errorHandler.addError(ctx->getStart(), "Expected enum/sum but got: " + sym->getType()->toString(toStringMode));
        },

        [this](BismuthParser::DefineTypeContext * ctx) -> std::variant<DefinitionSymbol *, ErrorChain *>{
            return errorHandler.addCompilerError(ctx->getStart(), "Failed to generate the type for a definition; Unknown and unimplemented case for define type.");
        }

    );
}

std::variant<TypedNode *, ErrorChain *> SemanticVisitor::visitLValue(antlr4::ParserRuleContext *ctx)
{
    while(BismuthParser::ParenExprContext * lctx = dynamic_cast<BismuthParser::ParenExprContext * >(ctx)) {
        ctx = lctx->ex;
    }

    if(BismuthParser::PathContext * lctx = dynamic_cast<BismuthParser::PathContext *>(ctx))
    {
        return TNVariantCast<TPathNode>(visitCtx(lctx, false));
    }
    else if(BismuthParser::PathExprContext * lctx = dynamic_cast<BismuthParser::PathExprContext *>(ctx))
    {
        return TNVariantCast<TPathNode>(visitCtx(lctx->path(), false));
    }
    else if(BismuthParser::FieldAccessExprContext * lctx = dynamic_cast<BismuthParser::FieldAccessExprContext *>(ctx))
    {
        return TNVariantCast<TFieldAccessNode>(visitCtx(lctx, false));
    }
    else if(BismuthParser::IdentifierExprContext * lctx = dynamic_cast<BismuthParser::IdentifierExprContext *>(ctx))
    {
        return TNVariantCast<TIdentifier>(visitCtx(lctx, false));
    }
    else if(BismuthParser::DerefContext * lctx = dynamic_cast<BismuthParser::DerefContext *>(ctx))
    {
        return TNVariantCast<TDerefBoxNode>(visitCtx(lctx, false));
    }
    else if(BismuthParser::ArrayAccessContext * lctx = dynamic_cast<BismuthParser::ArrayAccessContext *>(ctx))
    {
        return visitCtx(lctx, false);
    }

    return errorHandler.addError(ctx->getStart(), "Required an l-value, but the provided expression (" + ctx->getText() + ") is not."); // TODO: better error
}

std::variant<const ProtocolSequence *, ErrorChain *>
SemanticVisitor::visitProtocolAsSeq(BismuthParser::ProtocolContext *ctx)
{
    ProtocolVisitor *protoVisitor = new ProtocolVisitor(errorHandler, this);
    std::variant<const ProtocolSequence *, ErrorChain *> protoOpt = protoVisitor->visitProto(ctx); // TODO: how to prevent calls to bad overrides? ie, ProtocolVisitor visit type ctx?
    delete protoVisitor;

    return protoOpt;
}

std::variant<const TypeChannel *, ErrorChain *>
SemanticVisitor::visitProtocolAsChannel(BismuthParser::ProtocolContext *ctx)
{
    DEFINE_OR_PROPAGATE_VARIANT_WMSG(const ProtocolSequence *, proto, visitProtocolAsSeq(ctx), ctx, "Failed to generate channel protocol");
    return new TypeChannel(proto);
}
