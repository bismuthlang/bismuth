/**
 * @file BismuthInternalError.h
 * @author Alex Friedman (ahfriedman.com)
 * @brief Handles errors internal to Bismuth in a standalone manner
 * @version 0.1
 * @date 2025-02-09
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <string>
#include <vector>
#include <optional>


/**
 * @brief Defines an error in the language
 *
 */
struct InternalBismuthError
{
    InternalBismuthError(std::string msg)
        : message(msg)
    {}
    std::string toString() { return message; }
private: 
    std::string message;  // Error Message text
};