#pragma once
#include "antlr4-runtime.h"
#include "WPLBaseVisitor.h"
#include "STManager.h"
#include "PropertyManager.h"
#include "WPLErrorHandler.h"
#include "CompilerFlags.h"
#include "TypedAST.h"
#include "CastUtils.h"

// #include "TypeVisitor.h"

#include "LinkedMap.h"

#include <regex>

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




    IConstExprNode* visitCtx(WPLParser::IConstExprContext *ctx);
    std::any visitIConstExpr(WPLParser::IConstExprContext *ctx) override { return visitCtx(ctx); }

    BooleanConstNode *visitCtx(WPLParser::BConstExprContext *ctx) { return visitCtx(ctx->booleanConst()); }
    std::any visitBConstExpr(WPLParser::BConstExprContext *ctx) override { return visitCtx(ctx); }

    BooleanConstNode *visitCtx(WPLParser::BooleanConstContext *ctx);
    std::any visitBooleanConst(WPLParser::BooleanConstContext *ctx) override { return visitCtx(ctx); }

    StringConstNode *visitCtx(WPLParser::SConstExprContext *ctx);
    std::any visitSConstExpr(WPLParser::SConstExprContext *ctx) override { return visitCtx(ctx); }

    LogAndExprNode *visitCtx(WPLParser::LogAndExprContext *ctx);
    std::any visitLogAndExpr(WPLParser::LogAndExprContext *ctx) override { return visitCtx(ctx); }

    LogOrExprNode *visitCtx(WPLParser::LogOrExprContext *ctx);
    std::any visitLogOrExpr(WPLParser::LogOrExprContext *ctx) override { return visitCtx(ctx); }

    EqExprNode *visitCtx(WPLParser::EqExprContext *ctx);
    std::any visitEqExpr(WPLParser::EqExprContext *ctx) override { return visitCtx(ctx); }

    std::optional<UnaryExprNode *> visitCtx(WPLParser::UnaryExprContext *ctx);
    std::any visitUnaryExpr(WPLParser::UnaryExprContext *ctx) override { return visitCtx(ctx); }

    std::optional<BinaryArithNode *> visitCtx(WPLParser::BinaryArithExprContext *ctx);
    std::any visitBinaryArithExpr(WPLParser::BinaryArithExprContext *ctx) override { return visitCtx(ctx); }

    std::optional<TypedNode *> visitCtx(WPLParser::ParenExprContext *ctx);
    std::any visitParenExpr(WPLParser::ParenExprContext *ctx) override { return visitCtx(ctx); }

    std::optional<FieldAccessNode*> visitCtx(WPLParser::FieldAccessExprContext *ctx);
    std::any visitFieldAccessExpr(WPLParser::FieldAccessExprContext *ctx) override { return visitCtx(ctx); }

    std::optional<ArrayAccessNode*> visitCtx(WPLParser::ArrayAccessContext *ctx);
    std::any visitArrayAccess(WPLParser::ArrayAccessContext *ctx) override { return visitCtx(ctx); }

    std::optional<ArrayAccessNode*> visitCtx(WPLParser::ArrayAccessExprContext *ctx) { return this->visitCtx(ctx->arrayAccess()); }
    std::any visitArrayAccessExpr(WPLParser::ArrayAccessExprContext *ctx) override { return visitCtx(ctx); }

    std::optional<TypedNode*> visitCtx(WPLParser::ArrayOrVarContext *ctx);
    std::any visitArrayOrVar(WPLParser::ArrayOrVarContext *ctx) override { return visitCtx(ctx); }

    std::optional<AssignNode*> visitCtx(WPLParser::AssignStatementContext *ctx);
    std::any visitAssignStatement(WPLParser::AssignStatementContext *ctx) override { return visitCtx(ctx); }

    std::optional<ParameterListNode> visitCtx(WPLParser::ParameterListContext *ctx);
    std::any visitParameterList(WPLParser::ParameterListContext *ctx) override { return visitCtx(ctx); }

    std::optional<LambdaConstNode *> visitCtx(WPLParser::LambdaConstExprContext *ctx);
    std::any visitLambdaConstExpr(WPLParser::LambdaConstExprContext *ctx) override { return visitCtx(ctx); }

    std::optional<BlockNode*> visitCtx(WPLParser::BlockStatementContext *ctx) { return this->visitCtx(ctx->block()); }
    std::any visitBlockStatement(WPLParser::BlockStatementContext *ctx) override { return visitCtx(ctx); }

    std::optional<BlockNode*> visitCtx(WPLParser::BlockContext *ctx) { return this->safeVisitBlock(ctx, true); }
    std::any visitBlock(WPLParser::BlockContext *ctx) override { return visitCtx(ctx); }

    std::optional<ExternNode*> visitCtx(WPLParser::ExternStatementContext *ctx);
    std::any visitExternStatement(WPLParser::ExternStatementContext *ctx) override { return visitCtx(ctx); }

    ParameterNode visitCtx(WPLParser::ParameterContext *ctx);
    std::any visitParameter(WPLParser::ParameterContext *ctx) override { return visitCtx(ctx); }

    std::optional<InvocationNode*> visitCtx(WPLParser::InvocationContext *ctx);
    std::any visitInvocation(WPLParser::InvocationContext *ctx) override { return visitCtx(ctx); }

    std::optional<InvocationNode*> visitCtx(WPLParser::CallStatementContext *ctx) { return this->visitCtx(ctx->call); }
    std::any visitCallStatement(WPLParser::CallStatementContext *ctx) override { return visitCtx(ctx); }

    std::optional<InvocationNode*> visitCtx(WPLParser::CallExprContext *ctx) { return this->visitCtx(ctx->call); }
    std::any visitCallExpr(WPLParser::CallExprContext *ctx) override { return visitCtx(ctx); }

    std::optional<ConditionNode *> visitCtx(WPLParser::ConditionContext *ctx);
    std::any visitCondition(WPLParser::ConditionContext *ctx) override { return visitCtx(ctx); }

    std::optional<BinaryRelNode* > visitCtx(WPLParser::BinaryRelExprContext *ctx);
    std::any visitBinaryRelExpr(WPLParser::BinaryRelExprContext *ctx) override { return visitCtx(ctx); }

    std::optional<SelectAlternativeNode* > visitCtx(WPLParser::SelectAlternativeContext *ctx);
    std::any visitSelectAlternative(WPLParser::SelectAlternativeContext *ctx) override { return visitCtx(ctx); }

    std::any visitProgDef(WPLParser::ProgDefContext *ctx) override { return this->visitInvokeable(ctx->defineProc()); }
    std::any visitDefineProgram(WPLParser::DefineProgramContext *ctx) override { return visitInvokeable(ctx->defineProc()); } // FIXME: DO BETTER!!!

    std::optional<SelectStatementNode *> visitCtx(WPLParser::SelectStatementContext *ctx);
    std::any visitSelectStatement(WPLParser::SelectStatementContext *ctx) override { return visitCtx(ctx); }

    std::optional<ConditionalStatementNode*> visitCtx(WPLParser::ConditionalStatementContext *ctx);
    std::any visitConditionalStatement(WPLParser::ConditionalStatementContext *ctx) override { return visitCtx(ctx); }

    std::optional<WhileLoopNode*> visitCtx(WPLParser::ProgramLoopContext *ctx);
    std::any visitProgramLoop(WPLParser::ProgramLoopContext *ctx) override { return visitCtx(ctx); }

    std::optional<ReturnNode*> visitCtx(WPLParser::ReturnStatementContext *ctx);
    std::any visitReturnStatement(WPLParser::ReturnStatementContext *ctx) override { return visitCtx(ctx); }

    std::optional<DefineEnumNode*> visitCtx(WPLParser::DefineEnumContext *ctx);
    std::any visitDefineEnum(WPLParser::DefineEnumContext *ctx) override { return visitCtx(ctx); }

    std::optional<DefineStructNode*> visitCtx(WPLParser::DefineStructContext *ctx);
    std::any visitDefineStruct(WPLParser::DefineStructContext *ctx) override { return visitCtx(ctx); }

    std::optional<InitProductNode*> visitCtx(WPLParser::InitProductContext *ctx);
    std::any visitInitProduct(WPLParser::InitProductContext *ctx) override { return visitCtx(ctx); }

    std::optional<ProgramSendNode*> TvisitProgramSend(WPLParser::ProgramSendContext *ctx);
    std::any visitProgramSend(WPLParser::ProgramSendContext *ctx) override { return TvisitProgramSend(ctx); }

    std::optional<ProgramRecvNode*> TvisitAssignableRecv(WPLParser::AssignableRecvContext *ctx);
    std::any visitAssignableRecv(WPLParser::AssignableRecvContext *ctx) override { return TvisitAssignableRecv(ctx); }

    std::optional<ProgramContractNode*> TvisitProgramContract(WPLParser::ProgramContractContext *ctx);
    std::any visitProgramContract(WPLParser::ProgramContractContext *ctx) override { return TvisitProgramContract(ctx); }
    
    std::optional<ProgramWeakenNode*> TvisitProgramWeaken(WPLParser::ProgramWeakenContext *ctx);
    std::any visitProgramWeaken(WPLParser::ProgramWeakenContext *ctx) override { return TvisitProgramWeaken(ctx); }

    std::optional<ProgramExecNode*> TvisitAssignableExec(WPLParser::AssignableExecContext *ctx);
    std::any visitAssignableExec(WPLParser::AssignableExecContext *ctx) override { return TvisitAssignableExec(ctx); }

    std::optional<ProgramAcceptNode*> TvisitProgramAccept(WPLParser::ProgramAcceptContext *ctx);
    std::any visitProgramAccept(WPLParser::ProgramAcceptContext *ctx) override { return TvisitProgramAccept(ctx); }
    

//CompilationUnitNode
    std::optional<CompilationUnitNode*> visitCtx(WPLParser::CompilationUnitContext *ctx);
    std::any visitCompilationUnit(WPLParser::CompilationUnitContext *ctx) override { return visitCtx(ctx); }

    // const Type *visitCtx(WPLParser::VariableExprContext *ctx);
    const Type *visitCtx(WPLParser::AssignmentContext *ctx);
    const Type *visitCtx(WPLParser::VarDeclStatementContext *ctx);


    /*
     *  Types
     */
    const Type *visitCtx(WPLParser::BaseTypeContext *ctx);
    std::any visitBaseType(WPLParser::BaseTypeContext *ctx) override { return visitCtx(ctx); }

    const Type *visitCtx(WPLParser::ArrayTypeContext *ctx);
    std::any visitArrayType(WPLParser::ArrayTypeContext *ctx) override { return visitCtx(ctx); }

    const Type *visitCtx(WPLParser::LambdaTypeContext *ctx);
    std::any visitLambdaType(WPLParser::LambdaTypeContext *ctx) override { return visitCtx(ctx); }

    const Type *visitCtx(WPLParser::ChannelTypeContext *ctx);
    std::any visitChannelType(WPLParser::ChannelTypeContext *ctx) override { return visitCtx(ctx); }

    const Type *visitCtx(WPLParser::CustomTypeContext *ctx);
    std::any visitCustomType(WPLParser::CustomTypeContext *ctx) override { return visitCtx(ctx); }
    
    const Type *visitCtx(WPLParser::TypeOrVarContext *ctx);
    std::any visitTypeOrVar(WPLParser::TypeOrVarContext *ctx) override { return visitCtx(ctx); }

    const Type *visitCtx(WPLParser::SumTypeContext *ctx); // FIXME: NEED TO DO THIS & OTHERS!
    std::any visitSumType(WPLParser::SumTypeContext *ctx) override { return visitCtx(ctx); }






    const Type *visitCtx(WPLParser::MatchStatementContext *ctx);
    std::any visitMatchStatement(WPLParser::MatchStatementContext *ctx) override { return visitCtx(ctx); }
    



    /*
     *  Protocols
     */
    const Protocol *visitProto(WPLParser::ProtocolContext *ctx);
    const Protocol *visitProto(WPLParser::RecvTypeContext *ctx);
    const Protocol *visitProto(WPLParser::SendTypeContext *ctx);
    const Protocol *visitProto(WPLParser::WnProtoContext *ctx);
    const Protocol *visitProto(WPLParser::OcProtoContext *ctx);
    const Protocol *visitProto(WPLParser::ExtChoiceProtoContext *ctx);
    const Protocol *visitProto(WPLParser::IntChoiceProtoContext *ctx);

    std::any visitProtocol(WPLParser::ProtocolContext *ctx) override { return visitProto(ctx); }
    std::any visitRecvType(WPLParser::RecvTypeContext *ctx) override { return visitProto(ctx); }
    std::any visitSendType(WPLParser::SendTypeContext *ctx) override { return visitProto(ctx); }
    std::any visitWnProto(WPLParser::WnProtoContext *ctx) override { return visitProto(ctx); }
    std::any visitOcProto(WPLParser::OcProtoContext *ctx) override { return visitProto(ctx); }
    std::any visitExtChoiceProto(WPLParser::ExtChoiceProtoContext *ctx) override { return visitProto(ctx); }
    std::any visitIntChoiceProto(WPLParser::IntChoiceProtoContext *ctx) override { return visitProto(ctx); }



    /*
     * Traditional visitor methods all overridden with our typed versions
     */
    // std::any visitVariableExpr(WPLParser::VariableExprContext *ctx) override { return visitCtx(ctx); }
    std::any visitAssignment(WPLParser::AssignmentContext *ctx) override { return visitCtx(ctx); }
    std::any visitVarDeclStatement(WPLParser::VarDeclStatementContext *ctx) override { return visitCtx(ctx); }
    

    std::any visitProgramCase(WPLParser::ProgramCaseContext *ctx) override { return TvisitProgramCase(ctx); }
    const Type *TvisitProgramCase(WPLParser::ProgramCaseContext *ctx);

    std::any visitProgramProject(WPLParser::ProgramProjectContext *ctx) override { return TvisitProgramProject(ctx); }
    const Type *TvisitProgramProject(WPLParser::ProgramProjectContext *ctx);

    /**
     * @brief Used to safely enter a block. This is used to ensure there aren't FUNC/PROC definitions / code following returns in it.
     *
     * @param ctx The BlockContext to visit
     * @param newScope  true if we should enter a new scope, false otherwise
     * @return const Type* Types::UNDEFINED as this is a statement and not a value
     */
    std::optional<BlockNode*> safeVisitBlock(WPLParser::BlockContext *ctx, bool newScope)
    {
        // Enter a new scope if desired
        if (newScope)
            stmgr->enterScope(StopType::NONE); //FIXME: DO BETTER?


        std::vector<TypedNode *> nodes; 

        // Tracks if we have found a return statement or not
        bool foundReturn = false;
        for (auto e : ctx->stmts)
        {
            // Visit all the statements in the block
            std::optional<TypedNode*> tnOpt = any2Opt<TypedNode*>(e->accept(this));

            if(!tnOpt) return {}; //FIXME: DO BETTER

            nodes.push_back(tnOpt.value());

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

        return new BlockNode(nodes); //FIXME: DO BETTER< HANDLE ERRORS! CURRENTLY ALWAYS RETURNS NODE
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
    std::optional<ProgramDefNode *> visitInvokeable(WPLParser::DefineProcContext *ctx)
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

        Symbol * channelSymbol = new Symbol(ctx->channelName->getText(), funcType->getChannelType()->getCopy(), false, false);

        stmgr->addSymbol(channelSymbol);
        // In the new scope. set our return type. We use @RETURN as it is not a valid symbol the programmer could write in the language
        // stmgr->addSymbol(new Symbol("@RETURN", funcType->getReturnType(), false, false));

        // Safe visit the program block without creating a new scope (as we are managing the scope)
        std::optional<BlockNode*> blkOpt = this->safeVisitBlock(ctx->block(), false);
        if(!blkOpt) return {}; 

        // If we have a return type, make sure that we return as the last statement in the FUNC. The type of the return is managed when we visited it.
        // if (ty && (ctx->block()->stmts.size() == 0 || !dynamic_cast<WPLParser::ReturnStatementContext *>(ctx->block()->stmts.at(ctx->block()->stmts.size() - 1))))
        // {
        //     errorHandler.addSemanticError(ctx->getStart(), "Function must end in return statement"); //FIXME: we don't have returns anymore...
        // }

        // Safe exit the scope.
        safeExitScope(ctx);

        // Add a binding in the property manager
        // bindings->bind(ctx, funcSymbol);
        // bindings->bind(ctx->VARIABLE().at(1), channelSymbol);

        return new ProgramDefNode(funcId, channelSymbol, blkOpt.value(), funcType);
    }


    const Type *any2Type(std::any any)
    {
        // if(!any) return {};
        std::optional<const Type*> valOpt = any2Opt<const Type*>(any);
        if(!valOpt) return Types::UNDEFINED; 
        return valOpt.value(); 
        // if (const Type *valOpt = std::any_cast<const Type *>(any))
            // return valOpt;

        // return Types::UNDEFINED; // TODO: DO BETTER
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
            std::vector<Symbol *> lins = scope->getRemainingLinearTypes();

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