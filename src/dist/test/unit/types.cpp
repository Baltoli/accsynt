#include <catch2/catch.hpp>

#include <dist/types.h>

using namespace accsynt;

// TODO
/* TEST_CASE( "sized pointers respect their size", "[types]" ) { */
/*   auto size = Size{32}; */
/*   auto i64 = Integer{}; */
/*   auto sp = SizedPointer{i64, size}; */

/*   SECTION( "generated values are 0 < gv <= ub" ) { */
/*     for(auto i = 0; i < 128; ++i) { */
/*       auto g = size.generate(); */
/*       REQUIRE(g <= size.upper_bound); */
/*       REQUIRE(g > 0); */
/*     } */
/*   } */

/*   SECTION( "sps generate appropriately sized vectors" ) { */
/*     auto gv = sp.generate(); */
/*     REQUIRE(gv.size() <= size.upper_bound); */
/*   } */
/* } */

TEST_CASE( "metaprogramming for return types" ) {
  using out_1 = all_outputs<
    Integer
  >::type;
  REQUIRE(std::tuple_size_v<out_1> == 1);

  using out_2 = all_outputs<
    Void,
    Output<Integer>
  >::type;
  REQUIRE(std::tuple_size_v<out_2> == 1);

  using out_3 = all_outputs<
    Integer,
    Integer,
    Integer,
    Output<Array<Integer>>
  >::type;
  REQUIRE(std::tuple_size_v<out_3> == 2);

  using as_out_p = all_outputs<
    Void,
    Output<Integer>
  >::type;

  using as_return = all_outputs<
    Integer
  >::type;
  REQUIRE(std::is_same_v<as_out_p, as_return>);

  using with_args = all_outputs<
    Void,
    Output<Integer>,
    Integer,
    Integer
  >::type;
  REQUIRE(std::is_same_v<with_args, as_out_p>);
}

TEST_CASE( "equality of examples" ) {
  using return_t = all_outputs<
    Integer,
    Output<Array<Integer>>
  >::type;

  return_t a = {
    0, { 1, 2, 3, 4 }
  };

  return_t b = {
    0, { 2, 3, 4, 5 }
  };

  return_t c = {
    1, { 1, 2, 3, 4 }
  };

  return_t ap = {
    0, { 1, 2, 3, 4 }
  };

  return_t al = {
    0, { 1, 2, 3, 4, 5 }
  };

  REQUIRE(a == ap);
  REQUIRE(a != b);
  REQUIRE(a != c);
  REQUIRE(b != c);
  REQUIRE(b != ap);
  REQUIRE(c != ap);
  REQUIRE(a != al);
}
