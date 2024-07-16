# ********************************************************************************************
# * @file OBCClientApp.py
# * @brief MAC FP client Python implementation generator
# ********************************************************************************************
# * @version           interface OBC v3.4
# *
# * @copyright         (C) Copyright EnduroSat
# *
# *                    Contents and presentations are protected world-wide.
# *                    Any kind of using, copying etc. is prohibited without prior permission.
# *                    All rights - incl. industrial property rights - are reserved.
# *
# *-------------------------------------------------------------------------------------------
# * GENERATOR: org.endurosat.generators.macchiato.binders.Gen_Py v1.11
# *-------------------------------------------------------------------------------------------
# * !!! Please note that this code is fully GENERATED and shall not be manually modified as
# * all changes will be overwritten !!!
# ********************************************************************************************

from .SerDesHelpers import SerDesHelpers

class FP_API_OBC:
    def __init__(self, rawSerDesSupport : bool = False):
        self.const_OBC_PROTOCOL_ID = 14
        self.rawSerDesSupport = rawSerDesSupport
        self.versionMajor=3
        self.versionMinor=4


        #
        # Response parsers map
        #
        self.responseParsersDict = {}
        self.responseParsersDict[14] = self.resp_getGpOutputStates
        self.responseParsersDict[15] = self.resp_setGpOutputState
        self.responseParsersDict[18] = self.resp_getI2CPullUpsState
        self.responseParsersDict[19] = self.resp_setI2CPullUpsState
        self.responseParsersDict[24] = self.resp_get_uptime
        self.responseParsersDict[42] = self.resp_getResetCounters
        self.responseParsersDict[43] = self.resp_clearResetCounter
        self.responseParsersDict[54] = self.resp_triggerResetInMode
        self.responseParsersDict[64] = self.resp_set_device_mac_address
        self.responseParsersDict[65] = self.resp_get_device_mac_address

    class enum_HwResult:
        HWRESULT_SUCCESS = 0
        HWRESULT_ERROR = 1
        HWRESULT_DISABLED = 255
    
        ValuesDict = {
            HWRESULT_SUCCESS : 'HWRESULT_SUCCESS', 
            HWRESULT_ERROR : 'HWRESULT_ERROR', 
            HWRESULT_DISABLED : 'HWRESULT_DISABLED'
        }
    
        def __init__(self, value = 0):
            self.value = value
    
        def serialize(self):
            result = bytearray()
    
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.value)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_OBC.enum_HwResult()
    
            (resultInstance.value, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, pos)
    
            return (resultInstance, bytesProcessed)
    
        def getSymbolicName(self):
            return FP_API_OBC.enum_HwResult.ValuesDict[self.value]
    
        @staticmethod
        def getValueBySymbolicName(literalName):
            for key, value in FP_API_OBC.enum_HwResult.ValuesDict.items():
                if literalName == value:
                    return key
    
        @staticmethod
        def getSize():
            return 1
    
    class enum_StandardResult:
        STANDARDRESULT_SUCCESS = 0
        STANDARDRESULT_ERROR = 1
        STANDARDRESULT_INVALID_ARGS = 2
        STANDARDRESULT_NOT_SUPPORTED = 3
    
        ValuesDict = {
            STANDARDRESULT_SUCCESS : 'STANDARDRESULT_SUCCESS', 
            STANDARDRESULT_ERROR : 'STANDARDRESULT_ERROR', 
            STANDARDRESULT_INVALID_ARGS : 'STANDARDRESULT_INVALID_ARGS', 
            STANDARDRESULT_NOT_SUPPORTED : 'STANDARDRESULT_NOT_SUPPORTED'
        }
    
        def __init__(self, value = 0):
            self.value = value
    
        def serialize(self):
            result = bytearray()
    
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.value)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_OBC.enum_StandardResult()
    
            (resultInstance.value, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, pos)
    
            return (resultInstance, bytesProcessed)
    
        def getSymbolicName(self):
            return FP_API_OBC.enum_StandardResult.ValuesDict[self.value]
    
        @staticmethod
        def getValueBySymbolicName(literalName):
            for key, value in FP_API_OBC.enum_StandardResult.ValuesDict.items():
                if literalName == value:
                    return key
    
        @staticmethod
        def getSize():
            return 1
    
    class enum_ApplicationMode:
        APPLICATIONMODE_APPLICATION = 0
        APPLICATIONMODE_BOOTLOADER = 1
    
        ValuesDict = {
            APPLICATIONMODE_APPLICATION : 'APPLICATIONMODE_APPLICATION', 
            APPLICATIONMODE_BOOTLOADER : 'APPLICATIONMODE_BOOTLOADER'
        }
    
        def __init__(self, value = 0):
            self.value = value
    
        def serialize(self):
            result = bytearray()
    
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.value)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_OBC.enum_ApplicationMode()
    
            (resultInstance.value, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, pos)
    
            return (resultInstance, bytesProcessed)
    
        def getSymbolicName(self):
            return FP_API_OBC.enum_ApplicationMode.ValuesDict[self.value]
    
        @staticmethod
        def getValueBySymbolicName(literalName):
            for key, value in FP_API_OBC.enum_ApplicationMode.ValuesDict.items():
                if literalName == value:
                    return key
    
        @staticmethod
        def getSize():
            return 1
    
    class struct_GpioStatus:
        def __init__(self, uint8__gpioStatusBitField = 0):
            self.uint8__gpioStatusBitField = uint8__gpioStatusBitField
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.uint8__gpioStatusBitField)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_OBC.struct_GpioStatus()
    
            currentPos = pos
            
            (resultInstance.uint8__gpioStatusBitField, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 1
    
    class struct_I2CPullUpsState:
        def __init__(self, bool__SystemBus_4K7 = False, bool__SystemBus_10K = False, bool__PayloadBus_4K7 = False, bool__PayloadBus_10K = False):
            self.bool__SystemBus_4K7 = bool__SystemBus_4K7
            self.bool__SystemBus_10K = bool__SystemBus_10K
            self.bool__PayloadBus_4K7 = bool__PayloadBus_4K7
            self.bool__PayloadBus_10K = bool__PayloadBus_10K
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.bool__SystemBus_4K7)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.bool__SystemBus_10K)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.bool__PayloadBus_4K7)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.bool__PayloadBus_10K)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_OBC.struct_I2CPullUpsState()
    
            currentPos = pos
            
            (resultInstance.bool__SystemBus_4K7, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.bool__SystemBus_10K, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.bool__PayloadBus_4K7, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.bool__PayloadBus_10K, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 4
    
    class struct_ResetCountersInfo:
        def __init__(self, uint32__WWD = 0, uint32__IWD = 0, uint32__LPR = 0, uint32__POR = 0, uint32__RstPin = 0, uint32__BOR = 0, uint32__HardFault = 0, uint32__MemFault = 0, uint32__BusFault = 0, uint32__UsageFault = 0):
            self.uint32__WWD = uint32__WWD
            self.uint32__IWD = uint32__IWD
            self.uint32__LPR = uint32__LPR
            self.uint32__POR = uint32__POR
            self.uint32__RstPin = uint32__RstPin
            self.uint32__BOR = uint32__BOR
            self.uint32__HardFault = uint32__HardFault
            self.uint32__MemFault = uint32__MemFault
            self.uint32__BusFault = uint32__BusFault
            self.uint32__UsageFault = uint32__UsageFault
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__WWD)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__IWD)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__LPR)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__POR)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__RstPin)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__BOR)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__HardFault)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__MemFault)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__BusFault)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__UsageFault)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_OBC.struct_ResetCountersInfo()
    
            currentPos = pos
            
            (resultInstance.uint32__WWD, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__IWD, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__LPR, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__POR, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__RstPin, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__BOR, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__HardFault, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__MemFault, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__BusFault, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__UsageFault, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 40
    
    class enum_ResetCntrId:
        RESETCNTRID_WWD = 0
        RESETCNTRID_IWD = 1
        RESETCNTRID_LPR = 2
        RESETCNTRID_POR = 3
        RESETCNTRID_RSTPIN = 4
        RESETCNTRID_BOR = 5
        RESETCNTRID_HARDFAULT = 6
        RESETCNTRID_MEMFAULT = 7
        RESETCNTRID_BUSFAULT = 8
        RESETCNTRID_USAGEFAULT = 9
        RESETCNTRID_ALL = 10
    
        ValuesDict = {
            RESETCNTRID_WWD : 'RESETCNTRID_WWD', 
            RESETCNTRID_IWD : 'RESETCNTRID_IWD', 
            RESETCNTRID_LPR : 'RESETCNTRID_LPR', 
            RESETCNTRID_POR : 'RESETCNTRID_POR', 
            RESETCNTRID_RSTPIN : 'RESETCNTRID_RSTPIN', 
            RESETCNTRID_BOR : 'RESETCNTRID_BOR', 
            RESETCNTRID_HARDFAULT : 'RESETCNTRID_HARDFAULT', 
            RESETCNTRID_MEMFAULT : 'RESETCNTRID_MEMFAULT', 
            RESETCNTRID_BUSFAULT : 'RESETCNTRID_BUSFAULT', 
            RESETCNTRID_USAGEFAULT : 'RESETCNTRID_USAGEFAULT', 
            RESETCNTRID_ALL : 'RESETCNTRID_ALL'
        }
    
        def __init__(self, value = 0):
            self.value = value
    
        def serialize(self):
            result = bytearray()
    
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.value)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_OBC.enum_ResetCntrId()
    
            (resultInstance.value, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, pos)
    
            return (resultInstance, bytesProcessed)
    
        def getSymbolicName(self):
            return FP_API_OBC.enum_ResetCntrId.ValuesDict[self.value]
    
        @staticmethod
        def getValueBySymbolicName(literalName):
            for key, value in FP_API_OBC.enum_ResetCntrId.ValuesDict.items():
                if literalName == value:
                    return key
    
        @staticmethod
        def getSize():
            return 1
    
    class enum_PanelId:
        PANELID_X_P = 0
        PANELID_Y_P = 1
        PANELID_Z_P = 2
        PANELID_X_M = 3
        PANELID_Y_M = 4
        PANELID_Z_M = 5
    
        ValuesDict = {
            PANELID_X_P : 'PANELID_X_P', 
            PANELID_Y_P : 'PANELID_Y_P', 
            PANELID_Z_P : 'PANELID_Z_P', 
            PANELID_X_M : 'PANELID_X_M', 
            PANELID_Y_M : 'PANELID_Y_M', 
            PANELID_Z_M : 'PANELID_Z_M'
        }
    
        def __init__(self, value = 0):
            self.value = value
    
        def serialize(self):
            result = bytearray()
    
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.value)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_OBC.enum_PanelId()
    
            (resultInstance.value, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, pos)
    
            return (resultInstance, bytesProcessed)
    
        def getSymbolicName(self):
            return FP_API_OBC.enum_PanelId.ValuesDict[self.value]
    
        @staticmethod
        def getValueBySymbolicName(literalName):
            for key, value in FP_API_OBC.enum_PanelId.ValuesDict.items():
                if literalName == value:
                    return key
    
        @staticmethod
        def getSize():
            return 1
    
    class struct_RegData:
        def __init__(self, e__HwResult__status = 0, uint16__data = 0):
            self.e__HwResult__status = e__HwResult__status
            self.uint16__data = uint16__data
    
        def serialize(self):
            result = bytearray()
    
            
            result += FP_API_OBC.enum_HwResult(self.e__HwResult__status).serialize()
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__data)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_OBC.struct_RegData()
    
            currentPos = pos
            
            (resultInstance.e__HwResult__status, bytesProcessed) = FP_API_OBC.enum_HwResult.deserialize(data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__data, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 3
    
    class struct_SensorInUseData:
        def __init__(self, bool__isSensorValid = False, uint8__usersCount = 0):
            self.bool__isSensorValid = bool__isSensorValid
            self.uint8__usersCount = uint8__usersCount
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.bool__isSensorValid)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.uint8__usersCount)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_OBC.struct_SensorInUseData()
    
            currentPos = pos
            
            (resultInstance.bool__isSensorValid, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint8__usersCount, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 2
    
    class enum_AccelId:
        ACCELID_ONE = 0
        ACCELID_TWO = 1
    
        ValuesDict = {
            ACCELID_ONE : 'ACCELID_ONE', 
            ACCELID_TWO : 'ACCELID_TWO'
        }
    
        def __init__(self, value = 0):
            self.value = value
    
        def serialize(self):
            result = bytearray()
    
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.value)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_OBC.enum_AccelId()
    
            (resultInstance.value, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, pos)
    
            return (resultInstance, bytesProcessed)
    
        def getSymbolicName(self):
            return FP_API_OBC.enum_AccelId.ValuesDict[self.value]
    
        @staticmethod
        def getValueBySymbolicName(literalName):
            for key, value in FP_API_OBC.enum_AccelId.ValuesDict.items():
                if literalName == value:
                    return key
    
        @staticmethod
        def getSize():
            return 1
    
    class enum_MagnetometerId:
        MAGNETOMETERID_LOW = 0
        MAGNETOMETERID_HIGH = 1
    
        ValuesDict = {
            MAGNETOMETERID_LOW : 'MAGNETOMETERID_LOW', 
            MAGNETOMETERID_HIGH : 'MAGNETOMETERID_HIGH'
        }
    
        def __init__(self, value = 0):
            self.value = value
    
        def serialize(self):
            result = bytearray()
    
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.value)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_OBC.enum_MagnetometerId()
    
            (resultInstance.value, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, pos)
    
            return (resultInstance, bytesProcessed)
    
        def getSymbolicName(self):
            return FP_API_OBC.enum_MagnetometerId.ValuesDict[self.value]
    
        @staticmethod
        def getValueBySymbolicName(literalName):
            for key, value in FP_API_OBC.enum_MagnetometerId.ValuesDict.items():
                if literalName == value:
                    return key
    
        @staticmethod
        def getSize():
            return 1
    
    class enum_SafeBool:
        SAFEBOOL_FALSE = 0
        SAFEBOOL_TRUE = 255
    
        ValuesDict = {
            SAFEBOOL_FALSE : 'SAFEBOOL_FALSE', 
            SAFEBOOL_TRUE : 'SAFEBOOL_TRUE'
        }
    
        def __init__(self, value = 0):
            self.value = value
    
        def serialize(self):
            result = bytearray()
    
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.value)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_OBC.enum_SafeBool()
    
            (resultInstance.value, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, pos)
    
            return (resultInstance, bytesProcessed)
    
        def getSymbolicName(self):
            return FP_API_OBC.enum_SafeBool.ValuesDict[self.value]
    
        @staticmethod
        def getValueBySymbolicName(literalName):
            for key, value in FP_API_OBC.enum_SafeBool.ValuesDict.items():
                if literalName == value:
                    return key
    
        @staticmethod
        def getSize():
            return 1
    

    ############################################################################################################
    """
    Request function for FIDL method: getGpOutputStates
        - function ID: 0000000E
        - description: Provides the states of all OBC general-purpose outputs
    """
    def req_getGpOutputStates(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_OBC_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x0000000E
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x0000000E, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: getGpOutputStates
        - function ID: 0000000E
        - description: Provides the states of all OBC general-purpose outputs
    """
    def resp_getGpOutputStates(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            fpHeaderInstance, headerBytesProcessed = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_OBC_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x0000000E):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        field, bytesProcessed = FP_API_OBC.struct_GpioStatus.deserialize(data, currentPos)
        responseInstance["s__data"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: setGpOutputState
        - function ID: 0000000F
        - description: Triggers a change in the specified output pin state
    """
    def req_setGpOutputState(self, uint8__pinId, bool__value):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_OBC_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x0000000F
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += SerDesHelpers.serdesType_basic.serialize("uint8", uint8__pinId)
        requestBytes += SerDesHelpers.serdesType_basic.serialize("uint8", bool__value)
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x0000000F, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: setGpOutputState
        - function ID: 0000000F
        - description: Triggers a change in the specified output pin state
    """
    def resp_setGpOutputState(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            fpHeaderInstance, headerBytesProcessed = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_OBC_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x0000000F):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        field, bytesProcessed = FP_API_OBC.enum_HwResult.deserialize(data, currentPos)
        responseInstance["e__HwResult__opResult"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: getI2CPullUpsState
        - function ID: 00000012
        - description: Obtains information on state of the I2C Pull-Up resistors for system and
                              customer payload buses
    """
    def req_getI2CPullUpsState(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_OBC_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000012
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000012, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: getI2CPullUpsState
        - function ID: 00000012
        - description: Obtains information on state of the I2C Pull-Up resistors for system and
                              customer payload buses
    """
    def resp_getI2CPullUpsState(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            fpHeaderInstance, headerBytesProcessed = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_OBC_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000012):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        field, bytesProcessed = FP_API_OBC.struct_I2CPullUpsState.deserialize(data, currentPos)
        responseInstance["s__nvm_pullupsState"] = field
        currentPos += bytesProcessed
    
        field, bytesProcessed = FP_API_OBC.struct_I2CPullUpsState.deserialize(data, currentPos)
        responseInstance["s__io_pullupsState"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: setI2CPullUpsState
        - function ID: 00000013
        - description: Reconfigures the state of the I2C Pull-Up resistors for system and
                              customer payload buses
    """
    def req_setI2CPullUpsState(self, s__pullupsState):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_OBC_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000013
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__pullupsState.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000013, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: setI2CPullUpsState
        - function ID: 00000013
        - description: Reconfigures the state of the I2C Pull-Up resistors for system and
                              customer payload buses
    """
    def resp_setI2CPullUpsState(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            fpHeaderInstance, headerBytesProcessed = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_OBC_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000013):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        field, bytesProcessed = FP_API_OBC.struct_I2CPullUpsState.deserialize(data, currentPos)
        responseInstance["s__pullupsIoState"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_uptime
        - function ID: 00000018
        - description: Obtains the up time of the OBC since last power on.
    """
    def req_get_uptime(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_OBC_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000018
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000018, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_uptime
        - function ID: 00000018
        - description: Obtains the up time of the OBC since last power on.
    """
    def resp_get_uptime(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            fpHeaderInstance, headerBytesProcessed = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_OBC_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000018):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        field, bytesProcessed = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
        responseInstance["uint32__uptime"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: getResetCounters
        - function ID: 0000002A
        - description: Obtains the current values of the MCU reset counters
    """
    def req_getResetCounters(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_OBC_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x0000002A
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x0000002A, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: getResetCounters
        - function ID: 0000002A
        - description: Obtains the current values of the MCU reset counters
    """
    def resp_getResetCounters(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            fpHeaderInstance, headerBytesProcessed = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_OBC_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x0000002A):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        field, bytesProcessed = FP_API_OBC.struct_ResetCountersInfo.deserialize(data, currentPos)
        responseInstance["s__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: clearResetCounter
        - function ID: 0000002B
        - description: Clears a given MCU reset counter
    """
    def req_clearResetCounter(self, e__ResetCntrId__id):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_OBC_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x0000002B
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += FP_API_OBC.enum_ResetCntrId(e__ResetCntrId__id).serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x0000002B, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: clearResetCounter
        - function ID: 0000002B
        - description: Clears a given MCU reset counter
    """
    def resp_clearResetCounter(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            fpHeaderInstance, headerBytesProcessed = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_OBC_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x0000002B):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        field, bytesProcessed = FP_API_OBC.enum_StandardResult.deserialize(data, currentPos)
        responseInstance["e__StandardResult__opResult"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: triggerResetInMode
        - function ID: 00000036
        - description: Triggers a reset of the OBC starting with the specified APP mode
    """
    def req_triggerResetInMode(self, e__ApplicationMode__startMode):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_OBC_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000036
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += FP_API_OBC.enum_ApplicationMode(e__ApplicationMode__startMode).serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000036, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: triggerResetInMode
        - function ID: 00000036
        - description: Triggers a reset of the OBC starting with the specified APP mode
    """
    def resp_triggerResetInMode(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            fpHeaderInstance, headerBytesProcessed = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_OBC_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000036):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        field, bytesProcessed = FP_API_OBC.enum_StandardResult.deserialize(data, currentPos)
        responseInstance["e__StandardResult__opResult"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_device_mac_address
        - function ID: 00000040
        - description: Update the MAC addres in the mac address book of the OBC NVM.
    """
    def req_set_device_mac_address(self, uint8__new_mac_address, uint8__device_id):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_OBC_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000040
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += SerDesHelpers.serdesType_basic.serialize("uint8", uint8__new_mac_address)
        requestBytes += SerDesHelpers.serdesType_basic.serialize("uint8", uint8__device_id)
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000040, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_device_mac_address
        - function ID: 00000040
        - description: Update the MAC addres in the mac address book of the OBC NVM.
    """
    def resp_set_device_mac_address(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            fpHeaderInstance, headerBytesProcessed = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_OBC_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000040):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        field, bytesProcessed = FP_API_OBC.enum_StandardResult.deserialize(data, currentPos)
        responseInstance["e__StandardResult__opResult"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_device_mac_address
        - function ID: 00000041
        - description: Read the MAC addres in the mac address book of the OBC NVM.
    """
    def req_get_device_mac_address(self, uint8__device_id):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_OBC_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000041
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += SerDesHelpers.serdesType_basic.serialize("uint8", uint8__device_id)
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000041, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_device_mac_address
        - function ID: 00000041
        - description: Read the MAC addres in the mac address book of the OBC NVM.
    """
    def resp_get_device_mac_address(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            fpHeaderInstance, headerBytesProcessed = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_OBC_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000041):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        field, bytesProcessed = SerDesHelpers.serdesType_basic.deserialize("uint8", data, currentPos)
        responseInstance["uint8__mac_address"] = field
        currentPos += bytesProcessed
    
        field, bytesProcessed = FP_API_OBC.enum_StandardResult.deserialize(data, currentPos)
        responseInstance["e__StandardResult__opResult"] = field
        currentPos += bytesProcessed
    
        return responseInstance


    ############################################################################################################
    """
    Deserializes the provided bytearray and returns a dictionary of parsed values for the response;
    functionId parameter shall be supplied if the class is used in rawSerDesSupport mode, otherwise
    it is extracted from the FP header
    """
    def resp_parse(self, respBytes, functionId : int = 0):
        if not self.rawSerDesSupport:
            # try to parse FunctionProtocol header
            (fpHeaderInstance, bytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(respBytes, 0)
            funcId = fpHeaderInstance.u32FuncId

            if fpHeaderInstance.u16ProtoId != self.const_OBC_PROTOCOL_ID:
                raise Exception("Unsupported protocol ID", fpHeaderInstance.u16ProtoId)
        else:
            funcId = functionId

        if funcId in self.responseParsersDict:
            respParserFunc = self.responseParsersDict[funcId]
            return respParserFunc(respBytes) if respParserFunc is not None else None
        else:
            raise Exception('Unsupported function id', hex(funcId))
    ############################################################################################################
    """
    Returns the Protocol version as a string vM.m
    """
    def get_version(self):
        return f'v{self.versionMajor}.{self.versionMinor}'
    ############################################################################################################

