project(espsi_common C)

add_library(espsi_common STATIC
	"FP_BaseProtocolTypes.h"
	"FP_Helpers.c"
	"FP_Helpers.h"
	"FP_ProtocolServerCommon.c"
	"FP_ProtocolServerCommon.h"
)

target_include_directories(espsi_common PUBLIC ${ROOT_INCLUDES} PUBLIC ${PROJECT_SOURCE_DIR})
target_compile_definitions(espsi_common PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(espsi_common PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(espsi_common PRIVATE ${ROOT_LINK_OPTIONS})
