#pragma once

#include <cstddef>

namespace llvm {
class Function;
}

namespace support {

size_t instr_count(llvm::Function const&);

} // namespace support
