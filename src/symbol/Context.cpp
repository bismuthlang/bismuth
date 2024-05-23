#include "Context.h"

Scope &Context::enterScope(bool insertStop, std::optional<Identifier *> idOpt)  //std::string id, std::optional<std::function<std::string()>> meta)
{
    // This is safe because we use optionals
    Identifier * id = [this, idOpt](){
        if(idOpt) return idOpt.value(); 

        auto parentOpt = 
            this->currentScope ? 
                (std::optional<Identifier *>) this->currentScope.value()->getIdentifier() 
                : (std::optional<Identifier *>) std::nullopt; 
        return new Identifier("", "", parentOpt);
        
    }(); 



    Scope *next = new Scope(this->currentScope, id, insertStop);
    next->setId(this->scopeNumber++);

    this->currentScope = std::optional<Scope *>{next};
    // scopes.push_back(next);

    return *next;
}

void Context::enterScope(Scope * scope)
{
    this->currentScope = scope; 
}

Scope * Context::createNamespace(Identifier * id)
{
    Scope *next = new Scope(this->currentScope, id, true);
    next->setId(this->scopeNumber++);

    return next; 
}

std::optional<Scope *> Context::exitScope()
{
    // INFO: Potential memory leak
    if (!currentScope)
    {
        return std::nullopt;
    }

    Scope *last = currentScope.value();

    currentScope = last->getParent();

    return std::optional<Scope *>{last};
}

std::optional<SymbolRef> Context::addSymbol(std::string id, const Type * t, bool glob)
{
    // Check that the exact same identifier doesn't already exist in the current scope
    if(!currentScope || this->lookupInCurrentScope(id)) return std::nullopt;


    // Find a unique name for the symbol within the current stop
    uint32_t idNum = 0; 
    std::string uniqName = getUniqNameFor(*currentScope.value(), id); 


    // Note: this is safe as we previously check that currentScope exists
    return currentScope.value()->addSymbol<Symbol>(
        std::make_unique<LocatableSymbol>(
            new Identifier(
                id, 
                uniqName, 
                currentScope.value()->getIdentifier()
            ), 
            t, 
            glob, 
            currentScope.value()
        ));
}

std::optional<DefinitionSymbolRef> Context::addDefinition(VisibilityModifier m, std::string id, const Type * t, bool glob)
{
    // Check that the exact same identifier doesn't already exist in the current scope
    if(!currentScope || this->lookupInCurrentScope(id)) return std::nullopt;

    // Find a unique name for the symbol within the current stop
    uint32_t idNum = 0; 
    std::string uniqName = getUniqNameFor(*currentScope.value(), id); 

    auto identifier = new Identifier(
        id, 
        uniqName, 
        currentScope.value()->getIdentifier()
    ); 

    Scope* innerScope = this->createNamespace(identifier);

    return currentScope.value()->addSymbol(
        std::make_unique<DefinitionSymbol>(
            m, 
            identifier, 
            t, 
            glob, 
            currentScope.value(), 
            innerScope
        )
    );
}

std::optional<AliasSymbolRef> Context::addAlias(std::string id, const Type * t, Identifier * a)
{
    // Check that the exact same identifier doesn't already exist in the current scope
    if(!currentScope || this->lookupInCurrentScope(id)) return std::nullopt;


    // TODO: why are we doing uniqueName? I guess it shouldnt ever happen tho given lookup in currentScope?
    std::string uniqName = getUniqNameFor(*currentScope.value(), id); 

    return currentScope.value()->addSymbol(
        std::make_unique<AliasSymbol>(
            new Identifier(id, uniqName, currentScope.value()->getIdentifier()),
            currentScope.value(),
            t, 
            a
        )
    );
}

std::optional<SymbolRef> Context::addAnonymousSymbol(std::string wantedId, const Type * t)
{
    std::string id = "#" + wantedId; // TODO: Better symbol to indicate anon. @ reserved for compiler internals
    // Check that the exact same identifier doesn't already exist in the current scope
    if(!currentScope) return std::nullopt;
    // Find a unique name for the symbol within the current stop
    id = getUniqNameFor(*currentScope.value(), id);

    // Note: this is safe as we previously check that currentScope exists
    // FIXME: DETERMINE GLOB!!! SHOULD IT BE FALSE OR TRUE?
    return currentScope.value()->addSymbol(
        std::make_unique<LocatableSymbol>(
        new Identifier(id, id, currentScope.value()->getIdentifier()), t, false, currentScope.value()));
}

std::optional<DefinitionSymbolRef> Context::addAnonymousDefinition(std::string wantedId, const Type * t)
{
    std::string id = "#" + wantedId; // TODO: Better symbol to indicate anon. @ reserved for compiler internals
    // Check that the exact same identifier doesn't already exist in the current scope
    if(!currentScope) return std::nullopt;
    // Find a unique name for the symbol within the current stop
    id = getUniqNameFor(*currentScope.value(), id);

    Identifier * identifier = new Identifier(id, id, currentScope.value()->getIdentifier());

    // FIXME: DETERMINE GLOB!!! SHOULD IT BE FALSE OR TRUE?

    // Note: this is safe as we previously check that currentScope exists
    return currentScope.value()->addSymbol(
        std::make_unique<DefinitionSymbol>(
            VisibilityModifier::PRIVATE,
            identifier, 
            t, 
            false,
            currentScope.value(), 
            createNamespace(identifier)
        ));
}

bool Context::removeSymbol(Symbol& symbol)
{
    std::optional<Scope *> opt = currentScope;
    bool foundStop = false; 

    while (opt && !foundStop)
    {
        Scope *scope = opt.value();

        if (!foundStop) // depth >= stop)
        {
            if(scope->removeSymbol(symbol))
                return true; 
        }
        else 
        {
            return false;
        }

        foundStop = scope->isStop(); 
        opt = scope->getParent();
    }

    return false;
}

std::optional<SymbolRef> Context::lookup(std::string id)
{
    std::optional<Scope *> opt = currentScope;
    bool foundStop = false; 

    while (opt)
    {
        Scope *scope = opt.value();

        auto symOpt = scope->lookup(id);
        if (symOpt)
        {
            auto sym = symOpt.value(); 
            if (!foundStop || sym.get().isDefinition() || sym.get().isGlobal())
                return sym;
            return std::nullopt;
        }

        foundStop = scope->isStop(); 
        opt = scope->getParent();
    }

    return std::nullopt;
}

std::vector<SymbolRef> Context::findSymbols(int flags) //TODO: DO BETTER
{
    std::vector<SymbolRef> ans;

    std::optional<Scope *> opt = currentScope;
    bool foundStop = false; 

    while (!foundStop)//depth >= stop)
    {
        Scope *scope = opt.value();

        auto toAdd = scope->findSymbols(flags);
        ans.insert(ans.end(), toAdd.begin(), toAdd.end());

        foundStop = scope->isStop(); 
        opt = scope->getParent();
    }

    return ans;
}

std::optional<SymbolRef> Context::lookupInCurrentScope(std::string id)
{
    std::optional<Scope *> opt = currentScope;
    if (opt)
    {
        Scope *scope = opt.value();
        return scope->lookup(id);
    }

    return std::nullopt;
}

// Directly from sample
std::string Context::toString() const
{
    std::ostringstream description;
    std::optional<Scope *> scopeOpt = currentScope; 
    while(scopeOpt)
    {
        Scope * scope = scopeOpt.value(); 
        description << scope->toString(); 
        scopeOpt = scope->getParent(); 
    }
    // for (auto scope : scopes)
    // {
    //     description << scope->toString();
    // }
    return description.str();
}

std::optional<Scope *> Context::getOrProvisionScope(std::vector<std::string> steps, VisibilityModifier m)
{
    // Note bad variable names (we have two current scopes in here)
    std::optional<Scope *> origScope = this->currentScope; 

    this->currentScope = globalScope; 



    for(std::string s : steps)
    {
        auto symOpt = lookup(s);
        if(!symOpt)
        {
            TypeModule * mod = new TypeModule();
            auto dsOpt = addDefinition(m, s, mod, true);

            assert(dsOpt.has_value()); // We already checked conflicts

            this->currentScope = dsOpt.value().get().getInnerScope(); 
        }
        else if(DefinitionSymbol * ds = dynamic_cast<DefinitionSymbol *>(&symOpt.value().get())) // TODO: DO BETTER!
            this->currentScope = ds->getInnerScope(); 
        else 
        {
            this->currentScope = origScope; 
            return std::nullopt; 
        }
    }

    assert(this->currentScope.has_value());
    Scope * ans = this->currentScope.value(); 
    this->currentScope = origScope; 
    return ans; 
}

std::string Context::getUniqNameFor(Scope& parent, std::string inScope) {
    // TODO: not sure if getting FQN here will break some stuff wrt generics...
    std::string id = parent.getIdentifier()->getFullyQualifiedName() + "::" + inScope;
    
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