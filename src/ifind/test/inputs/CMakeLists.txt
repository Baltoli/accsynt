set(CC_BC "${LLVM_TOOLS_BINARY_DIR}/clang")

function(add_bc_example name)
  SET(OUTPUT_F "${CMAKE_BINARY_DIR}/inputs/${name}.bc")

  add_custom_command(
    OUTPUT "${OUTPUT_F}"
    COMMAND ${CC_BC} -c -emit-llvm ${CMAKE_CURRENT_SOURCE_DIR}/${name}.c -o ${OUTPUT_F}
    MAIN_DEPENDENCY "${name}.c"
  )

  add_custom_target("${name}bc" ALL DEPENDS "${OUTPUT_F}")
endfunction(add_bc_example)

function(add_json_example name)
  SET(OUTPUT_F "${CMAKE_BINARY_DIR}/inputs/${name}.json")

  add_custom_command(
    OUTPUT "${OUTPUT_F}"
    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/${name}.json" "${OUTPUT_F}"
    MAIN_DEPENDENCY "${name}.json"
  )

  add_custom_target("${name}json" ALL DEPENDS "${OUTPUT_F}")
endfunction(add_json_example)

add_bc_example(empty)

add_json_example(empty)
