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

namespace accsynt {

using value_array = llvm::ArrayRef<llvm::Value *>;

bool validate_types(size_t num, value_array args);
size_t max_gep_depth(llvm::Type *t);

class ConstantValue {
public:
  ConstantValue(int64_t v) :
    value(v) {}

  template <typename B>
  llvm::Value *combine(SynthMetadata &m, B&& b, value_array args)
  {
    auto load = constant_instruction(b, value);
    m.set_index_bound(load, value);
    return load;
  }

  const int64_t value;
};

class RandomIndex {
public:
  bool validate(SynthMetadata &m, value_array args)
  {
    return args.size() > 0 && m.has_size(args[0]);
  }
  
  template <typename B>
  llvm::Value *combine(SynthMetadata &m, B&& b, value_array args)
  {
    if(!validate(m, args)) {
      return nullptr;
    }

    auto size = m.size(args[0]).value();

    auto rd = std::random_device{};
    auto dist = std::uniform_int_distribution<uint64_t>{0, size - 1};

    auto inst = constant_instruction(b, dist(rd));
    m.set_index_bound(inst, size - 1);
    return inst;
  }
};

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
    
    auto max = llvm::ConstantInt::get(args[1]->getType(), *m.index_bound(args[1]));
    auto upper_pred = b.CreateICmpUGT(args[1], max);
    m.make_oob_flag(upper_pred);

    auto zero = llvm::ConstantInt::get(z_ty, 0);
    auto gep = b.CreateInBoundsGEP(args[0], {zero, args[1]});
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
      /* BinaryOp{[](auto &m, auto &b, auto* v1, auto* v2) { return b.CreateSub(v1, v2); }}, */
      BinaryOp{[](auto &m, auto &b, auto* v1, auto* v2) { return b.CreateMul(v1, v2); }},
      CreateGEP{},
      RandomIndex{}
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

    for_each(all(), [&] (auto op) {
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
      if(auto i = llvm::dyn_cast<llvm::Instruction>(c); i && c != ret) {
        i->eraseFromParent();
      }
    }

    return ret;
  }

  SynthMetadata &metadata() { return metadata_; }

private:
  SynthMetadata metadata_;
};

}
