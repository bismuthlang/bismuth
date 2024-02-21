/**
 * @file Context.h
 * @author Alex Friedman (ahfriedman.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "Scope.h"
#include <vector>
#include <optional>

#include <stack>

class Context {
  private: 
    std::map<std::string, uint32_t> * nameCounter; 
    Scope * globalScope; 

  public:
    Context(std::map<std::string, uint32_t> * nc) 
      : nameCounter(nc) 
    {
      // Maybe add a global scope for all files? 
      enterScope();
      globalScope = getCurrentScope().value(); 
    }

    /**
     * @brief Enter a new scope
     * 
     * @return Scope& the scope we entered
     */
    Scope& enterScope(std::optional<Identifier *> idOpt = std::nullopt) { //std::string id, std::optional<std::function<std::string()>> meta = std::nullopt) {
      return enterScope(false, idOpt); //id, meta);
    }

    Scope& enterScope(bool insertStop, std::optional<Identifier *> idOpt  = std::nullopt); // std::string id, std::optional<std::function<std::string()>> meta = std::nullopt);
    
    Scope * createNamespace(Identifier * id);

    void enterScope(Scope * scope);
    /**
     * @brief Exit the current scope and move up one level
     * 
     * @return std::optional<Scope*> Returns empty if no parent scope to enter; otherwise returns last scope. 
     */
    std::optional<Scope*> exitScope();

    /**
     * @brief Add a symbol to the current scope
     * 
     * @param symbol The symbol to add
     * @return true if successful
     * @return false if unsuccessful (ie, name already bound to another symbol)
     */
    std::optional<Symbol *> addSymbol(std::string id, const Type * t, bool glob); // Symbol* symbol);

    std::optional<DefinitionSymbol *> addDefinition(std::string id, const Type * t, bool glob); 

    std::optional<AliasSymbol *> addAlias(std::string id, const Type * t, Identifier * a);//Symbol * a);

    std::optional<Symbol *> addAnonymousSymbol(std::string id, const Type * t); 
    std::optional<DefinitionSymbol *> addAnonymousDefinition(std::string id, const Type * t); 

    /**
     * @brief Removes a symbol from the scope
     * 
     * @param symbol 
     */
    bool removeSymbol(Symbol* symbol);
    
    /**
     * @brief Lookup a symbol across all scopes returning the first definition found
     * 
     * @param id The symbol name to lookup
     * @return std::optional<Symbol*>  Empty if symbol not found; present with value if found. 
     */
    std::optional<Symbol*> lookup(std::string id);

    std::optional<std::pair<Symbol *, Scope *>> lookupWithScope(std::string id); 

    std::vector<Symbol *> getSymbols(int flags);

    /**
     * @brief Lookup a symbol only in the current scope. 
     * 
     * @param id The symbol name to lookup
     * @return std::optional<Symbol*>  Empty if symbol not found; present with value if found. 
     */
    std::optional<Symbol*> lookupInCurrentScope(std::string id);

    /****************************************
     * Miscellaneous (useful for testing)
     ****************************************/

    /**
     * @brief Get the Current Scope object
     * 
     * @return std::optional<Scope*> 
     */
    std::optional<Scope*> getCurrentScope() { 
      if(currentScope) return std::optional<Scope*> {currentScope.value()};
      return std::optional<Scope*>{}; 
    }

    /**
     * @brief Gets the number of scopes
     * 
     * @return int 
     */
    int scopeCount() { return scopeNumber; } // return scopes.size(); }
    std::string toString() const;

    /**
     * @brief Determines if the current scope is the global scope
     * 
     * @return true if current scope is the global scope
     * @return false if the current scope is not the global scope
     */
    bool isGlobalScope() {
      // if(scopes.size() == 0) return false; 

      if(!currentScope) return false; 

      return !currentScope.value()->getParent().has_value(); //->getId() == 0; 
    }

    std::optional<Scope *> getOrProvisionScope(std::vector<std::string> steps);
    

    Scope * getGlobalScope() { return globalScope; }
  private:
    std::vector<Scope*> scopes;
    std::optional<Scope*> currentScope = {}; 
    int scopeNumber = 0;

    std::string getUniqNameFor(Scope * parent, std::string inScope) {
      // TODO: not sure if getting FQN here will break some stuff wrt generics...
      std::string id = parent->getIdentifier()->getFullyQualifiedName() + "::" + inScope;
      std::cout << "Find " << id << std::endl; 
      auto itr = nameCounter->find(id);
      if(itr == nameCounter->end())
      {
          nameCounter->insert({id, 0});
          return inScope;
      }
      std::ostringstream nextName; 
      nextName << inScope << "." << itr->second; 
      nameCounter->insert({id, itr->second++});
      return nextName.str(); 
    }
};