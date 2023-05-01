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
        if (std::holds_alternative<TProgramDefNode *>(e))
        {
            TProgramDefNode *octx = std::get<TProgramDefNode *>(e);

            const TypeProgram *type = octx->getType();

            Function *fn = Function::Create(type->getLLVMFunctionType(module), GlobalValue::ExternalLinkage, octx->name, module);
            type->setName(fn->getName().str());
        }
        else if (std::holds_alternative<TLambdaConstNode *>(e))
        {
            TLambdaConstNode *octx = std::get<TLambdaConstNode *>(e);

            const TypeInvoke *type = octx->getType();

            Function *fn = Function::Create(type->getLLVMFunctionType(module), GlobalValue::ExternalLinkage, octx->name, module);
            type->setName(fn->getName().str());
        }
    }

    for (auto e : n->externs)
    {
        AcceptType(this, e);
    }

    for (auto e : n->defs)
    {
        // Generate code for statement
        if (std::holds_alternative<TProgramDefNode *>(e))
        {
            TProgramDefNode *a = std::get<TProgramDefNode *>(e);
            AcceptType(this, a);
        }
        else if (std::holds_alternative<TLambdaConstNode *>(e))
        {
            TLambdaConstNode *a = std::get<TLambdaConstNode *>(e);
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
    BasicBlock *mergeBlk = BasicBlock::Create(module->getContext(), "matchcont");

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

        llvm::Type *toFind = localSym->type->getLLVMType(module);

        unsigned int index = sumType->getIndex(module, toFind);

        if (index == 0)
        {
            errorHandler.addError(n->getStart(), "Unable to find key for type " + localSym->type->toString() + " in sum");
            return std::nullopt;
        }

        BasicBlock *matchBlk = BasicBlock::Create(module->getContext(), "tagBranch" + std::to_string(index));

        builder->SetInsertPoint(matchBlk);

        switchInst->addCase(ConstantInt::get(Int32Ty, index, true), matchBlk);
        origParent->getBasicBlockList().push_back(matchBlk);

        //  Get the type of the symbol
        llvm::Type *ty = localSym->type->getLLVMType(module);

        // Can skip global stuff
        llvm::AllocaInst *v = CreateEntryBlockAlloc(ty, localSym->getIdentifier());
        // *localSym->val = v;
        localSym->setAllocation(v); 
        // varSymbol->val = v;

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
    BasicBlock *mergeBlk = BasicBlock::Create(module->getContext(), "matchcont");

    // Attempt to cast the check; if this fails, then codegen for the check failed
    Symbol *sym = n->sym;
    std::optional<llvm::AllocaInst *> optVal = sym->getAllocation(); 

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in case: " + n->sym->getIdentifier());
        return std::nullopt;
    }

    Value *chanVal = optVal.value();
    // ReadProjection
    Value *tag = builder->CreateCall(getReadProjection(), {builder->CreateLoad(Int32Ty, chanVal)});

    llvm::SwitchInst *switchInst = builder->CreateSwitch(tag, mergeBlk, n->cases.size());

    // for (std::pair<Symbol *, TypedNode *> caseNode : n->cases)
    for (unsigned int i = 0; i < n->cases.size(); i++)
    {
        // TODO: find a way to error handle cases where correct block DNE or something
        BasicBlock *matchBlk = BasicBlock::Create(module->getContext(), "tagBranch" + std::to_string(i + 1));

        builder->SetInsertPoint(matchBlk);

        switchInst->addCase(ConstantInt::get(Int32Ty, i + 1, true), matchBlk);
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
    std::optional<llvm::AllocaInst *> optVal = sym->getAllocation(); 

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in case: " + n->sym->getIdentifier());
        return std::nullopt;
    }

    Value *chanVal = optVal.value();

    builder->CreateCall(getWriteProjection(), {builder->CreateLoad(Int32Ty, chanVal),
                                               ConstantInt::get(Int32Ty, n->projectIndex, false)});
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
            if (const TypeSum *sum = dynamic_cast<const TypeSum *>(n->paramType.at(args.size()))) // argNodes.at(args.size())->getType()))
            {
                val = correctSumAssignment(sum, val);
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
    std::optional<llvm::AllocaInst *> optVal = sym->getAllocation(); 

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in recv: " + n->sym->getIdentifier());
        return std::nullopt;
    }

    Value *chanVal = optVal.value();

    llvm::Type *recvType = n->ty->getLLVMType(module);

    Value *valPtr = builder->CreateCall(getReadChannel(), {builder->CreateLoad(Int32Ty, chanVal)}); // Will be a void*
    Value *casted = builder->CreateBitCast(valPtr, recvType->getPointerTo());                       // Cast the void* to the correct type ptr

    Value *ans = builder->CreateLoad(recvType, casted);

    builder->CreateCall(getFree(), {valPtr}); // May leak depending on how GC works?

    return ans;
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
    std::optional<Value *> valOpt = AcceptType(this, n->expr);
    if (!valOpt)
    {
        errorHandler.addError(n->getStart(), "Failed to generate code");
        return std::nullopt;
    }

    Symbol *sym = n->sym;

    Value *stoVal = valOpt.value();

    // Same as return node's
    if (const TypeSum *sum = dynamic_cast<const TypeSum *>(n->lType))
    {
        stoVal = correctSumAssignment(sum, stoVal);
    }

    // std::optional<Value *> v = copyVisitor->deepCopy(builder, n->lType, stoVal);
    std::optional<Value *> v = [this, n, &stoVal]() -> std::optional<Value *>
    {
        if (n->lType->requiresDeepCopy())
        {
            // Function *fn = n->lType->clone(module, builder);
            // if (fn == nullptr)
            // {
            //     errorHandler.addError(n->getStart(), "Failed to generate clone fn for type: " + n->lType->toString());
            //     return std::nullopt;
            // }
            // Value *addrMap = getNewAddressMap();
            // stoVal = builder->CreateCall(fn, {stoVal, addrMap});
            // deleteAddressMap(addrMap);
            auto opt = copyVisitor->deepCopy(builder, n->lType, stoVal);
            if (!opt)
                return std::nullopt;
            stoVal = opt.value();
        }

        Value *v = builder->CreateCall(getMalloc(), {builder->getInt32(module->getDataLayout().getTypeAllocSize(stoVal->getType()))});
        Value *casted = builder->CreateBitCast(v, stoVal->getType()->getPointerTo());

        builder->CreateStore(stoVal, casted);

        return v;
    }();

    // std::optional<Value *> v = [this, n, &stoVal]() -> std::optional<Value *>
    // {
    //     if (n->lType->requiresDeepCopy())
    //     {
    //         Function *fn = n->lType->clone(module, builder);
    //         if (fn == nullptr)
    //         {
    //             errorHandler.addError(n->getStart(), "Failed to generate clone fn for type: " + n->lType->toString());
    //             return std::nullopt;
    //         }
    //         Value *addrMap = getNewAddressMap();
    //         stoVal = builder->CreateCall(fn, {stoVal, addrMap});
    //         deleteAddressMap(addrMap);
    //         // return v;
    //     }

    //     Value *v = builder->CreateCall(getMalloc(), {builder->getInt32(module->getDataLayout().getTypeAllocSize(stoVal->getType()))});
    //     Value *casted = builder->CreateBitCast(v, stoVal->getType()->getPointerTo());

    //     builder->CreateStore(stoVal, casted);

    //     return v;
    // }();

    if (!v)
        return std::nullopt; // Error handled already.

    Value *corrected = builder->CreateBitCast(v.value(), i8p);
    std::optional<llvm::AllocaInst *> optVal = sym->getAllocation(); 

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in send: " + n->sym->getIdentifier());
        return std::nullopt;
    }

    Value *chanVal = optVal.value();
    builder->CreateCall(getWriteChannel(), {builder->CreateLoad(Int32Ty, chanVal), corrected}); // Will be a void*
    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TProgramContractNode *n)
{
    Symbol *sym = n->sym;
    std::optional<llvm::AllocaInst *> optVal = sym->getAllocation(); 

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in contract: " + n->sym->getIdentifier());
        return std::nullopt;
    }

    Value *chanVal = optVal.value();

    builder->CreateCall(getContractChannel(), {builder->CreateLoad(Int32Ty, chanVal)});

    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TProgramWeakenNode *n)
{
    Symbol *sym = n->sym;
    std::optional<llvm::AllocaInst *> optVal = sym->getAllocation(); 

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in weaken: " + n->sym->getIdentifier());
        return std::nullopt;
    }

    Value *chanVal = optVal.value();

    builder->CreateCall(getWeakenChannel(), {builder->CreateLoad(Int32Ty, chanVal)});

    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TProgramAcceptNode *n)
{
    // Very similar to regular loop

    Symbol *sym = n->sym;
    std::optional<llvm::AllocaInst *> optVal = sym->getAllocation(); 

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in accept: " + n->sym->getIdentifier());
        return std::nullopt;
    }

    Value *chanVal = optVal.value();

    auto checkFn = getShouldLoop();
    Value *check = builder->CreateCall(checkFn, {builder->CreateLoad(Int32Ty, chanVal)});

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
        // e->accept(this);
        AcceptType(this, e);
    }

    // Re-calculate the loop condition
    check = builder->CreateCall(checkFn, {builder->CreateLoad(Int32Ty, chanVal)});

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
    // FIXME: Somewhat inefficient due to dequeuing

    Symbol *sym = n->sym;
    std::optional<llvm::AllocaInst *> optVal = sym->getAllocation(); 

    if (!optVal)
    {
        errorHandler.addError(n->getStart(), "Could not find value for channel in accept: " + n->sym->getIdentifier());
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
    Value *check = builder->CreateCall(getShouldAcceptWhileLoop(), {builder->CreateLoad(Int32Ty, chanVal)});

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
    // builder->CreateCall(getPopEndLoop(), {builder->CreateLoad(Int32Ty, chanVal)});

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
    llvm::AllocaInst *v = CreateEntryBlockAlloc(ty, "");
    {
        unsigned i = 0;
        std::vector<std::pair<std::string, const Type *>> elements = product->getElements();

        for (Value *a : args)
        {
            if (const TypeSum *sum = dynamic_cast<const TypeSum *>(elements.at(i).second))
            {
                a = correctSumAssignment(sum, a);
            }

            Value *ptr = builder->CreateGEP(v, {Int32Zero, ConstantInt::get(Int32Ty, i, true)});

            builder->CreateStore(a, ptr);

            i++;
        }
    }

    Value *loaded = builder->CreateLoad(v->getType()->getPointerElementType(), v);
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

    if (const TypeSum *sum = dynamic_cast<const TypeSum *>(box->getInnerType()))
    {
        stoVal = correctSumAssignment(sum, stoVal);
    }

    Value *v = builder->CreateCall(getGCMalloc(), {builder->getInt64(module->getDataLayout().getTypeAllocSize(stoVal->getType()))});
    Value *casted = builder->CreateBitCast(v, box->getLLVMType(module));

    builder->CreateStore(stoVal, casted);

    // Value *loaded = builder->CreateLoad(v->getType()->getPointerElementType(), v);
    return casted;
}

std::optional<Value *> CodegenVisitor::visit(TArrayAccessNode *n)
{
    std::optional<Value *> index = AcceptType(this, n->indexExpr);

    if (!index)
    {
        errorHandler.addError(n->getStart(), "Failed to generate code in TvisitArrayAccess for index!");
        return std::nullopt;
    }

    std::optional<Value *> arrayPtr = AcceptType(this, n->field);
    if (!arrayPtr)
    {
        errorHandler.addError(n->getStart(), "Failed to locate array in access");
        return std::nullopt;
    }

    Value *v = arrayPtr.value();

    auto ptr = builder->CreateGEP(v, {Int32Zero, index.value()});

    if (n->is_rvalue)
        return builder->CreateLoad(ptr->getType()->getPointerElementType(), ptr);
    return ptr;
}

std::optional<Value *> CodegenVisitor::visit(TIntConstExprNode *n)
{
    return builder->getInt32(n->value);
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

        return builder->CreateNSWSub(builder->getInt32(0), innerVal.value());
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
    phi->addIncoming(lastValue, builder->GetInsertBlock()); // Have to use insert block as, due to nested short circuiting, its possible that the insert block isnt actually the entryblock anymore

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
    phi->addIncoming(lastValue, builder->GetInsertBlock()); // Have to use insert block as, due to nested short circuiting, its possible that the insert block isnt actually the entryblock anymore

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
    Symbol *sym = n->symbol;

    if (!sym->type)
    {
        errorHandler.addError(n->getStart(), "Improperly initialized symbol in field access: " + n->symbol->getIdentifier());
        return std::nullopt;
    }

    if (n->accesses.size() > 0 && n->accesses.at(n->accesses.size() - 1).first == "length")
    {
        const Type *modOpt = (n->accesses.size() > 1) ? n->accesses.at(n->accesses.size() - 2).second : sym->type;
        if (const TypeArray *ar = dynamic_cast<const TypeArray *>(modOpt))
        {
            // If it is, correctly, an array type, then we can get the array's length (this is the only operation currently, so we can just do thus)
            Value *v = builder->getInt32(ar->getLength());

            return v;
        }

        // Can't throw error b/c length could be field of struct
    }

    const Type *ty = sym->type;
    std::optional<Value *> baseOpt = visitVariable(sym, n->accesses.size() == 0 ? n->is_rvalue : false);

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
        if (const TypeStruct *s = dynamic_cast<const TypeStruct *>(ty))
        {
            std::string field = n->accesses.at(i).first;
            std::optional<unsigned int> indexOpt = s->getIndex(field);

            if (!indexOpt)
            {
                errorHandler.addError(n->getStart(), "Could not lookup " + field);
                return std::nullopt;
            }

            unsigned int index = indexOpt.value();
            addresses.push_back(ConstantInt::get(Int32Ty, index, false));

            const Type *fieldType = n->accesses.at(i).second;
            ty = fieldType;
        }
        else
        {
            errorHandler.addError(n->getStart(), "Could not perform field access. Got type: " + ty->toString());
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

    if (!symbol->type)
    {
        errorHandler.addError(n->getStart(), "Type for extern statement not correctly bound! Probably a compiler error.");
        return std::nullopt;
    }

    const TypeInvoke *type = n->getType();

    Function *fn = Function::Create(type->getLLVMFunctionType(module), GlobalValue::ExternalLinkage, symbol->getIdentifier(), module);
    type->setName(fn->getName().str());

    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(TAssignNode *n)
{
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
    std::optional<Value *> val = AcceptType(this, n->var); // varSym->val;

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
    // Sanity check to ensure that we now have a value for the variable
    if (!val)
    {
        errorHandler.addError(n->getStart(), "1184 - Improperly initialized variable in assignment: " + n->var->toString());
        return std::nullopt;
    }

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
    if (const TypeSum *sum = dynamic_cast<const TypeSum *>(varSymType)) // FIXME: WILL THIS WORK IF USING TYPE INF?
    {
        unsigned int index = sum->getIndex(module, stoVal->getType());

        if (index == 0)
        {
            // Value *corrected = builder->CreateBitCast(stoVal, varSymType->getLLVMType(module));
            // builder->CreateStore(corrected, v);
            Value *corrected = builder->CreateBitCast(v, stoVal->getType()->getPointerTo());
            builder->CreateStore(stoVal, corrected);
            return std::nullopt;
        }
        Value *tagPtr = builder->CreateGEP(v, {Int32Zero, Int32Zero});

        builder->CreateStore(ConstantInt::get(Int32Ty, index, true), tagPtr);
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
            //  Get the type of the symbol
            llvm::Type *ty = varSymbol->type->getLLVMType(module);
            ty = varSymbol->type->getLLVMType(module);
            // Branch depending on if the var is global or not
            if (varSymbol->isGlobal)
            {
                // If it is global, then we need to insert a new global variable of this type.
                // A lot of these options are done to make it match what a C program would
                // generate for global vars
                module->getOrInsertGlobal(varSymbol->getIdentifier(), ty);
                llvm::GlobalVariable *glob = module->getNamedGlobal(varSymbol->getIdentifier());
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
                llvm::AllocaInst *v = CreateEntryBlockAlloc(ty, varSymbol->getIdentifier());
                // *varSymbol->val = v;
                varSymbol->setAllocation(v);

                // Similarly, if we have an expression for the local var, we can store it. Otherwise, we can leave it undefined.
                if (e->val)
                {
                    Value *stoVal = exVal.value();
                    if (const TypeSum *sum = dynamic_cast<const TypeSum *>(varSymbol->type)) // FIXME: WILL THIS WORK IF USING TYPE INF? - ONLY WORKS BC TYPEINF CANT INFER A -> A + B.
                    {
                        unsigned int index = sum->getIndex(module, stoVal->getType());

                        if (index == 0)
                        {
                            // Value *corrected = builder->CreateBitCast(stoVal, varSymbol->type->getLLVMType(module));
                            Value *corrected = builder->CreateBitCast(v, stoVal->getType()->getPointerTo());
                            builder->CreateStore(stoVal, corrected);
                            return std::nullopt;
                        }

                        Value *tagPtr = builder->CreateGEP(v, {Int32Zero, Int32Zero});

                        builder->CreateStore(ConstantInt::get(Int32Ty, index, true), tagPtr);
                        Value *valuePtr = builder->CreateGEP(v, {Int32Zero, Int32One});

                        Value *corrected = builder->CreateBitCast(valuePtr, stoVal->getType()->getPointerTo());
                        builder->CreateStore(stoVal, corrected);
                    }
                    else
                    {
                        builder->CreateStore(stoVal, v);
                    }
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

    BasicBlock *restBlk = n->falseOpt ? BasicBlock::Create(module->getContext(), "ifcont")
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
    BasicBlock *mergeBlk = BasicBlock::Create(module->getContext(), "ifcont");

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

        if (const TypeSum *sum = dynamic_cast<const TypeSum *>(expr.first))
        {
            inner = correctSumAssignment(sum, inner);
        }

        // As the code was generated correctly, build the return statement; we ensure no following code due to how block visitors work in semantic analysis.
        return builder->CreateRet(inner);
    }

    // If there is no value, return void. We ensure no following code and type-correctness in the semantic pass.
    return builder->CreateRetVoid();
}

std::optional<Value *> CodegenVisitor::visit(TExitNode *n)
{
    // If there is no value, return void. We ensure no following code and type-correctness in the semantic pass.
    return builder->CreateRetVoid();
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

    const TypeInvoke *type = n->getType();

    llvm::FunctionType *fnType = type->getLLVMFunctionType(module);

    Function *fn = type->getLLVMName() ? module->getFunction(type->getLLVMName().value()) : Function::Create(fnType, GlobalValue::PrivateLinkage, n->name, module);
    type->setName(fn->getName().str()); // Note: NOT ALWAYS NEEDED

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

        std::string argName = param->getIdentifier();

        // Create an allocation for the argument
        llvm::AllocaInst *v = CreateEntryBlockAlloc(type, argName);

        // *param->val = v;
        param->setAllocation(v); 

        builder->CreateStore(&arg, v);
    }

    // Generate code for the block
    for (auto e : n->block->exprs)
    {
        AcceptType(this, e);
    }


    // Needed to help make the branching programs work due to switches being exhaustive. Will have to do this better eventually!
    llvm::Instruction * inst = &*(builder->GetInsertBlock()->rbegin());
    if(!dyn_cast<llvm::ReturnInst>(inst))
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