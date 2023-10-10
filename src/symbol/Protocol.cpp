#include "Protocol.h"

/*********************************************
 *
 *  ProtocolRecv
 *
 * ********************************************/

// const TypeSum *NullOptional::asSum()
// {
//     return new TypeSum({innerType, Types::UNIT});
// }

std::string ProtocolRecv::as_str() const
{
    std::ostringstream description;
    description << "+" << recvType->toString();

    return description.str();
}

const Protocol *ProtocolRecv::getInverse() const // FIXME: ADD GUARD?
{
    return new ProtocolSend(this->inCloseable, this->recvType);
}

const Protocol *ProtocolRecv::getCopy() const
{
    auto ans = new ProtocolRecv(this->inCloseable, this->recvType->getCopy());
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
    return new ProtocolRecv(this->inCloseable, this->sendType);
}

const Protocol *ProtocolSend::getCopy() const
{
    auto ans = new ProtocolSend(this->inCloseable, this->sendType->getCopy());
    ;
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
    return new ProtocolOC(this->inCloseable, this->proto->getInverse());
}

const Protocol *ProtocolWN::getCopy() const
{
    auto ans = new ProtocolWN(this->inCloseable, this->proto->getCopy());
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
    return new ProtocolWN(this->inCloseable, this->proto->getInverse());
}

const Protocol *ProtocolOC::getCopy() const
{
    auto ans = new ProtocolOC(this->inCloseable, this->proto->getCopy());
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

    return new ProtocolEChoice(this->inCloseable, opts);
}

const Protocol *ProtocolIChoice::getCopy() const
{
    std::set<const ProtocolSequence *, ProtocolCompare> opts;

    for (auto p : this->opts)
    {
        opts.insert(p->getCopy());
    }

    auto ans = new ProtocolIChoice(this->inCloseable, opts);
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

    return new ProtocolIChoice(this->inCloseable, opts);
}

const Protocol *ProtocolEChoice::getCopy() const
{
    std::set<const ProtocolSequence *, ProtocolCompare> opts;

    for (auto p : this->opts)
    {
        opts.insert(p->getCopy());
    }

    auto ans = new ProtocolEChoice(this->inCloseable, opts);
    ans->guardCount = this->guardCount;
    return ans;
}

/*********************************************
 *
 *  ProtocolSequence
 *
 * ********************************************/

RecvMetadata::RecvMetadata(const Type* inner, bool isSum)
{
    protocolType = inner; 
    actingType = isSum ? (optional<const TypeSum*>) new TypeSum({protocolType, Types::UNIT}) : std::nullopt; 
}

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

    return new ProtocolSequence(this->inCloseable, invs);
}

const ProtocolSequence *ProtocolSequence::getCopy() const
{
    vector<const Protocol *> invs;

    for (auto p : this->steps)
    {
        invs.push_back(p->getCopy());
    }

    auto ans = new ProtocolSequence(this->inCloseable, invs);
    ans->guardCount = this->guardCount;
    return ans;
}

bool ProtocolSequence::isComplete() const
{
    return steps.size() == 0;
}

bool ProtocolSequence::isInCloseable() const
{
    optional<const Protocol *> protoOpt = this->getFirst();
    if (!protoOpt)
        return this->inCloseable;
    return protoOpt.value()->isInCloseable();
}

optional<const ProtocolSend *> ProtocolSequence::getSend() const
{
    if (isComplete())
        return std::nullopt;

    if (steps.front()->isGuarded() || this->isGuarded()) // FIXME: VERIFY WORKS W CLOSE PROTOS!
        return std::nullopt;

    optional<const Protocol *> protoOpt = this->getFirst();
    if (!protoOpt)
        return std::nullopt;

    if (const ProtocolSend *send = dynamic_cast<const ProtocolSend *>(protoOpt.value()))
    {
        return send;
    }

    return std::nullopt;
}

// FIXME: this will get complicated if we have (Unit + Closable) -- how will we know what to close?
optional<const Type *> ProtocolSequence::canSend(const Type *ty) const
{
    optional<const ProtocolSend *> sendOpt = this->getSend();
    if (!sendOpt)
        return std::nullopt;

    const Type *sendTy = sendOpt.value()->getSendType();

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

optional<const ProtocolRecv *> ProtocolSequence::getRecv() const
{
    if (isComplete())
        return std::nullopt;

    if (steps.front()->isGuarded() || this->isGuarded())
        return std::nullopt;

    optional<const Protocol *> protoOpt = this->getFirst();

    if (!protoOpt)
        return std::nullopt;

    if (const ProtocolRecv *recv = dynamic_cast<const ProtocolRecv *>(protoOpt.value()))
    {
        return recv;
    }

    return std::nullopt;
}

optional<RecvMetadata> ProtocolSequence::recv() const
{
    // FIXME: BETTER ERROR HANDLING
    optional<const ProtocolRecv *> recvOpt = this->getRecv();

    if (!recvOpt)
        return std::nullopt;

    this->popFirst(); // TODO: ENSURE SAME AS recvOpt value?

    const ProtocolRecv *recvProto = recvOpt.value();

    const Type *recvType = recvProto->getRecvType();
    
    return RecvMetadata(recvType, recvProto->isInCloseable());  // FIXME: must be linear-ish SUM!!!
}

bool ProtocolSequence::contract() const
{
    optional<const ProtocolWN *> proto = this->getWN();
    if (!proto)
        return false;

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

optional<const ProtocolClose *> ProtocolSequence::cancel() const
{
    if (steps.front()->isGuarded() || this->isGuarded())
        return std::nullopt;

    return this->popFirstCancelable(); // should always be true?
}

optional<const ProtocolOC *> ProtocolSequence::getOC(bool includeGuarded) const
{
    if (isComplete())
        return std::nullopt;

    if (!includeGuarded &&
        (steps.front()->isGuarded() || this->isGuarded()))
        return std::nullopt;

    optional<const Protocol *> protoOpt = this->getFirst();
    if (!protoOpt)
        return std::nullopt;

    if (const ProtocolOC *oc = dynamic_cast<const ProtocolOC *>(protoOpt.value()))
    {
        return oc;
    }

    return std::nullopt;
}

optional<const ProtocolWN *> ProtocolSequence::getWN() const
{
    if (isComplete())
        return std::nullopt;

    optional<const Protocol *> protoOpt = this->getFirst();
    if (!protoOpt)
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
    optional<const ProtocolOC *> oc = this->getOC();
    if (!oc)
        return std::nullopt;

    const ProtocolSequence *ans = oc.value()->getInnerProtocol()->getCopy();
    this->popFirst();

    return ans;
}

// Odd how this one isn't really a modifier to the proto... huh...
optional<const ProtocolSequence *> ProtocolSequence::acceptWhileLoop() const
{
    optional<const ProtocolOC *> oc = this->getOC(true);
    if (!oc)
        return std::nullopt;

    return oc.value()->getInnerProtocol()->getCopy();
}

optional<const ProtocolSequence *> ProtocolSequence::acceptIf() const
{
    optional<const ProtocolOC *> oc = this->getOC(true);
    if (!oc)
        return std::nullopt;

    const ProtocolSequence *ans = oc.value()->getInnerProtocol()->getCopy();

    insertSteps(ans->steps);

    return this;
}

// FIXME: METHODIZE A LOT OF THESE
optional<const ProtocolIChoice *> ProtocolSequence::getIntChoice() const
{
    if (isComplete())
        return std::nullopt;

    if (steps.front()->isGuarded() || this->isGuarded())
        return std::nullopt;

    optional<const Protocol *> protoOpt = this->getFirst();

    if (!protoOpt)
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
    if (!ic)
        return 0;

    unsigned int ans = 1;
    for (const ProtocolSequence *p : ic.value()->getOptions())
    {
        if (ps->toString() == p->toString()) // FIXME: DO BETTER
        {
            if (!this->swapChoice(ps))
                return 0;
            return ans;
        }
        ans++;
    }

    return 0;
}

// optional<vector<const ProtocolSequence *>> 
optional<CaseMetadata> 
ProtocolSequence::caseAnalysis(vector<const ProtocolSequence *> testOpts) const // Note: using vector as otherwise duplicate cases could be too easily ignored by type checking (ie, semantic visitor dumps cases into set and thus isn't aware of duplicates) //set<const ProtocolSequence *, ProtocolCompare> testOpts) const
{
    if (isComplete())
        return std::nullopt;

    if (steps.front()->isGuarded() || this->isGuarded())
        return std::nullopt;

    optional<const Protocol *> protoOpt = this->getFirst();

    if (!protoOpt)
        return std::nullopt;

    const Protocol *proto = protoOpt.value();

    if (const ProtocolEChoice *eChoice = dynamic_cast<const ProtocolEChoice *>(proto))
    {
        std::set<const ProtocolSequence *, ProtocolCompare> foundCaseTypes = {};
        std::vector<const ProtocolSequence *> ans = {}; 

        for (const ProtocolSequence *p : testOpts) // TODO: METHODIZE WITH MATCHSTATEMENT
        {
            const ProtocolSequence * res = this->getCopy(); 
            
            if(!res->swapChoice(p)) // if (!eChoice->getOptions().count(p))
            {
                // errorHandler.addSemanticError(ctx->getStart(), "Impossible case: " p->toString());
                return std::nullopt;
            }
            else 
            {
                ans.push_back(res); 
            }

            if (foundCaseTypes.count(p)) // Is this even possible? its a set after all. Would require messy subtyping
            {
                // errorHandler.addSemanticError(ctx->getStart(), "Duplicate case: " + p->toString());
                return std::nullopt; // FIXME: HANDLE ERRORS BETTER IN THE SEMANTIC VISITOR SO WE CAN GET THESE ERRORS!!
            }
            else
            {
                foundCaseTypes.insert(p);
            }
        }

        if (foundCaseTypes.size() != eChoice->getOptions().size())
        {
            return std::nullopt;
            // errorHandler.addSemanticError(ctx->getStart(), "Match statement did not cover all cases needed for " + sumType->toString());
        }

        this->popFirst(); // Remove the choice
        return CaseMetadata(ans, this); // Should be safe due to passing get first
    }

    return std::nullopt;
}

// void ProtocolSequence::append(const ProtocolSequence *proto) const
// {
    // ProtocolSequence *u_this = const_cast<ProtocolSequence *>(this);
    // vector<const Protocol *> other = proto->steps;
    // u_this->steps.
    // u_this->steps.insert(steps.end(), other.begin(), other.end()); // Flattening should be good enough for now...
// }

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

    Protocol *proto = const_cast<Protocol *>(steps.front());

    while (const ProtocolClose *protoClose = dynamic_cast<const ProtocolClose *>(proto))
    {
        const ProtocolSequence *innerSeq = protoClose->getInnerProtocol();

        if (innerSeq->isComplete())
            return protoClose;

        proto = const_cast<Protocol *>(innerSeq->steps.front());
    }

    return proto;
}

// TODO : I worry some of these inserts where we do protocol sequence -> vector of steps
// may now erase critical information (at times) about things like closeable blocks.
// This specific instance should be fine, but we should probably move away from returning protocol
// sequences when its just a vector of steps. 
//
// FIXME: There are also likely issues should we have closeable blocks in choice branches 
// as we won't correctly track the close block #!
bool ProtocolSequence::swapChoice(const ProtocolSequence * swap) const
{
    if (isComplete())
        return false;

    // const Protocol *protoTemp = steps.front();
    const ProtocolSequence * tempPtr = this; 
    const ProtocolSequence ** protoSeqPtr = &tempPtr; 
    // const Protocol **protoPtr = &protoTemp;

    while (const ProtocolClose *protoClose = dynamic_cast<const ProtocolClose *>((*protoSeqPtr)->steps.front()))//(*protoPtr))
    {
        const ProtocolSequence *seq = protoClose->getInnerProtocol();

        if (seq->isComplete())
            break; 
            // return protoClose;
            

        // const Protocol *tmp = seq->steps.front();
        // protoPtr = &tmp;
        protoSeqPtr = &seq; 
    }

    const ProtocolSequence * correctedPtr = *protoSeqPtr; 

    if(const ProtocolEChoice * extChoice = dynamic_cast<const ProtocolEChoice *>(correctedPtr->steps.front()))
    {
        if(!extChoice->getOptions().count(swap))
            return false; 
    }
    else if(const ProtocolIChoice * intChoice = dynamic_cast<const ProtocolIChoice *>(correctedPtr->steps.front()))
    {
        if(!intChoice->getOptions().count(swap))
            return false; 
    }
    else 
    {
        return false; 
    }

    ProtocolSequence *m_seq = const_cast<ProtocolSequence *>(correctedPtr);
    m_seq->steps.erase(m_seq->steps.begin());
    m_seq->steps.insert(m_seq->steps.begin(), swap->steps.begin(), swap->steps.end()); 


    return true;
}

// void ProtocolSequence::swapFirst(const Protocol * toSwap) const
// {
//     if (isComplete())
//     {
//         ProtocolSequence *u_this = const_cast<ProtocolSequence *>(this);
//         u_this->steps.insert(u_this->steps.begin(), toSwap); // FIXME: THIS BREAKS EVERYTHING!
//         return;
//     }

//     const Protocol *protoTemp = steps.front();
//     const Protocol **protoPtr = &protoTemp;

//     while (const ProtocolClose *protoClose = dynamic_cast<const ProtocolClose *>(*protoPtr))
//     {
//         const ProtocolSequence *seq = protoClose->getInnerProtocol();

//         const Protocol *tmp = seq->steps.front();
//         protoPtr = &tmp;

//         if (seq->isComplete())
//             break; 

//     }

//     if((*protoPtr)->isComplete())
//     {

//     }

//     // return *protoPtr;
// }


// bool ProtocolSequence::selectExtChoice(set<const ProtocolSequence *, ProtocolCompare> testOpts) const
// {
//     if (isComplete())
//         return false;

//     if (steps.front()->isGuarded() || this->isGuarded())
//         return false;

//     optional<const Protocol *> protoOpt = this->popFirst();

//     if (!protoOpt)
//         return false;

//     const Protocol *proto = protoOpt.value();

//     if (const ProtocolEChoice *eChoice = dynamic_cast<const ProtocolEChoice *>(proto))
//     {
//         std::set<const ProtocolSequence *, ProtocolCompare> foundCaseTypes = {};

//         for (const ProtocolSequence *p : testOpts) // TODO: METHODIZE WITH MATCHSTATEMENT
//         {
//             if (!eChoice->getOptions().count(p))
//             {
//                 // errorHandler.addSemanticError(ctx->getStart(), "Impossible case: " p->toString());
//                 return false;
//             }

//             if (foundCaseTypes.count(p))
//             {
//                 // errorHandler.addSemanticError(ctx->getStart(), "Duplicate case: " + p->toString());
//                 return false; // FIXME: HANDLE ERRORS BETTER IN THE SEMANTIC VISITOR SO WE CAN GET THESE ERRORS!!
//             }
//             else
//             {
//                 foundCaseTypes.insert(p);
//             }
//         }

//         if (foundCaseTypes.size() != eChoice->getOptions().size())
//         {
//             return false;
//             // errorHandler.addSemanticError(ctx->getStart(), "Match statement did not cover all cases needed for " + sumType->toString());
//         }

//         // ProtocolSequence *u_this = const_cast<ProtocolSequence *>(this);
//         // u_this->steps.erase(steps.begin());

//         return true;
//     }

//     return false;
// }

optional<const Protocol *> ProtocolSequence::popFirst() const
{
    if (isComplete())
        return std::nullopt;

    const ProtocolSequence *tempSeq = this;
    const ProtocolSequence **seqPtr = &tempSeq;

    while (const ProtocolClose *protoClose = dynamic_cast<const ProtocolClose *>((*seqPtr)->steps.front()))
    {
        const ProtocolSequence *seq = protoClose->getInnerProtocol();

        if (seq->isComplete())
            break;

        seqPtr = &seq;
    }

    const Protocol *ans = (*seqPtr)->steps.front();
    ProtocolSequence *m_seq = const_cast<ProtocolSequence *>(*seqPtr);
    m_seq->steps.erase(m_seq->steps.begin());

    return ans;
}

std::optional<const ProtocolClose *> ProtocolSequence::popFirstCancelable() const
{
    if (isComplete())
        return std::nullopt;

    if (const ProtocolClose *outerClose = dynamic_cast<const ProtocolClose *>(this->steps.front()))
    {
        ProtocolSequence *seq = const_cast<ProtocolSequence *>(this);
        ProtocolClose * close = const_cast<ProtocolClose *>(outerClose); 

        while (!seq->isComplete())
        {
            std::cout << "844 " << seq->toString() << std::endl; 
            const ProtocolSequence *tempSeq = close->getInnerProtocol();

            if (tempSeq->isComplete())
                break;

            if (const ProtocolClose *protoClose = dynamic_cast<const ProtocolClose *>(tempSeq->steps.front()))
            {
                seq = const_cast<ProtocolSequence *>(tempSeq);
                close = const_cast<ProtocolClose*>(protoClose); 
            }
            else
            {
                break;
            }
        }
        seq->steps.erase(seq->steps.begin());
        return close;
    }
    return std::nullopt;
}

void ProtocolSequence::insertSteps(vector<const Protocol *> ins) const
{
    ProtocolSequence *seq = const_cast<ProtocolSequence *>(this);

    if (isComplete())
    {
        seq->steps.insert(seq->steps.begin(), ins.begin(), ins.end());
        return; // true;
    }

    while (const ProtocolClose *protoClose = dynamic_cast<const ProtocolClose *>(seq->steps.front()))
    {
        const ProtocolSequence *innerSeq = protoClose->getInnerProtocol();

        if (innerSeq->isComplete())
            break;

        seq = const_cast<ProtocolSequence *>(innerSeq);
    }

    seq->steps.insert(seq->steps.begin(), ins.begin(), ins.end());
    return; // true;
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
    description << "Cancelable<" << proto->toString() << ">";

    return description.str();
}
const Protocol *ProtocolClose::getInverse() const
{
    return new ProtocolClose(this->inCloseable, this->proto->getInverse(), this->getCloseNumber());
}

const Protocol *ProtocolClose::getCopy() const
{
    auto ans = new ProtocolClose(this->inCloseable, this->proto->getCopy(), this->getCloseNumber());
    ans->guardCount = this->guardCount;
    return ans;
}