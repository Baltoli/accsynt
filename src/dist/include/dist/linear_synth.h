#pragma once

#include <dist/function_callable.h>
#include <dist/synth_op.h>
#include <dist/types.h>
#include <dist/utils.h>

#include <llvm/Analysis/InstructionSimplify.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>

#include <algorithm>
#include <forward_list>
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

template <typename R, typename... Args>
class Linear {
public:
  using ret_t = typename R::example_t;
  using args_t = std::tuple<typename Args::example_t...>;
  using io_pair_t = std::pair<ret_t, args_t>;

  Linear(R r, Args... args) :
    return_type_{r}, arg_types_{args...},
    examples_{}
  {}

  void add_example(ret_t ret, args_t args);
  std::unique_ptr<llvm::Module> operator()(bool clear = true);

  std::tuple<Args...> arg_types() const { return arg_types_; }

private:
  llvm::FunctionType *llvm_function_type() const;
  size_t value_count(llvm::Function *f) const;
  bool satisfies_examples(llvm::Function *f) const;
  llvm::Value *sample(llvm::Function *f);

  void clear_functions(llvm::Module& module);

  R return_type_;
  std::tuple<Args...> arg_types_;

  std::vector<io_pair_t> examples_;
};

template <typename R, typename... Args>
std::unique_ptr<llvm::Module> Linear<R, Args...>::operator()(bool clear)
{
  auto ret = std::unique_ptr<llvm::Module>{};
  auto mut = std::mutex{};

  auto work = [&] {
    auto fn_ty = llvm_function_type();
    auto B = llvm::IRBuilder<>{ThreadContext::get()};
    auto mod = std::make_unique<llvm::Module>("", ThreadContext::get());

    while(true) {
      if(ret) {
        return;
      }

      if(clear) {
        clear_functions(*mod);
      }

      auto fn = llvm::Function::Create(fn_ty, llvm::GlobalValue::ExternalLinkage, 
                                       "cand", mod.get());

      auto bb = llvm::BasicBlock::Create(ThreadContext::get(), "", fn);
      B.SetInsertPoint(bb);

      for(auto i = 0; i < 20; ++i) {
        auto v1 = sample(fn);
        auto v2 = sample(fn);
        
        // is this the right thing to do?
        if(!Ops::sample(B, {v1, v2})) {
          return;
        }
      }

      B.CreateRet(sample(fn));

      if(satisfies_examples(fn)) {
        ret = std::move(mod);
        return;
      } else {
        fn->eraseFromParent();
      }
    }
  };

  auto threads = std::forward_list<std::thread>{};
  auto max_threads = 1; // std::thread::hardware_concurrency()
  for(auto i = 0; i < max_threads; ++i) {
    threads.emplace_front(work);
  }

  for(auto& t : threads) {
    t.join();
  }

  return ret;
}

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
  auto fc = FunctionCallable<ret_t>(f->getParent(), f->getName());
  return std::all_of(std::begin(examples_), std::end(examples_), [&fc](auto ex) {
    return std::apply(fc, ex.second) == ex.first;
  });
}

template <typename R, typename... Args>
llvm::Value *Linear<R, Args...>::sample(llvm::Function *f)
{
  auto rd = std::random_device{};

  auto range = value_count(f) - 1;

  auto dist = std::uniform_int_distribution<decltype(range)>{0, range};
  auto index = dist(rd);

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
void Linear<R, Args...>::clear_functions(llvm::Module& module)
{
  auto to_clear = std::forward_list<llvm::Function *>{};

  for(auto& f : module) {
    to_clear.push_front(&f);
  }

  for(auto* f : to_clear) {
    f->eraseFromParent();
  }
}

}
