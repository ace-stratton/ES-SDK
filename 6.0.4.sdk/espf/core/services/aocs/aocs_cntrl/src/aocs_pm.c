/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup aocs_pm
 * @{
 *
 * @file     aocs_pm.c
 * @brief    Attitude performance monitor
 *
 * @}
 */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "aocs_pm.h"
#include "trace.h"
#include "es_exeh.h"
#include "SdMngr.h"
#include "assertions.h"
#include <stdio.h>

/** @brief Module ID used for this file to report error events in EXEH */
#define EXEH_CURRENT_MODULE_ID  (eEXEHModuleID_AOCS_PM)

/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/
#define TEST_ENABLED 0


/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/



/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/
/** @brief Main counters structure to be used by the algorithm */
STATIC aocs_pm_counters_t s_aocs_pm_cnt = {0x00000000,0x00000000, 0x0000000,0x0000,false,false};

/** @brief Configuration of the algorithm */
STATIC aocs_pm_parameters_t s_aocs_pm_params;

/** @brief Context of each value to be logged  */
STATIC aocs_pm_ctx_t s_aocs_pm_ctx[NUM_OF_VALUES_TO_EVALUATE];

/** @brief This is how the file in wich we log is called  */
STATIC const char c_aocs_pm_file_name[11] = {"AOCS_PM.TXT"};

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/
#if TEST_ENABLED
#else
STATIC void 	fs_aocs_pm_manage_offset(aocs_cntrl_offset_t* offset,aocs_cntrl_res_t aocs_data_status);
STATIC void 	fs_aocs_update_att_buff(aocs_pm_ctx_t* context, int32_t input_data, aocs_cntrl_res_t data_status);
STATIC uint8_t 	fs_aocs_pm_assess_stability(aocs_pm_ctx_t* context);
#endif
/*
*********************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

void aocs_pm_init(void)
{
    EXEH_INIT_MODULE_FILENAME();
	//get threshold configuration from nvm
	for(int i = 0; i < NUM_OF_VALUES_TO_EVALUATE; i++)
	{
		memset(&s_aocs_pm_ctx[i], 0x00, sizeof(aocs_pm_ctx_t));
		aocs_pm_get_threshold_from_nvm(&s_aocs_pm_ctx[i].s_threshold_values, i);
	}
	queue_init(&s_aocs_pm_ctx[0].s_circ_buf, &s_aocs_pm_ctx[0].a_circ_buf[0],(tQueueSize) SIZE_OF_CIRC_BUF);
	queue_init(&s_aocs_pm_ctx[1].s_circ_buf, &s_aocs_pm_ctx[1].a_circ_buf[0],(tQueueSize) SIZE_OF_CIRC_BUF);
	queue_init(&s_aocs_pm_ctx[2].s_circ_buf, &s_aocs_pm_ctx[2].a_circ_buf[0],(tQueueSize) SIZE_OF_CIRC_BUF);

	//get update interval from nvm
	aocs_pm_get_config_form_nvm(&s_aocs_pm_params);
}

void aocs_pm_calc_performance(aocs_cntrl_log_data_t* get_data_to_pass_to_pm_algorythm, aocs_cntrl_offset_t* aocs_pm_detect_offset_change, aocs_cntrl_res_t data_status )
{
	static char c_write_data_buff [SIZE_OF_ARRAY_HEADER]; // buffer to write to file
	datetime_stamp_t time_stamp;		 // structure to read the rtc data in
	unix_time_t unix_time_stamp;		 // structure to write unix time stamp in the log file
	static FIL f_file_handler;			 // file handler for the log file
	static FRESULT res = FR_OK;			 // result from the file operations
	static uint32_t u32_bytes_written;	 // variable for checking how many bytes we wrote
	static uint8_t u8_counter_pm = 0;	 // counter that increment each second, it used to know when to start the logic for the algorithm
	FILINFO fno;						 // file info structure
	UINT size = 0;						 // size for how many bytes to write
	uint32_t u32_current_tick_count;	 // variable to get the current systick

	CRIT_ASSERT(NULL != get_data_to_pass_to_pm_algorythm);

	CRIT_ASSERT(NULL != aocs_pm_detect_offset_change);

	/* Detect offset change or broken data from the datacache */
	fs_aocs_pm_manage_offset(aocs_pm_detect_offset_change,data_status);

	u8_counter_pm++;
	if( u8_counter_pm >= s_aocs_pm_params.u8_update_interval )
	{
		/* Get the current tick count */
		u32_current_tick_count = osKernelGetTickCount();

		/* Calculate how much time is passed from the last sample */
		s_aocs_pm_cnt.d_t = u32_current_tick_count - s_aocs_pm_cnt.d_t_last;

		/* Convert to seconds */
		s_aocs_pm_cnt.d_t_in_sec = (float)s_aocs_pm_cnt.d_t * CONVERSION_CONST_FROMMS_TO_SEC;

		/* Keep the current sys tick for next time */
		s_aocs_pm_cnt.d_t_last = u32_current_tick_count;

		/* The first compare is for the normal logging that is activated from fp command,
		 * the second compare is for the auto logging functionality */
		if((s_aocs_pm_cnt.u32_time_passed_since_logging_sec < s_aocs_pm_cnt.u32_time_for_logging_in_sec) ||
			(false != s_aocs_pm_cnt.b_auto_logging_enabled))
		{
			/* Get the file status of the log file to check if it exist */
			res = SdMngr_f_stat((TCHAR*)&c_aocs_pm_file_name, &fno);

			/* Write  header if the file does not exist */
			if(FR_NO_FILE == res)
			{
				snprintf(c_write_data_buff, sizeof(c_write_data_buff), "date, time, dt,short term metric, data, long term metric, enc history, offset, stable time,"
						"short term metric, data, long term metric, enc history, offset, stable time,"
						"short term metric, data, long term metric, enc history, offset, stable time \r\n");
				res = SdMngr_f_open(&f_file_handler, c_aocs_pm_file_name, FA_WRITE | FA_OPEN_EXISTING | FA_OPEN_APPEND);

				size = strlen(c_write_data_buff);

				if(FR_OK == res )
				{
					res = SdMngr_f_write(&f_file_handler, c_write_data_buff, size, (UINT*) &u32_bytes_written);
					if(FR_OK != res)
					{
			            EXEH_HANDLE(eEXEHSeverity_Warning, eEXEH_AOCS_PM_FAILED_TO_WRITE_TO_FILE);
					}
					SdMngr_f_close(&f_file_handler);
				}
				else
				{
					EXEH_HANDLE(eEXEHSeverity_Warning, eEXEH_AOCS_PM_FAILED_TO_OPEN_FILE);
				}
				memset(c_write_data_buff,0x00,sizeof(c_write_data_buff));
				size = 0;
			}

			/* Get date and time for time stamp */
			datetime_now(&time_stamp);

			/* If There is something wrong with the time stamp log error*/
			if( 0 == time_stamp.date.year )
			{
				EXEH_HANDLE(eEXEHSeverity_Warning, eEXEH_AOCS_PM_FAILED_TO_GET_TIME_STAMP);
			}

			unix_time_stamp = datetime_to_unix(&time_stamp);
			/* Put the data in a buffer to write */
			snprintf(c_write_data_buff, sizeof(c_write_data_buff), "%lu, %.2f,",
					(uint32_t) unix_time_stamp,
					s_aocs_pm_cnt.d_t_in_sec);

			size = strlen(c_write_data_buff);

			/* Write data to the file */
			res = SdMngr_f_open(&f_file_handler, c_aocs_pm_file_name, FA_WRITE | FA_OPEN_EXISTING | FA_OPEN_APPEND);

			if(FR_OK == res )
			{
				res = SdMngr_f_write(&f_file_handler, c_write_data_buff, size, (UINT*) &u32_bytes_written);

				if(FR_OK != res)
				{
		            EXEH_HANDLE(eEXEHSeverity_Warning, eEXEH_AOCS_PM_FAILED_TO_WRITE_TO_FILE);
				}

				SdMngr_f_close(&f_file_handler);
			}
			else
			{
				EXEH_HANDLE(eEXEHSeverity_Warning, eEXEH_AOCS_PM_FAILED_TO_OPEN_FILE);
			}
		}

		/* Calculate data */
		fs_aocs_update_att_buff(&s_aocs_pm_ctx[0], (int32_t)get_data_to_pass_to_pm_algorythm->value1, data_status);
		fs_aocs_update_att_buff(&s_aocs_pm_ctx[1], (int32_t)get_data_to_pass_to_pm_algorythm->value2, data_status);
		fs_aocs_update_att_buff(&s_aocs_pm_ctx[2], (int32_t)get_data_to_pass_to_pm_algorythm->value3, data_status);

		if((s_aocs_pm_cnt.u32_time_passed_since_logging_sec < s_aocs_pm_cnt.u32_time_for_logging_in_sec) ||
			(false != s_aocs_pm_cnt.b_auto_logging_enabled))
		{
			/* Keep track of how much time we have been logging */
			s_aocs_pm_cnt.u32_time_passed_since_logging_sec += s_aocs_pm_params.u8_update_interval;

			/* Clear the buffer before writing to it */
			memset(c_write_data_buff,0x00, sizeof(c_write_data_buff));

			/* Put the data in a buffer to write */
			snprintf(c_write_data_buff, sizeof(c_write_data_buff), "\r\n");

			/* Calculate the length of the buffer */
			size = strlen(c_write_data_buff);

			res = SdMngr_f_open(&f_file_handler, c_aocs_pm_file_name, FA_WRITE | FA_OPEN_EXISTING | FA_OPEN_APPEND);

			if(FR_OK == res )
			{
				res = SdMngr_f_write(&f_file_handler, c_write_data_buff, size, (UINT*) &u32_bytes_written);
				if(FR_OK != res)
				{
					EXEH_HANDLE(eEXEHSeverity_Warning, eEXEH_AOCS_PM_FAILED_TO_WRITE_TO_FILE);
				}
				SdMngr_f_close(&f_file_handler);
			}
			else
			{
				EXEH_HANDLE(eEXEHSeverity_Warning, eEXEH_AOCS_PM_FAILED_TO_OPEN_FILE);
			}
		}
		if((s_aocs_pm_cnt.u32_time_passed_since_logging_sec > s_aocs_pm_params.u32_max_time_for_auto_log ) &&
			( false == s_aocs_pm_cnt.b_max_autolog_reached ))
		{
			s_aocs_pm_cnt.b_max_autolog_reached = true;
		}
		u8_counter_pm = 0;
	}
}

void aocs_pm_reset(void)
{
	/* Clear the context variables */
	for(int i = 0; i < NUM_OF_VALUES_TO_EVALUATE; i++)
	{
		queue_flush(&s_aocs_pm_ctx[i].s_circ_buf);
		s_aocs_pm_ctx[i].s_output.u16_encoded_history = 0;
		s_aocs_pm_ctx[i].s_output.u8_stability_measure = 0;
		s_aocs_pm_ctx[i].data = 0;
		s_aocs_pm_ctx[i].u16_buffer_sum = 0;
		s_aocs_pm_ctx[i].u32_cnt_long_term_window = 0;
		s_aocs_pm_ctx[i].u32_cnt_uninterrupted_time = 0;
		s_aocs_pm_ctx[i].u32_number_of_samples_passed = 0;
		s_aocs_pm_ctx[i].u8_last_data = 0;
	}

	/* Clear the counters for the algorithms */
	s_aocs_pm_cnt.u16_skiped_samples = 0;
	s_aocs_pm_cnt.u32_time_for_logging_in_sec = 0;
	s_aocs_pm_cnt.u32_time_passed_since_logging_sec = 0;
	s_aocs_pm_cnt.b_auto_logging_enabled = 0;
	s_aocs_pm_cnt.u32_counter_for_max_logging = 0;
	s_aocs_pm_cnt.b_max_autolog_reached = 0;
}

uint32_t aocs_pm_get_max_time_for_auto_logging(void)
{
	/* Variables to store the data after we read it */
	aocs_pm_config_t s_read_from_nvm;

	/* Read from the NVM */
	Nvm_GetBlockById(NVM_BLOCK_AOCS_PM_CONFIG, &s_read_from_nvm);

	return s_read_from_nvm.parameters.u32_max_time_for_auto_log;
}

uint8_t aocs_pm_set_max_time_for_auto_logging(uint32_t u32_time)
{
	aocs_pm_config_t s_write_from_nvm; 	// Variables to store the data after we read it
	uint8_t res = 0;					// Result

	/* Get the data from the NVM */
	Nvm_GetBlockById(NVM_BLOCK_AOCS_PM_CONFIG, &s_write_from_nvm);

	/* Change the time variable */
	s_write_from_nvm.parameters.u32_max_time_for_auto_log = u32_time;

	/* Change the time variable in the local variables */
	s_aocs_pm_params.u32_max_time_for_auto_log = u32_time;

	/* Set the data with new changes to the NVM */
	Nvm_SetBlockById(NVM_BLOCK_AOCS_PM_CONFIG, &s_write_from_nvm,NVMSETBLOCK_STORE_IMMEDIATELY);

	/* Set the structure to 0 to read the structure again to make sure it is set*/
	memset(&s_write_from_nvm, 0x00, sizeof(aocs_pm_config_t));

	/* Get the data from the NVM again */
	Nvm_GetBlockById(NVM_BLOCK_AOCS_PM_CONFIG, &s_write_from_nvm);

	/* Compare the data with the new variable */
	if(s_write_from_nvm.parameters.u32_max_time_for_auto_log == u32_time)
	{
		res = 0;
	}
	else
	{
		res = 1;
	}

	return res;
}


void aocs_pm_start_auto_logging(void)
{
	if(false == s_aocs_pm_cnt.b_max_autolog_reached )
	{
		/* We enter this if only if we didn't reach the max log time */
		s_aocs_pm_cnt.b_auto_logging_enabled = true;
		/* This is because we don't want the normal logging to work only the auto log */
		s_aocs_pm_cnt.u32_time_for_logging_in_sec = 0;
		s_aocs_pm_cnt.u32_time_passed_since_logging_sec = 0;
	}
	else
	{
		/* If we did reach the max log time we set the counters to 0 and stop the enable for logging */
		s_aocs_pm_cnt.b_auto_logging_enabled = false;
	}
}

void aocs_pm_stop_auto_logging(void)
{
	s_aocs_pm_cnt.b_auto_logging_enabled = 0;
	s_aocs_pm_cnt.b_max_autolog_reached = 0;
}

void aocs_pm_start_logging(uint32_t u32_time)
{
	s_aocs_pm_cnt.u32_time_for_logging_in_sec = u32_time;
	s_aocs_pm_cnt.u32_time_passed_since_logging_sec = 0;
}


aocs_log_data_types_t aocs_pm_get_data_type_for_assessment(void)
{
	return s_aocs_pm_params.data_type;
}


uint8_t aocs_pm_set_data_type_for_assessment(aocs_log_data_types_t data)
{
	aocs_pm_parameters_t data_for_nvm;

	Nvm_GetBlockById(NVM_BLOCK_AOCS_PM_CONFIG, &data_for_nvm);

	/* Change the current data */
	s_aocs_pm_params.data_type = data;

	data_for_nvm.data_type = data;

	/* Write new data to NVM*/
	Nvm_SetBlockById(NVM_BLOCK_AOCS_PM_CONFIG, &data_for_nvm, NVMSETBLOCK_STORE_IMMEDIATELY);

	/* Reset all buffers so we don't get wrong conclusions */
	aocs_pm_reset();

	Nvm_GetBlockById(NVM_BLOCK_AOCS_PM_CONFIG, &data_for_nvm);
	if(data_for_nvm.data_type == data)
	{
		return 0; // success
	}
	else
	{
		return 1; //error
	}
}

uint8_t aocs_pm_get_update_interval(void)
{
	return s_aocs_pm_params.u8_update_interval;
}


uint8_t aocs_pm_set_update_interval(uint8_t data)
{
	aocs_pm_parameters_t data_for_nvm;

	Nvm_GetBlockById(NVM_BLOCK_AOCS_PM_CONFIG, &data_for_nvm);

	/* Change the current data */
	s_aocs_pm_params.u8_update_interval = data;

	data_for_nvm.u8_update_interval = data;

	/* Write new data to NVM*/
	Nvm_SetBlockById(NVM_BLOCK_AOCS_PM_CONFIG, &data_for_nvm, NVMSETBLOCK_STORE_IMMEDIATELY);

	/* Reset all buffers so we don't get wrong conclusions */
	aocs_pm_reset();

	Nvm_GetBlockById(NVM_BLOCK_AOCS_PM_CONFIG, &data_for_nvm);

	if(data_for_nvm.u8_update_interval == data)
	{
		return 0; // success
	}
	else
	{
		return 1; //error
	}

}

uint16_t aocs_pm_get_samples_to_skip(void)
{
	return s_aocs_pm_params.u16_samples_to_skip;
}

uint8_t aocs_pm_set_samples_to_skip(uint16_t data)
{
	aocs_pm_parameters_t data_for_nvm;

	if( MAX_SAMPLES_TO_SKIP == data )
	{
		return 1;
	}

	Nvm_GetBlockById(NVM_BLOCK_AOCS_PM_CONFIG, &data_for_nvm);

	/* Change the current data */
	s_aocs_pm_params.u16_samples_to_skip = data;

	data_for_nvm.u16_samples_to_skip = data;

	/* Write new data to NVM*/
	Nvm_SetBlockById(NVM_BLOCK_AOCS_PM_CONFIG, &data_for_nvm, NVMSETBLOCK_STORE_IMMEDIATELY);

	Nvm_GetBlockById(NVM_BLOCK_AOCS_PM_CONFIG, &data_for_nvm);

	if(data_for_nvm.u16_samples_to_skip == data)
	{
		return 0; // success
	}
	else
	{
		return 1; //error
	}

}

void aocs_pm_get_config_form_nvm(aocs_pm_parameters_t* config)
{
	aocs_pm_config_t config_nvm;
	Nvm_GetBlockById(NVM_BLOCK_AOCS_PM_CONFIG, &config_nvm);

	CRIT_ASSERT(NULL != config);

	config->u32_max_time_for_auto_log = config_nvm.parameters.u32_max_time_for_auto_log;
	config->u8_update_interval = config_nvm.parameters.u8_update_interval;
	config->data_type = config_nvm.parameters.data_type;
	config->u16_samples_to_skip = config_nvm.parameters.u16_samples_to_skip;
}


uint8_t aocs_pm_set_config_to_nvm(aocs_pm_parameters_t* config)
{
	aocs_pm_config_t config_nvm;
	uint8_t res;

	CRIT_ASSERT(NULL != config);

	if( MAX_SAMPLES_TO_SKIP == config->u16_samples_to_skip )
	{
		return 1;
	}

	config_nvm.parameters.data_type = config->data_type;
	config_nvm.parameters.u16_samples_to_skip = config->u16_samples_to_skip;
	config_nvm.parameters.u32_max_time_for_auto_log = config->u32_max_time_for_auto_log;
	config_nvm.parameters.u8_update_interval = config->u8_update_interval;
	Nvm_SetBlockById(NVM_BLOCK_AOCS_PM_CONFIG, &config_nvm, NVMSETBLOCK_STORE_IMMEDIATELY);

	s_aocs_pm_params.data_type = config->data_type;
	s_aocs_pm_params.u16_samples_to_skip = config->u16_samples_to_skip;
	s_aocs_pm_params.u32_max_time_for_auto_log = config->u32_max_time_for_auto_log;
	s_aocs_pm_params.u8_update_interval = config->u8_update_interval;

	Nvm_GetBlockById(NVM_BLOCK_AOCS_PM_CONFIG, &config_nvm);

	if(memcmp(&config_nvm,config,sizeof(aocs_pm_parameters_t)))
	{
		res = 1;
	}
	else
	{
		res = 0;
	}

	return res;
}


void aocs_pm_get_threshold(aocs_pm_threshold_values_t* values, aocs_pm_value_id_t id)
{
	CRIT_ASSERT(id < NUM_OF_VALUES_TO_EVALUATE);

	CRIT_ASSERT(NULL != values);

	values->f_safety_factor = s_aocs_pm_ctx[id].s_threshold_values.f_safety_factor;
	values->f_tolerance = s_aocs_pm_ctx[id].s_threshold_values.f_tolerance;
}

void aocs_pm_get_threshold_from_nvm(aocs_pm_threshold_values_t* f_values, aocs_pm_value_id_t id)
{
	/* Structure to put data from the NVM */
	aocs_pm_thresholds_t th_values;

	CRIT_ASSERT(NULL != f_values);

	CRIT_ASSERT(id < NUM_OF_VALUES_TO_EVALUATE);

	/* Get the data from the NVM */
	Nvm_GetBlockById(NVM_BLOCK_AOCS_PM_THRESHOLDS, &th_values);

	f_values->f_safety_factor = th_values.value[id].f_safety_factor ;
	f_values->f_tolerance = th_values.value[id].f_tolerance ;
}


uint8_t aocs_pm_set_thresholds_to_nvm(aocs_pm_threshold_values_t* values, aocs_pm_value_id_t id)
{
	aocs_pm_thresholds_t dummy_data;
	uint8_t res = 0;

	CRIT_ASSERT(NULL != values);

	CRIT_ASSERT(id < NUM_OF_VALUES_TO_EVALUATE);

	/* First set the local values */
	memcpy(&s_aocs_pm_ctx[id].s_threshold_values,values,sizeof(aocs_pm_threshold_values_t));

	/* Get the whole structure from the NVM */
	Nvm_GetBlockById(NVM_BLOCK_AOCS_PM_THRESHOLDS, &dummy_data);

	/* Write only the id we want */
	dummy_data.value[id].f_safety_factor = values->f_safety_factor;
	dummy_data.value[id].f_tolerance = values->f_tolerance;

	/* Set new data */
	Nvm_SetBlockById(NVM_BLOCK_AOCS_PM_THRESHOLDS, &dummy_data, NVMSETBLOCK_STORE_IMMEDIATELY);

	/* Get the whole structure from the NVM */
	Nvm_GetBlockById(NVM_BLOCK_AOCS_PM_THRESHOLDS, &dummy_data);

	if(memcmp(&dummy_data.value[id],values,sizeof(aocs_pm_threshold_values_t)))
	{
		res = 1;
	}
	else
	{
		res = 0;
	}

	return res;
}

void aocs_pm_get_output(aocs_pm_output_t* output, uint8_t id)
{
	CRIT_ASSERT(id < NUM_OF_VALUES_TO_EVALUATE);

	CRIT_ASSERT(NULL != output);

	output->u8_stability_measure = s_aocs_pm_ctx[id].s_output.u8_stability_measure;
	output->u16_encoded_history = s_aocs_pm_ctx[id].s_output.u16_encoded_history;
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/** @brief Responsible for detecting offset change and extrapolating if there is a problem
 * with the datacache read
 *  @param[in] aocs_cntrl_offset_t* offset - buffer with the values for the offset
 *  @param[in] ,aocs_cntrl_res_t aocs_data_status - status of the data cache read */
STATIC void fs_aocs_pm_manage_offset(aocs_cntrl_offset_t* offset, aocs_cntrl_res_t aocs_data_status)
{

	CRIT_ASSERT(NULL != offset);

	if( AOCS_CNTRL_FAILED == aocs_data_status )
	{
		/* If something failed take the old offset value */
		for(int i = 0; i < NUM_OF_VALUES_TO_EVALUATE; i++)
		{
			s_aocs_pm_ctx[i].f_offset = s_aocs_pm_ctx[i].f_old_offset;
		}
//		ES_TRACE_DEBUG("[AOCS_PM] bad data for offset manager\r\n");
		EXEH_HANDLE(eEXEHSeverity_Warning, eEXEH_AOCS_PM_RECEIVED_BAD_DATA);
	}
	else
	{
		for(int i = 0; i < NUM_OF_VALUES_TO_EVALUATE; i++)
		{
			s_aocs_pm_ctx[i].f_offset = (float) offset->offset_value[i] * CONVERSION_CONST_UNITS_TO_MUNITS;

			/* Compare if the new offset is changed with the old offset */
			if(fabs(s_aocs_pm_ctx[i].f_old_offset - s_aocs_pm_ctx[i].f_offset) > PECISION_FOR_FLOAT_COMPARE)
			{
				/* We multiply by NUM_OF_VALUES_TO_EVALUATE because each axis subtracts one */
				s_aocs_pm_cnt.u16_skiped_samples = s_aocs_pm_params.u16_samples_to_skip * NUM_OF_VALUES_TO_EVALUATE;
			}
			s_aocs_pm_ctx[i].f_old_offset = s_aocs_pm_ctx[i].f_offset;
		}
	}
}

/** @brief Responsible for properly updating and managing the buffer
 *  @param[in] aocs_pm_ctx_t* context - context for each value for assessment
 *  @param[in] int32_t input_data - data that is going to be assessed needs to be in [mili]
 *  @param[in] aocs_cntrl_res_t data_status - status of the data cache read, this is important because
 *  if the data is invalid the algorithm is extrapolating.
 *  */
STATIC void fs_aocs_update_att_buff(aocs_pm_ctx_t* context, int32_t input_data, aocs_cntrl_res_t data_status)
{
	static uint8_t u8_last_data;							/* Variable to store old data */
	static FIL f_file_handler;								/* File handler */
	static FRESULT res = FR_OK;								/* File operations result */
	static uint32_t u32_bytes_written;						/* Variable to store how many bytes we wrote to file */
	static char c_write_data_buff [AOCS_UPDATE_BUFFER_SIZE];/* Buffer to write to file */
	UINT size = 0;											/* Size to write to file */
	float temp;												/* Temporary float value used to aid calculation */
	static uint8_t u8_assessed_data; 						/* Values to store the assessed data */
	bool b_valid_data_is_present = 0;						/* Indicates that we have a full buffer */

	CRIT_ASSERT(NULL != context);

	/* Keep statistics of how much samples have passed */
	context->u32_number_of_samples_passed++;

	/* Convert data to normal value */
	context->data = (float)input_data * CONVERSION_CONST_UNITS_TO_MUNITS;

	/* If bad data is received extrapolate previous sample */
	if((AOCS_CNTRL_FAILED == data_status))
	{
		if(s_aocs_pm_cnt.u16_skiped_samples > 0)
		{
			s_aocs_pm_cnt.u16_skiped_samples--;
		}

		u8_assessed_data = context->u8_last_data;

		if(AOCS_CNTRL_FAILED == data_status)
		{
			context->data = MAGIC_NUMBER_FOR_INCORRECT_DATA;			// This is done so we can debug what failed
		}

//		ES_TRACE_DEBUG("[aocs_pm] aocs_update_att_buff received bad data\r\n");

		EXEH_HANDLE(eEXEHSeverity_Warning, eEXEH_AOCS_PM_RECEIVED_BAD_DATA);
	}
	else
	{
		if(s_aocs_pm_cnt.u16_skiped_samples > 0)
		{
			s_aocs_pm_cnt.u16_skiped_samples--;
			u8_assessed_data = context->u8_last_data;
		}else
		{
			/* Call the function to assess the data that we just gathered from the data cache */
			u8_assessed_data = fs_aocs_pm_assess_stability(context);
		}
	}

	if(true == u8_assessed_data)
	{
		context->u32_cnt_uninterrupted_time += s_aocs_pm_params.u8_update_interval;
	}
	else{
//		ES__DEBUG("[aocs_pm] AOCS is not stable\r\n");
		context->u32_cnt_uninterrupted_time = 0;
	}
	/* If the buffer is full that means we have data for the entire stability window that we want */
	if((uint32_t)(LONG_TERM_WINDOW / s_aocs_pm_params.u8_update_interval) < queue_data_len(&context->s_circ_buf))
	{
		/* We have valid data now */
		b_valid_data_is_present = true;

		/* Get the head byte to free up space for the next one */
		u8_last_data = queue_get(&context->s_circ_buf);

		/* Remove the oldest assessed data from the sum */
		context->u16_buffer_sum -= u8_last_data;
	}
	if((u8_assessed_data) && (CONTACT_TIME_IN_SECONDS < context->u32_cnt_uninterrupted_time))
	{
		/* Put new data in the circular buffer */
		queue_put(&context->s_circ_buf, (const tQueueData) u8_assessed_data);
	}
	else{
		context->u8_last_data = u8_assessed_data;
		u8_assessed_data = 0;
		/* Put new data in the circular buffer */
		queue_put(&context->s_circ_buf,(const tQueueData) u8_assessed_data);
	}

	/* Add new assessed data to the entire sum */
	context->u16_buffer_sum += u8_assessed_data;

	if( true == b_valid_data_is_present )
	{
		/* Calculate stability measure here so at every point in time we have the performance stats calculated.
		 * Divide the sum of the buffer by the length of the buffer and convert integer in percent */
		temp = ((float)context->u16_buffer_sum / ((float)LONG_TERM_WINDOW / (float)s_aocs_pm_params.u8_update_interval)) * CONVERSION_TO_PROCENTAGE_CONSTANT;

		context->s_output.u8_stability_measure = (uint8_t) temp;

		/* u8_stability_measure is percentage so if it is above 100 there was something left in the buffer */
		if( context->s_output.u8_stability_measure > 100 )
		{
			EXEH_HANDLE(eEXEHSeverity_Warning, eEXEH_AOCS_PM_LONG_TERM_MEASURE_TOO_BIG);
			aocs_pm_reset();
		}
	}else{
		/* Have a number before we reach the 1.5 orbit data points */
		temp = (((float)context->u16_buffer_sum / (float)context->u32_number_of_samples_passed)) * CONVERSION_TO_PROCENTAGE_CONSTANT;
		context->s_output.u8_stability_measure = (uint8_t) temp;

		/* u8_stability_measure is percentage so if it is above 100 there was something left in the buffer */
		if( context->s_output.u8_stability_measure > MAXIMUM_PERCENTS )
		{
			EXEH_HANDLE(eEXEHSeverity_Warning, eEXEH_AOCS_PM_LONG_TERM_MEASURE_TOO_BIG);
			aocs_pm_reset();
		}
	}
	/* Calculate long term stability */
	context->u32_cnt_long_term_window += s_aocs_pm_params.u8_update_interval;

	if( context->u32_cnt_long_term_window > CONTACT_TIME_IN_SECONDS )
	{
//		ES_TRACE_DEBUG("[aocs_pm] Contact time reset\r\n");

		/* Shift all the bits left for the new assessment b0001 -> b001[0 -> new assessment] */
		/* Set or clear the newly imported bit based on the assessment */
		context->s_output.u16_encoded_history = (context->s_output.u16_encoded_history << 1) | (u8_assessed_data & 1);

		/* Clear the counter to start counting for the next window */
		context->u32_cnt_long_term_window = 0;
	}

	if((s_aocs_pm_cnt.u32_time_passed_since_logging_sec < s_aocs_pm_cnt.u32_time_for_logging_in_sec) ||
				(false != s_aocs_pm_cnt.b_auto_logging_enabled))
	{
		/* Clear the buffer before writing to it */
		memset(c_write_data_buff,0x00, sizeof(c_write_data_buff));

		/* The time stamp will be written beforehand
		 * Data format for the file is [data after assessment] [raw data] [stability measure in %] [encoded history] */
		snprintf(c_write_data_buff, sizeof(c_write_data_buff), " %d, %.2f, %d, %d, %.2f, %d,",
				(int)u8_assessed_data,
				context->data,
				(int)context->s_output.u8_stability_measure,
				(int)context->s_output.u16_encoded_history,
				context->f_offset,
				(int)context->u32_cnt_uninterrupted_time);

		res = SdMngr_f_open(&f_file_handler, c_aocs_pm_file_name, FA_WRITE | FA_OPEN_EXISTING | FA_OPEN_APPEND);

		/* Calculate the length of the buffer */
		size = strlen(c_write_data_buff);

		if(FR_OK == res )
		{
			res = SdMngr_f_write(&f_file_handler, c_write_data_buff, size, (UINT*) &u32_bytes_written);
			if(FR_OK != res)
			{
	            EXEH_HANDLE(eEXEHSeverity_Warning, eEXEH_AOCS_PM_FAILED_TO_WRITE_TO_FILE);
			}
			SdMngr_f_close(&f_file_handler);
		}
		else
		{
			EXEH_HANDLE(eEXEHSeverity_Warning, eEXEH_AOCS_PM_FAILED_TO_OPEN_FILE);
		}
	}

}

/** @brief Assesses the the data and manages the safety factor and threshold values
 *  @param[in] aocs_pm_ctx_t* ctx - context for each value for assessment
 *  @param[in] int32_t input_data - data that is going to be assessed needs to be in [mili]*/
STATIC uint8_t fs_aocs_pm_assess_stability(aocs_pm_ctx_t* ctx)
{
	static uint8_t result;

	CRIT_ASSERT(NULL != ctx);

	/* Determine in what range does the value falls and save it for next time, this way we make hysteresis */
	/* Set threshold safety factor based on the previous threshold condition */
	if(ctx->data >= ctx->f_offset + (ctx->f_upper_threshold * ctx->s_threshold_values.f_tolerance))
	{
		ctx->f_upper_threshold = 1 - ctx->s_threshold_values.f_safety_factor;
		ctx->f_lower_threshold = 1 - ctx->s_threshold_values.f_safety_factor;
	}
	else if((ctx->data <= ctx->f_offset + (ctx->f_upper_threshold * ctx->s_threshold_values.f_tolerance))&&
			(ctx->data >= ctx->f_offset - (ctx->f_lower_threshold * ctx->s_threshold_values.f_tolerance)))
	{
		ctx->f_lower_threshold = 1 + ctx->s_threshold_values.f_safety_factor;
		ctx->f_upper_threshold = 1 + ctx->s_threshold_values.f_safety_factor;
	}
	else if((ctx->data <= ctx->f_offset - (ctx->f_lower_threshold * ctx->s_threshold_values.f_tolerance)))
	{
		ctx->f_lower_threshold = 1 - ctx->s_threshold_values.f_safety_factor;
		ctx->f_upper_threshold = 1 + ctx->s_threshold_values.f_safety_factor;
	}

	/* Assess sample with the thresholds calculated above */
	if((ctx->data >= ctx->f_offset - (ctx->f_lower_threshold * ctx->s_threshold_values.f_tolerance))&&
	   (ctx->data <= ctx->f_offset + (ctx->f_upper_threshold * ctx->s_threshold_values.f_tolerance)))
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}
/* ********************************************************************************************/
