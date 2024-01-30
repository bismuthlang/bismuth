#include "Context.h"

// enum InsertStopType
// {
//     NONE,
//     LINEAR,
//     GLOBAL
// };

Scope &Context::enterScope(bool insertStop, std::optional<Identifier *> idOpt)  //std::string id, std::optional<std::function<std::string()>> meta)
{
    // This is safe because we use optionals
    Identifier * id = [this, idOpt](){
        if(idOpt) return idOpt.value(); 

        std::optional<Identifier *> parentOpt = this->currentScope ? (std::optional<Identifier *>) this->currentScope.value()->getIdentifier() : (std::optional<Identifier *>) std::nullopt; 
        Identifier * i = new Identifier("", "", parentOpt);
        // i->meta = meta;

        return i; 
        
    }(); 



    Scope *next = new Scope(this->currentScope, id);
    next->setId(this->scopeNumber++);

    this->currentScope = std::optional<Scope *>{next};
    scopes.push_back(next);

    if (insertStop)
    {
        stops.push(scopes.size() - 1);
        nameCounter->push(std::map<std::string, uint32_t>());
    }

    return *next;
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
    scopes.pop_back(); // FIXME: Delete last element in vector? -> We don't do this because it breaks the scope count

    int depth = scopes.size();
    if (getCurrentStop() == depth && getCurrentStop() != 0)
    {
        stops.pop();
        nameCounter->pop();
    }

    return std::optional<Scope *>{last};
}

std::optional<Symbol *> Context::addSymbol(std::string id, const Type * t, bool d, bool glob)
{
    // Check that the exact same identifier doesn't already exist in the current scope
    if(!currentScope || this->lookupInCurrentScope(id)) return std::nullopt;


    // Find a unique name for the symbol within the current stop
    uint32_t idNum = 0; 
    std::string uniqName = getUniqNameFor(id); 

    // std::cout << "END W/ " << uniqName << " for " << id << std::endl; 

    // std::cout << this->toString() << std::endl;  // FIXME: THIS SEGFUALTS!
    // Note: this is safe as we previously check that currentScope exists
    return currentScope.value()->addSymbol(new Symbol(new Identifier(
        id, 
        uniqName, 
        currentScope.value()->getIdentifier()
    ), t, d, glob, currentScope.value()));
}

std::optional<Symbol *> Context::addAnonymousSymbol(std::string wantedId, const Type * t, bool d)
{
    std::string id = "#" + wantedId; // TODO: Better symbol to indicate anon. @ reserved for compiler internals
    // Check that the exact same identifier doesn't already exist in the current scope
    if(!currentScope) return std::nullopt;
    // Find a unique name for the symbol within the current stop
    id = getUniqNameFor(id);

    // Note: this is safe as we previously check that currentScope exists
    // FIXME: DETERMINE GLOB!!! SHOULD IT BE FALSE OR TRUE?
    return currentScope.value()->addSymbol(new Symbol(
        new Identifier(id, id, currentScope.value()->getIdentifier()), t, d, false, currentScope.value()));
}

bool Context::removeSymbol(Symbol *symbol)
{
    std::optional<Scope *> opt = currentScope;

    int depth = scopes.size() - 1;
    int stop = this->getCurrentStop();
    while (opt)
    {
        Scope *scope = opt.value();

        if (depth >= stop)
        {
            if( scope->removeSymbol(symbol))
                return true; 
            // return scope->removeSymbol(symbol);
        }
        else 
        {
            return false;
        }

        depth--;
        opt = scope->getParent();
    }

    return false;
}

std::optional<Symbol *> Context::lookup(std::string id)
{
    std::optional<Scope *> opt = currentScope;

    int depth = scopes.size() - 1;
    int stop = this->getCurrentStop();
    while (opt)
    {
        Scope *scope = opt.value();

        std::optional<Symbol *> sym = scope->lookup(id);
        if (sym)
        {
            if (depth >= stop || sym.value()->isDefinition() || sym.value()->isGlobal())
                return sym;
            return std::nullopt;
        }

        depth--;
        opt = scope->getParent();
    }

    return std::nullopt;
}

std::vector<Symbol *> Context::getSymbols(int flags) //TODO: DO BETTER
{
    std::vector<Symbol *> ans;

    std::optional<Scope *> opt = currentScope;

    int depth = scopes.size() - 1;
    int stop = this->getCurrentStop();
    while (depth >= stop)
    {
        Scope *scope = opt.value();

        auto toAdd = scope->getSymbols(flags);
        ans.insert(ans.end(), toAdd.begin(), toAdd.end());

        depth--;
        opt = scope->getParent();
    }

    return ans;
}

std::optional<Symbol *> Context::lookupInCurrentScope(std::string id)
{
    std::optional<Scope *> opt = currentScope;
    if (opt)
    {
        Scope *scope = opt.value();
        std::optional<Symbol *> sym = scope->lookup(id);
        if (sym)
            return sym;
        // opt = scope->getParent();
        // while (opt)
        // {
        //     scope = opt.value();
        //     std::optional<Symbol *> sym = scope->lookup(id);
        //     if (sym)
        //     {
        //         // std::cout << sym.value()->toString() << " " << depth << " >= " << stop  << " || " << sym.value()->isDefinition << std::endl;
        //         if (sym.value()->isDefinition)
        //             return sym;
        //         return std::nullopt;
        //     }
        //     opt = scope->getParent();
        // }
    }

    return std::nullopt;
}

// Directly from sample
std::string Context::toString() const
{
    std::ostringstream description;
    for (auto scope : scopes)
    {
        description << scope->toString();
    }
    return description.str();
}