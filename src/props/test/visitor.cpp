#include <catch2/catch.hpp>

#include <props/props.h>

#include <sstream>

using namespace props;
using namespace props::literals;

// clang-format off
TEST_CASE("can visit type signatures")
{
  SECTION("visiting empty signatures")
  {
    auto s1 = "void f()"_sig;
    auto s2 = "int g()"_sig;
    auto s3 = "float h()"_sig;

    auto throw_none = []() { throw 0; };
    auto throw_int = [](int) { throw 0; };
    auto throw_p = [](param const&) { throw 0; };

    auto throw_v1 = sig_visitor {
      throw_none, throw_none, throw_int, throw_int
    };

    REQUIRE_NOTHROW(throw_v1.visit(s1));
    REQUIRE_NOTHROW(throw_v1.visit(s2));
    REQUIRE_NOTHROW(throw_v1.visit(s3));

    auto throw_v2 = sig_visitor {
      throw_p, throw_p, throw_p, throw_p
    };

    REQUIRE_NOTHROW(throw_v2.visit(s1));
    REQUIRE_NOTHROW(throw_v2.visit(s2));
    REQUIRE_NOTHROW(throw_v2.visit(s3));

    int i = 0;
    auto add = [&i] (param const&) { ++i; };
    auto add_v = sig_visitor {
      add, add, add, add
    };

    add_v.visit(s1);
    add_v.visit(s2);
    add_v.visit(s3);

    REQUIRE(i == 0);
  }

  SECTION("can visit using actions, receiving depth")
  {
    auto sig = "int wefhui(int a, int b, float ff, float **z, int ****tt)"_sig;

    int i = 0;
    auto v = sig_visitor {
      [&] { i += 1; },
      [&] { i += 3; },
      [&](int d) { i += d*5; },
      [&](int d) { i += d*7; }
    };

    v.visit(sig);
    REQUIRE(i == 2 + 3 + (4 * 5) + (2 * 7));
  }

  SECTION("can visit using values, receiving depth")
  {
    auto sig = "void ghhgj(int **a, int *b, float *b, float c)"_sig;

    auto v = sig_visitor {
      [] { return 'a'; },
      [] { return 'b'; },
      [](int) { return 'c'; },
      [](int) { return 'd'; }
    };

    REQUIRE(v.visit(sig) == std::vector{ 'c', 'c', 'd', 'b' });
  }

  SECTION("can visit using actions, receiving the param")
  {
    auto sig = "float gfty(float b, float c, int a, int *s, float **z)"_sig;

    auto ss = std::stringstream{}; 
    auto v = sig_visitor {
      [&](param const& p) { ss << "I" << p.name; },
      [&](param const& p) { ss << "F" << p.name; },
      [&](param const& p) { ss << "iP" << p.pointer_depth << p.name; },
      [&](param const& p) { ss << "fP" << p.pointer_depth << p.name; }
    };

    v.visit(sig);
    REQUIRE(ss.str() == "FbFcIaiP1sfP2z");
  }

  SECTION("can visit using values, receiving the param")
  {
    auto sig = "int ji(int a, float bbb, float ***c, int *x)"_sig;

    auto v = sig_visitor {
      [&](param const& p) { return "I" + p.name; },
      [&](param const& p) { return "F" + p.name; },
      [&](param const& p) { return "iP" + std::to_string(p.pointer_depth) + p.name; },
      [&](param const& p) { return "fP" + std::to_string(p.pointer_depth) + p.name; }
    };

    REQUIRE(v.visit(sig) == std::vector<std::string>{ "Ia", "Fbbb", "fP3c", "iP1x" });
  }

  SECTION("can ignore parameters")
  {
    auto throw_none = [] { throw 0; };
    auto throw_int = [](int) { throw 0; };

    auto s1 = "void f(float a, int *b, float *c)"_sig;
    auto s2 = "int g(int a, int *b, float *c)"_sig;
    auto s3 = "float h(int a, float b, float *c)"_sig;
    auto s4 = "void i(int a, float b, int *c)"_sig;

    auto v1 = sig_visitor{throw_none, ignore_param, ignore_param, ignore_param};
    auto v2 = sig_visitor{ignore_param, throw_none, ignore_param, ignore_param};
    auto v3 = sig_visitor{ignore_param, ignore_param, throw_int, ignore_param};
    auto v4 = sig_visitor{ignore_param, ignore_param, ignore_param, throw_int};

    REQUIRE_NOTHROW(v1.visit(s1));
    REQUIRE_NOTHROW(v2.visit(s2));
    REQUIRE_NOTHROW(v3.visit(s3));
    REQUIRE_NOTHROW(v4.visit(s4));
  }
}

TEST_CASE("Can use the v2 visitor")
{
  SECTION("in a very basic case") {
    auto s = "void f(float a, int *b, int c)"_sig;

    auto c = 0;
    auto vis = v2::sig_visitor{
      v2::on(data_type::integer, [&] (auto const&) { ++c; })
    };

    vis.visit(s);
    REQUIRE(c == 1);
  }
}
// clang-format on
