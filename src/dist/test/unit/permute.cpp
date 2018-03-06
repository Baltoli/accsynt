#include "catch.h"

#include <dist/permute.h>

#include <iostream>
#include <sstream>

using namespace accsynt;
using namespace std;

TEST_CASE( "permutations can be used", "[permute]" ) {
  auto data = vector<string>{"first", "second", "third"};
  auto order = {2, 0, 1};

  auto p = Permutation(begin(order), end(order), begin(data));

  SECTION( "they support iteration" ) {
    stringstream ss;

    for(auto ptr : p) {
      ss << *ptr;
    }

    REQUIRE(ss.str() == "thirdfirstsecond");
  }

  SECTION( "they support random access" ) {
    REQUIRE(*p[0] == "third");
    REQUIRE(*p[1] == "first");
    REQUIRE(*p[2] == "second");
  }

  SECTION( "they don't change the underlying container" ) {
    REQUIRE(data[0] == "first");
    REQUIRE(data[1] == "second");
    REQUIRE(data[2] == "third");
  }
}
