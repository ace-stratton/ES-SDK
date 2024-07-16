project(ethernetif C)

add_library(ethernetif STATIC
    "src/ethernetif.c"
)

list(
    APPEND ESPSI_DRV_INCLUDES
    "${PROJECT_SOURCE_DIR}/inc"
    )

target_include_directories(ethernetif PUBLIC ${ROOT_INCLUDES} PUBLIC ${ESPSI_DRV_INCLUDES})
target_compile_definitions(ethernetif PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(ethernetif PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(ethernetif PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(ethernetif PUBLIC nxp-tja11xx lwIP)