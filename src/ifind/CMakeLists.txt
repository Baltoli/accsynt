add_executable(ifind
  src/main.cpp
)

target_link_libraries(ifind
  interfind
  ${llvm_libs}
  CONAN_PKG::fmt
  CONAN_PKG::jsonformoderncpp
)

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  target_link_libraries(ifind stdc++fs)
endif()

install(
  TARGETS ifind
  DESTINATION ${CMAKE_INSTALL_BINDIR})

add_subdirectory(test/inputs)
