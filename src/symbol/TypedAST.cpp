#include "TypedAST.h"

// #include "CastUtils.h"

std::optional<Value *> TypedASTVisitor::visit(CompCodeWrapper &n)
{
    return n.generator(); 
}



bool TypedAST::endsInReturn(vector<TypedNode *> n)
{
    if (n.size() == 0)
        return false;
    return TypedAST::endsInReturn(*n.at(n.size() - 1));
}

bool TypedAST::endsInReturn(TypedNode & n)
{
    if (dynamic_cast<TReturnNode *>(&n))
        return true;
    if (dynamic_cast<TExitNode*>(&n))
        return true;

    if (auto bn = dynamic_cast<TBlockNode *>(&n))
    {
        return endsInReturn(bn->exprs);
    }

    if (auto cn = dynamic_cast<TConditionalStatementNode *>(&n))
    {
        if(cn->post.size())
            return endsInReturn(cn->post);
        
        if(cn->falseOpt) 
        {
            return endsInReturn(*cn->falseOpt.value()) && endsInReturn(*cn->trueBlk);
        }

        return false; 
    }

    if (auto cn = dynamic_cast<TMatchStatementNode *>(&n))
    {
        if(cn->post.size())
            return endsInReturn(cn->post);
        
        for(auto branch : cn->cases)
            if(!endsInReturn(*branch.second))
                return false; 
        return true; 
    }

    if (auto cn = dynamic_cast<TSelectStatementNode *>(&n))
    {
        if(cn->post.size())
            return endsInReturn(cn->post);
        
        for(auto branch : cn->nodes)
            if(!endsInReturn(*branch))
                return false; 
        return true; 
    }

    if(auto cn = dynamic_cast<TSelectAlternativeNode *>(&n))
    {
        return endsInReturn(*cn->eval);
    }
    
    return false;
}


bool TypedAST::endsInBranch(vector<TypedNode *> n)
{
    if (n.size() == 0)
        return false;
    return TypedAST::endsInBranch(*n.at(n.size() - 1));
}

bool TypedAST::endsInBranch(TypedNode & n)
{
    if (TBlockNode *bn = dynamic_cast<TBlockNode *>(&n))
    {
        return endsInBranch(bn->exprs);
    }

    // FIXME: DO THESE BETTER!
    if (TConditionalStatementNode *cn = dynamic_cast<TConditionalStatementNode *>(&n))
    {
        return true; 
    }

    if (TMatchStatementNode *cn = dynamic_cast<TMatchStatementNode *>(&n))
    {
        return true; 
    }

    if (TSelectStatementNode *cn = dynamic_cast<TSelectStatementNode *>(&n))
    {
        return true; 
    }

    if (TSelectAlternativeNode *cn = dynamic_cast<TSelectAlternativeNode *>(&n))
    {
        return endsInBranch(*cn->eval);
        // return true; 
    }

    if(TChannelCaseStatementNode * sn = dynamic_cast<TChannelCaseStatementNode*>(&n))
    {
        return true; 
    }

    return false;
}