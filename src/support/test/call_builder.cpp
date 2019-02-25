#include <support/call_builder.h>

#include <catch2/catch.hpp>

#include <random>

using namespace props;
using namespace props::literals;
using namespace support;

TEST_CASE("Can extract the nth byte of values")
{
  SECTION("for easy int vals")
  {
    auto val = 0xDEADBEEF;
    REQUIRE(detail::nth_byte(val, 0) == 239);
    REQUIRE(detail::nth_byte(val, 1) == 190);
    REQUIRE(detail::nth_byte(val, 2) == 173);
    REQUIRE(detail::nth_byte(val, 3) == 222);
  }

  SECTION("for floating values")
  {
    auto val = float{ 12.345 };
    REQUIRE(detail::nth_byte(val, 0) == 31);
    REQUIRE(detail::nth_byte(val, 1) == 133);
    REQUIRE(detail::nth_byte(val, 2) == 69);
    REQUIRE(detail::nth_byte(val, 3) == 65);
  }

  SECTION("for pointers")
  {
    auto long_val = 0xDEADBEEF01020304;
    int* val;

    REQUIRE(sizeof(long_val) == sizeof(val));
    memcpy(&val, &long_val, sizeof(long_val));

    REQUIRE(detail::nth_byte(val, 0) == 4);
    REQUIRE(detail::nth_byte(val, 1) == 3);
    REQUIRE(detail::nth_byte(val, 2) == 2);
    REQUIRE(detail::nth_byte(val, 3) == 1);
    REQUIRE(detail::nth_byte(val, 4) == 239);
    REQUIRE(detail::nth_byte(val, 5) == 190);
    REQUIRE(detail::nth_byte(val, 6) == 173);
    REQUIRE(detail::nth_byte(val, 7) == 222);
  }
}

#define u8ptr(v) reinterpret_cast<uint8_t const*>(&v)
TEST_CASE("Can get values back from bytes")
{
  auto rd = std::random_device{};
  auto engine = std::default_random_engine(rd());

  SECTION("for ints")
  {
    auto dis = std::uniform_int_distribution<int>();
    for (auto i = 0; i < 100; ++i) {
      auto val = dis(engine);
      REQUIRE(detail::from_bytes<int>(u8ptr(val)) == val);
    }
  }

  SECTION("for floats")
  {
    auto dis = std::uniform_real_distribution<float>();
    for (auto i = 0; i < 100; ++i) {
      auto val = dis(engine);
      REQUIRE(detail::from_bytes<float>(u8ptr(val)) == val);
    }
  }

  SECTION("for pointers")
  {
    REQUIRE(sizeof(long) == sizeof(int*));

    auto dis = std::uniform_int_distribution<long>();
    for (auto i = 0; i < 100; ++i) {
      auto val = dis(engine);
      int* ptr;

      memcpy(&ptr, &val, sizeof(val));

      REQUIRE(detail::from_bytes<int*>(u8ptr(ptr)) == ptr);
    }
  }
}
#undef u8ptr

TEST_CASE("Can construct call builders from signatures")
{
  auto s1 = "void f()"_sig;
  auto c1 = call_builder(s1);
}

TEST_CASE("Can extract arguments from a call_builder")
{
  auto rd = std::random_device{};
  auto engine = std::default_random_engine(rd());

  SECTION("Fails if not enough arguments are present")
  {
    auto c1 = call_builder("void f()"_sig);
    REQUIRE_THROWS_AS(c1.get<int>(0), call_builder_error);

    auto c2 = call_builder("void f(int x)"_sig);
    c2.add(0);
    REQUIRE_THROWS_AS(c2.get<int>(1), call_builder_error);

    auto c3 = call_builder("void f(int x, int y, int z)"_sig);
    c3.add(0);
    c3.add(0);
    REQUIRE_THROWS_AS(c3.get<int>(2), call_builder_error);
  }

  SECTION("Can get ints back correctly")
  {
    for (int i = 0; i < 100; ++i) {
      auto dis = std::uniform_int_distribution<int>();

      auto c1 = call_builder("void f(int x)"_sig);
      auto v = dis(engine);
      c1.add(v);
      REQUIRE(c1.get<int>(0) == v);
    }

    for (int i = 0; i < 100; ++i) {
      auto dis = std::uniform_int_distribution<int>();

      auto c = call_builder("void g(int x, float v, int y)"_sig);
      auto v = dis(engine);
      auto v1 = dis(engine);

      c.add(v);
      c.add(0.4f);
      c.add(v1);

      REQUIRE(c.get<int>(0) == v);
      REQUIRE(c.get<int>(2) == v1);
    }
  }

  SECTION("Can get floats back correctly")
  {
    for (int i = 0; i < 100; ++i) {
      auto dis = std::uniform_real_distribution<float>();

      auto c1 = call_builder("void f(float x)"_sig);
      auto v = dis(engine);
      c1.add(v);
      REQUIRE(c1.get<float>(0) == Approx(v));
    }

    for (int i = 0; i < 100; ++i) {
      auto dis = std::uniform_real_distribution<float>();

      auto c = call_builder("void g(float x, int v, float y)"_sig);
      auto v = dis(engine);
      auto v1 = dis(engine);

      c.add(v);
      c.add(4);
      c.add(v1);

      REQUIRE(c.get<float>(0) == v);
      REQUIRE(c.get<float>(2) == v1);
    }
  }

  SECTION("Can get vectors back correctly")
  {
    for (int i = 0; i < 100; ++i) {
      auto dis = std::uniform_int_distribution<int>();
      auto c1 = call_builder("void h(int *x)"_sig);

      auto vec = std::vector<int>(64);
      std::generate(vec.begin(), vec.end(), [&] { return dis(engine); });
      c1.add(vec);

      auto ext_vec = c1.get<std::vector<int>>(0);
      REQUIRE(ext_vec == vec);
      REQUIRE(ext_vec.data() != vec.data());
    }

    for (int i = 0; i < 100; ++i) {
      auto dis = std::uniform_real_distribution<float>();
      auto c1 = call_builder("void h(float *x)"_sig);

      auto vec = std::vector<float>(64);
      std::generate(vec.begin(), vec.end(), [&] { return dis(engine); });
      c1.add(vec);

      auto ext_vec = c1.get<std::vector<float>>(0);
      REQUIRE(ext_vec == vec);
      REQUIRE(ext_vec.data() != vec.data());
    }
  }

  SECTION("Can get whole signatures back correctly")
  {
  }
}
