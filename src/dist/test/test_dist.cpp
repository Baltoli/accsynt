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
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>

#include <random>

using namespace llvm;

FunctionType *function_type()
{
  auto it = IntegerType::get(ThreadContext::get(), 64);
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
  auto two = ConstantInt::get(IntegerType::get(ThreadContext::get(), 64), 3);
  auto mul = B.CreateMul(arg_1, two);
  B.CreateRet(mul);

  B.SetInsertPoint(ret_bb);
  auto add = B.CreateAdd(arg_1, arg_2);
  B.CreateRet(add);
  return fn;
}

std::unique_ptr<Module> make_h()
{
  auto mod = std::make_unique<Module>("hmod", ThreadContext::get());

  auto ret_t = IntegerType::get(mod->getContext(), 64);
  auto arr_t = ArrayType::get(ret_t, 4);
  auto ptr_t = PointerType::getUnqual(arr_t);
  auto fn_t = FunctionType::get(ret_t, {ptr_t, ret_t}, false);

  auto fn = Function::Create(fn_t, GlobalValue::ExternalLinkage, "h", mod.get());
  auto bb = BasicBlock::Create(fn->getContext(), "entry", fn);
  auto B = IRBuilder<>(&fn->getEntryBlock());

  auto three = ConstantInt::get(ret_t, 3);
  auto zero = ConstantInt::get(ret_t, 0);
  auto i = fn->arg_begin() + 1;

  auto max_p = B.CreateICmpSGT(i, three);
  auto max_sel = B.CreateSelect(max_p, three, i);
  auto min_p = B.CreateICmpSLT(max_sel, zero);
  auto min_sel = B.CreateSelect(min_p, zero, max_sel);

  auto gep = B.CreateGEP(fn->arg_begin(), {zero, min_sel});
  auto load = B.CreateLoad(gep);

  B.CreateRet(load);

  return mod;
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
  auto i64 = types::Integer{64};
  auto arr = types::Array{i64, 4};
  auto idx = types::Index{arr};

  /* auto f = [](auto a, auto b, auto c, auto d) { */
  /*   return a * a; */
  /* }; */

  /* auto o = synth::Oracle{f, i64, i64, i64, i64, i64}; */
  /* o()->print(llvm::outs(), nullptr); */

  auto g = [](auto a, auto i) {
    return a[i];
  };
  
  auto p = synth::Oracle{g, i64, arr, idx};
  if(auto r = p()) {
    r->print(llvm::outs(), nullptr);
  }
}

void test_array_call()
{
  auto mod = make_h();
  mod->print(llvm::outs(), nullptr);

  auto fc = FunctionCallable<intmax_t>{mod.get(), "h"};

  auto buf = std::vector<intmax_t>{{1, 2, 3, 4}};
  llvm::outs () << fc(buf, 1) << '\n';
}

void test_exn()
{
  const auto str = R"(
@_ZTIi = external constant i8*
declare i8* @__cxa_allocate_exception(i64)
declare void @__cxa_throw(i8*, i8*, i8*)

define i32 @main() {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i8* @__cxa_allocate_exception(i64 4)
  %3 = bitcast i8* %2 to i32*
  store i32 1, i32* %3, align 16
  call void @__cxa_throw(i8* %2, i8* bitcast (i8** @_ZTIi to i8*), i8* null)
  unreachable
})";

  auto sm = SMDiagnostic{};
  auto buf = MemoryBuffer::getMemBuffer(str);
  auto mod = parseIR(*buf, sm, ThreadContext::get());

  auto fc = FunctionCallable<int>{mod.get(), "main"};
  try {
    fc();
  } catch(int i) {
    llvm::outs() << i << '\n';
  }
}

int main()
{
  /* test_types(); */
  /* test_oracles(); */
  /* test_ops(); */
  test_synth_v2();
  /* test_array_call(); */
  /* test_exn(); */
}
