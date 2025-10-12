#pragma once
#include "Debug.h"
#include "BismuthBaseVisitor.h"
#include "STManager.h"
#include "PropertyManager.h"
#include "BismuthErrorHandler.h"
#include "BismuthInternalError.h"
#include "TypedAST.h"
#include "CastUtils.h"
#include "MacroUtils.h"
#include "ProtocolVisitor.h"

#include <functional>
#include <variant>
#include <fplus/fplus.hpp>

template<typename T>
concept RestRuleContext = requires(T a) {
    std::is_base_of<antlr4::ParserRuleContext, T>::value;
    { a.rest };
};

class SemanticVisitor;

class DefinitionSignature {
    private: 
    DefinitionSymbol& sym; 
    public: 
        DefinitionSignature(
            DefinitionSymbol & s
        ) : sym(s) {}

        DefinitionSignature(DefinitionSignature&) = delete; 
        virtual ~DefinitionSignature() = default; 

        // virtual antlr4::ParserRuleContext * getInnerContext(); 
        DefinitionSymbol& getSymbol() { return sym; }


        virtual std::variant<DefinitionNode *, ErrorChain *> generateAST(SemanticVisitor& sv) = 0;
    
    // antlr4::ParserRuleContext * innerCtx;
};

class FunctionSignature : public DefinitionSignature {
    public: 
        FunctionSignature(
            DefinitionSymbol& s, 
            vector<std::reference_wrapper<Symbol>> p, 
            BismuthParser::BlockContext * i
        ) : DefinitionSignature(s)
            , params(p)
            , innerCtx(i)
        {}
            
        BismuthParser::BlockContext * getInnerContext() { return innerCtx; }
        vector<std::reference_wrapper<Symbol>> getParams() { return params; }
        
        std::variant<DefinitionNode *, ErrorChain *> generateAST(SemanticVisitor& sv) override;
    private:
    vector<std::reference_wrapper<Symbol>> params;
    BismuthParser::BlockContext * innerCtx;
};

class ProgramSignature : public DefinitionSignature {
    public: 
        ProgramSignature(
            DefinitionSymbol& s, 
            std::reference_wrapper<Symbol> c, 
            BismuthParser::BlockContext * i
        ) : DefinitionSignature(s)
            , channel(c)
            , innerCtx(i)
        {}
            
        BismuthParser::BlockContext * getInnerContext() { return innerCtx; }
        std::reference_wrapper<Symbol> getChannelSymbol() { return channel; }

        std::variant<DefinitionNode *, ErrorChain *> generateAST(SemanticVisitor& sv) override;

    private:
    std::reference_wrapper<Symbol> channel;
    BismuthParser::BlockContext * innerCtx;
};

class EnumSignature : public DefinitionSignature {
    public: 
        EnumSignature(
            DefinitionSymbol& s,
            BismuthParser::DefineEnumContext * c
            // BismuthParser::BlockContext * i
        ) : DefinitionSignature(s)
            , ctx(c)
        {}
            
        // BismuthParser::BlockContext * getInnerContext() override { return innerCtx; }
        // std::reference_wrapper<Symbol> getChannelSymbol() { return channel; }

        std::variant<DefinitionNode *, ErrorChain *> generateAST(SemanticVisitor& sv) override;

    private:
    BismuthParser::DefineEnumContext *ctx;
};

class StructSignature : public DefinitionSignature {
    public: 
        StructSignature(
            DefinitionSymbol& s,
            BismuthParser::DefineStructContext *c
            // BismuthParser::BlockContext * i
        ) : DefinitionSignature(s)
            , ctx(c)
        //   , channel(c)
        //   , innerCtx(i)
        {}
            
        // BismuthParser::BlockContext * getInnerContext() override { return innerCtx; }
        // std::reference_wrapper<Symbol> getChannelSymbol() { return channel; }

        std::variant<DefinitionNode *, ErrorChain *> generateAST(SemanticVisitor& sv) override;

    private:
    BismuthParser::DefineStructContext *ctx;
    // std::reference_wrapper<Symbol> channel;
    // BismuthParser::BlockContext * innerCtx;
};



class TraitSignature : public DefinitionSignature {
    public: 
        TraitSignature(
            DefinitionSymbol& s
            // BismuthParser::BlockContext * i
        ) : DefinitionSignature(s)
        //   , channel(c)
        //   , innerCtx(i)
        {}
            
        // BismuthParser::BlockContext * getInnerContext() override { return innerCtx; }
        // std::reference_wrapper<Symbol> getChannelSymbol() { return channel; }

        std::variant<DefinitionNode *, ErrorChain *> generateAST(SemanticVisitor& sv) override;

    private:
    // std::reference_wrapper<Symbol> channel;
    // BismuthParser::BlockContext * innerCtx;
};

  

class SemanticVisitor : public BismuthBaseVisitor
{

  

public:
    /**
     * @brief Construct a Semantic Visitor object
     *
     * @param s Symbol table manager to use
     * @param p Property manager to use
     * @param f Compiler flags
     */
    SemanticVisitor(STManager& s, DisplayMode mode, int f = 0)
        : stmgr(s)
        , toStringMode(mode)
        , flags(f)
    {}

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

    std::variant<TypedNode *, ErrorChain *> visitCtx(BismuthParser::IConstExprContext *ctx);
    std::any visitIConstExpr(BismuthParser::IConstExprContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return visitCtx(ctx); }

    std::variant<TBooleanConstNode *, ErrorChain *> visitCtx(BismuthParser::BConstExprContext *ctx) { return visitCtx(ctx->booleanConst()); }
    std::any visitBConstExpr(BismuthParser::BConstExprContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TBooleanConstNode>(visitCtx(ctx)); }

    std::variant<TBooleanConstNode *, ErrorChain *> visitCtx(BismuthParser::BooleanConstContext *ctx);
    std::any visitBooleanConst(BismuthParser::BooleanConstContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TBooleanConstNode>(visitCtx(ctx)); }

    std::variant<TStringConstNode *, ErrorChain *> visitCtx(BismuthParser::SConstExprContext *ctx);
    std::any visitSConstExpr(BismuthParser::SConstExprContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TStringConstNode>(visitCtx(ctx)); }

    std::variant<TLogAndExprNode *, ErrorChain *> visitCtx(BismuthParser::LogAndExprContext *ctx);
    std::any visitLogAndExpr(BismuthParser::LogAndExprContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TLogAndExprNode>(visitCtx(ctx)); }

    std::variant<TLogOrExprNode *, ErrorChain *> visitCtx(BismuthParser::LogOrExprContext *ctx);
    std::any visitLogOrExpr(BismuthParser::LogOrExprContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TLogOrExprNode>(visitCtx(ctx)); }

    std::variant<TEqExprNode *, ErrorChain *> visitCtx(BismuthParser::EqExprContext *ctx);
    std::any visitEqExpr(BismuthParser::EqExprContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TEqExprNode>(visitCtx(ctx)); }

    std::variant<TUnaryExprNode *, ErrorChain *> visitCtx(BismuthParser::UnaryExprContext *ctx);
    std::any visitUnaryExpr(BismuthParser::UnaryExprContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TUnaryExprNode>(visitCtx(ctx)); }

    std::variant<TBinaryArithNode *, ErrorChain *> visitCtx(BismuthParser::BinaryArithExprContext *ctx);
    std::any visitBinaryArithExpr(BismuthParser::BinaryArithExprContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TBinaryArithNode>(visitCtx(ctx)); }

    std::variant<TypedNode *, ErrorChain *> visitCtx(BismuthParser::ParenExprContext *ctx);
    std::any visitParenExpr(BismuthParser::ParenExprContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TypedNode>(visitCtx(ctx)); }

    std::variant<TPathNode *, ErrorChain*> visitCtx(BismuthParser::PathContext * ctx, bool is_rvalue);
    std::any visitPath(BismuthParser::PathContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TPathNode>(visitCtx(ctx, true)); }

    std::variant<TFieldAccessNode *, ErrorChain *> visitCtx(BismuthParser::FieldAccessExprContext *ctx, bool is_rvalue);
    std::any visitFieldAccessExpr(BismuthParser::FieldAccessExprContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TFieldAccessNode>(visitCtx(ctx, true)); }

    std::variant<TIdentifier *, ErrorChain *> visitCtx(BismuthParser::IdentifierExprContext * ctx, bool is_rvalue);
    std::any visitIdentifierExpr(BismuthParser::IdentifierExprContext * ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TIdentifier>(visitCtx(ctx, true)); }

    std::any visitPathExpr(BismuthParser::PathExprContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TPathNode>(visitCtx(ctx->path(), true)); }

    std::variant<TDerefBoxNode *, ErrorChain *> visitCtx(BismuthParser::DerefContext *ctx, bool is_rvalue);
    std::any visitDeref(BismuthParser::DerefContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TDerefBoxNode>(visitCtx(ctx, true)); }

    std::variant<TypedNode *, ErrorChain *> visitCtx(BismuthParser::ArrayAccessContext *ctx, bool is_rvalue);
    std::any visitArrayAccess(BismuthParser::ArrayAccessContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return visitCtx(ctx, true); }

    std::variant<TAssignNode *, ErrorChain *> visitCtx(BismuthParser::AssignmentStatementContext *ctx);
    std::any visitAssignmentStatement(BismuthParser::AssignmentStatementContext * ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TAssignNode>(visitCtx(ctx)); }
    std::any visitAssignStatement(BismuthParser::AssignStatementContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TAssignNode>(visitCtx(ctx->assignmentStatement())); }

    std::variant<ParameterListNode, ErrorChain *> visitCtx(BismuthParser::ParameterListContext *ctx);
    std::any visitParameterList(BismuthParser::ParameterListContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return visitCtx(ctx); }

    std::variant<DefinitionNode *, ErrorChain *> visitCtx(BismuthParser::LambdaConstExprContext *ctx, optional_ref<DefinitionSymbol> sym);
    std::any visitLambdaConstExpr(BismuthParser::LambdaConstExprContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<DefinitionNode>(visitCtx(ctx, std::nullopt)); }

    std::variant<TBlockNode *, ErrorChain *> visitCtx(BismuthParser::BlockStatementContext *ctx) { return this->visitCtx(ctx->block()); }
    std::any visitBlockStatement(BismuthParser::BlockStatementContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TBlockNode>(visitCtx(ctx)); }

    std::variant<TBlockNode *, ErrorChain *> visitCtx(BismuthParser::BlockContext *ctx) { return this->safeVisitBlock(ctx, true); }
    std::any visitBlock(BismuthParser::BlockContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TBlockNode>(visitCtx(ctx)); }

    std::variant<TExternNode *, ErrorChain *> visitCtx(BismuthParser::ExternStatementContext *ctx);
    std::any visitExternStatement(BismuthParser::ExternStatementContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TExternNode>(visitCtx(ctx)); }

    std::variant<ParameterNode, ErrorChain *> visitCtx(BismuthParser::ParameterContext *ctx);
    std::any visitParameter(BismuthParser::ParameterContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return visitCtx(ctx); }

    std::variant<TypedNode *, ErrorChain *> visitCtx(BismuthParser::ExpressionStatementContext *ctx);
    std::any visitExpressionStatement(BismuthParser::ExpressionStatementContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return visitCtx(ctx); }

    std::variant<TInvocationNode *, ErrorChain *> visitCtx(BismuthParser::CallExprContext *ctx);// { return this->visitCtx(ctx->call); }
    std::any visitCallExpr(BismuthParser::CallExprContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TInvocationNode>(visitCtx(ctx)); }

    std::variant<TypedNode *, ErrorChain *> visitCtx(BismuthParser::ConditionContext *ctx) { return this->visitCondition(ctx->ex); }
    std::any visitCondition(BismuthParser::ConditionContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return visitCtx(ctx); }

    std::variant<TBinaryRelNode *, ErrorChain *> visitCtx(BismuthParser::BinaryRelExprContext *ctx);
    std::any visitBinaryRelExpr(BismuthParser::BinaryRelExprContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TBinaryRelNode>(visitCtx(ctx)); }

    std::variant<TSelectAlternativeNode *, ErrorChain *> visitCtx(BismuthParser::SelectAlternativeContext *ctx);
    std::any visitSelectAlternative(BismuthParser::SelectAlternativeContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TSelectAlternativeNode>(visitCtx(ctx)); }

    std::any visitTypeDef(BismuthParser::TypeDefContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return ctx->defineType()->accept(this); }

    std::variant<DefinitionNode *, ErrorChain *> visitCtx(BismuthParser::DefineImplContext *ctx);
    std::any visitDefineImpl(BismuthParser::DefineImplContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<DefinitionNode>(visitCtx(ctx)); }

    std::variant<DefinitionNode *, ErrorChain *> visitCtx(BismuthParser::DefineProgramContext *ctx);
    std::any visitDefineProgram(BismuthParser::DefineProgramContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<DefinitionNode>(visitCtx(ctx)); }

    std::variant<DefinitionNode *, ErrorChain *> visitCtx(BismuthParser::DefineFunctionContext *ctx);
    std::any visitDefineFunction(BismuthParser::DefineFunctionContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<DefinitionNode>(visitCtx(ctx)); }

    std::variant<TSelectStatementNode *, ErrorChain *> visitCtx(BismuthParser::SelectStatementContext *ctx);
    std::any visitSelectStatement(BismuthParser::SelectStatementContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TSelectStatementNode>(visitCtx(ctx)); }

    std::variant<TConditionalStatementNode *, ErrorChain *> visitCtx(BismuthParser::ConditionalStatementContext *ctx);
    std::any visitConditionalStatement(BismuthParser::ConditionalStatementContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TConditionalStatementNode>(visitCtx(ctx)); }

    std::variant<TWhileLoopNode *, ErrorChain *> visitCtx(BismuthParser::ProgramLoopContext *ctx);
    std::any visitProgramLoop(BismuthParser::ProgramLoopContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TWhileLoopNode>(visitCtx(ctx)); }


    std::variant<TBlockNode *, ErrorChain *> visitCtx(BismuthParser::ForStatementContext *ctx);
    std::any visitForStatement(BismuthParser::ForStatementContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TBlockNode>(visitCtx(ctx)); }

    std::variant<TReturnNode *, ErrorChain *> visitCtx(BismuthParser::ReturnStatementContext *ctx);
    std::any visitReturnStatement(BismuthParser::ReturnStatementContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TReturnNode>(visitCtx(ctx)); }

    std::variant<DefinitionNode *, ErrorChain *> visitCtx(BismuthParser::DefineEnumContext *ctx);
    std::any visitDefineEnum(BismuthParser::DefineEnumContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<DefinitionNode>(visitCtx(ctx)); }

    std::variant<DefinitionNode *, ErrorChain *> visitCtx(BismuthParser::DefineStructContext *ctx);
    std::any visitDefineStruct(BismuthParser::DefineStructContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<DefinitionNode>(visitCtx(ctx)); }

    std::variant<DefinitionNode *, ErrorChain *> visitCtx(BismuthParser::DefineTraitContext *ctx);
    std::any visitDefineTrait(BismuthParser::DefineTraitContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<DefinitionNode>(visitCtx(ctx)); }

    std::variant<TInitProductNode *, ErrorChain *> visitCtx(BismuthParser::InitProductContext *ctx);
    std::any visitInitProduct(BismuthParser::InitProductContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TInitProductNode>(visitCtx(ctx)); }

    std::variant<TArrayRValue *, ErrorChain *> visitCtx(BismuthParser::ArrayExpressionContext * ctx);
    std::any visitArrayExpression(BismuthParser::ArrayExpressionContext * ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TArrayRValue>(visitCtx(ctx)); }

    std::variant<TInitBoxNode *, ErrorChain *> visitCtx(BismuthParser::InitBoxContext *ctx);
    std::any visitInitBox(BismuthParser::InitBoxContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TInitBoxNode>(visitCtx(ctx)); }

    std::variant<TProgramSendNode *, ErrorChain *> TvisitProgramSend(BismuthParser::ProgramSendContext *ctx);
    std::any visitProgramSend(BismuthParser::ProgramSendContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TProgramSendNode>(TvisitProgramSend(ctx)); }

    std::variant<TProgramRecvNode *, ErrorChain *> TvisitAssignableRecv(BismuthParser::AssignableRecvContext *ctx);
    std::any visitAssignableRecv(BismuthParser::AssignableRecvContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TProgramRecvNode>(TvisitAssignableRecv(ctx)); }

    std::variant<TProgramIsPresetNode *, ErrorChain *> TvisitAssignableIsPresent(BismuthParser::AssignableIsPresentContext *ctx);
    std::any visitAssignableIsPresent(BismuthParser::AssignableIsPresentContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TProgramIsPresetNode>(TvisitAssignableIsPresent(ctx)); }

    std::variant<TProgramContractNode *, ErrorChain *> TvisitProgramContract(BismuthParser::ProgramContractContext *ctx);
    std::any visitProgramContract(BismuthParser::ProgramContractContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TProgramContractNode>(TvisitProgramContract(ctx)); }

    std::variant<TProgramWeakenNode *, ErrorChain *> TvisitProgramWeaken(BismuthParser::ProgramWeakenContext *ctx);
    std::any visitProgramWeaken(BismuthParser::ProgramWeakenContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TProgramWeakenNode>(TvisitProgramWeaken(ctx)); }

    std::variant<TProgramCancelNode *, ErrorChain *> TvisitProgramCancel(BismuthParser::ProgramCancelContext *ctx);
    std::any visitProgramCancel(BismuthParser::ProgramCancelContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TProgramCancelNode>(TvisitProgramCancel(ctx)); }

    std::variant<TProgramExecNode *, ErrorChain *> TvisitAssignableExec(BismuthParser::AssignableExecContext *ctx);
    std::any visitAssignableExec(BismuthParser::AssignableExecContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TProgramExecNode>(TvisitAssignableExec(ctx)); }

    std::variant<TProgramAcceptNode *, ErrorChain *> TvisitProgramAccept(BismuthParser::ProgramAcceptContext *ctx);
    std::any visitProgramAccept(BismuthParser::ProgramAcceptContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TProgramAcceptNode>(TvisitProgramAccept(ctx)); }

    std::variant<TProgramAcceptWhileNode *, ErrorChain *> TvisitProgramAcceptWhile(BismuthParser::ProgramAcceptWhileContext *ctx);
    std::any visitProgramAcceptWhile(BismuthParser::ProgramAcceptWhileContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TProgramAcceptWhileNode>(TvisitProgramAcceptWhile(ctx)); }

    std::variant<TProgramAcceptIfNode *, ErrorChain *> TvisitProgramAcceptIf(BismuthParser::ProgramAcceptIfContext *ctx);
    std::any visitProgramAcceptIf(BismuthParser::ProgramAcceptIfContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TProgramAcceptIfNode>(TvisitProgramAcceptIf(ctx)); }

    std::any visitCompilationUnit(BismuthParser::CompilationUnitContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); assert(false && "Compiler got lost; use phased visit instead!"); }

    std::variant<TVarDeclNode *, ErrorChain *> visitCtx(BismuthParser::VariableDeclarationContext *ctx);
    std::any visitVariableDeclaration(BismuthParser::VariableDeclarationContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<>(visitCtx(ctx)); };
    std::any visitVarDeclStatement(BismuthParser::VarDeclStatementContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<>(visitCtx(ctx->variableDeclaration())); }

    std::variant<TMatchStatementNode *, ErrorChain *> visitCtx(BismuthParser::MatchStatementContext *ctx);
    std::any visitMatchStatement(BismuthParser::MatchStatementContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<>(visitCtx(ctx)); } // NOTE: CASTS NEEDED B/C OF HOW C++ HANDLES ANYs BY MANGLED NAME!

    std::variant<TExitNode *, ErrorChain *> visitCtx(BismuthParser::ExitStatementContext *ctx);
    std::any visitExitStatement(BismuthParser::ExitStatementContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<>(visitCtx(ctx)); }

    std::variant<TExprCopyNode *, ErrorChain *> TvisitCopyExpr(BismuthParser::CopyExprContext *ctx);
    std::any visitCopyExpr(BismuthParser::CopyExprContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TExprCopyNode>(TvisitCopyExpr(ctx)); }

    std::variant<TAsChannelNode *, ErrorChain *> TvisitAsChannelExpr(BismuthParser::AsChannelExprContext *ctx);
    std::any visitAsChannelExpr(BismuthParser::AsChannelExprContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TAsChannelNode>(TvisitAsChannelExpr(ctx)); }


    // Note: this method doesn't actually add anything to codegen---it just adds symbols or throws errors
    std::optional<ErrorChain *> TVisitImportStatement(BismuthParser::ImportStatementContext * ctx);
    std::any visitImportStatement(BismuthParser::ImportStatementContext * ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TVisitImportStatement(ctx); }

    const Type *visitCtx(BismuthParser::AssignmentContext *ctx);

    /*
     *  Types
     */
    std::variant<const Type *, ErrorChain *> visitCtx(BismuthParser::BaseTypeContext *ctx);
    std::any visitBaseType(BismuthParser::BaseTypeContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return visitCtx(ctx); } // casting done in the function

    std::variant<const TypeDynArray *, ErrorChain*> visitCtx(BismuthParser::DynArrayTypeContext * ctx);
    std::any visitDynArrayType(BismuthParser::DynArrayTypeContext * ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TypeVariantCast<TypeDynArray>(visitCtx(ctx)); }

    std::variant<const TypeArray *, ErrorChain *> visitCtx(BismuthParser::ArrayTypeContext *ctx);
    std::any visitArrayType(BismuthParser::ArrayTypeContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TypeVariantCast<TypeArray>(visitCtx(ctx)); } // { return visitCtx(ctx); }

    std::variant<const TypeFunc *, ErrorChain *> visitCtx(BismuthParser::LambdaTypeContext *ctx);
    std::any visitLambdaType(BismuthParser::LambdaTypeContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TypeVariantCast<TypeFunc>(visitCtx(ctx)); } // { return visitCtx(ctx); }

    std::variant<const TypeChannel *, ErrorChain *> visitCtx(BismuthParser::ChannelTypeContext *ctx);
    std::any visitChannelType(BismuthParser::ChannelTypeContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TypeVariantCast<TypeChannel>(visitCtx(ctx)); } // { return visitCtx(ctx); }

    std::variant<const TypeBox *, ErrorChain *> visitCtx(BismuthParser::BoxTypeContext *ctx);
    std::any visitBoxType(BismuthParser::BoxTypeContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TypeVariantCast<TypeBox>(visitCtx(ctx)); } // { return visitCtx(ctx); }

    std::variant<const TypeProgram *, ErrorChain *> visitCtx(BismuthParser::ProgramTypeContext *ctx);
    std::any visitProgramType(BismuthParser::ProgramTypeContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TypeVariantCast<TypeProgram>(visitCtx(ctx)); } // { return visitCtx(ctx); }

    // std::variant<const, ErrorChain*> visitCtx(BismuthParser::PathContext * ctx, bool is_rvalue);
    std::variant<const Type *, ErrorChain *> visitPathType(BismuthParser::PathContext *ctx);
    std::any visitCustomType(BismuthParser::CustomTypeContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return visitPathType(ctx->path()); } // Casting done by lower level call

    std::variant<const Type *, ErrorChain *> visitCtx(BismuthParser::TypeOrVarContext *ctx);
    std::any visitTypeOrVar(BismuthParser::TypeOrVarContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return visitCtx(ctx); }

    std::variant<const TypeSum *, ErrorChain *>  visitCtx(BismuthParser::SumTypeContext *ctx);
    std::any visitSumType(BismuthParser::SumTypeContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TypeVariantCast<TypeSum>(visitCtx(ctx)); } // { return visitCtx(ctx); }

    std::variant<const Type *, ErrorChain *> visitCtx(BismuthParser::TemplatedTypeContext * ctx);
    std::any visitTemplatedType(BismuthParser::TemplatedTypeContext * ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return visitCtx(ctx); }

    // std::optional<ErrorChain *> calculatePredeclarations(BismuthParser::CompilationUnitContext *ctx);
    std::optional<ErrorChain *> provisionFwdDeclSymbols(BismuthParser::CompilationUnitContext *ctx);
    std::variant<std::vector<DefinitionSignature *>, ErrorChain *> defineFwdDeclSymbols(BismuthParser::CompilationUnitContext *ctx);
    std::variant<std::vector<DefinitionNode *>, ErrorChain *> visitFwdDecls(std::vector<DefinitionSignature *> sigs);
    std::variant<std::vector<TExternNode *>, ErrorChain *> visitExterns(BismuthParser::CompilationUnitContext *ctx);
    std::optional<ErrorChain *> postCUVisitChecks(BismuthParser::CompilationUnitContext *ctx);

    // typedef unsigned long ulong;
    typedef std::variant<TCompilationUnitNode *, ErrorChain *> PhaseNResult;
    typedef std::function<PhaseNResult()> PhaseNClosure;

    typedef std::variant<PhaseNClosure, ErrorChain *> DefineFwdDeclsPhaseResult;
    typedef std::function<DefineFwdDeclsPhaseResult()> DefineFwdDeclsPhaseClosure;

    typedef std::variant<DefineFwdDeclsPhaseClosure, ErrorChain *> ImportPhaseResult;
    typedef std::function<ImportPhaseResult()> ImportPhaseClosure;

std::variant<
    ImportPhaseClosure,
    ErrorChain *
>
    phasedVisit(BismuthParser::CompilationUnitContext *ctx, std::vector<std::string> steps);

    /*
     * Traditional visitor methods all overridden with our typed versions
     */
    // std::any visitVariableExpr(BismuthParser::VariableExprContext *ctx) override { return visitCtx(ctx); }
    std::any visitAssignment(BismuthParser::AssignmentContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return visitCtx(ctx); }

    std::variant<TChannelCaseStatementNode *, ErrorChain *> TvisitProgramCase(BismuthParser::ProgramCaseContext *ctx);
    std::any visitProgramCase(BismuthParser::ProgramCaseContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TChannelCaseStatementNode>(TvisitProgramCase(ctx)); }

    std::variant<TProgramProjectNode *, ErrorChain *> TvisitProgramProject(BismuthParser::ProgramProjectContext *ctx);
    std::any visitProgramProject(BismuthParser::ProgramProjectContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TNVariantCast<TProgramProjectNode>(TvisitProgramProject(ctx)); }


    /*
    virtual std::any visitGenericTemplate(BismuthParser::GenericTemplateContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual std::any visitGenericType(BismuthParser::GenericTypeContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual std::any visitGenericSession(BismuthParser::GenericSessionContext *ctx) override {
        return visitChildren(ctx);
    }
    */

    TemplateInfo TvisitGenericTemplate(BismuthParser::GenericTemplateContext *ctx);
    std::any visitGenericTemplate(BismuthParser::GenericTemplateContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TvisitGenericTemplate(ctx); }

    std::variant<std::vector<const Type *>, ErrorChain *> TvisitGenericSpecifier(BismuthParser::GenericSpecifierContext *ctx);
    std::any visitGenericSpecifier(BismuthParser::GenericSpecifierContext *ctx) override { DEBUG_CERR("Visit " + ctx->getText()); return TvisitGenericSpecifier(ctx); }


    std::variant<TypedNode *, ErrorChain *> visitCondition(BismuthParser::ExpressionContext *ex)
    {
        auto a =  ex->accept(this);
        DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, cond, anyOpt2VarError<TypedNode>(errorHandler, a), ex, "Unable to type check condition expression");
        const Type& conditionType = cond->getType();

        if (conditionType.isNotSubtype(*Types::DYN_BOOL))
        {
            return errorHandler.addError(ex->getStart(), "Condition expected boolean, but was given " + conditionType.toString(toStringMode));
        }
        
        return cond;
    }


    // TODO: refactor into general saveVisit!
    /**
     * @brief Used to safely enter a block. This is used to ensure that there isn't code following returns and that
     * variables are inferred, and that linears are used.
     *
     * @param ctx The BlockContext to visit
     * @param newScope  true if we should enter a new scope, false otherwise
     * @return const Type* Types::UNDEFINED as this is a statement and not a value
     */
    std::variant<TBlockNode *, ErrorChain *> safeVisitBlock(BismuthParser::BlockContext *ctx, bool newScope)
    {
        // Enter a new scope if desired
        if (newScope)
            stmgr.enterScope(StopType::NONE); // TODO: DO BETTER?

        std::vector<TypedNode *> nodes;

        // Tracks if we have found a return statement or not
        bool foundReturn = false;
        for (auto e : ctx->stmts)
        {
            // Visit all the statements in the block
            DEFINE_OR_PROPAGATE_VARIANT_WMSG(TypedNode *, tn, anyOpt2VarError<TypedNode>(errorHandler, e->accept(this)), ctx, "Failed to type check statement in block");
            nodes.push_back(tn);
            // If we found a return, then this is dead code, and we can break out of the loop.
            if (foundReturn)
            {
                errorHandler.addError(ctx->getStart(), "Dead code");
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


    // TODO: will have to be very careful with this. It could easily break type
    // checking... maybe? by skipping over parts due to return, but then still
    // check later code...
    std::variant<TBlockNode *, ErrorChain *> safeVisit(std::vector<antlr4::ParserRuleContext *> exprs, bool newScope)
    {
        if(exprs.size() == 0) return errorHandler.addCompilerError(nullptr, "safeVisit was called; however, exprs was an empty list.");

        // Enter a new scope if desired
        if (newScope)
            stmgr.enterScope(StopType::NONE); // TODO: DO BETTER?

        std::vector<TypedNode *> nodes;

        // Tracks if we have found a return statement or not
        bool foundReturn = false;
        for (auto expr : exprs)
        {
            // Visit all the statements in the block
            // TODO: does having return here w/o safe exit again mean that we have a bug if we hit this case?
            DEFINE_OR_PROPAGATE_VARIANT(TypedNode *, tn, anyOpt2VarError<TypedNode>(errorHandler, expr->accept(this)), expr);
            nodes.push_back(tn);

            // If we found a return, then this is dead code, and we can break out of the loop.
            if (foundReturn)
            {
                errorHandler.addError(expr->getStart(), "Dead code");
                break;
            }

            // If the current statement is a return, set foundReturn = true
            if (dynamic_cast<BismuthParser::ReturnStatementContext *>(expr)) // FIXME: what about exit? Also need it here AND in block!
                foundReturn = true;
        }
        // If we entered a new scope, then we can now safely exit a scope
        if (newScope)
            this->safeExitScope(exprs.at(0));

        return new TBlockNode(nodes, exprs.at(0)->getStart()); // FIXME: DO BETTER< HANDLE ERRORS! CURRENTLY ALWAYS RETURNS NODE
    }

    struct ProtocolCompareInv
    {
        bool operator()(std::pair<std::variant<const ProtocolSequence *, std::string>, BismuthParser::StatementContext *> ap,
                        std::pair<std::variant<const ProtocolSequence *, std::string>, BismuthParser::StatementContext *> bp) const
        {
            std::variant<const ProtocolSequence *, std::string> a = ap.first;
            std::variant<const ProtocolSequence *, std::string> b = bp.first;

            if(std::holds_alternative<std::string>(a))
            {
                if(std::holds_alternative<std::string>(b))
                    return std::get<std::string>(a) < std::get<std::string>(b);

                return true; // TODO: verify
            }

            if(std::holds_alternative<std::string>(b))
                return false;

            return std::get<const ProtocolSequence *>(a)->toString(DisplayMode::C_STYLE) < std::get<const ProtocolSequence *>(b)->toString(DisplayMode::C_STYLE);
        }
    };

    template <typename T>
    struct ConditionalData
    {
        vector<T> cases;
        vector<TypedNode *> post;

        ConditionalData(vector<T> cases, vector<TypedNode *> post)
            : cases(cases)
            , post(post)
        {}
    };

    //FIXME: WHAT AB Ext<A,B>;!P;Ext<A,B>?
    struct DeepRestData
    {
        vector<BismuthParser::StatementContext *> ctxRest;
        bool isGenerated;
        vector<TypedNode *> post;

        DeepRestData(vector<BismuthParser::StatementContext *> ctx) : ctxRest(ctx), isGenerated(false) {}
    };


    template <RestRuleContext R, typename T, typename Y>
    inline std::variant<ConditionalData<Y>, ErrorChain *> checkBranch(
        R *ctx,
        std::function<void(std::deque<DeepRestData *> *)> forwardBindings,
        std::vector<T *> ctxCases,
        bool checkRestIndependently,
        std::function<TypedNode *(Y)> getNode,
        std::function<std::variant<Y, ErrorChain *>(T *)> typeCheck);


    inline std::variant<const ProtocolSequence *, ErrorChain *>
    visitProtocolAsSeq(BismuthParser::ProtocolContext *ctx);

    inline std::variant<const TypeChannel *, ErrorChain *>
    visitProtocolAsChannel(BismuthParser::ProtocolContext *ctx);

public:
    DisplayMode getToStringMode() { return toStringMode; }

private:
friend class DefinitionSignature;
friend class ProgramSignature;
friend class FunctionSignature;
friend class EnumSignature;
friend class StructSignature;
friend class TraitSignature;
    STManager& stmgr;
    DisplayMode toStringMode;
    PropertyManager<std::reference_wrapper<DefinitionSymbol>> symBindings = PropertyManager<std::reference_wrapper<DefinitionSymbol>>();
    PropertyManager<std::deque<DeepRestData *>*> restBindings = PropertyManager<std::deque<DeepRestData *>*>();
    BismuthErrorHandler errorHandler = BismuthErrorHandler(SEMANTIC);


    int flags; // Compiler flags


    std::variant<TypedNode *, ErrorChain *> visitLValue(antlr4::ParserRuleContext *ctx);

    // void safeVisitScope(antlr4::ParserRuleContext *ctx, StopType stopType, void (*visitor)())
    // {
    //     stmgr.enterScope(stopType);
    //     visitor();
    //     safeExitScope(ctx);
    // }

    // template<typename T>
    // safeVisitScope(StopType stopType, T (*visitor)())
    // {
    //     stmgr.enterScope(stopType);
    //     visitor();
    //     // safeExitScope(ctx);
    //     stmgr.exitScope();
    // }

    std::variant<FunctionSignature *, ErrorChain *> defineFunctionType(DefinitionSymbol& sym, BismuthParser::LambdaConstExprContext *ctx, const TypeFunc *funcType, bool variadic=false);
    std::variant<ProgramSignature *, ErrorChain *> defineProgramType(DefinitionSymbol& sym, BismuthParser::DefineProgramContext *ctx, const TypeProgram *progType);
    std::variant<EnumSignature *, ErrorChain *> defineEnumType(DefinitionSymbol& sym, BismuthParser::DefineEnumContext *ctx, const TypeSum *sumTy);
    std::variant<StructSignature *, ErrorChain *> defineStructType(DefinitionSymbol& sym, BismuthParser::DefineStructContext *ctx, const TypeStruct *structType);
    std::variant<TraitSignature *, ErrorChain *> defineTraitType(DefinitionSymbol& sym, BismuthParser::DefineTraitContext *ctx, const TypeTrait *traitTy);
    std::variant<DefinitionSignature *, ErrorChain *> defineTemplateType(BismuthParser::DefineTypeContext *ctx, const TypeTemplate *templateTy, DefinitionSymbol& defSym, VisibilityModifier m);
    std::variant<std::reference_wrapper<Scope>, ErrorChain*> enterTemplateScope(DefinitionSymbol& defSym, VisibilityModifier m, TemplateInfo info);

    void safeExitScope(antlr4::ParserRuleContext *ctx)
    {
        // First, try exiting the scope
        std::optional<std::reference_wrapper<Scope>> res = stmgr.exitScope();

        // If we did so and got a value back, then we can do type inferencing.
        if (res)
        {
            // Get the Scope* and check for any uninferred symbols
            Scope& scope = res.value().get();

            // Try to unify symbols (really needed for things like nums wherein
            // we know what types are possible to infer, so we can just
            // pick one if the code doesn't make it clear which variant we need)
            for(Symbol& sym : scope.getSymbols(SymbolLookupFlags::UNINFERRED_TYPE))
            {
                // Should always be inferrable
                if(const TypeInfer * inf = dynamic_cast<const TypeInfer *>(sym.getType()))
                {
                    inf->unify();
                }
            }

            // If there are any uninferred symbols, then add it as an error as we won't be able to resolve them
            // due to the var leaving the scope
            if (auto unInf = scope.getSymbols(SymbolLookupFlags::UNINFERRED_TYPE); // TODO: CHANGE getSymbols BACK TO CONST?
                unInf.size() > 0)
            {
                std::ostringstream details;

                for (auto e : unInf)
                {
                    details << e.get().toString() << "; ";
                }

                errorHandler.addError(ctx->getStart(), "Uninferred types in context: " + details.str());
            }

            // If there are any uninferred symbols, then add it as an error as we won't be able to resolve them
            // due to the var leaving the scope
            if (auto lins = scope.getSymbols(SymbolLookupFlags::PENDING_LINEAR);
                lins.size() > 0)
            {
                std::ostringstream details;

                for (auto e : lins)
                {
                    details << e.get().toString() << "; ";
                }

                errorHandler.addError(ctx->getStart(), "Unused linear types in context: " + details.str());
            }
        }
        // return res;
    }

    // NOTE: IS THERE A WAY FOR ME TO PROVIDE ONE OF TWO TYPES TO A FN, AND THEN HAVE THAT BE RET TYPE? (BUT ONLY ONE OF TWO...)

    //BismuthParser::DefineFunctionContext *ctx,
    template <class T>
    T defineTypeCase(BismuthParser::DefineTypeContext * ctx,
                        std::function<T(BismuthParser::DefineFunctionContext *)> funcFn,
                        std::function<T(BismuthParser::DefineProgramContext *)> progFn,
                        std::function<T(BismuthParser::DefineStructContext *)> structFn,
                        std::function<T(BismuthParser::DefineEnumContext *)> enumFn,
                        std::function<T(BismuthParser::DefineTraitContext *)> traitFn,
                        std::function<T(BismuthParser::DefineTypeContext *)> errFn){
        if(BismuthParser::DefineFunctionContext * fnCtx = dynamic_cast<BismuthParser::DefineFunctionContext *>(ctx))
            return funcFn(fnCtx);
        if(BismuthParser::DefineProgramContext * progCtx = dynamic_cast<BismuthParser::DefineProgramContext *>(ctx))
            return progFn(progCtx);
        if(BismuthParser::DefineStructContext * structCtx = dynamic_cast<BismuthParser::DefineStructContext *>(ctx))
            return structFn(structCtx);
        if(BismuthParser::DefineEnumContext * enumCtx = dynamic_cast<BismuthParser::DefineEnumContext *>(ctx))
            return enumFn(enumCtx);
        if(BismuthParser::DefineTraitContext * traitCtx = dynamic_cast<BismuthParser::DefineTraitContext *>(ctx))
            return traitFn(traitCtx);
        return errFn(ctx);
    }

    std::variant<DefinitionSignature *, ErrorChain *> getTemplateSignature(
        VisibilityModifier m,
        optional_ref<DefinitionSymbol> opt, 
        std::string symName, 
        BismuthParser::DefineTypeContext* innerCtx
    );

    std::variant<DefinitionSignature *, ErrorChain *>  defineAndGetSymbolFor(BismuthParser::DefineTypeContext * ctx, VisibilityModifier m = VisibilityModifier::PRIVATE);
    
    // std::variant<ProgramSignature*, ErrorChain *> getProgramSignature(BismuthParser::DefineProgramContext * ctx, VisibilityModifier m);
    // std::variant<DefinitionSignature*, ErrorChain *> getFunctionSignature(BismuthParser::DefineFunctionContext * fnCtx, VisibilityModifier m);
    std::variant<FunctionSignature*, ErrorChain *> getLambdaSignature(BismuthParser::LambdaConstExprContext *ctx, optional_ref<DefinitionSymbol> sym);

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
            restBindings.bind(cs, rd);
            return;
        }

        if (BismuthParser::SelectStatementContext *sel = dynamic_cast<BismuthParser::SelectStatementContext *>(ctx))
        {
            // for(auto c : sel->cases) {
            //     bindRestData(c->eval, rd);
            // }
            restBindings.bind(sel, rd);
            return;
        }

        if (BismuthParser::MatchStatementContext *mc = dynamic_cast<BismuthParser::MatchStatementContext *>(ctx))
        {
            // for(auto c : mc->cases) {
            //     bindRestData(c->eval, rd);
            // }
            restBindings.bind(mc, rd);
            return;
        }

        if (BismuthParser::ProgramCaseContext *cc = dynamic_cast<BismuthParser::ProgramCaseContext *>(ctx))
        {
            // for(auto o : cc->opts) {
            //     bindRestData(o->eval, rd);
            // }
            restBindings.bind(cc, rd);
            return;
        }
    }

    void isTypeCyclical(const Type *def, const Type *inner)
    {
        std::vector<const Type *> toVisit = {inner};
        std::set<const Type *> visited = {def};
    }

    // std::any reportBadVisit(antlr4::ParserRuleContext * ctx) {
    //     return errorHandler.addError(ctx->getStart(), "Bad visit from semantic visitor to context!");
    // }
};
