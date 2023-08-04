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
    const Type *ty = any2Type(sematicVisitor->visit(ctx->ty));

     // FIXME: METHODIZE WITH CODE FOR SEND AS THEYRE THE SAME!! AND CHANGE TO MORE GENERAL LOSSY TYPE CHECK?
    if(this->inClose)
    {
        if(const TypeChannel * channelTy = dynamic_cast<const TypeChannel *>(ty))
        {
            const std::vector<const Protocol*> steps = channelTy->getProtocol()->getSteps(); 
            if(steps.size() != 1) return errorHandler.addError(ctx->getStart(), "Cannot receive non-lossy type " + ty->toString() + " in a closeable protocol"); 

            if(!dynamic_cast<const ProtocolClose*>(steps.at(0)))
                return errorHandler.addError(ctx->getStart(), "Cannot receive non-lossy type " + ty->toString() + " in a closeable protocol"); 
        }
    }


    return new ProtocolRecv(ty);
}

// FIXME: ADD TEST CASES WITH BRANCHES, LOOPS, SEQ, ETC TO VERIFY THISLL CATCH
std::variant<const ProtocolSend *, ErrorChain *> ProtocolVisitor::visitProto(BismuthParser::SendTypeContext *ctx)
{
    const Type *ty = any2Type(ctx->ty->accept(sematicVisitor));

    if(this->inClose)
    {
        if(const TypeChannel * channelTy = dynamic_cast<const TypeChannel *>(ty))
        {
            const std::vector<const Protocol*> steps = channelTy->getProtocol()->getSteps(); 
            if(steps.size() != 1) return errorHandler.addError(ctx->getStart(), "Cannot send non-lossy type " + ty->toString() + " in a closeable protocol"); 

            if(!dynamic_cast<const ProtocolClose*>(steps.at(0)))
                return errorHandler.addError(ctx->getStart(), "Cannot send non-lossy type " + ty->toString() + " in a closeable protocol"); 
        }
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

    for (auto e : ctx->protoOpts)
    {
        std::variant<const Protocol *, ErrorChain *> protoOpt = anyOpt2VarError<const Protocol>(errorHandler, e->accept(this));
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

    return new ProtocolEChoice(opts);
}

std::variant<const ProtocolIChoice *, ErrorChain *> ProtocolVisitor::visitProto(BismuthParser::IntChoiceProtoContext *ctx)
{
    std::set<const ProtocolSequence *, ProtocolCompare> opts = {};

    for (auto e : ctx->protoOpts)
    {
        std::variant<const Protocol *, ErrorChain *> protoOpt = anyOpt2VarError<const Protocol>(errorHandler, e->accept(this));
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

    // FIXME: NEED TO ALSO CHECK AGAINST LINEAR RESOURCES IN GENERAL!!  AND NEED TO ADD TEST CASES!!!

    return new ProtocolClose(toSequence(proto));
}