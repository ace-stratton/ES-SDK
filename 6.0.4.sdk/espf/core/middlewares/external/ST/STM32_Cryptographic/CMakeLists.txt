project(stm32_crypto C)
set(make_target "stm32_crypto")

list(APPEND module_includes
    "${PROJECT_SOURCE_DIR}/include"
)

list(APPEND stm32_crypto_sources
    "${PROJECT_SOURCE_DIR}/src/dummy.c"
)

add_library(${make_target} STATIC
    ${stm32_crypto_sources}
)

#remove -pedantic compiler option for micropython, there are too many warnings from the implementation of micropython itself.
list(APPEND stm32_crypto_compile_options ${ROOT_COMPILE_OPTIONS})
list(REMOVE_ITEM stm32_crypto_compile_options "-pedantic")


target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${stm32_crypto_compile_options})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} PUBLIC "${PROJECT_SOURCE_DIR}/lib/libSTM32Cryptographic_CM7.a")
