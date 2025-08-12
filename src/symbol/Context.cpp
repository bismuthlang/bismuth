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

std::optional<std::reference_wrapper<Scope>> Context::exitScope()
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

std::optional<Symbol *> Context::addSymbol(std::string id, const Type * t, bool glob)
{
    // Check that the exact same identifier doesn't already exist in the current scope
    if(this->lookupInCurrentScope(id)) return std::nullopt;


    // Find a unique name for the symbol within the current stop
    std::string uniqName = getUniqNameFor(currentScope, id); 


    // Note: this is safe as we previously check that currentScope exists
    return currentScope.get().addSymbol(
        new LocatableSymbol(
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

std::optional<DefinitionSymbol *> Context::addDefinition(Scope & scope, VisibilityModifier m, std::string id, const Type * t, bool glob)
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

std::optional<AliasSymbol *> Context::addAlias(std::string id, const Type * t, Identifier * a)
{
    // Check that the exact same identifier doesn't already exist in the current scope
    if(this->lookupInCurrentScope(id)) return std::nullopt;


    // TODO: why are we doing uniqueName? I guess it shouldnt ever happen tho given lookup in currentScope?
    std::string uniqName = getUniqNameFor(currentScope.get(), id); 

    AliasSymbol * alias = new AliasSymbol(
        new Identifier(id, uniqName, currentScope.get().getIdentifier()),
        currentScope,
        t, 
        a
    );

    if(currentScope.get().addSymbol(alias))
        return alias; 

    delete alias; 

    return std::nullopt; 
}

std::optional<Symbol *> Context::addAnonymousSymbol(std::string wantedId, const Type * t)
{
    std::string id = "#" + wantedId; // TODO: Better symbol to indicate anon. @ reserved for compiler internals
    // Check that the exact same identifier doesn't already exist in the current scope
    
    // Find a unique name for the symbol within the current stop
    id = getUniqNameFor(currentScope.get(), id);

    // Note: this is safe as we previously check that currentScope exists
    // FIXME: DETERMINE GLOB!!! SHOULD IT BE FALSE OR TRUE?
    return currentScope.get().addSymbol(new LocatableSymbol(
        new Identifier(id, id, currentScope.get().getIdentifier()), t, false, currentScope));
}

std::optional<DefinitionSymbol *> Context::addAnonymousDefinition(std::string wantedId, const Type * t)
{
    std::string id = "#" + wantedId; // TODO: Better symbol to indicate anon. @ reserved for compiler internals
    // Check that the exact same identifier doesn't already exist in the current scope

    // Find a unique name for the symbol within the current stop
    id = getUniqNameFor(currentScope.get(), id);

    Identifier * identifier = new Identifier(id, id, currentScope.get().getIdentifier());

    // FIXME: DETERMINE GLOB!!! SHOULD IT BE FALSE OR TRUE?
    DefinitionSymbol * ds = new DefinitionSymbol(
        VisibilityModifier::PRIVATE,
        identifier, 
        t, 
        false,
        currentScope, 
        createNamespace(identifier)
    ); 

    // Note: this is safe as we previously check that currentScope exists
    if(currentScope.get().addSymbol(ds))
        return ds; 

    delete ds; 

    return std::nullopt;
}

bool Context::removeSymbol(Symbol *symbol)
{
    std::optional<std::reference_wrapper<Scope>> opt = currentScope;
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

std::optional<Symbol *> Context::lookupInAccessableScopes(std::string id)
{
    return currentScope.get().lookupInAccessableScopes(id); 
}

std::optional<std::pair<Symbol *, std::reference_wrapper<Scope>>> Context::lookupWithScope(std::string id)
{
    return currentScope.get().lookupWithScope(id);
}

std::vector<Symbol *> Context::getSymbols(int flags) //TODO: DO BETTER
{
    std::vector<Symbol *> ans;

    std::optional<std::reference_wrapper<Scope>> opt = currentScope;
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

std::optional<Symbol *> Context::lookupInCurrentScope(std::string id)
{
    return currentScope.get().lookupInCurrentScope(id); 
}

// Directly from sample
std::string Context::toString() const
{
    std::ostringstream description;
    std::optional<std::reference_wrapper<Scope>> scopeOpt = currentScope; 
    while(scopeOpt)
    {
        Scope& scope = scopeOpt.value().get(); 
        description << scope.toString(); 
        scopeOpt = scope.getParent(); 
    }
    // for (auto scope : scopes)
    // {
    //     description << scope->toString();
    // }
    return description.str();
}

std::optional<std::reference_wrapper<Scope>> Context::getOrProvisionScope(std::vector<std::string> steps, VisibilityModifier m)
{
    // Note bad variable names (we have two current scopes in here)
    std::reference_wrapper<Scope> seek = globalScope;

    for(std::string s : steps)
    {
        // FIXME: should this be lookupInCurrentScope?
        std::optional<Symbol *> symOpt = seek.get().lookupInAccessableScopes(s);
        if(!symOpt)
        {
            TypeModule * mod = new TypeModule();
            std::optional<DefinitionSymbol *> dsOpt = addDefinition(seek, m, s, mod, true);

            assert(dsOpt.has_value()); // We already checked conflicts

            seek = dsOpt.value()->getInnerScope(); 
        }
        else if(DefinitionSymbol * ds = dynamic_cast<DefinitionSymbol *>(symOpt.value()))
            seek = ds->getInnerScope(); 
        else 
        {
            return std::nullopt; 
        }
    }

    return seek; 
}
