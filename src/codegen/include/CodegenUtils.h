/**
 * @file CodegenUtils.h
 * @author Alex Friedman (ahfriedman.com)
 * @brief Shared functions used by various codegen components
 * @version 0.1
 * @date 2023-04-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include "BismuthErrorHandler.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/NoFolder.h"

// #include "CastUtils.h"

// #include <any>
#include <string>
// #include <regex>

#include <variant>
#include <optional>

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

class CodegenVisitor
{

public:
    /**
     * @brief Construct a new Codegen Visitor object
     *
     * @param p Property manager to use
     * @param moduleName LLVM Module name to use
     * @param f Compiler flags
     */
    CodegenVisitor(std::string moduleName, int f = 0)
    {
        flags = f;

        // LLVM Stuff
        context = new LLVMContext();
        module = new Module(moduleName, *context);

        // Use the NoFolder to turn off constant folding
        builder = new IRBuilder<NoFolder>(module->getContext());

        // LLVM Types
        VoidTy = llvm::Type::getVoidTy(module->getContext());
        Int32Ty = llvm::Type::getInt32Ty(module->getContext());
        Int64Ty = llvm::Type::getInt64Ty(module->getContext());
        Int1Ty = llvm::Type::getInt1Ty(module->getContext());
        Int8Ty = llvm::Type::getInt8Ty(module->getContext());
        Int32Zero = ConstantInt::get(Int32Ty, 0, true);
        Int32One = ConstantInt::get(Int32Ty, 1, true);
        i8p = llvm::Type::getInt8PtrTy(module->getContext());
        Int8PtrPtrTy = i8p->getPointerTo();
    }

    // These should automatically have GlobalValue::ExternalLinkage per inspecting source code...
    llvm::FunctionCallee getWriteProjection()
    {
        return module->getOrInsertFunction("WriteProjection",
                                           llvm::FunctionType::get(
                                               VoidTy,
                                               {Int32Ty,
                                                Int32Ty},
                                               false));
    }

    llvm::FunctionCallee getReadProjection()
    {
        return module->getOrInsertFunction("ReadProjection",
                                           llvm::FunctionType::get(
                                               Int32Ty,
                                               {Int32Ty},
                                               false));
    }

    llvm::FunctionCallee getMalloc()
    {
        return module->getOrInsertFunction(
            "malloc",
            llvm::FunctionType::get(
                i8p,
                {Int32Ty},
                false));
    }

    llvm::FunctionCallee getFree()
    {
        return module->getOrInsertFunction(
            "free",
            llvm::FunctionType::get(
                VoidTy,
                {i8p},
                false));
    }

    llvm::FunctionCallee getGCMalloc()
    {
        // return module->getOrInsertFunction(
        //     "malloc",
        //     llvm::FunctionType::get(
        //         i8p,
        //         {Int32Ty},
        //         false));

        return module->getOrInsertFunction(
            "GC_malloc",
            llvm::FunctionType::get(
                i8p,
                {Int64Ty},
                false));
    }

    llvm::FunctionCallee getWeakenChannel()
    {
        return module->getOrInsertFunction(
            "WeakenChannel",
            llvm::FunctionType::get(
                VoidTy,
                {Int32Ty},
                false));
    }

    llvm::FunctionCallee getWriteChannel()
    {
        return module->getOrInsertFunction(
            "WriteChannel",
            llvm::FunctionType::get(
                VoidTy,
                {Int32Ty,
                 i8p},
                false));
    }

    llvm::FunctionCallee getReadChannel()
    {
        return module->getOrInsertFunction(
            "ReadChannel",
            llvm::FunctionType::get(
                i8p,
                {Int32Ty},
                false));
    }

    llvm::FunctionCallee getExecute()
    {
        return module->getOrInsertFunction(
            "Execute",
            llvm::FunctionType::get(
                Int32Ty,
                {llvm::FunctionType::get(
                     VoidTy,
                     {Int32Ty},
                     false)
                     ->getPointerTo()},
                false));
    }

    llvm::FunctionCallee getShouldLoop()
    {
        return module->getOrInsertFunction(
            "ShouldLoop",
            llvm::FunctionType::get(
                Int1Ty,
                {Int32Ty},
                false));
    }
    llvm::FunctionCallee getShouldAcceptWhileLoop()
    {
        return module->getOrInsertFunction(
            "ShouldAcceptWhileLoop",
            llvm::FunctionType::get(
                Int1Ty,
                {Int32Ty},
                false));
    }

    llvm::FunctionCallee getPopEndLoop()
    {
        return module->getOrInsertFunction(
            "PopEndLoop",
            llvm::FunctionType::get(
                VoidTy,
                {Int32Ty},
                false));
    }

    llvm::FunctionCallee getContractChannel()
    {
        return module->getOrInsertFunction(
            "ContractChannel",
            llvm::FunctionType::get(
                VoidTy,
                {Int32Ty},
                false));
    }

    llvm::FunctionCallee get_address_map_create()
    {
        return module->getOrInsertFunction(
            "_address_map_create",
            llvm::FunctionType::get(
                i8p,
                {},
                false));
    }

    llvm::Value *getNewAddressMap()
    {
        return builder->CreateCall(get_address_map_create(), {});
    }

    void deleteAddressMap(llvm::Value *val)
    {
        builder->CreateCall(
            module->getOrInsertFunction(
                "_address_map_delete",
                llvm::FunctionType::get(
                    VoidTy,
                    {i8p},
                    false)),
            val);
    }

    // https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl07.html#adjusting-existing-variables-for-mutation
    llvm::AllocaInst *CreateEntryBlockAlloc(llvm::Type *ty, std::string identifier)
    {
        llvm::Function *fn = builder->GetInsertBlock()->getParent();
        IRBuilder<> tempBuilder(&fn->getEntryBlock(), fn->getEntryBlock().begin());
        return tempBuilder.CreateAlloca(ty, 0, identifier);
    }

private:
    BismuthErrorHandler errorHandler = BismuthErrorHandler(CODEGEN);

    // LLVM
    LLVMContext *context;
    Module *module;
    IRBuilder<NoFolder> *builder;

    // Commonly used types
    llvm::Type *VoidTy;
    llvm::Type *Int1Ty;
    llvm::IntegerType *Int8Ty;
    llvm::IntegerType *Int32Ty; // Things like 32 bit integers
    llvm::IntegerType *Int64Ty;
    llvm::Type *i8p;
    llvm::Type *Int8PtrPtrTy;
    Constant *Int32Zero;
    Constant *Int32One;
};
