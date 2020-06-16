#include "rules.h"

#include <support/assert.h>

namespace presyn {

void first_of_type::match(
    filler const& fill, llvm::CallInst* hole,
    std::vector<llvm::Value*> const& choices,
    std::vector<llvm::Value*>& ret) const
{
  assumes(!choices.empty(), "Must have some choices");

  if (fill.has_unknown_type(hole)) {
    ret.push_back(choices[0]);
  } else {
    for (auto c : choices) {
      if (c->getType() == hole->getType()) {
        ret.push_back(c);
        break;
      }
    }
  }
}

} // namespace presyn
