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

    std::variant<TIntConstExprNode *, ErrorChain *> visitCtx(BismuthParser::IConstExprContext *ctx);
    std::any visitIConstExpr(BismuthParser::IConstExprContext *ctx) override { return TNVariantCast<TIntConstExprNode>(visitCtx(ctx)); }

    std::variant<TBooleanConstNode *, ErrorChain *> visitCtx(BismuthParser::BConstExprContext *ctx) { return visitCtx(ctx->booleanConst()); }
    std::any visitBConstExpr(BismuthParser::BConstExprContext *ctx) override { return TNVariantCast<TBooleanConstNode>(visitCtx(ctx)); }

    std::variant<TBooleanConstNode *, ErrorChain *> visitCtx(BismuthParser::BooleanConstContext *ctx);
    std::any visitBooleanConst(BismuthParser::BooleanConstContext *ctx) override { return TNVariantCast<TBooleanConstNode>(visitCtx(ctx)); }

    std::variant<TStringConstNode *, ErrorChain *> visitCtx(BismuthParser::SConstExprContext *ctx);
    std::any visitSConstExpr(BismuthParser::SConstExprContext *ctx) override { return TNVariantCast<TStringConstNode>(visitCtx(ctx)); }

    std::variant<TLogAndExprNode *, ErrorChain *> visitCtx(BismuthParser::LogAndExprContext *ctx);
    std::any visitLogAndExpr(BismuthParser::LogAndExprContext *ctx) override { return TNVariantCast<TLogAndExprNode>(visitCtx(ctx)); }

    std::variant<TLogOrExprNode *, ErrorChain *> visitCtx(BismuthParser::LogOrExprContext *ctx);
    std::any visitLogOrExpr(BismuthParser::LogOrExprContext *ctx) override { return TNVariantCast<TLogOrExprNode>(visitCtx(ctx)); }

    std::variant<TEqExprNode *, ErrorChain *> visitCtx(BismuthParser::EqExprContext *ctx);
    std::any visitEqExpr(BismuthParser::EqExprContext *ctx) override { return TNVariantCast<TEqExprNode>(visitCtx(ctx)); }

    std::variant<TUnaryExprNode *, ErrorChain *> visitCtx(BismuthParser::UnaryExprContext *ctx);
    std::any visitUnaryExpr(BismuthParser::UnaryExprContext *ctx) override { return TNVariantCast<TUnaryExprNode>(visitCtx(ctx)); }

    std::variant<TBinaryArithNode *, ErrorChain *> visitCtx(BismuthParser::BinaryArithExprContext *ctx);
    std::any visitBinaryArithExpr(BismuthParser::BinaryArithExprContext *ctx) override { return TNVariantCast<TBinaryArithNode>(visitCtx(ctx)); }

    std::variant<TypedNode *, ErrorChain *> visitCtx(BismuthParser::ParenExprContext *ctx);
    std::any visitParenExpr(BismuthParser::ParenExprContext *ctx) override { return TNVariantCast<TypedNode>(visitCtx(ctx)); }

    std::variant<TFieldAccessNode *, ErrorChain *> visitCtx(BismuthParser::FieldAccessExprContext *ctx, bool is_rvalue);
    std::any visitFieldAccessExpr(BismuthParser::FieldAccessExprContext *ctx) override { return TNVariantCast<TFieldAccessNode>(visitCtx(ctx, true)); }

    std::variant<TDerefBoxNode *, ErrorChain *> visitCtx(BismuthParser::DereferenceExprContext *ctx, bool is_rvalue);
    std::any visitDereferenceExpr(BismuthParser::DereferenceExprContext *ctx) override { return TNVariantCast<TDerefBoxNode>(visitCtx(ctx, true)); }

    std::variant<TArrayAccessNode *, ErrorChain *> visitCtx(BismuthParser::ArrayAccessContext *ctx, bool is_rvalue);
    std::any visitArrayAccess(BismuthParser::ArrayAccessContext *ctx) override { return TNVariantCast<TArrayAccessNode>(visitCtx(ctx, true)); }

    std::variant<TArrayAccessNode *, ErrorChain *> visitCtx(BismuthParser::ArrayAccessExprContext *ctx) { return this->visitCtx(ctx->arrayAccess(), true); }
    std::any visitArrayAccessExpr(BismuthParser::ArrayAccessExprContext *ctx) override { return TNVariantCast<TArrayAccessNode>(visitCtx(ctx)); }

    std::variant<TypedNode *, ErrorChain *> visitCtx(BismuthParser::LValueContext *ctx);
    std::any visitLValue(BismuthParser::LValueContext *ctx) override { return TNVariantCast<TypedNode>(visitCtx(ctx)); }

    std::variant<TAssignNode *, ErrorChain *> visitCtx(BismuthParser::AssignStatementContext *ctx);
    std::any visitAssignStatement(BismuthParser::AssignStatementContext *ctx) override { return TNVariantCast<TAssignNode>(visitCtx(ctx)); }

    std::optional<ParameterListNode> visitCtx(BismuthParser::ParameterListContext *ctx);
    std::any visitParameterList(BismuthParser::ParameterListContext *ctx) override { return visitCtx(ctx); }

    std::variant<TLambdaConstNode *, ErrorChain *> visitCtx(BismuthParser::LambdaConstExprContext *ctx);
    std::any visitLambdaConstExpr(BismuthParser::LambdaConstExprContext *ctx) override { return TNVariantCast<TLambdaConstNode>(visitCtx(ctx)); }

    std::variant<TBlockNode *, ErrorChain *> visitCtx(BismuthParser::BlockStatementContext *ctx) { return this->visitCtx(ctx->block()); }
    std::any visitBlockStatement(BismuthParser::BlockStatementContext *ctx) override { return TNVariantCast<TBlockNode>(visitCtx(ctx)); }

    std::variant<TBlockNode *, ErrorChain *> visitCtx(BismuthParser::BlockContext *ctx) { return this->safeVisitBlock(ctx, true); }
    std::any visitBlock(BismuthParser::BlockContext *ctx) override { return TNVariantCast<TBlockNode>(visitCtx(ctx)); }

    std::variant<TExternNode *, ErrorChain *> visitCtx(BismuthParser::ExternStatementContext *ctx);
    std::any visitExternStatement(BismuthParser::ExternStatementContext *ctx) override { return TNVariantCast<TExternNode>(visitCtx(ctx)); }

    ParameterNode visitCtx(BismuthParser::ParameterContext *ctx);
    std::any visitParameter(BismuthParser::ParameterContext *ctx) override { return visitCtx(ctx); }

    std::variant<TInvocationNode *, ErrorChain *> visitCtx(BismuthParser::InvocationContext *ctx);
    std::any visitInvocation(BismuthParser::InvocationContext *ctx) override { return TNVariantCast<TInvocationNode>(visitCtx(ctx)); }

    std::variant<TInvocationNode *, ErrorChain *> visitCtx(BismuthParser::CallStatementContext *ctx) { return this->visitCtx(ctx->call); }
    std::any visitCallStatement(BismuthParser::CallStatementContext *ctx) override { return TNVariantCast<TInvocationNode>(visitCtx(ctx)); }

    std::variant<TInvocationNode *, ErrorChain *> visitCtx(BismuthParser::CallExprContext *ctx) { return this->visitCtx(ctx->call); }
    std::any visitCallExpr(BismuthParser::CallExprContext *ctx) override { return TNVariantCast<TInvocationNode>(visitCtx(ctx)); }

    std::variant<TypedNode *, ErrorChain *> visitCtx(BismuthParser::ConditionContext *ctx) { return this->visitCondition(ctx->ex); }
    std::any visitCondition(BismuthParser::ConditionContext *ctx) override { return visitCtx(ctx); }

    std::variant<TBinaryRelNode *, ErrorChain *> visitCtx(BismuthParser::BinaryRelExprContext *ctx);
    std::any visitBinaryRelExpr(BismuthParser::BinaryRelExprContext *ctx) override { return TNVariantCast<TBinaryRelNode>(visitCtx(ctx)); }

    std::variant<TSelectAlternativeNode *, ErrorChain *> visitCtx(BismuthParser::SelectAlternativeContext *ctx);
    std::any visitSelectAlternative(BismuthParser::SelectAlternativeContext *ctx) override { return TNVariantCast<TSelectAlternativeNode>(visitCtx(ctx)); }

    std::any visitTypeDef(BismuthParser::TypeDefContext *ctx) override { return ctx->defineType()->accept(this); }

    std::any visitDefineProgram(BismuthParser::DefineProgramContext *ctx) override { return TNVariantCast<TProgramDefNode>(visitCtx(ctx)); }

    std::variant<TLambdaConstNode *, ErrorChain *> visitCtx(BismuthParser::DefineFunctionContext *ctx);
    std::any visitDefineFunction(BismuthParser::DefineFunctionContext *ctx) override { return TNVariantCast<TLambdaConstNode>(visitCtx(ctx)); }

    std::variant<TSelectStatementNode *, ErrorChain *> visitCtx(BismuthParser::SelectStatementContext *ctx);
    std::any visitSelectStatement(BismuthParser::SelectStatementContext *ctx) override { return TNVariantCast<TSelectStatementNode>(visitCtx(ctx)); }

    std::variant<TConditionalStatementNode *, ErrorChain *> visitCtx(BismuthParser::ConditionalStatementContext *ctx);
    std::any visitConditionalStatement(BismuthParser::ConditionalStatementContext *ctx) override { return TNVariantCast<TConditionalStatementNode>(visitCtx(ctx)); }

    std::variant<TWhileLoopNode *, ErrorChain *> visitCtx(BismuthParser::ProgramLoopContext *ctx);
    std::any visitProgramLoop(BismuthParser::ProgramLoopContext *ctx) override { return TNVariantCast<TWhileLoopNode>(visitCtx(ctx)); }

    std::variant<TReturnNode *, ErrorChain *> visitCtx(BismuthParser::ReturnStatementContext *ctx);
    std::any visitReturnStatement(BismuthParser::ReturnStatementContext *ctx) override { return TNVariantCast<TReturnNode>(visitCtx(ctx)); }

    std::variant<TDefineEnumNode *, ErrorChain *> visitCtx(BismuthParser::DefineEnumContext *ctx);
    std::any visitDefineEnum(BismuthParser::DefineEnumContext *ctx) override { return TNVariantCast<TDefineEnumNode>(visitCtx(ctx)); }

    std::variant<TDefineStructNode *, ErrorChain *> visitCtx(BismuthParser::DefineStructContext *ctx);
    std::any visitDefineStruct(BismuthParser::DefineStructContext *ctx) override { return TNVariantCast<TDefineStructNode>(visitCtx(ctx)); }

    std::variant<TInitProductNode *, ErrorChain *> visitCtx(BismuthParser::InitProductContext *ctx);
    std::any visitInitProduct(BismuthParser::InitProductContext *ctx) override { return TNVariantCast<TInitProductNode>(visitCtx(ctx)); }

    std::variant<TInitBoxNode *, ErrorChain *> visitCtx(BismuthParser::InitBoxContext *ctx);
    std::any visitInitBox(BismuthParser::InitBoxContext *ctx) override { return TNVariantCast<TInitBoxNode>(visitCtx(ctx)); }

    std::variant<TProgramSendNode *, ErrorChain *> TvisitProgramSend(BismuthParser::ProgramSendContext *ctx);
    std::any visitProgramSend(BismuthParser::ProgramSendContext *ctx) override { return TNVariantCast<TProgramSendNode>(TvisitProgramSend(ctx)); }

    std::variant<TProgramRecvNode *, ErrorChain *> TvisitAssignableRecv(BismuthParser::AssignableRecvContext *ctx);
    std::any visitAssignableRecv(BismuthParser::AssignableRecvContext *ctx) override { return TNVariantCast<TProgramRecvNode>(TvisitAssignableRecv(ctx)); }

    std::variant<TProgramIsPresetNode *, ErrorChain *> TvisitAssignableIsPresent(BismuthParser::AssignableIsPresentContext *ctx);
    std::any visitAssignableIsPresent(BismuthParser::AssignableIsPresentContext *ctx) override { return TNVariantCast<TProgramIsPresetNode>(TvisitAssignableIsPresent(ctx)); }

    std::variant<TProgramContractNode *, ErrorChain *> TvisitProgramContract(BismuthParser::ProgramContractContext *ctx);
    std::any visitProgramContract(BismuthParser::ProgramContractContext *ctx) override { return TNVariantCast<TProgramContractNode>(TvisitProgramContract(ctx)); }

    std::variant<TProgramWeakenNode *, ErrorChain *> TvisitProgramWeaken(BismuthParser::ProgramWeakenContext *ctx);
    std::any visitProgramWeaken(BismuthParser::ProgramWeakenContext *ctx) override { return TNVariantCast<TProgramWeakenNode>(TvisitProgramWeaken(ctx)); }

    std::variant<TProgramExecNode *, ErrorChain *> TvisitAssignableExec(BismuthParser::AssignableExecContext *ctx);
    std::any visitAssignableExec(BismuthParser::AssignableExecContext *ctx) override { return TNVariantCast<TProgramExecNode>(TvisitAssignableExec(ctx)); }

    std::variant<TProgramAcceptNode *, ErrorChain *> TvisitProgramAccept(BismuthParser::ProgramAcceptContext *ctx);
    std::any visitProgramAccept(BismuthParser::ProgramAcceptContext *ctx) override { return TNVariantCast<TProgramAcceptNode>(TvisitProgramAccept(ctx)); }

    std::variant<TProgramAcceptWhileNode *, ErrorChain *> TvisitProgramAcceptWhile(BismuthParser::ProgramAcceptWhileContext *ctx);
    std::any visitProgramAcceptWhile(BismuthParser::ProgramAcceptWhileContext *ctx) override { return TNVariantCast<TProgramAcceptWhileNode>(TvisitProgramAcceptWhile(ctx)); }

    std::variant<TProgramAcceptIfNode *, ErrorChain *> TvisitProgramAcceptIf(BismuthParser::ProgramAcceptIfContext *ctx);
    std::any visitProgramAcceptIf(BismuthParser::ProgramAcceptIfContext *ctx) override { return TNVariantCast<TProgramAcceptIfNode>(TvisitProgramAcceptIf(ctx)); }

    std::variant<TCompilationUnitNode *, ErrorChain *> visitCtx(BismuthParser::CompilationUnitContext *ctx);
    std::any visitCompilationUnit(BismuthParser::CompilationUnitContext *ctx) override { return visitCtx(ctx); }

    std::variant<TVarDeclNode *, ErrorChain *> visitCtx(BismuthParser::VarDeclStatementContext *ctx);
    std::any visitVarDeclStatement(BismuthParser::VarDeclStatementContext *ctx) override { return TNVariantCast<>(visitCtx(ctx)); }

    std::variant<TMatchStatementNode *, ErrorChain *> visitCtx(BismuthParser::MatchStatementContext *ctx);
    std::any visitMatchStatement(BismuthParser::MatchStatementContext *ctx) override { return TNVariantCast<>(visitCtx(ctx)); } // NOTE: CASTS NEEDED B/C OF HOW C++ HANDLES ANYs BY MANGLED NAME!

    std::variant<TExitNode *, ErrorChain *> visitCtx(BismuthParser::ExitStatementContext *ctx);
    std::any visitExitStatement(BismuthParser::ExitStatementContext *ctx) override { return TNVariantCast<>(visitCtx(ctx)); }

    std::variant<TExprCopyNode *, ErrorChain *> TvisitCopyExpr(BismuthParser::CopyExprContext *ctx);
    std::any visitCopyExpr(BismuthParser::CopyExprContext *ctx) override { return TNVariantCast<TExprCopyNode>(TvisitCopyExpr(ctx)); }

    std::variant<TAsChannelNode *, ErrorChain *> TvisitAsChannelExpr(BismuthParser::AsChannelExprContext *ctx);
    std::any visitAsChannelExpr(BismuthParser::AsChannelExprContext *ctx) override { return TNVariantCast<TAsChannelNode>(TvisitAsChannelExpr(ctx)); }

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

    std::variant<TChannelCaseStatementNode *, ErrorChain *> TvisitProgramCase(BismuthParser::ProgramCaseContext *ctx);
    std::any visitProgramCase(BismuthParser::ProgramCaseContext *ctx) override { return TNVariantCast<TChannelCaseStatementNode>(TvisitProgramCase(ctx)); }

    std::variant<TProgramProjectNode *, ErrorChain *> TvisitProgramProject(BismuthParser::ProgramProjectContext *ctx);
    std::any visitProgramProject(BismuthParser::ProgramProjectContext *ctx) override { return TNVariantCast<TProgramProjectNode>(TvisitProgramProject(ctx)); }

    std::variant<TypedNode *, ErrorChain *> visitCondition(BismuthParser::ExpressionContext *ex)
    {
        std::variant<TypedNode *, ErrorChain *> condOpt = anyOpt2VarError<TypedNode>(errorHandler, ex->accept(this));

        if (ErrorChain **e = std::get_if<ErrorChain *>(&condOpt))
        {
            (*e)->addError(ex->getStart(), "Unable to type check condition expression.");
            return *e;
        }

        TypedNode *cond = std::get<TypedNode *>(condOpt);
        const Type *conditionType = cond->getType();

        if (conditionType->isNotSubtype(Types::DYN_BOOL))
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
    std::variant<TBlockNode *, ErrorChain *> safeVisitBlock(BismuthParser::BlockContext *ctx, bool newScope)
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
                (*e)->addError(ctx->getStart(), "Failed to type check statement in block.");
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

        return new TBlockNode(nodes, ctx->getStart()); // FIXME: DO BETTER< HANDLE ERRORS! CURRENTLY ALWAYS RETURNS NODE
    }

    std::variant<Symbol *, ErrorChain *> getProgramSymbol(BismuthParser::DefineProgramContext *ctx)
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
    std::variant<TProgramDefNode *, ErrorChain *> visitCtx(BismuthParser::DefineProgramContext *ctx)
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
            std::variant<TBlockNode *, ErrorChain *> blkOpt = this->safeVisitBlock(ctx->block(), false);
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
            return new TProgramDefNode(funcId, channelSymbol, std::get<TBlockNode *>(blkOpt), progType, ctx->getStart());
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
    //FIXME: WHAT AB Ext<A,B>;!P;Ext<A,B>?
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

        STManager *origStmgr = this->stmgr;

        for (unsigned int i = 0; i < ctxCases.size(); i++)
        {
            auto alt = ctxCases.at(i);

            if (checkRestIndependently || i + 1 < ctxCases.size())
            {
                std::optional<STManager *> optSTCopy = origStmgr->getCopy();
                if (!optSTCopy)
                    return errorHandler.addError(alt->getStart(), "Failed to copy symbol table; this is likely a compiler error.");
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

            // safeExitScope(ctx);
            if (!endsInReturn(caseNode) && !endsInBranch(caseNode))
            {
                for (auto s : ctxRest->ctxRest)
                {
                    std::variant<TypedNode *, ErrorChain *> rOpt = anyOpt2VarError<TypedNode>(errorHandler, s->accept(this));

                    if (ErrorChain **e = std::get_if<ErrorChain *>(&rOpt))
                    {
                        (*e)->addError(alt->getStart(), "Failed to type check code following branch.");
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

                        if (ErrorChain **e = std::get_if<ErrorChain *>(&rOpt))
                        {
                            (*e)->addError(ctx->getStart(), "Failed to type check when no branch followed.");
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

                errorHandler.addError(alt->getStart(), "537 Unused linear types in context: " + details.str());
            }
        }

        if (checkRestIndependently)
        {
            this->stmgr = origStmgr;

            stmgr->enterScope(StopType::NONE); // Why? This doesnt make sense..

            for (auto s : ctxRest->ctxRest)
            {
                std::variant<TypedNode *, ErrorChain *> rOpt = anyOpt2VarError<TypedNode>(errorHandler, s->accept(this));
                if (ErrorChain **e = std::get_if<ErrorChain *>(&rOpt))
                {
                    (*e)->addError(ctx->getStart(), "Failed to type check code when conditional skipped over.");
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

                        if (ErrorChain **e = std::get_if<ErrorChain *>(&rOpt))
                        {
                            (*e)->addError(ctx->getStart(), "2097");
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

            ctxRest->isGenerated = true;
            safeExitScope(ctx);

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

                errorHandler.addError(ctx->getStart(), "608 Unused linear types in context: " + details.str());
            }
        }
        
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
            std::vector<Symbol *> uninf = scope->getSymbols(SymbolLookupFlags::UNINFERRED_TYPE); // TODO: CHANGE BACK TO CONST?

            // If there are any uninferred symbols, then add it as a compiler error as we won't be able to resolve them
            // due to the var leaving the scope
            if (uninf.size() > 0)
            {
                std::ostringstream details;

                for (auto e : uninf)
                {
                    details << e->toString() << "; ";
                }

                errorHandler.addError(ctx->getStart(), "711 Uninferred types in context: " + details.str());
            }
        }

        if (res.second)
        {
            Scope *scope = res.second.value();
            std::vector<Symbol *> lins = scope->getSymbols(SymbolLookupFlags::PENDING_LINEAR);

            // If there are any uninferred symbols, then add it as a compiler error as we won't be able to resolve them
            // due to the var leaving the scope
            if (lins.size() > 0)
            {
                std::ostringstream details;

                for (auto e : lins)
                {
                    details << e->toString() << "; ";
                }

                errorHandler.addError(ctx->getStart(), "736 Unused linear types in context: " + details.str());
            }
        }
        // return res;
    }

    // NOTE: IS THERE A WAY FOR ME TO PROVIDE ONE OF TWO TYPES TO A FN, AND THEN HAVE THAT BE RET TYPE? (BUT ONLY ONE OF TWO...)

    std::variant<Symbol *, ErrorChain *> getFunctionSymbol(BismuthParser::DefineFunctionContext *ctx)
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