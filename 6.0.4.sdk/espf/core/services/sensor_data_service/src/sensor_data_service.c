/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup sds
 * @{
 *
 * @file     sensor_data_service.c
 * @brief    This is the sensor data service (SDS) main source file
 *
 * @}
*/

#include "../inc/sensor_data_service.h"
#include "sds_events.h"

#include "TaskMonitor.h"
#include "es_exeh.h"
#include "datacache.h"
#include "nvm/inc/nvm.h"

#include "timer.h"

#include "es_coordsys.h"

#include <math.h>
#include <string.h>

#include "sensor_data_dbg.h"
#include "assertions.h"

/** @brief Enable this define you want to check the SDS performance using pin toggling. WARNING, the used pins are
 * the GPIO pins, the OBC MUST NOT be stacked with other devices! */
#define SDS_PIN_DBG (0)

/** @brief Module ID used for this file to report error events in EXEH */
#define EXEH_CURRENT_MODULE_ID eEXEHModuleID_SDS
/** @brief Time in ms representing the period between the NVM update check */
#define SDS_NVM_CHECK_PERIOD_MS	(1000U)
/** @brief Task base sampling period */
#define SDS_BASE_SAMPLING_PERIOD_MS	(1000U)
/** @brief Sensor mutex lock timeout in [ms] */
#define SDS_LOCK_TIMEOUT (0U)

#if SDS_PIN_DBG
	#define OBC_OUT1_Pin GPIO_PIN_15
	#define OBC_OUT1_GPIO_Port GPIOB
	#define OBC_OUT2_Pin GPIO_PIN_5
	#define OBC_OUT2_GPIO_Port GPIOD
	#define OBC_OUT3_Pin GPIO_PIN_4
	#define OBC_OUT3_GPIO_Port GPIOD
	#define OBC_OUT5_Pin GPIO_PIN_6
	#define OBC_OUT5_GPIO_Port GPIOG
	#define OBC_OUT4_6_Pin GPIO_PIN_0
	#define OBC_OUT4_6_GPIO_Port GPIOD
	#define OBC_OUT7_Pin GPIO_PIN_5
	#define OBC_OUT7_GPIO_Port GPIOH
	#define OBC_OUT8_Pin GPIO_PIN_15
	#define OBC_OUT8_GPIO_Port GPIOH
#endif /* SDS_PIN_DBG */

/**********************************************************************
 *
 * Type definitions
 *
 **********************************************************************/
/** @typedef sds_exceptions_t
    @brief Exceptions logged by the exeh module */
typedef enum
{
	SDS_Exception_Runtime_Error,
	SDS_Exception_OS_Task_Spawn_Error,
	SDS_Exception_OS_Mutex_Spawn_Error,
	SDS_Exception_OS_Mutex_Lock_Error,
	SDS_Exception_OS_Mutex_Release_Error
} sds_exceptions_t;

/**********************************************************************
 *
 * Internal type definitions
 *
 **********************************************************************/
static       osThreadId_t   sds_task_taskHandle;
static const osThreadAttr_t sds_task_attributes = {
  .name = "fs_sds_task",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 2048
};

/** @brief The events mask used in the task */
static uint32_t events_mask;

/** @brief Used for the SW timer that periodically requests the NVM timers configuration */
static timer_handle_t time_nvm_check;

/** @brief In default mode, the SDS performs sampling of the sensors every second. However, some sensor readings
 * take significant time in this mode and the sampling period is broken. We are using a SW timer to remedy this
 * without looking for high accuracy. The sampling should happen every second and should be completed before the
 * next sampling period starts */
static timer_handle_t time_periodic_sample;

/** @brief Used to cache the last NVM read configuration */
static sds_sens_read_freq_t sds_chan_freq_cfgs;

/**@brief Store mutex objects used for access control to the sensors */
static osMutexId_t p_sens_lock[SENSOR_COUNT];

/**********************************************************************
 *
 * Static function declarations
 *
 **********************************************************************/
STATIC void fs_sds_task(void *arg);
STATIC void fs_sds_check_pwr_save_off(uint8_t sindx);
STATIC void fs_sds_check_pwr_save_on(uint8_t sindx);
STATIC void fs_sds_init_timer(void);
STATIC void fs_sds_spawn_locks(void);

#if SDS_PIN_DBG
	STATIC void fs_dbg_out_pin_on(uint32_t event_id, sensor_data_sensors_t sensor_type);
	STATIC void fs_dbg_out_pin_off(uint32_t event_id, sensor_data_sensors_t sensor_type);
#endif /* SDS_PIN_DBG */

/**********************************************************************
 *
 * Public functions
 *
 **********************************************************************/
void sds_init(void)
{
	EXEH_INIT_MODULE_FILENAME();

	sds_task_taskHandle = osThreadNew(fs_sds_task, NULL, &sds_task_attributes);

	if ( NULL == sds_task_taskHandle )
	{
		EXEH_HANDLE(eEXEHSeverity_Fatal, (int32_t)SDS_Exception_OS_Task_Spawn_Error);
	}
	else
	{
		TaskMonitor_TaskInitialized(TASK_SDS);
	}

	fs_sds_spawn_locks();

	for ( uint8_t sindx = 0; sindx < SENSOR_COUNT; ++sindx)
	{
		sensor_base_cfg[sindx].sens_if->init();
	}

	events_mask = (uint32_t)pow(2, SENSOR_COUNT) - 1U;

	fs_sds_init_timer();

	timer_start(&time_nvm_check);
}

osThreadId_t sds_get_thread_id(void)
{
    return sds_task_taskHandle;
}

bool sds_sens_lock(sensor_data_sensors_t s_type)
{
	bool res = true;

	if ( osOK != osMutexAcquire(p_sens_lock[s_type], SDS_LOCK_TIMEOUT) )
	{
		EXEH_HANDLE(eEXEHSeverity_Error, (int32_t)SDS_Exception_OS_Mutex_Lock_Error);

		res = false;
	}

	return res;
}

bool sds_sens_release(sensor_data_sensors_t s_type)
{
	bool res = true;

	if ( osOK != osMutexRelease(p_sens_lock[s_type]) )
	{
		EXEH_HANDLE(eEXEHSeverity_Error, (int32_t)SDS_Exception_OS_Mutex_Release_Error);

		res = false;
	}

	return res;
}

void sds_conv_mag_data_to_sat_frame(sds_mag_data_t const * const p_mag_data, sds_mag_enum_t mag_id, sds_mag_data_sat_t * const p_mag_data_sat)
{
	CRIT_ASSERT(p_mag_data != NULL);
	CRIT_ASSERT(p_mag_data_sat != NULL);
	CRIT_ASSERT(mag_id < SDS_MAG_NUM);

	/* Local arrays for using coordinate frame transformation */
	int32_t mag_data_sensor_frame[3];
	int32_t mag_data_satellite_frame[3];

	/* Extract measurements in sensor frame */
	(void)memcpy(mag_data_sensor_frame, p_mag_data, sizeof(sds_mag_data_t));

	/* Transform data from sensor frame to satellite frame */
	(void)coordSys_transformMag(mag_data_sensor_frame, mag_data_satellite_frame);

	/* Fill the satellite frame measurements struct with transformed data */
	(void)memcpy(p_mag_data_sat, mag_data_satellite_frame, sizeof(mag_data_satellite_frame));
}

void sds_conv_gyro_data_to_sat_frame(sds_gyro_data_t const * const p_gyro_data, sds_gyro_data_sat_t * const p_gyro_data_sat)
{
	CRIT_ASSERT(p_gyro_data != NULL);
	CRIT_ASSERT(p_gyro_data_sat != NULL);

	/* Local arrays for using coordinate frame transformation */
	int32_t gyr_data_sensor_frame[3];
	int32_t gyr_data_satellite_frame[3];

	/* Extract measurements in sensor frame */
	(void)memcpy(gyr_data_sensor_frame, p_gyro_data, sizeof(sds_gyro_data_t));

	/* Transform data from sensor frame to satellite frame */
	(void)coordSys_transformGyr(gyr_data_sensor_frame, gyr_data_satellite_frame);

	/* Fill the satellite frame measurements struct with transformed data */
	(void)memcpy(p_gyro_data_sat, gyr_data_satellite_frame, sizeof(gyr_data_satellite_frame));
}

void sds_conv_css_data_to_sat_frame(sds_css_data_t const * const p_css_data, sds_css_data_sat_t * const p_css_data_sat)
{
	CRIT_ASSERT(p_css_data != NULL);
	CRIT_ASSERT(p_css_data_sat != NULL);

	/* Local arrays for using coordinate frame transformation */
	int32_t css_data_sensor_frame[6];
	int32_t css_data_satellite_frame[6];

	/* Extract measurements in sensor frame */
	(void)memcpy(css_data_sensor_frame, p_css_data, sizeof(sds_css_data_t));

	/* Transform data from sensor frame to satellite frame */
	(void)coordSys_transformCss(css_data_sensor_frame, css_data_satellite_frame);

	/* Fill the satellite frame measurements struct with transformed data */
	(void)memcpy(p_css_data_sat, css_data_satellite_frame, sizeof(css_data_satellite_frame));
}

void sds_conv_acc_data_to_sat_frame(sds_acc_data_t const * const p_acc_data, sds_acc_enum_t acc_id, sds_acc_data_sat_t * const p_acc_data_sat)
{
	CRIT_ASSERT(p_acc_data != NULL);
	CRIT_ASSERT(p_acc_data_sat != NULL);
	CRIT_ASSERT(acc_id < SDS_ACC_NUM);

	/* Local arrays for using coordinate frame transformation */
	int32_t acc_data_sensor_frame[3];
	int32_t acc_data_satellite_frame[3];

	/* Extract measurements in sensor frame */
	(void)memcpy(acc_data_sensor_frame, p_acc_data, sizeof(sds_acc_data_t));

	/* Transform data from sensor frame to satellite frame */
	(void)coordSys_transformAcc(acc_data_sensor_frame, acc_data_satellite_frame);

	/* Fill the satellite frame measurements struct with transformed data */
	(void)memcpy(p_acc_data_sat, acc_data_satellite_frame, sizeof(acc_data_satellite_frame));
}

void sds_conv_panel_temp_data_to_sat_frame(sds_panel_temp_data_t const * const p_panel_temp_data, sds_panel_temp_data_sat_t * const p_panel_temp_data_sat)
{
	CRIT_ASSERT(p_panel_temp_data != NULL);
	CRIT_ASSERT(p_panel_temp_data_sat != NULL);

	/* Local arrays for using coordinate frame transformation */
	int32_t panel_temp_data_sensor_frame[6];
	int32_t panel_temp_data_satellite_frame[6];

	/* Extract measurements in sensor frame */
	memcpy(panel_temp_data_sensor_frame, p_panel_temp_data, sizeof(sds_panel_temp_data_t));

	/* Transform data from sensor frame to satellite frame */
	coordSys_transform_panel_temp(panel_temp_data_sensor_frame, panel_temp_data_satellite_frame);

	/* Fill the satellite frame measurements struct with transformed data */
	memcpy(p_panel_temp_data_sat, panel_temp_data_satellite_frame, sizeof(panel_temp_data_satellite_frame));
}

void sds_conv_gyro_temp_data_to_sat_frame(sds_gyro_temp_data_t const * const p_gyro_temp_data, sds_gyro_temp_data_sat_t * const p_gyro_temp_data_sat)
{
	CRIT_ASSERT(p_gyro_temp_data != NULL);
	CRIT_ASSERT(p_gyro_temp_data_sat != NULL);

	/* Local arrays for using coordinate frame transformation */
	int32_t gyro_temp_data_sensor_frame[3];
	int32_t gyro_temp_data_satellite_frame[3];

	/* Extract measurements in sensor frame */
	memcpy(gyro_temp_data_sensor_frame, p_gyro_temp_data, sizeof(sds_gyro_temp_data_t));

	/* Transform data from sensor frame to satellite frame */
	coordSys_transform_gyro_temp(gyro_temp_data_sensor_frame, gyro_temp_data_satellite_frame);

	/* Fill the satellite frame measurements struct with transformed data */
	memcpy(p_gyro_temp_data_sat, gyro_temp_data_satellite_frame, sizeof(gyro_temp_data_satellite_frame));
}


/**********************************************************************
 *
 * Static function definitions
 *
 **********************************************************************/
/** @brief The Sensor Data Service task
 *  @param[in] void const *argument - task arguments */
STATIC void fs_sds_task(void *arg)
{
	uint32_t events;

	uint32_t wait_time_ms = SDS_BASE_SAMPLING_PERIOD_MS;

	static sds_all_sens_data_t sens_data;
	static sds_all_sens_data_sat_step_t sens_data_sat;

	const void *p_sens_data;
	const void *p_sens_data_sat;

	for(;;)
	{
		events = osThreadFlagsWait(events_mask, osFlagsWaitAny, wait_time_ms);

		timer_start(&time_periodic_sample);

		if ( (osFlagsErrorUnknown != events) &&
				(osFlagsErrorResource != events) &&
					(osFlagsErrorParameter != events) )
		{
			/* Default case, if no events have arrived during the SDS wait period, read all sensors */
			if ( osFlagsErrorTimeout == events )
			{
				events = events_mask;
			}

			for ( uint8_t sindx = 0; sindx < SENSOR_COUNT; ++sindx )
			{
				if ( (false != (events & sds_chan_freq_cfgs.sens_cfg[sensor_base_cfg[sindx].freq_cfg_id].event_cfg)) &&
						( true == sds_sens_lock(sindx) ) )
				{
#if SDS_PIN_DBG
					fs_dbg_out_pin_on(sds_chan_freq_cfgs.sens_cfg[sensor_base_cfg[sindx].freq_cfg_id].event_cfg, sindx);
#endif /* SDS_PIN_DBG */
					fs_sds_check_pwr_save_off(sindx);

					if ( SDS_SENSOR_STATUS_INIT == sensor_base_cfg[sindx].sens_if->get_state() )
					{
						if ( SDS_OP_STATUS_OK == sds_get_sensor_data(sindx, &sens_data, &sens_data_sat, &p_sens_data, &p_sens_data_sat) )
						{
							dc_set_raw_data(DC_DATA_INPUT_INTERNAL,
									sensor_base_cfg[sindx].dc_did_id_SI_sens_frame,
									p_sens_data, sensor_base_cfg[sindx].dc_did_id_SI_sens_frame_size);

							dc_set_raw_data(DC_DATA_INPUT_INTERNAL,
									sensor_base_cfg[sindx].dc_did_id_SI_sat_frame,
									p_sens_data_sat, sensor_base_cfg[sindx].dc_did_id_SI_sat_frame_size);
						}
					}

					fs_sds_check_pwr_save_on(sindx);
#if SDS_PIN_DBG
					fs_dbg_out_pin_off(sds_chan_freq_cfgs.sens_cfg[sensor_base_cfg[sindx].freq_cfg_id].event_cfg, sindx);
#endif /* SDS_PIN_DBG */
					sds_sens_release(sindx);
				}
			}
		}
		if ( true == timer_is_elapsed(&time_nvm_check, SDS_NVM_CHECK_PERIOD_MS) )
		{
			/* Start next check */
			timer_start(&time_nvm_check);

			fs_sds_init_timer();
		}

		if ( SAFE_FALSE == sds_chan_freq_cfgs.enable)
		{
            uint32_t wait_time_ms_temp = SDS_BASE_SAMPLING_PERIOD_MS - timer_get_elapsed_time(&time_periodic_sample);
            if(SDS_BASE_SAMPLING_PERIOD_MS < wait_time_ms_temp)
            {
                wait_time_ms = SDS_BASE_SAMPLING_PERIOD_MS;
            }
            else
            {
                wait_time_ms = wait_time_ms_temp;
            }
		}
		else
		{
			wait_time_ms = SDS_BASE_SAMPLING_PERIOD_MS;
		}

		TaskMonitor_IamAlive(TASK_SDS);
		vApplicationLowStackCheck(TASK_SDS);
	}
}

/** @brief Disable power saving
 *  @param[in] uint8_t sindx */
STATIC void fs_sds_check_pwr_save_off(uint8_t sindx)
{
	if ( SDS_SENSOR_STATUS_INIT != sensor_base_cfg[sindx].sens_if->get_state() )
	{
		if ( !((sds_chan_freq_cfgs.enable == SAFE_TRUE) && (sds_chan_freq_cfgs.sens_cfg[sensor_base_cfg[sindx].freq_cfg_id].freq_cfg < 1)) )
		{
			sensor_base_cfg[sindx].sens_if->init();
		}
	}
}

/** @brief Enable power saving in case we are running with default frequency or minimum update frequency of 1 Hz
 *  @param[in] uint8_t sindx */
STATIC void fs_sds_check_pwr_save_on(uint8_t sindx)
{
	if ( SDS_SENSOR_STATUS_INIT == sensor_base_cfg[sindx].sens_if->get_state() )
	{
		if ( ((sds_chan_freq_cfgs.enable == SAFE_TRUE) && (sds_chan_freq_cfgs.sens_cfg[sensor_base_cfg[sindx].freq_cfg_id].freq_cfg < 1)) ||
				(sds_chan_freq_cfgs.enable == SAFE_FALSE) )
		{
			sensor_base_cfg[sindx].sens_if->deinit();
		}
	}
}

/** @brief Get the NVM configuration and initialise the timer */
STATIC void fs_sds_init_timer(void)
{
	Nvm_GetBlockById(NVM_BLOCK_SDS_SENS_READ_FREQ_CFG, (void *)&sds_chan_freq_cfgs);

	if ( SAFE_FALSE == sds_chan_freq_cfgs.enable )
	{
		sds_deinit_events_timer();
	}
	else
	{
		sds_init_events_timer(&sds_chan_freq_cfgs);
	}
}

/** @brief Spawn lock objects for all sensors */
STATIC void fs_sds_spawn_locks(void)
{
	for ( uint8_t sindx = 0; sindx < SENSOR_COUNT; sindx++ )
	{
		char lock_name[10U];
		snprintf(lock_name, sizeof(lock_name), "sens_%02d", sindx);
		const osMutexAttr_t sens_lock_attr = { lock_name, osMutexRecursive | osMutexPrioInherit, NULL, 0U };
		osMutexId_t lock_it = osMutexNew(&sens_lock_attr);

		if ( NULL != lock_it)
		{
			p_sens_lock[sindx] = lock_it;
		}
		else
		{
			EXEH_HANDLE(eEXEHSeverity_Error, (int32_t)SDS_Exception_OS_Mutex_Spawn_Error);
		}
	}
}

#if SDS_PIN_DBG
/** @brief Pin output state change for debug purposes */
STATIC void fs_dbg_out_pin_on(uint32_t event_id, sensor_data_sensors_t sensor_type)
{
//	if ( (SDS_THREAD_FLAGS_MTM == event_id) && (SENSOR_MAG_PRIMARY == sensor_type) )
//	{
//		HAL_GPIO_WritePin(OBC_OUT1_GPIO_Port, OBC_OUT1_Pin, GPIO_PIN_SET);
//	}

	if ( (SDS_THREAD_FLAGS_MTM == event_id) && (SENSOR_MAG_SECONDARY == sensor_type) )
	{
		HAL_GPIO_WritePin(OBC_OUT2_GPIO_Port, OBC_OUT2_Pin, GPIO_PIN_SET);
	}

	if ( SDS_THREAD_FLAGS_GYRO == event_id )
	{
		HAL_GPIO_WritePin(OBC_OUT8_GPIO_Port, OBC_OUT8_Pin, GPIO_PIN_SET);
	}

	if ( SDS_THREAD_FLAGS_CSS == event_id )
	{
		HAL_GPIO_WritePin(OBC_OUT7_GPIO_Port, OBC_OUT7_Pin, GPIO_PIN_SET);
	}

	if ( (SDS_THREAD_FLAGS_ACC == event_id ) && (SENSOR_ACC_PRIMARY == sensor_type) )
	{
		HAL_GPIO_WritePin(OBC_OUT3_GPIO_Port, OBC_OUT3_Pin, GPIO_PIN_SET);
	}

	if ( (SDS_THREAD_FLAGS_ACC == event_id ) && (SENSOR_ACC_SECONDARY == sensor_type) )
	{
		HAL_GPIO_WritePin(OBC_OUT5_GPIO_Port, OBC_OUT5_Pin, GPIO_PIN_SET);
	}

//	if ( SDS_THREAD_FLAGS_TEMP == event_id )
//	{
//		HAL_GPIO_WritePin(OBC_OUT8_GPIO_Port, OBC_OUT8_Pin, GPIO_PIN_SET);
//	}

	if ( SDS_THREAD_FLAGS_GYRO_TEMP == event_id )
	{
		HAL_GPIO_WritePin(OBC_OUT1_GPIO_Port, OBC_OUT1_Pin, GPIO_PIN_SET);
	}
}

/** @brief Pin output state change to OFF for debug purposes */
STATIC void fs_dbg_out_pin_off(uint32_t event_id, sensor_data_sensors_t sensor_type)
{
//	if ( (SDS_THREAD_FLAGS_MTM == event_id) && (SENSOR_MAG_PRIMARY == sensor_type) )
//	{
//		HAL_GPIO_WritePin(OBC_OUT1_GPIO_Port, OBC_OUT1_Pin, GPIO_PIN_RESET);
//	}

	if ( (SDS_THREAD_FLAGS_MTM == event_id) && (SENSOR_MAG_SECONDARY == sensor_type) )
	{
		HAL_GPIO_WritePin(OBC_OUT2_GPIO_Port, OBC_OUT2_Pin, GPIO_PIN_RESET);
	}

	if ( SDS_THREAD_FLAGS_GYRO == event_id )
	{
		HAL_GPIO_WritePin(OBC_OUT8_GPIO_Port, OBC_OUT8_Pin, GPIO_PIN_RESET);
	}

	if ( SDS_THREAD_FLAGS_CSS == event_id )
	{
		HAL_GPIO_WritePin(OBC_OUT7_GPIO_Port, OBC_OUT7_Pin, GPIO_PIN_RESET);
	}

	if ( (SDS_THREAD_FLAGS_ACC == event_id ) && (SENSOR_ACC_PRIMARY == sensor_type) )
	{
		HAL_GPIO_WritePin(OBC_OUT3_GPIO_Port, OBC_OUT3_Pin, GPIO_PIN_RESET);
	}

	if ( (SDS_THREAD_FLAGS_ACC == event_id ) && (SENSOR_ACC_SECONDARY == sensor_type) )
	{
		HAL_GPIO_WritePin(OBC_OUT5_GPIO_Port, OBC_OUT5_Pin, GPIO_PIN_RESET);
	}

//	if ( SDS_THREAD_FLAGS_TEMP == event_id )
//	{
//		HAL_GPIO_WritePin(OBC_OUT8_GPIO_Port, OBC_OUT8_Pin, GPIO_PIN_RESET);
//	}

	if ( SDS_THREAD_FLAGS_GYRO_TEMP == event_id )
	{
		HAL_GPIO_WritePin(OBC_OUT1_GPIO_Port, OBC_OUT1_Pin, GPIO_PIN_RESET);
	}
}
#endif /* SDS_PIN_DBG */

/* ******************************************************************************************* */
