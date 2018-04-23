#pragma once

#include <dist/utils.h>

#include <iostream>
#include <memory>
#include <variant>
#include <vector>

namespace accsynt {

struct Hole {};
struct LoopId { 
  LoopId() = delete;
  long id; 
};

using Slot = std::variant<
  Hole,
  LoopId
>;

class Loop {
  std::vector<std::unique_ptr<Loop>> loops_;
  Slot slot_;

public:
  Loop() = default;
  ~Loop() = default;

  Loop(const Loop& other);
  Loop& operator=(Loop other);

  void add_child(Loop const& l);

  using iterator = decltype(loops_)::iterator;
  using const_iterator = decltype(loops_)::const_iterator;

  iterator begin() noexcept(noexcept(loops_.begin())) { return loops_.begin(); }
  const_iterator begin() const noexcept(noexcept(loops_.begin())) { return loops_.begin(); }
  const_iterator cbegin() const noexcept(noexcept(loops_.begin())) { return loops_.cbegin(); }

  iterator end() noexcept(noexcept(loops_.end())) { return loops_.end(); }
  const_iterator end() const noexcept(noexcept(loops_.end())) { return loops_.end(); }
  const_iterator cend() const noexcept(noexcept(loops_.end())) { return loops_.cend(); }

  friend std::ostream& operator<<(std::ostream& os, Loop const& loop);
};

Loop::Loop(const Loop& other) :
  slot_(other.slot_)
{
  for(const auto& child : other.loops_) {
    loops_.emplace_back(new Loop(*child));
  }
}

Loop& Loop::operator=(Loop other)
{
  using std::swap;
  swap(slot_, other.slot_);
  swap(loops_, other.loops_);
  return *this;
}

void Loop::add_child(Loop const& l)
{
  loops_.emplace_back(new Loop(l));
}

std::ostream& operator<<(std::ostream& os, Slot const& slot)
{
  auto printer = visitor{
    [&os] (Hole) { os << "()"; },
    [&os] (LoopId l) { os << "L" << l.id; }
  };

  std::visit(printer, slot);
  return os;
}

std::ostream& operator<<(std::ostream& os, Loop const& loop)
{
  os << loop.slot_;

  if(!loop.loops_.empty()) {
    os << "[";
    for(const auto& l : loop.loops_) {
      os << *l << " ";
    }
    os << "\b]";
  }

  return os;
}

}
