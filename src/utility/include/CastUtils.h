#pragma once
#include <optional>
#include <variant>
#include "TypedAST.h"
#include "BismuthErrorHandler.h"

// template<typename I, typename E>
// std::optional<E&> cast_ref(I& i)
// {
//     try {
//         E& val = dynamic_cast<E&>(i);
//         return val; 
//     }
//     catch(const std::bad_cast& e) {
//         return std::nullopt; 
//     }
// }



#define IMPL_MACRO_CONCAT(a,b) a##b
#define MACRO_ARG(...) __VA_ARGS__

#define IMPL_DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(type, id, expr, ctx, message, tmp) \
  std::optional<type> tmp = expr; \
  if(!tmp) { \
    return errorHandler.addError(ctx->getStart(), message); \
  } \
  std::cout << "Trying opt " << __FILE__<<":"<< __LINE__<<" "#type" "#id" "#expr << std::endl; \
  type id = tmp.value(); \

#define IMPL_DEFINE_OR_PROPAGATE_VARIANT_WMSG(type, id, expr, ctx, message, tmp) \
  std::variant<type, ErrorChain*> tmp = expr; \
  if (ErrorChain **e = std::get_if<ErrorChain *>(&tmp)) \
  { \
    return (*e)->addError(ctx->getStart(), message); \
  } \
  std::cout << "Trying "<< __FILE__<<":"<< __LINE__<<" "#type" "#id" "#expr << std::endl; \
  type id = std::get<type>(tmp); \
  std::cout << "Yay" << std::endl; \

#define IMPL_DEFINE_OR_PROPAGATE_VARIANT(type, id, expr, ctx, tmp) \
  std::variant<type, ErrorChain*> tmp = expr; \
  if (ErrorChain **e = std::get_if<ErrorChain *>(&tmp)) \
  { \
    return (*e)->addErrorAt(ctx->getStart()); \
  } \
  std::cout << "Trying "<< __FILE__<<":"<< __LINE__<<" "#type" "#id" "#expr << std::endl; \
  type id = std::get<type>(tmp); \
  std::cout << "Yay" << std::endl; \

# define DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(type, id, expr, ctx, message) IMPL_DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(MACRO_ARG(type), id, MACRO_ARG(expr), ctx, message, IMPL_MACRO_CONCAT(id, _COUNTER__))
# define DEFINE_OR_PROPAGATE_VARIANT_WMSG(type, id, expr, ctx, message) IMPL_DEFINE_OR_PROPAGATE_VARIANT_WMSG(MACRO_ARG(type), id, MACRO_ARG(expr), ctx, message, IMPL_MACRO_CONCAT(id, __COUNTER__))
# define DEFINE_OR_PROPAGATE_VARIANT(type, id, expr, ctx) IMPL_DEFINE_OR_PROPAGATE_VARIANT(MACRO_ARG(type), id, MACRO_ARG(expr), ctx, IMPL_MACRO_CONCAT(id, __COUNTER__))


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
    details << "Unable to cast " << a.type().name() << " to Variant<" << typeid(T).name() << "*, ErrorChain*>.";
    return errorHandler.addCompilerError(nullptr, details.str());
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