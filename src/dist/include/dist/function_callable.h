/**
 * \file function_callable.h
 */

#pragma once

#include <dist/contexts.h>
#include <dist/types.h>
#include <dist/utils.h>

#include <llvm/ADT/APInt.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Transforms/Utils/Cloning.h>

#include <memory>
#include <vector>

namespace llvm {
  class Function;
  class Module;
}

namespace accsynt {

inline namespace v1 {

/**
 * \brief Wraps an LLVM function in a callable interface.
 *
 * This class creates a copy of the function it is constructed with, and allows
 * it to be called with native values as arguments. The return type of the
 * function must be known in advance to construct an instance of this class.
 */
template<class R>
class FunctionCallable {
public:
  /**
   * \brief Construct a callable wrapper by copying \p f.
   */
  FunctionCallable(llvm::Module *m, llvm::StringRef name, bool e = false);

  FunctionCallable(llvm::Function *f, bool e = false);

  /**
   * \brief Call the LLVM function with a variadic set of arguments.
   *
   * The compile-time size of \p args must be the same as the argument count of
   * the LLVM function associated with this callable.
   */
  template<class... Args>
  R operator()(Args... args);

  std::optional<int64_t> get_error() { return error_; };

private:
  bool uses_error_;
  std::optional<int64_t> error_ = {};

  std::unique_ptr<llvm::Module> module_;
  llvm::Function *func_;
  std::unique_ptr<llvm::ExecutionEngine> engine_;

  R return_val(llvm::GenericValue gv) const { 
    return R{gv.IntVal.getSExtValue()};
  };
};

template <typename R>
FunctionCallable<R>::FunctionCallable(llvm::Module *m, llvm::StringRef name, bool e) :
  uses_error_{e},
  module_{copy_module_to(ThreadContext::get(), m)},
  func_{module_->getFunction(name)}
{
  auto eb = llvm::EngineBuilder{std::move(module_)};
  engine_.reset(eb.create());
}

template <typename R>
FunctionCallable<R>::FunctionCallable(llvm::Function *f, bool e) :
  FunctionCallable{f->getParent(), f->getName(), e}
{
}

template<class R>
template<class... Args>
R FunctionCallable<R>::operator()(Args... args) 
{
  if(!uses_error_) assert(func_->arg_size() == sizeof...(args) && "Argument count mismatch");
  if(uses_error_) assert(func_->arg_size() - 1 == sizeof...(args) && "Argument count mismatch");

  auto func_args = std::array<llvm::GenericValue, sizeof...(args)>{
    { make_generic(args)... }
  };

  if(uses_error_) {
    auto args_with_err = std::array<llvm::GenericValue, sizeof...(args) + 1>{};
    std::copy(std::begin(func_args), std::end(func_args), std::next(std::begin(args_with_err)));

    auto err = int64_t{0};
    auto err_v = llvm::GenericValue{};
    err_v.PointerVal = &err;

    args_with_err[0] = err_v;
    auto ret = engine_->runFunction(func_, args_with_err);
    
    if(err != 0) {
      error_ = err;
      return R{0};
    } else {
      error_ = {};
      return return_val(ret);
    }
  } else {
    auto ret = engine_->runFunction(func_, func_args);
    return return_val(ret);
  }
}

template <typename T>
struct has_error_code_st : std::false_type {};

template <typename T>
struct has_error_code_st<FunctionCallable<T>> : std::true_type {};

template <typename T>
constexpr inline bool has_error_code_v = has_error_code_st<std::decay_t<T>>::value;

template <typename F, typename... Args>
decltype(auto) try_apply(F&& f, Args&&... args)
{
  using result_t = decltype(std::apply(std::forward<F>(f), std::forward<Args...>(args...)));

  try {
    auto result = std::apply(std::forward<F>(f), std::forward<Args...>(args...));

    if constexpr(has_error_code_v<F>) {
      if(auto err = f.get_error()) {
        return std::make_pair(true, result);
      }
    }

    return std::make_pair(false, result);
  } catch(...) {
    return std::make_pair(true, result_t{});
  }
}

}

namespace v2 {

template <typename> struct gv_to_val;

template <typename T>
struct gv_to_val<Output<T>> {
  decltype(auto) operator()(Output<T> arg, llvm::GenericValue gv)
  {
    auto ch = gv_to_val<T>{};
    return ch(arg.type(), gv);
  }
};

template <typename T>
struct gv_to_val<Array<T>> {
  decltype(auto) operator()(Array<T> arg, llvm::GenericValue gv)
  {
    using element_type = typename T::example_t;
    auto size = arg.array_size();
    auto ptr = static_cast<element_type *>(gv.PointerVal);
    return std::vector<element_type>(ptr, ptr + size);
  }
};

template <>
struct gv_to_val<Integer> {
  decltype(auto) operator()(Integer i, llvm::GenericValue gv)
  {
    return long{gv.IntVal.getSExtValue()};
  }
};

static constexpr struct with_error_code_tag{} with_error_code = {};
static constexpr struct no_error_code_tag{} no_error_code = {};

template <typename R, typename... Args>
class FunctionCallable {
public:
  using return_type = typename all_outputs<R, Args...>::type;

  template <typename Tag>
  FunctionCallable(Tag, llvm::Module *m, llvm::StringRef name, R r, Args... as);

  template <typename Tag>
  FunctionCallable(Tag, llvm::Function *f, R r, Args... as);

  return_type operator()(typename Args::example_t... args);

private:
  R return_type_;
  std::tuple<Args...> arg_types_;

  bool uses_error_ = false;

  std::unique_ptr<llvm::Module> module_;
  llvm::Function *func_;
  std::unique_ptr<llvm::ExecutionEngine> engine_;

  template <typename Tuple, size_t idx>
  auto collect_impl(Tuple&& t) {
    using Arg = std::tuple_element_t<idx, std::tuple<Args...>>;

    if constexpr(is_output_type<Arg>::value) {
      auto gtv = gv_to_val<Arg>{};
      return std::make_tuple(gtv(std::get<idx>(arg_types_), std::get<idx>(std::forward<decltype(t)>(t))));
    } else {
      return std::make_tuple();
    }
  }

  template <typename Tuple, std::size_t... Is>
  auto collect_impl2(Tuple&& t, std::index_sequence<Is...>) {
    return std::tuple_cat(
      collect_impl<Tuple, Is>(std::forward<decltype(t)>(t))...
    );
  }

  template <typename Tuple>
  auto collect(llvm::GenericValue return_val, Tuple&& t) {
    auto ret = collect_impl2(std::forward<decltype(t)>(t), std::make_index_sequence<sizeof...(Args)>());
    if constexpr(std::is_same_v<R, Void>) {
      return ret;
    } else {
      auto gtv = gv_to_val<R>{};
      return std::tuple_cat(std::tuple(gtv(return_type_, return_val)), ret);
    }
  }
};

template <typename R, typename... Args>
template <typename Tag>
FunctionCallable<R, Args...>::FunctionCallable(
    Tag,
    llvm::Module *m, llvm::StringRef name,
    R r, Args... args) :
  return_type_(r), arg_types_(args...),
  module_{copy_module_to(ThreadContext::get(), m)},
  func_{module_->getFunction(name)}
{
  static_assert(
    std::is_same_v<Tag, no_error_code_tag> ||
    std::is_same_v<Tag, with_error_code_tag>,
    "Unsupported tag type for function callable");

  uses_error_ = std::is_same_v<Tag, with_error_code_tag>;

  auto eb = llvm::EngineBuilder{std::move(module_)};
  engine_.reset(eb.create());
}

template <typename R, typename... Args>
template <typename Tag>
FunctionCallable<R, Args...>::FunctionCallable(
    Tag t,
    llvm::Function *f,
    R r, Args... args) :
  FunctionCallable(t, f->getParent(), f->getName(), r, args...)
{
}

template <typename R, typename... Args>
typename FunctionCallable<R, Args...>::return_type
FunctionCallable<R, Args...>::operator()(typename Args::example_t... args)
{
  using return_t = typename FunctionCallable<R, Args...>::return_type;

  assert(func_->arg_size() == sizeof...(args) + uses_error_ && "Argument count mismatch");

  auto func_args = std::array<llvm::GenericValue, sizeof...(args)>{
    { make_generic(args)... }
  };

  if(uses_error_) {
    auto args_with_err = std::array<llvm::GenericValue, sizeof...(args) + 1>{};
    std::copy(std::begin(func_args), std::end(func_args), std::next(std::begin(args_with_err)));

    auto err = int64_t{0};
    auto err_v = llvm::GenericValue{};
    err_v.PointerVal = &err;

    args_with_err[0] = err_v;
    auto ret = engine_->runFunction(func_, args_with_err);
    
    if(err != 0) {
      /* error_ = err; */
      return return_t{};
    } else {
      /* error_ = {}; */
      auto args_no_err = std::array<llvm::GenericValue, sizeof...(args)>{};
      std::copy(std::next(args_with_err.begin()), args_with_err.end(), args_no_err.begin());
      return collect(ret, args_no_err);
    }
  } else {
    auto ret = engine_->runFunction(func_, func_args);
    return collect(ret, func_args);
  }
}

}

}
