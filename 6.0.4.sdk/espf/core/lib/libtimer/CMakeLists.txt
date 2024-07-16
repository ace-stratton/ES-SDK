project(timer C)

add_library(timer STATIC
    "src/timer.c"
)

target_include_directories(timer PUBLIC inc PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(timer PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(timer PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(timer PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(timer assertions)
