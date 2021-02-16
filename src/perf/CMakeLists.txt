add_library(perf
  src/lib.cpp)

target_include_directories(perf PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

target_link_libraries(perf
  ${llvm_libs}
  support
  CONAN_PKG::fmt)

add_executable(perf-model
  src/options.cpp
  src/main.cpp)

target_link_libraries(perf-model
  perf)

add_executable(perf_unit
  test/main.cpp)

target_link_libraries(perf_unit
  perf
  CONAN_PKG::catch2)

target_include_directories(perf_unit
  PRIVATE src)

install(TARGETS perf EXPORT CoverageConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT CoverageConfig DESTINATION share/Coverage/cmake)

add_test(NAME perf_unit
         COMMAND $<TARGET_FILE:perf_unit>)
