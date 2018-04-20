#pragma once

#include <dist/utils.h>

#include <iostream>
#include <memory>
#include <unordered_set>
#include <variant>
#include <vector>

namespace accsynt {
  struct EmptySlot;
  struct Nest;
  class Shape;
}

namespace std {
  template <> struct hash<accsynt::Shape> {
    size_t operator()(accsynt::Shape const& slot) const;
  };

  template <> struct hash<accsynt::EmptySlot> {
    size_t operator()(accsynt::EmptySlot const& slot) const;
  };

  template <> struct hash<accsynt::Nest> {
    size_t operator()(accsynt::Nest const& slot) const;
  };
}

namespace accsynt {

class Indexer {
public:
  Indexer(int n) :
    length_(n), indexes_(n*n, 0), ids_(length_, 0)
  {
    std::iota(begin(ids_), end(ids_), 0);
  }

  std::unordered_set<Shape> all_loops();
  bool set_next_indexes(Shape& shape);

private:
  int length_;
  std::vector<int> indexes_;
  std::vector<int> ids_;
};

struct Nest {
  Nest(int i, int n);

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
  friend struct std::hash<Shape>;

public:
  Shape(int n) :
    n_loops{n}, slots{}
  {
    for(auto i = 0; i < n_loops; ++i) {
      slots.emplace_back(EmptySlot{});
    }
  }

  template <typename Iterator>
  void set_loop_id(int id, Iterator begin, Iterator end);

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

protected:
  size_t empty_count() const;

  const int n_loops;
  std::vector<Slot> slots;
};

void Shape::set_loop_id(int id, std::vector<int> idx)
{
  set_loop_id(id, begin(idx), end(idx));
}

template <typename Iterator>
void Shape::set_loop_id(int id, Iterator begin, Iterator end)
{
  if(begin == end) {
    return;
  }

  auto& slot = slots.at(*begin);

  auto setter = visitor{
    [&] (EmptySlot) {
      slot.template emplace<int>(id);
    },

    [&] (int i) {
      slot.template emplace<Nest>(Nest{i, n_loops});
      auto nest = std::get<Nest>(slot);
      nest.shape->set_loop_id(id, begin+1, end);
    },

    [&] (Nest nest) {
      nest.shape->set_loop_id(id, begin+1, end);
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

Nest::Nest(int i, int n) :
  ID(i), shape(new Shape(n)) 
{
}

bool Nest::operator==(Nest const& other) const
{
  return ID == other.ID && (*shape == *other.shape);
}

bool Indexer::set_next_indexes(Shape& shape)
{
  for(auto i = 0; i < length_; ++i) {
    auto id = ids_.at(i);

    auto b_it = begin(indexes_) + (i * length_);
    auto e_it = begin(indexes_) + ((i+1) * length_);

    shape.set_loop_id(id, b_it, e_it);
  }

  auto it = begin(indexes_);
  bool carry = false;

  do {
    carry = false;
    *it += 1;
    if(*it == length_) {
      *it = 0;
      carry = true;
    }
    it++;
  } while (carry);

  if(std::all_of(begin(indexes_), end(indexes_), [](auto i) { return i == 0; })) {
    return !std::next_permutation(begin(ids_), end(ids_));
  }

  return false;
}

std::unordered_set<Shape> Indexer::all_loops()
{
  auto ret = std::unordered_set<Shape>{};

  bool done = false;
  do {
    auto shape = Shape{length_};
    done = set_next_indexes(shape);
    ret.insert(shape);
  } while(!done);

  return ret;
}

}

namespace std {
  size_t hash<accsynt::EmptySlot>::operator()(accsynt::EmptySlot const& slot) const
  {
    return 0;
  }

  size_t hash<accsynt::Shape>::operator()(accsynt::Shape const& shape) const
  {
    size_t val = 0;
    accsynt::hash_combine(val, shape.n_loops);

    auto hasher = accsynt::visitor{
      [&](accsynt::EmptySlot) {},
      [&](auto v) { accsynt::hash_combine(val, v); }
    };
    
    for(auto slot : shape.slots) {
      std::visit(hasher, slot);
    }

    return val;
  }

  size_t hash<accsynt::Nest>::operator()(accsynt::Nest const& nest) const
  {
    size_t val = 0;
    accsynt::hash_combine(val, nest.ID);
    accsynt::hash_combine(val, *nest.shape);
    return val;
  }
}
