#pragma once

#include <iosfwd>
#include <memory>
#include <optional>
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

struct Hole {
  bool operator==(Hole const& other) const { return true; }
  bool operator!=(Hole const& other) const { return !(*this == other); }
};

struct LoopID { 
  LoopID() = delete;

  bool operator==(LoopID const& other) const
  {
    return id == other.id;
  }

  bool operator!=(LoopID const& other) const
  {
    return !(*this == other);
  }

  long id;
};

class Loop {
  std::vector<std::unique_ptr<Loop>> loops_ = {};
  std::optional<Slot> slot_ = Hole{};

public:
  Loop() = default;
  Loop(std::nullopt_t) : slot_{} {}

  ~Loop() = default;

  bool operator==(Loop const& other) const;
  bool operator!=(Loop const& other) const;
  size_t hash() const;

  Loop(const Loop& other);
  Loop& operator=(Loop other);

  Loop& add_child(Loop const& l);
  Loop nested() const;

  using iterator = decltype(loops_)::iterator;
  using const_iterator = decltype(loops_)::const_iterator;

  iterator begin() noexcept(noexcept(loops_.begin())) { return loops_.begin(); }
  const_iterator begin() const noexcept(noexcept(loops_.begin())) { return loops_.begin(); }
  const_iterator cbegin() const noexcept(noexcept(loops_.begin())) { return loops_.cbegin(); }

  iterator end() noexcept(noexcept(loops_.end())) { return loops_.end(); }
  const_iterator end() const noexcept(noexcept(loops_.end())) { return loops_.end(); }
  const_iterator cend() const noexcept(noexcept(loops_.end())) { return loops_.cend(); }

  size_t size() const { return loops_.size(); }
  Loop& nth_child(size_t n) const { return *loops_.at(n); }

  friend std::ostream& operator<<(std::ostream& os, Loop const& loop);
};

}
