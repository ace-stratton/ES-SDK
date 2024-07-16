project(sensor_data_service C)
set(make_target "sensor_data_service")

include(${ROOT_BUILD_PATH}/espf.cmake)

cmake_path(SET fp_gen_path "${PROJECT_SOURCE_DIR}/fp")

if (COMM_ESPS_ENABLED)
	#
	# Global declarations for "Sensor_Data_Service"
	#
	cmake_path(SET sensor_data_service_fdepl_path "${PROJECT_SOURCE_DIR}/config/Sensor_Data_Service.fdepl")
	cmake_path(SET sensor_data_service_fidl_path "${FIDL_ROOT_OBC}/sds.fidl")
	
	list(APPEND fp_sensor_data_service_src_list
		${PROJECT_SOURCE_DIR}/fp/SDS/v0.3/SDS_server/FP_SDSProtocolServer.c
		${PROJECT_SOURCE_DIR}/fp/SDS/v0.3/SDS_server/FP_SDSProtocolServer.h
		${PROJECT_SOURCE_DIR}/fp/SDS/v0.3/SDS_server/FP_SDSProtocolTypes.h
		${PROJECT_SOURCE_DIR}/fp/SDS/v0.3/SDS_server/FP_SDSServerApp.c
		${PROJECT_SOURCE_DIR}/fp/SDS/v0.3/SDS_server/FP_SDSServerApp.h
	)
	
	set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
	    "#include \"fp/SDS/v0.3/SDS_server/FP_SDSProtocolServer.h\""
	)
	
	set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
	    "&FP_SDSProtocolServerInfo"
	)
	
	set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
	    "#include \"fp/SDS/v0.3/SDS_server/FP_SDSServerApp.h\""
	)
	
	set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
	    "SDSServerAppInit()\;"
	)
	
	list(APPEND sds_sources
	    ${fp_sensor_data_service_src_list}
	)
	
	FP_GEN_AT_PATH(fp_sensor_data_service_src_list ${sensor_data_service_fdepl_path} sensor_data_service_fidl_path ${fp_gen_path})
endif (COMM_ESPS_ENABLED)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
)

list (APPEND sds_sources
	"src/sensor_data_service.c"
)

add_library(${make_target} STATIC
    ${sds_sources}
)

list(APPEND sds_libs
    timer
    nvm
    assertions
)
target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} ${sds_libs})
