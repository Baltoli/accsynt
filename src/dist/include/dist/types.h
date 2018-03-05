#pragma once

#include <dist/contexts.h>
#include <dist/utils.h>

#include <random>
#include <tuple>
#include <variant>

#include <llvm/IR/DerivedTypes.h>

namespace llvm {
  class IntegerType;
}

namespace types {

template <typename> struct example_ts;

template <typename... Args>
struct example_ts<std::tuple<Args...>> {
  using type = std::tuple<typename Args::example_t...>;
};

class Integer {
public:
  using example_t = intmax_t;

  Integer(size_t b = 64);

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

  llvm::PointerType *llvm_type() const
  {
    return llvm::PointerType::getUnqual(
      llvm::ArrayType::get(type_.llvm_type(), size_));
  }

  example_t generate() const
  {
    auto ret = example_t{};

    for(auto i = 0; i < size_; ++i) {
      ret.push_back(type_.generate());
    }

    return ret;
  }

  size_t array_size() const { 
    return size_; 
  }

private:
  Type type_;
  size_t size_;
};

template <typename T>
class Index {
public:
  using example_t = size_t;

  Index(Array<T> const& a) :
    bound_(a.array_size() - 1)
  {}

  Index(size_t b) :
    bound_(b)
  {}

  llvm::IntegerType *llvm_type() const
  {
    return llvm::IntegerType::get(ThreadContext::get(), 64);
  }

  example_t generate() const
  {
    auto rd = std::random_device{};
    auto dis = std::uniform_int_distribution<example_t>{0, bound()};
    return dis(rd);
  }

  size_t bound() const 
  {
    return bound_;
  }

private:
  size_t bound_;
};

namespace {

template <typename T>
struct is_index_type : std::false_type {};

template <typename T>
struct is_index_type<Index<T>> : std::true_type {};

}

constexpr bool is_index(auto&& ty) {
  return is_index_type<std::decay_t<decltype(ty)>>::value;
}

template <typename... Types>
class Struct {
public:
  using example_t = std::tuple<typename Types::example_t...>;

  Struct(Types... ts) :
    types_{ts...}
  {}

  llvm::StructType *llvm_type() const
  {
    auto llvm_types = std::array<llvm::Type *, sizeof...(Types)>{};
    util::zip_for_each(types_, llvm_types, [&] (auto&& t, auto&& l) {
      l = llvm::dyn_cast<llvm::Type>(t.llvm_type());
    });
    return llvm::StructType::get(ThreadContext::get(), llvm_types);
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
};

}
