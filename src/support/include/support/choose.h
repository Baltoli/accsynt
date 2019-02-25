#pragma once

#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

#define FWD(x) std::forward<decltype(x)>(x)

namespace support {

class choose {
public:
  choose(size_t n, size_t k);

  template <typename Func>
  void for_each(Func&& f) const;

private:
  template <typename Func>
  void recursive_step(
      std::vector<size_t> idxs, std::vector<size_t> accum, Func&& f) const;

  size_t elements_;
  size_t choice_size_;
};

template <typename Func>
void choose::recursive_step(
    std::vector<size_t> idxs, std::vector<size_t> accum, Func&& f) const
{
  if (accum.size() == choice_size_) {
    FWD(f)
    (accum);
  } else {
    for (auto i = 0u; i < idxs.size(); ++i) {
      auto remain = idxs;
      remain.erase(remain.begin() + i);

      auto element = idxs.at(i);
      auto next_accum = accum;
      next_accum.push_back(element);

      recursive_step(remain, next_accum, FWD(f));
    }
  }
}

template <typename Func>
void choose::for_each(Func&& f) const
{
  auto indices = std::vector<size_t>(elements_);
  std::iota(indices.begin(), indices.end(), 0);

  recursive_step(indices, {}, FWD(f));
}

#undef FWD
}
