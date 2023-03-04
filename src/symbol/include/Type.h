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

    virtual bool requiresDeepCopy() const { return false; } // FIXME: WHAT TO DO?

    virtual llvm::Function *clone(llvm::Module *M, llvm::IRBuilder<llvm::NoFolder> *builder) const { return nullptr; } // FIXME:DO BETTER

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
protected:
    unsigned int guardCount = 0;
    virtual std::string as_str() const = 0;

public:
    virtual ~Protocol() = default;

    /**
     * @brief Returns a human-readable string representation of the Protocol's name.
     *
     * @return std::string The string name of the Protocol
     */
    std::string toString() const
    {
        std::ostringstream description;
        for (unsigned int i = 0; i < guardCount; i++)
        {
            description << "*";
        }

        description << as_str();

        return description.str();
    }

    virtual const Protocol *getInverse() const = 0;

    virtual const Protocol *getCopy() const = 0;

    virtual bool isGuarded() const { return guardCount > 0; } // FIXME: handle these better b/c right now kind of sketchy that we only guard first part of protocol step?

    virtual void guard() const // FIXME: DO BETTER
    {
        Protocol *mthis = const_cast<Protocol *>(this);
        mthis->guardCount = mthis->guardCount + 1;
    }

    virtual bool unguard() const // FIXME: DO BETTER
    {
        if (guardCount == 0)
            return false;
        Protocol *mthis = const_cast<Protocol *>(this);

        mthis->guardCount = mthis->guardCount - 1;
        return true;
    }
};

// FIXME: REFACTOR WITH METHOD IN CODEGENVISITOR!
inline llvm::AllocaInst *CreateEntryBlockAlloc(llvm::IRBuilder<llvm::NoFolder> *builder, llvm::Type *ty, std::string identifier)
{
    llvm::Function *fn = builder->GetInsertBlock()->getParent();

    // if (fn != nullptr)
    // {
    // if (llvm::isa<llvm::Function>(insPoint))
    // {
    // llvm::Function *fn = static_cast<llvm::Function *>(insPoint);
    llvm::IRBuilder<> tempBuilder(&fn->getEntryBlock(), fn->getEntryBlock().begin());
    return tempBuilder.CreateAlloca(ty, 0, identifier);
    // return builder->CreateAlloca(ty, 0, identifier);
    // }

    // insPoint = insPoint->getParent();
    // }
    // return std::nullopt;
}

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

    std::string as_str() const override
    {
        std::ostringstream description;
        // for (auto p : steps)
        for (unsigned int i = 0; i < steps.size(); i++)
        {
            if (i != 0)
                description << ";";
            description << steps.at(i)->toString();
        }

        return description.str();
    }

    const Protocol *getInverse() const override;

    const ProtocolSequence *getCopy() const override;

    bool isComplete() const
    {
        return steps.size() == 0;
    }

    // bool canSend(const Type *ty) const;
    optional<const Type *> canSend(const Type *ty) const;

    // bool send(const Type *ty) const;
    optional<const Type *> send(const Type *ty) const;

    bool canRecv() const;

    optional<const Type *> recv() const;

    bool isWN() const;

    bool contract() const;

    bool weaken() const;

    bool isOC() const;

    optional<const ProtocolSequence *> acceptLoop() const;

    bool isIntChoice() const;

    unsigned int project(const ProtocolSequence *ps) const;

    bool isExtChoice(set<const ProtocolSequence *, ProtocolCompare> testOpts) const;

    void append(const ProtocolSequence *proto) const
    {
        ProtocolSequence *mthis = const_cast<ProtocolSequence *>(this);
        vector<const Protocol *> other = proto->steps;
        mthis->steps.insert(steps.end(), other.begin(), other.end()); // Flattening should be good enough for now...
    }

    bool isGuarded() const override // FIXME: DO BETTER
    {
        if (steps.size() == 0)
        {
            return guardCount > 0;
        }
        return steps.front()->isGuarded();
    }

    void guard() const override // FIXME: DO BETTER
    {
        if (steps.size() == 0)
        {
            ProtocolSequence *mthis = const_cast<ProtocolSequence *>(this);
            mthis->guardCount = mthis->guardCount + 1;
        }
        else
        {
            steps.front()->guard();
        }
    }

    bool unguard() const override // FIXME: DO BETTER
    {
        if (steps.size() == 0)
        {
            if (guardCount == 0)
                return false;
            ProtocolSequence *mthis = const_cast<ProtocolSequence *>(this);

            mthis->guardCount = mthis->guardCount - 1;
            return true;
        }

        return steps.front()->unguard();
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

    std::string as_str() const override
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

    std::string as_str() const override
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

    std::string as_str() const override
    {
        std::ostringstream description;
        description << "?(" << proto->toString() << ")";

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

    std::string as_str() const override
    {
        std::ostringstream description;
        description << "!(" << proto->toString() << ")";

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

    std::string as_str() const override
    {
        std::ostringstream description;

        unsigned int i = 0;
        for (auto p : opts)
        {
            if (i != 0)
                description << "&";
            description << p->toString();
            i++;
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

    std::string as_str() const override
    {
        std::ostringstream description;
        unsigned int i = 0;
        for (auto p : opts)
        {
            if (i != 0)
                description << "\u2295";
            description << p->toString();
            i++;
        }

        return description.str();
    }

    const Protocol *getInverse() const override;
    const Protocol *getCopy() const override;

    std::set<const ProtocolSequence *, ProtocolCompare> getOptions() const { return opts; }
};

/*******************************************
 *
 * Integer (32 bit, signed) Type Definition
 *
 *******************************************/
class TypeInt : public Type
{
public:
    std::string toString() const override { return "INT"; }
    llvm::IntegerType *getLLVMType(llvm::Module *M) const override
    {
        return llvm::Type::getInt32Ty(M->getContext());
    }

    bool requiresDeepCopy() const override { return false; }

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

    bool requiresDeepCopy() const override { return false; }

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

    bool requiresDeepCopy() const override { return false; }

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
    std::string toString() const override { return "\u22A5"; }

protected:
    bool isSupertypeFor(const Type *other) const override; // Defined in .cpp
};

/*******************************************
 *
 * Unit Type
 *
 *******************************************/
class TypeUnit : public Type
{
public:
    std::string toString() const override { return "1"; }

protected:
    bool isSupertypeFor(const Type *other) const override; // Defined in .cpp
};

/*******************************************
 *
 * Absurd Type
 *
 *******************************************/
class TypeAbsurd : public Type
{
public:
    std::string toString() const override { return "0"; }

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
    inline const TypeUnit *UNIT = new TypeUnit();
    inline const TypeAbsurd *ABSURD = new TypeAbsurd();
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

    bool requiresDeepCopy() const override { return valueType->requiresDeepCopy(); }

    // std::optional<llvm::Value *> clone(llvm::Module *M, llvm::Value *orig) const override
    // {
    //     // FIXME: WRONG!
    //     return orig; // Stack value, can just return it for the copy.
    // }

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

    std::string toString() const override
    {
        std::ostringstream description;
        description << "\u21BF" << protocol->toString() << "\u21BE";

        return description.str();
    }

    // TODO: Build LLVM Type here instead of in codegen!
    llvm::Type *getLLVMType(llvm::Module *M) const override
    {
        return llvm::Type::getInt32Ty(M->getContext());
    }

    bool requiresDeepCopy() const override { return false; }

    // std::optional<llvm::Value *> clone(llvm::Module *M, llvm::Value *orig) const override
    // {
    //     // FIXME: MOVE NOT COPY!
    //     return orig; // Stack value, can just return it for the copy.
    // }

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

    void setProtocol(const ProtocolSequence *p) const // FIXME: DO BETTER
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
    TypeBox(const Type *t) : innerType(t)
    {
    }

    std::string toString() const override
    {
        std::ostringstream description;
        description << "Box<" << innerType->toString() << ">";

        return description.str();
    }

    const Type *getInnerType() const { return innerType; }

    // TODO: Build LLVM Type here instead of in codegen!
    llvm::Type *getLLVMType(llvm::Module *M) const override
    {
        return innerType->getLLVMType(M)->getPointerTo();
    }

    bool requiresDeepCopy() const override { return true; }

    virtual llvm::Function *clone(llvm::Module *M, llvm::IRBuilder<llvm::NoFolder> *builder) const override
    {
        llvm::Function *testFn = M->getFunction("_clone_" + toString());
        if (testFn)
            return testFn;

        llvm::BasicBlock *ins = builder->GetInsertBlock();

        // FIXME: DONT DUPLICATE THESE ACROSS FILES
        llvm::Function *fn = llvm::Function::Create(llvm::FunctionType::get(
                                                        getLLVMType(M),
                                                        {
                                                            getLLVMType(M),                           // llvm::Type::getInt8PtrTy(M->getContext()), // Value
                                                            llvm::Type::getInt8PtrTy(M->getContext()) // Map
                                                        },
                                                        false),
                                                    llvm::GlobalValue::PrivateLinkage, "_clone_" + toString(), M);

        llvm::BasicBlock *bBlk = llvm::BasicBlock::Create(M->getContext(), "entry", fn);
        builder->SetInsertPoint(bBlk);

        // Bind all of the arguments
        llvm::Value *v = CreateEntryBlockAlloc(builder, getLLVMType(M), "v");

        builder->CreateStore((fn->args()).begin(), v);
        llvm::Value *loaded = builder->CreateLoad(innerType->getLLVMType(M), builder->CreateLoad(getLLVMType(M), v));

        if (innerType->requiresDeepCopy())
        {
            llvm::AllocaInst *m = CreateEntryBlockAlloc(builder, llvm::Type::getInt8PtrTy(M->getContext()), "m");
            builder->CreateStore(fn->getArg(1), m);

            llvm::Value *hasValPtr = builder->CreateCall(
                M->getOrInsertFunction(
                    "_address_map_has",
                    llvm::FunctionType::get(
                        llvm::Type::getInt8PtrTy(M->getContext()),
                        {llvm::Type::getInt8PtrTy(M->getContext()),
                         llvm::Type::getInt8PtrTy(M->getContext())},
                        false)),
                {builder->CreateLoad(llvm::Type::getInt8PtrTy(M->getContext()), m),
                 builder->CreateBitCast(loaded, llvm::Type::getInt8PtrTy(M->getContext()))});

            auto parentFn = builder->GetInsertBlock()->getParent();

            llvm::BasicBlock *thenBlk = llvm::BasicBlock::Create(M->getContext(), "then", parentFn);
            llvm::BasicBlock *elseBlk = llvm::BasicBlock::Create(M->getContext(), "else");
            llvm::BasicBlock *restBlk = llvm::BasicBlock::Create(M->getContext(), "ifcont");

            builder->CreateCondBr(
                builder->CreateZExtOrTrunc(
                    builder->CreateICmpNE(
                        hasValPtr,
                        llvm::Constant::getNullValue(hasValPtr->getType())
                        // llvm::ConstantInt::get(llvm::Type::getInt8Ty(M->getContext()), 0, true)
                        ),
                    llvm::Type::getInt1Ty(M->getContext())),
                thenBlk,
                elseBlk);

            /*
             * Then block
             */
            builder->SetInsertPoint(thenBlk);
            llvm::Value *casted = builder->CreateBitCast(hasValPtr, innerType->getLLVMType(M));

            builder->CreateBr(restBlk);

            thenBlk = builder->GetInsertBlock();

            /*
             * Insert the else block (same as rest if no else branch)
             */
            parentFn->getBasicBlockList().push_back(elseBlk);
            builder->SetInsertPoint(elseBlk);

            // Generate the code for the else block; follows the same logic as the then block.
            llvm::Value *cloned = builder->CreateCall(innerType->clone(M, builder), {loaded,
                                                                                     builder->CreateLoad(llvm::Type::getInt8PtrTy(M->getContext()), m)});
            builder->CreateBr(restBlk);

            elseBlk = builder->GetInsertBlock();

            // As we have an else block, rest and else are different, so we have to merge back in.
            parentFn->getBasicBlockList().push_back(restBlk);
            builder->SetInsertPoint(restBlk);

            llvm::PHINode *phi = builder->CreatePHI(innerType->getLLVMType(M), 2, "phi");
            phi->addIncoming(casted, thenBlk);
            phi->addIncoming(cloned, elseBlk);

            llvm::Value *alloc = builder->CreateCall(
                M->getOrInsertFunction(
                    "GC_malloc",
                    llvm::FunctionType::get(
                        llvm::Type::getInt8PtrTy(M->getContext()),
                        {llvm::Type::getInt64Ty(M->getContext())},
                        false)),
                {builder->getInt64(M->getDataLayout().getTypeAllocSize(innerType->getLLVMType(M)))});

            llvm::Value *casted2 = builder->CreateBitCast(alloc, innerType->getLLVMType(M)->getPointerTo());
            builder->CreateStore(phi, casted2);
            v = casted2;

            builder->CreateCall(
                M->getOrInsertFunction(
                    "_address_map_put",
                    llvm::FunctionType::get(
                        llvm::Type::getVoidTy(M->getContext()),
                        {llvm::Type::getInt8PtrTy(M->getContext()),
                         llvm::Type::getInt8PtrTy(M->getContext()),
                         llvm::Type::getInt8PtrTy(M->getContext())},
                        false)),
                {builder->CreateLoad(llvm::Type::getInt8PtrTy(M->getContext()), m),
                 builder->CreateBitCast(loaded, llvm::Type::getInt8PtrTy(M->getContext())),
                 alloc});
        }
        else
        {
            // llvm::Value *casted = builder->CreateBitCast(v, getLLVMType(M)->getPointerTo());

            llvm::Value *alloc = builder->CreateCall(
                M->getOrInsertFunction(
                    "GC_malloc",
                    llvm::FunctionType::get(
                        llvm::Type::getInt8PtrTy(M->getContext()),
                        {llvm::Type::getInt64Ty(M->getContext())},
                        false)),
                {builder->getInt64(M->getDataLayout().getTypeAllocSize(innerType->getLLVMType(M)))});

            llvm::Value *casted = builder->CreateBitCast(alloc, innerType->getLLVMType(M)->getPointerTo());

            builder->CreateStore(loaded, casted);
            v = casted;
        }

        builder->CreateRet(v);

        builder->SetInsertPoint(ins);

        return fn; // Stack value, can just return it for the copy.
    }

protected:
    bool isSupertypeFor(const Type *other) const override
    {
        if (const TypeBox *p = dynamic_cast<const TypeBox *>(other))
        {
            return innerType->isSubtype(p->innerType);
        }
        return false;
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
    const TypeChannel *channel;

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
    TypeProgram() : defined(false)
    {
    }
    /**
     * @brief Construct a new Type Invoke object
     *
     * @param p List of type parameters
     * @param v Determines if this should be a variadic
     * @param d Determines if this has been fully defined
     */
    TypeProgram(const TypeChannel *c) : channel(c), defined(true)
    {
    }

    bool setChannel(const TypeChannel *c) const
    {
        if (defined)
            return false;

        TypeProgram *mthis = const_cast<TypeProgram *>(this);
        mthis->defined = true;
        mthis->channel = c;

        return true;
    }

    std::string toString() const override
    {
        std::ostringstream description;
        description << "PROGRAM : " << (channel ? channel->toString() : "PARTIAL DEFINITION");

        return description.str();
    }

    llvm::FunctionType *getLLVMFunctionType(llvm::Module *M) const
    {
        // Create a vector for our argument types
        // std::vector<llvm::Type *> typeVec;
        // llvm::ArrayRef<llvm::Type *> paramRef = llvm::ArrayRef(typeVec);

        llvm::Type *ret = llvm::Type::getVoidTy(M->getContext());

        return llvm::FunctionType::get(
            ret,
            {llvm::Type::getInt32Ty(M->getContext())},
            false);
    }

    // TODO: Build LLVM Type here instead of in codegen!
    llvm::PointerType *getLLVMType(llvm::Module *M) const override
    {
        return getLLVMFunctionType(M)->getPointerTo();
    }

    bool requiresDeepCopy() const override { return false; }

    // std::optional<llvm::Value *> clone(llvm::Module *M, llvm::Value *orig) const override
    // {
    //     return orig; // Stack value, can just return it for the copy.
    // }

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
        if (const TypeProgram *p = dynamic_cast<const TypeProgram *>(other))
        {
            return channel->isSubtype(p->channel); // FIXME: DO BETTER/VERIFY!
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
    TypeInvoke() : defined(false)
    {
    }

    /**
     * @brief Construct a new Type Invoke object
     *
     * @param p List of type parameters
     * @param v Determines if this should be a variadic
     * @param d Determines if this has been fully defined
     */
    TypeInvoke(std::vector<const Type *> p, const Type *r = Types::UNIT, bool v = false) : paramTypes(p), retType(r), variadic(v), defined(true)
    {
    }

    bool setInvoke(std::vector<const Type *> p, const Type *r = Types::UNIT, bool v = false) const
    {
        if (defined)
            return false;

        TypeInvoke *mthis = const_cast<TypeInvoke *>(this);
        mthis->defined = true;
        mthis->paramTypes = p;
        mthis->retType = r;
        mthis->variadic = v;

        return true;
    }

    /**
     * @brief Returns a string representation of the type in format: <PROC | FUNC> (param_0, param_1, ...) -> return_type.
     *
     * @return std::string
     */
    std::string toString() const override
    {
        std::ostringstream description;

        if (paramTypes.size() == 0)
            description << "()"; // TODO: change whole thing to tuple to make it easier to deal with

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

    llvm::FunctionType *getLLVMFunctionType(llvm::Module *M) const
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
    // TODO: Build LLVM Type here instead of in codegen!
    llvm::PointerType *getLLVMType(llvm::Module *M) const override
    {
        return getLLVMFunctionType(M)->getPointerTo();
    }

    bool requiresDeepCopy() const override { return false; }

    // std::optional<llvm::Value *> clone(llvm::Module *M, llvm::Value *orig) const override
    // {
    //     return orig; // Stack value, can just return it for the copy.
    // }

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
                {
                    return false;
                }
            }
            // Makes sure that the return type of this function is a subtype of the other
            return this->retType->isSubtype(p->retType) || (dynamic_cast<const TypeUnit *>(this->retType) && dynamic_cast<const TypeUnit *>(p->retType));
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

    // FIXME: BAD OPT ACCESS
    bool requiresDeepCopy() const override { return valueType->value()->requiresDeepCopy(); }

    // std::optional<llvm::Value *> clone(llvm::Module *M, llvm::Value *orig) const override
    // {
    //     // FIXME: WRONG, HAVE TO COPY CHILD!
    //     return orig; // Stack value, can just return it for the copy.
    // }

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

    bool defined; 

public:
    TypeSum(std::set<const Type *, TypeCompare> c, std::optional<std::string> n = {}) : cases(c), name(n), defined(true)
    {}

    TypeSum(std::string n) : name(n), defined(false)
    {}

    bool define(std::set<const Type *, TypeCompare> c) const {
        if(isDefined()) return false; 

        TypeSum *mthis = const_cast<TypeSum *>(this);
        mthis->defined = true; 

        mthis->cases = c; 

        return true; 
    }

    bool isDefined() const { return defined; }

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
    llvm::StructType *getLLVMType(llvm::Module *M) const override
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
        }

        // FIXME: DO BETTER
        uint64_t len = (uint64_t)max;
        llvm::Type *inner = llvm::Type::getInt8Ty(M->getContext());
        llvm::Type *arr = llvm::ArrayType::get(inner, len);

        std::vector<llvm::Type *> typeVec = {llvm::Type::getInt32Ty(M->getContext()), arr};

        llvm::ArrayRef<llvm::Type *> ref = llvm::ArrayRef(typeVec);

        return llvm::StructType::create(M->getContext(), ref, toString());
    }

    bool requiresDeepCopy() const override
    {
        for (auto e : cases)
            if (e->requiresDeepCopy())
                return true;

        return false;
    }

    virtual llvm::Function *clone(llvm::Module *M, llvm::IRBuilder<llvm::NoFolder> *builder) const override
    {
        llvm::Function *testFn = M->getFunction("_clone_" + toString());
        if (testFn)
            return testFn;

        llvm::BasicBlock *ins = builder->GetInsertBlock();

        // FIXME: DONT DUPLICATE THESE ACROSS FILES
        llvm::Function *fn = llvm::Function::Create(llvm::FunctionType::get(
                                                        getLLVMType(M),
                                                        {
                                                            getLLVMType(M),                           // llvm::Type::getInt8PtrTy(M->getContext()), // Value
                                                            llvm::Type::getInt8PtrTy(M->getContext()) // Map
                                                        },
                                                        false),
                                                    llvm::GlobalValue::PrivateLinkage, "_clone_" + toString(), M);

        llvm::BasicBlock *bBlk = llvm::BasicBlock::Create(M->getContext(), "entry", fn);
        builder->SetInsertPoint(bBlk);

        // Bind all of the arguments
        llvm::Value *v = CreateEntryBlockAlloc(builder, getLLVMType(M), "v");

        builder->CreateStore((fn->args()).begin(), v);
        llvm::Value *loaded = builder->CreateLoad(getLLVMType(M), v);

        llvm::Value *alloc = builder->CreateCall(
            M->getOrInsertFunction(
                "GC_malloc",
                llvm::FunctionType::get(
                    llvm::Type::getInt8PtrTy(M->getContext()),
                    {llvm::Type::getInt64Ty(M->getContext())},
                    false)),
            {builder->getInt64(M->getDataLayout().getTypeAllocSize(getLLVMType(M)))});

        llvm::Value *casted = builder->CreateBitCast(alloc, getLLVMType(M)->getPointerTo());

        builder->CreateStore(loaded, casted);
        v = casted;

        if (requiresDeepCopy())
        {
            auto origParent = builder->GetInsertBlock()->getParent();

            llvm::AllocaInst *m = CreateEntryBlockAlloc(builder, llvm::Type::getInt8PtrTy(M->getContext()), "m");
            builder->CreateStore(fn->getArg(1), m);

            llvm::BasicBlock *mergeBlk = llvm::BasicBlock::Create(M->getContext(), "matchcont");

            llvm::Value *tagPtr = builder->CreateGEP(v,
                                                     {llvm::ConstantInt::get(
                                                          llvm::Type::getInt32Ty(M->getContext()),
                                                          0,
                                                          true),
                                                      llvm::ConstantInt::get(
                                                          llvm::Type::getInt32Ty(M->getContext()),
                                                          0,
                                                          true)});

            llvm::Value *tag = builder->CreateLoad(tagPtr->getType()->getPointerElementType(), tagPtr);

            llvm::SwitchInst *switchInst = builder->CreateSwitch(tag, mergeBlk, cases.size());

            unsigned int index = 0;
            for (const Type *caseNode : cases)
            {
                index = index + 1;

                llvm::BasicBlock *matchBlk = llvm::BasicBlock::Create(M->getContext(), "tagBranch" + std::to_string(index));

                builder->SetInsertPoint(matchBlk);

                switchInst->addCase(llvm::ConstantInt::get(llvm::Type::getInt32Ty(M->getContext()), index, true), matchBlk);
                origParent->getBasicBlockList().push_back(matchBlk);

                if (caseNode->requiresDeepCopy())
                {
                    llvm::Value *memLoc = builder->CreateGEP(v, {llvm::ConstantInt::get(
                                                                     llvm::Type::getInt32Ty(M->getContext()),
                                                                     0,
                                                                     true),
                                                                 llvm::ConstantInt::get(
                                                                     llvm::Type::getInt32Ty(M->getContext()),
                                                                     1,
                                                                     true)});
                    llvm::Value *corrected = builder->CreateBitCast(memLoc, caseNode->getLLVMType(M)->getPointerTo());

                    if (caseNode->getLLVMType(M)->isPointerTy())
                    {
                        // llvm::Value *loaded = builder->CreateLoad(caseNode->getLLVMType(M), corrected);

                        llvm::Value *hasValPtr = builder->CreateCall(
                            M->getOrInsertFunction(
                                "_address_map_has",
                                llvm::FunctionType::get(
                                    llvm::Type::getInt8PtrTy(M->getContext()),
                                    {llvm::Type::getInt8PtrTy(M->getContext()),
                                     llvm::Type::getInt8PtrTy(M->getContext())},
                                    false)),
                            {builder->CreateLoad(llvm::Type::getInt8PtrTy(M->getContext()), m),
                             builder->CreateBitCast(memLoc, llvm::Type::getInt8PtrTy(M->getContext()))});

                        auto parentFn = builder->GetInsertBlock()->getParent();

                        llvm::BasicBlock *thenBlk = llvm::BasicBlock::Create(M->getContext(), "then", parentFn);
                        llvm::BasicBlock *elseBlk = llvm::BasicBlock::Create(M->getContext(), "else");
                        llvm::BasicBlock *restBlk = llvm::BasicBlock::Create(M->getContext(), "ifcont");

                        builder->CreateCondBr(
                            builder->CreateZExtOrTrunc(
                                builder->CreateICmpNE(
                                    hasValPtr,
                                    llvm::Constant::getNullValue(hasValPtr->getType())
                                    // llvm::ConstantInt::get(llvm::Type::getInt8Ty(M->getContext()), 0, true)
                                    ),
                                llvm::Type::getInt1Ty(M->getContext())),
                            thenBlk,
                            elseBlk);

                        /*
                         * Then block
                         */
                        builder->SetInsertPoint(thenBlk);
                        llvm::Value *casted = builder->CreateBitCast(hasValPtr, caseNode->getLLVMType(M));

                        builder->CreateBr(restBlk);

                        thenBlk = builder->GetInsertBlock();

                        /*
                         * Insert the else block (same as rest if no else branch)
                         */
                        parentFn->getBasicBlockList().push_back(elseBlk);
                        builder->SetInsertPoint(elseBlk);

                        // Generate the code for the else block; follows the same logic as the then block.
                        llvm::Value *cloned = builder->CreateCall(caseNode->clone(M, builder), {builder->CreateLoad(caseNode->getLLVMType(M), corrected),
                                                                                                builder->CreateLoad(llvm::Type::getInt8PtrTy(M->getContext()), m)});
                        builder->CreateBr(restBlk);

                        elseBlk = builder->GetInsertBlock();

                        // As we have an else block, rest and else are different, so we have to merge back in.
                        parentFn->getBasicBlockList().push_back(restBlk);
                        builder->SetInsertPoint(restBlk);

                        llvm::PHINode *phi = builder->CreatePHI(caseNode->getLLVMType(M), 2, "phi");
                        phi->addIncoming(casted, thenBlk);
                        phi->addIncoming(cloned, elseBlk);

                        builder->CreateStore(phi, memLoc);
                        // v = casted2;

                        builder->CreateCall( // TODO: why here and not in just the case that we have to gen it?
                            M->getOrInsertFunction(
                                "_address_map_put",
                                llvm::FunctionType::get(
                                    llvm::Type::getVoidTy(M->getContext()),
                                    {llvm::Type::getInt8PtrTy(M->getContext()),
                                     llvm::Type::getInt8PtrTy(M->getContext()),
                                     llvm::Type::getInt8PtrTy(M->getContext())},
                                    false)),
                            {builder->CreateLoad(llvm::Type::getInt8PtrTy(M->getContext()), m),
                             builder->CreateBitCast(loaded, llvm::Type::getInt8PtrTy(M->getContext())),
                             builder->CreateBitCast(phi, llvm::Type::getInt8PtrTy(M->getContext()))});
                    }
                    else
                    {

                        llvm::Value *cloned = builder->CreateCall(caseNode->clone(M, builder), {builder->CreateLoad(caseNode->getLLVMType(M), corrected),
                                                                                                builder->CreateLoad(llvm::Type::getInt8PtrTy(M->getContext()), m)});
                        builder->CreateStore(cloned, corrected);
                    }
                }
                builder->CreateRet(builder->CreateLoad(v, getLLVMType(M)));
            }
            origParent->getBasicBlockList().push_back(mergeBlk);
            builder->SetInsertPoint(mergeBlk);
        }

        // builder->CreateRet(v);

        builder->CreateRet(builder->CreateLoad(v, getLLVMType(M)));

        builder->SetInsertPoint(ins);

        return fn; // Stack value, can just return it for the copy.
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

    /**
     * @brief Determines if the function has been fully defined (true), or if it is a partial signature (ie, a predeclaration waiting to be fulfilled)
     *
     */
    bool defined;

public:
    TypeStruct(LinkedMap<std::string, const Type *> e, std::optional<std::string> n = {}) : elements(e), name(n), defined(true)
    {}

    TypeStruct(std::string n) : name(n), defined(false)
    {}

    std::optional<const Type *> get(std::string id) const
    {
        return elements.lookup(id);
    }

    std::optional<unsigned int> getIndex(std::string id) const
    {
        return elements.getIndex(id);
    }

    bool define(LinkedMap<std::string, const Type *> e) const {
        if(isDefined()) return false; 

        TypeStruct *mthis = const_cast<TypeStruct *>(this);
        mthis->defined = true; 

        mthis->elements = e; 
        // mthis->name = n; 

        return true; 
    }

    bool isDefined() const { return defined; }

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
    llvm::StructType *getLLVMType(llvm::Module *M) const override
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

    bool requiresDeepCopy() const override
    {
        for (auto ty : elements.getElements())
            if (ty.second->requiresDeepCopy())
                return true;

        return false;
    }

    virtual llvm::Function *clone(llvm::Module *M, llvm::IRBuilder<llvm::NoFolder> *builder) const override
    {
        llvm::Function *testFn = M->getFunction("_clone_" + toString());
        if (testFn)
            return testFn;

        llvm::BasicBlock *ins = builder->GetInsertBlock();

        // FIXME: DONT DUPLICATE THESE ACROSS FILES
        llvm::Function *fn = llvm::Function::Create(llvm::FunctionType::get(
                                                        getLLVMType(M),
                                                        {
                                                            getLLVMType(M),                           // llvm::Type::getInt8PtrTy(M->getContext()), // Value
                                                            llvm::Type::getInt8PtrTy(M->getContext()) // Map
                                                        },
                                                        false),
                                                    llvm::GlobalValue::PrivateLinkage, "_clone_" + toString(), M);

        llvm::BasicBlock *bBlk = llvm::BasicBlock::Create(M->getContext(), "entry", fn);
        builder->SetInsertPoint(bBlk);

        // Bind all of the arguments
        llvm::Value *v = CreateEntryBlockAlloc(builder, getLLVMType(M), "v");

        builder->CreateStore((fn->args()).begin(), v);
        llvm::Value *loaded = builder->CreateLoad(getLLVMType(M), v);

        llvm::Value *alloc = builder->CreateCall(
            M->getOrInsertFunction(
                "GC_malloc",
                llvm::FunctionType::get(
                    llvm::Type::getInt8PtrTy(M->getContext()),
                    {llvm::Type::getInt64Ty(M->getContext())},
                    false)),
            {builder->getInt64(M->getDataLayout().getTypeAllocSize(getLLVMType(M)))});

        llvm::Value *casted = builder->CreateBitCast(alloc, getLLVMType(M)->getPointerTo());

        builder->CreateStore(loaded, casted);
        v = casted;

        if (requiresDeepCopy())
        {
            llvm::AllocaInst *m = CreateEntryBlockAlloc(builder, llvm::Type::getInt8PtrTy(M->getContext()), "m");
            builder->CreateStore(fn->getArg(1), m);

            // for (unsigned int i = 0; i < elements.size(); i++)
            for (auto eleItr : elements.getElements())
            {
                const Type *eleType = eleItr.second;

                if (eleType->requiresDeepCopy())
                {
                    llvm::Value *memLoc = builder->CreateGEP(casted, {llvm::ConstantInt::get(
                                                                          llvm::Type::getInt32Ty(M->getContext()),
                                                                          0,
                                                                          true),
                                                                      llvm::ConstantInt::get(
                                                                          llvm::Type::getInt32Ty(M->getContext()),
                                                                          elements.getIndex(eleItr.first).value(), // In theory, bad opt access, but should never happen
                                                                          true)});

                    llvm::Value *loaded = builder->CreateLoad(eleType->getLLVMType(M), memLoc);

                    if (eleType->getLLVMType(M)->isPointerTy())
                    {
                        llvm::Value *hasValPtr = builder->CreateCall(
                            M->getOrInsertFunction(
                                "_address_map_has",
                                llvm::FunctionType::get(
                                    llvm::Type::getInt8PtrTy(M->getContext()),
                                    {llvm::Type::getInt8PtrTy(M->getContext()),
                                     llvm::Type::getInt8PtrTy(M->getContext())},
                                    false)),
                            {builder->CreateLoad(llvm::Type::getInt8PtrTy(M->getContext()), m),
                             builder->CreateBitCast(loaded, llvm::Type::getInt8PtrTy(M->getContext()))});

                        auto parentFn = builder->GetInsertBlock()->getParent();

                        llvm::BasicBlock *thenBlk = llvm::BasicBlock::Create(M->getContext(), "then", parentFn);
                        llvm::BasicBlock *elseBlk = llvm::BasicBlock::Create(M->getContext(), "else");
                        llvm::BasicBlock *restBlk = llvm::BasicBlock::Create(M->getContext(), "ifcont");

                        builder->CreateCondBr(
                            builder->CreateZExtOrTrunc(
                                builder->CreateICmpNE(
                                    hasValPtr,
                                    llvm::Constant::getNullValue(hasValPtr->getType())
                                    // llvm::ConstantInt::get(llvm::Type::getInt8Ty(M->getContext()), 0, true)
                                    ),
                                llvm::Type::getInt1Ty(M->getContext())),
                            thenBlk,
                            elseBlk);

                        /*
                         * Then block
                         */
                        builder->SetInsertPoint(thenBlk);
                        llvm::Value *casted = builder->CreateBitCast(hasValPtr, eleType->getLLVMType(M));

                        builder->CreateBr(restBlk);

                        thenBlk = builder->GetInsertBlock();

                        /*
                         * Insert the else block (same as rest if no else branch)
                         */
                        parentFn->getBasicBlockList().push_back(elseBlk);
                        builder->SetInsertPoint(elseBlk);

                        // Generate the code for the else block; follows the same logic as the then block.
                        llvm::Value *cloned = builder->CreateCall(eleType->clone(M, builder), {loaded,
                                                                                               builder->CreateLoad(llvm::Type::getInt8PtrTy(M->getContext()), m)});
                        builder->CreateBr(restBlk);

                        elseBlk = builder->GetInsertBlock();

                        // As we have an else block, rest and else are different, so we have to merge back in.
                        parentFn->getBasicBlockList().push_back(restBlk);
                        builder->SetInsertPoint(restBlk);

                        llvm::PHINode *phi = builder->CreatePHI(eleType->getLLVMType(M), 2, "phi");
                        phi->addIncoming(casted, thenBlk);
                        phi->addIncoming(cloned, elseBlk);

                        // llvm::Value *alloc = builder->CreateCall(
                        //     M->getOrInsertFunction(
                        //         "GC_malloc",
                        //         llvm::FunctionType::get(
                        //             llvm::Type::getInt8PtrTy(M->getContext()),
                        //             {llvm::Type::getInt64Ty(M->getContext())},
                        //             false)),
                        //     {builder->getInt64(M->getDataLayout().getTypeAllocSize(eleType->getLLVMType(M)))});

                        // llvm::Value *casted2 = builder->CreateBitCast(alloc, eleType->getLLVMType(M)->getPointerTo());
                        // builder->CreateStore(phi, casted2);

                        builder->CreateStore(phi, memLoc);
                        // v = casted2;

                        builder->CreateCall( // TODO: why here and not in just the case that we have to gen it?
                            M->getOrInsertFunction(
                                "_address_map_put",
                                llvm::FunctionType::get(
                                    llvm::Type::getVoidTy(M->getContext()),
                                    {llvm::Type::getInt8PtrTy(M->getContext()),
                                     llvm::Type::getInt8PtrTy(M->getContext()),
                                     llvm::Type::getInt8PtrTy(M->getContext())},
                                    false)),
                            {builder->CreateLoad(llvm::Type::getInt8PtrTy(M->getContext()), m),
                             builder->CreateBitCast(loaded, llvm::Type::getInt8PtrTy(M->getContext())),
                             builder->CreateBitCast(phi, llvm::Type::getInt8PtrTy(M->getContext()))});
                    }
                    else
                    {
                        llvm::Value *cloned = builder->CreateCall(eleType->clone(M, builder), {loaded,
                                                                                               builder->CreateLoad(llvm::Type::getInt8PtrTy(M->getContext()), m)});

                        builder->CreateStore(cloned, memLoc);
                    }
                }
            }
        }

        builder->CreateRet(builder->CreateLoad(v, getLLVMType(M)));

        builder->SetInsertPoint(ins);

        return fn; // Stack value, can just return it for the copy.
    }

protected:
    bool isSupertypeFor(const Type *other) const override
    {
        // FIXME: How do we get types across files?
        return this == other; // FIXME: DO BETTER
    }
};

/****************************************
 * Utility Functions
 ****************************************/

inline bool isGuarded(const Type *ty)
{
    if (const TypeChannel *channel = dynamic_cast<const TypeChannel *>(ty))
    {
        return channel->getProtocol()->isGuarded();
    }

    return false;
}

inline bool isLinear(const Type *ty)
{
    if (dynamic_cast<const TypeChannel *>(ty))
        return true; // FIXME: DO BETTER LINEAR CHECK! Maybe separate symbol and value, then we can have linear values and ensure tehy are used?
    return false;
}