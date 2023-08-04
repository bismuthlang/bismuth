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
            (*e)->addError(ctx->getStart(), "FIXME: 21");
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
    return new ProtocolRecv(ty);
}

std::variant<const ProtocolSend *, ErrorChain *> ProtocolVisitor::visitProto(BismuthParser::SendTypeContext *ctx)
{
    const Type *ty = any2Type(ctx->ty->accept(this));
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
        (*e)->addError(ctx->getStart(), "FIXME: 49");
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
        (*e)->addError(ctx->getStart(), "FIXME: 68");
        return *e;
    }

    const Protocol *proto = std::get<const Protocol *>(protoOpt);
    return new ProtocolOC(toSequence(proto));

    // const Protocol *proto = any2Protocol(ctx->proto->accept(this));
    // return new ProtocolOC(toSequence(proto));
}

std::variant<const ProtocolEChoice *, ErrorChain *> ProtocolVisitor::visitProto(BismuthParser::ExtChoiceProtoContext *ctx)
{
    std::set<const ProtocolSequence *, ProtocolCompare> opts = {};

    for (auto e : ctx->protoOpts)
    {
        std::variant<const Protocol *, ErrorChain *> protoOpt = anyOpt2VarError<const Protocol>(errorHandler, e->accept(this));
        if (ErrorChain **e = std::get_if<ErrorChain *>(&protoOpt))
        {
            (*e)->addError(ctx->getStart(), "FIXME: 88");
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
            (*e)->addError(ctx->getStart(), "FIXME: 114");
            return *e;
        }

        const Protocol *proto = std::get<const Protocol *>(protoOpt);

        opts.insert(toSequence(proto));
        // opts.insert(toSequence(any2Protocol(e->accept(this))));
    }

    if (ctx->protoOpts.size() != opts.size())
    {
        return errorHandler.addError(ctx->getStart(), "Duplicate protocols in choice");
    }

    return new ProtocolIChoice(opts);

}

std::variant<const ProtocolClose *, ErrorChain *> ProtocolVisitor::visitProto(BismuthParser::CloseableProtoContext *ctx)
{
    std::variant<const Protocol *, ErrorChain *> protoOpt = anyOpt2VarError<const Protocol>(errorHandler, ctx->proto->accept(this));
    if (ErrorChain **e = std::get_if<ErrorChain *>(&protoOpt))
    {
        (*e)->addError(ctx->getStart(), "FIXME: 138");
        return *e;
    }

    const Protocol *proto = std::get<const Protocol *>(protoOpt);
    // if(proto->containsLoop()) // FIXME: DELETE FN?
    if(this->inLoop)
    {
        return errorHandler.addError(ctx->getStart(), "Currently cannot include looping protocol within closeable block. Instead, move loop outside block or use higher-order channels.");
    }
    else if(!proto->areHigherOrderChannelsClosable())
    {
        return errorHandler.addError(ctx->getStart(), "All higher-order channels within closeable must be of form Channel<Closable<P>>");
    }
    // FIXME: NEED TO ALSO CHECK AGAINST LINEAR RESOURCES IN GENERAL!!  AND NEED TO ADD TEST CASES!!!

    return new ProtocolClose(toSequence(proto));
}