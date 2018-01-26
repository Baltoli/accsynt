#include <dist/distinguisher.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

static LLVMContext C{};

FunctionType *function_type()
{
  auto it = IntegerType::get(C, 32);
  return FunctionType::get(it, {it, it}, false);
}

Function *make_f()
{
  auto ty = function_type();
  auto fn = Function::Create(ty, GlobalValue::ExternalLinkage, "f");
  auto bb = BasicBlock::Create(C, "", fn);
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
  auto bb = BasicBlock::Create(C, "", fn);
  auto B = IRBuilder<>(&fn->getEntryBlock());

  auto* arg_1 = fn->arg_begin();
  auto* arg_2 = (fn->arg_begin() + 1);

  auto add = B.CreateMul(arg_1, arg_2);
  auto ret = B.CreateRet(add);

  return fn;
}

int main()
{
  auto d = Distinguisher(make_f(), make_g(), "dist");
}
