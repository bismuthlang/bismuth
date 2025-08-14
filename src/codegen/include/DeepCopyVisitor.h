/**
 * @file DeepCopyVisitor.h
 * @author Alex Friedman (ahfriedman.com)
 * @brief Code for copying variables
 * @version 0.1
 * @date 2023-04-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include "CodegenUtils.h"

using llvm::AllocaInst;
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
using llvm::SwitchInst;

using std::optional;

class DeepCopyVisitor : public CodegenModule
{

    // enum DeepCopyType
    // {
    //     GC_MALLOC,
    //     MIXED_MALLOC, // Uses Malloc at top level, then GC MALLOC
    //     NORM_MALLOC,
    // };

public:
    DeepCopyVisitor(Module *m, DisplayMode mode, int f, BismuthErrorHandler e) : CodegenModule(m, mode, f, e)
    {
        errorHandler = e;
    }

    Value *runGCMalloc(IRBuilder<NoFolder> *builder, llvm::TypeSize size)
    {
        return builder->CreateCall(
            getGCMalloc(),
            {builder->getInt64(size)});
    }

    Value *getNewAddressMap(IRBuilder<NoFolder> *builder)
    {
        return builder->CreateCall(get_address_map_create(), {});
    }

    void deleteAddressMap(IRBuilder<NoFolder> *builder, Value *val)
    {
        builder->CreateCall(
            module->getOrInsertFunction(
                "_address_map_delete",
                FunctionType::get(
                    UnitTy,
                    {i8p},
                    false)),
            val);
    }

    // TODO: REFACTOR W IMPL IN CODEGEN VISITOR
    // https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl07.html#adjusting-existing-variables-for-mutation
    llvm::AllocaInst * CreateEntryBlockAlloc(IRBuilder<NoFolder> *builder, llvm::Type *ty, std::string identifier)
    {
        llvm::Function *fn = builder->GetInsertBlock()->getParent();
        IRBuilder<> tempBuilder(&fn->getEntryBlock(), fn->getEntryBlock().begin());
        return tempBuilder.CreateAlloca(ty, 0, identifier);
    }

    optional<Value *> deepCopy(IRBuilder<NoFolder> *builder, const Type* type, Value *to_copy) = delete;

    optional<Value *> deepCopy(IRBuilder<NoFolder> *builder, const Type& type, Value *to_copy)
    {
        Value *addrMap = getNewAddressMap(builder);
        optional<Value *> ans = deepCopyHelper(builder, type, to_copy, addrMap);// , MIXED_MALLOC);
        deleteAddressMap(builder, addrMap);
        return ans;
    }

private:
    // FIXME: DONT DUPLICATE THESE ACROSS FILES
    optional<Value *> deepCopyHelper(IRBuilder<NoFolder> *builder, const Type& type, Value *stoVal, Value *addrMap);
    optional<Value *> deepCopyHelper(IRBuilder<NoFolder> *builder, const Type* type, Value *stoVal, Value *addrMap) = delete;
};
