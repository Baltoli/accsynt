#include <support/options.h>

#include <llvm/Support/CommandLine.h>

#include <array>

using namespace llvm;

namespace support {

void hide_llvm_options()
{
  static std::array hidden_options
      = {"color",
         "enable-cse-in-irtranslator",
         "enable-cse-in-legalizer",
         "x86-align-branch",
         "x86-align-branch-boundary",
         "x86-branches-within-32B-boundaries"};

  auto& map = cl::getRegisteredOptions();

  for (auto const& name : hidden_options) {
    auto it = map.find(name);
    if (it != map.end()) {
      it->second->setHiddenFlag(cl::Hidden);
    }
  }
}

} // namespace support
