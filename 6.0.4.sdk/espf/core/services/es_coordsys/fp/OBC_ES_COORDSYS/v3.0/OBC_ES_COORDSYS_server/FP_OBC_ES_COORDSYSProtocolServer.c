/*!
********************************************************************************************
* @file FP_OBC_ES_COORDSYSProtocolServer.c
* @brief ESSA Stack server-side implementation
********************************************************************************************
* @version           interface OBC_ES_COORDSYS v3.0
*
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
*-------------------------------------------------------------------------------------------
* GENERATOR: org.endurosat.generators.macchiato.binders.Gen_C v2.12
*-------------------------------------------------------------------------------------------
* !!! Please note that this code is fully GENERATED and shall not be manually modified as
* all changes will be overwritten !!!
********************************************************************************************
*/

#include "FP_OBC_ES_COORDSYSProtocolServer.h"
#include "FP_common/FP_ProtocolServerCommon.h"

#define OBC_ES_COORDSYS_PROTOCOL_VERSION_MAJOR   ((uint8_t) 3)
#define OBC_ES_COORDSYS_PROTOCOL_VERSION_MINOR   ((uint8_t) 0)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSSET_GYROSCOPE_FRAMERequestData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSSET_GYROSCOPE_FRAMEProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSSET_GYROSCOPE_FRAMEResponseData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSSET_GYROSCOPE_FRAMEProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_COORDSYSGET_GYROSCOPE_FRAMEProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSGET_GYROSCOPE_FRAMEResponseData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSGET_GYROSCOPE_FRAMEProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMERequestData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMEProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMEResponseData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMEProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_COORDSYSGET_MAGNETOMETER_FRAMEProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSGET_MAGNETOMETER_FRAMEResponseData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSGET_MAGNETOMETER_FRAMEProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMERequestData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMEProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMEResponseData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMEProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_COORDSYSGET_MAGNETORQUER_FRAMEProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSGET_MAGNETORQUER_FRAMEResponseData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSGET_MAGNETORQUER_FRAMEProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMERequestData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMEProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMEResponseData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMEProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_COORDSYSGET_COARSE_SUN_SENSOR_FRAMEProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSGET_COARSE_SUN_SENSOR_FRAMEResponseData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSGET_COARSE_SUN_SENSOR_FRAMEProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_COORDSYSSAVE_COORDSYS_CONFIGProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSSAVE_COORDSYS_CONFIGResponseData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSSAVE_COORDSYS_CONFIGProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_COORDSYSLOAD_COORDSYS_CONFIGProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSLOAD_COORDSYS_CONFIGResponseData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSLOAD_COORDSYS_CONFIGProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMERequestData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMEProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMEResponseData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMEProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_COORDSYSGET_ACCELEROMETER_FRAMEProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_COORDSYSGET_ACCELEROMETER_FRAMEResponseData_t data;
} PACKED_STRUCT OBC_ES_COORDSYSGET_ACCELEROMETER_FRAMEProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SET_GYROSCOPE_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_GYROSCOPE_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SET_MAGNETOMETER_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_MAGNETOMETER_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SET_MAGNETORQUER_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_MAGNETORQUER_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SET_COARSE_SUN_SENSOR_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_COARSE_SUN_SENSOR_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SAVE_COORDSYS_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_LOAD_COORDSYS_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SET_ACCELEROMETER_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_ACCELEROMETER_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_OBC_ES_COORDSYSProtocolServerInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static OBC_ES_COORDSYS_ServerApi_t *pSrvApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { OBC_ES_COORDSYS_SET_GYROSCOPE_FRAME_FUNC_ID, fs_SET_GYROSCOPE_FRAMEReq },
    { OBC_ES_COORDSYS_GET_GYROSCOPE_FRAME_FUNC_ID, fs_GET_GYROSCOPE_FRAMEReq },
    { OBC_ES_COORDSYS_SET_MAGNETOMETER_FRAME_FUNC_ID, fs_SET_MAGNETOMETER_FRAMEReq },
    { OBC_ES_COORDSYS_GET_MAGNETOMETER_FRAME_FUNC_ID, fs_GET_MAGNETOMETER_FRAMEReq },
    { OBC_ES_COORDSYS_SET_MAGNETORQUER_FRAME_FUNC_ID, fs_SET_MAGNETORQUER_FRAMEReq },
    { OBC_ES_COORDSYS_GET_MAGNETORQUER_FRAME_FUNC_ID, fs_GET_MAGNETORQUER_FRAMEReq },
    { OBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAME_FUNC_ID, fs_SET_COARSE_SUN_SENSOR_FRAMEReq },
    { OBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAME_FUNC_ID, fs_GET_COARSE_SUN_SENSOR_FRAMEReq },
    { OBC_ES_COORDSYS_SAVE_COORDSYS_CONFIG_FUNC_ID, fs_SAVE_COORDSYS_CONFIGReq },
    { OBC_ES_COORDSYS_LOAD_COORDSYS_CONFIG_FUNC_ID, fs_LOAD_COORDSYS_CONFIGReq },
    { OBC_ES_COORDSYS_SET_ACCELEROMETER_FRAME_FUNC_ID, fs_SET_ACCELEROMETER_FRAMEReq },
    { OBC_ES_COORDSYS_GET_ACCELEROMETER_FRAME_FUNC_ID, fs_GET_ACCELEROMETER_FRAMEReq }
};

/**********************************************************************
 *
 *  Static methods implementation
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    ESSA_Stack_FP_MsgHdr_t *pHdr = NULL;
    bool bIsFuncSupported = false;
    uint8_t i;

    // Basic header validity check
    if ((fp_DataInfo == NULL) ||
        (fp_DataInfo->u16DataSize < sizeof(ESSA_Stack_FP_MsgHdr_t)) ||
        (fp_DataInfo->pu8Data == NULL))
    {
        return false;
    }

    pHdr = (ESSA_Stack_FP_MsgHdr_t *) fp_DataInfo->pu8Data;

    if (IS_REQUEST(*pHdr))
    {
        for (i = 0; i < COUNT_OF(fs_aFuncArray); i++)
        {
            if (fs_aFuncArray[i].funcId == pHdr->funcId)
            {
                if (fs_aFuncArray[i].pfFunc != NULL)
                {
                    bIsFuncSupported = true;
                    fs_aFuncArray[i].pfFunc(fp_DataInfo);
                }

                break;
            }
        }

        if (!bIsFuncSupported)
            (void) ProtocolSendErrorResp(fp_DataInfo, (uint8_t) ESSA_FP_ERRCODE_FUNC_NOT_SUPPORTED);
    }

    return bIsFuncSupported;
}

static void fs_SET_GYROSCOPE_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_COORDSYSSET_GYROSCOPE_FRAMEProtocolRequestData_t *fullrequest = (OBC_ES_COORDSYSSET_GYROSCOPE_FRAMEProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_ES_COORDSYSSET_GYROSCOPE_FRAMERequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSSET_GYROSCOPE_FRAMEProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_ES_COORDSYSSET_GYROSCOPE_FRAMERequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_COORDSYS_SET_GYROSCOPE_FRAMERequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_COORDSYS_SET_GYROSCOPE_FRAMERequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_GET_GYROSCOPE_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_COORDSYSGET_GYROSCOPE_FRAMEProtocolRequestData_t *fullrequest = (OBC_ES_COORDSYSGET_GYROSCOPE_FRAMEProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSGET_GYROSCOPE_FRAMEProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_COORDSYS_GET_GYROSCOPE_FRAMERequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_COORDSYS_GET_GYROSCOPE_FRAMERequestHandler(&requestCtx);
    }
}

static void fs_SET_MAGNETOMETER_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMEProtocolRequestData_t *fullrequest = (OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMEProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMERequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMEProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMERequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_COORDSYS_SET_MAGNETOMETER_FRAMERequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_COORDSYS_SET_MAGNETOMETER_FRAMERequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_GET_MAGNETOMETER_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_COORDSYSGET_MAGNETOMETER_FRAMEProtocolRequestData_t *fullrequest = (OBC_ES_COORDSYSGET_MAGNETOMETER_FRAMEProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSGET_MAGNETOMETER_FRAMEProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_COORDSYS_GET_MAGNETOMETER_FRAMERequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_COORDSYS_GET_MAGNETOMETER_FRAMERequestHandler(&requestCtx);
    }
}

static void fs_SET_MAGNETORQUER_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMEProtocolRequestData_t *fullrequest = (OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMEProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMERequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMEProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMERequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_COORDSYS_SET_MAGNETORQUER_FRAMERequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_COORDSYS_SET_MAGNETORQUER_FRAMERequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_GET_MAGNETORQUER_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_COORDSYSGET_MAGNETORQUER_FRAMEProtocolRequestData_t *fullrequest = (OBC_ES_COORDSYSGET_MAGNETORQUER_FRAMEProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSGET_MAGNETORQUER_FRAMEProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_COORDSYS_GET_MAGNETORQUER_FRAMERequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_COORDSYS_GET_MAGNETORQUER_FRAMERequestHandler(&requestCtx);
    }
}

static void fs_SET_COARSE_SUN_SENSOR_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMEProtocolRequestData_t *fullrequest = (OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMEProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMERequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMEProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMERequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAMERequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAMERequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_GET_COARSE_SUN_SENSOR_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_COORDSYSGET_COARSE_SUN_SENSOR_FRAMEProtocolRequestData_t *fullrequest = (OBC_ES_COORDSYSGET_COARSE_SUN_SENSOR_FRAMEProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSGET_COARSE_SUN_SENSOR_FRAMEProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAMERequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAMERequestHandler(&requestCtx);
    }
}

static void fs_SAVE_COORDSYS_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_COORDSYSSAVE_COORDSYS_CONFIGProtocolRequestData_t *fullrequest = (OBC_ES_COORDSYSSAVE_COORDSYS_CONFIGProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSSAVE_COORDSYS_CONFIGProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_COORDSYS_SAVE_COORDSYS_CONFIGRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_COORDSYS_SAVE_COORDSYS_CONFIGRequestHandler(&requestCtx);
    }
}

static void fs_LOAD_COORDSYS_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_COORDSYSLOAD_COORDSYS_CONFIGProtocolRequestData_t *fullrequest = (OBC_ES_COORDSYSLOAD_COORDSYS_CONFIGProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSLOAD_COORDSYS_CONFIGProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_COORDSYS_LOAD_COORDSYS_CONFIGRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_COORDSYS_LOAD_COORDSYS_CONFIGRequestHandler(&requestCtx);
    }
}

static void fs_SET_ACCELEROMETER_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMEProtocolRequestData_t *fullrequest = (OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMEProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMERequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMEProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMERequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_COORDSYS_SET_ACCELEROMETER_FRAMERequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_COORDSYS_SET_ACCELEROMETER_FRAMERequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_GET_ACCELEROMETER_FRAMEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_COORDSYSGET_ACCELEROMETER_FRAMEProtocolRequestData_t *fullrequest = (OBC_ES_COORDSYSGET_ACCELEROMETER_FRAMEProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSGET_ACCELEROMETER_FRAMEProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_COORDSYS_GET_ACCELEROMETER_FRAMERequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_COORDSYS_GET_ACCELEROMETER_FRAMERequestHandler(&requestCtx);
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void OBC_ES_COORDSYS_registerServerApi(OBC_ES_COORDSYS_ServerApi_t *pSrvApiHandlers)
{
    pSrvApiHnd = pSrvApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t OBC_ES_COORDSYS_getServerProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_OBC_ES_COORDSYSProtocolServerInfo;
}

ESSATMAC_ErrCodes OBC_ES_COORDSYS_SET_GYROSCOPE_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_COORDSYSSET_GYROSCOPE_FRAMEProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_COORDSYSSET_GYROSCOPE_FRAMEProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSSET_GYROSCOPE_FRAMEProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS;
        responseParams.hdr.funcId  = OBC_ES_COORDSYS_SET_GYROSCOPE_FRAME_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOpResult = eOpResult;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_ES_COORDSYSSET_GYROSCOPE_FRAMEProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_COORDSYS_GET_GYROSCOPE_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_GYROSCOPE_FRAME_t * const sActiveGyrFrame,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_COORDSYSGET_GYROSCOPE_FRAMEProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_COORDSYSGET_GYROSCOPE_FRAMEProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSGET_GYROSCOPE_FRAMEProtocolResponseData_t);

    if ((ctx != NULL) && (sActiveGyrFrame != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS;
        responseParams.hdr.funcId  = OBC_ES_COORDSYS_GET_GYROSCOPE_FRAME_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sActiveGyrFrame != NULL)
        {
            responseParams.data.sActiveGyrFrame = *(sActiveGyrFrame);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sActiveGyrFrame,
                          0U,
                          sizeof(responseParams.data.sActiveGyrFrame));
        }
        responseParams.data.eOpResult = eOpResult;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_ES_COORDSYSGET_GYROSCOPE_FRAMEProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_COORDSYS_SET_MAGNETOMETER_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMEProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMEProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMEProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS;
        responseParams.hdr.funcId  = OBC_ES_COORDSYS_SET_MAGNETOMETER_FRAME_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOpResult = eOpResult;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMEProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_COORDSYS_GET_MAGNETOMETER_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_MAGNETOMETER_FRAME_t * const sActiveMagFrame,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_COORDSYSGET_MAGNETOMETER_FRAMEProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_COORDSYSGET_MAGNETOMETER_FRAMEProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSGET_MAGNETOMETER_FRAMEProtocolResponseData_t);

    if ((ctx != NULL) && (sActiveMagFrame != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS;
        responseParams.hdr.funcId  = OBC_ES_COORDSYS_GET_MAGNETOMETER_FRAME_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sActiveMagFrame != NULL)
        {
            responseParams.data.sActiveMagFrame = *(sActiveMagFrame);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sActiveMagFrame,
                          0U,
                          sizeof(responseParams.data.sActiveMagFrame));
        }
        responseParams.data.eOpResult = eOpResult;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_ES_COORDSYSGET_MAGNETOMETER_FRAMEProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_COORDSYS_SET_MAGNETORQUER_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMEProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMEProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMEProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS;
        responseParams.hdr.funcId  = OBC_ES_COORDSYS_SET_MAGNETORQUER_FRAME_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOpResult = eOpResult;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMEProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_COORDSYS_GET_MAGNETORQUER_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_MAGNETORQUER_FRAME_t * const sActiveMtqFrame,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_COORDSYSGET_MAGNETORQUER_FRAMEProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_COORDSYSGET_MAGNETORQUER_FRAMEProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSGET_MAGNETORQUER_FRAMEProtocolResponseData_t);

    if ((ctx != NULL) && (sActiveMtqFrame != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS;
        responseParams.hdr.funcId  = OBC_ES_COORDSYS_GET_MAGNETORQUER_FRAME_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sActiveMtqFrame != NULL)
        {
            responseParams.data.sActiveMtqFrame = *(sActiveMtqFrame);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sActiveMtqFrame,
                          0U,
                          sizeof(responseParams.data.sActiveMtqFrame));
        }
        responseParams.data.eOpResult = eOpResult;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_ES_COORDSYSGET_MAGNETORQUER_FRAMEProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMEProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMEProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMEProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS;
        responseParams.hdr.funcId  = OBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAME_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOpResult = eOpResult;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMEProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_COARSE_SUN_SENSOR_FRAME_t * const sActiveCssFrame,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_COORDSYSGET_COARSE_SUN_SENSOR_FRAMEProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_COORDSYSGET_COARSE_SUN_SENSOR_FRAMEProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSGET_COARSE_SUN_SENSOR_FRAMEProtocolResponseData_t);

    if ((ctx != NULL) && (sActiveCssFrame != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS;
        responseParams.hdr.funcId  = OBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAME_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sActiveCssFrame != NULL)
        {
            responseParams.data.sActiveCssFrame = *(sActiveCssFrame);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sActiveCssFrame,
                          0U,
                          sizeof(responseParams.data.sActiveCssFrame));
        }
        responseParams.data.eOpResult = eOpResult;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_ES_COORDSYSGET_COARSE_SUN_SENSOR_FRAMEProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_COORDSYS_SAVE_COORDSYS_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_COORDSYSSAVE_COORDSYS_CONFIGProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_COORDSYSSAVE_COORDSYS_CONFIGProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSSAVE_COORDSYS_CONFIGProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS;
        responseParams.hdr.funcId  = OBC_ES_COORDSYS_SAVE_COORDSYS_CONFIG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOpResult = eOpResult;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_ES_COORDSYSSAVE_COORDSYS_CONFIGProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_COORDSYS_LOAD_COORDSYS_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_COORDSYSLOAD_COORDSYS_CONFIGProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_COORDSYSLOAD_COORDSYS_CONFIGProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSLOAD_COORDSYS_CONFIGProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS;
        responseParams.hdr.funcId  = OBC_ES_COORDSYS_LOAD_COORDSYS_CONFIG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOpResult = eOpResult;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_ES_COORDSYSLOAD_COORDSYS_CONFIGProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_COORDSYS_SET_ACCELEROMETER_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMEProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMEProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMEProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS;
        responseParams.hdr.funcId  = OBC_ES_COORDSYS_SET_ACCELEROMETER_FRAME_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOpResult = eOpResult;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMEProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_COORDSYS_GET_ACCELEROMETER_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_ACCELEROMETER_FRAME_t * const sActiveAccFrame,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_COORDSYSGET_ACCELEROMETER_FRAMEProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_COORDSYSGET_ACCELEROMETER_FRAMEProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_COORDSYSGET_ACCELEROMETER_FRAMEProtocolResponseData_t);

    if ((ctx != NULL) && (sActiveAccFrame != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS;
        responseParams.hdr.funcId  = OBC_ES_COORDSYS_GET_ACCELEROMETER_FRAME_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sActiveAccFrame != NULL)
        {
            responseParams.data.sActiveAccFrame = *(sActiveAccFrame);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sActiveAccFrame,
                          0U,
                          sizeof(responseParams.data.sActiveAccFrame));
        }
        responseParams.data.eOpResult = eOpResult;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_ES_COORDSYSGET_ACCELEROMETER_FRAMEProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


