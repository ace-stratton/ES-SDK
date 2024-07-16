project(assertions C)

add_library(assertions STATIC
    "src/assertions.c"
)

target_include_directories(assertions PRIVATE ${ROOT_INCLUDES} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_compile_definitions(assertions PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(assertions PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(assertions PRIVATE ${ROOT_LINK_OPTIONS})
