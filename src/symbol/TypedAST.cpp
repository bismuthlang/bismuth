#include "TypedAST.h"

std::optional<Value *> TypedASTVisitor::visit(CompCodeWrapper *n)
{
    return n->generator(); 
}