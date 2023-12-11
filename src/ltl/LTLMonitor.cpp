#include "LTLMonitor.h"

LTLMonitor::LTLMonitor(LTLMonitorDef def, Symbol *progSym, Symbol *monSym) : def(def), progSym(progSym), monSym(monSym) {}

void LTLMonitor::resolveMonitorType()
{
    TypeProgram *ty = new TypeProgram(this->getProgTy()->getProtocol());
    ty->setName(this->monSym->getIdentifier());
    this->monSym->type = ty;
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
    DFA *dfa;
    
    BismuthErrorHandler *errorHandler;
    Symbol *abortSym;
    antlr4::Token *rootTok; // TODO: more precise error locations

    ChanCx c;
    ChanCx child;

    std::vector<TypedNode *> body;
};

void genExec(GenCx &cx, Symbol *sym);
void genProtocol(GenCx &cx, const Protocol *&&proto);


std::variant<TProgramDefNode *, ErrorChain *> LTLMonitor::gen(BismuthErrorHandler &errorHandler, Symbol *abortSym)
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
        .dfa = &dfa,
        .errorHandler = &errorHandler,
        .abortSym = abortSym,
        .rootTok = this->rootTok,
        .c = chanCx,
        .child = childCx,
        //body{}
    };

    genExec(genCx, this->progSym);
        
    dfa.genInit(genCx.body);

    genProtocol(genCx, protocol);
    
    TBlockNode *block = new TBlockNode(genCx.body, this->rootTok);

    TProgramDefNode *def = new TProgramDefNode(this->monSym->getIdentifier(), genCx.c.sym, block, dynamic_cast<const TypeProgram *>(this->monSym->type), this->rootTok);
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

// GenCx GenCx::makeInner() {
//     GenCx innerCx{
//         .dfa = this->dfa,
//         .errorHandler = this->errorHandler,
//         .abortSym = this->abortSym,
//         .rootTok = this->rootTok,
//         .c = this->c,
//         .child = this->child,
//         //body{}        
//     };
//     return innerCx;
// }

void genLoop(GenCx &cx, ChanCx *acceptChan, ChanCx *moreChan);
void genChoice(GenCx &cx, ChanCx *projectChan, ChanCx *offerChan, std::set<const ProtocolBranchOption *, BranchOptCompare> caseSet);
    
void genProtocol(GenCx &cx, const Protocol *&&proto)
{
    if (const ProtocolSequence *seq = dynamic_cast<const ProtocolSequence *>(proto))
    {
        for (const Protocol *step : seq->getSteps())
        {
            genProtocol(cx, std::move(step)); // threads through the channel types and output via cx
        }
        return;
    }
    else if (const ProtocolRecv *recv = dynamic_cast<const ProtocolRecv *>(proto))
    {
        TProgramRecvNode *recvExpr = cx.c.recv(cx);
        TProgramSendNode *sendExpr = cx.child.send(cx, recvExpr);
        cx.body.push_back(sendExpr);
        return;
    }
    else if (const ProtocolSend *send = dynamic_cast<const ProtocolSend *>(proto))
    {
        TProgramRecvNode *recvExpr = cx.child.recv(cx);
        TProgramSendNode *sendExpr = cx.c.send(cx, recvExpr);
        cx.body.push_back(sendExpr);
        return;
    }
    else if (const ProtocolWN *wn = dynamic_cast<const ProtocolWN *>(proto))
    {
        genLoop(cx, &cx.child, &cx.c);
        return;
    }
    else if (const ProtocolOC *oc = dynamic_cast<const ProtocolOC *>(proto))
    {
        genLoop(cx, &cx.c, &cx.child);
        return;
    }
    else if (const ProtocolEChoice *ec = dynamic_cast<const ProtocolEChoice *>(proto))
    {
        std::set<const ProtocolBranchOption *, BranchOptCompare> inv;
        for (auto br : ec->getOptions()) {
            inv.insert(br->getInverse());
        }
        genChoice(cx, &cx.child, &cx.c, inv);
        return;
    }
    else if (const ProtocolIChoice *ic = dynamic_cast<const ProtocolIChoice *>(proto))
    {
        genChoice(cx, &cx.child, &cx.c, ic->getOptions());
        return;
    }
    
    assert(false); // Unknown protocol
}

void genExec(GenCx &cx, Symbol *sym) {
    TFieldAccessNode *field = new TFieldAccessNode(cx.rootTok, sym, true);

    TProgramExecNode *exec = new TProgramExecNode(field, new TypeChannel(cx.child.proto), cx.rootTok);

    AssignmentNode *assign = new AssignmentNode({cx.child.sym}, exec);

    TVarDeclNode *decl = new TVarDeclNode({assign}, cx.rootTok);

    cx.body.push_back(decl);
}

void genFail(GenCx &cx) {

    TFieldAccessNode *nameNode = new TFieldAccessNode(cx.rootTok, cx.abortSym, false, {});

    TInvocationNode *invokeNode = new TInvocationNode(nameNode, {}, {}, cx.rootTok);

    cx.body.push_back(invokeNode);
}

void genLoop(GenCx &cx, ChanCx *acceptChan, ChanCx *moreChan) {
    std::optional<const ProtocolSequence *> acceptProto = acceptChan->proto->acceptLoop();
    assert(acceptProto);

    bool inCloseable = acceptChan->proto->isInCloseable(); // no clue if this is right

    ChanCx innerChan {
        .sym = acceptChan->sym,
        .proto = acceptProto.value(),
    };

    ChanCx restoreChan = std::exchange(*acceptChan, innerChan);
    std::vector restoreBody = std::exchange(cx.body, {});

    assert(moreChan->proto->contract());

    TProgramContractNode *contractNode = new TProgramContractNode(moreChan->sym, cx.rootTok);
    cx.body.push_back(contractNode);

    genProtocol(cx, acceptChan == &cx.c ? acceptProto.value() : acceptProto.value()->getInverse());

    TBlockNode *loopBodyNode = new TBlockNode(cx.body, cx.rootTok);
    TProgramAcceptNode *acceptNode = new TProgramAcceptNode(acceptChan->sym, inCloseable, loopBodyNode, cx.rootTok);

    *acceptChan = restoreChan;
    cx.body = restoreBody;
    
    cx.body.push_back(acceptNode);

    assert(moreChan->proto->weaken());
    TProgramWeakenNode *weakenNode = new TProgramWeakenNode(moreChan->sym, cx.rootTok);
    cx.body.push_back(weakenNode);
}

void genChoice(GenCx &cx, ChanCx *projectChan, ChanCx *offerChan, std::set<const ProtocolBranchOption *, BranchOptCompare> caseSet)
{
    bool inCloseable = offerChan->proto->isInCloseable(); // ?

    std::vector<const ProtocolBranchOption *> cases(caseSet.begin(), caseSet.end());
    
    std::vector<variant<const ProtocolSequence *, string>> arms;
    for (const ProtocolBranchOption *alt : cases)
    {
        if (alt->label) {
            arms.push_back(std::string(alt->label.value()));
        } else {
            arms.push_back(alt->seq->getInverse());
        }
    }
    
    std::optional<CaseMetadata> meta = offerChan->proto->caseAnalysis(arms);
    assert(meta);

    std::vector<TypedNode *> armNodes;

    const ProtocolSequence *unprojected = projectChan->proto->getCopy();
    std::vector outerBody = std::exchange(cx.body, {}); // a new body for each alternative

    assert(meta->fullSequences.size() == cases.size());
    for (unsigned long idx = 0; idx < meta->fullSequences.size(); idx++)
    {
        const ProtocolSequence *seq = meta->fullSequences[idx];
        const ProtocolBranchOption *branch = cases[idx];
        
        offerChan->proto = seq;
        projectChan->proto = unprojected->getCopy();
        cx.body = {};

        if (branch->label)
        {
            projectChan->proto->project(branch->label.value());
        } else {
            projectChan->proto->project(branch->seq);
        }
        cx.body.push_back(new TProgramProjectNode(projectChan->sym, idx + 1, cx.rootTok));
        
        const ProtocolSequence *innerStructure = offerChan == &cx.c ? branch->seq->getInverse() : branch->seq;
        genProtocol(cx, innerStructure);

        armNodes.push_back(new TBlockNode(cx.body, cx.rootTok));
     }

    offerChan->proto = meta->rest;
    projectChan->proto = meta->rest->getInverse();
    cx.body = {}; // the body for post

    //    genProtocol(cx, meta->rest);

    TChannelCaseStatementNode *caseNode = new TChannelCaseStatementNode(offerChan->sym, inCloseable, false, armNodes, {}/*cx.body*/, cx.rootTok);

    cx.body = outerBody;

    cx.body.push_back(caseNode);
}
