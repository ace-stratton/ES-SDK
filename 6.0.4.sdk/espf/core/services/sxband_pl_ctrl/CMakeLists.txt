project(sxband_pl_ctrl C)
set(make_target "sxband_pl_ctrl")

include(${ROOT_BUILD_PATH}/espf.cmake)

list(APPEND module_sources 
	"src/sxband_pl_ctrl.c"
)

add_library(${make_target} STATIC
    ${module_sources}
)

list(APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
)

if (SXBAND_SCHEDULER_ENABLED)
list(APPEND sxband_libs sxband_sched)
target_link_libraries(${make_target} ${sxband_libs})
endif (SXBAND_SCHEDULER_ENABLED)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
