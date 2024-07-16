project(libcsq_algo C)

add_library(libcsq_algo STATIC
    "src/csq_algo.c"
)

target_include_directories(libcsq_algo PRIVATE ${ROOT_INCLUDES} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_compile_definitions(libcsq_algo PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(libcsq_algo PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(libcsq_algo PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(libcsq_algo assertions)
