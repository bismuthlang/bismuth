
// Generated from Bismuth.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "BismuthParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by BismuthParser.
 */
class  BismuthListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterCompilationUnit(BismuthParser::CompilationUnitContext *ctx) = 0;
  virtual void exitCompilationUnit(BismuthParser::CompilationUnitContext *ctx) = 0;

  virtual void enterStructCase(BismuthParser::StructCaseContext *ctx) = 0;
  virtual void exitStructCase(BismuthParser::StructCaseContext *ctx) = 0;

  virtual void enterGenericTemplate(BismuthParser::GenericTemplateContext *ctx) = 0;
  virtual void exitGenericTemplate(BismuthParser::GenericTemplateContext *ctx) = 0;

  virtual void enterGenericType(BismuthParser::GenericTypeContext *ctx) = 0;
  virtual void exitGenericType(BismuthParser::GenericTypeContext *ctx) = 0;

  virtual void enterGenericSession(BismuthParser::GenericSessionContext *ctx) = 0;
  virtual void exitGenericSession(BismuthParser::GenericSessionContext *ctx) = 0;

  virtual void enterGenericSpecifier(BismuthParser::GenericSpecifierContext *ctx) = 0;
  virtual void exitGenericSpecifier(BismuthParser::GenericSpecifierContext *ctx) = 0;

  virtual void enterDefineEnum(BismuthParser::DefineEnumContext *ctx) = 0;
  virtual void exitDefineEnum(BismuthParser::DefineEnumContext *ctx) = 0;

  virtual void enterDefineStruct(BismuthParser::DefineStructContext *ctx) = 0;
  virtual void exitDefineStruct(BismuthParser::DefineStructContext *ctx) = 0;

  virtual void enterDefineProgram(BismuthParser::DefineProgramContext *ctx) = 0;
  virtual void exitDefineProgram(BismuthParser::DefineProgramContext *ctx) = 0;

  virtual void enterDefineFunction(BismuthParser::DefineFunctionContext *ctx) = 0;
  virtual void exitDefineFunction(BismuthParser::DefineFunctionContext *ctx) = 0;

  virtual void enterExternStatement(BismuthParser::ExternStatementContext *ctx) = 0;
  virtual void exitExternStatement(BismuthParser::ExternStatementContext *ctx) = 0;

  virtual void enterPathElement(BismuthParser::PathElementContext *ctx) = 0;
  virtual void exitPathElement(BismuthParser::PathElementContext *ctx) = 0;

  virtual void enterPath(BismuthParser::PathContext *ctx) = 0;
  virtual void exitPath(BismuthParser::PathContext *ctx) = 0;

  virtual void enterImportStatement(BismuthParser::ImportStatementContext *ctx) = 0;
  virtual void exitImportStatement(BismuthParser::ImportStatementContext *ctx) = 0;

  virtual void enterInv_args(BismuthParser::Inv_argsContext *ctx) = 0;
  virtual void exitInv_args(BismuthParser::Inv_argsContext *ctx) = 0;

  virtual void enterAssignableIsPresent(BismuthParser::AssignableIsPresentContext *ctx) = 0;
  virtual void exitAssignableIsPresent(BismuthParser::AssignableIsPresentContext *ctx) = 0;

  virtual void enterCopyExpr(BismuthParser::CopyExprContext *ctx) = 0;
  virtual void exitCopyExpr(BismuthParser::CopyExprContext *ctx) = 0;

  virtual void enterIConstExpr(BismuthParser::IConstExprContext *ctx) = 0;
  virtual void exitIConstExpr(BismuthParser::IConstExprContext *ctx) = 0;

  virtual void enterArrayAccess(BismuthParser::ArrayAccessContext *ctx) = 0;
  virtual void exitArrayAccess(BismuthParser::ArrayAccessContext *ctx) = 0;

  virtual void enterBinaryArithExpr(BismuthParser::BinaryArithExprContext *ctx) = 0;
  virtual void exitBinaryArithExpr(BismuthParser::BinaryArithExprContext *ctx) = 0;

  virtual void enterIdentifierExpr(BismuthParser::IdentifierExprContext *ctx) = 0;
  virtual void exitIdentifierExpr(BismuthParser::IdentifierExprContext *ctx) = 0;

  virtual void enterCallExpr(BismuthParser::CallExprContext *ctx) = 0;
  virtual void exitCallExpr(BismuthParser::CallExprContext *ctx) = 0;

  virtual void enterFieldAccessExpr(BismuthParser::FieldAccessExprContext *ctx) = 0;
  virtual void exitFieldAccessExpr(BismuthParser::FieldAccessExprContext *ctx) = 0;

  virtual void enterBinaryRelExpr(BismuthParser::BinaryRelExprContext *ctx) = 0;
  virtual void exitBinaryRelExpr(BismuthParser::BinaryRelExprContext *ctx) = 0;

  virtual void enterAssignableRecv(BismuthParser::AssignableRecvContext *ctx) = 0;
  virtual void exitAssignableRecv(BismuthParser::AssignableRecvContext *ctx) = 0;

  virtual void enterInitBox(BismuthParser::InitBoxContext *ctx) = 0;
  virtual void exitInitBox(BismuthParser::InitBoxContext *ctx) = 0;

  virtual void enterLambdaExpr(BismuthParser::LambdaExprContext *ctx) = 0;
  virtual void exitLambdaExpr(BismuthParser::LambdaExprContext *ctx) = 0;

  virtual void enterAsChannelExpr(BismuthParser::AsChannelExprContext *ctx) = 0;
  virtual void exitAsChannelExpr(BismuthParser::AsChannelExprContext *ctx) = 0;

  virtual void enterSConstExpr(BismuthParser::SConstExprContext *ctx) = 0;
  virtual void exitSConstExpr(BismuthParser::SConstExprContext *ctx) = 0;

  virtual void enterUnaryExpr(BismuthParser::UnaryExprContext *ctx) = 0;
  virtual void exitUnaryExpr(BismuthParser::UnaryExprContext *ctx) = 0;

  virtual void enterAssignableExec(BismuthParser::AssignableExecContext *ctx) = 0;
  virtual void exitAssignableExec(BismuthParser::AssignableExecContext *ctx) = 0;

  virtual void enterEqExpr(BismuthParser::EqExprContext *ctx) = 0;
  virtual void exitEqExpr(BismuthParser::EqExprContext *ctx) = 0;

  virtual void enterLogAndExpr(BismuthParser::LogAndExprContext *ctx) = 0;
  virtual void exitLogAndExpr(BismuthParser::LogAndExprContext *ctx) = 0;

  virtual void enterLogOrExpr(BismuthParser::LogOrExprContext *ctx) = 0;
  virtual void exitLogOrExpr(BismuthParser::LogOrExprContext *ctx) = 0;

  virtual void enterArrayExpression(BismuthParser::ArrayExpressionContext *ctx) = 0;
  virtual void exitArrayExpression(BismuthParser::ArrayExpressionContext *ctx) = 0;

  virtual void enterInitProduct(BismuthParser::InitProductContext *ctx) = 0;
  virtual void exitInitProduct(BismuthParser::InitProductContext *ctx) = 0;

  virtual void enterParenExpr(BismuthParser::ParenExprContext *ctx) = 0;
  virtual void exitParenExpr(BismuthParser::ParenExprContext *ctx) = 0;

  virtual void enterPathExpr(BismuthParser::PathExprContext *ctx) = 0;
  virtual void exitPathExpr(BismuthParser::PathExprContext *ctx) = 0;

  virtual void enterDeref(BismuthParser::DerefContext *ctx) = 0;
  virtual void exitDeref(BismuthParser::DerefContext *ctx) = 0;

  virtual void enterBConstExpr(BismuthParser::BConstExprContext *ctx) = 0;
  virtual void exitBConstExpr(BismuthParser::BConstExprContext *ctx) = 0;

  virtual void enterLambdaConstExpr(BismuthParser::LambdaConstExprContext *ctx) = 0;
  virtual void exitLambdaConstExpr(BismuthParser::LambdaConstExprContext *ctx) = 0;

  virtual void enterBlock(BismuthParser::BlockContext *ctx) = 0;
  virtual void exitBlock(BismuthParser::BlockContext *ctx) = 0;

  virtual void enterCondition(BismuthParser::ConditionContext *ctx) = 0;
  virtual void exitCondition(BismuthParser::ConditionContext *ctx) = 0;

  virtual void enterSelectAlternative(BismuthParser::SelectAlternativeContext *ctx) = 0;
  virtual void exitSelectAlternative(BismuthParser::SelectAlternativeContext *ctx) = 0;

  virtual void enterMatchAlternative(BismuthParser::MatchAlternativeContext *ctx) = 0;
  virtual void exitMatchAlternative(BismuthParser::MatchAlternativeContext *ctx) = 0;

  virtual void enterProtoAlternative(BismuthParser::ProtoAlternativeContext *ctx) = 0;
  virtual void exitProtoAlternative(BismuthParser::ProtoAlternativeContext *ctx) = 0;

  virtual void enterProtoElse(BismuthParser::ProtoElseContext *ctx) = 0;
  virtual void exitProtoElse(BismuthParser::ProtoElseContext *ctx) = 0;

  virtual void enterParameterList(BismuthParser::ParameterListContext *ctx) = 0;
  virtual void exitParameterList(BismuthParser::ParameterListContext *ctx) = 0;

  virtual void enterParameter(BismuthParser::ParameterContext *ctx) = 0;
  virtual void exitParameter(BismuthParser::ParameterContext *ctx) = 0;

  virtual void enterAssignment(BismuthParser::AssignmentContext *ctx) = 0;
  virtual void exitAssignment(BismuthParser::AssignmentContext *ctx) = 0;

  virtual void enterTypeDef(BismuthParser::TypeDefContext *ctx) = 0;
  virtual void exitTypeDef(BismuthParser::TypeDefContext *ctx) = 0;

  virtual void enterVarDeclStatement(BismuthParser::VarDeclStatementContext *ctx) = 0;
  virtual void exitVarDeclStatement(BismuthParser::VarDeclStatementContext *ctx) = 0;

  virtual void enterAssignStatement(BismuthParser::AssignStatementContext *ctx) = 0;
  virtual void exitAssignStatement(BismuthParser::AssignStatementContext *ctx) = 0;

  virtual void enterConditionalStatement(BismuthParser::ConditionalStatementContext *ctx) = 0;
  virtual void exitConditionalStatement(BismuthParser::ConditionalStatementContext *ctx) = 0;

  virtual void enterSelectStatement(BismuthParser::SelectStatementContext *ctx) = 0;
  virtual void exitSelectStatement(BismuthParser::SelectStatementContext *ctx) = 0;

  virtual void enterMatchStatement(BismuthParser::MatchStatementContext *ctx) = 0;
  virtual void exitMatchStatement(BismuthParser::MatchStatementContext *ctx) = 0;

  virtual void enterReturnStatement(BismuthParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(BismuthParser::ReturnStatementContext *ctx) = 0;

  virtual void enterExitStatement(BismuthParser::ExitStatementContext *ctx) = 0;
  virtual void exitExitStatement(BismuthParser::ExitStatementContext *ctx) = 0;

  virtual void enterSkipStatement(BismuthParser::SkipStatementContext *ctx) = 0;
  virtual void exitSkipStatement(BismuthParser::SkipStatementContext *ctx) = 0;

  virtual void enterBlockStatement(BismuthParser::BlockStatementContext *ctx) = 0;
  virtual void exitBlockStatement(BismuthParser::BlockStatementContext *ctx) = 0;

  virtual void enterProgramSend(BismuthParser::ProgramSendContext *ctx) = 0;
  virtual void exitProgramSend(BismuthParser::ProgramSendContext *ctx) = 0;

  virtual void enterProgramLoop(BismuthParser::ProgramLoopContext *ctx) = 0;
  virtual void exitProgramLoop(BismuthParser::ProgramLoopContext *ctx) = 0;

  virtual void enterForStatement(BismuthParser::ForStatementContext *ctx) = 0;
  virtual void exitForStatement(BismuthParser::ForStatementContext *ctx) = 0;

  virtual void enterProgramCase(BismuthParser::ProgramCaseContext *ctx) = 0;
  virtual void exitProgramCase(BismuthParser::ProgramCaseContext *ctx) = 0;

  virtual void enterProgramProject(BismuthParser::ProgramProjectContext *ctx) = 0;
  virtual void exitProgramProject(BismuthParser::ProgramProjectContext *ctx) = 0;

  virtual void enterProgramContract(BismuthParser::ProgramContractContext *ctx) = 0;
  virtual void exitProgramContract(BismuthParser::ProgramContractContext *ctx) = 0;

  virtual void enterProgramWeaken(BismuthParser::ProgramWeakenContext *ctx) = 0;
  virtual void exitProgramWeaken(BismuthParser::ProgramWeakenContext *ctx) = 0;

  virtual void enterProgramAccept(BismuthParser::ProgramAcceptContext *ctx) = 0;
  virtual void exitProgramAccept(BismuthParser::ProgramAcceptContext *ctx) = 0;

  virtual void enterProgramAcceptWhile(BismuthParser::ProgramAcceptWhileContext *ctx) = 0;
  virtual void exitProgramAcceptWhile(BismuthParser::ProgramAcceptWhileContext *ctx) = 0;

  virtual void enterProgramAcceptIf(BismuthParser::ProgramAcceptIfContext *ctx) = 0;
  virtual void exitProgramAcceptIf(BismuthParser::ProgramAcceptIfContext *ctx) = 0;

  virtual void enterProgramClose(BismuthParser::ProgramCloseContext *ctx) = 0;
  virtual void exitProgramClose(BismuthParser::ProgramCloseContext *ctx) = 0;

  virtual void enterProgramCancel(BismuthParser::ProgramCancelContext *ctx) = 0;
  virtual void exitProgramCancel(BismuthParser::ProgramCancelContext *ctx) = 0;

  virtual void enterExpressionStatement(BismuthParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(BismuthParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterAssignmentStatement(BismuthParser::AssignmentStatementContext *ctx) = 0;
  virtual void exitAssignmentStatement(BismuthParser::AssignmentStatementContext *ctx) = 0;

  virtual void enterVariableDeclaration(BismuthParser::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(BismuthParser::VariableDeclarationContext *ctx) = 0;

  virtual void enterShiftOp(BismuthParser::ShiftOpContext *ctx) = 0;
  virtual void exitShiftOp(BismuthParser::ShiftOpContext *ctx) = 0;

  virtual void enterTypeOrVar(BismuthParser::TypeOrVarContext *ctx) = 0;
  virtual void exitTypeOrVar(BismuthParser::TypeOrVarContext *ctx) = 0;

  virtual void enterProtocol(BismuthParser::ProtocolContext *ctx) = 0;
  virtual void exitProtocol(BismuthParser::ProtocolContext *ctx) = 0;

  virtual void enterRecvType(BismuthParser::RecvTypeContext *ctx) = 0;
  virtual void exitRecvType(BismuthParser::RecvTypeContext *ctx) = 0;

  virtual void enterSendType(BismuthParser::SendTypeContext *ctx) = 0;
  virtual void exitSendType(BismuthParser::SendTypeContext *ctx) = 0;

  virtual void enterWnProto(BismuthParser::WnProtoContext *ctx) = 0;
  virtual void exitWnProto(BismuthParser::WnProtoContext *ctx) = 0;

  virtual void enterOcProto(BismuthParser::OcProtoContext *ctx) = 0;
  virtual void exitOcProto(BismuthParser::OcProtoContext *ctx) = 0;

  virtual void enterExtChoiceProto(BismuthParser::ExtChoiceProtoContext *ctx) = 0;
  virtual void exitExtChoiceProto(BismuthParser::ExtChoiceProtoContext *ctx) = 0;

  virtual void enterIntChoiceProto(BismuthParser::IntChoiceProtoContext *ctx) = 0;
  virtual void exitIntChoiceProto(BismuthParser::IntChoiceProtoContext *ctx) = 0;

  virtual void enterCloseableProto(BismuthParser::CloseableProtoContext *ctx) = 0;
  virtual void exitCloseableProto(BismuthParser::CloseableProtoContext *ctx) = 0;

  virtual void enterProtoBranch(BismuthParser::ProtoBranchContext *ctx) = 0;
  virtual void exitProtoBranch(BismuthParser::ProtoBranchContext *ctx) = 0;

  virtual void enterLambdaType(BismuthParser::LambdaTypeContext *ctx) = 0;
  virtual void exitLambdaType(BismuthParser::LambdaTypeContext *ctx) = 0;

  virtual void enterCustomType(BismuthParser::CustomTypeContext *ctx) = 0;
  virtual void exitCustomType(BismuthParser::CustomTypeContext *ctx) = 0;

  virtual void enterArrayType(BismuthParser::ArrayTypeContext *ctx) = 0;
  virtual void exitArrayType(BismuthParser::ArrayTypeContext *ctx) = 0;

  virtual void enterDynArrayType(BismuthParser::DynArrayTypeContext *ctx) = 0;
  virtual void exitDynArrayType(BismuthParser::DynArrayTypeContext *ctx) = 0;

  virtual void enterSumType(BismuthParser::SumTypeContext *ctx) = 0;
  virtual void exitSumType(BismuthParser::SumTypeContext *ctx) = 0;

  virtual void enterBaseType(BismuthParser::BaseTypeContext *ctx) = 0;
  virtual void exitBaseType(BismuthParser::BaseTypeContext *ctx) = 0;

  virtual void enterTemplatedType(BismuthParser::TemplatedTypeContext *ctx) = 0;
  virtual void exitTemplatedType(BismuthParser::TemplatedTypeContext *ctx) = 0;

  virtual void enterProgramType(BismuthParser::ProgramTypeContext *ctx) = 0;
  virtual void exitProgramType(BismuthParser::ProgramTypeContext *ctx) = 0;

  virtual void enterChannelType(BismuthParser::ChannelTypeContext *ctx) = 0;
  virtual void exitChannelType(BismuthParser::ChannelTypeContext *ctx) = 0;

  virtual void enterBoxType(BismuthParser::BoxTypeContext *ctx) = 0;
  virtual void exitBoxType(BismuthParser::BoxTypeContext *ctx) = 0;

  virtual void enterIntegerValue(BismuthParser::IntegerValueContext *ctx) = 0;
  virtual void exitIntegerValue(BismuthParser::IntegerValueContext *ctx) = 0;

  virtual void enterBooleanConst(BismuthParser::BooleanConstContext *ctx) = 0;
  virtual void exitBooleanConst(BismuthParser::BooleanConstContext *ctx) = 0;


};

