#pragma once

#include <dist/synth_metadata.h>
#include <dist/types.h>
#include <dist/utils.h>

#include <llvm/IR/Constants.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>

#include <functional>
#include <random>
#include <tuple>

namespace llvm {
  template <typename> class ArrayRef;
}

using value_array = llvm::ArrayRef<llvm::Value *>;

bool validate_types(size_t num, value_array args);
size_t max_gep_depth(llvm::Type *t);

template <class F>
class BinaryOp {
public:
  BinaryOp(F f) :
    create_(f)
  {}

  bool validate(SynthMetadata &m, value_array args)
  {
    return validate_types(2, args) && 
           llvm::isa<llvm::IntegerType>(args[0]->getType());
  }

  template <typename B>
  llvm::Value *combine(SynthMetadata &m, B&& b, value_array args)
  {
    if(!validate(m, args)) {
      return nullptr;
    }

    auto result = create_(m, b, args[0], args[1]);

    for(auto arg : {args[0], args[1]}) {
      if(auto b = m.index_bound(arg)) {
        m.set_index_bound(result, *b);
      }
    }

    return result;
  }

private:
  F create_;
};

class CreateGEP {
public:
  CreateGEP() = default;

  bool validate(SynthMetadata &m, value_array args)
  {
    const auto can_gep = [](auto val) {
      const auto ty = val->getType();
      auto ptr_ty = llvm::dyn_cast<llvm::PointerType>(ty);

      // TODO: not completely right?
      return ptr_ty && llvm::isa<llvm::ArrayType>(ptr_ty->getElementType());
    };

    return args.size() >= 2 && can_gep(args[0]) && m.is_index(args[1]);
  }

  template <typename B>
  llvm::Value *combine(SynthMetadata &m, B&& b, value_array args)
  {
    if(!validate(m, args)) {
      return nullptr;
    }
    assert(m.is_index(args[1]) && "Need an index to do array GEPs");

    auto ptr_ty = llvm::dyn_cast<llvm::PointerType>(args[0]->getType());
    assert(ptr_ty && "Need a pointer to GEP");

    auto indexes = std::vector<llvm::Value *>{};

    auto z_ty = llvm::IntegerType::get(ThreadContext::get(), 64);
    
    // this needs to be replaced with exception throwing code. then the code
    // that compares the two versions can run each and make sure they both
    // throw? or just ignore cases where they throw?
    auto max = llvm::ConstantInt::get(args[1]->getType(), *m.index_bound(args[1]));
    auto upper_pred = b.CreateICmpSGT(args[1], max);
    auto max_sel = b.CreateSelect(upper_pred, max, args[1]);

    auto min = llvm::ConstantInt::get(max_sel->getType(), 0);
    auto lower_pred = b.CreateICmpSLT(max_sel, min);
    auto min_sel = b.CreateSelect(lower_pred, min, max_sel);

    auto zero = llvm::ConstantInt::get(z_ty, 0);
    auto gep = b.CreateInBoundsGEP(args[0], {zero, min_sel});
    return b.CreateLoad(gep);
  }
};

class ValueSampler {
public:
  ValueSampler() = default;

  auto all() const
  {
    return std::make_tuple(
      BinaryOp{[](auto &m, auto &b, auto* v1, auto* v2) { return b.CreateAdd(v1, v2); }},
      BinaryOp{[](auto &m, auto &b, auto* v1, auto* v2) { return b.CreateSub(v1, v2); }},
      BinaryOp{[](auto &m, auto &b, auto* v1, auto* v2) { return b.CreateMul(v1, v2); }},
      CreateGEP{}
    );
  }

  // combination functions will need to take an extra parameter - const ref to
  // metadata class so that they can consult the analysis?
  // instance of this class will construct a metadata object, then expose a
  // reference so that the synthesizer can add things to it. Then pass each
  // combiner a metadata object.
  template <typename B>
  llvm::Value *operator()(B&& b, value_array args)
  {
    auto candidates = std::vector<llvm::Value *>{};

    util::for_each(all(), [&] (auto op) {
      auto c = op.combine(metadata_, b, args);
      if(c) {
        candidates.push_back(c);
      }
    });

    auto len = std::size(candidates);
    if(len == 0) {
      return nullptr;
    }

    auto rd = std::random_device{};
    auto dist = std::uniform_int_distribution<size_t>{0, len - 1};

    auto ret = candidates[dist(rd)];

    for(auto* c : candidates) {
      if(auto i = llvm::dyn_cast<llvm::Instruction>(c); c != ret) {
        i->eraseFromParent();
      }
    }

    return ret;
  }

  SynthMetadata &metadata() { return metadata_; }

private:
  SynthMetadata metadata_;
};
