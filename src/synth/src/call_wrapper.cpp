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
}

call_wrapper::call_wrapper(signature sig, 
                           llvm::Module const& mod, 
                           std::string const& name, 
                           dynamic_library const& dl)
  : builder_(sig)
{
  auto mod_copy = copy_module_to(thread_context::get(), mod);

  auto sym = dl.raw_symbol(name);
  auto mod_fn = sig.create_function(*mod_copy);

  auto eb = llvm::EngineBuilder{std::move(mod_copy)};
  engine_.reset(eb.create());

  engine_->addGlobalMapping(mod_fn, sym);
}

}
