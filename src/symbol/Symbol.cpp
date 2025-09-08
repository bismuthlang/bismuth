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


std::shared_ptr<Symbol> Symbol::getCopy() {
    return std::make_shared<Symbol>(
        this->identifier,
        this->type->getCopy(),
        this->global
    );
}



Scope& LocatableSymbol::getScope() const { return scope; }


std::shared_ptr<Symbol> DefinitionSymbol::getCopy() {
    return std::make_shared<DefinitionSymbol>(
        this->visibility,
        this->getIdentifier(),
        this->getType()->getCopy(),
        this->isGlobal(),
        this->getScope(), // FIXME: if we are copying into new scope, this isn't right
        this->innerScope // FIXME: This is similarly dubious!
    );
}


std::shared_ptr<Symbol> AliasSymbol::getCopy() {
    return std::make_shared<AliasSymbol>(
        this->getIdentifier(),
        this->getScope(), // FIXME: if we are copying into new scope, this isn't right
        this->getType()->getCopy(),
        this->orig
    );
}