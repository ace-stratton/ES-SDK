/** @file cubeObc_tctlmCommsMasterSvc.c
 *
 * @brief libCubeObc TCTLM Master Comms Handler
 *
 * @par
 * COPYRIGHT NOTICE: (c) 2023 Cubespace ADCS All rights reserved.
 */

/***************************** SYSTEM INCLUDES *******************************/

/***************************** MODULE INCLUDES *******************************/

#include <cubeObc/cubeObc_tctlmCommsMasterSvc.h>

/***************************** MODULE DEFINES ********************************/

/**
 * @brief TC/TLM protocol max frame size
 */
#define COMMS_BUFFER_SIZE	((U32)512)

/**
 * @brief Telemetry Start ID
 */
#define V1_TLM_ID_START	((U8)128u)

/**
 * @brief TC/TLM Message Type (5bit) mask
 */
#define V1_TCTLM_CAN_EXTDID_TYPE_MASK  ((U32)0x1Fu)
/**
 * @brief TC/TLM Message Type (5bit) shift
 */
#define V1_TCTLM_CAN_EXTDID_TYPE_SHIFT ((U32)24u)
/**
 * @brief TC/TLM Message Number (8bit) mask
 */
#define V1_TCTLM_CAN_EXTDID_ID_MASK  ((U32)0xFFu)
/**
 * @brief TC/TLM Message Number (8bit) shift
 */
#define V1_TCTLM_CAN_EXTDID_ID_SHIFT ((U32)16u)
/**
 * @brief TC/TLM Message CAN Source address (8bit) mask
 */
#define V1_TCTLM_CAN_EXTDID_SRC_MASK  ((U32)0xFFu)
/**
 * @brief TC/TLM Message CAN Source address (8bit) shift
 */
#define V1_TCTLM_CAN_EXTDID_SRC_SHIFT ((U32)8u)
/**
 * @brief TC/TLM Message CAN Destination address (8bit) mask
 */
#define V1_TCTLM_CAN_EXTDID_DST_MASK  ((U32)0xFFu)
/**
 * @brief TC/TLM Message CAN Destination address (8bit) shift
 */
#define V1_TCTLM_CAN_EXTDID_DST_SHIFT ((U32)0u)

#define V1_TCTLM_UART_EOM_OFFSET ((U32)1u)				/*!< Footer offset where the EOM byte is located */
#define V1_TCTLM_UART_SOM_OFFSET ((U32)1u)				/*!< Header offset where the SOM byte is located */
#define V1_TCTLM_UART_ESCAPE_OFFSET ((U32)0u)			/*!< Footer/Header offset where the Escape byte is located */
#define V1_TCTLM_UART_ID_OFFSET ((U32)2u)				/*!< Header offset where the ID byte is located */

/* Plain protocol Point-to-Point */
#define V1_TCTLM_UART_HEADER_SIZE_PLAIN ((U32)3u)		/*!< PLAIN: Offset in the buffer where the remaining data starts */
#define V1_TCTLM_UART_SOM_NORMAL_PLAIN ((U8)0x7Fu)		/*!< PLAIN: Start of Message in UART protocol */
#define V1_TCTLM_UART_SOM_NACK_PLAIN ((U8)0x0Fu)		/*!< PLAIN: Start of Nack Message in UART protocol */
#define V1_TCTLM_UART_SOM_ACK_PLAIN ((U8)0x07u)			/*!< PLAIN: Start of Ack Message in UART protocol */
#define V1_TCTLM_UART_SOM_EVENT ((U8)0x2Fu)				/*!< PLAIN: Start of Event Message in UART protocol */
#define V1_TCTLM_UART_SOM_UNSOL ((U8)0x4Fu)				/*!< PLAIN: Start of Unsolicited TLM Message in UART protocol */

/* Passthrough protocol Point-to-Point */
#define V1_TCTLM_UART_SOM_NORMAL_PASS ((U8)0x7Eu)		/*!< PASSTHROUGH: Start of Message in UART protocol */
#define V1_TCTLM_UART_SOM_NACK_PASS ((U8)0x0Eu)			/*!< PASSTHROUGH: Start of Nack Message in UART protocol */
#define V1_TCTLM_UART_SOM_ACK_PASS ((U8)0x06u)			/*!< PASSTHROUGH: Start of Ack Message in UART protocol */

/**
 * @brief Size of the footer appended to the data payload
 */
#define V1_TCTLM_UART_FOOTER_SIZE   ((U32)2u)

/**
 * @brief Escape char in UART protocol
 */
#define V1_TCTLM_UART_ESCAPE ((U8)0x1Fu)

/**
 * @brief End of Message in UART protocol
 */
#define V1_TCTLM_UART_EOM ((U8)0xFFu)

/****************************** MODULE MACROS ********************************/

/***************************** MODULE TYPEDEFS *******************************/

/**
 * @brief Message Types
 */
typedef enum V1TctlmCanTransport_TypeEnum {
	V1_TCTLM_CAN_TRANSPORT__TYPE_NONE = 0,				/**< Invalid */
	V1_TCTLM_CAN_TRANSPORT__TYPE_TC = 1,				/**< Telecommand */
	V1_TCTLM_CAN_TRANSPORT__TYPE_TC_EXT = 7,			/**< Telecommand Extended*/
	V1_TCTLM_CAN_TRANSPORT__TYPE_TC_RESP = 2,			/**< Telecommand Reply */
	V1_TCTLM_CAN_TRANSPORT__TYPE_TC_NACK = 3,			/**< Telecommand Request Invalid Reply */
	V1_TCTLM_CAN_TRANSPORT__TYPE_TLM = 4,				/**< Telemetry request */
	V1_TCTLM_CAN_TRANSPORT__TYPE_TLM_RESP = 5,			/**< Telemetry reply */
	V1_TCTLM_CAN_TRANSPORT__TYPE_TLM_RESP_EXT = 8,		/**< Telemetry Extended reply */
	V1_TCTLM_CAN_TRANSPORT__TYPE_TLM_NACK = 6,			/**< Telemetry Request Invalid Reply */
	V1_TCTLM_CAN_TRANSPORT__TYPE_EVENT = 9,				/**< Unsolicited event */
	V1_TCTLM_CAN_TRANSPORT__TYPE_USOL_TLM_FIRST = 10,	/**< Unsolicited telemetry first packet */
	V1_TCTLM_CAN_TRANSPORT__TYPE_USOL_TLM_BODY = 11,	/**< Unsolicited telemetry body packet */
	V1_TCTLM_CAN_TRANSPORT__TYPE_USOL_TLM_LAST = 12,	/**< Unsolicited telemetry last packet */
} V1TctlmCanTransport_Type;

/**
 * @brief Handle
 */
typedef struct HandleStruct {
	U8 buffer[COMMS_BUFFER_SIZE];							/**< Buffer for packing and unpacking */
	U32 bufferSize;											/**< Buffer size */
	U32 bufferSizeUsed;										/**< Buffer size used */
	U32 timeout;											/**< Master rx timeout */
	U32 busyStart;											/**< Millisecond ticks captured at start of transaction (used for timeout) */
} Handle;

/***************************** MODULE VARIABLES ******************************/

/**
 * @brief Master comms handles
 */
PRIVATE Handle handle[TYPEDEF__COMMS_ENDPOINT_MAX];

/**
 * @brief Buffer used for UART data containing protocol bytes
 *
 * @note a separate buffer is used instead of moving data around to insert special characters
 */
PRIVATE U8 uartProtocolBuffer[COMMS_BUFFER_SIZE];

/**
 * @brief Host address (for CAN interface)
 */
PRIVATE U8 hostAddr;

/***************************** MODULE FUNCTIONS ******************************/

/**
 * @brief Convert TCTLM nack value to global error code
 *
 * @param[in]	byte	Nack byte
 *
 * @return Global error code corresponding to TCTLM nack byte
 */
PRIVATE ErrorCode nackToErrorCode(U8 byte)
{
	ErrorCode result;

	switch (byte)
	{
		case (U8)TCTLM__ERROR_OK:
		{
			result = CUBEOBC_ERROR_OK;
		}
		break;

		case (U8)TCTLM__ERROR_INVALID_ID:
		{
			result = CUBEOBC_ERROR_TCTLM_INVALID_ID;
		}
		break;

		case (U8)TCTLM__ERROR_INVALID_LENGTH:
		{
			result = CUBEOBC_ERROR_TCTLM_INVALID_LENGTH;
		}
		break;

		case (U8)TCTLM__ERROR_INVALID_PARAM:
		{
			result = CUBEOBC_ERROR_TCTLM_INVALID_PARAM;
		}
		break;

		case (U8)TCTLM__ERROR_CRC:
		{
			result = CUBEOBC_ERROR_TCTLM_CRC;
		}
		break;

		case (U8)TCTLM__ERROR_NOT_IMPLEMENTED:
		{
			result = CUBEOBC_ERROR_TCTLM_NOT_IMPLEMENTED;
		}
		break;

		case (U8)TCTLM__ERROR_BUSY:
		{
			result = CUBEOBC_ERROR_TCTLM_BUSY;
		}
		break;

		case (U8)TCTLM__ERROR_SEQUENCE:
		{
			result = CUBEOBC_ERROR_TCTLM_SEQUENCE;
		}
		break;

		case (U8)TCTLM__ERROR_INTERNAL:
		{
			result = CUBEOBC_ERROR_TCTLM_INTERNAL;
		}
		break;

		case (U8)TCTLM__ERROR_PASS_TIMEOUT:
		{
			result = CUBEOBC_ERROR_TCTLM_PASS_TOUT;
		}
		break;

		case (U8)TCTLM__ERROR_PASS_TARGET:
		{
			result = CUBEOBC_ERROR_TCTLM_PASS_TARGET;
		}
		break;

		default:
		{
			result = CUBEOBC_ERROR_UKN_NACK;
		}
		break;
	}

	return result;
}

/***************************** GLOBAL FUNCTIONS ******************************/

ErrorCode cubeObc_tctlmCommsMasterSvc_init(U8 hostAddress)
{
	hostAddr = hostAddress;

	handle[TYPEDEF__COMMS_ENDPOINT_CAN].bufferSize = COMMS_BUFFER_SIZE;
	handle[TYPEDEF__COMMS_ENDPOINT_I2C].bufferSize = COMMS_BUFFER_SIZE;
	handle[TYPEDEF__COMMS_ENDPOINT_UART].bufferSize = COMMS_BUFFER_SIZE;

	return CUBEOBC_ERROR_OK;
}

uint8_t *cubeObc_tctlmCommsMasterSvc_buffer(CONST TctlmCommsMasterSvc_Endpoint *masterEndpoint)
{
	return handle[masterEndpoint->endpoint.type].buffer;
}

U32 cubeObc_tctlmCommsMasterSvc_bufferSize(CONST TctlmCommsMasterSvc_Endpoint *masterEndpoint)
{
	return handle[masterEndpoint->endpoint.type].bufferSize;
}

ErrorCode cubeObc_tctlmCommsMasterSvc_sendReceive(TctlmCommsMasterSvc_Endpoint *masterEndpoint, U32 *bufferSizeUsed)
{
	ErrorCode result = CUBEOBC_ERROR_OK;
	TypeDef_TctlmEndpoint *endpoint = &masterEndpoint->endpoint; // Get the generic endpoint

	switch (endpoint->type)
	{
		case TYPEDEF__COMMS_ENDPOINT_CAN:
		{
			// Empty the rx buffer before new transaction
			cubeObc_canIfc_rxFlush();

			// Build up the header
			U8 packetLeftCounter = 0u;
			U8 *data = handle[endpoint->type].buffer;
			U32 dataLen = *bufferSizeUsed;
			V1TctlmCanTransport_Type msgType;

			if (masterEndpoint->id < V1_TLM_ID_START)
			{
				// This is a telecommand
				if (*bufferSizeUsed > CAN_DATA_BYTES)
				{
					// The telecommand requires multiple packets
					msgType = V1_TCTLM_CAN_TRANSPORT__TYPE_TC_EXT;

					packetLeftCounter = (U8)(dataLen / 7u);
					if ((dataLen % 7u) == 0u)
					{
						packetLeftCounter--;
					}
				}
				else
				{
					// The telecommand requires only one packet of data
					msgType = V1_TCTLM_CAN_TRANSPORT__TYPE_TC;
				}
			}
			else
			{
				// This is a telemetry request
				msgType = V1_TCTLM_CAN_TRANSPORT__TYPE_TLM;
			}

			U8 dstAddr;

			if (endpoint->passthrough == FALSE)
			{
				dstAddr = endpoint->addr;
			}
			else
			{
				dstAddr = endpoint->addrPass;
			}

			// Format the extended ID
			// The headers for all the CAN message packets are identical
			U32 canExtendedID = (((U32)msgType & V1_TCTLM_CAN_EXTDID_TYPE_MASK) << V1_TCTLM_CAN_EXTDID_TYPE_SHIFT) |
								((masterEndpoint->id & V1_TCTLM_CAN_EXTDID_ID_MASK) << V1_TCTLM_CAN_EXTDID_ID_SHIFT) |
								((hostAddr & V1_TCTLM_CAN_EXTDID_SRC_MASK) << V1_TCTLM_CAN_EXTDID_SRC_SHIFT) |
								((dstAddr & V1_TCTLM_CAN_EXTDID_DST_MASK) << V1_TCTLM_CAN_EXTDID_DST_SHIFT);

			U32 packets = packetLeftCounter + 1u; // The number of packet to be transmitted
			U32 offset = 0u; // The offset within the data buffer to next extract data for packet or insert from packet

			// Format and transmit the packets. Exit in error.
			for (U32 i = 0u; ((i < packets) && (result == CUBEOBC_ERROR_OK)); i++)
			{
				CanPacket packet;

				ZERO_VAR(packet);

				packet.canExtId = canExtendedID;
				packet.idType = CAN_ID_TYPE_EXTENDED;

				// Does this CAN message contain data?
				if (dataLen > 0u)
				{
					U8 copyLen; // The amount of data we need to copy from the data buffer in to this packet

					// Multi-packet sequence
					if (dataLen > CAN_DATA_BYTES)
					{
						packet.canSize = CAN_DATA_BYTES;
						copyLen = 7u;

						if ((offset + copyLen) > dataLen)
						{
							// This is the last packet
							copyLen = dataLen - offset;
							packet.canData[copyLen] = packetLeftCounter;
							packet.canSize = copyLen + 1u;
						}
						else
						{
							packet.canData[7u] = packetLeftCounter;
						}

						packetLeftCounter--;
					}
					// Single packet
					else
					{
						copyLen = dataLen;
						packet.canSize = dataLen;
					}

					// Copy data into the CAN packet
					MEMCPY(packet.canData, &data[offset], copyLen);

					// How much data we processed so far
					offset += copyLen;
				}

				// Send CAN packet
				result = cubeObc_canIfc_tx(&packet);

				// 1ms delay between packets for CubeComputer
				if ((endpoint->nodeType == TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_COMPUTER) &&
					(packetLeftCounter > 0u))
				{
					cubeObc_time_delay(1u);
				}
			}

			// Now wait for the response
			if (result == CUBEOBC_ERROR_OK)
			{
				offset = 0u;
				handle[endpoint->type].busyStart = cubeObc_time_getMs(); // Capture start time for timeout
				Boolean done = FALSE;

				do
				{
					ErrorCode managedResult;
					CanPacket packet;
					V1TctlmCanTransport_Type rxMsgType;
					U8 tctlmId;

					ZERO_VAR(packet);

					managedResult = cubeObc_canIfc_rx(&packet);

					if (managedResult == CUBEOBC_ERROR_OK)
					{
						U8 copyLen;

						tctlmId = (packet.canExtId >> V1_TCTLM_CAN_EXTDID_ID_SHIFT) & V1_TCTLM_CAN_EXTDID_ID_MASK;

						if (tctlmId != masterEndpoint->id)
						{
							result = CUBEOBC_ERROR_TCTLM_ID;
						}

						if (result == CUBEOBC_ERROR_OK)
						{
							rxMsgType = (V1TctlmCanTransport_Type)((packet.canExtId >> V1_TCTLM_CAN_EXTDID_TYPE_SHIFT) &
																   V1_TCTLM_CAN_EXTDID_TYPE_MASK);

							// Multi-packet sequence
							if (rxMsgType == V1_TCTLM_CAN_TRANSPORT__TYPE_TLM_RESP_EXT)
							{
								packetLeftCounter = packet.canData[packet.canSize - 1u];
								copyLen = packet.canSize - 1u;

								done = (packetLeftCounter == 0u);
							}
							// Single packet
							else
							{
								/* Check for Nack */
								if ((rxMsgType == V1_TCTLM_CAN_TRANSPORT__TYPE_TC_NACK) ||
									(rxMsgType == V1_TCTLM_CAN_TRANSPORT__TYPE_TLM_NACK))
								{
									result = nackToErrorCode(packet.canData[0u]);
								}

								copyLen = packet.canSize;

								done = TRUE;
							}

							// Extract data from packet
							MEMCPY(&data[offset], packet.canData, copyLen);

							// How much data we processed so far
							offset += copyLen;
						}
					}
					else
					{
						// Keep retrying until timeout is reached
					}

					if (result == CUBEOBC_ERROR_OK)
					{
						U32 timeDelta = cubeObc_time_getMs() - handle[endpoint->type].busyStart;

						if (timeDelta >= endpoint->timeout)
						{
							result = CUBEOBC_ERROR_TOUT;

							done = TRUE;
						}
					}
				}
				while ((result == CUBEOBC_ERROR_OK) && (done == FALSE));

				// How much data we received (does not include protocol bytes)
				*bufferSizeUsed = offset;
			}
		}
		break;

		case TYPEDEF__COMMS_ENDPOINT_UART:
		{
			// Empty the rx buffer before new transaction
			cubeObc_uartIfc_rxFlush();

			U8 *data = handle[TYPEDEF__COMMS_ENDPOINT_UART].buffer;
			U32 dataLen = *bufferSizeUsed;
			U32 dataProtocolIdx = 0u; // Index in the protocol buffer to insert data

			// Insert escape character for SOM byte
			uartProtocolBuffer[V1_TCTLM_UART_ESCAPE_OFFSET] = V1_TCTLM_UART_ESCAPE;

			// Insert SOM Byte
			if (endpoint->passthrough == FALSE)
			{
				uartProtocolBuffer[V1_TCTLM_UART_SOM_OFFSET] = V1_TCTLM_UART_SOM_NORMAL_PLAIN;
			}
			else
			{
				uartProtocolBuffer[V1_TCTLM_UART_SOM_OFFSET] = V1_TCTLM_UART_SOM_NORMAL_PASS;
			}

			// Insert TCTLM ID
			uartProtocolBuffer[V1_TCTLM_UART_ID_OFFSET] = masterEndpoint->id;

			// Update buffer index after populating header bytes
			dataProtocolIdx += V1_TCTLM_UART_HEADER_SIZE_PLAIN;

			// Now we must replace any escape characters in the payload with the escape sequence (0x1f => 0x1f 0x1f)
			for (U32 i = 0u; i < dataLen; i++)
			{
				if (data[i] == V1_TCTLM_UART_ESCAPE)
				{
					uartProtocolBuffer[dataProtocolIdx] = V1_TCTLM_UART_ESCAPE;

					dataProtocolIdx++;
				}

				uartProtocolBuffer[dataProtocolIdx] = data[i];

				dataProtocolIdx++;
			}

			// Add the end of message sequence (0x1f 0xff)
			uartProtocolBuffer[dataProtocolIdx] = V1_TCTLM_UART_ESCAPE;
			dataProtocolIdx++;
			uartProtocolBuffer[dataProtocolIdx] = V1_TCTLM_UART_EOM;
			dataProtocolIdx++; // This is now equal to the size of the complete data with protocol bytes

			// Now we send the protocol formatted buffer to the device
			result = cubeObc_uartIfc_tx(uartProtocolBuffer, dataProtocolIdx);

			// Now wait for response
			if (result == CUBEOBC_ERROR_OK)
			{
				handle[endpoint->type].busyStart = cubeObc_time_getMs();

				Boolean done = FALSE;
				U32 dataIdx = 0u;
				Boolean escaped = FALSE; // Is the last processed byte the escape character
				Boolean som = FALSE; // Is the last processed byte the start-of-message (SOM) character
				Boolean validRxWindow = FALSE;	// Have we received a valid header and can we start extracting data bytes
				Boolean nack = FALSE; // Is the response type a nack
				Boolean passthrough = FALSE;
				U8 tctlmId;

				do
				{
					U8 byte;
					U32 sizeRead;

					// Read one byte at a time
					result = cubeObc_uartIfc_rx(&byte, sizeof(byte), &sizeRead);

					if ((result == CUBEOBC_ERROR_OK) &&
						(sizeRead != sizeof(byte)))
					{
						result = CUBEOBC_ERROR_SIZE;
					}

					if (result == CUBEOBC_ERROR_OK)
					{
						if (escaped == TRUE)
						{
							if ((byte == V1_TCTLM_UART_SOM_ACK_PLAIN) ||
								(byte == V1_TCTLM_UART_SOM_ACK_PASS))
							{
								som = TRUE;
								passthrough = (byte == V1_TCTLM_UART_SOM_ACK_PASS);
							}
							else if ((byte == V1_TCTLM_UART_SOM_NACK_PLAIN) ||
									 (byte == V1_TCTLM_UART_SOM_NACK_PASS))
							{
								som = TRUE;
								nack = TRUE;
								passthrough = (byte == V1_TCTLM_UART_SOM_NACK_PASS);
							}
							else if (byte == V1_TCTLM_UART_EOM)
							{
								done = TRUE;
							}
							else if (byte == V1_TCTLM_UART_ESCAPE)
							{
								if (validRxWindow == TRUE)
								{
									data[dataIdx] = byte;
									dataIdx++;
								}
							}

							escaped = FALSE; // The escape byte has now been handled
						}
						else
						{
							if (byte == V1_TCTLM_UART_ESCAPE)
							{
								escaped = TRUE;
							}
							else
							{
								if (som == TRUE)
								{
									tctlmId = byte; // The byte following the SOM is always the tctlm ID
									validRxWindow = TRUE;
									som = FALSE; // The SOM byte has now been handled
								}
								else if (validRxWindow == TRUE)
								{
									data[dataIdx] = byte;
									dataIdx++;
								}
							}
						}
					}
					else
					{
						// Keep retrying until timeout is reached
					}

					U32 timeDelta = cubeObc_time_getMs() - handle[endpoint->type].busyStart;

					if (timeDelta >= endpoint->timeout)
					{
						result = CUBEOBC_ERROR_TOUT;

						done = TRUE;
					}
				}
				while (done == FALSE);

				// How much data we received (does not include protocol bytes)
				*bufferSizeUsed = dataIdx;

				// Make sure that a valid SOM was received and,
				// Make sure that the response is a passthrough message if we expect it
				if ((result == CUBEOBC_ERROR_OK) &&
					((validRxWindow == FALSE) || (passthrough != endpoint->passthrough)))
				{
					result = CUBEOBC_ERROR_TCTLM_PROTOCOL;
				}

				// Make sure that the ID requested matches the response
				if ((result == CUBEOBC_ERROR_OK) && (tctlmId != masterEndpoint->id))
				{
					result = CUBEOBC_ERROR_TCTLM_ID;
				}

				if ((result == CUBEOBC_ERROR_OK) && (nack == TRUE))
				{
					result = nackToErrorCode(data[0u]);
				}
			}
		}
		break;

		case TYPEDEF__COMMS_ENDPOINT_I2C:
		{
			// TODO
			result = CUBEOBC_ERROR_TODO;
		}
		break;

		case TYPEDEF__COMMS_ENDPOINT_MAX:
		default:
		{
			result = CUBEOBC_ERROR_PARAM;
		}
		break;
	}

	return result;
}

/*** end of file ***/
