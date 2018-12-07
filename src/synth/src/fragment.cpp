#include "fragment.h"

#include <llvm/IR/Constant.h>
#include <llvm/IR/Function.h>

#include <algorithm>
#include <numeric>

using namespace llvm;
using namespace props;

namespace synth {

std::vector<fragment::frag_ptr> fragment::enumerate_all(std::vector<frag_ptr>&& fragments)
{
  auto ret = std::vector<fragment::frag_ptr>{};

  std::sort(fragments.begin(), fragments.end());
  do {
    auto all_for_perm = enumerate_permutation(fragments);
    for(auto&& frag : all_for_perm) {
      ret.push_back(std::move(frag));
    }
  } while(std::next_permutation(fragments.begin(), fragments.end()));

  return std::move(ret);
}

std::vector<fragment::frag_ptr> fragment::enumerate_permutation(std::vector<frag_ptr> const& perm)
{
  if(perm.empty()) {
    return {};
  }

  auto ret = std::vector<fragment::frag_ptr>{};

  auto begin = std::next(perm.begin());
  auto end = perm.end();
  auto accum = perm.at(0)->clone();

  enumerate_recursive(ret, std::move(accum), begin, end);
  return std::move(ret);
}

fragment::fragment(std::vector<value> args) :
  args_(args)
{
}

compile_metadata fragment::compile(compile_context& ctx)
{
  splice(ctx, ctx.entry_, ctx.exit_);
  return ctx.metadata_;
}

size_t fragment::count_or_empty(fragment::frag_ptr const& frag)
{
  if(frag) {
    return frag->count_holes();
  } else {
    return 1;
  }
}

std::string fragment::string_or_empty(frag_ptr const& frag, size_t ind)
{
  if(frag) {
    return frag->to_str(ind);
  } else {
    return fmt::format("{}[?]", ::support::indent{ind});
  }
}

/**
 * From what I've thought about, I think the best thing to do is to have a
 * context "own" / manage a single function which is created when we create a
 * context object - then we can also keep track of the appropriate basic blocks
 * with the context object as well.
 */
compile_context::compile_context(Module& mod, signature sig) :
  sig_(sig), mod_(mod), 
  func_(sig_.create_function(mod_)),
  entry_(BasicBlock::Create(mod_.getContext(), "entry", func_)),
  exit_(BasicBlock::Create(mod_.getContext(), "exit", func_)),
  metadata_(func_)
{
  auto& ctx = mod_.getContext();

  auto rt = func_->getFunctionType()->getReturnType();
  if(rt->isVoidTy()) {
    return_ = ReturnInst::Create(ctx, exit_);
  } else {
    auto zero = Constant::getNullValue(rt);
    return_ = ReturnInst::Create(ctx, zero, exit_);
  }
}

llvm::Argument *compile_context::argument(std::string const& name)
{
  return std::next(func_->arg_begin(), sig_.param_index(name));
}

compile_metadata::compile_metadata(llvm::Function *fn)
  : function(fn)
{
}

}
