#pragma once

#include "call_wrapper.h"
#include "generator.h"

#include <props/props.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>

#include <string>
#include <vector>

namespace synth {

class synthesizer {
public:
  synthesizer(props::property_set ps, call_wrapper& wrap);

  virtual std::string name() const = 0;
  virtual llvm::Function* generate() = 0;

protected:
  void make_examples(generator& gen, size_t n);

  props::property_set properties_;
  call_wrapper& reference_;

  std::vector<std::pair<call_builder, output_example>> examples_;

private:
};

class null_synth : public synthesizer {
public:
  using synthesizer::synthesizer;

  std::string name() const override;
  llvm::Function *generate() override;
};

class blas_synth : public synthesizer {
public:
  blas_synth(props::property_set ps, call_wrapper& wrap);

  std::string name() const override;
  llvm::Function *generate() override;

private:
  llvm::Function *candidate();
  bool satisfies_examples(llvm::Function *cand) const;

  blas_generator gen_;
  llvm::Module mod_;
};

}
