#include <props/props.h>

#include <catch2/catch.hpp>

#include <fmt/format.h>

#include <filesystem>

namespace fs = std::filesystem;
using namespace props;
using namespace props::literals;

TEST_CASE("signatures can be parsed")
{
  SECTION("with valid signatures")
  {
    auto s = signature::parse("float x()");
    REQUIRE(s.name == "x");
    REQUIRE(s.return_type);
    REQUIRE(s.return_type.value() == data_type{ base_type::floating, 0 });
    REQUIRE(s.parameters.empty());

    auto s2 = signature::parse("int na_me(int   x,  float zz_)");
    REQUIRE(s2.name == "na_me");
    REQUIRE(s2.return_type);
    REQUIRE(s2.return_type.value() == data_type{ base_type::integer, 0 });
    REQUIRE(s2.parameters.at(0).name == "x");
    REQUIRE(s2.parameters.at(0).type == base_type::integer);
    REQUIRE(s2.parameters.at(0).pointer_depth == 0);
    REQUIRE(s2.parameters.at(1).name == "zz_");
    REQUIRE(s2.parameters.at(1).type == base_type::floating);
    REQUIRE(s2.parameters.at(1).pointer_depth == 0);

    auto s3 = signature::parse("void fwio(int***woo)");
    REQUIRE(s3.name == "fwio");
    REQUIRE(!s3.return_type);
    REQUIRE(s3.parameters.at(0).name == "woo");
    REQUIRE(s3.parameters.at(0).type == base_type::integer);
    REQUIRE(s3.parameters.at(0).pointer_depth == 3);

    auto s4 = signature::parse("char f(char*   c)");
    REQUIRE(s4.name == "f");
    REQUIRE(s4.return_type);
    REQUIRE(s4.return_type.value() == data_type{ base_type::character, 0 });
    REQUIRE(s4.parameters.at(0).name == "c");
    REQUIRE(s4.parameters.at(0).type == base_type::character);
    REQUIRE(s4.parameters.at(0).pointer_depth == 1);

    auto s5 = "bool g(bool b,  char **s)"_sig;
    REQUIRE(s5.name == "g");
    REQUIRE(s5.return_type);
    REQUIRE(s5.return_type.value() == data_type{ base_type::boolean, 0 });
    REQUIRE(s5.parameters.at(0).name == "b");
    REQUIRE(s5.parameters.at(0).type == base_type::boolean);
    REQUIRE(s5.parameters.at(0).pointer_depth == 0);
    REQUIRE(s5.parameters.at(1).name == "s");
    REQUIRE(s5.parameters.at(1).type == base_type::character);
    REQUIRE(s5.parameters.at(1).pointer_depth == 2);

    auto s6 = "int *woo()"_sig;
    REQUIRE(s6.name == "woo");
    REQUIRE(s6.return_type);
    REQUIRE(s6.return_type.value() == data_type{ base_type::integer, 1 });
    REQUIRE(s6.parameters.empty());
  }

  SECTION("without valid signatures")
  {
    REQUIRE_THROWS("aefjio"_sig);
    REQUIRE_THROWS(""_sig);
    REQUIRE_THROWS("int f("_sig);
    REQUIRE_THROWS("double d()"_sig);
    REQUIRE_THROWS("int)"_sig);
    REQUIRE_THROWS("int woo()  fef"_sig);
    REQUIRE_THROWS("int(int, float)"_sig);
    REQUIRE_THROWS("character f()"_sig);
    REQUIRE_THROWS("boolean f(char c, int *g)"_sig);
    REQUIRE_THROWS("void f(int c, boolean g)"_sig);
  }
}

TEST_CASE("properties can be parsed")
{
  SECTION("with no values")
  {
    auto s1 = "name";
    auto pr1 = property::parse(s1);

    REQUIRE(pr1.name == "name");
    REQUIRE(pr1.values.empty());
  }
}

TEST_CASE("files can be parsed")
{
  auto file = R"(;hello

;qwd


;werjio


int main(int s, float *d, char **argv, bool on)
name 2.111, 0.000, 4, :string, s, d
fjio
wefjop
)";
  auto ps = property_set::parse(file);

  REQUIRE(ps.type_signature.return_type == data_type{ base_type::integer, 0 });

  REQUIRE(ps.type_signature.parameters.at(0).type == base_type::integer);
  REQUIRE(ps.type_signature.parameters.at(0).name == "s");
  REQUIRE(ps.type_signature.parameters.at(0).pointer_depth == 0);

  REQUIRE(ps.type_signature.parameters.at(1).type == base_type::floating);
  REQUIRE(ps.type_signature.parameters.at(1).name == "d");
  REQUIRE(ps.type_signature.parameters.at(1).pointer_depth == 1);

  REQUIRE(ps.type_signature.parameters.at(2).type == base_type::character);
  REQUIRE(ps.type_signature.parameters.at(2).name == "argv");
  REQUIRE(ps.type_signature.parameters.at(2).pointer_depth == 2);

  REQUIRE(ps.type_signature.parameters.at(3).type == base_type::boolean);
  REQUIRE(ps.type_signature.parameters.at(3).name == "on");
  REQUIRE(ps.type_signature.parameters.at(3).pointer_depth == 0);

  REQUIRE(ps.properties.size() == 3);
}

TEST_CASE("files can be loaded")
{
  auto current_path = fs::path(RESOURCE_DIR);

  auto test_a_path = current_path / "test_a.props";
  auto ps_a = property_set::load(test_a_path.string());

  REQUIRE(ps_a.type_signature.return_type == data_type{ base_type::integer, 0 });

  REQUIRE(ps_a.type_signature.name == "main");

  REQUIRE(ps_a.type_signature.parameters.at(0).type == base_type::integer);
  REQUIRE(ps_a.type_signature.parameters.at(0).name == "argc");
  REQUIRE(ps_a.type_signature.parameters.at(0).pointer_depth == 0);

  REQUIRE(ps_a.type_signature.parameters.at(1).type == base_type::character);
  REQUIRE(ps_a.type_signature.parameters.at(1).name == "argv");
  REQUIRE(ps_a.type_signature.parameters.at(1).pointer_depth == 2);

  REQUIRE(ps_a.properties.at(0).name == "property");
  REQUIRE(ps_a.properties.at(0).values.size() == 2);
}
