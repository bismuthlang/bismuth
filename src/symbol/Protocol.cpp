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
std::string ProtocolOC::as_str() const
{
    std::ostringstream description;
    description << "!(" << proto->toString() << ")";

    return description.str();
}
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

optional<const Type *> ProtocolSequence::canSend(const Type *ty) const
{
    if (isComplete())
        return std::nullopt;

    if(steps.front()->isGuarded() || this->isGuarded())// FIXME: VERIFY WORKS W CLOSE PROTOS!
        return std::nullopt;

    optional<const Protocol *> protoOpt = this->getFirst(); 
    if(!protoOpt)
        return std::nullopt; 


    if (const ProtocolSend *send = dynamic_cast<const ProtocolSend *>(protoOpt.value()))
    {
        if (ty->isSubtype(send->getSendType()))
            return send->getSendType();
        return std::nullopt;
    }

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

bool ProtocolSequence::canRecv() const
{
    if (isComplete())
        return false;

    if (steps.front()->isGuarded() || this->isGuarded())
        return false;

    optional<const Protocol*> protoOpt = this->getFirst();

    if(!protoOpt)
        return false; 

    if (const ProtocolRecv *recv = dynamic_cast<const ProtocolRecv *>(protoOpt.value()))
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

    this->popFirst();

    return recv->getRecvType();
}

bool ProtocolSequence::isWN() const
{
    if (isComplete())
        return false;

    optional<const Protocol *> protoOpt = this->getFirst(); 
    if(!protoOpt)
        return false; 
    
    const Protocol *proto = protoOpt.value();
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

    optional<const Protocol *> proto = this->getFirst(); // TODO: Handle more efficiently
    if(!proto) return false; // Lots of these checks are basically redundant

    const ProtocolWN *wn = dynamic_cast<const ProtocolWN *>(proto.value());

    this->insertSteps(wn->getInnerProtocol()->steps);
    return true; 
}

bool ProtocolSequence::weaken() const
{
    if (!isWN())
        return false;

    if (steps.front()->isGuarded() || this->isGuarded())
        return false;

    return this->popFirst().has_value(); // should always be true 
}

bool ProtocolSequence::isOC(bool includeGuarded) const
{
    if (isComplete())
        return false;
    // const Protocol *proto = steps.front();

    if (!includeGuarded &&
        (steps.front()->isGuarded() || this->isGuarded())) //TODO: WHY DOESN'T ISWN HAVE THIS?
        return false;

    optional<const Protocol *> protoOpt = this->getFirst(); 
    if(!protoOpt)
        return false; 
    
    const Protocol *proto = protoOpt.value();
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
    // FIXME: UPDATE
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

    optional<const Protocol *> protoOpt = this->getFirst();
    if(!protoOpt) return std::nullopt; //Should never happen due to isOC check

    const ProtocolOC *oc = dynamic_cast<const ProtocolOC *>(protoOpt.value());
    const ProtocolSequence *ans = toSequence(oc->getInnerProtocol()->getCopy());

    insertSteps(ans->steps);

    return this;
}

// FIXME: METHODIZE A LOT OF THESE
bool ProtocolSequence::isIntChoice() const
{
    if (isComplete())
        return false;

    if (steps.front()->isGuarded() || this->isGuarded())
        return false;

    optional<const Protocol*> protoOpt = this->getFirst(); 

    if(!protoOpt)
        return false; 

    if (const ProtocolIChoice *wn = dynamic_cast<const ProtocolIChoice *>(protoOpt.value()))
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
    optional<const Protocol *>protoOpt = this->getFirst(); // Is it safe to pop here vs in the check for proto equality?
    if(!protoOpt) return 0; 

    const ProtocolIChoice *ic = dynamic_cast<const ProtocolIChoice *>(protoOpt.value());

    for (const ProtocolSequence *p : ic->getOptions())
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

optional<const Protocol *> ProtocolSequence::getFirst() const
{
    if (isComplete())
        return std::nullopt;

    const Protocol * protoTemp = steps.front();
    const Protocol ** protoPtr = &protoTemp; 

    while(const ProtocolClose *protoClose = dynamic_cast<const ProtocolClose *>(*protoPtr))
    {
        const ProtocolSequence * seq = protoClose->getInnerProtocol();

        if(seq->isComplete())
            return protoClose; 
        
        const Protocol * tmp = seq->steps.front();
        protoPtr = &tmp; 
    }

    return *protoPtr;
}

optional<const Protocol *> ProtocolSequence::popFirst() const
{
    if (isComplete())
        return std::nullopt;

    const ProtocolSequence * tempSeq = this; 
    const ProtocolSequence ** seqPtr = & tempSeq; 

    while(const ProtocolClose *protoClose = dynamic_cast<const ProtocolClose *>((*seqPtr)->steps.front()))
    {
        const ProtocolSequence * seq = protoClose->getInnerProtocol();

        if(seq->isComplete())
            break;
        
        seqPtr = &seq; 
    }

    const Protocol * ans = (*seqPtr)->steps.front(); 
    ProtocolSequence * m_seq = const_cast<ProtocolSequence *>(*seqPtr); 
    m_seq->steps.erase(m_seq->steps.begin());

    return ans;
}

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

    while(const ProtocolClose *protoClose = dynamic_cast<const ProtocolClose *>((*seqPtr)->steps.front()))
    {
        const ProtocolSequence * seq = protoClose->getInnerProtocol();

        if(seq->isComplete())
            break;
        
        seqPtr = &seq; 
    }


    ProtocolSequence * m_seq = const_cast<ProtocolSequence *>(*seqPtr); 
    m_seq->steps.insert(m_seq->steps.begin(), ins.begin(), ins.end());
    return;// true;
}

/*********************************************
 *
 *  ProtocolClose
 * 
 * *******************************************/
std::string ProtocolClose::as_str() const
{
    // TODO: CHANGE SYMBOLS?
    std::ostringstream description;
    description << "Closeable<" << proto->toString() << ">";

    return description.str();
}
const Protocol *ProtocolClose::getInverse() const
{
    return new ProtocolClose(toSequence(this->proto->getInverse()), this->getCloseNumber());
}

const Protocol *ProtocolClose::getCopy() const
{
    auto ans = new ProtocolClose(toSequence(this->proto->getCopy()), this->getCloseNumber()); 
    ans->guardCount = this->guardCount;
    return ans;
}