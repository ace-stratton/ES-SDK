project(fatfs C)

add_library(fatfs STATIC 
                 oofatfs/src/ff.c
                 oofatfs/src/ffunicode.c
                 option/syscall.c
                 diskio_adapter.c
                 fatfs.c
                 ff_gen_drv.c
)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/oofatfs/src"
)

list(
    APPEND ROOT_COMPILE_DEFS
    -DFFCONF_H="ffconf.h"
    -DFF_USE_WRITE
    -DFF_USE_IOCTL
)
    

target_include_directories(fatfs PRIVATE ${ROOT_INCLUDES} PUBLIC ${module_includes})
target_compile_definitions(fatfs PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(fatfs PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(fatfs PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(fatfs sd_diskio)
