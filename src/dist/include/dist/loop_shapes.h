/**
 * \file: loop_shapes.h
 */

#pragma once

#include <iosfwd>
#include <memory>
#include <optional>
#include <unordered_set>
#include <variant>
#include <vector>

namespace accsynt {
  struct Hole;
  struct LoopID;
  using Slot = std::variant<Hole, LoopID>;
  class Loop;
}

namespace std {
  template <>
  struct hash<accsynt::Hole> {
    size_t operator()(accsynt::Hole const& h) const;
  };

  template <>
  struct hash<accsynt::LoopID> {
    size_t operator()(accsynt::LoopID const& h) const;
  };

  template <>
  struct hash<accsynt::Loop> {
    size_t operator()(accsynt::Loop const& h) const;
  };
}

namespace accsynt {

/**
 * \brief Represents a slot in which a loop ID can be instantiated.
 *
 * These holes are used to build the unlabelled tree structure representing
 * loops in the shape code.
 */
struct Hole {
  /// Always returns true; all holes are equivalent.
  bool operator==(Hole const& other) const { return true; }

  /// Always returns false; all holes are equivalent.
  bool operator!=(Hole const& other) const { return false; }

  bool operator<(Hole const& other) const { return false; }
};

/**
 * \brief Small type-safe wrapper around a loop identifier.
 */
struct LoopID { 
  LoopID() = delete;

  /// Comparisons use underlying id.
  bool operator==(LoopID const& other) const
  {
    return id == other.id;
  }

  /// Comparisons use underlying id.
  bool operator!=(LoopID const& other) const
  {
    return !(*this == other);
  }

  bool operator<(LoopID const& other) const
  {
    return id < other.id;
  }

  /// Underlying ID.
  long id;
};

class Loop {
  std::vector<std::unique_ptr<Loop>> loops_ = {};
  std::optional<Slot> slot_ = Hole{};

public:
  Loop() = default;
  Loop(std::optional<Slot> s) : slot_{s} {}

  ~Loop() = default;

  bool operator==(Loop const& other) const;
  bool operator!=(Loop const& other) const;
  bool operator<(Loop const& other) const;
  size_t hash() const;

  Loop(const Loop& other);
  Loop& operator=(Loop other);

  std::optional<long> ID() const;

  Loop& add_child(Loop const& l);
  Loop nested() const;
  Loop normalised() const;
  std::unordered_set<Loop> next_variants() const;
  static std::unordered_set<Loop> shapes(size_t n);

  template <typename Iterator>
  std::pair<Loop, Iterator> instantiated(Iterator begin, Iterator end) const;

  template <typename Container>
  void instantiate(Container c);

  static std::unordered_set<Loop> loops(size_t n);
  bool is_instantiated() const;

  using iterator = decltype(loops_)::iterator;
  using const_iterator = decltype(loops_)::const_iterator;
  using reverse_iterator = decltype(loops_)::reverse_iterator;
  using const_reverse_iterator = decltype(loops_)::const_reverse_iterator;

  iterator begin() noexcept(noexcept(loops_.begin())) { return loops_.begin(); }
  const_iterator begin() const noexcept(noexcept(loops_.begin())) { return loops_.begin(); }
  const_iterator cbegin() const noexcept(noexcept(loops_.begin())) { return loops_.cbegin(); }

  iterator end() noexcept(noexcept(loops_.end())) { return loops_.end(); }
  const_iterator end() const noexcept(noexcept(loops_.end())) { return loops_.end(); }
  const_iterator cend() const noexcept(noexcept(loops_.end())) { return loops_.cend(); }

  reverse_iterator rbegin() noexcept(noexcept(loops_.rbegin())) { return loops_.rbegin(); }
  const_reverse_iterator rbegin() const noexcept(noexcept(loops_.rbegin())) { return loops_.rbegin(); }
  const_reverse_iterator crbegin() const noexcept(noexcept(loops_.rbegin())) { return loops_.crbegin(); }

  reverse_iterator rend() noexcept(noexcept(loops_.rend())) { return loops_.rend(); }
  const_reverse_iterator rend() const noexcept(noexcept(loops_.rend())) { return loops_.rend(); }
  const_reverse_iterator crend() const noexcept(noexcept(loops_.rend())) { return loops_.crend(); }

  size_t children_size() const { return loops_.size(); }
  Loop& nth_child(size_t n) const { return *loops_.at(n); }

  size_t count() const;

  friend std::ostream& operator<<(std::ostream& os, Loop const& loop);
};

template <typename Container>
void Loop::instantiate(Container c)
{
  using std::begin; using std::end;
  *this = instantiated(begin(c), end(c)).first;
}

template <typename Iterator>
std::pair<Loop, Iterator> Loop::instantiated(Iterator begin, Iterator end) const
{
  if(begin == end) {
    return {*this, begin};
  }

  auto ret = *this;
  auto it = begin;
  if(ret.slot_) {
    ret.slot_ = LoopID{*it++};
  }

  for(auto i = 0u; i < ret.children_size(); ++i) {
    auto& ch = ret.nth_child(i);
    auto pair = ch.instantiated(it++, end);
    ch = pair.first;
    it = pair.second;
  }

  return {ret, it};
}

}
