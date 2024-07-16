project(datetime C)

add_library(datetime STATIC
    "src/datetime.c"
)

target_include_directories(datetime PRIVATE ${ROOT_INCLUDES} PUBLIC inc)
target_compile_definitions(datetime PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(datetime PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(datetime PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(datetime assertions)
