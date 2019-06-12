#include <support/call_builder.h>

#include <catch2/catch.hpp>

using namespace props;
using namespace props::literals;
using namespace support;

char to_c(int i) { return char(i); }

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

  SECTION("for character vals")
  {
    auto val = 'A';
    REQUIRE(detail::nth_byte(val, 0) == 65);
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
#define MAXV(T) (std::numeric_limits<T>::max())
#define MINV(T) (std::numeric_limits<T>::min())
#define ALLVS(T) random(MINV(T), MAXV(T))
#define ALLCHARS() range(MINV(char), MAXV(char))

TEST_CASE("Can get values back from bytes")
{
  SECTION("for ints")
  {
    auto i = GENERATE(take(1000, ALLVS(int)));
    REQUIRE(detail::from_bytes<int>(u8ptr(i)) == i);
  }

  SECTION("for floats")
  {
    auto i = GENERATE(take(1000, ALLVS(float)));
    REQUIRE(detail::from_bytes<float>(u8ptr(i)) == i);
  }

  SECTION("for chars")
  {
    char i = GENERATE(ALLCHARS());
    REQUIRE(detail::from_bytes<char>(u8ptr(i)) == i);
  }

  SECTION("for pointers")
  {
    REQUIRE(sizeof(long) == sizeof(int*));

    long long_val = GENERATE(take(1000, ALLVS(long)));

    int* ptr;
    memcpy(&ptr, &long_val, sizeof(long_val));
    REQUIRE(detail::from_bytes<int*>(u8ptr(ptr)) == ptr);
  }
}
#undef u8ptr

TEST_CASE("Can construct call builders from signatures")
{
  auto s1 = "void f()"_sig;
  auto c1 = call_builder(s1);

  auto s2 = "char c(int a, char b, float c)"_sig;
  auto c2 = call_builder(s2);
}

TEST_CASE("Can extract arguments from a call_builder")
{
  SECTION("Fails if not enough arguments are present")
  {
    auto c1 = call_builder("void f()"_sig);
    REQUIRE_THROWS_AS(c1.get<int>(0), call_builder_error);

    auto c2 = call_builder("void f(int x)"_sig);
    c2.add(0);
    REQUIRE_THROWS_AS(c2.get<int>(1), call_builder_error);

    auto c3 = call_builder("void f(int x, int y, int z)"_sig);
    c3.add(0, 0);
    REQUIRE_THROWS_AS(c3.get<int>(2), call_builder_error);

    auto c4 = call_builder("void f(char v, int g)"_sig);
    c4.add('a', 78);
    REQUIRE_THROWS_AS(c4.get<char>(2), call_builder_error);
  }

  SECTION("Can get ints back correctly")
  {
    SECTION("A simple case")
    {
      auto c1 = call_builder("void f(int x)"_sig);
      auto v1 = GENERATE(take(1000, ALLVS(int)));
      c1.add(v1);
      REQUIRE(c1.get<int>(0) == v1);
    }

    SECTION("More args")
    {
      auto c2 = call_builder("void g(int x, float v, int y)"_sig);
      auto v2 = GENERATE(take(1000, chunk(2, ALLVS(int))));
      c2.add(v2[0], 0.4f, v2[1]);
      REQUIRE(c2.get<int>(0) == v2[0]);
      REQUIRE(c2.get<int>(2) == v2[1]);
    }
  }

  SECTION("Can get chars back correctly")
  {
    SECTION("A simple case")
    {
      auto c1 = call_builder("void f(char c)"_sig);
      char v = GENERATE(ALLCHARS());
      c1.add(v);
      REQUIRE(c1.get<char>(0) == v);
    }

    SECTION("More args")
    {
      auto c2 = call_builder("int g(char c1, int x, float y, char c2)"_sig);

      auto vs
          = GENERATE_COPY(take(100, chunk(2, map<char>(to_c, ALLVS(char)))));

      c2.add(vs[0], 0, 0.0f, vs[1]);
      REQUIRE(c2.get<char>(0) == vs[0]);
      REQUIRE(c2.get<char>(3) == vs[1]);
    }
  }

  SECTION("Can get floats back correctly")
  {
    SECTION("A simple case")
    {
      auto c1 = call_builder("void f(float x)"_sig);
      auto v = GENERATE(take(1000, ALLVS(float)));
      c1.add(v);
      REQUIRE(c1.get<float>(0) == v);
    }

    SECTION("More args")
    {
      auto c = call_builder("void g(float x, int v, float y)"_sig);
      auto v = GENERATE(take(1000, chunk(2, ALLVS(float))));
      c.add(v[0], 4, v[1]);

      REQUIRE(c.get<float>(0) == v[0]);
      REQUIRE(c.get<float>(2) == v[1]);
    }
  }

  SECTION("Can get vectors back correctly")
  {
    SECTION("For ints")
    {
      auto c1 = call_builder("void h(int *x)"_sig);

      auto len = GENERATE(take(1, random(1, 1000)));
      auto vec = GENERATE_COPY(take(100, chunk(len, ALLVS(int))));

      c1.add(vec);

      auto ext_vec = c1.get<std::vector<int>>(0);
      REQUIRE(ext_vec == vec);
      REQUIRE(ext_vec.data() != vec.data());
    }

    SECTION("For chars")
    {
      auto c = call_builder("void z(char *cs)"_sig);

      auto len = GENERATE(take(1, random(1, 1000)));
      auto vec
          = GENERATE_COPY(take(100, chunk(len, map<char>(to_c, ALLVS(char)))));

      c.add(vec);

      auto ext_vec = c.get<std::vector<char>>(0);
      REQUIRE(ext_vec == vec);
      REQUIRE(ext_vec.data() != vec.data());
    }

    SECTION("For floats")
    {
      auto c1 = call_builder("void h(float *x)"_sig);

      auto len = GENERATE(take(1, random(1, 1000)));
      auto vec = GENERATE_COPY(take(100, chunk(len, ALLVS(float))));

      c1.add(vec);

      auto ext_vec = c1.get<std::vector<float>>(0);
      REQUIRE(ext_vec == vec);
      REQUIRE(ext_vec.data() != vec.data());
    }
  }

  SECTION("Can get whole signatures back correctly")
  {
    auto c1 = call_builder("int fun(int a, int *b, float *c, float d)"_sig);
    auto a = 784123;
    auto b = std::vector{ 1, 2, 3 };
    auto c = std::vector{ 0.4f, 0.2f, 453.2f };
    auto d = 5768.11f;
    c1.add(a, b, c, d);

    REQUIRE(c1.get<int>(0) == a);
    REQUIRE(c1.get<std::vector<int>>(1) == b);
    REQUIRE(c1.get<std::vector<float>>(2) == c);
    REQUIRE(c1.get<float>(3) == d);
  }

  SECTION("Can get parameters back by name")
  {
    auto c1 = call_builder(
        "int fun(int *aio_efd, int woo, float *c__a, float doo)"_sig);
    auto aio_efd = std::vector{ 1, 2, 3 };
    auto woo = 784123;
    auto c__a = std::vector{ 0.4f, 0.2f, 453.2f };
    auto doo = 5768.11f;
    c1.add(aio_efd, woo, c__a, doo);

    REQUIRE(c1.get<std::vector<int>>("aio_efd") == aio_efd);
    REQUIRE(c1.get<int>("woo") == woo);
    REQUIRE(c1.get<std::vector<float>>("c__a") == c__a);
    REQUIRE(c1.get<float>("doo") == doo);
  }
}
