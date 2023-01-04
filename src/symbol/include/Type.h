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

#include <any>      // Needed for anycasts
#include <utility>  // Needed for anycasts
#include <iostream> // cout
#include <vector>   // Vectors
#include <optional> // Optionals

#include <set> // Sets

#include <climits> // Max & Min

#include "LinkedMap.h"
#include "Protocol.h"

// FIXME: ENABLE LINEAR TYPES!!!
// FIXME: CAN NOW HAVE UNDEFINED TYPES!!!! NEED TO TEST (AND PROBABLY REMOVE NULLPTR)!

/*******************************************
 *
 * Top Type Definition
 *
 *******************************************/
class Type
{
public:
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
     * @param other The posposed subtype of this type.
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

protected:
    /**
     * @brief Internal tool used to determine if this type is a supertype for another type. NOTE: THIS SHOULD NEVER BE CALLED DIRECTLY OUTSIDE OF THE TYPE DEFINITIONS. DOING SO MAY LEAD TO UNUSUAL BEHAVIOR!
     *
     * @param other The type to test against
     * @return true if this is a supertype of other
     * @return false if this is not a supertype of other.
     */
    virtual bool isSupertypeFor(const Type *other) const { return true; } // The top type is the universal supertype
};

class Protocol
{
public:
    virtual ~Protocol() = default;

    /**
     * @brief Returns a human-readable string representation of the Protocol's name.
     *
     * @return std::string The string name of the Protocol
     */
    virtual std::string toString() const = 0;

    virtual const Protocol *getInverse() const = 0;

    virtual const Protocol *getCopy() const = 0; // FIXME: DO BETTER!
};

// FIXME: DO BETTER
struct ProtocolCompare
{
    bool operator()(const Protocol *a, const Protocol *b) const
    {
        return a->toString() < b->toString();
    }
};

/*******************************************
 *
 * Sequential Protocol
 *
 *******************************************/
class ProtocolSequence : public Protocol
{
private:
    vector<const Protocol *> steps;
    // vector<const Protocol *> prev;

public:
    ProtocolSequence(vector<const Protocol *> p)
    {
        steps = p;
    }

    std::string toString() const override
    {
        std::ostringstream description;
        for (auto p : steps)
        {
            description << p->toString() << ";"; // FIXME: DONT PRINT LAST
        }

        return description.str();
    }

    const Protocol *getInverse() const override;

    const ProtocolSequence *getCopy() const override;

    bool isComplete() const
    {
        return steps.size() == 0;
    }

    bool canSend(const Type *ty) const;

    bool send(const Type *ty) const;

    bool canRecv() const;

    optional<const Type *> recv() const;

    bool isWN() const;

    bool contract() const;

    bool weaken() const;

    bool isWNWN() const;

    optional<const ProtocolSequence *> shearLoop() const;

    bool isOC() const;

    optional<const ProtocolSequence *> acceptLoop() const;

    bool isIntChoice() const;

    bool project(const ProtocolSequence *ps) const;

    bool isExtChoice(set<const ProtocolSequence *, ProtocolCompare> testOpts) const;

    void append(const ProtocolSequence *proto) const
    {
        ProtocolSequence *mthis = const_cast<ProtocolSequence *>(this);
        vector<const Protocol *> other = proto->steps;
        mthis->steps.insert(steps.end(), other.begin(), other.end()); // FIXME: WE PROBABLY NEED TO DO BETTER FLATTENING!
    }

    // optional<vector<const Protocol *>> extChoice()
    // {
    // }
};

inline const ProtocolSequence *toSequence(const Protocol *proto)
{
    if (const ProtocolSequence *seq = dynamic_cast<const ProtocolSequence *>(proto))
    {
        return seq;
    }

    vector<const Protocol *> a;
    a.push_back(proto);

    return new ProtocolSequence(a);
}

/*******************************************
 *
 * RecvType Protocol
 *
 *******************************************/
class ProtocolRecv : public Protocol
{
private:
    const Type *recvType;

public:
    ProtocolRecv(const Type *v)
    {
        recvType = v;
    }

    std::string toString() const override
    {
        std::ostringstream description;
        description << "+" << recvType->toString();

        return description.str();
    }

    const Protocol *getInverse() const override;
    const Protocol *getCopy() const override;

    const Type *getRecvType() const { return recvType; }
};

/*******************************************
 *
 * SendType Protocol
 *
 *******************************************/
class ProtocolSend : public Protocol
{
private:
    const Type *sendType;

public:
    ProtocolSend(const Type *v)
    {
        sendType = v;
    }

    std::string toString() const override
    {
        std::ostringstream description;
        description << "-" << sendType->toString();

        return description.str();
    }

    const Protocol *getInverse() const override;
    const Protocol *getCopy() const override;

    const Type *getSendType() const { return sendType; }
};

/*******************************************
 *
 * Why Not Protocol
 *
 *******************************************/
class ProtocolWN : public Protocol
{
private:
    const ProtocolSequence *proto;

public:
    ProtocolWN(const ProtocolSequence *p)
    {
        proto = p;
    }

    std::string toString() const override
    {
        std::ostringstream description;
        description << "?(" << proto->toString() << ")"; // FIXME: NEED PARENS IN REAL DEF!

        return description.str();
    }

    const Protocol *getInverse() const override;
    const Protocol *getCopy() const override;

    const ProtocolSequence *getInnerProtocol() const { return proto; }
};

/*******************************************
 *
 * Of Course Protocol
 *
 *******************************************/
class ProtocolOC : public Protocol
{
private:
    const ProtocolSequence *proto;

public:
    ProtocolOC(const ProtocolSequence *p)
    {
        proto = p;
    }

    std::string toString() const override
    {
        std::ostringstream description;
        description << "!(" << proto->toString() << ")"; // FIXME: NEED PARENS IN REAL DEF!

        return description.str();
    }

    const Protocol *getInverse() const override;
    const Protocol *getCopy() const override;

    const ProtocolSequence *getInnerProtocol() const { return proto; }
};

/*******************************************
 *
 * Internal Choice Protocol
 *
 *******************************************/
class ProtocolIChoice : public Protocol
{
private:
    std::set<const ProtocolSequence *, ProtocolCompare> opts;

public:
    ProtocolIChoice(std::set<const ProtocolSequence *, ProtocolCompare> o)
    {
        opts = o;
    }

    std::string toString() const override
    {
        std::ostringstream description;
        for (auto p : opts)
        {
            description << p->toString() << "&"; // FIXME: DONT PRINT LAST
        }

        return description.str();
    }

    const Protocol *getInverse() const override;
    const Protocol *getCopy() const override;

    std::set<const ProtocolSequence *, ProtocolCompare> getOptions() const { return opts; }
};

/*******************************************
 *
 * External Choice Protocol
 *
 *******************************************/
class ProtocolEChoice : public Protocol
{
private:
    std::set<const ProtocolSequence *, ProtocolCompare> opts;

public:
    ProtocolEChoice(std::set<const ProtocolSequence *, ProtocolCompare> o)
    {
        opts = o;
    }

    std::string toString() const override
    {
        std::ostringstream description;
        for (auto p : opts)
        {
            description << p->toString() << "&"; // FIXME: DONT PRINT LAST
        }

        return description.str();
    }

    const Protocol *getInverse() const override;
    const Protocol *getCopy() const override;

    std::set<const ProtocolSequence *, ProtocolCompare> getOptions() const { return opts; }
};

// FIXME: IMPLEMENT OTHER PROTOS!

/*******************************************
 *
 * Integer (32 bit, signed) Type Definition
 *
 *******************************************/
class TypeInt : public Type
{
public:
    std::string toString() const override { return "INT"; }
    llvm::Type *getLLVMType(llvm::Module *M) const override
    {
        return llvm::Type::getInt32Ty(M->getContext());
    }

protected:
    bool isSupertypeFor(const Type *other) const override; // Defined in .cpp
};

/*******************************************
 *
 *     Boolean (1 bit) Type Definition
 *
 *******************************************/

class TypeBool : public Type
{
public:
    std::string toString() const override { return "BOOL"; }
    llvm::Type *getLLVMType(llvm::Module *M) const override
    {
        return llvm::Type::getInt1Ty(M->getContext());
    }

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
    std::string toString() const override { return "STR"; }
    llvm::Type *getLLVMType(llvm::Module *M) const override { return llvm::Type::getInt8PtrTy(M->getContext()); }

protected:
    bool isSupertypeFor(const Type *other) const override; // Defined in .cpp
};

/*******************************************
 *
 * Bottom/Unit Type
 *
 *******************************************/

class TypeBot : public Type
{
public:
    std::string toString() const override { return "BOT"; }

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
    inline const TypeInt *INT = new TypeInt();
    inline const TypeBool *BOOL = new TypeBool();
    inline const TypeStr *STR = new TypeStr();
    inline const TypeBot *UNDEFINED = new TypeBot();
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
    TypeArray(const Type *v, int l)
    {
        valueType = v;
        length = l;
    }

    /**
     * @brief Returns the name of the string in form of <valueType name>[<array length>].
     *
     * @return std::string String name representation of this type.
     */
    std::string toString() const override
    {
        std::ostringstream description;
        description << valueType->toString() << "[" << length << "]";

        return description.str();
    }

    /**
     * @brief Get the Value Type object
     *
     * @return const Type*
     */
    const Type *getValueType() const { return valueType; }

    /**
     * @brief Get the Length object
     *
     * @return int
     */
    int getLength() const { return length; }

    /**
     * @brief Gets the LLVM type for an array of the given valueType and length.
     *
     * @param C LLVM Context
     * @return llvm::Type*
     */
    llvm::Type *getLLVMType(llvm::Module *M) const override
    {
        uint64_t len = (uint64_t)length;
        llvm::Type *inner = valueType->getLLVMType(M);
        llvm::Type *arr = llvm::ArrayType::get(inner, len);

        return arr;
    }

protected:
    bool isSupertypeFor(const Type *other) const override
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
    TypeChannel(const ProtocolSequence *p)
    {
        protocol = p;
    }

    /**
     * @brief Returns a string representation of the type in format: <PROC | FUNC> (param_0, param_1, ...) -> return_type.
     *
     * @return std::string
     */
    std::string toString() const override
    {
        std::ostringstream description;
        description << "\u21BF" << protocol->toString() << "\u21BE";

        return description.str();
    }

    // TODO: Build LLVM Type here instead of in codegen!
    llvm::Type *getLLVMType(llvm::Module *M) const override
    {
        return llvm::Type::getInt32Ty(M->getContext());; // FIXME: DO BETTER
    }

    const ProtocolSequence *getProtocol() const
    {
        return protocol;
    }

    const ProtocolSequence *getProtocolCopy() const
    {
        return toSequence(protocol->getCopy());
    }

    const TypeChannel *getCopy() const
    {
        return new TypeChannel(getProtocolCopy());
    }

    void setProtocol(const ProtocolSequence *p) const //FIXME: DO BETTER
    {
        TypeChannel *mthis = const_cast<TypeChannel *>(this);
        mthis->protocol = p;
    }

protected:
    bool isSupertypeFor(const Type *other) const override
    {
        return toString() == other->toString(); // FIXME: DO BETTER
        // // Checks that the other type is also invokable
        // if (const TypeInvoke *p = dynamic_cast<const TypeInvoke *>(other))
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
        // return false;
    }
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
    const TypeChannel *channel; // FIXME: PROBABLY NEEDS TO BE SEQ!

    /**
     * @brief Determines if the function has been fully defined (true), or if it is a partial signature (ie, a predeclaration waiting to be fulfilled)
     *
     */
    bool defined = true;

    /**
     * @brief Name used by llvm to represent this function
     *
     */
    std::optional<std::string> name = {}; // NOT FOR SEMANTIC NAMES!!! THIS ONE IS FOR LLVM ONLY

public:
    /**
     * @brief Construct a new Type Invoke object
     *
     * @param p List of type parameters
     * @param v Determines if this should be a variadic
     * @param d Determines if this has been fully defined
     */
    TypeProgram(const TypeChannel *c, bool d) //FIXME: why is d required, if it also defaults to true? (or really, why do we say true if we have to specify it? NOTE: INVOKE defaults to true... and here we use things the same way)
    {
        channel = c;

        defined = d;
    }

    /**
     * @brief Returns a string representation of the type in format: <PROC | FUNC> (param_0, param_1, ...) -> return_type.
     *
     * @return std::string
     */
    std::string toString() const override
    {

        std::ostringstream description;
        description << "PROGRAM : " << channel->toString();

        return description.str();
    }

    // TODO: Build LLVM Type here instead of in codegen!
    llvm::Type *getLLVMType(llvm::Module *M) const override
    {
        // Cretae a vector for our argument types
        // std::vector<llvm::Type *> typeVec;
        // llvm::ArrayRef<llvm::Type *> paramRef = llvm::ArrayRef(typeVec);

        llvm::Type *ret = llvm::Type::getVoidTy(M->getContext());

        llvm::FunctionType *fnType = llvm::FunctionType::get(
            ret,
            {llvm::Type::getInt32Ty(M->getContext())},
            false);

        return fnType->getPointerTo();
    }

    std::optional<std::string> getLLVMName() const { return name; }
    bool setName(std::string n) const
    {
        if (name)
            return false;
        TypeProgram *mthis = const_cast<TypeProgram *>(this);
        mthis->name = n;
        // name = n;
        return true;
    }

    /**
     * @brief Returns if this is defined
     *
     * @return true
     * @return false
     */
    bool isDefined() const { return defined; }

    /**
     * @brief Marks this invokable as defined
     *
     */
    void define() const
    {
        TypeProgram *mthis = const_cast<TypeProgram *>(this);
        mthis->defined = true;
    }

    const TypeChannel *getChannelType() const
    {
        return channel;
    }

protected:
    bool isSupertypeFor(const Type *other) const override
    {
        // // Checks that the other type is also invokable
        // if (const TypeInvoke *p = dynamic_cast<const TypeInvoke *>(other))
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
        if(const TypeProgram *p = dynamic_cast<const TypeProgram*>(other))
        {
            return channel->isSubtype(p->channel); //FIXME: DO BETTER/VERIFY!
        }
        return false;
    }
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
    bool defined = true;

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
    TypeInvoke()
    {
        retType = Types::UNDEFINED;
    }

    /**
     * @brief Construct a new Type Invoke object with the provided arguments and no return type
     *
     * @param p The types of the arguments
     */
    TypeInvoke(std::vector<const Type *> p)
    {
        paramTypes = p;
        retType = Types::UNDEFINED;
    }

    /**
     * @brief Construct a new Type Invoke object
     *
     * @param p List of type parameters
     * @param v Determines if this should be a variadic
     * @param d Determines if this has been fully defined
     */
    TypeInvoke(std::vector<const Type *> p, bool v, bool d)
    {
        paramTypes = p;
        retType = Types::UNDEFINED;

        variadic = v;
        defined = d;
    }

    /**
     * @brief Construct a new Type Invoke object
     *
     * @param p List of type parameters
     * @param r Return type
     */
    TypeInvoke(std::vector<const Type *> p, const Type *r)
    {
        paramTypes = p;
        retType = r;
    }

    /**
     * @brief Construct a new Type Invoke object
     *
     * @param p List of type parameters
     * @param r Return type
     * @param v Determines if this should be a variadic
     * @param d Determines if this has been fully defined
     */
    TypeInvoke(std::vector<const Type *> p, const Type *r, bool v, bool d)
    {
        paramTypes = p;
        retType = r;

        variadic = v;
        defined = d;
    }

    /**
     * @brief Returns a string representation of the type in format: <PROC | FUNC> (param_0, param_1, ...) -> return_type.
     *
     * @return std::string
     */
    std::string toString() const override
    {
        bool isProc = dynamic_cast<const TypeBot *>(retType);

        std::ostringstream description;
        description << (isProc ? "PROC " : "FUNC ");
        for (unsigned int i = 0; i < paramTypes.size(); i++)
        {
            description << paramTypes.at(i)->toString();

            if (i + 1 < paramTypes.size())
            {
                description << ", ";
            }
        }

        if (variadic)
            description << ", ... ";

        description << "-> ";

        description << retType->toString();
        return description.str();
    }

    // TODO: Build LLVM Type here instead of in codegen!
    llvm::Type *getLLVMType(llvm::Module *M) const override
    {
        // Cretae a vector for our argument types
        std::vector<llvm::Type *> typeVec;

        for (const Type *ty : paramTypes)
        {
            typeVec.push_back(ty->getLLVMType(M));
        }

        llvm::ArrayRef<llvm::Type *> paramRef = llvm::ArrayRef(typeVec);

        llvm::Type *ret = retType->getLLVMType(M); // FIXME: WHEN THIS WAS RETTYPE, TRY THAT CASE IN WPL

        llvm::FunctionType *fnType = llvm::FunctionType::get(
            ret,
            paramRef,
            variadic);

        return fnType->getPointerTo();
    }

    std::optional<std::string> getLLVMName() const { return name; }
    bool setName(std::string n) const
    {
        if (name)
            return false;
        TypeInvoke *mthis = const_cast<TypeInvoke *>(this);
        mthis->name = n;
        // name = n;
        return true;
    }

    /**
     * @brief Get the Param Types object
     *
     * @return std::vector<const Type *>
     */
    std::vector<const Type *> getParamTypes() const { return paramTypes; }

    /**
     * @brief Get the Return Type object
     *
     * @return const Type*
     */
    const Type *getReturnType() const { return retType; }

    /**
     * @brief Returns if this is a variadic
     *
     * @return true
     * @return false
     */
    bool isVariadic() const { return variadic; }

    /**
     * @brief Returns if this is defined
     *
     * @return true
     * @return false
     */
    bool isDefined() const { return defined; }

    /**
     * @brief Marks this invokable as defined
     *
     */
    void define() const
    {
        TypeInvoke *mthis = const_cast<TypeInvoke *>(this);
        mthis->defined = true;
    }

protected:
    bool isSupertypeFor(const Type *other) const override
    {
        // Checks that the other type is also invokable
        if (const TypeInvoke *p = dynamic_cast<const TypeInvoke *>(other))
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
                    return false;
            }
            // Makes sure that the return type of this function is a subtype of the other
            return this->retType->isSubtype(p->retType) || (dynamic_cast<const TypeBot *>(this->retType) && dynamic_cast<const TypeBot *>(p->retType));
        }
        return false;
    }
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
    TypeInfer()
    {
        valueType = new std::optional<const Type *>;
    }

    /**
     * @brief Returns if type inference has detemined the type of this var yet
     *
     * @return true
     * @return false
     */
    bool hasBeenInferred() const { return valueType->has_value(); }

    /**
     * @brief Returns VAR if type inference has not been completed or {VAR/<INFERRED TYPE>} if type inference has completed.
     *
     * @return std::string
     */
    std::string toString() const override
    {
        if (hasBeenInferred())
        {
            return "{VAR/" + valueType->value()->toString() + "}";
        }
        return "VAR";
    }

    /**
     * @brief Gets the LLVM representation of the inferred type.
     *
     * @param C LLVM Context
     * @return llvm::Type* the llvm type for the inferred type.
     */
    llvm::Type *getLLVMType(llvm::Module *M) const override
    {
        if (valueType->has_value())
            return valueType->value()->getLLVMType(M);

        // This should never happen: we should have always detected such cases in our semantic analyis
        return nullptr;
    }

    // TODO: There shouldn't be any parody in codegen, but something does seem off.

protected:
    /**
     * @brief Internal helper function used to try updating the type that this inference represents
     *
     * @param other The type we are trying to update to
     * @return true If this type is already a subtype other, or this type can be updated to have the type of other
     * @return false If this type cannot be of type other.
     */
    bool setValue(const Type *other) const
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
        TypeInfer *mthis = const_cast<TypeInfer *>(this);
        *mthis->valueType = other;

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

        // Return true/false depending on if the afformentoned process was successful.
        return valid;
    }

    /**
     * @brief Determines if this is a supertype of another type (and thus, also performs type inferencing).
     *
     * @param other
     * @return true
     * @return false
     */
    bool isSupertypeFor(const Type *other) const override
    {
        // If we already have an inferred type, we can simply
        // check if that type is a subtype of other.
        if (valueType->has_value())
            return other->isSubtype(valueType->value());

        /*
         * If the other type is also an inference type...
         */
        if (const TypeInfer *oinf = dynamic_cast<const TypeInfer *>(other))
        {
            // If the other inference type has a value determined, try using that
            if (oinf->valueType->has_value())
            {
                return setValue(oinf->valueType->value());
            }

            // Otherwise, add the types to be dependencies of eachother, and return true.
            TypeInfer *mthis = const_cast<TypeInfer *>(this);
            mthis->infTypes.push_back(oinf);

            TypeInfer *moth = const_cast<TypeInfer *>(oinf);
            moth->infTypes.push_back(this);
            return true;
        }

        // Try to update this type's inferred value with the other type
        return setValue(other);
    }
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

public:
    TypeSum(std::set<const Type *, TypeCompare> c, std::optional<std::string> n = {})
    {
        cases = c;
        name = n;
    }

    // auto lexical_compare = [](int a, int b) { return to_string(a) < to_string(b); };

    bool contains(const Type *ty) const
    {
        return cases.count(ty);
    }

    std::set<const Type *, TypeCompare> getCases() const { return cases; }

    unsigned int getIndex(llvm::Module *M, llvm::Type *toFind) const
    {
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

    /**
     * @brief Returns the name of the string in form of <valueType name>[<array length>].
     *
     * @return std::string String name representation of this type.
     */
    std::string toString() const override
    {
        if (name)
            return name.value();

        std::ostringstream description;

        description << "(";

        unsigned int ctr = 0;
        unsigned int size = cases.size();

        for (const Type *el : cases)
        {
            description << el->toString();
            if (++ctr != size)
                description << " + ";
        }
        description << ")";

        return description.str();
    }

    /**
     * @brief Gets the LLVM type for an array of the given valueType and length.
     *
     * @param C LLVM Context
     * @return llvm::Type*
     */
    llvm::Type *getLLVMType(llvm::Module *M) const override
    {
        llvm::StructType *ty = llvm::StructType::getTypeByName(M->getContext(), toString());

        if (ty)
            return ty;

        unsigned int min = std::numeric_limits<unsigned int>::max();
        unsigned int max = std::numeric_limits<unsigned int>::min();

        for (auto e : cases)
        {
            // Note: This is why one has to use pointers in order to nest a type into itself
            unsigned int t = M->getDataLayout().getTypeAllocSize(e->getLLVMType(M));
            // FIXME: DO BETTER - ALSO WILL NOT WORK ON VARS! (there are actually a LOT of places where using a var may break things bc we only check for TypeSum)

            // M->getDataLayout().getTypeAllocSize(e->getLLVMType(M));

            if (t < min)
            {
                min = t;
            }

            if (t > max)
            {
                max = t;
            }

            // std::cout << e->toString() << " size: " << t << std::endl; //FIXME: Verify that strings (and such) are done with pointers (which I think they are) so that they don't go out of bounds
        }

        // FIXME: DO BETTER
        uint64_t len = (uint64_t)max;
        llvm::Type *inner = llvm::Type::getInt8Ty(M->getContext());
        llvm::Type *arr = llvm::ArrayType::get(inner, len);

        std::vector<llvm::Type *> typeVec = {llvm::Type::getInt32Ty(M->getContext()), arr};

        llvm::ArrayRef<llvm::Type *> ref = llvm::ArrayRef(typeVec);

        // Needed to prevent duplicating the type's definition
        //  TypeSum *mthis = const_cast<TypeSum *>(this);
        ty = llvm::StructType::create(M->getContext(), ref, toString());

        return ty; // this->llvmType; //FIXME: WHAT SHOULD THE DEFAULT OF EMPTY ENUMS BE? OR I GUESS WE SHOULDNT ALLOW ANY EMPTYS -> but they are in global!!
    }

protected:
    bool isSupertypeFor(const Type *other) const override
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

public:
    TypeStruct(LinkedMap<std::string, const Type *> e, std::optional<std::string> n = {})
    {
        elements = e;
        name = n;
    }

    std::optional<const Type *> get(std::string id) const
    {
        return elements.lookup(id);
    }

    std::optional<unsigned int> getIndex(std::string id) const
    {
        return elements.getIndex(id);
    }

    // std::map<std::string, const Type*> getElements() const { return elements; }
    vector<pair<std::string, const Type *>> getElements() const { return elements.getElements(); }
    /**
     * @brief Returns the name of the string in form of <valueType name>[<array length>].
     *
     * @return std::string String name representation of this type.
     */
    std::string toString() const override
    {
        if (name)
            return name.value();

        std::ostringstream description;

        description << "(";

        unsigned int ctr = 0;
        unsigned int size = elements.getElements().size();

        for (auto e : elements.getElements())
        {
            description << e.second->toString();
            if (++ctr != size)
                description << " * ";
        }
        description << ")";

        return description.str();
    }

    /**
     * @brief Gets the LLVM type for an array of the given valueType and length.
     *
     * @param C LLVM Context
     * @return llvm::Type*
     */
    llvm::Type *getLLVMType(llvm::Module *M) const override
    {
        llvm::StructType *ty = llvm::StructType::getTypeByName(M->getContext(), toString());

        if (ty)
            return ty;

        std::vector<llvm::Type *> typeVec;

        for (auto ty : elements.getElements())
        {
            typeVec.push_back(ty.second->getLLVMType(M));
        }

        llvm::ArrayRef<llvm::Type *> ref = llvm::ArrayRef(typeVec);

        // Needed to prevent duplicating the type's definition
        ty = llvm::StructType::create(M->getContext(), ref, toString());

        return ty;
    }

protected:
    bool isSupertypeFor(const Type *other) const override
    {
        // FIXME: How do we get types across files?
        return this == other; // FIXME: DO BETTER
    }
};
