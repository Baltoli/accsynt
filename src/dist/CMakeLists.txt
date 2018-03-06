project(libdist VERSION 0.1 LANGUAGES CXX)

add_library(dist
  src/contexts.cpp
  src/types.cpp
  src/utils.cpp
  src/synth_metadata.cpp
  src/synth_op.cpp
)

target_include_directories(dist PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

target_link_libraries(dist
  ${llvm_libs}
)

install(TARGETS dist EXPORT DistConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT DistConfig DESTINATION share/Dist/cmake)

export(TARGETS dist FILE DistConfig.cmake)

add_executable(test_dist
  test/test_dist.cpp
)

add_executable(unit_tests
  test/unit/main.cpp
  test/unit/function_call.cpp
  test/unit/linear_synth.cpp
  test/unit/permute.cpp
  test/unit/load_module.cpp
  test/unit/types.cpp
)

target_link_libraries(test_dist dist)
target_link_libraries(unit_tests dist)
add_test(unit_tests test_dist)
