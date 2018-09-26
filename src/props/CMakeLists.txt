project(libprops VERSION 0.1 LANGUAGES CXX)

add_library(props
  src/lib.cpp)

add_executable(testprops
  test/main.cpp)

target_link_libraries(testprops
  props
  CONAN_PKG::catch2
  CONAN_PKG::pegtl)
