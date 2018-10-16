#pragma once

#include "call_wrapper.h"
#include "generator.h"

#include <props/props.h>

#include <llvm/IR/Function.h>

#include <string>
#include <vector>

namespace synth {

class synthesizer {
public:
  synthesizer(props::property_set ps, call_wrapper& wrap);

  virtual std::string name() const = 0;
  virtual llvm::Function* generate() const = 0;

protected:
  props::property_set properties_;
  call_wrapper& reference_;

private:
};

class null_synth : public synthesizer {
public:
  using synthesizer::synthesizer;

  std::string name() const override;
  llvm::Function *generate() const override;
};

class blas_synth : public synthesizer {
public:
  blas_synth(props::property_set ps, call_wrapper& wrap);

  std::string name() const override;
  llvm::Function *generate() const override;

private:
  blas_generator generator_;
  std::vector<std::pair<call_builder, output_example>> examples_;
};

}
