#pragma once

#include "blas_properties.h"
#include "loops.h"
#include "synthesizer.h"

#include <props/props.h>

namespace synth {

struct blas_control_data {
  std::vector<llvm::Instruction *> seeds;
  std::vector<llvm::Instruction *> outputs;
  std::vector<llvm::BasicBlock *> data_blocks;
  llvm::BasicBlock *exit;
};

class blas_synth : public synthesizer {
public:
  blas_synth(props::property_set ps, call_wrapper& wrap);

  std::string name() const override;

protected:
  llvm::Function *candidate() override;

private:
  bool should_loop() const;
  void next_loop();

  blas_control_data build_control_flow(llvm::Function *fn, loop shape) const;
  blas_control_data build_control_flow(llvm::Function *fn) const;

  llvm::BasicBlock *build_loop(
      loop shape, llvm::BasicBlock* end_dst, 
      std::vector<llvm::Instruction *>& seeds,
      std::vector<llvm::Instruction *>& outputs,
      std::vector<llvm::BasicBlock *>& data_blocks,
      std::vector<llvm::Value *> iters) const;

  blas_properties blas_props_;
  blas_generator gen_;

  std::unordered_set<loop> loops_;
  decltype(loops_)::iterator current_loop_;
};

}
