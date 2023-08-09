#include "ProtocolVisitor.h"

/*************************************************************
 *
 * Protocols
 *
 *************************************************************/

// const Protocol *
std::variant<const ProtocolSequence *, ErrorChain *> ProtocolVisitor::visitProto(BismuthParser::ProtocolContext *ctx)
{
    std::vector<const Protocol *> steps;

    for (auto e : ctx->protos)
    {
        std::variant<const Protocol *, ErrorChain *> protoOpt = anyOpt2VarError<const Protocol>(errorHandler, e->accept(this));
        if (ErrorChain **e = std::get_if<ErrorChain *>(&protoOpt))
        {
            (*e)->addError(ctx->getStart(), "Error in protocol sequence");
            return *e;
        }

        const Protocol *proto = std::get<const Protocol *>(protoOpt);
        steps.push_back(proto);
    }

    return new ProtocolSequence(steps);
}

std::variant<const ProtocolRecv *, ErrorChain *> ProtocolVisitor::visitProto(BismuthParser::RecvTypeContext *ctx)
{
    std::variant<const Type *, ErrorChain *> tyOpt = anyOpt2VarError<const Type>(errorHandler, ctx->ty->accept(ASTGenVisitor));
    
    if (ErrorChain **e = std::get_if<ErrorChain *>(&tyOpt))
    {
        (*e)->addError(ctx->getStart(), "Failed to generate receive type");
        return *e;
    }

    const Type * ty = std::get<const Type*>(tyOpt);
    
    if(this->inClose && !ty->isLossy())
    {
        return errorHandler.addError(ctx->getStart(), "Cannot receive non-lossy type " + ty->toString() + " in a closeable protocol"); 
    }


    return new ProtocolRecv(ty);
}

// FIXME: ADD TEST CASES WITH BRANCHES, LOOPS, SEQ, ETC TO VERIFY THISLL CATCH, POTENTIALLY METHODIZE THESE ALL
std::variant<const ProtocolSend *, ErrorChain *> ProtocolVisitor::visitProto(BismuthParser::SendTypeContext *ctx)
{
    std::variant<const Type *, ErrorChain *> tyOpt = anyOpt2VarError<const Type>(errorHandler, ctx->ty->accept(ASTGenVisitor));
    
    if (ErrorChain **e = std::get_if<ErrorChain *>(&tyOpt))
    {
        (*e)->addError(ctx->getStart(), "Failed to generate send type");
        return *e;
    }

    const Type * ty = std::get<const Type*>(tyOpt);
    
    if(this->inClose && !ty->isLossy())
    {
        return errorHandler.addError(ctx->getStart(), "Cannot send non-lossy type " + ty->toString() + " in a closeable protocol"); 
    }

    return new ProtocolSend(ty);
}

std::variant<const ProtocolWN *, ErrorChain *> ProtocolVisitor::visitProto(BismuthParser::WnProtoContext *ctx)
{
    bool origStatus = this->inLoop; 
    this->inLoop = true;
    std::variant<const Protocol *, ErrorChain *> protoOpt = anyOpt2VarError<const Protocol>(errorHandler, ctx->proto->accept(this));
    this->inLoop = origStatus; 

    if (ErrorChain **e = std::get_if<ErrorChain *>(&protoOpt))
    {
        (*e)->addError(ctx->getStart(), "Error in ? loop protocol");  // PLAN: refactor symbols into constants/pull from parser rule?
        return *e;
    }

    const Protocol *proto = std::get<const Protocol *>(protoOpt);
    return new ProtocolWN(toSequence(proto));
}

std::variant<const ProtocolOC *, ErrorChain *> ProtocolVisitor::visitProto(BismuthParser::OcProtoContext *ctx)
{
    bool origStatus = this->inLoop; 
    this->inLoop = true;
    std::variant<const Protocol *, ErrorChain *> protoOpt = anyOpt2VarError<const Protocol>(errorHandler, ctx->proto->accept(this));
    this->inLoop = origStatus; 

    if (ErrorChain **e = std::get_if<ErrorChain *>(&protoOpt))
    {
        (*e)->addError(ctx->getStart(), "Error in ! loop protocol");
        return *e;
    }

    const Protocol *proto = std::get<const Protocol *>(protoOpt);
    return new ProtocolOC(toSequence(proto));
}

std::variant<const ProtocolEChoice *, ErrorChain *> ProtocolVisitor::visitProto(BismuthParser::ExtChoiceProtoContext *ctx)
{
    std::set<const ProtocolSequence *, ProtocolCompare> opts = {};
    unsigned int origCloseNumber = this->closeNumber; 
    unsigned int maxCloseNumber = this->closeNumber; 

    for (auto e : ctx->protoOpts)
    {
        this->closeNumber = origCloseNumber; 
        std::variant<const Protocol *, ErrorChain *> protoOpt = anyOpt2VarError<const Protocol>(errorHandler, e->accept(this));
        maxCloseNumber = this->closeNumber > maxCloseNumber ? this->closeNumber : maxCloseNumber;

        if (ErrorChain **e = std::get_if<ErrorChain *>(&protoOpt))
        {
            (*e)->addError(ctx->getStart(), "Error in external choice branch");
            return *e;
        }

        const Protocol *proto = std::get<const Protocol *>(protoOpt);

        opts.insert(toSequence(proto));
    }

    if (ctx->protoOpts.size() != opts.size())
    {
        return errorHandler.addError(ctx->getStart(), "Duplicate protocols in choice");
    }
    
    this->closeNumber = maxCloseNumber; 

    return new ProtocolEChoice(opts);
}

std::variant<const ProtocolIChoice *, ErrorChain *> ProtocolVisitor::visitProto(BismuthParser::IntChoiceProtoContext *ctx)
{
    std::set<const ProtocolSequence *, ProtocolCompare> opts = {};
    unsigned int origCloseNumber = this->closeNumber;  // We do this logic regardless as probably faster to not branch, and will remain zero in the case that were not in a close block
    unsigned int maxCloseNumber = this->closeNumber; 

    for (auto e : ctx->protoOpts)
    {
        this->closeNumber = origCloseNumber;
        std::variant<const Protocol *, ErrorChain *> protoOpt = anyOpt2VarError<const Protocol>(errorHandler, e->accept(this));
        maxCloseNumber = this->closeNumber > maxCloseNumber ? this->closeNumber : maxCloseNumber;

        if (ErrorChain **e = std::get_if<ErrorChain *>(&protoOpt))
        {
            (*e)->addError(ctx->getStart(), "Error in internal choice branch");
            return *e;
        }

        const Protocol *proto = std::get<const Protocol *>(protoOpt);

        opts.insert(toSequence(proto));
    }

    if (ctx->protoOpts.size() != opts.size())
    {
        return errorHandler.addError(ctx->getStart(), "Duplicate protocols in choice");
    }

    this->closeNumber = maxCloseNumber; 

    return new ProtocolIChoice(opts);
}

std::variant<const ProtocolClose *, ErrorChain *> ProtocolVisitor::visitProto(BismuthParser::CloseableProtoContext *ctx)
{
    if(this->inLoop) // PLAN: Potentially report this and lower down proto errors?
    {
        return errorHandler.addError(ctx->getStart(), "Currently cannot include looping protocol within closeable block. Instead, move loop outside block or use higher-order channels.");
    }
     
    bool origStatus = this->inClose; 
    this->inClose = true; 
    std::variant<const Protocol *, ErrorChain *> protoOpt = anyOpt2VarError<const Protocol>(errorHandler, ctx->proto->accept(this));
    this->inClose = origStatus; 

    if (ErrorChain **e = std::get_if<ErrorChain *>(&protoOpt))
    {
        (*e)->addError(ctx->getStart(), "Error in close protocol");
        return *e;
    }

    const Protocol *proto = std::get<const Protocol *>(protoOpt);

    return new ProtocolClose(toSequence(proto), ++closeNumber); // NOTE, must be ++i otherwise first would be zero, which could potentially be a problem?
}