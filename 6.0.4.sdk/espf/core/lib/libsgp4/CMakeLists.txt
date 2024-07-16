project(SGP4 C)

add_library(SGP4 STATIC 
    source/sgp4_other.c 
    source/sgp4_propagator.c
    source/sgp4_two_line_element.c
)

list(
    APPEND module_includes
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/config
)

target_include_directories(SGP4 PUBLIC ${module_includes} PUBLIC ${ROOT_INCLUDES})
target_compile_definitions(SGP4 PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(SGP4 PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(SGP4 PRIVATE ${ROOT_LINK_OPTIONS})
