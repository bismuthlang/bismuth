/**
 * @file LLVMTypeGenerator.h
 * @author Alex Friedman (ahfriedman.com)
 * @version 0.1
 * @date 2025-8-19
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include "Type.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/NoFolder.h"


#include <string>
#include <optional>

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

class LLVMTypeGenerator : public virtual TypeVisitor<llvm::Type *>
{
public:
    LLVMTypeGenerator(Module * m)
        : mod(m)
    {}

llvm::Type * visit_typed(TypeInt& t) override;
llvm::Type * visit_typed(TypeU32& t) override;
llvm::Type * visit_typed(TypeI64& t) override;
llvm::Type * visit_typed(TypeU64& t) override;
llvm::Type * visit_typed(TypeBool& t) override;
llvm::Type * visit_typed(TypeStr& t) override;
llvm::Type * visit_typed(TypeBottom& t) override;
llvm::Type * visit_typed(TypeUnit& t) override;
llvm::Type * visit_typed(TypeAbsurd& t) override;
llvm::Type * visit_typed(TypeArray& t) override;
llvm::Type * visit_typed(TypeDynArray & t) override;
llvm::Type * visit_typed(TypeChannel& t) override;
llvm::Type * visit_typed(TypeBox& t) override;
llvm::Type * visit_typed(TypeProgram& t) override;
llvm::Type * visit_typed(TypeFunc& t) override;
llvm::Type * visit_typed(TypeInfer& t) override;
llvm::Type * visit_typed(TypeSum& t) override;
llvm::Type * visit_typed(TypeStruct& t) override;
llvm::Type * visit_typed(TypeGeneric& t) override;
llvm::Type * visit_typed(TypeTemplate& t) override;
llvm::Type * visit_typed(TypeModule & t) override;
llvm::Type * visit_typed(TypeTrait& t) override;


llvm::FunctionType * getLLVMFunctionType(TypeProgram& t);
llvm::FunctionType * getLLVMFunctionType(TypeFunc& t);

private: 
    llvm::Module * mod; 
};
