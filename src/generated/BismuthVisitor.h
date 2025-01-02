
// Generated from Bismuth.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "BismuthParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by BismuthParser.
 */
class  BismuthVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by BismuthParser.
   */
    virtual std::any visitCompilationUnit(BismuthParser::CompilationUnitContext *context) = 0;

    virtual std::any visitStructCase(BismuthParser::StructCaseContext *context) = 0;

    virtual std::any visitGenericTemplate(BismuthParser::GenericTemplateContext *context) = 0;

    virtual std::any visitGenericType(BismuthParser::GenericTypeContext *context) = 0;

    virtual std::any visitGenericSession(BismuthParser::GenericSessionContext *context) = 0;

    virtual std::any visitGenericSpecifier(BismuthParser::GenericSpecifierContext *context) = 0;

    virtual std::any visitDefineEnum(BismuthParser::DefineEnumContext *context) = 0;

    virtual std::any visitDefineStruct(BismuthParser::DefineStructContext *context) = 0;

    virtual std::any visitDefineProgram(BismuthParser::DefineProgramContext *context) = 0;

    virtual std::any visitDefineFunction(BismuthParser::DefineFunctionContext *context) = 0;

    virtual std::any visitExternStatement(BismuthParser::ExternStatementContext *context) = 0;

    virtual std::any visitPathElement(BismuthParser::PathElementContext *context) = 0;

    virtual std::any visitPath(BismuthParser::PathContext *context) = 0;

    virtual std::any visitImportStatement(BismuthParser::ImportStatementContext *context) = 0;

    virtual std::any visitInv_args(BismuthParser::Inv_argsContext *context) = 0;

    virtual std::any visitAssignableIsPresent(BismuthParser::AssignableIsPresentContext *context) = 0;

    virtual std::any visitCopyExpr(BismuthParser::CopyExprContext *context) = 0;

    virtual std::any visitIConstExpr(BismuthParser::IConstExprContext *context) = 0;

    virtual std::any visitArrayAccess(BismuthParser::ArrayAccessContext *context) = 0;

    virtual std::any visitBinaryArithExpr(BismuthParser::BinaryArithExprContext *context) = 0;

    virtual std::any visitIdentifierExpr(BismuthParser::IdentifierExprContext *context) = 0;

    virtual std::any visitCallExpr(BismuthParser::CallExprContext *context) = 0;

    virtual std::any visitFieldAccessExpr(BismuthParser::FieldAccessExprContext *context) = 0;

    virtual std::any visitBinaryRelExpr(BismuthParser::BinaryRelExprContext *context) = 0;

    virtual std::any visitAssignableRecv(BismuthParser::AssignableRecvContext *context) = 0;

    virtual std::any visitInitBox(BismuthParser::InitBoxContext *context) = 0;

    virtual std::any visitLambdaExpr(BismuthParser::LambdaExprContext *context) = 0;

    virtual std::any visitAsChannelExpr(BismuthParser::AsChannelExprContext *context) = 0;

    virtual std::any visitSConstExpr(BismuthParser::SConstExprContext *context) = 0;

    virtual std::any visitUnaryExpr(BismuthParser::UnaryExprContext *context) = 0;

    virtual std::any visitAssignableExec(BismuthParser::AssignableExecContext *context) = 0;

    virtual std::any visitEqExpr(BismuthParser::EqExprContext *context) = 0;

    virtual std::any visitLogAndExpr(BismuthParser::LogAndExprContext *context) = 0;

    virtual std::any visitLogOrExpr(BismuthParser::LogOrExprContext *context) = 0;

    virtual std::any visitArrayExpression(BismuthParser::ArrayExpressionContext *context) = 0;

    virtual std::any visitInitProduct(BismuthParser::InitProductContext *context) = 0;

    virtual std::any visitParenExpr(BismuthParser::ParenExprContext *context) = 0;

    virtual std::any visitPathExpr(BismuthParser::PathExprContext *context) = 0;

    virtual std::any visitDeref(BismuthParser::DerefContext *context) = 0;

    virtual std::any visitBConstExpr(BismuthParser::BConstExprContext *context) = 0;

    virtual std::any visitLambdaConstExpr(BismuthParser::LambdaConstExprContext *context) = 0;

    virtual std::any visitBlock(BismuthParser::BlockContext *context) = 0;

    virtual std::any visitCondition(BismuthParser::ConditionContext *context) = 0;

    virtual std::any visitSelectAlternative(BismuthParser::SelectAlternativeContext *context) = 0;

    virtual std::any visitMatchAlternative(BismuthParser::MatchAlternativeContext *context) = 0;

    virtual std::any visitProtoAlternative(BismuthParser::ProtoAlternativeContext *context) = 0;

    virtual std::any visitProtoElse(BismuthParser::ProtoElseContext *context) = 0;

    virtual std::any visitParameterList(BismuthParser::ParameterListContext *context) = 0;

    virtual std::any visitParameter(BismuthParser::ParameterContext *context) = 0;

    virtual std::any visitAssignment(BismuthParser::AssignmentContext *context) = 0;

    virtual std::any visitTypeDef(BismuthParser::TypeDefContext *context) = 0;

    virtual std::any visitVarDeclStatement(BismuthParser::VarDeclStatementContext *context) = 0;

    virtual std::any visitAssignStatement(BismuthParser::AssignStatementContext *context) = 0;

    virtual std::any visitConditionalStatement(BismuthParser::ConditionalStatementContext *context) = 0;

    virtual std::any visitSelectStatement(BismuthParser::SelectStatementContext *context) = 0;

    virtual std::any visitMatchStatement(BismuthParser::MatchStatementContext *context) = 0;

    virtual std::any visitReturnStatement(BismuthParser::ReturnStatementContext *context) = 0;

    virtual std::any visitExitStatement(BismuthParser::ExitStatementContext *context) = 0;

    virtual std::any visitSkipStatement(BismuthParser::SkipStatementContext *context) = 0;

    virtual std::any visitBlockStatement(BismuthParser::BlockStatementContext *context) = 0;

    virtual std::any visitProgramSend(BismuthParser::ProgramSendContext *context) = 0;

    virtual std::any visitProgramLoop(BismuthParser::ProgramLoopContext *context) = 0;

    virtual std::any visitForStatement(BismuthParser::ForStatementContext *context) = 0;

    virtual std::any visitProgramCase(BismuthParser::ProgramCaseContext *context) = 0;

    virtual std::any visitProgramProject(BismuthParser::ProgramProjectContext *context) = 0;

    virtual std::any visitProgramContract(BismuthParser::ProgramContractContext *context) = 0;

    virtual std::any visitProgramWeaken(BismuthParser::ProgramWeakenContext *context) = 0;

    virtual std::any visitProgramAccept(BismuthParser::ProgramAcceptContext *context) = 0;

    virtual std::any visitProgramAcceptWhile(BismuthParser::ProgramAcceptWhileContext *context) = 0;

    virtual std::any visitProgramAcceptIf(BismuthParser::ProgramAcceptIfContext *context) = 0;

    virtual std::any visitProgramClose(BismuthParser::ProgramCloseContext *context) = 0;

    virtual std::any visitProgramCancel(BismuthParser::ProgramCancelContext *context) = 0;

    virtual std::any visitExpressionStatement(BismuthParser::ExpressionStatementContext *context) = 0;

    virtual std::any visitAssignmentStatement(BismuthParser::AssignmentStatementContext *context) = 0;

    virtual std::any visitVariableDeclaration(BismuthParser::VariableDeclarationContext *context) = 0;

    virtual std::any visitShiftOp(BismuthParser::ShiftOpContext *context) = 0;

    virtual std::any visitTypeOrVar(BismuthParser::TypeOrVarContext *context) = 0;

    virtual std::any visitProtocol(BismuthParser::ProtocolContext *context) = 0;

    virtual std::any visitRecvType(BismuthParser::RecvTypeContext *context) = 0;

    virtual std::any visitSendType(BismuthParser::SendTypeContext *context) = 0;

    virtual std::any visitWnProto(BismuthParser::WnProtoContext *context) = 0;

    virtual std::any visitOcProto(BismuthParser::OcProtoContext *context) = 0;

    virtual std::any visitExtChoiceProto(BismuthParser::ExtChoiceProtoContext *context) = 0;

    virtual std::any visitIntChoiceProto(BismuthParser::IntChoiceProtoContext *context) = 0;

    virtual std::any visitCloseableProto(BismuthParser::CloseableProtoContext *context) = 0;

    virtual std::any visitProtoBranch(BismuthParser::ProtoBranchContext *context) = 0;

    virtual std::any visitLambdaType(BismuthParser::LambdaTypeContext *context) = 0;

    virtual std::any visitCustomType(BismuthParser::CustomTypeContext *context) = 0;

    virtual std::any visitArrayType(BismuthParser::ArrayTypeContext *context) = 0;

    virtual std::any visitDynArrayType(BismuthParser::DynArrayTypeContext *context) = 0;

    virtual std::any visitSumType(BismuthParser::SumTypeContext *context) = 0;

    virtual std::any visitBaseType(BismuthParser::BaseTypeContext *context) = 0;

    virtual std::any visitTemplatedType(BismuthParser::TemplatedTypeContext *context) = 0;

    virtual std::any visitProgramType(BismuthParser::ProgramTypeContext *context) = 0;

    virtual std::any visitChannelType(BismuthParser::ChannelTypeContext *context) = 0;

    virtual std::any visitBoxType(BismuthParser::BoxTypeContext *context) = 0;

    virtual std::any visitIntegerValue(BismuthParser::IntegerValueContext *context) = 0;

    virtual std::any visitBooleanConst(BismuthParser::BooleanConstContext *context) = 0;


};

