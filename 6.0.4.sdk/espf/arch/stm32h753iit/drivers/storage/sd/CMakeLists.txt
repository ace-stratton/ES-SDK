project(sd_diskio C)

add_library(sd_diskio STATIC 
                 bsp_driver_sd.c
                 sd_diskio.c
)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
)

list(
    APPEND ROOT_COMPILE_DEFS
    -DENABLE_SD_DMA_CACHE_MAINTENANCE=0
)
    
target_include_directories(sd_diskio PRIVATE ${ROOT_INCLUDES} PUBLIC ${module_includes})
target_compile_definitions(sd_diskio PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(sd_diskio PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(sd_diskio PRIVATE ${ROOT_LINK_OPTIONS})
