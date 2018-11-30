#include <support/cartesian_product.h>

#include <catch2/catch.hpp>

#include <iostream>

#include <set>
#include <vector>

using namespace support;

TEST_CASE("can construct products from nested containers") {
  SECTION("using iterators") {
    auto v = std::vector<std::vector<int>>{{0,1}, {2}};
    auto prod = cartesian_product(v.begin(), v.end());

    auto s = std::set<std::set<int>>{{0,1}, {3}, {2,2}};
    auto p2 = cartesian_product(s.begin(), s.end());
  }

  SECTION("using the containers") {
    // TODO
  }
}

TEST_CASE("can iterate over products with a range for loop") {
  auto v = std::vector<std::vector<int>>{{0, 1}, {2}};
  auto prod = cartesian_product(v.begin(), v.end());

  for(auto _ : prod) {}
}

TEST_CASE("products are counted correctly") {
  auto v = std::vector<std::vector<int>>{{0, 1}, {2}, {5,6,7}};
  auto prod = cartesian_product(v.begin(), v.end());

  REQUIRE(prod.product_size() == 3);
  REQUIRE(prod.size() == 6);
}

TEST_CASE("products are correct") {
  auto v = std::vector<std::vector<int>>{{0, 1}, {2}, {5,6,7}};
  auto prod = cartesian_product(v.begin(), v.end());

  auto it = prod.begin();
  REQUIRE(*it == std::vector{ 0, 2, 5 });

  ++it;
  REQUIRE(*it == std::vector{ 1, 2, 5 });

  ++it;
  REQUIRE(*it == std::vector{ 0, 2, 6 });

  ++it;
  REQUIRE(*it == std::vector{ 1, 2, 6 });

  ++it;
  REQUIRE(*it == std::vector{ 0, 2, 7 });

  ++it;
  REQUIRE(*it == std::vector{ 1, 2, 7 });
}

TEST_CASE("iterators are iterators") {
  auto v = std::vector<std::vector<int>>{{0, 1}, {2}, {5,6,7}};
  auto prod = cartesian_product(v.begin(), v.end());
  auto it = prod.begin();

  *it;
  ++it;
}

TEST_CASE("iterators are input iterators") {
  auto v = std::vector<std::vector<int>>{{0, 1}, {2}, {5,6,7}};
  auto prod = cartesian_product(v.begin(), v.end());
  auto it = prod.begin();
  auto i2 = prod.end();

  REQUIRE((it != i2));

  using iter_t = decltype(it);
  static_assert(
      std::is_convertible_v<decltype(*it), std::iterator_traits<iter_t>::value_type>, 
      "Dereference must convert to value_type");

  REQUIRE(it->data() == (*it).data());

  static_assert(
      std::is_same_v<decltype(++it), iter_t&>,
      "Increment must return reference to iterator");

  auto it_c = it;
  REQUIRE((it == it_c));
  (void)++it;
  (void)it_c++;
  REQUIRE((it == it_c));

  auto d1 = *it++;
  auto d2 = *it_c;
  ++it_c;
  REQUIRE(d1 == d2);
  REQUIRE((it == it_c));

  using std::swap;
  swap(it, i2);
}

TEST_CASE("iterators are bidirectional iterators") {
  auto v = std::vector<std::vector<int>>{{0, 1}, {2}, {5,6,7}};
  auto prod = cartesian_product(v.begin(), v.end());

  auto it = prod.begin();
  ++it;

  using iter_t = decltype(it);
  static_assert(
      std::is_same_v<decltype(--it), iter_t&>, 
      "Predecrement must be value_type");

  static_assert(
      std::is_convertible_v<decltype(it--), iter_t const&>, 
      "Postdecrement must convert to const reference");
  auto copy = it;
  REQUIRE((copy == it));
  REQUIRE((copy == it--));
  REQUIRE((--copy == it));

  static_assert(
      std::is_same_v<decltype(*it--), std::iterator_traits<iter_t>::reference>, 
      "Deref of postdecrement must be reference");
}
