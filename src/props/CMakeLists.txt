project(libprops VERSION 0.1 LANGUAGES CXX)

add_library(props
  src/parsing.cpp
  src/printing.cpp
  src/llvm_function.cpp
  src/comparisons.cpp
  src/props.cpp)

target_link_libraries(props
  ${llvm_libs}
  support
  CONAN_PKG::fmt
  CONAN_PKG::pegtl)

target_include_directories(props PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

install(TARGETS props EXPORT PropsConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT PropsConfig DESTINATION share/Props/cmake)

add_executable(props_unit
  test/main.cpp
  test/llvm.cpp
  test/usage.cpp
  test/printing.cpp
  test/parsing.cpp)

target_link_libraries(props_unit
  props
  stdc++fs
  CONAN_PKG::fmt
  CONAN_PKG::catch2)

target_compile_options(props_unit
  PUBLIC -DRESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test/inputs")

add_test(NAME props_unit
         COMMAND $<TARGET_FILE:props_unit>)
