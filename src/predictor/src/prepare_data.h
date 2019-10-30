#pragma once

#include <props/props.h>

#include <support/utility.h>

#include <fmt/format.h>

#include <iterator>
#include <map>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

namespace predict {

namespace detail {
  int encode(props::base_type);
}

using feature_map = std::map<std::string, int>;

/**
 * A single instance of example data for a learner to later consume. Belongs to
 * a dataset, which is responsible for inserting missing values etc. when
 * encoding.
 */
class example {
public:
  template <typename Func>
  example(Func&&, props::property_set const&);

  auto const& input() const { return input_; }
  auto const& output() const { return output_; }

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

  std::string to_csv() const;

  auto const& examples() const { return examples_; }

private:
  static constexpr int missing_ = -1;

  constexpr auto prop_encoder() {
    return [this] (auto const& pn) {
      auto found = prop_names_.find(pn);
      return std::distance(prop_names_.begin(), found);
    };
  }

  std::set<std::string> prop_names_ = {};
  std::vector<example> examples_ = {};
};

/**
 * Implementations
 */

template <typename Func>
example::example(Func&& prop_enc, props::property_set const& ps)
{
  using namespace fmt::literals;
  using namespace support;

  // Inputs

  if(auto rt = ps.type_signature.return_type) {
    input_["return_type"] = detail::encode(rt->base);
    input_["return_pointers"] = rt->pointers;
  }

  for (auto const& [i, param] : enumerate(ps.type_signature.parameters)) {
    auto base_key = "param_{}_type"_format(i);
    auto ptr_key = "param_{}_pointers"_format(i);

    input_[base_key] = detail::encode(param.type);
    input_[ptr_key] = param.pointer_depth;
  }

  // Outputs - whatever variables we want to use

  if(auto rt = ps.type_signature.return_type) {
    output_["out_return_type"] = detail::encode(rt->base);
  }

  output_["out_num_props"] = ps.properties.size();

  output_["out_num_sizes"] = 0;
  output_["out_num_outputs"] = 0;

  auto outputs = 0;
  for(auto const& prop : ps.properties) {
    if(prop.name == "size") {
      output_["out_num_sizes"]++;
    }

    if(prop.name == "output") {
      auto key = "out_output_{}_arg"_format(outputs++);
      output_[key] = ps.type_signature.param_index(prop.values[0].param_val);

      output_["out_num_outputs"]++;
    }
  }
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
    examples_.emplace_back(prop_encoder(), ps);
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
    using namespace fmt::literals;

    auto in_entries = std::vector<std::string>{};
    auto out_entries = std::vector<std::string>{};

    for(auto const& [k, v] : e.input()) {
      in_entries.push_back("{}={}"_format(k, v));
    }

    for(auto const& [k, v] : e.output()) {
      out_entries.push_back("{}={}"_format(k, v));
    }

    auto format = R"(Example(
  input=( {} ),
  output=( {} )
))";

    return format_to(
      ctx.out(), format,
      fmt::join(in_entries, ", "),
      fmt::join(out_entries, ", ")
    );
  }
};

template <>
struct formatter<::predict::dataset> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

  template <typename FormatContext>
  auto format(::predict::dataset const &d, FormatContext &ctx) {
    auto format = R"(Dataset(
{}
))";

    return format_to(
      ctx.out(), format, fmt::join(d.examples(), ",\n")
    );
  }
};

}
