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
    std::stack<std::map<std::string, uint32_t>> * nameCounter; 

  public:
    Context(){
      nameCounter = new std::stack<std::map<std::string, uint32_t>>(); 
      nameCounter->push(std::map<std::string, uint32_t>());};

    /**
     * @brief Enter a new scope
     * 
     * @return Scope& the scope we entered
     */
    Scope& enterScope(std::optional<Identifier *> idOpt = std::nullopt) { //std::string id, std::optional<std::function<std::string()>> meta = std::nullopt) {
      return enterScope(false, idOpt); //id, meta);
    }

    Scope& enterScope(bool insertStop, std::optional<Identifier *> idOpt  = std::nullopt); // std::string id, std::optional<std::function<std::string()>> meta = std::nullopt);
    
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
    std::optional<Symbol *> addSymbol(std::string id, const Type * t, bool d, bool glob); // Symbol* symbol);

    std::optional<Symbol *> addAnonymousSymbol(std::string id, const Type * t, bool d); 

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
    int scopeCount() { return scopes.size(); }
    std::string toString() const;

    /**
     * @brief Determines if the current scope is the global scope
     * 
     * @return true if current scope is the global scope
     * @return false if the current scope is not the global scope
     */
    bool isGlobalScope() {
      if(scopes.size() == 0) return false; 

      if(!currentScope) return false; 

      return currentScope.value()->getId() == 0; 
    }

    int getCurrentStop() {
      return getCurrentStop(stops);
    }

    std::optional<Context> getCopy() {
      std::map<Scope*, Scope*> copies; 
      std::vector<Scope*> newScopes; 

      for(Scope * orig : scopes)
      {
        std::optional<Scope *> optParent = orig->getParent();

        if(!optParent)
        {
          Scope * ans = new Scope({}, orig->copySymbols(), orig->getIdentifier()); // FIXME SWITCH TO COPY CONSTRUCTOR!
          ans->setId(orig->getId());
          copies.insert({orig, ans});
          newScopes.push_back(ans); 
        }
        else if(copies.find(optParent.value()) != copies.end())
        {
          Scope * ans = new Scope(copies[optParent.value()], orig->copySymbols(), orig->getIdentifier());
          ans->setId(orig->getId());
          copies.insert({orig, ans});
          newScopes.push_back(ans); 
        }
        else 
        {
          return std::nullopt; 
        }
      }

      Context c; 
      c.scopes = newScopes; 
      if(currentScope)
      {
        c.currentScope = copies[currentScope.value()];
      }
      // c.currentScope = currentScope ? copies[currentScope.value()] : std::nullopt; 
      c.scopeNumber = scopeNumber;
      c.stops = stops; 
      c.nameCounter = nameCounter;
      return c; 
    }

  private:
    std::vector<Scope*> scopes;
    std::optional<Scope*> currentScope = {}; 
    int scopeNumber = 0;

    std::stack<int> stops; 

    int getCurrentStop(std::stack<int> st)
    {
      return st.size() == 0 ? 0 : st.top(); 
    }


    std::string getUniqNameFor(std::string id) {
      auto itr = nameCounter->top().find(id);
      if(itr == nameCounter->top().end())
      {
          nameCounter->top().insert({id, 0});
          return id;
      }
      std::ostringstream nextName; 
      nextName << id << "." << itr->second; 
      nameCounter->top().insert({id, itr->second++});
      return nextName.str(); 
    }
};