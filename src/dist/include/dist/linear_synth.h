#pragma once

#include <dist/function_callable.h>
#include <dist/types.h>
#include <dist/utils.h>

#include <llvm/Analysis/InstructionSimplify.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>

#include <algorithm>
#include <memory>
#include <mutex>
#include <random>
#include <thread>
#include <type_traits>

namespace llvm {
  class Function;
  class Module;
}

namespace synth {

namespace v2 {

template <typename R, typename... Args>
class Linear {
public:
  using ret_t = typename R::example_t;
  using args_t = std::tuple<typename Args::example_t...>;
  using io_pair_t = std::pair<ret_t, args_t>;

  Linear(R r, Args... args) :
    return_type_{r}, arg_types_{args...},
    examples_{},
    module_{std::make_unique<llvm::Module>("", ThreadContext::get())}
  {}

  void add_example(ret_t ret, args_t args);

private:
  llvm::FunctionType *llvm_function_type() const;
  size_t value_count(llvm::Function *f) const;
  bool satisfies_examples(llvm::Function *f) const;
  llvm::Value *sample(llvm::Function *f);

  R return_type_;
  std::tuple<Args...> arg_types_;

  std::vector<io_pair_t> examples_;

  std::unique_ptr<llvm::Module> module_;
};

template <typename R, typename... Args>
void Linear<R, Args...>::add_example(Linear::ret_t r, Linear::args_t args)
{
  examples_.push_back({r, args});
}

template <typename R, typename... Args>
llvm::FunctionType *Linear<R, Args...>::llvm_function_type() const
{
  auto llvm_arg_tys = std::array<llvm::Type*, sizeof...(Args)>{};
  util::zip_for_each(arg_types_, llvm_arg_tys, [] (auto a, auto& ll) {
    ll = a.llvm_type();
  });
  return llvm::FunctionType::get(return_type_.llvm_type(), llvm_arg_tys, false);
}

template <typename R, typename... Args>
size_t Linear<R, Args...>::value_count(llvm::Function *f) const
{
  auto instrs = std::accumulate
    (std::begin(*f), std::end(*f), 0, [f](auto sum, auto& bb) {
      return sum + bb.size();
    });
  return instrs + f->arg_size();
}

template <typename R, typename... Args>
bool Linear<R, Args...>::satisfies_examples(llvm::Function *f) const
{
  auto fc = FunctionCallable<R>(f);
  return std::all_of(std::begin(examples_), std::end(examples_), [&fc](auto ex) {
    return std::apply(fc, ex.second) == ex.first;
  });
}

}

using create_t = std::function<llvm::Value *(llvm::IRBuilder<>&, llvm::Value *, llvm::Value *)>;

#define sizeof_array(x) (sizeof((x)) / sizeof((x)[0]))
#define FUNC(name) ([](auto& B, auto *v1, auto *v2) { return B.Create##name(v1, v2); })

std::array<std::pair<create_t, int>, 9> linear_binary = {{
  { FUNC(Add), 5 },
  { FUNC(Sub), 1 },
  { FUNC(Mul), 5 },
  { FUNC(Shl), 1 },
  { FUNC(LShr), 1 },
  { FUNC(AShr), 1 },
  { FUNC(And), 1 },
  { FUNC(Or), 1 },
  { FUNC(Xor), 1 },
  /* { FUNC(UDiv), 1 }, */
  /* { FUNC(URem), 1 }, */
  /* { FUNC(SDiv), 1 }, */
  /* { FUNC(SRem), 1 }, */
}};

#undef FUNC

/*
 * This is a linear synthesizer.
 */
template <typename R, typename... Args>
class Linear {
public:
  Linear() :
    module_(std::make_unique<llvm::Module>("", C_)) {}

  void add_example(R ret, std::tuple<Args...> args);
  llvm::Function *operator()(bool clear = true);

private:
  llvm::LLVMContext C_;
  std::unique_ptr<llvm::Module> module_;

  void clear_functions();

  llvm::FunctionType *llvm_function_type();
  auto weighted_distribution(auto items) const;

  size_t value_count(llvm::Function *f) const;
  bool satisfies_examples(llvm::Function *f) const;
  llvm::Value *sample(llvm::Function *f);

  using example_t = std::pair<R, std::tuple<Args...>>;
  std::vector<example_t> examples_;

  std::random_device rd_;
};

template <typename R, typename... Args>
void Linear<R, Args...>::clear_functions()
{
  std::vector<llvm::Function *> to_clear;

  for(auto& F : *module_) {
    to_clear.push_back(&F);
  }

  for(auto F : to_clear) {
    F->eraseFromParent();
  }
}

template <typename R, typename... Args>
llvm::FunctionType *Linear<R, Args...>::llvm_function_type()
{
  auto ret_ty = util::get_llvm_type<R>(C_);
  auto arg_tys = std::array<llvm::Type*, sizeof...(Args)>{
    { util::get_llvm_type<Args>(C_)... }
  };

  return llvm::FunctionType::get(ret_ty, arg_tys, false);
}

template <typename R, typename... Args>
auto Linear<R, Args...>::weighted_distribution(auto items) const
{
  auto weights = std::vector<int>{};
  std::transform(std::begin(items), std::end(items), std::back_inserter(weights),
      [](auto p) { return p.second; });

  return std::discrete_distribution<>{std::begin(weights), std::end(weights)};
}

template <typename R, typename... Args>
void Linear<R, Args...>::add_example(R ret, std::tuple<Args...> args)
{
  examples_.push_back({ret, args});
}

template <typename R, typename... Args>
size_t Linear<R, Args...>::value_count(llvm::Function *f) const
{
  auto instrs = std::accumulate
    (std::begin(*f), std::end(*f), 0, [f](auto sum, auto& bb) {
      return sum + bb.size();
    });
  return instrs + f->arg_size();
}

template <typename R, typename... Args>
llvm::Value *Linear<R, Args...>::sample(llvm::Function *f)
{
  auto range = value_count(f) - 1;

  auto dist = std::uniform_int_distribution<decltype(range)>{0, range};
  auto index = dist(rd_);

  if(index < f->arg_size()) {
    return f->arg_begin() + index;
  } else {
    auto count = f->arg_size();
    for(auto& BB : *f) {
      for(auto& I : BB) {
        if(count++ == index) {
          return &I;
        }
      }
    }
  }

  // Exceptional case here - correct way to handle it?
  return nullptr;
}

template <typename R, typename... Args>
llvm::Function *Linear<R, Args...>::operator()(bool clear)
{
  if(clear) {
    clear_functions();
  }

  auto fn_ty = llvm_function_type();
  auto B = llvm::IRBuilder<>{C_};

  auto dist = weighted_distribution(linear_binary);

  while(true) {
    auto fn = llvm::Function::Create(fn_ty, llvm::GlobalValue::ExternalLinkage, "", module_.get());

    auto bb = llvm::BasicBlock::Create(C_, "", fn);
    B.SetInsertPoint(bb);

    for(auto i = 0; i < 10; ++i) {
      auto v1 = sample(fn);
      auto v2 = sample(fn);
      linear_binary[dist(rd_)].first(B, v1, v2);
    }

    B.CreateRet(sample(fn));

    if(satisfies_examples(fn)) {
      return fn;
    } else {
      fn->eraseFromParent();
    }
  }
}

template <typename R, typename... Args>
bool Linear<R, Args...>::satisfies_examples(llvm::Function *f) const
{
  auto fc = FunctionCallable<R>(f);
  return std::all_of(std::begin(examples_), std::end(examples_), [&fc](auto ex) {
    return std::apply(fc, ex.second) == ex.first;
  });
}


}
