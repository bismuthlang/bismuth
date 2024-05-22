#pragma once
#include "Symbol.h"
#include "antlr4-runtime.h"

template <typename T>
class PropertyManager {
  public:
    // Get the Symbol associated with this node
    std::optional<T> getBinding(antlr4::tree::ParseTree *ctx) {

      if(!bindings.contains(ctx)) return std::nullopt;

      if(auto ans = bindings.find(ctx); ans != bindings.end())
      {
        return ans->second;
      }

      return  std::nullopt;

      // T ans = bindings.get(ctx); 

      // if(ans) return ans; 

      // return std::nullopt; 
    }

    // Bind the symbol to the node
    void bind(antlr4::tree::ParseTree *ctx, T&& symbol) {
      // bindings.put(ctx, symbol);
      // bindings[ctx] = symbol;
      bindings.insert(ctx, symbol);
    }


    void bind(antlr4::tree::ParseTree *ctx, T& symbol) {
      // bindings.put(ctx, symbol);
      // bindings[ctx] = symbol;
      bindings.emplace(ctx, symbol);
    }
    //     virtual V get(ParseTree *node) {
    //   return _annotations[node];
    // }

  private:
    // antlr4::tree::ParseTreeProperty<T> bindings;
    std::map<antlr4::tree::ParseTree *, T> bindings;
};