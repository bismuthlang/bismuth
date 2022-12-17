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
#include "antlr4-runtime.h"
#include "WPLBaseVisitor.h"

template <class T> class TypedVisitor : public WPLBaseVisitor
{
public:

    T visitCtx(WPLParser::CompilationUnitContext * ctx); 
    
    std::any visitCompilationUnit(WPLParser::CompilationUnitContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::InvocationContext * ctx); 
    std::any visitInvocation(WPLParser::InvocationContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::ArrayAccessContext * ctx); 
    std::any visitArrayAccess(WPLParser::ArrayAccessContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::ArrayOrVarContext * ctx); 
    std::any visitArrayOrVar(WPLParser::ArrayOrVarContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::IConstExprContext * ctx); 
    std::any visitIConstExpr(WPLParser::IConstExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::ArrayAccessExprContext * ctx); 
    std::any visitArrayAccessExpr(WPLParser::ArrayAccessExprContext *ctx) override { return visitCtx(ctx); }
    
    T visitCtx(WPLParser::SConstExprContext * ctx); 
    std::any visitSConstExpr(WPLParser::SConstExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::UnaryExprContext * ctx); 
    std::any visitUnaryExpr(WPLParser::UnaryExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::BinaryArithExprContext * ctx); 
    std::any visitBinaryArithExpr(WPLParser::BinaryArithExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::EqExprContext * ctx); 
    std::any visitEqExpr(WPLParser::EqExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::LogAndExprContext * ctx); 
    std::any visitLogAndExpr(WPLParser::LogAndExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::LogOrExprContext * ctx); 
    std::any visitLogOrExpr(WPLParser::LogOrExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::CallExprContext * ctx); 
    std::any visitCallExpr(WPLParser::CallExprContext *ctx) override { return visitCtx(ctx); }

    // T visitCtx(WPLParser::VariableExprContext * ctx); 
    // std::any visitVariableExpr(WPLParser::VariableExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::FieldAccessExprContext * ctx); 
    std::any visitFieldAccessExpr(WPLParser::FieldAccessExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::ParenExprContext * ctx); 
    std::any visitParenExpr(WPLParser::ParenExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::BinaryRelExprContext * ctx); 
    std::any visitBinaryRelExpr(WPLParser::BinaryRelExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::BConstExprContext * ctx); 
    std::any visitBConstExpr(WPLParser::BConstExprContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::BlockContext * ctx); 
    std::any visitBlock(WPLParser::BlockContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::ConditionContext * ctx); 
    std::any visitCondition(WPLParser::ConditionContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::SelectAlternativeContext * ctx); 
    std::any visitSelectAlternative(WPLParser::SelectAlternativeContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::ParameterListContext * ctx); 
    std::any visitParameterList(WPLParser::ParameterListContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::ParameterContext * ctx); 
    std::any visitParameter(WPLParser::ParameterContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::AssignmentContext * ctx); 
    std::any visitAssignment(WPLParser::AssignmentContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::ExternStatementContext * ctx); 
    std::any visitExternStatement(WPLParser::ExternStatementContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::FuncDefContext * ctx); 
    std::any visitFuncDef(WPLParser::FuncDefContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::AssignStatementContext * ctx); 
    std::any visitAssignStatement(WPLParser::AssignStatementContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::VarDeclStatementContext * ctx); 
    std::any visitVarDeclStatement(WPLParser::VarDeclStatementContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::ProgramLoopContext * ctx); 
    std::any visitProgramLoop(WPLParser::ProgramLoopContext *ctx) override { return visitCtx(ctx); }


    T visitCtx(WPLParser::ConditionalStatementContext * ctx); 
    std::any visitConditionalStatement(WPLParser::ConditionalStatementContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::SelectStatementContext * ctx); 
    std::any visitSelectStatement(WPLParser::SelectStatementContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::CallStatementContext * ctx); 
    std::any visitCallStatement(WPLParser::CallStatementContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::ReturnStatementContext * ctx); 
    std::any visitReturnStatement(WPLParser::ReturnStatementContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::BlockStatementContext * ctx); 
    std::any visitBlockStatement(WPLParser::BlockStatementContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::TypeOrVarContext * ctx); 
    std::any visitTypeOrVar(WPLParser::TypeOrVarContext *ctx) override { return visitCtx(ctx); }

    // T visitCtx(WPLParser::TypeContext * ctx); 
    // std::any visitType(WPLParser::TypeContext *ctx) override { return visitCtx(ctx); }

    T visitCtx(WPLParser::BooleanConstContext * ctx); 
    std::any visitBooleanConst(WPLParser::BooleanConstContext *ctx) override { return visitCtx(ctx); }
};


/*
class TypeVisitor : public TypedVisitor<const Type*> 
{
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
    const Type *visitCtx(WPLParser::VariableExprContext *ctx);
    const Type *visitCtx(WPLParser::FieldAccessExprContext *ctx);
    const Type *visitCtx(WPLParser::ParenExprContext *ctx);
    const Type *visitCtx(WPLParser::BinaryRelExprContext *ctx);
    const Type *visitCtx(WPLParser::BConstExprContext *ctx);
    const Type *visitCtx(WPLParser::BlockContext *ctx);
    const Type *visitCtx(WPLParser::ConditionContext *ctx);
    const Type *visitCtx(WPLParser::SelectAlternativeContext *ctx);
    const Type *visitCtx(WPLParser::ParameterListContext *ctx);
    const Type *visitCtx(WPLParser::ParameterContext *ctx);
    const Type * visitCtx(WPLParser::AssignmentContext *ctx) ;
    const Type *visitCtx(WPLParser::ExternStatementContext *ctx);
    const Type *visitCtx(WPLParser::FuncDefContext *ctx);
    const Type *visitCtx(WPLParser::AssignStatementContext *ctx);
    const Type *visitCtx(WPLParser::VarDeclStatementContext *ctx);
    const Type *visitCtx(WPLParser::LoopStatementContext *ctx);
    const Type *visitCtx(WPLParser::ConditionalStatementContext *ctx);
    const Type *visitCtx(WPLParser::SelectStatementContext *ctx);
    const Type *visitCtx(WPLParser::CallStatementContext *ctx);
    const Type *visitCtx(WPLParser::ReturnStatementContext *ctx);
    const Type *visitCtx(WPLParser::BlockStatementContext *ctx);
    const Type *visitCtx(WPLParser::TypeOrVarContext *ctx);
    const Type *visitCtx(WPLParser::TypeContext *ctx);
    const Type *visitCtx(WPLParser::BooleanConstContext *ctx);
};
*/
// class DerivedVisitor : WPLBaseVisitor
// {
// public: 
//     int visitCtx(WPLParser::CompilationUnitContext * ctx) {

//     }
// };