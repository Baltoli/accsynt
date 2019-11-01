#include "loops.h"

#include <support/hashes.h>
#include <support/visitor.h>

#include <iostream>
#include <numeric>

namespace synth {

loop::loop(const loop& other)
    : slot_(other.slot_)
{
  for (const auto& child : other.loops_) {
    loops_.emplace_back(new loop(*child));
  }
}

loop& loop::operator=(loop other)
{
  using std::swap;
  slot_ = other.slot_;
  swap(loops_, other.loops_);
  return *this;
}

std::optional<long> loop::ID() const
{
  if (!slot_) {
    return {};
  }
  if (auto l_id = std::get_if<loop_id>(&*slot_)) {
    return l_id->id;
  }
  return {};
}

loop& loop::add_child(loop const& l)
{
  return *loops_.emplace_back(new loop(l));
}

loop loop::nested() const
{
  auto ret = loop{};
  ret.add_child(*this);
  return ret;
}

loop loop::normalised() const
{
  auto ret = loop{ {} };
  if (slot_) {
    ret = loop{};
  }

  for (auto& ch : loops_) {
    if (ch->slot_) {
      ret.add_child(*ch);
    } else {
      for (auto& nest : *ch) {
        ret.add_child(*nest);
      }
    }
  }
  return ret;
}

std::unordered_set<loop> loop::next_variants() const
{
  auto ret = std::unordered_set<loop>{};

  // Recurse
  for (auto i = 0u; i < children_size(); ++i) {
    auto child = nth_child(i);
    for (auto var : child.next_variants()) {
      auto cp = *this;
      cp.nth_child(i) = var;
      ret.insert(cp);
    }
  }

  // Nest
  ret.insert(nested());

  // Pre-/post-sequence
  auto l = loop{ {} };
  auto l2 = l;
  l.add_child(loop{});
  l.add_child(*this);
  l2.add_child(*this);
  l2.add_child(loop{});
  ret.insert(l);
  ret.insert(l2);

  return ret;
}

std::unordered_set<loop> loop::shapes(size_t n)
{
  auto ret = std::unordered_set<loop>{};

  if (n == 0) {
  } else if (n == 1) {
    ret.insert(loop{});
  } else {
    auto prevs = shapes(n - 1);
    for (auto p : prevs) {
      auto vars = p.next_variants();
      for (auto v : vars) {
        ret.insert(v.normalised());
      }
    }
  }

  return ret;
}

bool loop::operator==(loop const& other) const
{
  if (slot_ != other.slot_) {
    return false;
  }

  if (loops_.size() != other.loops_.size()) {
    return false;
  }

  for (auto it = begin(), o_it = other.begin();
       it != end() && o_it != other.end(); ++it, ++o_it) {
    if (**it != **o_it) {
      return false;
    }
  }

  return true;
}

bool loop::operator!=(loop const& other) const { return !(*this == other); }

size_t loop::hash() const
{
  size_t ret = 0;
  support::hash_combine(ret, slot_);
  for (const auto& loop : loops_) {
    support::hash_combine(ret, *loop);
  }
  return ret;
}

std::unordered_set<loop> loop::loops(size_t n)
{
  auto ids = std::vector<long>(n);
  std::iota(ids.begin(), ids.end(), 0);
  return loops(n, ids.begin(), ids.end());
}

bool loop::is_instantiated() const
{
  if (auto sl = slot_; !std::holds_alternative<loop_id>(*sl)) {
    return false;
  }

  return std::all_of(
      begin(), end(), [](auto& loop) { return loop->is_instantiated(); });
}

std::ostream& operator<<(std::ostream& os, slot const& slot)
{
  auto printer = support::visitor{ [&os](hole) { os << "()"; },
    [&os](loop_id l) { os << "L" << l.id; } };

  std::visit(printer, slot);
  return os;
}

std::ostream& operator<<(std::ostream& os, loop const& loop)
{
  auto nest = bool{ loop.slot_ };
  if (nest) {
    os << *loop.slot_;
  }

  if (!loop.loops_.empty()) {
    if (nest) {
      os << '[';
    }
    for (const auto& l : loop.loops_) {
      os << *l << " ";
    }
    os << '\b';
    if (nest) {
      os << ']';
    }
  }

  return os;
}
} // namespace synth

namespace std {
using namespace synth;

size_t hash<hole>::operator()(hole const& h) const { return 0; }

size_t hash<loop_id>::operator()(loop_id const& h) const
{
  size_t ret = 0;
  support::hash_combine(ret, h.id);
  return ret;
}

size_t hash<loop>::operator()(loop const& l) const { return l.hash(); }
} // namespace std
