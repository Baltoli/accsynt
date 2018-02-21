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

size_t max_gep_depth(llvm::Type *t);

template <class F>
class BinaryOp {
public:
  BinaryOp(F f) :
    create_(f)
  {}

  bool validate(value_array args)
  {
    return validate_types(2, args) && 
           llvm::isa<llvm::IntegerType>(args[0]->getType());
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
      auto ptr_ty = llvm::dyn_cast<llvm::PointerType>(ty);

      // TODO: not completely right?
      return ptr_ty && llvm::isa<llvm::ArrayType>(ptr_ty->getElementType());
    };

    return args.size() >= 2 && can_gep(args[0]) &&
           std::all_of(args.begin() + 1, args.end(), [](auto a) {
              return llvm::isa<llvm::IntegerType>(a->getType());
           });
  }

  template <typename B>
  llvm::Value *combine(B&& b, value_array args)
  {
    if(!validate(args)) {
      return nullptr;
    }

    auto ptr_ty = llvm::dyn_cast<llvm::PointerType>(args[0]->getType());
    assert(ptr_ty && "Need a pointer to GEP");

    auto indexes = std::vector<llvm::Value *>{};

    if(llvm::isa<llvm::ArrayType>(ptr_ty->getElementType())) {
      auto z_ty = llvm::IntegerType::get(ThreadContext::get(), 64);
      auto zero = llvm::ConstantInt::get(z_ty, 0);
      indexes.push_back(zero);
    }

    auto n = std::min(max_gep_depth(ptr_ty), indexes.size());
    std::copy_n(args.begin() + 1, n, std::back_inserter(indexes));

    return b.CreateGEP(args[0], indexes);
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
      BinaryOp{[](auto& b, auto* v1, auto* v2) { return b.CreateMul(v1, v2); }},
      CreateGEP{}
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
