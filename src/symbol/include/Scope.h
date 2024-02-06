#pragma once
/**
 * @file Scope.h
 * @author Alex Friedman (ahfriedman.com)
 * @brief Scope header file
 * @version 0.1
 * @date 2022-09-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Symbol.h"
#include <map>
#include <optional>
// #include <assert.h>

enum SymbolLookupFlags
{
    NON_LINEAR = 1,
    PENDING_LINEAR = 2,
    GUARDED_LINEAR = 4,
    COMPLETE_LINEAR = 8,
    UNINFERRED_TYPE = 16,
};

class Scope
{
public:
    Scope(Identifier * n, bool s)
        : id(n)
        , stop(s)
    {
        // By default, we set parent to be empty
    }

    /**
     * @brief Construct a new Scope object
     *
     * @param p The parent to the current scope
     */
    Scope(std::optional<Scope *> p, Identifier * n, bool s)
    {
        parent = p;
        id = n; 
        stop = s; 
    }

    Scope(std::optional<Scope *> p, std::map<std::string, Symbol *> syms, Identifier * n, bool s)
    {
        parent = p;
        symbols = syms;
        id = n; 
        stop = s; 
    }

    /**
     * @brief Add a symbol to the current scope
     *
     * @param symbol The scope to add to the scope
     * @return true If successful
     * @return false If this could not be done (ie, due to a redeclaration)
     */
    std::optional<Symbol *> addSymbol(Symbol *symbol);

    bool removeSymbol(const Symbol *symbol);

    /**
     * @brief Add a symbol to the current scope
     *
     * @param id Name of the symbol to construct
     * @param t Type of the symbol to construct
     * @return true If successful
     * @return false If this could not be done (ie, due to a redeclaration)
     */
    // bool addSymbol(std::string id, Type *t);

    /**
     * @brief Looks up a symbol in the current scope
     *
     * @param id Name of the symbol
     * @return std::optional<Symbol*> Empty if could not be found; present with value if symbol found.
     */
    std::optional<Symbol *> lookup(std::string id);

    /**
     * @brief Get the Parent object
     *
     * @return std::optional<Scope*> Empty no parent; present with value if has parent
     */
    std::optional<Scope *> getParent() { return parent; }

    void setParent(Scope * scope) { parent = scope; } // FIXME: MAKE PRIVATE?

    /**
     * @brief Set the Id object
     *
     * @param id
     */
    void setId(int id) { scopeId = id; }

    /**
     * @brief Get the Id object
     *
     * @return int
     */
    int getId() { return scopeId; }

    /**
     * @brief Gets a string representation of the scope. Nice for debugging.
     *
     * @return std::string
     */
    std::string toString() const;

    
    std::vector<Symbol *> getSymbols(int flags)
    {
        // Create an answer vector
        std::vector<Symbol *> ans;

        // if(flags & SymbolLookupFlags::NON_LINEAR)
        // {
        //     ans.insert(ans.end(),)
        // }
        bool include_complete = flags & SymbolLookupFlags::COMPLETE_LINEAR;
        bool include_guarded = flags & SymbolLookupFlags::GUARDED_LINEAR;
        bool include_pending = flags & SymbolLookupFlags::PENDING_LINEAR;

        bool include_linear = include_complete || include_guarded || include_pending;

        bool include_uninferred = flags & SymbolLookupFlags::UNINFERRED_TYPE;
        // Iterate through the symbols looking for TypeInfers which have not been inferred
        for (auto item : symbols)
        {
            if (include_uninferred)
            {
                if (const TypeInfer *inf = dynamic_cast<const TypeInfer *>(item.second->getType()))
                {
                    if (!inf->hasBeenInferred())
                        ans.push_back(item.second);
                }
            }

            if (include_linear && item.second->getType()->isLinear() && !(item.second->getScopedIdentifier() == "@RETURN"))
            {
                if (const TypeChannel *inf = dynamic_cast<const TypeChannel *>(item.second->getType()))
                {
                    if (
                        (include_complete || !inf->getProtocol()->isComplete()) &&
                        (include_guarded || !inf->getProtocol()->isGuarded()))
                        ans.push_back(item.second);
                }
                else
                {
                    ans.push_back(item.second);
                }
            }
        }

        return ans;
    }

    std::map<std::string, Symbol *> copySymbols()
    {
        std::map<std::string, Symbol *> ans;

        for (auto itr : symbols)
        {
            if(itr.second->isDefinition())
                ans.insert({
                    itr.first, 
                    new DefinitionSymbol(*dynamic_cast<DefinitionSymbol *>(itr.second)) // TODO: not exactly the safest, but should be fine as its the only current way to get definition symbols 
                });
            else
                ans.insert({itr.first, new Symbol(*itr.second)});
        }

        return ans;
    }

    Identifier * getIdentifier() { return id; }

    // std::string getName() {
    //     return nameGenerator(); // TODO: Do better & use mangler 
    // }


    bool isStop() { return stop; }


    Scope * copyToStop() {
      std::optional<Scope *> scopeOpt = this;
      std::optional<Scope *> ans = std::nullopt; 
      std::optional<Scope *> prev = std::nullopt;

      while(scopeOpt)
      {
        Scope * scope = scopeOpt.value(); 

        Scope * scopeCpy = new Scope(std::nullopt, scope->copySymbols(), scope->getIdentifier(), scope->isStop());

        scopeCpy->setId(10 * scope->getId());

        if(!ans)
        {
          ans = scopeCpy;
        }

        if(prev)
        {
          prev.value()->setParent(scopeCpy); 
        }

        if(scope->isStop())
        {
            if(scope->getParent())
            {
                scopeCpy->setParent(scope->getParent().value());
            }

            // std::cout << "211 ---- COPIED SCOPE " << scope->toString() << " as ---" << scopeCpy->toString() << std::endl; 
            return ans.value(); 
        }
        
        
        // std::cout << "219 ---- COPIED SCOPE " << scope->toString() << " as ---" << scopeCpy->toString() << std::endl; 

        prev = scopeCpy; 
        scopeOpt = scope->getParent(); 
      }

        return ans.value(); 
    }

private:
    int scopeId = -1;
    std::optional<Scope *> parent = {};
    std::map<std::string, Symbol *> symbols;

    Identifier * id; 

    bool stop; // FIXME: Switch to visibility modifiers?
};
