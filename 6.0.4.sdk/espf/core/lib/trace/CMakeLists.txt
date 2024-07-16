project(libtrace C)

add_library(libtrace STATIC
    "src/trace.c"
)

target_include_directories(libtrace PRIVATE ${ROOT_INCLUDES} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_compile_definitions(libtrace PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(libtrace PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(libtrace PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(libtrace PUBLIC cbuf PRIVATE cobs_inplace irq datetime crc sys_printf)
