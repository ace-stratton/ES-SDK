project(nxp-tja11xx C)

add_library(nxp-tja11xx STATIC
    "src/nxp-tja11xx.c"
)

list(
    APPEND ESPSI_DRV_INCLUDES
    "${PROJECT_SOURCE_DIR}/inc"
    )

target_include_directories(nxp-tja11xx PUBLIC ${ROOT_INCLUDES} PUBLIC ${ESPSI_DRV_INCLUDES})
target_compile_definitions(nxp-tja11xx PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(nxp-tja11xx PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(nxp-tja11xx PRIVATE ${ROOT_LINK_OPTIONS})
