add_library(coresynth
  src/indexing.cpp
  src/dataflow_synth.cpp
  src/value_sampler.cpp
  src/blas_properties.cpp
  src/loops.cpp
  src/synthesizer.cpp
  src/blas_synth.cpp
  src/generator.cpp
  src/call_builder.cpp
  src/call_wrapper.cpp)

add_executable(synth
  src/synth.cpp)

target_link_libraries(coresynth
  ${llvm_libs}
  CONAN_PKG::fmt
  CONAN_PKG::spdlog
  support
  props)

target_link_libraries(synth
  coresynth)

install(
  TARGETS synth
  DESTINATION ${CMAKE_INSTALL_BINDIR})
