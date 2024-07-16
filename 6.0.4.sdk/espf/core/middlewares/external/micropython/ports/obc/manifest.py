#needed libraries
module("struct.py", base_path="$(MPY_DIR)/lib/micropython-lib/python-stdlib/struct")

#Endurosat specific modules
module("SerDesHelpers.py", base_path="$(MPY_DIR)/esmodules/pymodules/OBC/v3.4/gen")
module("OBCClientApp.py", base_path="$(MPY_DIR)/esmodules/pymodules/OBC/v3.4/gen")
module("data_cacheClientApp.py", base_path="$(MPY_DIR)/esmodules/pymodules/data_cache/v0.1/gen")
module("upy_helper.py", base_path="$(MPY_DIR)/esmodules/pymodules/upy_helper")


