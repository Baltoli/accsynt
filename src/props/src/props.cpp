#include <props/props.h>

#define TAO_PEGTL_NAMESPACE props_pegtl
#include <tao/pegtl.hpp>

#include <iostream>

namespace props {

namespace pegtl = tao::props_pegtl;

template <typename Rule>
struct signature_action : pegtl::nothing<Rule>
{};

template <typename Rule>
struct param_action : pegtl::nothing<Rule>
{};

struct type_name
  : pegtl::sor<
      pegtl::string<'v', 'o', 'i', 'd'>,
      pegtl::string<'i', 'n', 't'>,
      pegtl::string<'f', 'l', 'o', 'a', 't'>
    >
{};

struct interface_name
  : pegtl::identifier
{};

struct param_spec
  : pegtl::seq<
      type_name,
      pegtl::plus<pegtl::space>,
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

struct grammar
  : pegtl::must<
      type_name,
      pegtl::plus<pegtl::space>,
      interface_name,
      pegtl::string<'('>,
      pegtl::action<
        param_action,
        pegtl::opt<params>
      >,
      pegtl::string<')'>,
      pegtl::eof
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

std::optional<data_type> data_type_from_string(std::string const& str)
{
  if(str == "int") { return data_type::integer; }
  else if(str == "float") { return data_type::floating; }
  else { return std::nullopt; }
}

void test()
{
  signature s;
  pegtl::parse<grammar, signature_action>(pegtl::string_input("float wooo(float   x,int y)", ""), s);
  std::cout << s << '\n';
}

std::ostream& operator <<(std::ostream& os, const data_type& dt)
{
  switch(dt) {
    case data_type::integer:
      os << "int";
      break;
    case data_type::floating:
      os << "float";
      break;
  }
  return os;
}

std::ostream& operator <<(std::ostream& os, const param& p)
{
  os << p.type << " " << p.name;
  return os;
}

std::ostream& operator <<(std::ostream& os, const signature& sig)
{
  if(auto rt = sig.return_type) {
    os << rt.value();
  } else {
    os << "void";
  }

  os << " " << sig.name << "(";

  for(auto it = sig.parameters.begin(); 
      it != sig.parameters.end(); 
      ++it)
  {
    os << *it;
    if(std::next(it) != sig.parameters.end()) {
      os << ", ";
    }
  }

  os << ")";
  return os;
}

}
