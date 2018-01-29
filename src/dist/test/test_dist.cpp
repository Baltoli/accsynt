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
  auto bb = BasicBlock::Create(C, "entry", fn);
  auto B = IRBuilder<>(&fn->getEntryBlock());

  auto* arg_1 = fn->arg_begin();
  auto* arg_2 = (fn->arg_begin() + 1);

  auto wrong_bb = BasicBlock::Create(C, "wrong", fn);
  auto ret_bb = BasicBlock::Create(C, "correct", fn);

  auto eq = B.CreateICmpEQ(arg_1, arg_2);
  auto br = B.CreateCondBr(eq, wrong_bb, ret_bb);

  B.SetInsertPoint(wrong_bb);
  auto two = ConstantInt::get(IntegerType::get(C, 32), 3);
  auto mul = B.CreateMul(arg_1, two);
  B.CreateRet(mul);

  B.SetInsertPoint(ret_bb);
  auto add = B.CreateAdd(arg_1, arg_2);
  B.CreateRet(add);
  return fn;
}

int main()
{
  auto d = FunctionDistinguisher(make_f(), make_g(), "dist");

  auto res = d();
  if(!res) {
    llvm::outs() << "Functions are identical!\n";
  } else {
    llvm::outs() << "Found a counterexample!\n";
    llvm::outs() << "(";
    for(auto& gv : *res) {
      llvm::outs() << gv.IntVal.getLimitedValue() << ", ";
    }
    llvm::outs() << ")\n";
  }
}
