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
#include "BismuthBaseVisitor.h"
#include "CompilerFlags.h"

#include "BismuthErrorHandler.h"
#include "DeepCopyVisitor.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/NoFolder.h"

#include "CastUtils.h"

// #include <any>
#include <string>
// #include <regex>

#include <variant>
#include <optional>

#include "TypedAST.h"
#include "CodegenUtils.h"
#include "Scope.h"

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

class CodegenVisitor : public CodegenModule, TypedASTVisitor
{
    // TODO: move all defs to cpp file and move everything here to the private section at the end of the file
private:
    // TODO: DO BETTER W/ A mangler
    // std::string currentNamespacePath; 
    std::map<std::string, llvm::AllocaInst *> allocations; 

    std::string getCodegenID(Symbol * sym);

    std::string getCodegenAllocationID(Symbol * sym);

    void setAllocation(Symbol * sym, llvm::AllocaInst * a);

    std::optional<llvm::AllocaInst *> getAllocation(Symbol * sym);

    llvm::AllocaInst * CreateAndLinkEntryBlockAlloc(llvm::Type * ty, Symbol * sym);

    llvm::Type * getLLVMType(Symbol * sym);

public:
    /**
     * @brief Construct a Codegen Visitor object
     *
     * @param p Property manager to use
     * @param moduleName LLVM Module name to use
     * @param f Compiler flags
     */
    CodegenVisitor(std::string moduleName, DisplayMode mode, int f = 0) 
        : CodegenModule(moduleName, mode, f)
        , copyVisitor(module, mode, f, errorHandler)
    {}

    /******************************************************************
     * Standard visitor methods all defined to use the typed versions
     ******************************************************************/
    // std::optional<Value *> visit(TSelectAlternativeNode & n) override;
    std::optional<Value *> visit(TSelectStatementNode & n) override;
    std::optional<Value *> visit(TBlockNode & n) override;
    std::optional<Value *> visit(TLambdaConstNode & n) override;
    std::optional<Value *> visit(TProgramDefNode & n) override;
    std::optional<Value *> visit(TDefineTemplateNode & n) override; 
    std::optional<Value *> visit(TConditionalStatementNode & n) override;
    std::optional<Value *> visit(TReturnNode & n) override;
    std::optional<Value *> visit(TProgramSendNode & n) override;
    std::optional<Value *> visit(TProgramRecvNode & n) override;
    std::optional<Value *> visit(TProgramIsPresetNode & n) override; 
    std::optional<Value *> visit(TProgramContractNode & n) override;
    std::optional<Value *> visit(TProgramWeakenNode & n) override;
    std::optional<Value *> visit(TProgramCancelNode & n) override;
    std::optional<Value *> visit(TProgramExecNode & n) override;
    std::optional<Value *> visit(TProgramAcceptNode & n) override;
    std::optional<Value *> visit(TProgramAcceptWhileNode & n) override;
    std::optional<Value *> visit(TProgramAcceptIfNode & n) override; 
    std::optional<Value *> visit(TDefineEnumNode & n) override;
    std::optional<Value *> visit(TDefineStructNode & n) override;
    std::optional<Value *> visit(TInitProductNode & n) override;
    std::optional<Value *> visit(TArrayRValue & n) override; 
    std::optional<Value *> visit(TWhileLoopNode & n) override;
    std::optional<Value *> visit(TExternNode & n) override;
    std::optional<Value *> visit(TInvocationNode & n) override;
    std::optional<Value *> visit(TFieldAccessNode & n) override;
    std::optional<Value *> visit(TIdentifier & n) override;
    std::optional<Value *> visit(TPathNode & n) override; 
    std::optional<Value *> visit(TDerefBoxNode & n) override;
    std::optional<Value *> visit(TArrayAccessNode & n) override;
    std::optional<Value *> visit(TDynArrayAccessNode & n) override; 
    std::optional<Value *> visit(TAssignNode & n) override;
    std::optional<Value *> visit(TBinaryRelNode & n) override;
    std::optional<Value *> visit(TBinaryArithNode & n) override;
    std::optional<Value *> visit(TEqExprNode & n) override;
    std::optional<Value *> visit(TUnaryExprNode & n) override;
    std::optional<Value *> visit(TLogAndExprNode & n) override;
    std::optional<Value *> visit(TLogOrExprNode & n) override;
    std::optional<Value *> visit(TStringConstNode & n) override;
    std::optional<Value *> visit(TBooleanConstNode & n) override;
    std::optional<Value *> visit(TInt32ConstExprNode & n) override;
    std::optional<Value *> visit(TInt64ConstExprNode & n) override;
    std::optional<Value *> visit(TIntU32ConstExprNode & n) override;
    std::optional<Value *> visit(TIntU64ConstExprNode & n) override;
    std::optional<Value *> visit(TNumConstExprNode & n) override;
    std::optional<Value *> visit(TCompilationUnitNode & n) override;
    std::optional<Value *> visit(TVarDeclNode & n) override;
    std::optional<Value *> visit(TMatchStatementNode & n) override;
    std::optional<Value *> visit(TExitNode & n) override;
    std::optional<Value *> visit(TChannelCaseStatementNode & n) override;
    std::optional<Value *> visit(TProgramProjectNode & n) override;
    std::optional<Value *> visit(TInitBoxNode & n) override;
    std::optional<Value *> visit(TExprCopyNode & n) override; 
    std::optional<Value *> visit(TAsChannelNode & n) override;  

    std::optional<Value *> visitCompilationUnit(TCompilationUnitNode & n) { return visit(n); }

    Module *getModule() { return module; }
    void modPrint() { module->print(llvm::outs(), nullptr); }

    // From C++ Documentation for visitors
    template <class... Ts>
    struct overloaded : Ts...
    {
        using Ts::operator()...;
    };
    template <class... Ts>
    overloaded(Ts...) -> overloaded<Ts...>;

    Value * correctSumAssignment(const TypeSum *sum, Value *original)
    {
        unsigned int index = sum->getIndex(module, original->getType());

        if (index != 0)
        {
            llvm::Type *sumTy = sum->getLLVMType(module);
            llvm::AllocaInst * alloc = CreateEntryBlockAlloc(sumTy, "");

            Value *tagPtr = builder->CreateGEP(alloc, {Int32Zero, Int32Zero});

            builder->CreateStore(getU32(index), tagPtr);

            Value *valuePtr = builder->CreateGEP(alloc, {Int32Zero, Int32One});

            Value *corrected = builder->CreateBitCast(valuePtr, original->getType()->getPointerTo());
            builder->CreateStore(original, corrected);

            return builder->CreateLoad(sumTy, alloc);
        }

        return original; // Already correct (ie, a sum to the same sum), but WILL Break if we start doing more fancy sum cases...
    }

    std::optional<Value *> correctNullOptionalToSum(RecvMetadata meta, Value *original);

private:
    DeepCopyVisitor copyVisitor;
};
