#include "sketch.h"

#include "sketch_context.h"

#include <support/thread_context.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

using namespace support;
using namespace llvm;

namespace presyn {

sketch::sketch(props::signature sig, fragment const& frag)
    : module_("sketch", thread_context::get())
    , ctx_(sig)
{
  auto function = sig.create_function(module_);

  auto entry
      = BasicBlock::Create(thread_context::get(), "sketch.entry", function);
  auto exit
      = BasicBlock::Create(thread_context::get(), "sketch.exit", function);

  auto frag_entry = frag.compile(ctx_, exit);

  auto build = IRBuilder(entry);
  build.CreateBr(frag_entry);
}

sketch::sketch(props::signature sig, std::unique_ptr<fragment> const& frag)
    : sketch(sig, *frag)
{
}

Module& sketch::module() { return module_; }

Module const& sketch::module() const { return module_; }

} // namespace presyn
