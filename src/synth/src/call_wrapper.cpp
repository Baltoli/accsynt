#include "call_wrapper.h"

#include <support/llvm_cloning.h>
#include <support/thread_context.h>

using namespace props;
using namespace support;

using namespace llvm;

namespace synth {

call_wrapper::call_wrapper(signature sig, 
                           llvm::Module const& mod, 
                           std::string const& name)
  :builder_(sig)
{
  // TODO
}

call_wrapper::call_wrapper(signature sig, 
                           llvm::Module const& mod, 
                           std::string const& name, 
                           dynamic_library const& dl)
  : builder_(sig)
{
  auto mod_copy = copy_module_to(thread_context::get(), mod);

  auto sym = dl.raw_symbol(name);
  function_ = sig.create_function(*mod_copy);

  auto wrapper = build_wrapper_function(*mod_copy, function_);

  auto topts = TargetOptions{};
  std::string err;

  mod_copy->print(llvm::errs(), nullptr);

  auto eb = llvm::EngineBuilder{std::move(mod_copy)};
  eb.setErrorStr(&err);
  eb.setEngineKind(EngineKind::JIT);
  eb.setTargetOptions(topts);
  engine_.reset(eb.create());

  if(!engine_) {
    errs() << "BAD: engine not created\n";
    errs() << err << '\n';
    throw std::runtime_error("Engine creation failed");
  }

  engine_->addGlobalMapping(function_, sym);
}

void call_wrapper::call()
{
}

llvm::Function *call_wrapper::build_wrapper_function(llvm::Module& mod, llvm::Function *fn) const
{
  auto name = fn->getName().str() + "_wrap";
  auto rt = fn->getFunctionType()->getReturnType();
  auto byte_t = IntegerType::get(thread_context::get(), 8);
  auto ptr_t = byte_t->getPointerTo();
  auto fn_ty = FunctionType::get(rt, {ptr_t}, false);

  auto new_fn = Function::Create(fn_ty, GlobalValue::ExternalLinkage, name, &mod);
  // TODO: build marshalling code in here...
  return new_fn;
}

}
