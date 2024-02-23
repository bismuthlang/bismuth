#pragma once

#include "antlr4-runtime.h"
#include <sstream>

/**
 * @file SymbolUtils.h
 * @author Alex Friedman (ahf.dev)
 * @brief 
 * @version 0.1
 * @date 2023-10-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
enum DisplayMode {
    C_STYLE, 
    MATH_STYLE
};

inline std::string tokenToLineChar(antlr4::Token *token)
{
    std::ostringstream e;
    e << token->getLine() + ':' + token->getCharPositionInLine();

    return e.str(); 
}