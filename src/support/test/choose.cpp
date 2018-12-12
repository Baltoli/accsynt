#include <support/choose.h>

#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace support;

TEST_CASE("can use choices") {
  choose(12, 3).for_each([&] (auto idxs) {
  });
}
