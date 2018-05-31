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

void test_sum(size_t n)
{
  auto i64 = Integer{64};
  auto arr = Array(i64, n);

  auto g = [n](auto a) -> int64_t {
    auto sum = 0;
    for(auto i = 0u; i < n; ++i) {
      sum += a.at(i);
    }
    return sum;
  };
  
  auto p = Oracle(g, i64, arr);
  if(auto r = p()) {
    r->print(llvm::outs(), nullptr);
  }
}

void test_dot_product()
{
  auto i64 = Integer{64};
  auto ptr = SizedPointer(i64, 0);
  auto size = Size(ptr);

  auto fun = [](int64_t s, auto v1, auto v2) -> int64_t {
    auto sum = 0;
    for(auto i = 0; i < s; ++i) {
      sum += v1.at(i) * v2.at(i);
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
  auto arr = Array(i64, size);
  
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

void test_linear()
{
  auto i64 = Integer{64};
  
  auto fun = [](auto a, auto b) -> int64_t {
    return a + b;
  };

  auto p = Oracle(fun, i64, i64, i64);
  if(auto r = p()) {
    r->print(llvm::outs(), nullptr);
  }
}

void test_output(size_t size)
{
  auto i64 = Integer{64};
  auto arr = Array{i64, size};
  auto out_arr = Output{arr};

  auto fun = [size] (auto& a, auto& o) {
    for(auto i = 0u; i < size; ++i) {
      o.at(i) = a.at(i);
    }
  };

  auto p = Oracle(fun, Void{}, arr, out_arr);
  if(auto r = p()) {
    r->print(llvm::outs(), nullptr);
  }
}

void test_vsum(size_t size)
{
  auto i64 = Integer{64};
  auto arr = Array{i64, size};
  auto out_arr = Output{arr};

  auto fun = [size] (auto& a, auto& b, auto& o) {
    for(auto i = 0u; i < size; ++i) {
      o.at(i) = a.at(i) + b.at(i);
    }
  };

  auto p = Oracle(fun, Void{}, arr, arr, out_arr);
  if(auto r = p()) {
    r->print(llvm::outs(), nullptr);
  }
}

void test_pointer()
{
  auto i64 = Integer(64);
  auto ptr = Pointer(i64);
  auto s_ptr = SizedPointer(i64, 0);
  auto size = Size(s_ptr);

  auto fun = [] (auto s, auto v, auto p) {
    int64_t sum = 0;
    for(auto i = 0u; i < s; ++i) {
      sum += v.at(i) + p.at(i);
    }
    return sum;
  };

  auto p = Oracle(fun, i64, size, s_ptr, ptr);
  if(auto r = p()) {
    r->print(llvm::outs(), nullptr);
  }
}

void test_nested()
{
  auto i64 = Integer(64);
  auto size = Size();
  auto size2 = Size();

  auto fun = [] (auto s, auto s2) {
    auto sum = 0;
    for(auto i = 0u; i < s; ++i) {
      for(auto j = 0u; j < s2; ++j) {
        sum += i;
      }
    }
    return sum;
  };

  auto p = Oracle(fun, i64, size, size2);
  if(auto r = p()) {
    r->print(llvm::outs(), nullptr);
  }
}

void test_matvec()
{
  auto i64 = Integer(64);
  auto col_ptr = SizedPointer(i64, 0);
  auto row_ptr = SizedPointer(i64, 1);
  auto cols = Size(col_ptr);
  auto rows = Size(row_ptr);
  auto ptr = Pointer(i64);

  auto fun = [] (auto cols, auto rows, auto vec, auto mat, auto& out) {
    for(auto row = 0u; row < rows; ++row) {
      long sum = 0;
      for(auto col = 0u; col < cols; ++col) {
        sum += vec.at(col);
      }
      out.at(row) = row;
    }
  };

  auto p = Oracle(fun, Void{}, cols, rows, col_ptr, ptr, Output(row_ptr));
  if(auto r = p()) {
    r->print(llvm::outs(), nullptr);
  }
}

int main()
{
  /* test_linear(); */
  /* test_sum(256); */
  /* test_dot_product(); */
  /* test_fixed_dot(4); */
  /* test_output(64); */
  /* test_vsum(4); */
  /* test_pointer(); */
  /* test_nested(); */
  test_matvec();
}
