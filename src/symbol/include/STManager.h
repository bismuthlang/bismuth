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
#include "Debug.h"
#include "TypeDefs.h"


#include <vector>
#include <optional>
#include <functional> // std::function

enum StopType
{
  NONE,
  GLOBAL
};


class STManager
{
private: 
  // PLAN: handle better, tracks where in hierarchy we are able to access
  bool nonLinearOnly = false; 

public:
  STManager()
    : nameCounter(std::map<std::string, uint32_t>())
    , context(Context(nameCounter))
  {}

  /**
   * @brief Enter a new scope
   *
   * @return Scope& the scope we entered
   */
  void enterScope(StopType stopType, std::optional<Identifier *> idOpt = std::nullopt);

  void enterScope(Scope & s) { context.enterScope(s); }

  Scope * createNamespace(Identifier * id);

  /**
   * @brief Exit the current scope and move up one level
   *
   * @return std::optional<Scope*> Returns empty if no parent scope to enter; otherwise returns last scope.
   */
  std::optional<std::reference_wrapper<Scope>> exitScope();

  /**
   * @brief Add a symbol to the current scope
   *
   * @param symbol The symbol to add
   * @return true if successful
   * @return false if unsuccessful (ie, name already bound to another symbol)
   */
  optional_ref<Symbol> addSymbol(std::string id, const Type * t, bool g); 

  optional_ref<DefinitionSymbol> addDefinition(VisibilityModifier m, std::string id, const Type * t, bool glob); 

  optional_ref<AliasSymbol> addAlias(std::string id, const Type * t, Identifier * a);//Symbol * a);

  optional_ref<Symbol> addAnonymousSymbol(std::string id, const Type * t);

  optional_ref<DefinitionSymbol> addAnonymousDefinition(std::string id, const Type * t);

  bool removeSymbol(Symbol& symbol);

  /**
   * @brief Lookup a symbol across all scopes returning the first definition found
   *
   * @param id The symbol name to lookup
   * @return std::optional<Symbol*>  Empty if symbol not found; present with value if found.
   */
  optional_ref<Symbol> lookup(std::string id);

  // Has to be std::function so they can be capturing---which is unfortunately less efficient 
  void enterNonlinearScope(std::function<void()> func); //void (*func)())


  bool isBound(std::string id);

  /**
   * @brief Lookup a symbol only in the current scope.
   *
   * @param id The symbol name to lookup
   * @return std::optional<Symbol*>  Empty if symbol not found; present with value if found.
   */
  optional_ref<Symbol> lookupInCurrentScope(std::string id); 

  /****************************************
   * Miscellaneous (useful for testing)
   ****************************************/

  /**
   * @brief Get the Current Scope object
   *
   * @return std::optional<Scope*>
   */
  std::reference_wrapper<Scope>  getCurrentScope(); 

  std::vector<std::reference_wrapper<Symbol>> getLinears(int flags);

  
  void guard(); 

  bool unguard(); 

  /**
   * @brief Gets the number of scopes
   *
   * @return int
   */
  int scopeCount();

  std::string toString() const; 

  /**
   * @brief Determines if the current scope is the global scope
   *
   * @return true if current scope is the global scope
   * @return false if the current scope is not the global scope
   */
  bool isGlobalScope(); 


  std::optional<std::reference_wrapper<Scope>> getOrProvisionScope(std::vector<std::string> steps, VisibilityModifier m) { return context.getOrProvisionScope(steps, m); }

  Scope& getGlobalScope() { return context.getGlobalScope(); }

private: 
  std::string getUniqNameFor(Scope * parent, std::string inScope); 

private:
  std::map<std::string, uint32_t> nameCounter;
  Context context;
};
