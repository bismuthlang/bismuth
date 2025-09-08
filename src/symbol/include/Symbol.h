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
#include <memory>

#include "Type.h"
#include "TypeDefs.h"
#include "FQN.h"

class Scope; 

// FIXME: Make these apply directly in semantic analysis---particularly with paths!
enum VisibilityModifier {
    PUBLIC,         // Globally accessible
    PUBLIC_LINK,    // Can be linked globally, but private for semantics (used for externs and imports)
    PRIVATE
};

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

    Symbol(Symbol& sym) = delete;
    // {
    //     identifier = sym.identifier; 
    //     type = sym.type->getCopy(); 
    //     global = sym.global;
    //     // FIXME: is this constructor needed? If so, do we need to add uniqName and scope?
    // }

    virtual ~Symbol() {
        std::cerr << "61 - SYMBOL DELETED - " << toString() << std::endl;
    }; 

    std::string toString() const;
    const Type * getType() const; 

    bool isGlobal() const; 
    virtual bool isDefinition() const; 

    virtual std::string getUniqueNameInScope() const; 
    virtual std::string getScopedIdentifier() const; 
    virtual std::string getFullyQualifiedName() const { return identifier->getFullyQualifiedName(); }

    Identifier * getIdentifier() const { return identifier; }

    virtual std::shared_ptr<Symbol> getCopy();


    void updateIdentifier(Identifier * nxt); // TODO: DO BETTER, USED ONLY FOR TEMPLATES!
};

class LocatableSymbol : public Symbol 
{
public: 
    LocatableSymbol(Identifier * id, const Type *t, bool glob, Scope& s)
        : Symbol(id, t, glob)
        , scope(s)
    {}

    LocatableSymbol(LocatableSymbol& sym) = delete;
    //     : Symbol(sym)
    //     , scope(sym.scope)
    // {
    //     // sym.scope = scope;  
    // }


    Scope& getScope() const; 

private: 
    Scope& scope; 
};

class DefinitionSymbol : public LocatableSymbol 
{
public: 
    DefinitionSymbol(VisibilityModifier v, Identifier * id, const Type *t, bool glob, Scope& s, Scope * i)
        : LocatableSymbol(id, t, glob, s)
        , innerScope(i)
        , visibility(v)
    {} 

    DefinitionSymbol(DefinitionSymbol& sym) = delete;
    //     : LocatableSymbol(sym)
    // {
    //     this->innerScope = sym.innerScope;
    //     this->visibility = sym.visibility;
    // }

    virtual ~DefinitionSymbol() = default; 

    bool isDefinition() const override { return true; }

    Scope& getInnerScope() const { return *innerScope; }

    VisibilityModifier getVisibility() { return visibility; }

    std::shared_ptr<Symbol> getCopy() override;

private:
    Scope * innerScope; 
    VisibilityModifier visibility; 
};

class AliasSymbol : public LocatableSymbol 
{
public:
    AliasSymbol(Identifier * id, Scope& s, const Type * t, Identifier * a)//Symbol * a)
        : LocatableSymbol(id, t, true, s)
        , orig(a)
    {}

    virtual std::string getFullyQualifiedName() const override {
        return orig->getFullyQualifiedName(); 
    }
    // std::string getUniqueNameInScope() const override {
    //     return orig->getUniqueNameInScope();
    // }

    std::shared_ptr<Symbol> getCopy() override;

    bool isDefinition() const override { return true; }

    private:
        Identifier * orig; 
};



/****************************************
 * Utility Functions
 ****************************************/

template<typename T> 
inline optional_ref<T> symbol_cast(Symbol & sym) 
{
    if(T* ans = dynamic_cast<T*>(&sym))
    {
        return *ans; 
    }
    return std::nullopt;
}

template<typename T> 
inline optional_ref<T> symbol_cast(std::reference_wrapper<Symbol> sym) 
{
    return symbol_cast<T>(sym.get());
}

template<typename T> 
inline optional_ref<const T> symbol_cast(const Symbol & sym) 
{
    if(T* ans = dynamic_cast<T*>(&sym))
    {
        return *ans; 
    }
    return std::nullopt;
}

template<typename T> 
inline optional_ref<const T> symbol_cast(std::reference_wrapper<const Symbol> sym) 
{
    return symbol_cast<T>(sym.get());
}
