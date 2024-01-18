#include "CodegenVisitor.h"

std::optional<Value *> CodegenVisitor::visit(TCompilationUnitNode *n)
{
    /***********************************
     *
     *
     * Runtime Stuff
     *
     *
     ***********************************/

    /***********************************
     *
     *
     * Actual Code
     *
     *
     ***********************************/
    for (auto e : n->defs)
    {
        if (TProgramDefNode * octx = dynamic_cast<TProgramDefNode *>(e))
        {
            const TypeProgram *type = octx->getType();

            Function *fn = Function::Create(type->getLLVMFunctionType(module), GlobalValue::ExternalLinkage, getCodegenID(octx->getSymbol()), module);
            // type->setName(fn->getName().str());
        }
        else if (TLambdaConstNode *octx = dynamic_cast<TLambdaConstNode *>(e))
        {
            const TypeFunc *type = octx->getType();

            Function *fn = Function::Create(type->getLLVMFunctionType(module), GlobalValue::ExternalLinkage, getCodegenID(octx->getSymbol()), module);
            // type->setName(fn->getName().str());
        }
        else if (TDefineTemplateNode *octx = dynamic_cast<TDefineTemplateNode *>(e))
        {
            // FIXME: forward decl!
        }
    }

    for (auto e : n->externs)
    {
        AcceptType(this, e);
    }

    for (auto e : n->defs)
    {
        // Generate code for statement
        if (TProgramDefNode * a = dynamic_cast<TProgramDefNode *>(e))
        {
            AcceptType(this, a);
        }
        else if (TLambdaConstNode *a = dynamic_cast<TLambdaConstNode *>(e))
        {
            AcceptType(this, a);
        }
        else if (TDefineTemplateNode *a = dynamic_cast<TDefineTemplateNode *>(e))
        {
            AcceptType(this, a);
        }
    }

    /*******************************************
     * Extra checks depending on compiler flags
     *******************************************/

    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TMatchStatementNode *n)
{
    const TypeSum *sumType = n->matchType;

    auto origParent = builder->GetInsertBlock()->getParent();
    BasicBlock *mergeBlk = BasicBlock::Create(module->getContext(), "match-cont");

    // Attempt to cast the check; if this fails, then codegen for the check failed
    std::optional<Value *> optVal = AcceptType(this, n->checkExpr);

    // Check that the optional, in fact, has a value. Otherwise, something went wrong.
    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "207 - Failed to generate code for: " + n->checkExpr->toString());
        return std::nullopt;
    }

    Value *sumVal = optVal.value();

    llvm::AllocaInst *SumPtr = CreateEntryBlockAlloc(sumVal->getType(), "");
    builder->CreateStore(sumVal, SumPtr);

    Value *tagPtr = builder->CreateGEP(SumPtr, {Int32Zero, Int32Zero});

    Value *tag = builder->CreateLoad(tagPtr->getType()->getPointerElementType(), tagPtr);

    llvm::SwitchInst *switchInst = builder->CreateSwitch(tag, mergeBlk, n->cases.size()); // sumType->getCases().size());

    for (std::pair<Symbol *, TypedNode *> caseNode : n->cases)
    {
        Symbol *localSym = caseNode.first;

        llvm::Type *toFind = getLLVMType(localSym);

        unsigned int index = sumType->getIndex(module, toFind);

        if (index == 0)
        {
            errorHandler.addError(n->getStart(), "Unable to find key for type " + localSym->getType()->toString(getToStringMode()) + " in sum"); 
            return std::nullopt;
        }

        BasicBlock *matchBlk = BasicBlock::Create(module->getContext(), "tagBranch" + std::to_string(index));

        builder->SetInsertPoint(matchBlk);

        switchInst->addCase(getU32(index), matchBlk);
        origParent->getBasicBlockList().push_back(matchBlk);

        //  Get the type of the symbol // FIXME: WHY IS THIS SAME AS TOFIND?
        llvm::Type *ty = getLLVMType(localSym);

        // Can skip global stuff
        llvm::AllocaInst *v = CreateAndLinkEntryBlockAlloc(ty, localSym);

        // Now to store the var
        Value *valuePtr = builder->CreateGEP(SumPtr, {Int32Zero, Int32One});
        Value *corrected = builder->CreateBitCast(valuePtr, ty->getPointerTo());

        Value *val = builder->CreateLoad(ty, corrected);

        builder->CreateStore(val, v);

        // altCtx->eval->accept(this);
        AcceptType(this, caseNode.second);

        if (TBlockNode *blkStmtCtx = dynamic_cast<TBlockNode *>(caseNode.second))
        {
            if (!endsInReturn(blkStmtCtx))
            {
                builder->CreateBr(mergeBlk);
            }
            // if it ends in a return, we're good!
        }
        else if (TReturnNode *retCtx = dynamic_cast<TReturnNode *>(caseNode.second))
        {
            // Similarly, we don't need to generate the branch
        }
        else
        {
            builder->CreateBr(mergeBlk);
        }
    }

    origParent->getBasicBlockList().push_back(mergeBlk);
    builder->SetInsertPoint(mergeBlk);

    for (TypedNode *s : n->post)
    {
        AcceptType(this, s);
    }

    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TChannelCaseStatementNode *n)
{
    auto origParent = builder->GetInsertBlock()->getParent();
    BasicBlock *mergeBlk = BasicBlock::Create(module->getContext(), "match-cont");

    // Attempt to cast the check; if this fails, then codegen for the check failed
    Symbol *sym = n->sym;
    std::optional<llvm::AllocaInst *> optVal = getAllocation(sym);

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in case: " + getCodegenID(n->sym));
        return std::nullopt;
    }

    Value *chanVal = optVal.value();
    // ReadProjection
    Value *tag = builder->CreateCall(
        n->isInCloseable() ? 
            getReadLossyProjection() :  // Should be fine as will handle exact logic later
            getReadLinearProjection(),
        {builder->CreateLoad(channelRtPtrTy(), chanVal)});

    llvm::SwitchInst *switchInst = builder->CreateSwitch(tag, mergeBlk, n->cases.size());

    // for (std::pair<Symbol *, TypedNode *> caseNode : n->cases)
    for (unsigned int i = 0; i < n->cases.size(); i++)
    {
        // TODO: find a way to error handle cases where correct block DNE or something
        BasicBlock *matchBlk = BasicBlock::Create(module->getContext(), "tagBranch" + std::to_string(i + 1));

        builder->SetInsertPoint(matchBlk);

        switchInst->addCase(
            getU32(n->hasElseStatement && (i + 1) == n->cases.size() ? 
                    0 :  // FIXME: TEST THESE ELSE BLOCKS
                    i + 1
                ), 
            matchBlk);
        origParent->getBasicBlockList().push_back(matchBlk);

        // altCtx->eval->accept(this);
        TypedNode *caseNode = n->cases.at(i);

        AcceptType(this, caseNode);

        if (TBlockNode *blkStmtCtx = dynamic_cast<TBlockNode *>(caseNode))
        {
            if (!endsInReturn(blkStmtCtx))
            {
                builder->CreateBr(mergeBlk);
            }
            // if it ends in a return, we're good!
        }
        else if (TReturnNode *retCtx = dynamic_cast<TReturnNode *>(caseNode))
        {
            // Similarly, we don't need to generate the branch
        }
        else
        {
            builder->CreateBr(mergeBlk);
        }
    }

    origParent->getBasicBlockList().push_back(mergeBlk);
    builder->SetInsertPoint(mergeBlk);

    for (TypedNode *s : n->post)
    {
        AcceptType(this, s);
    }

    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TProgramProjectNode *n)
{
    Symbol *sym = n->sym;
    std::optional<llvm::AllocaInst *> optVal = getAllocation(sym);

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in case: " + getCodegenID(n->sym));
        return std::nullopt;
    }

    Value *chanVal = optVal.value();

    builder->CreateCall(getWriteProjection(), {builder->CreateLoad(channelRtPtrTy(), chanVal),
                                               getU32(n->projectIndex)});
    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TInvocationNode *n)
{
    vector<TypedNode *> argNodes = n->args;

    // Create the argument vector
    std::vector<llvm::Value *> args;

    // Populate the argument vector, breaking out of compilation if any argument fails to generate.
    for (TypedNode *e : argNodes)
    {
        std::optional<Value *> valOpt = AcceptType(this, e);
        if (!valOpt)
        {
            errorHandler.addError(n->getStart(), "Failed to generate code");
            return std::nullopt;
        }

        Value *val = valOpt.value();

        if (args.size() < n->paramType.size())
        {
            if (std::optional<const TypeSum *> sumOpt = type_cast<TypeSum>(n->paramType.at(args.size()))) // argNodes.at(args.size())->getType()))
            {
                val = correctSumAssignment(sumOpt.value(), val);
            }
        }

        args.push_back(val);
    }

    // Convert to an array ref, then find and execute the call.
    ArrayRef<Value *> ref = ArrayRef(args);

    std::optional<Value *> fnOpt = AcceptType(this, n->fn);
    if (!fnOpt)
    {
        errorHandler.addError(n->getStart(), "Could not locate function for invocation. Has it been defined in IR yet?");
        return std::nullopt;
    }

    Value *fnVal = fnOpt.value();

    llvm::Type *ty = fnVal->getType();

    if (llvm::isa<llvm::Function>(fnVal))
    {
        llvm::Function *call = static_cast<llvm::Function *>(fnVal);
        Value *val = builder->CreateCall(call, ref); // Needs to be separate line because, C++
        return val;
    }

    llvm::FunctionType *fnType = static_cast<llvm::FunctionType *>(ty->getPointerElementType());

    Value *val = builder->CreateCall(fnType, fnVal, ref);
    return val;
}

std::optional<Value *> CodegenVisitor::visit(TProgramRecvNode *n)
{
    Symbol *sym = n->sym;
    std::optional<llvm::AllocaInst *> optVal = getAllocation(sym);

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in recv: " + getCodegenID(n->sym));
        return std::nullopt;
    }

    Value *chanVal = optVal.value();

    const Type *allocType = n->meta.actingType ? n->meta.actingType.value() : n->meta.protocolType;
    llvm::Type *recvType = allocType->getLLVMType(module);

    Value *valPtr = builder->CreateCall(
        n->isInCloseable() ? 
            getReadLossyChannel() : // Should be fine as logic ab diff return types handled later 
            getReadLinearChannel(), 
        {builder->CreateLoad(channelRtPtrTy(), chanVal)}); // Will be a void*
    Value *casted = builder->CreateBitCast(valPtr, recvType->getPointerTo());                       // Cast the void* to the correct type ptr

    if (n->isInCloseable())
    {
        std::optional<Value *> castedOpt = correctNullOptionalToSum(n->meta, casted);
        if (!castedOpt)
        {
            errorHandler.addError(n->getStart(), "Failed to correct null optional for: " + getCodegenID(n->sym));
            return std::nullopt;
        }
        casted = castedOpt.value();
        // casted = correctNullOptionalToSum(n->getType(), casted);
    }

    Value *ans = builder->CreateLoad(recvType, casted);

    builder->CreateCall(getFree(), {valPtr}); // May leak depending on how GC works?

    return ans;
}

std::optional<Value *> CodegenVisitor::visit(TProgramIsPresetNode *n)
{
    Symbol *sym = n->sym;
    std::optional<llvm::AllocaInst *> optVal = getAllocation(sym);

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in recv: " + getCodegenID(n->sym));
        return std::nullopt;
    }

    Value *chanVal = optVal.value();

    return builder->CreateCall(
        n->isInCloseable() ? 
            get_OC_isPresentLossy() :  // Should be fine as just booleans
            get_OC_isPresentLinear(), 
        {builder->CreateLoad(channelRtPtrTy(), chanVal)});
}

std::optional<Value *> CodegenVisitor::visit(TProgramExecNode *n)
{
    std::optional<Value *> fnOpt = AcceptType(this, n->prog);

    if (!fnOpt)
    {
        return std::nullopt;
    }

    Value *fnVal = fnOpt.value();

    if (llvm::isa<llvm::Function>(fnVal))
    {
        llvm::Function *lambdaThread = static_cast<llvm::Function *>(fnVal);

        Value *val = builder->CreateCall(getExecute(), {lambdaThread});
        return val;
    }
    // TODO: REFACTOR, BOTH WITH THIS METHOD AND INVOCATION!

    Value *val = builder->CreateCall(getExecute(), {fnVal});
    return val;
}

std::optional<Value *> CodegenVisitor::visit(TProgramSendNode *n)
{
    std::optional<Value *> valOpt = AcceptType(this, new TExprCopyNode(n->expr, n->token));
    if (!valOpt)
    {
        errorHandler.addError(n->getStart(), "Failed to generate code");
        return std::nullopt;
    }

    Symbol *sym = n->sym;

    Value *stoVal = valOpt.value();

    // Same as return node's
    if (std::optional<const TypeSum *> sumOpt = type_cast<TypeSum>(n->lType))
    {
        stoVal = correctSumAssignment(sumOpt.value(), stoVal);
    }

    Value *v = builder->CreateCall(getMalloc(), {getU32(getSizeForValue(stoVal))});
    Value *casted = builder->CreateBitCast(v, stoVal->getType()->getPointerTo());

    builder->CreateStore(stoVal, casted);
    Value *corrected = builder->CreateBitCast(v, i8p);

    std::optional<llvm::AllocaInst *> optVal = getAllocation(sym);
    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in send: " + getCodegenID(n->sym));
        return std::nullopt;
    }

    Value *chanVal = optVal.value();
    builder->CreateCall(getWriteChannel(), {builder->CreateLoad(channelRtPtrTy(), chanVal), corrected}); // Will be a void*
    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TProgramContractNode *n)
{
    Symbol *sym = n->sym;
    std::optional<llvm::AllocaInst *> optVal = getAllocation(sym);

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in contract: " + getCodegenID(n->sym));
        return std::nullopt;
    }

    Value *chanVal = optVal.value();

    builder->CreateCall(getContractChannel(), {builder->CreateLoad(channelRtPtrTy(), chanVal)});

    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TProgramWeakenNode *n)
{
    Symbol *sym = n->sym;
    std::optional<llvm::AllocaInst *> optVal = getAllocation(sym);

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in weaken: " + getCodegenID(n->sym));
        return std::nullopt;
    }

    Value *chanVal = optVal.value();

    builder->CreateCall(getWeakenChannel(), {builder->CreateLoad(channelRtPtrTy(), chanVal)});

    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TProgramCancelNode *n)
{
    Symbol *sym = n->sym;
    std::optional<llvm::AllocaInst *> optVal = getAllocation(sym);

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in cancel: " + getCodegenID(n->sym));
        return std::nullopt;
    }

    Value *chanVal = optVal.value();

    builder->CreateCall(getCancelChannel(), {builder->CreateLoad(channelRtPtrTy(), chanVal), getU32(n->closeNumber)});
    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TProgramAcceptNode *n)
{
    // Very similar to regular loop

    Symbol *sym = n->sym;
    std::optional<llvm::AllocaInst *> optVal = getAllocation(sym);

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in accept: " + getCodegenID(n->sym));
        return std::nullopt;
    }

    Value *chanVal = optVal.value();

    auto checkFn = n->isInCloseable() ? getShouldLossyLoop() : getShouldLinearLoop();  // Should be fine as just booleans 
    Value *check = builder->CreateCall(checkFn, {builder->CreateLoad(channelRtPtrTy(), chanVal)});

    auto parent = builder->GetInsertBlock()->getParent();

    BasicBlock *loopBlk = BasicBlock::Create(module->getContext(), "loop", parent);
    BasicBlock *restBlk = BasicBlock::Create(module->getContext(), "rest");

    builder->CreateCondBr(check, loopBlk, restBlk);

    /*
     * In the loop block
     */
    builder->SetInsertPoint(loopBlk);
    for (auto e : n->blk->exprs)
    {
        AcceptType(this, e);
    }

    // Re-calculate the loop condition
    check = builder->CreateCall(checkFn, {builder->CreateLoad(channelRtPtrTy(), chanVal)});

    // Check if we need to loop back again...
    builder->CreateCondBr(check, loopBlk, restBlk);
    loopBlk = builder->GetInsertBlock();

    /*
     * Out of loop
     */
    parent->getBasicBlockList().push_back(restBlk);
    builder->SetInsertPoint(restBlk);

    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TProgramAcceptWhileNode *n)
{
    // Very similar to regular loop & Accept while
    Symbol *sym = n->sym;
    std::optional<llvm::AllocaInst *> optVal = getAllocation(sym);

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in accept: " + getCodegenID(n->sym));
        return std::nullopt;
    }

    Value *chanVal = optVal.value();

    auto parent = builder->GetInsertBlock()->getParent();
    BasicBlock *condBlk = BasicBlock::Create(module->getContext(), "aw-cond", parent);
    BasicBlock *thenBlk = BasicBlock::Create(module->getContext(), "aw-then");

    BasicBlock *loopBlk = BasicBlock::Create(module->getContext(), "loop");
    BasicBlock *restBlk = BasicBlock::Create(module->getContext(), "rest");

    builder->CreateBr(condBlk);
    builder->SetInsertPoint(condBlk);
    std::optional<Value *> condOpt = AcceptType(this, n->cond);

    if (!condOpt)
    {
        errorHandler.addError(n->getStart(), "521 - Failed to generate code for: " + n->cond->toString());
        return std::nullopt;
    }

    builder->CreateCondBr(condOpt.value(), thenBlk, restBlk);
    condBlk = builder->GetInsertBlock();

    parent->getBasicBlockList().push_back(thenBlk);
    builder->SetInsertPoint(thenBlk);
    Value *check = builder->CreateCall(
        n->isInCloseable() ? 
            getShouldLossyAcceptWhileLoop() :  // Here this is fine as its just a boolean either way
            getShouldLinearAcceptWhileLoop(), 
        {builder->CreateLoad(channelRtPtrTy(), chanVal)});

    builder->CreateCondBr(check, loopBlk, restBlk);

    thenBlk = builder->GetInsertBlock();

    /*
     * In the loop block
     */
    parent->getBasicBlockList().push_back(loopBlk);
    builder->SetInsertPoint(loopBlk);
    for (auto e : n->blk->exprs)
    {
        AcceptType(this, e);
    }

    // Check if we need to loop back again...
    builder->CreateBr(condBlk);
    loopBlk = builder->GetInsertBlock();

    /*
     * Out of loop
     */
    parent->getBasicBlockList().push_back(restBlk);
    builder->SetInsertPoint(restBlk);

    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TProgramAcceptIfNode *n)
{
    // Very similar to regular loop & Accept while
    std::optional<Value *> condOpt = AcceptType(this, n->cond);

    if (!condOpt)
    {
        errorHandler.addError(n->getStart(), "558 - Failed to generate code for: " + n->cond->toString());
        return std::nullopt;
    }

    Symbol *sym = n->sym;
    std::optional<llvm::AllocaInst *> optVal = getAllocation(sym);

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in acceptIf: " + getCodegenID(n->sym));
        return std::nullopt;
    }

    Value *chanVal = optVal.value();

    auto parent = builder->GetInsertBlock()->getParent();
    BasicBlock *condBlk = BasicBlock::Create(module->getContext(), "ai-cond", parent);
    BasicBlock *thenBlk = BasicBlock::Create(module->getContext(), "ai-then");
    BasicBlock *restBlk = BasicBlock::Create(module->getContext(), "rest");

    BasicBlock *elseBlk = n->falseOpt ? BasicBlock::Create(module->getContext(), "ai-else") : restBlk;

    builder->CreateCondBr(condOpt.value(), condBlk, elseBlk);

    builder->SetInsertPoint(condBlk);
    builder->CreateCondBr(
        builder->CreateCall(
            n->isInCloseable() ? 
                getShouldLossyAcceptWhileLoop() :  // Fine here as just booleans either way 
                getShouldLinearAcceptWhileLoop(), 
            {builder->CreateLoad(channelRtPtrTy(), chanVal)}),
        thenBlk,
        elseBlk);
    condBlk = builder->GetInsertBlock();

    parent->getBasicBlockList().push_back(thenBlk);
    builder->SetInsertPoint(thenBlk);
    
    for (auto e : n->trueBlk->exprs)
    {
        AcceptType(this, e);
    }
    if (!endsInReturn(n->trueBlk))
    {
        builder->CreateBr(restBlk);
    }
    thenBlk = builder->GetInsertBlock();

    if (n->falseOpt)
    {
        parent->getBasicBlockList().push_back(elseBlk);
        builder->SetInsertPoint(elseBlk);
        for (auto e : n->falseOpt.value()->exprs)
        {
            AcceptType(this, e);
        }
        if (!endsInReturn(n->falseOpt.value()))
        {
            builder->CreateBr(restBlk);
        }
    }

    parent->getBasicBlockList().push_back(restBlk);
    builder->SetInsertPoint(restBlk);
    for (auto e : n->post)
    {
        AcceptType(this, e);
    }

    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TInitProductNode *n)
{
    std::vector<Value *> args;

    for (TypedNode *e : n->exprs)
    {
        std::optional<Value *> valOpt = AcceptType(this, e);
        if (!valOpt)
        {
            errorHandler.addError(n->getStart(), "Failed to generate code");
            return std::nullopt;
        }

        Value *stoVal = valOpt.value();

        args.push_back(stoVal);
    }

    const TypeStruct *product = n->product;

    llvm::Type *ty = product->getLLVMType(module);
    llvm::AllocaInst *v = CreateEntryBlockAlloc(ty, ""); // TODO: this allocation isn' always needed
    {
        unsigned i = 0;
        std::vector<std::pair<std::string, const Type *>> elements = product->getElements();

        for (Value *a : args)
        {
            if (std::optional<const TypeSum *> sumOpt = type_cast<TypeSum>(elements.at(i).second))
            {
                a = correctSumAssignment(sumOpt.value(), a);
            }

            Value *ptr = builder->CreateGEP(v, {Int32Zero, getU32(i)});

            builder->CreateStore(a, ptr);

            i++;
        }
    }

    Value *loaded = builder->CreateLoad(v->getType()->getPointerElementType(), v);
    return loaded;
}

std::optional<Value *> CodegenVisitor::visit(TArrayRValue *n)
{
    // FIXME: ADD OPTIMIZATION TO USE GLOBAL CONSTANT WHEN ABLE!
    std::variant<const TypeArray *, const TypeDynArray *> typeVariant = n->getTypeVariant(); 

    llvm::AllocaInst * ans; 
    Value * writeTo; 
    const Type * stoType = nullptr; 

    if(std::holds_alternative<const TypeArray *>(typeVariant))
    {
        const TypeArray * ty = std::get<const TypeArray *>(typeVariant);

        ans = CreateEntryBlockAlloc(ty->getLLVMType(module), ""); // TODO: this isn't always needed
        writeTo = ans; 
        stoType = const_cast<Type *>(ty->getValueType()); 
    }
    else // TODO: UNUSED SO FAR BC NO WAY TO SET IT AS DYN
    {
        // TODO: use pattern matching instead of get to ensure we visit all possible opts
        const TypeDynArray * ty = std::get<const TypeDynArray *>(typeVariant); 

        ans = CreateEntryBlockAlloc(ty->getLLVMType(module), ""); // TODO: this isn't always needed

        InitDynArray(ans, getU32(n->exprs.size()));

        Value * vecPtr = builder->CreateGEP(ans, {Int32Zero, Int32Zero});
        writeTo = builder->CreateLoad(vecPtr, vecPtr->getType()->getPointerElementType());

        stoType = const_cast<Type *>(ty->getValueType()); 
    }
    
    std::vector<Value *> args;

    for (TypedNode *e : n->exprs)
    {
        std::optional<Value *> valOpt = AcceptType(this, e);
        if (!valOpt)
        {
            errorHandler.addError(n->getStart(), "Failed to generate code");
            return std::nullopt;
        }

        Value *stoVal = valOpt.value();

        args.push_back(stoVal);
    }

    unsigned int i = 0; 

    if(std::optional<const TypeSum *> sumOpt = type_cast<TypeSum>(stoType)) // FIXME: WONT WORK FOR [[(A + B)]]
    {
        const TypeSum * sumTy = sumOpt.value();
        for(Value * a : args)
        {
            a = correctSumAssignment(sumTy, a);

            Value *ptr = builder->CreateGEP(writeTo, {Int32Zero, getU32(i)});
            builder->CreateStore(a, ptr);
            i++;
        }
    }
    else 
    {
        for(Value * a : args)
        {
            Value *ptr = builder->CreateGEP(writeTo, {Int32Zero, getU32(i)});
            builder->CreateStore(a, ptr);
            i++;   
        }
    }


    Value *loaded = builder->CreateLoad(ans->getType()->getPointerElementType(), ans);
    return loaded;
}

std::optional<Value *> CodegenVisitor::visit(TInitBoxNode *n)
{
    std::optional<Value *> valOpt = AcceptType(this, n->expr);
    if (!valOpt)
    {
        errorHandler.addError(n->getStart(), "Failed to generate code");
        return std::nullopt;
    }

    Value *stoVal = valOpt.value();

    const TypeBox *box = n->boxType;

    if (std::optional<const TypeSum *> sumOpt = type_cast<TypeSum>(box->getInnerType()))
    {
        stoVal = correctSumAssignment(sumOpt.value(), stoVal);
    }

    Value *v = builder->CreateCall(getGCMalloc(), {builder->getInt64(module->getDataLayout().getTypeAllocSize(stoVal->getType()))});
    Value *casted = builder->CreateBitCast(v, box->getLLVMType(module));

    builder->CreateStore(stoVal, casted);

    // Value *loaded = builder->CreateLoad(v->getType()->getPointerElementType(), v);
    return casted;
}

std::optional<Value *> CodegenVisitor::visit(TArrayAccessNode *n) // TODO: COnsider refactoring/ improving generated IR
{
    std::optional<Value *> indexOpt = AcceptType(this, n->indexExpr);

    if (!indexOpt)
    {
        errorHandler.addError(n->getStart(), "Failed to generate code in visiting TArrayAccessNode for index!");
        return std::nullopt;
    }

    std::optional<Value *> arrayPtrOpt = AcceptType(this, n->field);
    if (!arrayPtrOpt)
    {
        errorHandler.addError(n->getStart(), "Failed to locate array in access");
        return std::nullopt;
    }

    Value *indexValue = indexOpt.value();
    Value *arrayPtr = arrayPtrOpt.value();

    if (!n->is_rvalue)
    {
        // If its an lvalue,need the pointer!
        return builder->CreateGEP(arrayPtr, {Int32Zero, indexValue});
    }

    // TODO: SIGNED VS UNSIGNED? AND LENGTH! NUM ELEMENTS IS 64!!
    Value *idxBoundsCheckValue = builder->CreateICmpSLT(
        indexValue,
        getU32(n->length())
    );

    auto parentFn = builder->GetInsertBlock()->getParent();

    BasicBlock *ltlBlk = BasicBlock::Create(module->getContext(), "accessLTL", parentFn);
    BasicBlock *gtzBlk = BasicBlock::Create(module->getContext(), "accessGTZ");
    BasicBlock *elseBlk = BasicBlock::Create(module->getContext(), "accessBad");
    BasicBlock *restBlk = BasicBlock::Create(module->getContext(), "accessAfter");

    builder->CreateCondBr(builder->CreateZExtOrTrunc(idxBoundsCheckValue, Int1Ty), ltlBlk, elseBlk);

    /*
     * We knw its less than the length, but need to ensure greater than zero
     */
    builder->SetInsertPoint(ltlBlk);

    builder->CreateCondBr(
        builder->CreateZExtOrTrunc(
            builder->CreateICmpSGE(indexValue, Int32Zero), // PLAN: Add slices which could loop!
            Int1Ty),
        gtzBlk,
        elseBlk);
    ltlBlk = builder->GetInsertBlock();

    /*
     * Passed Bounds Check Blk
     */
    parentFn->getBasicBlockList().push_back(gtzBlk);
    builder->SetInsertPoint(gtzBlk);
    Value *valuePtr = builder->CreateGEP(arrayPtr, {Int32Zero, indexValue});
    Value *value = builder->CreateLoad(valuePtr->getType()->getPointerElementType(), valuePtr);
    auto ptr = correctSumAssignment(n->getRValueType(), value); // FIXME: DONT CALCULATE getRValueType TWICE!!
    builder->CreateBr(restBlk);
    gtzBlk = builder->GetInsertBlock();

    /*
     * Out of bounds, so set unit
     */
    parentFn->getBasicBlockList().push_back(elseBlk);
    builder->SetInsertPoint(elseBlk);

    auto unitPtr = correctSumAssignment(n->getRValueType(), getUnitValue());
    builder->CreateBr(restBlk);
    elseBlk = builder->GetInsertBlock();

    /*
     * Return to computation
     */
    parentFn->getBasicBlockList().push_back(restBlk);
    builder->SetInsertPoint(restBlk);

    PHINode *phi = builder->CreatePHI(n->getType()->getLLVMType(module), 2, "arrayAccess");
    phi->addIncoming(ptr, gtzBlk);
    phi->addIncoming(unitPtr, elseBlk);

    return phi;
}


std::optional<Value *> CodegenVisitor::visit(TDynArrayAccessNode *n) // TODO: COnsider refactoring/ improving generated IR
{
    std::optional<Value *> indexOpt = AcceptType(this, n->indexExpr);

    if (!indexOpt)
    {
        errorHandler.addError(n->getStart(), "Failed to generate code in visiting TArrayAccessNode for index!");
        return std::nullopt;
    }

    std::optional<Value *> structOpt = AcceptType(this, n->field);
    if (!structOpt)
    {
        errorHandler.addError(n->getStart(), "Failed to locate array in access");
        return std::nullopt;
    }

    Value *indexValue = indexOpt.value();
    Value *structPtr = structOpt.value();



    Value *lengthPtr = builder->CreateGEP(structPtr, {Int32Zero, Int32One});
    Value *length = builder->CreateLoad(lengthPtr->getType()->getPointerElementType(), lengthPtr); 

    if (!n->is_rvalue)
    {
        
        (new TConditionalStatementNode(
            nullptr, 
            // Condition
            new TBinaryRelNode(
                BinaryRelOperator::BINARY_Rel_LESS_EQ,
                new CompCodeWrapper([length]() { return length; }),
                new CompCodeWrapper([indexValue](){ return indexValue; }),
                nullptr
            ), 
            // True block 
            new TBlockNode({
                new CompCodeWrapper([this, lengthPtr, length, structPtr, indexValue](){

                    Value *capPtr = builder->CreateGEP(structPtr, {Int32Zero, Int32One});
                    Value *cap =    builder->CreateLoad(Int32Ty, capPtr);

                    // TODO: does this memory leak?
                    (new TConditionalStatementNode(
                        nullptr,
                        // Condition
                        new TBinaryRelNode(
                            BinaryRelOperator::BINARY_Rel_LESS_EQ,
                            new CompCodeWrapper([cap](){ return cap; }),
                            new CompCodeWrapper([indexValue]() { return indexValue; }),
                            nullptr
                        ), 
                        // True Block 
                        new TBlockNode({
                            new CompCodeWrapper([this, structPtr, indexValue](){
                                ReallocateDynArray(structPtr, 
                                    builder->CreateNSWMul(indexValue, // TODO: Should really be the max of capacity or len!
                                    getU32(DYN_ARRAY_GROW_FACTOR))
                                );

                                return std::nullopt; 
                            })
                        }, nullptr),
                        // Post 
                        {
                            new CompCodeWrapper(
                                [this, lengthPtr, indexValue](){
                                    builder->CreateStore(
                                        builder->CreateNSWAdd(indexValue, Int32One),
                                        lengthPtr
                                    ); 
                                    return std::nullopt; 
                                }
                            )
                        }
                    ))->accept(this); 
                    

                    return std::nullopt; 
                })
            }, nullptr),
            // Post 
            {

            }
        ))->accept(this); 
        // ReallocateDynArray


        // If its an lvalue,need the pointer!
        Value * arrayPtr = builder->CreateGEP(structPtr, {Int32Zero, Int32Zero});
        Value * loadedArray = builder->CreateLoad(arrayPtr, arrayPtr->getType()->getPointerElementType());
        Value * indexPtr = builder->CreateGEP(loadedArray, indexValue);

        return indexPtr; //builder->CreateGEP(arrayPtr, {Int32Zero, indexValue});
    }

    


    Value *idxBoundsCheckValue = builder->CreateICmpSLT(
        indexValue,
        length
    );

    auto parentFn = builder->GetInsertBlock()->getParent();

    BasicBlock *ltlBlk = BasicBlock::Create(module->getContext(), "accessLTL", parentFn);
    BasicBlock *gtzBlk = BasicBlock::Create(module->getContext(), "accessGTZ");
    BasicBlock *elseBlk = BasicBlock::Create(module->getContext(), "accessBad");
    BasicBlock *restBlk = BasicBlock::Create(module->getContext(), "accessAfter");

    builder->CreateCondBr(builder->CreateZExtOrTrunc(idxBoundsCheckValue, Int1Ty), ltlBlk, elseBlk);

    /*
     * We knw its less than the length, but need to ensure greater than zero
     */
    builder->SetInsertPoint(ltlBlk);

    builder->CreateCondBr(
        builder->CreateZExtOrTrunc(
            builder->CreateICmpSGE(indexValue, Int32Zero), // PLAN: Add slices which could loop!
            Int1Ty),
        gtzBlk,
        elseBlk);
    ltlBlk = builder->GetInsertBlock();

    /*
     * Passed Bounds Check Blk
     */
    parentFn->getBasicBlockList().push_back(gtzBlk);
    builder->SetInsertPoint(gtzBlk);
    Value *vecPtr = builder->CreateGEP(structPtr, {Int32Zero, Int32Zero});
    Value *vec = builder->CreateLoad(vecPtr->getType()->getPointerElementType(), vecPtr);
    
    Value * valuePtr = builder->CreateGEP(vec, {indexValue});
    Value * value = builder->CreateLoad(valuePtr->getType()->getPointerElementType(), valuePtr);

    // FIXME: NULLABILITY CHECKS + FIX BUG WHERE DYN ARRAY CAN BE USED W/ LINEAR RESOURCES 
    // FIXME: ALLOW STREAMING OF DYN ARRAYS!





    // std::cout << n->getRValueType()->toString(DisplayMode::C_STYLE) << std::endl; 
    auto ptr = correctSumAssignment(n->getRValueType(), value); // FIXME: DONT CALCULATE getRValueType TWICE!!
    builder->CreateBr(restBlk);
    gtzBlk = builder->GetInsertBlock();

    /*
     * Out of bounds, so set unit
     */
    parentFn->getBasicBlockList().push_back(elseBlk);
    builder->SetInsertPoint(elseBlk);

    auto unitPtr = correctSumAssignment(n->getRValueType(), getUnitValue());
    builder->CreateBr(restBlk);
    elseBlk = builder->GetInsertBlock();

    /*
     * Return to computation
     */
    parentFn->getBasicBlockList().push_back(restBlk);
    builder->SetInsertPoint(restBlk);

    module->dump(); 

    PHINode *phi = builder->CreatePHI(n->getType()->getLLVMType(module), 2, "arrayAccess");
    phi->addIncoming(ptr, gtzBlk);
    phi->addIncoming(unitPtr, elseBlk);

    return phi;
}

std::optional<Value *> CodegenVisitor::visit(TInt32ConstExprNode *n)
{
    return getI32(n->value);
}

std::optional<Value *> CodegenVisitor::visit(TInt64ConstExprNode *n)
{
    return getI64(n->value);
}

std::optional<Value *> CodegenVisitor::visit(TIntU32ConstExprNode *n)
{
    return getU32(n->value);
}

std::optional<Value *> CodegenVisitor::visit(TIntU64ConstExprNode *n)
{
    return getU64(n->value);
}

std::optional<Value *> CodegenVisitor::visit(TStringConstNode *n)
{
    // Create a constant to represent our string (now with the escape characters corrected)
    llvm::Constant *dat = llvm::ConstantDataArray::getString(module->getContext(), n->value);

    // Allocate a global variable for the constant, and set flags to make it match what the CreateGlobalStringPtr function would have done
    llvm::GlobalVariable *glob = new llvm::GlobalVariable(
        *module,
        dat->getType(),
        true,
        GlobalValue::PrivateLinkage,
        dat,
        "");
    glob->setAlignment(llvm::MaybeAlign(1));
    glob->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);

    // Allocate the string and return that value.
    // This prevents the issue of CreateGlobalStringPtr where it creates a string AND a pointer to it.
    // Here, we can deal with the pointer later (just as if it were a normal variable)
    llvm::Constant *Indices[] = {Int32Zero, Int32Zero};

    Value *val = llvm::ConstantExpr::getInBoundsGetElementPtr(
        glob->getValueType(),
        glob,
        Indices);

    return val;
}

std::optional<Value *> CodegenVisitor::visit(TUnaryExprNode *n)
{
    switch (n->op)
    {
    case UNARY_MINUS:
    {
        std::optional<Value *> innerVal = AcceptType(this, n->value);

        if (!innerVal)
        {
            errorHandler.addError(n->getStart(), "Failed to generate code for: unary minus");
            return std::nullopt;
        }

        return builder->CreateNSWSub(Int32Zero, innerVal.value());
    }

    case UNARY_NOT:
    {
        std::optional<Value *> innerVal = AcceptType(this, n->value);

        if (!innerVal)
        {
            errorHandler.addError(n->getStart(), "Failed to generate code for: unary not");
            return std::nullopt;
        }

        return builder->CreateNot(innerVal.value());
    }
    }
}

std::optional<Value *> CodegenVisitor::visit(TBinaryArithNode *n)
{
    std::optional<Value *> lhs = AcceptType(this, n->lhs);
    std::optional<Value *> rhs = AcceptType(this, n->rhs);

    if (!lhs || !rhs)
    {
        errorHandler.addError(n->getStart(), "Failed to generate code for: binary arith");
        return std::nullopt;
    }

    // FIXME: VERIFY NSW vs NUW!
    switch (n->op)
    {
    case BINARY_ARITH_PLUS:
        return builder->CreateNSWAdd(lhs.value(), rhs.value());
    case BINARY_ARITH_MINUS:
        return builder->CreateNSWSub(lhs.value(), rhs.value());
    case BINARY_ARITH_MULT:
        return builder->CreateNSWMul(lhs.value(), rhs.value());
    case BINARY_ARITH_DIV:
        return builder->CreateSDiv(lhs.value(), rhs.value());
    case BINARY_ARITH_MOD:
        return builder->CreateSRem(lhs.value(), rhs.value());
    }
}

std::optional<Value *> CodegenVisitor::visit(TEqExprNode *n)
{
    std::optional<Value *> lhs = AcceptType(this, n->lhs);
    std::optional<Value *> rhs = AcceptType(this, n->rhs);

    if (!lhs || !rhs)
    {
        errorHandler.addError(n->getStart(), "Failed to generate code for: eq expr");
        return std::nullopt;
    }

    switch (n->op)
    {
    case EQUAL_OP:
    {
        Value *v1 = builder->CreateICmpEQ(lhs.value(), rhs.value());
        Value *v = builder->CreateZExtOrTrunc(v1, Int1Ty);
        return v;
    }

    case NOT_EQUAL_OP:
    {
        Value *v1 = builder->CreateICmpNE(lhs.value(), rhs.value());
        Value *v = builder->CreateZExtOrTrunc(v1, Int1Ty);
        return v;
    }
    }
}

/**
 * @brief Generates code for Logical Ands
 *
 * Tested in: test2.bismuth
 *
 * @param ctx LogAndExprContext to generate this from
 * @return std::optional<Value *> The resulting value or {} if errors.
 */
std::optional<Value *> CodegenVisitor::visit(TLogAndExprNode *n)
{
    // Create the basic block for our conditions
    BasicBlock *current = builder->GetInsertBlock();
    BasicBlock *mergeBlk = BasicBlock::Create(module->getContext(), "mergeBlkAnd");

    /*
     * PHI node to merge both sides back together
     */
    builder->SetInsertPoint(mergeBlk);
    PHINode *phi = builder->CreatePHI(Int1Ty, n->exprs.size(), "logAnd");

    builder->SetInsertPoint(current);

    std::optional<Value *> first = AcceptType(this, n->exprs.at(0));

    if (!first)
    {
        errorHandler.addError(n->getStart(), "Failed to generate code for: first log and");
        return std::nullopt;
    }

    Value *lastValue = first.value();

    auto parent = current->getParent();
    phi->addIncoming(lastValue, builder->GetInsertBlock()); // Have to use insert block as, due to nested short circuiting, its possible that the insert block isn't actually the entry block anymore

    BasicBlock *falseBlk;

    // Branch on the lhs value
    for (unsigned int i = 1; i < n->exprs.size(); i++)
    {
        falseBlk = BasicBlock::Create(module->getContext(), "prevTrueAnd", parent);
        builder->CreateCondBr(lastValue, falseBlk, mergeBlk);

        /*
         * LHS False - Need to check RHS value
         */
        builder->SetInsertPoint(falseBlk);

        std::optional<Value *> rhs = AcceptType(this, n->exprs.at(i));

        if (!rhs)
        {
            errorHandler.addError(n->getStart(), "901 - Failed to generate code for: " + n->exprs.at(i)->toString());
            return std::nullopt;
        }
        lastValue = rhs.value();

        falseBlk = builder->GetInsertBlock();
        parent = falseBlk->getParent();
        phi->addIncoming(lastValue, falseBlk);
    }

    builder->CreateBr(mergeBlk); // CONSIDER: Methodize with or?
    /*
     * LHS True - Can skip checking RHS and return true
     */
    parent->getBasicBlockList().push_back(mergeBlk);
    builder->SetInsertPoint(mergeBlk);

    return phi;
}

/**
 * @brief Generates code for Logical Ors.
 *
 * Tested in: test2.bismuth
 *
 * @param ctx Context to generate code from
 * @return std::optional<Value *> The resulting value or {} if errors.
 */
std::optional<Value *> CodegenVisitor::visit(TLogOrExprNode *n)
{
    // Create the basic block for our conditions
    BasicBlock *current = builder->GetInsertBlock();
    BasicBlock *mergeBlk = BasicBlock::Create(module->getContext(), "mergeBlkOr");

    /*
     * PHI node to merge both sides back together
     */
    builder->SetInsertPoint(mergeBlk);
    PHINode *phi = builder->CreatePHI(Int1Ty, n->exprs.size(), "logOr");

    builder->SetInsertPoint(current);

    std::optional<Value *> first = AcceptType(this, n->exprs.at(0));

    if (!first)
    {
        errorHandler.addError(n->getStart(), "947 - Failed to generate code for: " + n->exprs.at(0)->toString());
        return std::nullopt;
    }

    Value *lastValue = first.value();

    auto parent = current->getParent();
    phi->addIncoming(lastValue, builder->GetInsertBlock()); // Have to use insert block as, due to nested short circuiting, its possible that the insert block isn't actually the entry block anymore

    BasicBlock *falseBlk;

    // Branch on the lhs value
    for (unsigned int i = 1; i < n->exprs.size(); i++)
    {
        falseBlk = BasicBlock::Create(module->getContext(), "prevFalseOr", parent);
        builder->CreateCondBr(lastValue, mergeBlk, falseBlk);

        /*
         * LHS False - Need to check RHS value
         */
        builder->SetInsertPoint(falseBlk);

        std::optional<Value *> rhs = AcceptType(this, n->exprs.at(i));

        if (!rhs)
        {
            errorHandler.addError(n->getStart(), "973 - Failed to generate code for: " + n->exprs.at(i)->toString());
            return std::nullopt;
        }
        lastValue = rhs.value();

        falseBlk = builder->GetInsertBlock();
        parent = falseBlk->getParent();
        phi->addIncoming(lastValue, falseBlk);
    }

    builder->CreateBr(mergeBlk);

    /*
     * LHS True - Can skip checking RHS and return true
     */
    parent->getBasicBlockList().push_back(mergeBlk);
    builder->SetInsertPoint(mergeBlk);

    return phi;
}

std::optional<Value *> CodegenVisitor::visit(TFieldAccessNode *n)
{
    // Symbol *sym = n->symbol;

    // if (!sym->getType()) // TODO: symbol or use local type on typed ast node?
    // {
    //     errorHandler.addError(n->getStart(), "Improperly initialized symbol in field access: " + getCodegenID(n->symbol));
    //     return std::nullopt;
    // }

    if (n->accesses.size() > 0 && n->accesses.at(n->accesses.size() - 1).first == "length")
    {
        const Type *modOpt = (n->accesses.size() > 1) ? n->accesses.at(n->accesses.size() - 2).second : n->getSymbolType(); //sym->getType();
        if (std::optional<const TypeArray *> arOpt = type_cast<TypeArray>(modOpt))
        {
            // If it is, correctly, an array type, then we can get the array's length (this is the only operation currently, so we can just do thus)
            return getU32(arOpt.value()->getLength());
        }
        // else if(std::optional<const TypeDynArray *> dynArOpt = type_cast<TypeDynArray>(modOpt))
        // {
            // Value *lenPtr = builder->CreateGEP(dynArOpt.value(), {Int32Zero, Int32One});
        // }

        // Can't throw error b/c length could be field of struct
    }

    const Type *ty = n->getSymbolType(); //sym->getType();
    std::cout << "1414!!!! " << ty->toString(DisplayMode::C_STYLE) << std::endl; 
    std::optional<Value *> baseOpt = visitVariable(n->getSymbol(), n->accesses.size() == 0 ? n->is_rvalue : false);

    if (!baseOpt)
    {
        errorHandler.addError(n->getStart(), "1023 - Failed to generate field access: " + n->toString());
        return std::nullopt;
    }

    Value *baseValue = baseOpt.value();

    if (n->accesses.size() == 0)
    {
        return baseValue;
    }

    std::vector<Value *> addresses = {Int32Zero};

    for (unsigned int i = 0; i < n->accesses.size(); i++)
    {
        if (std::optional<const TypeStruct *> sOpt = type_cast<TypeStruct>(ty))
        {
            std::string field = n->accesses.at(i).first;
            std::optional<unsigned int> indexOpt = sOpt.value()->getIndex(field);

            if (!indexOpt)
            {
                errorHandler.addError(n->getStart(), "Could not lookup " + field);
                return std::nullopt;
            }

            unsigned int index = indexOpt.value();
            addresses.push_back(getU32(index));

            const Type *fieldType = n->accesses.at(i).second;
            ty = fieldType;
        }
        else if (type_cast<TypeDynArray>(ty) &&  i + 1 == n->accesses.size() && n->accesses.at(n->accesses.size() - 1).first == "length")
        {
            // Value *lenPtr = builder->CreateGEP(dynArOpt.value(), {Int32Zero, Int32One});
            addresses.push_back(Int32One);
            ty = Types::DYN_U32; 
        }
        else
        {
            errorHandler.addError(n->getStart(), "Could not perform field access. Got type: " + ty->toString(getToStringMode()));
            return std::nullopt;
        }
    }

    Value *valPtr = builder->CreateGEP(baseValue, addresses);

    if (n->is_rvalue)
    {
        const Type *fieldType = n->accesses.at(n->accesses.size() - 1).second;

        llvm::Type *ansType = fieldType->getLLVMType(module);
        baseOpt = builder->CreateLoad(ansType, valPtr);
        return baseOpt;
    }

    return valPtr;
}

std::optional<Value *> CodegenVisitor::visit(TDerefBoxNode *n)
{
    std::optional<Value *> baseOpt = AcceptType(this, n->expr);

    if (!baseOpt)
    {
        errorHandler.addError(n->getStart(), "985 - Failed to generate deref expr: " + n->expr->toString());
        return std::nullopt;
    }

    Value *ptrVal = baseOpt.value();
    return n->is_rvalue ? builder->CreateLoad(ptrVal->getType()->getPointerElementType(), ptrVal) : ptrVal;

    // return loaded;
    // return n->is_rvalue ? builder->CreateLoad(loaded->getType()->getPointerElementType(), loaded) : loaded;
}

std::optional<Value *> CodegenVisitor::visit(TBinaryRelNode *n)
{
    // Generate code for LHS and RHS
    std::optional<Value *> lhs = AcceptType(this, n->lhs);
    std::optional<Value *> rhs = AcceptType(this, n->rhs);

    // Ensure we successfully generated LHS and RHS
    if (!lhs)
    {
        errorHandler.addError(n->getStart(), "Failed to generate code for lhs of BinaryRel: " + n->lhs->toString());
        return std::nullopt;
    }

    if (!rhs)
    {
        errorHandler.addError(n->getStart(), "Failed to generate code for rhs of BinaryRel: " + n->rhs->toString());
        return std::nullopt;
    }

    Value *v1;

    switch (n->op)
    {
    case BINARY_Rel_LESS:
        v1 = builder->CreateICmpSLT(lhs.value(), rhs.value());
        break;
    case BINARY_Rel_LESS_EQ:
        v1 = builder->CreateICmpSLE(lhs.value(), rhs.value());
        break;
    case BINARY_Rel_GREATER:
        v1 = builder->CreateICmpSGT(lhs.value(), rhs.value());
        break;
    case BINARY_Rel_GREATER_EQ:
        v1 = builder->CreateICmpSGE(lhs.value(), rhs.value());
        break;
    }

    Value *v = builder->CreateZExtOrTrunc(v1, Int1Ty);
    return v;
}

std::optional<Value *> CodegenVisitor::visit(TExternNode *n)
{
    Symbol *symbol = n->getSymbol(); // WHY ARE SOME PRIVATE AND OTHERS PUBLIC?

    if (!symbol->getType())
    {
        errorHandler.addCompilerError(n->getStart(), "Type for extern statement not correctly bound.");
        return std::nullopt;
    }

    const TypeFunc *type = n->getType();

    Function *fn = Function::Create(type->getLLVMFunctionType(module), GlobalValue::ExternalLinkage, getCodegenID(symbol), module);
    // type->setName(fn->getName().str());

    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TAssignNode *n)
{

    std::optional<Value *> val = AcceptType(this, n->var); // varSym->val;
    // Sanity check to ensure that we now have a value for the variable
    if (!val)
    {
        errorHandler.addError(n->getStart(), "1184 - Improperly initialized variable in assignment: " + n->var->toString());
        return std::nullopt;
    }

    // Visit the expression to get the value we will assign
    std::optional<Value *> exprVal = AcceptType(this, n->val);

    // Check that the expression generated
    if (!exprVal)
    {
        errorHandler.addError(n->getStart(), "1145 - Failed to generate code for: " + n->val->toString());
        return std::nullopt;
    }

    // Lookup the binding for the variable we are assigning to and and ensure that we find it
    // std::optional<Symbol *> varSymOpt = props->getBinding(ctx->to);
    // if (!varSymOpt)
    // {
    //     errorHandler.addError(n->getStart(), "Incorrectly processed variable in assignment: " + ctx->to->getText());
    //     return std::nullopt;
    // }

    /*
    Symbol *varSym = varSymOpt.value();
    */
    // Get the allocation instruction for the symbol

    /*
    // If the symbol is global
    if (varSym->isGlobal)
    {
        // Find the global variable that corresponds to our symbol
        llvm::GlobalVariable *glob = module->getNamedGlobal(varSym->identifier);

        // If we can't find it, then throw an error.
        if (!glob)
        {
            errorHandler.addError(n->getStart(), "Unable to find global variable: " + varSym->identifier);
            return std::nullopt;
        }

        // Load a pointer to the global variable
        val = builder->CreateLoad(glob)->getPointerOperand();
    }
    */

    /*
    // Checks to see if we are dealing with an array
    if (!ctx->to->var)
    {
        // As this is an array access, we need to determine the index we will be accessing
        std::optional<Value *> index = any2Value(ctx->to->array->index->accept(this));

        // Ensure we built an index
        if (!index)
        {
            errorHandler.addError(n->getStart(), "Failed to generate code for: " + ctx->to->getText());
            return std::nullopt;
        }

        // Create a GEP to the index based on our previously calculated value and index
        Value *built = builder->CreateGEP(val.value(), {Int32Zero, index.value()});
        val = built;
    }
    */

    // Store the expression's value
    // TODO: METHODIZE?
    Value *v = val.value();
    Value *stoVal = exprVal.value();
    const Type *varSymType = n->var->getType();
    if (std::optional<const TypeSum *> sumOpt = type_cast<TypeSum>(varSymType))
    {
        uint32_t index = sumOpt.value()->getIndex(module, stoVal->getType());

        if (index == 0)
        {
            Value *corrected = builder->CreateBitCast(v, stoVal->getType()->getPointerTo());
            builder->CreateStore(stoVal, corrected);
            return std::nullopt;
        }
        Value *tagPtr = builder->CreateGEP(v, {Int32Zero, Int32Zero});

        builder->CreateStore(getU32(index), tagPtr);
        Value *valuePtr = builder->CreateGEP(v, {Int32Zero, Int32One});

        Value *corrected = builder->CreateBitCast(valuePtr, stoVal->getType()->getPointerTo());
        builder->CreateStore(stoVal, corrected);
    }
    else
    {
        builder->CreateStore(stoVal, v);
    }

    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TVarDeclNode *n)
{
    /*
     * Visit each of the assignments in the context (variables paired with an expression)
     */
    for (auto e : n->assignments)
    {
        std::optional<Value *> exVal = (e->val) ? AcceptType(this, e->val.value()) : std::nullopt;

        if ((e->val) && !exVal)
        {
            errorHandler.addError(n->getStart(), "1206 - Failed to generate code for: " + e->val.value()->toString());
            return std::nullopt;
        }

        // For each of the variables being assigned to that value
        for (Symbol *varSymbol : e->syms)
        {
            std::cout << "1677 " << varSymbol->toString() << " --- " << varSymbol->getUniqueNameInScope() << std::endl; 
            //  Get the type of the symbol
            llvm::Type *ty = getLLVMType(varSymbol);

            // Branch depending on if the var is global or not
            if (varSymbol->isGlobal())
            {
                // If it is global, then we need to insert a new global variable of this type.
                // A lot of these options are done to make it match what a C program would
                // generate for global vars
                // FIXME: REFACTOR THIS? WHY GET OR INSERT THEN GET AGAIN?
                module->getOrInsertGlobal(getCodegenID(varSymbol), ty);
                llvm::GlobalVariable *glob = module->getNamedGlobal(getCodegenID(varSymbol));
                glob->setLinkage(GlobalValue::ExternalLinkage);
                glob->setDSOLocal(true);

                // If we had an expression to set the var equal to
                if (e->val)
                {
                    // Ensure that the value is a constant, then, if so, initialize it.
                    if (llvm::Constant *constant = static_cast<llvm::Constant *>(exVal.value()))
                    {
                        glob->setInitializer(constant);
                    }
                    else
                    {
                        // Should already be checked in semantic, and I don't think we could get here anyways, but still might as well have it.
                        errorHandler.addError(n->getStart(), "Global variable can only be initalized to a constant!");
                        return std::nullopt;
                    }
                }
                else
                {
                    // As there was no constant, just set the global var to be initalized to zero as C does with llvm.
                    llvm::ConstantAggregateZero *constant = llvm::ConstantAggregateZero::get(ty);
                    glob->setInitializer(constant);
                }
            }
            else
            {
                //  As this is a local var we can just create an allocation for it
                llvm::AllocaInst *v = CreateAndLinkEntryBlockAlloc(ty, varSymbol);

                // Similarly, if we have an expression for the local var, we can store it. Otherwise, we can leave it undefined.
                if (e->val)
                {
                    Value *stoVal = exVal.value();
                    if (std::optional<const TypeSum *> sumOpt = type_cast<TypeSum>(varSymbol->getType()))
                    {
                        uint32_t index = sumOpt.value()->getIndex(module, stoVal->getType());

                        if (index == 0)
                        {
                            Value *corrected = builder->CreateBitCast(v, stoVal->getType()->getPointerTo());
                            builder->CreateStore(stoVal, corrected);
                            return std::nullopt;
                        }

                        Value *tagPtr = builder->CreateGEP(v, {Int32Zero, Int32Zero});

                        builder->CreateStore(getU32(index), tagPtr);
                        Value *valuePtr = builder->CreateGEP(v, {Int32Zero, Int32One});

                        Value *corrected = builder->CreateBitCast(valuePtr, stoVal->getType()->getPointerTo());
                        builder->CreateStore(stoVal, corrected);
                    }
                    else
                    {
                        builder->CreateStore(stoVal, v);
                    }
                }
                else if(const TypeDynArray * dynArray = dynamic_cast<const TypeDynArray*>(varSymbol->getType()))
                {
                    InitDynArray(v, getU32(10)); // FIXME: DO BETTER
                }
            }
        }
    }
    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TWhileLoopNode *n)
{
    // Very similar to conditionals
    std::optional<Value *> check = AcceptType(this, n->cond);

    if (!check)
    {
        errorHandler.addError(n->getStart(), "1342 - Failed to generate code for: " + n->cond->toString());
        return std::nullopt;
    }

    auto parent = builder->GetInsertBlock()->getParent();

    BasicBlock *loopBlk = BasicBlock::Create(module->getContext(), "loop", parent);
    BasicBlock *restBlk = BasicBlock::Create(module->getContext(), "rest");

    builder->CreateCondBr(check.value(), loopBlk, restBlk);

    /*
     * In the loop block
     */
    builder->SetInsertPoint(loopBlk);

    for (auto e : n->blk->exprs)
    {
        AcceptType(this, e);
    }

    // Re-calculate the loop condition
    check = AcceptType(this, n->cond);
    if (!check)
    {
        errorHandler.addError(n->getStart(), "1367 - Failed to generate code for: " + n->cond->toString());
        return std::nullopt;
    }

    // Check if we need to loop back again...
    builder->CreateCondBr(check.value(), loopBlk, restBlk);
    loopBlk = builder->GetInsertBlock();

    /*
     * Out of loop
     */
    parent->getBasicBlockList().push_back(restBlk);
    builder->SetInsertPoint(restBlk);
    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TConditionalStatementNode *n)
{
    // Get the condition that the if statement is for
    std::optional<Value *> cond = AcceptType(this, n->cond);

    if (!cond)
    {
        errorHandler.addError(n->getStart(), "1391 - Failed to generate code for: " + n->cond->toString());
        return std::nullopt;
    }

    /*
     * Generate the basic blocks for then, else, and the remaining code.
     * (NOTE: We set rest to be else if there is no else branch).
     */
    auto parentFn = builder->GetInsertBlock()->getParent();

    BasicBlock *thenBlk = BasicBlock::Create(module->getContext(), "then", parentFn);
    BasicBlock *elseBlk = BasicBlock::Create(module->getContext(), "else");

    BasicBlock *restBlk = n->falseOpt ? BasicBlock::Create(module->getContext(), "if-cont")
                                      : elseBlk;

    builder->CreateCondBr(cond.value(), thenBlk, elseBlk);

    /*
     * Then block
     */
    builder->SetInsertPoint(thenBlk);
    for (auto e : n->trueBlk->exprs)
    {
        AcceptType(this, e);
    }

    // If the block ends in a return, then we can't make the branch; things would break
    if (!endsInReturn(n->trueBlk))
    {
        builder->CreateBr(restBlk);
    }

    thenBlk = builder->GetInsertBlock();

    /*
     * Insert the else block (same as rest if no else branch)
     */
    parentFn->getBasicBlockList().push_back(elseBlk);
    builder->SetInsertPoint(elseBlk);

    if (n->falseOpt) // If we have an else branch
    {
        // Generate the code for the else block; follows the same logic as the then block.
        for (auto e : n->falseOpt.value()->exprs)
        {
            // e->accept(this);
            AcceptType(this, e);
        }

        if (!endsInReturn(n->falseOpt.value()))
        {
            builder->CreateBr(restBlk);
        }

        elseBlk = builder->GetInsertBlock();

        // As we have an else block, rest and else are different, so we have to merge back in.
        parentFn->getBasicBlockList().push_back(restBlk);
        builder->SetInsertPoint(restBlk);
    }

    for (auto s : n->post)
    {
        AcceptType(this, s);
    }

    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TSelectStatementNode *n)
{
    /*
     * Set up the merge block that all cases go to after the select statement
     */
    auto origParent = builder->GetInsertBlock()->getParent();
    BasicBlock *mergeBlk = BasicBlock::Create(module->getContext(), "if-cont");

    // Iterate through each of the cases
    for (unsigned long i = 0; i < n->nodes.size(); i++)
    {
        TSelectAlternativeNode *evalCase = n->nodes.at(i);

        // Visit the check code
        std::optional<Value *> optVal = AcceptType(this, evalCase->check);

        // Check that the optional, in fact, has a value. Otherwise, something went wrong.
        if (!optVal)
        {
            errorHandler.addError(n->getStart(), "Failed to generate code for: 1442"); // + evalCase->getText());
            return std::nullopt;
        }

        // Knowing that we have a value, get what the value is.
        Value *val = optVal.value();

        // Helpful check for later on
        bool isLast = i == n->nodes.size() - 1;

        // Create the then and else blocks as if this were an if statement
        auto parent = builder->GetInsertBlock()->getParent();
        BasicBlock *thenBlk = BasicBlock::Create(module->getContext(), "then", parent);
        BasicBlock *elseBlk = isLast ? mergeBlk : BasicBlock::Create(module->getContext(), "else");

        // Branch based on the value
        builder->CreateCondBr(val, thenBlk, elseBlk);

        /*
         *
         * THEN BLOCK
         *
         */
        builder->SetInsertPoint(thenBlk);

        // Visit the evaluation code for the case
        // evalCase->eval->accept(this);
        AcceptType(this, evalCase->eval);

        /*
         * As codegen worked, we now need to determine if
         * the code we generated was for a block ending in
         * a return or if it is a return statement. This
         * Must be done as it determines if we create
         * a merge into the merge block or not.
         */
        if (TBlockNode *blk = dynamic_cast<TBlockNode *>(evalCase->eval))
        {
            if (!endsInReturn(blk))
            {
                builder->CreateBr(mergeBlk);
            }
            // if it ends in a return, we're good!
        }
        else if (TReturnNode *retCtx = dynamic_cast<TReturnNode *>(evalCase->eval))
        {
            // Similarly, we don't need to generate the branch
        }
        else
        {
            builder->CreateBr(mergeBlk);
        }

        thenBlk = builder->GetInsertBlock();

        /*
         *
         * Else Block
         *
         */
        if (!isLast)
        {
            parent->getBasicBlockList().push_back(elseBlk);
            builder->SetInsertPoint(elseBlk);
        }
    }

    // We could probably do this as an else on the is !isLast check, but this works
    origParent->getBasicBlockList().push_back(mergeBlk);
    builder->SetInsertPoint(mergeBlk);

    for (TypedNode *s : n->post)
    {
        AcceptType(this, s);
    }

    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TReturnNode *n)
{
    // Check if we are returning an expression or not
    if (n->expr)
    {
        std::pair<const Type *, TypedNode *> expr = n->expr.value();
        // Perform some checks to make sure that code was generated
        std::optional<Value *> innerOpt = AcceptType(this, expr.second);

        if (!innerOpt)
        {
            errorHandler.addError(n->getStart(), "1571 - Failed to generate code for: " + n->toString());
            return std::nullopt;
        }

        Value *inner = innerOpt.value();

        if (std::optional<const TypeSum *> sumOpt = type_cast<TypeSum>(expr.first))
        {
            inner = correctSumAssignment(sumOpt.value(), inner);
        }

        // As the code was generated correctly, build the return statement; we ensure no following code due to how block visitors work in semantic analysis.
        return builder->CreateRet(inner);
    }

    // If there is no value, return void. We ensure no following code and type-correctness in the semantic pass.
    return builder->CreateRet(getUnitValue());
}

std::optional<Value *> CodegenVisitor::visit(TExitNode *n)
{
    // If there is no value, return void. We ensure no following code and type-correctness in the semantic pass.
    return builder->CreateRet(getUnitValue());
}

std::optional<Value *> CodegenVisitor::visit(TBooleanConstNode *n)
{
    return n->value ? builder->getTrue() : builder->getFalse();
}

std::optional<Value *> CodegenVisitor::visit(TBlockNode *n)
{
    for (auto e : n->exprs)
    {
        AcceptType(this, e);
    }

    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TLambdaConstNode *n)
{
    // Get the current insertion point
    BasicBlock *ins = builder->GetInsertBlock();

    const TypeFunc *type = n->getType();

    llvm::FunctionType *fnType = type->getLLVMFunctionType(module);

    std::string funcFullName = getCodegenID(n->getSymbol());

    Function *fn = module->getFunction(funcFullName);
    if(!fn)
        fn = Function::Create(fnType, GlobalValue::PrivateLinkage, funcFullName, module);
    // type->setName(fn->getName().str()); // Note: NOT ALWAYS NEEDED -> Probably not needed

    std::vector<Symbol *> paramList = n->paramSymbols;

    // Create basic block
    BasicBlock *bBlk = BasicBlock::Create(module->getContext(), "entry", fn);
    builder->SetInsertPoint(bBlk);

    // Bind all of the arguments
    for (auto &arg : fn->args())
    {
        // Get the argument number (just seems easier than making my own counter)
        int argNumber = arg.getArgNo();

        // Get the argument's type
        llvm::Type *type = fnType->params()[argNumber];

        // Get the argument name (This even works for arrays!)
        Symbol *param = paramList.at(argNumber);

        // Create an allocation for the argument
        llvm::AllocaInst *v = CreateAndLinkEntryBlockAlloc(type, param);

        builder->CreateStore(&arg, v);
    }

    // Generate code for the block
    for (auto e : n->block->exprs)
    {
        AcceptType(this, e);
    }

    // Needed to help make the branching programs work due to switches being exhaustive. Will have to do this better eventually!
    llvm::Instruction *inst = &*(builder->GetInsertBlock()->rbegin());
    if (!dyn_cast<llvm::ReturnInst>(inst))
    {
        builder->CreateUnreachable();
    }
    // if(!llvm::isa<llvm::ReturnInst>(builder->GetInsertBlock()->end()))
    // if(llvm::ReturnInst * dead = dynamic_cast<llvm::ReturnInst>(builder->GetInsertBlock()->end()))
    // {

    // }
    // else
    // {
    //     builder->CreateUnreachable();
    // }

    // NOTE HOW WE DONT NEED TO CREATE RET VOID EVER BC NO FN!

    // Return to original insert point
    builder->SetInsertPoint(ins);

    return fn;
}

std::optional<Value *> CodegenVisitor::visit(TProgramDefNode *n)
{
    BasicBlock *ins = builder->GetInsertBlock();

    const TypeProgram *prog = n->getType();

    llvm::FunctionType *fnType = prog->getLLVMFunctionType(module);

    std::string funcFullName = getCodegenID(n->getSymbol());

    Function *fn = module->getFunction(funcFullName);
    if(!fn)
        fn = Function::Create(fnType, GlobalValue::PrivateLinkage, funcFullName, module);

    // prog->setName(fn->getName().str());// Note: NOT ALWAYS NEEDED -> Probably not needed

    // Create basic block
    BasicBlock *bBlk = BasicBlock::Create(module->getContext(), "entry", fn);
    builder->SetInsertPoint(bBlk);

    // Bind all of the arguments
    std::optional<llvm::AllocaInst *> vOpt = CreateAndLinkEntryBlockAlloc(channelRtPtrTy(), n->channelSymbol);
    if (!vOpt)
    {
        errorHandler.addError(nullptr, "Failed to generate alloc for channel value, is it somehow void?"); // Should never occur bc int32Ty
        return std::nullopt;
    }
    llvm::AllocaInst *v = vOpt.value();
    builder->CreateStore((fn->args()).begin(), v);

    // Generate code for the block
    for (auto e : n->block->exprs)
    {
        this->accept(e);
    }

    if (!endsInReturn(n->block)) // TODO: THIS SHOULD BECOME ALWAYS TRUE, OR IS IT GIVEN EXIT?
    {
        builder->CreateRet(getUnitValue());
    }

    builder->SetInsertPoint(ins);
    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TDefineTemplateNode *n)
{
    // FIXME: BAD OPT ACCESS
    auto info = n->getType()->getTemplateInfo().value(); 

    for(auto t : n->getType()->getRegisteredTemplates())
    {
        // FIXME: CHECK BOUNDS ARE SAME FOR BOTH?
        
        for(unsigned int i = 0; i < info.templates.size(); i++)
        {
            // info.templates.at(i).second->actingType = t.first.at(i); 
            info.templates.at(i).second->setActingType(t.first.at(i)); 
        }

        // substitute each 
        AcceptType(this, n->getTemplatedNodes());
        std::cout << "2176 " << n->getSymbol()->toString() << std::endl; 
    }

    return std::nullopt; 
}

std::optional<Value *> CodegenVisitor::visit(TExprCopyNode *n)
{
    std::optional<Value *> valOpt = AcceptType(this, n->expr);
    if (!valOpt)
    {
        errorHandler.addError(n->getStart(), "Failed to generate code");
        return std::nullopt;
    }

    Value *stoVal = valOpt.value();

    if (n->getType()->requiresDeepCopy())
    {
        auto opt = copyVisitor->deepCopy(builder, n->getType(), stoVal);
        if (!opt)
            return std::nullopt;
        stoVal = opt.value();
    }

    return stoVal;
}

std::optional<Value *> CodegenVisitor::visit(TAsChannelNode *n) // TODO: POSSIBLE PROBLEM AS THIS DUPLICATES THE LENGTH OF AN ARRAY!
{
    std::optional<Value *> valOpt = AcceptType(this, n->expr); // new TExprCopyNode(n->expr, n->token)); // FIXME: WILL THIS LEAK THE TOPLEVEL ARRAY? CANT DEEP COPY EACH INDEPENDENTLY OR ELSE WE WOULD BREAK REFERENCES!

    if (!valOpt)
    {
        errorHandler.addError(n->getStart(), "Failed to generate code");
        return std::nullopt;
    }

    Value *loadedVal = valOpt.value();
    const TypeArray *arrayType = [this, n, &loadedVal]() -> const TypeArray *
    {
        const Type *ty = n->expr->getType();
        if (const TypeArray *arrayType = dynamic_cast<const TypeArray *>(ty))
        {
            // FIXME: ONLY NEEDED BC CANT SPECIFY THAT THIS IS AN LVALUE!!!
            AllocaInst *stoVal = CreateEntryBlockAlloc(loadedVal->getType(), "cast_arr");
            builder->CreateStore(loadedVal, stoVal);
            loadedVal = stoVal;
            return arrayType;
        }

        // FIXME: NEEDED BC NO LVALUE
        const TypeArray *arrTy = new TypeArray(ty, 1);

        // TODO: Remove Array and make things use pointers?
        AllocaInst *saveBlock = CreateEntryBlockAlloc(arrTy->getLLVMType(module), "createdArray");

        Value *stoLoc = builder->CreateGEP(saveBlock, {Int32Zero, Int32Zero});
        builder->CreateStore(loadedVal, stoLoc);

        loadedVal = saveBlock; // builder->CreateLoad(saveBlock->getType(), saveBlock);

        return arrTy;
    }();

    // TODO: TURN INTO FN?
    // FIXME: VERY SIMILAR TO TSend

    llvm::ArrayType *arrayPtrTy = llvm::ArrayType::get(i8p, arrayType->getLength());
    AllocaInst *saveBlock = CreateEntryBlockAlloc(arrayPtrTy, "save_blk");

    // FIXME: SIMILAR TO DEEP COPY VISITOR

    AllocaInst *loop_index = CreateEntryBlockAlloc(Int32Ty, "idx");
    AllocaInst *loop_len = CreateEntryBlockAlloc(Int32Ty, "len");
    builder->CreateStore(Int32Zero, loop_index);
    builder->CreateStore(getU32(arrayType->getLength()), loop_len);

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
        Value *stoLoc = builder->CreateGEP(saveBlock, {Int32Zero,
                                                       builder->CreateLoad(Int32Ty, loop_index)});

        Value *readLoc = builder->CreateGEP(loadedVal, {Int32Zero,
                                                        builder->CreateLoad(Int32Ty, loop_index)});

        Value *read = builder->CreateLoad(readLoc->getType()->getPointerElementType(), readLoc); // FIXME: MALLOCS SEEM EXCESSIVE, SEE ABOUT DOING BETTER!!

        Value *v = builder->CreateCall(getMalloc(), {getU32(getSizeForValue(read))});
        Value *casted = builder->CreateBitCast(v, read->getType()->getPointerTo());

        builder->CreateStore(read, casted);
        Value *corrected = builder->CreateBitCast(v, i8p);

        builder->CreateStore(corrected, stoLoc);
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

    // Convert [n x i8*] to i8**
    Value *arrayStart = builder->CreateBitCast(
        builder->CreateGEP(saveBlock, {Int32Zero, Int32Zero}),
        Int8PtrPtrTy);

    // return saveBlock;
    return builder->CreateCall(get_arrayToChannel(), {arrayStart, builder->CreateLoad(Int32Ty, loop_len)});
}

std::optional<Value *> CodegenVisitor::correctNullOptionalToSum(RecvMetadata meta, Value *original)
{
    if(!meta.actingType)
    {
         errorHandler.addError(nullptr, "Trying to correct a nullOptional to a sum, but we aren't a null optional");
        return std::nullopt;
    }

    const TypeSum * sum = meta.actingType.value(); 

    uint32_t unitIndex = sum->getIndex(module, Types::UNIT->getLLVMType(module));
    
    if (unitIndex == 0) // Shouldn't be a problem...
    {
        errorHandler.addError(nullptr, "Trying to correct a nullOptional to a sum, but the sum doesn't allow for a Unit case");
        return std::nullopt;
    }

    // TODO: DO NULL OPTIONALS BETTER!
    if (sum->getCases().size() != 2)
    {
        errorHandler.addError(nullptr, "Trying to correct a nullOptional to a sum, but sum doesn't have exactly two cases");
        return std::nullopt;
    }

    llvm::Type * valueType = meta.protocolType->getLLVMType(module);
    uint32_t valueIndex = sum->getIndex(module, valueType);

    if (valueIndex == 0)
    {
        errorHandler.addError(nullptr, "Trying to correct a nullOptional to a sum, but the sum doesn't allow for a value case");
        return std::nullopt;
    }


    llvm::Type *sumTy = sum->getLLVMType(module);
    llvm::AllocaInst *alloc = CreateEntryBlockAlloc(sumTy, "");

    Value *tagPtr = builder->CreateGEP(alloc, {Int32Zero, Int32Zero});

    builder->CreateStore(getU32(unitIndex), tagPtr); // TODO: IS THIS WASTEFUL AS OPPOSED TO BRANCH?

    // Get the condition that the if statement is for

    Value *rawEquality = builder->CreateICmpNE(original, Constant::getNullValue(original->getType())); // llvm::ConstantPointerNull::get(original->getType()->getPointerTo()));
    Value *cond = builder->CreateZExtOrTrunc(rawEquality, Int1Ty);

    // AcceptType(this, n->cond);

    /*
     * Generate the basic blocks for then, else, and the remaining code.
     * (NOTE: We set rest to be else if there is no else branch).
     */
    auto parentFn = builder->GetInsertBlock()->getParent();

    BasicBlock *thenBlk = BasicBlock::Create(module->getContext(), "val-opt", parentFn);
    BasicBlock *restBlk = BasicBlock::Create(module->getContext(), "rest");

    builder->CreateCondBr(cond, thenBlk, restBlk);

    /*
     * Then block
     */
    builder->SetInsertPoint(thenBlk);
    builder->CreateStore(getU32(valueIndex), tagPtr);

    Value *valuePtr = builder->CreateGEP(alloc, {Int32Zero, Int32One});

    Value *corrected = builder->CreateBitCast(valuePtr, valueType->getPointerTo());
    Value *castedValue = builder->CreateBitCast(original, valueType->getPointerTo());
    Value *loadedValue = builder->CreateLoad(castedValue);
    builder->CreateStore(loadedValue, corrected);

    builder->CreateBr(restBlk);

    thenBlk = builder->GetInsertBlock();

    /*
     * Insert the else block (same as rest if no else branch)
     */
    parentFn->getBasicBlockList().push_back(restBlk);
    builder->SetInsertPoint(restBlk);

    // return builder->CreateLoad(sumTy, alloc);
    return alloc;
}


std::string CodegenVisitor::getCodegenAllocationID(Symbol * sym)
{
    std::string name = sym->getUniqueNameInScope(); 

    std::optional<Scope *> scopeOpt = sym->getScope(); 
    while(scopeOpt)
    {
        Scope * scope = scopeOpt.value(); 
        std::string scopeName = scope->getName();

        if(scopeName != "")
            name = scopeName + "::" + name; 

        scopeOpt = scope->getParent();
    }

    return name;
}

std::string CodegenVisitor::getCodegenID(Symbol * sym)
{
    if(!sym->isDefinition())
        return sym->getUniqueNameInScope();

    return getCodegenAllocationID(sym); 
}

void CodegenVisitor::setAllocation(Symbol * sym, llvm::AllocaInst * a)
{
    allocations.insert({getCodegenAllocationID(sym), a});
}

std::optional<llvm::AllocaInst *> CodegenVisitor::getAllocation(Symbol * sym) {
    auto it = allocations.find(getCodegenAllocationID(sym)); 
    if(it == allocations.end()) return std::nullopt; 
    return it->second; 
}

llvm::AllocaInst * CodegenVisitor::CreateAndLinkEntryBlockAlloc(llvm::Type * ty, Symbol * sym)
{
    llvm::AllocaInst *v = CreateEntryBlockAlloc(ty, getCodegenID(sym));
    setAllocation(sym, v); 
    return v; 
}

llvm::Type * CodegenVisitor::getLLVMType(Symbol * sym)
{
    // FIXME: ADD TEMPLATE CHECK!
    return sym->getType()->getLLVMType(module); 
}