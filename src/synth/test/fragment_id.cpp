#include <catch2/catch.hpp>

#include "fragment.h"
#include "fragment_id.h"
#include "linear_fragment.h"
#include "string_loop_fragment.h"

#include <value_ptr/value_ptr.h>

#include <set>

using namespace bsc;
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

TEST_CASE("Can get IDs for all the fragment types")
{
  auto all_ids = std::set<int> {};
  auto args = std::vector<props::value> {};

  auto lin_f = make_val<linear_fragment>();
  all_ids.insert(lin_f->get_id());

  auto emp_f = make_val<empty_fragment>();
  all_ids.insert(emp_f->get_id());

  auto str_f
      = make_val<string_loop_fragment>(args, nullptr, nullptr, nullptr, false);
  all_ids.insert(str_f->get_id());

  REQUIRE(all_ids.size() == 3);
}
