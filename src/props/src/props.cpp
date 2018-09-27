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
  static void apply(Input const& in) {
    std::cout << "Name in sig mode " << in.string() << '\n';
  }
};

template <>
struct param_action<interface_name> {
  template <typename Input>
  static void apply(Input const& in) {
    std::cout << "Name in param mode " << in.string() << '\n';
  }
};

template <>
struct param_action<type_name> {
  template <typename Input>
  static void apply(Input const& in) {
    std::cout << "Type in param mode " << in.string() << '\n';
  }
};

void test()
{
  pegtl::parse<grammar, signature_action>(pegtl::string_input("float wooo(float   x,int y)", ""));
}

}
