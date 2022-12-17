#pragma once
#include "Symbol.h"
#include "antlr4-runtime.h"

class PropertyManager {
  public:
    // Get the Symbol associated with this node
    std::optional<Symbol*> getBinding(antlr4::tree::ParseTree *ctx) {
      Symbol * ans = bindings.get(ctx); 

      if(ans) return ans; 

      return std::nullopt; 
    }

    // Bind the symbol to the node
    void bind(antlr4::tree::ParseTree *ctx, Symbol* symbol) {
      bindings.put(ctx, symbol);
    }

  private:
    antlr4::tree::ParseTreeProperty<Symbol*> bindings;
};