#include "Type.h"

bool Type::isSubtype(const Type *other) const
{
    if (const TypeInfer *inf = dynamic_cast<const TypeInfer *>(this))
    {
        // return false;
        // return inf->isSupertype(this);
        return inf->isSupertype(other);
    }
    return other->isSupertypeFor(this);
}

/*
 * INT Types
 */
bool TypeInt::isSupertypeFor(const Type *other) const
{
    return dynamic_cast<const TypeInt *>(other);
}

/*
 * BOOL types
 */
bool TypeBool::isSupertypeFor(const Type *other) const
{
    return dynamic_cast<const TypeBool *>(other);
}

/*
 * Strings
 */

bool TypeStr::isSupertypeFor(const Type *other) const
{
    return dynamic_cast<const TypeStr *>(other);
}

/*
 * BOT
 */
bool TypeBot::isSupertypeFor(const Type *other) const
{
    return false;
}

/*************************************
 *
 * Protocols
 *
 *************************************/

bool ProtocolSequence::canSend(const Type *ty) const
{
    if (isComplete())
        return false;

    const Protocol *proto = steps.front();

    if (const ProtocolSend *send = dynamic_cast<const ProtocolSend *>(proto))
    {
        return ty->isSubtype(send->getSendType());
    }

    return false;
}

bool ProtocolSequence::send(const Type *ty) const
{
    // FIXME: BETTER ERROR HANDLING

    if (canSend(ty))
    {
        ProtocolSequence *mthis = const_cast<ProtocolSequence *>(this);
        mthis->steps.erase(steps.begin());
        return true;
    }

    return false;
}

bool ProtocolSequence::canRecv() const
{
    if (isComplete())
        return false;

    const Protocol *proto = steps.front();

    if (const ProtocolRecv *recv = dynamic_cast<const ProtocolRecv *>(proto))
    {
        return true; // ty->isSubtype(recv->getRecvType());
    }

    return false;
}

optional<const Type *> ProtocolSequence::recv() const
{
    // FIXME: BETTER ERROR HANDLING
    if (canRecv())
    {
        // FIXME: DO BETTER:

        const Protocol *proto = steps.front();
        const ProtocolRecv *recv = dynamic_cast<const ProtocolRecv *>(proto);

        ProtocolSequence *mthis = const_cast<ProtocolSequence *>(this);
        mthis->steps.erase(steps.begin());
        return recv->getRecvType();
    }

    return {};
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
    if (isWN())
    {
        const Protocol *proto = steps.front(); // TODO: Handle more efficiently
        const ProtocolWN *wn = dynamic_cast<const ProtocolWN *>(proto);

        ProtocolSequence *mthis = const_cast<ProtocolSequence *>(this);
        vector<const Protocol *> other = wn->getInnerProtocol()->steps;
        mthis->steps.insert(steps.begin(), other.begin(), other.end()); //FIXME: WE PROBABLY NEED TO DO BETTER FLATTENING!
        return true;
    }

    return false;
}

bool ProtocolSequence::weaken() const
{
    if (isWN())
    {
        ProtocolSequence *mthis = const_cast<ProtocolSequence *>(this);
        mthis->steps.erase(steps.begin());
        return true;
    }

    return false;
}

bool ProtocolSequence::isWNWN() const
{
    if (isComplete())
        return false;
    const Protocol *proto = steps.front();
    if (const ProtocolWN *wn = dynamic_cast<const ProtocolWN *>(proto))
    {
        return wn->getInnerProtocol()->isWN();
    }

    return false;
}

optional<const ProtocolSequence *> ProtocolSequence::shearLoop() const
{
    if (isWNWN())
    {
        const Protocol *proto = steps.front();
        const ProtocolWN *wn = dynamic_cast<const ProtocolWN *>(proto);

        return toSequence(wn->getInnerProtocol()->getCopy());
    }

    return {};
}

bool ProtocolSequence::isOC() const
{
    if (isComplete())
        return false;
    const Protocol *proto = steps.front();
    if (const ProtocolOC *wn = dynamic_cast<const ProtocolOC *>(proto))
    {
        return true;
    }

    return false;
}

optional<const ProtocolSequence *> ProtocolSequence::acceptLoop() const
{
    if (isOC())
    {
        const Protocol *proto = steps.front();
        const ProtocolOC *wn = dynamic_cast<const ProtocolOC *>(proto);
        const ProtocolSequence *ans = toSequence(wn->getInnerProtocol()->getCopy());

        ProtocolSequence *mthis = const_cast<ProtocolSequence *>(this);
        mthis->steps.erase(steps.begin());

        return ans;
    }

    return {};
}

// FIXME: METHODIZE A LOT OF THESE
bool ProtocolSequence::isIntChoice() const
{
    if (isComplete())
        return false;
    const Protocol *proto = steps.front();
    if (const ProtocolIChoice *wn = dynamic_cast<const ProtocolIChoice *>(proto))
    {
        return true;
    }

    return false;
}

bool ProtocolSequence::project(const ProtocolSequence *ps) const
{
    if (isIntChoice())
    {
        const Protocol *proto = steps.front();
        const ProtocolIChoice *ic = dynamic_cast<const ProtocolIChoice *>(proto);

        for (const ProtocolSequence *p : ic->getOptions())
        {
            if (ps->toString() == p->toString()) // FIXME: DO BETTER
            {
                ProtocolSequence *mthis = const_cast<ProtocolSequence *>(this);
                mthis->steps.erase(steps.begin());
                vector<const Protocol *> other = p->steps;
                mthis->steps.insert(steps.begin(), other.begin(), other.end());

                return true;
            }
        }

        return false;
    }

    return false;
}

bool ProtocolSequence::isExtChoice(set<const ProtocolSequence *, ProtocolCompare> testOpts) const
{
    if (isComplete())
        return false;

    const Protocol *proto = steps.front();
    // FIXME: NEED TO CHANGE INT AND EXT CHOICE TO SETS TO PREVENT DUP!!!
    if (const ProtocolEChoice *eChoice = dynamic_cast<const ProtocolEChoice *>(proto))
    {
        std::set<const ProtocolSequence *, ProtocolCompare> foundCaseTypes = {};
        // FIXME: THIS WILL BE BROKEN UNTIL WE CAN USE SETS!

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

        ProtocolSequence *mthis = const_cast<ProtocolSequence *>(this);
        mthis->steps.erase(steps.begin());

        return true; 

        // return ty->isSubtype(send->getSendType());
    }

    return false;
}