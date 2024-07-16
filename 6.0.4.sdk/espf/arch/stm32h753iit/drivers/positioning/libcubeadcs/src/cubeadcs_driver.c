/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup cubeadcs
 * @{
 *
 * @file     cubeadcs_driver.c
 * @brief    Low-level driver used to communicate with the CubeADCS over UART.
 *
 * @}
 */

/*
*********************************************************************************************
* INCLUDES
*********************************************************************************************
*/

#include "cubeadcs_driver.h"
#include "cubeadcs_crc.h"
#include "cmsis_os.h"
#include "es_exeh.h"
#include "assertions.h"
#include "main.h"

#include "cubeadcs_ftransfer.h"

#include <string.h>

/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/
/** @brief Array describing all bootloader command requests and response lengths (TC and TLM)  */
STATIC const CubeADCS_Cmd_t CubeADCS_Boot_Cmd_List[] = {

        /* Telecommands */
        {   1,   { 1, CUBEADCS_TC_RPLY_LEN } },    /* TC ID 1 - Common Telecommands */
        {   2,   { 6, CUBEADCS_TC_RPLY_LEN } },
        {   3,   { 1, CUBEADCS_TC_RPLY_LEN } },
        {   4,   { 0, CUBEADCS_TC_RPLY_LEN } },
        {   5,   { 0, CUBEADCS_TC_RPLY_LEN } },
        {   6,   { 0, CUBEADCS_TC_RPLY_LEN } },
        {   7,   { 0, CUBEADCS_TC_RPLY_LEN } },
        {   8,   { 2, CUBEADCS_TC_RPLY_LEN } },
        {   9,   { 2, CUBEADCS_TC_RPLY_LEN } },

		{  33,   { 1, CUBEADCS_TC_RPLY_LEN } },

		{ 100,   { 1, CUBEADCS_TC_RPLY_LEN } },
        { 101,   { 0, CUBEADCS_TC_RPLY_LEN } },
        { 102,   { 1, CUBEADCS_TC_RPLY_LEN } },
        { 103,   { 2, CUBEADCS_TC_RPLY_LEN } },

        { 108,   { 3, CUBEADCS_TC_RPLY_LEN } },

        { 112,   { 8, CUBEADCS_TC_RPLY_LEN } },
        { 113,   { 0, CUBEADCS_TC_RPLY_LEN } },
        { 114,   { 2, CUBEADCS_TC_RPLY_LEN } },
        { 115,  { 22, CUBEADCS_TC_RPLY_LEN } },
        { 116,   { 7, CUBEADCS_TC_RPLY_LEN } },
        { 117,   { 0, CUBEADCS_TC_RPLY_LEN } },
        { 118,   { 0, CUBEADCS_TC_RPLY_LEN } },
        { 119,   { 2, CUBEADCS_TC_RPLY_LEN } },
        { 120,  { 16, CUBEADCS_TC_RPLY_LEN } },
        { 121,  { 16, CUBEADCS_TC_RPLY_LEN } },
        { 122,  { 16, CUBEADCS_TC_RPLY_LEN } },
        { 123,  { 16, CUBEADCS_TC_RPLY_LEN } },
        { 124,  { 16, CUBEADCS_TC_RPLY_LEN } },
        { 125,  { 16, CUBEADCS_TC_RPLY_LEN } },
        { 126,  { 16, CUBEADCS_TC_RPLY_LEN } },
        { 127,  { 16, CUBEADCS_TC_RPLY_LEN } },

        /* Telemetry */
        { 128, { CUBEADCS_TLM_WRT_LEN,   9 } },
        { 129, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 130, { CUBEADCS_TLM_WRT_LEN,   3 } },
        { 131, { CUBEADCS_TLM_WRT_LEN,   2 } },
        { 132, { CUBEADCS_TLM_WRT_LEN,   7 } },

        { 134, { CUBEADCS_TLM_WRT_LEN,   3 } },

        { 140, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 141, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 142, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 143, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 144, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 145, { CUBEADCS_TLM_WRT_LEN,   3 } },

        { 232, { CUBEADCS_TLM_WRT_LEN,   9 } },
        { 233, { CUBEADCS_TLM_WRT_LEN,   2 } },
		{ 234, { CUBEADCS_TLM_WRT_LEN,   2 } },
        { 240, { CUBEADCS_TLM_WRT_LEN,   5 } },
        { 241, { CUBEADCS_TLM_WRT_LEN,  23 } },
        { 242, { CUBEADCS_TLM_WRT_LEN,   6 } },
        { 243, { CUBEADCS_TLM_WRT_LEN,  13 } },
        { 244, { CUBEADCS_TLM_WRT_LEN,   2 } },
        { 245, { CUBEADCS_TLM_WRT_LEN,   2 } },
        { 246, { CUBEADCS_TLM_WRT_LEN,   3 } },
        { 247, { CUBEADCS_TLM_WRT_LEN,  17 } },
        { 248, { CUBEADCS_TLM_WRT_LEN,  17 } },
        { 249, { CUBEADCS_TLM_WRT_LEN,  17 } },
        { 250, { CUBEADCS_TLM_WRT_LEN,  17 } },
        { 251, { CUBEADCS_TLM_WRT_LEN,  17 } },
        { 252, { CUBEADCS_TLM_WRT_LEN,  17 } },
        { 253, { CUBEADCS_TLM_WRT_LEN,  17 } },
        { 254, { CUBEADCS_TLM_WRT_LEN,  17 } },
};

/** @brief Array describing all ACP command requests and response lengths (TC and TLM)  */
STATIC const CubeADCS_Cmd_t CubeADCS_ACP_Cmd_List[] = {

        /* Telecommands */
        {   1,   { 1, CUBEADCS_TC_RPLY_LEN } },    /* TC ID 1 - Common Telecommands */
        {   2,   { 6, CUBEADCS_TC_RPLY_LEN } },
        {   3,   { 1, CUBEADCS_TC_RPLY_LEN } },
        {   4,   { 0, CUBEADCS_TC_RPLY_LEN } },
        {   5,   { 0, CUBEADCS_TC_RPLY_LEN } },
        {   6,   { 0, CUBEADCS_TC_RPLY_LEN } },
        {   7,   { 1, CUBEADCS_TC_RPLY_LEN } },
        {   8,   { 2, CUBEADCS_TC_RPLY_LEN } },
        {   9,   { 2, CUBEADCS_TC_RPLY_LEN } },
        {  10,   { 1, CUBEADCS_TC_RPLY_LEN } },
        {  11,   { 3, CUBEADCS_TC_RPLY_LEN } },
        {  12,   { 1, CUBEADCS_TC_RPLY_LEN } },
        {  13,   { 3, CUBEADCS_TC_RPLY_LEN } },
        {  14,   { 1, CUBEADCS_TC_RPLY_LEN } },
        {  15,   { 6, CUBEADCS_TC_RPLY_LEN } },
        {  16,   { 6, CUBEADCS_TC_RPLY_LEN } },
        {  17,   { 6, CUBEADCS_TC_RPLY_LEN } },
        {  18,   { 0, CUBEADCS_TC_RPLY_LEN } },
        {  19, { 127, CUBEADCS_TC_RPLY_LEN } },
        {  20, { 504, CUBEADCS_TC_RPLY_LEN } },
        {  21,   { 3, CUBEADCS_TC_RPLY_LEN } },
        {  22,   { 4, CUBEADCS_TC_RPLY_LEN } },
        {  23,  { 10, CUBEADCS_TC_RPLY_LEN } },
        {  24,  { 21, CUBEADCS_TC_RPLY_LEN } },
        {  25, { 112, CUBEADCS_TC_RPLY_LEN } },
        {  26,  { 30, CUBEADCS_TC_RPLY_LEN } },
        {  27,  { 31, CUBEADCS_TC_RPLY_LEN } },
        {  28,  { 30, CUBEADCS_TC_RPLY_LEN } },
        {  29,  { 96, CUBEADCS_TC_RPLY_LEN } },
        {  30, { 173, CUBEADCS_TC_RPLY_LEN } },
        {  31,   { 1, CUBEADCS_TC_RPLY_LEN } },
        {  32,   { 0, CUBEADCS_TC_RPLY_LEN } },
		{  33,   { 1, CUBEADCS_TC_RPLY_LEN } },
		{  34,   { 6, CUBEADCS_TC_RPLY_LEN } },

        {  36,  { 30, CUBEADCS_TC_RPLY_LEN } },
        {  37,  { 53, CUBEADCS_TC_RPLY_LEN } },
        {  38,  { 14, CUBEADCS_TC_RPLY_LEN } },
        {  39,  { 20, CUBEADCS_TC_RPLY_LEN } },
        {  40,  { 13, CUBEADCS_TC_RPLY_LEN } },
        {  41,  { 24, CUBEADCS_TC_RPLY_LEN } },

        {  45,  { 64, CUBEADCS_TC_RPLY_LEN } },
        {  46,   { 8, CUBEADCS_TC_RPLY_LEN } },
        {  47,   { 8, CUBEADCS_TC_RPLY_LEN } },
        {  48,   { 8, CUBEADCS_TC_RPLY_LEN } },
        {  49,   { 8, CUBEADCS_TC_RPLY_LEN } },
        {  50,   { 8, CUBEADCS_TC_RPLY_LEN } },
        {  51,   { 8, CUBEADCS_TC_RPLY_LEN } },
        {  52,   { 8, CUBEADCS_TC_RPLY_LEN } },
        {  53,   { 8, CUBEADCS_TC_RPLY_LEN } },
        {  54,  { 13, CUBEADCS_TC_RPLY_LEN } },
        {  55,  { 12, CUBEADCS_TC_RPLY_LEN } },
        {  56,   { 1, CUBEADCS_TC_RPLY_LEN } },
        {  57,   { 3, CUBEADCS_TC_RPLY_LEN } },

        {  63,   { 0, CUBEADCS_TC_RPLY_LEN } },
        {  64,   { 0, CUBEADCS_TC_RPLY_LEN } },

        {  80,   { 2, CUBEADCS_TC_RPLY_LEN } },

        { 104,  { 13, CUBEADCS_TC_RPLY_LEN } },
        { 105,  { 13, CUBEADCS_TC_RPLY_LEN } },
        { 106,  { 12, CUBEADCS_TC_RPLY_LEN } },

        { 108,   { 3, CUBEADCS_TC_RPLY_LEN } },

        { 112,   { 8, CUBEADCS_TC_RPLY_LEN } },
        { 113,   { 0, CUBEADCS_TC_RPLY_LEN } },
        { 114,   { 2, CUBEADCS_TC_RPLY_LEN } },
        { 115,  { 22, CUBEADCS_TC_RPLY_LEN } },
        { 116,   { 7, CUBEADCS_TC_RPLY_LEN } },
        { 117,   { 0, CUBEADCS_TC_RPLY_LEN } },
        { 118,   { 0, CUBEADCS_TC_RPLY_LEN } },
        { 119,   { 2, CUBEADCS_TC_RPLY_LEN } },
        { 120,  { 16, CUBEADCS_TC_RPLY_LEN } },
        { 121,  { 16, CUBEADCS_TC_RPLY_LEN } },
        { 122,  { 16, CUBEADCS_TC_RPLY_LEN } },
        { 123,  { 16, CUBEADCS_TC_RPLY_LEN } },
        { 124,  { 16, CUBEADCS_TC_RPLY_LEN } },
        { 125,  { 16, CUBEADCS_TC_RPLY_LEN } },
        { 126,  { 16, CUBEADCS_TC_RPLY_LEN } },
        { 127,  { 16, CUBEADCS_TC_RPLY_LEN } },

        /* Telemetry */
        { 128, { CUBEADCS_TLM_WRT_LEN,   9 } },
        { 129, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 130, { CUBEADCS_TLM_WRT_LEN,   3 } },
        { 131, { CUBEADCS_TLM_WRT_LEN,   2 } },
        { 132, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 133, { CUBEADCS_TLM_WRT_LEN,   4 } },
        { 134, { CUBEADCS_TLM_WRT_LEN,   3 } },
        { 135, { CUBEADCS_TLM_WRT_LEN,   2 } },
        { 136, { CUBEADCS_TLM_WRT_LEN,   4 } },
        { 137, { CUBEADCS_TLM_WRT_LEN,   5 } },
        { 138, { CUBEADCS_TLM_WRT_LEN,  11 } },
        { 139, { CUBEADCS_TLM_WRT_LEN,  22 } },
        { 140, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 141, { CUBEADCS_TLM_WRT_LEN,   7 } },
		{ 142, { CUBEADCS_TLM_WRT_LEN,   7 } },
		{ 143, { CUBEADCS_TLM_WRT_LEN,   7 } },
		{ 144, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 145, { CUBEADCS_TLM_WRT_LEN,   3 } },
        { 146, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 147, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 148, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 149, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 150, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 151, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 152, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 153, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 154, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 155, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 156, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 157, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 158, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 159, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 160, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 161, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 162, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 163, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 164, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 165, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 166, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 167, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 168, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 169, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 170, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 171, { CUBEADCS_TLM_WRT_LEN,   5 } },
        { 172, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 173, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 174, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 175, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 176, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 177, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 178, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 179, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 180, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 181, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 182, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 183, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 184, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 185, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 186, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 187, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 188, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 189, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 190, { CUBEADCS_TLM_WRT_LEN,  55 } },
        { 191, { CUBEADCS_TLM_WRT_LEN,  73 } },
        { 192, { CUBEADCS_TLM_WRT_LEN,  13 } },
        { 193, { CUBEADCS_TLM_WRT_LEN,  43 } },
        { 194, { CUBEADCS_TLM_WRT_LEN,  35 } },
        { 195, { CUBEADCS_TLM_WRT_LEN,  39 } },
        { 196, { CUBEADCS_TLM_WRT_LEN,   9 } },
        { 197, { CUBEADCS_TLM_WRT_LEN,   4 } },
        { 198, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 199, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 200, { CUBEADCS_TLM_WRT_LEN,  13 } },
        { 201, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 202, { CUBEADCS_TLM_WRT_LEN,  54 } },
        { 203, { CUBEADCS_TLM_WRT_LEN, 113 } },
        { 204, { CUBEADCS_TLM_WRT_LEN,  31 } },
        { 205, { CUBEADCS_TLM_WRT_LEN,  31 } },
        { 206, { CUBEADCS_TLM_WRT_LEN, 505 } },
        { 207, { CUBEADCS_TLM_WRT_LEN,  65 } },
        { 208, { CUBEADCS_TLM_WRT_LEN,  15 } },
        { 209, { CUBEADCS_TLM_WRT_LEN,  21 } },
        { 210, { CUBEADCS_TLM_WRT_LEN,  37 } },
        { 211, { CUBEADCS_TLM_WRT_LEN,  55 } },
        { 212, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 213, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 214, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 215, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 216, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 217, { CUBEADCS_TLM_WRT_LEN,  14 } },
        { 218, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 219, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 220, { CUBEADCS_TLM_WRT_LEN,   4 } },
        { 221, { CUBEADCS_TLM_WRT_LEN,  14 } },
        { 222, { CUBEADCS_TLM_WRT_LEN,  25 } },
        { 223, { CUBEADCS_TLM_WRT_LEN,  32 } },
        { 224, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 225, { CUBEADCS_TLM_WRT_LEN, 174 } },
        { 226, { CUBEADCS_TLM_WRT_LEN,  97 } },
        { 227, { CUBEADCS_TLM_WRT_LEN,  31 } },
        { 228, { CUBEADCS_TLM_WRT_LEN,  34 } },
        { 229, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 230, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 231, { CUBEADCS_TLM_WRT_LEN,   7 } },
        { 232, { CUBEADCS_TLM_WRT_LEN,   5 } },
        { 233, { CUBEADCS_TLM_WRT_LEN,   3 } },
		{ 234, { CUBEADCS_TLM_WRT_LEN,   2 } },
        { 235, { CUBEADCS_TLM_WRT_LEN,  14 } },
        { 236, { CUBEADCS_TLM_WRT_LEN,  14 } },
        { 237, { CUBEADCS_TLM_WRT_LEN,  13 } },
		{ 238, { CUBEADCS_TLM_WRT_LEN,   7 } },

        { 240, { CUBEADCS_TLM_WRT_LEN,   5 } },
        { 241, { CUBEADCS_TLM_WRT_LEN,  23 } },
        { 242, { CUBEADCS_TLM_WRT_LEN,   6 } },
        { 243, { CUBEADCS_TLM_WRT_LEN,  13 } },
        { 244, { CUBEADCS_TLM_WRT_LEN,   2 } },
        { 245, { CUBEADCS_TLM_WRT_LEN,   2 } },
        { 246, { CUBEADCS_TLM_WRT_LEN,   3 } },
        { 247, { CUBEADCS_TLM_WRT_LEN,  17 } },
        { 248, { CUBEADCS_TLM_WRT_LEN,  17 } },
        { 249, { CUBEADCS_TLM_WRT_LEN,  17 } },
        { 250, { CUBEADCS_TLM_WRT_LEN,  17 } },
        { 251, { CUBEADCS_TLM_WRT_LEN,  17 } },
        { 252, { CUBEADCS_TLM_WRT_LEN,  17 } },
        { 253, { CUBEADCS_TLM_WRT_LEN,  17 } },
        { 254, { CUBEADCS_TLM_WRT_LEN,  17 } },
        { 255, { CUBEADCS_TLM_WRT_LEN,  23 } },  /* NOTE: This is not part of the standard CubeACP commands, we use it for burst file transfers */

};

static UART_HandleTypeDef huart4;
/** @brief Pointer to the used UART (be default this is UART 4) */
static UART_HandleTypeDef *sUsedUart = &huart4;

static DMA_HandleTypeDef hdma_usart4_rx;
/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/
tQueue cubeadcs_queue_p;
tQueue cubeadcs_queue_s;

tQueue *p_cubeadcs_queue;

fp_cubeadcs_uart_init cubeadcs_uart_init;

/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/

/** @brief CubeADCS DMA RX buffer */
__ALIGN_BEGIN uint8_t  cubeadcs_dma_buffer[2] __ALIGN_END;

/** @brief Command request reply state */
volatile static CubeADCS_Rply_t cmd_req_rply;

/** @brief CMSIS event used during the receive process */
static osEventFlagsId_t cubeadcs_rx_event;

/** @brief Primary buffer */
static tQueueData cubeadcs_buffer_p[CUBEADCS_UART_BUFFER_SIZE];

/** @brief Secondary buffer */
static tQueueData cubeadcs_buffer_s[CUBEADCS_UART_BUFFER_SIZE];

/** @brief Is the previous character the service character 0x1F */
volatile static bool is_prev_esc_char;

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/

STATIC uint8_t                      fs_CubeADCS_Driver_GetCmdLen(uint8_t u8Cmd, const CubeADCS_Cmd_t *csCmdArr, uint8_t u8CmdArrLen, CubeADCS_Cmd_t *psSrchRes);
STATIC void                         fs_CubeADCS_Driver_Pack(uint8_t u8CmdID, uint8_t *u8Src, uint16_t u16SrcSize, uint8_t *u8Dst, uint16_t *u16PSize, eCubeADCS_Mode_t eMode);
STATIC eCubeADCS_Comm_Status_t      fs_CubeADCS_Driver_ExecTxReq(CubeADCS_CmdCfg_t *sCmd, eCubeADCS_Mode_t eMode);
STATIC eCubeADCS_Comm_Status_t      fs_CubeADCS_Driver_ExecRxReq(CubeADCS_CmdCfg_t *sCmd, CubeADCS_Cmd_t *sCmdDescript);
STATIC eCubeADCS_Comm_Status_t 		fs_CubeADCS_Driver_ExecFDwnRxReq(void);
STATIC uint16_t                     fs_CubeADCS_Driver_GetPackedLen(uint8_t cmd_id, uint8_t *u8Src, uint16_t u16CmdDataSize);

STATIC void 					 	fs_cubeadcs_rxhcpl_callback(UART_HandleTypeDef *huart);
STATIC void 						fs_cubeadcs_rxcpl_callback(UART_HandleTypeDef *huart);
STATIC void 						fs_cubeadcs_rx_logic(uint8_t data);

STATIC void 						fs_cubeadcs_rxcpl_callback_dwn(UART_HandleTypeDef *huart);
STATIC void 						fs_cubeadcs_rxhcpl_callback_dwn(UART_HandleTypeDef *huart);
STATIC void 						fs_cubeadcs_rx_logic_fdwn(uint8_t data);

STATIC void 						fs_cubeadcs_error_callback(UART_HandleTypeDef *huart);


/*
*********************************************************************************************
* EXTERNAL (NONE STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/
eCubeADCS_Comm_Status_t CubeADCS_Driver_ExecCmdReq(CubeADCS_CmdCfg_t *sCmd, eCubeADCS_CommReqType_t eCommReq, eCubeADCS_Mode_t eMode)
{
    eCubeADCS_Comm_Status_t retStatus;
    CubeADCS_Cmd_t          sCmdDescript;
    const CubeADCS_Cmd_t   *spCmds;
    uint8_t                 u8CmdNum;

    retStatus = eCUBEADCS_COMM_COMM_ERR;

    CRIT_ASSERT(sCmd != NULL);
    CRIT_ASSERT(sCmd->pvCmdResDst != NULL);

    /* Load correct commands list */
    if ( eCUBEADCS_MODE_BOOTLOADER == eMode )
    {
    	spCmds   = CubeADCS_Boot_Cmd_List;
    	u8CmdNum = CDEF_ELEMENT_COUNT(CubeADCS_Boot_Cmd_List);
    }
    else
    {
    	spCmds   = CubeADCS_ACP_Cmd_List;
    	u8CmdNum = CDEF_ELEMENT_COUNT(CubeADCS_ACP_Cmd_List);
    }

    /* Check expected vs given data size (if such exists) */
    if ( !fs_CubeADCS_Driver_GetCmdLen(sCmd->u8CmdID, spCmds, u8CmdNum, &sCmdDescript) )
    {
    	if ( sCmdDescript.CmdLengths.WrtLength != sCmd->u16CmdDataSize)
    	{
    		retStatus = eCUBEADCS_COMM_LEN_WRT_ERR;
    	}
    }
    else
    {
    	retStatus = eCUBEADCS_COMM_CMD_ERR;
    }

    if ( retStatus == eCUBEADCS_COMM_COMM_ERR )
    {
    	switch(eCommReq)
    	{
    	case eCUBEADCS_COMMREQTYPE_FETCH:

    		if ( eCUBEADCS_COMM_OK == (retStatus = fs_CubeADCS_Driver_ExecTxReq(sCmd, eMode) ) )
    		{
    			retStatus = fs_CubeADCS_Driver_ExecRxReq(sCmd, &sCmdDescript);
    		}

    		break;

    	case eCUBEADCS_COMMREQTYPE_TX_ONLY:

    		retStatus = fs_CubeADCS_Driver_ExecTxReq(sCmd, eMode);

    		break;

    	case eCUBEADCS_COMMREQTYPE_RX_ONLY:

    		retStatus = fs_CubeADCS_Driver_ExecRxReq(sCmd, &sCmdDescript);

    		break;

    	case eCUBEADCS_COMMREQTYPE_RX_FDWN:

    		retStatus = fs_CubeADCS_Driver_ExecFDwnRxReq();

    		break;

    	default:
    		EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS, eEXEH_CUBEADCS_EXCEPTION_RUNTIME_ERROR, __LINE__);
    		break;
    	}
    }

    return retStatus;
}

void CubeADCS_Driver_SetUsedUart(UART_HandleTypeDef * sNewUartToUse)
{
    sUsedUart = sNewUartToUse;
}

void cubeadcs_driver_init(void)
{
	cubeadcs_driver_set_dma_cfg(false);

	cubeadcs_driver_init_uart();
}

void cubeadcs_driver_deinit(void)
{
	HAL_UART_DMAStop(&huart4);
	HAL_UART_DeInit(&huart4);
}

void MX_USART4_UART_DMA_Init(void)
{
    HAL_UART_RegisterCallback(&huart4, HAL_UART_RX_COMPLETE_CB_ID, fs_cubeadcs_rxcpl_callback);
    HAL_UART_RegisterCallback(&huart4, HAL_UART_RX_HALFCOMPLETE_CB_ID, fs_cubeadcs_rxhcpl_callback);
    HAL_UART_RegisterCallback(&huart4, HAL_UART_ERROR_CB_ID, fs_cubeadcs_error_callback);

}

void MX_USART4_UART_DMA_Init_FDWN(void)
{
	HAL_UART_RegisterCallback(&huart4, HAL_UART_RX_COMPLETE_CB_ID, fs_cubeadcs_rxcpl_callback_dwn);
	HAL_UART_RegisterCallback(&huart4, HAL_UART_RX_HALFCOMPLETE_CB_ID, fs_cubeadcs_rxhcpl_callback_dwn);
	HAL_UART_RegisterCallback(&huart4, HAL_UART_ERROR_CB_ID, fs_cubeadcs_error_callback);
}

void cubeadcs_driver_set_dma_cfg(bool is_dwn)
{
	if ( true != is_dwn)
		cubeadcs_uart_init = MX_USART4_UART_DMA_Init;
	else
		cubeadcs_uart_init = MX_USART4_UART_DMA_Init_FDWN;
}

void cubeadcs_driver_init_uart(void)
{
	// Stop DMA and de-initialise the UART
	HAL_UART_DMAStop(&huart4);
	HAL_UART_DeInit(&huart4);

    // Return to initial state of buffers and IT states
    queue_init(&cubeadcs_queue_p, &cubeadcs_buffer_p[0], (tQueueSize)CUBEADCS_UART_BUFFER_SIZE);
    queue_init(&cubeadcs_queue_s, &cubeadcs_buffer_s[0], (tQueueSize)CUBEADCS_UART_BUFFER_SIZE);

    p_cubeadcs_queue = &cubeadcs_queue_p;

    is_prev_esc_char = false;

    cmd_req_rply.u8RplyState = 0;

	huart4.Instance = UART4;
	huart4.Init.BaudRate = 115200;
	huart4.Init.WordLength = UART_WORDLENGTH_8B;
	huart4.Init.StopBits = UART_STOPBITS_1;
	huart4.Init.Parity = UART_PARITY_NONE;
	huart4.Init.Mode = UART_MODE_TX_RX;
	huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart4.Init.OverSampling = UART_OVERSAMPLING_16;
	huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    /* DMA controller clock enable */
	if ( true != __HAL_RCC_DMA1_IS_CLK_ENABLED() )
	{
	    __HAL_RCC_DMA1_CLK_ENABLE();
	}

	/* UART4 DMA Init */
	/* UART4_RX Init */
	hdma_usart4_rx.Instance = DMA1_Stream5;
	hdma_usart4_rx.Init.Request = DMA_REQUEST_UART4_RX;
	hdma_usart4_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma_usart4_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_usart4_rx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_usart4_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_usart4_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_usart4_rx.Init.Mode = DMA_CIRCULAR;
	hdma_usart4_rx.Init.Priority = DMA_PRIORITY_HIGH;
	hdma_usart4_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

	if (HAL_DMA_Init(&hdma_usart4_rx) != HAL_OK)
	{
		Error_Handler();
	}

	__HAL_LINKDMA(&huart4,hdmarx,hdma_usart4_rx);

	if (HAL_UART_Init(&huart4) != HAL_OK)
	{
		Error_Handler();
	}

	(*cubeadcs_uart_init)();

	HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
}

uint32_t cubeadcs_driver_get_rx_event_status(void)
{
	return osEventFlagsGet(cubeadcs_rx_event);
}

void cubeadcs_driver_switch_buffer(void)
{
	CRIT_ASSERT(p_cubeadcs_queue != NULL);

	(p_cubeadcs_queue == &cubeadcs_queue_s) ? (p_cubeadcs_queue = &cubeadcs_queue_p) : (p_cubeadcs_queue = &cubeadcs_queue_s);
}

tQueue *cubeadcs_driver_get_buffer_in_use(void)
{
	return p_cubeadcs_queue;
}

tQueue *cubeadcs_driver_get_buffer_not_in_use(void)
{
	if (p_cubeadcs_queue == &cubeadcs_queue_p)
		return &cubeadcs_queue_s;
	else
		return &cubeadcs_queue_p;
}

void cubeadcs_driver_mem_init(void)
{
	cubeadcs_rx_event = osEventFlagsNew(NULL);
	if (cubeadcs_rx_event == NULL)
	{
		Error_Handler();
	}
}

void cubeadcs_driver_uart_irq_handler(void)
{
    HAL_UART_IRQHandler(&huart4);
}

void cubeadcs_driver_dma_irq_handler(void)
{
    HAL_DMA_IRQHandler(&hdma_usart4_rx);
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/** @brief Get command lengths out of the command array (binary search)
 *
 * 	@param[in] u8Cmd command id
 * 	@param[in] csCmdArr pointer to the command array (bootloader or ACP)
 * 	@param[in] u8CmdArrLen length of the command array
 *
 * 	@param[out] psSrchRes pointer to destination to store the command lengths
 *
 * 	@retval 0: found a math and has returned the lengths
 * 	@retval 100: failed to find a match
 */
STATIC uint8_t fs_CubeADCS_Driver_GetCmdLen(uint8_t u8Cmd, const CubeADCS_Cmd_t *csCmdArr, uint8_t u8CmdArrLen, CubeADCS_Cmd_t *psSrchRes)
{
    CRIT_ASSERT(csCmdArr != NULL);
    CRIT_ASSERT(psSrchRes != NULL);

    uint8_t     u8CrntCmd;

    int16_t     u16CrntIndx;
    int16_t     u16TopIndx;
    int16_t     u16BottomIndx;

    u16BottomIndx   = 0;
    u16TopIndx      = (u8CmdArrLen - 1);

    while (u16BottomIndx <= u16TopIndx)
    {
        u16CrntIndx   = ( (u16BottomIndx + u16TopIndx) / 2 );

        u8CrntCmd = csCmdArr[ (uint8_t)u16CrntIndx ].CmdID;

        if ( u8Cmd < u8CrntCmd ) {
            u16TopIndx = u16CrntIndx - 1;
        }
        else
            if ( u8Cmd > u8CrntCmd ) {
                u16BottomIndx = u16CrntIndx + 1;
            }
            else
            {
                *psSrchRes = csCmdArr[ (uint8_t)u16CrntIndx ];

                return 0;
            }
    }

    return 100; /* To avoid a random bit-flip if 1 is used */
}

/** @brief Pack data in the CubeADCS specific UART data format
 *
 * 	@param[in] u8CmdID command id
 * 	@param[in] u8Src pointer to input data
 * 	@param[in] u16SrcSize input data size
 * 	@param[in] eMode pack for bootloader or ACP
 *
 * 	@param[out] u8Dst pointer to destination for output packed data
 * 	@param[out] u16PSize pointer to destination for output data size
 *
 *  @note Packs the UART message with the ID, SOM, EOF identifiers
 */
STATIC void fs_CubeADCS_Driver_Pack(uint8_t u8CmdID, uint8_t *u8Src, uint16_t u16SrcSize, uint8_t *u8Dst, uint16_t *u16PSize, eCubeADCS_Mode_t eMode)
{
    CRIT_ASSERT(u8Dst != NULL);

    uint8_t  u8Crc8;
    uint8_t *u8LSrc;
    uint8_t *u8Ldst;
    uint16_t u16EscCntr;
    uint16_t u16LSrcSize;

    u8Crc8      = 0;
    u8LSrc      = u8Src;
    u8Ldst      = u8Dst;
    u16EscCntr  = 0;
    *u16PSize   = u16SrcSize;

    /* Begin message */
    *u8Ldst++ = CUBEADCS_COMM_ESC_CHAR;
    *u8Ldst++ = CUBEADCS_COMM_SOM_CHAR;
    *u8Ldst++ = u8CmdID;

    /* Escape the cmd ID identifier */
    if ( CUBEADCS_COMM_ESC_CHAR == u8CmdID )
    {
    	*u8Ldst++ = CUBEADCS_COMM_ESC_CHAR;
    	++u16EscCntr;
    }

    /* Escape the escape identifier */
    if ( u16SrcSize != 0 )
    {
        for ( u16LSrcSize = 0; u16LSrcSize < u16SrcSize; u16LSrcSize++ )
        {
            if ( CUBEADCS_COMM_ESC_CHAR == *u8Src )
            {
                *u8Ldst++ = CUBEADCS_COMM_ESC_CHAR;
                ++u16EscCntr;
            }

            *u8Ldst++ = *u8Src++;
        }
    }

    /* Only telecommands in application mode (ACP) can be appended with a crc8 byte */
    if ( !(u8CmdID & 0x80) && (CUBEADCS_NODE_TYPE_IDENTIFIER_BOOT != eMode ) )
    {
        /* Calculate the CRC of the telecommand */
        u8Crc8 = CubeADCS_CRC_8(u8LSrc, u16SrcSize);

        /* Escape it if necessary */
        if ( CUBEADCS_COMM_ESC_CHAR == u8Crc8 ) {
            *u8Ldst++ = CUBEADCS_COMM_ESC_CHAR;
            ++u16EscCntr;
        }

        *u8Ldst++  = u8Crc8;
        *u16PSize += 1;
    }

    /* End message */
    *u8Ldst++ = CUBEADCS_COMM_ESC_CHAR;
    *u8Ldst++ = CUBEADCS_COMM_EOM_CHAR;

    /* Update message size at the end of the pack operation */
    *u16PSize += (u16EscCntr + CUBEADCS_COMM_PACK_HEAD_SIZE + CUBEADCS_COMM_PACK_TAIL_SIZE);
}

/** @brief Execute a command transmit request to the CubeADCS
 *
 * 	@param[in] sCmd pointer to command details
 * 	@param[in] eMode current mode of the CubeADCS - bootloader or ACP
 *
 * 	@return status of the performed request
 *
 *  @note The function packs the command and data into a CubeADCS frame and transmits
 *        it over UART (in blocking mode) with timeout
 */
STATIC eCubeADCS_Comm_Status_t fs_CubeADCS_Driver_ExecTxReq(CubeADCS_CmdCfg_t *sCmd, eCubeADCS_Mode_t eMode)
{
    uint16_t u16PackedSize;

    uint16_t u16ExpPackedSize;

    eCubeADCS_Comm_Status_t retStatus;

    retStatus = eCUBEADCS_COMM_OK;

    /* Get expected packed size */
    u16ExpPackedSize = fs_CubeADCS_Driver_GetPackedLen(sCmd->u8CmdID, sCmd->pu8CmdData, sCmd->u16CmdDataSize);

    /* Reserve memory for the pack operation */
    uint8_t au8TxDataBuf[u16ExpPackedSize];

    /* Pack command and data */
    fs_CubeADCS_Driver_Pack(sCmd->u8CmdID, sCmd->pu8CmdData, sCmd->u16CmdDataSize, &au8TxDataBuf[0], &u16PackedSize, eMode);

    /* Send via UART in blocking mode */
    HAL_StatusTypeDef UsartStat;

    /* Clear IT state prior to new request*/
	is_prev_esc_char = false;

	cmd_req_rply.u8RplyState = 0;

    UsartStat = HAL_UART_Receive_DMA(&huart4, cubeadcs_dma_buffer, 2);

    if ( UsartStat == HAL_OK )
    {
        UsartStat = HAL_UART_Transmit(sUsedUart, &au8TxDataBuf[0], u16PackedSize, CUBEADCS_UART_COMM_TIMEOUT_MS);

        if ( UsartStat != HAL_OK )
        {
            if ( UsartStat == HAL_TIMEOUT )
            {
                retStatus = eCUBEADCS_COMM_TX_TIMEOUT;
            }
            else
            {
                retStatus = eCUBEADCS_COMM_ERR;
            }

            cubeadcs_driver_init_uart();
        }
    }
    else
    {
        if ( UsartStat == HAL_TIMEOUT )
        {
            retStatus = eCUBEADCS_COMM_RX_TIMEOUT;
        }
        else
        {
            retStatus = eCUBEADCS_COMM_ERR;
        }

        cubeadcs_driver_init_uart();
    }

    return retStatus;
}

/** @brief Execute a command receive request from the CubeADCS
 *
 * 	@param[in] sCmd pointer to command details
 * 	@param[in] sCmdDescript pointer to destination for reply
 *
 * 	@return status of the performed request
 *
 *  @note This function waits until an RX event is received or until timeout
 */
STATIC eCubeADCS_Comm_Status_t fs_CubeADCS_Driver_ExecRxReq(CubeADCS_CmdCfg_t *sCmd, CubeADCS_Cmd_t *sCmdDescript)
{
	uint32_t rx_event_code;
	eCubeADCS_Comm_Status_t retStatus;

	int ch;

	uint8_t *dst = (uint8_t *)sCmd->pvCmdResDst;

	rx_event_code = osEventFlagsWait(cubeadcs_rx_event, 0x00000003U, osFlagsWaitAny, CUBEADCS_COMM_RX_TIMEOUT);

    (void)HAL_UART_AbortReceive(&huart4);

	if ( 0x00000001U == rx_event_code )
	{
		*sCmd->u16CmdResSize = (uint16_t)queue_data_len(&cubeadcs_queue_p);

		// Check if command reply ID matches requested command ID
		if ( -1 != (ch = (int)queue_get(&cubeadcs_queue_p)) )
		{
			if ( sCmd->u8CmdID == ch)
			{
				*dst++ = (uint8_t)ch;

				while ( -1 != (ch = (int)queue_get(&cubeadcs_queue_p)) )
					*dst++ = (uint8_t)ch;

				retStatus =  eCUBEADCS_COMM_OK;
			}
			else
			{
				retStatus =  eCUBEADCS_COMM_CMD_ERR;
			}
		}
		else
		{
			retStatus =  eCUBEADCS_COMM_COMM_ERR;
		}
	}
	else if ( 0x00000002U == rx_event_code)
	{
		retStatus =  eCUBEADCS_COMM_COMM_ERR;
	}
	else
	{
	    retStatus = eCUBEADCS_COMM_RX_TIMEOUT;
	}

	queue_quick_flush(&cubeadcs_queue_p);

	// In case of missed/broken packet, stall until transfer is over and clear the DMA states
	if ( (eCUBEADCS_COMM_COMM_ERR == retStatus) || (eCUBEADCS_COMM_CMD_ERR == retStatus) )
	{
		osDelay(50);

		cubeadcs_driver_init();
	}

	return retStatus;
}

/** @brief Execute a command receive request in the context of a file download from the CubeADCS
 * 	@return status of the performed request
 *
 *  @note Waits for an event indicating an error or successful reception of several packets.
 * 		  The number of packets that flag the success event depends on the receive buffer size.
 * 		  The timeout for the event also depends on the buffer size.
 */
STATIC eCubeADCS_Comm_Status_t fs_CubeADCS_Driver_ExecFDwnRxReq(void)
{
	uint32_t rx_event_code;
    eCubeADCS_Comm_Status_t retStatus;

    rx_event_code = osEventFlagsWait(cubeadcs_rx_event, 0x00000003U, osFlagsWaitAny, CUBEADCS_COMM_RX_TIMEOUT);

    if ( 0x00000001U == rx_event_code ) {
    	retStatus =  eCUBEADCS_COMM_OK;
    }
    else if ( 0x00000002U == rx_event_code)
    {
    	retStatus =  eCUBEADCS_COMM_COMM_ERR;

    	HAL_UART_AbortReceive(&huart4);
    }
    else
    	retStatus = eCUBEADCS_COMM_RX_TIMEOUT;

    return retStatus;
}

/** @brief Get expected number of bytes after pack operation
 *
 *  @param[in] cmd_id command id
 *  @param[in] u8Src pointer to source data buffer
 *  @param[in] u16CmdDataSize size of source data buffer
 *
 * 	@return expected number of bytes after a pack operation
 *
 *  @note Expected size is determined from: SOM, EOM identifiers, ESC character,
 *        calculated crc8. All data, including crc8 must be escaped if their value
 *        equals ESC character.
 */
STATIC uint16_t fs_CubeADCS_Driver_GetPackedLen(uint8_t cmd_id, uint8_t *u8Src, uint16_t u16CmdDataSize)
{
    uint16_t u16Indx;

    uint16_t u16CmdDataSizeAfterPack;

    /* SOM, ESC, Command ID, CRC8, potential escape of CRC8, EOM, ESC */
    u16CmdDataSizeAfterPack = CUBEADCS_COMM_PACK_SIZE + CUBEADCS_COMM_CRC8_SIZE + 1;

    if ( NULL != u8Src )
    {
        for ( u16Indx = 0; u16Indx < u16CmdDataSize; u16Indx++ )
            if ( CUBEADCS_COMM_ESC_CHAR == *u8Src++ )
                ++u16CmdDataSizeAfterPack;

        u16CmdDataSizeAfterPack += u16CmdDataSize;
    }

    /* The command ID also needs escaping */
    if ( CUBEADCS_COMM_ESC_CHAR == cmd_id )
    	++u16CmdDataSizeAfterPack;

    return u16CmdDataSizeAfterPack;
}

/** @brief DMA RX complete callback
 *
 *  @param[in] huart pointer to huart handle
 */
STATIC void fs_cubeadcs_rxcpl_callback(UART_HandleTypeDef *huart)
{
	fs_cubeadcs_rx_logic(cubeadcs_dma_buffer[1]);
}

/** @brief DMA RX half-complete callback
 *
 *  @param[in] huart pointer to huart handle
 */
STATIC void fs_cubeadcs_rxhcpl_callback(UART_HandleTypeDef *huart)
{
	fs_cubeadcs_rx_logic(cubeadcs_dma_buffer[0]);
}

/** @brief DMA RX complete callback during file downloads
 *
 *  @param[in] huart pointer to huart handle
 */
STATIC void fs_cubeadcs_rxcpl_callback_dwn(UART_HandleTypeDef *huart)
{
	fs_cubeadcs_rx_logic_fdwn(cubeadcs_dma_buffer[1]);
}

/** @brief DMA RX half-complete callback during file downloads
 *
 *  @param[in] huart pointer to huart handle
 */
STATIC void fs_cubeadcs_rxhcpl_callback_dwn(UART_HandleTypeDef *huart)
{
	fs_cubeadcs_rx_logic_fdwn(cubeadcs_dma_buffer[0]);
}

/** @brief DMA RX error callback
 *
 *  @param[in] huart pointer to huart handle
 */
STATIC void fs_cubeadcs_error_callback(UART_HandleTypeDef *huart)
{
	HAL_StatusTypeDef retVal = HAL_UART_Receive_DMA(&huart4, cubeadcs_dma_buffer, 2);
	if(retVal != HAL_OK)
	{
		EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS, eEXEH_CUBEADCS_EXCEPTION_OS_ERROR, __LINE__);
	}
}

/** @brief Receive logic in non file-download mode
 *
 *  @param[in] data the received data byte
 *
 *  @note This is the standard logic called from the DMA callbacks
 */
STATIC void fs_cubeadcs_rx_logic(uint8_t data)
{
	if ( true == is_prev_esc_char )
	{
		switch (data)
		{
		case CUBEADCS_COMM_ESC_CHAR:
			if ( 0x03 == cmd_req_rply.u8RplyState ) {
				queue_put(&cubeadcs_queue_p, (const tQueueData) data);
			}

			break;
		case CUBEADCS_COMM_SOM_CHAR:
			if ( 0x00 == cmd_req_rply.u8RplyState ) {
				cmd_req_rply.SOM_ESC = 1;
				cmd_req_rply.SOM_CHR = 1;
			}
			else
			{
				EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS, eEXEH_CUBEADCS_EXCEPTION_COMM_COMM_ERROR, __LINE__);

				cmd_req_rply.res = 1;
			}

			break;
		case CUBEADCS_COMM_EOM_CHAR:
			if ( 0x03 == cmd_req_rply.u8RplyState ) {
				cmd_req_rply.EOM_ESC = 1;
				cmd_req_rply.EOM_CHR = 1;
			}
			else
			{
				EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS, eEXEH_CUBEADCS_EXCEPTION_COMM_COMM_ERROR, __LINE__);

				cmd_req_rply.res = 1;
			}

			break;
		default:
			EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS, eEXEH_CUBEADCS_EXCEPTION_COMM_COMM_ERROR, __LINE__);

			cmd_req_rply.res = 1;

			break;
		}

		is_prev_esc_char = false;

	}
	else if (CUBEADCS_COMM_ESC_CHAR == data)
	{
		is_prev_esc_char = true;
	}
	else
	{
		if ( 0x03 == cmd_req_rply.u8RplyState ) {
			queue_put(&cubeadcs_queue_p, (const tQueueData) data);
		}
	}

	if ( cmd_req_rply.res == 1 )
	{
		osEventFlagsSet(cubeadcs_rx_event, 0x00000002U);

		return;
	}

	if ( CUBEADCS_COMM_DECODE_OK == cmd_req_rply.u8RplyState )
	{
		osEventFlagsSet(cubeadcs_rx_event, 0x00000001U);

		return;
	}
}

/** @brief Receive logic in file download mode
 *
 *  @param[in] data the received data byte
 *
 *  @note This is the standard logic called from the DMA callbacks during file downloads
 */
STATIC void fs_cubeadcs_rx_logic_fdwn(uint8_t data)
{
	if ( true == is_prev_esc_char )
	{
		switch (data)
		{
		case CUBEADCS_COMM_ESC_CHAR:
			if ( 0x03 == cmd_req_rply.u8RplyState ) {
				queue_put(p_cubeadcs_queue, (const tQueueData) data);
			}
			break;
		case CUBEADCS_COMM_SOM_CHAR:
			if ( 0x00 == cmd_req_rply.u8RplyState ) {
				cmd_req_rply.SOM_ESC = 1;
				cmd_req_rply.SOM_CHR = 1;
			}
			else
			{
				cmd_req_rply.res = 1;
			}

			break;
		case CUBEADCS_COMM_EOM_CHAR:
			if ( 0x03 == cmd_req_rply.u8RplyState ) {
				cmd_req_rply.EOM_ESC = 1;
				cmd_req_rply.EOM_CHR = 1;
			}
			else
			{
				cmd_req_rply.res = 1;
			}

			break;
		default:
			EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS, eEXEH_CUBEADCS_EXCEPTION_COMM_COMM_ERROR, __LINE__);

			cmd_req_rply.res = 1;

			break;
		}

		is_prev_esc_char = false;
	}
	else if (CUBEADCS_COMM_ESC_CHAR == data)
	{
		is_prev_esc_char = true;
	}
	else
	{
		if ( 0x03 == cmd_req_rply.u8RplyState ) {
			queue_put(p_cubeadcs_queue, (const tQueueData) data);
		}
	}

	/* Exit on detected error */
	if ( cmd_req_rply.res == 1 )
	{
		cmd_req_rply.u8RplyState = 0;

		osEventFlagsSet(cubeadcs_rx_event, 0x00000002U);

		is_prev_esc_char = false;

		return;
	}

	if ( CUBEADCS_COMM_DECODE_OK == cmd_req_rply.u8RplyState ) {
		cmd_req_rply.u8RplyState = 0;
		is_prev_esc_char = false;
	}

	/* Check if buffer is full, switch to other buffer and flag the waiting task */
	if ( p_cubeadcs_queue->tail == (CUBEADCS_UART_BUFFER_SIZE - (CUBEADCS_UART_BUFFER_SIZE % CUBEADCS_FTRANSF_PKT_SIZE)) )
	{
		cubeadcs_driver_switch_buffer();

		queue_quick_flush(p_cubeadcs_queue);

		osEventFlagsSet(cubeadcs_rx_event, 0x00000001U);

		is_prev_esc_char = false;
	}
}

/* ******************************************************************************************* */
