#include "Type.h"

bool Type::isSubtype(const Type *other) const
{
    if (const TypeInfer *inf = dynamic_cast<const TypeInfer *>(this))
    {
        // return false;
        // return inf->isSupertype(this);
        return inf->isSupertype(other);
    }

    if(other->isLinear() && !this->isLinear()) return false;  //FIXME: VERIFY WORKS WITH TYPE INF!

    return other->isSupertypeFor(this);
}

/*******************************************
 *
 * Integer (32 bit, signed) Type Definition
 *
 *******************************************/
bool TypeInt::isSupertypeFor(const Type *other) const
{
    return dynamic_cast<const TypeInt *>(other);
}

std::string TypeInt::toString(DisplayMode) const { return "int"; }

llvm::IntegerType *TypeInt::getLLVMType(llvm::Module *M) const
{
    return llvm::Type::getInt32Ty(M->getContext());
}

/*******************************************
 *
 * Integer (32 bit, unsigned) Type Definition
 *
 *******************************************/
bool TypeU32::isSupertypeFor(const Type *other) const
{
    return dynamic_cast<const TypeU32 *>(other);
}

std::string TypeU32::toString(DisplayMode) const { return "u32"; }

llvm::IntegerType *TypeU32::getLLVMType(llvm::Module *M) const
{
    return llvm::Type::getInt32Ty(M->getContext());
}


/*******************************************
 *
 * Integer (64 bit, signed) Type Definition
 *
 *******************************************/
bool TypeI64::isSupertypeFor(const Type *other) const
{
    return dynamic_cast<const TypeI64 *>(other);
}

std::string TypeI64::toString(DisplayMode) const { return "i64"; }

llvm::IntegerType *TypeI64::getLLVMType(llvm::Module *M) const
{
    return llvm::Type::getInt64Ty(M->getContext());
}

/*******************************************
 *
 * Integer (64 bit, unsigned) Type Definition
 *
 *******************************************/
bool TypeU64::isSupertypeFor(const Type *other) const
{
    return dynamic_cast<const TypeU64 *>(other);
}

std::string TypeU64::toString(DisplayMode) const { return "u64"; }

llvm::IntegerType *TypeU64::getLLVMType(llvm::Module *M) const
{
    return llvm::Type::getInt32Ty(M->getContext());
}


/*******************************************
 *
 *     Boolean (1 bit) Type Definition
 *
 *******************************************/
bool TypeBool::isSupertypeFor(const Type *other) const
{
    return dynamic_cast<const TypeBool *>(other);
}

std::string TypeBool::toString(DisplayMode) const { return "boolean"; }

llvm::Type *TypeBool::getLLVMType(llvm::Module *M) const
{
    return llvm::Type::getInt1Ty(M->getContext());
}

/*********************************************
 *
 * String (dynamic allocation) Type Definition
 *
 *********************************************/
std::string TypeStr::toString(DisplayMode) const { return "str"; }
llvm::Type *TypeStr::getLLVMType(llvm::Module *M) const { return llvm::Type::getInt8PtrTy(M->getContext()); }
bool TypeStr::isSupertypeFor(const Type *other) const
{
    return dynamic_cast<const TypeStr *>(other);
}



/*******************************************
 *
 * Bottom Type
 *
 *******************************************/
std::string TypeBottom::toString(DisplayMode mode) const { return "\u22A5"; } // TODO: improve tostring?

const TypeBottom * TypeBottom::getCopy() const { return this; };

bool TypeBottom::isSupertypeFor(const Type *other) const
{
    return false;
}



/*******************************************
 *
 * Unit Type
 *
 *******************************************/
std::string TypeUnit::toString(DisplayMode mode) const 
{
    switch (mode)
    {
    case C_STYLE:
        return "Unit";
    case MATH_STYLE:
        return "1"; // Used to always be 1 pre July 15 2023; Unit until Oct 21, 2023; then display mode
    }
} 

const TypeUnit * TypeUnit::getCopy() const { return this; };

llvm::Type *TypeUnit::getLLVMType(llvm::Module *M) const
{
    llvm::StructType *ty = llvm::StructType::getTypeByName(M->getContext(), toString(C_STYLE));
    if (ty)
        return ty;

    ty = llvm::StructType::create(M->getContext(), toString(C_STYLE));

    std::vector<llvm::Type *> typeVec;
    
    llvm::ArrayRef<llvm::Type *> ref = llvm::ArrayRef(typeVec);
    ty->setBody(ref); // Done like this to enable recursive types

    return ty;
}

bool TypeUnit::isSupertypeFor(const Type *other) const
{
    // return dynamic_cast<const TypeUnit *>(other);
    // return false;
    return dynamic_cast<const TypeUnit *>(other);
}


/*******************************************
 *
 * Absurd Type
 *
 *******************************************/
std::string TypeAbsurd::toString(DisplayMode mode) const { return "0"; }

const TypeAbsurd * TypeAbsurd::getCopy() const { return this; };

bool TypeAbsurd::isSupertypeFor(const Type *other) const
{
    return false;
}


/*******************************************
 *
 * Fixed-Length Array Type Definition
 *
 *******************************************/

std::string TypeArray::toString(DisplayMode mode) const
{
    std::ostringstream description;
    description << valueType->toString(mode) << "[" << length << "]";

    return description.str();
}

const Type *TypeArray::getValueType() const { return valueType; }

int TypeArray::getLength() const { return length; }

llvm::ArrayType *TypeArray::getLLVMType(llvm::Module *M) const
{
    uint64_t len = (uint64_t)length;
    llvm::Type *inner = valueType->getLLVMType(M);
    return llvm::ArrayType::get(inner, len);
}

bool TypeArray::requiresDeepCopy() const { return valueType->requiresDeepCopy(); }

const TypeArray * TypeArray::getCopy() const { return this; };

bool TypeArray::isSupertypeFor(const Type *other) const
{
    // An array can only be a supertype of another array
    if (const TypeArray *p = dynamic_cast<const TypeArray *>(other))
    {
        /*
            * If the other array's value type is a subtype of the current
            * array's type AND their lengths match, then we can consider
            * this to be a supertype of the other array.
            */
        return p->valueType->isSubtype(valueType) && this->length == p->length;
    }

    return false;
}


/*******************************************
 *
 * Dynamic-Length Array Type Definition
 *
 *******************************************/

std::string TypeDynArray::toString(DisplayMode mode=C_STYLE) const
{
    return valueType->toString(mode) + "[]";
}

const Type *TypeDynArray::getValueType() const { return valueType; }

llvm::StructType *TypeDynArray::getLLVMType(llvm::Module *M) const
{
    llvm::StructType *ty = llvm::StructType::getTypeByName(M->getContext(), toString());
    if (ty)
        return ty;

    ty = llvm::StructType::create(M->getContext(), toString());

    std::vector<llvm::Type *> typeVec = {
        valueType->getLLVMType(M)->getPointerTo(), // Pointer
        llvm::Type::getInt32Ty(M->getContext()),   // Length
        llvm::Type::getInt32Ty(M->getContext())    // Capacity
    };


    llvm::ArrayRef<llvm::Type *> ref = llvm::ArrayRef(typeVec);
    ty->setBody(ref); // Done like this to enable recursive types

    return ty;
}

// FIXME: VERIFY, THIS PROBS DOENST WORK BC WILL HAVE TO COPY OVER THE MALLOCED DATA!!!
bool TypeDynArray::requiresDeepCopy() const { return valueType->requiresDeepCopy(); }

const TypeDynArray * TypeDynArray::getCopy() const { return this; };

bool TypeDynArray::isSupertypeFor(const Type *other) const
{
    // An array can only be a supertype of another array
    if (const TypeDynArray *p = dynamic_cast<const TypeDynArray *>(other))
    {
        /*
            * If the other array's value type is a subtype of the current
            * array's type AND their lengths match, then we can consider
            * this to be a supertype of the other array.
            */
        return p->valueType->isSubtype(valueType);
    }
    // TODO: allow unsized arrays to become sized!

    return false;
}


/*******************************************
 *
 * Channel Type Definition
 *
 *******************************************/
std::string TypeChannel::toString(DisplayMode mode) const
{
    switch(mode)
    {
        case C_STYLE:
        {
            return "Channel<" + protocol->toString(mode) + ">";
        }
        case MATH_STYLE:
            return "\u21BF" + protocol->toString(mode) + "\u21BE";

    }
    // std::ostringstream description;
    // description << 

    // return description.str();
}

llvm::Type *TypeChannel::getLLVMType(llvm::Module *M) const
{
    // return llvm::Type::getInt32Ty(M->getContext());
    // TODO: bring in line w/ definition in CodegenUtils! (if a change was made in either, itd break the other)
    llvm::StructType *ty = llvm::StructType::getTypeByName(M->getContext(), "_Channel");
    if (ty)
        return ty->getPointerTo();

    return llvm::StructType::create(M->getContext(), "_Channel")->getPointerTo();
}

// Note rhetoric of how we could group each type by fn. ie keep the deep copies together
bool TypeChannel::requiresDeepCopy() const { return false; }

const ProtocolSequence *TypeChannel::getProtocol() const
{
    return protocol;
}

const ProtocolSequence *TypeChannel::getProtocolCopy() const
{
    return protocol->getCopy();
}

const TypeChannel *TypeChannel::getCopy() const
{
    return new TypeChannel(getProtocolCopy());
}

void TypeChannel::setProtocol(const ProtocolSequence *p) const // FIXME: DO BETTER
{
    TypeChannel *u_this = const_cast<TypeChannel *>(this);
    u_this->protocol = p;
}

bool TypeChannel::isGuarded() const // FIXME: DO BETTER, NEED TO ALSO REDIRECT isGuarded!? FOR THIS AND FOR TYPE PROGRAM? NO probably JUST THIS?
{
    return protocol->isGuarded();
}

void TypeChannel::guard() const 
{
    return protocol->guard();
}

bool TypeChannel::unguard() const
{
    return protocol->unguard();
}

bool TypeChannel::isLossy() const 
{
    const std::vector<const Protocol*> steps = this->getProtocol()->getSteps(); 
    if(steps.size() != 1) 
        return false; 

    if(dynamic_cast<const ProtocolClose*>(steps.at(0)))
        return true; 
    return false; 
}

bool TypeChannel::isSupertypeFor(const Type *other) const
{

    if (const TypeChannel *p = dynamic_cast<const TypeChannel *>(other))
    {
        // return p->isSubtype(protocol);
        return toString(C_STYLE) == other->toString(C_STYLE); // FIXME: DO BETTER
    //     // Makes sure that both functions have the same number of parameters
    //     if (p->paramTypes.size() != this->paramTypes.size())
    //         return false;

    //     // Makes sure both functions have the same variadic status
    //     if (this->variadic != p->variadic)
    //         return false;

    //     // Checks that the parameters of this function are all subtypes of the other
    //     for (unsigned int i = 0; i < this->paramTypes.size(); i++)
    //     {
    //         if (this->paramTypes.at(i)->isNotSubtype(p->paramTypes.at(i)))
    //             return false;
    //     }
    //     // Makes sure that the return type of this function is a subtype of the other
    //     return this->retType->isSubtype(p->retType) || (dynamic_cast<const TypeBot *>(this->retType) && dynamic_cast<const TypeBot *>(p->retType));
    }
    return false;
}

/*******************************************
 *
 * Box Type Definition
 *
 *******************************************/
std::string TypeBox::toString(DisplayMode mode) const
{
    std::ostringstream description;
    description << "Box<" << innerType->toString(mode) << ">"; // TODO: remove ostringstream?

    return description.str();
}

const Type *TypeBox::getInnerType() const { return innerType; }

llvm::Type *TypeBox::getLLVMType(llvm::Module *M) const
{
    return innerType->getLLVMType(M)->getPointerTo();
}

bool TypeBox::requiresDeepCopy() const { return true; }

const TypeBox * TypeBox::getCopy() const { return this; };

bool TypeBox::isSupertypeFor(const Type *other) const
{
    if (const TypeBox *p = dynamic_cast<const TypeBox *>(other))
    {
        return innerType->isSubtype(p->innerType);
    }
    return false;
}


/*******************************************
 *
 * Program Type Definition
 *
 *******************************************/
bool TypeProgram::setProtocol(const ProtocolSequence * p) const
{
    if (defined)
        return false;

    TypeProgram *u_this = const_cast<TypeProgram *>(this);
    u_this->defined = true;
    u_this->protocol = p;

    return true;
}

// FIXME: should this and function return the actual name of the type, not just the representation (like what happens with structs and such)
// SHould also greatly improve this
std::string TypeProgram::toString(DisplayMode mode) const
{
    std::ostringstream description;
    description << "PROGRAM : " << (protocol ? protocol->toString(mode) : "PARTIAL DEFINITION");

    return description.str();
}

llvm::FunctionType *TypeProgram::getLLVMFunctionType(llvm::Module *M) const
{
    llvm::Type *ret = Types::UNIT->getLLVMType(M);

     // TODO: bring in line w/ definition in CodegenUtils! (if a change was made in either, itd break the other)
    llvm::StructType *argTy = llvm::StructType::getTypeByName(M->getContext(), "_Channel");
    if (!argTy)
        argTy = llvm::StructType::create(M->getContext(), "_Channel");


    return llvm::FunctionType::get(
        ret,
        {argTy->getPointerTo()},
        false);
}


llvm::PointerType *TypeProgram::getLLVMType(llvm::Module *M) const
{
    return getLLVMFunctionType(M)->getPointerTo();
}

bool TypeProgram::requiresDeepCopy() const { return false; }

std::optional<std::string> TypeProgram::getLLVMName() const { return name; }

bool TypeProgram::setName(std::string n) const
{
    if (name)
        return false;
    TypeProgram *u_this = const_cast<TypeProgram *>(this);
    u_this->name = n;
    return true;
}

bool TypeProgram::isDefined() const { return defined; }

// Note how the class is kinda obscured
const ProtocolSequence * TypeProgram::getProtocol() const
{
    return protocol;
}

const TypeProgram * TypeProgram::getCopy() const { return this; };

bool TypeProgram::isSupertypeFor(const Type *other) const
{
    // // Checks that the other type is also a function
    // if (const TypeFunc *p = dynamic_cast<const TypeFunc *>(other))
    // {
    //     // Makes sure that both functions have the same number of parameters
    //     if (p->paramTypes.size() != this->paramTypes.size())
    //         return false;

    //     // Makes sure both functions have the same variadic status
    //     if (this->variadic != p->variadic)
    //         return false;

    //     // Checks that the parameters of this function are all subtypes of the other
    //     for (unsigned int i = 0; i < this->paramTypes.size(); i++)
    //     {
    //         if (this->paramTypes.at(i)->isNotSubtype(p->paramTypes.at(i)))
    //             return false;
    //     }
    //     // Makes sure that the return type of this function is a subtype of the other
    //     return this->retType->isSubtype(p->retType) || (dynamic_cast<const TypeBot *>(this->retType) && dynamic_cast<const TypeBot *>(p->retType));
    // }
    if (const TypeProgram *p = dynamic_cast<const TypeProgram *>(other))
    {
        return toString(C_STYLE) == other->toString(C_STYLE); // FIXME: DO BETTER
        // return protocol->isSubtype(p->protocol);
    }
    return false;
}

/*******************************************
 *
 * Function
 *
 *******************************************/
bool TypeFunc::setInvoke(std::vector<const Type *> p, const Type *r, bool v) const //Note defaults!! and rhetoric!
{
    if (defined)
        return false;

    TypeFunc *u_this = const_cast<TypeFunc *>(this);
    u_this->defined = true;
    u_this->paramTypes = p;
    u_this->retType = r;
    u_this->variadic = v;

    return true;
}

// PLAN: should improve tostring, make it match syntax + math
std::string TypeFunc::toString(DisplayMode mode) const
{
    std::ostringstream description;

    if (paramTypes.size() == 0)
        description << "()"; // TODO: change whole thing to tuple to make it easier to deal with

    for (unsigned int i = 0; i < paramTypes.size(); i++)
    {
        description << paramTypes.at(i)->toString(mode);

        if (i + 1 < paramTypes.size())
        {
            description << ", ";
        }
    }

    if (variadic)
        description << ", ... ";

    description << "-> ";

    description << retType->toString(mode);
    return description.str();
}

llvm::FunctionType *TypeFunc::getLLVMFunctionType(llvm::Module *M) const
{
    // Create a vector for our argument types
    std::vector<llvm::Type *> typeVec;

    for (const Type *ty : paramTypes)
    {
        typeVec.push_back(ty->getLLVMType(M));
    }

    llvm::ArrayRef<llvm::Type *> paramRef = llvm::ArrayRef(typeVec);

    llvm::Type *ret = retType->getLLVMType(M);

    return llvm::FunctionType::get(
        ret,
        paramRef,
        variadic);
}

llvm::PointerType *TypeFunc::getLLVMType(llvm::Module *M) const
{
    return getLLVMFunctionType(M)->getPointerTo();
}

bool TypeFunc::requiresDeepCopy() const { return false; }

std::optional<std::string> TypeFunc::getLLVMName() const { return name; }
bool TypeFunc::setName(std::string n) const
{
    if (name)
        return false;
    TypeFunc *u_this = const_cast<TypeFunc *>(this);
    u_this->name = n;
    // name = n;
    return true;
}

std::vector<const Type *> TypeFunc::getParamTypes() const { return paramTypes; }

const Type *TypeFunc::getReturnType() const { return retType; }

bool TypeFunc::isVariadic() const { return variadic; }

bool TypeFunc::isDefined() const { return defined; }

const TypeFunc * TypeFunc::getCopy() const { return this; };

bool TypeFunc::isSupertypeFor(const Type *other) const
{
    // Checks that the other type is also a function
    if (const TypeFunc *p = dynamic_cast<const TypeFunc *>(other))
    {
        // Makes sure that both functions have the same number of parameters
        if (p->paramTypes.size() != this->paramTypes.size())
            return false;

        // Makes sure both functions have the same variadic status
        if (this->variadic != p->variadic)
            return false;

        // Checks that the parameters of this function are all subtypes of the other
        for (unsigned int i = 0; i < this->paramTypes.size(); i++)
        {
            if (this->paramTypes.at(i)->isNotSubtype(p->paramTypes.at(i)))
            {
                return false;
            }
        }
        // Makes sure that the return type of this function is a subtype of the other
        return this->retType->isSubtype(p->retType) || (dynamic_cast<const TypeUnit *>(this->retType) && dynamic_cast<const TypeUnit *>(p->retType));
    }
    return false;
}


/*******************************************
 *
 * Type used for Type Inference
 *
 *******************************************/
bool TypeInfer::hasBeenInferred() const { return valueType->has_value(); }

std::optional<const Type*> TypeInfer::getValueType() const
{ 
    if(hasBeenInferred()) return  valueType->value(); 
    return std::nullopt; 
}

/**
 * @brief Returns VAR if type inference has not been completed or {VAR/<INFERRED TYPE>} if type inference has completed.
 *
 * @return std::string
 */
std::string TypeInfer::toString(DisplayMode mode) const
{
    if (hasBeenInferred())
    {
        return "{VAR/" + valueType->value()->toString(mode) + "}";
    }
    return "VAR";
}

llvm::Type *TypeInfer::getLLVMType(llvm::Module *M) const
{
    if (valueType->has_value())
        return valueType->value()->getLLVMType(M);

    // This should never happen: we should have always detected such cases in our semantic analysis
    return nullptr;
}

// FIXME: BAD OPT ACCESS
bool TypeInfer::requiresDeepCopy() const { return valueType->value()->requiresDeepCopy(); }

const TypeInfer * TypeInfer::getCopy() const { return this; };

bool TypeInfer::setValue(const Type *other) const
{
    // Prevent us from being sent another TypeInfer. There's no reason for this to happen
    // as it should have been added as a dependency (and doing this would break things)
    if (dynamic_cast<const TypeInfer *>(other))
        return false;

    // If we have already inferred a type, we just need to check
    // that that type is a subtype of other.
    if (valueType->has_value())
    {
        return other->isSubtype(valueType->value()); // NOTE: CONDITION INVERSED BECAUSE WE CALL IT INVERSED IN SYMBOL.CPP!
    }

    // Set our valueType to be the provided type to see if anything breaks...
    TypeInfer *u_this = const_cast<TypeInfer *>(this);
    *u_this->valueType = other;

    // Run through our dependencies making sure they can all also
    // be compatible with having a type of other.
    bool valid = true;
    for (const TypeInfer *ty : infTypes)
    {
        if (!ty->setValue(other))
        {
            valid = false;
        }
    }

    // Return true/false depending on if the aforementioned process was successful.
    return valid;
}

bool TypeInfer::isSupertypeFor(const Type *other) const
{
    // If we already have an inferred type, we can simply
    // check if that type is a subtype of other.
    if (valueType->has_value())
        // return other->isSubtype(valueType->value());
        return valueType->value()->isSubtype(other);

    /*
        * If the other type is also an inference type...
        */
    if (const TypeInfer *oInf = dynamic_cast<const TypeInfer *>(other))
    {
        // If the other inference type has a value determined, try using that
        if (oInf->valueType->has_value())
        {
            return setValue(oInf->valueType->value());
        }

        // Otherwise, add the types to be dependencies of each other, and return true.
        TypeInfer *u_this = const_cast<TypeInfer *>(this);
        u_this->infTypes.push_back(oInf);

        TypeInfer *moth = const_cast<TypeInfer *>(oInf);
        moth->infTypes.push_back(this);
        return true;
    }

    // Try to update this type's inferred value with the other type
    return setValue(other);
}


/*******************************************
 *
 * Sum Types
 *
 *******************************************/
bool TypeSum::define(std::set<const Type *, TypeCompare> c) const
{
    if (isDefined())
        return false;

    TypeSum *u_this = const_cast<TypeSum *>(this);
    u_this->defined = true;

    u_this->cases = c;

    return true;
}

bool TypeSum::isDefined() const { return defined; }

// auto lexical_compare = [](int a, int b) { return to_string(a) < to_string(b); };

bool TypeSum::contains(const Type *ty) const
{
    return cases.count(ty);
}

std::set<const Type *, TypeCompare> TypeSum::getCases() const { return cases; }

unsigned int TypeSum::getIndex(llvm::Module *M, llvm::Type *toFind) const
{
    std::string type_str;
    llvm::raw_string_ostream rso(type_str);
    toFind->print(rso);
    std::cout << "TOFIND: " << rso.str() << std::endl; 

    unsigned i = 1;

    for (auto e : getCases())
    {
        if (e->getLLVMType(M) == toFind)
        {
            return i;
        }
        i++;
    }
    return (unsigned int)0;
}

// TODO: Improve tostring to make it match syntax?
std::string TypeSum::toString(DisplayMode mode) const
{
    if (name)
        return name.value();

    std::ostringstream description;

    description << "(";

    unsigned int ctr = 0;
    unsigned int size = cases.size();

    for (const Type *el : cases)
    {
        description << el->toString(mode);
        if (++ctr != size)
            description << " + ";
    }
    description << ")";

    return description.str();
}

llvm::StructType *TypeSum::getLLVMType(llvm::Module *M) const
{
    llvm::StructType *ty = llvm::StructType::getTypeByName(M->getContext(), toString(C_STYLE));
    if (ty)
        return ty;

    unsigned int min = std::numeric_limits<unsigned int>::max();
    unsigned int max = std::numeric_limits<unsigned int>::min();

    for (auto e : cases)
    {
        // Note: This is why one has to use pointers in order to nest a type into itself
        llvm::Type* caseType = e->getLLVMType(M);

        unsigned int t = caseType->isSized() ? M->getDataLayout().getTypeAllocSize(caseType) : 0;
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

    // Probably not needed in struct, but might be. 
    // Needed in the case that we generate the type while generating one of the subtypes...
    ty = llvm::StructType::getTypeByName(M->getContext(), toString(C_STYLE));
    if (ty)
        return ty;

    // FIXME: DO BETTER
    uint64_t len = (uint64_t)max;
    llvm::Type *inner = llvm::Type::getInt8Ty(M->getContext());
    llvm::Type *arr = llvm::ArrayType::get(inner, len);

    std::vector<llvm::Type *> typeVec = {llvm::Type::getInt32Ty(M->getContext()), arr};

    llvm::ArrayRef<llvm::Type *> ref = llvm::ArrayRef(typeVec);
    auto ans = llvm::StructType::create(M->getContext(), ref, toString(C_STYLE));
    
    return ans;
}

bool TypeSum::requiresDeepCopy() const
{
    for (auto e : cases)
        if (e->requiresDeepCopy())
            return true;

    return false;
}

const TypeSum * TypeSum::getCopy() const { return this; };

bool TypeSum::isSupertypeFor(const Type *other) const
{
    if (this->contains(other))
        return true;

    if (const TypeSum *oSum = dynamic_cast<const TypeSum *>(other))
    {
        if (this->cases.size() != oSum->cases.size())
            return false;

        for (const Type *t : this->cases)
        {
            bool found = false;

            for (const Type *y : oSum->cases)
            {
                if (t->isSubtype(y))
                {
                    found = true;
                    break;
                }
            }

            if (!found)
                return false;
        }

        return true;
    }

    return false;
}


/*******************************************
 *
 * Struct Types (Product Types w/ Names)
 *
 *******************************************/
std::optional<const Type *> TypeStruct::get(std::string id) const
{
    return elements.lookup(id);
}

std::optional<unsigned int> TypeStruct::getIndex(std::string id) const
{
    return elements.getIndex(id);
}

bool TypeStruct::define(LinkedMap<std::string, const Type *> e) const
{
    if (isDefined())
        return false;

    TypeStruct *u_this = const_cast<TypeStruct *>(this);
    u_this->defined = true;

    u_this->elements = e;
    // u_this->name = n;

    return true;
}

bool TypeStruct::isDefined() const { return defined; }

vector<pair<std::string, const Type *>> TypeStruct::getElements() const { return elements.getElements(); }
optional<unsigned int> TypeStruct::getElementIndex(std::string k) const { return elements.getIndex(k); }

std::string TypeStruct::toString(DisplayMode mode=C_STYLE) const
{
    if (name)
        return name.value();

    std::ostringstream description;

    description << "(";

    unsigned int ctr = 0;
    unsigned int size = elements.getElements().size();

    for (auto e : elements.getElements())
    {
        description << e.second->toString(mode);
        if (++ctr != size)
            description << " * ";
    }
    description << ")";

    return description.str();
}

llvm::StructType *TypeStruct::getLLVMType(llvm::Module *M) const
{
    llvm::StructType *ty = llvm::StructType::getTypeByName(M->getContext(), toString());
    if (ty)
        return ty;

    ty = llvm::StructType::create(M->getContext(), toString());

    std::vector<llvm::Type *> typeVec;

    for (auto ty : elements.getElements())
    {
        typeVec.push_back(ty.second->getLLVMType(M));
    }

    llvm::ArrayRef<llvm::Type *> ref = llvm::ArrayRef(typeVec);
    ty->setBody(ref); // Done like this to enable recursive types

    return ty;
}

bool TypeStruct::requiresDeepCopy() const
{
    for (auto ty : elements.getElements())
        if (ty.second->requiresDeepCopy())
            return true;

    return false;
}

const TypeStruct * TypeStruct::getCopy() const { return this; };

bool TypeStruct::isSupertypeFor(const Type *other) const
{
    // PLAN: allow for extern/import structs
    return this == other; // FIXME: DO BETTER
}
