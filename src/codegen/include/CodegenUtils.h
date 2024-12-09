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
#include "llvm/IR/NoFolder.h"

#include <string>

#include "TypedAST.h"
#include "Symbol.h" // Only for VisibilityModifier

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


inline GlobalValue::LinkageTypes getLinkageType(VisibilityModifier m)
{
    switch(m)
    {
        case VisibilityModifier::PUBLIC:
            return GlobalValue::ExternalLinkage; 

        case VisibilityModifier::PUBLIC_LINK:
            return GlobalValue::AvailableExternallyLinkage;

        case VisibilityModifier::PRIVATE:
            return GlobalValue::PrivateLinkage; 
    }
}


class CodegenModule
{
public: 
    const unsigned int DYN_ARRAY_GROW_FACTOR = 2; // FIXME: DO BETTER


public:
    /**
     * @brief Construct a Codegen Visitor object
     *
     * @param p Property manager to use
     * @param moduleName LLVM Module name to use
     * @param f Compiler flags
     */
    CodegenModule(std::string moduleName, DisplayMode mode, int f = 0) : toStringMode(mode), errorHandler(BismuthErrorHandler(CODEGEN))
    {
        flags = f;

        // LLVM Stuff
        auto context = new LLVMContext(); // TODO: free contexts?
        module = new Module(moduleName, *context);

        // Use the NoFolder to turn off constant folding
        builder = new IRBuilder<NoFolder>(module->getContext());

        // LLVM Types
        UnitTy = Types::UNIT->getLLVMType(module);//llvm::Type::getVoidTy(module->getContext());
        Int32Ty = llvm::Type::getInt32Ty(module->getContext());
        Int64Ty = llvm::Type::getInt64Ty(module->getContext());
        Int1Ty = llvm::Type::getInt1Ty(module->getContext());
        Int8Ty = llvm::Type::getInt8Ty(module->getContext());
        Int32Zero = ConstantInt::get(Int32Ty, 0, true);
        Int32One = ConstantInt::get(Int32Ty, 1, true);
        i8p = llvm::Type::getInt8Ty(module->getContext())->getPointerTo();
        Int8PtrPtrTy = i8p->getPointerTo();
    }

    CodegenModule(Module *m, DisplayMode mode, int f, BismuthErrorHandler e) : toStringMode(mode), errorHandler(e)
    {
        flags = f;

        // LLVM Stuff
        module = m;

        // Use the NoFolder to turn off constant folding
        builder = new IRBuilder<NoFolder>(module->getContext());

        // LLVM Types
        UnitTy = Types::UNIT->getLLVMType(module);//llvm::Type::getVoidTy(module->getContext());
        Int32Ty = llvm::Type::getInt32Ty(module->getContext());
        Int64Ty = llvm::Type::getInt64Ty(module->getContext());
        Int1Ty = llvm::Type::getInt1Ty(module->getContext());
        Int8Ty = llvm::Type::getInt8Ty(module->getContext());
        Int32Zero = ConstantInt::get(Int32Ty, 0, true);
        Int32One = ConstantInt::get(Int32Ty, 1, true);
        i8p = llvm::Type::getInt8Ty(module->getContext())->getPointerTo();
        Int8PtrPtrTy = i8p->getPointerTo();
    }

    bool hasErrors(int flags) { return errorHandler.hasErrors(flags); }
    std::string getErrors() { return errorHandler.errorList(); }

    llvm::StructType * channelRtTy() {
        llvm::StructType *ty = llvm::StructType::getTypeByName(module->getContext(), "_Channel");
        if (ty)
            return ty;

        return llvm::StructType::create(module->getContext(), "_Channel");
    }

    llvm::PointerType * channelRtPtrTy() 
    {
        return channelRtTy()->getPointerTo(); 
    }


    // These should automatically have GlobalValue::ExternalLinkage per inspecting source code...
    llvm::FunctionCallee getWriteProjection()
    {
        return module->getOrInsertFunction("_WriteProjection",
                                           llvm::FunctionType::get(
                                               UnitTy,
                                               {channelRtPtrTy(),
                                                Int32Ty},
                                               false));
    }

    llvm::FunctionCallee getReadLinearProjection()
    {
        return module->getOrInsertFunction("_ReadLinearProjection",
                                           llvm::FunctionType::get(
                                               Int32Ty,
                                               {channelRtPtrTy()},
                                               false));
    }

    llvm::FunctionCallee getReadLossyProjection()
    {
        return module->getOrInsertFunction("_ReadLossyProjection",
                                           llvm::FunctionType::get(
                                               Int32Ty,
                                               {channelRtPtrTy()},
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
                UnitTy,
                {i8p},
                false));
    }

    llvm::FunctionCallee getGCMalloc()
    {
        return module->getOrInsertFunction(
            "GC_malloc",
            llvm::FunctionType::get(
                i8p,
                {Int64Ty},
                false));
    }

    // Allocates on the heap, returns 
    // a pointer casted to the specified type. 
    llvm::Value * TypedGCHeapAlloc(
        llvm::Value * allocArg, 
        llvm::Type * castTy
    ){
        Value *allocated = builder->CreateCall(
            getGCMalloc(), 
            {
                allocArg
            }
        );


        return builder->CreateBitCast(allocated, castTy);
    }

    llvm::FunctionCallee getWeakenChannel()
    {
        return module->getOrInsertFunction(
            "_WeakenChannel",
            llvm::FunctionType::get(
                UnitTy,
                {channelRtPtrTy()},
                false));
    }

    llvm::FunctionCallee getWriteChannel()
    {
        return module->getOrInsertFunction(
            "_WriteChannel",
            llvm::FunctionType::get(
                UnitTy,
                {channelRtPtrTy(),
                 i8p},
                false));
    }

    llvm::FunctionCallee getReadLinearChannel()
    {
        return module->getOrInsertFunction(
            "_ReadLinearChannel",
            llvm::FunctionType::get(
                i8p,
                {channelRtPtrTy()},
                false));
    }

    llvm::FunctionCallee getReadLossyChannel()
    {
        return module->getOrInsertFunction(
            "_ReadLossyChannel",
            llvm::FunctionType::get(
                i8p,
                {channelRtPtrTy()},
                false));
    }

    llvm::FunctionCallee getExecute()
    {
        return module->getOrInsertFunction(
            "_Execute",
            llvm::FunctionType::get(
                channelRtPtrTy(),
                {llvm::FunctionType::get(
                     UnitTy,
                     {channelRtPtrTy()},
                     false)
                     ->getPointerTo()},
                false));
    }

    llvm::FunctionCallee getShouldLinearLoop()
    {
        return module->getOrInsertFunction(
            "_ShouldLinearLoop",
            llvm::FunctionType::get(
                Int1Ty,
                {channelRtPtrTy()},
                false));
    }

    llvm::FunctionCallee getShouldLossyLoop()
    {
        return module->getOrInsertFunction(
            "_ShouldLossyLoop",
            llvm::FunctionType::get(
                Int1Ty,
                {channelRtPtrTy()},
                false));
    }

    llvm::FunctionCallee getShouldLinearAcceptWhileLoop()
    {
        return module->getOrInsertFunction(
            "_ShouldLinearAcceptWhileLoop",
            llvm::FunctionType::get(
                Int1Ty,
                {channelRtPtrTy()},
                false));
    }

    llvm::FunctionCallee getShouldLossyAcceptWhileLoop()
    {
        return module->getOrInsertFunction(
            "_ShouldLossyAcceptWhileLoop",
            llvm::FunctionType::get(
                Int1Ty,
                {channelRtPtrTy()},
                false));
    }

    llvm::FunctionCallee get_OC_isPresentLinear()
    {
        return module->getOrInsertFunction(
            "_OC_isPresent",
            llvm::FunctionType::get(
                Int1Ty,
                {channelRtPtrTy()},
                false));
    }

    llvm::FunctionCallee get_OC_isPresentLossy()
    {
        return module->getOrInsertFunction(
            "_OC_isPresentLossy",
            llvm::FunctionType::get(
                Int1Ty,
                {channelRtPtrTy()},
                false));
    }

    llvm::FunctionCallee getContractChannel()
    {
        return module->getOrInsertFunction(
            "_ContractChannel",
            llvm::FunctionType::get(
                UnitTy,
                {channelRtPtrTy()},
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

    llvm::FunctionCallee get_arrayToChannel()
    {
        return module->getOrInsertFunction(
            "_ArrayToChannel",
            llvm::FunctionType::get(
                channelRtPtrTy(),
                {Int8PtrPtrTy, Int32Ty},
                false));
    }
    
    llvm::Value *getNewAddressMap()
    {
        return builder->CreateCall(get_address_map_create(), {});
    }

    llvm::Value *getUnitValue() {
        return Constant::getNullValue(Types::UNIT->getLLVMType(module));
    }

    void deleteAddressMap(llvm::Value *val)
    {
        builder->CreateCall(
            module->getOrInsertFunction(
                "_address_map_delete",
                llvm::FunctionType::get(
                    UnitTy,
                    {i8p},
                    false)),
            val);
    }

    FunctionCallee get_address_map_has()
    {
        return module->getOrInsertFunction(
            "_address_map_has",
            FunctionType::get(
                i8p,
                {i8p, i8p},
                false));
    }

    FunctionCallee get_address_map_put()
    {
        return module->getOrInsertFunction(
            "_address_map_put",
            FunctionType::get(
                UnitTy,
                {i8p,
                 i8p,
                 i8p},
                false));
    }

    llvm::FunctionCallee getCancelChannel()
    {
        return module->getOrInsertFunction(
            "_PreemptChannel",
            llvm::FunctionType::get(
                UnitTy,
                {channelRtPtrTy(), Int32Ty},
                false));
    }


    // https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl07.html#adjusting-existing-variables-for-mutation
    llvm::AllocaInst *CreateEntryBlockAlloc(llvm::Type *ty, std::string identifier)
    {
        llvm::Function *fn = builder->GetInsertBlock()->getParent();
        // fn->front(); // Do this?
        IRBuilder<> tempBuilder(&fn->getEntryBlock(), fn->getEntryBlock().begin());
        return tempBuilder.CreateAlloca(ty, 0, identifier);
    }


    /******************************
     * 
     * Dynamic Arrays Section
     * 
     ******************************/

    // llvm::AllocaInst * CreateDynArrayAlloc(TypeDynArray * array, std::string identifier)
    // {

    // }
    
    void InitDynArray(llvm::AllocaInst * alloc, uint32_t len); //ConstantInt * len);

    void ReallocateDynArray(llvm::Value * alloc, llvm::Value * newLen32); 


private:
    DisplayMode toStringMode; 

public:
    DisplayMode getToStringMode() { return toStringMode; }

protected: 
    llvm::TypeSize getSizeForType(llvm::Type *type)
    {
        return module->getDataLayout().getTypeAllocSize(type);
    }

    llvm::TypeSize getSizeForValue(Value *val)
    {
        return getSizeForType(val->getType());
    }

protected:
    int flags; 

    BismuthErrorHandler errorHandler;

    // LLVM
    // LLVMContext *context;
    Module *module;
    IRBuilder<NoFolder> *builder;

    // Commonly used types
    llvm::Type *UnitTy;
    llvm::Type *Int1Ty;
    llvm::IntegerType *Int8Ty;
    llvm::IntegerType *Int32Ty; // Things like 32 bit integers
    llvm::IntegerType *Int64Ty;
    llvm::Type *i8p;
    llvm::Type *Int8PtrPtrTy;
    Constant *Int32Zero;
    Constant *Int32One;

protected:
    llvm::ConstantInt * getI32(int32_t value) { return ConstantInt::get(Int32Ty, value, true); }
    llvm::ConstantInt * getU32(uint32_t value) { return ConstantInt::get(Int32Ty, value, false); }
    llvm::ConstantInt * getI64(int64_t value) { return ConstantInt::get(Int64Ty, value, true); }
    llvm::ConstantInt * getU64(uint64_t value) { return ConstantInt::get(Int64Ty, value, false); }
};
