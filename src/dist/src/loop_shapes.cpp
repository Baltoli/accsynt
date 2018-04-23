#include <dist/loop_shapes.h>
#include <dist/utils.h>

#include <iostream>

namespace accsynt {

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

bool Loop::operator==(Loop const& other) const
{
  if(slot_ != other.slot_) {
    return false;
  }

  if(loops_.size() != other.loops_.size()) {
    return false;
  }

  for(auto it = begin(), o_it = other.begin();
      it != end() && o_it != other.end(); ++it, ++o_it) 
  {
    if(*it != *o_it) {
      return false;
    }
  }

  return true;
}

bool Loop::operator!=(Loop const& other) const
{
  return !(*this == other);
}

size_t Loop::hash() const
{
  size_t ret = 0;
  hash_combine(ret, slot_);
  for(const auto& loop : loops_) {
    hash_combine(ret, *loop);
  }
  return ret;
}

std::ostream& operator<<(std::ostream& os, Slot const& slot)
{
  auto printer = visitor{
    [&os] (Hole) { os << "()"; },
    [&os] (LoopID l) { os << "L" << l.id; }
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

namespace std {
  using namespace accsynt;

  size_t hash<Hole>::operator()(Hole const& h) const {
    return 0;
  }

  size_t hash<LoopID>::operator()(LoopID const& h) const {
    size_t ret = 0;
    hash_combine(ret, h.id);
    return ret;
  }

  size_t hash<Loop>::operator()(Loop const& l) const {
    return l.hash();
  }
}
