#include "Symbol.h"

// std::string Symbol::getIdentifier() const { return identifier; }

std::string Symbol::toString() const
{
    std::ostringstream description;
    std::string typeName = type->toString(DisplayMode::C_STYLE);
    description << '[' << identifier << ", " << typeName << ']';
    return description.str();
}

const Type * Symbol::getType() const { return type; }

bool Symbol::isGlobal() const { return global; }
bool Symbol::isDefinition() const { return definition; }

std::string Symbol::getUniqueNameInScope() const { 
    if(const TypeTemplate * t = dynamic_cast<const TypeTemplate *>(getType()))
    {
        return uniqueNameInScope + t->templateString(DisplayMode::C_STYLE);
    }
    return uniqueNameInScope; 
}
std::string Symbol::getScopedIdentifier() const { return identifier; }

Scope * Symbol::getScope() const { return scope; }
