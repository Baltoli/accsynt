#include <support/instr_count.h>

#include <llvm/IR/Function.h>

using namespace llvm;

namespace support {

size_t instr_count(Function const& fn)
{
  auto count = size_t(0);

  for (auto const& bb : fn) {
    for (auto const& inst : bb) {
      count++;
    }
  }

  return count;
}

} // namespace support
