add_library(hsm STATIC
    "src/libhsm.c"
)

target_include_directories(hsm PUBLIC ${ROOT_INCLUDES} PUBLIC inc)
target_compile_definitions(hsm PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(hsm PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(hsm PRIVATE ${ROOT_LINK_OPTIONS})
