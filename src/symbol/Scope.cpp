#include "Scope.h"

/**
 * @brief Adds a symbol to the scope.
 *
 * @param id The identifier for the symbol
 * @param t The type of the symbol
 * @return true If the symbol was added
 * @return false If the symbol was already defined
 */
optional_ref<Symbol> Scope::addSymbol(std::shared_ptr<Symbol> symbol)
{
  std::string id = symbol->getScopedIdentifier();
  if (symbols.find(id) != symbols.end())
  {
    // Symbol already defined
    return std::nullopt;
  }

  symbols.emplace(id, symbol);
  return *symbol;
}

bool Scope::removeSymbol(const Symbol& symbol)
{
  std::string id = symbol.getScopedIdentifier();
  if (auto it = symbols.find(id); it != symbols.end())
  {
    deletedSymbols.insert(it->second);
    symbols.erase(symbols.find(id)); 
    return true;
  }

  return false;
}


std::optional<std::pair<std::reference_wrapper<Symbol>, std::reference_wrapper<Scope>>> Scope::lookupWithScope(std::string id)
{
    std::optional<std::reference_wrapper<Scope>> opt = *this;
    bool foundStop = false; 

    while (opt)
    {
        Scope& scope = opt.value().get();

        if (optional_ref<Symbol> symOpt = scope.lookupInCurrentScope(id); symOpt.has_value())
        {
            auto sym = symOpt.value(); 
            if (!foundStop || sym.get().isDefinition() || sym.get().isGlobal())
            {
                return std::make_pair(sym, opt.value());
            }
            return std::nullopt;
        }

        foundStop = scope.isStop(); 
        opt = scope.getParent();
    }

    return std::nullopt;
}


optional_ref<Symbol> Scope::lookupInAccessableScopes(std::string id)
{
  optional_ref<Scope> opt = *this;
  bool foundStop = false; 

  while (opt)
  {
    Scope& scope = opt.value().get();

    optional_ref<Symbol> symOpt = scope.lookupInCurrentScope(id);
    if (symOpt)
    {
      auto sym = symOpt.value(); 
      if (!foundStop || sym.get().isDefinition() || sym.get().isGlobal())
          return sym;
      return std::nullopt;
    }

    foundStop = scope.isStop(); 
    opt = scope.getParent();
  }

    return std::nullopt;
}


Scope * Scope::createNamespace(Identifier * id)
{
  return new Scope(*this, id, true);
}


optional_ref<DefinitionSymbol> Scope::addDefinition(VisibilityModifier m, Identifier * identifier, const Type * t, bool glob)
{
    Scope* innerScope = this->createNamespace(identifier);

    // Need to do this hack just to preserve type safety. No need to add duplicate function. 
    auto ans = this->addSymbol(std::make_shared<DefinitionSymbol>(m, identifier, t, glob, *this, innerScope));
    if(ans)
    {
      return *dynamic_cast<DefinitionSymbol *>(&ans.value().get());
    }
    return std::nullopt; 
}

/**
 * @brief Searches for a token in the given scope.
 *
 * @param id The identifier of the token to search for
 * @return std::optional<Symbol*> - Empty if not found; value provided if found.
 */
optional_ref<Symbol> Scope::lookupInCurrentScope(std::string id)
{
  auto symbol = symbols.find(id);
  if (symbol == symbols.end())
    return std::nullopt;
  return *symbol->second;
}

// Modified from starter
std::string Scope::toString() const
{
  std::ostringstream description;
  /*
  description << std::endl
              << "-------------------" << std::endl
              << "SCOPE: " << scopeId;
  if (parent)
  {
    description << " PARENT: " << (parent.value())->scopeId;
  }
  description << std::endl
              << '{';
  for (auto sym : symbols)
  {
    description << std::endl
                << "    " << sym.second->toString();
  }
  description << std::endl
              << '}' << std::endl;
  */

  description << '{'; 
  description << "\tid: " << scopeId << ", " << std::endl;
  
  if(parent) 
    description << "\tparent: " << parent.value().get().scopeId << ", " << std::endl; 
  
  description << "\tsymbols: {" << std::endl; 

  for (auto sym : symbols)
  {
    description << "\t\t" << sym.second->toString() << ", " << std::endl;
  }

  description << "\t}," << std::endl; 
  description << "}," << std::endl; 
  return description.str();
}
