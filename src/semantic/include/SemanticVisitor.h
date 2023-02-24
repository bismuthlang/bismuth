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
#include <variant>
// typedef std::variant<Value, START_LOOP, END_LOOP, SEL> Message;
// typedef

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

    // From C++ Documentation for visitors
    template <class... Ts>
    struct overloaded : Ts...
    {
        using Ts::operator()...;
    };
    template <class... Ts>
    overloaded(Ts...) -> overloaded<Ts...>;

    std::variant<IConstExprNode *, ErrorChain *> visitCtx(WPLParser::IConstExprContext *ctx);
    // std::variant<TypedNode*, ErrorChain*> visitCtx(WPLParser::IConstExprContext *ctx) { return  }
    std::any visitIConstExpr(WPLParser::IConstExprContext *ctx) override { return TNVariantCast<IConstExprNode>(visitCtx(ctx)); }

    std::variant<BooleanConstNode *, ErrorChain *> visitCtx(WPLParser::BConstExprContext *ctx) { return visitCtx(ctx->booleanConst()); }
    std::any visitBConstExpr(WPLParser::BConstExprContext *ctx) override { return TNVariantCast<BooleanConstNode>(visitCtx(ctx)); }

    std::variant<BooleanConstNode *, ErrorChain *> visitCtx(WPLParser::BooleanConstContext *ctx);
    std::any visitBooleanConst(WPLParser::BooleanConstContext *ctx) override { return TNVariantCast<BooleanConstNode>(visitCtx(ctx)); }

    std::variant<StringConstNode *, ErrorChain *> visitCtx(WPLParser::SConstExprContext *ctx);
    std::any visitSConstExpr(WPLParser::SConstExprContext *ctx) override { return TNVariantCast<StringConstNode>(visitCtx(ctx)); }

    std::variant<LogAndExprNode *, ErrorChain *> visitCtx(WPLParser::LogAndExprContext *ctx);
    std::any visitLogAndExpr(WPLParser::LogAndExprContext *ctx) override { return TNVariantCast<LogAndExprNode>(visitCtx(ctx)); }

    std::variant<LogOrExprNode *, ErrorChain *> visitCtx(WPLParser::LogOrExprContext *ctx);
    std::any visitLogOrExpr(WPLParser::LogOrExprContext *ctx) override { return TNVariantCast<LogOrExprNode>(visitCtx(ctx)); }

    std::variant<EqExprNode *, ErrorChain *> visitCtx(WPLParser::EqExprContext *ctx);
    std::any visitEqExpr(WPLParser::EqExprContext *ctx) override { return TNVariantCast<EqExprNode>(visitCtx(ctx)); }

    std::variant<UnaryExprNode *, ErrorChain *> visitCtx(WPLParser::UnaryExprContext *ctx);
    std::any visitUnaryExpr(WPLParser::UnaryExprContext *ctx) override { return TNVariantCast<UnaryExprNode>(visitCtx(ctx)); }

    std::variant<BinaryArithNode *, ErrorChain *> visitCtx(WPLParser::BinaryArithExprContext *ctx);
    std::any visitBinaryArithExpr(WPLParser::BinaryArithExprContext *ctx) override { return TNVariantCast<BinaryArithNode>(visitCtx(ctx)); }

    std::variant<TypedNode *, ErrorChain *> visitCtx(WPLParser::ParenExprContext *ctx);
    std::any visitParenExpr(WPLParser::ParenExprContext *ctx) override { return TNVariantCast<TypedNode>(visitCtx(ctx)); }

    std::variant<FieldAccessNode *, ErrorChain *> visitCtx(WPLParser::FieldAccessExprContext *ctx, bool is_rvalue);
    std::any visitFieldAccessExpr(WPLParser::FieldAccessExprContext *ctx) override { return TNVariantCast<FieldAccessNode>(visitCtx(ctx, true)); }

    // std::optional<ArrayAccessNode*> visitCtx(WPLParser::ArrayAccessContext *ctx);
    std::variant<ArrayAccessNode *, ErrorChain *> visitCtx(WPLParser::ArrayAccessContext *ctx, bool is_rvalue);
    std::any visitArrayAccess(WPLParser::ArrayAccessContext *ctx) override { return TNVariantCast<ArrayAccessNode>(visitCtx(ctx, true)); }

    std::variant<ArrayAccessNode *, ErrorChain *> visitCtx(WPLParser::ArrayAccessExprContext *ctx) { return this->visitCtx(ctx->arrayAccess(), true); }
    std::any visitArrayAccessExpr(WPLParser::ArrayAccessExprContext *ctx) override { return TNVariantCast<ArrayAccessNode>(visitCtx(ctx)); }

    std::variant<TypedNode *, ErrorChain *> visitCtx(WPLParser::ArrayOrVarContext *ctx);
    std::any visitArrayOrVar(WPLParser::ArrayOrVarContext *ctx) override { return TNVariantCast<TypedNode>(visitCtx(ctx)); }

    std::variant<AssignNode *, ErrorChain *> visitCtx(WPLParser::AssignStatementContext *ctx);
    std::any visitAssignStatement(WPLParser::AssignStatementContext *ctx) override { return TNVariantCast<AssignNode>(visitCtx(ctx)); }

    std::optional<ParameterListNode> visitCtx(WPLParser::ParameterListContext *ctx);
    std::any visitParameterList(WPLParser::ParameterListContext *ctx) override { return visitCtx(ctx); }

    std::variant<LambdaConstNode *, ErrorChain *> visitCtx(WPLParser::LambdaConstExprContext *ctx);
    std::any visitLambdaConstExpr(WPLParser::LambdaConstExprContext *ctx) override { return TNVariantCast<LambdaConstNode>(visitCtx(ctx)); }

    std::variant<BlockNode *, ErrorChain *> visitCtx(WPLParser::BlockStatementContext *ctx) { return this->visitCtx(ctx->block()); }
    std::any visitBlockStatement(WPLParser::BlockStatementContext *ctx) override { return TNVariantCast<BlockNode>(visitCtx(ctx)); }

    std::variant<BlockNode *, ErrorChain *> visitCtx(WPLParser::BlockContext *ctx) { return this->safeVisitBlock(ctx, true); }
    std::any visitBlock(WPLParser::BlockContext *ctx) override { return TNVariantCast<BlockNode>(visitCtx(ctx)); }

    std::variant<ExternNode *, ErrorChain *> visitCtx(WPLParser::ExternStatementContext *ctx);
    std::any visitExternStatement(WPLParser::ExternStatementContext *ctx) override { return TNVariantCast<ExternNode>(visitCtx(ctx)); }

    ParameterNode visitCtx(WPLParser::ParameterContext *ctx);
    std::any visitParameter(WPLParser::ParameterContext *ctx) override { return visitCtx(ctx); }

    std::variant<InvocationNode *, ErrorChain *> visitCtx(WPLParser::InvocationContext *ctx);
    std::any visitInvocation(WPLParser::InvocationContext *ctx) override { return TNVariantCast<InvocationNode>(visitCtx(ctx)); }

    std::variant<InvocationNode *, ErrorChain *> visitCtx(WPLParser::CallStatementContext *ctx) { return this->visitCtx(ctx->call); }
    std::any visitCallStatement(WPLParser::CallStatementContext *ctx) override { return TNVariantCast<InvocationNode>(visitCtx(ctx)); }

    std::variant<InvocationNode *, ErrorChain *> visitCtx(WPLParser::CallExprContext *ctx) { return this->visitCtx(ctx->call); }
    std::any visitCallExpr(WPLParser::CallExprContext *ctx) override { return TNVariantCast<InvocationNode>(visitCtx(ctx)); }

    std::variant<TypedNode *, ErrorChain *> visitCtx(WPLParser::ConditionContext *ctx);
    std::any visitCondition(WPLParser::ConditionContext *ctx) override { return visitCtx(ctx); }

    std::variant<BinaryRelNode *, ErrorChain *> visitCtx(WPLParser::BinaryRelExprContext *ctx);
    std::any visitBinaryRelExpr(WPLParser::BinaryRelExprContext *ctx) override { return TNVariantCast<BinaryRelNode>(visitCtx(ctx)); }

    std::variant<SelectAlternativeNode *, ErrorChain *> visitCtx(WPLParser::SelectAlternativeContext *ctx);
    std::any visitSelectAlternative(WPLParser::SelectAlternativeContext *ctx) override { return TNVariantCast<SelectAlternativeNode>(visitCtx(ctx)); }

    std::any visitProgDef(WPLParser::ProgDefContext *ctx) override { return TNVariantCast<ProgramDefNode>(this->visitInvokeable(ctx->defineProc())); }
    std::any visitDefineProgram(WPLParser::DefineProgramContext *ctx) override { return TNVariantCast<ProgramDefNode>(visitInvokeable(ctx->defineProc())); }

    std::variant<LambdaConstNode *, ErrorChain *> visitCtx(WPLParser::DefineFuncContext *ctx);
    std::any visitDefineFunc(WPLParser::DefineFuncContext *ctx) override { return TNVariantCast<LambdaConstNode>(visitCtx(ctx)); }
    std::any visitFuncDef(WPLParser::FuncDefContext *ctx) override { return TNVariantCast<LambdaConstNode>(visitCtx(ctx->defineFunc())); }
    std::any visitDefineFunction(WPLParser::DefineFunctionContext *ctx) override { return TNVariantCast<LambdaConstNode>(visitCtx(ctx->defineFunc())); }

    std::variant<SelectStatementNode *, ErrorChain *> visitCtx(WPLParser::SelectStatementContext *ctx);
    std::any visitSelectStatement(WPLParser::SelectStatementContext *ctx) override { return TNVariantCast<SelectStatementNode>(visitCtx(ctx)); }

    std::variant<ConditionalStatementNode *, ErrorChain *> visitCtx(WPLParser::ConditionalStatementContext *ctx);
    std::any visitConditionalStatement(WPLParser::ConditionalStatementContext *ctx) override { return TNVariantCast<ConditionalStatementNode>(visitCtx(ctx)); }

    std::variant<WhileLoopNode *, ErrorChain *> visitCtx(WPLParser::ProgramLoopContext *ctx);
    std::any visitProgramLoop(WPLParser::ProgramLoopContext *ctx) override { return TNVariantCast<WhileLoopNode>(visitCtx(ctx)); }

    std::variant<ReturnNode *, ErrorChain *> visitCtx(WPLParser::ReturnStatementContext *ctx);
    std::any visitReturnStatement(WPLParser::ReturnStatementContext *ctx) override { return TNVariantCast<ReturnNode>(visitCtx(ctx)); }

    std::variant<DefineEnumNode *, ErrorChain *> visitCtx(WPLParser::DefineEnumContext *ctx);
    std::any visitDefineEnum(WPLParser::DefineEnumContext *ctx) override { return TNVariantCast<DefineEnumNode>(visitCtx(ctx)); }

    std::variant<DefineStructNode *, ErrorChain *> visitCtx(WPLParser::DefineStructContext *ctx);
    std::any visitDefineStruct(WPLParser::DefineStructContext *ctx) override { return TNVariantCast<DefineStructNode>(visitCtx(ctx)); }

    std::variant<InitProductNode *, ErrorChain *> visitCtx(WPLParser::InitProductContext *ctx);
    std::any visitInitProduct(WPLParser::InitProductContext *ctx) override { return TNVariantCast<InitProductNode>(visitCtx(ctx)); }

    std::variant<ProgramSendNode *, ErrorChain *> TvisitProgramSend(WPLParser::ProgramSendContext *ctx);
    std::any visitProgramSend(WPLParser::ProgramSendContext *ctx) override { return TNVariantCast<ProgramSendNode>(TvisitProgramSend(ctx)); }

    std::variant<ProgramRecvNode *, ErrorChain *> TvisitAssignableRecv(WPLParser::AssignableRecvContext *ctx);
    std::any visitAssignableRecv(WPLParser::AssignableRecvContext *ctx) override { return TNVariantCast<ProgramRecvNode>(TvisitAssignableRecv(ctx)); }

    std::variant<ProgramContractNode *, ErrorChain *> TvisitProgramContract(WPLParser::ProgramContractContext *ctx);
    std::any visitProgramContract(WPLParser::ProgramContractContext *ctx) override { return TNVariantCast<ProgramContractNode>(TvisitProgramContract(ctx)); }

    std::variant<ProgramWeakenNode *, ErrorChain *> TvisitProgramWeaken(WPLParser::ProgramWeakenContext *ctx);
    std::any visitProgramWeaken(WPLParser::ProgramWeakenContext *ctx) override { return TNVariantCast<ProgramWeakenNode>(TvisitProgramWeaken(ctx)); }

    std::variant<ProgramExecNode *, ErrorChain *> TvisitAssignableExec(WPLParser::AssignableExecContext *ctx);
    std::any visitAssignableExec(WPLParser::AssignableExecContext *ctx) override { return TNVariantCast<ProgramExecNode>(TvisitAssignableExec(ctx)); }

    std::variant<ProgramAcceptNode *, ErrorChain *> TvisitProgramAccept(WPLParser::ProgramAcceptContext *ctx);
    std::any visitProgramAccept(WPLParser::ProgramAcceptContext *ctx) override { return TNVariantCast<ProgramAcceptNode>(TvisitProgramAccept(ctx)); }

    std::variant<CompilationUnitNode *, ErrorChain *> visitCtx(WPLParser::CompilationUnitContext *ctx);
    std::any visitCompilationUnit(WPLParser::CompilationUnitContext *ctx) override { return visitCtx(ctx); }

    std::variant<VarDeclNode *, ErrorChain *> visitCtx(WPLParser::VarDeclStatementContext *ctx);
    std::any visitVarDeclStatement(WPLParser::VarDeclStatementContext *ctx) override { return TNVariantCast<>(visitCtx(ctx)); }

    std::variant<MatchStatementNode *, ErrorChain *> visitCtx(WPLParser::MatchStatementContext *ctx);
    std::any visitMatchStatement(WPLParser::MatchStatementContext *ctx) override { return TNVariantCast<>(visitCtx(ctx)); } // NOTE: CASTS NEEDED B/C OF HOW C++ HANDLES ANYS BY MANGLED NAME!

    std::variant<ExitNode *, ErrorChain *> visitCtx(WPLParser::ExitStatementContext *ctx);
    std::any visitExitStatement(WPLParser::ExitStatementContext *ctx) override { return TNVariantCast<>(visitCtx(ctx)); }

    // const Type *visitCtx(WPLParser::VariableExprContext *ctx);
    const Type *visitCtx(WPLParser::AssignmentContext *ctx);

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

    const Type *visitCtx(WPLParser::ProgramTypeContext *ctx);
    std::any visitProgramType(WPLParser::ProgramTypeContext *ctx) override { return visitCtx(ctx); }

    const Type *visitCtx(WPLParser::CustomTypeContext *ctx);
    std::any visitCustomType(WPLParser::CustomTypeContext *ctx) override { return visitCtx(ctx); }

    const Type *visitCtx(WPLParser::TypeOrVarContext *ctx);
    std::any visitTypeOrVar(WPLParser::TypeOrVarContext *ctx) override { return visitCtx(ctx); }

    const Type *visitCtx(WPLParser::SumTypeContext *ctx);
    std::any visitSumType(WPLParser::SumTypeContext *ctx) override { return visitCtx(ctx); }

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

    std::variant<ChannelCaseStatementNode *, ErrorChain *> TvisitProgramCase(WPLParser::ProgramCaseContext *ctx);
    std::any visitProgramCase(WPLParser::ProgramCaseContext *ctx) override { return TNVariantCast<ChannelCaseStatementNode>(TvisitProgramCase(ctx)); }

    std::variant<ProgramProjectNode *, ErrorChain *> TvisitProgramProject(WPLParser::ProgramProjectContext *ctx);
    std::any visitProgramProject(WPLParser::ProgramProjectContext *ctx) override { return TNVariantCast<ProgramProjectNode>(TvisitProgramProject(ctx)); }

    /**
     * @brief Used to safely enter a block. This is used to ensure there aren't FUNC/PROC definitions / code following returns in it.
     *
     * @param ctx The BlockContext to visit
     * @param newScope  true if we should enter a new scope, false otherwise
     * @return const Type* Types::UNDEFINED as this is a statement and not a value
     */
    std::variant<BlockNode *, ErrorChain *> safeVisitBlock(WPLParser::BlockContext *ctx, bool newScope)
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
                (*e)->addError(ctx->getStart(), "h280");
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
            if (dynamic_cast<WPLParser::ReturnStatementContext *>(e))
                foundReturn = true;
        }

        // If we entered a new scope, then we can now safely exit a scope
        if (newScope)
            this->safeExitScope(ctx);

        return new BlockNode(nodes, ctx->getStart()); // FIXME: DO BETTER< HANDLE ERRORS! CURRENTLY ALWAYS RETURNS NODE
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
    std::variant<ProgramDefNode *, ErrorChain *> visitInvokeable(WPLParser::DefineProcContext *ctx)
    {
        std::optional<Symbol *> symOpt = bindings->getBinding(ctx);

        if (!symOpt && stmgr->lookupInCurrentScope(ctx->name->getText()))
        {
            return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of " + ctx->name->getText());
        }

        Symbol *sym = symOpt.value_or(
            new Symbol(
                ctx->name->getText(), [this, ctx]() -> const Type *
                {
                    const Type *retType = any2Type(ctx->ty->accept(this));

                    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(retType))
                    {
                        // Create a new func with the return type (or reuse the procType) NOTE: We do NOT need to worry about discarding the variadic here as variadic FUNC/PROC is not supported
                        const TypeProgram *funcType = new TypeProgram(channel, false);

                        return funcType;
                    }
                    return retType; }(),
                true, false));

        if (const TypeProgram *funcType = dynamic_cast<const TypeProgram *>(sym->type))
        {
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

            // Add the symbol to the stmgr and enter the scope.
            stmgr->addSymbol(sym);
            stmgr->enterScope(StopType::GLOBAL); // NOTE: We do NOT duplicate scopes here because we use a saveVisitBlock with newScope=false

            Symbol *channelSymbol = new Symbol(ctx->channelName->getText(), funcType->getChannelType()->getCopy(), false, false);

            stmgr->addSymbol(channelSymbol);
            // In the new scope. set our return type. We use @RETURN as it is not a valid symbol the programmer could write in the language
            stmgr->addSymbol(new Symbol("@EXIT", Types::UNIT, false, false));

            // Safe visit the program block without creating a new scope (as we are managing the scope)
            std::variant<BlockNode *, ErrorChain *> blkOpt = this->safeVisitBlock(ctx->block(), false);
            if (ErrorChain **e = std::get_if<ErrorChain *>(&blkOpt))
            {
                (*e)->addError(ctx->getStart(), "h374");
                return *e;
            }

            // If we have a return type, make sure that we return as the last statement in the FUNC. The type of the return is managed when we visited it.
            // if (ty && (ctx->block()->stmts.size() == 0 || !dynamic_cast<WPLParser::ReturnStatementContext *>(ctx->block()->stmts.at(ctx->block()->stmts.size() - 1))))
            // {
            //     errorHandler.addError(ctx->getStart(), "Function must end in return statement");
            // }

            // Safe exit the scope.
            safeExitScope(ctx);

            return new ProgramDefNode(funcId, channelSymbol, std::get<BlockNode *>(blkOpt), funcType, ctx->getStart());
        }
        else
        {
            return errorHandler.addError(ctx->getStart(), "Cannot invoke " + sym->toString());
        }
    }

    struct ConditionalData
    {
        vector<TypedNode *> cases;
        vector<TypedNode *> post;

        ConditionalData(vector<TypedNode *> cases, vector<TypedNode *> post) : cases(cases), post(post)
        {
        }
    };

    template <typename T>
    inline std::variant<ConditionalData, ErrorChain *> checkBranch(
        antlr4::ParserRuleContext *ctx,
        std::vector<T *> ctxCases,
        std::vector<WPLParser::StatementContext *> ctxRest,
        bool checkRestIndependently,
        std::function<std::variant<TypedNode *, ErrorChain *>(T *)> typeCheck)
    {
        std::cout << stmgr->toString() << std::endl; 
        std::vector<TypedNode *> cases;
        std::vector<TypedNode *> restVec;
        bool restVecFilled = false;

        std::vector<Symbol *> syms = stmgr->getAvaliableLinears(true);                    // FIXME: WILL TRY TO REBIND VAR WE JUST BOUND TO NEW CHAN VALUE!
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
            // const ProtocolSequence *proto = toSequence(any2Protocol(alt->check->accept(this)));

            for (Symbol *s : syms)
            {
                stmgr->addSymbol(s);
                std::cout << "436 " << s->toString() << std::endl; 
            }
            for (auto pair : to_fix)
            {
                pair.first->setProtocol(pair.second->getCopy());
                std::cout << "441 " << pair.first->toString() << " " << pair.second->toString() << std::endl; 
            }

            // proto->append(savedRest->getCopy());
            // channel->setProtocol(proto);

            // stmgr->addSymbol(sym);

            stmgr->enterScope(StopType::NONE);
            std::variant<TypedNode *, ErrorChain *> optEval = typeCheck(alt);

            // anyOpt2VarError<TypedNode>(errorHandler, alt->eval->accept(this));

            if (ErrorChain **e = std::get_if<ErrorChain *>(&optEval))
            {
                (*e)->addError(ctx->getStart(), "2083");
                return *e;
            }

            TypedNode *caseNode = std::get<TypedNode *>(optEval);
            cases.push_back(caseNode);

            // safeExitScope(ctx);

            if (!endsInReturn(caseNode))
            {
                for (auto s : ctxRest)
                {
                    std::variant<TypedNode *, ErrorChain *> rOpt = anyOpt2VarError<TypedNode>(errorHandler, s->accept(this));

                    if (!restVecFilled)
                    {

                        if (ErrorChain **e = std::get_if<ErrorChain *>(&rOpt))
                        {
                            (*e)->addError(ctx->getStart(), "2097");
                            return *e;
                        }

                        restVec.push_back(std::get<TypedNode *>(rOpt));
                    }
                }

                restVecFilled = true;
            }

            safeExitScope(ctx); // FIXME: MAKE THIS ABLE TO TRIP ERROR?

            std::vector<Symbol *> lins = stmgr->getAvaliableLinears();

            // If there are any uninferred symbols, then add it as a compiler error as we won't be able to resolve them
            // due to the var leaving the scope
            if (lins.size() > 0)
            {
                std::ostringstream details;

                for (auto e : lins)
                {
                    details << e->toString() << "; ";
                }

                errorHandler.addError(alt->getStart(), "Unused linear types in context: " + details.str());
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

            for (auto s : ctxRest)
            {
                std::variant<TypedNode *, ErrorChain *> rOpt = anyOpt2VarError<TypedNode>(errorHandler, s->accept(this));

                if (!restVecFilled)
                {

                    if (ErrorChain **e = std::get_if<ErrorChain *>(&rOpt))
                    {
                        (*e)->addError(ctx->getStart(), "2097");
                        return *e;
                    }

                    restVec.push_back(std::get<TypedNode *>(rOpt));
                }
            }

            restVecFilled = true;

            safeExitScope(ctx);

            std::vector<Symbol *> lins = stmgr->getAvaliableLinears();

            // If there are any uninferred symbols, then add it as a compiler error as we won't be able to resolve them
            // due to the var leaving the scope
            if (lins.size() > 0)
            {
                std::ostringstream details;

                for (auto e : lins)
                {
                    details << e->toString() << "; ";
                }

                errorHandler.addError(ctx->getStart(), "Unused linear types in context: " + details.str());
            }
        }

        // return Types::UNDEFINED;
        // return ty.value();
        return ConditionalData(cases, restVec);
    }

    template <typename T>
    std::vector<T> Append(std::vector<T> &a, const std::vector<T> &b)
    {
        std::vector<T> ans; 
        ans.reserve(a.size() + b.size());
        ans.insert(ans.end(), a.begin(), a.end());
        ans.insert(ans.end(), b.begin(), b.end());
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
    PropertyManager *bindings;
    WPLErrorHandler errorHandler = WPLErrorHandler(SEMANTIC);

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

                errorHandler.addError(ctx->getStart(), "Unused linear types in context: " + details.str());
            }
        }
        // return res;
    }

    // NOTE: IS THERE A WAY FOR ME TO PROVIDE ONE OF TWO TYPES TO A FN, AND THEN HAVE THAT BE RET TYPE? (BUT ONLY ONE OF TWO...)

    std::variant<Symbol *, ErrorChain *> getFunctionSymbol(WPLParser::DefineFuncContext *ctx)
    {
        std::optional<Symbol *> opt = bindings->getBinding(ctx);
        if (opt)
            return opt.value();

        if (stmgr->lookupInCurrentScope(ctx->name->getText()))
        {
            return errorHandler.addError(ctx->getStart(), "Unsupported redeclaration of " + ctx->name->getText());
        }

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

        Symbol *sym = new Symbol(ctx->name->getText(), new TypeInvoke(ps, retType), true, false); // FIXME: DO BETTER;

        stmgr->addSymbol(sym);

        return sym;
    }
};