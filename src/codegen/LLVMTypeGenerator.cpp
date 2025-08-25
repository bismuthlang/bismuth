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
    std::optional<const Type*> inferredType = t.getValueType();
    assert(inferredType.has_value() && "Cannot generate the LLVM type for an uninferred type");
    return const_cast<Type *>(inferredType.value())->accept<llvm::Type *>(*this);
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeSum& t){
 // FIXME: I THINK WE HAVE TO CHANGE TOSTRING BC IF WE DONT, THEN canApplyTemplate SHOULD BREAK AS IT WONT USE FQNS! 
    std::string name =  t.hasName() ? t.getIdentifier().value()->getFullyQualifiedName() :  t.getTypeRepresentation(DisplayMode::C_STYLE);

    llvm::StructType *ty = llvm::StructType::getTypeByName(mod->getContext(), name);
    if (ty)
        return ty;

    unsigned int min = std::numeric_limits<unsigned int>::max();
    unsigned int max = std::numeric_limits<unsigned int>::min();

    for (auto e : t.getCases())
    {
        // Note: This is why one has to use pointers in order to nest a type into itself
        llvm::Type* caseType = const_cast<Type *>(e)->accept<llvm::Type *>(*this);

        unsigned int t = caseType->isSized() ? mod->getDataLayout().getTypeAllocSize(caseType) : 0;
        // FIXME: DO BETTER - ALSO WILL NOT WORK ON VARS! (there are actually a LOT of places where using a var may break things bc we only check for TypeSum)

        if (t < min && t != 0 )
        {
            min = t;
        }

        if (t > max)
        {
            max = t;
        }
    }

    // FIXME: WHY DO WE DO THIS TWICE?
    // Probably not needed in struct, but might be. 
    // Needed in the case that we generate the type while generating one of the subtypes...
    ty = llvm::StructType::getTypeByName(mod->getContext(), name);
    if (ty)
        return ty;

    // FIXME: DO BETTER
    uint64_t len = (uint64_t)max;
    llvm::Type *inner = llvm::Type::getInt8Ty(mod->getContext());
    llvm::Type *arr = llvm::ArrayType::get(inner, len);

    std::vector<llvm::Type *> typeVec = {llvm::Type::getInt32Ty(mod->getContext()), arr};

    llvm::ArrayRef<llvm::Type *> ref = llvm::ArrayRef(typeVec);
    auto ans = llvm::StructType::create(mod->getContext(), ref, name);
    
    return ans;
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeStruct& t){
    // PLAN: have to use this vs tostring bc tostring isnt fqn. Maybe change tostring to fqn?
    std::string name =  t.hasName() ? 
        t.getIdentifier().value()->getFullyQualifiedName() :  t.getTypeRepresentation(DisplayMode::C_STYLE);

    llvm::StructType *ty = llvm::StructType::getTypeByName(mod->getContext(), name);
    if (ty)
        return ty;

    ty = llvm::StructType::create(mod->getContext(), name);

    std::vector<llvm::Type *> typeVec;

    for (auto ty : t.getElements())
    {
        typeVec.push_back(genLLVMType(*ty.second));
    }

    llvm::ArrayRef<llvm::Type *> ref = llvm::ArrayRef(typeVec);
    ty->setBody(ref); // Done like this to enable recursive types

    return ty;
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeGeneric& t){
     if(auto actingType = t.getActingType(); actingType.has_value())
            return genLLVMType(*actingType.value()); 

    std::cerr << "1082: Attempted to take llvm type of a generic parameter" << std::endl;
    return llvm::Type::getVoidTy(mod->getContext());
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeTemplate& t){
return llvm::Type::getVoidTy(mod->getContext()); // TODO: DO BETTER!
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeModule & t){
    assert(false && "Attempted to get LLVM type for module"); 
}

llvm::Type * LLVMTypeGenerator::visit_typed(TypeTrait& t){
  // FIXME: this is wrong, traits have a type!(a pointer to teh value + ptr to vtable)
    assert(false && "Attempted to get LLVM type for trait"); 
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


llvm::Type * LLVMTypeGenerator::genLLVMType(Type & t){
    return t.accept<llvm::Type *>(*this);
}

llvm::Type * LLVMTypeGenerator::genLLVMType(const Type& t){
    return genLLVMType(const_cast<Type &>(t));
}
