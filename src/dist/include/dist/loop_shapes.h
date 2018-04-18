#pragma once

#include <cassert>
#include <cmath>
#include <memory>
#include <string>

namespace accsynt {

struct Shape {
  virtual bool eq(Shape *const other) const = 0;
  virtual std::string str() const = 0;
};

struct Hole : Shape {
  bool eq(Shape *const other) const override
  {
    auto other_hole = dynamic_cast<Hole*>(other);
    return other_hole != nullptr;
  }

  std::string str() const override
  {
    return "()";
  }
};

struct Seq : Shape {
  template <typename F, typename S>
  Seq(F f, S s) :
    first(new F(f)),
    second(new S(s)) {}

  bool eq(Shape *const other) const override
  {
    auto other_seq = dynamic_cast<Seq*>(other);
    if(other_seq) {
      return other_seq->first->eq(first.get()) && 
             other_seq->second->eq(second.get());
    }

    return false;
  }

  std::string str() const override
  {
    return first->str() + " " + second->str();
  }

  const std::unique_ptr<Shape> first;
  const std::unique_ptr<Shape> second;
};

struct Nest : Shape {
  template <typename I>
  Nest(I in) :
    inner(new I(in)) {}

  bool eq(Shape *const other) const override
  {
    auto other_nest = dynamic_cast<Nest*>(other);
    if(other_nest) {
      return other_nest->inner->eq(inner.get());
    }

    return false;
  }

  std::string str() const override
  {
    return "(" + inner->str() + ")";
  }

  const std::unique_ptr<Shape> inner;
};

int num_shapes(int loops)
{
  if (loops <= 1) {
    return 1;
  } else {
    return (3 * num_shapes(loops - 1));
  }
}

}
