#include <interfind/common.h>
#include <interfind/region.h>
#include <interfind/visitors.h>

#include <llvm/IR/Argument.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#include <support/cartesian_product.h>
#include <support/llvm_values.h>

using namespace support;
using namespace llvm;

namespace interfind {

/*
 * Region methods
 */

region::region(Instruction *out, std::vector<Value *> in, 
               Function& orig, FunctionType *ty) :
  output_(out), inputs_(in), original_(orig), function_type_(ty)
{
}

Instruction* region::output() const
{
  return output_;
}

std::vector<Value *> const& region::inputs() const
{
  return inputs_;
}

Function *region::extract() const
{
  auto mod = original_.getParent();
  auto func = Function::Create(function_type_, GlobalValue::ExternalLinkage, "extracted_region", mod);

  // map bbs and values to their translated equivalents?
  auto v_map = ValueToValueMapTy{};
  make_initial_value_map(v_map, func);

  auto bb = BasicBlock::Create(mod->getContext(), "", func);
  v_map[output()->getParent()] = bb;

  auto build = IRBuilder<>(bb);

  auto deps = topo_sort(all_deps(output(), inputs_));
  for(auto dep : deps) {
    if(auto i_dep = dyn_cast<Instruction>(dep)) {
      clone_instruction(i_dep, v_map, build);
    }
  }

  auto out_clone = build.Insert(output()->clone());
  for(auto j = 0u; j < out_clone->getNumOperands(); ++j) {
    auto op = out_clone->getOperand(j);
    if(v_map.find(op) != v_map.end()) {
      out_clone->setOperand(j, v_map[op]);
    }
  }

  build.CreateRet(out_clone);

  return func;
}

void region::make_initial_value_map(
    ValueToValueMapTy &v_map, Function *func) const
{
  auto i = 0;
  for(auto input : inputs_) {
    v_map[input] = func->arg_begin() + i;
    ++i;
  }
}

void region::clone_instruction(
    Instruction *inst, ValueToValueMapTy& v_map, IRBuilder<>& build) const
{
  if(v_map.find(inst) == v_map.end()) {
    auto i_clone = inst->clone();
    v_map[inst] = i_clone;
    build.Insert(i_clone);

    for(auto j = 0u; j < i_clone->getNumOperands(); ++j) {
      auto new_operand = [&] () -> llvm::Value * {
        auto oper = i_clone->getOperand(j);
        if(v_map.find(oper) == v_map.end()) {
          // Can we assert anything about the operand?
          return oper;
        } else {
          return v_map[oper];
        }
      }();

      i_clone->setOperand(j, new_operand);
    }
  }
}

/*
 * Region finder methods
 */

region_finder::region_finder(Function& fn, Type *out_t, 
                             std::vector<Type *> in_ts) :
  function_(fn), return_type_(out_t), argument_types_(in_ts),
  ud_analysis_(function_)
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

  if(is_global(ret) || is_global(arg)) {
    return true;
  } else {
    auto ret_i = dyn_cast<Instruction>(ret);
    auto arg_i = dyn_cast<Instruction>(arg);

    if(!ret_i || !arg_i) {
      throw std::runtime_error("Non-global, non-instructions passed to dominance");
    }

    return ud_analysis_.depends(ret, arg);
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

  return std::none_of(begin, end, [&] (auto arg_t) {
    return part.find(arg_t) == part.end();
  });
}

std::vector<region> region_finder::all_candidates() const
{
  auto regions = std::vector<region>{};

  auto vt = values_of_type(function_, return_type_);
  for(auto v : vt) {
    if(is_global(v) || isa<CastInst>(v)) {
      continue;
    }

    auto parts = type_partition(available_set(v));

    if(!partition_is_valid(parts)) {
      continue;
    }

    auto arg_components = std::vector<std::set<llvm::Value *>>{};
    for(auto arg_t : argument_types_) {
      arg_components.push_back(parts.at(arg_t));
    }

    // There's a big opportunity for optimisation here - if we replace the naive
    // cartesian product with a backtracking search across possible root sets,
    // then we should be able to enumerate through far fewer possible
    // combinations.
    //
    // For now the product + prune method works but slowly so I'll keep it in
    // place, but it will need to be replaced in order to scale the method. It
    // will hopefully be the smart approach that I've had half in my mind all
    // the way through this work.
    //
    // Additionally, I can probably reduce memory requirements of this part by
    // rewriting the enumeration logic to take a callback so that we don't need
    // to store everything up front?
    for(auto arg_list : cartesian_product(arg_components)) {
      if(auto inst = dyn_cast<Instruction>(v)) {
        if(ud_analysis_.is_root_set(v, arg_list)) {
          auto f_ty = FunctionType::get(return_type_, argument_types_, false);
          regions.emplace_back(inst, arg_list, function_, f_ty);
        }
      }
    }
  }

  return regions;
}

}
