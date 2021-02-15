add_library(io
  src/lib.cpp)

target_include_directories(io PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

target_link_libraries(io
  ${llvm_libs}
  support
  CONAN_PKG::fmt)

add_executable(io-dump
  src/options.cpp
  src/main.cpp)

target_link_libraries(io-dump
  io)

add_executable(io_unit
  test/main.cpp)

target_link_libraries(io_unit
  io
  CONAN_PKG::catch2)

target_include_directories(io_unit
  PRIVATE src)

install(TARGETS io EXPORT CoverageConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT CoverageConfig DESTINATION share/Coverage/cmake)

add_test(NAME io_unit
         COMMAND $<TARGET_FILE:io_unit>)
