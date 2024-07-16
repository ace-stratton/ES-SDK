/** @file cubeObc_example_cubeSpaceFileUpload.c
 *
 * @brief libCubeObc Example - how to upload a CubeSpace file to cube-computer control-program
 *
 * @par
 * COPYRIGHT NOTICE: (c) 2023 Cubespace ADCS All rights reserved.
 */
#include <stdio.h>

#include <cubeObc/cubeObc.h>

#define TO_BOOTLOADER	(1)	/**< Select if the file should be uploaded to bootloader or CubeComputer control-program */

#define USE_UART		(1) /**< Select to use UART (1) or CAN (0) */

#define UART_DEVICE	"/dev/ttyUSB0"	/**< Terminal device */

#define CAN_DEVICE	"can0"		/**< CAN device */
#define CAN_ADDR_CC	((U8)2u)	/**< CubeComputer CAN address */

#define UPLOAD_FILE "/path/to/your/file/<file>.cs"	/**< CubeSpace file to upload - use a file from software bundle */

/**
 * @brief Data used during upload
 *
 * @note This is propogated as void *userData
 */
typedef struct UploadDataStruct {
	FILE *filePtr;						/**< File pointer */
	S32 fileSeekIdx;					/**< File seek index for next frame to extract */
	U16 lastFrameSize;					/**< Size of the last frame requested by the lib */
	U8 frameBuffer[BDT_MAX_FRAME_SIZE];	/**< Buffer for a single frame of data */
} UploadData;

UploadData uploadData;	/**< Data used during upload */

/* WEAK OVERRIDE */
ErrorCode cubeObc_uartIfc_rx(U8 *data, U32 size, U32 *sizeRead)
{
	return cubeObc_uart_rx(data, size, sizeRead);
}

/* WEAK OVERRIDE */
ErrorCode cubeObc_uartIfc_tx(CONST U8 *data, U32 size)
{
	return cubeObc_uart_tx(data, size);
}

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

	UploadData *data = (UploadData *)userData;

	fseek(data->filePtr, data->fileSeekIdx, SEEK_SET);

	U32 numRead = fread(data->frameBuffer, 1, size, data->filePtr);

	if (numRead != size)
	{
		result = CUBEOBC_ERROR_SIZE;
	}

	*frame = data->frameBuffer;

	data->lastFrameSize = size;

	return result;
}

/* WEAK OVERRIDE */
ErrorCode cubeObc_bulkDataTransfer_commitFrameBuffer(void *userData, U8 *frame, U16 size)
{
	ErrorCode result = CUBEOBC_ERROR_OK;

	UploadData *data = (UploadData *)userData;

	if ((frame == data->frameBuffer) && (size == data->lastFrameSize))
	{
		data->fileSeekIdx += size;
	}
	else
	{
		result = CUBEOBC_ERROR_COMMIT;
	}

	return result;
}

/**
 * @brief main - CubeSpace file upload example
 */
int main(void)
{
	ErrorCode result;
	TypeDef_TctlmEndpoint endpoint;
	CubeObc_Config config;
	CubeObc__Version version;
	CubeObc__Version sysVersion;

	config.hostAddress = 1u;

	endpoint.nodeType = TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_COMPUTER;
	endpoint.timeout = 500u;
	endpoint.passthrough = FALSE;

	cubeObc_init(&config);

	cubeObc_getVersion(&version);
	cubeObc_getSystemVersion(&sysVersion);

	printf("libCubeObc Version: %u.%u.%u\r\n", version.vMajor, version.vMinor, version.vPatch);
	printf("libCubeObc System Version: %u.%u.%u\r\n", sysVersion.vMajor, sysVersion.vMinor, sysVersion.vPatch);

#if (USE_UART == 1)

	endpoint.type = TYPEDEF__COMMS_ENDPOINT_UART;

	result = cubeObc_uart_init(UART_DEVICE, 921600u);

	if (result != CUBEOBC_ERROR_OK)
	{
		printf("UART initialization failed: %u\r\n", result);
		return -1;
	}

#else

	endpoint.type = TYPEDEF__COMMS_ENDPOINT_CAN;
	endpoint.addr = CAN_ADDR_CC;

	result = cubeObc_can_init(CAN_DEVICE);

	if (result != CUBEOBC_ERROR_OK)
	{
		printf("CAN initialization failed: %u\r\n", result);
		return -1;
	}

#endif

	/* MAKE SURE THE CUBE-COMPUTER CONTROL-PROGRAM IS RUNNING */

	TctlmCommonFramework1_Identification identification;

	result = tctlmCommonFramework1_getIdentification(&endpoint, &identification);

	if (result != CUBEOBC_ERROR_OK)
	{
		printf("Failed to get identification: %u\r\n", result);
		return -1;
	}

#if (TO_BOOTLOADER == 1)

	if (identification.programType != TCTLM_COMMON_FRAMEWORK_ENUMS__PROGRAM_TYPE_BOOTLOADER)
	{
		printf("Reset to bootloader...\r\n");

		(void)tctlmCommonFramework1_setReset(&endpoint, TCTLM_COMMON_FRAMEWORK_1__SOFT);

		// Wait for boot
		cubeObc_time_delay(1000u);

		result = tctlmCommonFramework1_getIdentification(&endpoint, &identification);

		if (result != CUBEOBC_ERROR_OK)
		{
			printf("Failed to get identification after reset: %u\r\n", result);
			return -1;
		}

		if (identification.programType != TCTLM_COMMON_FRAMEWORK_ENUMS__PROGRAM_TYPE_BOOTLOADER)
		{
			printf("Failed to enter bootloader!\r\n");
			return -1;
		}

		printf("Halting to bootloader...\r\n");

		result = tctlmCubeCommonBaseBootloader5_setHalt(&endpoint);

		if (result != CUBEOBC_ERROR_OK)
		{
			printf("Failed to get halt bootloader: %u\r\n", result);
			return -1;
		}

		// Continue to upload
	}

#else

	if (identification.nodeType != TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_COMPUTER)
	{
		printf("Connected node is not CubeComputer!\r\n");
		return -1;
	}

	if (identification.programType != TCTLM_COMMON_FRAMEWORK_ENUMS__PROGRAM_TYPE_CONTROL)
	{
		if (identification.programType == TCTLM_COMMON_FRAMEWORK_ENUMS__PROGRAM_TYPE_BOOTLOADER)
		{
			printf("Jumping to control-program...\r\n");

			// Tel the bootloader to jump to app
			result = tctlmCubeCommonBaseBootloader5_setJumpToDefaultApp(&endpoint);

			if (result != CUBEOBC_ERROR_OK)
			{
				printf("Failed to command bootloader to jump: %u\r\n", result);
				return -1;
			}

			// Wait for boot
			cubeObc_time_delay(1000u);

			// Wait for port validation/auto-discovery to complete
			result =  cubeObc_common_pollForBootState(&endpoint, TCTLM_COMMON_FRAMEWORK_1__APPLICATION_RUNNING, 500u, 10000u, FALSE);

			if (result != CUBEOBC_ERROR_OK)
			{
				printf("control-program failed to complete port validation/auto-discovery within 10 seconds: %u\r\n", result);
				return -1;
			}
		}
		else
		{
			printf("Connected program is not control-program or bootloader!\r\n");
			return -1;
		}
	}

#endif

	/* FILE UPLOAD */

	printf("Uploading file: %s\r\n", UPLOAD_FILE);

	uploadData.filePtr = fopen(UPLOAD_FILE, "r");
	if (uploadData.filePtr == NULL)
	{
		printf("Failed to open file\r\n");
		return -1;
	}
	fseek(uploadData.filePtr, 0, SEEK_END);
	S32 fsize = ftell(uploadData.filePtr);

	// We will read the file frame by frame, starting from index 0 from the start
	// The library will handle reading the meta data
	uploadData.fileSeekIdx = 0;

#if (TO_BOOTLOADER == 1)

	printf("Uploading to bootloader...\r\n");

	TctlmCubeCommonBaseBootloader5_Errors errors;

	result = cubeObc_bootloader_uploadCubeSpaceFile(&endpoint, (U32)fsize, (void *)&uploadData, &errors);

	if (result != CUBEOBC_ERROR_OK)
	{
		printf("File upload failed: %u\r\n", result);
		printf("errors.result = %u\r\n", errors.result);
		return -1;
	}

#else

	printf("Uploading to control-program...\r\n");

	TctlmCubeComputerControlProgram8_FileTransferStatus status;

	result = cubeObc_cubeComputer_uploadCubeSpaceFile(&endpoint, (U32)fsize, (void *)&uploadData, &status);

	if (result != CUBEOBC_ERROR_OK)
	{
		printf("File upload failed: %u\r\n", result);
		printf("status.errorCode = %u\r\n", status.errorCode);
		return -1;
	}

#endif

	printf("SUCCESS\r\n");

	fclose(uploadData.filePtr);

	return 0;
}
