#include "catch.h"

#include <dist/loop_synth.h>
#include <dist/types.h>

using namespace accsynt;

TEST_CASE("can use synth example generator", "[synth]") {
  auto i4 = Integer{4};
  auto synth = Synthesizer(i4, i4);
  auto&& [ex] = synth.example();
  REQUIRE(ex >= 0);
  REQUIRE(ex < 8);
}

TEST_CASE("can use loop Synthesizer", "[loopsynth]") {
  /* auto i4 = Integer{4}; */
  /* auto arr = Array{i4, 4}; */
  /* auto synth = Loop(i4, arr); */
}
