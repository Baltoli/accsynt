#pragma once

#include <props/props.h>

#include <llvm/IR/Function.h>

#include <string>

namespace synth {

class synthesizer {
public:
  synthesizer(props::property_set ps, llvm::Function *fn);

  virtual std::string name() const = 0;

protected:
  props::property_set properties_;
  llvm::Function *reference_;

private:
};

class null_synth : public synthesizer {
public:
  using synthesizer::synthesizer;

  std::string name() const override;
};

}
