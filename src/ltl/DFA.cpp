#include "DFA.h"

DFA::DFA(bool demo) {
    if (demo) {
        this->demoSym = new Symbol("@dfa::demo", new TypeBool(false), false, false);
    } else {
        this->demoSym = std::nullopt;
    }
}

void DFA::genInit(GenCx &cx) {
    if (this->demoSym) {
        cx.body.push_back(new TVarDeclNode({new AssignmentNode({this->demoSym.value()}, new TBooleanConstNode(false, cx.rootTok))}, cx.rootTok));
    }
}

void DFA::genLabel(GenCx &cx, std::string label) {
    if (!this->demoSym) { return; }
    
    TypedNode *condition;
    if (label == "ready") {
        condition = new TFieldAccessNode(cx.rootTok, this->demoSym.value(), true);
    } else if (label == "unready") {
        condition = new TUnaryExprNode(UnaryOperator::UNARY_NOT, new TFieldAccessNode(cx.rootTok, this->demoSym.value(), true), cx.rootTok);
    } else {
        return; // don't care
    }

    std::vector<TypedNode *> restoreBody = std::exchange(cx.body, {});

    genFail(cx);

    TBlockNode *consequent = new TBlockNode(cx.body, cx.rootTok);

    cx.body = restoreBody;

    TAssignNode *update = new TAssignNode(
        new TFieldAccessNode(cx.rootTok, this->demoSym.value(), false),
        new TUnaryExprNode(UnaryOperator::UNARY_NOT, new TFieldAccessNode(cx.rootTok, this->demoSym.value(), true), cx.rootTok),
        cx.rootTok
    );

    cx.body.push_back(new TConditionalStatementNode(cx.rootTok, condition, consequent, {update}));
}
