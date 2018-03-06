#pragma once

#include <iterator>
#include <vector>

namespace accsynt {

template <typename Iter, typename OrderIter>
class Permutation {
public:
  Permutation(const OrderIter o_begin, const OrderIter o_end, const Iter begin) :
    refs_(std::distance(o_begin, o_end))
  {
    for(auto i = 0u; i < refs_.size(); ++i) {
      auto idx = *(o_begin + i);
      refs_[i] = &*(begin + idx);
    }
  }

  auto begin() const { return std::begin(refs_); }
  auto end() const { return std::end(refs_); }

  auto operator[](size_t idx) const { return refs_[idx]; }

private:
  using item_t = typename std::iterator_traits<Iter>::value_type;

  std::vector<item_t const*> refs_;
};

}
