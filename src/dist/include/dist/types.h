#pragma once

#include <dist/contexts.h>
#include <dist/utils.h>

#include <random>
#include <tuple>

#include <llvm/IR/DerivedTypes.h>

namespace llvm {
  class IntegerType;
}

namespace types {

class Integer {
public:
  using example_t = intmax_t;

  Integer(size_t b = 32);

  llvm::IntegerType *llvm_type() const;

  example_t generate() const;
  size_t bits() const { return bits_; }

private:
  example_t max() const;
  example_t min() const;

  const size_t bits_;
};

template <typename Type>
class Array {
public:
  using example_t = std::vector<typename Type::example_t>;

  Array(Type t, size_t s) :
    type_{t}, size_{s}
  {}

  llvm::ArrayType *llvm_type() const
  {
    return llvm::ArrayType::get(type_.llvm_type(), size_);
  }

  example_t generate() const
  {
    auto ret = example_t{};

    for(auto i = 0; i < size_; ++i) {
      ret.push_back(type_.generate());
    }

    return ret;
  }

private:
  Type type_;
  size_t size_;
};

template <typename... Types>
class Struct {
public:
  using example_t = std::tuple<typename Types::example_t...>;

  Struct(Types... ts) :
    types_{ts...},
    llvm_types_{{ llvm::dyn_cast<llvm::Type>(ts.llvm_type())... }}
  {}

  llvm::StructType *llvm_type() const
  {
    return llvm::StructType::get(ThreadContext::get(), types_);
  }

  example_t generate() const
  {
    auto ret = example_t{};
    util::zip_for_each(types_, ret, [&] (auto&& t, auto&& r) {
      r = t.generate();
    });
    return ret;
  }
private:
  std::tuple<Types...> types_;
  std::array<llvm::Type *, sizeof...(Types)> llvm_types_;
};

}
