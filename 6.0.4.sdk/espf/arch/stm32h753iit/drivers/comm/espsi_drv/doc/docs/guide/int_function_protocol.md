--8<-- "includes/abbreviations.md"

# Function Protocol

EnduroSat's Function Protocol, is designed to be sent as payload withint the MAC Frames and it is used to send predefined messages between devices in the same network without defining the interfaces between them multiple times in different places.

The FP interfaces code is generated automatically with Endurosat's tool Macchiatto. The typical folder structure for an interface generated in C is the following:

| Folder                                    | Description |
|-------------------------------------------|-------------|
| `<Protocol>/<version>/FP_common`          | Common files for any function protocol |
| `<Protocol>/<version>/<Protocol>_client`  | Client interface implementation |
| `<Protocol>/<version>/<Protocol>_server`  | Server interface implementation |

For this example, we have placed the code for the PingPong protocol in `Core`.

## Initialization

The initialization of the Protocol must be done in two steps:

- Add the descriptor hanlders to the list `FUNCTION_PROTOCOL_HANDLERS_LIST` in `ESPS_StackConfig.h`.
- Call the initialize function. See [ESPS I Initialization](int_esps_i_stack.md#initialization) or [Inter-Module Only ESPS I Initialization](../im_only/im_esps_i_stack.md#initialization) configuration.

The descriptor handlers return the ID of the function protocol and the callback function that process the data of a request.

## Application

To send a request, we must call the function from the client header as we have done in `application.c`:

```c
            // Now send a ping pong request
            eRet_code = PingPong_PingReq(&ePingPong_request_context, &sData);
```

This function is defined in `Core/PingPong/v0.1/FP_common/PingPong_client/FP_PingPongProtocolClient.c`.

Also, whenever we receive a request from another device, the function `PingPong_PingRequestHandlerImpl()` will be called. As mentioned before, the code for this protocols is generated automatically. But it can be seen in the request handler a comment indicating where you can add some code to be executed every time a PingPong message request is received from another device. This is defined in `Core/PingPong/v0.1/FP_common/PingPong_server/FP_PingPongProtocolServer.c` with the tags `USER_VAR_SECTION_START` and `USER_CODE_SECTION_START`:

```c
// @START@ Request handler for method PingPong::Ping (ID = 0x00000001)
static void PingPong_PingRequestHandlerImpl(ReqContext_t *pReqCtx,
            const PingPongPingRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    PINGPONG_sPing_t sOpResult;

    // @USER_VAR_SECTION_START@PingPong::Ping@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@PingPong::Ping@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@PingPong::Ping@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@PingPong::Ping@

        respResult = PingPong_PingResp(
                        &respCtx,
                        &sOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_PINGPONG, PINGPONG_PING_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method PingPong::Ping (ID = 0x00000001)
```

Whenever a MAC Frame is received using the Function Protocol, the ESPS I will verify that the ID matches one of the list of the descriptors. Then, it will call the given function in that descriptor to process the data of the request.
