project(netw C)
set(make_target "netw")

include(${ROOT_BUILD_PATH}/espf.cmake)

add_library(${make_target} STATIC
    "src/netw.c"
)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}/inc"
)

list(APPEND libs
    lwIP
)

if (ETHERNET_SUPPORT_ENABLED)
list(APPEND libs
	ethernetif
)
endif (ETHERNET_SUPPORT_ENABLED)

if (TFTPD_SUPPORT_ENABLED)
list(APPEND libs
    tftpd
)
endif (TFTPD_SUPPORT_ENABLED)

if (SLIP_SUPPORT_ENABLED)
    list(APPEND libs
         slipif
    )
endif (SLIP_SUPPORT_ENABLED)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} PUBLIC ${libs})
