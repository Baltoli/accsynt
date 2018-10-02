add_library(AccsyntPasses SHARED
  src/clean.cpp
  src/namer.cpp
  src/to_idl.cpp
  src/translate.cpp
  src/opcode.cpp)

target_link_libraries(AccsyntPasses
  CONAN_PKG::fmt)

target_include_directories(AccsyntPasses PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

install(TARGETS AccsyntPasses EXPORT AccsyntPassesConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT AccsyntPassesConfig DESTINATION share/AccsyntPassesConfig/cmake)

export(TARGETS AccsyntPasses FILE AccsyntPassesConfig.cmake)

set_target_properties(AccsyntPasses PROPERTIES
  COMPILE_FLAGS "-fno-rtti"
)
