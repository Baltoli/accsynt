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

  bool operator==(Nest const& other) const;

  int ID;
  Shape *shape;
};

struct EmptySlot {
  bool operator==(EmptySlot const&) const { return true; }
};

using Slot = std::variant<
  int,
  Nest,
  EmptySlot
>;

bool slot_empty(Slot slot)
{
  return std::holds_alternative<EmptySlot>(slot);
}

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

  bool operator==(Shape const& other) const;

private:
  size_t empty_count() const;

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

size_t Shape::empty_count() const
{
  return std::count_if(begin(slots), end(slots), slot_empty);
}

bool Shape::operator==(Shape const& other) const
{
  if(empty_count() != other.empty_count()) {
    return false;
  }

  auto iter = begin(slots);
  auto other_iter = begin(other.slots);

  auto find_next = [](auto& it) {
    while(slot_empty(*it)) { ++it; }
  };

  bool all = true;
  for(auto i = 0u; i < (n_loops - empty_count()); ++i) {
    find_next(iter);
    find_next(other_iter);

    all = all && (*iter == *other_iter);
  }

  return all;
}

Nest::Nest(int i, size_t n) :
  ID(i), shape(new Shape(n)) 
{
}

bool Nest::operator==(Nest const& other) const
{
  return ID == other.ID && (*shape == *other.shape);
}

}
