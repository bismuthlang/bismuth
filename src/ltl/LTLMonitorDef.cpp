#include "LTLMonitorDef.h"

LTLMonitorDef::LTLMonitorDef(bool demo) : demo(demo) {}

std::optional<LTLMonitorDef> LTLMonitorDef::get(BismuthParser::DefineProgramContext * const &progCtx) {
    if (progCtx->name->getText().starts_with("MONITORED")) {
        return LTLMonitorDef(progCtx->name->getText().starts_with("MONITORED_DEMO"));
    }
    return std::nullopt;
}

std::variant<DFA, ErrorChain *> LTLMonitorDef::dfa(const ProtocolSequence *&protocol, BismuthErrorHandler &errorHandler) {
    return DFA(this->demo);
}
