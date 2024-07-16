// Include MicroPython API.
#include "../../../../../../services/upython/inc/upy_fp_gw.h"

#include "py/runtime.h"

/**
 * \brief This is the interface function to be used from micropython to send FP
 * commands to the obc module
 *
 * \param request_obj Object containing a buffer with formatted FP command as a
 * request to the ESSA stack. \param result_obj Object containing the result
 * buffer after calling the requested FP command \param op_status Object
 * containing status of the command. \return result of the command execution.
 */
STATIC mp_obj_t
obc_fp_gw_Send(mp_obj_t a_obj, mp_obj_t result_obj)
{
    // Extract the ints from the micropython input objects.
    mp_buffer_info_t bufinfo;
    mp_buffer_info_t resp_bufinfo;
    uint8_t     Status;

    mp_get_buffer(a_obj, &bufinfo, MP_BUFFER_RW);
    mp_get_buffer(result_obj, &resp_bufinfo, MP_BUFFER_RW);


    eCPDispatchResult_t res = upy_fp_gw_send_cmd(
        bufinfo.buf, bufinfo.len, resp_bufinfo.buf, resp_bufinfo.len, &Status);

    mp_obj_t returnValues[2];
    returnValues[0] = mp_obj_new_int(res);
    returnValues[1] = mp_obj_new_int(Status);

    return mp_obj_new_tuple(2, returnValues);
}
// Define a Python reference to the function above.
STATIC MP_DEFINE_CONST_FUN_OBJ_2(obc_fp_gw_Send_obj, obc_fp_gw_Send);

// Define all properties of the module.
// Table entries are key/value pairs of the attribute name (a string)
// and the MicroPython object reference.
// All identifiers and strings are written as MP_QSTR_xxx and will be
// optimized to word-sized integers by the build system (interned strings).
STATIC const mp_rom_map_elem_t obc_fp_gw_module_globals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___name__),         MP_ROM_QSTR(MP_QSTR_obc_fp_gw) },
    { MP_ROM_QSTR(MP_QSTR_SendFpGwCommand), MP_ROM_PTR(&obc_fp_gw_Send_obj)},
};
STATIC MP_DEFINE_CONST_DICT(obc_fp_gw_module_globals,
                            obc_fp_gw_module_globals_table);

// Define module object.
const mp_obj_module_t obc_fp_gw_user_cmodule = {
    .base    = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&obc_fp_gw_module_globals,
};

// Register the module to make it available in Python.
MP_REGISTER_MODULE(MP_QSTR_obc_fp_gw, obc_fp_gw_user_cmodule);
