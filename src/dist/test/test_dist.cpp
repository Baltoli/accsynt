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
#include <llvm/Support/raw_ostream.h>

#include <random>

using namespace llvm;

FunctionType *function_type()
{
  auto it = IntegerType::get(ThreadContext::get(), 32);
  return FunctionType::get(it, {it, it}, false);
}

Function *make_f()
{
  auto ty = function_type();
  auto fn = Function::Create(ty, GlobalValue::ExternalLinkage, "f");
  auto bb = BasicBlock::Create(ThreadContext::get(), "", fn);
  auto B = IRBuilder<>(&fn->getEntryBlock());

  auto* arg_1 = fn->arg_begin();
  auto* arg_2 = (fn->arg_begin() + 1);

  auto add = B.CreateAdd(arg_1, arg_2);
  auto ret = B.CreateRet(add);

  return fn;
}

Function *make_g()
{
  auto ty = function_type();
  auto fn = Function::Create(ty, GlobalValue::ExternalLinkage, "g");
  auto bb = BasicBlock::Create(ThreadContext::get(), "entry", fn);
  auto B = IRBuilder<>(&fn->getEntryBlock());

  auto* arg_1 = fn->arg_begin();
  auto* arg_2 = (fn->arg_begin() + 1);

  auto wrong_bb = BasicBlock::Create(ThreadContext::get(), "wrong", fn);
  auto ret_bb = BasicBlock::Create(ThreadContext::get(), "correct", fn);

  auto eq = B.CreateICmpEQ(arg_1, arg_2);
  auto br = B.CreateCondBr(eq, wrong_bb, ret_bb);

  B.SetInsertPoint(wrong_bb);
  auto two = ConstantInt::get(IntegerType::get(ThreadContext::get(), 32), 3);
  auto mul = B.CreateMul(arg_1, two);
  B.CreateRet(mul);

  B.SetInsertPoint(ret_bb);
  auto add = B.CreateAdd(arg_1, arg_2);
  B.CreateRet(add);
  return fn;
}

void test_oracles()
{
  /* auto f = FunctionCallable<int>(make_f()); */
  /* auto g = FunctionCallable<int>(make_g()); */

  /* auto d = dist::make_oracle_distinguisher<int, int>(f, g); */
  /* auto example = d(); */

  /* if(example) { */
  /*   llvm::outs() << "Counterexample!\nArgs: ("; */
  /*   util::for_each(example->args, [&](auto&& arg) { */
  /*     llvm::outs() << arg << ", "; */
  /*   }); */
  /*   llvm::outs() << ")\nf: " << example->f_return << '\n'; */
  /*   llvm::outs() << "g: " << example->g_return << '\n'; */
  /* } else { */
  /*   llvm::outs() << "Identical!\n"; */
  /* } */
}

void test_types()
{
  auto i1 = types::Integer{4};
  auto i2 = types::Integer{8};
  auto a = types::Array{i2, 2};
  auto s = types::Struct{i1, a};

  auto&& [i, ag] = s.generate();
  llvm::outs() << "{ " << i << ", ";
  for(auto i = 0; i < ag.size(); ++i) {
    if(i == 0) { 
      llvm::outs() << "["; 
    }

    llvm::outs() << ag.at(i);
    
    if(i == ag.size() - 1) {
      llvm::outs() << "]";
    } else {
      llvm::outs() << ", ";
    }
  }
  llvm::outs() << " }\n";

  s.llvm_type()->print(llvm::outs());
  llvm::outs() << '\n';
}

void test_ops()
{
  /* auto a = Add{}; */

  /* auto ty = function_type(); */
  /* auto fn = Function::Create(ty, GlobalValue::ExternalLinkage, "ops"); */
  /* auto bb = BasicBlock::Create(ThreadContext::get(), "entry", fn); */
  /* auto B = IRBuilder<>(&fn->getEntryBlock()); */

  /* auto v1 = fn->arg_begin(); */
  /* auto v2 = fn->arg_begin() + 1; */

  /* Ops::sample(B, {v1, v2}); */
  /* fn->print(llvm::errs()); */
}

void test_synth_v2()
{
  auto i32 = types::Integer{32};
  auto arr = types::Array{i32, 4};

  /* auto f = [](auto a, auto b, auto c, auto d) { */
  /*   return (a*c) + (b*d); */
  /* }; */

  /* auto o = synth::Oracle{f, i32, i32, i32, i32, i32}; */
  /* o()->print(llvm::outs(), nullptr); */

  auto g = [](auto a, auto i) {
    return a[i <= 3 ? (i < 0 ? 0 : i) : 3];
  };
  
  auto p = synth::Oracle{g, i32, arr, i32};
  if(auto r = p()) {
    r->print(llvm::outs(), nullptr);
  }
}

int main()
{
  /* test_types(); */
  /* test_oracles(); */
  /* test_ops(); */
  test_synth_v2();
}
