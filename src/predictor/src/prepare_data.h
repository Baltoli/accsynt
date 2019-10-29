#pragma once

#include <props/props.h>

#include <iterator>
#include <unordered_set>
#include <string>

namespace predict {

class summary {
public:
  struct report {
    size_t params;
    size_t prop_names;
    size_t props;
    size_t arity;
  };

  summary() = default;

  /**
   * Update the current summary model to reflect the new state with respect to
   * this new property set - i.e. keeping track of how many params, props,
   * arities etc. we need in order to properly construct feature vectors.
   */
  void update(props::property_set ps);

  report get() const;

private:
  size_t params_ = 0;
  std::unordered_set<std::string> prop_names_ = {};
  size_t num_props_ = 0;
  size_t prop_arity_ = 0;
};

template <typename Iterator>
summary summarise_props(Iterator begin, Iterator end)
{
  auto ret = summary{};
  
  for(auto it = begin; it != end; ++it) {
    ret.update(*it);
  }

  return ret;
}

template <typename Container>
summary summarise_props(Container&& c)
{
  using std::begin;
  using std::end;

  return summarise_props(begin(c), end(c));
}

}
