#include <dist/distinguisher.h>

#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/Utils/Cloning.h>

using namespace llvm;

Distinguisher::Distinguisher(
  Function *old_f,
  Function *old_g,
  std::string id
) :
  C_{},
  module_(std::make_unique<Module>(id, C_)),
  f_(Function::Create(old_f->getFunctionType(), old_f->getLinkage(), 
                      old_f->getName(), module_.get())),
  g_(Function::Create(old_g->getFunctionType(), old_g->getLinkage(), 
                      old_g->getName(), module_.get()))
{
  ValueToValueMapTy v_map;
  SmallVector<ReturnInst*, 8> returns;

  auto f_arg_it = f_->arg_begin();
  for(const auto& I : old_f->args()) {
    f_arg_it->setName(I.getName());
    v_map[&I] = &*f_arg_it++;
  }

  auto g_arg_it = g_->arg_begin();
  for(const auto& I : old_g->args()) {
    g_arg_it->setName(I.getName());
    v_map[&I] = &*g_arg_it++;
  }

  CloneFunctionInto(f_, old_f, v_map, false, returns);
  CloneFunctionInto(g_, old_g, v_map, false, returns);

  module_->print(errs(), nullptr);
}

GenericValue Distinguisher::run_function(Function *f, ArrayRef<GenericValue> args)
{
  assert(f->arg_size() == args.size() && "Wrong number of arguments");

  auto&& clone = llvm::CloneModule(module_.get());
  llvm::EngineBuilder eb(std::move(clone));
  auto e = eb.create();
  return e->runFunction(f, args);
}
