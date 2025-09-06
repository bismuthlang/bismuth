#pragma once

#include "tree/ParseTree.h"
#include <optional>
#include <map>

template <typename T>
class PropertyManager {
  public:
    // Get the Symbol associated with this node
    std::optional<T> getBinding(antlr4::tree::ParseTree *ctx) {
      auto attrIt = bindings.find(ctx); 
      if(attrIt == bindings.end()) return std::nullopt;

      return attrIt->second; 
    }

    // Bind the symbol to the node
    void bind(antlr4::tree::ParseTree *ctx, T symbol) {
      bindings.emplace(ctx, symbol);
    }

    bool hasAttrOn(antlr4::tree::ParseTree *ctx) {
      if(bindings.find(ctx) == bindings.end())
        return false;
      return true;
    }

  private:
    std::map<antlr4::tree::ParseTree*, T> bindings; 
    // antlr4::tree::ParseTreeProperty<T> bindings;
};
