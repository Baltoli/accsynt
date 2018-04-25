/**
 * \file: loop_shapes.h
 */

#pragma once

#include <algorithm>
#include <iosfwd>
#include <memory>
#include <optional>
#include <unordered_set>
#include <variant>
#include <vector>

namespace accsynt {
  struct Hole;
  struct LoopID;
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

  /// Underlying ID.
  long id;
};

/**
 * \brief Represents the positition of a loop iterator.
 *
 * If a Slot instance holds a Hole, it has not yet been instantiated with a loop
 * identifier. Similarly, if it holds a LoopID, it represents a specific
 * iterator within the loop structure (i.e. it has been instantiated).
 */
using Slot = std::variant<Hole, LoopID>;

/**
 * \brief Represents a node in a loop tree structure.
 *
 * Represents a sequence of loops, which are themselves optionally nested inside
 * another loop.
 *
 * For example, consider the following loops:
 *
 * ```
 * for(... : L0) {}
 * for(... : L1) {}
 * ```
 *
 * The loops `L0` and `L1` are not nested inside another loop. This class can
 * also represent the following structure:
 *
 * ```
 * for(... : L2) {
 *   for(... : L3) {}
 *   for(... : L4) {}
 * }
 * ```
 *
 * In this case, the loops `L3` and `L4` are nested inside another loop.
 *
 * Both structures above can be represented by this class, depending on whether
 * an instance has an outer "slot". If it does, the instance represents a single
 * loop (possibly with others nested inside). If it does not, the instance
 * represents a (potentially empty) sequence of loops.
 */
class Loop {
  // The sequence of child loops for this instance.
  std::vector<std::unique_ptr<Loop>> loops_ = {};

  // If a loop has no slot, it represents a sequence of its children.
  std::optional<Slot> slot_ = Hole{};

public:
  /**
   * \brief The default state for a Loop object is a Hole with no child loops.
   *
   * This default state represents the following loop structure:
   * ```
   * for(... : ?) {}
   * ```
   */
  Loop() = default;

  /**
   * \brief Construct a Loop using a slot.
   *
   * If the argument to this constructor is a Hole, it is equivalent to default
   * constructing.
   *
   * This constructor can be used to construct a container Loop (one that does
   * not have an outer iterator) by passing an empty optional.
   */
  Loop(std::optional<Slot> s) : slot_{s} {}

  /**
   * \brief Copy-construct a Loop by copying all child loops.
   */
  Loop(const Loop& other);

  /**
   * \brief Assignment operator uses copy-and swap.
   */
  Loop& operator=(Loop other);

  /**
   * \name Comparison
   *
   * Equality is defined in terms of loop structure - if two loops have the same
   * outer slot, and all their children compare equal, the loops are equal.
   */
  ///@{
  bool operator==(Loop const& other) const;
  bool operator!=(Loop const& other) const;
  
  /**
   * \brief Public hash function that can access private state.
   *
   * This function is used by the `std::hash<Loop>` specialisation.
   */
  size_t hash() const;
  ///@}

  /**
   * \brief Convenience function to access this loop's ID if it has one.
   *
   * Will return a value if this loop has a slot and it has been instantiated.
   * Otherwise returns an empty optional.
   */
  std::optional<long> ID() const;

  bool is_instantiated() const;

  /**
   * \name In-place manipulation
   */
  ///@{
  Loop& add_child(Loop const& l);

  template <typename Container>
  void instantiate(Container c);
  ///@}

  /**
   * \name Constructing new Loops
   */
  ///@{
  Loop nested() const;
  Loop normalised() const;
  std::unordered_set<Loop> next_variants() const;

  template <typename Iterator>
  std::pair<Loop, Iterator> instantiated(Iterator begin, Iterator end) const;
  ///@}

  /**
   * \name Iteration
   */
  ///@{
  size_t children_size() const { return loops_.size(); }
  Loop& nth_child(size_t n) const { return *loops_.at(n); }

  auto begin() const { return loops_.begin(); }
  auto end() const { return loops_.end(); }
  auto rbegin() const { return loops_.rbegin(); }
  auto rend() const { return loops_.rend(); }
  ///@}
  
  /**
   * \name Enumeration
   *
   * The methods in this group can be used to enumerate all possible loop
   * structures for a given number of iterators.
   */
  ///@{
  static std::unordered_set<Loop> shapes(size_t n);

  static std::unordered_set<Loop> loops(size_t n);

  template <typename Iterator>
  static std::unordered_set<Loop> loops(size_t n, Iterator begin, Iterator end);
  ///@}

  /// Print a human-readable representation of this object to a stream.
  friend std::ostream& operator<<(std::ostream& os, Loop const& loop);
};

template <typename Iterator>
std::unordered_set<Loop> Loop::loops(size_t n, Iterator begin, Iterator end)
{
  auto ret = std::unordered_set<Loop>{};
  auto all_shapes = shapes(n);
  do {
    for(const auto& shape : all_shapes) {
      auto inst = shape.instantiated(begin, end).first;
      ret.insert(inst);
    }
  } while(std::next_permutation(begin, end));

  return ret;
}

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
