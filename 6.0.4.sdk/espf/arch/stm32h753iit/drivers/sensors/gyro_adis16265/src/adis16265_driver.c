/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup gyro_adis16265
 * @{
 *
 * @file     adis16265_driver.c
 * @brief    ADIS16265 driver file
 *
 * @}
 *
 */

#include "../inc/adis16265_driver.h"

#include <string.h>
#include <sys/_stdint.h>

#include "../../../../../../app/main.h"
#include "../../../../../../config/arch/stm32h753iit/MCU_Init.h"
#include "../../../../../../config/nvm_appcfg/inc/nvm_app_block_ids.h"
#include "../../../../../../config/nvm_appcfg/inc/nvm_app_types.h"
#include "../../../../../../core/lib/cdef/User_types.h"
#include "../../../../../../core/lib/assertions/inc/assertions.h"
#include "../../../../../../core/services/nvm/inc/nvm.h"
#include "../../../../hal/inc/stm32h7xx_hal_def.h"
#include "../../../../hal/inc/stm32h7xx_hal_rcc.h"
#include "../../../../hal/inc/stm32h7xx_hal_spi.h"

/**********************************************************************
 *
 * Internal type definitions
 *
 **********************************************************************/
/** @brief File static variables that hold active gyroscope information */
static gyroscope_t gyroscope_X;
static gyroscope_t gyroscope_Y;
static gyroscope_t gyroscope_Z;

/** @brief Bundle that holds the status of all gyroscopes; To be used when reading evaluating errors from SDS or through FP commands */
static gyroscope_status_bundle_t gyroscopeStatus;

/** @brief The loaded NVM config upon initialization */
static gyroscope_configs_t loadedNVMConfig;

/**********************************************************************
 *
 * Static function declarations
 *
 **********************************************************************/
static void    fs_ADIS16265_ReadSingleAxisAngle(gyroscope_t* gyroscope, int16_t* gyroData);
static void    fs_ADIS16265_ReadSingleAxisRate(gyroscope_t* gyroscope, int16_t* gyroData);
static void    fs_ADIS16265_ReadSingleAxisTemp(gyroscope_t* gyroscope, int16_t* gyroData);
static void    fs_ADIS16265_StallDelay(void);
static void    fs_ADIS16265_ChipSelect(gyroscope_t* gyroscope, uint8_t mode);
static uint8_t fs_ADIS16265_FindGyroBasedOnAxis(gyroscope_configs_t* gyroscopeConfigs, PanId_t satelliteAxis);
static void    fs_ADIS16265_SaveGyroConfigChange(gyroscope_t* gyroscope);
static void    fs_ADIS16265_UpdateGyroStatusBundle(void);
static void    fs_ADIS16265_DisableGyroBasedOnAxis(PanId_t satelliteAxis);

gyroscope_status_t ADIS16265_Init(PanId_t satelliteAxis, bool is_init_time_req)
{
	uint8_t gyro_config_index_positive = 0;
	uint8_t gyro_config_index_negative = 0;

	uint8_t gyro_config_to_init_index = 0;
	gyroscope_t gyroscopeToInit;

	uint16_t gyro_product_num = 0;

    /* This delay compensates for gyroscope initial start-up time, 165ms as per datasheet, page 4 */
	/* This can be significantly reduced if the gyroscopes are never shut off, but instead put into sleep mode - TBD */
    if ( ADIS16265_INIT_TIME_REQ == is_init_time_req )
	{
    	sysDelay(200);
	}

    /* Fetch base gyro configs from NVM */
    Nvm_GetBlockById(NVM_BLOCK_GYROSCOPE_CONFIG, &loadedNVMConfig);

    /* If X axis gyroscope has not been initialized */
    if (ADIS16265_DISABLED == gyroscope_X.enabledFlag)
    {
    	/* Find which one is for gyroscope on axis X */
    	gyro_config_index_positive = fs_ADIS16265_FindGyroBasedOnAxis(&loadedNVMConfig, PAN_X_P);
    	gyro_config_index_negative = fs_ADIS16265_FindGyroBasedOnAxis(&loadedNVMConfig, PAN_X_M);

    	/* If the index positive did not return MAX_PAN, that means the positive axis was found in the configurations */
    	if (gyro_config_index_positive < MAX_PAN)
    	{
    		gyroscope_X = loadedNVMConfig.gyroscopeArray[gyro_config_index_positive];
    	}
    	/* If the index negative did not return MAX_PAN, that means the negative axis was found in the configurations */
    	else if (gyro_config_index_negative < MAX_PAN)
    	{
    		gyroscope_X = loadedNVMConfig.gyroscopeArray[gyro_config_index_negative];
    	}
    	/* If both axis directions were not found, that means the axis wasn't in the configurations - error */
    	else
    	{
    		gyroscope_X.generalStatus = GYRO_INIT_X_NOT_FOUND;
    		return GYRO_INIT_X_NOT_FOUND;
    	}
    }

    /* If Y axis gyroscope has not been initialized */
    if (ADIS16265_DISABLED == gyroscope_Y.enabledFlag)
    {
    	/* Find which one is for gyroscope on axis Y */
    	gyro_config_index_positive = fs_ADIS16265_FindGyroBasedOnAxis(&loadedNVMConfig, PAN_Y_P);
    	gyro_config_index_negative = fs_ADIS16265_FindGyroBasedOnAxis(&loadedNVMConfig, PAN_Y_M);

    	/* If the index positive did not return MAX_PAN, that means the positive axis was found in the configurations */
    	if (gyro_config_index_positive < MAX_PAN)
    	{
    		gyroscope_Y = loadedNVMConfig.gyroscopeArray[gyro_config_index_positive];
    	}
    	/* If the index negative did not return MAX_PAN, that means the negative axis was found in the configurations */
    	else if (gyro_config_index_negative < MAX_PAN)
    	{
    		gyroscope_Y = loadedNVMConfig.gyroscopeArray[gyro_config_index_negative];
    	}
    	/* If both axis directions were not found, that means the axis wasn't in the configurations - error */
    	else
    	{
    		gyroscope_Y.generalStatus = GYRO_INIT_Y_NOT_FOUND;
    		return GYRO_INIT_Y_NOT_FOUND;
    	}
    }

    /* If Z axis gyroscope has not been initialized */
    if (ADIS16265_DISABLED == gyroscope_Z.enabledFlag)
    {
    	/* Find which one is for gyroscope on axis Z */
    	gyro_config_index_positive = fs_ADIS16265_FindGyroBasedOnAxis(&loadedNVMConfig, PAN_Z_P);
    	gyro_config_index_negative = fs_ADIS16265_FindGyroBasedOnAxis(&loadedNVMConfig, PAN_Z_M);

    	/* If the index positive did not return MAX_PAN, that means the positive axis was found in the configurations */
    	if (gyro_config_index_positive < MAX_PAN)
    	{
    		gyroscope_Z = loadedNVMConfig.gyroscopeArray[gyro_config_index_positive];
    	}
    	/* If the index negative did not return MAX_PAN, that means the negative axis was found in the configurations */
    	else if (gyro_config_index_negative < MAX_PAN)
    	{
    		gyroscope_Z = loadedNVMConfig.gyroscopeArray[gyro_config_index_negative];
    	}
    	/* If both axis directions were not found, that means the axis wasn't in the configurations - error */
    	else
    	{
    		gyroscope_Z.generalStatus = GYRO_INIT_Z_NOT_FOUND;
    		return GYRO_INIT_Z_NOT_FOUND;
    	}
    }

    /* Find the config which has desired axis */
    gyro_config_to_init_index = fs_ADIS16265_FindGyroBasedOnAxis(&loadedNVMConfig, satelliteAxis);
    if (gyro_config_to_init_index < MAX_PAN)
    {
    	gyroscopeToInit = loadedNVMConfig.gyroscopeArray[gyro_config_to_init_index];
    }
    else
    {
    	return GYRO_INIT_AXIS_NOT_FOUND_IN_NVM;
    }

    /* Init sequence for the desired singular gyroscope */
    if (GYRO_SUCCESS != ADIS16265_ReadReg16(&gyroscopeToInit, ADIS16265_PROD_ID, &gyro_product_num))
    {
    	return GYRO_COMM_READ_FAIL;
    }

    if (ADIS16265_PROD_NUM != gyro_product_num)
    {
    	return GYRO_PROD_ID_ERROR;
    }

    /* Change initial gyroscope sampling and filtering configurations */
    if (GYRO_SUCCESS != ADIS16265_WriteReg16(&gyroscopeToInit, ADIS16265_SENS_AVG, ADIS16265_CONFIG))
    {
    	return GYRO_COMM_WRITE_FAIL;
    }

    /* Enable the gyroscope as it is initialized */
    gyroscopeToInit.enabledFlag = ADIS16265_ENABLED;

    fs_ADIS16265_SaveGyroConfigChange(&gyroscopeToInit);

    return GYRO_SUCCESS;
}

void ADIS16265_DeInit(PanId_t satelliteAxis)
{
	/* Disable the correct gyroscope based on the axis */
	fs_ADIS16265_DisableGyroBasedOnAxis(satelliteAxis);
}

gyroscope_status_t ADIS16265_GetAxesAngle(PANLE_GYROS_AXIS Axis, AxesRaw_t* buff)
{
	CRIT_ASSERT(NULL != buff);

	/* Invalidate the data */
	buff->AXIS_X = buff->AXIS_Y = buff->AXIS_Z = ADIS16265_INVALID_VALUE;

	/* Axis X */
	if ((PANLE_GYROS_AXIS_ALL == Axis) || (PANLE_GYROS_AXIS_X == Axis))
	{
		/* Check if the gyroscope is enabled */
		if (ADIS16265_ENABLED == gyroscope_X.enabledFlag)
		{
			/* Read data from X axis gyroscope */
			fs_ADIS16265_ReadSingleAxisAngle(&gyroscope_X, &buff->AXIS_X);
		}
		else
		{
			/* Gyroscope is not enabled */
			gyroscope_X.generalStatus = GYRO_DISABLED;
		}
	}

	/* Axis Y */
	if ((PANLE_GYROS_AXIS_ALL == Axis) || (PANLE_GYROS_AXIS_Y == Axis))
	{
		/* Check if the gyroscope is enabled */
		if (ADIS16265_ENABLED == gyroscope_Y.enabledFlag)
		{
			/* Read data from Y axis gyroscope */
			fs_ADIS16265_ReadSingleAxisAngle(&gyroscope_Y, &buff->AXIS_Y);
		}
		else
		{
			/* Gyroscope is not enabled */
			gyroscope_Y.generalStatus = GYRO_DISABLED;
		}
	}

	/* Axis Z */
	if ((PANLE_GYROS_AXIS_ALL == Axis) || (PANLE_GYROS_AXIS_Z == Axis))
	{
		/* Check if the gyroscope is enabled */
		if (ADIS16265_ENABLED == gyroscope_Z.enabledFlag)
		{
			/* Read data from Z axis gyroscope */
			fs_ADIS16265_ReadSingleAxisAngle(&gyroscope_Z, &buff->AXIS_Z);
		}
		else
		{
			/* Gyroscope is not enabled */
			gyroscope_Z.generalStatus = GYRO_DISABLED;
		}
	}

	/* Update any changes to gyroscopes' status */
	fs_ADIS16265_UpdateGyroStatusBundle();

	/* If all gyroscopes have failed to read any data */
	if ( (GYRO_SUCCESS != gyroscope_X.generalStatus) &&
	     (GYRO_SUCCESS != gyroscope_Y.generalStatus) &&
	     (GYRO_SUCCESS != gyroscope_Z.generalStatus) )
	{
		/* Signal a complete gyroscope failure */
		return GYRO_ERROR;
	}
	else
	{
		/* Partial or full gyroscope read was completed */
		return GYRO_SUCCESS;
	}
}

gyroscope_status_t ADIS16265_GetAxesRate(PANLE_GYROS_AXIS Axis, AxesRaw_t* buff)
{
	CRIT_ASSERT(NULL != buff);

	/* Invalidate the data */
	buff->AXIS_X = buff->AXIS_Y = buff->AXIS_Z = ADIS16265_INVALID_VALUE;

	/* Axis X */
	if ((PANLE_GYROS_AXIS_ALL == Axis) || (PANLE_GYROS_AXIS_X == Axis))
	{
		/* Check if the gyroscope is enabled */
		if (ADIS16265_ENABLED == gyroscope_X.enabledFlag)
		{
			/* Read data from X axis gyroscope */
			fs_ADIS16265_ReadSingleAxisRate(&gyroscope_X, &buff->AXIS_X);
		}
		else
		{
			/* Gyroscope is not enabled */
			gyroscope_X.generalStatus = GYRO_DISABLED;
		}
	}

	/* Axis Y */
	if ((PANLE_GYROS_AXIS_ALL == Axis) || (PANLE_GYROS_AXIS_Y == Axis))
	{
		/* Check if the gyroscope is enabled */
		if (ADIS16265_ENABLED == gyroscope_Y.enabledFlag)
		{
			/* Read data from Y axis gyroscope */
			fs_ADIS16265_ReadSingleAxisRate(&gyroscope_Y, &buff->AXIS_Y);
		}
		else
		{
			/* Gyroscope is not enabled */
			gyroscope_Y.generalStatus = GYRO_DISABLED;
		}
	}

	/* Axis Z */
	if ((PANLE_GYROS_AXIS_ALL == Axis) || (PANLE_GYROS_AXIS_Z == Axis))
	{
		/* Check if the gyroscope is enabled */
		if (ADIS16265_ENABLED == gyroscope_Z.enabledFlag)
		{
			/* Read data from Z axis gyrscope */
			fs_ADIS16265_ReadSingleAxisRate(&gyroscope_Z, &buff->AXIS_Z);
		}
		else
		{
			/* Gyroscope is not enabled */
			gyroscope_Z.generalStatus = GYRO_DISABLED;
		}
	}

	/* Update any changes to gyroscopes' status */
	fs_ADIS16265_UpdateGyroStatusBundle();

	/* If all gyroscopes have failed to read any data */
	if ( (GYRO_SUCCESS != gyroscope_X.generalStatus) &&
	     (GYRO_SUCCESS != gyroscope_Y.generalStatus) &&
	     (GYRO_SUCCESS != gyroscope_Z.generalStatus) )
	{
		/* Signal a complete gyroscope failure */
		return GYRO_ERROR;
	}
	else
	{
		/* Partial or full gyroscope read was completed */
		return GYRO_SUCCESS;
	}
}

gyroscope_status_t ADIS16265_GetTemperature(Temperature_t* tmp)
{
	CRIT_ASSERT(NULL != tmp);

    /* Invalidate the data */
	tmp->Temp_X = tmp->Temp_Y = tmp->Temp_Z = ADIS16265_INVALID_VALUE;

	/* Axis X */
	/* Check if the gyroscope is enabled */
	if (ADIS16265_ENABLED == gyroscope_X.enabledFlag)
	{
		/* Read temperature data from X axis gyroscope */
		fs_ADIS16265_ReadSingleAxisTemp(&gyroscope_X, &tmp->Temp_X);
	}
	else
	{
		/* Gyroscope is not enabled */
		gyroscope_X.generalStatus = GYRO_DISABLED;
	}

	/* Axis Y */
	/* Check if the gyroscope is enabled */
	if (ADIS16265_ENABLED == gyroscope_Y.enabledFlag)
	{
		/* Read temperature data from Y axis gyroscope */
		fs_ADIS16265_ReadSingleAxisTemp(&gyroscope_Y, &tmp->Temp_Y);
	}
	else
	{
		/* Gyroscope is not enabled */
		gyroscope_Y.generalStatus = GYRO_DISABLED;
	}

	/* Axis Z */
	/* Check if the gyroscope is enabled */
	if (ADIS16265_ENABLED == gyroscope_Z.enabledFlag)
	{
		/* Read temperature data from Z axis gyroscope */
		fs_ADIS16265_ReadSingleAxisTemp(&gyroscope_Z, &tmp->Temp_Z);
	}
	else
	{
		/* Gyroscope is not enabled */
		gyroscope_Z.generalStatus = GYRO_DISABLED;
	}

	/* Update any changes to gyroscopes' status */
	fs_ADIS16265_UpdateGyroStatusBundle();

	/* If all gyroscopes have failed to read any data */
	if ( (GYRO_SUCCESS != gyroscope_X.generalStatus) &&
	     (GYRO_SUCCESS != gyroscope_Y.generalStatus) &&
		 (GYRO_SUCCESS != gyroscope_Z.generalStatus) )
	{
		/* Signal a complete gyroscope failure */
		return GYRO_ERROR;
	}
	else
	{
		/* Partial or full gyroscope read was completed */
		return GYRO_SUCCESS;
	}
}

gyroscope_status_t ADIS16265_WriteReg16(gyroscope_t* gyroscope, uint8_t Address, uint16_t data)
{
	CRIT_ASSERT(NULL != gyroscope);

	uint16_t txdata;
	HAL_StatusTypeDef res = HAL_OK;

	/* Flip 15th bit to high (0x8000) to signal that it's a write operation */
	/* Put high byte of destination register address plus 1 in high 8-bits as per datasheet, page 12 */
	/* Put high byte of 16-bit data sequence in low 8-bits */
	txdata = (0x8000 | ((uint16_t) (Address+1) << 8) | (data >> 8));

	/* SPI Chip select on */
	fs_ADIS16265_ChipSelect(gyroscope, ADIS16265_CHIP_SELECT_ON);

	/* Panel SPI is configured as 16 bit data sequence, therefore it sends 16 bits at once */
	/* Cast of 2nd parameter to uint8_t pointer is due to the way SPI_Transmit function is written from ST HAL */
	res = HAL_SPI_Transmit(&PANEL_SPI_HANDLER, (uint8_t *) &txdata, 1, 10);

	/* Catch communication error */
	if (HAL_OK != res)
	{
		gyroscope->generalStatus = GYRO_COMM_SPI_W_FAIL;
		return GYRO_COMM_SPI_W_FAIL;
	}

	/* Stall delay between the 2 writes that make up the 16 bit sequence as per datasheet, page 5 */
	fs_ADIS16265_StallDelay();

	/* Flip 15th bit to high (0x8000) to signal that it's a write operation */
	/* Put low byte of destination register address in high 8-bits as per datasheet, page 12 */
	/* Put low byte of 16-bit data sequence in low 8-bits */
	txdata = (0x8000 | ((uint16_t) Address << 8) | (data & 0xFF));

	/* Panel SPI is configured as 16 bit data sequence, therefore it sends 16 bits at once */
	/* Cast of 2nd parameter to uint8_t pointer is due to the way SPI_Transmit function is written from ST HAL */
	res = HAL_SPI_Transmit(&PANEL_SPI_HANDLER, (uint8_t *) &txdata, 1, 10);

	/* SPI Chip select off */
	fs_ADIS16265_ChipSelect(gyroscope, ADIS16265_CHIP_SELECT_OFF);

	/* Catch communication error */
	if (HAL_OK != res)
	{
		gyroscope->generalStatus = GYRO_COMM_SPI_W_FAIL;
		return GYRO_COMM_SPI_W_FAIL;
	}

	return GYRO_SUCCESS;
}

gyroscope_status_t ADIS16265_ReadReg16(gyroscope_t* gyroscope, uint8_t Address, uint16_t *data)
{
	CRIT_ASSERT(NULL != gyroscope);
	CRIT_ASSERT(NULL != data);

	uint16_t txdata;
	HAL_StatusTypeDef res = HAL_OK;

	/* Put low byte of destination register address in high 8-bits as per datasheet, page 12 */
	txdata = (uint16_t) Address << 8;

	/* SPI Chip select on */
	fs_ADIS16265_ChipSelect(gyroscope, ADIS16265_CHIP_SELECT_ON);

	/* Panel SPI is configured as 16 bit data sequence, therefore it sends 16 bits at once */
	/* Cast of 2nd parameter to uint8_t pointer is due to the way SPI_Transmit function is written from ST HAL */
	res = HAL_SPI_Transmit(&PANEL_SPI_HANDLER, (uint8_t *) &txdata, 1, 10);

	/* Catch communication error */
	if (HAL_OK != res)
	{
		gyroscope->generalStatus = GYRO_COMM_SPI_W_FAIL;
		return GYRO_COMM_SPI_W_FAIL;
	}

	/* Stall delay between the 2 operations that make up the 16 bit sequence as per datasheet, page 5 */
	fs_ADIS16265_StallDelay();

	/* Clear variable in preparation for reading */
	*data = 0U;

	/* Panel SPI is configured as 16 bit data sequence, therefore it receives 16 bits at once */
	/* Cast of 2nd parameter to uint8_t pointer is due to the way SPI_Transmit function is written from ST HAL */
	res = HAL_SPI_Receive(&PANEL_SPI_HANDLER, (uint8_t *) data, 1, 10);

	/* SPI Chip select off */
	fs_ADIS16265_ChipSelect(gyroscope, ADIS16265_CHIP_SELECT_OFF);

	/* Catch communication error */
	if (HAL_OK != res)
	{
		gyroscope->generalStatus = GYRO_COMM_SPI_R_FAIL;
		return GYRO_COMM_SPI_R_FAIL;
	}

	return GYRO_SUCCESS;
}

gyroscope_status_bundle_t ADIS16265_GetStatus(void)
{
	return gyroscopeStatus;
}

void ADIS16265_SetPanel(PanId_t satelliteAxis, Panel_Number_t attachedPanel)
{
	/* If the config is for X axis gyroscope - change the panel */
	if ( (PAN_X_P == satelliteAxis) || (PAN_X_M == satelliteAxis) )
	{
		gyroscope_X.attachedPanel = attachedPanel;
	}
	/* If the config is for Y axis gyroscope - change the panel */
	else if ( (PAN_Y_P == satelliteAxis) || (PAN_Y_M == satelliteAxis) )
	{
		gyroscope_Y.attachedPanel = attachedPanel;
	}
	/* The config is for Z axis gyroscope - change the panel */
	else
	{
		gyroscope_Z.attachedPanel = attachedPanel;
	}

	ADIS16265_Save_Config_to_NVM();
}

Panel_Number_t ADIS16265_GetPanel(PanId_t satelliteAxis)
{
	/* If the config is for X axis gyroscope - change the panel */
	if ( (PAN_X_P == satelliteAxis) || (PAN_X_M == satelliteAxis) )
	{
		return gyroscope_X.attachedPanel;
	}
	/* If the config is for Y axis gyroscope - change the panel */
	else if ( (PAN_Y_P == satelliteAxis) || (PAN_Y_M == satelliteAxis) )
	{
		return gyroscope_Y.attachedPanel;
	}
	/* The config is for Z axis gyroscope - change the panel */
	else
	{
		return gyroscope_Z.attachedPanel;
	}
}

void ADIS16265_Save_Config_to_NVM(void)
{
	gyroscope_configs_t gyroConfig;

	gyroscope_X.generalStatus = GYRO_DISABLED;
	gyroscope_X.enabledFlag = ADIS16265_DISABLED;
	gyroConfig.gyroscopeArray[0] = gyroscope_X;

	gyroscope_Y.generalStatus = GYRO_DISABLED;
	gyroscope_Y.enabledFlag = ADIS16265_DISABLED;
	gyroConfig.gyroscopeArray[1] = gyroscope_Y;

	gyroscope_Z.generalStatus = GYRO_DISABLED;
	gyroscope_Z.enabledFlag = ADIS16265_DISABLED;
	gyroConfig.gyroscopeArray[2] = gyroscope_Z;

    Nvm_SetBlockById(NVM_BLOCK_GYROSCOPE_CONFIG, &gyroConfig, NVMSETBLOCK_STORE_IMMEDIATELY);
}

void ADIS16265_Load_Config_from_NVM(void)
{
    gyroscope_configs_t gyroConfig;

    Nvm_GetBlockById(NVM_BLOCK_GYROSCOPE_CONFIG, &gyroConfig);

    gyroscope_X = gyroConfig.gyroscopeArray[0];
    gyroscope_Y = gyroConfig.gyroscopeArray[1];
    gyroscope_Z = gyroConfig.gyroscopeArray[2];
}

void ADIS16265_get_full_gyro_info(gyroscope_t *const gyro_x, gyroscope_t *const gyro_y, gyroscope_t *const gyro_z)
{
	memcpy(gyro_x, &gyroscope_X, sizeof(gyroscope_t));
	memcpy(gyro_y, &gyroscope_Y, sizeof(gyroscope_t));
	memcpy(gyro_z, &gyroscope_Z, sizeof(gyroscope_t));
}

/**********************************************************************
 *
 * Static function definitions
 *
 **********************************************************************/
/** @brief Reads the angles (angular position) from a single gyroscope axis
 *  @param[in]  gyroscope_t* gyroscope - pointer to struct with selected gyroscope data
 *  @param[out] int16_t*      gyroData - pointer to variable for storing read data */
static void fs_ADIS16265_ReadSingleAxisAngle(gyroscope_t* gyroscope, int16_t* gyroData)
{
	CRIT_ASSERT(NULL != gyroscope);
	CRIT_ASSERT(NULL != gyroData);

	uint32_t temp_data;
	gyroscope_status_t status;
	uint8_t attemptCounter = 0;

	/* Several attempts to read the gyroscope data */
	for (attemptCounter = 0; attemptCounter < ADIS16265_MAX_ATTEMPTS; attemptCounter++)
	{
		status = ADIS16265_ReadReg16(gyroscope, ADIS16265_ANGL_OUT, (uint16_t *) &temp_data);

		/* Disconnected gyroscope */
		if (0xFFFF == (uint16_t) temp_data)
		{
			status = GYRO_DISCONNECTED;
		}

		if (GYRO_SUCCESS == status)
		{
			/* Reading successful, stop attempts */
			gyroscope->generalStatus = status;
			break;
		}
		else
		{
			/* Reading failed, update gyroscope status variable */
			gyroscope->generalStatus = status;
		}
	}
	if (GYRO_SUCCESS == status)
	{
		/* Transform ADC readings into actual angle value */
		if (attemptCounter < ADIS16265_MAX_ATTEMPTS)
		{
			/* Only retrieve first 14 bits of reading */
			temp_data &= ADIS16265_GYRO_OUT_14BIT_MASK;
			/* Use integer scaling to convert to hundreds of thousands of degrees */
			temp_data *= ADIS16265_BITS_TO_SCALED_DEG;
			/* Scale back down to degrees */
			temp_data /= ADIS16265_SCALED_DEG_TO_DEG;
			/* Transfer to output buffer */
			*gyroData = (int16_t) temp_data;
		}
		else
		{
			/* Gyroscope has failed to provide data within accepted read attempts */
			gyroscope->generalStatus = GYRO_ATTEMPTS_EXPIRED;
		}
	}
}

/** @brief Reads the rates (angular velocity) from a single gyroscope axis
 *  @param[in]  gyroscope_t* gyroscope - pointer to struct with selected gyroscope data
 *  @param[out] int16_t*      gyroData - pointer to variable for storing read data */
static void fs_ADIS16265_ReadSingleAxisRate(gyroscope_t* gyroscope, int16_t* gyroData)
{
	CRIT_ASSERT(NULL != gyroscope);
	CRIT_ASSERT(NULL != gyroData);

	gyroscope_status_t status;
	uint8_t attemptCounter = 0;

	/* Several attempts to read the gyroscope data */
	for (attemptCounter = 0; attemptCounter < ADIS16265_MAX_ATTEMPTS; attemptCounter++)
	{
		status = ADIS16265_ReadReg16(gyroscope, ADIS16265_GYRO_OUT, (uint16_t *)(gyroData));

		/* Disconnected gyroscope */
		if (0xFFFF == (uint16_t) *gyroData)
		{
			status = GYRO_DISCONNECTED;
		}

		if (GYRO_SUCCESS == status)
		{
			/* If the measurement is outside expected range - invalidate it */
			/* The output data from the gyroscope is 14 bits, hence the ADIS16265_GYRO_OUT_14BIT_MASK */
			if ( ((*gyroData & ADIS16265_GYRO_OUT_14BIT_MASK) > ADIS16265_GYRO_OUT_POS_MAX_VAL) &&
				 ((*gyroData & ADIS16265_GYRO_OUT_14BIT_MASK) < ADIS16265_GYRO_OUT_NEG_MAX_VAL) )
			{
				gyroscope->generalStatus = GYRO_MEASURE_OUT_OF_RANGE;
				attemptCounter = ADIS16265_MAX_ATTEMPTS;
			}
			/* Reading successful, stop attempts */
			gyroscope->generalStatus = status;
			break;
		}
		else
		{
			/* Reading failed, update gyroscope status variable */
			gyroscope->generalStatus = status;
		}
	}
	if (GYRO_SUCCESS == status)
	{
		/* Only retrieve first 14 bits of reading */
		if (attemptCounter < ADIS16265_MAX_ATTEMPTS)
		{
			/* Only retrieve first 14 bits of reading */
			*gyroData &= ADIS16265_GYRO_OUT_14BIT_MASK;
		}
		else
		{
			/* Gyroscope has failed to provide data within accepted read attempts */
			gyroscope->generalStatus = GYRO_ATTEMPTS_EXPIRED;
		}
	}
}

/** @brief Reads the temperature from a single gyroscope
 *  @param[in]  gyroscope_t* gyroscope - pointer to struct with selected gyroscope data
 *  @param[out] int16_t*      gyroData - pointer to variable for storing read data */
static void fs_ADIS16265_ReadSingleAxisTemp(gyroscope_t* gyroscope, int16_t* gyroData)
{
	CRIT_ASSERT(NULL != gyroscope);
	CRIT_ASSERT(NULL != gyroData);

	uint32_t temp_data = 0;
	gyroscope_status_t status;
	uint8_t attemptCounter = 0;

	/* Several attempts to read the gyroscope data */
	for (attemptCounter = 0; attemptCounter < ADIS16265_MAX_ATTEMPTS; attemptCounter++)
	{
		status = ADIS16265_ReadReg16(gyroscope, ADIS16265_TEMP_OUT, (uint16_t *) &temp_data);

		/* Disconnected gyroscope */
		if (0xFFFF == (uint16_t) temp_data)
		{
			status = GYRO_DISCONNECTED;
		}

		if (GYRO_SUCCESS == status)
		{
			/* Reading successful, stop attempts */
			gyroscope->generalStatus = status;
			break;
		}
		else
		{
			/* Reading failed, update gyroscope status variable */
			gyroscope->generalStatus = status;
		}
	}
	if (GYRO_SUCCESS == status)
	{
		/* Transform ADC readings into actual temperature value */
		if (attemptCounter < ADIS16265_MAX_ATTEMPTS)
		{
			/* Only retrieve first 12 bits of reading */
			temp_data &= ADIS16265_TEMP_12BIT_MASK;
			/* Data conversion as per datasheet, page 13, table 12 */
			if (temp_data >= ADIS16265_TEMP_MINUS_40)
			{
				temp_data = ADIS16265_TEMP_12BIT_MASK - temp_data;
				/* Multiply by scaling factor to get tens of thousands of degrees (integer scaling) */
				temp_data *= ADIS16265_TEMP_FRAC;
				/* Subtract from scaled ambient temperature (25 deg C) */
				temp_data  = ADIS16265_TEMP_25 - temp_data;
			}
			else
			{
				/* Multiply by scaling factor to get tens of thousands of degrees (integer scaling) */
				temp_data *= ADIS16265_TEMP_FRAC;
				/* Add to scaled ambient temperature (25 deg C) */
				temp_data  = ADIS16265_TEMP_25 + temp_data;
			}

			/* Scale down from tens of thousands of degrees to degrees */
			temp_data /= ADIS16265_TEMP_DIV;

			/* Transfer to output buffer */
			*gyroData = temp_data;
		}
		else
		{
			/* Gyroscope has failed to provide data within accepted read attempts */
			gyroscope_X.generalStatus = GYRO_ATTEMPTS_EXPIRED;
		}
	}
}

/** @brief Calculates the necessary empty processor loops in order to provide a minimum of 12usec delay
 *  @note See ADIS16265 gyroscope datasheet for more information */
static void fs_ADIS16265_StallDelay(void)
 {
    /* System clock tick speed */
    double SysClockSpeed = (double)1.0 / (double)HAL_RCC_GetSysClockFreq();

    /* How many ticks are needed to fulfill adis16265 stall delay requirement */
    uint32_t neededEmptyLoops = ADIS16265_STALL_DELAY_MINIMUM_S / SysClockSpeed;

    for (volatile uint32_t i = 0; i < neededEmptyLoops; i++)
    	 __asm volatile("nop");
 }

/** @brief SPI Chip select function to enable/disable proper PANEL pin according to given gyroscope struct
 *  @param[in]  gyroscope_t* gyroscope - pointer to struct with selected gyroscope data
 *  @param[out] uint8_t           mode - possible values are ADIS16265_CHIP_SELECT_ON or ADIS16265_CHIP_SELECT_OFF */
static void fs_ADIS16265_ChipSelect(gyroscope_t* gyroscope, uint8_t mode)
{
	CRIT_ASSERT(NULL != gyroscope);

	/* The SPI_SlaveSelect function works with 0 base enum, so you need to subtract 1 from the given panel in the gyroscope struct */
	uint8_t panel = gyroscope->attachedPanel - 1;

	/* Chip select on */
	if (ADIS16265_CHIP_SELECT_ON == mode)
	{
		SPI_SlaveSelect(ADIS16265_CHIP_SELECT_ON  | panel);
	}
	else
	{
		SPI_SlaveSelect(ADIS16265_CHIP_SELECT_OFF | panel);
	}
}

/** @brief Returns the panel id which corresponds to a given satellite axis
 *  @param[in]  gyroscope_configs_t* gyroscopeConfigs - pointer to struct with all NVM gyroscope configurations
 *  @param[out] PanId_t                 satelliteAxis - the satellite axis configuration which is to be found
 *  @return     uint8_t                               - the panel id that is connected to the given axis */
static uint8_t fs_ADIS16265_FindGyroBasedOnAxis(gyroscope_configs_t* gyroscopeConfigs, PanId_t satelliteAxis)
{
	CRIT_ASSERT(NULL != gyroscopeConfigs);

	uint8_t res = MAX_PAN;
	uint8_t i = 0;

	CRIT_ASSERT(NULL != gyroscopeConfigs);

	/* Go through all gyroscope configs */
	for (i = 0; i < (GYROSCOPE_COUNT - 1); i++)
	{
		/* Find the one that is for the desired axis */
		if (satelliteAxis == gyroscopeConfigs->gyroscopeArray[i].satelliteAxis)
		{
			res = i;
		}
	}

	return res;
}

/** @brief Transfers the given configuration parameters to the local gyroscope parameters based on axis
 *  @param[in]  gyroscope_t* gyroscope - pointer to struct with all NVM gyroscope configurations */
static void fs_ADIS16265_SaveGyroConfigChange(gyroscope_t* gyroscope)
{
	CRIT_ASSERT(NULL != gyroscope);

	/* If the config is for X axis gyroscope - update that local variable */
	if ( (PAN_X_P == gyroscope->satelliteAxis) || (PAN_X_M == gyroscope->satelliteAxis) )
	{
		memcpy(&gyroscope_X, gyroscope, sizeof(gyroscope_t));
	}
	/* If the config is for Y axis gyroscope - update that local variable */
	else if ( (PAN_Y_P == gyroscope->satelliteAxis) || (PAN_Y_M == gyroscope->satelliteAxis) )
	{
		memcpy(&gyroscope_Y, gyroscope, sizeof(gyroscope_t));
	}
	/* The config is for Z axis gyroscope - update that local variable */
	else
	{
		memcpy(&gyroscope_Z, gyroscope, sizeof(gyroscope_t));
	}
}

/** @brief Updates the gyroscope status bundle by extracting data from local variables for each gyroscope */
static void fs_ADIS16265_UpdateGyroStatusBundle(void)
{
	gyroscopeStatus.gyroscope_X_status = gyroscope_X.generalStatus;
	gyroscopeStatus.gyroscope_Y_status = gyroscope_Y.generalStatus;
	gyroscopeStatus.gyroscope_Z_status = gyroscope_Z.generalStatus;
}

/** @brief Stops a gyroscope by disabling the enableFlag in the corresponding data struct based on axis
 *  @param[in] PanId_t satelliteAxis - desired axis to be stopped */
static void fs_ADIS16265_DisableGyroBasedOnAxis(PanId_t satelliteAxis)
{
	/* If the config is for X axis gyroscope - disable that gyroscope */
	if ( (PAN_X_P == satelliteAxis) || (PAN_X_M == satelliteAxis) )
	{
		gyroscope_X.enabledFlag = ADIS16265_DISABLED;
	}
	/* If the config is for Y axis gyroscope - disable that gyroscope */
	else if ( (PAN_Y_P == satelliteAxis) || (PAN_Y_M == satelliteAxis) )
	{
		gyroscope_Y.enabledFlag = ADIS16265_DISABLED;
	}
	/* The config is for Z axis gyroscope - disable that gyroscope */
	else
	{
		gyroscope_Z.enabledFlag = ADIS16265_DISABLED;
	}
}
