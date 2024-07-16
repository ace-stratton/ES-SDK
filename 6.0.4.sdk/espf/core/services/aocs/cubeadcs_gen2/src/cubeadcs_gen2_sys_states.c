/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup cubeadcs_gen2
 * @{
 *
 * @file     cubeadcs_gen2_sys_states.c
 * @brief    Cubeadcs Gen2 system states source file.
 *
 * @}
 */

#include "es_cdef.h"
#include "assertions.h"
#include "cubeadcs_gen2_sys_states.h"

/** @brief Control modes descriptions - each mode relates to a control group type. This is described here. */
STATIC const cubeadcs_gen2_control_mode_info_t control_modes_desc[CUBEADCS_GEN2_MAX_NUM_OF_CONTROL_MODES] = {
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_NONE,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_NO_CONTROL,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_BDOT,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_DETUMB_AND_SPIN,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_YSPIN,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_DETUMB_AND_SPIN,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_BDOT_3,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_DETUMB_AND_SPIN,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_DETUMBLE,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_DETUMB_AND_SPIN,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_SUN_YSPIN,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_DETUMB_AND_SPIN,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_ZSPIN,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_DETUMB_AND_SPIN,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_SUN_ZSPIN,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_DETUMB_AND_SPIN,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_GGBOOM,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_GG,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_GGSUN,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_GG,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_YWHEEL_INIT,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_Y_MOMENTUM,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_YWHEEL,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_Y_MOMENTUM,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_XYZWHEEL,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_XYZ_WHEEL,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_SUN_TRACK,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_XYZ_WHEEL,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_TGT_TRACK,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_XYZ_WHEEL,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_TGT_STEER,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_XYZ_WHEEL,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_GND_TRACK,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_XYZ_WHEEL,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_IRC_TRACK,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_XYZ_WHEEL,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_MOON_TRACK,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_XYZ_WHEEL,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_SAT_TRACK,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_XYZ_WHEEL,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_YAW_SUN,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_XYZ_WHEEL,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_YAW_TARGET,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_XYZ_WHEEL,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_ROLL_SUN,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_XYZ_WHEEL,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_ROLL_TARGET,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_XYZ_WHEEL,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_YAW_TARGET_BEST,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_XYZ_WHEEL,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_STOP_RW,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_WHEEL_MANAGEMENET,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_HXYZ_RW,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_WHEEL_MANAGEMENET,
    },
    {
        .control_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_USER,
        .control_group = CUBEADCS_GEN2_CONTROL_GROUP_USER,
    }
};
/** @brief Estimator modes descriptions - Estimator modes are stored as an enum with specific values. In order to make combination checks easier a link to a "group" description is added here. */
STATIC const cubeadcs_gen2_estimator_mode_info_t est_modes_desc[CUBEADCS_GEN2_MAX_NUM_OF_ESTIMATOR_MODES] = {
    {
        .estimator_type = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_NONE,
        .estimator_group = CUBEADCS_GEN2_EST_GROUP_NO_EST,
    },
    {
        .estimator_type = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_GYRO,
        .estimator_group = CUBEADCS_GEN2_EST_GROUP_GYRO,
    },
    {
        .estimator_type = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_MAG_RKF,
        .estimator_group = CUBEADCS_GEN2_EST_GROUP_MAG,
    },
    {
        .estimator_type = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_PITCH_RKF,
        .estimator_group = CUBEADCS_GEN2_EST_GROUP_MAG_PITCH,
    },
    {
        .estimator_type = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_TRIAD,
        .estimator_group = CUBEADCS_GEN2_EST_GROUP_TRIAD,
    },
    {
        .estimator_type = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_FULL_EKF,
        .estimator_group = CUBEADCS_GEN2_EST_GROUP_FULL_STATE,
    },
    {
        .estimator_type = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_GYRO_EKF,
        .estimator_group = CUBEADCS_GEN2_EST_GROUP_GYRO_EKF,
    },
    {
        .estimator_type = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_USER,
        .estimator_group = CUBEADCS_GEN2_EST_GROUP_USER,
    }
};
/** @brief Valid estimation and control mode combinations - based on Table 6, p.55 of the User Manual CS-DEV.UM_CA-01, Revision 1.04 */
STATIC const bool valid_combos[CUBEADCS_GEN2_CONTROL_GROUP_MAX][CUBEADCS_GEN2_EST_GROUP_MAX] =
{
    {true , true , true , true , true , true , true, true}, // CUBEADCS_GEN2_CONTROL_GROUP_NO_CONTROL
    {false, true , true , true , true , false, true, true}, // CUBEADCS_GEN2_CONTROL_GROUP_DETUMB_AND_SPIN
    {false, false, false, false, false, true , true, true}, // CUBEADCS_GEN2_CONTROL_GROUP_GG
    {false, false, false, true , false, true , true, true}, // CUBEADCS_GEN2_CONTROL_GROUP_Y_MOMENTUM
    {false, false, false, false, false, true , true, true}, // CUBEADCS_GEN2_CONTROL_GROUP_XYZ_WHEEL
    {true , true , true , true , true , true , true, true}, // CUBEADCS_GEN2_CONTROL_GROUP_WHEEL_MANAGEMENET
    {true , true , true , true , true , true , true, true}, // CUBEADCS_GEN2_CONTROL_GROUP_USER
};

STATIC bool fs_cubeadcs_gen2_get_control_mode_info(const TctlmCubeComputerControlProgram8_ConModeSelect control_mode, cubeadcs_gen2_control_group_t * const p_control_mode_group);
STATIC bool fs_cubeadcs_gen2_get_estimator_mode_info(const TctlmCubeComputerControlProgram8_EstModeSelect estimation_mode, cubeadcs_gen2_est_group_t * const p_estimation_mode_group);
STATIC bool fs_cubeadcs_gen2_binary_search(uint8_t id, uint8_t size, uint8_t (*group)(uint8_t), uint8_t *p_found_id_dst);
STATIC uint8_t fs_cubeadcs_gen2_get_control_mode_group(uint8_t index);
STATIC uint8_t fs_cubeadcs_gen2_get_est_mode_group(uint8_t index);

bool cubeadcs_gen2_is_sys_state_combo_valid(const TctlmCubeComputerControlProgram8_ConModeSelect control_mode, const TctlmCubeComputerControlProgram8_EstModeSelect estimation_mode)
{
    bool is_valid = false;

    uint8_t control_mode_info_id;
    uint8_t estimator_mode_info_id;

    if ( (true == fs_cubeadcs_gen2_get_control_mode_info(control_mode, &control_mode_info_id)) &&
            (true == fs_cubeadcs_gen2_get_estimator_mode_info(estimation_mode, &estimator_mode_info_id)) )
    {
        is_valid = valid_combos[control_mode_info_id][estimator_mode_info_id];
    }

    return is_valid;
}

/** @brief Get control mode group 
 * 
 *  @param[in] control_mode Control mode
 *  @param[out] p_control_mode_group Control mode group
 * 
 *  @return true if found, false otherwise
*/
STATIC bool fs_cubeadcs_gen2_get_control_mode_info(const TctlmCubeComputerControlProgram8_ConModeSelect control_mode, cubeadcs_gen2_control_group_t * const p_control_mode_group)
{
    CRIT_ASSERT(NULL != p_control_mode_group);

    bool op_res = false;
    uint8_t found_id = 0;

    if ( true == fs_cubeadcs_gen2_binary_search((uint8_t)control_mode, CUBEADCS_GEN2_MAX_NUM_OF_CONTROL_MODES, fs_cubeadcs_gen2_get_control_mode_group, &found_id) )
    {
        op_res = true;

        *p_control_mode_group = control_modes_desc[found_id].control_group;
    }

    return op_res;


}

/** @brief Get estimator mode group
 * 
 *  @param[in] estimation_mode Estimator mode
 *  @param[out] p_estimation_mode_group Estimator mode group
 * 
 *  @return true if found, false otherwise
 * 
*/
STATIC bool fs_cubeadcs_gen2_get_estimator_mode_info(const TctlmCubeComputerControlProgram8_EstModeSelect estimation_mode, cubeadcs_gen2_est_group_t * const p_estimation_mode_group)
{
    CRIT_ASSERT(NULL != p_estimation_mode_group);

    bool op_res = false;
    uint8_t found_id = 0;

    if ( true == fs_cubeadcs_gen2_binary_search((uint8_t)estimation_mode, CUBEADCS_GEN2_MAX_NUM_OF_ESTIMATOR_MODES, fs_cubeadcs_gen2_get_est_mode_group, &found_id) )
    {
        op_res = true;

        *p_estimation_mode_group = est_modes_desc[found_id].estimator_group;
    }

    return op_res;
}

/** @brief Basic binary search to search for an id in a random sorted array
 *
 * 	@param[in] uint8_t id the id to search for
 * 	@param[in] uint8_t size the size of the array
 * 	@param[in] uint8_t (*group)(uint8_t) a function that returns the id of the element at the given index
 *
 * 	@param[out] uint8_t * found_id_dst the id of the element that was found
 *
 * 	@retval true found a match
 * 	@retval false failed to find a match
 */
STATIC bool fs_cubeadcs_gen2_binary_search(uint8_t id, uint8_t size, uint8_t (*group)(uint8_t), uint8_t *p_found_id_dst)
{
    CRIT_ASSERT(NULL != p_found_id_dst);

    bool found = false;

    uint8_t bottom = 0;
    uint8_t top = size - 1;

    while (bottom <= top)
    {
        uint8_t current = (bottom + top) / 2;

        uint8_t is_this_the_id = group(current);

        if (id < is_this_the_id)
        {
            top = current - 1;
        }
        else if (id > is_this_the_id)
        {
            bottom = current + 1;
        }
        else
        {
            *p_found_id_dst = current;
            found = true;
            break;
        }
    }

    return found;
}

/** @brief Get the control mode group out of the control mode info array based on an input index
 * 
 * @param[in] index Index of the control mode info array
 * 
 * @return Control mode group
*/
STATIC uint8_t fs_cubeadcs_gen2_get_control_mode_group(uint8_t index)
{
    CRIT_ASSERT(index < CUBEADCS_GEN2_MAX_NUM_OF_CONTROL_MODES);

    return (uint8_t)control_modes_desc[index].control_mode;
}

/** @brief Get the estimator mode group out of the estimator mode info array based on an input index
 * 
 * @param[in] index Index of the estimator mode info array
 * 
 * @return Estimator mode group
 * 
*/
STATIC uint8_t fs_cubeadcs_gen2_get_est_mode_group(uint8_t index)
{
    CRIT_ASSERT(index < CUBEADCS_GEN2_MAX_NUM_OF_ESTIMATOR_MODES);
    
    return (uint8_t)est_modes_desc[index].estimator_type;
}
