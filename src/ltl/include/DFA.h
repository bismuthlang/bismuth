#pragma once

#include "TypedAST.h"

class DFA
{
  public:
    DFA() = default; // temporary
    void genInit(std::vector<TypedNode *> &body);
};
