#include <props/props.h>

#define TAO_PEGTL_NAMESPACE props_pegtl
#include <tao/pegtl.hpp>

#include <iostream>

namespace props {

namespace pegtl = tao::props_pegtl;

std::optional<data_type> data_type_from_string(std::string const& str)
{
  if(str == "int") { return data_type::integer; }
  else if(str == "float") { return data_type::floating; }
  else { return std::nullopt; }
}

template <typename Rule>
struct signature_action : pegtl::nothing<Rule>
{};

template <typename Rule>
struct param_action : pegtl::nothing<Rule>
{};

struct type_name
  : pegtl::sor<
      TAO_PEGTL_STRING("void"),
      TAO_PEGTL_STRING("int"),
      TAO_PEGTL_STRING("float")
    >
{};

struct interface_name
  : pegtl::identifier
{};

struct pointers
  : pegtl::star<
      pegtl::string<'*'>
    >
{};

struct param_spec
  : pegtl::seq<
      type_name,
      pegtl::plus<pegtl::space>,
      pointers,
      interface_name
    >
{};

struct params
  : pegtl::list<
      param_spec,
      pegtl::seq<
        pegtl::star<pegtl::space>,
        pegtl::string<','>,
        pegtl::star<pegtl::space>
      >
    >
{};

struct signature_grammar
  : pegtl::seq<
      type_name,
      pegtl::plus<pegtl::space>,
      interface_name,
      pegtl::string<'('>,
      pegtl::action<
        param_action,
        pegtl::opt<params>
      >,
      pegtl::string<')'>,
      pegtl::eolf
    >
{};

struct comment_grammar
  : pegtl::seq<
      pegtl::bol,
      pegtl::string<';'>,
      pegtl::star<pegtl::any>,
      pegtl::eolf
    >
{};

struct property_grammar
  : pegtl::seq<
      TAO_PEGTL_STRING("prop"),
      pegtl::eolf
    >
{};

struct file_grammar
  : pegtl::seq<
      pegtl::star<comment_grammar>,
      pegtl::state<
        signature,
        signature_grammar
      >
      /* pegtl::star< */
      /*   pegtl::sor< */
      /*     comment_grammar, */
      /*     property_grammar */
      /*   > */
      /* > */
    >
{};

template <>
struct signature_action<interface_name> {
  template <typename Input>
  static void apply(Input const& in, signature& sig) {
    sig.name = in.string();
  }
};

template <>
struct signature_action<type_name> {
  template <typename Input>
  static void apply(Input const& in, signature& sig) {
    sig.return_type = data_type_from_string(in.string());
  }
};

template <>
struct param_action<interface_name> {
  template <typename Input>
  static void apply(Input const& in, signature& sig) {
    sig.parameters.back().name = in.string();
  }
};

template <>
struct param_action<pointers> {
  template <typename Input>
  static void apply(Input const& in, signature& sig) {
    sig.parameters.back().pointer_depth = in.string().length();
  }
};

template <>
struct param_action<type_name> {
  template <typename Input>
  static void apply(Input const& in, signature& sig) {
    sig.parameters.emplace_back();
    auto type = data_type_from_string(in.string());
    if(type) {
      sig.parameters.back().type = type.value();
    }
  }
};

signature signature::parse(std::string_view str)
{
  signature sig;
  pegtl::parse<pegtl::must<signature_grammar>, signature_action>(pegtl::string_input(str, ""), sig);
  return sig;
}

property_set property_set::parse(std::string_view str)
{
  property_set pset;
  pegtl::parse<pegtl::must<file_grammar>>(pegtl::string_input(str, ""), pset);
  return pset;
}

}
