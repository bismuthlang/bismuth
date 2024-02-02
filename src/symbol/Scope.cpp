#include "Scope.h"

/**
 * @brief Adds a symbol to the scope.
 *
 * @param id The identifier for the symbol
 * @param t The type of the symbol
 * @return true If the symbol was added
 * @return false If the symbol was already defined
 */
// bool Scope::addSymbol(std::string id, Type* t)
// {
//   Symbol *symbol = new Symbol(id, t);
//   return addSymbol(symbol);
// }

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

/**
 * @brief Searches for a token in the given scope.
 *
 * @param id The identifier of the token to search for
 * @return std::optional<Symbol*> - Empty if not found; value provided if found.
 */
std::optional<Symbol *> Scope::lookup(std::string id)
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
    description << "\tparent: " << parent.value()->scopeId << ", " << std::endl; 
  description << "\tsymbols: {" << std::endl; 

  for (auto sym : symbols)
  {
    description << "\t\t" << sym.second->toString() << ", " << std::endl;
  }

  description << "\t}," << std::endl; 

  description << "}," << std::endl; 
  return description.str();
}
