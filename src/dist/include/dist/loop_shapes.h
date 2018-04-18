#pragma once

#include <iostream>
#include <memory>

namespace accsynt {

struct Shape {
  virtual size_t size() const = 0;
  virtual Shape *copy() const = 0;
  virtual std::string str() const = 0;
};

struct Hole : public Shape {
  size_t size() const override 
  { 
    return 1; 
  }

  Shape *copy() const override
  {
    return new Hole(*this);
  }

  std::string str() const override
  {
    return "()";
  }
};

struct Nest : public Shape {
  template <typename T>
  Nest(T&& t) : inner(t.copy()) {}

  size_t size() const override
  {
    return 1 + inner->size();
  }

  Shape *copy() const override
  {
    return new Nest(*inner);
  }

  std::string str() const override
  {
    return "(" + inner->str() + ")";
  }

  const std::unique_ptr<Shape> inner;
};

std::ostream& operator<<(std::ostream& os, const Shape& s)
{
  os << s.str();
  return os;
}

}
