#include <support/dynamic_library.h>

namespace support {

dynamic_library::dynamic_library(const std::string& path)
{
  lib_ = dlopen(path.c_str(), RTLD_NOW);
  if(!lib_) {
    throw std::runtime_error(dlerror());
  }
}

dynamic_library::~dynamic_library()
{
  if(lib_) {
    dlclose(lib_);
  }
}

void *dynamic_library::raw_symbol(const std::string& sym)
{
  dlerror();
  void *dy_sym = dlsym(lib_, sym.c_str());
  char *err = dlerror();
  if(err) {
    throw std::runtime_error(err);
  }

  return dy_sym;
}

}
