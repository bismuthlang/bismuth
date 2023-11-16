#pragma once

#include <optional>
#include "BismuthParser.h"
#include "LTLMonitorDef.h"
#include "Symbol.h"
#include "TypedAST.h"
#include "BismuthErrorHandler.h"

class LTLMonitor
{
  private:
    LTLMonitorDef def;
    Symbol *progSym;
    Symbol *monSym;

 public:
    LTLMonitor(LTLMonitorDef def, Symbol *progSym, Symbol *monSym);

    std::variant<TProgramDefNode *, ErrorChain *> gen();

    void resolveMonitorType();
};
