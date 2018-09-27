#include <catch2/catch.hpp>

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

  auto i64_ty = llvm::IntegerType::get(ctx, 64);
  auto extents = std::map<long, llvm::Value *>{
    {0, llvm::ConstantInt::get(i64_ty, 10)},
    {1, llvm::ConstantInt::get(i64_ty, 5)},
    {2, llvm::ConstantInt::get(i64_ty, 3)}
  };
  auto l = Loop{{}};
  auto& l2 = l.add_child(Loop{});
  auto& l3 = l2.add_child(Loop{});
  l3.add_child(Loop{});
  l.instantiate(std::array{0, 1, 2, 3});
}
