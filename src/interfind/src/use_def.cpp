#include <interfind/use_def.h>

#include <support/llvm_values.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Value.h>

#include <set>

using namespace support;
using namespace llvm;

namespace interfind {

use_def_analysis::use_def_analysis(Function& fn) :
  function_(&fn)
{
  for(auto& bb : fn) {
    for(auto& inst : bb) {
      deps_.emplace(&inst, all_deps(&inst));
    }
  }
}

bool use_def_analysis::depends(Value *use, Value *def) const
{
  if(auto inst_use = dyn_cast<Instruction>(use)) {
    auto const& ids = deps_.at(inst_use);
    return ids.find(def) != ids.end();
  }

  return false;
}

}
