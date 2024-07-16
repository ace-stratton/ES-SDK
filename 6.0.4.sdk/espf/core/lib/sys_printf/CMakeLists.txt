project(sys_printf C)

add_library(sys_printf STATIC
    "src/sys_printf.c"
)

target_include_directories(sys_printf PRIVATE ${ROOT_INCLUDES} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_compile_definitions(sys_printf PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(sys_printf PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(sys_printf PRIVATE ${ROOT_LINK_OPTIONS})
