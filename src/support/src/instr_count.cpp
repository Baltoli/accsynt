#include <support/instr_count.h>

#include <llvm/IR/Function.h>

#include <numeric>

using namespace llvm;

namespace support {

size_t instr_count(Function const& fn)
{
  return std::accumulate(fn.begin(), fn.end(), 0, [](auto a, auto const& bb) {
    return a + std::distance(bb.begin(), bb.end());
  });
}

} // namespace support
