project(file_stack C)

add_library(file_stack STATIC
    "src/libfile_stack.c"
)

target_include_directories(file_stack PRIVATE ${ROOT_INCLUDES} PUBLIC inc)
target_compile_definitions(file_stack PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(file_stack PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(file_stack PRIVATE ${ROOT_LINK_OPTIONS})
