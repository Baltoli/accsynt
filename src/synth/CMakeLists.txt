add_executable(synth
  src/call_builder.cpp
  src/call_wrapper.cpp
  src/synth.cpp)

target_link_libraries(synth
  ${llvm_libs}
  CONAN_PKG::fmt
  CONAN_PKG::spdlog
  support
  props)

install(
  TARGETS synth
  DESTINATION ${CMAKE_INSTALL_BINDIR})
