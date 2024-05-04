#pragma once

/**
 * @file Protocol.h
 * @author Alex Friedman (ahfriedman.com)
 * @brief
 * @version 1.3.4
 * @date 2023-08-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <string>  //Includes strings

#include <vector>   // Vectors
#include <optional> // Optionals

#include <set> // Sets

#include <variant>


#include "Type.h"
#include "SymbolUtils.h"

class Type;
class TypeSum;

class ProtocolSend;
class ProtocolRecv;
class ProtocolOC;
class ProtocolWN;
class ProtocolIChoice;

class ProtocolClose; 

struct ProtocolBranchOption; 

class Protocol
{
protected:
    virtual std::string as_str(DisplayMode mode) const = 0;
    mutable unsigned int guardCount = 0;
    const bool inCloseable = false;

public:
    Protocol(bool _inCloseable) : inCloseable(_inCloseable){};

    virtual ~Protocol() = default;

    /**
     * @brief Returns a human-readable string representation of the Protocol's name.
     *
     * @return std::string The string name of the Protocol
     */
    std::string toString(DisplayMode mode) const
    {
        std::ostringstream description;
        for (unsigned int i = 0; i < guardCount; i++)
        {
            description << "*";
        }

        description << as_str(mode);

        return description.str();
    }

    virtual bool isInCloseable() const { return inCloseable; }

    virtual const Protocol *getInverse() const = 0;

    virtual const Protocol *getCopy() const = 0;

    // virtual bool isClosable() const = 0;

    // FIXME: ALMOST SAME AS TO TYPE!
    virtual bool isGuarded() const { return guardCount > 0; } // FIXME: handle these better b/c right now kind of sketchy that we only guard first part of protocol step?
    
    // FIXME: Change to be more robust (ie, flags) + allow soft cancel in loops!
    virtual bool isCancelable() const { return guardCount == 0; }

    virtual void guard() const
    {
        guardCount = guardCount + 1;
    }

    virtual bool unguard() const
    {
        if (guardCount == 0)
            return false;

        guardCount = guardCount - 1;
        return true;
    }

    bool isSubtype(const Protocol * other) const; 

    virtual const Protocol * getCopySubst(std::map<const Type *, const Type *> & existing) const = 0;
protected: 
    virtual bool isSupertypeFor(const Protocol *other) const = 0; 
};

// FIXME: DO BETTER, can probably be removed
struct ProtocolCompare
{
    bool operator()(const Protocol *a, const Protocol *b) const
    {
        return a->toString(DisplayMode::C_STYLE) < b->toString(DisplayMode::C_STYLE);
    }
};
struct RecvMetadata 
{
    const Type* protocolType; 
    optional<const TypeSum*> actingType; 

    RecvMetadata(const Type* inner, bool isSum);

    // const TypeSum * asSum();// { return new TypeSum({innerType, Types::UNIT}); }
};


class ProtocolSequence; 
struct CaseMetadata 
{
    vector<const ProtocolSequence *> fullSequences; 
    const ProtocolSequence * rest; 

    CaseMetadata(vector<const ProtocolSequence *> s, const ProtocolSequence * r) 
        : fullSequences(s), 
          rest (r)
    {}
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

public:
    ProtocolSequence(bool inCloseable, vector<const Protocol *> p)
        : Protocol(inCloseable), steps(p)

    {}

    // FIXME: DO BETTER!
    const vector<const Protocol *> getSteps() const { return steps; }

    std::string as_str(DisplayMode mode) const override;

    bool isInCloseable() const override; 

    const ProtocolSequence *getInverse() const override;

    const ProtocolSequence *getCopy() const override;

    bool isComplete() const;

    optional<const Type *> canSend(const Type *ty) const;

    optional<const Type *> send(const Type *ty) const;

    optional<RecvMetadata> recv() const;

    // bool isWN() const;

    bool contract() const;

    bool weaken() const;


    bool isOC(bool includeGuarded = false) const;

    optional<const ProtocolClose *> cancel() const; 

    optional<const ProtocolSequence *> acceptLoop() const;
    optional<const ProtocolSequence *> acceptWhileLoop() const;
    optional<const ProtocolSequence *> acceptIf() const;

    unsigned int project(const ProtocolSequence *ps) const;
    unsigned int project(std::string label) const; 
    
    optional<CaseMetadata>
    caseAnalysis(vector<variant<const ProtocolSequence *, string>> testOpts) const;


    bool isGuarded() const override;
    bool isCancelable() const override; 

    void guard() const override;
    bool unguard() const override;

    const ProtocolSequence * getCopySubst(std::map<const Type *, const Type *> & existing) const override;
protected: 
    virtual bool isSupertypeFor(const Protocol *other) const override; 

private:
    // void append(const ProtocolSequence *proto) const;

    std::optional<const Protocol *> getFirst() const;
    std::optional<const Protocol *> popFirst() const;

    // void swapFirst(const Protocol * toSwap) const;
    bool swapChoice(const ProtocolBranchOption *) const;
    void insertSteps(vector<const Protocol *> ins) const;

    std::optional<const ProtocolClose *> popFirstCancelable() const;

    optional<const ProtocolSend *> getSend() const;
    optional<const ProtocolRecv *> getRecv() const;
    optional<const ProtocolOC *> getOC(bool includeGuarded = false) const;
    optional<const ProtocolWN *> getWN() const;
    optional<const ProtocolIChoice *> getIntChoice() const;
};

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
    ProtocolRecv(bool inCloseable, const Type *v)
        : Protocol(inCloseable), recvType(v)
    {}

    std::string as_str(DisplayMode mode) const override;

    const Protocol *getInverse() const override;
    const Protocol *getCopy() const override;

    const Type* getRecvType() const { return recvType; }

    const ProtocolRecv * getCopySubst(std::map<const Type *, const Type *> & existing) const override;
protected: 
    virtual bool isSupertypeFor(const Protocol *other) const override;
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
    ProtocolSend(bool inCloseable, const Type *v)
        : Protocol(inCloseable), sendType(v)
    {}

    std::string as_str(DisplayMode mode) const override;

    const Protocol *getInverse() const override;
    const Protocol *getCopy() const override;

    const Type *getSendType() const { return sendType; }

    const ProtocolSend * getCopySubst(std::map<const Type *, const Type *> & existing) const override;
protected: 
    virtual bool isSupertypeFor(const Protocol *other) const override;
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
    ProtocolWN(bool inCloseable, const ProtocolSequence *p)
        : Protocol(inCloseable), proto(p)
    {}

    std::string as_str(DisplayMode mode) const override;

    const Protocol *getInverse() const override;
    const Protocol *getCopy() const override;

    const ProtocolSequence *getInnerProtocol() const { return proto; }

    const ProtocolWN * getCopySubst(std::map<const Type *, const Type *> & existing) const override;

protected: 
    virtual bool isSupertypeFor(const Protocol *other) const override;
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
    ProtocolOC(bool inCloseable, const ProtocolSequence *p)
        : Protocol(inCloseable), proto(p)
    {}

    std::string as_str(DisplayMode mode) const override;

    const Protocol *getInverse() const override;
    const Protocol *getCopy() const override;

    const ProtocolSequence *getInnerProtocol() const { return proto; }

    const ProtocolOC * getCopySubst(std::map<const Type *, const Type *> & existing) const override;

protected: 
    virtual bool isSupertypeFor(const Protocol *other) const override;
};


/*******************************************
 * 
 * Branch Helpers
 * 
 ********************************************/

struct ProtocolBranchOption {
    std::optional<std::string> label; 
    const ProtocolSequence * seq; 

    ProtocolBranchOption(std::string lbl, const ProtocolSequence * s) 
        : label(lbl)
        , seq(s) 
    {}

    ProtocolBranchOption(const ProtocolSequence * s)
        : label(std::nullopt)
        , seq(s) 
        {}

    
    std::string toString(DisplayMode mode) const {
        if(label) return label.value() + " : " + seq->toString(mode); 
        return seq->toString(mode); 
    }

private: 
    ProtocolBranchOption(std::optional<std::string> lbl, const ProtocolSequence * s) 
            : label(lbl)
            , seq(s) 
        {}

public: 
    const ProtocolBranchOption * getInverse() const { 
        return new ProtocolBranchOption(
            label, 
            seq->getInverse()
        );
    }

    const ProtocolBranchOption * getCopy() const { 
        return new ProtocolBranchOption(
            label, 
            seq->getCopy()
        );
    }

    const ProtocolBranchOption * getCopySubst(std::map<const Type *, const Type *> & existing) const {
        return new ProtocolBranchOption(
            label, 
            seq->getCopySubst(existing)
        );
    }
};


// FIXME: DO BETTER
struct BranchOptCompare
{
    bool operator()(const ProtocolBranchOption * a, const ProtocolBranchOption *b) const
    {
        if(a->label)
        {
            if(b->label)
                return a->label.value() < b->label.value(); 

            return true;
        }
        
        if(b->label)
            return false; 

        return a->seq->toString(DisplayMode::C_STYLE) < b->seq->toString(DisplayMode::C_STYLE);
    }
};

/*******************************************
 *
 * External Choice Protocol
 *
 *******************************************/
class ProtocolEChoice : public Protocol
{
private:
    std::set<const ProtocolBranchOption *, BranchOptCompare> opts;

public:
    ProtocolEChoice(bool inCloseable, std::set<const ProtocolBranchOption *, BranchOptCompare> o)
        : Protocol(inCloseable), opts(o)
    {}

    std::string as_str(DisplayMode mode) const override;

    const Protocol *getInverse() const override;
    const Protocol *getCopy() const override;

    std::set<const ProtocolBranchOption *, BranchOptCompare> getOptions() const { return opts; }
    std::optional<const ProtocolBranchOption *> lookup(std::variant<const ProtocolSequence *, std::string> opt) const; 

    const ProtocolEChoice * getCopySubst(std::map<const Type *, const Type *> & existing) const override;
protected: 
    virtual bool isSupertypeFor(const Protocol *other) const override;
};

/*******************************************
 *
 * Internal Choice Protocol
 *
 *******************************************/
class ProtocolIChoice : public Protocol
{
private:
    std::set<const ProtocolBranchOption *, BranchOptCompare> opts;

public:
    ProtocolIChoice(bool inCloseable, std::set<const ProtocolBranchOption *, BranchOptCompare> o)
        : Protocol(inCloseable), opts(o)
    {}

    std::string as_str(DisplayMode mode) const override;

    const ProtocolEChoice *getInverse() const override;
    const Protocol *getCopy() const override;

    std::set<const ProtocolBranchOption *, BranchOptCompare> getOptions() const { return opts; }
    const ProtocolIChoice * getCopySubst(std::map<const Type *, const Type *> & existing) const override;
protected: 
    virtual bool isSupertypeFor(const Protocol *other) const override;
};

/*******************************************
 *
 * Closeable Protocol
 *
 *******************************************/
class ProtocolClose : public Protocol
{
private:
    const ProtocolSequence *proto;
    const unsigned int closeNumber;

public:
    ProtocolClose(bool inCloseable, const ProtocolSequence *p, unsigned int num) : Protocol(inCloseable), proto(p), closeNumber(num) {}

    std::string as_str(DisplayMode mode) const override;

    const Protocol *getInverse() const override;
    const Protocol *getCopy() const override;

    const ProtocolSequence *getInnerProtocol() const { return proto; }

    unsigned int getCloseNumber() const { return closeNumber; }

    bool isGuarded() const override;
    bool isCancelable() const override; 

    void guard() const override;
    bool unguard() const override;

    const ProtocolClose * getCopySubst(std::map<const Type *, const Type *> & existing) const override;

protected: 
    virtual bool isSupertypeFor(const Protocol *other) const override;
};