#pragma once

#include <optional>
#include <variant>
#include "BismuthParser.h"
#include "LTLMonitorDef.h"
#include "DFA.h"
#include "Symbol.h"
#include "TypedAST.h"
#include "BismuthErrorHandler.h"
#include "GenCx.h"

class LTLMonitor
{
  private:
    LTLMonitorDef def;
    Symbol *progSym;
    Symbol *monSym;
    antlr4::Token *rootTok = NULL;

 public:
    LTLMonitor(LTLMonitorDef def, Symbol *progSym, Symbol *monSym);

    std::variant<TProgramDefNode *, ErrorChain *> gen(BismuthErrorHandler &errorHandler, Symbol *abortSym);

    void resolveMonitorType();

  private:
    const TypeProgram *getProgTy();
};

