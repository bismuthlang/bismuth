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

public:
    // Constructs a symbol from an ID and symbol type.
    Symbol(Identifier * id, const Type *t, bool glob) 
    {
        identifier = id; 
        type = t;
        global = glob;
    }

    Symbol(Symbol& sym)
    {
        identifier = sym.identifier; 
        type = sym.type->getCopy(); 
        global = sym.global;
        // FIXME: is this constructor needed? If so, do we need to add uniqName and scope?
    }

    virtual ~Symbol() = default; 

    std::string toString() const;
    const Type * getType() const; 

    bool isGlobal() const; 
    virtual bool isDefinition() const; 

    virtual std::string getUniqueNameInScope() const; 
    std::string getScopedIdentifier() const; 
    std::string getFullyQualifiedName() const { return identifier->getFullyQualifiedName(); }

    Identifier * getIdentifier() const { return identifier; }

    


    void updateIdentifier(Identifier * nxt); // TODO: DO BETTER, USED ONLY FOR TEMPLATES!
};

class LocatableSymbol : public Symbol 
{
public: 
    LocatableSymbol(Identifier * id, const Type *t, bool glob, Scope * s)
        : Symbol(id, t, glob)
        , scope(s)
    {}

    LocatableSymbol(LocatableSymbol& sym) 
        : Symbol(sym)
    {
        sym.scope = scope;  
    }


    Scope * getScope() const; 

private: 
    Scope * scope; 
};

class DefinitionSymbol : public LocatableSymbol 
{
public: 
    DefinitionSymbol(Identifier * id, const Type *t, bool glob, Scope * s, Scope * i)
        : LocatableSymbol(id, t, glob, s)
        , innerScope(i)
    {} 

    DefinitionSymbol(DefinitionSymbol& sym) 
        : LocatableSymbol(sym)
    {
        sym.innerScope = this->innerScope; 
    }

    virtual ~DefinitionSymbol() = default; 

    bool isDefinition() const override { return true; }

    Scope * getInnerScope() const { return innerScope; }
private:
    Scope * innerScope; 
};


// FIXME: finish this and impl paths!
class AliasSymbol : public LocatableSymbol 
{
public:
    AliasSymbol(Identifier * id, Scope * s, Symbol * a)
        : LocatableSymbol(id, a->getType(), a->isGlobal(), s)
        , orig(a)
    {}

    std::string getUniqueNameInScope() const override {
        return orig->getUniqueNameInScope();
    }

    private:
        Symbol * orig; 
};