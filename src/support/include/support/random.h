#pragma once

#include <algorithm>
#include <limits>
#include <random>

namespace support {

template <typename Iterator>
auto uniform_sample(Iterator begin, Iterator end)
{
  if(begin == end) {
    return end;
  }

  auto rd = std::random_device{};
  auto dist = std::uniform_int_distribution<long>{0, std::distance(begin, end) - 1};
  auto idx = dist(rd);

  auto it = begin;
  std::advance(it, idx);

  return it;
}

template <typename Container>
auto uniform_sample(Container const& c)
{
  using std::begin;
  using std::end;

  return uniform_sample(begin(c), end(c));
}

template <typename Iterator, typename UnaryPred>
auto uniform_sample_if(Iterator begin, Iterator end, UnaryPred p)
{
  auto count = std::count_if(begin, end, p);
  if(count == 0) {
    return end;
  }

  auto rd = std::random_device{};
  auto dist = std::uniform_int_distribution<long>{0, count-1};
  auto nth = dist(rd);

  auto ret = std::find_if(begin, end, p);
  for(auto i = 0; i < nth; ++i) {
    ret = std::find_if(std::next(ret), end, p);
  }
  return ret;
}

template <typename Container, typename UnaryPred>
auto uniform_sample_if(Container const& c, UnaryPred p)
{
  using std::begin;
  using std::end;

  return uniform_sample_if(begin(c), end(c), p);
}

template <typename IntType>
IntType random_int(IntType min = std::numeric_limits<IntType>::min(),
                   IntType max = std::numeric_limits<IntType>::max())
{
  auto rd = std::random_device{};
  auto dist = std::uniform_int_distribution<IntType>{min, max};
  return dist(rd);
}

}
