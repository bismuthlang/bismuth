#include "Symbol.h"

// std::string Symbol::getIdentifier() const { return identifier; }

std::string Symbol::toString() const
{
    std::cerr << "7 " << this << " " << type << " " << identifier << std::endl;
    std::ostringstream description;
    std::string typeName = type->toString(DisplayMode::C_STYLE);
    std::cerr << "10" << std::endl;
    description << '[' << identifier->getScopedIdentifier() << ", " << typeName << ']';
    std::cerr << "12" << std::endl;
    return description.str();
}

const Type * Symbol::getType() const { return type; }

bool Symbol::isGlobal() const { return global; }
bool Symbol::isDefinition() const { return false; }

std::string Symbol::getUniqueNameInScope() const { return identifier->getUniqueNameInScope(); }

std::string Symbol::getScopedIdentifier() const { return identifier->getScopedIdentifier(); } //identifier; }

void Symbol::updateIdentifier(Identifier * nxt) 
{
    if(const NameableType * nt = dynamic_cast<const NameableType *>(type))
    {
        nt->setIdentifier(nxt); 
    }
    this->identifier = nxt; 
}

Scope& LocatableSymbol::getScope() const { return scope; }
