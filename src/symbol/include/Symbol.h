#pragma once

/**
 * @file Symbol.h
 * @author Alex Friedman (ahfriedman.com)
 * @brief Stores information about a specific symbol in the language. Based on starter code.
 * @version 0.1
 * @date 2022-09-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <string>  //Includes strings
#include <sstream> //Used for string streams
#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"

#include <any>      // Needed for anycasts
#include <utility>  // Needed for anycasts
#include <vector>   // Vectors
#include <optional> // Optionals

#include "Type.h"

// using namespace Types; 

/*******************************************
 *
 * Symbol Definition
 *
 *******************************************/
struct Symbol
{
    std::string identifier; // Mostly needed for our tostring function
    const Type *type;       // Keeps track of the symbol's type

    std::optional<llvm::AllocaInst *> val;

    bool isGlobal;

    /**
     * @brief Tracks if symbol cna be modified at all or if it is a definition
     * 
     */
    bool isDefinition; 

    // Constructs a symbol from an ID and symbol type.
    Symbol(std::string id, const Type *t, bool definition, bool glob)
    {
        identifier = id;
        type = t;
        isGlobal = glob;
        isDefinition = definition; 

        val = {};
    }

    std::string getIdentifier() const { return identifier; }

    std::string toString() const
    {
        std::ostringstream description;
        std::string typeName = type->toString(); // getStringFor(type);
        description << '[' << identifier << ", " << typeName << ']';
        return description.str();
    }
};
