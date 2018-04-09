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
  auto arr = Array{i64, 2};

  /* auto f = [](auto a, auto b, auto c, auto d) { */
  /*   return a * a; */
  /* }; */

  /* auto o = synth::Oracle{f, i64, i64, i64, i64, i64}; */
  /* o()->print(llvm::outs(), nullptr); */

  auto g = [](auto a, auto b) -> int64_t {
    return (a.at(0) * b.at(0)) + (a.at(1) * b.at(1));
  };
  
  auto p = Oracle{g, i64, arr, arr};
  if(auto r = p()) {
    r->print(llvm::outs(), nullptr);
  }
}

void test_dot_product()
{
  auto i64 = Integer{64};
  auto size = Size{};
  auto ptr = SizedPointer(i64, size);

  auto fun = [](int64_t s, auto v1, auto v2) -> int64_t {
    auto sum = 0;
    for(auto i = 0; i < s; ++i) {
      sum += v1[i] * v2[i];
    }
    return sum;
  };

  auto p = Oracle(fun, i64, size, ptr, ptr);
  if(auto r = p()) {
    r->print(llvm::outs(), nullptr);
  }
}

void test_fixed_dot(uint64_t size)
{
  auto i64 = Integer{64};
  auto arr = Array{i64, size};
  
  auto fun = [size](auto v1, auto v2) -> int64_t {
    auto sum = 0;
    for(auto i = 0u; i < size; ++i) {
      sum += v1.at(i) * v2.at(i);
    }
    return sum;
  };

  auto p = Oracle(fun, i64, arr, arr);
  if(auto r = p()) {
    r->print(llvm::outs(), nullptr);
  }
}

int main()
{
  /* test_synth_v2(); */
  /* test_dot_product(); */
  test_fixed_dot(2);
}
