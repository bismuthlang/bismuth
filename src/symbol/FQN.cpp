#include "FQN.h"


std::string Identifier::getFullyQualifiedName() const 
{
    std::string name = this->getUniqueNameInScope(); 

    optional<Identifier *> parentOpt = this->parent; 

    if(name == "" && parentOpt)
        return parentOpt.value()->getFullyQualifiedName();
    // TODO: what if name = "" and parentOpt is empty? shouldn't be possible, but still..
    
    while(parentOpt)
    {
        Identifier * parent = parentOpt.value(); 
        std::string parentName = parent->getUniqueNameInScope(); 

        if(parentName != "")
            name = parentName + "::" + name; 

        parentOpt = parent->parent;
    }

    return name; 
} 

std::string Identifier::getUniqueNameInScope() const
{
    return this->uniqueNameInScope + (meta.has_value() ? meta.value()() : "");
}

std::string Identifier::getScopedIdentifier() const
{
    return this->identifier + (meta.has_value() ? meta.value()() : "");
}
