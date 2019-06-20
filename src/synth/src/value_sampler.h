#pragma once

#include <support/random.h>
#include <support/tuple.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CFG.h>
#include <llvm/IR/Constant.h>
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

// Collection of sampling rules in the new style

// clang-format off
inline auto all_rules() { 
  return std::tuple{
    sampling_rule(both_floats, [] (auto& B, auto v1, auto v2) {
      return B.CreateFMul(v1, v2);
    }),
    sampling_rule(both_floats, [] (auto& B, auto v1, auto v2) {
      return B.CreateFAdd(v1, v2);
    }),
    sampling_rule(both_floats, [] (auto& B, auto v1, auto v2) {
      return B.CreateFSub(v1, v2);
    }),
    sampling_rule(one_float, [] (auto& B, auto v, auto) {
      return make_clamp(B, v);
    }),
    sampling_rule(one_float, [] (auto& B, auto v, auto) {
      return make_intrinsic(B, llvm::Intrinsic::fabs, v);
    })
  };
}
// clang-format on

// Sampling from a tuple of rules

/*
 * TODO: this is BLAS specific code - need to tidy it up and put it behind a
 * more general interface so that other domains can then pick how they want
 * to build their dataflow. Keeping instructions restricted for now.
 */
class value_sampler {
public:
  value_sampler() = default;

  template <typename Builder>
  void block(Builder&&, size_t, std::vector<llvm::Value*>&);

  void add_incoming(llvm::PHINode* phi,
      std::map<llvm::BasicBlock*, std::vector<llvm::Value*>> const& live);

  llvm::Value* constant(llvm::Type* ty) const;

protected:
  template <typename Builder>
  llvm::Value* arithmetic(Builder&& B, llvm::Value* v1, llvm::Value* v2) const;

private:
  // Internal state kept during the generation process
};

template <typename Builder>
void value_sampler::block(
    Builder&& B, size_t n, std::vector<llvm::Value*>& live)
{
  auto non_const = [](auto* v) { return !llvm::isa<llvm::Constant>(v); };

  for (auto i = 0u; i < n; ++i) {
    if (!live.empty()) {
      /* auto v1 = support::uniform_sample_if(live, non_const); */
      /* auto v2 = support::uniform_sample_if(live, non_const); */
      auto v1 = support::uniform_sample(live);
      auto v2 = support::uniform_sample(live);
      if (v1 != live.end() && v2 != live.end()) {
        auto val = arithmetic(B, *v1, *v2);
        if (val) {
          live.push_back(val);
        }
      }
    }
  }
}

template <typename Builder>
llvm::Value* value_sampler::arithmetic(
    Builder&& B, llvm::Value* v1, llvm::Value* v2) const
{
  // TODO: be more forgiving to different types being passed in here - look for
  // common base type etc and try to do some extensions / upcasting

  if (v1->getType() != v2->getType()) {
    return nullptr;
  }

  /* if (v1->getType()->isIntegerTy()) { */
  /*   return nullptr; */
  /* } */

  // TODO: check integer vs. floating point etc
  auto options = std::vector{ 8, 9, 10 };
  auto choice = *support::uniform_sample(options);
  switch (choice) {
  case 0:
    return B.CreateFAdd(v1, v2);
  case 1:
    return B.CreateFMul(v1, v2);
  case 2:
    return B.CreateFSub(v1, v2);
  case 3:
    return make_intrinsic(B, llvm::Intrinsic::fabs, v1);
  case 4:
    return make_intrinsic(B, llvm::Intrinsic::sqrt, v1);
  case 5:
    return make_intrinsic(B, llvm::Intrinsic::exp, v1);
  case 6:
    return make_clamp(B, v1);
  case 7:
    return B.CreateFDiv(v1, v2);
  case 8:
    return B.getInt32(0);
  case 9:
    return B.getInt32(1);
  case 10:
    return B.CreateAdd(v1, v2);
  }

  __builtin_unreachable();
}

} // namespace synth
