add_executable(ifind
  src/main.cpp
)

target_link_libraries(ifind
  interfind
  ${llvm_libs}
  stdc++fs
  CONAN_PKG::fmt
  CONAN_PKG::jsonformoderncpp
)

install(
  TARGETS ifind
  DESTINATION ${CMAKE_INSTALL_BINDIR})

add_subdirectory(test/inputs)
