#pragma once

#include "BismuthErrorHandler.h"

class DFA; 

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


void genFail(GenCx &cx);
