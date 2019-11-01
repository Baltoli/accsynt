#include <catch2/catch.hpp>

#include "fragment_id.h"

using namespace synth;

struct A {
  static char ID;
};
char A::ID = 0;
static register_fragment_id<A> X;

TEST_CASE("Can get ids for registered types") {}
