#pragma once

#include <props/props.h>

#include <support/utility.h>

#include <fmt/format.h>

#include <iterator>
#include <unordered_set>
#include <string>
#include <type_traits>
#include <vector>

namespace predict {

/**
 * This structure is deliberately lightweight - all it does is wrap the input
 * and output data generated from a particular property set such that they can
 * be easily passed to some kind of learning step later in the process.
 *
 * The schema for doing so is as follows:
 *
 * missing / padding is always -1 for every type
 *
 * base type: void=0, char=1, bool=2, int=3, float=4
 *
 * Input:
 *  return base type as above [1]
 *  return pointers [1]
 *  for each param:
 *    base type as above [1]
 *    pointers [1]
 *  padding to max params
 *
 * Output:
 *  for each prop:
 *    prop name encoded [1]
 *    for each val:
 *      index into params of val [1] // TODO: values???
 *      padding to max arity
 *    padding to max props
 */
struct example {
  std::vector<int> input = {};
  std::vector<int> output = {};
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
    using namespace fmt::literals;

    return format_to(ctx.out(), 
      "Example(\n  input=[{in}],\n  output=[{out}]\n)",
      "in"_a = fmt::join(e.input, ", "),
      "out"_a = fmt::join(e.output, ", ")
    );
  }
};

}
