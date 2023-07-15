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

std::string TypeInt::toString() const { return "INT"; }

llvm::IntegerType *TypeInt::getLLVMType(llvm::Module *M) const
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

std::string TypeBool::toString() const { return "BOOL"; }

llvm::Type *TypeBool::getLLVMType(llvm::Module *M) const
{
    return llvm::Type::getInt1Ty(M->getContext());
}

/*********************************************
 *
 * String (dynamic allocation) Type Definition
 *
 *********************************************/
std::string TypeStr::toString() const { return "STR"; }
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
std::string TypeBottom::toString() const { return "\u22A5"; }

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
std::string TypeUnit::toString() const { return "Unit"; } // Used to be 1 pre July 15 2023

const TypeUnit * TypeUnit::getCopy() const { return this; };

llvm::Type *TypeUnit::getLLVMType(llvm::Module *M) const
{
    llvm::StructType *ty = llvm::StructType::getTypeByName(M->getContext(), toString());
    if (ty)
        return ty;

    ty = llvm::StructType::create(M->getContext(), toString());

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
std::string TypeAbsurd::toString() const { return "0"; }

const TypeAbsurd * TypeAbsurd::getCopy() const { return this; };

bool TypeAbsurd::isSupertypeFor(const Type *other) const
{
    return false;
}



/*************************************
 *
 * Protocols
 *
 *************************************/