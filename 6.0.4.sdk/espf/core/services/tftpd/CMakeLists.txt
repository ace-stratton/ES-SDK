project(tftpd C)
set(make_target "tftpd")

include(${ROOT_BUILD_PATH}/espf.cmake)

list(APPEND module_sources 
	"src/tftpd.c"
)

add_library(${make_target} STATIC
    ${module_sources}
)

list(APPEND module_includes
    "${PROJECT_SOURCE_DIR}/inc"
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} lwIP libtrace)
