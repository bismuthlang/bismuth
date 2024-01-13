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

#include <optional> // Optionals


#include "Type.h"

// #include "Scope.h"

class Scope; 

// using namespace Types; 

/*******************************************
 *
 * Symbol Definition
 *
 *******************************************/
struct Symbol
{
private: 
    std::string identifier;         // The symbol's name as seen in code
    std::string uniqueNameInScope;  // Unique name for the symbol in its scope
    const Type *type;               // The symbol's type

    bool global;                    // Determines if the symbol is globally defined or not
    bool definition;                // Tracks if symbol can be modified at all or if it is a definition

    Scope * scope; 
public:
    // Constructs a symbol from an ID and symbol type.
    Symbol(std::string id, const Type *t, bool d, bool glob, std::string uniqName, Scope * s) 
    {
        identifier = id;
        type = t;
        global = glob;
        definition = d; 

        uniqueNameInScope = uniqName; 
        scope = s; 
    }

    Symbol(Symbol& sym)
    {
        identifier = sym.identifier; 
        type = sym.type->getCopy(); 
        global = sym.global;
        definition = sym.definition;
        // FIXME: is this constructor needed? If so, do we need to add uniqName and scope?
    }

    // std::string getIdentifier() const; 
    std::string toString() const;
    const Type * getType() const; 

    bool isGlobal() const; 
    bool isDefinition() const; 

    std::string getUniqueNameInScope() const; 
    std::string getScopedIdentifier() const; 
};
