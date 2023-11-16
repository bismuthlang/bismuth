#pragma once

#include <optional>
#include "BismuthParser.h"

class LTLMonitorDef
{
  public:
    static std::optional<LTLMonitorDef> get(BismuthParser::DefineProgramContext * const &progCtx);
};
