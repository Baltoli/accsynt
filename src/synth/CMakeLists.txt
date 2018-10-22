add_executable(synth
  src/dataflow_synth.cpp
  src/value_sampler.cpp
  src/blas_properties.cpp
  src/loops.cpp
  src/synthesizer.cpp
  src/blas_synth.cpp
  src/generator.cpp
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
