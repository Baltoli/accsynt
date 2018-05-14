#include "catch.h"

#include <dist/contexts.h>
#include <dist/index_synth.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/Support/raw_ostream.h>

using namespace accsynt;
using namespace llvm;

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

  mod->print(llvm::errs(), nullptr);
}
