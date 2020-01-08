#include "fragment_parse.h"
#include "fragment.h"

#include <support/assert.h>

namespace presyn {

using namespace tao::pre_tl;

std::unique_ptr<fragment> build(grammar::fragment_parse const&);

template <typename Frag>
std::unique_ptr<fragment> build_for(grammar::fragment_parse const&);

template <>
std::unique_ptr<fragment> build_for<linear>(
    grammar::fragment_parse const& parse)
{
  assertion(parse.template_args.size() == 1,
      "Linear requires exactly one template argument");

  assertion(std::holds_alternative<int>(parse.template_args[0]),
      "Linear template argument must be integer");

  assertion(parse.child_args.empty(), "Linear takes no child arguments");

  return std::make_unique<linear>(std::get<int>(parse.template_args[0]));
}

template <>
std::unique_ptr<fragment> build_for<empty>(grammar::fragment_parse const& parse)
{
  assertion(parse.template_args.empty(), "Empty takes no template arguments");
  assertion(parse.child_args.empty(), "Empty takes no child arguments");

  return std::make_unique<empty>();
}

template <>
std::unique_ptr<fragment> build_for<seq>(grammar::fragment_parse const& parse)
{
  assertion(parse.template_args.empty(), "Seq takes no template arguments");
  assertion(
      parse.child_args.size() <= 2, "Seq takes at most 2 child arguments");

  std::unique_ptr<fragment> ret = std::make_unique<seq>();
  for (auto const& c_arg : parse.child_args) {
    ret = ret->compose(build(c_arg));
  }

  return ret;
}

std::unique_ptr<fragment> build(grammar::fragment_parse const& parse)
{
  if (parse.name == "linear") {
    return build_for<linear>(parse);
  } else if (parse.name == "empty") {
    return build_for<empty>(parse);
  } else if (parse.name == "seq") {
    return build_for<seq>(parse);
  } else {
    invalid_state();
  }
}

std::unique_ptr<fragment> fragment::parse(std::string_view str)
{
  auto state = grammar::fragment_state{};

  tao::pre_tl::parse<must<grammar::fragment, eof>, grammar::fragment_action>(
      memory_input(str.begin(), str.end(), ""), state);

  assert(state.stack.empty() && "Parsing did not finish with empty stack");
  return build(state.result);
}

namespace literals {

std::unique_ptr<fragment> operator""_frag(const char* str, size_t len)
{
  return fragment::parse(std::string_view(str, len));
}

} // namespace literals

} // namespace presyn
