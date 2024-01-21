#include "Symbol.h"

// std::string Symbol::getIdentifier() const { return identifier; }

std::string Symbol::toString() const
{
    std::ostringstream description;
    std::string typeName = type->toString(DisplayMode::C_STYLE);
    description << '[' << identifier->getScopedIdentifier() << ", " << typeName << ']';
    return description.str();
}

const Type * Symbol::getType() const { return type; }

bool Symbol::isGlobal() const { return global; }
bool Symbol::isDefinition() const { return definition; }

std::string Symbol::getUniqueNameInScope() const { 
    // if(const NameableType * t = dynamic_cast<const NameableType *>(getType()))
    // {
    //     std::cout << "21 " << t->toString(DisplayMode::C_STYLE) << std::endl; 
    // }
    // if(const TypeTemplate * t = dynamic_cast<const TypeTemplate *>(getType()))
    // {
    //     return uniqueNameInScope + t->templateString(DisplayMode::C_STYLE);
    // }
    // return uniqueNameInScope; 

    return identifier->getUniqueNameInScope(); 
}
std::string Symbol::getScopedIdentifier() const { return identifier->getScopedIdentifier(); } //identifier; }

Scope * Symbol::getScope() const { return scope; }

void Symbol::updateIdentifier(Identifier * nxt) 
{
    if(const NameableType * nt = dynamic_cast<const NameableType *>(type))
    {
        nt->setIdentifier(nxt); 
    }
    this->identifier = nxt; 
}
