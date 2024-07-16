project(cbuf C)

add_library(cbuf STATIC
    "src/cbuf.c"
)

target_include_directories(cbuf PRIVATE ${ROOT_INCLUDES} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_compile_definitions(cbuf PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(cbuf PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(cbuf PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(cbuf assertions)
