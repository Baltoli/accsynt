#include <interfind/use_def.h>

#include <support/llvm_values.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Value.h>

#include <queue>
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

bool use_def_analysis::is_root_set(
    Value *use, std::set<Value *> const& roots) const
{
  auto queue = std::queue<Value *>{{use}};

  while(!queue.empty()) {
    auto work = queue.front();
    queue.pop();

    if(roots.find(work) != roots.end()) {
      // If the value we're looking at is in the query set, then we don't
      // recurse into it.
      continue;
    }

    if(auto inst = dyn_cast<Instruction>(work)) {
      // If we find an instruction that isn't in the query set, we need to
      // recurse into its operands.
      for(auto& op : inst->operands()) {
        queue.push(op);
      }
    } else {
      // If we find something that isn't an instruction, but isn't in the query
      // set, then it's an extra root and the query set isn't valid.
      return false;
    }
  }

  return true;
}

}
