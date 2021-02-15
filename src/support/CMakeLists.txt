project(libsupport VERSION 0.1 LANGUAGES CXX)

add_library(support
  src/argument_generator.cpp
  src/call_builder.cpp
  src/call_wrapper.cpp
  src/choose.cpp
  src/dynamic_library.cpp
  src/file.cpp
  src/float_compare.cpp
  src/hash.cpp
  src/input.cpp
  src/instr_count.cpp
  src/llvm_cloning.cpp
  src/llvm_types.cpp
  src/llvm_utils.cpp
  src/llvm_values.cpp
  src/load_module.cpp
  src/options.cpp
  src/random.cpp
  src/string.cpp
  src/thread_context.cpp
)

target_link_libraries(support
  ${llvm_libs}
  props
  CONAN_PKG::readline
  )

target_link_filesystem(support)

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
  test/argument_generator.cpp
  test/bit_cast.cpp
  test/call_builder.cpp
  test/cartesian_product.cpp
  test/choose.cpp
  test/floats.cpp
  test/hash.cpp
  test/instr_count.cpp
  test/llvm_types.cpp
  test/llvm_values.cpp
  test/load_module.cpp
  test/random.cpp
  test/string.cpp
  test/timeout.cpp
  test/traits.cpp
  test/utility.cpp
  test/main.cpp)

target_link_libraries(support_unit
  support
  ${llvm_libs}
  CONAN_PKG::fmt
  CONAN_PKG::catch2)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/test/inputs/deps.ll"
  "${CMAKE_CURRENT_BINARY_DIR}/inputs/deps.ll"
  COPYONLY
)

target_compile_options(support_unit
  PUBLIC -DRESOURCE_DIR="${CMAKE_CURRENT_BINARY_DIR}/inputs/")

add_test(NAME support_unit
         COMMAND $<TARGET_FILE:support_unit>)
