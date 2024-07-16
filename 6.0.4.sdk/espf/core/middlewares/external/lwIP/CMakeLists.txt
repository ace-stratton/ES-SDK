project(lwIP C)
set(make_target "lwIP")

list(APPEND module_includes
    "${PROJECT_SOURCE_DIR}/src/include"
    "${PROJECT_SOURCE_DIR}/system"
)

list(APPEND lwip_sources
	"${PROJECT_SOURCE_DIR}/src/api/api_lib.c"
	"${PROJECT_SOURCE_DIR}/src/api/api_msg.c"
	"${PROJECT_SOURCE_DIR}/src/api/err.c"
	"${PROJECT_SOURCE_DIR}/src/api/netbuf.c"
	"${PROJECT_SOURCE_DIR}/src/api/netdb.c"
	"${PROJECT_SOURCE_DIR}/src/api/netifapi.c"
	"${PROJECT_SOURCE_DIR}/src/api/sockets.c"
	"${PROJECT_SOURCE_DIR}/src/api/tcpip.c"
	"${PROJECT_SOURCE_DIR}/src/apps/http/fs.c"
	"${PROJECT_SOURCE_DIR}/src/apps/http/httpd.c"
    "${PROJECT_SOURCE_DIR}/src/apps/tftp/tftp.c"
	"${PROJECT_SOURCE_DIR}/src/core/def.c"
	"${PROJECT_SOURCE_DIR}/src/core/dns.c"
	"${PROJECT_SOURCE_DIR}/src/core/inet_chksum.c"
	"${PROJECT_SOURCE_DIR}/src/core/init.c"
	"${PROJECT_SOURCE_DIR}/src/core/ip.c"
	"${PROJECT_SOURCE_DIR}/src/core/mem.c"
	"${PROJECT_SOURCE_DIR}/src/core/memp.c"
	"${PROJECT_SOURCE_DIR}/src/core/netif.c"
	"${PROJECT_SOURCE_DIR}/src/core/pbuf.c"
	"${PROJECT_SOURCE_DIR}/src/core/raw.c"
	"${PROJECT_SOURCE_DIR}/src/core/stats.c"
	"${PROJECT_SOURCE_DIR}/src/core/sys.c"
	"${PROJECT_SOURCE_DIR}/src/core/tcp.c"
	"${PROJECT_SOURCE_DIR}/src/core/tcp_in.c"
	"${PROJECT_SOURCE_DIR}/src/core/tcp_out.c"
	"${PROJECT_SOURCE_DIR}/src/core/timeouts.c"
	"${PROJECT_SOURCE_DIR}/src/core/udp.c"
	"${PROJECT_SOURCE_DIR}/src/core/ipv4/autoip.c"
	"${PROJECT_SOURCE_DIR}/src/core/ipv4/dhcp.c"
	"${PROJECT_SOURCE_DIR}/src/core/ipv4/etharp.c"
	"${PROJECT_SOURCE_DIR}/src/core/ipv4/icmp.c"
	"${PROJECT_SOURCE_DIR}/src/core/ipv4/igmp.c"
	"${PROJECT_SOURCE_DIR}/src/core/ipv4/ip4.c"
	"${PROJECT_SOURCE_DIR}/src/core/ipv4/ip4_addr.c"
	"${PROJECT_SOURCE_DIR}/src/core/ipv4/ip4_frag.c"
	"${PROJECT_SOURCE_DIR}/src/netif/ethernet.c"
	"${PROJECT_SOURCE_DIR}/system/OS/sys_arch.c"
)

add_library(${make_target} STATIC
    ${lwip_sources}
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS} -DLWIP_DEBUG)
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
