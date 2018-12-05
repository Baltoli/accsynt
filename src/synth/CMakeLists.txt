add_library(coresynth
  src/rules.cpp
  src/rule_registry.cpp
  src/dataflow_synth.cpp
  src/value_sampler.cpp
  src/blas_properties.cpp
  src/loops.cpp
  src/synthesizer.cpp
  src/blas_synth.cpp
  src/generator.cpp
  src/call_builder.cpp
  src/call_wrapper.cpp
  src/fragment.cpp
  src/fragment_registry.cpp
  src/regular_loop_fragment.cpp)

add_executable(synth
  src/synth.cpp)

add_executable(fragment-demo
  src/fragment_demo.cpp)

add_executable(synth_unit
  test/main.cpp)

target_link_libraries(coresynth
  ${llvm_libs}
  CONAN_PKG::fmt
  CONAN_PKG::spdlog
  support
  props)

target_link_libraries(synth
  coresynth)

target_link_libraries(fragment-demo
  coresynth)

target_link_libraries(synth_unit
  coresynth
  CONAN_PKG::catch2)

target_include_directories(synth_unit
  PRIVATE src)

install(
  TARGETS synth
  DESTINATION ${CMAKE_INSTALL_BINDIR})

add_test(NAME synth_unit
         COMMAND $<TARGET_FILE:synth_unit>)
