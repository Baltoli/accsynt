project(libinterfind VERSION 0.1 LANGUAGES CXX)

add_library(interfind
  src/analysis.cpp
  src/common.cpp
  src/finder.cpp
  src/region.cpp
  src/use_def.cpp
  src/visitors.cpp
  src/json.cpp
)

target_link_libraries(interfind
  ${llvm_libs}
  AccsyntPasses_static
  stdc++fs
  support
  props
  CONAN_PKG::fmt
  CONAN_PKG::jsonformoderncpp
)

target_include_directories(interfind PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  PRIVATE src)

install(TARGETS interfind EXPORT InterFindConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT InterFindConfig DESTINATION share/InterFind/cmake)

add_executable(interfind_unit
  test/use_def.cpp
  test/main.cpp)

target_compile_options(interfind_unit
  PUBLIC -Wno-unused-value
)

target_link_libraries(interfind_unit
  interfind
  support
  CONAN_PKG::Catch2)

target_compile_options(interfind_unit
  PUBLIC -DRESOURCE_DIR="${CMAKE_BINARY_DIR}/inputs/")

add_test(
  NAME interfind_unit
  COMMAND $<TARGET_FILE:interfind_unit>)
