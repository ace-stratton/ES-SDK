project(cobs_inplace C)

add_library(cobs_inplace STATIC
    "src/cobs_inplace.c"
)

target_include_directories(cobs_inplace PRIVATE ${ROOT_INCLUDES} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_compile_definitions(cobs_inplace PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(cobs_inplace PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(cobs_inplace PRIVATE ${ROOT_LINK_OPTIONS})
