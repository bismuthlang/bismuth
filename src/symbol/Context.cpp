#include "Context.h"

enum InsertStopType
{
    NONE,
    LINEAR,
    GLOBAL
};

Scope &Context::enterScope(bool insertStop)
{
    // This is safe because we use optionals
    Scope *next = new Scope(this->currentScope);
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

bool Context::addSymbol(Symbol *symbol)
{
    if (!currentScope)
    {
        return false;
    }

    Scope *current = currentScope.value();

    // Check to see if it exists
    std::string id = symbol->identifier;
    if (current->lookup(id))
    {
        // Change if you want to throw an exception
        // return std::nullopt;
        return false;
    }
    return current->addSymbol(symbol);
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
            if (depth >= stop || sym.value()->isDefinition || sym.value()->isGlobal)
                return sym;
            return std::nullopt;
        }

        depth--;
        opt = scope->getParent();
    }

    return std::nullopt;
}

std::vector<Symbol *> Context::getAvailableLinears(bool include_complete) //TODO: DO BETTER
{
    std::vector<Symbol *> ans;

    std::optional<Scope *> opt = currentScope;

    int depth = scopes.size() - 1;
    int stop = this->getCurrentStop();
    while (depth >= stop)
    {
        Scope *scope = opt.value();

        auto toAdd = scope->getRemainingLinearTypes(include_complete);
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