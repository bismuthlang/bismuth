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

//   std::cout << "Trying opt " << __FILE__<<":"<< __LINE__<<" "#type" "#id" "#expr << std::endl;

#define IMPL_DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(type, id, expr, ctx, message, tmp) \
  std::optional<type> tmp = expr; \
  if(!tmp) { \
    return errorHandler.addError(ctx->getStart(), message); \
  } \
  type id = tmp.value(); \

#define IMPL_DEFINE_OR_PROPAGATE_VARIANT_IERR(type, id, expr, ctx, tmp) \
    std::variant<type, InternalBismuthError> tmp = expr; \
    if(InternalBismuthError *e = std::get_if<InternalBismuthError>(&tmp)) \
    { \
        return errorHandler.addError(ctx->getStart(), e->toString()); \
    } \
    type id = std::get<type>(tmp); \

#define IMPL_DEFINE_OR_PROPAGATE_VARIANT_WMSG(type, id, expr, ctx, message, tmp) \
  std::variant<type, ErrorChain*> tmp = expr; \
  if (ErrorChain **e = std::get_if<ErrorChain *>(&tmp)) \
  { \
    return (*e)->addError(ctx->getStart(), message); \
  } \
  type id = std::get<type>(tmp); \

#define IMPL_DEFINE_OR_PROPAGATE_VARIANT(type, id, expr, ctx, tmp) \
  std::variant<type, ErrorChain*> tmp = expr; \
  if (ErrorChain **e = std::get_if<ErrorChain *>(&tmp)) \
  { \
    return (*e)->addErrorAt(ctx->getStart()); \
  } \
  type id = std::get<type>(tmp); \

# define DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(type, id, expr, ctx, message) IMPL_DEFINE_OR_PROPAGATE_OPTIONAL_WMSG(MACRO_ARG(type), id, MACRO_ARG(expr), ctx, message, IMPL_MACRO_CONCAT(id, _COUNTER__))
# define DEFINE_OR_PROPAGATE_VARIANT_WMSG(type, id, expr, ctx, message) IMPL_DEFINE_OR_PROPAGATE_VARIANT_WMSG(MACRO_ARG(type), id, MACRO_ARG(expr), ctx, message, IMPL_MACRO_CONCAT(id, __COUNTER__))
# define DEFINE_OR_PROPAGATE_VARIANT(type, id, expr, ctx) IMPL_DEFINE_OR_PROPAGATE_VARIANT(MACRO_ARG(type), id, MACRO_ARG(expr), ctx, IMPL_MACRO_CONCAT(id, __COUNTER__))

# define DEFINE_OR_PROPAGATE_VARIANT_IERR(type, id, expr, ctx) IMPL_DEFINE_OR_PROPAGATE_VARIANT_IERR(MACRO_ARG(type), id, MACRO_ARG(expr), ctx, IMPL_MACRO_CONCAT(id, __COUNTER__))



#define STR1(x) #x
#define STR(x) STR1(x)

# define IMPL_WRAPPED_DYNAMIC_CAST(type, tmp, expr, tmpEval) \
  auto tmpEval = expr;\
  type tmp = dynamic_cast<type>(tmpEval); \
  assert(tmp != nullptr && "Failed to cast to " #type  ); \

# define WRAPPED_DYNAMIC_CAST(type, id, expr) \
    IMPL_WRAPPED_DYNAMIC_CAST(MACRO_ARG(type), id, MACRO_ARG(expr), IMPL_MACRO_CONCAT(id, __COUNTER__))


# define IMPL_WRAPPED_ANY_CAST(type, tmp, expr, tmpEval) \
  auto tmpEval = expr;\
  type tmp = any_cast<type>(tmpEval); \
  assert(tmp != nullptr && "Failed to cast to " #type  ); \

# define WRAPPED_ANY_CAST(type, id, expr) \
    IMPL_WRAPPED_ANY_CAST(MACRO_ARG(type), id, MACRO_ARG(expr), IMPL_MACRO_CONCAT(id, __COUNTER__))
