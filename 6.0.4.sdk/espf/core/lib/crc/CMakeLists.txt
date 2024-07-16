project(crc C)
set(make_target "crc")

include(${ROOT_BUILD_PATH}/espf.cmake)

list(APPEND module_sources 
	"src/crc16-ccitt.c"
	"src/es_crc32.c"
	"src/es_crc8.c"
	"src/MACCRC32_Classic_Impl.c"
)

add_library(${make_target} STATIC
    ${module_sources}
)

list(APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} fatfs)