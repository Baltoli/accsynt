#pragma once

#include <dist/utils.h>

#include <iostream>
#include <memory>
#include <variant>
#include <vector>

namespace accsynt {

class Shape;

struct Nest {
  Nest(int i, size_t n);

  int ID;
  Shape *shape;
};

struct EmptySlot {};

using Slot = std::variant<
  int,
  Nest,
  EmptySlot
>;

class Shape {
public:
  Shape(size_t n) :
    n_loops{n}, slots{}
  {
    for(auto i = 0u; i < n_loops; ++i) {
      slots.emplace_back(EmptySlot{});
    }
  }

  template <typename Iterator>
  void set_loop_id(int id, Iterator it);

  void set_loop_id(int id, std::vector<int> idx);

  friend std::ostream& operator<<(std::ostream& os, Shape const& shape)
  {
    auto printer = visitor{
      [&](int i) {
        os << "L" << i << " "; 
      },

      [&](Nest n) {
        os << "L" << n.ID;
        os << "[" << *n.shape << "] ";
      },

      [&](EmptySlot) {}
    };

    for(auto& slot : shape.slots) {
      std::visit(printer, slot);
    }
    os << '\b';

    return os;
  }

private:
  const size_t n_loops;
  std::vector<Slot> slots;
};

void Shape::set_loop_id(int id, std::vector<int> idx)
{
  auto iter = begin(idx);
  set_loop_id(id, iter);
}

template <typename Iterator>
void Shape::set_loop_id(int id, Iterator it)
{
  auto& slot = slots.at(*it);

  auto setter = visitor{
    [&] (EmptySlot) {
      slot.template emplace<int>(id);
    },

    [&] (int i) {
      slot.template emplace<Nest>(Nest{i, n_loops});
      auto nest = std::get<Nest>(slot);
      nest.shape->set_loop_id(id, ++it);
    },

    [&] (Nest nest) {
      nest.shape->set_loop_id(id, ++it);
    }
  };

  std::visit(setter, slot);
}

Nest::Nest(int i, size_t n) :
  ID(i), shape(new Shape(n)) 
{
}

}
