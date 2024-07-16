project(ESPSI)
set(make_target "ESPSI")

list(APPEND includes
    "../ESPLATFORM_COMMON"
    "./"
    "ES_CP/Diagnostics"
    "ES_CP"
    "ES_CP/ESCP_Common"
    "ES_FW_UPD_CB_INTF"
    "ES_HS"
    "ES_SAT_AIRMAC"
    "ES_SAT_API/include"
    "ES_SAT_API/Source"
    "ES_SAT_MACGW"
    "ES_SAT_MAC"
    "ES_TL_LAYER"
)

include(${CMAKE_SOURCE_DIR}/build_cfg.cmake)

cmake_path(APPEND LIB_PATH ${CMAKE_SOURCE_DIR} ".." "lib" ${BUILD_CFG_NAME} lib${make_target}.a)

if (EXISTS ${LIB_PATH})
    add_library(${make_target} INTERFACE)
    
    target_link_libraries(${make_target} INTERFACE ${LIB_PATH})
    target_include_directories(${make_target} INTERFACE ${includes})
else ()
    add_library(${make_target} STATIC
        "ES_CP/ESCCP_ModDrv.c"
        "ES_CP/ESCP_ModDrv.c"
        "ES_FW_UPD_CB_INTF/ESFWUPD_ModDrv.c"
        "ES_HS/ESHS_ModDrv.c"
        "ES_SAT_API/Source/ESSA_BridgeDrvProtocol.c"
        "ES_SAT_API/Source/ESSA_MACTestProtocol.c"
        "ES_SAT_API/Source/ESSA_ServiceProtocol_Impl.c"
        "ES_SAT_API/Source/ESSA_ServiceProtocol_Impl_CCP.c"
        "ES_SAT_API/Source/ESSA_Stack.c"
        "ES_TL_LAYER/ESTL_Bridge_Drv.c"
        "ES_TL_LAYER/ESTL_Drv.c"
        "ES_TL_LAYER/ESTL_Receiver.c"
        "ES_TL_LAYER/ESTL_Sender.c"
        "ES_TL_LAYER/ESTL_Utils.c"
        "ES_SAT_API/Source/ESSA_FP.c"
    )
    
    list(APPEND target_options ${ROOT_COMPILE_OPTIONS})
    list(REMOVE_ITEM target_options "-pedantic")
    list(APPEND target_options "-Wno-switch")
    list(APPEND target_options "-Wno-unused-function")
    list(APPEND target_options "-Wno-unknown-pragmas")
    list(APPEND target_options "-Wno-switch-enum")
    
    target_include_directories(${make_target} PUBLIC ${includes} PRIVATE ${ROOT_INCLUDES})
    target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
    target_compile_options(${make_target} PRIVATE ${target_options})
    target_link_options(${make_target} PUBLIC ${ROOT_LINK_OPTIONS})
endif ()

