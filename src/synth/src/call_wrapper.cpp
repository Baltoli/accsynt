#include "call_wrapper.h"

#include <support/llvm_cloning.h>
#include <support/thread_context.h>

using namespace support;
using namespace llvm;

namespace synth {

call_wrapper::call_wrapper(Module const& mod)
{
  auto mod_copy = copy_module_to(thread_context::get(), mod);
  auto eb = llvm::EngineBuilder{std::move(mod_copy)};
  engine_.reset(eb.create());
}

call_wrapper::call_wrapper(llvm::Module const& mod, 
                           std::string const& name)
  : call_wrapper(mod)
{
}

call_wrapper::call_wrapper(llvm::Module const& mod, 
                           std::string const& name, 
                           dynamic_library const& dl)
  : call_wrapper(mod)
{
}

}
