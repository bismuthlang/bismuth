#pragma once
/**
 * @file FQN.h
 * @author Alex Friedman (ahf.dev)
 * @brief Fully qualified identifier
 * @version 0.1
 * @date 2024-01-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include <string>  //Includes strings

#include <optional> // Optionals

#include <functional>

using std::optional; 

// using namespace Types; 

/*******************************************
 *
 * Fully qualified name definition
 *
 *******************************************/





class Identifier
{
private: 
    std::string identifier;         // The name as seen in code (usually local to the scope)
    std::string uniqueNameInScope;  // Unique name for the symbol in its scope
    // Scope * scope; 

    optional<Identifier *> parent; 


public:
    optional<std::function<std::string()>> meta; 

    // Constructs a symbol from an ID and symbol type.
    Identifier(std::string id, std::string uniqName, optional<Identifier *> s) 
    {
        identifier = id;
        uniqueNameInScope = uniqName; 
        parent = s; 
    }

    Identifier(Identifier& id)
    {
        identifier = id.identifier; 
        // FIXME: is this constructor needed? If so, do we need to add uniqName and scope?

        uniqueNameInScope = id.uniqueNameInScope;
        parent = id.parent; 
    }

    // std::string toString() const;

    std::string getUniqueNameInScope() const; 
    std::string getScopedIdentifier() const; 
    std::string getFullyQualifiedName() const; 


    // FIXME: this is a hacky approach to allowing mains to be identified. Do better
    void promoteToGlobal() {
        parent = std::nullopt; 
    }
    // optional<Identifier *>  getParent() const; 
};

