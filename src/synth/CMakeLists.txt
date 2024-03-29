add_library(coresynth
  src/accessor_rules.cpp
  src/rules.cpp
  src/rule_registry.cpp
  src/dataflow_synth.cpp
  src/value_sampler.cpp
  src/blas_properties.cpp
  src/loops.cpp
  src/synthesizer.cpp
  src/blas_synth.cpp
  src/hill_synth.cpp
  src/rule_synth.cpp
  src/synth_options.cpp
  src/generator.cpp
  src/accessor.cpp
  src/compile_context.cpp
  src/compile_metadata.cpp
  src/fragment.cpp
  src/loop_fragment.cpp
  src/linear_fragment.cpp
  src/string_loop_fragment.cpp
  src/regular_loop_fragment.cpp
  src/loop_to_n_fragment.cpp
  src/affine_fragment.cpp
  src/data_loop_fragment.cpp
  src/fragment_registry.cpp
  src/generator_rules.cpp
  src/fragment_id.cpp)

add_executable(synth
  src/synth.cpp)

add_executable(fragment-demo
  src/fragment_demo.cpp)

add_executable(synth_unit
  test/regular_loop_fragment.cpp
  test/linear_fragment.cpp
  test/fragment_id.cpp
  test/main.cpp)

target_link_libraries(coresynth
  ${llvm_libs}
  CONAN_PKG::fmt
  CONAN_PKG::value-ptr
  support
  predict
  props)

target_link_libraries(synth
  coresynth)

target_link_libraries(fragment-demo
  coresynth)

target_link_libraries(synth_unit
  coresynth
  CONAN_PKG::catch2)

target_link_filesystem(synth_unit)

target_include_directories(synth_unit
  PRIVATE src)

install(
  TARGETS synth
  DESTINATION ${CMAKE_INSTALL_BINDIR})

add_test(NAME synth_unit
         COMMAND $<TARGET_FILE:synth_unit>)

add_subdirectory(test/inputs)
