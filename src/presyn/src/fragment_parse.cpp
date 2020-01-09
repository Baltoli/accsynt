#include "fragment_parse.h"
#include "fragment.h"

#include <support/assert.h>

namespace presyn {

using namespace tao::pre_tl;

std::unique_ptr<fragment> build(grammar::fragment_parse const&);

template <typename Frag, typename... TArgs>
std::unique_ptr<fragment>
build_from_children(grammar::fragment_parse const& parse, TArgs&&... targs)
{
  std::unique_ptr<fragment> ret
      = std::make_unique<Frag>(std::forward<TArgs>(targs)...);
  for (auto const& c_arg : parse.child_args) {
    ret = ret->compose(build(c_arg));
  }

  return ret;
}

template <typename Frag>
std::unique_ptr<fragment> build_for(grammar::fragment_parse const&);

template <>
std::unique_ptr<fragment>
build_for<linear>(grammar::fragment_parse const& parse)
{
  assertion(
      parse.template_args.size() == 1,
      "Linear requires exactly one template argument");

  assertion(
      std::holds_alternative<int>(parse.template_args[0]),
      "Linear template argument must be integer");

  assertion(parse.child_args.empty(), "Linear takes no child arguments");

  return build_from_children<linear>(
      parse, std::get<int>(parse.template_args[0]));
}

template <>
std::unique_ptr<fragment> build_for<empty>(grammar::fragment_parse const& parse)
{
  assertion(parse.template_args.empty(), "Empty takes no template arguments");
  assertion(parse.child_args.empty(), "Empty takes no child arguments");

  return build_from_children<empty>(parse);
}

template <>
std::unique_ptr<fragment> build_for<seq>(grammar::fragment_parse const& parse)
{
  assertion(parse.template_args.empty(), "Seq takes no template arguments");
  assertion(
      parse.child_args.size() <= 2, "Seq takes at most 2 child arguments");

  return build_from_children<seq>(parse);
}

template <>
std::unique_ptr<fragment> build_for<loop>(grammar::fragment_parse const& parse)
{
  assertion(parse.template_args.empty(), "Loop takes no template arguments");
  assertion(
      parse.child_args.size() <= 1, "Loop takes at most 1 child argument");

  return build_from_children<loop>(parse);
}

template <>
std::unique_ptr<fragment>
build_for<delimiter_loop>(grammar::fragment_parse const& parse)
{
  assertion(
      parse.template_args.size() == 1,
      "Delim requires exactly one template argument");

  assertion(
      std::holds_alternative<std::string>(parse.template_args[0]),
      "Delim template arg must be a named parameter");

  return build_from_children<delimiter_loop>(
      parse, std::get<std::string>(parse.template_args[0]));
}

std::unique_ptr<fragment> build(grammar::fragment_parse const& parse)
{
  if (parse.name == "linear") {
    return build_for<linear>(parse);
  } else if (parse.name == "empty") {
    return build_for<empty>(parse);
  } else if (parse.name == "seq") {
    return build_for<seq>(parse);
  } else if (parse.name == "loop") {
    return build_for<loop>(parse);
  } else if (parse.name == "delim") {
    return build_for<delimiter_loop>(parse);
  } else {
    invalid_state();
  }
}

std::unique_ptr<fragment> fragment::parse(std::string_view str)
{
  auto state = grammar::fragment_state {};

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
