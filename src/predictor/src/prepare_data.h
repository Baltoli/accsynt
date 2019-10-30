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
 * A collection of examples, along with logic to make sure that missing values
 * etc. are encoded properly.
 */
class dataset {
public:
private:
};

/**
 * A single instance of example data for a learner to later consume. Belongs to
 * a dataset, which is responsible for inserting missing values etc. when
 * encoding.
 */
class example {
public:
private:
};

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
    std::for_each(begin, end, [this] (auto const& ps) {
      update(ps); 
    });
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

  int encode(props::base_type) const;
  int encode(std::string const&) const;

  example encode(props::property_set const&) const;
  props::property_set decode(example const&) const;

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

namespace fmt {
  
template <>
struct formatter<::predict::summary::report> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

  template <typename FormatContext>
  auto format(::predict::summary::report const &r, FormatContext &ctx) {
    using namespace fmt::literals;

    return format_to(ctx.out(), 
      "Report(params={fps}, names={ns}, props={ps}, arity={a})", 
      "fps"_a = r.params,
      "ns"_a = r.prop_names,
      "ps"_a = r.props,
      "a"_a = r.arity
    );
  }
};

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
