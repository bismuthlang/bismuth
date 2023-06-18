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
using llvm::SwitchInst; 

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

    // TODO: REFACTOR W IMPL IN CODEGEN VISITOR
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

    // FIXME: DONT DUPLICATE THESE ACROSS FILES
    optional<Value *> deepCopyHelper(IRBuilder<NoFolder> *builder, const Type *type, Value *stoVal, Value *addrMap, DeepCopyType copyType)
    {
        if (type->isLinear())
        {
            errorHandler->addError(nullptr, "Cannot make a copy of a linear type: " + type->toString());
            return std::nullopt;
        }

        if (!type->requiresDeepCopy())
        {
            // Value *v = (copyType == GC_MALLOC) ? runGCMalloc(builder, getSizeForValue(stoVal))
            //                                    : runMalloc(builder, getSizeForValue(stoVal));
            // Value *casted = builder->CreateBitCast(v, stoVal->getType()->getPointerTo());
            // builder->CreateStore(stoVal, casted);
            // // return casted;
            // return builder->CreateLoad(stoVal->getType(), casted);
            return stoVal;//builder->CreateLoad(stoVal->getType(), stoVal);
        }

        if(const TypeInfer * infType = dynamic_cast<const TypeInfer *>(type))
        {
            if(infType->hasBeenInferred()) {
                return  deepCopyHelper(builder, infType->getValueType().value(), stoVal, addrMap, GC_MALLOC);
            }
            return std::nullopt; //FIXME: ADD ERROR 
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
            Value * loaded_i8p_v = builder->CreateBitCast(builder->CreateLoad(llvmType, v), i8p);
            const Type *innerType = boxType->getInnerType();

            Value *hasValPtr = builder->CreateCall(
                get_address_map_has(),
                {builder->CreateLoad(i8p, m),
                 loaded_i8p_v}); // NEEDS TO BE LOADED

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
            optional<Value *> clonedOpt = deepCopyHelper(builder, 
                                                         innerType, 
                                                         builder->CreateLoad(innerType->getLLVMType(module), builder->CreateLoad(llvmType, v)), 
                                                         builder->CreateLoad(i8p, m), 
                                                         GC_MALLOC);
            if (!clonedOpt)
                return std::nullopt;
            // Value *cloned = clonedOpt.value();
            Value *alloc = runGCMalloc(builder, getSizeForType(type->getLLVMType(module)));
            Value *casted2 = builder->CreateBitCast(alloc, type->getLLVMType(module));
            builder->CreateStore(clonedOpt.value(), casted2);
            builder->CreateCall(
                get_address_map_put(),
                {builder->CreateLoad(i8p, m),
                 loaded_i8p_v,
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
        else if (const TypeStruct *structType = dynamic_cast<const TypeStruct *>(type))
        {
            for (auto eleItr : structType->getElements())
            {
                const Type *localTy = eleItr.second;

                if (localTy->requiresDeepCopy())
                {
                    Value *memLoc = builder->CreateGEP(v, {Int32Zero,
                                                           ConstantInt::get(Int32Ty,
                                                                            structType->getElementIndex(eleItr.first).value(), // In theory, bad opt access, but should never happen
                                                                            true)});
                    Value *loaded = builder->CreateLoad(eleItr.second->getLLVMType(module), memLoc);

                    optional<Value *> valOpt = deepCopyHelper(builder, eleItr.second, loaded, builder->CreateLoad(i8p, m), GC_MALLOC);
                    if (!valOpt)
                        return std::nullopt;
                    builder->CreateStore(valOpt.value(), memLoc);
                }
            }
            v = builder->CreateLoad(llvmType, v);
        }
        else if (const TypeSum *sumType = dynamic_cast<const TypeSum *>(type))
        {
            auto origParent = builder->GetInsertBlock()->getParent();

            BasicBlock *mergeBlk = BasicBlock::Create(module->getContext(), "matchcont");

            Value *memLoc = builder->CreateGEP(v, {Int32Zero, Int32One});
            Value *tagPtr = builder->CreateGEP(v, {Int32Zero, Int32Zero});
            Value *tag = builder->CreateLoad(tagPtr->getType()->getPointerElementType(), tagPtr);
            SwitchInst *switchInst = builder->CreateSwitch(tag, mergeBlk, sumType->getCases().size());

            unsigned int index = 0;
            for(const Type * caseNode : sumType->getCases())
            {
                index = index + 1;
                BasicBlock *matchBlk = BasicBlock::Create(module->getContext(), "tagBranch" + std::to_string(index));
                builder->SetInsertPoint(matchBlk);
                
                switchInst->addCase(ConstantInt::get(Int32Ty, index, true), matchBlk);
                origParent->getBasicBlockList().push_back(matchBlk);

                Value *corrected = builder->CreateBitCast(memLoc, caseNode->getLLVMType(module)->getPointerTo());
                Value *loaded = builder->CreateLoad(caseNode->getLLVMType(module), corrected);

                optional<Value *> valOpt = deepCopyHelper(builder, caseNode, loaded, builder->CreateLoad(i8p, m), GC_MALLOC);
                    if (!valOpt)
                        return std::nullopt;
                                                                                                 // builder->CreateLoad(llvm::Type::getInt8PtrTy(M->getContext()), m)});
                builder->CreateStore(valOpt.value(), corrected);
                builder->CreateBr(mergeBlk);
            }

            origParent->getBasicBlockList().push_back(mergeBlk);
            builder->SetInsertPoint(mergeBlk);
            v = builder->CreateLoad(llvmType, v);
        }
        else if(const TypeArray * arrayType = dynamic_cast<const TypeArray*>(type))
        {
            const Type * valueType = arrayType->getValueType(); 
            
            AllocaInst *loop_index = CreateEntryBlockAlloc(builder,Int32Ty, "idx");
            AllocaInst *loop_len = CreateEntryBlockAlloc(builder, Int32Ty, "len");
            builder->CreateStore(Int32Zero, loop_index);
            builder->CreateStore(ConstantInt::get(Int32Ty, arrayType->getLength(), true), loop_len);

            auto parent = builder->GetInsertBlock()->getParent();
            BasicBlock *condBlk = BasicBlock::Create(module->getContext(), "loop-cond", parent);

            BasicBlock *loopBlk = BasicBlock::Create(module->getContext(), "loop");
            BasicBlock *restBlk = BasicBlock::Create(module->getContext(), "rest");

            builder->CreateBr(condBlk);
            builder->SetInsertPoint(condBlk);

            builder->CreateCondBr(builder->CreateICmpSLT(builder->CreateLoad(Int32Ty, loop_index), builder->CreateLoad(Int32Ty, loop_len)), loopBlk, restBlk);
            condBlk = builder->GetInsertBlock();

            parent->getBasicBlockList().push_back(loopBlk);
            builder->SetInsertPoint(loopBlk);

            /******************Loop Body********************/
            /**     Note: This may Have to be improved depending on **/
            /**           how inheritance & such ends up working.   **/
            /**/
            /**/
            {
                Value *memLoc = builder->CreateGEP(v, {Int32Zero,
                                                              builder->CreateLoad(Int32Ty, loop_index)});

                Value *loaded = builder->CreateLoad(valueType->getLLVMType(module), memLoc);

                optional<Value *> valOpt = deepCopyHelper(builder, valueType, loaded, builder->CreateLoad(i8p, m), GC_MALLOC);
                    if (!valOpt)
                        return std::nullopt;
                builder->CreateStore(valOpt.value(), memLoc);
            }

            /**/
            /**/
            /***********************************************/
            builder->CreateStore(
                builder->CreateNSWAdd(builder->CreateLoad(Int32Ty, loop_index),
                                      Int32One),
                loop_index);
            builder->CreateBr(condBlk);
            loopBlk = builder->GetInsertBlock();

            parent->getBasicBlockList().push_back(restBlk);
            builder->SetInsertPoint(restBlk);
            v = builder->CreateLoad(llvmType, v);

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
