#include "Symbol.h"

//FIXME: WHY ARE THERES HERE AND NOT IN TYPE.h?????

/*********************************************
 *
 *  ProtocolRecv
 * 
 * ********************************************/
const Protocol *ProtocolRecv::getInverse() const
{
    return new ProtocolSend(this->recvType);
}

const Protocol *ProtocolRecv::getCopy() const
{
    return new ProtocolRecv(this->recvType);
}


/*********************************************
 *
 *  ProtocolSend
 * 
 * ********************************************/
const Protocol *ProtocolSend::getInverse() const
{
    return new ProtocolRecv(this->sendType);
}

const Protocol *ProtocolSend::getCopy() const
{
    return new ProtocolSend(this->sendType);
}


/*********************************************
 *
 *  ProtocolWN
 * 
 * ********************************************/
const Protocol *ProtocolWN::getInverse() const
{
    return new ProtocolOC(toSequence(this->proto->getInverse()));
}

const Protocol *ProtocolWN::getCopy() const
{
    return new ProtocolWN(toSequence(this->proto->getCopy()));
}


/*********************************************
 *
 *  ProtocolOC
 * 
 * ********************************************/
const Protocol *ProtocolOC::getInverse() const
{
    return new ProtocolWN(toSequence(this->proto->getInverse()));
}

const Protocol *ProtocolOC::getCopy() const
{
    return new ProtocolOC(toSequence(this->proto->getCopy()));
}


/*********************************************
 *
 *  ProtocolSequence
 * 
 * ********************************************/
const Protocol *ProtocolSequence::getInverse() const
{
    vector<const Protocol *> invs;

    for (auto p : this->steps)
    {
        invs.push_back(p->getInverse());
    }

    return new ProtocolSequence(invs);
}

const ProtocolSequence *ProtocolSequence::getCopy() const
{
    vector<const Protocol *> invs;

    for (auto p : this->steps)
    {
        invs.push_back(p->getCopy());
    }

    return new ProtocolSequence(invs);
}



/*********************************************
 *
 *  ProtocolIChoice
 * 
 * ********************************************/

const Protocol *ProtocolIChoice::getInverse() const
{
    std::set<const ProtocolSequence *, ProtocolCompare> opts;

    for (auto p : this->opts)
    {
        opts.insert(toSequence(p->getInverse()));
    }

    return new ProtocolEChoice(opts);
}

const Protocol *ProtocolIChoice::getCopy() const
{
    std::set<const ProtocolSequence *, ProtocolCompare> opts;

    for (auto p : this->opts)
    {
        opts.insert(toSequence(p->getCopy()));
    }

    return new ProtocolIChoice(opts);
}


/*********************************************
 *
 *  ProtocolEChoice
 * 
 * ********************************************/

const Protocol *ProtocolEChoice::getInverse() const
{
    std::set<const ProtocolSequence *, ProtocolCompare> opts;

    for (auto p : this->opts)
    {
        opts.insert(toSequence(p->getInverse()));
    }

    return new ProtocolIChoice(opts);
}

const Protocol *ProtocolEChoice::getCopy() const
{
    std::set<const ProtocolSequence *, ProtocolCompare> opts;

    for (auto p : this->opts)
    {
        opts.insert(toSequence(p->getCopy()));
    }

    return new ProtocolEChoice(opts);
}