#include "Context.h"

// FIXME: Rename this function to be createAndEnterScope or something to that effect. Maybe mkAndEnterScope()?
Scope &Context::enterScope(bool insertStop, std::optional<Identifier *> idOpt)  //std::string id, std::optional<std::function<std::string()>> meta)
{
    // This is safe because we use optionals
    Identifier * id = [this, idOpt](){
        if(idOpt) return idOpt.value(); // FIXME: why is this allowed? shouldn't we require better scope access in the first place?

        std::optional<Identifier *> parentOpt =  this->currentScope.get().getIdentifier(); 
        Identifier * i = new Identifier("", "", parentOpt);
        // i->meta = meta;

        return i; 
        
    }(); 



    Scope *next = new Scope(this->currentScope.get(), id, insertStop);
    next->setId(this->scopeNumber++);

    this->currentScope = *next;
    // scopes.push_back(next);

    return *next;
}

void Context::enterScope(Scope & scope)
{
    this->currentScope = scope; 
}

Scope * Context::createNamespace(Identifier * id)
{
    Scope *next = currentScope.get().createNamespace(id);
    next->setId(this->scopeNumber++); // FIXME: REMOVE ID number in this form

    return next; 
}

optional_ref<Scope> Context::exitScope()
{
    // INFO: Potential memory leak
    if (auto parentScope = currentScope.get().getParent(); parentScope.has_value())
    {
        Scope& last = currentScope; 
        currentScope = *parentScope;
        return last; 
    }

    return std::nullopt;
}

optional_ref<Symbol> Context::addSymbol(std::string id, const Type * t, bool glob)
{
    // Check that the exact same identifier doesn't already exist in the current scope
    if(this->lookupInCurrentScope(id)) return std::nullopt;


    // Find a unique name for the symbol within the current stop
    std::string uniqName = getUniqNameFor(currentScope, id); 


    // Note: this is safe as we previously check that currentScope exists
    return currentScope.get().addSymbol(
        std::make_shared<LocatableSymbol>(
            new Identifier(
                id, 
                uniqName, 
                currentScope.get().getIdentifier()
            ), 
            t, 
            glob, 
            currentScope
        ));
}

optional_ref<DefinitionSymbol> Context::addDefinition(Scope & scope, VisibilityModifier m, std::string id, const Type * t, bool glob)
{
    // Check that the exact same identifier doesn't already exist in the current scope
    if(scope.lookupInCurrentScope(id)) return std::nullopt;


    // Find a unique name for the symbol within the current stop
    std::string uniqName = getUniqNameFor(scope, id); 

    Identifier * identifier = new Identifier(
        id, 
        uniqName, 
        scope.getIdentifier()
    ); 

    return scope.addDefinition(m, identifier, t, glob);
}

optional_ref<AliasSymbol> Context::addAlias(std::string id, const Type * t, Identifier * a)
{
    // Check that the exact same identifier doesn't already exist in the current scope
    if(this->lookupInCurrentScope(id)) return std::nullopt;


    // TODO: why are we doing uniqueName? I guess it shouldnt ever happen tho given lookup in currentScope?
    std::string uniqName = getUniqNameFor(currentScope.get(), id); 

    auto ans = currentScope.get().addSymbol(
        std::make_shared<AliasSymbol>(
            new Identifier(id, uniqName, currentScope.get().getIdentifier()),
            currentScope,
            t, 
            a
        )
    );

    if(ans)
        return *dynamic_cast<AliasSymbol *>(&ans.value().get());

    return std::nullopt; 
}

optional_ref<Symbol> Context::addAnonymousSymbol(std::string wantedId, const Type * t)
{
    std::string id = "#" + wantedId; // TODO: Better symbol to indicate anon. @ reserved for compiler internals
    // Check that the exact same identifier doesn't already exist in the current scope
    
    // Find a unique name for the symbol within the current stop
    id = getUniqNameFor(currentScope.get(), id);

    // Note: this is safe as we previously check that currentScope exists
    // FIXME: DETERMINE GLOB!!! SHOULD IT BE FALSE OR TRUE?
    return currentScope.get().addSymbol(std::make_shared<LocatableSymbol>(
        new Identifier(id, id, currentScope.get().getIdentifier()), t, false, currentScope));
}

optional_ref<DefinitionSymbol > Context::addAnonymousDefinition(std::string wantedId, const Type * t)
{
    std::string id = "#" + wantedId; // TODO: Better symbol to indicate anon. @ reserved for compiler internals
    // Check that the exact same identifier doesn't already exist in the current scope

    // Find a unique name for the symbol within the current stop
    id = getUniqNameFor(currentScope.get(), id);

    Identifier * identifier = new Identifier(id, id, currentScope.get().getIdentifier());

    // FIXME: DETERMINE GLOB!!! SHOULD IT BE FALSE OR TRUE?

    // Note: this is safe as we previously check that currentScope exists
    auto ans = currentScope.get().addSymbol(std::make_shared<DefinitionSymbol>(
        VisibilityModifier::PRIVATE,
        identifier, 
        t, 
        false,
        currentScope, 
        createNamespace(identifier)
    ));

    if(ans)
        return *dynamic_cast<DefinitionSymbol*>(&ans.value().get());

    return std::nullopt;
}

bool Context::removeSymbol(Symbol& symbol)
{
    optional_ref<Scope> opt = currentScope;
    bool foundStop = false; 

    while (opt && !foundStop)
    {
        Scope& scope = opt.value().get();

        if (!foundStop) // depth >= stop)
        {
            if(scope.removeSymbol(symbol))
                return true; 
        }
        else 
        {
            return false;
        }

        foundStop = scope.isStop(); 
        opt = scope.getParent();
    }

    return false;
}

optional_ref<Symbol> Context::lookupInAccessableScopes(std::string id)
{
    return currentScope.get().lookupInAccessableScopes(id); 
}

std::optional<std::pair<std::reference_wrapper<Symbol>, std::reference_wrapper<Scope>>> Context::lookupWithScope(std::string id)
{
    return currentScope.get().lookupWithScope(id);
}

std::vector<std::reference_wrapper<Symbol>> Context::getSymbols(int flags) //TODO: DO BETTER
{
    std::vector<std::reference_wrapper<Symbol>> ans;

    optional_ref<Scope> opt = currentScope;
    bool foundStop = false; 

    while (!foundStop)//depth >= stop)
    {
        Scope& scope = opt.value().get();

        auto toAdd = scope.getSymbols(flags);
        ans.insert(ans.end(), toAdd.begin(), toAdd.end());

        foundStop = scope.isStop(); 
        opt = scope.getParent();
    }

    return ans;
}

optional_ref<Symbol> Context::lookupInCurrentScope(std::string id)
{
    return currentScope.get().lookupInCurrentScope(id); 
}

// Directly from sample
std::string Context::toString() const
{
    std::ostringstream description;
    optional_ref<Scope> scopeOpt = currentScope; 
    std::cerr << "230" << std::endl;
    while(scopeOpt)
    {
        std::cerr << "233" << std::endl;
        Scope& scope = scopeOpt.value().get(); 
        std::cerr << "235" << std::endl;
        description << scope.toString(); 
        std::cerr << "237"  << scope.toString() << std::endl;
        scopeOpt = scope.getParent(); 
        std::cerr << "239" << std::endl;
    }
    // for (auto scope : scopes)
    // {
    //     description << scope->toString();
    // }
    return description.str();
}

optional_ref<Scope> Context::getOrProvisionScope(std::vector<std::string> steps, VisibilityModifier m)
{
    // Note bad variable names (we have two current scopes in here)
    std::reference_wrapper<Scope> seek = globalScope;

    for(std::string s : steps)
    {
        // FIXME: should this be lookupInCurrentScope?
        optional_ref<Symbol> symOpt = seek.get().lookupInAccessableScopes(s);
        if(!symOpt)
        {
            TypeModule * mod = new TypeModule();
            auto dsOpt = addDefinition(seek, m, s, mod, true);

            assert(dsOpt.has_value()); // We already checked conflicts

            seek = dsOpt.value().get().getInnerScope(); 
        }
        else if(auto ds = symbol_cast<DefinitionSymbol>(symOpt.value()); ds.has_value())
            seek = ds.value().get().getInnerScope(); 
        else 
        {
            return std::nullopt; 
        }
    }

    return seek; 
}
