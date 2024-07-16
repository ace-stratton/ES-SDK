project(csp C)
set(make_target "csp")

add_library(${make_target} STATIC 
    src/arch/csp_system.c
    src/arch/csp_time.c
    src/arch/freertos/csp_clock.c
    src/arch/freertos/csp_malloc.c
    src/arch/freertos/csp_queue.c
    src/arch/freertos/csp_semaphore.c
    src/arch/freertos/csp_system.c
    src/arch/freertos/csp_thread.c
    src/arch/freertos/csp_time.c
    src/crypto/csp_hmac.c
    src/crypto/csp_sha1.c
    src/crypto/csp_xtea.c
    src/csp_bridge.c
    src/csp_buffer.c
    src/csp_conn.c
    src/csp_crc32.c
    src/csp_debug.c
    src/csp_dedup.c
    src/csp_endian.c
    src/csp_hex_dump.c
    src/csp_iflist.c
    src/csp_init.c
    src/csp_io.c
    src/csp_port.c
    src/csp_promisc.c
    src/csp_qfifo.c
    src/csp_route.c
    src/csp_service_handler.c
    src/csp_services.c
    src/csp_sfp.c
    src/interfaces/csp_if_can.c
    src/interfaces/csp_if_can_pbuf.c
    src/interfaces/csp_if_i2c.c
    src/interfaces/csp_if_kiss.c
    src/interfaces/csp_if_lo.c
    src/rtable/csp_rtable.c
    src/rtable/csp_rtable_static.c
    src/transport/csp_rdp.c
    src/transport/csp_udp.c
)

list(APPEND csp_compile_options ${ROOT_COMPILE_OPTIONS})
list(REMOVE_ITEM csp_compile_options "-pedantic")

target_include_directories(${make_target} PUBLIC ${OBC_includes} PUBLIC build/include include) 
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${csp_compile_options})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
