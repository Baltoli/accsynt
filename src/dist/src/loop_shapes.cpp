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

std::optional<long> Loop::ID() const
{
  if(!slot_) { return {}; }
  if(auto l_id = std::get_if<LoopID>(&*slot_)) {
    return l_id->id;
  }
  return {};
}

Loop& Loop::add_child(Loop const& l)
{
  return *loops_.emplace_back(new Loop(l));
}

Loop Loop::nested() const
{
  auto ret = Loop{};
  ret.add_child(*this);
  return ret;
}

Loop Loop::normalised() const
{
  auto ret = Loop{{}};
  if(slot_) {
    ret = Loop{};
  }

  for(auto& ch : loops_) {
    if(ch->slot_) {
      ret.add_child(*ch);
    } else {
      for(auto& nest : *ch) {
        ret.add_child(*nest);
      }
    }
  }
  return ret;
}

std::unordered_set<Loop> Loop::next_variants() const
{
  auto ret = std::unordered_set<Loop>{};

  // Recurse
  for(auto i = 0u; i < children_size(); ++i) {
    auto child = nth_child(i);
    for(auto var : child.next_variants()) {
      auto cp = *this;
      cp.nth_child(i) = var;
      ret.insert(cp);
    }
  }

  // Nest
  ret.insert(nested());
  
  // Pre-/post-sequence
  auto loop = Loop{{}};
  auto l2 = loop;
  loop.add_child(Loop{});
  loop.add_child(*this);
  l2.add_child(*this);
  l2.add_child(Loop{});
  ret.insert(loop);
  ret.insert(l2);

  return ret;
}

std::unordered_set<Loop> Loop::shapes(size_t n)
{
  auto ret = std::unordered_set<Loop>{};

  if(n == 0) {
  } else if(n == 1) {
    ret.insert(Loop{});
  } else {
    auto prevs = shapes(n - 1);
    for(auto p : prevs) {
      auto vars = p.next_variants();
      for(auto v : vars) {
        ret.insert(v.normalised());
      }
    }
  }

  return ret;
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
    if(**it != **o_it) {
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

std::unordered_set<Loop> Loop::loops(size_t n)
{
  auto ret = std::unordered_set<Loop>{};
  auto ids = std::vector<long>(n);
  std::iota(ids.begin(), ids.end(), 0);

  auto all_shapes = shapes(n);
  do {
    for(const auto& shape : all_shapes) {
      auto inst = shape.instantiated(ids.begin(), ids.end()).first;
      ret.insert(inst);
    }
  } while(std::next_permutation(ids.begin(), ids.end()));

  return ret;
}

size_t Loop::count() const
{
  size_t count = 0;
  if(slot_) {
    count++;
  }

  for(auto const& ch : loops_) {
    count += ch->count();
  }
  return count;
}

bool Loop::is_instantiated() const
{
  if(auto sl = slot_; !std::holds_alternative<LoopID>(*sl)) {
    return false;
  }

  return std::all_of(begin(), end(), [](auto& loop) {
    return loop->is_instantiated();
  });
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
  auto nest = bool{loop.slot_};
  if(nest) {
    os << *loop.slot_;
  }

  if(!loop.loops_.empty()) {
    if(nest) { os << '['; }
    for(const auto& l : loop.loops_) {
      os << *l << " ";
    }
    os << '\b';
    if(nest) { os << ']'; }
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
