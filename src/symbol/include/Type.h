#pragma once

/**
 * @file Type.h
 * @author Alex Friedman (ahfriedman.com)
 * @brief Stores information the language's types.
 * @version 0.1
 * @date 2022-11-10
 *
 * @copyright Copyright (M->getContext()) 2022
 *
 */

#include <string>  //Includes strings
#include <sstream> //Used for string streams
#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/NoFolder.h"

#include <any>      // Needed for anycasts
#include <utility>  // Needed for anycasts
#include <vector>   // Vectors
#include <optional> // Optionals

#include <set> // Sets

#include <climits> // Max & Min

#include "LinkedMap.h"
#include "Protocol.h"

#include "SymbolUtils.h"

#include <iostream> // cout

#include "FQN.h"

class ProtocolSequence;

enum InferenceMode {
    SET, 
    QUERY,
    // RESTRICT
};

/*******************************************
 *
 * Top Type Definition
 *
 *******************************************/
class Type
{
public:
    Type(bool linear) : linear(linear) {};
    virtual ~Type() = default;

    /**
     * @brief Returns a human-readable string representation of the type's name.
     *
     * @return std::string The string name of the type
     */
    virtual std::string toString(DisplayMode mode) const { return "TOP"; }

    /**
     * @brief Determines if this type is a subtype of another.
     *
     * @param other The type we are testing to see if we are a subtype of
     * @return true If the current type is a subtype of other
     * @return false If the current type is not a subtype of other.
     */
    virtual bool isSubtype(const Type *other, InferenceMode mode=InferenceMode::SET) const;
    // virtual bool isSubtype(std::vector<const Type *> others) const; 

    virtual bool isNotSubtype(const Type *other, InferenceMode mode=InferenceMode::SET) const { return !(isSubtype(other, mode)); }
    // TODO: probably doesn't work nicely with inference
    virtual bool isNotSubtype(std::vector<const Type *> others, InferenceMode mode=InferenceMode::SET) const; 

    /**
     * @brief Determines if this type is a supertype of another
     *
     * @param other The type to check against.
     * @return true If this is a supertype for other.
     * @return false If this is not a supertype for other.
     */
    virtual bool isSupertype(const Type *other) const { return isSupertypeFor(other); }
    virtual bool isNotSupertype(const Type *other) const { return !isSupertypeFor(other); }

    /**
     * @brief Gets the llvm::Type* which corresponds to the current type in LLVM
     *
     * @param C The llvm context
     * @return llvm::Type* The representation of this type in LLVM
     */
    virtual llvm::Type *getLLVMType(llvm::Module *M) const
    {
        return llvm::Type::getVoidTy(M->getContext());
    }

    virtual bool requiresDeepCopy() const { return false; } // FIXME: WHAT TO DO?

    virtual const Type * getCopy() const { return this; }

    virtual bool isGuarded() const { return linear && guardCount > 0; } 

    virtual void guard() const
    {
        if(!linear) return; 

        guardCount = guardCount + 1;
    }

    virtual bool unguard() const
    {
        if(!linear) return true; 

        if (guardCount == 0)
            return false;

        guardCount = guardCount - 1;
        return true;
    }

    bool isLinear() const { return linear; }

    virtual bool isLossy() const { return !linear; }

    virtual const Type * getCopySubst(std::map<const Type *, const Type *> existing) const { 
        if(existing.contains(this))
            return existing.find(this)->second; 

        existing.insert({this, this});

        return this; 
    }

protected:
    mutable unsigned int guardCount = 0;

    /**
     * @brief Internal tool used to determine if this type is a supertype for another type. NOTE: THIS SHOULD NEVER BE CALLED DIRECTLY OUTSIDE OF THE TYPE DEFINITIONS. DOING SO MAY LEAD TO UNUSUAL BEHAVIOR!
     *
     * @param other The type to test against
     * @return true if this is a supertype of other
     * @return false if this is not a supertype of other.
     */
    virtual bool isSupertypeFor(const Type *other) const { return true; } // The top type is the universal supertype

private: 
    const bool linear; 
};


class NameableType : public Type  {
protected: 
    NameableType(bool v, std::optional<Identifier *> n) : Type(v), identifier(n) {}
    virtual ~NameableType() = default;

// private: 
    mutable std::optional<Identifier *> identifier; 

public: 
    std::optional<Identifier *> getIdentifier() const { return identifier; }

    virtual void setIdentifier(std::optional<Identifier *> nxt) const {
        identifier = nxt; // FIXME: DO BETTER!
    }

    virtual std::string getTypeRepresentation(DisplayMode mode) const = 0;
    bool hasName() const { return identifier.has_value(); }

    std::string toString(DisplayMode mode) const override
    {
        // std::string metaInfo = (meta.has_value() ? meta.value()() : "");
        // return this->getName().value_or("") + (meta.has_value() ? meta.value()() : "");
        // DO NOT USE value_or, as it will force the evaluation of getTypeRepresentation -- leading to infinite recursion
        if (this->hasName())
        {
            return this->getIdentifier().value()->getUniqueNameInScope(); // FIXME: VERIFY
        }
            // return this->getName().value() + metaInfo;
        return getTypeRepresentation(mode);
    } 

    /****************************************
     * 
     * Passthrough functions required of any type
     * 
     ****************************************/

    virtual llvm::Type *getLLVMType(llvm::Module *M) const override = 0;
    virtual bool requiresDeepCopy() const override = 0;
    virtual const Type * getCopy() const override = 0;

    virtual const Type * getCopySubst(std::map<const Type *, const Type *> existing) const override = 0;

protected: 
    virtual bool isSupertypeFor(const Type *other) const override = 0;
};


class TypeNum {
private: 
    bool isSigned;
    unsigned int numBits; 
    bool isFloat; 


public: 
    TypeNum(bool s, unsigned int bits, bool f=false) : isSigned(s), numBits(bits), isFloat(f)
    {}



public: 
    bool Signed() const { return isSigned; }
    unsigned int getNumBits() const { return numBits; }
    bool Float() const { return isFloat; }  

};

/*******************************************
 *
 * Integer (32 bit, signed) Type Definition
 *
 *******************************************/
class TypeInt : public Type, public TypeNum 
{
public:
    TypeInt(bool isLinear) : Type(isLinear), TypeNum(true, 32, false) {}; 

    std::string toString(DisplayMode mode) const override;

    llvm::IntegerType *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override { return false; }

    const TypeInt * getCopy() const override { return this; };

protected:
    bool isSupertypeFor(const Type *other) const override;
};


/*******************************************
 *
 * Integer (32 bit, unsigned) Type Definition
 *
 *******************************************/
class TypeU32 : public Type, public TypeNum
{
public:
    TypeU32(bool isLinear) : Type(isLinear), TypeNum(false, 32, false){}; 

    std::string toString(DisplayMode mode) const override;

    llvm::IntegerType *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override { return false; }

    const TypeU32 * getCopy() const override { return this; };

protected:
    bool isSupertypeFor(const Type *other) const override;
};


/*******************************************
 *
 * Integer (64 bit, signed) Type Definition
 *
 *******************************************/
class TypeI64 : public Type, public TypeNum 
{
public:
    TypeI64(bool isLinear) : Type(isLinear), TypeNum(true, 64, false){}; 

    std::string toString(DisplayMode mode) const override;

    llvm::IntegerType *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override { return false; }

    const TypeI64 * getCopy() const override { return this; };

protected:
    bool isSupertypeFor(const Type *other) const override;
};

/*******************************************
 *
 * Integer (64 bit, unsigned) Type Definition
 *
 *******************************************/
class TypeU64 : public Type, public TypeNum
{
public:
    TypeU64(bool isLinear) : Type(isLinear), TypeNum(false, 64, false){}; 

    std::string toString(DisplayMode mode) const override;

    llvm::IntegerType *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override { return false; }

    const TypeU64 * getCopy() const override { return this; };

protected:
    bool isSupertypeFor(const Type *other) const override;
};

/*******************************************
 *
 *     Boolean (1 bit) Type Definition
 *
 *******************************************/

class TypeBool : public Type
{
public:
    TypeBool(bool isLinear) : Type(isLinear) {}; 

    std::string toString(DisplayMode mode) const override;

    llvm::Type *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override { return false; }

    const TypeBool * getCopy() const override { return this; };

protected:
    bool isSupertypeFor(const Type *other) const override; // Defined in .cpp
};

/*********************************************
 *
 * String (dynamic allocation) Type Definition
 *
 *********************************************/

class TypeStr : public Type
{
public:
    TypeStr(bool isLinear) : Type(isLinear) {}; 

    std::string toString(DisplayMode mode) const override;

    llvm::Type *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override { return false; }

    const TypeStr * getCopy() const override { return this; };

protected:
    bool isSupertypeFor(const Type *other) const override; // Defined in .cpp
};

/*******************************************
 *
 * Bottom Type
 *
 *******************************************/

class TypeBottom : public Type
{
public:
    TypeBottom(bool isLinear) : Type(isLinear) {}; 

    std::string toString(DisplayMode mode) const override;

    const TypeBottom * getCopy() const override;

protected:
    bool isSupertypeFor(const Type *other) const override;
};

/*******************************************
 *
 * Unit Type
 *
 *******************************************/
class TypeUnit : public Type
{
public:
    TypeUnit(bool isLinear) : Type(isLinear) {};

    std::string toString(DisplayMode mode) const override;

    const TypeUnit * getCopy() const override;

    llvm::Type *getLLVMType(llvm::Module *M) const override;

protected:
    bool isSupertypeFor(const Type *other) const override;
};

/*******************************************
 *
 * Absurd Type
 *
 *******************************************/
class TypeAbsurd : public Type
{
public:
    TypeAbsurd(bool isLinear) : Type(isLinear) {}; 
    
    std::string toString(DisplayMode mode) const override;

    const TypeAbsurd * getCopy() const override;

protected:
    bool isSupertypeFor(const Type *other) const override; // Defined in .cpp
};

/*******************************************
 *
 * Basic Types
 *
 *******************************************/

struct TypeCompare
{
    bool operator()(const Type *a, const Type *b) const;
};

namespace Types
{
    inline const TypeInt *DYN_INT = new TypeInt(false);
    inline const TypeInt *LIN_INT = new TypeInt(true);
    inline const TypeBool *DYN_BOOL = new TypeBool(false);
    inline const TypeBool *LIN_BOOL = new TypeBool(true);
    inline const TypeStr *DYN_STR = new TypeStr(false);
    inline const TypeStr *LIN_STR = new TypeStr(true);
    inline const TypeUnit *UNIT = new TypeUnit(false);
    inline const TypeAbsurd *ABSURD = new TypeAbsurd(false);

    inline const TypeU32 *DYN_U32 = new TypeU32(false);
    inline const TypeI64 *DYN_I64 = new TypeI64(false);
    inline const TypeU64 *DYN_U64 = new TypeU64(false);
};

/*******************************************
 *
 * Fixed-Length Array Type Definition
 *
 *******************************************/
class TypeArray : public Type
{
private:
    /**
     * @brief The type of the array elements
     *
     */
    const Type *valueType;

    /**
     * @brief The length of the array
     *
     */
    uint32_t length;

public:
    /**
     * @brief Construct a TypeArray
     *
     * @param v The type of the array elements
     * @param l The length of the array. NOTE: THIS SHOULD ALWAYS BE AT LEAST ONE!
     */
    TypeArray(const Type *valTy, uint32_t len) : Type(false), valueType(valTy), length(len) {}

    /**
     * @brief Returns the name of the string in form of <valueType name>[<array length>].
     *
     * @return std::string String name representation of this type.
     */
    std::string toString(DisplayMode mode) const override;

    /**
     * @brief Get the Value Type object
     *
     * @return const Type*
     */
    const Type *getValueType() const;

    /**
     * @brief Get the Length object
     *
     * @return uint32_t
     */
    uint32_t getLength() const;

    /**
     * @brief Gets the LLVM type for an array of the given valueType and length.
     *
     * @param C LLVM Context
     * @return llvm::Type*
     */
    llvm::ArrayType *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    const TypeArray * getCopy() const override;

    const Type * getCopySubst(std::map<const Type *, const Type *> existing) const override;

protected:
    bool isSupertypeFor(const Type *other) const override;
};


/*******************************************
 *
 * Dynamic-Length Array Type Definition
 *
 *******************************************/
class TypeDynArray : public Type
{
private:
    /**
     * @brief The type of the array elements
     *
     */
    const Type *valueType;

public:
    /**
     * @brief Construct a TypeArray
     *
     * @param v The type of the array elements
     */
    TypeDynArray(const Type *valTy) : Type(false), valueType(valTy)  {}

    /**
     * @brief Returns the name of the string in form of <valueType name>[<array length>].
     *
     * @return std::string String name representation of this type.
     */
    std::string toString(DisplayMode mode) const override;

    /**
     * @brief Get the Value Type object
     *
     * @return const Type*
     */
    const Type *getValueType() const;

    /**
     * @brief Gets the LLVM type for an array of the given valueType and length.
     *
     * @param C LLVM Context
     * @return llvm::Type*
     */
    llvm::StructType *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    const TypeDynArray * getCopy() const override;

    const Type * getCopySubst(std::map<const Type *, const Type *> existing) const override;

protected:
    bool isSupertypeFor(const Type *other) const override;
};

/*******************************************
 *
 * Channel Type Definition
 *
 *******************************************/

class TypeChannel : public Type
{
private:
    /**
     * @brief Represents the types of the function's arguments
     *
     */
    const ProtocolSequence *protocol;

public:
    /**
     * @brief Construct a Type Channel object
     * 
     * @param proto The protocol sequence for the channel to follow
     */
    TypeChannel(const ProtocolSequence *proto) : Type(true), protocol(proto) {}

    std::string toString(DisplayMode mode) const override;

    llvm::Type *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    const ProtocolSequence *getProtocol() const;

    const ProtocolSequence *getProtocolCopy() const;

    const TypeChannel *getCopy() const override;

    void setProtocol(const ProtocolSequence *p) const;

    bool isGuarded() const override; 

    void guard() const override;

    bool unguard() const override;

    bool isLossy() const override; 

    // FIXME: IMPL!
    // const Type * getCopySubst(std::map<const Type *, const Type *> existing) const override;

protected:
    bool isSupertypeFor(const Type *other) const override;

};

/*******************************************
 *
 * Box Type Definition
 *
 *******************************************/

class TypeBox : public Type
{
private:
    /**
     * @brief Type stored in the box
     *
     */
    const Type *innerType;

public:
    TypeBox(const Type *t) : Type(false), innerType(t) {}

    std::string toString(DisplayMode mode) const override;

    const Type *getInnerType() const;

    llvm::Type *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    const TypeBox * getCopy() const override;

    const Type * getCopySubst(std::map<const Type *, const Type *> existing) const override;

protected:
    bool isSupertypeFor(const Type *other) const override;

};

/*******************************************
 *
 * Program Type Definition
 *
 *******************************************/

class TypeProgram : public NameableType
{
private:
    /**
     * @brief Represents the types of the function's arguments
     *
     */
    const ProtocolSequence *protocol;

    /**
     * @brief Determines if the function has been fully defined (true), or if it is a partial signature (ie, a pre-declaration waiting to be fulfilled)
     *
     */
    bool defined;

public:
    TypeProgram() 
        : NameableType(false, std::nullopt)
        , defined(false)
    {}

    /**
     * @brief Construct a Type Program object
     * 
     * @param p The protocol sequence for the program's main channel to follow
     */
    TypeProgram(const ProtocolSequence *p) 
        : NameableType(false, std::nullopt)
        , protocol(p)
        , defined(true)
    {}

    bool setProtocol(const ProtocolSequence * p) const; 

    std::string getTypeRepresentation(DisplayMode mode) const override; 


    llvm::FunctionType *getLLVMFunctionType(llvm::Module *M) const;

    llvm::PointerType *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    // std::optional<std::string> getLLVMName() const;

    // bool setName(std::string n) const;

    /**
     * @brief Returns if this is defined
     *
     * @return true
     * @return false
     */
    bool isDefined() const;

    const ProtocolSequence * getProtocol() const; 

    const TypeProgram * getCopy() const override;

    const Type * getCopySubst(std::map<const Type *, const Type *> existing) const override;

protected:
    bool isSupertypeFor(const Type *other) const override;

};

/*******************************************
 *
 * Function Type Definition
 *
 *******************************************/

// TODO: With generics, allow for pattern matching? Ie, 
// <TY1, TY2 : { someIdentifier : TY1, ...}> ? 
class TypeFunc : public NameableType
{
private:
    /**
     * @brief Represents the types of the function's arguments
     *
     */
    std::vector<const Type *> paramTypes;

    /**
     * @brief Represents the function's return type.
     *
     */
    const Type *retType;

    /**
     * @brief Determines if the function should be variadic.
     *
     */
    bool variadic = false;

    /**
     * @brief Determines if the function has been fully defined (true), or if it is a partial signature (ie, a pre-declaration waiting to be fulfilled)
     *
     */
    bool defined;

    // FIXME: FUNCS ALWAYS HAVE NULLOPT NAME?!
public:
    TypeFunc() 
        : NameableType(false, std::nullopt)
        , defined(false)
    {}

    /**
     * @brief Construct a TypeFunc object
     *
     * @param p List of type parameters
     * @param v Determines if this should be a variadic
     * @param d Determines if this has been fully defined
     */
    TypeFunc(std::vector<const Type *> p, const Type *r = Types::UNIT, bool v = false) 
        : NameableType(false, std::nullopt)
        , paramTypes(p)
        , retType(r)
        , variadic(v)
        , defined(true)
    {}

    bool setInvoke(std::vector<const Type *> p, const Type *r = Types::UNIT, bool v = false) const;

    std::string getTypeRepresentation(DisplayMode mode) const override; 

    llvm::FunctionType *getLLVMFunctionType(llvm::Module *M) const;

    llvm::PointerType *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;
    /**
     * @brief Get the Param Types object
     *
     * @return std::vector<const Type *>
     */
    std::vector<const Type *> getParamTypes() const;

    /**
     * @brief Get the Return Type object
     *
     * @return const Type*
     */
    const Type *getReturnType() const;

    /**
     * @brief Returns if this is a variadic
     *
     * @return true
     * @return false
     */
    bool isVariadic() const;

    /**
     * @brief Returns if this is defined
     *
     * @return true
     * @return false
     */
    bool isDefined() const;

    const TypeFunc * getCopy() const override;

    const Type * getCopySubst(std::map<const Type *, const Type *> existing) const override;
    
protected:
    bool isSupertypeFor(const Type *other) const override;

};

/*******************************************
 *
 * Type used for Type Inference
 *
 *******************************************/
class TypeInfer : public Type
{
private:
    /**
     * @brief Optional type that represents the inferred type (type this is acting as). Empty if inference was unable to determine the type or is not complete
     *
     */
    std::optional<const Type *> *valueType;

    /**
     * @brief Keeps track of all the other inferred types that this shares a dependency with.
     *
     */
    std::vector<const TypeInfer *> infTypes;

    /**
     * @brief Keeps track of a set of possible types for this infer to resolve to. If left empty, this behaves as normal
     * 
     */
    std::set<const Type *> possibleTypes; 

public:
    TypeInfer(std::set<const Type *> pt = {}) : Type(false) // FIXME: IS IT Non linear?
    {
        valueType = new std::optional<const Type *>;
        possibleTypes = pt; 
    }

    /**
     * @brief Returns if type inference has determined the type of this var yet
     *
     * @return true
     * @return false
     */
    bool hasBeenInferred() const;
    bool hasPossibleTypes() const { return !possibleTypes.empty(); }

    std::optional<const Type*> getValueType() const;

    /**
     * @brief Returns VAR if type inference has not been completed or {VAR/<INFERRED TYPE>} if type inference has completed.
     *
     * @return std::string
     */
    std::string toString(DisplayMode mode) const override;
    /**
     * @brief Gets the LLVM representation of the inferred type.
     *
     * @param C LLVM Context
     * @return llvm::Type* the llvm type for the inferred type.
     */
    llvm::Type *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    const TypeInfer * getCopy() const override;

    // FIXME: IMPL!
    // const Type * getCopySubst(std::map<const Type *, const Type *> existing) const override;

    bool unify() const; 
protected:
    /**
     * @brief Internal helper function used to try updating the type that this inference represents
     *
     * @param other The type we are trying to update to
     * @return true If this type is already a subtype other, or this type can be updated to have the type of other
     * @return false If this type cannot be of type other.
     */
    bool setValue(const Type *other, InferenceMode mode) const;

    /**
     * @brief Determines if this is a supertype of another type (and thus, also performs type inferencing).
     *
     * @param other
     * @return true
     * @return false
     */
    bool isSupertypeFor(const Type *other) const override;
friend class Type; 
    bool isSupertypeFor(const Type *other, InferenceMode mode) const;

};

/*******************************************
 *
 * Sum Types
 *
 *******************************************/
class TypeSum : public NameableType
{
private:
    /**
     * @brief The types valid in this sum
     *
     */
    std::set<const Type *, TypeCompare> cases = {};

    bool defined;

public:
    TypeSum(std::set<const Type *, TypeCompare> c, std::optional<Identifier *> n = {}) 
        : NameableType(false, n)
        , cases(c)
        , defined(true)
    {}

    TypeSum(std::optional<Identifier *> n = {})
        : NameableType(false, n)
        , defined(false)
    {}

    bool define(std::set<const Type *, TypeCompare> c) const;
    bool isDefined() const;

    // auto lexical_compare = [](int a, int b) { return to_string(a) < to_string(b); };

    bool contains(const Type *ty) const;

    std::set<const Type *, TypeCompare> getCases() const;

    unsigned int getIndex(llvm::Module *M, llvm::Type *toFind) const;

    std::string getTypeRepresentation(DisplayMode mode) const override; 

    /**
     * @brief Gets the LLVM type for an array of the given valueType and length.
     *
     * @param C LLVM Context
     * @return llvm::Type*
     */
    llvm::StructType *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    const TypeSum * getCopy() const override;

    const Type * getCopySubst(std::map<const Type *, const Type *> existing) const override;

protected:
    bool isSupertypeFor(const Type *other) const override;

};

/*******************************************
 *
 * Struct Types (Product Types w/ Names)
 *
 *******************************************/
class TypeStruct : public NameableType
{
private:
    /**
     * @brief The types valid in this sum
     *
     */
    LinkedMap<std::string, const Type *> elements;

    /**
     * @brief Determines if the function has been fully defined (true), or if it is a partial signature (ie, a pre-declaration waiting to be fulfilled)
     *
     */
    bool defined;

public:
    TypeStruct(LinkedMap<std::string, const Type *> e, std::optional<Identifier *> n = {}) 
        : NameableType(false, n)
        , elements(e)
        , defined(true)
    {}

    TypeStruct(std::optional<Identifier *> n = {}) 
        : NameableType(false, n)
        , defined(false)
    {}

    std::optional<const Type *> get(std::string id) const;

    std::optional<unsigned int> getIndex(std::string id) const;

    bool define(LinkedMap<std::string, const Type *> e) const;

    bool isDefined() const;

    vector<pair<std::string, const Type *>> getElements() const;
    optional<unsigned int> getElementIndex(std::string k) const;

    std::string getTypeRepresentation(DisplayMode mode) const override; 

    /**
     * @brief Gets the LLVM type for an array of the given valueType and length.
     *
     * @param C LLVM Context
     * @return llvm::Type*
     */
    llvm::StructType *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    const TypeStruct * getCopy() const override;

    const Type * getCopySubst(std::map<const Type *, const Type *> existing) const override;


protected:
    bool isSupertypeFor(const Type *other) const override;

};


/****************************************
 * Utility Functions
 ****************************************/

template <typename T>
inline std::optional<const T*> type_cast(const Type * ty) 
{
    if(const T* ans = dynamic_cast<const T*>(ty))
    {
        return ans; 
    }

    if(const TypeInfer * inf = dynamic_cast<const TypeInfer *>(ty))
    {
        inf->unify(); // TODO: maybe move unify call to getValueType()?
        std::optional<const Type *> opt = inf->getValueType(); 
        if(!opt) return std::nullopt; //TODO: Handle better? Challenging for things like Struct... (ie, multiplicities), but may be less of a problem, perhaps, when we disable nulls.
        return type_cast<T>(opt.value()); 
    }

    return std::nullopt; 
}




/*******************************************
 *
 * Generic Type; Used for polymorphism. 
 *
 *******************************************/
class TypeGeneric : public Type
{
private: 
    std::string identifier; 
    std::optional<const Type *> actingType = std::nullopt; 
public:
    TypeGeneric(bool isLinear, std::string id) : Type(isLinear), identifier(id) {}; 

    std::string toString(DisplayMode mode) const override { 
        if(actingType) return actingType.value()->toString(mode); 
        return identifier;
        // return actingType->toString(mode); 
    }

    llvm::Type *getLLVMType(llvm::Module *M) const override {
        if(actingType)
            return actingType.value()->getLLVMType(M); 

        std::cerr << "1082: Attempted to take llvm type of a generic parameter" << std::endl;
        return llvm::Type::getVoidTy(M->getContext());
    } 

    bool requiresDeepCopy() const override { 
        if(actingType)
            return actingType.value()->requiresDeepCopy(); 
        std::cerr << "1089: Attempted to determine if a generic parameter requires a deep copy" << std::endl;
        return false; 
    } //false; }

    const TypeGeneric * getCopy() const override { return this; };

    std::string getId() const { return identifier; }
    // const Type * getActingType() const { return actingType; }
    void setActingType(const Type * nxt) { actingType = nxt; }

    // FIXME: IMPL
    // const Type * getCopySubst(std::map<const Type *, const Type *> existing) const override;

protected:
    bool isSupertypeFor(const Type *other) const override { return this == other; }

};

class  TemplateInfo {
public: // TODO CHANGE
//     std::vector<SymbolRef> templates; 
    std::vector<std::pair<std::string, TypeGeneric *>> templates; 

public: 
    TemplateInfo( std::vector<std::pair<std::string, TypeGeneric *>> t) : templates(t) {}    
    ~TemplateInfo() = default; 
};

/*******************************************
 *
 * Type used for Generics Inference
 *
 *******************************************/
class TypeTemplate : public NameableType
{
private:
    std::optional<const NameableType *> valueType;

    mutable std::map<std::vector<const Type *>, const NameableType *> registeredTemplates = {};

    std::optional<TemplateInfo> info; 

    bool defined = false; 
 

public:
    TypeTemplate() : NameableType(false, std::nullopt), info(std::nullopt), defined(false) {}

    TypeTemplate(std::optional<TemplateInfo> i, const NameableType * vt) : NameableType(false, std::nullopt), valueType(vt), info(i), defined(true)// FIXME: IS IT Non linear?
    {
    }

    bool isDefined() const { return defined; }

    std::optional<TemplateInfo> getTemplateInfo() const { return info; }

    // PLAN: Contract that such a function may exist, but no guarantee about param types?
    bool define(std::optional<TemplateInfo> i, const NameableType * vt) const;

    void setIdentifier(std::optional<Identifier *> nxt) const override; 

    std::optional<const NameableType *> getValueType() const;

    std::optional<const NameableType *> canApplyTemplate(std::vector<const Type *>) const; 

    /**
     * @brief Returns VAR if type inference has not been completed or {VAR/<INFERRED TYPE>} if type inference has completed.
     *
     * @return std::string
     */
    // std::string toString(DisplayMode mode) const override;
    std::string getTypeRepresentation(DisplayMode mode) const override;

    std::string templateString(DisplayMode mode) const; 
    
    /**
     * @brief Gets the LLVM representation of the inferred type.
     *
     * @param C LLVM Context
     * @return llvm::Type* the llvm type for the inferred type.
     */
    llvm::Type *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    const TypeTemplate * getCopy() const override;

    const Type * getCopySubst(std::map<const Type *, const Type *> existing) const override;

    const std::map<std::vector<const Type *>, const NameableType *> getRegisteredTemplates() const { return registeredTemplates; }

protected:
    /**
     * @brief Determines if this is a supertype of another type (and thus, also performs type inferencing).
     *
     * @param other
     * @return true
     * @return false
     */
    bool isSupertypeFor(const Type *other) const override;
};


/*******************************************
 *
 * Type used for files/namespaces/modules  
 *
 *******************************************/
class TypeModule : public NameableType
{
private:
    // Scope * innerScope;
    bool defined = false; 
public:
    TypeModule() 
        : NameableType(false, std::nullopt)
        , defined(false) 
    {}
    bool isDefined() const { return defined; }

    std::string getTypeRepresentation(DisplayMode mode) const override;
    
    /**
     * @brief Gets the LLVM representation of the inferred type.
     *
     * @param C LLVM Context
     * @return llvm::Type* the llvm type for the inferred type.
     */
    llvm::Type *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    const TypeModule * getCopy() const override;

    const Type * getCopySubst(std::map<const Type *, const Type *> existing) const override;


protected:
    /**
     * @brief Determines if this is a supertype of another type (and thus, also performs type inferencing).
     *
     * @param other
     * @return true
     * @return false
     */
    bool isSupertypeFor(const Type *other) const override;
};