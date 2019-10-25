#pragma once

#include <iterator>

namespace predict {

class summary {
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
