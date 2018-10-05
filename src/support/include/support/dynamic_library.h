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
  Func *symbol(const std::string& symbol);

private:
  void *lib_;
};

template <typename Func>
Func *dynamic_library::symbol(const std::string& symbol)
{
  dlerror();
  void *sym = dlsym(lib_, symbol.c_str());
  char *err = dlerror();
  if(err) {
    throw std::runtime_error(err);
  }

  return reinterpret_cast<Func *>(sym);
}

}
