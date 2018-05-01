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

namespace accsynt {

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

    for(auto i = 0u; i < size_; ++i) {
      ret.push_back(type_.generate());
    }

    return ret;
  }

  size_t array_size() const { 
    return size_; 
  }

  Type type() const
  {
    return type_;
  }

private:
  Type type_;
  size_t size_;
};

class Index {
public:
  using example_t = size_t;

  template <typename T>
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

class Size {
public:
  using example_t = size_t;

  Size() = default;
  Size(size_t ub) : upper_bound(ub) {}

  llvm::IntegerType *llvm_type() const
  {
    return llvm::IntegerType::get(ThreadContext::get(), 64);
  }

  example_t generate() const
  {
    auto rd = std::random_device{};
    auto dis = std::uniform_int_distribution<example_t>{1, upper_bound};
    return dis(rd);
  }

  const size_t upper_bound = 1024;
};

template <typename Type>
class SizedPointer {
public:
  using example_t = std::vector<typename Type::example_t>;

  SizedPointer(Type t, Size s) :
    type(t), size(s) {}

  llvm::PointerType *llvm_type() const
  {
    return llvm::PointerType::getUnqual(type.llvm_type());
  }

  example_t generate() const
  {
    auto vec = example_t(size.upper_bound);
    std::for_each(std::begin(vec), std::end(vec), [this](auto &ex) {
      ex = type.generate();
    });
    return vec;
  }

  const Type type;
  const Size size;
};

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
    zip_for_each(types_, llvm_types, [&] (auto&& t, auto&& l) {
      l = llvm::dyn_cast<llvm::Type>(t.llvm_type());
    });
    return llvm::StructType::get(ThreadContext::get(), llvm_types);
  }

  example_t generate() const
  {
    auto ret = example_t{};
    zip_for_each(types_, ret, [&] (auto&& t, auto&& r) {
      r = t.generate();
    });
    return ret;
  }

private:
  std::tuple<Types...> types_;
};

template <typename Type>
class Output {
public:
  using example_t = typename Type::example_t;

  Output(Type t) :
    type_{t}
  {}

  auto llvm_type() const
  {
    return type_.llvm_type();
  }

  example_t generate() const
  {
    return type_.generate();
  }

  Type type() const
  {
    return type_;
  }
private:
  Type type_;
};

class Void {
public:
  auto llvm_type() const
  {
    return llvm::Type::getVoidTy(ThreadContext::get());
  }
};

template <typename T>
struct outputs {
  using type = std::tuple<>;
};

template <typename T>
struct outputs<Output<T>> {
  using type = std::tuple<typename Output<T>::example_t>;
};

template <typename T>
struct return_tuple {
  using type = std::tuple<typename T::example_t>;
};

template <>
struct return_tuple<Void> {
  using type = std::tuple<>;
};

template <typename R, typename... Args>
struct all_outputs {
  using type = decltype(
    std::tuple_cat(
      std::declval<typename return_tuple<R>::type>(),
      std::declval<typename outputs<Args>::type>()...
    )
  );
};

template <typename T>
struct is_index_type : std::false_type {};

template <>
struct is_index_type<Index> : std::true_type {};

template <typename T>
struct is_array_type : std::false_type {};

template <typename T>
struct is_array_type<Array<T>> : std::true_type {};

template <typename  T>
struct is_output_type : std::false_type {};

template <typename T>
struct is_output_type<Output<T>> : std::true_type {};

template <typename T>
constexpr bool is_index(T&& ty)
{
  return is_index_type<std::decay_t<decltype(ty)>>::value;
}

template <typename T>
constexpr bool is_array(T&& ty)
{
  return is_array_type<std::decay_t<decltype(ty)>>::value;
}

template <typename T>
constexpr bool is_output(T&& ty)
{
  return is_output_type<std::decay_t<decltype(ty)>>::value;
}

}
