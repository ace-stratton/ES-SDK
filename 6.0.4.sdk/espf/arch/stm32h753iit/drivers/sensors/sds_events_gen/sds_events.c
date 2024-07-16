/*!
********************************************************************************************
* @file sds_events.c
* @brief Sensor Data Service events generation
********************************************************************************************
* @copyright         (C) Copyright Endurosat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
********************************************************************************************
*/

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_tim.h"

#include "sds_events.h"
#include "sensor_data_service.h"

#include "assertions.h"

#include <string.h>

#include "fp/SDS/v0.3/SDS_server/FP_SDSProtocolTypes.h"

/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/
#define SDS_EVENTS_TIMER_TICK_FREQ (10000U)	//10kHz

#define SDS_FREQ_BASE_MULT	(100U)

#define SDS_CONV_FREQ_TO_TICK_CNT(x)	((uint16_t)((1U/(double)x)*(SDS_EVENTS_TIMER_TICK_FREQ - 1)))

/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/
static TIM_HandleTypeDef  htim3;
static TIM_OC_InitTypeDef htim3_oc_chan_1;
static TIM_OC_InitTypeDef htim3_oc_chan_2;
static TIM_OC_InitTypeDef htim3_oc_chan_3;
static TIM_OC_InitTypeDef htim3_oc_chan_4;

static TIM_MasterConfigTypeDef htim3_master_config;
static TIM_SlaveConfigTypeDef htim3_slave_config;

static TIM_HandleTypeDef  htim4;
static TIM_OC_InitTypeDef htim4_oc_chan_1;
static TIM_OC_InitTypeDef htim4_oc_chan_2;
static TIM_OC_InitTypeDef htim4_oc_chan_3;
static TIM_OC_InitTypeDef htim4_oc_chan_4;

static TIM_SlaveConfigTypeDef htim4_slave_config;

/** @brief Local stash of the requested frequencies */
static uint16_t sds_events_chan_freqs[SDS_SENSTYPE_MAX_CNT];
/** @brief Local stash of the events values */
static uint16_t sds_events_chan_events[SDS_SENSTYPE_MAX_CNT];

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

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/
STATIC void sds_events_delay_elapsed_cb(TIM_HandleTypeDef *htim);
STATIC bool sds_events_init_oc_chan(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *htim_oc_chan_cfg, uint32_t channel, uint16_t freq);
STATIC void sds_events_start_oc_chan_it(uint16_t freq, uint32_t channel, TIM_HandleTypeDef *htim);

/*
*********************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

void sds_init_events_timer(const sds_sens_read_freq_t *sds_events_cfg)
{
	CRIT_ASSERT(NULL != sds_events_cfg);

	RCC_ClkInitTypeDef clkconfig;

	uint32_t uwTimclock;
	uint32_t uwAPB1Prescaler;
	uint32_t uwPrescalerValue;
	uint32_t pFLatency;

	/* Start by de-initilising the timer */
	sds_deinit_events_timer();

	for (uint8_t f_num = 0; f_num < SDS_SENSTYPE_MAX_CNT; f_num++)
	{
		sds_events_chan_freqs[f_num] = sds_events_cfg->sens_cfg[f_num].freq_cfg > 0 ? SDS_CONV_FREQ_TO_TICK_CNT(sds_events_cfg->sens_cfg[f_num].freq_cfg): 0;
		sds_events_chan_events[f_num] = sds_events_cfg->sens_cfg[f_num].event_cfg;
	}

	/* Enable TIM3 and TIM4 clocks */
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_TIM4_CLK_ENABLE();

	/* Get clock configuration */
	HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);

	/* Get APB1 prescaler */
	uwAPB1Prescaler = clkconfig.APB1CLKDivider;

	/* Compute TIM3/4 clock */
	if (uwAPB1Prescaler == RCC_HCLK_DIV1)
	{
		uwTimclock = HAL_RCC_GetPCLK1Freq();
	}
	else
	{
		uwTimclock = 2UL * HAL_RCC_GetPCLK1Freq();
	}

	/* Compute the prescaler value to have TIM3/4 counter clock equal to 10kHz */
	uwPrescalerValue = ((uwTimclock / SDS_EVENTS_TIMER_TICK_FREQ) - 1U);

	/* Initialise TIM3 */
	htim3.Instance = TIM3;
	htim3.Init.Period = SDS_EVENTS_TIMER_TICK_FREQ - 1U;
	htim3.Init.Prescaler = uwPrescalerValue;
	htim3.Init.ClockDivision = 0U;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.AutoReloadPreload = 0U;
	htim3.Init.RepetitionCounter = 0U;

	/* Initialise TIM4 */
	htim4.Instance = TIM4;
	htim4.Init.Period = SDS_EVENTS_TIMER_TICK_FREQ - 1U;
	htim4.Init.Prescaler = uwPrescalerValue;
	htim4.Init.ClockDivision = 0U;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.AutoReloadPreload = 0U;
	htim4.Init.RepetitionCounter = 0U;

	if ( (HAL_OK != HAL_TIM_Base_Init(&htim3)) || (HAL_OK != HAL_TIM_Base_Init(&htim4)) )
	{
		Error_Handler();
	}

    /* Set priority levels */
    HAL_NVIC_SetPriority(TIM3_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);

    HAL_NVIC_SetPriority(TIM4_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);

    /* Initialise OC channels for TIM3 */
    if ( (true != sds_events_init_oc_chan(&htim3, &htim3_oc_chan_1, TIM_CHANNEL_1, sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_MTM])) ||
    	 (true != sds_events_init_oc_chan(&htim3, &htim3_oc_chan_2, TIM_CHANNEL_2, sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_GYRO])) ||
		 (true != sds_events_init_oc_chan(&htim3, &htim3_oc_chan_3, TIM_CHANNEL_3, sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_CSS])) ||
		 (true != sds_events_init_oc_chan(&htim3, &htim3_oc_chan_4, TIM_CHANNEL_4, sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_ACC])) )
    {
    	Error_Handler();
    }

    /* Initialise OC channels for TIM4 */
    if ( (true != sds_events_init_oc_chan(&htim4, &htim4_oc_chan_1, TIM_CHANNEL_1, sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_PANEL_TEMP])) ||
    	 (true != sds_events_init_oc_chan(&htim4, &htim4_oc_chan_2, TIM_CHANNEL_2, sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_GYRO_TEMP])) ||
		 (true != sds_events_init_oc_chan(&htim4, &htim4_oc_chan_3, TIM_CHANNEL_3, sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_RES_0])) ||
		 (true != sds_events_init_oc_chan(&htim4, &htim4_oc_chan_4, TIM_CHANNEL_4, sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_RES_1])) )
    {
    	Error_Handler();
    }

    if ( (HAL_OK != HAL_TIM_OC_Init(&htim3)) || (HAL_OK != HAL_TIM_OC_Init(&htim4)) )
    {
    	Error_Handler();
    }

    /* Register callback */
    if ( (HAL_OK != HAL_TIM_RegisterCallback(&htim3, HAL_TIM_OC_DELAY_ELAPSED_CB_ID, sds_events_delay_elapsed_cb)) ||
    		(HAL_OK != HAL_TIM_RegisterCallback(&htim4, HAL_TIM_OC_DELAY_ELAPSED_CB_ID, sds_events_delay_elapsed_cb)) )
    {
    	Error_Handler();
    }

    /* Configure TIM3 as master and TIM4 as slave */
    htim3_master_config.MasterOutputTrigger = TIM_TRGO_ENABLE;
    htim3_master_config.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;

    htim3_slave_config.InputTrigger = TIM_TS_TI1F_ED;
    htim3_slave_config.SlaveMode = TIM_SLAVEMODE_TRIGGER;

    htim4_slave_config.InputTrigger = TIM_TS_ITR2;
    htim4_slave_config.SlaveMode = TIM_SLAVEMODE_TRIGGER;

    if (	(HAL_OK != HAL_TIM_SlaveConfigSynchro(&htim3, &htim3_slave_config)) ||
    		(HAL_OK != HAL_TIMEx_MasterConfigSynchronization(&htim3, &htim3_master_config)) ||
			(HAL_OK != HAL_TIM_SlaveConfigSynchro(&htim4, &htim4_slave_config)) )
    {
    	Error_Handler();
    }

    /* We have a master-slave configuration with synchronisation and we want to start
     * the master from its internal interrupt. However Base_Start does a slave configuration check and
     * thus it will not be possible using the HAL library. Therefore we set the state of both timers to busy and
     * go for the enable of the master. The configuration follows  39.3.19 Timer Synchronization - Figure 452 */
    htim3.State = HAL_TIM_STATE_BUSY;
    htim4.State = HAL_TIM_STATE_BUSY;
    __HAL_TIM_ENABLE(&htim3);

    /* Start in interrupt mode */
    sds_events_start_oc_chan_it(sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_MTM], TIM_CHANNEL_1, &htim3);
    sds_events_start_oc_chan_it(sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_GYRO], TIM_CHANNEL_2, &htim3);
    sds_events_start_oc_chan_it(sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_CSS], TIM_CHANNEL_3, &htim3);
    sds_events_start_oc_chan_it(sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_ACC], TIM_CHANNEL_4, &htim3);

    sds_events_start_oc_chan_it(sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_PANEL_TEMP], TIM_CHANNEL_1, &htim4);
    sds_events_start_oc_chan_it(sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_GYRO_TEMP], TIM_CHANNEL_2, &htim4);
    sds_events_start_oc_chan_it(sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_RES_0], TIM_CHANNEL_3, &htim4);
    sds_events_start_oc_chan_it(sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_RES_1], TIM_CHANNEL_4, &htim4);

}

void sds_deinit_events_timer(void)
{
	if ( ( HAL_OK != HAL_TIM_Base_Stop(&htim3) ) ||
			( HAL_OK != HAL_TIM_Base_Stop(&htim4) ) )
	{
		Error_Handler();
	}

	if ( (HAL_OK != HAL_TIM_OC_Stop_IT(&htim3, TIM_CHANNEL_1)) ||
			(HAL_OK != HAL_TIM_OC_Stop_IT(&htim3, TIM_CHANNEL_2)) ||
			(HAL_OK != HAL_TIM_OC_Stop_IT(&htim3, TIM_CHANNEL_3)) ||
			(HAL_OK != HAL_TIM_OC_Stop_IT(&htim3, TIM_CHANNEL_4)) ||
			(HAL_OK != HAL_TIM_OC_DeInit(&htim3)) ||
			(HAL_OK != HAL_TIM_Base_DeInit(&htim3)))
	{
		Error_Handler();
	}

	if ( (HAL_OK != HAL_TIM_OC_Stop_IT(&htim4, TIM_CHANNEL_1)) ||
			(HAL_OK != HAL_TIM_OC_Stop_IT(&htim4, TIM_CHANNEL_2)) ||
			(HAL_OK != HAL_TIM_OC_Stop_IT(&htim4, TIM_CHANNEL_3)) ||
			(HAL_OK != HAL_TIM_OC_Stop_IT(&htim4, TIM_CHANNEL_4)) ||
			(HAL_OK != HAL_TIM_OC_DeInit(&htim4)) ||
			(HAL_OK != HAL_TIM_Base_DeInit(&htim4)))
	{
		Error_Handler();
	}
}

/** @brief Timer 3 IRQ */
void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim3);
}

/** @brief Timer 4 IRQ */
void TIM4_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim4);
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/** @brief Delay elapsed callback */
STATIC void sds_events_delay_elapsed_cb(TIM_HandleTypeDef* htim)
{
	uint32_t cmp_val;

	uint16_t freq_1;
	uint16_t freq_2;
	uint16_t freq_3;
	uint16_t freq_4;

	uint32_t flags_1;
	uint32_t flags_2;
	uint32_t flags_3;
	uint32_t flags_4;

	freq_1 = (&htim3 == htim) ? (sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_MTM]) : (sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_PANEL_TEMP]);
	freq_2 = (&htim3 == htim) ? (sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_GYRO]) : (sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_GYRO_TEMP]);
	freq_3 = (&htim3 == htim) ? (sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_CSS]) : (sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_RES_0]);
	freq_4 = (&htim3 == htim) ? (sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_ACC]) : (sds_events_chan_freqs[SDS_SENSTYPECFGNUM_SENS_RES_1]);

	flags_1 = (&htim3 == htim) ? (sds_events_chan_events[SDS_SENSTYPECFGNUM_SENS_MTM]) : (sds_events_chan_events[SDS_SENSTYPECFGNUM_SENS_PANEL_TEMP]);
	flags_2 = (&htim3 == htim) ? (sds_events_chan_events[SDS_SENSTYPECFGNUM_SENS_GYRO]) : (sds_events_chan_events[SDS_SENSTYPECFGNUM_SENS_GYRO_TEMP]);
	flags_3 = (&htim3 == htim) ? (sds_events_chan_events[SDS_SENSTYPECFGNUM_SENS_CSS]) : (sds_events_chan_events[SDS_SENSTYPECFGNUM_SENS_RES_0]);
	flags_4 = (&htim3 == htim) ? (sds_events_chan_events[SDS_SENSTYPECFGNUM_SENS_ACC]) : (sds_events_chan_events[SDS_SENSTYPECFGNUM_SENS_RES_1]);

	if ( htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1 )
	{
		cmp_val = (freq_1 + __HAL_TIM_GET_COUNTER(htim)) % SDS_EVENTS_TIMER_TICK_FREQ;

		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, cmp_val);

		(void) osThreadFlagsSet (sds_get_thread_id(), flags_1);
	}

	if ( htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2 )
	{
		cmp_val = (freq_2 + __HAL_TIM_GET_COUNTER(htim)) % SDS_EVENTS_TIMER_TICK_FREQ;

		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_2, cmp_val);

		(void) osThreadFlagsSet (sds_get_thread_id(), flags_2);
	}

	if ( htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3 )
	{
		cmp_val = (freq_3 + __HAL_TIM_GET_COUNTER(htim)) % SDS_EVENTS_TIMER_TICK_FREQ;

		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_3, cmp_val);

		(void) osThreadFlagsSet (sds_get_thread_id(), flags_3);
	}

	if ( htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4 )
	{
		cmp_val = (freq_4 + __HAL_TIM_GET_COUNTER(htim)) % SDS_EVENTS_TIMER_TICK_FREQ;

		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_4, cmp_val);

		(void) osThreadFlagsSet (sds_get_thread_id(), flags_4);
	}
}

/** @brief Initialise an output compare of a timer
 *
 *  @param  htim TIM Output Compare handle
 *  @param  htim_oc_chan_cfg TIM Output Compare configuration structure
 *  @param  channel TIM Channels to configure
 *  @param  freq Frequency configuration for the output compare
 *
 *	@retval True - Success
 *	@retval False - Failure to initialise
 */
STATIC bool sds_events_init_oc_chan(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *htim_oc_chan_cfg, uint32_t channel, uint16_t freq)
{
	CRIT_ASSERT(NULL != htim);
	CRIT_ASSERT(NULL != htim_oc_chan_cfg);

	bool res = true;

	htim_oc_chan_cfg->OCMode = TIM_OCMODE_TIMING;
	htim_oc_chan_cfg->Pulse = freq;

	if ( freq > 0 )
	{
		if ( HAL_OK != HAL_TIM_OC_ConfigChannel(htim, htim_oc_chan_cfg, channel) )
		{
			res = false;
		}
	}

	return res;
}

/** @brief Start output compare of a timer in interrupt mode
 *
 *	@param  freq Frequency configuration for the output compare
 *	@param  channel TIM Channels to configure
 *	@param  htim Pointer to a TIM Output Compare handle
 *
 */
STATIC void sds_events_start_oc_chan_it(uint16_t freq, uint32_t channel, TIM_HandleTypeDef *htim)
{
	if ( freq > 0 )
	{
		if ( HAL_OK != HAL_TIM_OC_Start_IT(htim, channel) )
		{
			Error_Handler();
		}
	}
}

/* ******************************************************************************************* */
