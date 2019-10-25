#pragma once

#include <props/props.h>

#include <iterator>

namespace predict {

class summary {
public:
  summary() = default;

  /**
   * Update the current summary model to reflect the new state with respect to
   * this new property set - i.e. keeping track of how many params, props,
   * arities etc. we need in order to properly construct feature vectors.
   */
  void update(props::property_set ps);

private:
};

template <typename Iterator>
summary summarise_props(Iterator begin, Iterator end)
{
  return summary{};
}

template <typename Container>
summary summarise_props(Container&& c)
{
  using std::begin;
  using std::end;

  return summarise_props(begin(c), end(c));
}

}
