#pragma once

#include <props/props.h>

#include <support/utility.h>

#include <fmt/format.h>

#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <type_traits>
#include <vector>

namespace predict {

using feature_map = std::unordered_map<std::string, int>;

/**
 * A single instance of example data for a learner to later consume. Belongs to
 * a dataset, which is responsible for inserting missing values etc. when
 * encoding.
 */
class example {
public:
  template <typename Func>
  example(Func&&, props::property_set const&);

private:
  feature_map input_ = {};
  feature_map output_ = {};
};

/**
 * A collection of examples, along with logic to make sure that missing values
 * etc. are encoded properly.
 *
 * In this model, the only summarisation that needs to be done is mapping
 * property names to classes - can simplify the summarisation code.
 *
 * So this summarisation can be removed and pushed into the dataset class
 * instead - it will just need to make two passes through the data in order to
 * summarise, then encode each individual property set.
 */
class dataset {
public:
  template <typename Iterator>
  dataset(Iterator begin, Iterator end);

  template <typename Container>
  explicit dataset(Container&& c);

  int encode(props::base_type) const;

private:
  void update(props::property_set const& ps);

  std::unordered_set<std::string> prop_names_ = {};
  std::vector<example> examples_ = {};
};

/**
 * Implementations
 */

template <typename Func>
example::example(Func&&, props::property_set const&)
{
}

template <typename Iterator>
dataset::dataset(Iterator begin, Iterator end)
{
  // Summarise the data so that we're able to map property names to unique
  // indices later - this requires a first pass through the data.
  std::for_each(begin, end, [this] (auto const& ps) {
    for(auto const& prop : ps.properties) {
      prop_names_.insert(prop.name);
    }
  });

  // Then construct the set of examples from each property set.
  std::for_each(begin, end, [this] (auto const& ps) {
    examples_.emplace_back([] {}, ps);
  });
}

template <typename Container>
dataset::dataset(Container&& c) :
  dataset(support::adl_begin(FWD(c)), support::adl_end(FWD(c)))
{
}

}

namespace fmt {
  
template <>
struct formatter<::predict::example> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

  template <typename FormatContext>
  auto format(::predict::example const &e, FormatContext &ctx) {
    return format_to(ctx.out(), "Example()");
  }
};

}
