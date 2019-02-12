#include <interfind/region.h>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Dominators.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

using namespace llvm;

namespace interfind {

region::region(Value *out, std::vector<Value *> in) :
  output_(out), inputs_(in)
{
}


region_finder::region_finder(Function& fn, Type *out_t, 
                             std::vector<Type *> in_ts) :
  function_(fn), return_type_(out_t), argument_types_(in_ts)
{
}

region_finder::region_finder(Function& fn, FunctionType *fn_t) :
  region_finder(fn, fn_t->getReturnType(), fn_t->params())
{
}

std::vector<region> region_finder::all_candidates() const
{
  auto dom_tree = DominatorTree(function_);
  return {};
}

}
