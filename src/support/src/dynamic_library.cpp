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

}
