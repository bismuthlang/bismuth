#include "LTLMonitorDef.h"

LTLMonitorDef::LTLMonitorDef() = default;

std::optional<LTLMonitorDef> LTLMonitorDef::get(BismuthParser::DefineProgramContext * const &progCtx) {
    if (progCtx->name->getText().starts_with("MONITORED")) {
        return LTLMonitorDef();
    }
    return std::nullopt;
}

std::variant<DFA, ErrorChain *> LTLMonitorDef::dfa(const ProtocolSequence *&protocol, BismuthErrorHandler &errorHandler) {
    return DFA();
}
