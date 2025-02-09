#include "Protocol.h"
#include "matchit.h"

bool Protocol::isSubtype(const Protocol *other) const
{
    return other->isSupertypeFor(this);
}


/*********************************************
 *
 *  ProtocolRecv
 *
 * ********************************************/

// const TypeSum *NullOptional::asSum()
// {
//     return new TypeSum({innerType, Types::UNIT});
// }

std::string ProtocolRecv::as_str(DisplayMode mode) const
{
    return "+" + recvType->toString(mode);
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

bool ProtocolRecv::isSupertypeFor(const Protocol *other) const
{
    if(const ProtocolRecv * pOther = dynamic_cast<const ProtocolRecv *>(other))
    {
        return this->recvType->isSubtype(pOther->recvType);
    }

    return false;
}

const ProtocolRecv * ProtocolRecv::getCopySubst(std::map<const Type *, const Type *> & existing) const
{
    return new ProtocolRecv(
        this->isInCloseable(), 
        recvType->getCopySubst(existing)
    );
}
/*********************************************
 *
 *  ProtocolSend
 *
 * ********************************************/

std::string ProtocolSend::as_str(DisplayMode mode) const
{
    return "-" + sendType->toString(mode);
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

bool ProtocolSend::isSupertypeFor(const Protocol *other) const
{
    if(const ProtocolSend * pOther = dynamic_cast<const ProtocolSend *>(other))
    {
        return this->sendType->isSubtype(pOther->sendType);
    }

    return false;
}


const ProtocolSend * ProtocolSend::getCopySubst(std::map<const Type *, const Type *> & existing) const
{
    return new ProtocolSend(
        this->isInCloseable(), 
        sendType->getCopySubst(existing)
    );
}
/*********************************************
 *
 *  ProtocolWN
 *
 * ********************************************/

std::string ProtocolWN::as_str(DisplayMode mode) const
{
    return "?(" + proto->toString(mode) + ")";
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

bool ProtocolWN::isSupertypeFor(const Protocol *other) const
{
    if(const ProtocolWN * pOther = dynamic_cast<const ProtocolWN *>(other))
    {
        return this->proto->isSubtype(pOther->proto);
        // return this->sendType->isSubtype(pOther->sendType);
    }

    return false;
}

const ProtocolWN * ProtocolWN::getCopySubst(std::map<const Type *, const Type *> & existing) const
{
    return new ProtocolWN(
        this->isInCloseable(),
        proto->getCopySubst(existing)
    );
}

/*********************************************
 *
 *  ProtocolOC
 *
 * ********************************************/
std::string ProtocolOC::as_str(DisplayMode mode) const
{
    return "!(" + proto->toString(mode) + ")";
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

bool ProtocolOC::isSupertypeFor(const Protocol *other) const
{
    if(const ProtocolOC * pOther = dynamic_cast<const ProtocolOC *>(other))
    {
        return this->proto->isSubtype(pOther->proto);
        // return this->sendType->isSubtype(pOther->sendType);
    }

    return false;
}

const ProtocolOC * ProtocolOC::getCopySubst(std::map<const Type *, const Type *> & existing) const
{
    return new ProtocolOC(
        this->isInCloseable(),
        proto->getCopySubst(existing)
    );
}

/*********************************************
 *
 *  ProtocolIChoice
 *
 * ********************************************/
std::string ProtocolIChoice::as_str(DisplayMode mode) const
{
    std::ostringstream description;

    switch(mode)
    {
        case C_STYLE:
        {
            description << "InternalChoice<";
            unsigned int i = 0;
            for (auto p : opts)
            {
                if (i != 0)
                    description << ", ";
                description << p->toString(mode);
                i++;
            }
            description << ">";

            return description.str(); 
        }

        case MATH_STYLE:
        {
            unsigned int i = 0;
            for (auto p : opts)
            {
                if (i != 0)
                    description << "&";
                description << p->toString(mode);
                i++;
            }

            return description.str();
        }
    }
}

const ProtocolEChoice *ProtocolIChoice::getInverse() const
{
    std::set<const ProtocolBranchOption *, BranchOptCompare> opts;

    for (auto p : this->opts)
    {
        opts.insert(p->getInverse());
    }

    return new ProtocolEChoice(this->inCloseable, opts);
}

const Protocol *ProtocolIChoice::getCopy() const
{
    std::set<const ProtocolBranchOption *, BranchOptCompare> opts;

    for (auto p : this->opts)
    {
        opts.insert(p->getCopy());
    }

    auto ans = new ProtocolIChoice(this->inCloseable, opts);
    ans->guardCount = this->guardCount;
    return ans;
}

bool ProtocolIChoice::isSupertypeFor(const Protocol *other) const
{
    if(const ProtocolIChoice * pOther = dynamic_cast<const ProtocolIChoice *>(other))
    {
        // TODO: subtype branches properly instead of via equality 
        if(this->opts.size() != pOther->opts.size()) return false; 

        for(const ProtocolBranchOption * branch : opts)
        {
            if(!pOther->opts.contains(branch)) return false; 
        }

        return true; 
    }

    return false;
}

const ProtocolIChoice * ProtocolIChoice::getCopySubst(std::map<const Type *, const Type *> & existing) const
{
    std::set<const ProtocolBranchOption *, BranchOptCompare> opts;

    for (auto p : this->opts)
    {
        opts.insert(p->getCopySubst(existing));
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
std::string ProtocolEChoice::as_str(DisplayMode mode) const
{
    std::ostringstream description;

    switch(mode)
    {
        case C_STYLE:
        {
            description << "ExternalChoice<";
            unsigned int i = 0;
            for (auto p : opts)
            {
                if (i != 0)
                    description << ", ";
                description << p->toString(mode);
                i++;
            }
            description << ">";

            return description.str(); 
        }

        case MATH_STYLE:
        {
            unsigned int i = 0;
            for (auto p : opts)
            {
                if (i != 0)
                    description << "\u2295";
                description << p->toString(mode);
                i++;
            }

            return description.str();
        }
    }
}

const Protocol *ProtocolEChoice::getInverse() const
{
    std::set<const ProtocolBranchOption *, BranchOptCompare> opts;

    for (auto p : this->opts)
    {
        opts.insert(p->getInverse());
    }

    return new ProtocolIChoice(this->inCloseable, opts);
}

const Protocol *ProtocolEChoice::getCopy() const
{
    std::set<const ProtocolBranchOption *, BranchOptCompare> opts;

    for (auto p : this->opts)
    {
        opts.insert(p->getCopy());
    }

    auto ans = new ProtocolEChoice(this->inCloseable, opts);
    ans->guardCount = this->guardCount;
    return ans;
}


// TODO: add to internal choice then use it instead of existing lookup? 
std::optional<const ProtocolBranchOption *> 
ProtocolEChoice::lookup(std::variant<const ProtocolSequence *, std::string> opt) const
{
    using namespace matchit; 
    Id<std::string> label; 
    Id<const ProtocolSequence *> ps;
    return match(opt)(
        pattern | as<std::string>(label) = [&]()-> std::optional<const ProtocolBranchOption *> {
            for(const ProtocolBranchOption * br : opts)
            {
                if(!br->label) continue; 

                if(br->label.value() == *label) return std::make_optional<const ProtocolBranchOption *>(br);
            }
            return std::nullopt;
        },
        pattern | as<const ProtocolSequence *>(ps) = [&]()-> std::optional<const ProtocolBranchOption *> {
            for(const ProtocolBranchOption * br : opts)
            {
                if(br->label) continue; 

                // Note: this has to be explicit matching; subtypes/structural equivalences could technically be 
                // other branches...
                if (br->seq->toString(DisplayMode::C_STYLE) == (*ps)->toString(DisplayMode::C_STYLE)) 
                    return std::make_optional<const ProtocolBranchOption *>(br);
            }
            return std::nullopt;
        }
    );
}

bool ProtocolEChoice::isSupertypeFor(const Protocol *other) const
{
    if(const ProtocolEChoice * pOther = dynamic_cast<const ProtocolEChoice *>(other))
    {
        // TODO: subtype branches properly instead of via equality 
        if(this->opts.size() != pOther->opts.size()) return false; 

        for(const ProtocolBranchOption * branch : opts)
        {
            if(!pOther->opts.contains(branch)) return false; 
        }

        return true; 
    }

    return false;
}

const ProtocolEChoice * ProtocolEChoice::getCopySubst(std::map<const Type *, const Type *> & existing) const
{
    std::set<const ProtocolBranchOption *, BranchOptCompare> opts;

    for (auto p : this->opts)
    {
        opts.insert(p->getCopySubst(existing));
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

std::string ProtocolSequence::as_str(DisplayMode mode) const
{
    std::ostringstream description;
    // for (auto p : steps)
    for (unsigned int i = 0; i < steps.size(); i++)
    {
        if (i != 0)
            description << ";";
        description << steps.at(i)->toString(mode);
    }

    return description.str();
}

const ProtocolSequence *ProtocolSequence::getInverse() const
{
    vector<const Protocol *> inverseSteps;

    for (auto p : this->steps)
    {
        inverseSteps.push_back(p->getInverse());
    }

    return new ProtocolSequence(this->inCloseable, inverseSteps);
}

const ProtocolSequence *ProtocolSequence::getCopy() const
{
    vector<const Protocol *> inverseSteps;

    for (auto p : this->steps)
    {
        inverseSteps.push_back(p->getCopy());
    }

    auto ans = new ProtocolSequence(this->inCloseable, inverseSteps);
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
    if(steps.size() == 0 || !this->isCancelable())
        return std::nullopt; 
    // if (steps.front()->isGuarded() || this->isGuarded())
        // return std::nullopt;

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

    unsigned int ans = 0;
    for (auto *p : ic.value()->getOptions())
    {
        ans++;
        if(p->label) continue; 

        // Note: this has to be explicit matching; subtypes/structural equivalences could technically be 
        // other branches...
        if (p->seq->toString(DisplayMode::C_STYLE) == ps->toString(DisplayMode::C_STYLE)) 
        {
            if (!this->swapChoice(p))
                return 0;
            return ans;
        }
    }

    return 0;
}

unsigned int ProtocolSequence::project(std::string label) const
{
    optional<const ProtocolIChoice *> ic = this->getIntChoice();
    if (!ic)
        return 0;

    unsigned int ans = 1;
    for (auto *p : ic.value()->getOptions())
    {
        if(!p->label) continue; 

        if (label == p->label.value())
        {
            if (!this->swapChoice(p))
                return 0;
            return ans;
        }
        ans++;
    }

    return 0;
}

// optional<vector<const ProtocolSequence *>> 
optional<CaseMetadata> 
ProtocolSequence::caseAnalysis(vector<variant<const ProtocolSequence *, string>> testOpts) const // Note: using vector as otherwise duplicate cases could be too easily ignored by type checking (ie, semantic visitor dumps cases into set and thus isn't aware of duplicates) //set<const ProtocolSequence *, ProtocolCompare> testOpts) const
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
        std::set<const ProtocolBranchOption *, BranchOptCompare> foundCaseTypes = {};
        std::vector<const ProtocolSequence *> ans = {}; 

        for (auto p : testOpts) // TODO: METHODIZE WITH MatchStatement?
        {
            std::optional<const ProtocolBranchOption *> brOpt = eChoice->lookup(p);
            if(!brOpt) return std::nullopt; // Got something that isn't in the ext choice 

            const ProtocolBranchOption * br = brOpt.value(); 

            const ProtocolSequence * res = this->getCopy(); 
            
            if(!res->swapChoice(br)) // if (!eChoice->getOptions().count(p))
            {
                // errorHandler.addSemanticError(ctx->getStart(), "Impossible case: " p->toString());
                return std::nullopt;
            }
            else 
            {
                ans.push_back(res); 
            }

            if (foundCaseTypes.count(br)) // Is this even possible? its a set after all. Would require messy subtyping
            {
                // errorHandler.addSemanticError(ctx->getStart(), "Duplicate case: " + p->toString());
                return std::nullopt; // FIXME: HANDLE ERRORS BETTER IN THE SEMANTIC VISITOR SO WE CAN GET THESE ERRORS!!
            }
            else
            {
                foundCaseTypes.insert(br);
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

bool ProtocolSequence::isCancelable() const // FIXME: DO BETTER
{
    if (steps.size() == 0)
    {
        return guardCount == 0;
    }
    return steps.front()->isCancelable();
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
bool ProtocolSequence::swapChoice(const ProtocolBranchOption * swap) const
{
    if (isComplete())
        return false;

    ProtocolSequence * seq = const_cast<ProtocolSequence *>(this); 

    while (const ProtocolClose *protoClose = dynamic_cast<const ProtocolClose *>(seq->steps.front()))
    {
        const ProtocolSequence *innerSeq = protoClose->getInnerProtocol();

        if (innerSeq->isComplete())
            break; 

        seq = const_cast<ProtocolSequence *>(innerSeq);
    }

    if(const ProtocolEChoice * extChoice = dynamic_cast<const ProtocolEChoice *>(seq->steps.front()))
    {
        if(!extChoice->getOptions().count(swap))
            return false; 
    }
    else if(const ProtocolIChoice * intChoice = dynamic_cast<const ProtocolIChoice *>(seq->steps.front()))
    {
        if(!intChoice->getOptions().count(swap))
            return false; 
    }
    else 
    {
        return false; 
    }

    seq->steps.erase(seq->steps.begin());
    seq->steps.insert(seq->steps.begin(), swap->seq->steps.begin(), swap->seq->steps.end()); 

    return true;
}

optional<const Protocol *> ProtocolSequence::popFirst() const
{
    if (isComplete())
        return std::nullopt;

    ProtocolSequence *seq = const_cast<ProtocolSequence *>(this);

    while (const ProtocolClose *protoClose = dynamic_cast<const ProtocolClose *>(seq->steps.front()))
    {
        const ProtocolSequence *innerSeq = protoClose->getInnerProtocol();

        if (innerSeq->isComplete())
            break;

        seq = const_cast<ProtocolSequence *>(innerSeq);
    }

    const Protocol *ans = seq->steps.front();
    seq->steps.erase(seq->steps.begin());

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

bool ProtocolSequence::isSupertypeFor(const Protocol *other) const
{
    if(const ProtocolSequence * pOther = dynamic_cast<const ProtocolSequence *>(other))
    {
        if(pOther->steps.size() != this->steps.size())
            return false; 

        for(unsigned int i = 0; i < this->steps.size(); i++)
        {
            if(!this->steps.at(i)->isSubtype(pOther->steps.at(i)))
                return false;
        }

        return true;
    }

    return false;
}

const ProtocolSequence * ProtocolSequence::getCopySubst(std::map<const Type *, const Type *> & existing) const
{
    std::vector<const Protocol *> substSteps; 

    for(auto step : this->steps)
    {
        substSteps.push_back(
            step->getCopySubst(existing)
        );
    }

    return new ProtocolSequence(this->isInCloseable(), substSteps);
}

/*********************************************
 *
 *  ProtocolClose
 *
 * *******************************************/
std::string ProtocolClose::as_str(DisplayMode mode) const
{
    return "Cancelable<" +  proto->toString(mode) + ">";
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

bool ProtocolClose::isGuarded() const // FIXME: DO BETTER
{
    // if (proto.   steps.size() == 0)
    // {
    //     return guardCount > 0;
    // }
    return proto->isGuarded(); // && guardCount >> 0; //steps.front()->isGuarded();
}

bool ProtocolClose::isCancelable() const // FIXME: DO BETTER
{
    return guardCount == 0; 
    // if (steps.size() == 0)
    // {
    //     return guardCount == 0;
    // }
    // return steps.front()->isCancelable();
}

void ProtocolClose::guard() const // FIXME: DO BETTER
{
    // if (steps.size() == 0)
    // {
    guardCount = guardCount + 1;
    // }
    // else
    // {
    proto->guard(); // TOOD: may be wrong...
    // }
}

bool ProtocolClose::unguard() const // FIXME: DO BETTER
{
    if(guardCount == 0)
        return false; 
    

    // if (steps.size() == 0)
    // {
    //     if (guardCount == 0)
    //         return false;

    guardCount = guardCount - 1;
    //     return true;
    // }
    proto->unguard(); 
    return true; 
    // return steps.front()->unguard();
}

bool ProtocolClose::isSupertypeFor(const Protocol *other) const
{
    if(const ProtocolClose * pOther = dynamic_cast<const ProtocolClose *>(other))
    {
        return this->proto->isSubtype(pOther->proto);
        // return this->sendType->isSubtype(pOther->sendType);
    }

    return false;
}

const ProtocolClose * ProtocolClose::getCopySubst(std::map<const Type *, const Type *> & existing) const
{
    return new ProtocolClose(
        this->isInCloseable(), 
        proto->getCopySubst(existing),
        closeNumber
    );
}