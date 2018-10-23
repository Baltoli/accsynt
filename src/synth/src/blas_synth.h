#pragma once

#include "blas_properties.h"
#include "loops.h"
#include "synthesizer.h"

#include <props/props.h>

namespace synth {

struct blas_control_data {
  std::vector<llvm::Instruction *> seeds;
  std::vector<llvm::Instruction *> outputs;
  llvm::BasicBlock *exit;
};

class blas_synth : public synthesizer {
public:
  blas_synth(props::property_set ps, call_wrapper& wrap);

  std::string name() const override;

private:
  llvm::Function *candidate() override;
  void next_loop();

  blas_control_data build_control_flow(loop shape, llvm::Function *fn) const;

  llvm::BasicBlock *build_loop(
      loop shape, llvm::BasicBlock* end_dst, 
      std::vector<llvm::Instruction *>& outputs,
      std::vector<llvm::Instruction *>& seeds) const;

  blas_properties blas_props_;
  blas_generator gen_;

  std::unordered_set<loop> loops_;
  decltype(loops_)::iterator current_loop_;
};

}
