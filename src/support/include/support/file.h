#pragma once

#include <llvm/Support/raw_ostream.h>

#include <memory>
#include <string>

namespace support {

std::unique_ptr<llvm::raw_fd_ostream> get_fd_ostream(std::string const& path);

template <typename Printer, typename OStr>
void to_file_or_default(std::string const& path, OStr& os, Printer&& p)
{
  if (path == "-") {
    std::forward<Printer>(p)(os);
  } else {
    std::forward<Printer>(p)(*get_fd_ostream(path));
  }
}

template <typename Printer>
void to_file_or_default(std::string const& path, Printer&& p)
{
  to_file_or_default(path, llvm::outs(), std::forward<Printer>(p));
}

} // namespace support
