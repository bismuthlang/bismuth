
// Generated from Bismuth.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "BismuthVisitor.h"


/**
 * This class provides an empty implementation of BismuthVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  BismuthBaseVisitor : public BismuthVisitor {
public:

  virtual std::any visitCompilationUnit(BismuthParser::CompilationUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructCase(BismuthParser::StructCaseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGenericTemplate(BismuthParser::GenericTemplateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGenericType(BismuthParser::GenericTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGenericSession(BismuthParser::GenericSessionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGenericSpecifier(BismuthParser::GenericSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefineEnum(BismuthParser::DefineEnumContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefineStruct(BismuthParser::DefineStructContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefineProgram(BismuthParser::DefineProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefineFunction(BismuthParser::DefineFunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExternStatement(BismuthParser::ExternStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPathElement(BismuthParser::PathElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPath(BismuthParser::PathContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportStatement(BismuthParser::ImportStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInv_args(BismuthParser::Inv_argsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignableIsPresent(BismuthParser::AssignableIsPresentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCopyExpr(BismuthParser::CopyExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIConstExpr(BismuthParser::IConstExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayAccess(BismuthParser::ArrayAccessContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinaryArithExpr(BismuthParser::BinaryArithExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifierExpr(BismuthParser::IdentifierExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallExpr(BismuthParser::CallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFieldAccessExpr(BismuthParser::FieldAccessExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinaryRelExpr(BismuthParser::BinaryRelExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignableRecv(BismuthParser::AssignableRecvContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitBox(BismuthParser::InitBoxContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLambdaExpr(BismuthParser::LambdaExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAsChannelExpr(BismuthParser::AsChannelExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSConstExpr(BismuthParser::SConstExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpr(BismuthParser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignableExec(BismuthParser::AssignableExecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqExpr(BismuthParser::EqExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogAndExpr(BismuthParser::LogAndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogOrExpr(BismuthParser::LogOrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayExpression(BismuthParser::ArrayExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitProduct(BismuthParser::InitProductContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenExpr(BismuthParser::ParenExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPathExpr(BismuthParser::PathExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeref(BismuthParser::DerefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBConstExpr(BismuthParser::BConstExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLambdaConstExpr(BismuthParser::LambdaConstExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(BismuthParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondition(BismuthParser::ConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectAlternative(BismuthParser::SelectAlternativeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMatchAlternative(BismuthParser::MatchAlternativeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProtoAlternative(BismuthParser::ProtoAlternativeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProtoElse(BismuthParser::ProtoElseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterList(BismuthParser::ParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameter(BismuthParser::ParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment(BismuthParser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeDef(BismuthParser::TypeDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDeclStatement(BismuthParser::VarDeclStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignStatement(BismuthParser::AssignStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionalStatement(BismuthParser::ConditionalStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectStatement(BismuthParser::SelectStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMatchStatement(BismuthParser::MatchStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStatement(BismuthParser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExitStatement(BismuthParser::ExitStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSkipStatement(BismuthParser::SkipStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockStatement(BismuthParser::BlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgramSend(BismuthParser::ProgramSendContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgramLoop(BismuthParser::ProgramLoopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForStatement(BismuthParser::ForStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgramCase(BismuthParser::ProgramCaseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgramProject(BismuthParser::ProgramProjectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgramContract(BismuthParser::ProgramContractContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgramWeaken(BismuthParser::ProgramWeakenContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgramAccept(BismuthParser::ProgramAcceptContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgramAcceptWhile(BismuthParser::ProgramAcceptWhileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgramAcceptIf(BismuthParser::ProgramAcceptIfContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgramClose(BismuthParser::ProgramCloseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgramCancel(BismuthParser::ProgramCancelContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStatement(BismuthParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentStatement(BismuthParser::AssignmentStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclaration(BismuthParser::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShiftOp(BismuthParser::ShiftOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeOrVar(BismuthParser::TypeOrVarContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProtocol(BismuthParser::ProtocolContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRecvType(BismuthParser::RecvTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSendType(BismuthParser::SendTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWnProto(BismuthParser::WnProtoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOcProto(BismuthParser::OcProtoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExtChoiceProto(BismuthParser::ExtChoiceProtoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntChoiceProto(BismuthParser::IntChoiceProtoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCloseableProto(BismuthParser::CloseableProtoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProtoBranch(BismuthParser::ProtoBranchContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLambdaType(BismuthParser::LambdaTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCustomType(BismuthParser::CustomTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayType(BismuthParser::ArrayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDynArrayType(BismuthParser::DynArrayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSumType(BismuthParser::SumTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBaseType(BismuthParser::BaseTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplatedType(BismuthParser::TemplatedTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgramType(BismuthParser::ProgramTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChannelType(BismuthParser::ChannelTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoxType(BismuthParser::BoxTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntegerValue(BismuthParser::IntegerValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBooleanConst(BismuthParser::BooleanConstContext *ctx) override {
    return visitChildren(ctx);
  }


};

