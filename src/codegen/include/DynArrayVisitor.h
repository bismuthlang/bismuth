/**
 * @file DynArrayVisitor.h
 * @author Alex Friedman (ahf.dev)
 * @brief 
 * @version 0.1
 * @date 2023-11-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 

#include "CodegenUtils.h"
#include "BismuthErrorHandler.h"


class DynArrayVisitor : public CodegenModule
{
// private:
    // BismuthErrorHandler errorHandler;


public: 
    DynArrayVisitor(Module *m, DisplayMode mode, int f, BismuthErrorHandler e) : CodegenModule(m, mode, f, e)
    {
        // errorHandler = e; // TODO: REMOVE FROM DEEPCOPYVISITOR OR NOT?
    }

};