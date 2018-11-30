project(libsupport VERSION 0.1 LANGUAGES CXX)

add_library(support
  src/float_compare.cpp
  src/random.cpp
  src/llvm_values.cpp
  src/llvm_cloning.cpp
  src/load_module.cpp
  src/dynamic_library.cpp
  src/thread_context.cpp)

target_link_libraries(support
  ${llvm_libs}
  dl)

target_include_directories(support PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

install(TARGETS support EXPORT SupportConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT SupportConfig DESTINATION share/Support/cmake)

add_executable(support_unit
  test/cartesian_product.cpp
  test/floats.cpp
  test/traits.cpp
  test/load_module.cpp
  test/main.cpp)

target_link_libraries(support_unit
  support
  CONAN_PKG::catch2)

target_compile_options(support_unit
  PUBLIC -DRESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test/inputs")

add_test(NAME support_unit
         COMMAND $<TARGET_FILE:support_unit>)
