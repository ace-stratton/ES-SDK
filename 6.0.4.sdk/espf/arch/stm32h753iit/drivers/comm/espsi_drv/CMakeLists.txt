add_library(espsi_drv STATIC
    "src/esps_drv.c"
    "src/esps_drv_dispatcher.c"
    "src/esps_drv_pool.c"
    "src/esps_drv_queue.c"
    "src/esps_drv_receive_irq.c"
    "src/esps_drv_stats.c"
    "src/esps_drv_transmit_irq.c"
    "src/esps_drv_rcc.c"
    "src/esps_drv_tim.c"
    "src/esps_drv_rng.c"
)

list(
    APPEND ESPSI_DRV_INCLUDES
    "inc"
    )

target_include_directories(espsi_drv PUBLIC ${ROOT_INCLUDES} PUBLIC ${ESPSI_DRV_INCLUDES})
target_compile_definitions(espsi_drv PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(espsi_drv PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(espsi_drv PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(espsi_drv PUBLIC crc)
