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
        return {};
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
        return {};
    }

    Scope *current = currentScope.value();

    // Check to see if it exists
    std::string id = symbol->identifier;
    if (current->lookup(id))
    {
        // Change if you want to throw an exception
        // return {};
        return false;
    }
    return current->addSymbol(symbol);
}

bool Context::removeSymbol(Symbol *symbol) // FIXME: DO BETTER, VERIFY!
{
    std::optional<Scope *> opt = currentScope;

    int depth = scopes.size() - 1;
    int stop = this->getCurrentStop();
    while (opt)
    {
        Scope *scope = opt.value();

        if (depth >= stop || symbol->isDefinition || symbol->isGlobal) //FIXME: CONDITION SEEMS WRONG
        {
            // scope->er
            return scope->removeSymbol(symbol);
        }
        else 
        {
        // return false; //FIXME: THROW ERROR? //FIXME: SEE HOW RHETORIC HANGED BETWEEN THIS AND OTHER SIMILAR FN?

        }
        // return sym;

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
            return {};
        }

        depth--;
        opt = scope->getParent();
    }

    return {};
}

std::vector<Symbol *> Context::getAvaliableLinears()
{ // FOXME: DO BETTER
    std::vector<Symbol *> ans;

    std::optional<Scope *> opt = currentScope;

    int depth = scopes.size() - 1;
    int stop = this->getCurrentStop();
    while (depth >= stop)
    {
        Scope *scope = opt.value();

        for (auto s : scope->getRemainingLinearTypes())
        {
            ans.push_back(s); // FIXME: DO BETTER, USE INSERT!
        }
        depth--;
        opt = scope->getParent();
    }

    return ans;
}

void Context::deleteAvaliableLinears()
{ // FIXME: UNSAFE
    // FIXME: SEARCH FOR FOXME AND OTHER MISSPELLINGS OF FIXME
    //  std::vector<const Symbol *> ans;

    std::optional<Scope *> opt = currentScope;

    int depth = scopes.size() - 1;
    int stop = this->getCurrentStop();
    while (depth >= stop)
    {
        Scope *scope = opt.value();

        for (auto s : scope->getRemainingLinearTypes())
        {
            scope->removeSymbol(s);
        }
        depth--;
        opt = scope->getParent();
    }

    // return ans;
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
        //         return {};
        //     }
        //     opt = scope->getParent();
        // }
    }

    return {};
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