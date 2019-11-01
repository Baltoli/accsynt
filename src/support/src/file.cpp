#include <support/file.h>

#include <llvm/Support/FileSystem.h>

#include <sstream>
#include <system_error>

using namespace llvm;

namespace support {

std::unique_ptr<raw_fd_ostream> get_fd_ostream(std::string const& path)
{
  auto err = std::error_code{};
  auto ptr = std::make_unique<raw_fd_ostream>(path, err, sys::fs::FA_Write);

  if (err) {
    auto ss = std::stringstream{};
    ss << "Error opening file: " << err;
    throw std::runtime_error(ss.str());
  }

  return ptr;
}

} // namespace support
