#include <props/props.h>

#include <catch2/catch.hpp>

#include <iostream>

using namespace props;

TEST_CASE("signatures can be parsed") {
  SECTION("with valid signatures") {
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
  }

  SECTION("without valid signatures") {
    REQUIRE_THROWS(signature::parse("aefjio"));
    REQUIRE_THROWS(signature::parse(""));
    REQUIRE_THROWS(signature::parse("int *woo()"));
    REQUIRE_THROWS(signature::parse("int f("));
    REQUIRE_THROWS(signature::parse("double d()"));
    REQUIRE_THROWS(signature::parse("int)"));
    REQUIRE_THROWS(signature::parse("int woo()  fef"));
    REQUIRE_THROWS(signature::parse("int(int, float)"));
  }
}

TEST_CASE("files can be parsed") {
  auto file = ";hello\n;no\nint f(int x)";
  auto ps = property_set::parse(file);
}
