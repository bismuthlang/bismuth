#include "CodegenVisitor.h"

std::optional<Value *> CodegenVisitor::visit(CompilationUnitNode *n)
{
    /***********************************
     *
     *
     * Runtime Stuff
     *
     *
     ***********************************/

    {
        {
            llvm::FunctionType *writeChanFnTy = llvm::FunctionType::get(
                VoidTy,
                {Int32Ty,
                 i8p},
                false);

            Function *fn = Function::Create(writeChanFnTy, GlobalValue::ExternalLinkage, "WriteChannel", module);
        }

        {
            Function::Create(
                llvm::FunctionType::get(
                    i8p,
                    {Int32Ty},
                    false),
                GlobalValue::ExternalLinkage,
                "ReadChannel",
                module);
        }

        {
            Function::Create(
                llvm::FunctionType::get(
                    Int32Ty,
                    {llvm::FunctionType::get(
                         VoidTy,
                         {Int32Ty},
                         false)
                         ->getPointerTo()},
                    false),
                GlobalValue::ExternalLinkage,
                "Execute",
                module);
        }

        {
            Function::Create(
                llvm::FunctionType::get(
                    i8p,
                    {Int32Ty},
                    false),
                GlobalValue::ExternalLinkage,
                "malloc",
                module);
        }

        {
            Function::Create(
                llvm::FunctionType::get(
                    Int1Ty,
                    {Int32Ty},
                    false),
                GlobalValue::ExternalLinkage,
                "ShouldLoop",
                module);
        }

        {
            Function::Create(
                llvm::FunctionType::get(
                    VoidTy,
                    {Int32Ty},
                    false),
                GlobalValue::ExternalLinkage,
                "ContractChannel",
                module);
        }

        {
            Function::Create(
                llvm::FunctionType::get(
                    VoidTy,
                    {Int32Ty},
                    false),
                GlobalValue::ExternalLinkage,
                "WeakenChannel",
                module);
        }

        // FIXME: INCLUDE ONLY IF NEEDED
        // {
        //     Function::Create(
        //         llvm::FunctionType::get(
        //             VoidTy,
        //             {Int32Ty,
        //              Int32Ty},
        //             false),
        //         GlobalValue::ExternalLinkage,
        //         "WriteProjection",
        //         module);
        // }

        // {
        //     Function::Create(
        //         llvm::FunctionType::get(
        //             Int32Ty,
        //             {Int32Ty},
        //             false),
        //         GlobalValue::ExternalLinkage,
        //         "ReadProjection",
        //         module);
        // }
    }

    /***********************************
     *
     *
     * Actual Code
     *
     *
     ***********************************/
    for (auto e : n->defs)
    {
        if (std::holds_alternative<ProgramDefNode *>(e)) // ProgramDefNode *octx = dynamic_cast<ProgramDefNode *>(e)) // FIXME: MAY USE WRONG TYPE HERE IN SEMANTIC ANALYSIS!
        {

            ProgramDefNode *octx = std::get<ProgramDefNode *>(e);

            const TypeProgram *type = octx->getType();

            llvm::Type *genericType = type->getLLVMType(module)->getPointerElementType();

            if (llvm::FunctionType *fnType = static_cast<llvm::FunctionType *>(genericType))
            {
                Function *fn = Function::Create(fnType, GlobalValue::ExternalLinkage, octx->name, module);
                type->setName(fn->getName().str());
            }
            else
            {
                errorHandler.addCodegenError(nullptr, "Could not treat function type as function.");
                return {};
            }
        }
        else if (std::holds_alternative<LambdaConstNode *>(e)) // ProgramDefNode *octx = dynamic_cast<ProgramDefNode *>(e)) // FIXME: MAY USE WRONG TYPE HERE IN SEMANTIC ANALYSIS!
        {
            LambdaConstNode *octx = std::get<LambdaConstNode *>(e);

            const TypeInvoke *type = octx->getType();

            llvm::Type *genericType = type->getLLVMType(module)->getPointerElementType();

            if (llvm::FunctionType *fnType = static_cast<llvm::FunctionType *>(genericType))
            {
                Function *fn = Function::Create(fnType, GlobalValue::ExternalLinkage, octx->name, module);
                type->setName(fn->getName().str());
            }
            else
            {
                errorHandler.addCodegenError(nullptr, "Could not treat function type as function.");
                return {};
            }
        }
        // else if (std::holds_alternative<DefineEnumNode *>(e)) // FIXME: DO BETTER
        // {
        //     DefineEnumNode *a = std::get<DefineEnumNode *>(e);
        //     AcceptType(this, a); // TODO: remove this?
        // }
        // else
        // {
        //     DefineStructNode *a = std::get<DefineStructNode *>(e);
        //     AcceptType(this, a); // TODO: remove this?
        // }
    }

    for (auto e : n->externs)
    {
        AcceptType(this, e);
    }

    for (auto e : n->defs)
    {
        // Generate code for statement
        if (std::holds_alternative<ProgramDefNode *>(e))
        {
            ProgramDefNode *a = std::get<ProgramDefNode *>(e);
            AcceptType(this, a);
        }
        else if (std::holds_alternative<LambdaConstNode *>(e))
        {
            LambdaConstNode *a = std::get<LambdaConstNode *>(e);
            AcceptType(this, a);
        }
    }

    /*******************************************
     * Extra checks depending on compiler flags
     *******************************************/

    if (flags & CompilerFlags::NO_RUNTIME)
    {
        /*
         * Need to create main method and invoke program()
         * Based on semantic analysis, both of these should be defined.
         *
         * This will segfault if not found, but, as stated, that should be impossible.
         */

        FunctionType *mainFuncType = FunctionType::get(Int32Ty, {Int32Ty, Int8PtrPtrTy}, false);
        Function *mainFunc = Function::Create(mainFuncType, GlobalValue::ExternalLinkage, "main", module);

        // Create block to attach to main
        BasicBlock *bBlk = BasicBlock::Create(module->getContext(), "entry", mainFunc);
        builder->SetInsertPoint(bBlk);

        llvm::Function *progFn = module->getFunction("program");
        builder->CreateRet(builder->CreateCall(progFn, {}));
    }

    return {};
}

std::optional<Value *> CodegenVisitor::visit(MatchStatementNode *n)
{
    const TypeSum *sumType = n->matchType;

    auto origParent = builder->GetInsertBlock()->getParent();
    BasicBlock *mergeBlk = BasicBlock::Create(module->getContext(), "matchcont");

    // Attempt to cast the check; if this fails, then codegen for the check failed
    std::optional<Value *> optVal = AcceptType(this, n->checkExpr);

    // Check that the optional, in fact, has a value. Otherwise, something went wrong.
    if (!optVal)
    {
        errorHandler.addCodegenError(nullptr, "Failed to generate code for: 202"); // FIXME: DO BETTER + ctx->check->getText());
        return {};
    }

    Value *sumVal = optVal.value();
    llvm::AllocaInst *SumPtr = builder->CreateAlloca(sumVal->getType());
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
            errorHandler.addCodegenError(nullptr, "Unable to find key for type " + localSym->type->toString() + " in sum");
            return {};
        }

        BasicBlock *matchBlk = BasicBlock::Create(module->getContext(), "tagBranch" + std::to_string(index));

        builder->SetInsertPoint(matchBlk);

        switchInst->addCase(ConstantInt::get(Int32Ty, index, true), matchBlk);
        origParent->getBasicBlockList().push_back(matchBlk);

        //  Get the type of the symbol
        llvm::Type *ty = localSym->type->getLLVMType(module);

        // Can skip global stuff
        llvm::AllocaInst *v = builder->CreateAlloca(ty, 0, localSym->getIdentifier());
        localSym->val = v;
        // varSymbol->val = v;

        // Now to store the var
        Value *valuePtr = builder->CreateGEP(SumPtr, {Int32Zero, Int32One});
        Value *corrected = builder->CreateBitCast(valuePtr, ty->getPointerTo());

        Value *val = builder->CreateLoad(ty, corrected);

        builder->CreateStore(val, v);

        // altCtx->eval->accept(this);
        AcceptType(this, caseNode.second);

        if (BlockNode *blkStmtCtx = dynamic_cast<BlockNode *>(caseNode.second))
        {
            if (!endsInReturn(blkStmtCtx))
            {
                builder->CreateBr(mergeBlk);
            }
            // if it ends in a return, we're good!
        }
        else if (ReturnNode *retCtx = dynamic_cast<ReturnNode *>(caseNode.second))
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

    return {};
}

std::optional<Value *> CodegenVisitor::visit(ChannelCaseStatementNode *n)
{
    auto origParent = builder->GetInsertBlock()->getParent();
    BasicBlock *mergeBlk = BasicBlock::Create(module->getContext(), "matchcont");

    // Attempt to cast the check; if this fails, then codegen for the check failed
    Symbol *sym = n->sym;

    if (!sym->val)
    {
        errorHandler.addCodegenError(nullptr, "Could not find value for channel in case: " + n->sym->getIdentifier()); // FIXME: DO BETTER
        return {};
    }

    Value *chanVal = sym->val.value();
    // ReadProjection
    Value *tag = builder->CreateCall(getReadProjection(), {builder->CreateLoad(Int32Ty, chanVal)});

    llvm::SwitchInst *switchInst = builder->CreateSwitch(tag, mergeBlk, n->cases.size());

    // for (std::pair<Symbol *, TypedNode *> caseNode : n->cases)
    for (unsigned int i = 0; i < n->cases.size(); i++)
    {
        // FIXME: find a way to error handle cases where coreetc block DNE or something
        BasicBlock *matchBlk = BasicBlock::Create(module->getContext(), "tagBranch" + std::to_string(i + 1));

        builder->SetInsertPoint(matchBlk);

        switchInst->addCase(ConstantInt::get(Int32Ty, i + 1, true), matchBlk);
        origParent->getBasicBlockList().push_back(matchBlk);

        // altCtx->eval->accept(this);
        TypedNode *caseNode = n->cases.at(i);

        AcceptType(this, caseNode);

        if (BlockNode *blkStmtCtx = dynamic_cast<BlockNode *>(caseNode))
        {
            if (!endsInReturn(blkStmtCtx))
            {
                builder->CreateBr(mergeBlk);
            }
            // if it ends in a return, we're good!
        }
        else if (ReturnNode *retCtx = dynamic_cast<ReturnNode *>(caseNode))
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

    return {};
}

std::optional<Value *> CodegenVisitor::visit(ProgramProjectNode *n)
{
    Symbol *sym = n->sym;

    if (!sym->val)
    {
        errorHandler.addCodegenError(nullptr, "Could not find value for channel in case: " + n->sym->getIdentifier()); // FIXME: DO BETTER
        return {};
    }

    Value *chanVal = sym->val.value();

    builder->CreateCall(getWriteProjection(), {builder->CreateLoad(Int32Ty, chanVal),
                                                                 ConstantInt::get(Int32Ty, n->projectIndex, false)}); 
    return {};
}

std::optional<Value *> CodegenVisitor::visit(InvocationNode *n)
{
    // if (const TypeInvoke *inv = dynamic_cast<const TypeInvoke *>(symOpt.value()->type))
    // {
    vector<TypedNode *> argNodes = n->args; // inv->getParamTypes();

    // Create the argument vector
    std::vector<llvm::Value *> args;

    // Populate the argument vector, breaking out of compilation if any argument fails to generate.
    for (TypedNode *e : argNodes)
    {
        std::optional<Value *> valOpt = AcceptType(this, e);
        if (!valOpt)
        {
            errorHandler.addCodegenError(nullptr, "Failed to generate code");
            return {};
        }

        Value *val = valOpt.value();

        if (args.size() < n->paramType.size())
        {
            // TODO: METHODIZE!
            if (const TypeSum *sum = dynamic_cast<const TypeSum *>(n->paramType.at(args.size()))) // argNodes.at(args.size())->getType()))
            {
                unsigned int index = sum->getIndex(module, val->getType());

                if (index != 0)
                {
                    llvm::Type *sumTy = sum->getLLVMType(module);
                    llvm::AllocaInst *alloc = builder->CreateAlloca(sumTy, 0, "");

                    Value *tagPtr = builder->CreateGEP(alloc, {Int32Zero, Int32Zero});

                    builder->CreateStore(ConstantInt::get(Int32Ty, index, true), tagPtr);

                    Value *valuePtr = builder->CreateGEP(alloc, {Int32Zero, Int32One});

                    Value *corrected = builder->CreateBitCast(valuePtr, val->getType()->getPointerTo());
                    builder->CreateStore(val, corrected);

                    val = builder->CreateLoad(sumTy, alloc);
                }
            }
        }

        args.push_back(val);
    }

    // Convert to an array ref, then find and execute the call.
    ArrayRef<Value *> ref = ArrayRef(args);
    // if (ctx->lam)
    // {
    //     std::optional<Value *> callOpt = TvisitLambdaConstExpr(ctx->lam);
    //     if (!callOpt)
    //     {
    //         errorHandler.addCodegenError(ctx->lam->getStart(), "Could not generate code for lambda");
    //         return {};
    //     }
    //     llvm::Function *call = (llvm::Function *)callOpt.value();
    //     Value *val = builder->CreateCall(call, ref); // Needs to be separate line because, C++
    //     return val;
    // }

    // llvm::Function *call = module->getFunction(ctx->VARIABLE()->getText());
    std::optional<Value *> fnOpt = AcceptType(this, n->fn);
    if (!fnOpt)
    {
        errorHandler.addCodegenError(nullptr, "Could not locate function for invocation. Has it been defined in IR yet?");
        return {};
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
    // }

    // errorHandler.addCodegenError(nullptr, "Invocation got non-invokable type!");
    // return {};
}

std::optional<Value *> CodegenVisitor::visit(ProgramRecvNode *n)
{
    Symbol *sym = n->sym;

    if (!sym->val)
    {
        errorHandler.addCodegenError(nullptr, "Could not find value for channel in recv: " + n->sym->getIdentifier()); // FIXME: DO BETTER
        return {};
    }

    Value *chanVal = sym->val.value();

    llvm::Type *recvType = n->ty->getLLVMType(module);

    // FIXME: DO BETTER NEED TO CONVERT TYPES AND LOAD.... but how?
    llvm::Function *progFn = module->getFunction("ReadChannel"); // FIXME: BAD OPTIONAL ACCESS

    Value *valPtr = builder->CreateCall(progFn, {builder->CreateLoad(Int32Ty, chanVal)}); // Will be a void*
    Value *casted = builder->CreateBitCast(valPtr, recvType->getPointerTo());             // Cast the void* to the correct type ptr
    // return builder->Create Store(corrected, )

    // FIXME: Methodize things so that way we don't have to do this as its just a redundant alloca given we have to have another for the var its self...
    // llvm::AllocaInst *v = builder->CreateAlloca(recvType, 0, "");
    // builder->Create Store(casted, v);
    return builder->CreateLoad(recvType, casted);
}

std::optional<Value *> CodegenVisitor::visit(ProgramExecNode *n)
{
    std::optional<Value *> fnOpt = visitVariable(n->sym, true); // FIXME: DO BETTER?

    if (!fnOpt)
    {
        errorHandler.addCodegenError(nullptr, "Could not locate value for invocation: " + n->sym->getIdentifier() + ". Has it been defined in IR yet?");
        return {};
    }

    Value *fnVal = fnOpt.value();

    llvm::Type *ty = fnVal->getType();

    if (llvm::isa<llvm::Function>(fnVal))
    {
        llvm::Function *lambdaThread = static_cast<llvm::Function *>(fnVal);
        llvm::Function *progFn = module->getFunction("Execute");

        Value *val = builder->CreateCall(progFn, {lambdaThread});
        return val;
    }
    // FIXME: REFACTOR, BOTH WITH THIS METHOD AND INVOCATION!

    // llvm::FunctionType *fnType = static_cast<llvm::FunctionType *>(ty->getPointerElementType());
    llvm::Function *progFn = module->getFunction("Execute");
    Value *val = builder->CreateCall(progFn, {fnVal});
    return val;
}

std::optional<Value *> CodegenVisitor::visit(ProgramSendNode *n)
{
    std::optional<Value *> valOpt = AcceptType(this, n->expr); //(ctx->expr->accept(this));
    if (!valOpt)
    {
        errorHandler.addCodegenError(nullptr, "Failed to generate code");
        return {};
    }

    Symbol *sym = n->sym;

    Value *stoVal = valOpt.value(); // FIXMME: STILL NEEDS TO BE DONE

    // Same as return node's
    if (const TypeSum *sum = dynamic_cast<const TypeSum *>(n->lType))
    {
        unsigned int index = sum->getIndex(module, stoVal->getType());

        if (index != 0)
        {
            llvm::Type *sumTy = sum->getLLVMType(module);
            llvm::AllocaInst *alloc = builder->CreateAlloca(sumTy, 0, "");

            Value *tagPtr = builder->CreateGEP(alloc, {Int32Zero, Int32Zero});
            builder->CreateStore(ConstantInt::get(Int32Ty, index, true), tagPtr);

            Value *valuePtr = builder->CreateGEP(alloc, {Int32Zero, Int32One});
            Value *corrected = builder->CreateBitCast(valuePtr, stoVal->getType()->getPointerTo());
            builder->CreateStore(stoVal, corrected);

            stoVal = builder->CreateLoad(sumTy, alloc);
        }
    }

    llvm::Function *mallocFn = module->getFunction("malloc"); // FIXME: WILL NEED TO FREE! (AND DO SO WITHOUT MESSING UP POINTERS.... but we dont have pointers quite yet.... I think)
    Value *v = builder->CreateCall(mallocFn, {builder->getInt32(module->getDataLayout().getTypeAllocSize(stoVal->getType()))});

    // llvm::AllocaInst *v = builder->CreateAlloca(stoVal->getType(), 0, "");
    builder->CreateStore(stoVal, v);

    Value *corrected = builder->CreateBitCast(v, i8p);

    if (!sym->val)
    {
        errorHandler.addCodegenError(nullptr, "Could not find value for channel in send: " + n->sym->getIdentifier()); // FIXME: DO BETTER
        return {};
    }

    Value *chanVal = sym->val.value();

    llvm::Function *progFn = module->getFunction("WriteChannel"); // FIXME: BAD OPTIONAL ACCESS
    // Value *valPtr = builder->CreateCall(progFn, {builder->CreateLoad(Int32Ty, chanVal), corrected}); // Will be a void*
    builder->CreateCall(progFn, {builder->CreateLoad(Int32Ty, chanVal), corrected}); // Will be a void*
    return {};
}

std::optional<Value *> CodegenVisitor::visit(ProgramContractNode *n)
{
    Symbol *sym = n->sym;

    if (!sym->val)
    {
        errorHandler.addCodegenError(nullptr, "Could not find value for channel in contract: " + n->sym->getIdentifier()); // FIXME: DO BETTER
        return {};
    }

    Value *chanVal = sym->val.value();

    // FIXME: DO BETTER NEED TO CONVERT TYPES AND LOAD.... but how?
    llvm::Function *progFn = module->getFunction("ContractChannel"); // FIXME: BAD OPTIONAL ACCESS

    // Value *valPtr = builder->CreateCall(progFn, {builder->CreateLoad(Int32Ty, chanVal)});
    builder->CreateCall(progFn, {builder->CreateLoad(Int32Ty, chanVal)});

    return {};
}

std::optional<Value *> CodegenVisitor::visit(ProgramWeakenNode *n)
{
    Symbol *sym = n->sym;

    if (!sym->val)
    {
        errorHandler.addCodegenError(nullptr, "Could not find value for channel in weaken: " + n->sym->getIdentifier()); // FIXME: DO BETTER
        return {};
    }

    Value *chanVal = sym->val.value();

    // FIXME: DO BETTER NEED TO CONVERT TYPES AND LOAD.... but how?
    llvm::Function *progFn = module->getFunction("WeakenChannel"); // FIXME: BAD OPTIONAL ACCESS
    // Value *valPtr = builder->CreateCall(progFn, {builder->CreateLoad(Int32Ty, chanVal)});
    builder->CreateCall(progFn, {builder->CreateLoad(Int32Ty, chanVal)});

    // FIXME: MAKE SURE TO FREE ON RECV!
    return {};
}

std::optional<Value *> CodegenVisitor::visit(ProgramAcceptNode *n)
{
    // Very similar to regular loop

    Symbol *sym = n->sym;

    if (!sym->val)
    {
        errorHandler.addCodegenError(nullptr, "Could not find value for channel in accept: " + n->sym->getIdentifier()); // FIXME: DO BETTER
        return {};
    }

    Value *chanVal = sym->val.value();

    llvm::Function *checkFn = module->getFunction("ShouldLoop"); // FIXME: BAD OPTIONAL ACCESS
    Value *check = builder->CreateCall(checkFn, {builder->CreateLoad(Int32Ty, chanVal)});

    auto parent = builder->GetInsertBlock()->getParent();

    BasicBlock *loopBlk = BasicBlock::Create(module->getContext(), "loop", parent);
    BasicBlock *restBlk = BasicBlock::Create(module->getContext(), "rest");

    builder->CreateCondBr(check, loopBlk, restBlk);

    // Need to add here otherwise we will overwrite it
    // parent->getBasicBlockList().push_back(loopBlk);

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

    return {};
}

std::optional<Value *> CodegenVisitor::visit(InitProductNode *n)
{
    std::vector<Value *> args;

    for (TypedNode *e : n->exprs)
    {
        std::optional<Value *> valOpt = AcceptType(this, e);
        if (!valOpt)
        {
            errorHandler.addCodegenError(nullptr, "Failed to generate code");
            return {};
        }

        Value *stoVal = valOpt.value();

        // FIXME: TRY PASSING GLOBAL ARG INTO FN

        args.push_back(stoVal);
    }

    const TypeStruct *product = n->product;

    llvm::Type *ty = product->getLLVMType(module);
    llvm::AllocaInst *v = builder->CreateAlloca(ty, 0, "");
    {
        unsigned i = 0;
        std::vector<std::pair<std::string, const Type *>> elements = product->getElements();

        for (Value *a : args)
        {
            if (const TypeSum *sum = dynamic_cast<const TypeSum *>(elements.at(i).second))
            {
                unsigned int index = sum->getIndex(module, a->getType());

                if (index != 0)
                {
                    llvm::Type *sumTy = sum->getLLVMType(module);
                    llvm::AllocaInst *alloc = builder->CreateAlloca(sumTy, 0, "");

                    Value *tagPtr = builder->CreateGEP(alloc, {Int32Zero, Int32Zero});
                    builder->CreateStore(ConstantInt::get(Int32Ty, index, true), tagPtr);

                    Value *valuePtr = builder->CreateGEP(alloc, {Int32Zero, Int32One});

                    Value *corrected = builder->CreateBitCast(valuePtr, a->getType()->getPointerTo());
                    builder->CreateStore(a, corrected);

                    a = builder->CreateLoad(sumTy, alloc);
                }
            }

            Value *ptr = builder->CreateGEP(v, {Int32Zero, ConstantInt::get(Int32Ty, i, true)});

            builder->CreateStore(a, ptr);

            i++;
        }
    }

    Value *loaded = builder->CreateLoad(v->getType()->getPointerElementType(), v);
    return loaded;
}

std::optional<Value *> CodegenVisitor::visit(ArrayAccessNode *n)
{
    std::optional<Value *> index = AcceptType(this, n->indexExpr);

    if (!index)
    {
        errorHandler.addCodegenError(nullptr, "Failed to generate code in TvisitArrayAccess for index!");
        return {};
    }

    std::optional<Value *> arrayPtr = AcceptType(this, n->field);
    if (!arrayPtr)
    {
        errorHandler.addCodegenError(nullptr, "Failed to locate array in access");
        return {};
    }

    /*
    Value *baseValue = arrayPtr.value();
    llvm::AllocaInst *v = builder->CreateAlloca(baseValue->getType());
    builder->CreateStore(baseValue, v);

    auto ptr = builder->CreateGEP(v, {Int32Zero, index.value()});
    if (n->is_rvalue)
    return builder->CreateLoad(ptr->getType()->getPointerElementType(), ptr);
    return ptr;
    */

    Value *v = arrayPtr.value();

    // llvm::AllocaInst *v = builder->CreateAlloca(baseValue->getType());
    // module->dump();
    // builder->CreateStore(baseValue, v);

    auto ptr = builder->CreateGEP(v, {Int32Zero, index.value()});

    if (n->is_rvalue)
        return builder->CreateLoad(ptr->getType()->getPointerElementType(), ptr);
    return ptr;
}

std::optional<Value *> CodegenVisitor::visit(IConstExprNode *n)
{
    return builder->getInt32(n->value);
}

std::optional<Value *> CodegenVisitor::visit(StringConstNode *n)
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

std::optional<Value *> CodegenVisitor::visit(UnaryExprNode *n)
{
    switch (n->op)
    {
    case UNARY_MINUS:
    {
        std::optional<Value *> innerVal = AcceptType(this, n->value);

        if (!innerVal)
        {
            errorHandler.addCodegenError(nullptr, "Failed to generate code for: unary minus");
            return {};
        }

        Value *v = builder->CreateNSWSub(builder->getInt32(0), innerVal.value());
        return v;
    }

    case UNARY_NOT:
    {
        std::optional<Value *> innerVal = AcceptType(this, n->value);

        if (!innerVal)
        {
            errorHandler.addCodegenError(nullptr, "Failed to generate code for: unary not");
            return {};
        }

        Value *v = builder->CreateNot(innerVal.value()); // FIXME: VERIFY!
        return v;
    }
    }
}

std::optional<Value *> CodegenVisitor::visit(BinaryArithNode *n)
{
    std::optional<Value *> lhs = AcceptType(this, n->lhs);
    std::optional<Value *> rhs = AcceptType(this, n->rhs);

    if (!lhs || !rhs)
    {
        errorHandler.addCodegenError(nullptr, "Failed to generate code for: binary arith");
        return {};
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
    }
}

std::optional<Value *> CodegenVisitor::visit(EqExprNode *n)
{
    std::optional<Value *> lhs = AcceptType(this, n->lhs);
    std::optional<Value *> rhs = AcceptType(this, n->rhs);

    // FIXME: CAN WE REMOVE ANY2VALUE ONCE WERE DONE USING AST?

    if (!lhs || !rhs)
    {
        errorHandler.addCodegenError(nullptr, "Failed to generate code for: eq expr");
        return {};
    }

    switch (n->op) // FIXME: STILL NEED THIS!!
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

    // errorHandler.addCodegenError(nullptr, "Unknown equality operator: " + ctx->op->getText());
    return {};
}

/**
 * @brief Generates code for Logical Ands
 *
 * Tested in: test2.prism
 *
 * @param ctx LogAndExprContext to generate this from
 * @return std::optional<Value *> The resulting value or {} if errors.
 */
std::optional<Value *> CodegenVisitor::visit(LogAndExprNode *n)
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
        errorHandler.addCodegenError(nullptr, "Failed to generate code for: first log and");
        return {};
    }

    Value *lastValue = first.value();

    auto parent = current->getParent();
    phi->addIncoming(lastValue, current);

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
            errorHandler.addCodegenError(nullptr, "Failed to generate code for: 842"); // FIXME: DO BETTER + toGen.at(i)->getText());
            return {};
        }
        lastValue = rhs.value();

        falseBlk = builder->GetInsertBlock();
        parent = falseBlk->getParent();
        phi->addIncoming(lastValue, falseBlk);
    }

    builder->CreateBr(mergeBlk); // FIXME: METHODIZE THIS WITH OR?
    // falseBlk = builder->GetInsertBlock();

    /*
     * LHS True - Can skip checking RHS and return true
     */
    parent->getBasicBlockList().push_back(mergeBlk);
    builder->SetInsertPoint(mergeBlk);

    // phi->addIncoming(rhs.value(), falseBlk);
    return phi;
}

/**
 * @brief Generates code for Logical Ors.
 *
 * Tested in: test2.prism
 *
 * @param ctx Context to generate code from
 * @return std::optional<Value *> The resulting value or {} if errors.
 */
std::optional<Value *> CodegenVisitor::visit(LogOrExprNode *n)
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
        errorHandler.addCodegenError(nullptr, "Failed to generate code for: 891"); // FIXME: DO BETTER + toGen.at(0)->getText());
        return {};
    }

    Value *lastValue = first.value();

    auto parent = current->getParent();
    phi->addIncoming(lastValue, current);

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
            errorHandler.addCodegenError(nullptr, "Failed to generate code for: 917"); // FIXME: DO BETTER + toGen.at(i)->getText());
            return {};
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

    // phi->addIncoming(rhs.value(), falseBlk);
    return phi;
}

std::optional<Value *> CodegenVisitor::visit(FieldAccessNode *n)
{
    Symbol *sym = n->symbol;

    if (!sym->type)
    {
        errorHandler.addCodegenError(nullptr, "Improperly initialized symbol in field access: " + n->symbol->getIdentifier());
        return {};
    }

    if (n->accesses.size() > 0 && n->accesses.at(n->accesses.size() - 1).first == "length")
    {
        const Type *modOpt = (n->accesses.size() > 1) ? n->accesses.at(n->accesses.size() - 2).second : sym->type;
        if (const TypeArray *ar = dynamic_cast<const TypeArray *>(modOpt))
        {
            // FIXME: VERIFY THIS STILL WORKS WHEN NESTED!
            // If it is, correctly, an array type, then we can get the array's length (this is the only operation currently, so we can just do thus)
            Value *v = builder->getInt32(ar->getLength());

            return v;
        }

        // FIXME: THROW ERROR? OH WAIT NO BC WE CAN HAVE LENGTH AS A FIELD
    }

    const Type *ty = sym->type;
    // std::optional<Value *> baseOpt = visitVariable(ctx->VARIABLE().at(0)->getText(), props->getBinding(ctx->VARIABLE().at(0)), ctx); // FIXME: STILL NEED THIS!!! AND WE REMOVED IT SOME PLACES!!!! THATS A PROBLEM!!
    std::optional<Value *> baseOpt = visitVariable(sym, n->accesses.size() == 0 ? n->is_rvalue : false); // n->is_rvalue); // n->accesses.size() == 0); // FIXME: VERIFY! // FIXME: STILL NEED THIS!!! AND WE REMOVED IT SOME PLACES!!!! THATS A PROBLEM!!

    if (!baseOpt)
    {
        errorHandler.addCodegenError(nullptr, "Failed to generate field access: "); // FIXME: DO BETTER + ctx->getText());
        return {};
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
                errorHandler.addCodegenError(nullptr, "Could not lookup " + field);
                return {};
            }

            unsigned int index = indexOpt.value();
            addresses.push_back(ConstantInt::get(Int32Ty, index, false));

            const Type *fieldType = n->accesses.at(i).second;
            ty = fieldType;
        }
        // FIXME: THROW ERROR?
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

std::optional<Value *> CodegenVisitor::visit(BinaryRelNode *n)
{
    // Generate code for LHS and RHS
    std::optional<Value *> lhs = AcceptType(this, n->lhs);
    std::optional<Value *> rhs = AcceptType(this, n->rhs);

    // Ensure we successfully generated LHS and RHS
    if (!lhs || !rhs)
    {
        errorHandler.addCodegenError(nullptr, "Failed to generate code for: 1032"); // FIXME: DO BETTER
        return {};
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

std::optional<Value *> CodegenVisitor::visit(ConditionNode *n)
{
    // Passthrough to visiting the conditon
    return AcceptType(this, n->condition);
}

std::optional<Value *> CodegenVisitor::visit(ExternNode *n)
{
    Symbol *symbol = n->getSymbol(); // FIXME: WHY ARE SOME PRIVATE AND OTHERS PUBLIC?

    if (!symbol->type)
    {
        errorHandler.addCodegenError(nullptr, "Type for extern statement not correctly bound! Probably a compiler errror.");
        return {};
    }

    const TypeInvoke *type = n->getType();
    llvm::Type *genericType = type->getLLVMType(module)->getPointerElementType();

    if (llvm::FunctionType *fnType = static_cast<llvm::FunctionType *>(genericType))
    {
        Function *fn = Function::Create(fnType, GlobalValue::ExternalLinkage, symbol->getIdentifier(), module);
        type->setName(fn->getName().str());
    }
    else
    {
        errorHandler.addCodegenError(nullptr, "Could not treat extern type as function.");
        return {};
    }
    return {};
}

std::optional<Value *> CodegenVisitor::visit(AssignNode *n)
{
    // Visit the expression to get the value we will assign
    std::optional<Value *> exprVal = AcceptType(this, n->val);

    // Check that the expression generated
    if (!exprVal)
    {
        errorHandler.addCodegenError(nullptr, "Failed to generate code for: 1098"); // FIXME: DO BETTER + ctx->a->getText());
        return {};
    }

    // Lookup the binding for the variable we are assigning to and and ensure that we find it
    // std::optional<Symbol *> varSymOpt = props->getBinding(ctx->to);
    // if (!varSymOpt)
    // {
    //     errorHandler.addCodegenError(nullptr, "Incorrectly processed variable in assignment: " + ctx->to->getText());
    //     return {};
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
            errorHandler.addCodegenError(nullptr, "Unable to find global variable: " + varSym->identifier);
            return {};
        }

        // Load a pointer to the global variable
        val = builder->CreateLoad(glob)->getPointerOperand();
    }
    */
    // Sanity check to ensure that we now have a value for the variable
    if (!val)
    {
        errorHandler.addCodegenError(nullptr, "Improperly initialized variable in assignment: "); // FIXME: DO BETTER + ctx->to->getText() + "@" + varSym->identifier);
        return {};
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
            errorHandler.addCodegenError(nullptr, "Failed to generate code for: " + ctx->to->getText());
            return {};
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
            Value *corrected = builder->CreateBitCast(stoVal, varSymType->getLLVMType(module));
            builder->CreateStore(corrected, v);
            return {};
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

    return {};
}

std::optional<Value *> CodegenVisitor::visit(VarDeclNode *n)
{
    /*
     * Visit each of the assignments in the context (variables paired with an expression)
     */
    for (auto e : n->assignments)
    {
        std::optional<Value *> exVal = (e->val) ? AcceptType(this, e->val.value()) : std::nullopt;

        if ((e->val) && !exVal)
        {
            errorHandler.addCodegenError(nullptr, "Failed to generate code for: 1206"); // FIXME: DO BETTER + e->a->getText());
            return {};
        }

        // For each of the variabes being assigned to that value
        for (Symbol *varSymbol : e->syms)
        {
            //  Get the type of the symbol
            llvm::Type *ty = varSymbol->type->getLLVMType(module);
            ty = varSymbol->type->getLLVMType(module);
            // Branch depending on if the var is global or not
            if (varSymbol->isGlobal)
            {
                // If it is global, then we need to insert a new gobal variable of this type.
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
                        errorHandler.addCodegenError(nullptr, "Global variable can only be initalized to a constant!");
                        return {};
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
                llvm::AllocaInst *v = builder->CreateAlloca(ty, 0, varSymbol->getIdentifier());
                varSymbol->val = v;

                // Similarly, if we have an expression for the local var, we can store it. Otherwise, we can leave it undefined.
                if (e->val)
                {
                    Value *stoVal = exVal.value();
                    if (const TypeSum *sum = dynamic_cast<const TypeSum *>(varSymbol->type)) // FIXME: WILL THIS WORK IF USING TYPE INF?
                    {
                        unsigned int index = sum->getIndex(module, stoVal->getType());

                        if (index == 0)
                        {
                            Value *corrected = builder->CreateBitCast(stoVal, varSymbol->type->getLLVMType(module));
                            builder->CreateStore(corrected, v);
                            return {};
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
    return {};
}

std::optional<Value *> CodegenVisitor::visit(WhileLoopNode *n)
{
    // FIXME: WE NEED TO START LOOP IN HERE

    // Very similar to conditionals

    std::optional<Value *> check = this->visit(n->cond);

    if (!check)
    {
        errorHandler.addCodegenError(nullptr, "Failed to generate code for: 1299"); // FIXME: DO BETTER + ctx->check->getText());
        return {};
    }

    auto parent = builder->GetInsertBlock()->getParent();

    BasicBlock *loopBlk = BasicBlock::Create(module->getContext(), "loop", parent);
    BasicBlock *restBlk = BasicBlock::Create(module->getContext(), "rest");

    builder->CreateCondBr(check.value(), loopBlk, restBlk);

    // Need to add here otherwise we will overwrite it
    // parent->getBasicBlockList().push_back(loopBlk);

    /*
     * In the loop block
     */
    builder->SetInsertPoint(loopBlk);

    for (auto e : n->blk->exprs)
    {
        AcceptType(this, e);
    }

    // Re-calculate the loop condition
    check = this->visit(n->cond);
    if (!check)
    {
        errorHandler.addCodegenError(nullptr, "Failed to generate code for: 1328"); // FIXME: DO BETTER + ctx->check->getText());
        return {};
    }

    // Check if we need to loop back again...
    builder->CreateCondBr(check.value(), loopBlk, restBlk);
    loopBlk = builder->GetInsertBlock();

    /*
     * Out of loop
     */
    parent->getBasicBlockList().push_back(restBlk);
    builder->SetInsertPoint(restBlk);

    return {};
}

std::optional<Value *> CodegenVisitor::visit(ConditionalStatementNode *n)
{
    // Get the condition that the if statement is for
    std::optional<Value *> cond = this->visit(n->cond);

    if (!cond)
    {
        errorHandler.addCodegenError(nullptr, "Failed to generate code for: 1352"); // FIXME:  + ctx->check->getText());
        return {};
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
        // e->accept(this);
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

    return {};
}

std::optional<Value *> CodegenVisitor::visit(SelectStatementNode *n)
{
    /*
     * Set up the merge block that all cases go to after the select statement
     */
    auto origParent = builder->GetInsertBlock()->getParent();
    BasicBlock *mergeBlk = BasicBlock::Create(module->getContext(), "ifcont");

    // Iterate through each of the cases
    for (unsigned long i = 0; i < n->nodes.size(); i++)
    {
        SelectAlternativeNode *evalCase = n->nodes.at(i);

        // Visit the check code
        std::optional<Value *> optVal = AcceptType(this, evalCase->check);

        // Check that the optional, in fact, has a value. Otherwise, something went wrong.
        if (!optVal)
        {
            errorHandler.addCodegenError(nullptr, "Failed to generate code for: 1442"); // + evalCase->getText());
            return {};
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
        if (BlockNode *blk = dynamic_cast<BlockNode *>(evalCase->eval))
        {
            // if (!CodegenVisitor::blockEndsInReturn(blk))
            if (!endsInReturn(blk))
            {
                builder->CreateBr(mergeBlk);
            }
            // if it ends in a return, we're good!
        }
        else if (ReturnNode *retCtx = dynamic_cast<ReturnNode *>(evalCase->eval))
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

    // std::optional<Value *> ans = {};
    return std::nullopt;
}

std::optional<Value *> CodegenVisitor::visit(ReturnNode *n)
{
    // Check if we are returning an expression or not
    if (n->expr)
    {
        std::pair<const Type *, TypedNode *> expr = n->expr.value();
        // Perform some checks to make sure that code was generated
        std::optional<Value *> innerOpt = AcceptType(this, expr.second);

        if (!innerOpt)
        {
            errorHandler.addCodegenError(nullptr, "Failed to generate code for: 1528"); // FIXME: DO BETTER + ctx->getText());
            return {};
        }

        Value *inner = innerOpt.value();

        // TODO: METHODIZE
        if (const TypeSum *sum = dynamic_cast<const TypeSum *>(expr.first))
        {
            unsigned int index = sum->getIndex(module, inner->getType());

            if (index != 0)
            {
                llvm::Type *sumTy = sum->getLLVMType(module);
                llvm::AllocaInst *alloc = builder->CreateAlloca(sumTy, 0, "");

                Value *tagPtr = builder->CreateGEP(alloc, {Int32Zero, Int32Zero});
                builder->CreateStore(ConstantInt::get(Int32Ty, index, true), tagPtr);

                Value *valuePtr = builder->CreateGEP(alloc, {Int32Zero, Int32One});

                Value *corrected = builder->CreateBitCast(valuePtr, inner->getType()->getPointerTo());
                builder->CreateStore(inner, corrected);

                inner = builder->CreateLoad(sumTy, alloc);
            }
        }

        // As the code was generated correctly, build the return statement; we ensure no following code due to how block visitors work in semantic analysis.
        Value *v = builder->CreateRet(inner);

        return v;
    }

    // If there is no value, return void. We ensure no following code and type-correctness in the semantic pass.
    Value *v = builder->CreateRetVoid();
    return v;
}

std::optional<Value *> CodegenVisitor::visit(ExitNode *n) // FIXME: VERIFY/DO BETTER
{
    // If there is no value, return void. We ensure no following code and type-correctness in the semantic pass.
    Value *v = builder->CreateRetVoid();
    return v;
}

std::optional<Value *> CodegenVisitor::visit(BooleanConstNode *n)
{
    Value *val = n->value ? builder->getTrue() : builder->getFalse();
    return val;
}

std::optional<Value *> CodegenVisitor::visit(BlockNode *n)
{
    for (auto e : n->exprs)
    {
        // e->accept(this);
        AcceptType(this, e);
    }

    return {};
}

std::optional<Value *> CodegenVisitor::visit(LambdaConstNode *n)
{
    // Get the current insertion point
    BasicBlock *ins = builder->GetInsertBlock();

    const TypeInvoke *type = n->getType();

    llvm::Type *genericType = type->getLLVMType(module)->getPointerElementType();

    if (llvm::FunctionType *fnType = static_cast<llvm::FunctionType *>(genericType)) // FIXME: MAKE THIS THE RETURN TYPE OF TypeInvoke's getLLVMTYPE
    {
        // Function *fn = Function::Create(fnType, GlobalValue::PrivateLinkage, n->name, module); ///"LAM", module);
        Function *fn = type->getLLVMName() ? module->getFunction(type->getLLVMName().value()) : Function::Create(fnType, GlobalValue::PrivateLinkage, n->name, module);
        type->setName(fn->getName().str()); // FIXME: NOT ALWAYS NEEDED

        std::vector<Symbol *> paramList = n->paramSymbols;

        // Create basic block
        BasicBlock *bBlk = BasicBlock::Create(module->getContext(), "entry", fn);
        builder->SetInsertPoint(bBlk);

        // Bind all of the arguments
        for (auto &arg : fn->args())
        {
            // Get the argumengt number (just seems easier than making my own counter)
            int argNumber = arg.getArgNo();

            // Get the argument's type
            llvm::Type *type = fnType->params()[argNumber];

            // Get the argument name (This even works for arrays!)
            Symbol *param = paramList.at(argNumber);

            std::string argName = param->getIdentifier();

            // Create an allocation for the argumentr
            llvm::AllocaInst *v = builder->CreateAlloca(type, 0, argName);

            // Try to find the parameter's bnding to determine what value to bind to it.
            // std::optional<Symbol *> symOpt = props->getBinding(paramList->params.at(argNumber)); // FIXME: STILL NEED TO DO THIS

            param->val = v; // FIXME: DO WE NEED TO CHECK IF ALREADY SET?

            builder->CreateStore(&arg, v);
        }

        // Generate code for the block
        for (auto e : n->block->exprs)
        {
            AcceptType(this, e);
        }

        // NOTE HOW WE DONT NEED TO CREATE RET VOID EVER BC NO FN!

        // Return to original insert point
        builder->SetInsertPoint(ins);

        return fn;
    }
    else
    {
        errorHandler.addCodegenError(nullptr, "Invocation type could not be cast to function!");
    }

    // Return to original insert point
    builder->SetInsertPoint(ins);

    return {};
}

/*
 *
 * UNUSED VISITORS
 * ===============
 *
 * These are visitors which should NEVER be seen during the compilation process.
 *
 */
