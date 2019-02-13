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

bool region_finder::available(Value *ret, Value *arg) const
{
  if(arg->getType()->isVoidTy()) {
    return false;
  }

  auto is_global = [] (auto *val) {
    return isa<Constant>(val) || isa<Argument>(val) || isa<GlobalValue>(val);
  };

  if(is_global(ret) || is_global(arg)) {
    return true;
  } else {
    auto ret_i = dyn_cast<Instruction>(ret);
    auto arg_i = dyn_cast<Instruction>(arg);

    if(!ret_i || !arg_i) {
      throw std::runtime_error("Non-global, non-instructions passed to dominance");
    }

    return dom_tree_.dominates(arg_i, ret_i);
  }
}

std::set<llvm::Value *> region_finder::available_set(Value *ret) const
{
  return values_by_pred(function_, [=] (auto& arg) {
    return available(ret, &arg);
  });
}

region_finder::partition region_finder::type_partition(
    std::set<Value *> const& vs) const
{
  auto partitions = std::map<Type *, std::set<Value *>>{};

  for(auto val : vs) {
    auto ty = val->getType();
    partitions.try_emplace(ty);
    partitions.at(ty).insert(val);
  }

  return partitions;
}

bool region_finder::partition_is_valid(region_finder::partition const& part) const
{
  auto begin = argument_types_.begin();
  auto end = argument_types_.end();

  return std::any_of(begin, end, [&] (auto arg_t) {
    return part.find(arg_t) == part.end();
  });
}

std::vector<region> region_finder::all_candidates() const
{
  auto vt = values_of_type(function_, return_type_);
  for(auto v : vt) {
    auto ds = available_set(v);
    auto parts = type_partition(ds);

    errs() << "Return Value: " << *v << '\n';
    errs() << "Available:\n";
    for(auto const& [ty, vals] : parts) {
      errs() << "  Type: " << *ty << '\n';
      for(auto val : vals) {
        errs() << "    " << *val << '\n';
      }
    }
  }

  return {};
}

}
