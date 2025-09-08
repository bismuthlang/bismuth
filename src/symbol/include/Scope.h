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
#include "TypeDefs.h"

#include <map>
#include <memory> // Smart pointers
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
    ~Scope() {
        std::cerr << "DELETING SCOPE!!!!!" << std::endl;
    }
    Scope(
        Identifier * n, 
        bool s
    )
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
    Scope(
        std::optional<std::reference_wrapper<Scope>> p, 
        Identifier * n, 
        bool s
    )
    {
        parent = p;
        id = n; 
        stop = s; 
    }

    Scope(
        std::optional<std::reference_wrapper<Scope>> p, 
        std::map<std::string, std::shared_ptr<Symbol>> syms, 
        std::set<std::shared_ptr<Symbol>> del,
        Identifier * n, 
        bool s
    )
    {
        parent = p;
        symbols = syms;
        deletedSymbols = del;
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
    optional_ref<Symbol> addSymbol(std::shared_ptr<Symbol> symbol);

    bool removeSymbol(const Symbol& symbol);

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
    optional_ref<Symbol> lookupInCurrentScope(std::string id);

    optional_ref<Symbol> lookupInAccessableScopes(std::string id);

    std::optional<std::pair<std::reference_wrapper<Symbol>, std::reference_wrapper<Scope>>>  lookupWithScope(std::string id);

    Scope * createNamespace(Identifier * id);

    optional_ref<DefinitionSymbol> addDefinition(VisibilityModifier m, Identifier * identifier, const Type * t, bool glob);

    /**
     * @brief Get the Parent object
     *
     * @return std::optional<Scope*> Empty no parent; present with value if has parent
     */
    std::optional<std::reference_wrapper<Scope>> getParent() { return parent; }

    void setParent(Scope& scope) { parent = scope; } // FIXME: MAKE PRIVATE?

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

    
    std::vector<std::reference_wrapper<Symbol>> getSymbols(int flags)
    {
        // Create an answer vector
        std::vector<std::reference_wrapper<Symbol>> ans;

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
                        ans.push_back(*item.second);
                }
            }

            if (include_linear && item.second->getType()->isLinear() && !(item.second->getScopedIdentifier() == "@RETURN"))
            {
                if (const TypeChannel *inf = dynamic_cast<const TypeChannel *>(item.second->getType()))
                {
                    if (
                        (include_complete || !inf->getProtocol()->isComplete()) &&
                        (include_guarded || !inf->getProtocol()->isGuarded()))
                        ans.push_back(*item.second);
                }
                else
                {
                    ans.push_back(*item.second);
                }
            }
        }

        return ans;
    }

    std::map<std::string, std::shared_ptr<Symbol>> copySymbols()
    {
        map_to_shared<std::string, Symbol> ans;

        for (auto itr : symbols)
        {
            ans.emplace(
                itr.first, 
                itr.second->getCopy()
            );
        }

        return ans;
    }

    shared_set<Symbol> copyDeletedSymbols() 
    {
        shared_set<Symbol> ans;
        for(auto itr : deletedSymbols)
        {
            ans.insert(itr->getCopy());
        }
        return ans;
    }

    Identifier * getIdentifier() { return id; }

    // std::string getName() {
    //     return nameGenerator(); // TODO: Do better & use mangler 
    // }


    bool isStop() { return stop; }


    Scope * copyToStop() {
      std::optional<std::reference_wrapper<Scope>> scopeOpt = *this;
      std::optional<Scope *> ans = std::nullopt; 
      std::optional<Scope *> prev = std::nullopt;

      while(scopeOpt)
      {
        Scope& scope = scopeOpt.value().get(); 

        Scope * scopeCpy = new Scope(std::nullopt, scope.copySymbols(), scope.copyDeletedSymbols(), scope.getIdentifier(), scope.isStop());

        scopeCpy->setId(10 * scope.getId());

        if(!ans)
        {
          ans = scopeCpy;
        }

        if(prev)
        {
          prev.value()->setParent(*scopeCpy); 
        }

        if(scope.isStop())
        {
            if(scope.getParent())
            {
                scopeCpy->setParent(scope.getParent().value());
            }
            return ans.value(); 
        }

        prev = scopeCpy; 
        scopeOpt = scope.getParent(); 
      }

        return ans.value(); 
    }

private:
    int scopeId = -1;
    std::optional<std::reference_wrapper<Scope>> parent = std::nullopt;
    std::map<std::string, std::shared_ptr<Symbol>> symbols;
    std::set<std::shared_ptr<Symbol>> deletedSymbols;

    Identifier * id; 

    bool stop; // FIXME: Switch to visibility modifiers?
};
