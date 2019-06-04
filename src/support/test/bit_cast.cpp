#include <catch2/catch.hpp>

#include <support/bit_cast.h>
#include <support/type_finder.h>

#include <limits>

#define MINV(T) (std::numeric_limits<T>::min())
#define MAXV(T) (std::numeric_limits<T>::max())

using namespace support;

#define ID(T)                                                                  \
  SECTION("on " #T)                                                            \
  {                                                                            \
    auto n = GENERATE(take(100, random(MINV(T), MAXV(T))));                    \
    REQUIRE(bit_cast<T>(n) == n);                                              \
  }

TEST_CASE("bit_cast is the identity function")
{
  ID(int);
  ID(char);
  ID(int8_t);
  ID(int32_t);
  ID(uint64_t);
  ID(float);
  ID(double);
}

#define INVOL(TA)                                                              \
  SECTION("from " #TA)                                                         \
  {                                                                            \
    auto n = GENERATE(take(100, random(MINV(TA), MAXV(TA))));                  \
    REQUIRE(bit_cast<TA>(bit_cast<int_of_equal_size_t<TA>>(n)) == n);          \
  }

TEST_CASE("bit_cast is an involution")
{
  INVOL(int);
  INVOL(char);
  INVOL(int8_t);
  INVOL(int32_t);
  INVOL(uint64_t);
  INVOL(float);
  INVOL(double);
}
