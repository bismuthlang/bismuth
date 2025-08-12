#include "Scope.h"

/**
 * @brief Adds a symbol to the scope.
 *
 * @param id The identifier for the symbol
 * @param t The type of the symbol
 * @return true If the symbol was added
 * @return false If the symbol was already defined
 */
std::optional<Symbol *> Scope::addSymbol(Symbol *symbol)
{
  std::string id = symbol->getScopedIdentifier();
  if (symbols.find(id) != symbols.end())
  {
    // Symbol already defined
    delete symbol; // Save the memory FIXME: IS THIS UNSAFE? It should be safe now that we create the symbol in context and only return it to user if valid
    return std::nullopt;
  }

  auto ret = symbols.insert({id, symbol}).first;
return ret->second;
}

bool Scope::removeSymbol(const Symbol *symbol)
{
  std::string id = symbol->getScopedIdentifier();
  if (symbols.find(id) != symbols.end())
  {
    symbols.erase(symbols.find(id));
    return true;
  }

  return false;
}


std::optional<std::pair<Symbol *, std::reference_wrapper<Scope>>> Scope::lookupWithScope(std::string id)
{
    std::optional<std::reference_wrapper<Scope>> opt = *this;
    bool foundStop = false; 

    while (opt)
    {
        Scope& scope = opt.value().get();

        if (std::optional<Symbol *> symOpt = scope.lookupInCurrentScope(id); symOpt.has_value())
        {
            Symbol * sym = symOpt.value(); 
            if (!foundStop || sym->isDefinition() || sym->isGlobal())
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


std::optional<Symbol *> Scope::lookupInAccessableScopes(std::string id)
{
  std::optional<std::reference_wrapper<Scope>> opt = *this;
  bool foundStop = false; 

  while (opt)
  {
    Scope& scope = opt.value().get();

    std::optional<Symbol *> symOpt = scope.lookupInCurrentScope(id);
    if (symOpt)
    {
      Symbol * sym = symOpt.value(); 
      if (!foundStop || sym->isDefinition() || sym->isGlobal())
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


std::optional<DefinitionSymbol *> Scope::addDefinition(VisibilityModifier m, Identifier * identifier, const Type * t, bool glob)
{
    Scope* innerScope = this->createNamespace(identifier);

    DefinitionSymbol * sym = new DefinitionSymbol(m, identifier, t, glob, *this, innerScope);

    // Need to do this hack just to preserve type safety. No need to add duplicate function. 
    if(this->addSymbol(sym))
        return sym; 

    delete sym; 

    return std::nullopt; 
}

/**
 * @brief Searches for a token in the given scope.
 *
 * @param id The identifier of the token to search for
 * @return std::optional<Symbol*> - Empty if not found; value provided if found.
 */
std::optional<Symbol *> Scope::lookupInCurrentScope(std::string id)
{
  auto symbol = symbols.find(id);
  if (symbol == symbols.end())
    return std::nullopt;
  return symbol->second;
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
