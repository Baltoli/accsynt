#include <catch2/catch.hpp>

#include "optimiser.h"

#include <holes/holes.h>

#include <support/call_wrapper.h>
#include <support/llvm_format.h>
#include <support/thread_context.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <fmt/format.h>

using namespace support;
using namespace llvm;

Function* create_target(Module& mod, holes::provider& hp)
{
  auto& ctx = mod.getContext();

  auto int64_ty = IntegerType::get(ctx, 64);
  auto f_ty = FunctionType::get(int64_ty, {int64_ty}, false);
  auto func
      = Function::Create(f_ty, GlobalValue::InternalLinkage, "target", mod);

  auto bb = BasicBlock::Create(ctx, "linear", func);

  for (auto i = 0; i < 3; ++i) {
    auto hole = hp.create_hole();
    IRBuilder<>(bb).Insert(hole);
  }

  auto ret_hole = hp.create_hole(int64_ty);
  IRBuilder<>(bb).Insert(ret_hole);
  ReturnInst::Create(ctx, ret_hole, bb);

  return func;
}

Function* create_ref(Module& mod)
{
  auto& ctx = mod.getContext();

  auto int64_ty = IntegerType::get(ctx, 64);
  auto f_ty = FunctionType::get(int64_ty, {int64_ty}, false);
  auto func = Function::Create(f_ty, GlobalValue::InternalLinkage, "ref", mod);

  auto bb = BasicBlock::Create(ctx, "linear", func);

  auto B = IRBuilder<>(bb);
  auto add = B.CreateAdd(func->getArg(0), B.getInt64(7));
  auto mul = B.CreateMul(add, B.getInt64(3));
  B.CreateRet(mul);

  return func;
}

TEST_CASE("Scratch tests for optimiser")
{
  auto& ctx = thread_context::get();
  auto mod = Module("test-opt", ctx);
  auto hp = holes::provider(ctx, mod);

  auto target = create_target(mod, hp);
  auto optim = presyn::optimiser(std::move(hp));

  auto ref = create_ref(mod);
  auto wrap = call_wrapper(*ref);
  optim.run(ref, wrap);

  fmt::print("{}\n", mod);
}
