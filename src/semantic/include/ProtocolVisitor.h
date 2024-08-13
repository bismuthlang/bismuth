/**
 * @file ProtocolVisitor.h
 * @author Alex Friedman (ahfriedman.com)
 * @brief Visitor for protocols. Each protocol should be visited by a unique ProtocolVisitor
 * @version 1.3.4
 * @date 2023-08-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include "BismuthBaseVisitor.h"
#include "BismuthErrorHandler.h"
#include "CastUtils.h"
#include "SemanticVisitor.h"

#include <variant>
// typedef std::variant<Value, START_LOOP, END_LOOP, SEL> Message;
// typedef
class SemanticVisitor;

class ProtocolVisitor : public BismuthBaseVisitor
{

public:
    ProtocolVisitor(BismuthErrorHandler &eh, SemanticVisitor *sv) : errorHandler(eh), semanticVisitor(sv) // inLoop(inL)
    {
    }

    std::string getErrors() { return errorHandler.errorList(); }
    bool hasErrors(int flags) { return errorHandler.hasErrors(flags); }

    // From C++ Documentation for visitors
    template <class... Ts>
    struct overloaded : Ts...
    {
        using Ts::operator()...;
    };
    template <class... Ts>
    overloaded(Ts...) -> overloaded<Ts...>;

    /*
     *  Protocols
     */
    std::variant<const ProtocolSequence *, ErrorChain *> visitProto(BismuthParser::ProtocolContext *ctx);
    std::variant<const ProtocolRecv *, ErrorChain *> visitProto(BismuthParser::RecvTypeContext *ctx);
    std::variant<const ProtocolSend *, ErrorChain *> visitProto(BismuthParser::SendTypeContext *ctx);
    std::variant<const ProtocolWN *, ErrorChain *> visitProto(BismuthParser::WnProtoContext *ctx);
    std::variant<const ProtocolOC *, ErrorChain *> visitProto(BismuthParser::OcProtoContext *ctx);
    std::variant<const ProtocolEChoice *, ErrorChain *> visitProto(BismuthParser::ExtChoiceProtoContext *ctx);
    std::variant<const ProtocolIChoice *, ErrorChain *> visitProto(BismuthParser::IntChoiceProtoContext *ctx);
    std::variant<const ProtocolClose *, ErrorChain *> visitProto(BismuthParser::CloseableProtoContext *ctx);

    std::any visitProtocol(BismuthParser::ProtocolContext *ctx) override { return ProtoVariantCast<ProtocolSequence>(visitProto(ctx)); }            //{ return visitProto(ctx); }
    std::any visitRecvType(BismuthParser::RecvTypeContext *ctx) override { return ProtoVariantCast<ProtocolRecv>(visitProto(ctx)); }                //{ return visitProto(ctx); }
    std::any visitSendType(BismuthParser::SendTypeContext *ctx) override { return ProtoVariantCast<ProtocolSend>(visitProto(ctx)); }                //{ return visitProto(ctx); }
    std::any visitWnProto(BismuthParser::WnProtoContext *ctx) override { return ProtoVariantCast<ProtocolWN>(visitProto(ctx)); }                    //{ return visitProto(ctx); }
    std::any visitOcProto(BismuthParser::OcProtoContext *ctx) override { return ProtoVariantCast<ProtocolOC>(visitProto(ctx)); }                    //{ return visitProto(ctx); }
    std::any visitExtChoiceProto(BismuthParser::ExtChoiceProtoContext *ctx) override { return ProtoVariantCast<ProtocolEChoice>(visitProto(ctx)); } //{ return visitProto(ctx); }
    std::any visitIntChoiceProto(BismuthParser::IntChoiceProtoContext *ctx) override { return ProtoVariantCast<ProtocolIChoice>(visitProto(ctx)); } //{ return visitProto(ctx); }
    std::any visitCloseableProto(BismuthParser::CloseableProtoContext *ctx) override { return ProtoVariantCast<ProtocolClose>(visitProto(ctx)); }   //{ return visitProto(ctx); }

private:
    BismuthErrorHandler &errorHandler;
    SemanticVisitor *semanticVisitor;
    bool inLoop = false;
    bool inClose = false;
    unsigned int closeNumber = 0; // Used for numbering close blocks

    inline const ProtocolSequence *toSequence(const Protocol *proto)
    {
        if (const ProtocolSequence *seq = dynamic_cast<const ProtocolSequence *>(proto))
        {
            return seq;
        }

        vector<const Protocol *> a;
        a.push_back(proto);

        return new ProtocolSequence(proto->isInCloseable(), a);
    }
};
