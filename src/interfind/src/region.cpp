#include <interfind/region.h>
#include <interfind/visitors.h>

#include <llvm/IR/Argument.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

using namespace llvm;

namespace interfind {

/*
 * Region methods
 */

region::region(Value *out, std::vector<Value *> in) :
  output_(out), inputs_(in)
{
}

/*
 * Region finder methods
 */

region_finder::region_finder(Function& fn, Type *out_t, 
                             std::vector<Type *> in_ts) :
  function_(fn), return_type_(out_t), argument_types_(in_ts),
  dom_tree_(function_)
{
}

region_finder::region_finder(Function& fn, FunctionType *fn_t) :
  region_finder(fn, fn_t->getReturnType(), fn_t->params())
{
}

bool region_finder::dominates(Value *a, Value *b) const
{
  auto is_global = [] (auto *val) {
    return isa<Constant>(val) || isa<Argument>(val) || isa<GlobalValue>(val);
  };

  if(is_global(a)) {
    return true;
  } else if(!is_global(a) && is_global(b)) {
    return false;
  } else {
    auto ai = dyn_cast<Instruction>(a);
    auto bi = dyn_cast<Instruction>(b);

    if(!ai || !bi) {
      throw std::runtime_error("Non-global, non-instructions passed to dominance");
    }

    return dom_tree_.dominates(bi, ai);
  }
}

std::set<llvm::Value *> region_finder::dominated_set(Value *val) const
{
  return values_by_pred(function_, [=] (auto& other) {
    return dominates(val, &other);
  });
}

std::vector<region> region_finder::all_candidates() const
{
  auto vt = values_of_type(function_, return_type_);
  for(auto v : vt) {
    auto ds = dominated_set(v);
    errs() << "Value: " << *v << '\n';
    errs() << "Dominates:\n";
    for(auto dv : ds) {
      errs() << '\t' << *dv << '\n';
    }
  }

  return {};
}

}
