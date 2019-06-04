#include <catch2/catch.hpp>

#include <support/bit_cast.h>
#include <support/call_builder.h>
#include <support/type_finder.h>

#include <limits>

#define MINV(T) (std::numeric_limits<T>::min())
#define MAXV(T) (std::numeric_limits<T>::max())

using namespace support;

#define TEST_CASES                                                             \
  OP(int)                                                                      \
  OP(char);                                                                    \
  OP(int8_t);                                                                  \
  OP(int32_t);                                                                 \
  OP(uint64_t);                                                                \
  OP(float);                                                                   \
  OP(double);

#define ID(T)                                                                  \
  SECTION("on " #T)                                                            \
  {                                                                            \
    auto n = GENERATE(take(100, random(MINV(T), MAXV(T))));                    \
    REQUIRE(bit_cast<T>(n) == n);                                              \
  }

TEST_CASE("bit_cast is the identity function")
{
#define OP ID
  TEST_CASES
#undef OP
}

#define INVOL(TA)                                                              \
  SECTION("from " #TA)                                                         \
  {                                                                            \
    auto n = GENERATE(take(100, random(MINV(TA), MAXV(TA))));                  \
    REQUIRE(bit_cast<TA>(bit_cast<int_of_equal_size_t<TA>>(n)) == n);          \
  }

TEST_CASE("bit_cast is an involution")
{
#define OP INVOL
  TEST_CASES
#undef OP
}

#define ROUND_TRIP(T)                                                          \
  SECTION("round trip to uint64_t from " #T)                                   \
  {                                                                            \
    auto n = GENERATE(take(100, random(MINV(T), MAXV(T))));                    \
    auto inter = bit_cast<uint64_t>(n);                                        \
    if constexpr (sizeof(uint64_t) > sizeof(T)) {                              \
      for (auto i = 0u; i < sizeof(uint64_t) - sizeof(T); ++i) {               \
        REQUIRE(detail::nth_byte(inter, i) == 0);                              \
      }                                                                        \
    }                                                                          \
    REQUIRE(bit_cast<T>(inter) == n);                                          \
  }

TEST_CASE("can round trip to uint64_t")
{
#define OP ROUND_TRIP
  TEST_CASES
#undef OP
}
