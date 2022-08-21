if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64")
    set(TEST_CC_FLAGS -static -O3 -mavx512f)
else()
    set(TEST_CC_FLAGS -static -O3)
endif()

set(tests
    just_include_header
    array_reduce_and
    #array_sum array_or array_xor
    #array_find_max array_find_min array_find_first
    #array_mul_pair_sum array_product
    #arrays_and #or xor
    #arrays_add arrays_mul
    #arrays_msum
)

#set(atomic4_cc_flags -std=c11 -latomic)
#set(test8_cc_flags ${CMAKE_CURRENT_SOURCE_DIR}/test8.S)

foreach(test_name IN LISTS tests)

    set(test_path ${CMAKE_CURRENT_SOURCE_DIR}/${test_name}.cpp)

    if(DEFINED ${test_name}_cc_flags)
        set(test_cc_flags "${${test_name}_cc_flags}")
    endif()

    add_executable(${test_name} ${test_path})
    target_compile_options(${test_name} PRIVATE ${TEST_CC_FLAGS} ${test_cc_flags})
    #add_dependencies(${test_name} generate) target "generate" calls generating scripts

    add_test(NAME ${test_name} COMMAND ${FSIM} ${test_name})

endforeach()

