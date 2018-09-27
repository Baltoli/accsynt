#include <props/props.h>

#define TAO_PEGTL_NAMESPACE props_pegtl
#include <tao/pegtl.hpp>

#include <iostream>

namespace props {

namespace pegtl = tao::props_pegtl;

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
  : pegtl::string<'p', 'a', 'r'>
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
      params,
      pegtl::string<')'>,
      pegtl::eof
    >
{};

void test()
{
  pegtl::parse<grammar>(pegtl::string_input("float wooo(par, par , par,par)", ""));
}

}
