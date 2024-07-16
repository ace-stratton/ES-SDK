project(slipif C)

add_library(slipif STATIC
    "src/sio.c"
    "src/slipif.c"
)

target_include_directories(slipif PUBLIC ${ROOT_INCLUDES})
target_compile_definitions(slipif PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(slipif PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(slipif PRIVATE ${ROOT_LINK_OPTIONS})

target_link_libraries(slipif PUBLIC lwIP CBUFF libtrace assertions)