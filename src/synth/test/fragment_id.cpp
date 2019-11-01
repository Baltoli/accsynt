#include <catch2/catch.hpp>

#include "fragment_id.h"

using namespace synth;

struct A {
  static char ID;
};
char A::ID = 0;
static register_fragment_id<A> X;

struct B {
  static char ID;
};
char B::ID = 0;
static register_fragment_id<B> Y;

struct C {
  static char ID;
};
char C::ID = 0;

struct D {
};

TEST_CASE("Can get ids for registered types")
{
  REQUIRE(get_fragment_id<A>() == get_fragment_id<A>());
  REQUIRE(get_fragment_id<A>() != get_fragment_id<B>());
  REQUIRE_THROWS(get_fragment_id<C>());

  auto a = A();
  auto b = B();

  REQUIRE(get_fragment_id(a) == get_fragment_id<A>());
  REQUIRE(get_fragment_id(a) != get_fragment_id(b));
}
