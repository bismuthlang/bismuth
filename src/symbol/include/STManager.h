/**
 * @file STManager.h
 * @author Alex Friedman (ahfriedman.com)
 * @brief
 * @version 0.1
 * @date 2022-09-09
 *
 * @copyright Copyright (c) 2022
 *
 *
 * Modified from starter code.
 */
#pragma once
#include "Context.h"
#include <vector>
#include <optional>

#include <stack>

enum StopType
{
  NONE,
  GLOBAL
};

enum ScopeType
{
  LINEAR_SCOPE,
  NON_LINEAR_SCOPE
};

typedef std::pair<ScopeType, Symbol *> SymbolContext;

class STManager
{
public:
  STManager(){};

  /**
   * @brief Enter a new scope
   *
   * @return Scope& the scope we entered
   */
  void enterScope(StopType stopType)
  {

    linearContext.enterScope(stopType == GLOBAL);
    dangerContext.enterScope(stopType == GLOBAL);
  }

  /**
   * @brief Exit the current scope and move up one level
   *
   * @return std::optional<Scope*> Returns empty if no parent scope to enter; otherwise returns last scope.
   */
  std::pair<std::optional<Scope *>, std::optional<Scope *>> exitScope()
  {
    return {dangerContext.exitScope(), linearContext.exitScope()};
  }

  /**
   * @brief Add a symbol to the current scope
   *
   * @param symbol The symbol to add
   * @return true if successful
   * @return false if unsuccessful (ie, name already bound to another symbol)
   */
  bool addSymbol(Symbol *symbol)
  {
    if (symbol->type->isLinear() &&
        symbol->getIdentifier() != "@RETURN") // Latter condition needed to prevent return types from being tracked as linear. see getBinaryStreamFor in adder5. PLAN: handle this better, should probably make return a linear type in general to make it so that way we can have better dead code detection/elim.
      return linearContext.addSymbol(symbol);
    return dangerContext.addSymbol(symbol);
  }

  bool removeSymbol(Symbol *symbol)
  {
    return linearContext.removeSymbol(symbol);
  }

  /**
   * @brief Lookup a symbol across all scopes returning the first definition found
   *
   * @param id The symbol name to lookup
   * @return std::optional<Symbol*>  Empty if symbol not found; present with value if found.
   */
  std::optional<SymbolContext> lookup(std::string id)
  {
    std::optional<Symbol *> opt = linearContext.lookup(id);
    if (opt)
      return (SymbolContext){LINEAR_SCOPE, opt.value()};

    opt = dangerContext.lookup(id);
    if (opt)
      return (SymbolContext){NON_LINEAR_SCOPE, opt.value()};

    return std::nullopt;
  }

  /**
   * @brief Lookup a symbol only in the current scope.
   *
   * @param id The symbol name to lookup
   * @return std::optional<Symbol*>  Empty if symbol not found; present with value if found.
   */
  std::optional<Symbol *> lookupInCurrentScope(std::string id)
  {
    std::optional<Symbol *> opt1 = linearContext.lookupInCurrentScope(id);
    if (opt1)
      return opt1;
    return dangerContext.lookupInCurrentScope(id);
  }

  /****************************************
   * Miscellaneous (useful for testing)
   ****************************************/

  /**
   * @brief Get the Current Scope object
   *
   * @return std::optional<Scope*>
   */
  std::optional<Scope *> getCurrentScope()
  {
    return dangerContext.getCurrentScope();
  }

  std::vector<Symbol *> getLinears(int flags) { return linearContext.getSymbols(flags); }

  void guard()
  {
    for (Symbol *sym : getLinears(SymbolLookupFlags::COMPLETE_LINEAR | SymbolLookupFlags::GUARDED_LINEAR | SymbolLookupFlags::PENDING_LINEAR))
    {
      if(sym->type->isLinear())
        sym->type->guard(); 
    }
  }

  bool unguard() 
  {
    for (Symbol *sym : getLinears(SymbolLookupFlags::COMPLETE_LINEAR | SymbolLookupFlags::GUARDED_LINEAR | SymbolLookupFlags::PENDING_LINEAR))
    {
        if(sym->type->isLinear() && !sym->type->unguard())
        {
          std::cout << "Failed to unguard " << sym->toString() << std::endl; 
          return false; 
        }
    }
    return true; 
  }

  /**
   * @brief Gets the number of scopes
   *
   * @return int
   */
  int scopeCount() { return dangerContext.scopeCount(); }

  std::string toString() const
  {
    std::ostringstream desc;
    desc << "{danger=" << dangerContext.toString() << "; linear=" << linearContext.toString() << "}";

    return desc.str();
  }

  /**
   * @brief Determines if the current scope is the global scope
   *
   * @return true if current scope is the global scope
   * @return false if the current scope is not the gobal scope
   */
  bool isGlobalScope()
  {
    return dangerContext.isGlobalScope();
  }

  int getCurrentStop()
  {
    return dangerContext.getCurrentStop();
  }

  std::optional<STManager *> getCopy()
  {
    std::optional<Context> lC = linearContext.getCopy();
    if (!lC)
      return std::nullopt;

    std::optional<Context> dC = dangerContext.getCopy();
    if (!dC)
      return std::nullopt;

    return new STManager(lC.value(), dC.value());
  }

private:
  Context linearContext;
  Context dangerContext;

  STManager(Context linear, Context danger) : linearContext(linear), dangerContext(danger) {}
};