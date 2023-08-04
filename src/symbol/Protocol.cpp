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

bool ProtocolRecv::areHigherOrderChannelsClosable() const 
{
    // FIXME: METHODIZE WITH CODE FOR SEND AS THEYRE THE SAME!!
    if(const TypeChannel * channelTy = dynamic_cast<const TypeChannel *>(this->recvType))
    {
        const std::vector<const Protocol*> steps = channelTy->getProtocol()->getSteps(); 
        if(steps.size() != 1) return false; 

        if(dynamic_cast<const ProtocolClose*>(steps.at(0)))
            return true; 
        return false; 
    }

    return true;
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

bool ProtocolSend::areHigherOrderChannelsClosable() const 
{
    // FIXME: METHODIZE WITH CODE FOR RECV AS THEYRE THE SAME!!
    if(const TypeChannel * channelTy = dynamic_cast<const TypeChannel *>(this->sendType))
    {
        const std::vector<const Protocol*> steps = channelTy->getProtocol()->getSteps(); 
        if(steps.size() != 1) return false; 

        if(dynamic_cast<const ProtocolClose*>(steps.at(0)))
            return true; 
        return false; 
    }

    return true;
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

bool ProtocolWN::areHigherOrderChannelsClosable() const 
{
    return false; // AS TECHNICALLY INVALID
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

bool ProtocolOC::areHigherOrderChannelsClosable() const { return false; }

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


bool ProtocolIChoice::areHigherOrderChannelsClosable() const 
{
    for(auto itr : opts)
        if(!itr->areHigherOrderChannelsClosable()) return false; 
    return true; 
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

bool ProtocolEChoice::areHigherOrderChannelsClosable() const 
{
    for(auto itr : opts)
        if(!itr->areHigherOrderChannelsClosable()) return false; 
    return true; 
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

    const Protocol *proto = steps.front(); // TODO: Handle more efficiently
    const ProtocolWN *wn = dynamic_cast<const ProtocolWN *>(proto);

    // FIXME: NEEDS UPDATE PER CLOSABLE?
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

    this->popFirst(); 

    return true;
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

    // FIXME: NEEDS UPDATE PER CLOSE!
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
    //FIXME: NEEDS UPDATE PER CLOSE!!
    if (isComplete())
        return false;


    if (steps.front()->isGuarded() || this->isGuarded())
        return false;

    optional<const Protocol*> protoOpt = this->getFirst();

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

        ProtocolSequence *u_this = const_cast<ProtocolSequence *>(this);
        u_this->steps.erase(steps.begin());

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
        ProtocolSequence *u_this = const_cast<ProtocolSequence *>(this);
        u_this->guardCount = u_this->guardCount + 1;
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
        ProtocolSequence *u_this = const_cast<ProtocolSequence *>(this);

        u_this->guardCount = u_this->guardCount - 1;
        return true;
    }

    return steps.front()->unguard();
}

bool ProtocolSequence::areHigherOrderChannelsClosable() const 
{
    for(const Protocol * proto : steps)
        if(!proto->areHigherOrderChannelsClosable())
            return false; 
    return true; 
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

unsigned int ProtocolSequence::numberCloseBlocks(unsigned int n) const
{
    return 0; // FIXME: IMPLEMENT!!!
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
    return new ProtocolClose(toSequence(this->proto->getInverse()));
}

const Protocol *ProtocolClose::getCopy() const
{
    auto ans = new ProtocolClose(toSequence(this->proto->getCopy())); 
    ans->guardCount = this->guardCount;
    return ans;
}

bool ProtocolClose::areHigherOrderChannelsClosable() const
{
    return proto->areHigherOrderChannelsClosable();
}