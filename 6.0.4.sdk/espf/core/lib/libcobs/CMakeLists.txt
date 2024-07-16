project(COBS C)

add_library(COBS STATIC 
                 src/cobs.c 
)

target_include_directories(COBS PRIVATE ${ROOT_INCLUDES} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_compile_definitions(COBS PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(COBS PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(COBS PRIVATE ${ROOT_LINK_OPTIONS})
