
// Generated from Bismuth.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "BismuthListener.h"


/**
 * This class provides an empty implementation of BismuthListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  BismuthBaseListener : public BismuthListener {
public:

  virtual void enterCompilationUnit(BismuthParser::CompilationUnitContext * /*ctx*/) override { }
  virtual void exitCompilationUnit(BismuthParser::CompilationUnitContext * /*ctx*/) override { }

  virtual void enterStructCase(BismuthParser::StructCaseContext * /*ctx*/) override { }
  virtual void exitStructCase(BismuthParser::StructCaseContext * /*ctx*/) override { }

  virtual void enterGenericTemplate(BismuthParser::GenericTemplateContext * /*ctx*/) override { }
  virtual void exitGenericTemplate(BismuthParser::GenericTemplateContext * /*ctx*/) override { }

  virtual void enterGenericType(BismuthParser::GenericTypeContext * /*ctx*/) override { }
  virtual void exitGenericType(BismuthParser::GenericTypeContext * /*ctx*/) override { }

  virtual void enterGenericSession(BismuthParser::GenericSessionContext * /*ctx*/) override { }
  virtual void exitGenericSession(BismuthParser::GenericSessionContext * /*ctx*/) override { }

  virtual void enterGenericSpecifier(BismuthParser::GenericSpecifierContext * /*ctx*/) override { }
  virtual void exitGenericSpecifier(BismuthParser::GenericSpecifierContext * /*ctx*/) override { }

  virtual void enterDefineEnum(BismuthParser::DefineEnumContext * /*ctx*/) override { }
  virtual void exitDefineEnum(BismuthParser::DefineEnumContext * /*ctx*/) override { }

  virtual void enterDefineStruct(BismuthParser::DefineStructContext * /*ctx*/) override { }
  virtual void exitDefineStruct(BismuthParser::DefineStructContext * /*ctx*/) override { }

  virtual void enterDefineProgram(BismuthParser::DefineProgramContext * /*ctx*/) override { }
  virtual void exitDefineProgram(BismuthParser::DefineProgramContext * /*ctx*/) override { }

  virtual void enterDefineFunction(BismuthParser::DefineFunctionContext * /*ctx*/) override { }
  virtual void exitDefineFunction(BismuthParser::DefineFunctionContext * /*ctx*/) override { }

  virtual void enterExternStatement(BismuthParser::ExternStatementContext * /*ctx*/) override { }
  virtual void exitExternStatement(BismuthParser::ExternStatementContext * /*ctx*/) override { }

  virtual void enterPathElement(BismuthParser::PathElementContext * /*ctx*/) override { }
  virtual void exitPathElement(BismuthParser::PathElementContext * /*ctx*/) override { }

  virtual void enterPath(BismuthParser::PathContext * /*ctx*/) override { }
  virtual void exitPath(BismuthParser::PathContext * /*ctx*/) override { }

  virtual void enterImportStatement(BismuthParser::ImportStatementContext * /*ctx*/) override { }
  virtual void exitImportStatement(BismuthParser::ImportStatementContext * /*ctx*/) override { }

  virtual void enterInv_args(BismuthParser::Inv_argsContext * /*ctx*/) override { }
  virtual void exitInv_args(BismuthParser::Inv_argsContext * /*ctx*/) override { }

  virtual void enterAssignableIsPresent(BismuthParser::AssignableIsPresentContext * /*ctx*/) override { }
  virtual void exitAssignableIsPresent(BismuthParser::AssignableIsPresentContext * /*ctx*/) override { }

  virtual void enterCopyExpr(BismuthParser::CopyExprContext * /*ctx*/) override { }
  virtual void exitCopyExpr(BismuthParser::CopyExprContext * /*ctx*/) override { }

  virtual void enterIConstExpr(BismuthParser::IConstExprContext * /*ctx*/) override { }
  virtual void exitIConstExpr(BismuthParser::IConstExprContext * /*ctx*/) override { }

  virtual void enterArrayAccess(BismuthParser::ArrayAccessContext * /*ctx*/) override { }
  virtual void exitArrayAccess(BismuthParser::ArrayAccessContext * /*ctx*/) override { }

  virtual void enterBinaryArithExpr(BismuthParser::BinaryArithExprContext * /*ctx*/) override { }
  virtual void exitBinaryArithExpr(BismuthParser::BinaryArithExprContext * /*ctx*/) override { }

  virtual void enterIdentifierExpr(BismuthParser::IdentifierExprContext * /*ctx*/) override { }
  virtual void exitIdentifierExpr(BismuthParser::IdentifierExprContext * /*ctx*/) override { }

  virtual void enterCallExpr(BismuthParser::CallExprContext * /*ctx*/) override { }
  virtual void exitCallExpr(BismuthParser::CallExprContext * /*ctx*/) override { }

  virtual void enterFieldAccessExpr(BismuthParser::FieldAccessExprContext * /*ctx*/) override { }
  virtual void exitFieldAccessExpr(BismuthParser::FieldAccessExprContext * /*ctx*/) override { }

  virtual void enterBinaryRelExpr(BismuthParser::BinaryRelExprContext * /*ctx*/) override { }
  virtual void exitBinaryRelExpr(BismuthParser::BinaryRelExprContext * /*ctx*/) override { }

  virtual void enterAssignableRecv(BismuthParser::AssignableRecvContext * /*ctx*/) override { }
  virtual void exitAssignableRecv(BismuthParser::AssignableRecvContext * /*ctx*/) override { }

  virtual void enterInitBox(BismuthParser::InitBoxContext * /*ctx*/) override { }
  virtual void exitInitBox(BismuthParser::InitBoxContext * /*ctx*/) override { }

  virtual void enterLambdaExpr(BismuthParser::LambdaExprContext * /*ctx*/) override { }
  virtual void exitLambdaExpr(BismuthParser::LambdaExprContext * /*ctx*/) override { }

  virtual void enterAsChannelExpr(BismuthParser::AsChannelExprContext * /*ctx*/) override { }
  virtual void exitAsChannelExpr(BismuthParser::AsChannelExprContext * /*ctx*/) override { }

  virtual void enterSConstExpr(BismuthParser::SConstExprContext * /*ctx*/) override { }
  virtual void exitSConstExpr(BismuthParser::SConstExprContext * /*ctx*/) override { }

  virtual void enterUnaryExpr(BismuthParser::UnaryExprContext * /*ctx*/) override { }
  virtual void exitUnaryExpr(BismuthParser::UnaryExprContext * /*ctx*/) override { }

  virtual void enterAssignableExec(BismuthParser::AssignableExecContext * /*ctx*/) override { }
  virtual void exitAssignableExec(BismuthParser::AssignableExecContext * /*ctx*/) override { }

  virtual void enterEqExpr(BismuthParser::EqExprContext * /*ctx*/) override { }
  virtual void exitEqExpr(BismuthParser::EqExprContext * /*ctx*/) override { }

  virtual void enterLogAndExpr(BismuthParser::LogAndExprContext * /*ctx*/) override { }
  virtual void exitLogAndExpr(BismuthParser::LogAndExprContext * /*ctx*/) override { }

  virtual void enterLogOrExpr(BismuthParser::LogOrExprContext * /*ctx*/) override { }
  virtual void exitLogOrExpr(BismuthParser::LogOrExprContext * /*ctx*/) override { }

  virtual void enterArrayExpression(BismuthParser::ArrayExpressionContext * /*ctx*/) override { }
  virtual void exitArrayExpression(BismuthParser::ArrayExpressionContext * /*ctx*/) override { }

  virtual void enterInitProduct(BismuthParser::InitProductContext * /*ctx*/) override { }
  virtual void exitInitProduct(BismuthParser::InitProductContext * /*ctx*/) override { }

  virtual void enterParenExpr(BismuthParser::ParenExprContext * /*ctx*/) override { }
  virtual void exitParenExpr(BismuthParser::ParenExprContext * /*ctx*/) override { }

  virtual void enterPathExpr(BismuthParser::PathExprContext * /*ctx*/) override { }
  virtual void exitPathExpr(BismuthParser::PathExprContext * /*ctx*/) override { }

  virtual void enterDeref(BismuthParser::DerefContext * /*ctx*/) override { }
  virtual void exitDeref(BismuthParser::DerefContext * /*ctx*/) override { }

  virtual void enterBConstExpr(BismuthParser::BConstExprContext * /*ctx*/) override { }
  virtual void exitBConstExpr(BismuthParser::BConstExprContext * /*ctx*/) override { }

  virtual void enterLambdaConstExpr(BismuthParser::LambdaConstExprContext * /*ctx*/) override { }
  virtual void exitLambdaConstExpr(BismuthParser::LambdaConstExprContext * /*ctx*/) override { }

  virtual void enterBlock(BismuthParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(BismuthParser::BlockContext * /*ctx*/) override { }

  virtual void enterCondition(BismuthParser::ConditionContext * /*ctx*/) override { }
  virtual void exitCondition(BismuthParser::ConditionContext * /*ctx*/) override { }

  virtual void enterSelectAlternative(BismuthParser::SelectAlternativeContext * /*ctx*/) override { }
  virtual void exitSelectAlternative(BismuthParser::SelectAlternativeContext * /*ctx*/) override { }

  virtual void enterMatchAlternative(BismuthParser::MatchAlternativeContext * /*ctx*/) override { }
  virtual void exitMatchAlternative(BismuthParser::MatchAlternativeContext * /*ctx*/) override { }

  virtual void enterProtoAlternative(BismuthParser::ProtoAlternativeContext * /*ctx*/) override { }
  virtual void exitProtoAlternative(BismuthParser::ProtoAlternativeContext * /*ctx*/) override { }

  virtual void enterProtoElse(BismuthParser::ProtoElseContext * /*ctx*/) override { }
  virtual void exitProtoElse(BismuthParser::ProtoElseContext * /*ctx*/) override { }

  virtual void enterParameterList(BismuthParser::ParameterListContext * /*ctx*/) override { }
  virtual void exitParameterList(BismuthParser::ParameterListContext * /*ctx*/) override { }

  virtual void enterParameter(BismuthParser::ParameterContext * /*ctx*/) override { }
  virtual void exitParameter(BismuthParser::ParameterContext * /*ctx*/) override { }

  virtual void enterAssignment(BismuthParser::AssignmentContext * /*ctx*/) override { }
  virtual void exitAssignment(BismuthParser::AssignmentContext * /*ctx*/) override { }

  virtual void enterTypeDef(BismuthParser::TypeDefContext * /*ctx*/) override { }
  virtual void exitTypeDef(BismuthParser::TypeDefContext * /*ctx*/) override { }

  virtual void enterVarDeclStatement(BismuthParser::VarDeclStatementContext * /*ctx*/) override { }
  virtual void exitVarDeclStatement(BismuthParser::VarDeclStatementContext * /*ctx*/) override { }

  virtual void enterAssignStatement(BismuthParser::AssignStatementContext * /*ctx*/) override { }
  virtual void exitAssignStatement(BismuthParser::AssignStatementContext * /*ctx*/) override { }

  virtual void enterConditionalStatement(BismuthParser::ConditionalStatementContext * /*ctx*/) override { }
  virtual void exitConditionalStatement(BismuthParser::ConditionalStatementContext * /*ctx*/) override { }

  virtual void enterSelectStatement(BismuthParser::SelectStatementContext * /*ctx*/) override { }
  virtual void exitSelectStatement(BismuthParser::SelectStatementContext * /*ctx*/) override { }

  virtual void enterMatchStatement(BismuthParser::MatchStatementContext * /*ctx*/) override { }
  virtual void exitMatchStatement(BismuthParser::MatchStatementContext * /*ctx*/) override { }

  virtual void enterReturnStatement(BismuthParser::ReturnStatementContext * /*ctx*/) override { }
  virtual void exitReturnStatement(BismuthParser::ReturnStatementContext * /*ctx*/) override { }

  virtual void enterExitStatement(BismuthParser::ExitStatementContext * /*ctx*/) override { }
  virtual void exitExitStatement(BismuthParser::ExitStatementContext * /*ctx*/) override { }

  virtual void enterSkipStatement(BismuthParser::SkipStatementContext * /*ctx*/) override { }
  virtual void exitSkipStatement(BismuthParser::SkipStatementContext * /*ctx*/) override { }

  virtual void enterBlockStatement(BismuthParser::BlockStatementContext * /*ctx*/) override { }
  virtual void exitBlockStatement(BismuthParser::BlockStatementContext * /*ctx*/) override { }

  virtual void enterProgramSend(BismuthParser::ProgramSendContext * /*ctx*/) override { }
  virtual void exitProgramSend(BismuthParser::ProgramSendContext * /*ctx*/) override { }

  virtual void enterProgramLoop(BismuthParser::ProgramLoopContext * /*ctx*/) override { }
  virtual void exitProgramLoop(BismuthParser::ProgramLoopContext * /*ctx*/) override { }

  virtual void enterForStatement(BismuthParser::ForStatementContext * /*ctx*/) override { }
  virtual void exitForStatement(BismuthParser::ForStatementContext * /*ctx*/) override { }

  virtual void enterProgramCase(BismuthParser::ProgramCaseContext * /*ctx*/) override { }
  virtual void exitProgramCase(BismuthParser::ProgramCaseContext * /*ctx*/) override { }

  virtual void enterProgramProject(BismuthParser::ProgramProjectContext * /*ctx*/) override { }
  virtual void exitProgramProject(BismuthParser::ProgramProjectContext * /*ctx*/) override { }

  virtual void enterProgramContract(BismuthParser::ProgramContractContext * /*ctx*/) override { }
  virtual void exitProgramContract(BismuthParser::ProgramContractContext * /*ctx*/) override { }

  virtual void enterProgramWeaken(BismuthParser::ProgramWeakenContext * /*ctx*/) override { }
  virtual void exitProgramWeaken(BismuthParser::ProgramWeakenContext * /*ctx*/) override { }

  virtual void enterProgramAccept(BismuthParser::ProgramAcceptContext * /*ctx*/) override { }
  virtual void exitProgramAccept(BismuthParser::ProgramAcceptContext * /*ctx*/) override { }

  virtual void enterProgramAcceptWhile(BismuthParser::ProgramAcceptWhileContext * /*ctx*/) override { }
  virtual void exitProgramAcceptWhile(BismuthParser::ProgramAcceptWhileContext * /*ctx*/) override { }

  virtual void enterProgramAcceptIf(BismuthParser::ProgramAcceptIfContext * /*ctx*/) override { }
  virtual void exitProgramAcceptIf(BismuthParser::ProgramAcceptIfContext * /*ctx*/) override { }

  virtual void enterProgramClose(BismuthParser::ProgramCloseContext * /*ctx*/) override { }
  virtual void exitProgramClose(BismuthParser::ProgramCloseContext * /*ctx*/) override { }

  virtual void enterProgramCancel(BismuthParser::ProgramCancelContext * /*ctx*/) override { }
  virtual void exitProgramCancel(BismuthParser::ProgramCancelContext * /*ctx*/) override { }

  virtual void enterExpressionStatement(BismuthParser::ExpressionStatementContext * /*ctx*/) override { }
  virtual void exitExpressionStatement(BismuthParser::ExpressionStatementContext * /*ctx*/) override { }

  virtual void enterAssignmentStatement(BismuthParser::AssignmentStatementContext * /*ctx*/) override { }
  virtual void exitAssignmentStatement(BismuthParser::AssignmentStatementContext * /*ctx*/) override { }

  virtual void enterVariableDeclaration(BismuthParser::VariableDeclarationContext * /*ctx*/) override { }
  virtual void exitVariableDeclaration(BismuthParser::VariableDeclarationContext * /*ctx*/) override { }

  virtual void enterShiftOp(BismuthParser::ShiftOpContext * /*ctx*/) override { }
  virtual void exitShiftOp(BismuthParser::ShiftOpContext * /*ctx*/) override { }

  virtual void enterTypeOrVar(BismuthParser::TypeOrVarContext * /*ctx*/) override { }
  virtual void exitTypeOrVar(BismuthParser::TypeOrVarContext * /*ctx*/) override { }

  virtual void enterProtocol(BismuthParser::ProtocolContext * /*ctx*/) override { }
  virtual void exitProtocol(BismuthParser::ProtocolContext * /*ctx*/) override { }

  virtual void enterRecvType(BismuthParser::RecvTypeContext * /*ctx*/) override { }
  virtual void exitRecvType(BismuthParser::RecvTypeContext * /*ctx*/) override { }

  virtual void enterSendType(BismuthParser::SendTypeContext * /*ctx*/) override { }
  virtual void exitSendType(BismuthParser::SendTypeContext * /*ctx*/) override { }

  virtual void enterWnProto(BismuthParser::WnProtoContext * /*ctx*/) override { }
  virtual void exitWnProto(BismuthParser::WnProtoContext * /*ctx*/) override { }

  virtual void enterOcProto(BismuthParser::OcProtoContext * /*ctx*/) override { }
  virtual void exitOcProto(BismuthParser::OcProtoContext * /*ctx*/) override { }

  virtual void enterExtChoiceProto(BismuthParser::ExtChoiceProtoContext * /*ctx*/) override { }
  virtual void exitExtChoiceProto(BismuthParser::ExtChoiceProtoContext * /*ctx*/) override { }

  virtual void enterIntChoiceProto(BismuthParser::IntChoiceProtoContext * /*ctx*/) override { }
  virtual void exitIntChoiceProto(BismuthParser::IntChoiceProtoContext * /*ctx*/) override { }

  virtual void enterCloseableProto(BismuthParser::CloseableProtoContext * /*ctx*/) override { }
  virtual void exitCloseableProto(BismuthParser::CloseableProtoContext * /*ctx*/) override { }

  virtual void enterProtoBranch(BismuthParser::ProtoBranchContext * /*ctx*/) override { }
  virtual void exitProtoBranch(BismuthParser::ProtoBranchContext * /*ctx*/) override { }

  virtual void enterLambdaType(BismuthParser::LambdaTypeContext * /*ctx*/) override { }
  virtual void exitLambdaType(BismuthParser::LambdaTypeContext * /*ctx*/) override { }

  virtual void enterCustomType(BismuthParser::CustomTypeContext * /*ctx*/) override { }
  virtual void exitCustomType(BismuthParser::CustomTypeContext * /*ctx*/) override { }

  virtual void enterArrayType(BismuthParser::ArrayTypeContext * /*ctx*/) override { }
  virtual void exitArrayType(BismuthParser::ArrayTypeContext * /*ctx*/) override { }

  virtual void enterDynArrayType(BismuthParser::DynArrayTypeContext * /*ctx*/) override { }
  virtual void exitDynArrayType(BismuthParser::DynArrayTypeContext * /*ctx*/) override { }

  virtual void enterSumType(BismuthParser::SumTypeContext * /*ctx*/) override { }
  virtual void exitSumType(BismuthParser::SumTypeContext * /*ctx*/) override { }

  virtual void enterBaseType(BismuthParser::BaseTypeContext * /*ctx*/) override { }
  virtual void exitBaseType(BismuthParser::BaseTypeContext * /*ctx*/) override { }

  virtual void enterTemplatedType(BismuthParser::TemplatedTypeContext * /*ctx*/) override { }
  virtual void exitTemplatedType(BismuthParser::TemplatedTypeContext * /*ctx*/) override { }

  virtual void enterProgramType(BismuthParser::ProgramTypeContext * /*ctx*/) override { }
  virtual void exitProgramType(BismuthParser::ProgramTypeContext * /*ctx*/) override { }

  virtual void enterChannelType(BismuthParser::ChannelTypeContext * /*ctx*/) override { }
  virtual void exitChannelType(BismuthParser::ChannelTypeContext * /*ctx*/) override { }

  virtual void enterBoxType(BismuthParser::BoxTypeContext * /*ctx*/) override { }
  virtual void exitBoxType(BismuthParser::BoxTypeContext * /*ctx*/) override { }

  virtual void enterIntegerValue(BismuthParser::IntegerValueContext * /*ctx*/) override { }
  virtual void exitIntegerValue(BismuthParser::IntegerValueContext * /*ctx*/) override { }

  virtual void enterBooleanConst(BismuthParser::BooleanConstContext * /*ctx*/) override { }
  virtual void exitBooleanConst(BismuthParser::BooleanConstContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

