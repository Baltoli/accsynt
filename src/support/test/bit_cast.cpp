#include <catch2/catch.hpp>

#include <support/bit_cast.h>

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

#define ISOM(TA, TB)                                                           \
  SECTION("from " #TA " to " #TB) {}

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

TEST_CASE("bit_cast is an isomorphism") {}
