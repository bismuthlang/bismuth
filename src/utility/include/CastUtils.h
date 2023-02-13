#pragma once

template <typename T>
std::optional<T> anyOpt2Val(const std::any &a) // https://stackoverflow.com/questions/66969536/how-to-correctly-check-any-cast-available
{
    if (const std::optional<T> *v = std::any_cast<std::optional<T>>(&a))
        return *v;
    return {};
}

template <typename T>
std::optional<T> any2Opt(const std::any &a) // https://stackoverflow.com/questions/66969536/how-to-correctly-check-any-cast-available
{
    if (const T *v = std::any_cast<T>(&a))
        return *v;
    else
        return {};
}


template <typename T>
std::variant<T *, ErrorChain*> anyOpt2VarError(WPLErrorHandler errorHandler, const std::any &a) // https://stackoverflow.com/questions/66969536/how-to-correctly-check-any-cast-available
{
    std::optional<std::variant<T *, ErrorChain*>> opt = any2Opt<std::variant<T *, ErrorChain*>>(a);

    if(opt) {
        std::variant<T *, ErrorChain*> val = opt.value(); 
     return val;    
    }
    // if (T **v = std::any_cast<T*>(&a))
    //     return *v;  
    return errorHandler.newErrorChain();
}

template<typename T, typename std::enable_if<std::is_base_of<TypedNode, T>::value>::type* = nullptr>
std::variant<TypedNode *, ErrorChain*> TNVariantCast(std::variant<T*, ErrorChain*> base) {
    // if(std::variant<T*, ErrorChain*>)
    if(std::holds_alternative<T*>(base)) {
        return (TypedNode*) std::get<T*>(base);
    }

    return std::get<ErrorChain*>(base);
}