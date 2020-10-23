#include <support/llvm_types.h>
#include <support/thread_context.h>

#include <catch2/catch.hpp>

#include <llvm/IR/DerivedTypes.h>

using namespace llvm;

namespace {

Type* get_opaque()
{
  auto& ctx = support::thread_context::get();
  auto struct_ty = StructType::get(ctx, "test.opaque");
  return struct_ty->getPointerTo();
}

Type* get_i32()
{
  auto& ctx = support::thread_context::get();
  return IntegerType::get(ctx, 32);
}

Type* get_i64()
{
  auto& ctx = support::thread_context::get();
  return IntegerType::get(ctx, 64);
}

} // namespace

TEST_CASE("Can work out type convertability")
{
  auto op = get_opaque();
  auto i32 = get_i32();
  auto i64 = get_i64();
  auto conv = support::type_conversions();

  conv.register_opaque(op);

  SECTION("Opaque types are registered") { REQUIRE(conv.is_opaque(op)); }

  SECTION("Can always convert from opaques")
  {
    REQUIRE(conv.is_lossless(op, op));
    REQUIRE(conv.is_lossless(op, i32));
    REQUIRE(conv.is_lossless(op, i64));
  }

  SECTION("Can't convert to opaques")
  {
    REQUIRE(!conv.is_lossless(i32, op));
    REQUIRE(!conv.is_lossless(i64, op));
  }

  SECTION("Can convert to self")
  {
    REQUIRE(conv.is_lossless(i32, i32));
    REQUIRE(conv.is_lossless(i64, i64));
  }
}
