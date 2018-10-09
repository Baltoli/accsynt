#pragma once

#include <dlfcn.h>
#include <stdexcept>
#include <string>

namespace support {

class dynamic_library {
public:
  dynamic_library(const std::string& path);
  ~dynamic_library();

  template <typename Func>
  Func *symbol(const std::string& sym);

  void *raw_symbol(const std::string& sym);

private:
  void *lib_;
};

template <typename Func>
Func *dynamic_library::symbol(const std::string& sym)
{
  return reinterpret_cast<Func *>(raw_symbol(sym));
}

}
