#include "fragment_parse.h"
#include "fragment.h"

#include <support/assert.h>
#include <support/visitor.h>

namespace presyn {

using namespace tao::pre_tl;

std::unique_ptr<parameter> make_param(grammar::template_arg_state ta)
{
  using ret_t = std::unique_ptr<parameter>;

  return std::visit(
      support::visitor {
          [](int i) -> ret_t { return std::make_unique<constant_int>(i); },
          [](std::string s) -> ret_t { return std::make_unique<named>(s); }},
      ta);
}

std::unique_ptr<fragment> build(grammar::fragment_parse const&);

template <typename Frag, typename... TArgs>
std::unique_ptr<fragment>
build_from_children(grammar::fragment_parse const& parse, TArgs&&... targs)
{
  std::unique_ptr<fragment> ret
      = std::make_unique<Frag>(make_param(parse.template_args[targs])...);

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

  return build_from_children<linear>(parse, 0);
}

template <>
std::unique_ptr<fragment> build_for<hole>(grammar::fragment_parse const& parse)
{
  assertion(parse.template_args.empty(), "Hole takes no template arguments");
  assertion(parse.child_args.empty(), "Hole takes no child arguments");

  return build_from_children<hole>(parse);
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

  assertion(
      parse.child_args.size() <= 1, "Delim takes at most 1 child argument");

  return build_from_children<delimiter_loop>(parse, 0);
}

template <>
std::unique_ptr<fragment>
build_for<fixed_loop>(grammar::fragment_parse const& parse)
{
  assertion(
      parse.template_args.size() > 0, "Fixed requires at least one argument");

  assertion(
      parse.child_args.size() <= 1, "Fixed takes at most 1 child argument");

  for (int i = 1; i < parse.template_args.size(); ++i) {
    assertion(
        std::holds_alternative<std::string>(parse.template_args[i]),
        "Pointer arguments to fixed loop must be named");
  }

  auto size = std::unique_ptr<parameter>();
  auto t_args = std::vector<std::unique_ptr<parameter>> {};
  for (auto const& t_arg : parse.template_args) {
    if (!size) {
      size = make_param(t_arg);
    } else {
      t_args.emplace_back(make_param(t_arg));
    }
  }

  std::unique_ptr<fragment> ret
      = std::make_unique<fixed_loop>(std::move(size), std::move(t_args));

  for (auto const& c_arg : parse.child_args) {
    ret = ret->compose(build(c_arg));
  }

  return ret;
}

template <>
std::unique_ptr<fragment> build_for<if_>(grammar::fragment_parse const& parse)
{
  assertion(parse.template_args.empty(), "If takes no template arguments");
  assertion(parse.child_args.size() <= 1, "If takes at most 1 child argument");

  return build_from_children<if_>(parse);
}

template <>
std::unique_ptr<fragment>
build_for<if_else>(grammar::fragment_parse const& parse)
{
  assertion(parse.template_args.empty(), "If-else takes no template arguments");
  assertion(
      parse.child_args.size() <= 2, "If-else takes at most 2 child argument");

  return build_from_children<if_else>(parse);
}

template <>
std::unique_ptr<fragment>
build_for<affine>(grammar::fragment_parse const& parse)
{
  assertion(
      parse.template_args.size() == 1,
      "Affine requires exactly two template arguments");

  assertion(
      std::holds_alternative<std::string>(parse.template_args[0]),
      "First affine template arg must be a named parameter");

  assertion(
      parse.child_args.size() <= 1, "Affine takes at most 1 child argument");

  return build_from_children<affine>(parse, 0);
}

template <>
std::unique_ptr<fragment> build_for<index>(grammar::fragment_parse const& parse)
{
  assertion(
      parse.template_args.size() == 1,
      "Index requires exactly two template arguments");

  assertion(
      std::holds_alternative<std::string>(parse.template_args[0]),
      "Index affine template arg must be a named parameter");

  assertion(
      parse.child_args.size() <= 1, "Index takes at most 1 child argument");

  return build_from_children<index>(parse, 0);
}

std::unique_ptr<fragment> build(grammar::fragment_parse const& parse)
{
  if (parse.name == "hole") {
    return build_for<hole>(parse);
  } else if (parse.name == "linear") {
    return build_for<linear>(parse);
  } else if (parse.name == "empty") {
    return build_for<empty>(parse);
  } else if (parse.name == "seq") {
    return build_for<seq>(parse);
  } else if (parse.name == "loop") {
    return build_for<loop>(parse);
  } else if (parse.name == "delim") {
    return build_for<delimiter_loop>(parse);
  } else if (parse.name == "fixed") {
    return build_for<fixed_loop>(parse);
  } else if (parse.name == "if") {
    return build_for<if_>(parse);
  } else if (parse.name == "if_else") {
    return build_for<if_else>(parse);
  } else if (parse.name == "affine") {
    return build_for<affine>(parse);
  } else if (parse.name == "index") {
    return build_for<index>(parse);
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
