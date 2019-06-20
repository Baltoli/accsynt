#pragma once

#include <support/random.h>
#include <support/tuple.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CFG.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Intrinsics.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>

#include <vector>

namespace synth {

// Helpers to make slightly more complex patterns

template <typename Builder>
llvm::Value* make_intrinsic(
    Builder&& B, llvm::Intrinsic::ID id, llvm::Value* v1)
{
  auto mod = B.GetInsertBlock()->getParent()->getParent();
  auto intrinsic = llvm::Intrinsic::getDeclaration(mod, id, v1->getType());
  return B.CreateCall(intrinsic, v1);
}

template <typename Builder>
llvm::Value* make_clamp(Builder&& B, llvm::Value* v1)
{
  auto zero = llvm::ConstantFP::get(B.getFloatTy(), 0.0);
  auto cond = B.CreateFCmpOLT(v1, zero);
  return B.CreateSelect(cond, zero, v1);
}

// New sampling rules

template <typename Pred, typename Build>
class sampling_rule {
public:
  sampling_rule(Pred&&, Build&&);
  sampling_rule(size_t, Pred&&, Build&&);

  bool valid_for(llvm::Type*, llvm::Type*);

  template <typename IRBuilder>
  llvm::Value* build(IRBuilder&, llvm::Value*, llvm::Value*);

  size_t weight() const { return weight_; }

private:
  size_t weight_;
  Pred pred_;
  Build build_;
};

template <typename Pred, typename Build>
sampling_rule<Pred, Build>::sampling_rule(size_t w, Pred&& p, Build&& b)
    : weight_(w)
    , pred_(std::forward<Pred>(p))
    , build_(std::forward<Build>(b))
{
}

template <typename Pred, typename Build>
sampling_rule<Pred, Build>::sampling_rule(Pred&& p, Build&& b)
    : sampling_rule(1, std::forward<Pred>(p), std::forward<Build>(b))
{
}

template <typename Pred, typename Build>
bool sampling_rule<Pred, Build>::valid_for(llvm::Type* t1, llvm::Type* t2)
{
  return pred_(t1, t2);
}

template <typename Pred, typename Build>
template <typename IRBuilder>
llvm::Value* sampling_rule<Pred, Build>::build(
    IRBuilder& B, llvm::Value* v1, llvm::Value* v2)
{
  return build_(B, v1, v2);
}

// Sampling predicates

bool both_floats(llvm::Type*, llvm::Type*);
bool one_float(llvm::Type*, llvm::Type*);

bool same_ints(llvm::Type*, llvm::Type*);
bool one_int(llvm::Type*, llvm::Type*);

bool same_type(llvm::Type*, llvm::Type*);

bool any(llvm::Type*, llvm::Type*);
bool none(llvm::Type*, llvm::Type*);

// Collection of sampling rules in the new style

// clang-format off
inline auto all_rules() { 
  return std::tuple{
    sampling_rule(1, both_floats, [] (auto& B, auto v1, auto v2) {
      return B.CreateFMul(v1, v2);
    }),
    sampling_rule(1, both_floats, [] (auto& B, auto v1, auto v2) {
      return B.CreateFAdd(v1, v2);
    }),
    sampling_rule(1, both_floats, [] (auto& B, auto v1, auto v2) {
      return B.CreateFSub(v1, v2);
    }),
    sampling_rule(1, one_float, [] (auto& B, auto v, auto) {
      return make_clamp(B, v);
    }),
    sampling_rule(1, one_float, [] (auto& B, auto v, auto) {
      return make_intrinsic(B, llvm::Intrinsic::fabs, v);
    }),
    sampling_rule(1, one_float, [] (auto& B, auto v, auto) {
      return make_intrinsic(B, llvm::Intrinsic::exp, v);
    }),
    sampling_rule(1, one_float, [] (auto& B, auto v, auto) {
      return make_intrinsic(B, llvm::Intrinsic::sqrt, v);
    }),
    sampling_rule(1, same_ints, [] (auto& B, auto v1, auto v2) {
      return B.CreateAdd(v1, v2);
    }),
    sampling_rule(1, same_ints, [] (auto& B, auto v1, auto v2) {
      return B.CreateMul(v1, v2);
    }),
    sampling_rule(1, same_ints, [] (auto& B, auto v1, auto v2) {
      return B.CreateSub(v1, v2);
    }),
    sampling_rule(1, any, [] (auto& B, auto, auto) {
      return B.getInt32(0);
    }),
    sampling_rule(1, any, [] (auto& B, auto, auto) {
      return B.getInt32(1);
    }),
    sampling_rule(1, any, [] (auto& B, auto, auto) {
      return llvm::ConstantFP::get(B.getFloatTy(), 0.0);
    })
  };
}
// clang-format on

// Sampling from a tuple of rules

template <typename Builder>
void weighted_rule_sample(Builder&& B, std::vector<llvm::Value*>& live)
{
  auto rules = all_rules();
  size_t total_weight = 0;

  support::for_each(
      rules, [&total_weight](auto& rule) { total_weight += rule.weight(); });

  if (total_weight == 0) {
    return;
  }

  auto spot = support::random_int<size_t>(0, total_weight - 1);
  bool done = false;

  size_t running_weight = 0;
  size_t max_attempts = 16;

  support::for_each(rules, [&](auto& rule) {
    running_weight += rule.weight();

    if (done || rule.weight() == 0) {
      return;
    }

    if (spot < running_weight) {
      for (auto attempts = 0u; attempts < max_attempts && !done; ++attempts) {
        auto v1 = support::uniform_sample(live);
        auto v2 = support::uniform_sample(live);

        if (v1 != live.end() && v2 != live.end()
            && rule.valid_for((*v1)->getType(), (*v2)->getType())) {
          auto val = rule.build(B, *v1, *v2);
          if (val) {
            live.push_back(val);
            done = true;
          }
        }
      }
    }
  });
}

// value sampling wrapper class called by the dataflow synthesis process

class value_sampler {
public:
  value_sampler() = default;

  template <typename Builder>
  void block(Builder&&, size_t, std::vector<llvm::Value*>&);

  void add_incoming(llvm::PHINode* phi,
      std::map<llvm::BasicBlock*, std::vector<llvm::Value*>> const& live);

  llvm::Value* constant(llvm::Type* ty) const;
};

template <typename Builder>
void value_sampler::block(
    Builder&& B, size_t n, std::vector<llvm::Value*>& live)
{
  for (auto i = 0u; i < n; ++i) {
    weighted_rule_sample(B, live);
  }
}

} // namespace synth
