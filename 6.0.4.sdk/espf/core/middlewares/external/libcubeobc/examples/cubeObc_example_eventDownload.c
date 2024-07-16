/** @file cubeObc_example_eventDownload.c
 *
 * @brief libCubeObc Example - how to download the event log from CubeComputer
 *
 * @par
 * COPYRIGHT NOTICE: (c) 2023 Cubespace ADCS All rights reserved.
 */
#include <stdio.h>

#include <cubeObc/cubeObc.h>

#define CAN_DEVICE	"can0"	/**< Socketcan device */

#define DOWNLOAD_FILE "/path/to/your/file/cubeObc_events.evt" /**< Path to file to store events */

#define CAN_ADDR_CC	((U8)2u)	/**< CubeComputer CAN address */

/**
 * @brief Data used during download
 *
 * @note This is propogated as void *userData
 */
typedef struct DownloadDataStruct {
	FILE *filePtr;						/**< File pointer */
	S32 fileSeekIdx;					/**< File seek index for next frame to store */
	U16 lastFrameSize;					/**< Size of the last frame requested by the lib */
	U8 frameBuffer[BDT_MAX_FRAME_SIZE];	/**< Buffer for a single frame of data */
} DownloadData;

DownloadData downloadData;	/**< Data used during the download */

/* WEAK OVERRIDE */
ErrorCode cubeObc_canIfc_rx(CanPacket *packet)
{
	return cubeObc_can_rx(packet);
}

/* WEAK OVERRIDE */
ErrorCode cubeObc_canIfc_tx(CONST CanPacket *packet)
{
	return cubeObc_can_tx(packet);
}

/* WEAK OVERRIDE */
ErrorCode cubeObc_bulkDataTransfer_getFrameBuffer(void *userData, U8 **frame, U16 size)
{
	ErrorCode result = CUBEOBC_ERROR_OK;

	DownloadData *data = (DownloadData *)userData;

	// The bulk data transfer will write the frame in frameBuffer and then commit it
	*frame = data->frameBuffer;

	data->lastFrameSize = size;

	return result;
}

/* WEAK OVERRIDE */
ErrorCode cubeObc_bulkDataTransfer_commitFrameBuffer(void *userData, U8 *frame, U16 size)
{
	ErrorCode result = CUBEOBC_ERROR_OK;

	DownloadData *data = (DownloadData *)userData;

	if ((frame == data->frameBuffer) && (size == data->lastFrameSize))
	{
		fseek(data->filePtr, data->fileSeekIdx, SEEK_SET);

		U32 written = fwrite(data->frameBuffer, 1, size, data->filePtr);

		if (written != size)
		{
			result = CUBEOBC_ERROR_SIZE;
		}

		data->fileSeekIdx += size;
	}
	else
	{
		result = CUBEOBC_ERROR_COMMIT;
	}

	return result;
}

int main(void)
{
	ErrorCode result;
	TypeDef_TctlmEndpoint endpoint;
	CubeObc_Config config;
	CubeObc__Version version;
	CubeObc__Version sysVersion;

	config.hostAddress = 1u;

	endpoint.nodeType = TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_COMPUTER;
	endpoint.type = TYPEDEF__COMMS_ENDPOINT_CAN;
	endpoint.addr = CAN_ADDR_CC;
	endpoint.timeout = 500u;
	endpoint.passthrough = FALSE;

	cubeObc_init(&config);

	cubeObc_getVersion(&version);
	cubeObc_getSystemVersion(&sysVersion);

	printf("libCubeObc Version: %u.%u.%u\r\n", version.vMajor, version.vMinor, version.vPatch);
	printf("libCubeObc System Version: %u.%u.%u\r\n", sysVersion.vMajor, sysVersion.vMinor, sysVersion.vPatch);

	result = cubeObc_can_init(CAN_DEVICE);

	if (result != CUBEOBC_ERROR_OK)
	{
		printf("CAN initialization failed: %u\r\n", result);
		return -1;
	}

	/* MAKE SURE WE ARE TALKING TO CUBECOMPUTER*/

	TctlmCommonFramework1_Identification identification;

	result = tctlmCommonFramework1_getIdentification(&endpoint, &identification);

	if (result != CUBEOBC_ERROR_OK)
	{
		printf("Failed to get identification: %u\r\n", result);
		return -1;
	}

	if (identification.nodeType != TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_COMPUTER)
	{
		printf("Connected node is not CubeComputer!\r\n");
		return -1;
	}

	/* EVENT DOWNLOAD */

	printf("Downloading events to file: %s\r\n", DOWNLOAD_FILE);

	downloadData.filePtr = fopen(DOWNLOAD_FILE, "w");
	if (downloadData.filePtr == NULL)
	{
		printf("Failed to open file\r\n");
		return -1;
	}

	// We will write to the file frame by frame, starting from index 0
	downloadData.fileSeekIdx = 0;

	TctlmCubeComputerCommon3_EventLogStatus status;
	TctlmCubeComputerCommon3_EventLogFilterTransferSetup setup;

	MEMSET((U8 *)&setup, 0xFF, sizeof(setup)); // Include all classes and all sources

	// Now replace 0xFF in the fields we care about
	// We will request the last 500 events
	setup.filterType = TCTLM_CUBE_COMPUTER_COMMON_3__FILTER_LAST_X;
	setup.numEntries = 500u;
	// All other setup parameters are don't-care for this filter type

	result = cubeObc_cubeComputer_eventDownload(&endpoint, &setup, (void *)&downloadData, &status);

	if (result != CUBEOBC_ERROR_OK)
	{
		printf("Event download failed: %u\r\n", result);
		return -1;
	}

	printf("SUCCESS\r\n");

	fclose(downloadData.filePtr);

	return 0;
}
