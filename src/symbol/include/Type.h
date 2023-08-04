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

class ProtocolSequence;

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
    virtual std::string toString() const { return "TOP"; }

    /**
     * @brief Determines if this type is a subtype of another.
     *
     * @param other The type we are testing to see if we are a subtype of
     * @return true If the current type is a subtype of other
     * @return false If the current type is not a subtype of other.
     */
    virtual bool isSubtype(const Type *other) const;
    virtual bool isNotSubtype(const Type *other) const { return !(isSubtype(other)); }

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

/*******************************************
 *
 * Integer (32 bit, signed) Type Definition
 *
 *******************************************/
class TypeInt : public Type
{
public:
    TypeInt(bool isLinear) : Type(isLinear){}; 

    std::string toString() const override;

    llvm::IntegerType *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override { return false; }

    const TypeInt * getCopy() const override { return this; };

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

    std::string toString() const override;

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

    std::string toString() const override;

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

    std::string toString() const override;

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

    std::string toString() const override;

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
    
    std::string toString() const override;

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
    bool operator()(const Type *a, const Type *b) const
    {
        return a->toString() < b->toString();
    }
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
    int length;

public:
    /**
     * @brief Construct a new TypeArray
     *
     * @param v The type of the array elements
     * @param l The length of the array. NOTE: THIS SHOULD ALWAYS BE AT LEAST ONE!
     */
    TypeArray(const Type *valTy, int len) : Type(false), valueType(valTy), length(len) {}

    /**
     * @brief Returns the name of the string in form of <valueType name>[<array length>].
     *
     * @return std::string String name representation of this type.
     */
    std::string toString() const override;

    /**
     * @brief Get the Value Type object
     *
     * @return const Type*
     */
    const Type *getValueType() const;

    /**
     * @brief Get the Length object
     *
     * @return int
     */
    int getLength() const;

    /**
     * @brief Gets the LLVM type for an array of the given valueType and length.
     *
     * @param C LLVM Context
     * @return llvm::Type*
     */
    llvm::ArrayType *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    const TypeArray * getCopy() const override;

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
     * @brief Construct a new Type Invoke object
     *
     * @param p List of type parameters
     * @param v Determines if this should be a variadic
     * @param d Determines if this has been fully defined
     */
    TypeChannel(const ProtocolSequence *proto) : Type(true), protocol(proto) {}

    std::string toString() const override;

    // TODO: Build LLVM Type here instead of in codegen!
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

    std::string toString() const override;

    const Type *getInnerType() const;

    // TODO: Build LLVM Type here instead of in codegen!
    llvm::Type *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    const TypeBox * getCopy() const override;

protected:
    bool isSupertypeFor(const Type *other) const override;
};

/*******************************************
 *
 * Program Type Definition
 *
 *******************************************/

class TypeProgram : public Type
{
private:
    /**
     * @brief Represents the types of the function's arguments
     *
     */
    const ProtocolSequence *protocol;

    /**
     * @brief Determines if the function has been fully defined (true), or if it is a partial signature (ie, a predeclaration waiting to be fulfilled)
     *
     */
    bool defined;

    /**
     * @brief Name used by llvm to represent this function
     *
     */
    std::optional<std::string> name = {}; // NOT FOR SEMANTIC NAMES!!! THIS ONE IS FOR LLVM ONLY

public:
    TypeProgram() : Type(false), defined(false)
    {
    }
    /**
     * @brief Construct a new Type Invoke object
     *
     * @param p List of type parameters
     * @param v Determines if this should be a variadic
     * @param d Determines if this has been fully defined
     */
    TypeProgram(const ProtocolSequence *p) : Type(false), protocol(p), defined(true)
    {
    }

    bool setProtocol(const ProtocolSequence * p) const; 

    std::string toString() const override;

    llvm::FunctionType *getLLVMFunctionType(llvm::Module *M) const;

    llvm::PointerType *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    std::optional<std::string> getLLVMName() const;

    bool setName(std::string n) const;

    /**
     * @brief Returns if this is defined
     *
     * @return true
     * @return false
     */
    bool isDefined() const;

    const ProtocolSequence * getProtocol() const; 

    const TypeProgram * getCopy() const override;

protected:
    bool isSupertypeFor(const Type *other) const override;
};

/*******************************************
 *
 * Invokable (FUNC/PROC) Type Definition
 *
 *******************************************/

class TypeInvoke : public Type
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
     * @brief Determines if the function has been fully defined (true), or if it is a partial signature (ie, a predeclaration waiting to be fulfilled)
     *
     */
    bool defined;

    /**
     * @brief Name used by llvm to represent this function
     *
     */
    std::optional<std::string> name = {}; // NOT FOR SEMANTIC NAMES!!! THIS ONE IS FOR LLVM ONLY

public:
    /**
     * @brief Construct a new Type Invoke object that has no return and no arguments
     *
     */
    TypeInvoke() : Type(false), defined(false)
    {
    }

    /**
     * @brief Construct a new Type Invoke object
     *
     * @param p List of type parameters
     * @param v Determines if this should be a variadic
     * @param d Determines if this has been fully defined
     */
    TypeInvoke(std::vector<const Type *> p, const Type *r = Types::UNIT, bool v = false) : Type(false), paramTypes(p), retType(r), variadic(v), defined(true)
    {
    }

    bool setInvoke(std::vector<const Type *> p, const Type *r = Types::UNIT, bool v = false) const;

    /**
     * @brief Returns a string representation of the type in format: <PROC | FUNC> (param_0, param_1, ...) -> return_type.
     *
     * @return std::string
     */
    std::string toString() const override;

    llvm::FunctionType *getLLVMFunctionType(llvm::Module *M) const;

    llvm::PointerType *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    std::optional<std::string> getLLVMName() const;

    bool setName(std::string n) const;

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

    const TypeInvoke * getCopy() const override;

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

public:
    TypeInfer() : Type(false) // FIXME: IS IT Non linear?
    {
        valueType = new std::optional<const Type *>;
    }

    /**
     * @brief Returns if type inference has determined the type of this var yet
     *
     * @return true
     * @return false
     */
    bool hasBeenInferred() const;

    std::optional<const Type*> getValueType() const;

    /**
     * @brief Returns VAR if type inference has not been completed or {VAR/<INFERRED TYPE>} if type inference has completed.
     *
     * @return std::string
     */
    std::string toString() const override;
    /**
     * @brief Gets the LLVM representation of the inferred type.
     *
     * @param C LLVM Context
     * @return llvm::Type* the llvm type for the inferred type.
     */
    llvm::Type *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    const TypeInfer * getCopy() const override;

protected:
    /**
     * @brief Internal helper function used to try updating the type that this inference represents
     *
     * @param other The type we are trying to update to
     * @return true If this type is already a subtype other, or this type can be updated to have the type of other
     * @return false If this type cannot be of type other.
     */
    bool setValue(const Type *other) const;

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
 * Sum Types
 *
 *******************************************/
class TypeSum : public Type
{
private:
    /**
     * @brief The types valid in this sum
     *
     */
    std::set<const Type *, TypeCompare> cases = {};

    /**
     * @brief LLVM IR Representation of the type
     *
     */
    // llvm::Type * llvmType;
    std::optional<std::string> name = {};

    bool defined;

public:
    TypeSum(std::set<const Type *, TypeCompare> c, std::optional<std::string> n = {}) : Type(false), cases(c), name(n), defined(true)
    {
    }

    TypeSum(std::string n) : Type(false), name(n), defined(false)
    {
    }

    bool define(std::set<const Type *, TypeCompare> c) const;
    bool isDefined() const;

    // auto lexical_compare = [](int a, int b) { return to_string(a) < to_string(b); };

    bool contains(const Type *ty) const;

    std::set<const Type *, TypeCompare> getCases() const;

    unsigned int getIndex(llvm::Module *M, llvm::Type *toFind) const;

    /**
     * @brief Returns the name of the string in form of <valueType name>[<array length>].
     *
     * @return std::string String name representation of this type.
     */
    std::string toString() const override;

    /**
     * @brief Gets the LLVM type for an array of the given valueType and length.
     *
     * @param C LLVM Context
     * @return llvm::Type*
     */
    llvm::StructType *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    const TypeSum * getCopy() const override;

protected:
    bool isSupertypeFor(const Type *other) const override;
};

/*******************************************
 *
 * Struct Types (Product Types w/ Names)
 *
 *******************************************/
class TypeStruct : public Type
{
private:
    /**
     * @brief The types valid in this sum
     *
     */
    LinkedMap<std::string, const Type *> elements;

    /**
     * @brief LLVM IR Representation of the type
     *
     */
    std::optional<std::string> name;

    /**
     * @brief Determines if the function has been fully defined (true), or if it is a partial signature (ie, a predeclaration waiting to be fulfilled)
     *
     */
    bool defined;

public:
    TypeStruct(LinkedMap<std::string, const Type *> e, std::optional<std::string> n = {}) : Type(false), elements(e), name(n), defined(true)
    {
    }

    TypeStruct(std::string n) : Type(false), name(n), defined(false)
    {
    }

    std::optional<const Type *> get(std::string id) const;

    std::optional<unsigned int> getIndex(std::string id) const;

    bool define(LinkedMap<std::string, const Type *> e) const;

    bool isDefined() const;

    vector<pair<std::string, const Type *>> getElements() const;
    optional<unsigned int> getElementIndex(std::string k) const;

    /**
     * @brief Returns the name of the string in form of <valueType name>[<array length>].
     *
     * @return std::string String name representation of this type.
     */
    std::string toString() const override;

    /**
     * @brief Gets the LLVM type for an array of the given valueType and length.
     *
     * @param C LLVM Context
     * @return llvm::Type*
     */
    llvm::StructType *getLLVMType(llvm::Module *M) const override;

    bool requiresDeepCopy() const override;

    const TypeStruct * getCopy() const override;

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
        std::optional<const Type *> opt = inf->getValueType(); 
        if(!opt) return std::nullopt; //TODO: Handle better? Challenging for things like Struct... (ie, multiplicities), but may be less of a problem, perhaps, when we disable nulls.
        return type_cast<T>(opt.value()); 
    }

    return std::nullopt; 
}