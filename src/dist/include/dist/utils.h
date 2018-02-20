/// \file utils.h

#pragma once

#include <llvm/ADT/APInt.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/DerivedTypes.h>

#include <memory>

namespace llvm {
  class ExecutionEngine;
  class Function;
  class Module;
}

/**
 * Implementation details needed by the utility functions.
 */
namespace {

/**
 * These functions are implementation details for the tuple iteration methods
 * below. They are taken from:
 *
 * https://blog.tartanllama.xyz/exploding-tuples-fold-expressions/
 */
template <std::size_t... Idx>
auto make_index_dispatcher(std::index_sequence<Idx...>) {
    return [] (auto&& f) { (f(std::integral_constant<std::size_t,Idx>{}), ...); };
}

template <std::size_t N>
auto make_index_dispatcher() {
    return make_index_dispatcher(std::make_index_sequence<N>{}); 
}

}

/**
 * \brief Utility functions used by other parts of the code.
 *
 * Ideally everything in this namespace would be better organised.
 */
namespace util {

/**
 * \brief Copy a function into another module.
 *
 * This creates a new function inside \p m with the same body as \p f, and
 * returns the new function.
 */
llvm::Function *copy_function(llvm::Function *f, llvm::Module *m);

std::unique_ptr<llvm::Module> copy_module_to(llvm::LLVMContext& ctx, llvm::Module *m);

/**
 * \brief Create a new execution engine using a clone of \p m.
 *
 * A clone of \p m is created and used to instantiate a new execution engine.
 * The new engine is returned and can be used to execute LLVM functions.
 */
std::unique_ptr<llvm::ExecutionEngine> create_engine(llvm::Module* m);

/**
 * \brief Convert an integer value to an LLVM GenericValue.
 *
 * The type \p T must satisfy \p std::is_integral . The returned generic value
 * can be used to pass arguments to LLVM functions being executed by an
 * execution engine.
 */
template <typename T>
llvm::GenericValue make_generic(T t)
{
  if constexpr(std::is_integral_v<T>) {
    llvm::GenericValue gv;
    gv.IntVal = llvm::APInt(sizeof(T)*8, t, std::is_signed_v<T>);
    return gv;
  } else {
    llvm::GenericValue gv;
    std::vector<llvm::GenericValue> agg{};
    for(auto item : t) {
      agg.push_back(make_generic(item));
    }
    gv.AggregateVal = agg;
    return gv;
  }
}

/**
 * \brief Iterate over each item in a tuple.
 *
 * The callable \p f is called for each element of \p t, which can be any type
 * that supports \p std::get and \p std::tuple_size.
 */
template <typename Tuple, typename Func>
void for_each(Tuple&& t, Func&& f) {
  constexpr auto n = std::tuple_size_v<std::decay_t<Tuple>>;
  auto dispatcher = ::make_index_dispatcher<n>();

  dispatcher([&f,&t](auto idx) {
    f(std::get<idx>(std::forward<Tuple>(t)));
  });
}

/**
 * \brief Iterate over two zipped tuples.
 *
 * The callable \p f is called with two arguments, one from each tuple. The
 * types \p Tuple1 and \p Tuple2 must both support \p std::get and \p
 * std::tuple_size. The size of \p Tuple1 must be less than or equal to the size
 * of \p Tuple2.
 */
template <typename Tuple1, typename Tuple2, typename Func>
void zip_for_each(Tuple1&& t1, Tuple2&& t2, Func&& f) {
  constexpr auto a1_size = std::tuple_size_v<std::decay_t<Tuple1>>;
  constexpr auto a2_size = std::tuple_size_v<std::decay_t<Tuple2>>;

  static_assert(a1_size <= a2_size, "Second argument tuple is too small");

  constexpr auto n = std::tuple_size_v<std::decay_t<Tuple1>>;
  auto dispatcher = ::make_index_dispatcher<n>();

  dispatcher([&f,&t1,&t2](auto idx) {
    f(std::get<idx>(std::forward<Tuple1>(t1)), 
      std::get<idx>(std::forward<Tuple2>(t2))); 
  });
}

/**
 * \brief Get an LLVM type corresponding to a C++ type.
 *
 * The returned type will be the same size as \p T. Currently, only integral
 * types are supported.
 *
 * \todo  Handle more types, signedness etc.
 */
template <typename T>
llvm::IntegerType *get_llvm_type(llvm::LLVMContext& C)
{
  constexpr auto is_int = std::is_integral_v<T>;

  if constexpr(is_int) {
    return llvm::IntegerType::get(C, sizeof(T)*8);
  } else {
    static_assert(is_int, "Only integral types supported for LLVM so far");
  }
}

template <typename T, typename = void>
struct is_tuple : std::false_type {};

template <typename T>
struct is_tuple<T, decltype(std::tuple_size_v<T>, void())> : std::true_type {};

/**
 * \brief Type trait that detects tuple-like types.
 */
template <typename T>
constexpr inline bool is_tuple_v = is_tuple<T>::value;

}
