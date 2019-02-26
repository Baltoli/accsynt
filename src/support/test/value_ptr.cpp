#include <catch2/catch.hpp>

#include <support/value_ptr.h>

using namespace support;

// clang-format off
struct rc {
  rc(int& c) : c_(c) { ++c_; }
  rc(rc const& o) : rc(o.c_) {}
  ~rc() { --c_; }

  int& c_;
};
// clang-format on

TEST_CASE("value_ptr manages scoped lifetimes")
{
  auto count = 0;

  {
    auto v = value_ptr<rc>(new rc(count));
    REQUIRE(count == 1);

    auto v2 = value_ptr<rc>(new rc(count));
    REQUIRE(count == 2);
  }

  REQUIRE(count == 0);
}

TEST_CASE("value_ptr can hold nullptr") {}

TEST_CASE("value_ptr holds a pointer")
{
  SECTION("with get")
  {
    auto v = value_ptr<int>(new int(3));
    int* ptr = v.get();
    REQUIRE((*ptr = 3));
  }
}

TEST_CASE("value_ptr can be copied")
{
  SECTION("stored values are copied")
  {
    auto count = 0;

    {
      auto v = value_ptr<rc>(new rc(count));
      REQUIRE(count == 1);

      auto v2(v);
      REQUIRE(count == 2);
    }

    REQUIRE(count == 0);
  }

  SECTION("stored pointers are different")
  {
    auto v = value_ptr<int>(new int(3));
    auto v2 = v;

    REQUIRE(v.get() != v2.get());
    REQUIRE(*v.get() == *v2.get());
  }
}
