#include "Context.h"

// enum InsertStopType
// {
//     NONE,
//     LINEAR,
//     GLOBAL
// };

Scope &Context::enterScope(bool insertStop, std::function<std::string()> n)
{
    // This is safe because we use optionals
    Scope *next = new Scope(this->currentScope, n);
    next->setId(this->scopeNumber++);

    this->currentScope = std::optional<Scope *>{next};
    scopes.push_back(next);

    if (insertStop)
        stops.push(scopes.size() - 1);

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
    }

    return std::optional<Scope *>{last};
}

std::optional<Symbol *> Context::addSymbol(std::string id, const Type * t, bool d, bool glob)
{
    // Check that the exact same identifier doesn't already exist in the current scope
    if(!currentScope || this->lookupInCurrentScope(id)) return std::nullopt;

    // Find a unique name for the symbol within the current stop
    // TODO: do this more efficiency! (Also note this may break if multiple contexts!!!)
    uint32_t idNum = 0; 
    std::string uniqName = id; 

    while(this->lookup(uniqName)) {
        std::ostringstream nxtName;
        nxtName << id << "." << idNum; // TODO: do better name mangling, make it an interface---one of which follows C spec
        idNum++; 
        uniqName = nxtName.str(); 
    }

    // Note: this is safe as we previously check that currentScope exists
    return currentScope.value()->addSymbol(new Symbol(id, t, d, glob, uniqName, currentScope.value()));
}

std::optional<Symbol *> Context::addAnonymousSymbol(std::string wantedId, const Type * t, bool d)
{
    std::string id = "#" + wantedId; // TODO: Better symbol to indicate anon. @ reserved for compiler internals
    // Check that the exact same identifier doesn't already exist in the current scope
    if(!currentScope) return std::nullopt;
    // Find a unique name for the symbol within the current stop
    // TODO: do this more efficiency! (Also note this may break if multiple contexts!!!)
    uint32_t idNum = 0; 
    while(this->lookup(id)) {
        std::ostringstream nxtName;
        nxtName << "#" << wantedId << "." << idNum; // TODO: do better name mangling, make it an interface---one of which follows C spec
        idNum++;
        id = nxtName.str(); 
    }

    std::cout << "ANON FOUND " << id << std::endl; 
    std::cout << "CURR SCOPE? " << currentScope.has_value() << std::endl; 
    // Note: this is safe as we previously check that currentScope exists
    // FIXME: DETERMINE GLOB!!! SHOULD IT BE FALSE OR TRUE?
    return currentScope.value()->addSymbol(new Symbol(id, t, d, false, id, currentScope.value()));
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