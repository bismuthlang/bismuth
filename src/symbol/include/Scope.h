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

class Scope
{
public:
    Scope()
    {
        // By default, we set parent to be empty
    }

    /**
     * @brief Construct a new Scope object
     *
     * @param p The parent to the current scope
     */
    Scope(std::optional<Scope *> p)
    {
        parent = p;
    }

    /**
     * @brief Add a symbol to the current scope
     *
     * @param symbol The scope to add to the scope
     * @return true If successful
     * @return false If this could not be done (ie, due to a redeclaration)
     */
    bool addSymbol(Symbol *symbol);

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

    /**
     * @brief Get the Uninferred objects in the current scope
     *
     * @return std::vector<const Symbol*> A vector of all the uninferred symbols in the scope
     */
    std::vector<const Symbol *> getUninferred()
    {
        // Create an answer vector
        std::vector<const Symbol *> ans;

        // Iterate through the symbols looking for TypeInfers which have not been inferred
        for (auto item : symbols)
        {
            if (const TypeInfer *inf = dynamic_cast<const TypeInfer *>(item.second->type))
            {
                if (!inf->hasBeenInferred())
                    ans.push_back(item.second);
            }
        }

        return ans;
    }

    // FIXME: DO BETTER
    std::vector<Symbol *> getRemainingLinearTypes(bool include_complete=false)
    {
        // Create an answer vector
        std::vector<Symbol *> ans;

        // Iterate through the symbols looking for TypeInfers which have not been inferred
        for (auto item : symbols)
        {
            if (const TypeChannel *inf = dynamic_cast<const TypeChannel *>(item.second->type))
            {
                if ((include_complete || !inf->getProtocol()->isComplete()) && !inf->getProtocol()->isGuarded())
                    ans.push_back(item.second);
            }
        }

        return ans;
    }

private:
    int scopeId = -1;
    std::optional<Scope *> parent = {};
    std::map<std::string, Symbol *> symbols;
};
