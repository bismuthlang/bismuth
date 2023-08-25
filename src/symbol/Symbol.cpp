#include "Symbol.h"

std::string Symbol::getIdentifier() const { return identifier; }

std::string Symbol::toString() const
{
    std::ostringstream description;
    std::string typeName = type->toString();
    description << '[' << identifier << ", " << typeName << ']';
    return description.str();
}

std::optional<llvm::AllocaInst *> Symbol::getAllocation()
{
    return *val;
}

void Symbol::setAllocation(llvm::AllocaInst * a) 
{ 
    *val = a; 
}