/**
 * @file CompilerFlags.h
 * @author Alex Friedman (ahfriedman.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "antlr4-runtime.h"
#include <string>
#include <vector>
#include <sstream>

/**
 * @brief Enum containing information that we may need to send to the compiler to make it perform specific operations.
 * 
 */
enum CompilerFlags 
{
  NO_RUNTIME = 1, //Used to represent that the program will NOT use a runtime (and thus we should generate a main method manually)
};