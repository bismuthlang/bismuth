#include "Protocol.h"

/*********************************************
 *
 *  ProtocolRecv
 * 
 * ********************************************/
const Protocol *ProtocolRecv::getInverse() const //FIXME: ADD GUARD?
{
    return new ProtocolSend(this->recvType);
}

const Protocol *ProtocolRecv::getCopy() const
{
    auto ans = new ProtocolRecv(copyType(this->recvType)); 
    ans->guardCount = this->guardCount;
    return ans;
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
    auto ans = new ProtocolSend(copyType(this->sendType));; 
    ans->guardCount = this->guardCount;
    return ans;
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
    auto ans = new ProtocolWN(toSequence(this->proto->getCopy())); 
    ans->guardCount = this->guardCount;
    return ans;
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
    auto ans = new ProtocolOC(toSequence(this->proto->getCopy())); 
    ans->guardCount = this->guardCount;
    return ans;
}


/*********************************************
 *
 *  ProtocolSequence
 * 
 * ********************************************/
const ProtocolSequence *ProtocolSequence::getInverse() const
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

    auto ans = new ProtocolSequence(invs); 
    ans->guardCount = this->guardCount;
    return ans;
}



/*********************************************
 *
 *  ProtocolIChoice
 * 
 * ********************************************/

const ProtocolEChoice *ProtocolIChoice::getInverse() const
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

    auto ans = new ProtocolIChoice(opts); 
    ans->guardCount = this->guardCount;
    return ans;
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

    auto ans = new ProtocolEChoice(opts); 
    ans->guardCount = this->guardCount;
    return ans;
}