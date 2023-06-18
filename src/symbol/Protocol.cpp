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
    auto ans = new ProtocolRecv(this->recvType->getCopy()); 
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
    auto ans = new ProtocolSend(this->sendType->getCopy());; 
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

optional<const Type *> ProtocolSequence::canSend(const Type *ty) const
{
    if (isComplete())
        return std::nullopt;
    // return false;

    const Protocol *proto = steps.front();

    if (proto->isGuarded() || this->isGuarded())
        return std::nullopt;

    if (const ProtocolSend *send = dynamic_cast<const ProtocolSend *>(proto))
    {
        if (ty->isSubtype(send->getSendType()))
            return send->getSendType();
        return std::nullopt;
    }

    // return false;
    return std::nullopt;
}

optional<const Type *> ProtocolSequence::send(const Type *ty) const
{
    // FIXME: BETTER ERROR HANDLING
    optional<const Type *> ans = canSend(ty);
    if (!ans)
        return std::nullopt;

    ProtocolSequence *u_this = const_cast<ProtocolSequence *>(this);
    u_this->steps.erase(steps.begin());

    return ans;
}

bool ProtocolSequence::canRecv() const
{
    if (isComplete())
        return false;

    const Protocol *proto = steps.front();

    if (proto->isGuarded() || this->isGuarded())
        return false;

    if (const ProtocolRecv *recv = dynamic_cast<const ProtocolRecv *>(proto))
    {
        return true; // ty->isSubtype(recv->getRecvType());
    }

    return false;
}

optional<const Type *> ProtocolSequence::recv() const
{
    // FIXME: BETTER ERROR HANDLING
    if (!canRecv())
        return std::nullopt;

    const Protocol *proto = steps.front();
    const ProtocolRecv *recv = dynamic_cast<const ProtocolRecv *>(proto);

    ProtocolSequence *u_this = const_cast<ProtocolSequence *>(this);
    u_this->steps.erase(steps.begin());
    return recv->getRecvType();
}

bool ProtocolSequence::isWN() const
{
    if (isComplete())
        return false;
    const Protocol *proto = steps.front();
    if (const ProtocolWN *wn = dynamic_cast<const ProtocolWN *>(proto))
    {
        return true;
    }

    return false;
}

bool ProtocolSequence::contract() const
{
    if (!isWN())
        return false;

    const Protocol *proto = steps.front(); // TODO: Handle more efficiently
    const ProtocolWN *wn = dynamic_cast<const ProtocolWN *>(proto);

    ProtocolSequence *u_this = const_cast<ProtocolSequence *>(this);
    vector<const Protocol *> other = wn->getInnerProtocol()->steps;

    u_this->steps.insert(steps.begin(), other.begin(), other.end());
    return true;
}

bool ProtocolSequence::weaken() const
{
    if (!isWN())
        return false;

    if (steps.front()->isGuarded() || this->isGuarded())
        return false;

    ProtocolSequence *u_this = const_cast<ProtocolSequence *>(this);
    u_this->steps.erase(steps.begin());
    return true;
}

bool ProtocolSequence::isOC(bool includeGuarded) const
{
    if (isComplete())
        return false;
    const Protocol *proto = steps.front();

    if (!includeGuarded &&
        (steps.front()->isGuarded() || this->isGuarded()))
        return false;

    if (const ProtocolOC *wn = dynamic_cast<const ProtocolOC *>(proto))
    {
        return true;
    }

    return false;
}

optional<const ProtocolSequence *> ProtocolSequence::acceptLoop() const
{
    if (!isOC())
        return std::nullopt;

    const Protocol *proto = steps.front();
    const ProtocolOC *wn = dynamic_cast<const ProtocolOC *>(proto);
    const ProtocolSequence *ans = toSequence(wn->getInnerProtocol()->getCopy());

    ProtocolSequence *u_this = const_cast<ProtocolSequence *>(this);
    u_this->steps.erase(steps.begin());

    return ans;
}

optional<const ProtocolSequence *> ProtocolSequence::acceptWhileLoop() const
{
    if (!isOC(true))
        return std::nullopt;

    const Protocol *proto = steps.front();
    const ProtocolOC *wn = dynamic_cast<const ProtocolOC *>(proto);
    return toSequence(wn->getInnerProtocol()->getCopy());
}

optional<const ProtocolSequence *> ProtocolSequence::acceptIf() const
{
    if (!isOC(true))
        return std::nullopt;

    const Protocol *proto = steps.front();
    const ProtocolOC *oc = dynamic_cast<const ProtocolOC *>(proto);
    const ProtocolSequence *ans = toSequence(oc->getInnerProtocol()->getCopy());

    ProtocolSequence *u_this = const_cast<ProtocolSequence *>(ans);
    u_this->steps.insert(ans->steps.end(), this->steps.begin(), this->steps.end());

    return ans;
}

// FIXME: METHODIZE A LOT OF THESE
bool ProtocolSequence::isIntChoice() const
{
    if (isComplete())
        return false;
    const Protocol *proto = steps.front();

    if (steps.front()->isGuarded() || this->isGuarded())
        return false;

    if (const ProtocolIChoice *wn = dynamic_cast<const ProtocolIChoice *>(proto))
    {
        return true;
    }

    return false;
}

unsigned int ProtocolSequence::project(const ProtocolSequence *ps) const
{
    if (!isIntChoice())
        return 0;

    unsigned int ans = 1;
    const Protocol *proto = steps.front();
    const ProtocolIChoice *ic = dynamic_cast<const ProtocolIChoice *>(proto);

    for (const ProtocolSequence *p : ic->getOptions())
    {
        if (ps->toString() == p->toString()) // FIXME: DO BETTER
        {
            ProtocolSequence *u_this = const_cast<ProtocolSequence *>(this);
            u_this->steps.erase(steps.begin());
            vector<const Protocol *> other = p->steps;
            u_this->steps.insert(steps.begin(), other.begin(), other.end());

            return ans;
        }
        ans++;
    }

    return 0;
}

bool ProtocolSequence::isExtChoice(set<const ProtocolSequence *, ProtocolCompare> testOpts) const
{
    if (isComplete())
        return false;

    const Protocol *proto = steps.front();

    if (steps.front()->isGuarded() || this->isGuarded())
        return false;

    if (const ProtocolEChoice *eChoice = dynamic_cast<const ProtocolEChoice *>(proto))
    {
        std::set<const ProtocolSequence *, ProtocolCompare> foundCaseTypes = {};

        for (const ProtocolSequence *p : testOpts) // TODO: METHODIZE WITH MATCHSTATEMENT
        {
            if (!eChoice->getOptions().count(p))
            {
                // errorHandler.addSemanticError(ctx->getStart(), "Impossible case: " p->toString());
                return false;
            }

            if (foundCaseTypes.count(p))
            {
                // errorHandler.addSemanticError(ctx->getStart(), "Duplicate case: " + p->toString());
                return false; // FIXME: HANDLE ERRORS BETTER IN THE SEMANTIC VISITOR SO WE CAN GET THESE ERRORS!!
            }
            else
            {
                foundCaseTypes.insert(p);
            }
        }

        if (foundCaseTypes.size() != eChoice->getOptions().size())
        {
            return false;
            // errorHandler.addSemanticError(ctx->getStart(), "Match statement did not cover all cases needed for " + sumType->toString());
        }

        ProtocolSequence *u_this = const_cast<ProtocolSequence *>(this);
        u_this->steps.erase(steps.begin());

        return true;
    }

    return false;
}