#include <dist/distinguisher.h>

#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/Utils/Cloning.h>

#include <random>
#include <vector>

using namespace llvm;

Distinguisher::Distinguisher(
  Function *old_f,
  Function *old_g,
  std::string id,
  size_t limit
) :
  C_{},
  module_(std::make_unique<Module>(id, C_)),
  f_(function_interface_copy(old_f, module_.get())),
  g_(function_interface_copy(old_g, module_.get())),
  example_limit_(limit)
{
  assert(old_f->arg_size() == old_g->arg_size() && "Functions must have same args");

  auto v_map = ValueToValueMapTy{};
  auto returns = SmallVector<ReturnInst*, 8>{};

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

  module_->print(llvm::outs(), nullptr);
}

Function *Distinguisher::function_interface_copy(llvm::Function *f, llvm::Module *m)
{
  return Function::Create(f->getFunctionType(), f->getLinkage(), f->getName(), m);
}

size_t Distinguisher::arg_size() const
{
  return f_->arg_size();
}

GenericValue Distinguisher::run_function(Function *f, ArrayRef<GenericValue> args) const
{
  assert(f->arg_size() == args.size() && "Wrong number of arguments");

  auto&& clone = llvm::CloneModule(module_.get());
  auto eb = llvm::EngineBuilder(std::move(clone));
  auto e = eb.create();
  return e->runFunction(f, args);
}

std::optional<std::vector<GenericValue>> Distinguisher::operator()() const
{
  auto rd = std::random_device{};
  auto engine = std::default_random_engine(rd());
  auto dist = std::geometric_distribution<int32_t>{0.1};

  for(int i = 0; i < example_limit_; ++i) {
    auto args = std::vector<GenericValue>(arg_size());
    for(auto i = 0; i < arg_size(); ++i) {
      auto val = GenericValue{};
      val.IntVal = APInt(32, dist(engine), true);
      args[i] = val;
    }

    auto f_ret = run_function(f_, args);
    auto g_ret = run_function(g_, args);

    if(f_ret.IntVal != g_ret.IntVal) {
      return args;
    }
  } 

  return {};
}
