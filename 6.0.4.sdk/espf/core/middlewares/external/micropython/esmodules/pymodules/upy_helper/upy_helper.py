import obc_fp_gw

# this enumerator is partially defined here. The definition normally comes from ES_TL_Layer.h 
class SESTL_StatusFrame_nTLReceiverError:
    EESTL_SFERR_SUCCESS = 0 
    EESTL_SFERR_RECEIVE_TIMEOUT = 6  
    EESTL_SFERR_UNKNOWN = 111        

class eCPDispatchResult_t:
    ECPDISPATCHRESULT_SIMPLERESULT_OK = 0
    ECPDISPATCHRESULT_RESULT_OK = 1
    ECPDISPATCHRESULT_RESULT_POSTPONED = 2
    ECPDISPATCHRESULT_RESULT_BY_CHUNKS = 3
    ECPDISPATCHRESULT_ERROR = 4
            
class exec_command_result:
    FP_COMMAND_SUCCESS = 0
    FP_COMMAND_TIMED_OUT = 1
    FP_COMMAND_ERROR = 2
    
        
def execute_command(api, cmd, buflen):
    resp = bytearray(buflen)
    status = exec_command_result.FP_COMMAND_ERROR
    
    res,dispatch_result = obc_fp_gw.SendFpGwCommand(cmd, resp)
    
    if eCPDispatchResult_t.ECPDISPATCHRESULT_RESULT_OK == res:
        if SESTL_StatusFrame_nTLReceiverError.EESTL_SFERR_SUCCESS == dispatch_result:
            resp = api.resp_parse(resp)
            status = exec_command_result.FP_COMMAND_SUCCESS
        elif SESTL_StatusFrame_nTLReceiverError.EESTL_SFERR_RECEIVE_TIMEOUT == dispatch_result:
            status = exec_command_result.FP_COMMAND_TIMED_OUT

    return status, resp 

