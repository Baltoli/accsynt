add_executable(detect
  src/detect.cpp)

add_executable(convert
  src/convert.cpp)

target_link_libraries(convert
  CONAN_PKG::fmt
  ${llvm_libs}
  AccsyntPasses)

target_link_libraries(detect
  CONAN_PKG::fmt
  -Wl,--whole-archive ${llvm_libs} -Wl,--no-whole-archive)
