add_library(coverage
  src/wrapper.cpp)

target_include_directories(coverage PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

target_link_libraries(coverage
  ${llvm_libs}
  support
  CONAN_PKG::fmt)

add_executable(input-cov
  src/options.cpp
  src/main.cpp)

target_link_libraries(input-cov
  coverage)

add_executable(coverage_unit
  test/wrapper.cpp
  test/main.cpp)

target_link_libraries(coverage_unit
  coverage
  CONAN_PKG::catch2)

target_include_directories(coverage_unit
  PRIVATE src)

install(TARGETS coverage EXPORT CoverageConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT CoverageConfig DESTINATION share/Coverage/cmake)

add_test(NAME coverage_unit
         COMMAND $<TARGET_FILE:coverage_unit>)
