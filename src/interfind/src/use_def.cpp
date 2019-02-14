#include <interfind/use_def.h>

#include <support/llvm_values.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/Value.h>

using namespace support;
using namespace llvm;

namespace interfind {

use_def_analysis::use_def_analysis(Function& fn) :
  function_(&fn)
{
  for(auto& bb : fn) {
    for(auto& inst : bb) {
      deps_.emplace(&inst, all_uses(&inst, false));
    }
  }
}

bool use_def_analysis::depends(Value *use, Value *def) const
{
  if(auto inst_use = dyn_cast<Instruction>(use)) {
    auto ids = deps_.at(inst_use);
    for(auto d : ids) {
      errs() << *inst_use << "  ->  " << *d << '\n';
    }
  }
  return false;
}

bool use_def_analysis::is_root_set(Value *use, std::set<Value *> roots) const
{
  return false;
}

}
