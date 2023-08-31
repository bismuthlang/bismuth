#include "Protocol.h"

/*********************************************
 *
 *  ProtocolRecv
 * 
 * ********************************************/

std::string ProtocolRecv::as_str() const
{
    std::ostringstream description;
    description << "+" << recvType->toString();

    return description.str();
}

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

std::string ProtocolSend::as_str() const
{
    std::ostringstream description;
    description << "-" << sendType->toString();

    return description.str();
}
    
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

std::string ProtocolWN::as_str() const
{
    std::ostringstream description;
    description << "?(" << proto->toString() << ")";

    return description.str();
}
const Protocol *ProtocolWN::getInverse() const
{
    return new ProtocolOC(this->proto->getInverse());
}

const Protocol *ProtocolWN::getCopy() const
{
    auto ans = new ProtocolWN(this->proto->getCopy());
    ans->guardCount = this->guardCount;
    return ans;
}

/*********************************************
 *
 *  ProtocolOC
 * 
 * ********************************************/
std::string ProtocolOC::as_str() const
{
    std::ostringstream description;
    description << "!(" << proto->toString() << ")";

    return description.str();
}
const Protocol *ProtocolOC::getInverse() const
{
    return new ProtocolWN(this->proto->getInverse());
}

const Protocol *ProtocolOC::getCopy() const
{
    auto ans = new ProtocolOC(this->proto->getCopy()); 
    ans->guardCount = this->guardCount;
    return ans;
}


/*********************************************
 *
 *  ProtocolIChoice
 * 
 * ********************************************/
std::string ProtocolIChoice::as_str() const
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

const ProtocolEChoice *ProtocolIChoice::getInverse() const
{
    std::set<const ProtocolSequence *, ProtocolCompare> opts;

    for (auto p : this->opts)
    {
        opts.insert(p->getInverse());
    }

    return new ProtocolEChoice(opts);
}

const Protocol *ProtocolIChoice::getCopy() const
{
    std::set<const ProtocolSequence *, ProtocolCompare> opts;

    for (auto p : this->opts)
    {
        opts.insert(p->getCopy());
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
std::string ProtocolEChoice::as_str() const
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

const Protocol *ProtocolEChoice::getInverse() const
{
    std::set<const ProtocolSequence *, ProtocolCompare> opts;

    for (auto p : this->opts)
    {
        opts.insert(p->getInverse());
    }

    return new ProtocolIChoice(opts);
}

const Protocol *ProtocolEChoice::getCopy() const
{
    std::set<const ProtocolSequence *, ProtocolCompare> opts;

    for (auto p : this->opts)
    {
        opts.insert(p->getCopy());
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
std::string ProtocolSequence::as_str() const
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

bool ProtocolSequence::isComplete() const
{
    return steps.size() == 0;
}

optional<const ProtocolSend *> ProtocolSequence::getSend() const
{
    if (isComplete())
        return std::nullopt;

    if(steps.front()->isGuarded() || this->isGuarded())
        return std::nullopt;

    optional<const Protocol *> protoOpt = this->getFirst(); 
    if(!protoOpt)
        return std::nullopt; 


    if (const ProtocolSend *send = dynamic_cast<const ProtocolSend *>(protoOpt.value()))
    {
        return send; 
    }

    return std::nullopt;
}

optional<const Type *> ProtocolSequence::canSend(const Type *ty) const
{
    optional<const ProtocolSend *> sendOpt = this->getSend(); 
    if(!sendOpt) return std::nullopt;  

    const Type * sendTy = sendOpt.value()->getSendType();
    
    if (ty->isSubtype(sendTy))
        return sendTy;


    return std::nullopt;
}

optional<const Type *> ProtocolSequence::send(const Type *ty) const
{
    // FIXME: BETTER ERROR HANDLING
    optional<const Type *> ans = canSend(ty);
    if (!ans)
        return std::nullopt;

    this->popFirst(); // TODO: HANDLE BETTER!

    return ans;
}

optional<const ProtocolRecv*> ProtocolSequence::getRecv() const
{
    if (isComplete())
        return std::nullopt;

    if (steps.front()->isGuarded() || this->isGuarded())
        return std::nullopt;

    optional<const Protocol*> protoOpt = this->getFirst();

    if(!protoOpt)
        return std::nullopt; 

    if (const ProtocolRecv *recv = dynamic_cast<const ProtocolRecv *>(protoOpt.value()))
    {
        return recv; 
    }

    return std::nullopt;
}

optional<const Type *> ProtocolSequence::recv() const
{
    // FIXME: BETTER ERROR HANDLING
    optional<const ProtocolRecv *> recvOpt = this->getRecv(); 

    if (!recvOpt) return std::nullopt;

    this->popFirst(); //TODO: ENSURE SAME AS recvOpt value?

    const ProtocolRecv * recvProto = recvOpt.value(); 

    const Type * recvType = recvProto->getRecvType();

    return recvType; 
}

bool ProtocolSequence::contract() const
{
    optional<const ProtocolWN *> proto = this->getWN();
    if(!proto) return false;

    this->insertSteps(proto.value()->getInnerProtocol()->steps);
    return true; 
}

bool ProtocolSequence::weaken() const
{
    if (!getWN())
        return false;

    if (steps.front()->isGuarded() || this->isGuarded())
        return false;

    return this->popFirst().has_value(); // should always be true 
}


optional<const ProtocolOC*> ProtocolSequence::getOC(bool includeGuarded) const
{
    if (isComplete())
        return std::nullopt;

    if (!includeGuarded &&
        (steps.front()->isGuarded() || this->isGuarded()))
        return std::nullopt; 

    optional<const Protocol *> protoOpt = this->getFirst(); 
    if(!protoOpt)
        return std::nullopt; 
    
    if (const ProtocolOC *oc = dynamic_cast<const ProtocolOC *>(protoOpt.value()))
    {
        return oc;
    }

    return std::nullopt;
}

optional<const ProtocolWN*> ProtocolSequence::getWN() const
{
    if (isComplete())
        return std::nullopt;

    optional<const Protocol *> protoOpt = this->getFirst(); 
    if(!protoOpt)
        return std::nullopt; 
    
    if (const ProtocolWN *wn = dynamic_cast<const ProtocolWN *>(protoOpt.value()))
    {
        return wn;
    }

    return std::nullopt;
}

// bool ProtocolSequence::isWN() const
// {
//     return getWN().has_value();
// }

bool ProtocolSequence::isOC(bool includeGuarded) const
{
    return getOC(includeGuarded).has_value(); 
}

optional<const ProtocolSequence *> ProtocolSequence::acceptLoop() const
{
    optional<const ProtocolOC *>oc = this->getOC(); 
    if(!oc) return std::nullopt; 

    const ProtocolSequence *ans = oc.value()->getInnerProtocol()->getCopy();
    this->popFirst(); 

    return ans;
}

// Odd how this one isn't really a modifier to the proto... huh...
optional<const ProtocolSequence *> ProtocolSequence::acceptWhileLoop() const
{
    optional<const ProtocolOC *> oc = this->getOC(true);
    if(!oc) return std::nullopt; 

    return oc.value()->getInnerProtocol()->getCopy();
}

optional<const ProtocolSequence *> ProtocolSequence::acceptIf() const
{
    optional<const ProtocolOC *> oc = this->getOC(true); 
    if(!oc) return std::nullopt; 

    const ProtocolSequence *ans = oc.value()->getInnerProtocol()->getCopy();

    insertSteps(ans->steps);

    return this;
}

// FIXME: METHODIZE A LOT OF THESE
optional<const ProtocolIChoice*> ProtocolSequence::getIntChoice() const
{
    if (isComplete())
        return std::nullopt;

    if (steps.front()->isGuarded() || this->isGuarded())
        return std::nullopt;

    optional<const Protocol*> protoOpt = this->getFirst(); 

    if(!protoOpt)
        return std::nullopt; 

    if (const ProtocolIChoice *ic = dynamic_cast<const ProtocolIChoice *>(protoOpt.value()))
    {
        return ic;
    }

    return std::nullopt;
}

unsigned int ProtocolSequence::project(const ProtocolSequence *ps) const
{
    optional<const ProtocolIChoice *> ic = this->getIntChoice();
    if(!ic) return 0; 


    unsigned int ans = 1;
    for (const ProtocolSequence *p : ic.value()->getOptions())
    {
        if (ps->toString() == p->toString()) // FIXME: DO BETTER
        {
            if(!this->popFirst().has_value()) return 0;  
            this->insertSteps(p->steps); 
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


    if (steps.front()->isGuarded() || this->isGuarded())
        return false;

    optional<const Protocol*> protoOpt = this->popFirst();

    if(!protoOpt)
        return false; 

    const Protocol* proto = protoOpt.value(); 

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

        // ProtocolSequence *u_this = const_cast<ProtocolSequence *>(this);
        // u_this->steps.erase(steps.begin());

        return true;
    }

    return false;
}

void ProtocolSequence::append(const ProtocolSequence *proto) const
{
    ProtocolSequence *u_this = const_cast<ProtocolSequence *>(this);
    vector<const Protocol *> other = proto->steps;
    u_this->steps.insert(steps.end(), other.begin(), other.end()); // Flattening should be good enough for now...
}

bool ProtocolSequence::isGuarded() const // FIXME: DO BETTER
{
    if (steps.size() == 0)
    {
        return guardCount > 0;
    }
    return steps.front()->isGuarded();
}

void ProtocolSequence::guard() const // FIXME: DO BETTER
{
    if (steps.size() == 0)
    {
        guardCount = guardCount + 1;
    }
    else
    {
        steps.front()->guard();
    }
}

bool ProtocolSequence::unguard() const // FIXME: DO BETTER
{
    if (steps.size() == 0)
    {
        if (guardCount == 0)
            return false;

        guardCount = guardCount - 1;
        return true;
    }

    return steps.front()->unguard();
}

// This code may look a bit odd, its because some changes need to be made later on for closeable protocols :)
optional<const Protocol *> ProtocolSequence::getFirst() const
{
    if (isComplete())
        return std::nullopt;

    const Protocol * protoTemp = steps.front();
    const Protocol ** protoPtr = &protoTemp; 

    return *protoPtr;
}

// This code may look a bit odd, its because some changes need to be made later on for closeable protocols :)
optional<const Protocol *> ProtocolSequence::popFirst() const
{
    if (isComplete())
        return std::nullopt;

    const ProtocolSequence * tempSeq = this; 
    const ProtocolSequence ** seqPtr = & tempSeq; 


    const Protocol * ans = (*seqPtr)->steps.front(); 
    ProtocolSequence * m_seq = const_cast<ProtocolSequence *>(*seqPtr); 
    m_seq->steps.erase(m_seq->steps.begin());

    return ans;
}

// This code may look a bit odd, its because some changes need to be made later on for closeable protocols :)
void ProtocolSequence::insertSteps(vector<const Protocol *> ins) const 
{
    if (isComplete())
    {
        ProtocolSequence * m_seq = const_cast<ProtocolSequence *>(this); 
        m_seq->steps.insert(m_seq->steps.begin(), ins.begin(), ins.end());
        return;// true;
    }
    //     return false; 

    const ProtocolSequence * tempSeq = this; 
    const ProtocolSequence ** seqPtr = & tempSeq; 


    ProtocolSequence * m_seq = const_cast<ProtocolSequence *>(*seqPtr); 
    m_seq->steps.insert(m_seq->steps.begin(), ins.begin(), ins.end());
    return;// true;
}