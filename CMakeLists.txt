project(espf C)
set(make_target "espf_sub")

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/core/middlewares"
    "${PROJECT_SOURCE_DIR}/core/lib/cdef"
    "${PROJECT_SOURCE_DIR}/core/lib/crc/inc"
    "${PROJECT_SOURCE_DIR}/app"
    "${PROJECT_SOURCE_DIR}/core/lib/debug/inc"
    "${PROJECT_SOURCE_DIR}/arch/stm32h753iit/hal/inc"
    "${PROJECT_SOURCE_DIR}/arch/stm32h753iit/hal/cmsis/device/st/stm32h7xx/include"
    "${PROJECT_SOURCE_DIR}/arch/arm/cmsis/include"
    "${PROJECT_SOURCE_DIR}/core/lib/FP_common"
    "${PROJECT_SOURCE_DIR}/core/lib"
    "${PROJECT_SOURCE_DIR}/core/lib/module_id/inc"
    "${PROJECT_SOURCE_DIR}/core/middlewares/external/FreeRTOS/Source/CMSIS_RTOS_V2"
    "${PROJECT_SOURCE_DIR}/core/middlewares/external/FreeRTOS/Source/include"
    "${PROJECT_SOURCE_DIR}/core/services/sd_mng"
    "${PROJECT_SOURCE_DIR}/core/services"
    "${PROJECT_SOURCE_DIR}/core/middlewares/external/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1"
    "${PROJECT_SOURCE_DIR}/arch/stm32h753iit/drivers/storage/sd"
    "${PROJECT_SOURCE_DIR}/core/services/init_service"
    "${PROJECT_SOURCE_DIR}/core/services/taskmon"
    "${PROJECT_SOURCE_DIR}/core/services/solar_panels"
    "${PROJECT_SOURCE_DIR}/core/services/exeh/inc"
    "${PROJECT_SOURCE_DIR}/config/ESPLATFORM_NETWORK_STACK/inc"
    "${PROJECT_SOURCE_DIR}/core/lib/misc"
    "${PROJECT_SOURCE_DIR}/config/datacache"
    "${PROJECT_SOURCE_DIR}/core/middlewares"
    "${PROJECT_SOURCE_DIR}/core/services"
    "${PROJECT_SOURCE_DIR}/config/aocs/adcs_tlm"
    "${PROJECT_SOURCE_DIR}/core/services/aocs/adcs_tlm"
    "${PROJECT_SOURCE_DIR}/core/lib/sys_instancer"
    "${PROJECT_SOURCE_DIR}/core/services/eps_ctrl"
    "${PROJECT_SOURCE_DIR}/core/lib/libcbuff"
    "${PROJECT_SOURCE_DIR}/config/libdebug"
    "${PROJECT_SOURCE_DIR}/config/aocs/aocs_cntrl"
    "${PROJECT_SOURCE_DIR}/core/services/aocs/aocs_cntrl/inc"
    "${PROJECT_SOURCE_DIR}/core/services/sys_time"
)

if (SXBAND_SCHEDULER_ENABLED)
    list(APPEND module_includes "${PROJECT_SOURCE_DIR}/config/sxband_sched")
endif (SXBAND_SCHEDULER_ENABLED)

list(APPEND ROOT_INCLUDES ${module_includes})

add_subdirectory(core/services/payload_ctrl payload_ctrl)
add_subdirectory(core/lib/assertions assertions)
add_subdirectory(core/lib/libsgp4 SGP4)
add_subdirectory(core/lib/libcobs COBS)
add_subdirectory(core/lib/libhsm hsm)
add_subdirectory(core/lib/libtimer timer)
add_subdirectory(core/services/eps_ctrl EPS_control)
add_subdirectory(core/lib/libdatetime datetime)
add_subdirectory(core/services/nvm nvm)
add_subdirectory(config/nvm nvm_cfg)
add_subdirectory(core/services/sys_time sys_time)
add_subdirectory(core/lib/libcbuff CBUFF)
add_subdirectory(config/datacache datacache)
add_subdirectory(core/lib/crc crc)
add_subdirectory(core/lib/cbuf cbuf)
add_subdirectory(core/lib/cobs_inplace cobs_inplace)
add_subdirectory(core/lib/trace libtrace)
add_subdirectory(core/lib/sys_printf sys_printf)
add_subdirectory(core/lib/irq irq)
add_subdirectory(core/lib/libfile_stack file_stack)
add_subdirectory(core/middlewares/ESPLATFORM_NETWORK_STACK ESPSI)
add_subdirectory(arch/stm32h753iit/drivers/arm_fault_handler arm_fault_handler)
add_subdirectory(core/services/fault_persistor fault_persistor)


if (CSP_SUPPORT_ENABLED)
    add_subdirectory(core/services/csp csp_service)
    add_subdirectory(core/middlewares/external/csp csp)
    list(APPEND libs
        csp_service
        csp
    )
endif (CSP_SUPPORT_ENABLED)

if (LWIP_SUPPORT_ENABLED)
    add_subdirectory(core/middlewares/external/lwIP lwIP)
    add_subdirectory(core/services/netw netw)

    list(APPEND libs
        lwIP
        netw
    )

if (ETHERNET_SUPPORT_ENABLED)
    add_subdirectory(arch/stm32h753iit/drivers/comm/nxp-tja11xx nxp-tja11xx)
    add_subdirectory(arch/stm32h753iit/drivers/comm/ethernetif ethernetif)

    list(APPEND libs
        nxp-tja11xx
        ethernetif
    )
endif (ETHERNET_SUPPORT_ENABLED)

if (TFTPD_SUPPORT_ENABLED)
    add_subdirectory(core/services/tftpd tftpd)
    list(APPEND libs
        tftpd
    )
endif (TFTPD_SUPPORT_ENABLED)

if (SLIP_SUPPORT_ENABLED)
    add_subdirectory(arch/stm32h753iit/drivers/comm/slipif slipif)
    list(APPEND libs
        slipif
    )
endif (SLIP_SUPPORT_ENABLED)

endif (LWIP_SUPPORT_ENABLED)

if (CRYPTO_SERVICE_ENABLED)
    add_subdirectory(core/middlewares/external/ST/STM32_Cryptographic stm32_crypto)
    list(APPEND libs stm32_crypto)
endif (CRYPTO_SERVICE_ENABLED)

list(APPEND libs
    assertions
    payload_ctrl
    SGP4
    COBS
    hsm
    timer
    eps_ctrl
    datetime
    sys_time
    datacache
    crc
    nvm
    nvm_cfg
    cbuf
    cobs_inplace
    libtrace
    sys_printf
    irq
    ESPSI
    file_stack
    arm_fault_handler
    fault_persistor
)

list(
    APPEND shared_sources_list
    "core/lib/debug/src/debug.c"
    "core/lib/FP_common/FP_Helpers.c"
    "core/lib/FP_common/FP_ProtocolServerCommon.c"
    "core/lib/libCFB/CircularFlatBuffer.c"
    "core/lib/liblz77/es_lz77.c"
    "core/lib/module_id/src/module_id.c"
    "core/lib/reset_counters/nvm_resetcounters.c"
    "core/lib/tle/TleUpdate.c"
    "core/middlewares/external/FreeRTOS/Source/croutine.c"
    "core/middlewares/external/FreeRTOS/Source/event_groups.c"
    "core/middlewares/external/FreeRTOS/Source/list.c"
    "core/middlewares/external/FreeRTOS/Source/queue.c"
    "core/middlewares/external/FreeRTOS/Source/stream_buffer.c"
    "core/middlewares/external/FreeRTOS/Source/tasks.c"
    "core/middlewares/external/FreeRTOS/Source/timers.c"
    "core/middlewares/external/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c"
    "core/middlewares/external/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/port.c"
    "core/middlewares/external/FreeRTOS/Source/portable/MemMang/heap_5.c"
    "core/services/exeh/src/es_exeh.c"
    "core/services/init_service/AppTasks.c"
    "core/services/init_service/DefTasks.c"
    "core/services/payload_scheduler/payload_scheduler.c"
    "core/services/sd_mng/FileManager.c"
    "core/services/sd_mng/SdMngr.c"
    "core/services/taskmon/TaskMonitor.c"
    "core/lib/misc/CommandsApi.c"
    "core/lib/sys_instancer/sys_instancer.c"
    "core/lib/libDataSink/DataSink.c"
    "core/lib/libDataSink/FileSink.c"
)

add_subdirectory(core/services/solar_panels ssp)
list(APPEND libs ssp)

if (COMM_ESPS_ENABLED)
    list(APPEND shared_sources_list
        "core/services/espsi/cp/CP_Handler.c"
        "core/services/espsi/cp/cp_cmd_handler.c"
        "core/services/espsi/cp/CP_Fault_Commands.c"
        "core/services/espsi/cp/CP_SX_Band_Commands.c"
        "core/services/espsi/fwupd/FWUPD_Handler.c"
        "config/ESPLATFORM_NETWORK_STACK/src/FWUPD_Handler_Cfg.c"
        "core/services/espsi/fwupd/FWUPD_Persistor.c"
        "core/services/espsi/tp/ESSA_Stack_TP_Layer.c"
    )

	if (CUBEADCS_GEN2_ENABLED)
		list(APPEND shared_sources_list
			"core/services/espsi/cp/CP_CubeADCS_Gen2_Commands.c"
		)
	endif (CUBEADCS_GEN2_ENABLED)
    add_subdirectory(core/lib/FP_common espsi_common)
    list(APPEND libs espsi_common)

    add_subdirectory(core/services/espsi espsi_fp)
    list(APPEND libs espsi_fp)
endif (COMM_ESPS_ENABLED)

add_subdirectory(arch/stm32h753iit/drivers/power/eps_i eps_i)
list(APPEND libs eps_i)

add_subdirectory(arch/stm32h753iit/drivers/power/eps_ii eps_ii)
list(APPEND libs eps_ii)

add_subdirectory(arch/stm32h753iit/drivers/power/eps_m eps_m)
list(APPEND libs eps_m)

add_subdirectory(arch/stm32h753iit/drivers/positioning/libcubeadcs cubeadcs)
list(APPEND libs cubeadcs)

add_subdirectory(core/middlewares/external/libcubeobc cubeobc)
list(APPEND libs cubeobc)

add_subdirectory(core/services/pingpong pingpong)
list(APPEND libs pingpong)

add_subdirectory(core/services/sharp sharp)
list(APPEND libs sharp)

add_subdirectory(core/services/meddea meddea)
list(APPEND libs meddea)

list(APPEND shared_sources_list
    "core/services/aocs/adcs_tlm/adcs_tlm.c"
    "config/aocs/adcs_tlm/adcs_tlm_cfg.c"
)


add_subdirectory(core/services/aocs/aocs_cntrl aocs_cntrl_service)
list(APPEND libs aocs_cntrl_service)

if (CUBEADCS_GEN2_ENABLED)
	add_subdirectory(core/services/aocs/cubeadcs_gen2 cubeadcs_gen2_service)
	list(APPEND libs cubeadcs_gen2_service)
endif (CUBEADCS_GEN2_ENABLED)

add_subdirectory(core/services/rng rng)
list(APPEND libs rng)

if (TELEMETRY_SERVICE_ENABLED)
    add_subdirectory(core/services/telemetry telemetry)
    list(APPEND libs telemetry)
endif (TELEMETRY_SERVICE_ENABLED)

if (BEACONS_ENABLED)
    add_subdirectory(core/services/beacons beacons)
    list(APPEND libs beacons)
endif (BEACONS_ENABLED)

if (SXBAND_SCHEDULER_ENABLED)
    add_subdirectory(core/services/sxband_sched sxband_sched)
    list(APPEND libs sxband_sched)
endif (SXBAND_SCHEDULER_ENABLED)

if (CRYPTO_SERVICE_ENABLED)
    add_subdirectory(core/services/crypto crypto)
    list(APPEND libs crypto)
endif (CRYPTO_SERVICE_ENABLED)

if (EXTMODULES_SBAND_TMTC_ENABLED)
    add_subdirectory(arch/stm32h753iit/drivers/radio/sband_tmtc sband_tmtc)
    list(APPEND libs sband_tmtc)
endif (EXTMODULES_SBAND_TMTC_ENABLED)

add_subdirectory(core/lib/libcsq_algo libcsq_algo)
list(APPEND libs libcsq_algo)

add_subdirectory(core/services/sxband_pl_ctrl sxband_pl_ctrl)
list(APPEND libs sxband_pl_ctrl)

add_subdirectory(core/services/sensor_data_service sensor_data_service)
list(APPEND libs sensor_data_service)

add_subdirectory(core/services/es_coordsys es_coordsys)
list(APPEND libs es_coordsys)

add_subdirectory(core/services/es_adcs es_adcs)
list(APPEND libs es_adcs)

add_subdirectory(core/services/actuator_control_service actuator_control_service)
list(APPEND libs actuator_control_service)

add_subdirectory(arch/stm32h753iit/drivers/sensors/gyro_adis16265 adis16265_gyro)
list(APPEND libs adis16265_gyro)

if (MICROPYTHON_SERVICE_ENABLED)
    list(APPEND ROOT_INCLUDES "${PROJECT_SOURCE_DIR}/core/services/upython/inc")
    add_subdirectory(core/middlewares/external/micropython/ports/obc micropython)
    add_subdirectory(core/services/upython upython)
    list(APPEND libs upython)
endif (MICROPYTHON_SERVICE_ENABLED)

add_library(${make_target} STATIC ${shared_sources_list})

# Generate ESSA_StackConfigServices.h with the configured services
get_property(TMP_LIST GLOBAL PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST)
set_property(GLOBAL PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST) # Unset global property
list(JOIN TMP_LIST "\n" FUNCTION_PROTOCOL_INCLUDE_LIST)
set(TMP_LIST) # Unset

get_property(TMP_LIST GLOBAL PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST)
set_property(GLOBAL PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST) # Unset global property
list(JOIN TMP_LIST ", \\\n    " FUNCTION_PROTOCOL_HANDLERS_LIST)
set(TMP_LIST) # Unset

configure_file(
    "${PROJECT_ROOT}/config/ESPLATFORM_NETWORK_STACK/inc/ESSA_StackConfigServices.h.tmpl"
    "${PROJECT_ROOT}/config/ESPLATFORM_NETWORK_STACK/inc/ESSA_StackConfigServices.h"
    NEWLINE_STYLE UNIX
)

get_property(TMP_LIST GLOBAL PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST)
set_property(GLOBAL PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST) # Unset global property
list(JOIN TMP_LIST "\n" FUNCTION_PROTOCOL_APP_INCLUDE_LIST)
set(TMP_LIST) # Unset

get_property(TMP_LIST GLOBAL PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST)
set_property(GLOBAL PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST) # Unset global property
list(JOIN TMP_LIST "\n    " FUNCTION_PROTOCOL_APP_INIT_LIST)
set(TMP_LIST) # Unset

configure_file(
    "${PROJECT_ROOT}/config/ESPLATFORM_NETWORK_STACK/inc/ESSA_StackConfigApps.h.tmpl"
    "${PROJECT_ROOT}/config/ESPLATFORM_NETWORK_STACK/inc/ESSA_StackConfigApps.h"
    NEWLINE_STYLE UNIX
)

target_include_directories(${make_target} INTERFACE ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PUBLIC ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} PUBLIC ${libs})
