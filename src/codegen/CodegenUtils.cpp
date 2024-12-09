#include "CodegenUtils.h"


void CodegenModule::InitDynArray(llvm::AllocaInst * alloc, uint32_t len)// ConstantInt * len32)
{
    // Value * len64 = builder->CreateSExtOrBitCast(len32, Int64Ty);//CreateIntCast(len, Int64Ty);

    // builder->CreateMaxNum(len32, )
    Value * len32 = getU32(len); 
    // TODO: DO GROWTH FACTOR BETTER
    Value * capacity = getU32(len == 0 ? 10 : (2 * len)); //builder->CreateNSWMul(len32, getU32(DYN_ARRAY_GROW_FACTOR));

    // FIXME: DYN ARRAYS DONT CURRENTLY WORK WITH COPY!

    // Allocate the vector 
    {
        llvm::Type * storeType =  alloc->getAllocatedType()->getStructElementType(0)->getArrayElementType();
        builder->CreateStore(
            TypedGCHeapAlloc(
                builder->CreateNSWMul(
                    builder->CreateSExtOrBitCast(capacity, Int64Ty), 
                    builder->getInt64(
                        getSizeForType(storeType)
                    )
                ),
                storeType->getPointerTo()
            ),
            builder->CreateGEP(nullptr, alloc, {Int32Zero, Int32Zero})
        );
    }

    Value *lenPtr = builder->CreateGEP(nullptr, alloc, {Int32Zero, Int32One});
    {
        builder->CreateStore(
            len32, 
            lenPtr
        );

    }

    Value *capPtr = builder->CreateGEP(nullptr, alloc, {Int32Zero, getU32(DYN_ARRAY_GROW_FACTOR)});
    {
        builder->CreateStore(
            capacity, 
            capPtr
        );
    }
}

void CodegenModule::ReallocateDynArray(llvm::Value * alloc, llvm::Value * newCapacity)
{
    // PLAN: use DYN_ARRAY_GROW_FACTOR

    Value *lenPtr = builder->CreateGEP(nullptr, alloc, {Int32Zero, Int32One});
    Value * origLen = builder->CreateLoad(Int32Ty, lenPtr); 

    // PLAN: REFACTOR W/ CONDITIONAL
    // PLAN: CHANGE STUFF TO UNSIGNED? 
    // Get the condition that the if statement is for
    Value * cond = builder->CreateICmpSGE(
        newCapacity, 
        origLen
    );
    

    /*
     * Generate the basic blocks for then, else, and the remaining code.
     * (NOTE: We set rest to be else if there is no else branch).
     */
    auto parentFn = builder->GetInsertBlock()->getParent();

    BasicBlock *thenBlk = BasicBlock::Create(module->getContext(), "then", parentFn);
    BasicBlock *elseBlk = BasicBlock::Create(module->getContext(), "else");
    builder->CreateCondBr(cond, thenBlk, elseBlk);

    /*
     * Then block
     */
    builder->SetInsertPoint(thenBlk);

    Value * vecPtr = builder->CreateGEP(nullptr, alloc, {Int32Zero, Int32Zero});
    Value * loadedArray = builder->CreateLoad(vecPtr->getType()->getArrayElementType(), vecPtr);
    // Value * indexPtr = builder->CreateGEP(nullptr, loadedArray, indexValue);

    // Value *newData_i8ptr = builder->CreateCall(
    //     getG_CMalloc(), 
    //     {
    //         builder->CreateNSWMul(
    //             builder->CreateSExtOrBitCast(newCapacity, Int64Ty), 
    //             builder->getInt64(
    //                 getSizeForType(loadedArray->getType()->getArrayElementType())
    //             )
    //         )
    //     }
    // );

    // Value * newData = builder->CreateBitCast(newData_i8ptr, loadedArray->getType());
    Value * newData = TypedGCHeapAlloc(
        builder->CreateNSWMul(
            builder->CreateSExtOrBitCast(newCapacity, Int64Ty), 
            builder->getInt64(
                getSizeForType(loadedArray->getType()->getArrayElementType())
            )
        ),
        loadedArray->getType()
    ); 


    {
        llvm::AllocaInst * loopValuePtr = CreateEntryBlockAlloc(Int32Ty, "");
        builder->CreateStore(Int32Zero, loopValuePtr);

        
        // TODO: Refactor with while loop! (AND MAYBE DEEP COPY VISITOR IMPL?)

        auto parent = builder->GetInsertBlock()->getParent();

        BasicBlock *loopBlk = BasicBlock::Create(module->getContext(), "loop", parent);
        BasicBlock *restBlk = BasicBlock::Create(module->getContext(), "rest");

        builder->CreateCondBr(
            builder->CreateICmpSLT(
                builder->CreateLoad(Int32Ty, loopValuePtr), 
                origLen
            )
            , loopBlk, restBlk);

        //
        // In the loop block
        //
        builder->SetInsertPoint(loopBlk);

        Value * loopValueLoaded = builder->CreateLoad(Int32Ty, loopValuePtr); 
        
        builder->CreateStore(
            builder->CreateLoad(
                vecPtr->getType()->getArrayElementType(),
                builder->CreateGEP(nullptr, loadedArray, loopValueLoaded)
            ), 
            builder->CreateGEP(nullptr, newData, loopValueLoaded)
        );
        
        builder->CreateStore(
            builder->CreateNSWAdd(
                loopValueLoaded,
                Int32One
            ),
            loopValuePtr
        );

        // Re-calculate the loop condition

        // Check if we need to loop back again...
        builder->CreateCondBr(
            builder->CreateICmpSLT(
                builder->CreateLoad(Int32Ty, loopValuePtr), 
                origLen
            ),
            loopBlk, restBlk);
        loopBlk = builder->GetInsertBlock();

        //
        // Out of loop
        //
        parent->insert(parent->end(), restBlk);
        builder->SetInsertPoint(restBlk);
        

        builder->CreateStore(
            newData, 
            vecPtr
        ); 
        Value *capPtr = builder->CreateGEP(nullptr, alloc, {Int32Zero, getU32(DYN_ARRAY_GROW_FACTOR)});

        builder->CreateStore(newCapacity, capPtr);

    }
    



    // If the block ends in a return, then we can't make the branch; things would break
    builder->CreateBr(elseBlk);

    thenBlk = builder->GetInsertBlock();

    /*
     * Insert the else block (same as rest if no else branch)
     */
    parentFn->insert(parentFn->end(), elseBlk);
    builder->SetInsertPoint(elseBlk);

}