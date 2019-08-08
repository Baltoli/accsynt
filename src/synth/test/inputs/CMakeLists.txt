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

  install(
    TARGETS ${name}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/accsynt
  )

  install(
    FILES "${CMAKE_BINARY_DIR}/inputs/${name}.props"
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/accsynt
  )
endfunction(add_test_shared_library)

# Misc Inputs
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
add_test_shared_library(safe_string_copy)
add_test_shared_library(saxpy)
add_test_shared_library(spmv)
add_test_shared_library(store)
add_test_shared_library(strlen)
add_test_shared_library(v_add)
add_test_shared_library(v_copy)
add_test_shared_library(vec2sum)
add_test_shared_library(v_sum)
add_test_shared_library(v_sum_two)

# Mathfu
add_test_shared_library(mf_subeq)
add_test_shared_library(mf_addeq)
add_test_shared_library(mf_muleq)
add_test_shared_library(mf_diveq)
add_test_shared_library(mf_subeq_sca)
add_test_shared_library(mf_addeq_sca)
add_test_shared_library(mf_muleq_sca)
add_test_shared_library(mf_diveq_sca)
add_test_shared_library(mf_negate)
add_test_shared_library(mf_clamp)
add_test_shared_library(mf_lerp)
add_test_shared_library(mf_length)
add_test_shared_library(mf_length_sq)

# string.h
add_test_shared_library(str_strlen)
add_test_shared_library(str_memcpy)
add_test_shared_library(str_memmove)
add_test_shared_library(str_memset)

# SafeStr

# BLAS
add_test_shared_library(blas_asum)
add_test_shared_library(blas_dot)
add_test_shared_library(blas_gemv)
add_test_shared_library(blas_ger)

# GLM
add_test_shared_library(glm_length)
add_test_shared_library(glm_abs)
add_test_shared_library(glm_dot)
add_test_shared_library(glm_sqrt)
add_test_shared_library(glm_invsqrt)
add_test_shared_library(glm_fma)

# Ti DSP
add_test_shared_library(ti_dotp)

# ARM DSP
add_test_shared_library(arm_vdot)
