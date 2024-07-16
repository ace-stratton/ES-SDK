/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef CUBEADCS_DRIVER_H
#define CUBEADCS_DRIVER_H

/**
 * @addtogroup cubeadcs
 * @{
 *
 * @file     cubeadcs_driver.h
 * @brief    Interface for the low-level driver dedicated to the CubeADCS module
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

/*
*********************************************************************************************
* INCLUDES
*********************************************************************************************
*/
/* Core platform dependency */
#include "es_cdef.h"
#include "MCU_Init.h"
#include "libqueue.h"

/*
*********************************************************************************************
* EXTERNAL DEFINES
*********************************************************************************************
*/
/** @brief Reply length to a TC in bytes - the actual reply is 2 bytes, but the first one is the TC ID so we omit it */
#define CUBEADCS_TC_RPLY_LEN       ((uint8_t)0x02)
/** @brief Number of data bytes to send when performing a TLM request */
#define CUBEADCS_TLM_WRT_LEN       ((uint8_t)0x00)
/** @brief Start-of-message (SOM) specific character */
#define CUBEADCS_COMM_SOM_CHAR     ((uint8_t)0x7F)
/** @brief End-of-message (EOM) specific character */
#define CUBEADCS_COMM_EOM_CHAR     ((uint8_t)0xFF)
/** @brief Escape character preceding SOM and EOM */
#define CUBEADCS_COMM_ESC_CHAR     ((uint8_t)0x1F)
/** @brief Indicator for a successful UART reply decode  */
#define CUBEADCS_COMM_DECODE_OK    ((uint8_t)0x0F)
/** @brief Times CUBEADCS_COMM_RX_TIMEOUT gives the total time to wait for a response to a command request  */
#define CUBEADCS_COMM_RETRY_CNT     		((uint8_t)0x64)
/** @brief Timeout time per retry count */
#define CUBEADCS_COMM_RX_RTRY_TIMEOUT_MS 	(0x0AU)
/** @brief RX Timeout time in ms */
#define CUBEADCS_COMM_RX_TIMEOUT			((uint32_t) (CUBEADCS_COMM_RETRY_CNT * CUBEADCS_COMM_RX_RTRY_TIMEOUT_MS))
/** @brief Size of the CRC8 in bytes */
#define CUBEADCS_COMM_CRC8_SIZE        ((uint8_t)0x01)
/** @brief Size in bytes of the header after packing a message to be sent to the CubeADCS */
#define CUBEADCS_COMM_PACK_HEAD_SIZE   ((uint8_t)0x03)
/** @brief Size in bytes of the tail after packing a message to be sent to the CubeADCS */
#define CUBEADCS_COMM_PACK_TAIL_SIZE   ((uint8_t)0x02)
/** @brief Size in bytes of the tail and head combined */
#define CUBEADCS_COMM_PACK_SIZE        (CUBEADCS_COMM_PACK_HEAD_SIZE + CUBEADCS_COMM_PACK_TAIL_SIZE)
/** @brief Size of the buffer used for RX messages from the CubeADCS */
#define CUBEADCS_UART_BUFFER_SIZE   (512)
/** @brief Timeout to transmit data to the CubeADCS */
#define CUBEADCS_UART_COMM_TIMEOUT_MS ((uint32_t)50)
/** @brief Bootloader identifier number */
#define CUBEADCS_NODE_TYPE_IDENTIFIER_BOOT ((uint8_t)110)
/** @brief ACP identifier number */
#define CUBEADCS_NODE_TYPE_IDENTIFIER_ACP  ((uint8_t)10)
/** @brief Size of a single file transfer packed (with overhead) */
#define CUBEADCS_FTRANSF_PKT_SIZE ((uint8_t)23)

/*
*********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
*********************************************************************************************
*/

typedef enum tag_eCubeADCS_Mode
{
    eCUBEADCS_MODE_APPLICATION = CUBEADCS_NODE_TYPE_IDENTIFIER_ACP,
    eCUBEADCS_MODE_BOOTLOADER  = CUBEADCS_NODE_TYPE_IDENTIFIER_BOOT,

    eCUBEADCS_MODE_INVALID     = 0xFF

} eCubeADCS_Mode_t;

typedef enum tag_CubeADCS_Comm_Status
{
    eCUBEADCS_COMM_OK,
    eCUBEADCS_COMM_ERR,
    eCUBEADCS_COMM_CMD_ERR,
    eCUBEADCS_COMM_LEN_WRT_ERR,
    eCUBEADCS_COMM_LEN_READ_ERR,
    eCUBEADCS_COMM_RX_TIMEOUT,
    eCUBEADCS_COMM_TX_TIMEOUT,
    eCUBEADCS_COMM_COMM_ERR,
    eCUBEADCS_COMM_INV_DATA,
    eCUBEADCS_COMM_NUMBER

} eCubeADCS_Comm_Status_t;

typedef struct tag_CubeADCS_Cmd_Desc
{
    uint16_t WrtLength;
    uint16_t ReadLength;

} CubeADCS_Cmd_Desc_t;

typedef struct tag_CubeADCS_Cmd
{
    uint8_t              CmdID;
    CubeADCS_Cmd_Desc_t  CmdLengths;

} CubeADCS_Cmd_t;

typedef union {
    struct
    {
        uint8_t SOM_ESC: 1;
        uint8_t SOM_CHR: 1;
        uint8_t EOM_ESC: 1;
        uint8_t EOM_CHR: 1;
        uint8_t res    : 4;
    };
    uint8_t u8RplyState;
} CubeADCS_Rply_t;

typedef struct tag_CubeADCS_CmdCfg
{
    uint8_t     u8CmdID;
    uint8_t    *pu8CmdData;
    uint16_t    u16CmdDataSize;
    void       *pvCmdResDst;
    uint16_t    u16CmdResDstSize;
    uint16_t   *u16CmdResSize;

} CubeADCS_CmdCfg_t;

/*-------------------------------------------*/
/*--------------Common-----------------------*/

typedef enum tag_CubeADCS_CommReqType
{
    eCUBEADCS_COMMREQTYPE_FETCH,
    eCUBEADCS_COMMREQTYPE_TX_ONLY,
    eCUBEADCS_COMMREQTYPE_RX_ONLY,
	eCUBEADCS_COMMREQTYPE_RX_FDWN,

} eCubeADCS_CommReqType_t;

/*-------------------------------------------*/

typedef enum tag_cubeadcs_dma_rx_type
{
	eCUBEADCS_DMA_RX_TYPE_NORMAL,
	eCUBEADCS_DMA_RX_TYPE_FDWN,
} cubeadcs_dma_rx_type_t;

typedef void (* fp_cubeadcs_uart_init)(void);

/*
*********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
*********************************************************************************************
*/
#if defined(TEST_ENABLED)

STATIC const CubeADCS_Cmd_t     CubeADCS_Boot_Cmd_List[];
STATIC const CubeADCS_Cmd_t     CubeADCS_ACP_Cmd_List[];

#endif /*TEST*/

/** @brief  Primary queue - used by default during communication with the CubeADCS and during file downloads */
extern tQueue cubeadcs_queue_p;
/** @brief  Secondary queue - used during file downloads only */
extern tQueue cubeadcs_queue_s;
/** @brief  Pointer to the currently used queue. This pointer is updated during file transfers on every N received packets */
extern tQueue *p_cubeadcs_queue;
/** @brief  Function pointer to callbacks initialisation for the DMA initialisation during normal operation or file downloads */
extern fp_cubeadcs_uart_init cubeadcs_uart_init;

/*
*********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
*********************************************************************************************
*/

/** @brief Execute a command request
 *  @param[in] pointer to the command (TC or TLM) structure
 *  @param[in] type of request
 *  @param[in] expected CubeADCS mode - bootloader or ACP
 *
 *  @return status of the request
 *
 *  @note This function sends the command to the CubeADCS with or without data,
 *		  waits until a response is received or the timeout time is reached,
 *		  writes the un-packed result of the command to the
 *        provided buffer.
 */
eCubeADCS_Comm_Status_t CubeADCS_Driver_ExecCmdReq(CubeADCS_CmdCfg_t *sCmd, eCubeADCS_CommReqType_t eCommReq, eCubeADCS_Mode_t eMode);

/** @brief Sets the used UART (obsolete) */
void CubeADCS_Driver_SetUsedUart(UART_HandleTypeDef * sNewUartToUse);

/** @brief Initialise the driver */
void cubeadcs_driver_init(void);

/** @brief De-Initialise the driver */
void cubeadcs_driver_deinit(void);

/** @brief UART4 DMA mode initialisation
 *
 *	@note This initialises the RX DMA callbacks for normal operation
 */
void MX_USART4_UART_DMA_Init(void);

/** @brief UART4 DMA mode initialisation for file downloads
 *
 *  @note This initialises the RX DMA callbacks for file download operation
 */
void MX_USART4_UART_DMA_Init_FDWN(void);

/** @brief Initialises the used UART
 *
 *  @note This initialises the used buffers as well /ref p_cubeadcs_queue
 */
void cubeadcs_driver_init_uart(void);

/** @brief Sets the DMA configuration for normal of file download operation
 *
 * 	@param[in] is_dwn boolean, TRUE for file download, FALSE for normal operation
 *
 *  @note This initialises the used buffers as well /ref p_cubeadcs_queue
 */
void cubeadcs_driver_set_dma_cfg(bool is_dwn);

/** @brief Gets the status of the event used to flag a reception
 *
 * 	@param[in] boolean, TRUE for file download, FALSE for normal operation
 *
 *  @return event status
 */
uint32_t cubeadcs_driver_get_rx_event_status(void);

/** @brief Swaps the two buffers (/ref cubeadcs_queue_p and /ref cubeadcs_queue_s)
 *
 * 	@note Used during file downloads. While one buffer is used for the reception of incoming packets
 * 		  the other one is being processes and written to the SD-card. The swap happens when the buffer used
 * 		  for reception is full.
 */
void cubeadcs_driver_switch_buffer(void);

/** @brief Returns the current buffer in use (that is, the buffer used for the reception)
 *
 * 	@return pointer to the buffer in use
 */
tQueue *cubeadcs_driver_get_buffer_in_use(void);

/** @brief Returns the unused buffer (that is, the buffer not used for reception)
 *
 * 	@return pointer to the buffer not in use
 */
tQueue *cubeadcs_driver_get_buffer_not_in_use(void);

/** @brief Initialises the driver memory (used by the run-time configuration) */
void cubeadcs_driver_mem_init(void);

void cubeadcs_driver_uart_irq_handler(void);
void cubeadcs_driver_dma_irq_handler(void);

#if defined(TEST_ENABLED)

STATIC uint8_t                  fs_CubeADCS_Driver_GetCmdLen(uint8_t cmd, const CubeADCS_Cmd_t *cmdArr, uint8_t cmdArrLen, CubeADCS_Cmd_t *srch_result);
STATIC void                     fs_CubeADCS_Driver_Pack(uint8_t u8CmdID, uint8_t *u8Src, uint16_t u16SrcSize, uint8_t *u8Dst, uint16_t *u16PSize, eCubeADCS_Mode_t eMode);
STATIC int                      fs_CubeADCS_Driver_GetChar();
STATIC eCubeADCS_Comm_Status_t  fs_CubeADCS_Driver_ExecTxReq(CubeADCS_CmdCfg_t *sCmd, eCubeADCS_Mode_t eMode);
STATIC eCubeADCS_Comm_Status_t  fs_CubeADCS_Driver_ExecRxReq(CubeADCS_CmdCfg_t *sCmd, CubeADCS_Cmd_t *sCmdDescript);
STATIC uint16_t                 fs_CubeADCS_Driver_GetPackedLen(uint8_t *u8Src, uint16_t u16CmdDataSize);
STATIC void 					fs_cubeadcs_driver_init_uart(void);

#endif /*TEST*/

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* CUBEADCS_DRIVER_H */

/* ******************************************************************************************* */
