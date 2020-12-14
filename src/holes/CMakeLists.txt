project(libholes VERSION 0.1 LANGUAGES CXX)

add_library(holes
  src/holes.cpp)

target_link_libraries(holes
  support
  ${llvm_libs})

target_include_directories(holes PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

install(TARGETS holes EXPORT HolesConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT HolesConfig DESTINATION share/Holes/cmake)

add_executable(holes_unit
  test/main.cpp)

target_link_libraries(holes_unit
  holes
  ${llvm_libs}
  CONAN_PKG::fmt
  CONAN_PKG::catch2)

add_test(NAME holes_unit
         COMMAND $<TARGET_FILE:holes_unit>)
