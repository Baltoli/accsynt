#include <interfind/use_def.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/Value.h>

using namespace llvm;

namespace interfind {

use_def_analysis::use_def_analysis()
{
}

use_def_analysis::use_def_analysis(Function& fn)
{
}

void use_def_analysis::recompute(Function& fn)
{
}

bool use_def_analysis::depends(Value *use, Value *def) const
{
  return false;
}

bool use_def_analysis::is_root_set(Value *use, std::set<Value *> roots) const
{
  return false;
}

}
