#include <catch2/catch.hpp>

#include "optimiser.h"

#include <support/thread_context.h>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Module.h>

using namespace support;
using namespace llvm;

TEST_CASE("Scratch tests for optimiser")
{
  auto& ctx = thread_context::get();
  auto mod = Module("test-opt", ctx);
  auto int64_ty = IntegerType::get(ctx, 64);
  auto f_ty = FunctionType::get(int64_ty, {int64_ty}, false);
  auto func = Function::Create(f_ty, GlobalValue::InternalLinkage, "ref", mod);
}
