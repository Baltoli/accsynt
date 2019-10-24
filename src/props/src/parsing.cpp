#include <props/props.h>

#define TAO_PEGTL_NAMESPACE props_pegtl
#include <tao/pegtl.hpp>

#include <iostream>
#include <unordered_map>

namespace props {

namespace pegtl = tao::props_pegtl;
using namespace pegtl;

std::optional<base_type> base_type_from_string(std::string const& str)
{
  auto map = std::unordered_map<std::string, base_type>{
    { "char",   base_type::character }, 
    { "int",    base_type::integer },
    { "float",  base_type::floating }, 
    { "bool",   base_type::boolean }
  };

  if(map.find(str) != map.end()) {
    return map.at(str);
  } else {
    return std::nullopt;
  }
}

template <typename Rule>
struct signature_action : nothing<Rule> {
};

template <typename Rule>
struct param_action : nothing<Rule> {
};

template <typename Rule>
struct property_action : nothing<Rule> {
};

struct type_name : sor<TAO_PEGTL_STRING("void"), TAO_PEGTL_STRING("int"),
                       TAO_PEGTL_STRING("float"), TAO_PEGTL_STRING("char"),
                       TAO_PEGTL_STRING("bool")> {
};

struct interface_name : identifier {
};

struct pointers : star<string<'*'>> {
};

struct return_type :
  sor<
    seq<
      type_name,
      star<blank>,
      plus<string<'*'>>
    >,
    type_name
  > {};

struct param_spec : seq<type_name, plus<blank>, pointers, interface_name> {
};

struct params : list<param_spec, seq<star<blank>, string<','>, star<blank>>> {
};

struct signature_grammar
    : seq<return_type, plus<blank>, interface_name, string<'('>,
          action<param_action, opt<params>>, string<')'>> {
};

struct any_in_line : seq<not_at<eol>, any> {
};

struct comment_grammar : seq<bol, string<';'>, star<any_in_line>> {
};

struct ignore_line : sor<comment_grammar, bol> {
};

struct property_name : identifier {
};

struct value_string : seq<TAO_PEGTL_STRING(":"), identifier> {
};

struct value_param : identifier {
};

struct value_int : seq<opt<sor<one<'+'>, one<'-'>>>, plus<digit>> {
};

struct value_float
    : seq<opt<sor<one<'+'>, one<'-'>>>, plus<digit>, one<'.'>, plus<digit>> {
};

struct property_value : sor<value_string, value_param, value_float, value_int> {
};

struct property_list
    : list<property_value, seq<star<blank>, string<','>, star<blank>>> {
};

struct property_grammar : seq<property_name, opt<star<blank>, property_list>> {
};

struct file_grammar
    : seq<star<ignore_line, eol>,
          action<signature_action, state<signature, signature_grammar>>, eol,
          action<property_action,
              star<state<property, property_grammar>, eolf>>> {
};

template <>
struct property_action<property_name> {
  template <typename Input>
  static void apply(Input const& in, property& prop)
  {
    prop.name = in.string();
  }
};

template <>
struct property_action<value_string> {
  template <typename Input>
  static void apply(Input const& in, property& prop)
  {
    prop.values.push_back(value::with_string(in.string()));
  }
};

template <>
struct property_action<value_param> {
  template <typename Input>
  static void apply(Input const& in, property& prop)
  {
    prop.values.push_back(value::with_param(in.string()));
  }
};

template <>
struct property_action<value_int> {
  template <typename Input>
  static void apply(Input const& in, property& prop)
  {
    prop.values.push_back(value::with_int(std::stoi(in.string())));
  }
};

template <>
struct property_action<value_float> {
  template <typename Input>
  static void apply(Input const& in, property& prop)
  {
    prop.values.push_back(value::with_float(std::stof(in.string())));
  }
};

template <>
struct signature_action<interface_name> {
  template <typename Input>
  static void apply(Input const& in, signature& sig)
  {
    sig.name = in.string();
  }
};

template <>
struct signature_action<type_name> {
  template <typename Input>
  static void apply(Input const& in, signature& sig)
  {
    auto type = base_type_from_string(in.string());
    if(type) {
      sig.return_type = data_type { type.value(), 0 };
    }
  }
};

template <>
struct signature_action<pointers> {
  template <typename Input>
  static void apply(Input const& in, signature& sig)
  {
    sig.return_type->pointers = in.string().length();
  }
};

template <>
struct param_action<interface_name> {
  template <typename Input>
  static void apply(Input const& in, signature& sig)
  {
    sig.parameters.back().name = in.string();
  }
};

template <>
struct param_action<pointers> {
  template <typename Input>
  static void apply(Input const& in, signature& sig)
  {
    sig.parameters.back().pointer_depth = in.string().length();
  }
};

template <>
struct param_action<type_name> {
  template <typename Input>
  static void apply(Input const& in, signature& sig)
  {
    sig.parameters.emplace_back();
    auto type = base_type_from_string(in.string());
    if (type) {
      sig.parameters.back().type = type.value();
    }
  }
};

signature signature::parse(std::string_view str)
{
  signature sig;
  pegtl::parse<must<signature_grammar, eof>, signature_action>(
      string_input(str, ""), sig);
  return sig;
}

property property::parse(std::string_view str)
{
  property prop;
  pegtl::parse<must<property_grammar, eolf>, property_action>(
      string_input(str, ""), prop);
  return prop;
}

property_set property_set::parse(std::string_view str)
{
  property_set pset;
  pegtl::parse<must<file_grammar, eof>>(string_input(str, ""), pset);

  if (!pset.is_valid()) {
    throw std::runtime_error("Invalid pset");
  }

  return pset;
}

property_set property_set::load(std::string_view path)
{
  property_set pset;
  pegtl::parse<must<file_grammar, eof>>(file_input(path), pset);

  if (!pset.is_valid()) {
    throw std::runtime_error("Invalid pset");
  }

  return pset;
}

value value::with_int(int i)
{
  value v;
  v.value_type = type::integer;
  v.int_val = i;
  return v;
}

value value::with_float(float f)
{
  value v;
  v.value_type = type::floating;
  v.float_val = f;
  return v;
}

value value::with_param(std::string param)
{
  value v;
  v.value_type = type::parameter;
  v.param_val = param;
  return v;
}

value value::with_string(std::string str)
{
  value v;
  v.value_type = type::string;

  if (str.at(0) != ':') {
    throw std::runtime_error("Invalid string literal");
  }

  v.string_val = str.substr(1);
  return v;
}

namespace literals {

signature operator""_sig(const char* str, size_t len)
{
  return signature::parse(std::string_view(str, len));
}
} // namespace literals
} // namespace props
