/**
 * @file TypeVisitor.h
 * @author Alex Friedman (ahfriedman.com)
 * @brief This file was an attempt to make a typed-wrapper around the base visitor. It did not appear to work, so this is UNUSED; may return later to try this again
 * @version 0.1
 * 
 * 
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "BismuthBaseVisitor.h"

template <class T> class TypedVisitor : public BismuthBaseVisitor
{
public:

    T visitCtx(BismuthParser::CompilationUnitContext * ctx); 
    
    std::any visitCompilationUnit(BismuthParser::CompilationUnitContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::InvocationContext * ctx); 
    std::any visitInvocation(BismuthParser::InvocationContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::ArrayAccessContext * ctx); 
    std::any visitArrayAccess(BismuthParser::ArrayAccessContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::ArrayOrVarContext * ctx); 
    std::any visitArrayOrVar(BismuthParser::ArrayOrVarContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::IConstExprContext * ctx); 
    std::any visitIConstExpr(BismuthParser::IConstExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::ArrayAccessExprContext * ctx); 
    std::any visitArrayAccessExpr(BismuthParser::ArrayAccessExprContext *ctx) override { return visitCtx(ctx); }
    
    T visitCtx(BismuthParser::SConstExprContext * ctx); 
    std::any visitSConstExpr(BismuthParser::SConstExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::UnaryExprContext * ctx); 
    std::any visitUnaryExpr(BismuthParser::UnaryExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::BinaryArithExprContext * ctx); 
    std::any visitBinaryArithExpr(BismuthParser::BinaryArithExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::EqExprContext * ctx); 
    std::any visitEqExpr(BismuthParser::EqExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::LogAndExprContext * ctx); 
    std::any visitLogAndExpr(BismuthParser::LogAndExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::LogOrExprContext * ctx); 
    std::any visitLogOrExpr(BismuthParser::LogOrExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::CallExprContext * ctx); 
    std::any visitCallExpr(BismuthParser::CallExprContext *ctx) override { return visitCtx(ctx); }

    // T visitCtx(BismuthParser::VariableExprContext * ctx); 
    // std::any visitVariableExpr(BismuthParser::VariableExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::FieldAccessExprContext * ctx); 
    std::any visitFieldAccessExpr(BismuthParser::FieldAccessExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::ParenExprContext * ctx); 
    std::any visitParenExpr(BismuthParser::ParenExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::BinaryRelExprContext * ctx); 
    std::any visitBinaryRelExpr(BismuthParser::BinaryRelExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::BConstExprContext * ctx); 
    std::any visitBConstExpr(BismuthParser::BConstExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::BlockContext * ctx); 
    std::any visitBlock(BismuthParser::BlockContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::ConditionContext * ctx); 
    std::any visitCondition(BismuthParser::ConditionContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::SelectAlternativeContext * ctx); 
    std::any visitSelectAlternative(BismuthParser::SelectAlternativeContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::ParameterListContext * ctx); 
    std::any visitParameterList(BismuthParser::ParameterListContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::ParameterContext * ctx); 
    std::any visitParameter(BismuthParser::ParameterContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::AssignmentContext * ctx); 
    std::any visitAssignment(BismuthParser::AssignmentContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::ExternStatementContext * ctx); 
    std::any visitExternStatement(BismuthParser::ExternStatementContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::FuncDefContext * ctx); 
    std::any visitFuncDef(BismuthParser::FuncDefContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::AssignStatementContext * ctx); 
    std::any visitAssignStatement(BismuthParser::AssignStatementContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::VarDeclStatementContext * ctx); 
    std::any visitVarDeclStatement(BismuthParser::VarDeclStatementContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::ProgramLoopContext * ctx); 
    std::any visitProgramLoop(BismuthParser::ProgramLoopContext *ctx) override { return visitCtx(ctx); }


    T visitCtx(BismuthParser::ConditionalStatementContext * ctx); 
    std::any visitConditionalStatement(BismuthParser::ConditionalStatementContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::SelectStatementContext * ctx); 
    std::any visitSelectStatement(BismuthParser::SelectStatementContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::CallStatementContext * ctx); 
    std::any visitCallStatement(BismuthParser::CallStatementContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::ReturnStatementContext * ctx); 
    std::any visitReturnStatement(BismuthParser::ReturnStatementContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::BlockStatementContext * ctx); 
    std::any visitBlockStatement(BismuthParser::BlockStatementContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::TypeOrVarContext * ctx); 
    std::any visitTypeOrVar(BismuthParser::TypeOrVarContext *ctx) override { return visitCtx(ctx); }

    // T visitCtx(BismuthParser::TypeContext * ctx); 
    // std::any visitType(BismuthParser::TypeContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(BismuthParser::BooleanConstContext * ctx); 
    std::any visitBooleanConst(BismuthParser::BooleanConstContext *ctx) override { return visitCtx(ctx); }
};


/*
class TypeVisitor : public TypedVisitor<const Type*> 
{
    const Type *visitCtx(BismuthParser::CompilationUnitContext *ctx);
    const Type *visitCtx(BismuthParser::InvocationContext *ctx);
    const Type *visitCtx(BismuthParser::ArrayAccessContext *ctx);
    const Type *visitCtx(BismuthParser::ArrayOrVarContext *ctx);
    const Type *visitCtx(BismuthParser::IConstExprContext *ctx);
    const Type *visitCtx(BismuthParser::ArrayAccessExprContext *ctx);
    const Type *visitCtx(BismuthParser::SConstExprContext *ctx);
    const Type *visitCtx(BismuthParser::UnaryExprContext *ctx);
    const Type *visitCtx(BismuthParser::BinaryArithExprContext *ctx);
    const Type *visitCtx(BismuthParser::EqExprContext *ctx);
    const Type *visitCtx(BismuthParser::LogAndExprContext *ctx);
    const Type *visitCtx(BismuthParser::LogOrExprContext *ctx);
    const Type *visitCtx(BismuthParser::CallExprContext *ctx);
    const Type *visitCtx(BismuthParser::VariableExprContext *ctx);
    const Type *visitCtx(BismuthParser::FieldAccessExprContext *ctx);
    const Type *visitCtx(BismuthParser::ParenExprContext *ctx);
    const Type *visitCtx(BismuthParser::BinaryRelExprContext *ctx);
    const Type *visitCtx(BismuthParser::BConstExprContext *ctx);
    const Type *visitCtx(BismuthParser::BlockContext *ctx);
    const Type *visitCtx(BismuthParser::ConditionContext *ctx);
    const Type *visitCtx(BismuthParser::SelectAlternativeContext *ctx);
    const Type *visitCtx(BismuthParser::ParameterListContext *ctx);
    const Type *visitCtx(BismuthParser::ParameterContext *ctx);
    const Type * visitCtx(BismuthParser::AssignmentContext *ctx) ;
    const Type *visitCtx(BismuthParser::ExternStatementContext *ctx);
    const Type *visitCtx(BismuthParser::FuncDefContext *ctx);
    const Type *visitCtx(BismuthParser::AssignStatementContext *ctx);
    const Type *visitCtx(BismuthParser::VarDeclStatementContext *ctx);
    const Type *visitCtx(BismuthParser::LoopStatementContext *ctx);
    const Type *visitCtx(BismuthParser::ConditionalStatementContext *ctx);
    const Type *visitCtx(BismuthParser::SelectStatementContext *ctx);
    const Type *visitCtx(BismuthParser::CallStatementContext *ctx);
    const Type *visitCtx(BismuthParser::ReturnStatementContext *ctx);
    const Type *visitCtx(BismuthParser::BlockStatementContext *ctx);
    const Type *visitCtx(BismuthParser::TypeOrVarContext *ctx);
    const Type *visitCtx(BismuthParser::TypeContext *ctx);
    const Type *visitCtx(BismuthParser::BooleanConstContext *ctx);
};
*/
// class DerivedVisitor : BismuthBaseVisitor
// {
// public: 
//     int visitCtx(BismuthParser::CompilationUnitContext * ctx) {

//     }
// };
