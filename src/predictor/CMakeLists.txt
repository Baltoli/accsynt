add_executable(predictor
  src/main.cpp)

target_link_libraries(predictor
  ${llvm_libs}
  props)

add_executable(predictor_unit
  test/main.cpp)

target_link_libraries(predictor_unit
  CONAN_PKG::Catch2)

target_include_directories(predictor_unit
  PRIVATE src)

add_test(NAME predictor_unit
         COMMAND $<TARGET_FILE:predictor_unit>)
