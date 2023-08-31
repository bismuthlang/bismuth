#pragma once
#include <optional>
#include <variant>
#include "TypedAST.h"

template <typename T>
std::optional<T> anyOpt2Val(const std::any &a) // https://stackoverflow.com/questions/66969536/how-to-correctly-check-any-cast-available
{
    if (const std::optional<T> *v = std::any_cast<std::optional<T>>(&a))
        return *v;
    return std::nullopt;
}

template <typename T>
std::optional<T> any2Opt(const std::any &a) // https://stackoverflow.com/questions/66969536/how-to-correctly-check-any-cast-available
{
    if (const T *v = std::any_cast<T>(&a))
        return *v;
    else
        return std::nullopt;
}


template <typename T>
std::variant<T *, ErrorChain*> anyOpt2VarError(BismuthErrorHandler& errorHandler, const std::any &a) // https://stackoverflow.com/questions/66969536/how-to-correctly-check-any-cast-available
{
    std::optional<std::variant<T *, ErrorChain*>> opt = any2Opt<std::variant<T *, ErrorChain*>>(a);

    if(opt) {
        std::variant<T *, ErrorChain*> val = opt.value(); 
        return val;    
    }

    std::ostringstream details;
    details << "Unable to cast " << a.type().name() << " to Variant<" << typeid(T).name() << "*, ErrorChain*>. This most likely an internal compiler error.";
    return errorHandler.addError(nullptr, details.str());
}

template<typename T, typename std::enable_if<std::is_base_of<TypedNode, T>::value>::type* = nullptr>
std::variant<TypedNode *, ErrorChain*> TNVariantCast(std::variant<T*, ErrorChain*> base) {
    // if(std::variant<T*, ErrorChain*>)
    if(std::holds_alternative<T*>(base)) {
        return (TypedNode*) std::get<T*>(base);
    }

    return std::get<ErrorChain*>(base);
}

template<typename T, typename std::enable_if<std::is_base_of<Protocol, T>::value>::type* = nullptr>
std::variant<const Protocol *, ErrorChain*> ProtoVariantCast(std::variant<const T*, ErrorChain*> base) {
    // if(std::variant<T*, ErrorChain*>)
    if(std::holds_alternative<const T*>(base)) {
        return (const Protocol*) std::get<const T*>(base);
    }

    return std::get<ErrorChain*>(base);
}

template<typename T, typename std::enable_if<std::is_base_of<Type, T>::value>::type* = nullptr>
std::variant<const Type *, ErrorChain*> TypeVariantCast(std::variant<const T*, ErrorChain*> base) {
    // if(std::variant<T*, ErrorChain*>)
    if(std::holds_alternative<const T*>(base)) {
        return (const Type*) std::get<const T*>(base);
    }

    return std::get<ErrorChain*>(base);
}