#pragma once
#include "Symbol.h"
#include "antlr4-runtime.h"

template <typename T>
class PropertyManager {
  public:
    // Get the Symbol associated with this node
    std::optional<T*> getBinding(antlr4::tree::ParseTree *ctx) {
      T* ans = bindings.get(ctx); 

      if(ans) return ans; 

      return std::nullopt; 
    }

    // Bind the symbol to the node
    void bind(antlr4::tree::ParseTree *ctx, T* symbol) {
      bindings.put(ctx, symbol);
    }

  private:
    antlr4::tree::ParseTreeProperty<T*> bindings;
};