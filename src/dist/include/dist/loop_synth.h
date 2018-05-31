#pragma once

#include <llvm/IR/IRBuilder.h>

#include <dist/block_gen.h>
#include <dist/index_synth.h>
#include <dist/loop_shapes.h>
#include <dist/synth.h>
#include <dist/synth_metadata.h>

#include <memory>

namespace accsynt {

struct LoopBody {
  llvm::BasicBlock *body;
  std::vector<llvm::Value *> loop_indexes;
  llvm::Instruction *insert_point;
};

class IRLoop {
public:
  IRLoop(
      llvm::Function *f, 
      Loop l, 
      std::set<llvm::Value *> a, 
      llvm::BasicBlock *err,
      std::map<long, llvm::Value *> const& sizes, 
      std::vector<std::set<long>> const& coalesced,
      std::vector<llvm::Value *> parent_iters,
      SynthMetadata m);

  std::set<llvm::Value *> const& available_values() const;
  llvm::BasicBlock *header() const;
  llvm::BasicBlock *pre_body() const;
  std::vector<IRLoop> const& children() const;
  llvm::BasicBlock *post_body() const;
  llvm::BasicBlock * exit() const;

private:
  void layout_children(llvm::Value *parent = nullptr);
  void construct_loop();
  llvm::Value *make_iterator();
  void construct_sequence();
  void construct_error_checks();

  template <typename Loc>
  void generate_body(llvm::Value *iter, SynthMetadata& meta, Loc loc);

  llvm::Value *create_valid_sized_gep(
    llvm::IRBuilder<>& b, llvm::Value *data, llvm::Value *idx, 
    llvm::Value *size, llvm::BasicBlock *bb);

  llvm::Function *func_;
  Loop loop_;

  std::map<long, llvm::Value *> const& sizes_;
  std::vector<std::set<long>> const& coalesced_;
  std::set<llvm::Value *> available_ = {};
  std::vector<llvm::Value *> parent_iters_;
  std::set<llvm::Instruction *> gep_check_instrs_ = {};

  llvm::BasicBlock *error_block_;
  llvm::BasicBlock *header_ = nullptr;
  llvm::BasicBlock *pre_body_ = nullptr;
  std::vector<IRLoop> children_ = {};
  llvm::BasicBlock *post_body_ = nullptr;
  llvm::BasicBlock *exit_ = nullptr;

  SynthMetadata meta_;
};

template <typename Loc>
void IRLoop::generate_body(llvm::Value *iter, SynthMetadata& meta, Loc loc)
{
  auto id = *loop_.ID();

  auto B = llvm::IRBuilder<>(loc);
  for(auto v : available_) {
    meta.live(v) = true;
  }

  auto indexer = IndexSynth(B);

  indexer.add_index(iter);
  for(auto parent_iter : parent_iters_) {
    indexer.add_index(parent_iter);
  }

  for(auto [id, size] : sizes_) {
    indexer.add_const(size);
  }

  for(auto lid : coalesced_.at(id)) {
    auto actual_iter = indexer.generate();
    meta.live(actual_iter) = true;

    auto data_ptr = func_->arg_begin() + lid + 1;
    auto item_ptr = create_valid_sized_gep(B, data_ptr, actual_iter, sizes_.at(id), error_block_);
    meta.live(B.CreateLoad(item_ptr)) = true;

    meta.output(item_ptr) = static_cast<bool>(meta.output(data_ptr));
  }
  
  // TODO: access things with physical sizes?

  if(meta.return_loc) {
    meta.live(B.CreateLoad(meta.return_loc)) = true;
  }

  for(auto it = func_->arg_begin(); it != func_->arg_end(); ++it) {
    meta.output(it) = false;
  }

  auto gen = BlockGenerator(B, meta);
  gen.populate(20);
  gen.output();

  for(auto v : meta.live) {
    available_.insert(v);
  }
}

template <typename R, typename... Args>
class LoopSynth : public Synthesizer<R, Args...> {
public:
  LoopSynth(R r, Args... args) 
    : Synthesizer<R, Args...>(r, args...),
      const_sizes_{}, rt_size_offsets_{}
  {
    index_for_each(this->arg_types_, [&] (auto& ty, auto i) {
      register_arg(ty, i);
    });

    auto ids = std::vector<long>{};
    for(auto pair : const_sizes_) {
      ids.emplace_back(pair.first);
    }
    for(auto pair : rt_size_offsets_) {
      ids.emplace_back(pair.first);
    }

    coalesced_ids_ = ids_to_coalesce();

    auto loop_set = Loop::loops(coalesced_ids_.size());
    std::copy(begin(loop_set), end(loop_set), std::back_inserter(loops_));
  }

  template <typename ArgTy>
  void register_arg(ArgTy ty, int i)
  {
    if constexpr(is_array(ty)) {
      const_sizes_.insert_or_assign(i, ty.array_size());
    }

    if constexpr(is_output(ty)) {
      outputs_.emplace_back(i);
      register_arg(ty.type(), i);
    }

    if constexpr(is_sized_pointer(ty)) {
      rt_size_offsets_.insert_or_assign(i, ty.size_index);
    }

    if constexpr(is_pointer(ty)) {
      physical_sizes_.insert_or_assign(i, ty.physical_size);
    }
  }

  using Synthesizer<R, Args...>::operator();

  // We can use this synthesizer when at least one (for now, exactly one?) of
  // the parameters is sized (i.e. is a fixed size array)
  // extend to handle sized pointers next
  virtual bool can_synthesize() const override
  {
    return !const_sizes_.empty() || !rt_size_offsets_.empty();
  }

private:
  void construct(llvm::Function *f, llvm::IRBuilder<>& b) const override;
  llvm::Value *construct_return(llvm::Type *rt, llvm::BasicBlock *where, 
                                llvm::IRBuilder<>& b) const;

  auto next_shape() const;
  SynthMetadata initial_metadata(llvm::Function *) const;
  std::vector<std::set<long>> ids_to_coalesce() const;
  std::map<long, llvm::Value *> runtime_sizes(llvm::Function *) const;
  llvm::BasicBlock *create_error_block(
      llvm::Function *f, llvm::IRBuilder<>& b, llvm::BasicBlock *post) const;

  std::vector<long> outputs_;
  std::map<long, long> const_sizes_;
  std::map<long, long> physical_sizes_;
  std::map<long, long> rt_size_offsets_;
  std::vector<std::set<long>> coalesced_ids_;

  mutable std::mutex mut = {};
  mutable std::vector<Loop> loops_;
};

template <typename R, typename... Args>
llvm::Value *
LoopSynth<R, Args...>::construct_return(
    llvm::Type *rt, llvm::BasicBlock *where, 
    llvm::IRBuilder<>& b) const
{
  auto insert = b.saveIP();

  auto ret = [&] () -> llvm::Value* {
    if(rt->isVoidTy()) {
      b.SetInsertPoint(where);
      b.CreateRetVoid();
      return nullptr;
    } else {
      auto loc = b.CreateAlloca(rt);
      b.CreateStore(llvm::ConstantInt::get(rt, 0), loc);

      b.SetInsertPoint(where);
      auto ret_load = b.CreateLoad(loc);
      b.CreateRet(ret_load);

      return loc;
    }
  }();

  b.restoreIP(insert);
  return ret;
}

template <typename R, typename... Args>
void LoopSynth<R, Args...>::construct(llvm::Function *f, llvm::IRBuilder<>& b) const
{
  auto shape = next_shape();
  shape = next_shape();

  auto post_loop_bb = llvm::BasicBlock::Create(f->getContext(), "post-loop", f);
  auto err_bb = create_error_block(f, b, post_loop_bb);

  auto function_meta = initial_metadata(f);
  function_meta.return_loc = construct_return(f->getReturnType(), post_loop_bb, b);
  IRLoop irl(f, shape, {}, err_bb, runtime_sizes(f), coalesced_ids_, {}, function_meta);

  b.CreateBr(irl.header());

  b.SetInsertPoint(irl.exit());
  b.CreateBr(post_loop_bb);

  /* llvm::errs() << *f << '\n'; */
}

template <typename R, typename... Args>
auto LoopSynth<R, Args...>::next_shape() const
{
  std::unique_lock ul{mut};
  auto shape = loops_.at(0);
  std::rotate(begin(loops_), std::next(begin(loops_)), end(loops_));
  return shape;
}

template <typename R, typename... Args>
SynthMetadata LoopSynth<R, Args...>::initial_metadata(llvm::Function *f) const
{
  auto meta = SynthMetadata{};

  for(auto [idx, size] : const_sizes_) {
    meta.const_size(f->arg_begin() + idx + 1) = size;
  }

  for(auto idx : outputs_) {
    meta.output(f->arg_begin() + idx + 1) = true;
  }

  return meta;
}

template <typename R, typename... Args>
std::vector<std::set<long>> LoopSynth<R, Args...>::ids_to_coalesce() const
{
  auto ret = std::vector<std::set<long>>{};

  auto insert_equivs = [&] (auto& container) {
    for(auto pair : container) {
      auto key = pair.second;
      auto equiv = std::set<long>{};
      for(auto pair : container) {
        auto other_idx = pair.first;
        auto other_key = pair.second;
        if(key == other_key) {
          equiv.insert(other_idx);
        }
      }
      ret.push_back(equiv);
    }
  };

  insert_equivs(const_sizes_);
  insert_equivs(rt_size_offsets_);

  auto last = std::unique(ret.begin(), ret.end());
  ret.erase(last, ret.end());

  return ret;
}

template <typename R, typename... Args>
std::map<long, llvm::Value *> LoopSynth<R, Args...>::runtime_sizes(llvm::Function *f) const
{
  auto ret = std::map<long, llvm::Value *>{};

  auto i = 0l;
  for(auto const& group : coalesced_ids_) {
    auto rep_id = *group.begin();
    
    if(auto ct_it = const_sizes_.find(rep_id);
       ct_it != const_sizes_.end()) {
      auto i64_ty = llvm::IntegerType::get(f->getContext(), 64);
      auto size = llvm::ConstantInt::get(i64_ty, ct_it->second);
      ret.insert({i++, size});
    }

    if(auto rt_it = rt_size_offsets_.find(rep_id);
       rt_it != rt_size_offsets_.end()) {
      ret.insert({i++, f->arg_begin() + rt_it->second + 1});
    }
  }

  return ret;
}

template <typename R, typename... Args>
llvm::BasicBlock *LoopSynth<R, Args...>::create_error_block(
  llvm::Function *f, llvm::IRBuilder<>& b, llvm::BasicBlock *post) const
{
  auto err_bb = llvm::BasicBlock::Create(f->getContext(), "error", f);
  auto ip = b.saveIP();
  b.SetInsertPoint(err_bb);

  auto err_loc = f->arg_begin();
  auto err_code = b.getInt64(1); // TODO: make sure types match
  b.CreateStore(err_code, err_loc);
  b.CreateBr(post);
  
  b.restoreIP(ip);
  return err_bb;
}

}
