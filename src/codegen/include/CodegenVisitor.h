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

#include "TypedAST.h"

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

class CodegenVisitor : TypedASTVisitor
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

    /******************************************************************
     * Standard visitor methods all defined to use the typed versions
     ******************************************************************/
    // std::optional<Value *> visit(SelectAlternativeNode *n) override;
    std::optional<Value *> visit(SelectStatementNode *n) override;
    std::optional<Value *> visit(ConditionNode *n) override;
    std::optional<Value *> visit(BlockNode *n) override;
    std::optional<Value *> visit(LambdaConstNode *n) override;
    std::optional<Value *> visit(ProgramDefNode *n) override { return visitInvokeable(n); };
    std::optional<Value *> visit(ConditionalStatementNode *n) override;
    std::optional<Value *> visit(ReturnNode *n) override;
    std::optional<Value *> visit(ProgramSendNode *n) override;
    std::optional<Value *> visit(ProgramRecvNode *n) override;
    std::optional<Value *> visit(ProgramContractNode *n) override;
    std::optional<Value *> visit(ProgramWeakenNode *n) override;
    std::optional<Value *> visit(ProgramExecNode *n) override;
    std::optional<Value *> visit(ProgramAcceptNode *n) override;
    // std::optional<Value *> visit(DefineEnumNode *n) override;
    // std::optional<Value *> visit(DefineStructNode *n) override;
    std::optional<Value *> visit(InitProductNode *n) override;
    std::optional<Value *> visit(WhileLoopNode *n) override;
    std::optional<Value *> visit(ExternNode *n) override;
    std::optional<Value *> visit(InvocationNode *n) override;
    std::optional<Value *> visit(FieldAccessNode *n) override;
    std::optional<Value *> visit(VariableIDNode *n) override { return visitVariable(n->symbol, n->is_rvalue); };
    std::optional<Value *> visit(ArrayAccessNode *n) override;
    std::optional<Value *> visit(AssignNode *n) override;
    std::optional<Value *> visit(BinaryRelNode *n) override;
    std::optional<Value *> visit(BinaryArithNode *n) override;
    std::optional<Value *> visit(EqExprNode *n) override;
    std::optional<Value *> visit(UnaryExprNode *n) override;
    std::optional<Value *> visit(LogAndExprNode *n) override;
    std::optional<Value *> visit(LogOrExprNode *n) override;
    std::optional<Value *> visit(StringConstNode *n) override;
    std::optional<Value *> visit(BooleanConstNode *n) override;
    std::optional<Value *> visit(IConstExprNode *n) override;
    std::optional<Value *> visit(CompilationUnitNode *n) override;
    std::optional<Value *> visit(VarDeclNode *n) override;
    std::optional<Value *> visit(MatchStatementNode *n) override;


    std::optional<Value *> visitCompilationUnit(CompilationUnitNode *n) { return visit(n); }

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
    std::optional<Value *> visitInvokeable(ProgramDefNode *n)
    {
        BasicBlock *ins = builder->GetInsertBlock();

        // Get the function name. Done separatley from sym in case the symbol isn't found
        std::string funcId = n->name;

        const TypeProgram *inv = n->getType();

        llvm::Type *genericType = inv->getLLVMType(module)->getPointerElementType();

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
            llvm::AllocaInst *v = builder->CreateAlloca(Int32Ty, 0, n->channelSymbol->getIdentifier());
            // std::optional<Symbol *> symOpt = props->getBinding(ctx->VARIABLE().at(1)); // FIXME: DO BETTER

            //FIXME: DO WE NEED TO CHECK THAT WE HAVENT PREVIOUSLY SET VAL?
            n->channelSymbol->val = v; // FIXME: BECAUSE THIS IS ON THE DEFINITION, DO WE HAVE ISSUES WITH ALLOCATION REUSE?

            builder->CreateStore((fn->args()).begin(), v);

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
                    errorHandler.addCodegenError(nullptr, "Unable to generate parameter for function: " + argName);
                }
                else
                {
                    symOpt.value()->val = v;

                    builder->CreateStore(&arg, v);
                }
            }
            */

            // Get the codeblock for the PROC/FUNC
            // WPLParser::BlockContext *block = ctx->block();

            // Generate code for the block
            for (auto e : n->block->exprs)
            {
                // e->accept(this);
                this->accept(e);
            }

            // If we are a PROC, make sure to add a return type (if we don't already have one)
            // if (ctx->PROC() && !CodegenVisitor::blockEndsInReturn(block))
            if (!CodegenVisitor::blockEndsInReturn(n->block)) // FIXME: THIS SHOULD BECOME ALWAYS TRUE
            {
                builder->CreateRetVoid();
            }
        }
        else
        {
            errorHandler.addCodegenError(nullptr, "Invocation type could not be cast to function!");
        }

        builder->SetInsertPoint(ins);
        return {};
    }

    std::optional<Value *> visitVariable(Symbol *sym, bool is_rvalue)
    {
        // Try getting the type for the symbol, raising an error if it could not be determined
        llvm::Type *type = sym->type->getLLVMType(module);
        if (!type)
        {
            errorHandler.addCodegenError(nullptr, "Unable to find type for variable: " + sym->getIdentifier());
            return {};
        }

        // Make sure the variable has an allocation (or that we can find it due to it being a global var)
        if (!sym->val)
        {
            // If the symbol is a global var
            if (const TypeProgram *inv = dynamic_cast<const TypeProgram *>(sym->type)) // FIXME: Potentially lots of places that say TypeInvoke when they mean TypeProgram
            {
                if (!inv->getLLVMName())
                {
                    errorHandler.addCodegenError(nullptr, "Could not locate IR name for function " + sym->toString());
                    return {};
                }

                Function *fn = module->getFunction(inv->getLLVMName().value());

                return fn;
            }
            else if (const TypeInvoke *inv = dynamic_cast<const TypeInvoke *>(sym->type)) // FIXME: This is annoying that we have to have duplicate code despite both APIs being the same
            {
                if (!inv->getLLVMName())
                {
                    errorHandler.addCodegenError(nullptr, "Could not locate IR name for function " + sym->toString());
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
                    errorHandler.addCodegenError(nullptr, "Unable to find global variable: " + sym->getIdentifier());
                    return {};
                }

                // Create and return a load for the global var
                Value *val = builder->CreateLoad(glob);
                return val;
            }

            errorHandler.addCodegenError(nullptr, "Unable to find allocation for variable: " + sym->getIdentifier());
            return {};
        }

        if(!is_rvalue) return sym->val.value(); 
        // Otherwise, we are a local variable with an allocation and, thus, can simply load it.
        Value *v = builder->CreateLoad(type, sym->val.value(), sym->getIdentifier());
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
    static bool blockEndsInReturn(BlockNode *n)
    {
        // FIXME: DOES THIS EVEN WORK STILL GIVEN THE NEW REST GRAMMAR?
        return n->exprs.size() > 0 && dynamic_cast<ReturnNode *>(n->exprs.at(n->exprs.size() - 1));
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
