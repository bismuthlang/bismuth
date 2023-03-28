#pragma once
#include "antlr4-runtime.h"
#include "BismuthBaseVisitor.h"
#include "STManager.h"
#include "PropertyManager.h"
#include "BismuthErrorHandler.h"
#include "CompilerFlags.h"
#include "TypedAST.h"
#include "CastUtils.h"

// #include "TypeVisitor.h"

#include "LinkedMap.h"

#include <regex>
#include <variant>
// typedef std::variant<Value, START_LOOP, END_LOOP, SEL> Message;
// typedef

class SemanticVisitor : BismuthBaseVisitor
{

public:
    /**
     * @brief Construct a new Semantic Visitor object
     *
     * @param s Symbol table manager to use
     * @param p Property manager to use
     * @param f Compiler flags
     */
    SemanticVisitor(STManager *s, int f = 0)
    {
        stmgr = s;

        flags = f;
    }

    std::string getErrors() { return errorHandler.errorList(); }
    bool hasErrors(int flags) { return errorHandler.hasErrors(flags); }

    // From C++ Documentation for visitors
    template <class... Ts>
    struct overloaded : Ts...
    {
        using Ts::operator()...;
    };
    template <class... Ts>
    overloaded(Ts...) -> overloaded<Ts...>;

    std::variant<IConstExprNode *, ErrorChain *> visitCtx(BismuthParser::IConstExprContext *ctx);
    // std::variant<TypedNode*, ErrorChain*> visitCtx(BismuthParser::IConstExprContext *ctx) { return  }
    std::any visitIConstExpr(BismuthParser::IConstExprContext *ctx) override { return TNVariantCast<IConstExprNode>(visitCtx(ctx)); }

    std::variant<BooleanConstNode *, ErrorChain *> visitCtx(BismuthParser::BConstExprContext *ctx) { return visitCtx(ctx->booleanConst()); }
    std::any visitBConstExpr(BismuthParser::BConstExprContext *ctx) override { return TNVariantCast<BooleanConstNode>(visitCtx(ctx)); }

    std::variant<BooleanConstNode *, ErrorChain *> visitCtx(BismuthParser::BooleanConstContext *ctx);
    std::any visitBooleanConst(BismuthParser::BooleanConstContext *ctx) override { return TNVariantCast<BooleanConstNode>(visitCtx(ctx)); }

    std::variant<StringConstNode *, ErrorChain *> visitCtx(BismuthParser::SConstExprContext *ctx);
    std::any visitSConstExpr(BismuthParser::SConstExprContext *ctx) override { return TNVariantCast<StringConstNode>(visitCtx(ctx)); }

    std::variant<LogAndExprNode *, ErrorChain *> visitCtx(BismuthParser::LogAndExprContext *ctx);
    std::any visitLogAndExpr(BismuthParser::LogAndExprContext *ctx) override { return TNVariantCast<LogAndExprNode>(visitCtx(ctx)); }

    std::variant<LogOrExprNode *, ErrorChain *> visitCtx(BismuthParser::LogOrExprContext *ctx);
    std::any visitLogOrExpr(BismuthParser::LogOrExprContext *ctx) override { return TNVariantCast<LogOrExprNode>(visitCtx(ctx)); }

    std::variant<EqExprNode *, ErrorChain *> visitCtx(BismuthParser::EqExprContext *ctx);
    std::any visitEqExpr(BismuthParser::EqExprContext *ctx) override { return TNVariantCast<EqExprNode>(visitCtx(ctx)); }

    std::variant<UnaryExprNode *, ErrorChain *> visitCtx(BismuthParser::UnaryExprContext *ctx);
    std::any visitUnaryExpr(BismuthParser::UnaryExprContext *ctx) override { return TNVariantCast<UnaryExprNode>(visitCtx(ctx)); }

    std::variant<BinaryArithNode *, ErrorChain *> visitCtx(BismuthParser::BinaryArithExprContext *ctx);
    std::any visitBinaryArithExpr(BismuthParser::BinaryArithExprContext *ctx) override { return TNVariantCast<BinaryArithNode>(visitCtx(ctx)); }

    std::variant<TypedNode *, ErrorChain *> visitCtx(BismuthParser::ParenExprContext *ctx);
    std::any visitParenExpr(BismuthParser::ParenExprContext *ctx) override { return TNVariantCast<TypedNode>(visitCtx(ctx)); }

    std::variant<FieldAccessNode *, ErrorChain *> visitCtx(BismuthParser::FieldAccessExprContext *ctx, bool is_rvalue);
    std::any visitFieldAccessExpr(BismuthParser::FieldAccessExprContext *ctx) override { return TNVariantCast<FieldAccessNode>(visitCtx(ctx, true)); }

    std::variant<DerefBoxNode *, ErrorChain *> visitCtx(BismuthParser::DereferenceExprContext *ctx, bool is_rvalue);
    std::any visitDereferenceExpr(BismuthParser::DereferenceExprContext *ctx) override { return TNVariantCast<DerefBoxNode>(visitCtx(ctx, true)); }

    // std::optional<ArrayAccessNode*> visitCtx(BismuthParser::ArrayAccessContext *ctx);
    std::variant<ArrayAccessNode *, ErrorChain *> visitCtx(BismuthParser::ArrayAccessContext *ctx, bool is_rvalue);
    std::any visitArrayAccess(BismuthParser::ArrayAccessContext *ctx) override { return TNVariantCast<ArrayAccessNode>(visitCtx(ctx, true)); }

    std::variant<ArrayAccessNode *, ErrorChain *> visitCtx(BismuthParser::ArrayAccessExprContext *ctx) { return this->visitCtx(ctx->arrayAccess(), true); }
    std::any visitArrayAccessExpr(BismuthParser::ArrayAccessExprContext *ctx) override { return TNVariantCast<ArrayAccessNode>(visitCtx(ctx)); }

    std::variant<TypedNode *, ErrorChain *> visitCtx(BismuthParser::LValueContext *ctx);
    std::any visitLValue(BismuthParser::LValueContext *ctx) override { return TNVariantCast<TypedNode>(visitCtx(ctx)); }

    std::variant<AssignNode *, ErrorChain *> visitCtx(BismuthParser::AssignStatementContext *ctx);
    std::any visitAssignStatement(BismuthParser::AssignStatementContext *ctx) override { return TNVariantCast<AssignNode>(visitCtx(ctx)); }

    std::optional<ParameterListNode> visitCtx(BismuthParser::ParameterListContext *ctx);
    std::any visitParameterList(BismuthParser::ParameterListContext *ctx) override { return visitCtx(ctx); }

    std::variant<LambdaConstNode *, ErrorChain *> visitCtx(BismuthParser::LambdaConstExprContext *ctx);
    std::any visitLambdaConstExpr(BismuthParser::LambdaConstExprContext *ctx) override { return TNVariantCast<LambdaConstNode>(visitCtx(ctx)); }

    std::variant<BlockNode *, ErrorChain *> visitCtx(BismuthParser::BlockStatementContext *ctx) { return this->visitCtx(ctx->block()); }
    std::any visitBlockStatement(BismuthParser::BlockStatementContext *ctx) override { return TNVariantCast<BlockNode>(visitCtx(ctx)); }

    std::variant<BlockNode *, ErrorChain *> visitCtx(BismuthParser::BlockContext *ctx) { return this->safeVisitBlock(ctx, true); }
    std::any visitBlock(BismuthParser::BlockContext *ctx) override { return TNVariantCast<BlockNode>(visitCtx(ctx)); }

    std::variant<ExternNode *, ErrorChain *> visitCtx(BismuthParser::ExternStatementContext *ctx);
    std::any visitExternStatement(BismuthParser::ExternStatementContext *ctx) override { return TNVariantCast<ExternNode>(visitCtx(ctx)); }

    ParameterNode visitCtx(BismuthParser::ParameterContext *ctx);
    std::any visitParameter(BismuthParser::ParameterContext *ctx) override { return visitCtx(ctx); }

    std::variant<InvocationNode *, ErrorChain *> visitCtx(BismuthParser::InvocationContext *ctx);
    std::any visitInvocation(BismuthParser::InvocationContext *ctx) override { return TNVariantCast<InvocationNode>(visitCtx(ctx)); }

    std::variant<InvocationNode *, ErrorChain *> visitCtx(BismuthParser::CallStatementContext *ctx) { return this->visitCtx(ctx->call); }
    std::any visitCallStatement(BismuthParser::CallStatementContext *ctx) override { return TNVariantCast<InvocationNode>(visitCtx(ctx)); }

    std::variant<InvocationNode *, ErrorChain *> visitCtx(BismuthParser::CallExprContext *ctx) { return this->visitCtx(ctx->call); }
    std::any visitCallExpr(BismuthParser::CallExprContext *ctx) override { return TNVariantCast<InvocationNode>(visitCtx(ctx)); }

    std::variant<TypedNode *, ErrorChain *> visitCtx(BismuthParser::ConditionContext *ctx) { return this->visitCondition(ctx->ex); }
    std::any visitCondition(BismuthParser::ConditionContext *ctx) override { return visitCtx(ctx); }

    std::variant<BinaryRelNode *, ErrorChain *> visitCtx(BismuthParser::BinaryRelExprContext *ctx);
    std::any visitBinaryRelExpr(BismuthParser::BinaryRelExprContext *ctx) override { return TNVariantCast<BinaryRelNode>(visitCtx(ctx)); }

    std::variant<SelectAlternativeNode *, ErrorChain *> visitCtx(BismuthParser::SelectAlternativeContext *ctx);
    std::any visitSelectAlternative(BismuthParser::SelectAlternativeContext *ctx) override { return TNVariantCast<SelectAlternativeNode>(visitCtx(ctx)); }

    std::any visitProgDef(BismuthParser::ProgDefContext *ctx) override { return TNVariantCast<ProgramDefNode>(this->visitInvokeable(ctx->defineProc())); }
    std::any visitDefineProgram(BismuthParser::DefineProgramContext *ctx) override { return TNVariantCast<ProgramDefNode>(visitInvokeable(ctx->defineProc())); }

    std::variant<LambdaConstNode *, ErrorChain *> visitCtx(BismuthParser::DefineFuncContext *ctx);
    std::any visitDefineFunc(BismuthParser::DefineFuncContext *ctx) override { return TNVariantCast<LambdaConstNode>(visitCtx(ctx)); }
    std::any visitFuncDef(BismuthParser::FuncDefContext *ctx) override { return TNVariantCast<LambdaConstNode>(visitCtx(ctx->defineFunc())); }
    std::any visitDefineFunction(BismuthParser::DefineFunctionContext *ctx) override { return TNVariantCast<LambdaConstNode>(visitCtx(ctx->defineFunc())); }

    std::variant<SelectStatementNode *, ErrorChain *> visitCtx(BismuthParser::SelectStatementContext *ctx);
    std::any visitSelectStatement(BismuthParser::SelectStatementContext *ctx) override { return TNVariantCast<SelectStatementNode>(visitCtx(ctx)); }

    std::variant<ConditionalStatementNode *, ErrorChain *> visitCtx(BismuthParser::ConditionalStatementContext *ctx);
    std::any visitConditionalStatement(BismuthParser::ConditionalStatementContext *ctx) override { return TNVariantCast<ConditionalStatementNode>(visitCtx(ctx)); }

    std::variant<WhileLoopNode *, ErrorChain *> visitCtx(BismuthParser::ProgramLoopContext *ctx);
    std::any visitProgramLoop(BismuthParser::ProgramLoopContext *ctx) override { return TNVariantCast<WhileLoopNode>(visitCtx(ctx)); }

    std::variant<ReturnNode *, ErrorChain *> visitCtx(BismuthParser::ReturnStatementContext *ctx);
    std::any visitReturnStatement(BismuthParser::ReturnStatementContext *ctx) override { return TNVariantCast<ReturnNode>(visitCtx(ctx)); }

    std::variant<DefineEnumNode *, ErrorChain *> visitCtx(BismuthParser::DefineEnumContext *ctx);
    std::any visitDefineEnum(BismuthParser::DefineEnumContext *ctx) override { return TNVariantCast<DefineEnumNode>(visitCtx(ctx)); }

    std::variant<DefineStructNode *, ErrorChain *> visitCtx(BismuthParser::DefineStructContext *ctx);
    std::any visitDefineStruct(BismuthParser::DefineStructContext *ctx) override { return TNVariantCast<DefineStructNode>(visitCtx(ctx)); }

    std::variant<InitProductNode *, ErrorChain *> visitCtx(BismuthParser::InitProductContext *ctx);
    std::any visitInitProduct(BismuthParser::InitProductContext *ctx) override { return TNVariantCast<InitProductNode>(visitCtx(ctx)); }

    std::variant<InitBoxNode *, ErrorChain *> visitCtx(BismuthParser::InitBoxContext *ctx);
    std::any visitInitBox(BismuthParser::InitBoxContext *ctx) override { return TNVariantCast<InitBoxNode>(visitCtx(ctx)); }

    std::variant<ProgramSendNode *, ErrorChain *> TvisitProgramSend(BismuthParser::ProgramSendContext *ctx);
    std::any visitProgramSend(BismuthParser::ProgramSendContext *ctx) override { return TNVariantCast<ProgramSendNode>(TvisitProgramSend(ctx)); }

    std::variant<ProgramRecvNode *, ErrorChain *> TvisitAssignableRecv(BismuthParser::AssignableRecvContext *ctx);
    std::any visitAssignableRecv(BismuthParser::AssignableRecvContext *ctx) override { return TNVariantCast<ProgramRecvNode>(TvisitAssignableRecv(ctx)); }

    std::variant<ProgramContractNode *, ErrorChain *> TvisitProgramContract(BismuthParser::ProgramContractContext *ctx);
    std::any visitProgramContract(BismuthParser::ProgramContractContext *ctx) override { return TNVariantCast<ProgramContractNode>(TvisitProgramContract(ctx)); }

    std::variant<ProgramWeakenNode *, ErrorChain *> TvisitProgramWeaken(BismuthParser::ProgramWeakenContext *ctx);
    std::any visitProgramWeaken(BismuthParser::ProgramWeakenContext *ctx) override { return TNVariantCast<ProgramWeakenNode>(TvisitProgramWeaken(ctx)); }

    std::variant<ProgramExecNode *, ErrorChain *> TvisitAssignableExec(BismuthParser::AssignableExecContext *ctx);
    std::any visitAssignableExec(BismuthParser::AssignableExecContext *ctx) override { return TNVariantCast<ProgramExecNode>(TvisitAssignableExec(ctx)); }

    std::variant<ProgramAcceptNode *, ErrorChain *> TvisitProgramAccept(BismuthParser::ProgramAcceptContext *ctx);
    std::any visitProgramAccept(BismuthParser::ProgramAcceptContext *ctx) override { return TNVariantCast<ProgramAcceptNode>(TvisitProgramAccept(ctx)); }

    std::variant<ProgramAcceptWhileNode *, ErrorChain *> TvisitProgramAcceptWhile(BismuthParser::ProgramAcceptWhileContext *ctx);
    std::any visitProgramAcceptWhile(BismuthParser::ProgramAcceptWhileContext *ctx) override { return TNVariantCast<ProgramAcceptWhileNode>(TvisitProgramAcceptWhile(ctx)); }

    std::variant<CompilationUnitNode *, ErrorChain *> visitCtx(BismuthParser::CompilationUnitContext *ctx);
    std::any visitCompilationUnit(BismuthParser::CompilationUnitContext *ctx) override { return visitCtx(ctx); }

    std::variant<VarDeclNode *, ErrorChain *> visitCtx(BismuthParser::VarDeclStatementContext *ctx);
    std::any visitVarDeclStatement(BismuthParser::VarDeclStatementContext *ctx) override { return TNVariantCast<>(visitCtx(ctx)); }

    std::variant<MatchStatementNode *, ErrorChain *> visitCtx(BismuthParser::MatchStatementContext *ctx);
    std::any visitMatchStatement(BismuthParser::MatchStatementContext *ctx) override { return TNVariantCast<>(visitCtx(ctx)); } // NOTE: CASTS NEEDED B/C OF HOW C++ HANDLES ANYs BY MANGLED NAME!

    std::variant<ExitNode *, ErrorChain *> visitCtx(BismuthParser::ExitStatementContext *ctx);
    std::any visitExitStatement(BismuthParser::ExitStatementContext *ctx) override { return TNVariantCast<>(visitCtx(ctx)); }

    // const Type *visitCtx(BismuthParser::VariableExprContext *ctx);
    const Type *visitCtx(BismuthParser::AssignmentContext *ctx);

    /*
     *  Types
     */
    const Type *visitCtx(BismuthParser::BaseTypeContext *ctx);
    std::any visitBaseType(BismuthParser::BaseTypeContext *ctx) override { return visitCtx(ctx); }

    const Type *visitCtx(BismuthParser::ArrayTypeContext *ctx);
    std::any visitArrayType(BismuthParser::ArrayTypeContext *ctx) override { return visitCtx(ctx); }

    const Type *visitCtx(BismuthParser::LambdaTypeContext *ctx);
    std::any visitLambdaType(BismuthParser::LambdaTypeContext *ctx) override { return visitCtx(ctx); }

    const Type *visitCtx(BismuthParser::ChannelTypeContext *ctx);
    std::any visitChannelType(BismuthParser::ChannelTypeContext *ctx) override { return visitCtx(ctx); }

    const Type *visitCtx(BismuthParser::BoxTypeContext *ctx);
    std::any visitBoxType(BismuthParser::BoxTypeContext *ctx) override { return visitCtx(ctx); }

    const Type *visitCtx(BismuthParser::ProgramTypeContext *ctx);
    std::any visitProgramType(BismuthParser::ProgramTypeContext *ctx) override { return visitCtx(ctx); }

    const Type *visitCtx(BismuthParser::CustomTypeContext *ctx);
    std::any visitCustomType(BismuthParser::CustomTypeContext *ctx) override { return visitCtx(ctx); }

    const Type *visitCtx(BismuthParser::TypeOrVarContext *ctx);
    std::any visitTypeOrVar(BismuthParser::TypeOrVarContext *ctx) override { return visitCtx(ctx); }

    const Type *visitCtx(BismuthParser::SumTypeContext *ctx);
    std::any visitSumType(BismuthParser::SumTypeContext *ctx) override { return visitCtx(ctx); }

    /*
     *  Protocols
     */
    const Protocol *visitProto(BismuthParser::ProtocolContext *ctx);
    const Protocol *visitProto(BismuthParser::RecvTypeContext *ctx);
    const Protocol *visitProto(BismuthParser::SendTypeContext *ctx);
    const Protocol *visitProto(BismuthParser::WnProtoContext *ctx);
    const Protocol *visitProto(BismuthParser::OcProtoContext *ctx);
    const Protocol *visitProto(BismuthParser::ExtChoiceProtoContext *ctx);
    const Protocol *visitProto(BismuthParser::IntChoiceProtoContext *ctx);

    std::any visitProtocol(BismuthParser::ProtocolContext *ctx) override { return visitProto(ctx); }
    std::any visitRecvType(BismuthParser::RecvTypeContext *ctx) override { return visitProto(ctx); }
    std::any visitSendType(BismuthParser::SendTypeContext *ctx) override { return visitProto(ctx); }
    std::any visitWnProto(BismuthParser::WnProtoContext *ctx) override { return visitProto(ctx); }
    std::any visitOcProto(BismuthParser::OcProtoContext *ctx) override { return visitProto(ctx); }
    std::any visitExtChoiceProto(BismuthParser::ExtChoiceProtoContext *ctx) override { return visitProto(ctx); }
    std::any visitIntChoiceProto(BismuthParser::IntChoiceProtoContext *ctx) override { return visitProto(ctx); }

    /*
     * Traditional visitor methods all overridden with our typed versions
     */
    // std::any visitVariableExpr(BismuthParser::VariableExprContext *ctx) override { return visitCtx(ctx); }
    std::any visitAssignment(BismuthParser::AssignmentContext *ctx) override { return visitCtx(ctx); }

    std::variant<ChannelCaseStatementNode *, ErrorChain *> TvisitProgramCase(BismuthParser::ProgramCaseContext *ctx);
    std::any visitProgramCase(BismuthParser::ProgramCaseContext *ctx) override { return TNVariantCast<ChannelCaseStatementNode>(TvisitProgramCase(ctx)); }

    std::variant<ProgramProjectNode *, ErrorChain *> TvisitProgramProject(BismuthParser::ProgramProjectContext *ctx);
    std::any visitProgramProject(BismuthParser::ProgramProjectContext *ctx) override { return TNVariantCast<ProgramProjectNode>(TvisitProgramProject(ctx)); }

    std::variant<TypedNode *, ErrorChain *> visitCondition(BismuthParser::ExpressionContext *ex)
    {
        std::variant<TypedNode *, ErrorChain *> condOpt = anyOpt2VarError<TypedNode>(errorHandler, ex->accept(this));

        if (ErrorChain **e = std::get_if<ErrorChain *>(&condOpt))
        {
            (*e)->addError(ex->getStart(), "Unable to typecheck condition expression.");
            return *e;
        }

        TypedNode *cond = std::get<TypedNode *>(condOpt);
        const Type *conditionType = cond->getType();

        if (conditionType->isNotSubtype(Types::BOOL))
        {
            return errorHandler.addError(ex->getStart(), "Condition expected BOOL, but was given " + conditionType->toString());
        }

        return cond;
    }

    /**
     * @brief Used to safely enter a block. This is used to ensure there aren't FUNC/PROC definitions / code following returns in it.
     *
     * @param ctx The BlockContext to visit
     * @param newScope  true if we should enter a new scope, false otherwise
     * @return const Type* Types::UNDEFINED as this is a statement and not a value
     */
    std::variant<BlockNode *, ErrorChain *> safeVisitBlock(BismuthParser::BlockContext *ctx, bool newScope)
    {
        // Enter a new scope if desired
        if (newScope)
            stmgr->enterScope(StopType::NONE); // TODO: DO BETTER?

        std::vector<TypedNode *> nodes;

        // Tracks if we have found a return statement or not
        bool foundReturn = false;
        for (auto e : ctx->stmts)
        {
            // Visit all the statements in the block
            std::variant<TypedNode *, ErrorChain *> tnOpt = anyOpt2VarError<TypedNode>(errorHandler, e->accept(this));

            if (ErrorChain **e = std::get_if<ErrorChain *>(&tnOpt))
            {
                (*e)->addError(ctx->getStart(), "Failed to typecheck statement in block.");
                return *e;
            }

            nodes.push_back(std::get<TypedNode *>(tnOpt));
            // If we found a return, then this is dead code, and we can break out of the loop.
            if (foundReturn)
            {
                errorHandler.addError(ctx->getStart(), "Dead code.");
                break;
            }

            // If the current statement is a return, set foundReturn = true
            if (dynamic_cast<BismuthParser::ReturnStatementContext *>(e))
                foundReturn = true;
        }

        // If we entered a new scope, then we can now safely exit a scope
        if (newScope)
            this->safeExitScope(ctx);

        return new BlockNode(nodes, ctx->getStart()); // FIXME: DO BETTER< HANDLE ERRORS! CURRENTLY ALWAYS RETURNS NODE
    }

    std::variant<Symbol *, ErrorChain *> getProgramSymbol(BismuthParser::DefineProcContext *ctx)
    {
        std::optional<Symbol *> symOpt = symBindings->getBinding(ctx);

        if (!symOpt && stmgr->lookupInCurrentScope(ctx->name->getText()))
        {
            return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of " + ctx->name->getText());
        }

        Symbol *sym = symOpt.value_or(
            new Symbol(
                ctx->name->getText(), new TypeProgram(),
                true, false));

        if (const TypeProgram *progType = dynamic_cast<const TypeProgram *>(sym->type))
        {
            // std::string funcId = ctx->name->getText();

            if (!progType->isDefined())
            {
                const Type *ty = any2Type(ctx->ty->accept(this));

                if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(ty))
                {
                    progType->setChannel(channel);
                }
                else
                {
                    return errorHandler.addError(ctx->getStart(), "Process expected channel but got " + ty->toString());
                }
            }
            return sym;
        }

        return errorHandler.addError(ctx->getStart(), "Expected program but got: " + sym->type->toString());
    }

    /**
     * @brief Visits an invokable definition (PROC or FUNC)
     *
     * @param ctx The parser rule context
     * @param funcId The name of the PROC/FUNC
     * @param paramList The parameter list for the PROC/FUNC
     * @param ty The return type (Type::UNDEFINED for PROC)
     * @param block The PROC/FUNC block
     * @return const Type* TypeInvoke if successful, empty if error
     */
    std::variant<ProgramDefNode *, ErrorChain *> visitInvokeable(BismuthParser::DefineProcContext *ctx)
    {
        std::variant<Symbol *, ErrorChain *> symOpt = getProgramSymbol(ctx);

        if (ErrorChain **e = std::get_if<ErrorChain *>(&symOpt))
        {
            return *e;
        }

        Symbol *sym = std::get<Symbol *>(symOpt);

        if (const TypeProgram *progType = dynamic_cast<const TypeProgram *>(sym->type))
        {
            std::string funcId = ctx->name->getText();

            // If the symbol name is program, do some extra checks to make sure it has no arguments and returns an INT. Otherwise, we will get a link error.
            // if (funcId == "program") //FIXME: DO BETTER
            // {
            //     if (!dynamic_cast<const TypeInt *>(progType->getReturnType()))
            //     {
            //         errorHandler.addSemanticCritWarning(ctx->getStart(), "program() should return type INT");
            //     }

            //     if (progType->getParamTypes().size() != 0)
            //     {
            //         errorHandler.addSemanticCritWarning(ctx->getStart(), "program() should have no arguments");
            //     }
            // }

            // Lookup the function in the current scope and prevent redeclaratons

            // Add the symbol to the stmgr and enter the scope.
            stmgr->addSymbol(sym);
            stmgr->enterScope(StopType::GLOBAL); // NOTE: We do NOT duplicate scopes here because we use a saveVisitBlock with newScope=false

            Symbol *channelSymbol = new Symbol(ctx->channelName->getText(), progType->getChannelType()->getCopy(), false, false);

            stmgr->addSymbol(channelSymbol);
            // In the new scope. set our return type. We use @RETURN as it is not a valid symbol the programmer could write in the language
            stmgr->addSymbol(new Symbol("@EXIT", Types::UNIT, false, false));

            // Safe visit the program block without creating a new scope (as we are managing the scope)
            std::variant<BlockNode *, ErrorChain *> blkOpt = this->safeVisitBlock(ctx->block(), false);
            if (ErrorChain **e = std::get_if<ErrorChain *>(&blkOpt))
            {
                (*e)->addError(ctx->getStart(), "Failed to safe visit block.");
                return *e;
            }

            // If we have a return type, make sure that we return as the last statement in the FUNC. The type of the return is managed when we visited it.
            // if (ty && (ctx->block()->stmts.size() == 0 || !dynamic_cast<BismuthParser::ReturnStatementContext *>(ctx->block()->stmts.at(ctx->block()->stmts.size() - 1))))
            // {
            //     errorHandler.addError(ctx->getStart(), "Function must end in return statement");
            // }

            // Safe exit the scope.
            safeExitScope(ctx);

            return new ProgramDefNode(funcId, channelSymbol, std::get<BlockNode *>(blkOpt), progType, ctx->getStart());
        }
        else
        {
            return errorHandler.addError(ctx->getStart(), "Cannot invoke " + sym->toString());
        }
    }

    struct ProtocolCompareInv
    {
        bool operator()(std::pair<const Protocol *, BismuthParser::StatementContext *> a, 
                        std::pair<const Protocol *, BismuthParser::StatementContext *> b) const
        {
            std::cout << a.first->toString() << " < " << b.first->toString() << " = " << (a.first->toString() < b.second->toString()) << std::endl; 
            return a.first->toString() < b.first->toString();
        }
    };

    struct ConditionalData
    {
        vector<TypedNode *> cases;
        // vector<TypedNode *> post;

        ConditionalData(vector<TypedNode *> cases) : cases(cases)
        {
        }
    };

    struct DeepRestData
    {
        vector<BismuthParser::StatementContext *> ctxRest;
        bool isGenerated;
        vector<TypedNode *> post;

        DeepRestData(vector<BismuthParser::StatementContext *> ctx) : ctxRest(ctx), isGenerated(false) {}
    };

    template <typename T>
    inline std::variant<ConditionalData, ErrorChain *> checkBranch(
        antlr4::ParserRuleContext *ctx,
        std::vector<T *> ctxCases,
        // std::vector<BismuthParser::StatementContext *> ctxRest,
        DeepRestData *ctxRest,
        bool checkRestIndependently,
        std::function<std::variant<TypedNode *, ErrorChain *>(T *)> typeCheck)
    {
        std::optional<std::deque<DeepRestData *> *> deepRest = restBindings->getBinding(ctx);

        std::vector<TypedNode *> cases;
        // std::vector<TypedNode *> restVec;
        // bool restVecFilled = false;

        std::vector<Symbol *> syms = stmgr->getAvailableLinears(true);                // FIXME: WILL TRY TO REBIND VAR WE JUST BOUND TO NEW CHAN VALUE!
        std::vector<std::pair<const TypeChannel *, const ProtocolSequence *>> to_fix; // FIXME: DO BETTER!
        for (Symbol *orig : syms)
        {
            // FIXME: DO BETTER, WONT WORK WITH VALUES!
            if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(orig->type))
            {
                to_fix.push_back({channel, channel->getProtocolCopy()});
            }
        }

        // const ProtocolSequence *savedRest = channel->getProtocolCopy();

        for (auto alt : ctxCases)
        {
            for (Symbol *s : syms)
            {
                stmgr->addSymbol(s);
            }
            for (auto pair : to_fix)
            {
                pair.first->setProtocol(pair.second->getCopy());
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

            // safeExitScope(ctx);
            if (!endsInReturn(caseNode) && !endsInBranch(caseNode))
            {
                for (auto s : ctxRest->ctxRest)
                {
                    std::variant<TypedNode *, ErrorChain *> rOpt = anyOpt2VarError<TypedNode>(errorHandler, s->accept(this));

                    if (ErrorChain **e = std::get_if<ErrorChain *>(&rOpt)) // FIXME: SHOULD THIS BE MOVED OUT OF IF?
                    {
                        (*e)->addError(alt->getStart(), "Failed to typecheck code following branch."); //FIXME: SWITCH THESE BACK TO ALTCTX?
                        return *e;
                    }

                    if (!ctxRest->isGenerated)
                    {
                        ctxRest->post.push_back(std::get<TypedNode *>(rOpt));
                    }
                }

                // restVecFilled = true;
                ctxRest->isGenerated = true;
            }

            // FIXME: WILL NEED TO RUN THIS CHECK ON EACH ITERATION!
            if (deepRest && !endsInReturn(ctxRest->post) && !endsInBranch(ctxRest->post))
            {
                for (auto r : *(deepRest.value()))
                {
                    for (auto s : r->ctxRest)
                    {
                        std::variant<TypedNode *, ErrorChain *> rOpt = anyOpt2VarError<TypedNode>(errorHandler, s->accept(this));

                        if (ErrorChain **e = std::get_if<ErrorChain *>(&rOpt)) // FIXME: SHOULD THIS BE MOVED OUT OF IF?
                        {
                            (*e)->addError(ctx->getStart(), "2097");
                            return *e;
                        }

                        if (!r->isGenerated) // FIXME: MAY CAUSE DOUBLE FILL ISSUES IF PRIOR BRANCH ERRORS (WHEN WE CHANGE TO GET ALL ERRORS)
                        {
                            r->post.push_back(std::get<TypedNode *>(rOpt));
                        }
                    }
                    r->isGenerated = true;
                }
            }

            safeExitScope(ctx); // FIXME: MAKE THIS ABLE TO TRIP ERROR?

            std::vector<Symbol *> lins = stmgr->getAvailableLinears();

            // If there are any uninferred symbols, then add it as a compiler error as we won't be able to resolve them
            // due to the var leaving the scope
            if (lins.size() > 0)
            {
                std::ostringstream details;

                for (auto e : lins)
                {
                    details << e->toString() << "; ";
                }

                errorHandler.addError(alt->getStart(), "537 Unused linear types in context: " + details.str());
            }
        }

        if (checkRestIndependently)
        {
            for (Symbol *s : syms)
            {
                stmgr->addSymbol(s);
            }
            for (auto pair : to_fix)
            {
                pair.first->setProtocol(pair.second->getCopy());
            }

            stmgr->enterScope(StopType::NONE);

            for (auto s : ctxRest->ctxRest)
            {
                std::variant<TypedNode *, ErrorChain *> rOpt = anyOpt2VarError<TypedNode>(errorHandler, s->accept(this));
                if (ErrorChain **e = std::get_if<ErrorChain *>(&rOpt))
                {
                    (*e)->addError(ctx->getStart(), "Failed to typecheck code when conditional skipped over.");
                    return *e;
                }
                if (!ctxRest->isGenerated)
                {
                    ctxRest->post.push_back(std::get<TypedNode *>(rOpt));
                }
            }

            if (deepRest && !endsInReturn(ctxRest->post))
            {
                for (auto r : *(deepRest.value())) // FIXME: NEED TO REVERSE?
                {
                    for (auto s : r->ctxRest)
                    {
                        std::variant<TypedNode *, ErrorChain *> rOpt = anyOpt2VarError<TypedNode>(errorHandler, s->accept(this));

                        if (ErrorChain **e = std::get_if<ErrorChain *>(&rOpt)) // FIXME: SHOULD THIS BE MOVED OUT OF IF?
                        {
                            (*e)->addError(ctx->getStart(), "2097");
                            return *e;
                        }

                        if (!r->isGenerated) // FIXME: MAY CAUSE DOUBLE FILL ISSUES IF PRIOR BRANCH ERRORS (WHEN WE CHANGE TO GET ALL ERRORS)
                        {
                            r->post.push_back(std::get<TypedNode *>(rOpt));
                        }
                    }
                    r->isGenerated = true;
                }
            }

            ctxRest->isGenerated = true;

            safeExitScope(ctx);

            std::vector<Symbol *> lins = stmgr->getAvailableLinears();

            // If there are any uninferred symbols, then add it as a compiler error as we won't be able to resolve them
            // due to the var leaving the scope
            if (lins.size() > 0)
            {
                std::ostringstream details;

                for (auto e : lins)
                {
                    details << e->toString() << "; ";
                }

                errorHandler.addError(ctx->getStart(), "608 Unused linear types in context: " + details.str());
            }
        }

        // return Types::UNDEFINED;
        // return ty.value();
        return ConditionalData(cases);
    }

    template <typename T>
    std::vector<T> *Append(std::vector<T> a, const std::vector<T> b)
    {
        std::vector<T> *ans = new std::vector<T>();
        ans->reserve(a.size() + b.size());
        ans->insert(ans->end(), a.begin(), a.end());
        ans->insert(ans->end(), b.begin(), b.end());
        return ans;
    }

    const Type *any2Type(std::any any)
    {
        std::optional<const Type *> valOpt = any2Opt<const Type *>(any);

        return valOpt.value_or(Types::ABSURD);
    }

    const Protocol *any2Protocol(std::any any)
    {
        if (const Protocol *valOpt = std::any_cast<const Protocol *>(any))
            return valOpt;

        return nullptr; // FIXME: DO BETTER
    }

private:
    STManager *stmgr;
    PropertyManager<Symbol> *symBindings = new PropertyManager<Symbol>();
    PropertyManager<std::deque<DeepRestData *>> *restBindings = new PropertyManager<std::deque<DeepRestData *>>();
    BismuthErrorHandler errorHandler = BismuthErrorHandler(SEMANTIC);

    int flags; // Compiler flags

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

                errorHandler.addError(ctx->getStart(), "Uninferred types in context: " + details.str());
            }
        }

        if (res.second)
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

                errorHandler.addError(ctx->getStart(), "694 Unused linear types in context: " + details.str());
            }
        }
        // return res;
    }

    // NOTE: IS THERE A WAY FOR ME TO PROVIDE ONE OF TWO TYPES TO A FN, AND THEN HAVE THAT BE RET TYPE? (BUT ONLY ONE OF TWO...)

    std::variant<Symbol *, ErrorChain *> getFunctionSymbol(BismuthParser::DefineFuncContext *ctx)
    {
        std::optional<Symbol *> opt = symBindings->getBinding(ctx);

        if (!opt && stmgr->lookupInCurrentScope(ctx->name->getText()))
        {
            return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of " + ctx->name->getText());
        }

        Symbol *sym = opt.value_or(
            new Symbol(
                ctx->name->getText(), new TypeInvoke(),
                true, false));

        if (const TypeInvoke *funcType = dynamic_cast<const TypeInvoke *>(sym->type))
        {
            if (!funcType->isDefined())
            {
                std::optional<ParameterListNode> paramTypeOpt = visitCtx(ctx->lam->parameterList());

                if (!paramTypeOpt)
                {
                    return errorHandler.addError(ctx->getStart(), "340");
                }

                ParameterListNode params = paramTypeOpt.value();
                std::vector<const Type *> ps;

                for (ParameterNode param : params)
                {
                    ps.push_back(param.type);
                }

                const Type *retType = ctx->lam->ret ? any2Type(ctx->lam->ret->accept(this))
                                                    : Types::UNIT;

                funcType->setInvoke(ps, retType);

                // stmgr->addSymbol(sym); //Maybe do this here instead? would be more similar to how others are managed...
            }

            return sym;
        }

        return errorHandler.addError(ctx->getStart(), "Expected program but got: " + sym->type->toString());
    }

    void bindRestData(antlr4::ParserRuleContext *ctx, std::deque<DeepRestData *> *rd)
    { // DeepRestData * rd) {
        if (BismuthParser::BlockStatementContext *bs = dynamic_cast<BismuthParser::BlockStatementContext *>(ctx))
        {
            return bindRestData(bs->block(), rd);
        }

        if (BismuthParser::BlockContext *blk = dynamic_cast<BismuthParser::BlockContext *>(ctx))
        {
            if (blk->stmts.size() == 0)
                return;

            return bindRestData(blk->stmts.at(blk->stmts.size() - 1), rd);
        }

        if (BismuthParser::ConditionalStatementContext *cs = dynamic_cast<BismuthParser::ConditionalStatementContext *>(ctx))
        {
            // for(auto b : cs->block()) {
            //     bindRestData(b, rd);
            // }
            restBindings->bind(cs, rd);
            return;
        }

        if (BismuthParser::SelectStatementContext *sel = dynamic_cast<BismuthParser::SelectStatementContext *>(ctx))
        {
            // for(auto c : sel->cases) {
            //     bindRestData(c->eval, rd);
            // }
            restBindings->bind(sel, rd);
            return;
        }

        if (BismuthParser::MatchStatementContext *mc = dynamic_cast<BismuthParser::MatchStatementContext *>(ctx))
        {
            // for(auto c : mc->cases) {
            //     bindRestData(c->eval, rd);
            // }
            restBindings->bind(mc, rd);
            return;
        }

        if (BismuthParser::ProgramCaseContext *cc = dynamic_cast<BismuthParser::ProgramCaseContext *>(ctx))
        {
            // for(auto o : cc->opts) {
            //     bindRestData(o->eval, rd);
            // }
            restBindings->bind(cc, rd);
            return;
        }
    }

    void isTypeCyclical(const Type *def, const Type *inner)
    {
        std::vector<const Type *> toVisit = {inner};
        std::set<const Type *> visited = {def};
    }
};