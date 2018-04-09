#include <dist/contexts.h>
#include <dist/distinguisher.h>
#include <dist/function_callable.h>
#include <dist/linear_synth.h>
#include <dist/oracle_synth.h>
#include <dist/synth_op.h>
#include <dist/types.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>

#include <random>

using namespace accsynt;
using namespace llvm;

void test_synth_v2()
{
  auto i64 = Integer{64};
  auto arr = Array{i64, 16};
  auto idx = Index{arr};
  auto idx2 = Index{arr};

  /* auto f = [](auto a, auto b, auto c, auto d) { */
  /*   return a * a; */
  /* }; */

  /* auto o = synth::Oracle{f, i64, i64, i64, i64, i64}; */
  /* o()->print(llvm::outs(), nullptr); */

  auto g = [](auto a, auto i, auto j) -> int64_t {
    auto idx = 0;
    return a.at(idx);
  };
  
  auto p = Oracle{g, i64, arr, idx, idx2};
  if(auto r = p()) {
    r->print(llvm::outs(), nullptr);
  }
}

int main()
{
  test_synth_v2();
}
