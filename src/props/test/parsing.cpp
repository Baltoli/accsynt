#include <props/props.h>

#include <catch2/catch.hpp>

#include <fmt/format.h>

#include <filesystem>

namespace fs = std::filesystem;
using namespace props;

TEST_CASE("signatures can be parsed")
{
  SECTION("with valid signatures")
  {
    auto s = signature::parse("float x()");
    REQUIRE(s.name == "x");
    REQUIRE(s.return_type);
    REQUIRE(s.return_type.value() == data_type::floating);
    REQUIRE(s.parameters.empty());

    auto s2 = signature::parse("int na_me(int   x,  float zz_)");
    REQUIRE(s2.name == "na_me");
    REQUIRE(s2.return_type);
    REQUIRE(s2.return_type.value() == data_type::integer);
    REQUIRE(s2.parameters.at(0).name == "x");
    REQUIRE(s2.parameters.at(0).type == data_type::integer);
    REQUIRE(s2.parameters.at(0).pointer_depth == 0);
    REQUIRE(s2.parameters.at(1).name == "zz_");
    REQUIRE(s2.parameters.at(1).type == data_type::floating);
    REQUIRE(s2.parameters.at(1).pointer_depth == 0);

    auto s3 = signature::parse("void fwio(int ***woo)");
    REQUIRE(s3.name == "fwio");
    REQUIRE(!s3.return_type);
    REQUIRE(s3.parameters.at(0).name == "woo");
    REQUIRE(s3.parameters.at(0).type == data_type::integer);
    REQUIRE(s3.parameters.at(0).pointer_depth == 3);

    auto s4 = signature::parse("char f(char *c)");
    REQUIRE(s4.name == "f");
    REQUIRE(s4.return_type);
    REQUIRE(s4.return_type.value() == data_type::character);
    REQUIRE(s4.parameters.at(0).name == "c");
    REQUIRE(s4.parameters.at(0).type == data_type::character);
    REQUIRE(s4.parameters.at(0).pointer_depth == 1);
  }

  SECTION("without valid signatures")
  {
    REQUIRE_THROWS(signature::parse("aefjio"));
    REQUIRE_THROWS(signature::parse(""));
    REQUIRE_THROWS(signature::parse("int *woo()"));
    REQUIRE_THROWS(signature::parse("int f("));
    REQUIRE_THROWS(signature::parse("double d()"));
    REQUIRE_THROWS(signature::parse("int)"));
    REQUIRE_THROWS(signature::parse("int woo()  fef"));
    REQUIRE_THROWS(signature::parse("int(int, float)"));
    REQUIRE_THROWS(signature::parse("character f()"));
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


int main(int s, float *d, char **argv)
name 2.111, 0.000, 4, :string, s, d
fjio
wefjop
)";
  auto ps = property_set::parse(file);

  REQUIRE(ps.type_signature.return_type == data_type::integer);

  REQUIRE(ps.type_signature.parameters.at(0).type == data_type::integer);
  REQUIRE(ps.type_signature.parameters.at(0).name == "s");
  REQUIRE(ps.type_signature.parameters.at(0).pointer_depth == 0);

  REQUIRE(ps.type_signature.parameters.at(1).type == data_type::floating);
  REQUIRE(ps.type_signature.parameters.at(1).name == "d");
  REQUIRE(ps.type_signature.parameters.at(1).pointer_depth == 1);

  REQUIRE(ps.type_signature.parameters.at(2).type == data_type::character);
  REQUIRE(ps.type_signature.parameters.at(2).name == "argv");
  REQUIRE(ps.type_signature.parameters.at(2).pointer_depth == 2);

  REQUIRE(ps.properties.size() == 3);
}

TEST_CASE("files can be loaded")
{
  auto current_path = fs::path(RESOURCE_DIR);

  auto test_a_path = current_path / "test_a.props";
  auto ps_a = property_set::load(test_a_path.string());

  REQUIRE(ps_a.type_signature.return_type == data_type::integer);

  REQUIRE(ps_a.type_signature.name == "main");

  REQUIRE(ps_a.type_signature.parameters.at(0).type == data_type::integer);
  REQUIRE(ps_a.type_signature.parameters.at(0).name == "argc");
  REQUIRE(ps_a.type_signature.parameters.at(0).pointer_depth == 0);

  REQUIRE(ps_a.type_signature.parameters.at(1).type == data_type::character);
  REQUIRE(ps_a.type_signature.parameters.at(1).name == "argv");
  REQUIRE(ps_a.type_signature.parameters.at(1).pointer_depth == 2);

  REQUIRE(ps_a.properties.at(0).name == "property");
  REQUIRE(ps_a.properties.at(0).values.size() == 2);
}
