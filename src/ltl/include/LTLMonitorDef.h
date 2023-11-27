#pragma once

#include <optional>
#include "BismuthParser.h"
#include "DFA.h"
#include "BismuthErrorHandler.h"
#include "Protocol.h"

class LTLMonitorDef
{
  private:
    /// A non-checking definition
    LTLMonitorDef(); 
    
  public:
    static std::optional<LTLMonitorDef> get(BismuthParser::DefineProgramContext * const &progCtx);

    std::variant<DFA, ErrorChain *> dfa(const ProtocolSequence *&protocol, BismuthErrorHandler &errorHandler);
};
