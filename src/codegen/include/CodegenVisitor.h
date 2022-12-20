/**
 * @file CodegenVisitor.h
 * @author Alex Friedman (ahfriedman.com)
 * @brief Code Generation visitor header inspired by sample code
 * @version 0.1
 * @date 2022-09-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "antlr4-runtime.h"
#include "WPLBaseVisitor.h"
#include "CompilerFlags.h"

// #include "WPLTypedVisitor.h"

#include "PropertyManager.h"
#include "WPLErrorHandler.h"
#include "SemanticVisitor.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/NoFolder.h"

#include "CastUtils.h"

#include <any>
#include <string>
#include <regex>

#include <variant>

// using namespace llvm;
using llvm::ArrayRef;
using llvm::ArrayType;
using llvm::BasicBlock;
using llvm::Constant;
using llvm::ConstantInt;
using llvm::Function;
using llvm::FunctionCallee;
using llvm::FunctionType;
using llvm::GlobalValue;
using llvm::IRBuilder;
using llvm::LLVMContext;
using llvm::Module;
using llvm::NoFolder;
using llvm::PHINode;
using llvm::StringRef;
using llvm::Value;

class CodegenVisitor : WPLBaseVisitor
{

public:
    /**
     * @brief Construct a new Codegen Visitor object
     *
     * @param p Property manager to use
     * @param moduleName LLVM Module name to use
     * @param f Compiler flags
     */
    CodegenVisitor(PropertyManager *p, std::string moduleName, int f = 0)
    {
        props = p;
        flags = f;

        // LLVM Stuff
        context = new LLVMContext();
        module = new Module(moduleName, *context);

        // Use the NoFolder to turn off constant folding
        builder = new IRBuilder<NoFolder>(module->getContext());

        // LLVM Types
        VoidTy = llvm::Type::getVoidTy(module->getContext());
        Int32Ty = llvm::Type::getInt32Ty(module->getContext());
        Int1Ty = llvm::Type::getInt1Ty(module->getContext());
        Int8Ty = llvm::Type::getInt8Ty(module->getContext());
        Int32Zero = ConstantInt::get(Int32Ty, 0, true);
        Int32One = ConstantInt::get(Int32Ty, 1, true);
        i8p = llvm::Type::getInt8PtrTy(module->getContext());
        Int8PtrPtrTy = i8p->getPointerTo();
    }

    /***************************************
     * Typed wrappers for the basic visitor
     ***************************************/

    std::optional<Value *> TvisitCompilationUnit(WPLParser::CompilationUnitContext *ctx);
    std::optional<Value *> TvisitInvocation(WPLParser::InvocationContext *ctx);
    std::optional<Value *> TvisitArrayAccess(WPLParser::ArrayAccessContext *ctx);
    std::optional<Value *> TvisitArrayOrVar(WPLParser::ArrayOrVarContext *ctx);

    std::optional<Value *> TvisitIConstExpr(WPLParser::IConstExprContext *ctx);
    std::optional<Value *> TvisitArrayAccessExpr(WPLParser::ArrayAccessExprContext *ctx);
    std::optional<Value *> TvisitSConstExpr(WPLParser::SConstExprContext *ctx);
    std::optional<Value *> TvisitUnaryExpr(WPLParser::UnaryExprContext *ctx);
    std::optional<Value *> TvisitBinaryArithExpr(WPLParser::BinaryArithExprContext *ctx);
    std::optional<Value *> TvisitEqExpr(WPLParser::EqExprContext *ctx);
    std::optional<Value *> TvisitLogAndExpr(WPLParser::LogAndExprContext *ctx);
    std::optional<Value *> TvisitLogOrExpr(WPLParser::LogOrExprContext *ctx);
    std::optional<Value *> TvisitCallExpr(WPLParser::CallExprContext *ctx);
    // std::optional<Value *> TvisitVariableExpr(WPLParser::VariableExprContext *ctx);
    std::optional<Value *> TvisitFieldAccessExpr(WPLParser::FieldAccessExprContext *ctx);
    std::optional<Value *> TvisitParenExpr(WPLParser::ParenExprContext *ctx);
    std::optional<Value *> TvisitBinaryRelExpr(WPLParser::BinaryRelExprContext *ctx);
    std::optional<Value *> TvisitBConstExpr(WPLParser::BConstExprContext *ctx);
    std::optional<Value *> TvisitBlock(WPLParser::BlockContext *ctx);
    std::optional<Value *> TvisitCondition(WPLParser::ConditionContext *ctx);
    std::optional<Value *> TvisitSelectAlternative(WPLParser::SelectAlternativeContext *ctx);
    std::optional<Value *> TvisitParameterList(WPLParser::ParameterListContext *ctx);
    std::optional<Value *> TvisitParameter(WPLParser::ParameterContext *ctx);
    std::optional<Value *> TvisitAssignment(WPLParser::AssignmentContext *ctx);
    std::optional<Value *> TvisitExternStatement(WPLParser::ExternStatementContext *ctx);
    std::optional<Value *> TvisitFuncDef(WPLParser::ProgDefContext *ctx);
    std::optional<Value *> TvisitAssignStatement(WPLParser::AssignStatementContext *ctx);
    std::optional<Value *> TvisitVarDeclStatement(WPLParser::VarDeclStatementContext *ctx);
    std::optional<Value *> TvisitProgramLoop(WPLParser::ProgramLoopContext *ctx);
    std::optional<Value *> TvisitConditionalStatement(WPLParser::ConditionalStatementContext *ctx);
    std::optional<Value *> TvisitSelectStatement(WPLParser::SelectStatementContext *ctx);
    std::optional<Value *> TvisitCallStatement(WPLParser::CallStatementContext *ctx);
    std::optional<Value *> TvisitReturnStatement(WPLParser::ReturnStatementContext *ctx);
    std::optional<Value *> TvisitBlockStatement(WPLParser::BlockStatementContext *ctx);
    std::optional<Value *> TvisitTypeOrVar(WPLParser::TypeOrVarContext *ctx);
    std::optional<Value *> TvisitType(WPLParser::TypeContext *ctx);
    std::optional<Value *> TvisitBooleanConst(WPLParser::BooleanConstContext *ctx);

    std::optional<Value *> TvisitLambdaConstExpr(WPLParser::LambdaConstExprContext *ctx);
    // std::optional<Value *> TvisitDefineEnum(WPLParser::DefineEnumContext *ctx);
    std::optional<Value *> TvisitMatchStatement(WPLParser::MatchStatementContext *ctx);
    std::optional<Value *> TvisitInitProduct(WPLParser::InitProductContext *ctx);

    // std::optional<Value *> TvisitDefineProgram(WPLParser::DefineProgramContext * ctx);

    /******************************************************************
     * Standard visitor methods all defined to use the typed versions
     ******************************************************************/

    std::any visitCompilationUnit(WPLParser::CompilationUnitContext *ctx) override { return TvisitCompilationUnit(ctx); };
    std::any visitInvocation(WPLParser::InvocationContext *ctx) override { return TvisitInvocation(ctx); };
    std::any visitArrayAccess(WPLParser::ArrayAccessContext *ctx) override { return TvisitArrayAccess(ctx); };
    std::any visitArrayOrVar(WPLParser::ArrayOrVarContext *ctx) override { return TvisitArrayOrVar(ctx); };

    std::any visitIConstExpr(WPLParser::IConstExprContext *ctx) override { return TvisitIConstExpr(ctx); };
    std::any visitArrayAccessExpr(WPLParser::ArrayAccessExprContext *ctx) override { return TvisitArrayAccessExpr(ctx); };
    std::any visitSConstExpr(WPLParser::SConstExprContext *ctx) override { return TvisitSConstExpr(ctx); };
    std::any visitUnaryExpr(WPLParser::UnaryExprContext *ctx) override { return TvisitUnaryExpr(ctx); };
    std::any visitBinaryArithExpr(WPLParser::BinaryArithExprContext *ctx) override { return TvisitBinaryArithExpr(ctx); };
    std::any visitEqExpr(WPLParser::EqExprContext *ctx) override { return TvisitEqExpr(ctx); };
    std::any visitLogAndExpr(WPLParser::LogAndExprContext *ctx) override { return TvisitLogAndExpr(ctx); };
    std::any visitLogOrExpr(WPLParser::LogOrExprContext *ctx) override { return TvisitLogOrExpr(ctx); };
    std::any visitCallExpr(WPLParser::CallExprContext *ctx) override { return TvisitCallExpr(ctx); };
    // std::any visitVariableExpr(WPLParser::VariableExprContext *ctx) override { return TvisitVariableExpr(ctx); };
    std::any visitFieldAccessExpr(WPLParser::FieldAccessExprContext *ctx) override { return TvisitFieldAccessExpr(ctx); };
    std::any visitParenExpr(WPLParser::ParenExprContext *ctx) override { return TvisitParenExpr(ctx); };
    std::any visitBinaryRelExpr(WPLParser::BinaryRelExprContext *ctx) override { return TvisitBinaryRelExpr(ctx); };
    std::any visitBConstExpr(WPLParser::BConstExprContext *ctx) override { return TvisitBConstExpr(ctx); };
    std::any visitBlock(WPLParser::BlockContext *ctx) override { return TvisitBlock(ctx); };
    std::any visitCondition(WPLParser::ConditionContext *ctx) override { return TvisitCondition(ctx); };
    std::any visitSelectAlternative(WPLParser::SelectAlternativeContext *ctx) override { return TvisitSelectAlternative(ctx); };
    std::any visitParameterList(WPLParser::ParameterListContext *ctx) override { return TvisitParameterList(ctx); };
    std::any visitParameter(WPLParser::ParameterContext *ctx) override { return TvisitParameter(ctx); };
    std::any visitAssignment(WPLParser::AssignmentContext *ctx) override { return TvisitAssignment(ctx); };
    std::any visitExternStatement(WPLParser::ExternStatementContext *ctx) override { return TvisitExternStatement(ctx); };
    std::any visitProgDef(WPLParser::ProgDefContext *ctx) override { return TvisitFuncDef(ctx); };
    std::any visitAssignStatement(WPLParser::AssignStatementContext *ctx) override { return TvisitAssignStatement(ctx); };
    std::any visitVarDeclStatement(WPLParser::VarDeclStatementContext *ctx) override { return TvisitVarDeclStatement(ctx); };
    std::any visitProgramLoop(WPLParser::ProgramLoopContext *ctx) override { return TvisitProgramLoop(ctx); };
    std::any visitConditionalStatement(WPLParser::ConditionalStatementContext *ctx) override { return TvisitConditionalStatement(ctx); };
    std::any visitSelectStatement(WPLParser::SelectStatementContext *ctx) override { return TvisitSelectStatement(ctx); };
    std::any visitCallStatement(WPLParser::CallStatementContext *ctx) override { return TvisitCallStatement(ctx); };
    std::any visitReturnStatement(WPLParser::ReturnStatementContext *ctx) override { return TvisitReturnStatement(ctx); };
    std::any visitBlockStatement(WPLParser::BlockStatementContext *ctx) override { return TvisitBlockStatement(ctx); };
    std::any visitTypeOrVar(WPLParser::TypeOrVarContext *ctx) override { return TvisitTypeOrVar(ctx); };
    // std::any visitType(WPLParser::TypeContext *ctx) override { return TvisitType(ctx); };
    std::any visitBooleanConst(WPLParser::BooleanConstContext *ctx) override { return TvisitBooleanConst(ctx); };

    std::any visitLambdaConstExpr(WPLParser::LambdaConstExprContext *ctx) override { return TvisitLambdaConstExpr(ctx); }
    // std::any visitDefineEnum(WPLParser::DefineEnumContext *ctx) override { return TvisitDefineEnum(ctx); }
    std::any visitMatchStatement(WPLParser::MatchStatementContext *ctx) override { return TvisitMatchStatement(ctx); }
    std::any visitInitProduct(WPLParser::InitProductContext *ctx) override { return TvisitInitProduct(ctx); }

    std::any visitDefineProgram(WPLParser::DefineProgramContext *ctx) override { return visitInvokeable(ctx->defineProc()); } // FIXME: DO BETTER!!!

    std::optional<Value *> TvisitAssignableRecv(WPLParser::AssignableRecvContext *ctx);
    std::any visitAssignableRecv(WPLParser::AssignableRecvContext *ctx) override { return TvisitAssignableRecv(ctx); }
    
    std::any visitProgramSend(WPLParser::ProgramSendContext *ctx) override { return TvisitProgramSend(ctx); }
    std::optional<Value *> TvisitProgramSend(WPLParser::ProgramSendContext *ctx);


    std::any visitAssignableExec(WPLParser::AssignableExecContext *ctx) override { return TvisitAssignableExec(ctx); }
    std::optional<Value *> TvisitAssignableExec(WPLParser::AssignableExecContext *ctx);


    bool hasErrors(int flags) { return errorHandler.hasErrors(flags); }
    std::string getErrors() { return errorHandler.errorList(); }

    PropertyManager *getProperties() { return props; }

    Module *getModule() { return module; }
    void modPrint() { module->print(llvm::outs(), nullptr); }

    /**
     * @brief Generates the code for an InvokeableType (PROC/FUNC)
     *
     * @param sum The FuncDefContext to build the function from
     * @return std::optional<Value *> Empty as this shouldn't be seen as a value
     */
    std::optional<Value *> visitInvokeable(WPLParser::DefineProcContext *ctx)
    {
        BasicBlock *ins = builder->GetInsertBlock();

        // Lookup the symbol from the context
        std::optional<Symbol *> symOpt = props->getBinding(ctx);

        // Get the function name. Done separatley from sym in case the symbol isn't found
        std::string funcId = ctx->name->getText();

        // If we couldn't find the function, throw an error.
        if (!symOpt)
        {
            errorHandler.addCodegenError(ctx->getStart(), "Unbound function: " + funcId);
            return {};
        }

        Symbol *sym = symOpt.value();
        if (!sym->type)
        {
            errorHandler.addCodegenError(ctx->getStart(), "Symbol in invocation missing type. Probably compiler error.");
            return {};
        }

        const Type *type = sym->type;

        if (const TypeProgram *inv = dynamic_cast<const TypeProgram *>(type))
        {

            llvm::Type *genericType = type->getLLVMType(module)->getPointerElementType();

            if (llvm::FunctionType *fnType = static_cast<llvm::FunctionType *>(genericType))
            {
                Function *fn = inv->getLLVMName() ? module->getFunction(inv->getLLVMName().value()) : Function::Create(fnType, GlobalValue::PrivateLinkage, funcId, module);
                ; // Lookup the function first
                inv->setName(fn->getName().str());

                // Get the parameter list context for the invokable
                // WPLParser::ParameterListContext *paramList = ctx->paramList;
                // Create basic block
                BasicBlock *bBlk = BasicBlock::Create(module->getContext(), "entry", fn);
                builder->SetInsertPoint(bBlk);

                // Bind all of the arguments
                llvm::AllocaInst *v = builder->CreateAlloca(Int32Ty, 0, ctx->channelName->getText());
                std::optional<Symbol *> symOpt = props->getBinding(ctx->VARIABLE().at(1)); // FIXME: DO BETTER
                if (!symOpt)
                {
                    errorHandler.addCodegenError(ctx->getStart(), "Unable to generate channel id");
                }
                else
                {
                    symOpt.value()->val = v;

                    builder->CreateStore((fn->args()).begin(), v);
                }

                /*
                for (auto &arg : fn->args())
                {
                    // Get the argumengt number (just seems easier than making my own counter)
                    int argNumber = arg.getArgNo();

                    // Get the argument's type
                    llvm::Type *type = fnType->params()[argNumber];

                    // Get the argument name (This even works for arrays!)
                    std::string argName = paramList->params.at(argNumber)->getText();

                    // Create an allocation for the argumentr
                    llvm::AllocaInst *v = builder->CreateAlloca(type, 0, argName);

                    // Try to find the parameter's bnding to determine what value to bind to it.
                    std::optional<Symbol *> symOpt = props->getBinding(paramList->params.at(argNumber));

                    if (!symOpt)
                    {
                        errorHandler.addCodegenError(ctx->getStart(), "Unable to generate parameter for function: " + argName);
                    }
                    else
                    {
                        symOpt.value()->val = v;

                        builder->CreateStore(&arg, v);
                    }
                }
                */

                // Get the codeblock for the PROC/FUNC
                WPLParser::BlockContext *block = ctx->block();

                // Generate code for the block
                for (auto e : block->stmts)
                {
                    e->accept(this);
                }

                // If we are a PROC, make sure to add a return type (if we don't already have one)
                // if (ctx->PROC() && !CodegenVisitor::blockEndsInReturn(block))
                if (!CodegenVisitor::blockEndsInReturn(block)) // FIXME: THIS SHOULD BECOME ALWAYS TRUE
                {
                    builder->CreateRetVoid();
                }
            }
            else
            {
                errorHandler.addCodegenError(ctx->getStart(), "Invocation type could not be cast to function!");
            }
        }
        else
        {
            errorHandler.addCodegenError(ctx->getStart(), "Could not generate a function call for type of: " + type->toString());
        }

        builder->SetInsertPoint(ins);
        return {};
    }

    std::optional<Value *> visitVariable(std::string id, std::optional<Symbol *> symOpt, antlr4::ParserRuleContext *ctx)
    {
        //  = props->getBinding(ctx);

        // If the symbol could not be found, raise an error
        if (!symOpt)
        {
            errorHandler.addCodegenError(ctx->getStart(), "Undefined variable access: " + id);
            return {};
        }

        Symbol *sym = symOpt.value();

        // Try getting the type for the symbol, raising an error if it could not be determined
        llvm::Type *type = sym->type->getLLVMType(module);
        if (!type)
        {
            errorHandler.addCodegenError(ctx->getStart(), "Unable to find type for variable: " + ctx->getText());
            return {};
        }

        // Make sure the variable has an allocation (or that we can find it due to it being a global var)
        if (!sym->val)
        {
            // If the symbol is a global var
            if (const TypeProgram *inv = dynamic_cast<const TypeProgram *>(sym->type)) //FIXME: Potentially lots of places that say TypeInvoke when they mean TypeProgram 
            {
                if (!inv->getLLVMName())
                {
                    errorHandler.addCodegenError(ctx->getStart(), "Could not locate IR name for function " + sym->toString());
                    return {};
                }

                Function *fn = module->getFunction(inv->getLLVMName().value());

                return fn;
            }
            else if (const TypeInvoke *inv = dynamic_cast<const TypeInvoke *>(sym->type)) //FIXME: This is annoying that we have to have duplicate code despite both APIs being the same
            {
                if (!inv->getLLVMName())
                {
                    errorHandler.addCodegenError(ctx->getStart(), "Could not locate IR name for function " + sym->toString());
                    return {};
                }

                Function *fn = module->getFunction(inv->getLLVMName().value());

                return fn;
            }
            else if (sym->isGlobal)
            {
                // Lookup the global var for the symbol
                llvm::GlobalVariable *glob = module->getNamedGlobal(sym->identifier);

                // Check that we found the variable. If not, throw an error.
                if (!glob)
                {
                    errorHandler.addCodegenError(ctx->getStart(), "Unable to find global variable: " + id);
                    return {};
                }

                // Create and return a load for the global var
                Value *val = builder->CreateLoad(glob);
                return val;
            }

            errorHandler.addCodegenError(ctx->getStart(), "Unable to find allocation for variable: " + ctx->getText());
            return {};
        }

        // Otherwise, we are a local variable with an allocation and, thus, can simply load it.
        Value *v = builder->CreateLoad(type, sym->val.value(), id);
        return v;
    }

    std::optional<Value *> any2Value(std::any any)
    {
        return anyOpt2Val<Value *>(any);
        // std::optional<std::optional<Value *>> temp = any2Opt<std::optional<Value *>>(any);
        // if(temp) return temp.value();
        // return {};
    }

protected:
    /**
     * @brief Helper function to determine if a Block ends in a return or not
     *
     * @param ctx The BlockContext to check
     * @return true If it ends in a return
     * @return false If it does not end in a return
     */
    static bool blockEndsInReturn(WPLParser::BlockContext *ctx)
    {
        return ctx->stmts.size() > 0 && dynamic_cast<WPLParser::ReturnStatementContext *>(ctx->stmts.at(ctx->stmts.size() - 1));
    }

private:
    PropertyManager *props;
    int flags;

    WPLErrorHandler errorHandler;

    // LLVM
    LLVMContext *context;
    Module *module;
    IRBuilder<NoFolder> *builder;

    // Commonly used types
    llvm::Type *VoidTy;
    llvm::Type *Int1Ty;
    llvm::IntegerType *Int8Ty;
    llvm::IntegerType *Int32Ty; // Things like 32 bit integers
    llvm::Type *i8p;
    llvm::Type *Int8PtrPtrTy;
    Constant *Int32Zero;
    Constant *Int32One;
};
