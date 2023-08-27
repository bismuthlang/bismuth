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
#include <sstream> //Used for string streams

// #include <any>      // Needed for anycasts
// #include <utility>  // Needed for anycasts
#include <vector>   // Vectors
#include <optional> // Optionals

#include <set> // Sets

// #include <climits> // Max & Min

#include "Type.h"

class Type;

class ProtocolSend;
class ProtocolRecv;
class ProtocolOC;
class ProtocolWN;
class ProtocolIChoice;

class Protocol
{
protected:
    virtual std::string as_str() const = 0;
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
    std::string toString() const
    {
        std::ostringstream description;
        for (unsigned int i = 0; i < guardCount; i++) // FIXME: ADD TO OTHERS
        {
            description << "*";
        }

        description << as_str();

        return description.str();
    }

    bool isInCloseable() const { return inCloseable; }

    virtual const Protocol *getInverse() const = 0;

    virtual const Protocol *getCopy() const = 0;

    // virtual bool isClosable() const = 0;

    // FIXME: ALMOST SAME AS TO TYPE!
    virtual bool isGuarded() const { return guardCount > 0; } // FIXME: handle these better b/c right now kind of sketchy that we only guard first part of protocol step?

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

public:
    ProtocolSequence(bool inCloseable, vector<const Protocol *> p)
        : Protocol(inCloseable), steps(p)

    {}

    // FIXME: DO BETTER!
    const vector<const Protocol *> getSteps() const { return steps; }

    std::string as_str() const override;

    const ProtocolSequence *getInverse() const override;

    const ProtocolSequence *getCopy() const override;

    bool isComplete() const;

    optional<const Type *> canSend(const Type *ty) const;

    optional<const Type *> send(const Type *ty) const;

    optional<const Type *> recv() const;

    // bool isWN() const;

    bool contract() const;

    bool weaken() const;

    bool isOC(bool includeGuarded = false) const;

    optional<const ProtocolSequence *> acceptLoop() const;
    optional<const ProtocolSequence *> acceptWhileLoop() const;
    optional<const ProtocolSequence *> acceptIf() const;

    unsigned int project(const ProtocolSequence *ps) const;

    bool isExtChoice(set<const ProtocolSequence *, ProtocolCompare> testOpts) const;

    void append(const ProtocolSequence *proto) const;

    bool isGuarded() const override;
    void guard() const override;
    bool unguard() const override;

private:
    std::optional<const Protocol *> getFirst() const;
    std::optional<const Protocol *> popFirst() const;
    void insertSteps(vector<const Protocol *> ins) const;

    optional<const ProtocolSend *> getSend() const;
    optional<const ProtocolRecv *> getRecv() const;
    optional<const ProtocolOC *> getOC(bool includeGuarded = false) const;
    optional<const ProtocolWN *> getWN() const;
    optional<const ProtocolIChoice *> getIntChoice() const;
};

inline const ProtocolSequence *toSequence(const Protocol *proto)
{
    if (const ProtocolSequence *seq = dynamic_cast<const ProtocolSequence *>(proto))
    {
        return seq;
    }

    vector<const Protocol *> a;
    a.push_back(proto);

    return new ProtocolSequence(proto->isInCloseable(), a);
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
    ProtocolRecv(bool inCloseable, const Type *v)
        : Protocol(inCloseable), recvType(v)
    {}

    std::string as_str() const override;

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
    ProtocolSend(bool inCloseable, const Type *v)
        : Protocol(inCloseable), sendType(v)
    {}

    std::string as_str() const override;

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
    ProtocolWN(bool inCloseable, const ProtocolSequence *p)
        : Protocol(inCloseable), proto(p)
    {}

    std::string as_str() const override;

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
    ProtocolOC(bool inCloseable, const ProtocolSequence *p)
        : Protocol(inCloseable), proto(p)
    {}

    std::string as_str() const override;

    const Protocol *getInverse() const override;
    const Protocol *getCopy() const override;

    const ProtocolSequence *getInnerProtocol() const { return proto; }
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
    ProtocolEChoice(bool inCloseable, std::set<const ProtocolSequence *, ProtocolCompare> o)
        : Protocol(inCloseable), opts(o)
    {}

    std::string as_str() const override;

    const Protocol *getInverse() const override;
    const Protocol *getCopy() const override;

    std::set<const ProtocolSequence *, ProtocolCompare> getOptions() const { return opts; }
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
    ProtocolIChoice(bool inCloseable, std::set<const ProtocolSequence *, ProtocolCompare> o)
        : Protocol(inCloseable), opts(o)
    {}

    std::string as_str() const override;

    const ProtocolEChoice *getInverse() const override;
    const Protocol *getCopy() const override;

    std::set<const ProtocolSequence *, ProtocolCompare> getOptions() const { return opts; }
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

    std::string as_str() const override;

    const Protocol *getInverse() const override;
    const Protocol *getCopy() const override;

    const ProtocolSequence *getInnerProtocol() const { return proto; }

    unsigned int getCloseNumber() const { return closeNumber; }
};