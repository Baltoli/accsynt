list(APPEND pass_sources
  src/fix_floats.cpp
  src/clean.cpp
  src/namer.cpp
  src/to_idl.cpp
  src/translate.cpp
  src/deduplicate.cpp
  src/cyclo.cpp
  src/opcode.cpp)

add_library(AccsyntPasses SHARED ${pass_sources})
add_library(AccsyntPasses_static STATIC ${pass_sources})

target_link_libraries(AccsyntPasses
  CONAN_PKG::fmt)

target_link_libraries(AccsyntPasses_static
  CONAN_PKG::fmt)

target_include_directories(AccsyntPasses PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

target_include_directories(AccsyntPasses_static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

install(TARGETS AccsyntPasses EXPORT AccsyntPassesConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT AccsyntPassesConfig DESTINATION share/AccsyntPasses/cmake)
export(TARGETS AccsyntPasses FILE AccsyntPassesConfig.cmake)

install(TARGETS AccsyntPasses_static EXPORT AccsyntPassesStaticConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT AccsyntPassesStaticConfig DESTINATION share/AccsyntPassesStatic/cmake)
export(TARGETS AccsyntPasses_static FILE AccsyntPassesStaticConfig.cmake)

set_target_properties(AccsyntPasses PROPERTIES
  COMPILE_FLAGS "-fno-rtti"
)

set_target_properties(AccsyntPasses_static PROPERTIES
  COMPILE_FLAGS "-fno-rtti"
)
