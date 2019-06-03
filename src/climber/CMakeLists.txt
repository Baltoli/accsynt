add_executable(climber
  src/main.cpp
)

target_link_libraries(climber
  support
  props
  ${llvm_libs}
  CONAN_PKG::fmt
)

install(
  TARGETS climber
  DESTINATION ${CMAKE_INSTALL_BINDIR})
