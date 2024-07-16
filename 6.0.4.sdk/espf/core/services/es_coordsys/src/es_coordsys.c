/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup es_coordsys
 * @{
 *
 * @file     es_coordsys.c
 * @brief    Coordinate System Transformation service source file
 *
 * @}
 */

#include <string.h>
#include "nvm.h"
#include "es_coordsys.h"
#include "assertions.h"

/**********************************************************************
 *
 * Internal type definitions
 *
 **********************************************************************/
/* @brief
 * Y- is on the side of PC104 connector; Z+ is up where antennas are placed
 *                       PAN1 PAN2 PAN3 PAN4 PAN5 PAN6
 * Satellite frame:       Y-   X-   Z-   Z+   Y+   X+
 */

/** @brief All active frames are kept in this struct */
static es_coordsys_frames_t activeFrames;

/*
 *  ----- Rotation matrices for sensors and actuators -----
 *  ----- 2022.11.01 -----
 */

/** @brief Gyroscope rotation matrix */
static int8_t gyr_rot_mat[9];

/** @brief Magnetometer rotation matrix */
static int8_t mag_rot_mat[9];

/** @brief Magnetorquer rotation matrix */
static int8_t mtq_rot_mat[9];

/** @brief Coarse sun sensor rotation matrix */
static int8_t css_rot_mat[36];

/** @brief Accelerometer rotation matrix */
static int8_t acc_rot_mat[9];

/**********************************************************************
 *
 * Static function declarations
 *
 **********************************************************************/
static void fs_coordSys_build_gyr_matrix(void);
static void fs_coordSys_build_gyr_matrix_col(es_coordsys_satellite_axes_t gyroscopeToMap, uint8_t colNum);
static void fs_coordSys_build_mag_matrix(void);
static void fs_coordSys_build_mag_matrix_col(es_coordsys_satellite_axes_t magnetometerToMap, uint8_t colNum);
static void fs_coordSys_build_mtq_matrix(void);
static void fs_coordSys_build_mtq_matrix_col(es_coordsys_satellite_axes_t magnetorquerToMap, uint8_t colNum);
static void fs_coordSys_transpose_mtq_matrix(void);
static void fs_coordSys_build_css_matrix(void);
static void fs_coordSys_build_css_matrix_col(es_coordsys_satellite_axes_t coarseSunSensorToMap, uint8_t colNum);
static int8_t fs_coordSys_map_axis_to_value(es_coordsys_satellite_axes_t axisToMap);
static void fs_coordSys_build_acc_matrix(void);
static void fs_coordSys_build_acc_matrix_col(es_coordsys_satellite_axes_t accelerometerToMap, uint8_t colNum);


/**********************************************************************
 *
 * Public functions
 *
 **********************************************************************/
bool coordSys_init(void)
{
    /* should consist of:
     * load configs from nvm
     * build the rotation matrices
     */

    /* AA TODO: could also add a flag variable to signal whether coordsys is initialized or not;
              this would be used in the transform functions to return fail if called before
              initialization
              */

    /* Load the active config from NVM */
    coordSys_load_config_from_NVM();

    /* Build the gyroscope rotation matrix */
    fs_coordSys_build_gyr_matrix();

    /* Build the magnetometer rotation matrix */
    fs_coordSys_build_mag_matrix();

    /* Build the magnetorquer rotation matrix */
    fs_coordSys_build_mtq_matrix();

    /* Build the coarse sun sensor rotation matrix */
    fs_coordSys_build_css_matrix();

    /* Build the accelerometers rotation matrix */
    fs_coordSys_build_acc_matrix();

    return true;
}

bool coordSys_transformGyr(const int32_t *inputData, int32_t *outputData)
{
	CRIT_ASSERT(NULL != inputData);
	CRIT_ASSERT(NULL != outputData);

    /* Apply gyroscope rotation matrix. Data is only transformed between coordinate frames, not units. */

    /* Satellite frame X positive axis */
    outputData[0] = inputData[0] * gyr_rot_mat[0] + inputData[1] * gyr_rot_mat[1] + inputData[2] * gyr_rot_mat[2];

    /* Satellite frame Y positive axis */
    outputData[1] = inputData[0] * gyr_rot_mat[3] + inputData[1] * gyr_rot_mat[4] + inputData[2] * gyr_rot_mat[5];

    /* Satellite frame Z positive axis */
    outputData[2] = inputData[0] * gyr_rot_mat[6] + inputData[1] * gyr_rot_mat[7] + inputData[2] * gyr_rot_mat[8];

    return true;
}

bool coordSys_transformMag(const int32_t *inputData, int32_t *outputData)
{
	CRIT_ASSERT(NULL != inputData);
	CRIT_ASSERT(NULL != outputData);

    /* Apply magnetometer rotation matrix. Data is only transformed between coordinate frames, not units. */

    /* Satellite frame X positive axis */
    outputData[0] = inputData[0] * mag_rot_mat[0] + inputData[1] * mag_rot_mat[1] + inputData[2] * mag_rot_mat[2];

    /* Satellite frame Y positive axis */
    outputData[1] = inputData[0] * mag_rot_mat[3] + inputData[1] * mag_rot_mat[4] + inputData[2] * mag_rot_mat[5];

    /* Satellite frame Z positive axis */
    outputData[2] = inputData[0] * mag_rot_mat[6] + inputData[1] * mag_rot_mat[7] + inputData[2] * mag_rot_mat[8];

    return true;
}

bool coordSys_transformMtq(const int8_t *inputData, int8_t *outputData)
{
	CRIT_ASSERT(NULL != inputData);
	CRIT_ASSERT(NULL != outputData);

    /* Apply magnetorquer rotation matrix. Data is only transformed between coordinate frames, not units. */

    /* Satellite frame X positive axis */
    outputData[0] = inputData[0] * mtq_rot_mat[0] + inputData[1] * mtq_rot_mat[1] + inputData[2] * mtq_rot_mat[2];

    /* Satellite frame Y positive axis */
    outputData[1] = inputData[0] * mtq_rot_mat[3] + inputData[1] * mtq_rot_mat[4] + inputData[2] * mtq_rot_mat[5];

    /* Satellite frame Z positive axis */
    outputData[2] = inputData[0] * mtq_rot_mat[6] + inputData[1] * mtq_rot_mat[7] + inputData[2] * mtq_rot_mat[8];

    return true;
}

bool coordSys_transformCss(const int32_t *inputData, int32_t *outputData)
{
	CRIT_ASSERT(NULL != inputData);
	CRIT_ASSERT(NULL != outputData);

    /* Apply coarse sun sensor rotation matrix. Data is only transformed between coordinate frames, not units. */

    /* Satellite frame X positive axis */
    outputData[0] =   inputData[0] * css_rot_mat[0]  + inputData[1] * css_rot_mat[1]  + inputData[2] * css_rot_mat[2]
                    + inputData[3] * css_rot_mat[3]  + inputData[4] * css_rot_mat[4]  + inputData[5] * css_rot_mat[5];

    /* Satellite frame Y positive axis */
    outputData[1] =   inputData[0] * css_rot_mat[6]  + inputData[1] * css_rot_mat[7]  + inputData[2] * css_rot_mat[8]
                    + inputData[3] * css_rot_mat[9]  + inputData[4] * css_rot_mat[10] + inputData[5] * css_rot_mat[11];

    /* Satellite frame Z positive axis */
    outputData[2] =   inputData[0] * css_rot_mat[12] + inputData[1] * css_rot_mat[13] + inputData[2] * css_rot_mat[14]
                    + inputData[3] * css_rot_mat[15] + inputData[4] * css_rot_mat[16] + inputData[5] * css_rot_mat[17];

    /* Satellite frame X negative axis */
    outputData[3] =   inputData[0] * css_rot_mat[18] + inputData[1] * css_rot_mat[19] + inputData[2] * css_rot_mat[20]
                    + inputData[3] * css_rot_mat[21] + inputData[4] * css_rot_mat[22] + inputData[5] * css_rot_mat[23];

    /* Satellite frame Y negative axis */
    outputData[4] =   inputData[0] * css_rot_mat[24] + inputData[1] * css_rot_mat[25] + inputData[2] * css_rot_mat[26]
                    + inputData[3] * css_rot_mat[27] + inputData[4] * css_rot_mat[28] + inputData[5] * css_rot_mat[29];

    /* Satellite frame Z negative axis */
    outputData[5] =   inputData[0] * css_rot_mat[30] + inputData[1] * css_rot_mat[31] + inputData[2] * css_rot_mat[32]
                    + inputData[3] * css_rot_mat[33] + inputData[4] * css_rot_mat[34] + inputData[5] * css_rot_mat[35];

    return true;
}

bool coordSys_transformAcc(const int32_t *inputData, int32_t *outputData)
{
	CRIT_ASSERT(NULL != inputData);
	CRIT_ASSERT(NULL != outputData);

    /* Apply accelerometer rotation matrix. Data is only transformed between coordinate frames, not units. */

    /* Satellite frame X positive axis */
    outputData[0] = inputData[0] * acc_rot_mat[0] + inputData[1] * acc_rot_mat[1] + inputData[2] * acc_rot_mat[2];

    /* Satellite frame Y positive axis */
    outputData[1] = inputData[0] * acc_rot_mat[3] + inputData[1] * acc_rot_mat[4] + inputData[2] * acc_rot_mat[5];

    /* Satellite frame Z positive axis */
    outputData[2] = inputData[0] * acc_rot_mat[6] + inputData[1] * acc_rot_mat[7] + inputData[2] * acc_rot_mat[8];

    return true;
}

bool coordSys_transform_panel_temp(const int32_t *inputData, int32_t *outputData)
{
	return coordSys_transformCss(inputData, outputData);
}

bool coordSys_transform_gyro_temp(const int32_t *inputData, int32_t *outputData)
{
	return coordSys_transformMag(inputData, outputData);
}

void coordSys_setGyrMatrix(const es_coordsys_gyr_frame_t *newGyrFrame)
{
    activeFrames.gyroscopeFrame.gyr1 = newGyrFrame->gyr1;
    activeFrames.gyroscopeFrame.gyr2 = newGyrFrame->gyr2;
    activeFrames.gyroscopeFrame.gyr3 = newGyrFrame->gyr3;

    /* Call the rotation matrix builder */
    fs_coordSys_build_gyr_matrix();
}

void coordSys_getGyrMatrix(es_coordsys_gyr_frame_t *activeGyrFrame)
{
    activeGyrFrame->gyr1 = activeFrames.gyroscopeFrame.gyr1;
    activeGyrFrame->gyr2 = activeFrames.gyroscopeFrame.gyr2;
    activeGyrFrame->gyr3 = activeFrames.gyroscopeFrame.gyr3;
}

void coordSys_setMagMatrix(const es_coordsys_mag_frame_t *newMagFrame)
{
    activeFrames.magnetometerFrame.mag_x = newMagFrame->mag_x;
    activeFrames.magnetometerFrame.mag_y = newMagFrame->mag_y;
    activeFrames.magnetometerFrame.mag_z = newMagFrame->mag_z;

    /* Call the rotation matrix builder */
    fs_coordSys_build_mag_matrix();
}

void coordSys_getMagMatrix(es_coordsys_mag_frame_t *activeMagFrame)
{
    activeMagFrame->mag_x = activeFrames.magnetometerFrame.mag_x;
    activeMagFrame->mag_y = activeFrames.magnetometerFrame.mag_y;
    activeMagFrame->mag_z = activeFrames.magnetometerFrame.mag_z;
}

void coordSys_setMtqMatrix(const es_coordsys_mtq_frame_t *newMtqFrame)
{
    activeFrames.magnetorquerFrame.mtq1 = newMtqFrame->mtq1;
    activeFrames.magnetorquerFrame.mtq2 = newMtqFrame->mtq2;
    activeFrames.magnetorquerFrame.mtq3 = newMtqFrame->mtq3;

    /* Call the rotation matrix builder */
    fs_coordSys_build_mtq_matrix();
}

void coordSys_getMtqMatrix(es_coordsys_mtq_frame_t *activeMtqFrame)
{
    activeMtqFrame->mtq1 = activeFrames.magnetorquerFrame.mtq1;
    activeMtqFrame->mtq2 = activeFrames.magnetorquerFrame.mtq2;
    activeMtqFrame->mtq3 = activeFrames.magnetorquerFrame.mtq3;
}

void coordSys_setCssMatrix(const es_coordsys_css_frame_t *newCssFrame)
{
    activeFrames.coarseSunSensorFrame.css1 = newCssFrame->css1;
    activeFrames.coarseSunSensorFrame.css2 = newCssFrame->css2;
    activeFrames.coarseSunSensorFrame.css3 = newCssFrame->css3;
    activeFrames.coarseSunSensorFrame.css4 = newCssFrame->css4;
    activeFrames.coarseSunSensorFrame.css5 = newCssFrame->css5;
    activeFrames.coarseSunSensorFrame.css6 = newCssFrame->css6;

    /* Call the rotation matrix builder */
    fs_coordSys_build_css_matrix();
}

void coordSys_getCssMatrix(es_coordsys_css_frame_t *activeCssFrame)
{
    activeCssFrame->css1 = activeFrames.coarseSunSensorFrame.css1;
    activeCssFrame->css2 = activeFrames.coarseSunSensorFrame.css2;
    activeCssFrame->css3 = activeFrames.coarseSunSensorFrame.css3;
    activeCssFrame->css4 = activeFrames.coarseSunSensorFrame.css4;
    activeCssFrame->css5 = activeFrames.coarseSunSensorFrame.css5;
    activeCssFrame->css6 = activeFrames.coarseSunSensorFrame.css6;
}

void coordSys_setAccMatrix(const es_coordsys_acc_frame_t *newAccFrame)
{
    activeFrames.accelerometerFrame.acc_x = newAccFrame->acc_x;
    activeFrames.accelerometerFrame.acc_y = newAccFrame->acc_y;
    activeFrames.accelerometerFrame.acc_z = newAccFrame->acc_z;

    /* Call the rotation matrix builder */
    fs_coordSys_build_acc_matrix();
}

void coordSys_getAccMatrix(es_coordsys_acc_frame_t *activeAccFrame)
{
    activeAccFrame->acc_x = activeFrames.accelerometerFrame.acc_x;
    activeAccFrame->acc_y = activeFrames.accelerometerFrame.acc_y;
    activeAccFrame->acc_z = activeFrames.accelerometerFrame.acc_z;
}

void coordSys_save_config_to_NVM(void)
{
    Nvm_SetBlockById(NVM_BLOCK_COORDINATE_FRAMES, &activeFrames, NVMSETBLOCK_STORE_IMMEDIATELY);
}

void coordSys_load_config_from_NVM(void)
{
    es_coordsys_frames_t loadedConfig;

    /* AA TODO: this probably needs an "is input config valid" check, even though it loads
     * an NVM config that SHOULD HAVE BEEN checked upon saving */
    Nvm_GetBlockById(NVM_BLOCK_COORDINATE_FRAMES, &loadedConfig);

    activeFrames = loadedConfig;
}

/**********************************************************************
 *
 * Static function definitions
 *
 **********************************************************************/
/** @brief Build the gyroscope rotation matrix based on activeFrames.gyroscopeFrame variable */
static void fs_coordSys_build_gyr_matrix(void)
{
    /* Zero out the matrix */
    memset(gyr_rot_mat, 0, sizeof(gyr_rot_mat));

    /* Assign first gyroscope to correct rotation matrix row */
    fs_coordSys_build_gyr_matrix_col(activeFrames.gyroscopeFrame.gyr1, 1);

    /* Assign second gyroscope to correct rotation matrix row */
    fs_coordSys_build_gyr_matrix_col(activeFrames.gyroscopeFrame.gyr2, 2);

    /* Assign third gyroscope to correct rotation matrix row */
    fs_coordSys_build_gyr_matrix_col(activeFrames.gyroscopeFrame.gyr3, 3);
}

/** @brief Build a column of the gyroscope rotation matrix
 *  @param[in] gyroscopeToMap assigned hardware gyroscope
 *  @param[in] colNum         column number of the rotation matrix to build */
static void fs_coordSys_build_gyr_matrix_col(es_coordsys_satellite_axes_t gyroscopeToMap, uint8_t colNum)
{
    /* Correct for proper array indexing */
    uint8_t idx = colNum - 1;

    if ((SAT_X_AXIS_POSITIVE == gyroscopeToMap) || (SAT_X_AXIS_NEGATIVE == gyroscopeToMap))
    {
        gyr_rot_mat[idx + 0] = fs_coordSys_map_axis_to_value(gyroscopeToMap);
    }
    else if ((SAT_Y_AXIS_POSITIVE == gyroscopeToMap) || (SAT_Y_AXIS_NEGATIVE == gyroscopeToMap))
    {
        gyr_rot_mat[idx + 3] = fs_coordSys_map_axis_to_value(gyroscopeToMap);
    }
    else
    {
        gyr_rot_mat[idx + 6] = fs_coordSys_map_axis_to_value(gyroscopeToMap);
    }
}

/** @brief Build the magnetometer rotation matrix based on activeFrames.magnetometerFrame variable */
static void fs_coordSys_build_mag_matrix(void)
{
    /* Zero out the matrix */
    memset(mag_rot_mat, 0, sizeof(mag_rot_mat));

    /* Assign first magnetometer axis to correct rotation matrix row */
    fs_coordSys_build_mag_matrix_col(activeFrames.magnetometerFrame.mag_x, 1);

    /* Assign second magnetometer axis to correct rotation matrix row */
    fs_coordSys_build_mag_matrix_col(activeFrames.magnetometerFrame.mag_y, 2);

    /* Assign third magnetometer axis to correct rotation matrix row */
    fs_coordSys_build_mag_matrix_col(activeFrames.magnetometerFrame.mag_z, 3);
}

/** @brief Build a column of the magnetometer rotation matrix
 *  @param[in] magnetometerToMap assigned hardware magnetometer
 *  @param[in] colNum            column number of the rotation matrix to build */
static void fs_coordSys_build_mag_matrix_col(es_coordsys_satellite_axes_t magnetometerToMap, uint8_t colNum)
{
    /* Correct for proper array indexing */
    uint8_t idx = colNum - 1;

    if ((SAT_X_AXIS_POSITIVE == magnetometerToMap) || (SAT_X_AXIS_NEGATIVE == magnetometerToMap))
    {
        mag_rot_mat[idx + 0] = fs_coordSys_map_axis_to_value(magnetometerToMap);
    }
    else if ((SAT_Y_AXIS_POSITIVE == magnetometerToMap) || (SAT_Y_AXIS_NEGATIVE == magnetometerToMap))
    {
        mag_rot_mat[idx + 3] = fs_coordSys_map_axis_to_value(magnetometerToMap);
    }
    else
    {
        mag_rot_mat[idx + 6] = fs_coordSys_map_axis_to_value(magnetometerToMap);
    }
}

/** @brief Build the magnetorquer rotation matrix based on activeFrames.magnetorquerFrame variable */
static void fs_coordSys_build_mtq_matrix(void)
{
    /* Zero out the matrix */
    memset(mtq_rot_mat, 0, sizeof(mtq_rot_mat));

    /* Assign first magnetorquer to correct rotation matrix row */
    fs_coordSys_build_mtq_matrix_col(activeFrames.magnetorquerFrame.mtq1, 1);

    /* Assign second magnetorquer to correct rotation matrix row */
    fs_coordSys_build_mtq_matrix_col(activeFrames.magnetorquerFrame.mtq2, 2);

    /* Assign third magnetorquer to correct rotation matrix row */
    fs_coordSys_build_mtq_matrix_col(activeFrames.magnetorquerFrame.mtq3, 3);

    /* Invert the resulting matrix in order to compute the correct transformations */
    fs_coordSys_transpose_mtq_matrix();
}

/** @brief Build a column of the magnetorquer rotation matrix
 *  @param[in] magnetorquerToMap assigned hardware magnetorquer
 *  @param[in] colNum            column number of the rotation matrix to build */
static void fs_coordSys_build_mtq_matrix_col(es_coordsys_satellite_axes_t magnetorquerToMap, uint8_t colNum)
{
    /* Correct for proper array indexing */
    uint8_t idx = colNum - 1;

    if ((SAT_X_AXIS_POSITIVE == magnetorquerToMap) || (SAT_X_AXIS_NEGATIVE == magnetorquerToMap))
    {
        mtq_rot_mat[idx + 0] = fs_coordSys_map_axis_to_value(magnetorquerToMap);
    }
    else if ((SAT_Y_AXIS_POSITIVE == magnetorquerToMap) || (SAT_Y_AXIS_NEGATIVE == magnetorquerToMap))
    {
        mtq_rot_mat[idx + 3] = fs_coordSys_map_axis_to_value(magnetorquerToMap);
    }
    else
    {
        mtq_rot_mat[idx + 6] = fs_coordSys_map_axis_to_value(magnetorquerToMap);
    }
}

/** @brief Transpose the magnetorquer matrix to get the inverted matrix. This is required because data flow is inverted with magnetorquers
 * compared to sensors */
static void fs_coordSys_transpose_mtq_matrix(void)
{
    int8_t temp[9];

    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            temp[i * 3 + j] = mtq_rot_mat[j * 3 + i];
        }
    }

    for (uint8_t k = 0; k < 9; k++) {
        mtq_rot_mat[k] = temp[k];
    }
}

/** @brief Build the coarse sun sensor rotation matrix based on activeFrames.coarseSunSensorFrame variable */
static void fs_coordSys_build_css_matrix(void)
{
    /* Zero out the matrix */
    memset(css_rot_mat, 0, sizeof(css_rot_mat));

    /* Assign first coarse sun sensor to correct rotation matrix row */
    fs_coordSys_build_css_matrix_col(activeFrames.coarseSunSensorFrame.css1, 1);

    /* Assign second coarse sun sensor to correct rotation matrix row */
    fs_coordSys_build_css_matrix_col(activeFrames.coarseSunSensorFrame.css2, 2);

    /* Assign third coarse sun sensor to correct rotation matrix row */
    fs_coordSys_build_css_matrix_col(activeFrames.coarseSunSensorFrame.css3, 3);

    /* Assign fourth coarse sun sensor to correct rotation matrix row */
    fs_coordSys_build_css_matrix_col(activeFrames.coarseSunSensorFrame.css4, 4);

    /* Assign fifth coarse sun sensor to correct rotation matrix row */
    fs_coordSys_build_css_matrix_col(activeFrames.coarseSunSensorFrame.css5, 5);

    /* Assign sixth coarse sun sensor to correct rotation matrix row */
    fs_coordSys_build_css_matrix_col(activeFrames.coarseSunSensorFrame.css6, 6);
}

/** @brief Build a column of the coarse sun sensor rotation matrix
 *  @param[in] coarseSunSensorToMap assigned hardware coarse sun sensor
 *  @param[in] colNum               column number of the rotation matrix to build */
static void fs_coordSys_build_css_matrix_col(es_coordsys_satellite_axes_t coarseSunSensorToMap, uint8_t colNum)
{
    /* AA TODO: this deserves to be remade using switch case or something completely better */

    /* Correct for proper array indexing */
    uint8_t idx = colNum - 1;

    if (SAT_X_AXIS_POSITIVE == coarseSunSensorToMap)
    {
        css_rot_mat[idx +  0] = 1;
    }
    else if (SAT_Y_AXIS_POSITIVE == coarseSunSensorToMap)
    {
        css_rot_mat[idx +  6] = 1;
    }
    else if (SAT_Z_AXIS_POSITIVE == coarseSunSensorToMap)
    {
        css_rot_mat[idx + 12] = 1;
    }
    else if (SAT_X_AXIS_NEGATIVE == coarseSunSensorToMap)
    {
        css_rot_mat[idx + 18] = 1;
    }
    else if (SAT_Y_AXIS_NEGATIVE == coarseSunSensorToMap)
    {
        css_rot_mat[idx + 24] = 1;
    }
    else
    {
        css_rot_mat[idx + 30] = 1;
    }
}

/** @brief Map an axis to a number for the rotation matrix
 *  @param[in] axisToMap axis to be mapped into a value @ref es_coordsys_satellite_axes_t
 *  @return int8 - +1 for an axis that is "POSITIVE" or -1 for an axis that is "NEGATIVE" */
static int8_t fs_coordSys_map_axis_to_value(es_coordsys_satellite_axes_t axisToMap)
{
	int8_t retVal = 0;

    /* If it's a positive axis, return +1 */
    if (SAT_Z_AXIS_POSITIVE >= axisToMap)
    {
    	retVal = 1;
    }
    /* If it's a negative axis, return -1 */
    else
    {
    	retVal = -1;
    }

    return retVal;
    /* AA TODO: this should probably be extended to catch values outside of the 6 values from the enum and return an error */
}

/** @brief Build the accelerometer rotation matrix based on activeFrames.accelerometerFrame variable */
static void fs_coordSys_build_acc_matrix(void)
{
    /* Zero out the matrix */
    memset(acc_rot_mat, 0, sizeof(acc_rot_mat));

    /* Assign first accelerometer axis to correct rotation matrix row */
    fs_coordSys_build_acc_matrix_col(activeFrames.accelerometerFrame.acc_x, 1);

    /* Assign second accelerometer axis to correct rotation matrix row */
    fs_coordSys_build_acc_matrix_col(activeFrames.accelerometerFrame.acc_y, 2);

    /* Assign third accelerometer axis to correct rotation matrix row */
    fs_coordSys_build_acc_matrix_col(activeFrames.accelerometerFrame.acc_z, 3);
}

/** @brief Build a column of the accelerometer rotation matrix
 *  @param[in] acceleromterToMap assigned hardware accelerometer
 *  @param[in] colNum            column number of the rotation matrix to build */
static void fs_coordSys_build_acc_matrix_col(es_coordsys_satellite_axes_t accelerometerToMap, uint8_t colNum)
{
    /* Correct for proper array indexing */
    uint8_t idx = colNum - 1;

    if ((SAT_X_AXIS_POSITIVE == accelerometerToMap) || (SAT_X_AXIS_NEGATIVE == accelerometerToMap))
    {
        acc_rot_mat[idx + 0] = fs_coordSys_map_axis_to_value(accelerometerToMap);
    }
    else if ((SAT_Y_AXIS_POSITIVE == accelerometerToMap) || (SAT_Y_AXIS_NEGATIVE == accelerometerToMap))
    {
        acc_rot_mat[idx + 3] = fs_coordSys_map_axis_to_value(accelerometerToMap);
    }
    else
    {
        acc_rot_mat[idx + 6] = fs_coordSys_map_axis_to_value(accelerometerToMap);
    }
}

/* **************************************************************************************** */
