#pragma once

#include <dist/types.h>
#include <dist/utils.h>

#include <llvm/IR/Constants.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Value.h>

#include <random>
#include <tuple>

namespace llvm {
  template <typename> class ArrayRef;
}

using value_array = llvm::ArrayRef<llvm::Value *>;

class Add {
public:
  bool validate(value_array args);

  template <typename B>
  llvm::Value *combine(B&& b, value_array args)
  {
    if(!validate(args)) {
      return nullptr;
    }

    return b.CreateAdd(args[0], args[1]);
  }
};

class Mul {
public:
  bool validate(value_array args);

  template <typename B>
  llvm::Value *combine(B&& b, value_array args)
  {
    if(!validate(args)) {
      return nullptr;
    }

    return b.CreateMul(args[0], args[1]);
  }
};

class Ops {
public:
  Ops(const Ops&) = delete;
  Ops& operator=(const Ops&) = delete;

  static auto inst_all()
  {
    return std::make_tuple(
      Add{}, Mul{}
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
