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

#include "FQN.h"

class Scope; 

// using namespace Types; 

/*******************************************
 *
 * Symbol Definition
 *
 *******************************************/
class Symbol
{
// public: 
private:
    Identifier * identifier; 
    const Type *type;               // The symbol's type

    bool global;                    // Determines if the symbol is globally defined or not
    // bool definition;             // Tracks if symbol can be modified at all or if it is a definition // TODO: Remove now that we have a definition symbol

    Scope * scope; 
public:
    // Constructs a symbol from an ID and symbol type.
    Symbol(Identifier * id, const Type *t, bool glob, Scope * s) 
    {
        identifier = id; 
        type = t;
        global = glob;
        // definition = d; 
        scope = s; 
    }

    Symbol(Symbol& sym)
    {
        identifier = sym.identifier; 
        type = sym.type->getCopy(); 
        global = sym.global;
        // definition = sym.definition;
        // FIXME: is this constructor needed? If so, do we need to add uniqName and scope?

        scope = sym.scope; 
    }

    virtual ~Symbol() = default; 

    // std::string getIdentifier() const; 
    std::string toString() const;
    const Type * getType() const; 

    bool isGlobal() const; 
    virtual bool isDefinition() const; 

    std::string getUniqueNameInScope() const; 
    std::string getScopedIdentifier() const; 
    std::string getFullyQualifiedName() const { return identifier->getFullyQualifiedName(); }

    Identifier * getIdentifier() const { return identifier; }

    Scope * getScope() const; 


    void updateIdentifier(Identifier * nxt); // TODO: DO BETTER, USED ONLY FOR TEMPLATES!
};

class DefinitionSymbol : public Symbol 
{
public: 
    DefinitionSymbol(Identifier * id, const Type *t, bool glob, Scope * s, Scope * i)
        : Symbol(id, t, glob, s)
        , innerScope(i)
    {} 

    DefinitionSymbol(DefinitionSymbol& sym) 
        : Symbol(sym)
    {
        sym.innerScope = this->innerScope; 
    }

    virtual ~DefinitionSymbol() = default; 

    bool isDefinition() const override { return true; }

    Scope * getInnerScope() const { return innerScope; }
private:
    Scope * innerScope; 
};