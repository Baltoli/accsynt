#include <catch2/catch.hpp>

#include <support/bit_cast.h>
#include <support/call_builder.h>
#include <support/call_wrapper.h>
#include <support/load_module.h>
#include <support/type_finder.h>

#include <props/props.h>

#include <limits>

#define MINV(T) (std::numeric_limits<T>::min())
#define MAXV(T) (std::numeric_limits<T>::max())

using namespace props;
using namespace props::literals;
using namespace support;

#define TEST_CASES                                                             \
  OP(char);                                                                    \
  OP(unsigned char);                                                           \
  OP(short);                                                                   \
  OP(unsigned short);                                                          \
  OP(int)                                                                      \
  OP(unsigned int)                                                             \
  OP(long int)                                                                 \
  OP(unsigned long int)                                                        \
  OP(long long int)                                                            \
  OP(unsigned long long int)                                                   \
  OP(int8_t);                                                                  \
  OP(uint8_t);                                                                 \
  OP(int16_t);                                                                 \
  OP(uint16_t);                                                                \
  OP(int32_t);                                                                 \
  OP(uint32_t);                                                                \
  OP(int64_t);                                                                 \
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
      for (auto i = sizeof(T); i < sizeof(uint64_t); ++i) {                    \
        REQUIRE(detail::nth_byte(inter, i) == 0);                              \
      }                                                                        \
    }                                                                          \
    REQUIRE(bit_cast<T>(inter) == n);                                          \
  }

TEST_CASE("can round trip to uint64_t"){
#define OP ROUND_TRIP
  TEST_CASES
#undef OP
}

TEST_CASE("bit casting works with the ABI")
{
  SECTION("basic case for ints")
  {
    auto str = R"(
define i32 @value() {
  ret i32 3
})";

    PARSE_TEST_MODULE(mod, str);

    auto wrap = call_wrapper("int value()"_sig, *mod, "value");
    auto cb = wrap.get_builder();

    auto ret = wrap.call(cb);
    REQUIRE(bit_cast<int>(ret) == 3);
  }

  SECTION("basic case for floats")
  {
    auto str = R"(
define float @value() {
  ret float 0x3FF6666660000000
})";

    PARSE_TEST_MODULE(mod, str);

    auto wrap = call_wrapper("float value()"_sig, *mod, "value");
    auto cb = wrap.get_builder();

    auto ret = wrap.call(cb);
    REQUIRE(bit_cast<float>(ret) == Approx(1.4));
  }

  SECTION("more complicated for ints")
  {
    auto str = R"(
define i32 @work(i32, i32, i32) {
  %4 = mul nsw i32 %2, %1
  %5 = add nsw i32 %4, %0
  ret i32 %5
})";

    PARSE_TEST_MODULE(mod, str);

    auto wrap = call_wrapper("int work(int x, int y, int z)"_sig, *mod, "work");
    auto cb = wrap.get_builder();
    cb.add(2, 3, 4);

    auto ret = wrap.call(cb);
    REQUIRE(bit_cast<int>(ret) == 14);
  }

  SECTION("more complicated for floats")
  {
    auto str = R"(
define float @work(float, float) {
  %3 = fmul float %1, %1
  %4 = fmul float %3, %1
  %5 = fadd float %4, %0
  ret float %5
})";

    PARSE_TEST_MODULE(mod, str);

    auto wrap = call_wrapper("float work(float x, float y)"_sig, *mod, "work");
    auto cb = wrap.get_builder();
    cb.add(1.1f, 2.2f);

    auto ret = wrap.call(cb);
    REQUIRE(bit_cast<float>(ret) == Approx(11.748));
  }
}
