#pragma once
#include <optional>
#include <variant>
#include <vector>
#include "TypedAST.h"
#include "BismuthErrorHandler.h"

#include <fplus/fplus.hpp>

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




template<typename T>
std::pair<std::vector<T>, std::vector<ErrorChain*>> 
collect_separate_results (std::vector<std::variant<T, ErrorChain *>> input)
{
  std::vector<T> res; 
  std::vector<ErrorChain *> errors; 

  for(auto ele : input)
  {
    if (ErrorChain **e = std::get_if<ErrorChain *>(&ele))
    {
      errors.push_back(*e);
    }
    else if(T * a = std::get_if<T>(&ele))
    {
      res.push_back(*a);
    }
  }

  return {res, errors};
}


template<typename T>
std::variant<std::vector<T>, ErrorChain*> 
collect_results (std::vector<std::variant<T, ErrorChain *>> input)
{
  std::vector<T> res; 
  std::vector<ErrorChain *> errors; 

  for(auto ele : input)
  {
    if (ErrorChain **e = std::get_if<ErrorChain *>(&ele))
    {
      errors.push_back(*e);
    }
    else if(T * a = std::get_if<T>(&ele))
    {
      res.push_back(*a);
    }
  }

  if(!errors.empty())
  {
    return fplus::reduce_1(
      [](auto a, auto b) { return a->addBranch(b); }, 
      errors
    );
  }

  return res;
}

inline std::optional<ErrorChain *> 
collect_optionals(std::vector<std::optional<ErrorChain *>> input)
{
  if(input.empty()) return std::nullopt; 
  
  return fplus::reduce_1(
    [](auto a, auto b) -> std::optional<ErrorChain *> {
      if(a.has_value())
      {
        if(b.has_value())
        {
          return a.value()->addBranch(b.value());
        }
        return a;
      }

      return b;
    },
    input
  );
}