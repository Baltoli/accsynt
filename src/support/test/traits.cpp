#include <support/traits.h>

#include <catch2/catch.hpp>

#include <map>
#include <set>

using namespace support;

struct s {
};
struct t {
};

TEST_CASE("pointer depth calculations work")
{
  SECTION("basic types")
  {
    REQUIRE(pointer_depth_v<int> == 0);
    REQUIRE(pointer_depth_v<float> == 0);
    REQUIRE(pointer_depth_v<void> == 0);
    REQUIRE(pointer_depth_v<s> == 0);
    REQUIRE(pointer_depth_v<t> == 0);
  }

  SECTION("pointers")
  {
    REQUIRE(pointer_depth_v<int*> == 1);
    REQUIRE(pointer_depth_v<float**> == 2);
    REQUIRE(pointer_depth_v<void***> == 3);
    REQUIRE(pointer_depth_v<s****> == 4);
    REQUIRE(pointer_depth_v<t*****> == 5);
  }
}

struct has_find {
  using key_type = int;
  int find(key_type);
};

TEST_CASE("has_member_find works")
{
  SECTION("trait works correctly")
  {
    static_assert(
        has_member_find_v<std::set<int>>, "Set should have member find");

    static_assert(!has_member_find_v<std::vector<std::string>>,
        "Vector should not have member find");

    static_assert(
        has_member_find_v<has_find>, "Types that look OK should also");
  }

  SECTION("generic find works")
  {
    auto set = std::set{ 1, 2, 3 };
    auto vec = std::vector{ 7, 5, 3, 1 };

    static_assert(has_member_find_v<decltype(set)>,
        "Set variable should have member find");

    static_assert(!has_member_find_v<decltype(vec)>,
        "Vector variable should not have member find");

    auto s_found = container_find(set, 2);
    REQUIRE(s_found != set.end());
    REQUIRE(*s_found == 2);

    auto v_found = container_find(vec, 1);
    REQUIRE(v_found != vec.end());
    REQUIRE(*v_found == 1);

    auto s_not = container_find(set, 4);
    REQUIRE(s_not == set.end());

    auto v_not = container_find(vec, 4);
    REQUIRE(v_not == vec.end());
  }
}

struct A;
struct B {
};

TEST_CASE("can check for completeness")
{
  static_assert(is_complete_v<B>);
  static_assert(!is_complete_v<A>);
  static_assert(is_complete_v<A*>);
  static_assert(is_complete_v<int>);
}

template <typename>
struct S;
template <>
struct S<int> {
};
template <>
struct S<float> {
};

TEST_CASE("can check for specialization")
{
  static_assert(is_specialized_v<S, int>);
  static_assert(is_specialized_v<S, float>);
  static_assert(!is_specialized_v<S, bool>);
  static_assert(!is_specialized_v<S, S<int>>);
}
