project(libprops VERSION 0.1 LANGUAGES CXX)

add_library(props
  src/props.cpp)

target_link_libraries(props
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
  test/parsing.cpp)

target_link_libraries(props_unit
  props
  CONAN_PKG::catch2)

add_test(NAME props_unit
         COMMAND $<TARGET_FILE:props_unit>)
