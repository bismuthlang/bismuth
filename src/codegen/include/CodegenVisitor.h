/**
 * @file CodegenVisitor.h
 * @author Alex Friedman (ahfriedman.com)
 * @brief Code Generation visitor header inspired by sample code
 * @version 0.1
 * @date 2022-09-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "antlr4-runtime.h"
#include "BismuthBaseVisitor.h"
#include "CompilerFlags.h"

#include "BismuthErrorHandler.h"
#include "DeepCopyVisitor.h"
// #include "SemanticVisitor.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/NoFolder.h"

#include "CastUtils.h"

#include <any>
#include <string>
#include <regex>

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

class CodegenVisitor : TypedASTVisitor
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

        copyVisitor = new DeepCopyVisitor(module, &errorHandler);

        // LLVM Types
        UnitTy = Types::UNIT->getLLVMType(module);
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
    std::optional<Value *> visit(TSelectStatementNode *n) override;
    std::optional<Value *> visit(TBlockNode *n) override;
    std::optional<Value *> visit(TLambdaConstNode *n) override;
    std::optional<Value *> visit(TProgramDefNode *n) override { return visitInvokeable(n); };
    std::optional<Value *> visit(TConditionalStatementNode *n) override;
    std::optional<Value *> visit(TReturnNode *n) override;
    std::optional<Value *> visit(TProgramSendNode *n) override;
    std::optional<Value *> visit(TProgramRecvNode *n) override;
    std::optional<Value *> visit(TProgramIsPresetNode *n) override; 
    std::optional<Value *> visit(TProgramContractNode *n) override;
    std::optional<Value *> visit(TProgramWeakenNode *n) override;
    std::optional<Value *> visit(TProgramExecNode *n) override;
    std::optional<Value *> visit(TProgramAcceptNode *n) override;
    std::optional<Value *> visit(TProgramAcceptWhileNode *n) override;
    std::optional<Value *> visit(TProgramAcceptIfNode *n) override; 
    // std::optional<Value *> visit(TDefineEnumNode *n) override;
    // std::optional<Value *> visit(TDefineStructNode *n) override;
    std::optional<Value *> visit(TInitProductNode *n) override;
    std::optional<Value *> visit(TWhileLoopNode *n) override;
    std::optional<Value *> visit(TExternNode *n) override;
    std::optional<Value *> visit(TInvocationNode *n) override;
    std::optional<Value *> visit(TFieldAccessNode *n) override;
    std::optional<Value *> visit(TDerefBoxNode *n) override;
    std::optional<Value *> visit(TArrayAccessNode *n) override;
    std::optional<Value *> visit(TAssignNode *n) override;
    std::optional<Value *> visit(TBinaryRelNode *n) override;
    std::optional<Value *> visit(TBinaryArithNode *n) override;
    std::optional<Value *> visit(TEqExprNode *n) override;
    std::optional<Value *> visit(TUnaryExprNode *n) override;
    std::optional<Value *> visit(TLogAndExprNode *n) override;
    std::optional<Value *> visit(TLogOrExprNode *n) override;
    std::optional<Value *> visit(TStringConstNode *n) override;
    std::optional<Value *> visit(TBooleanConstNode *n) override;
    std::optional<Value *> visit(TIntConstExprNode *n) override;
    std::optional<Value *> visit(TCompilationUnitNode *n) override;
    std::optional<Value *> visit(TVarDeclNode *n) override;
    std::optional<Value *> visit(TMatchStatementNode *n) override;
    std::optional<Value *> visit(TExitNode *n) override;
    std::optional<Value *> visit(TChannelCaseStatementNode *n) override;
    std::optional<Value *> visit(TProgramProjectNode *n) override;
    std::optional<Value *> visit(TInitBoxNode *n) override;
    std::optional<Value *> visit(TExprCopyNode *n) override; 
    std::optional<Value *> visit(TAsChannelNode *n) override;  

    std::optional<Value *> visitCompilationUnit(TCompilationUnitNode *n) { return visit(n); }

    bool hasErrors(int flags) { return errorHandler.hasErrors(flags); }
    std::string getErrors() { return errorHandler.errorList(); }

    Module *getModule() { return module; }
    void modPrint() { module->print(llvm::outs(), nullptr); }

    /**
     * @brief Generates the code for an InvokeableType (PROC/FUNC)
     *
     * @param sum The FuncDefContext to build the function from
     * @return std::optional<Value *> Empty as this shouldn't be seen as a value
     */
    std::optional<Value *> visitInvokeable(TProgramDefNode *n)
    {
        BasicBlock *ins = builder->GetInsertBlock();

        // Get the function name. Done separately from sym in case the symbol isn't found
        std::string funcId = n->name;

        const TypeProgram *inv = n->getType();

        llvm::FunctionType *fnType = inv->getLLVMFunctionType(module);

        Function *fn = inv->getLLVMName() ? module->getFunction(inv->getLLVMName().value()) : Function::Create(fnType, GlobalValue::PrivateLinkage, funcId, module);
        ; // Lookup the function first
        inv->setName(fn->getName().str());
        
        // Get the parameter list context for the invokable
        // BismuthParser::ParameterListContext *paramList = ctx->paramList;
        // Create basic block
        BasicBlock *bBlk = BasicBlock::Create(module->getContext(), "entry", fn);
        builder->SetInsertPoint(bBlk);

        // Bind all of the arguments
        std::optional<llvm::AllocaInst *> vOpt = CreateEntryBlockAlloc(Int32Ty, n->channelSymbol->getIdentifier());
        if(!vOpt)
        {
            errorHandler.addError(nullptr, "Failed to generate alloc for channel value, is it somehow void?"); // Should never occur bc int32Ty
            return std::nullopt; 
        }
        llvm::AllocaInst * v = vOpt.value(); 

        n->channelSymbol->setAllocation(v);
        builder->CreateStore((fn->args()).begin(), v);
        /*
        for (auto &arg : fn->args())
        {
            // Get the argument number (just seems easier than making my own counter)
            int argNumber = arg.getArgNo();

            // Get the argument's type
            llvm::Type *type = fnType->params()[argNumber];

            // Get the argument name (This even works for arrays!)
            std::string argName = paramList->params.at(argNumber)->getText();

            // Create an allocation for the argument
            llvm::AllocaInst *v = builder->CreateAlloca(type, 0, argName);

            // Try to find the parameter's binding to determine what value to bind to it.
            std::optional<Symbol *> symOpt = props->getBinding(paramList->params.at(argNumber));

            if (!symOpt)
            {
                errorHandler.addError(nullptr, "Unable to generate parameter for function: " + argName);
            }
            else
            {
                symOpt.value()->val = v;

                builder->CreateStore(&arg, v);
            }
        }
        */

        // Get the codeblock for the PROC/FUNC
        // BismuthParser::BlockContext *block = ctx->block();
        // Generate code for the block
        for (auto e : n->block->exprs)
        {
            // e->accept(this);
            this->accept(e);
            // module->dump();
        }
        
        // If we are a PROC, make sure to add a return type (if we don't already have one)
        // if (ctx->PROC() && !CodegenVisitor::blockEndsInReturn(block))
        if (!endsInReturn(n->block)) // TODO: THIS SHOULD BECOME ALWAYS TRUE, OR IS IT GIVEN EXIT?
        {
            builder->CreateRet(getUnitValue());
            // Value * val = llvm::UndefValue::get(llvm::Type::getVoidTy(module->getContext()));
            // builder->CreateRet(val);
        }
        
        builder->SetInsertPoint(ins);
        return std::nullopt;
    }

    std::optional<Value *> visitVariable(Symbol *sym, bool is_rvalue)
    {
        // Try getting the type for the symbol, raising an error if it could not be determined
        llvm::Type *type = sym->type->getLLVMType(module);
        if (!type)
        {
            errorHandler.addError(nullptr, "Unable to find type for variable: " + sym->getIdentifier());
            return std::nullopt;
        }
        
        // Make sure the variable has an allocation (or that we can find it due to it being a global var)
        std::optional<llvm::AllocaInst *> optVal = sym->getAllocation();
        if (!optVal)
        {
            // If the symbol is a global var
            if (const TypeProgram *inv = dynamic_cast<const TypeProgram *>(sym->type))
            {
                if (!inv->getLLVMName())
                {
                    errorHandler.addError(nullptr, "Could not locate IR name for program: " + sym->toString());
                    return std::nullopt;
                }

                Function *fn = module->getFunction(inv->getLLVMName().value());

                return fn;
            }
            else if (const TypeInvoke *inv = dynamic_cast<const TypeInvoke *>(sym->type)) // This is annoying that we have to have duplicate code despite both APIs being the same
            {
                if (!inv->getLLVMName())
                {
                    errorHandler.addError(nullptr, "Could not locate IR name for function: " + sym->toString());
                    return std::nullopt;
                }

                Function *fn = module->getFunction(inv->getLLVMName().value());

                return fn;
            }
            else if (sym->isGlobal)
            {
                // Lookup the global var for the symbol
                llvm::GlobalVariable *glob = module->getNamedGlobal(sym->identifier);

                // Check that we found the variable. If not, throw an error.
                if (!glob)
                {
                    errorHandler.addError(nullptr, "Unable to find global variable: " + sym->getIdentifier());
                    return std::nullopt;
                }

                // Create and return a load for the global var
                Value *val = builder->CreateLoad(glob);
                return val;
            }

            errorHandler.addError(nullptr, "Unable to find allocation for variable: " + sym->getIdentifier());
            return std::nullopt;
        }

        if (!is_rvalue)
            return optVal.value();

        // // Otherwise, we are a local variable with an allocation and, thus, can simply load it.
        Value *v = builder->CreateLoad(type, optVal.value(), sym->getIdentifier());
        // llvm::AllocaInst *alloc = builder->CreateAlloca(v->getType());
        // builder->CreateStore(v, alloc);
        // return alloc;
        return v;
    }

    // These should automatically have GlobalValue::ExternalLinkage per inspecting source code...
    llvm::FunctionCallee getWriteProjection()
    {
        return module->getOrInsertFunction("WriteProjection",
                                           llvm::FunctionType::get(
                                               UnitTy,
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

    llvm::FunctionCallee getWeakenChannel()
    {
        return module->getOrInsertFunction(
            "WeakenChannel",
            llvm::FunctionType::get(
                UnitTy,
                {Int32Ty},
                false));
    }

    llvm::FunctionCallee getWriteChannel()
    {
        return module->getOrInsertFunction(
            "WriteChannel",
            llvm::FunctionType::get(
                UnitTy,
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
                     UnitTy,
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

    llvm::FunctionCallee get_OC_isPresent()
    {
        return module->getOrInsertFunction(
            "_OC_isPresent",
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
                UnitTy,
                {Int32Ty},
                false));
    }

    llvm::FunctionCallee getContractChannel()
    {
        return module->getOrInsertFunction(
            "ContractChannel",
            llvm::FunctionType::get(
                UnitTy,
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

    llvm::FunctionCallee get_arrayToChannel()
    {
        return module->getOrInsertFunction(
            "_ArrayToChannel",
            llvm::FunctionType::get(
                Int32Ty,
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

    Value * correctSumAssignment(const TypeSum *sum, Value *original)
    {
        unsigned int index = sum->getIndex(module, original->getType());

        if (index != 0)
        {
            llvm::Type *sumTy = sum->getLLVMType(module);
            llvm::AllocaInst * alloc = CreateEntryBlockAlloc(sumTy, "");

            Value *tagPtr = builder->CreateGEP(alloc, {Int32Zero, Int32Zero});

            builder->CreateStore(ConstantInt::get(Int32Ty, index, true), tagPtr);

            Value *valuePtr = builder->CreateGEP(alloc, {Int32Zero, Int32One});

            Value *corrected = builder->CreateBitCast(valuePtr, original->getType()->getPointerTo());
            builder->CreateStore(original, corrected);

            return builder->CreateLoad(sumTy, alloc);
        }

        return original; // Already correct (ie, a sum to the same sum), but WILL Break if we start doing more fancy sum cases...
    }

    // TODO: void elimination? Should be somewhat handled by llvm
    // FIXME: BLOCK UNIT FROM BEING IN STRUCT? OR AT LEAST TEST IF ITS BREAKING
    // https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl07.html#adjusting-existing-variables-for-mutation
    llvm::AllocaInst *CreateEntryBlockAlloc(llvm::Type *ty, std::string identifier)
    {
        llvm::Function *fn = builder->GetInsertBlock()->getParent();
        IRBuilder<> tempBuilder(&fn->getEntryBlock(), fn->getEntryBlock().begin());
        return tempBuilder.CreateAlloca(ty, 0, identifier);
    }

private:
    int flags;

    BismuthErrorHandler errorHandler = BismuthErrorHandler(CODEGEN);
    DeepCopyVisitor *copyVisitor;
    // LLVM
    LLVMContext *context;
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
};
