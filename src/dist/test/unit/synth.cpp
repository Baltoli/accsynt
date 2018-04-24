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
}

TEST_CASE("can use loop builder", "[loopbuilder]") {
  auto& ctx = ThreadContext::get();
  auto mod = std::make_unique<llvm::Module>("builder-mod", ctx);
  auto void_ty = llvm::Type::getVoidTy(ctx);
  auto fn_ty = llvm::FunctionType::get(void_ty, {}, false);
  auto fn = llvm::Function::Create(fn_ty, llvm::GlobalValue::ExternalLinkage, "test", mod.get());
  auto ret_bb = llvm::BasicBlock::Create(ctx, "post", fn);
  llvm::ReturnInst::Create(ctx, ret_bb);

  auto extents = std::map<long, long>{
    {0, 10},
    {1, 5},
    {2, 3}
  };
  auto l = Loop{};
  auto& ch = l.add_child(Loop{});
  ch.add_child(Loop{});
  l.instantiate(std::array{0, 1, 2, 3});
  auto irl = IRLoop(fn, l, extents, ret_bb);

  mod->print(llvm::errs(), nullptr);
}
