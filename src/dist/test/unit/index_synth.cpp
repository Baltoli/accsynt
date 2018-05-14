#include "catch.h"

#include <dist/contexts.h>
#include <dist/function_callable.h>
#include <dist/index_synth.h>
#include <dist/types.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/Support/raw_ostream.h>

#include <random>
#include <set>

using namespace accsynt;
using namespace llvm;

std::set<long> candidates(long i, long j)
{
  auto ret = std::set<long>{};
  ret.insert(i);
  ret.insert(3*i);
  ret.insert(5*i);

  ret.insert(j);
  ret.insert(3*j);
  ret.insert(5*j);

  ret.insert(i + j);
  ret.insert(3*i + j);
  ret.insert(5*i + j);

  ret.insert(i + 3*j);
  ret.insert(3*i + 3*j);
  ret.insert(5*i + 3*j);

  ret.insert(i + 5*j);
  ret.insert(3*i + 5*j);
  ret.insert(5*i + 5*j);
  return ret;
}

TEST_CASE( "can generate indexes using constants / indexes", "[index]" ) {
  auto&& ctx = ThreadContext::get();

  auto mod = std::make_unique<Module>("index-gen", ctx);

  auto int_ty = IntegerType::get(ctx, 64);
  auto fn_ty = FunctionType::get(int_ty, {int_ty, int_ty}, false);
  auto func = Function::Create(fn_ty, GlobalValue::ExternalLinkage, "test-idx", mod.get());

  auto entry = BasicBlock::Create(ctx, "entry", func);
  auto b = IRBuilder<>(entry);

  auto synth = IndexSynth(b);
  synth.add_index(func->arg_begin());
  synth.add_index(func->arg_begin() + 1);
  synth.add_const(b.getInt64(3));
  synth.add_const(b.getInt64(5));

  auto value = synth.generate();
  b.CreateRet(value);

  auto fc = FunctionCallable(no_error_code, func, Integer(64), Integer(64), Integer(64));

  auto rd = std::random_device{};
  auto dist = std::uniform_int_distribution<long>{};
  
  auto i = dist(rd);
  auto j = dist(rd);
  auto cs = candidates(i, j);
  auto [res] = fc(i, j);
  REQUIRE(cs.find(res) != cs.end());
}
