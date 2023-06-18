#include "Type.h"

bool Type::isSubtype(const Type *other) const
{
    if (const TypeInfer *inf = dynamic_cast<const TypeInfer *>(this))
    {
        // return false;
        // return inf->isSupertype(this);
        return inf->isSupertype(other);
    }

    if(other->isLinear() && !this->isLinear()) return false;  //FIXME: VERIFY WORKS WITH TYPE INF!

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
bool TypeBottom::isSupertypeFor(const Type *other) const
{
    return false;
}

/*
 * Unit
 */
bool TypeUnit::isSupertypeFor(const Type *other) const
{
    // return dynamic_cast<const TypeUnit *>(other);
    // return false;
    return dynamic_cast<const TypeUnit *>(other);
}

/*
 * Absurd
 */
bool TypeAbsurd::isSupertypeFor(const Type *other) const
{
    return false;
}

/*************************************
 *
 * Protocols
 *
 *************************************/