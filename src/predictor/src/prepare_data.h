#pragma once

#include <props/props.h>

#include <support/utility.h>

#include <iterator>
#include <unordered_set>
#include <string>
#include <type_traits>

namespace predict {

class summary {
public:
  struct report {
    size_t params;
    size_t prop_names;
    size_t props;
    size_t arity;
  };

  template <typename Iterator>
  summary(Iterator begin, Iterator end)
  {
    for(auto it = begin; it != end; ++it) {
      update(*it);
    }
  }

  template <
    typename Container,
    typename = std::enable_if_t<
      !std::is_same_v<std::decay_t<Container>, props::property_set>
    >
  >
  explicit summary(Container&& c) :
    summary(
      support::adl_begin(FWD(c)),
      support::adl_end(FWD(c)))
  {
  }

  explicit summary(props::property_set const&);

  report get() const;

private:
  /**
   * Update the current summary model to reflect the new state with respect to
   * this new property set - i.e. keeping track of how many params, props,
   * arities etc. we need in order to properly construct feature vectors.
   */
  void update(props::property_set const& ps);

  size_t params_ = 0;
  std::unordered_set<std::string> prop_names_ = {};
  size_t num_props_ = 0;
  size_t prop_arity_ = 0;
};

}
