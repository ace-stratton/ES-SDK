/** @file cubeObc_example_passthrough.c
 *
 * @brief libCubeObc Example - how to perform passthrough communication via CubeComputer
 *
 * @par
 * COPYRIGHT NOTICE: (c) 2023 Cubespace ADCS All rights reserved.
 */
#include <stdio.h>

#include <cubeObc/cubeObc.h>

#define USE_UART	(1)	/**< Select if UART test is done */
#define USE_CAN		(1) /**< Select if CAN test is done */

#define UART_DEVICE	"/dev/ttyUSB0"	/**< Terminal device */

#define CAN_DEVICE	"can0"	/**< Socketcan device */

#define CAN_ADDR_CC	((U8)2u)	/**< CubeComputer CAN address */

#define CAN_ADDR_CC_PASS	((U8)235u)	/**< CubeComputer CAN passthrough address (config item - this is the default) */

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

/**
 * @brief Perform a general passthrough test
 *
 * @param[in] endpoint Comms endpoint
 */
int performPassthrough(TypeDef_TctlmEndpoint *endpoint)
{
	ErrorCode result;

	// DISABLE PASSTHROUGH
	endpoint->passthrough = FALSE;

	TctlmCommonFramework1_Identification identification;

	result = tctlmCommonFramework1_getIdentification(endpoint, &identification); // To CubeComputer

	if (result != CUBEOBC_ERROR_OK)
	{
		printf("Failed to get identification: %u\r\n", result);
		return result;
	}

	if (identification.nodeType != TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_COMPUTER)
	{
		printf("Connected node is not CubeComputer!\r\n");
		return result;
	}

	// Set the passthrough target

	result = tctlmCubeComputerCommon3_setPassThrough(endpoint, TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_FSS_0); // To CubeComputer

	if (result != CUBEOBC_ERROR_OK)
	{
		printf("Failed to set the passthrough target: %u\r\n", result);
		return result;
	}

	// Power on the target node for passthrough

	TctlmCubeComputerCommon3_PowerState power;

	ZERO_VAR(power);

	// Power on for passthrough
	// Note that POWER_ON_PASS prevents the control-program from communicating with the node
	// However, it is still possible to perform passthrough communications while the control-program is using the node
	power.fss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON_PASS;

	result = tctlmCubeComputerCommon3_setPowerState(endpoint, &power); // To CubeComputer

	if (result != CUBEOBC_ERROR_OK)
	{
		printf("Failed to power on node: %u\r\n", result);
		return result;
	}

	// Wait for boot
	cubeObc_time_delay(1000u);

	// ENABLE PASSTHROUGH
	endpoint->passthrough = TRUE;

	result = tctlmCommonFramework1_getIdentification(endpoint, &identification); // To Node

	if (result != CUBEOBC_ERROR_OK)
	{
		printf("Failed to get identification with passthrough: %u\r\n", result);
		return result;
	}

	// We use the abstract type to define the passthrough target, so,
	// to keep the example simple, we do not check for the exact expected node type,
	// which would require requesting the "ExpectedNodes" telemetry and extracting the mapping...
	// In the OBC this mapping should be hard coded and easy to look up.
	// In this example, we only make sure we get a different identification than that of CubeComputer.
	// The node type enum value is printed bellow for validation.

	if (identification.nodeType == TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_COMPUTER)
	{
		printf("Passthrough communication did not work!\r\n");
		return result;
	}

	printf("Passthrough identification NodeType: %u\r\n", (U32)identification.nodeType);
	printf("Passthrough identification ProgramType: %u\r\n", (U32)identification.programType);

	/*
	 * The tctlmCommonFramework1_getIdentification() telemetry is the most simple example
	 * because it should return a different NodeType when using passthrough.
	 * However, it might not best illustrate how to use passthrough...
	 *
	 * As an example, the following telemetry could slot in here to set the CubeSense boresight via CubeComputer:
	 *
	 * result = tctlmCubeSenseControlProgram5_setCamBoresight(endpoint, &setVal);
	 *
	 * So we call a CubeSense API, the endpoint is setup to target CubeComputer.
	 * The telecommand data will be formatted to set the boresight such that CubeSense can parse it,
	 * but the protocol data is changed so that CubeComputer knows that it is a passthrough message.
	 *
	 * Note that the endpoint nodeType stays as CubeComputer when using passthrough, since the communication is still physically with CubeComputer.
	 */

	// DISABLE PASSTHROUGH
	endpoint->passthrough = FALSE;

	// Power off the target node

	power.fss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF;

	result = tctlmCubeComputerCommon3_setPowerState(endpoint, &power); // To CubeComputer

	// Allow power dissipation in case another iteration is performed
	cubeObc_time_delay(1000u);

	return result;
}

/**
 * @brief main - CubeSpace passthrough example
 */
int main(void)
{
	ErrorCode result;
	TypeDef_TctlmEndpoint endpoint;
	CubeObc_Config config;
	CubeObc__Version version;
	CubeObc__Version sysVersion;

	config.hostAddress = 1u;

	cubeObc_init(&config);

	cubeObc_getVersion(&version);
	cubeObc_getSystemVersion(&sysVersion);

	printf("libCubeObc Version: %u.%u.%u\r\n", version.vMajor, version.vMinor, version.vPatch);
	printf("libCubeObc System Version: %u.%u.%u\r\n", sysVersion.vMajor, sysVersion.vMinor, sysVersion.vPatch);

	/************************/
	/********* UART *********/
	/************************/

#if (USE_UART == 1)

	endpoint.nodeType = TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_COMPUTER;
	endpoint.type = TYPEDEF__COMMS_ENDPOINT_UART;
	endpoint.timeout = 500u;

	result = cubeObc_uart_init(UART_DEVICE, 921600u);

	if (result != CUBEOBC_ERROR_OK)
	{
		printf("UART initialization failed: %u\r\n", result);
		return -1;
	}

	printf("\r\nPerforming passthrough over UART...\r\n");

	result = performPassthrough(&endpoint);

	if (result != CUBEOBC_ERROR_OK)
	{
		printf("UART passthrough failed: %u\r\n", result);
	}

#endif

	/************************/
	/********* CAN **********/
	/************************/

#if (USE_CAN == 1)

	endpoint.nodeType = TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_COMPUTER;
	endpoint.type = TYPEDEF__COMMS_ENDPOINT_CAN;
	endpoint.addr = CAN_ADDR_CC;
	endpoint.addrPass = CAN_ADDR_CC_PASS;
	endpoint.timeout = 500u;

	result = cubeObc_can_init(CAN_DEVICE);

	if (result != CUBEOBC_ERROR_OK)
	{
		printf("CAN initialization failed: %u\r\n", result);
		return -1;
	}

	printf("\r\nPerforming passthrough over CAN...\r\n");

	result = performPassthrough(&endpoint);

	if (result != CUBEOBC_ERROR_OK)
	{
		printf("CAN passthrough failed: %u\r\n", result);
	}

#endif

	printf("\r\nDONE\r\n");

	return 0;
}
