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

/**
 * A single instance of example data for a learner to later consume. Belongs to
 * a dataset, which is responsible for inserting missing values etc. when
 * encoding.
 */
class example {
public:
private:
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
  dataset(Iterator begin, Iterator end)
  {
    std::for_each(begin, end, [this] (auto const& ps) {
      for(auto const& prop : ps.properties) {
        prop_names_.insert(prop.name);
      }
    });
  }

  template <typename Container>
  explicit dataset(Container&& c) :
    dataset(
      support::adl_begin(FWD(c)),
      support::adl_end(FWD(c)))
  {
  }

  int encode(props::base_type) const;
  int encode(std::string const&) const;

private:
  void update(props::property_set const& ps);

  std::unordered_set<std::string> prop_names_ = {};
};

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
