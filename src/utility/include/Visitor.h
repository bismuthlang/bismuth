#pragma once

#include "MacroUtils.h"

// using namespace std;

template<typename T, typename R>
class Visitor;

template<typename T>
class AnyVisitor;

class VisitorBase {
  public:
    virtual ~VisitorBase() {}
};

class VisitableBase {
  public:
    virtual std::any Nuaccept_any(VisitorBase&) = 0; // const = 0;
    virtual ~VisitableBase() {}
};

template<typename I>
class Visitable : public VisitableBase {
  public:
    std::any Nuaccept_any(VisitorBase& v) override { // const override
      WRAPPED_DYNAMIC_CAST(MACRO_ARG(AnyVisitor<I> *), visitor, &v);
      WRAPPED_DYNAMIC_CAST(MACRO_ARG(I*), castedThis, this);
      I& ref = *castedThis;
      return visitor->visit_any(ref); // const I&
    }

    template<typename R>
    R Nuaccept(Visitor<I, R> & visitor) { // WAS CONST
      WRAPPED_DYNAMIC_CAST(MACRO_ARG(I*), castedThis, this);
      I& ref = *castedThis;
        return visitor.visit(ref); // const I&
    }
};

template<typename T>
class AnyVisitor : public virtual VisitorBase {
  public:
    virtual std::any visit_any(T& t) = 0; // const T&
};

template<typename T, typename R>
class Visitor : public virtual AnyVisitor<T> {
  public:
    virtual R visit_typed(T& t) = 0; // const T&

    virtual std::any visit_any(T& t) override { // const T&
      return visit_typed(t);
    }

    virtual R visit(T& t) { // const T&
      return any_cast<R>(t.Nuaccept_any(*this));
    }
};