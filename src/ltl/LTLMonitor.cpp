#include "LTLMonitor.h"

LTLMonitor::LTLMonitor(LTLMonitorDef def, Symbol *progSym, Symbol *monSym) : def(def), progSym(progSym), monSym(monSym) {}

std::variant<TProgramDefNode *, ErrorChain *> LTLMonitor::gen() {
    return new ErrorChain(nullptr, "Monitors are unimplemented", SEMANTIC, ERROR);
}

void LTLMonitor::resolveMonitorType() {
    const TypeProgram *progTy = dynamic_cast<const TypeProgram*>(this->progSym->type);

    // TODO: Figure out what the prefered ICE pattern and signal ICE on null progTy

    this->monSym->type = progTy->getCopy();
}




    
