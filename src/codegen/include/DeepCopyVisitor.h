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

#include "BismuthErrorHandler.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/NoFolder.h"

// #include "CastUtils.h"
#include "Type.h"

// #include <any>
#include <string>

#include <variant>
#include <optional>

// #include "TypedAST.h"

// using namespace llvm;
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

using std::optional;

class DeepCopyVisitor
{

    enum DeepCopyType
    {
        GC_MALLOC,
        MIXED_MALLOC, // Uses Malloc at top level, then GC MALLOC
        NORM_MALLOC,
    };

public:
    DeepCopyVisitor(Module *m, BismuthErrorHandler *e)
    {
        module = m;
        errorHandler = e;

        // Use the NoFolder to turn off constant folding
        // builder = new IRBuilder<NoFolder>(module->getContext());

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

    /******************************************************************
     * Standard visitor methods all defined to use the typed versions
     ******************************************************************/
    // std::optional<Value *> visit(TSelectAlternativeNode *n) override;

    // These should automatically have GlobalValue::ExternalLinkage per inspecting source code...
    llvm::FunctionCallee getMalloc()
    {
        return module->getOrInsertFunction(
            "malloc",
            FunctionType::get(
                i8p,
                {Int32Ty},
                false));
    }

    Value *runMalloc(IRBuilder<NoFolder> *builder, llvm::TypeSize size)
    {
        return builder->CreateCall(
            getMalloc(),
            {builder->getInt32(size)});
    }

    llvm::FunctionCallee getFree()
    {
        return module->getOrInsertFunction(
            "free",
            FunctionType::get(
                VoidTy,
                {i8p},
                false));
    }

    llvm::FunctionCallee getGCMalloc()
    {
        // return module->getOrInsertFunction(
        //     "malloc",
        //     FunctionType::get(
        //         i8p,
        //         {Int32Ty},
        //         false));

        return module->getOrInsertFunction(
            "GC_malloc",
            FunctionType::get(
                i8p,
                {Int64Ty},
                false));
    }

    Value *runGCMalloc(IRBuilder<NoFolder> *builder, llvm::TypeSize size)
    {
        return builder->CreateCall(
            getGCMalloc(),
            {builder->getInt64(size)});
        // return runMalloc(builder, size);
    }

    llvm::FunctionCallee get_address_map_create()
    {
        return module->getOrInsertFunction(
            "_address_map_create",
            FunctionType::get(
                i8p,
                {},
                false));
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
                    VoidTy,
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
                VoidTy,
                {i8p,
                 i8p,
                 i8p},
                false));
    }

    // https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl07.html#adjusting-existing-variables-for-mutation
    llvm::AllocaInst *CreateEntryBlockAlloc(IRBuilder<NoFolder> *builder, llvm::Type *ty, std::string identifier)
    {
        llvm::Function *fn = builder->GetInsertBlock()->getParent();
        // // for(auto B = fn->begin(), e = fn->end(); B != e; ++B)
        // for(auto& B : *fn)
        // {
        //     // for(llvm::BasicBlock::iterator it = B->begin(); it != B->end(); ++it)
        //     for(auto& I : B)
        //     {
        //         // llvm::Instruction * I = &*it;

        //         std::cout << "----\n" << I.getOpcodeName() << "\n";
        //         I.print(llvm::outs(), true);
        //         std::cout << "\n----\n\n";
        //     }
        // }

        // if (fn != nullptr)
        // {
        // if (llvm::isa<llvm::Function>(insPoint))
        // {
        // llvm::Function *fn = static_cast<llvm::Function *>(insPoint);
        IRBuilder<> tempBuilder(&fn->getEntryBlock(), fn->getEntryBlock().begin());
        return tempBuilder.CreateAlloca(ty, 0, identifier);
        // }

        // insPoint = insPoint->getParent();
        // }
        // return std::nullopt;
    }

    optional<Value *> deepCopy(IRBuilder<NoFolder> *builder, const Type *type, Value *to_copy)
    {
        Value *addrMap = getNewAddressMap(builder);
        optional<Value *> ans = deepCopyHelper(builder, type, to_copy, addrMap, MIXED_MALLOC);
        deleteAddressMap(builder, addrMap);
        return ans;
    }

private:
    BismuthErrorHandler *errorHandler;

    // LLVM
    Module *module;
    // IRBuilder<NoFolder> *builder;

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

    llvm::TypeSize getSizeForType(llvm::Type *type)
    {
        return module->getDataLayout().getTypeAllocSize(type);
    }

    llvm::TypeSize getSizeForValue(Value *val)
    {
        return getSizeForType(val->getType());
    }

    optional<Value *> deepCopyHelper(IRBuilder<NoFolder> *builder, const Type *type, Value *stoVal, Value *addrMap, DeepCopyType copyType)
    {
        if (isLinear(type))
        {
            errorHandler->addError(nullptr, "Cannot make a copy of a linear type: " + type->toString());
            return std::nullopt;
        }

        if (!type->requiresDeepCopy())
        { 
            Value *v = (copyType == GC_MALLOC) ? runGCMalloc(builder, getSizeForValue(stoVal))
                                               : runMalloc(builder, getSizeForValue(stoVal));
            Value *casted = builder->CreateBitCast(v, stoVal->getType()->getPointerTo());
            builder->CreateStore(stoVal, casted);
            // return casted;
            return builder->CreateLoad(stoVal->getType(), casted);
        }

        Function *testFn = module->getFunction("_clone_" + type->toString());
        if (testFn)
        {
            return builder->CreateCall(testFn, {stoVal, addrMap});
        }

        BasicBlock *ins = builder->GetInsertBlock();

        llvm::Type *llvmType = type->getLLVMType(module);

        Function *fn = Function::Create(FunctionType::get(
                                            llvmType,
                                            {
                                                llvmType, // Value
                                                i8p,      // Map
                                            },
                                            false),
                                        GlobalValue::PrivateLinkage, "_clone_" + type->toString(), module);
        BasicBlock *bBlk = BasicBlock::Create(module->getContext(), "entry", fn);
        builder->SetInsertPoint(bBlk);

        Value *v = CreateEntryBlockAlloc(builder, llvmType, "v");
        builder->CreateStore((fn->args()).begin(), v);
        // Value *loaded = builder->CreateLoad(llvmType, v);

        AllocaInst *m = CreateEntryBlockAlloc(builder, i8p, "m");
        builder->CreateStore(fn->getArg(1), m);

        if (const TypeBox *boxType = dynamic_cast<const TypeBox *>(type))
        {
            const Type *innerType = boxType->getInnerType();

            Value *hasValPtr = builder->CreateCall(
                get_address_map_has(),
                {builder->CreateLoad(i8p, m),
                 builder->CreateBitCast(v, i8p)});

            auto parentFn = builder->GetInsertBlock()->getParent();
            BasicBlock *thenBlk = BasicBlock::Create(module->getContext(), "then", parentFn);
            BasicBlock *elseBlk = BasicBlock::Create(module->getContext(), "else");
            BasicBlock *restBlk = BasicBlock::Create(module->getContext(), "ifcont");

            builder->CreateCondBr(
                builder->CreateZExtOrTrunc(
                    builder->CreateICmpNE(
                        hasValPtr,
                        llvm::Constant::getNullValue(hasValPtr->getType())),
                    Int1Ty),
                thenBlk,
                elseBlk);

            /*
             * Then block
             */
            builder->SetInsertPoint(thenBlk);
            Value *casted = builder->CreateBitCast(hasValPtr, type->getLLVMType(module));

            builder->CreateBr(restBlk);

            thenBlk = builder->GetInsertBlock();

            /*
             * Insert the else block (same as rest if no else branch)
             */
            parentFn->getBasicBlockList().push_back(elseBlk);
            builder->SetInsertPoint(elseBlk);

            // // Generate the code for the else block; follows the same logic as the then block.
            optional<Value *> clonedOpt = deepCopyHelper(builder, innerType, builder->CreateLoad(innerType->getLLVMType(module), builder->CreateLoad(llvmType, v)), builder->CreateLoad(i8p, m), GC_MALLOC);
            if (!clonedOpt)
                return std::nullopt;
            // Value *cloned = clonedOpt.value();
            Value *alloc = runGCMalloc(builder, getSizeForType(type->getLLVMType(module)));
            Value *casted2 = builder->CreateBitCast(alloc, type->getLLVMType(module));
            builder->CreateStore(clonedOpt.value(), casted2);
            builder->CreateCall(
                get_address_map_put(),
                {builder->CreateLoad(i8p, m),
                 builder->CreateBitCast(v, i8p),
                 alloc});

            builder->CreateBr(restBlk);

            elseBlk = builder->GetInsertBlock();

            // As we have an else block, rest and else are different, so we have to merge back in.
            parentFn->getBasicBlockList().push_back(restBlk);
            builder->SetInsertPoint(restBlk);

            llvm::PHINode *phi = builder->CreatePHI(type->getLLVMType(module), 2, "phi");
            phi->addIncoming(casted, thenBlk);
            phi->addIncoming(casted2, elseBlk);
            v = phi;
        }
        else if(const TypeStruct * structType = dynamic_cast<const TypeStruct*>(type))
        {
            
        }
        else
        {
            builder->CreateRet(v);
            builder->SetInsertPoint(ins);
            errorHandler->addError(nullptr, "Compiler Error (Please report this bug!): I don't know how to copy the following type: " + type->toString());
            return std::nullopt;
        }

        builder->CreateRet(v);
        builder->SetInsertPoint(ins);
        return builder->CreateCall(fn, {stoVal, addrMap});

        // Value * alloc = runGCMalloc(getSizeForType(llvmType));

        // Value *casted = builder->CreateBitCast(alloc, llvmType->getPointerTo());
        // builder->CreateStore(loaded, casted);
        // v = casted;
    }
};
