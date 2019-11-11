add_library(predict
  src/prepare_data.cpp
  src/harness.cpp
  src/generated.c)

add_executable(predictor
  src/main.cpp)

target_link_libraries(predict
  ${llvm_libs}
  props
  CONAN_PKG::fmt)

target_link_filesystem(predict)

target_include_directories(predict PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

install(TARGETS predict EXPORT PredictConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT PredictConfig DESTINATION share/Predict/cmake)

target_link_libraries(predictor
  predict)

add_executable(predictor_unit
  test/prepare_data.cpp
  test/main.cpp)

target_link_libraries(predictor_unit
  predict
  CONAN_PKG::Catch2)

target_include_directories(predictor_unit
  PRIVATE src)

add_test(NAME predictor_unit
         COMMAND $<TARGET_FILE:predictor_unit>)
