add_library(replace
  src/lib.cpp)

target_include_directories(replace PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

target_link_libraries(replace
  CONAN_PKG::fmt
  CONAN_PKG::nlohmann_json
  ${llvm_libs}
  support)

add_executable(apply-match
  src/main.cpp)

target_link_libraries(apply-match
  replace)

add_executable(replace_unit
  test/json.cpp
  test/main.cpp)

target_link_libraries(replace_unit
  replace
  CONAN_PKG::catch2)

target_include_directories(replace_unit
  PRIVATE src)

install(TARGETS replace EXPORT CoverageConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT CoverageConfig DESTINATION share/Coverage/cmake)

add_test(NAME replace_unit
         COMMAND $<TARGET_FILE:replace_unit>)
