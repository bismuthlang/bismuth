#include "LLVMTypeGenerator.h"


/*
 * What if I could write:
 * llvm::Type * LLVMTypeGenerator::visit_typed(TypeInt& t), 
 * llvm::Type * LLVMTypeGenerator::visit_typed(TypeU32& t) {
 *  // IMPL for both
 * }
 *
*/
llvm::Type * LLVMTypeGenerator::visit_typed(TypeInt& t){
    return llvm::Type::getInt32Ty(mod->getContext());
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeU32& t){
    return llvm::Type::getInt32Ty(mod->getContext());
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeI64& t){
    return llvm::Type::getInt64Ty(mod->getContext());
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeU64& t){
    return llvm::Type::getInt64Ty(mod->getContext());
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeBool& t){
    return llvm::Type::getInt1Ty(mod->getContext());
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeStr& t){
    return llvm::Type::getInt8Ty(mod->getContext())->getPointerTo();
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeBottom& t){
    assert(false && "Cannot take the llvm type of bot");
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeUnit& t){
    llvm::StructType *ty = llvm::StructType::getTypeByName(mod->getContext(), t.toString(C_STYLE));
    if (ty)
        return ty;

    ty = llvm::StructType::create(mod->getContext(), t.toString(C_STYLE));

    std::vector<llvm::Type *> typeVec;
    
    llvm::ArrayRef<llvm::Type *> ref = llvm::ArrayRef(typeVec);
    ty->setBody(ref); // Done like this to enable recursive types

    return ty;
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeAbsurd& t){
    assert(false && "Cannot take the llvm type of absurd");
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeArray& t){
    return llvm::ArrayType::get(
        const_cast<Type *>(t.getValueType())->accept<llvm::Type *>(*this),
        (uint64_t) t.getLength()
    );
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeDynArray & t){
    llvm::StructType *ty = llvm::StructType::getTypeByName(mod->getContext(), t.toString(C_STYLE));
    if (ty)
        return ty;

    ty = llvm::StructType::create(mod->getContext(), t.toString(C_STYLE));

    std::vector<llvm::Type *> typeVec = {
        const_cast<Type *>(t.getValueType())->accept<llvm::Type *>(*this)->getPointerTo(), // Pointer
        llvm::Type::getInt32Ty(mod->getContext()),   // Length
        llvm::Type::getInt32Ty(mod->getContext())    // Capacity
    };


    llvm::ArrayRef<llvm::Type *> ref = llvm::ArrayRef(typeVec);
    ty->setBody(ref); // Done like this to enable recursive types

    return ty;
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeChannel& t){
    // TODO: bring in line w/ definition in CodegenUtils! (if a change was made in either, itd break the other)
    llvm::StructType *ty = llvm::StructType::getTypeByName(
        mod->getContext(),
        "_Channel"
    );

    if (ty)
        return ty->getPointerTo();

    return llvm::StructType::create(
        mod->getContext(),
        "_Channel")->getPointerTo();
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeBox& t){
    return const_cast<Type *>(t.getInnerType())->accept<llvm::Type *>(*this)->getPointerTo();
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeProgram& t){
    return t.getLLVMFunctionType(mod)->getPointerTo();
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeFunc& t){
    return t.getLLVMFunctionType(mod)->getPointerTo();
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeInfer& t){
    return t.getLLVMType(mod);
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeSum& t){
return t.getLLVMType(mod);
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeStruct& t){
return t.getLLVMType(mod);
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeGeneric& t){
return t.getLLVMType(mod);
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeTemplate& t){
return t.getLLVMType(mod);
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeModule & t){
return t.getLLVMType(mod);
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeTrait& t){
return t.getLLVMType(mod);
}





llvm::FunctionType * LLVMTypeGenerator::getLLVMFunctionType(TypeProgram& t){
    llvm::Type *ret = const_cast<TypeUnit *>(Types::UNIT)->accept<llvm::Type *>(*this); // Types::UNIT->getLLVMType(M);

     // TODO: bring in line w/ definition in CodegenUtils! (if a change was made in either, itd break the other)
    llvm::StructType *argTy = llvm::StructType::getTypeByName(mod->getContext(), "_Channel");
    if (!argTy)
        argTy = llvm::StructType::create(mod->getContext(), "_Channel");


    return llvm::FunctionType::get(
        ret,
        {argTy->getPointerTo()},
        false);
}

llvm::FunctionType * LLVMTypeGenerator::getLLVMFunctionType(TypeFunc& t){
    // Create a vector for our argument types
    std::vector<llvm::Type *> typeVec;

    for (const Type *ty : t.getParamTypes())
    {
        typeVec.push_back(const_cast<Type *>(ty)->accept<llvm::Type *>(*this));
    }

    llvm::ArrayRef<llvm::Type *> paramRef = llvm::ArrayRef(typeVec);

    llvm::Type *ret = const_cast<Type *>(t.getReturnType())->accept<llvm::Type *>(*this);

    return llvm::FunctionType::get(
        ret,
        paramRef,
        t.isVariadic());
}
