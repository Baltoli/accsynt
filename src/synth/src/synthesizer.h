#pragma once

#include "generator.h"

#include <support/call_wrapper.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>

#include <string>
#include <vector>

namespace synth {

class synthesizer {
public:
  synthesizer(props::property_set ps, support::call_wrapper& wrap);

  virtual std::string name() const = 0;
  virtual llvm::Function* generate();

protected:
  void make_examples(generator& gen, size_t n);
  bool satisfies_examples(llvm::Function* cand) const;

  virtual llvm::Function* candidate() = 0;

  llvm::Function* create_stub();

  props::property_set properties_;
  support::call_wrapper& reference_;

  std::vector<std::pair<support::call_builder, support::output_example>>
      examples_;
  size_t attempts_ = 128;

  llvm::Module mod_;

private:
  llvm::Function* debug_generate();
};

class null_synth : public synthesizer {
public:
  using synthesizer::synthesizer;

  std::string name() const override;
  llvm::Function* generate() override;
};
}
