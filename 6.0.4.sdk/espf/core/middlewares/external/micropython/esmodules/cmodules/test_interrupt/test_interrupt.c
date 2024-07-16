// Include MicroPython API.
#include "py/runtime.h"

STATIC mp_obj_t test_interrupt_Send(mp_obj_t a_obj, mp_obj_t result_obj) {
    // Extract the ints from the micropython input objects.
    mp_buffer_info_t bufinfo;
    mp_buffer_info_t resp_bufinfo;

    mp_get_buffer(a_obj, &bufinfo, MP_BUFFER_RW);
    mp_get_buffer(result_obj, &resp_bufinfo, MP_BUFFER_RW);

    eCPDispatchResult_t res =upy_fp_gw_send_cmd(bufinfo.buf, bufinfo.len, resp_bufinfo.buf, resp_bufinfo.len);

    // Calculate the addition and convert to MicroPython object.
    return mp_obj_new_int(res);
}
// Define a Python reference to the function above.
STATIC MP_DEFINE_CONST_FUN_OBJ_2(test_interrupt_Send_obj, test_interrupt_Send);

// Define all properties of the module.
// Table entries are key/value pairs of the attribute name (a string)
// and the MicroPython object reference.
// All identifiers and strings are written as MP_QSTR_xxx and will be
// optimized to word-sized integers by the build system (interned strings).
STATIC const mp_rom_map_elem_t test_interrupt_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_test_interrupt) },
    { MP_ROM_QSTR(MP_QSTR_SendFpGwCommand), MP_ROM_PTR(&test_interrupt_Send_obj) },
};
STATIC MP_DEFINE_CONST_DICT(test_interrupt_module_globals, test_interrupt_module_globals_table);


// Define module object.
const mp_obj_module_t test_interrupt_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&test_interrupt_module_globals,
};

// Register the module to make it available in Python.
MP_REGISTER_MODULE(MP_QSTR_test_interrupt, test_interrupt_user_cmodule);
