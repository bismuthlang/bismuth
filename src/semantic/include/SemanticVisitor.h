#pragma once
#include "antlr4-runtime.h"
#include "WPLBaseVisitor.h"
#include "STManager.h"
#include "PropertyManager.h"
#include "WPLErrorHandler.h"
#include "CompilerFlags.h"
// #include "CastUtils.h"

// #include "TypeVisitor.h"

#include "LinkedMap.h"

class SemanticVisitor : WPLBaseVisitor
{

public:
    /**
     * @brief Construct a new Semantic Visitor object
     *
     * @param s Symbol table manager to use
     * @param p Property manager to use
     * @param f Compiler flags
     */
    SemanticVisitor(STManager *s, PropertyManager *p, int f = 0)
    {
        stmgr = s;
        bindings = p;

        flags = f;
    }

    std::string getErrors() { return errorHandler.errorList(); }
    STManager *getSTManager() { return stmgr; }
    PropertyManager *getBindings() { return bindings; }
    bool hasErrors(int flags) { return errorHandler.hasErrors(flags); }

    /*
     * The following are simply typed versions of the traditional visitor methods
     */
    const Type *visitCtx(WPLParser::CompilationUnitContext *ctx);
    const Type *visitCtx(WPLParser::InvocationContext *ctx);
    const Type *visitCtx(WPLParser::ArrayAccessContext *ctx);
    const Type *visitCtx(WPLParser::ArrayOrVarContext *ctx);
    const Type *visitCtx(WPLParser::IConstExprContext *ctx);
    const Type *visitCtx(WPLParser::ArrayAccessExprContext *ctx);
    const Type *visitCtx(WPLParser::SConstExprContext *ctx);
    const Type *visitCtx(WPLParser::UnaryExprContext *ctx);
    const Type *visitCtx(WPLParser::BinaryArithExprContext *ctx);
    const Type *visitCtx(WPLParser::EqExprContext *ctx);
    const Type *visitCtx(WPLParser::LogAndExprContext *ctx);
    const Type *visitCtx(WPLParser::LogOrExprContext *ctx);
    const Type *visitCtx(WPLParser::CallExprContext *ctx);
    // const Type *visitCtx(WPLParser::VariableExprContext *ctx);
    const Type *visitCtx(WPLParser::FieldAccessExprContext *ctx);
    const Type *visitCtx(WPLParser::ParenExprContext *ctx);
    const Type *visitCtx(WPLParser::BinaryRelExprContext *ctx);
    const Type *visitCtx(WPLParser::BConstExprContext *ctx);
    const Type *visitCtx(WPLParser::BlockContext *ctx);
    const Type *visitCtx(WPLParser::ConditionContext *ctx);
    const Type *visitCtx(WPLParser::SelectAlternativeContext *ctx);
    const Type *visitCtx(WPLParser::ParameterListContext *ctx);
    const Type *visitCtx(WPLParser::ParameterContext *ctx);
    const Type *visitCtx(WPLParser::AssignmentContext *ctx);
    const Type *visitCtx(WPLParser::ExternStatementContext *ctx);
    const Type *visitCtx(WPLParser::ProgDefContext *ctx);
    const Type *visitCtx(WPLParser::AssignStatementContext *ctx);
    const Type *visitCtx(WPLParser::VarDeclStatementContext *ctx);
    const Type *visitCtx(WPLParser::ProgramLoopContext *ctx);
    const Type *visitCtx(WPLParser::ConditionalStatementContext *ctx);
    const Type *visitCtx(WPLParser::SelectStatementContext *ctx);
    const Type *visitCtx(WPLParser::CallStatementContext *ctx);
    const Type *visitCtx(WPLParser::ReturnStatementContext *ctx);
    const Type *visitCtx(WPLParser::BlockStatementContext *ctx);
    const Type *visitCtx(WPLParser::TypeOrVarContext *ctx);
    // const Type *visitCtx(WPLParser::TypeContext *ctx);
    const Type *visitCtx(WPLParser::BooleanConstContext *ctx);

    const Type *visitCtx(WPLParser::LambdaTypeContext *ctx);
    const Type *visitCtx(WPLParser::BaseTypeContext *ctx);
    const Type *visitCtx(WPLParser::ArrayTypeContext *ctx);

    const Type *visitCtx(WPLParser::LambdaConstExprContext *ctx);

    const Type *visitCtx(WPLParser::SumTypeContext *ctx); // FIXME: NEED TO DO THIS & OTHERS!
    const Type *visitCtx(WPLParser::CustomTypeContext *ctx);
    const Type *visitCtx(WPLParser::DefineEnumContext *ctx);
    const Type *visitCtx(WPLParser::MatchStatementContext *ctx);
    const Type *visitCtx(WPLParser::DefineStructContext *ctx);
    const Type *visitCtx(WPLParser::InitProductContext *ctx);

    const Type *visitCtx(WPLParser::ChannelTypeContext *ctx);
    const Protocol *visitProto(WPLParser::ProtocolContext *ctx);
    const Protocol *visitProto(WPLParser::RecvTypeContext *ctx);
    const Protocol *visitProto(WPLParser::SendTypeContext *ctx);
    const Protocol *visitProto(WPLParser::WnProtoContext *ctx);
    const Protocol *visitProto(WPLParser::OcProtoContext *ctx);
    const Protocol *visitProto(WPLParser::ExtChoiceProtoContext *ctx);
    const Protocol *visitProto(WPLParser::IntChoiceProtoContext *ctx);

    /*
     * Traditional visitor methods all overridden with our typed versions
     */
    std::any visitCompilationUnit(WPLParser::CompilationUnitContext *ctx) override { return visitCtx(ctx); }
    std::any visitInvocation(WPLParser::InvocationContext *ctx) override { return visitCtx(ctx); }
    std::any visitArrayAccess(WPLParser::ArrayAccessContext *ctx) override { return visitCtx(ctx); }
    std::any visitArrayOrVar(WPLParser::ArrayOrVarContext *ctx) override { return visitCtx(ctx); }
    std::any visitIConstExpr(WPLParser::IConstExprContext *ctx) override { return visitCtx(ctx); }
    std::any visitArrayAccessExpr(WPLParser::ArrayAccessExprContext *ctx) override { return visitCtx(ctx); }
    std::any visitSConstExpr(WPLParser::SConstExprContext *ctx) override { return visitCtx(ctx); }
    std::any visitUnaryExpr(WPLParser::UnaryExprContext *ctx) override { return visitCtx(ctx); }
    std::any visitBinaryArithExpr(WPLParser::BinaryArithExprContext *ctx) override { return visitCtx(ctx); }
    std::any visitEqExpr(WPLParser::EqExprContext *ctx) override { return visitCtx(ctx); }
    std::any visitLogAndExpr(WPLParser::LogAndExprContext *ctx) override { return visitCtx(ctx); }
    std::any visitLogOrExpr(WPLParser::LogOrExprContext *ctx) override { return visitCtx(ctx); }
    std::any visitCallExpr(WPLParser::CallExprContext *ctx) override { return visitCtx(ctx); }
    // std::any visitVariableExpr(WPLParser::VariableExprContext *ctx) override { return visitCtx(ctx); }
    std::any visitFieldAccessExpr(WPLParser::FieldAccessExprContext *ctx) override { return visitCtx(ctx); }
    std::any visitParenExpr(WPLParser::ParenExprContext *ctx) override { return visitCtx(ctx); }
    std::any visitBinaryRelExpr(WPLParser::BinaryRelExprContext *ctx) override { return visitCtx(ctx); }
    std::any visitBConstExpr(WPLParser::BConstExprContext *ctx) override { return visitCtx(ctx); }
    std::any visitBlock(WPLParser::BlockContext *ctx) override { return visitCtx(ctx); }
    std::any visitCondition(WPLParser::ConditionContext *ctx) override { return visitCtx(ctx); }
    std::any visitSelectAlternative(WPLParser::SelectAlternativeContext *ctx) override { return visitCtx(ctx); }
    std::any visitParameterList(WPLParser::ParameterListContext *ctx) override { return visitCtx(ctx); }
    std::any visitParameter(WPLParser::ParameterContext *ctx) override { return visitCtx(ctx); }
    std::any visitAssignment(WPLParser::AssignmentContext *ctx) override { return visitCtx(ctx); }
    std::any visitExternStatement(WPLParser::ExternStatementContext *ctx) override { return visitCtx(ctx); }
    std::any visitProgDef(WPLParser::ProgDefContext *ctx) override { return visitCtx(ctx); }
    std::any visitAssignStatement(WPLParser::AssignStatementContext *ctx) override { return visitCtx(ctx); }
    std::any visitVarDeclStatement(WPLParser::VarDeclStatementContext *ctx) override { return visitCtx(ctx); }
    std::any visitProgramLoop(WPLParser::ProgramLoopContext *ctx) override { return visitCtx(ctx); }
    std::any visitConditionalStatement(WPLParser::ConditionalStatementContext *ctx) override { return visitCtx(ctx); }
    std::any visitSelectStatement(WPLParser::SelectStatementContext *ctx) override { return visitCtx(ctx); }
    std::any visitCallStatement(WPLParser::CallStatementContext *ctx) override { return visitCtx(ctx); }
    std::any visitReturnStatement(WPLParser::ReturnStatementContext *ctx) override { return visitCtx(ctx); }
    std::any visitBlockStatement(WPLParser::BlockStatementContext *ctx) override { return visitCtx(ctx); }
    std::any visitTypeOrVar(WPLParser::TypeOrVarContext *ctx) override { return visitCtx(ctx); }
    // std::any visitType(WPLParser::TypeContext *ctx) override { return visitCtx(ctx); }
    std::any visitBooleanConst(WPLParser::BooleanConstContext *ctx) override { return visitCtx(ctx); }

    std::any visitLambdaType(WPLParser::LambdaTypeContext *ctx) override { return visitCtx(ctx); }
    std::any visitBaseType(WPLParser::BaseTypeContext *ctx) override { return visitCtx(ctx); }
    std::any visitArrayType(WPLParser::ArrayTypeContext *ctx) override { return visitCtx(ctx); }

    std::any visitLambdaConstExpr(WPLParser::LambdaConstExprContext *ctx) override { return visitCtx(ctx); }

    std::any visitSumType(WPLParser::SumTypeContext *ctx) override { return visitCtx(ctx); }
    std::any visitCustomType(WPLParser::CustomTypeContext *ctx) override { return visitCtx(ctx); }
    std::any visitDefineEnum(WPLParser::DefineEnumContext *ctx) override { return visitCtx(ctx); }
    std::any visitMatchStatement(WPLParser::MatchStatementContext *ctx) override { return visitCtx(ctx); }
    std::any visitDefineStruct(WPLParser::DefineStructContext *ctx) override { return visitCtx(ctx); }
    std::any visitInitProduct(WPLParser::InitProductContext *ctx) override { return visitCtx(ctx); }

    std::any visitDefineProgram(WPLParser::DefineProgramContext *ctx) override { return visitInvokeable(ctx->defineProc()); } // FIXME: DO BETTER!!!
    std::any visitChannelType(WPLParser::ChannelTypeContext *ctx) override { return visitCtx(ctx); }
    std::any visitProtocol(WPLParser::ProtocolContext *ctx) override { return visitProto(ctx); }
    std::any visitRecvType(WPLParser::RecvTypeContext *ctx) override { return visitProto(ctx); }
    std::any visitSendType(WPLParser::SendTypeContext *ctx) override { return visitProto(ctx); }
    std::any visitWnProto(WPLParser::WnProtoContext *ctx) override { return visitProto(ctx); }
    std::any visitOcProto(WPLParser::OcProtoContext *ctx) override { return visitProto(ctx); }
    std::any visitExtChoiceProto(WPLParser::ExtChoiceProtoContext *ctx) override { return visitProto(ctx); }
    std::any visitIntChoiceProto(WPLParser::IntChoiceProtoContext *ctx) override { return visitProto(ctx); }

    std::any visitProgramSend(WPLParser::ProgramSendContext *ctx) override { return TvisitProgramSend(ctx); }
    const Type *TvisitProgramSend(WPLParser::ProgramSendContext *ctx);

    std::any visitAssignableRecv(WPLParser::AssignableRecvContext *ctx) override { return TvisitAssignableRecv(ctx); }
    const Type *TvisitAssignableRecv(WPLParser::AssignableRecvContext *ctx);

    // std::any visitProgramLoop(WPLParser::ProgramLoopContext *ctx) override { return TvisitProgramLoop(ctx); }
    // const Type *TvisitProgramLoop(WPLParser::ProgramLoopContext *ctx);

    std::any visitProgramCase(WPLParser::ProgramCaseContext *ctx) override { return TvisitProgramCase(ctx); }
    const Type *TvisitProgramCase(WPLParser::ProgramCaseContext *ctx);

    std::any visitProgramProject(WPLParser::ProgramProjectContext *ctx) override { return TvisitProgramProject(ctx); }
    const Type *TvisitProgramProject(WPLParser::ProgramProjectContext *ctx);

    std::any visitProgramContract(WPLParser::ProgramContractContext *ctx) override { return TvisitProgramContract(ctx); }
    const Type *TvisitProgramContract(WPLParser::ProgramContractContext *ctx);

    std::any visitProgramWeaken(WPLParser::ProgramWeakenContext *ctx) override { return TvisitProgramWeaken(ctx); }
    const Type *TvisitProgramWeaken(WPLParser::ProgramWeakenContext *ctx);

    std::any visitProgramAccept(WPLParser::ProgramAcceptContext *ctx) override { return TvisitProgramAccept(ctx); }
    const Type *TvisitProgramAccept(WPLParser::ProgramAcceptContext *ctx);

    std::any visitAssignableExec(WPLParser::AssignableExecContext *ctx) override { return TvisitAssignableExec(ctx); }
    const Type *TvisitAssignableExec(WPLParser::AssignableExecContext *ctx);

    /**
     * @brief Used to safely enter a block. This is used to ensure there aren't FUNC/PROC definitions / code following returns in it.
     *
     * @param ctx The BlockContext to visit
     * @param newScope  true if we should enter a new scope, false otherwise
     * @return const Type* Types::UNDEFINED as this is a statement and not a value
     */
    const Type *safeVisitBlock(WPLParser::BlockContext *ctx, bool newScope)
    {
        // Enter a new scope if desired
        if (newScope)
            stmgr->enterScope(StopType::NONE); //FIXME: DO BETTER?

        // Tracks if we have found a return statement or not
        bool foundReturn = false;
        for (auto e : ctx->stmts)
        {
            // Visit all the statements in the block
            e->accept(this);

            // If we found a return, then this is dead code, and we can break out of the loop.
            if (foundReturn)
            {
                errorHandler.addSemanticError(ctx->getStart(), "Dead code.");
                break;
            }

            // If the current statement is a return, set foundReturn = true
            if (dynamic_cast<WPLParser::ReturnStatementContext *>(e))
                foundReturn = true;
        }

        // If we entered a new scope, then we can now safely exit a scope
        if (newScope)
            this->safeExitScope(ctx);

        return Types::UNDEFINED;
    }

    /**
     * @brief Visits an invokable definition (PROC or FUNC)
     *
     * @param ctx The parser rule context
     * @param funcId The name of the PROC/FUNC
     * @param paramList The parameter list for the PROC/FUNC
     * @param ty The return type (Type::UNDEFINED for PROC)
     * @param block The PROC/FUNC block
     * @return const Type* TypeInvoke if successful, TypeBot if error
     */
    const Type *visitInvokeable(WPLParser::DefineProcContext *ctx)
    {
        std::optional<std::pair<const TypeProgram *, Symbol *>> pairOpt = invokableHelper(ctx);

        if (!pairOpt)
            return {}; // Errors already caught

        std::pair<const TypeProgram *, Symbol *> pair = pairOpt.value();

        const TypeProgram *funcType = pair.first;
        Symbol *funcSymbol = pair.second;

        std::string funcId = ctx->name->getText();

        // If the symbol name is program, do some extra checks to make sure it has no arguments and returns an INT. Otherwise, we will get a link error.
        // if (funcId == "program") //FIXME: DO BETTER
        // {
        //     if (!dynamic_cast<const TypeInt *>(funcType->getReturnType()))
        //     {
        //         errorHandler.addSemanticCritWarning(ctx->getStart(), "program() should return type INT");
        //     }

        //     if (funcType->getParamTypes().size() != 0)
        //     {
        //         errorHandler.addSemanticCritWarning(ctx->getStart(), "program() should have no arguments");
        //     }
        // }

        // Lookup the function in the current scope and prevent redeclaratons
        /*

        //FIXME: RE-ENABLE
        std::optional<Symbol *> opt = stmgr->lookupInCurrentScope(funcId);
        if (opt)
        {
            Symbol *defSym = opt.value();
            if (defSym->type)
            {
                if (const TypeInvoke *other = dynamic_cast<const TypeInvoke *>(defSym->type))
                {
                    if (other->isSubtype(funcType) && !(other->isDefined()))
                    {
                        other->define();
                        goto cont;
                    }
                }
            }
            errorHandler.addSemanticError(ctx->getStart(), "Unsupported redeclaration of " + funcId);
            return Types::UNDEFINED;
        }
        */

        // cont:
        // Add the symbol to the stmgr and enter the scope.
        stmgr->addSymbol(funcSymbol);
        stmgr->enterScope(StopType::GLOBAL); // NOTE: We do NOT duplicate scopes here because we use a saveVisitBlock with newScope=false

        stmgr->addSymbol(new Symbol(ctx->channelName->getText(), funcType->getChannelType()->getCopy(), false, false));
        // In the new scope. set our return type. We use @RETURN as it is not a valid symbol the programmer could write in the language
        // stmgr->addSymbol(new Symbol("@RETURN", funcType->getReturnType(), false, false));

        // Safe visit the program block without creating a new scope (as we are managing the scope)
        this->safeVisitBlock(ctx->block(), false);

        // If we have a return type, make sure that we return as the last statement in the FUNC. The type of the return is managed when we visited it.
        // if (ty && (ctx->block()->stmts.size() == 0 || !dynamic_cast<WPLParser::ReturnStatementContext *>(ctx->block()->stmts.at(ctx->block()->stmts.size() - 1))))
        // {
        //     errorHandler.addSemanticError(ctx->getStart(), "Function must end in return statement"); //FIXME: we don't have returns anymore...
        // }

        // Safe exit the scope.
        safeExitScope(ctx);

        // Add a binding in the property manager
        bindings->bind(ctx, funcSymbol);

        return funcType;
    }

    const Type *any2Type(std::any any)
    {
        // if(!any) return {};

        if (const Type *valOpt = std::any_cast<const Type *>(any))
            return valOpt;

        return Types::UNDEFINED; // TODO: DO BETTER
    }

    const Protocol *any2Protocol(std::any any)
    {
        // if(!any) return {};

        if (const Protocol *valOpt = std::any_cast<const Protocol *>(any))
            return valOpt;

        return nullptr; // FIXME: DO BETTER
    }

private:
    STManager *stmgr;
    PropertyManager *bindings;
    WPLErrorHandler errorHandler;

    int flags; // Compiler flags

    // INFO: TEST UNERLYING FNS!!!
    void safeExitScope(antlr4::ParserRuleContext *ctx)
    {
        // First, try exiting the scope
        std::pair<std::optional<Scope *>, std::optional<Scope *>> res = stmgr->exitScope();

        // If we did so and got a value back, then we can do type inferencing.
        if (res.first)
        {
            // Get the Scope* and check for any uninferred symbols
            Scope *scope = res.first.value();
            std::vector<const Symbol *> uninf = scope->getUninferred();

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
        }

        if(res.second)
        {
            Scope *scope = res.second.value();
            std::vector<const Symbol *> lins = scope->getRemainingLinearTypes();

            // If there are any uninferred symbols, then add it as a compiler error as we won't be able to resolve them
            // due to the var leaving the scope
            if (lins.size() > 0)
            {
                std::ostringstream details;

                for (auto e : lins)
                {
                    details << e->toString() << "; ";
                }

                errorHandler.addSemanticError(ctx->getStart(), "Unused linear types in context: " + details.str());
            }
        }
        // return res;
    }

    std::optional<const TypeProgram *> invokableHelper2(WPLParser::DefineProcContext *ctx)
    {
        std::optional<Symbol *> opt = stmgr->lookupInCurrentScope(ctx->name->getText()); // FIXME: VERIFY?

        if (opt)
        {
            Symbol *sym = opt.value();

            if (const TypeProgram *inv = dynamic_cast<const TypeProgram *>(sym->type))
            {
                return inv;
            }

            errorHandler.addSemanticError(ctx->getStart(), "Cannot invoke " + sym->toString());
            return {};
        }

        // If we have a return type, then visit that contex to determine what it is. Otherwise, set it as Types::UNDEFINED.
        const Type *retType = any2Type(ctx->ty->accept(this));

        if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(retType))
        {
            // Create a new func with the return type (or reuse the procType) NOTE: We do NOT need to worry about discarding the variadic here as variadic FUNC/PROC is not supported
            const TypeProgram *funcType = new TypeProgram(channel, false);

            return funcType;
        }

        errorHandler.addSemanticError(ctx->getStart(), "Program expected channel type!");
        return {};
    }

    std::optional<std::pair<const TypeProgram *, Symbol *>> invokableHelper(WPLParser::DefineProcContext *ctx)
    {
        std::optional<const TypeProgram *> funcTypeOpt = invokableHelper2(ctx);

        if (!funcTypeOpt)
            return {};

        const TypeProgram *funcType = funcTypeOpt.value();
        // Create a new symbol for the PROC/FUNC
        Symbol *funcSymbol = new Symbol(ctx->name->getText(), funcType, true, false);

        std::pair<const TypeProgram *, Symbol *> ans = {funcType, funcSymbol};
        return ans;
    }
};