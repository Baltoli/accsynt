add_library(corepredict
  src/prepare_data.cpp)

add_executable(predictor
  src/main.cpp)

target_link_libraries(corepredict
  ${llvm_libs}
  props
  CONAN_PKG::fmt)

target_link_libraries(predictor
  corepredict)

add_executable(predictor_unit
  test/prepare_data.cpp
  test/main.cpp)

target_link_libraries(predictor_unit
  corepredict
  CONAN_PKG::Catch2)

target_include_directories(predictor_unit
  PRIVATE src)

add_test(NAME predictor_unit
         COMMAND $<TARGET_FILE:predictor_unit>)

add_subdirectory(model)
