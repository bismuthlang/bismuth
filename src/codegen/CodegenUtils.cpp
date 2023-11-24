#include "CodegenUtils.h"


void CodegenModule::InitDynArray(llvm::AllocaInst * alloc, ConstantInt * len32)
{
    unsigned int GROW_FACTOR = 2; // FIXME: DO BETTER

    // Value * len64 = builder->CreateSExtOrBitCast(len32, Int64Ty);//CreateIntCast(len, Int64Ty);

    Value * capacity = builder->CreateNSWMul(len32, builder->getInt32(GROW_FACTOR));

    // FIXME: DYN ARRAYS DONT CURRENTLY WORK WITH COPY!

    // Allocate the vector 
    {
        // FIXME: MAKE A GCMALLOC + CAST ALL IN ONE!

        Value *vecPtr = builder->CreateGEP(alloc, {Int32Zero, Int32Zero});

        llvm::Type * storeType =  alloc->getAllocatedType()->getStructElementType(0)->getPointerElementType();
        Value *allocated = builder->CreateCall(
            getGCMalloc(), 
            {
                builder->CreateNSWMul(
                    builder->CreateSExtOrBitCast(capacity, Int64Ty), 
                    builder->getInt64(
                        module->getDataLayout().getTypeAllocSize( // TODO: Move DeepCopyVisitor::getSizeForType to here!
                           storeType
                        )
                    )
                )
            }
        );


        Value *casted = builder->CreateBitCast(allocated, storeType->getPointerTo());

        builder->CreateStore(casted, vecPtr);
    }

    Value *lenPtr = builder->CreateGEP(alloc, {Int32Zero, Int32One});
    {
        builder->CreateStore(
            len32, 
            lenPtr
        );

    }

    Value *capPtr = builder->CreateGEP(alloc, {Int32Zero, ConstantInt::get(Int32Ty, 2, true)});
    {
        builder->CreateStore(
            capacity, 
            capPtr
        );
    }
}

void CodegenModule::ReallocateDynArray(llvm::AllocaInst * alloc, ConstantInt * newCapacity)
{
    unsigned int GROW_FACTOR = 2; // FIXME: DO BETTER

    Value *lenPtr = builder->CreateGEP(alloc, {Int32Zero, Int32One});
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

    Value * vecPtr = builder->CreateGEP(alloc, {Int32Zero, Int32Zero});
    Value * loadedArray = builder->CreateLoad(vecPtr, vecPtr->getType()->getPointerElementType());
    // Value * indexPtr = builder->CreateGEP(loadedArray, indexValue);

    Value *newData = builder->CreateCall(
        getGCMalloc(), 
        {
            builder->CreateNSWMul(
                builder->CreateSExtOrBitCast(newCapacity, Int64Ty), 
                builder->getInt64(
                    module->getDataLayout().getTypeAllocSize( // TODO: Move DeepCopyVisitor::getSizeForType to here!
                        loadedArray->getType()->getPointerElementType()
                    )
                )
            )
        }
    );

    {
        llvm::AllocaInst * loopValue = CreateEntryBlockAlloc(Int32Ty, "");
        builder->CreateStore(Int32Zero, loopValue);

        // TODO: Refactor with while loop! (AND MAYBE DEEP COPY VISITOR IMPL?)

        auto parent = builder->GetInsertBlock()->getParent();

        BasicBlock *loopBlk = BasicBlock::Create(module->getContext(), "loop", parent);
        BasicBlock *restBlk = BasicBlock::Create(module->getContext(), "rest");

        builder->CreateCondBr(
            builder->CreateICmpSLT(
                builder->CreateLoad(Int32Ty, loopValue), 
                origLen
            )
            , loopBlk, restBlk);

        /*
        * In the loop block
        */
        builder->SetInsertPoint(loopBlk);

        builder->CreateStore(
            builder->CreateLoad(
                builder->CreateGEP(loadedArray, loopValue)
            ), 
            builder->CreateGEP(newData, loopValue)
        );

        builder->CreateStore(
            builder->CreateNSWAdd(
                builder->CreateLoad(loopValue),
                Int32One
            ),
            loopValue
        );

        // Re-calculate the loop condition

        // Check if we need to loop back again...
        builder->CreateCondBr(
            builder->CreateICmpSLT(
                builder->CreateLoad(Int32Ty, loopValue), 
                origLen
            ),
            loopBlk, restBlk);
        loopBlk = builder->GetInsertBlock();

        /*
        * Out of loop
        */
        parent->getBasicBlockList().push_back(restBlk);
        builder->SetInsertPoint(restBlk);


        builder->CreateStore(
            newData, 
            vecPtr
        ); 
        Value *capPtr = builder->CreateGEP(alloc, {Int32Zero, ConstantInt::get(Int32Ty, 2, true)});

        builder->CreateStore(newCapacity, capPtr);

    }



    // If the block ends in a return, then we can't make the branch; things would break
    builder->CreateBr(elseBlk);

    thenBlk = builder->GetInsertBlock();

    /*
     * Insert the else block (same as rest if no else branch)
     */
    parentFn->getBasicBlockList().push_back(elseBlk);
    builder->SetInsertPoint(elseBlk);

}