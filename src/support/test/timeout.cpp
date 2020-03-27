#include <catch2/catch.hpp>

#include <support/timeout.h>

#include <thread>

using namespace support;
using namespace std::literals::chrono_literals;

TEST_CASE("Can run short operations that don't time out")
{
  auto x = 0;

  auto op = [&x] { x = 2; };
  auto tm_out = [&x] { x = -3; };

  timeout(5s, op, tm_out);

  REQUIRE(x == 2);
}

TEST_CASE("Can run longer operations")
{
  auto x = 0;
  auto run = true;
  auto now = std::chrono::steady_clock::now();
  auto end = now + 3s;

  auto op = [&] {
    while (std::chrono::steady_clock::now() < end) {
      if (!run) {
        return;
      }
    }

    x = 1;
  };

  auto tm_out = [&run] { run = false; };

  timeout(100ms, op, tm_out);
  REQUIRE(x == 0);
}
