function(add_test_shared_library name)
  add_library(${name} MODULE "${name}.c")

  set_target_properties(${name}
    PROPERTIES 
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/inputs"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/inputs"
  )

  configure_file(
    "${name}.props" 
    "${CMAKE_BINARY_DIR}/inputs/${name}.props" 
    COPYONLY)
endfunction(add_test_shared_library)

add_test_shared_library(add)
add_test_shared_library(asum)
add_test_shared_library(bias)
add_test_shared_library(det)
add_test_shared_library(dot)
add_test_shared_library(fixed_dot)
add_test_shared_library(gemv)
add_test_shared_library(gemv_full)
add_test_shared_library(ger)
add_test_shared_library(mag)
add_test_shared_library(memcpy)
add_test_shared_library(memmove)
add_test_shared_library(memset)
add_test_shared_library(normalise)
add_test_shared_library(offset_sum)
add_test_shared_library(relu)
add_test_shared_library(relu-over)
add_test_shared_library(saxpy)
add_test_shared_library(spmv)
add_test_shared_library(store)
add_test_shared_library(v_add)
add_test_shared_library(v_copy)
add_test_shared_library(vec2sum)
add_test_shared_library(v_sum)
add_test_shared_library(v_sum_two)

add_test_shared_library(strlen)
