project(libinterfind VERSION 0.1 LANGUAGES CXX)

add_library(interfind
  src/analysis.cpp
  src/finder.cpp
)

target_link_libraries(interfind
  ${llvm_libs}
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
  test/main.cpp)

target_link_libraries(interfind_unit
  interfind
  CONAN_PKG::catch2)

add_test(
  NAME interfind_unit
  COMMAND $<TARGET_FILE:interfind_unit>)
