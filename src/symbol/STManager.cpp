#include "STManager.h"


void STManager::enterScope(StopType stopType, std::optional<Identifier *> idOpt) // std::string id, std::optional<std::function<std::string()>> meta = std::nullopt)
{
    context.enterScope(stopType == GLOBAL, idOpt); //id, meta);
} 


Scope * STManager::createNamespace(Identifier * id)
{
    return context.createNamespace(id); 
}

optional_ref<Scope> STManager::exitScope()
{
    return context.exitScope();
}

optional_ref<Symbol> STManager::addSymbol(std::string id, const Type * t, bool g) // TODO: automatically determine g?
{
    // Latter condition needed to prevent return types from being tracked as linear. see getBinaryStreamFor in adder5. PLAN: handle this better, should probably make return a linear type in general to make it so that way we can have better dead code detection/elimination.
    return context.addSymbol(id, t, g);
}

optional_ref<AliasSymbol> STManager::addAlias(std::string id, const Type * t, Identifier * a)//Symbol * a)
{
    return context.addAlias(id, t, a);
}

optional_ref<DefinitionSymbol> STManager::addDefinition(VisibilityModifier m, std::string id, const Type * t, bool glob)
{

    auto symOpt = context.addDefinition(getCurrentScope(), m, id, t, glob);

    if(symOpt)
    {
        DefinitionSymbol& sym = symOpt.value().get(); 
        if(const NameableType * nameable = dynamic_cast<const NameableType *>(sym.getType()))
        {
            if(!nameable->getIdentifier())
            {
                nameable->setIdentifier(sym.getIdentifier());
            }
        }
    }

    return symOpt; // context.addDefinition(id, t, glob);
}

optional_ref<Symbol> STManager::addAnonymousSymbol(std::string id, const Type * t)
{
    return context.addAnonymousSymbol(id, t); 
}

optional_ref<DefinitionSymbol> STManager::addAnonymousDefinition(std::string id, const Type * t)
{
    return context.addAnonymousDefinition(id, t); 
}

bool STManager::removeSymbol(Symbol& symbol)
{
    return context.removeSymbol(symbol);
}

optional_ref<Symbol> STManager::lookup(std::string id)
{
    auto sym = context.lookupInAccessableScopes(id); 
    // TODO: propagate this data down so we don't have 
    // to do excess branching checks. 
    // Also, ensure this doesn't mess w/ error messages by 
    // making it seem like stuff isn't unbound. 
    // Ie, while isBound will help, we may use lookup in field access!
    if(nonLinearOnly 
        && sym.has_value() 
        && sym.value().get().getType()->isLinear())
      return std::nullopt; 
    return sym; 
}

void STManager::enterNonlinearScope(std::function<void()> func)
{
    bool prevValue = nonLinearOnly; 
    nonLinearOnly = true; 
    func(); 
    nonLinearOnly = prevValue; 
}

bool STManager::isBound(std::string id)
{
    return context.lookupInAccessableScopes(id).has_value(); 
}

optional_ref<Symbol> STManager::lookupInCurrentScope(std::string id)
{
    return context.lookupInCurrentScope(id);
}

Scope& STManager::getCurrentScope()
{
    return context.getCurrentScope();
}

std::vector<std::reference_wrapper<Symbol>> STManager::getLinears(int flags) { return context.getSymbols(flags); }


void STManager::guard()
{
    for (Symbol& sym : getLinears(SymbolLookupFlags::COMPLETE_LINEAR | SymbolLookupFlags::GUARDED_LINEAR | SymbolLookupFlags::PENDING_LINEAR))
    {
      if(sym.getType()->isLinear())
        sym.getType()->guard(); 
    }
}

bool STManager::unguard() 
{
    for (Symbol& sym : getLinears(SymbolLookupFlags::COMPLETE_LINEAR | SymbolLookupFlags::GUARDED_LINEAR | SymbolLookupFlags::PENDING_LINEAR))
    {
        if(sym.getType()->isLinear() && !sym.getType()->unguard())
        {
          std::cout << "Failed to unguard " << sym.toString() << std::endl; 
          return false; 
        }
    }
    return true; 
}


int STManager::scopeCount() { return context.scopeCount(); }

std::string STManager::toString() const
{
    std::ostringstream desc;
    desc << "{context=" << context.toString() << "}";

    return desc.str();
}

bool STManager::isGlobalScope()
{
    return context.isGlobalScope();
}

std::string STManager::getUniqNameFor(Scope * parent, std::string inScope) {
    std::string id = parent->getIdentifier()->getFullyQualifiedName() + "::" + inScope;

    auto itr = nameCounter.find(id);
    if(itr == nameCounter.end())
    {
        nameCounter.insert({id, 0});
        return inScope;
    }
    std::ostringstream nextName; 
    nextName << inScope << "." << itr->second; 
    nameCounter.insert({id, itr->second++});
    return nextName.str(); 
}
