add_executable(ifind
  src/main.cpp
)

target_link_libraries(ifind
  interfind
  ${llvm_libs}
  CONAN_PKG::fmt
  CONAN_PKG::jsonformoderncpp
)

target_link_filesystem(ifind)

install(
  TARGETS ifind
  DESTINATION ${CMAKE_INSTALL_BINDIR})

add_subdirectory(test/inputs)
