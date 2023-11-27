#include "LTLMonitor.h"

LTLMonitor::LTLMonitor(LTLMonitorDef def, Symbol *progSym, Symbol *monSym) : def(def), progSym(progSym), monSym(monSym) {}

void LTLMonitor::resolveMonitorType()
{
    this->monSym->type = this->getProgTy()->getCopy();
}

const TypeProgram *LTLMonitor::getProgTy()
{
    
    const TypeProgram *progTy = dynamic_cast<const TypeProgram*>(this->progSym->type);

    // TODO: Figure out what the prefered ICE pattern and signal ICE on null progTy

    return progTy;
}

struct GenCx;

struct ChanCx
{
    Symbol *sym;
    const ProtocolSequence *proto;

    TProgramRecvNode *recv(GenCx &cx);
    TProgramSendNode *send(GenCx &cx, TProgramRecvNode *recv);
};

struct GenCx
{
    DFA dfa;
    
    BismuthErrorHandler *errorHandler;
    antlr4::Token *rootTok; // TODO: more precise error locations

    ChanCx c;
    ChanCx child;

    std::vector<TypedNode *> body;
};

void genExec(GenCx &cx, Symbol *sym);
std::variant<std::monostate, ErrorChain *> genProtocol(GenCx &cx, const Protocol *&&proto);


std::variant<TProgramDefNode *, ErrorChain *> LTLMonitor::gen(BismuthErrorHandler &errorHandler)
{
    const ProtocolSequence *protocol = this->getProgTy()->getProtocol();

    auto dfaRes = this->def.dfa(protocol, errorHandler);

    if (ErrorChain **e = std::get_if<ErrorChain *>(&dfaRes))
    {
        (*e)->addError(this->rootTok, "Error generating monitor dfa."); // wrong
        return *e;
    }
    DFA dfa = std::get<DFA>(dfaRes);

    ChanCx chanCx{
        .sym = new Symbol("c"s, new TypeChannel(protocol->getCopy()), false, false),
        .proto = protocol->getCopy(),
    };

    const ProtocolSequence *childProtocol = protocol->getInverse();

    ChanCx childCx{
        .sym = new Symbol("child"s, new TypeChannel(childProtocol->getCopy()), false, false),
        .proto = childProtocol,
    };
    
    GenCx genCx{
        .dfa = dfa,
        .errorHandler = &errorHandler,
        .rootTok = this->rootTok,
        .c = chanCx,
        .child = childCx,
        //body{}
    };

    genExec(genCx, this->progSym);
        
    dfa.genInit(genCx.body);

    auto genRes = genProtocol(genCx, protocol);
    
    if (ErrorChain **e = std::get_if<ErrorChain *>(&genRes))
    {
        (*e)->addError(this->rootTok, "Error generating monitor."); // wrong
        return *e;
    }
    
    TBlockNode *block = new TBlockNode(genCx.body, this->rootTok);

    TProgramDefNode *def = new TProgramDefNode(this->monSym->getIdentifier(), genCx.c.sym, block, this->getProgTy()->getCopy(), this->rootTok);
    return def;
}


TProgramRecvNode *ChanCx::recv(GenCx &cx)
{
    std::optional<RecvMetadata> meta = this->proto->recv();
    assert(meta);
    return new TProgramRecvNode(this->sym, *meta, this->proto->isInCloseable(), cx.rootTok);
}

TProgramSendNode *ChanCx::send(GenCx &cx, TProgramRecvNode *recv)
{
    optional<const Type *> sendTy = this->proto->send(recv->getType());
    assert(sendTy);
    return new TProgramSendNode(this->sym, this->proto->isInCloseable(), recv, *sendTy, cx.rootTok);
}
    
std::variant<std::monostate, ErrorChain *> genProtocol(GenCx &cx, const Protocol *&&proto)
{
    if (const ProtocolSequence *seq = dynamic_cast<const ProtocolSequence *>(proto))
    {
        for (const Protocol *step : seq->getSteps())
        {
            genProtocol(cx, std::move(step)); // threads through the channel types and output via cx
        }
        return std::monostate();
    }
    else if (const ProtocolRecv *recv = dynamic_cast<const ProtocolRecv *>(proto))
    {
        TProgramRecvNode *recvExpr = cx.c.recv(cx);
        TProgramSendNode *sendExpr = cx.child.send(cx, recvExpr);
        cx.body.push_back(sendExpr);
        return std::monostate();
    }
    else if (const ProtocolSend *send = dynamic_cast<const ProtocolSend *>(proto))
    {
        TProgramRecvNode *recvExpr = cx.child.recv(cx);
        TProgramSendNode *sendExpr = cx.c.send(cx, recvExpr);
        cx.body.push_back(sendExpr);
        return std::monostate();
    }
    else if (const ProtocolWN *wn = dynamic_cast<const ProtocolWN *>(proto))
    {
        //
    }
    else if (const ProtocolOC *oc = dynamic_cast<const ProtocolOC *>(proto))
    {
        //
    }
    else if (const ProtocolEChoice *ec = dynamic_cast<const ProtocolEChoice *>(proto))
    {
        //
    }
    else if (const ProtocolIChoice *ic = dynamic_cast<const ProtocolIChoice *>(proto))
    {
        // 
    }
    else if (const ProtocolClose *close = dynamic_cast<const ProtocolClose *>(proto))
    {
        //
    }
    else
    {
        assert(false); // TODO: better ICE strategy
    }

    return cx.errorHandler->addError(cx.rootTok, "Monitor unimplemented"s);
}

void genExec(GenCx &cx, Symbol *sym) {
    TFieldAccessNode *field = new TFieldAccessNode(cx.rootTok, sym, true);

    TProgramExecNode *exec = new TProgramExecNode(field, new TypeChannel(cx.child.proto), cx.rootTok);

    AssignmentNode *assign = new AssignmentNode({cx.child.sym}, exec);

    TVarDeclNode *decl = new TVarDeclNode({assign}, cx.rootTok);

    cx.body.push_back(decl);
}
