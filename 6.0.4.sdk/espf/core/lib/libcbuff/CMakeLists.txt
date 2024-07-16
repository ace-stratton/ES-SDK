project(CBUFF C)

add_library(CBUFF STATIC 
                 libqueue.c 
)

target_include_directories(CBUFF PRIVATE ${ROOT_INCLUDES} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_compile_definitions(CBUFF PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(CBUFF PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(CBUFF PRIVATE ${ROOT_LINK_OPTIONS})
