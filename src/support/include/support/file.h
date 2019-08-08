#pragma once

#include <llvm/Support/raw_ostream.h>

#include <memory>
#include <string>

namespace support {

std::unique_ptr<llvm::raw_fd_ostream> get_fd_ostream(std::string const& path);

} // namespace support
