#pragma once

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

template <class F>
class BinaryOp {
public:
  BinaryOp(F f) :
    create_(f)
  {}

  bool validate(value_array args)
  {
    return validate_types(2, args);
  }

  template <typename B>
  llvm::Value *combine(B&& b, value_array args)
  {
    if(!validate(args)) {
      return nullptr;
    }

    return create_(b, args[0], args[1]);
  }
private:
  F create_;
};

class CreateGEP {
public:
  CreateGEP() = default;

  bool validate(value_array args)
  {
    const auto can_gep = [](auto val) {
      const auto ty = val->getType();
      return llvm::isa<llvm::PointerType>(ty) ||
             llvm::isa<llvm::StructType>(ty) ||
             llvm::isa<llvm::ArrayType>(ty);
    };

    return args.size() >= 2 && can_gep(args[0]);
  }

  template <typename B>
  llvm::Value *combine(B&& b, value_array args)
  {
    if(!validate(args)) {
      return nullptr;
    }

    if(auto arr = llvm::dyn_cast<llvm::ArrayType>(args[0]->getType())) {
      auto ptr_ty = llvm::PointerType::getUnqual(arr->getElementType());
      auto ptr = b.CreateBitCast(args[0], ptr_ty);
      auto ret = b.CreateInBoundsGEP(ptr, args.drop_front());
      return ret;
    } else {
      return b.CreateInBoundsGEP(args[0], args.drop_front());
    }
  }
};

class Ops {
public:
  Ops(const Ops&) = delete;
  Ops& operator=(const Ops&) = delete;

  static auto inst_all()
  {
    return std::make_tuple(
      BinaryOp{[](auto& b, auto* v1, auto* v2) { return b.CreateAdd(v1, v2); }},
      BinaryOp{[](auto& b, auto* v1, auto* v2) { return b.CreateSub(v1, v2); }},
      BinaryOp{[](auto& b, auto* v1, auto* v2) { return b.CreateMul(v1, v2); }}
      /* CreateGEP{} */
    );
  }

  static auto all()
  {
    return instance().inst_all();
  }

  template <typename B>
  static llvm::Value *sample(B&& b, value_array args)
  {
    auto candidates = std::vector<llvm::Value *>{};

    util::for_each(all(), [&] (auto op) {
      auto c = op.combine(b, args);
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

private:
  Ops() {}

  static Ops& instance();
};
