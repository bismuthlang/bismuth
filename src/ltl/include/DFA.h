#pragma once

#include "TypedAST.h"
#include "GenCx.h"

class DFA
{
  private: 
    std::optional<Symbol *>demoSym;
  public:
    DFA(bool demo);
    void genInit(GenCx &cx);
    void genLabel(GenCx &cx, std::string label);
};
