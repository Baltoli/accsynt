#include <catch2/catch.hpp>

#include "error_function.h"

#include <props/props.h>

#include <support/bit_cast.h>
#include <support/call_builder.h>
#include <support/thread_context.h>

#include <llvm/IR/Module.h>

using namespace support;
using namespace presyn;
using namespace props;
using namespace props::literals;
using namespace llvm;

namespace {

int64_t add_one(int64_t a) { return a + 1; }
int64_t four(int64_t) { return 4; }

} // namespace

TEST_CASE("Can get errors from built packs")
{
  auto b1 = call_builder("int f(int x, int y)"_sig, 1, 2);
  auto b2 = call_builder("int g(int abc, int def)"_sig, 1, 2);

  [[maybe_unused]] auto err = scalar_distance_error({0, b1}, {0, b2});
}

TEST_CASE("Can properly compute errors from constructed packs")
{
  auto sig = "int f(int x)"_sig;

  auto b1 = call_builder(sig, 4);
  auto b2 = call_builder(sig, 4);

  auto e1
      = scalar_distance_error({6, b1}, {bit_cast<uint64_t>(int64_t(-8)), b2});
  REQUIRE(e1 == 14);

  auto e2 = scalar_distance_error({8, b1}, {8, b2});
  REQUIRE(e2 == 0);
}

TEST_CASE("Can properly compute errors from wrappers")
{
  SECTION("For simple scalar functions")
  {
    auto mod = Module("test-mod", thread_context::get());
    auto sig = "int f(int x)"_sig;

    auto w1 = call_wrapper(sig, mod, "add_one", add_one);
    auto w2 = call_wrapper(sig, mod, "four", four);

    auto a1 = call_builder(sig, 6);
    auto e1 = compute_error(scalar_distance_error, a1, w1, w2);
    REQUIRE(e1 == 3);

    auto a2 = call_builder(sig, 3);
    auto e2 = compute_error(scalar_distance_error, a2, w1, w2);
    REQUIRE(e2 == 0);
  }
}
