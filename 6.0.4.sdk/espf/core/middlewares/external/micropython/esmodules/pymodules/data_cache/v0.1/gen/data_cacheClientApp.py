# ********************************************************************************************
# * @file data_cacheClientApp.py
# * @brief MAC FP client Python implementation generator
# ********************************************************************************************
# * @version           interface data_cache v0.1
# *
# * @copyright         (C) Copyright EnduroSat
# *
# *                    Contents and presentations are protected world-wide.
# *                    Any kind of using, copying etc. is prohibited without prior permission.
# *                    All rights - incl. industrial property rights - are reserved.
# *
# *-------------------------------------------------------------------------------------------
# * GENERATOR: org.endurosat.generators.macchiato.binders.Gen_Py v1.9
# *-------------------------------------------------------------------------------------------
# * !!! Please note that this code is fully GENERATED and shall not be manually modified as
# * all changes will be overwritten !!!
# ********************************************************************************************

import re
import binascii
from struct import *
from SerDesHelpers import *

class FP_API_DATA_CACHE:
    def __init__(self, rawSerDesSupport : bool = False):
        self.const_DATA_CACHE_PROTOCOL_ID = 136
        self.rawSerDesSupport = rawSerDesSupport
        self.versionMajor=0
        self.versionMinor=1


        #
        # Response parsers map
        #
        self.responseParsersDict = {}
        self.responseParsersDict[0] = self.resp_get_OBC_0_Data
        self.responseParsersDict[1] = self.resp_set_OBC_0_Data
        self.responseParsersDict[2] = self.resp_get_ADCS_0_Data
        self.responseParsersDict[3] = self.resp_set_ADCS_0_Data
        self.responseParsersDict[4] = self.resp_get_ADCS_1_Data
        self.responseParsersDict[5] = self.resp_set_ADCS_1_Data
        self.responseParsersDict[6] = self.resp_get_ADCS_2_Data
        self.responseParsersDict[7] = self.resp_set_ADCS_2_Data
        self.responseParsersDict[8] = self.resp_get_EPS_0_Data
        self.responseParsersDict[9] = self.resp_set_EPS_0_Data
        self.responseParsersDict[10] = self.resp_get_SSP_0_Data
        self.responseParsersDict[11] = self.resp_set_SSP_0_Data
        self.responseParsersDict[12] = self.resp_get_SSP_1_Data
        self.responseParsersDict[13] = self.resp_set_SSP_1_Data
        self.responseParsersDict[14] = self.resp_get_SSP_2_Data
        self.responseParsersDict[15] = self.resp_set_SSP_2_Data
        self.responseParsersDict[16] = self.resp_get_AOCS_CNTRL_TLM_Data
        self.responseParsersDict[17] = self.resp_set_AOCS_CNTRL_TLM_Data
        self.responseParsersDict[18] = self.resp_get_EPS_1_Data
        self.responseParsersDict[19] = self.resp_set_EPS_1_Data
        self.responseParsersDict[20] = self.resp_get_EPS_2_Data
        self.responseParsersDict[21] = self.resp_set_EPS_2_Data
        self.responseParsersDict[22] = self.resp_get_EPS_3_Data
        self.responseParsersDict[23] = self.resp_set_EPS_3_Data
        self.responseParsersDict[24] = self.resp_get_EPS_4_Data
        self.responseParsersDict[25] = self.resp_set_EPS_4_Data
        self.responseParsersDict[26] = self.resp_get_EPS_5_Data
        self.responseParsersDict[27] = self.resp_set_EPS_5_Data
        self.responseParsersDict[28] = self.resp_get_EPS_6_Data
        self.responseParsersDict[29] = self.resp_set_EPS_6_Data
        self.responseParsersDict[30] = self.resp_get_OS_Task_Data
        self.responseParsersDict[31] = self.resp_set_OS_Task_Data
        self.responseParsersDict[32] = self.resp_get_SSP_3_Data
        self.responseParsersDict[33] = self.resp_set_SSP_3_Data
        self.responseParsersDict[34] = self.resp_get_ConOpsFlags_Data
        self.responseParsersDict[35] = self.resp_set_ConOpsFlags_Data
        self.responseParsersDict[36] = self.resp_get_AOCS_CNTRL_SYS_STATE_Data
        self.responseParsersDict[37] = self.resp_set_AOCS_CNTRL_SYS_STATE_Data

    class struct_AOCS_CNTRL_TLM:
        def __init__(self, uint16__adcsErrFlags = 0, int32__estAngRateNorm = 0, a__int32__3__estAngRateVec = [], a__int32__3__estAttAngles = [], a__int16__3__measWheelSpeed = []):
            self.uint16__adcsErrFlags = uint16__adcsErrFlags
            self.int32__estAngRateNorm = int32__estAngRateNorm
            self.a__int32__3__estAngRateVec = a__int32__3__estAngRateVec
            self.a__int32__3__estAttAngles = a__int32__3__estAttAngles
            self.a__int16__3__measWheelSpeed = a__int16__3__measWheelSpeed
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__adcsErrFlags)
            
            result += SerDesHelpers.serdesType_basic.serialize("int32", self.int32__estAngRateNorm)
            actualLen = len(self.a__int32__3__estAngRateVec)
            if (actualLen < 3):
                self.a__int32__3__estAngRateVec = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int32__3__estAngRateVec, 3)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int32", self.a__int32__3__estAngRateVec)
            actualLen = len(self.a__int32__3__estAttAngles)
            if (actualLen < 3):
                self.a__int32__3__estAttAngles = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int32__3__estAttAngles, 3)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int32", self.a__int32__3__estAttAngles)
            actualLen = len(self.a__int16__3__measWheelSpeed)
            if (actualLen < 3):
                self.a__int16__3__measWheelSpeed = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__3__measWheelSpeed, 3)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__3__measWheelSpeed)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_AOCS_CNTRL_TLM()
    
            currentPos = pos
            
            (resultInstance.uint16__adcsErrFlags, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int32__estAngRateNorm, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int32__3__estAngRateVec, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int32", data, currentPos, 3)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int32__3__estAttAngles, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int32", data, currentPos, 3)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__3__measWheelSpeed, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 3)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 36
    
    class struct_EPS_0:
        def __init__(self, int64__battEnergy = 0, int64__battCharge = 0, int64__battChargeCapacity = 0, int64__battPercent = 0, int32__battVoltage = 0, int32__battCurrent = 0, int32__battTemperature = 0):
            self.int64__battEnergy = int64__battEnergy
            self.int64__battCharge = int64__battCharge
            self.int64__battChargeCapacity = int64__battChargeCapacity
            self.int64__battPercent = int64__battPercent
            self.int32__battVoltage = int32__battVoltage
            self.int32__battCurrent = int32__battCurrent
            self.int32__battTemperature = int32__battTemperature
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("int64", self.int64__battEnergy)
            
            result += SerDesHelpers.serdesType_basic.serialize("int64", self.int64__battCharge)
            
            result += SerDesHelpers.serdesType_basic.serialize("int64", self.int64__battChargeCapacity)
            
            result += SerDesHelpers.serdesType_basic.serialize("int64", self.int64__battPercent)
            
            result += SerDesHelpers.serdesType_basic.serialize("int32", self.int32__battVoltage)
            
            result += SerDesHelpers.serdesType_basic.serialize("int32", self.int32__battCurrent)
            
            result += SerDesHelpers.serdesType_basic.serialize("int32", self.int32__battTemperature)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_EPS_0()
    
            currentPos = pos
            
            (resultInstance.int64__battEnergy, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int64", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int64__battCharge, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int64", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int64__battChargeCapacity, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int64", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int64__battPercent, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int64", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int32__battVoltage, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int32__battCurrent, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int32__battTemperature, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int32", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 44
    
    class enum_DCDataStatus:
        DCDATASTATUS_NOT_INITIALIZED = 0
        DCDATASTATUS_OK = 1
        DCDATASTATUS_INIT = 2
        DCDATASTATUS_TOUT = 3
    
        ValuesDict = {
            DCDATASTATUS_NOT_INITIALIZED : 'DCDATASTATUS_NOT_INITIALIZED', 
            DCDATASTATUS_OK : 'DCDATASTATUS_OK', 
            DCDATASTATUS_INIT : 'DCDATASTATUS_INIT', 
            DCDATASTATUS_TOUT : 'DCDATASTATUS_TOUT'
        }
    
        def __init__(self, value = 0):
            self.value = value
    
        def serialize(self):
            result = bytearray()
    
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.value)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.enum_DCDataStatus()
    
            (resultInstance.value, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, pos)
    
            return (resultInstance, bytesProcessed)
    
        def getSymbolicName(self):
            return FP_API_DATA_CACHE.enum_DCDataStatus.ValuesDict[self.value]
    
        @staticmethod
        def getValueBySymbolicName(literalName):
            for key, value in FP_API_DATA_CACHE.enum_DCDataStatus.ValuesDict.items():
                if literalName == value:
                    return key
    
        @staticmethod
        def getSize():
            return 1
    
    class struct_EPS_2:
        def __init__(self, int16__VOLT_BRDSUP = 0, int16__TEMP_MCU = 0, int16__VIP_INPUT_Voltage = 0, int16__VIP_INPUT_Current = 0, int16__VIP_INPUT_Power = 0, uint16__STAT_CH_ON = 0, uint16__STAT_CH_OCF = 0, int16__VIP_Voltage_VD0 = 0, int16__VIP_Current_VD0 = 0, int16__VIP_Voltage_VD4 = 0, int16__VIP_Current_VD4 = 0, int16__VIP_Voltage_VD6 = 0, int16__VIP_Current_VD6 = 0, int16__VIP_Voltage_VD7 = 0, int16__VIP_Current_VD7 = 0, int16__VIP_Voltage_VD8 = 0, int16__VIP_Current_VD8 = 0, int16__VIP_Voltage_VD9 = 0, int16__VIP_Current_VD9 = 0, int16__VIP_Voltage_VD10 = 0, int16__VIP_Current_VD10 = 0, int16__VIP_Voltage_VD11 = 0, int16__VIP_Current_VD11 = 0):
            self.int16__VOLT_BRDSUP = int16__VOLT_BRDSUP
            self.int16__TEMP_MCU = int16__TEMP_MCU
            self.int16__VIP_INPUT_Voltage = int16__VIP_INPUT_Voltage
            self.int16__VIP_INPUT_Current = int16__VIP_INPUT_Current
            self.int16__VIP_INPUT_Power = int16__VIP_INPUT_Power
            self.uint16__STAT_CH_ON = uint16__STAT_CH_ON
            self.uint16__STAT_CH_OCF = uint16__STAT_CH_OCF
            self.int16__VIP_Voltage_VD0 = int16__VIP_Voltage_VD0
            self.int16__VIP_Current_VD0 = int16__VIP_Current_VD0
            self.int16__VIP_Voltage_VD4 = int16__VIP_Voltage_VD4
            self.int16__VIP_Current_VD4 = int16__VIP_Current_VD4
            self.int16__VIP_Voltage_VD6 = int16__VIP_Voltage_VD6
            self.int16__VIP_Current_VD6 = int16__VIP_Current_VD6
            self.int16__VIP_Voltage_VD7 = int16__VIP_Voltage_VD7
            self.int16__VIP_Current_VD7 = int16__VIP_Current_VD7
            self.int16__VIP_Voltage_VD8 = int16__VIP_Voltage_VD8
            self.int16__VIP_Current_VD8 = int16__VIP_Current_VD8
            self.int16__VIP_Voltage_VD9 = int16__VIP_Voltage_VD9
            self.int16__VIP_Current_VD9 = int16__VIP_Current_VD9
            self.int16__VIP_Voltage_VD10 = int16__VIP_Voltage_VD10
            self.int16__VIP_Current_VD10 = int16__VIP_Current_VD10
            self.int16__VIP_Voltage_VD11 = int16__VIP_Voltage_VD11
            self.int16__VIP_Current_VD11 = int16__VIP_Current_VD11
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VOLT_BRDSUP)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__TEMP_MCU)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_INPUT_Voltage)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_INPUT_Current)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_INPUT_Power)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__STAT_CH_ON)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__STAT_CH_OCF)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_Voltage_VD0)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_Current_VD0)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_Voltage_VD4)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_Current_VD4)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_Voltage_VD6)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_Current_VD6)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_Voltage_VD7)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_Current_VD7)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_Voltage_VD8)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_Current_VD8)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_Voltage_VD9)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_Current_VD9)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_Voltage_VD10)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_Current_VD10)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_Voltage_VD11)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_Current_VD11)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_EPS_2()
    
            currentPos = pos
            
            (resultInstance.int16__VOLT_BRDSUP, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__TEMP_MCU, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_INPUT_Voltage, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_INPUT_Current, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_INPUT_Power, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__STAT_CH_ON, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__STAT_CH_OCF, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_Voltage_VD0, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_Current_VD0, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_Voltage_VD4, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_Current_VD4, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_Voltage_VD6, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_Current_VD6, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_Voltage_VD7, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_Current_VD7, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_Voltage_VD8, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_Current_VD8, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_Voltage_VD9, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_Current_VD9, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_Voltage_VD10, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_Current_VD10, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_Voltage_VD11, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_Current_VD11, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 46
    
    class struct_EPS_1:
        def __init__(self, int32__battCapacity = 0, int32__battVoltage = 0, int32__battCurrent = 0, int32__battTemperature = 0):
            self.int32__battCapacity = int32__battCapacity
            self.int32__battVoltage = int32__battVoltage
            self.int32__battCurrent = int32__battCurrent
            self.int32__battTemperature = int32__battTemperature
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("int32", self.int32__battCapacity)
            
            result += SerDesHelpers.serdesType_basic.serialize("int32", self.int32__battVoltage)
            
            result += SerDesHelpers.serdesType_basic.serialize("int32", self.int32__battCurrent)
            
            result += SerDesHelpers.serdesType_basic.serialize("int32", self.int32__battTemperature)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_EPS_1()
    
            currentPos = pos
            
            (resultInstance.int32__battCapacity, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int32__battVoltage, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int32__battCurrent, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int32__battTemperature, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int32", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 16
    
    class struct_TaskStats:
        def __init__(self, a__int16__30__taskStackMaxUnusedSize = []):
            self.a__int16__30__taskStackMaxUnusedSize = a__int16__30__taskStackMaxUnusedSize
    
        def serialize(self):
            result = bytearray()
    
            actualLen = len(self.a__int16__30__taskStackMaxUnusedSize)
            if (actualLen < 30):
                self.a__int16__30__taskStackMaxUnusedSize = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__30__taskStackMaxUnusedSize, 30)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__30__taskStackMaxUnusedSize)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_TaskStats()
    
            currentPos = pos
            
            (resultInstance.a__int16__30__taskStackMaxUnusedSize, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 30)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 60
    
    class struct_ADCS_0:
        def __init__(self, a__int16__3__magFieldVec = [], a__int16__3__coarseSunVec = [], a__int16__3__fineSunVec = [], a__int16__3__nadirVec = [], a__int16__3__angRateVec = [], a__int16__3__wheelSpeedArr = []):
            self.a__int16__3__magFieldVec = a__int16__3__magFieldVec
            self.a__int16__3__coarseSunVec = a__int16__3__coarseSunVec
            self.a__int16__3__fineSunVec = a__int16__3__fineSunVec
            self.a__int16__3__nadirVec = a__int16__3__nadirVec
            self.a__int16__3__angRateVec = a__int16__3__angRateVec
            self.a__int16__3__wheelSpeedArr = a__int16__3__wheelSpeedArr
    
        def serialize(self):
            result = bytearray()
    
            actualLen = len(self.a__int16__3__magFieldVec)
            if (actualLen < 3):
                self.a__int16__3__magFieldVec = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__3__magFieldVec, 3)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__3__magFieldVec)
            actualLen = len(self.a__int16__3__coarseSunVec)
            if (actualLen < 3):
                self.a__int16__3__coarseSunVec = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__3__coarseSunVec, 3)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__3__coarseSunVec)
            actualLen = len(self.a__int16__3__fineSunVec)
            if (actualLen < 3):
                self.a__int16__3__fineSunVec = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__3__fineSunVec, 3)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__3__fineSunVec)
            actualLen = len(self.a__int16__3__nadirVec)
            if (actualLen < 3):
                self.a__int16__3__nadirVec = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__3__nadirVec, 3)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__3__nadirVec)
            actualLen = len(self.a__int16__3__angRateVec)
            if (actualLen < 3):
                self.a__int16__3__angRateVec = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__3__angRateVec, 3)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__3__angRateVec)
            actualLen = len(self.a__int16__3__wheelSpeedArr)
            if (actualLen < 3):
                self.a__int16__3__wheelSpeedArr = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__3__wheelSpeedArr, 3)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__3__wheelSpeedArr)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_ADCS_0()
    
            currentPos = pos
            
            (resultInstance.a__int16__3__magFieldVec, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 3)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__3__coarseSunVec, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 3)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__3__fineSunVec, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 3)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__3__nadirVec, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 3)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__3__angRateVec, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 3)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__3__wheelSpeedArr, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 3)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 36
    
    class struct_EPS_4:
        def __init__(self, int16__VOLT_BRDSUP = 0, int16__TEMP_MCU = 0, int16__VIP_OUTPUT_Voltage = 0, int16__VIP_OUTPUT_Current = 0, int16__VIP_OUTPUT_Power = 0, a__int16__4__VIP_CC_OUTPUT_Voltage = [], a__int16__4__VIP_CC_OUTPUT_Current = [], a__int16__4__VIP_CC_OUTPUT_Power = [], a__int16__4__CCx_VOLT_IN_MPPT = [], a__int16__4__CCx_CURR_IN_MPPT = [], a__int16__4__CCx_VOLT_OU_MPPT = [], a__int16__4__CCx_CURR_OU_MPPT = []):
            self.int16__VOLT_BRDSUP = int16__VOLT_BRDSUP
            self.int16__TEMP_MCU = int16__TEMP_MCU
            self.int16__VIP_OUTPUT_Voltage = int16__VIP_OUTPUT_Voltage
            self.int16__VIP_OUTPUT_Current = int16__VIP_OUTPUT_Current
            self.int16__VIP_OUTPUT_Power = int16__VIP_OUTPUT_Power
            self.a__int16__4__VIP_CC_OUTPUT_Voltage = a__int16__4__VIP_CC_OUTPUT_Voltage
            self.a__int16__4__VIP_CC_OUTPUT_Current = a__int16__4__VIP_CC_OUTPUT_Current
            self.a__int16__4__VIP_CC_OUTPUT_Power = a__int16__4__VIP_CC_OUTPUT_Power
            self.a__int16__4__CCx_VOLT_IN_MPPT = a__int16__4__CCx_VOLT_IN_MPPT
            self.a__int16__4__CCx_CURR_IN_MPPT = a__int16__4__CCx_CURR_IN_MPPT
            self.a__int16__4__CCx_VOLT_OU_MPPT = a__int16__4__CCx_VOLT_OU_MPPT
            self.a__int16__4__CCx_CURR_OU_MPPT = a__int16__4__CCx_CURR_OU_MPPT
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VOLT_BRDSUP)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__TEMP_MCU)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_OUTPUT_Voltage)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_OUTPUT_Current)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_OUTPUT_Power)
            actualLen = len(self.a__int16__4__VIP_CC_OUTPUT_Voltage)
            if (actualLen < 4):
                self.a__int16__4__VIP_CC_OUTPUT_Voltage = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__4__VIP_CC_OUTPUT_Voltage, 4)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__4__VIP_CC_OUTPUT_Voltage)
            actualLen = len(self.a__int16__4__VIP_CC_OUTPUT_Current)
            if (actualLen < 4):
                self.a__int16__4__VIP_CC_OUTPUT_Current = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__4__VIP_CC_OUTPUT_Current, 4)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__4__VIP_CC_OUTPUT_Current)
            actualLen = len(self.a__int16__4__VIP_CC_OUTPUT_Power)
            if (actualLen < 4):
                self.a__int16__4__VIP_CC_OUTPUT_Power = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__4__VIP_CC_OUTPUT_Power, 4)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__4__VIP_CC_OUTPUT_Power)
            actualLen = len(self.a__int16__4__CCx_VOLT_IN_MPPT)
            if (actualLen < 4):
                self.a__int16__4__CCx_VOLT_IN_MPPT = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__4__CCx_VOLT_IN_MPPT, 4)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__4__CCx_VOLT_IN_MPPT)
            actualLen = len(self.a__int16__4__CCx_CURR_IN_MPPT)
            if (actualLen < 4):
                self.a__int16__4__CCx_CURR_IN_MPPT = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__4__CCx_CURR_IN_MPPT, 4)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__4__CCx_CURR_IN_MPPT)
            actualLen = len(self.a__int16__4__CCx_VOLT_OU_MPPT)
            if (actualLen < 4):
                self.a__int16__4__CCx_VOLT_OU_MPPT = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__4__CCx_VOLT_OU_MPPT, 4)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__4__CCx_VOLT_OU_MPPT)
            actualLen = len(self.a__int16__4__CCx_CURR_OU_MPPT)
            if (actualLen < 4):
                self.a__int16__4__CCx_CURR_OU_MPPT = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__4__CCx_CURR_OU_MPPT, 4)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__4__CCx_CURR_OU_MPPT)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_EPS_4()
    
            currentPos = pos
            
            (resultInstance.int16__VOLT_BRDSUP, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__TEMP_MCU, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_OUTPUT_Voltage, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_OUTPUT_Current, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_OUTPUT_Power, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__4__VIP_CC_OUTPUT_Voltage, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 4)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__4__VIP_CC_OUTPUT_Current, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 4)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__4__VIP_CC_OUTPUT_Power, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 4)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__4__CCx_VOLT_IN_MPPT, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 4)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__4__CCx_CURR_IN_MPPT, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 4)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__4__CCx_VOLT_OU_MPPT, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 4)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__4__CCx_CURR_OU_MPPT, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 4)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 66
    
    class struct_ConOpsFlags:
        def __init__(self, bool__PAY_ERR = False, bool__ADCS_ERR = False, bool__DETUMB_COMPLETED = False):
            self.bool__PAY_ERR = bool__PAY_ERR
            self.bool__ADCS_ERR = bool__ADCS_ERR
            self.bool__DETUMB_COMPLETED = bool__DETUMB_COMPLETED
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.bool__PAY_ERR)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.bool__ADCS_ERR)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.bool__DETUMB_COMPLETED)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_ConOpsFlags()
    
            currentPos = pos
            
            (resultInstance.bool__PAY_ERR, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.bool__ADCS_ERR, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.bool__DETUMB_COMPLETED, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 3
    
    class struct_ADCS_1:
        def __init__(self, a__int16__3__estQSet = [], a__int16__3__estAngRateVec = []):
            self.a__int16__3__estQSet = a__int16__3__estQSet
            self.a__int16__3__estAngRateVec = a__int16__3__estAngRateVec
    
        def serialize(self):
            result = bytearray()
    
            actualLen = len(self.a__int16__3__estQSet)
            if (actualLen < 3):
                self.a__int16__3__estQSet = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__3__estQSet, 3)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__3__estQSet)
            actualLen = len(self.a__int16__3__estAngRateVec)
            if (actualLen < 3):
                self.a__int16__3__estAngRateVec = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__3__estAngRateVec, 3)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__3__estAngRateVec)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_ADCS_1()
    
            currentPos = pos
            
            (resultInstance.a__int16__3__estQSet, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 3)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__3__estAngRateVec, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 3)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 12
    
    class struct_EPS_3:
        def __init__(self, int16__VOLT_BRDSUP = 0, int16__TEMP_MCU = 0, int16__VIP_INPUT_Voltage = 0, int16__VIP_INPUT_Current = 0, int16__VIP_INPUT_Power = 0, uint16__STAT_BU = 0, a__int16__2__VIP_BP_INPUT_Voltage = [], a__int16__2__VIP_BP_INPUT_Current = [], a__int16__2__VIP_BP_INPUT_Power = [], a__int16__2__STAT_BP = [], a__int16__2__VOLT_CELL1 = [], a__int16__2__VOLT_CELL2 = [], a__int16__2__VOLT_CELL3 = [], a__int16__2__VOLT_CELL4 = [], a__int16__2__BAT_TEMP1 = [], a__int16__2__BAT_TEMP2 = [], a__int16__2__BAT_TEMP3 = []):
            self.int16__VOLT_BRDSUP = int16__VOLT_BRDSUP
            self.int16__TEMP_MCU = int16__TEMP_MCU
            self.int16__VIP_INPUT_Voltage = int16__VIP_INPUT_Voltage
            self.int16__VIP_INPUT_Current = int16__VIP_INPUT_Current
            self.int16__VIP_INPUT_Power = int16__VIP_INPUT_Power
            self.uint16__STAT_BU = uint16__STAT_BU
            self.a__int16__2__VIP_BP_INPUT_Voltage = a__int16__2__VIP_BP_INPUT_Voltage
            self.a__int16__2__VIP_BP_INPUT_Current = a__int16__2__VIP_BP_INPUT_Current
            self.a__int16__2__VIP_BP_INPUT_Power = a__int16__2__VIP_BP_INPUT_Power
            self.a__int16__2__STAT_BP = a__int16__2__STAT_BP
            self.a__int16__2__VOLT_CELL1 = a__int16__2__VOLT_CELL1
            self.a__int16__2__VOLT_CELL2 = a__int16__2__VOLT_CELL2
            self.a__int16__2__VOLT_CELL3 = a__int16__2__VOLT_CELL3
            self.a__int16__2__VOLT_CELL4 = a__int16__2__VOLT_CELL4
            self.a__int16__2__BAT_TEMP1 = a__int16__2__BAT_TEMP1
            self.a__int16__2__BAT_TEMP2 = a__int16__2__BAT_TEMP2
            self.a__int16__2__BAT_TEMP3 = a__int16__2__BAT_TEMP3
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VOLT_BRDSUP)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__TEMP_MCU)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_INPUT_Voltage)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_INPUT_Current)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__VIP_INPUT_Power)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__STAT_BU)
            actualLen = len(self.a__int16__2__VIP_BP_INPUT_Voltage)
            if (actualLen < 2):
                self.a__int16__2__VIP_BP_INPUT_Voltage = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__2__VIP_BP_INPUT_Voltage, 2)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__2__VIP_BP_INPUT_Voltage)
            actualLen = len(self.a__int16__2__VIP_BP_INPUT_Current)
            if (actualLen < 2):
                self.a__int16__2__VIP_BP_INPUT_Current = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__2__VIP_BP_INPUT_Current, 2)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__2__VIP_BP_INPUT_Current)
            actualLen = len(self.a__int16__2__VIP_BP_INPUT_Power)
            if (actualLen < 2):
                self.a__int16__2__VIP_BP_INPUT_Power = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__2__VIP_BP_INPUT_Power, 2)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__2__VIP_BP_INPUT_Power)
            actualLen = len(self.a__int16__2__STAT_BP)
            if (actualLen < 2):
                self.a__int16__2__STAT_BP = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__2__STAT_BP, 2)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__2__STAT_BP)
            actualLen = len(self.a__int16__2__VOLT_CELL1)
            if (actualLen < 2):
                self.a__int16__2__VOLT_CELL1 = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__2__VOLT_CELL1, 2)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__2__VOLT_CELL1)
            actualLen = len(self.a__int16__2__VOLT_CELL2)
            if (actualLen < 2):
                self.a__int16__2__VOLT_CELL2 = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__2__VOLT_CELL2, 2)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__2__VOLT_CELL2)
            actualLen = len(self.a__int16__2__VOLT_CELL3)
            if (actualLen < 2):
                self.a__int16__2__VOLT_CELL3 = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__2__VOLT_CELL3, 2)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__2__VOLT_CELL3)
            actualLen = len(self.a__int16__2__VOLT_CELL4)
            if (actualLen < 2):
                self.a__int16__2__VOLT_CELL4 = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__2__VOLT_CELL4, 2)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__2__VOLT_CELL4)
            actualLen = len(self.a__int16__2__BAT_TEMP1)
            if (actualLen < 2):
                self.a__int16__2__BAT_TEMP1 = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__2__BAT_TEMP1, 2)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__2__BAT_TEMP1)
            actualLen = len(self.a__int16__2__BAT_TEMP2)
            if (actualLen < 2):
                self.a__int16__2__BAT_TEMP2 = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__2__BAT_TEMP2, 2)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__2__BAT_TEMP2)
            actualLen = len(self.a__int16__2__BAT_TEMP3)
            if (actualLen < 2):
                self.a__int16__2__BAT_TEMP3 = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__int16__2__BAT_TEMP3, 2)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("int16", self.a__int16__2__BAT_TEMP3)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_EPS_3()
    
            currentPos = pos
            
            (resultInstance.int16__VOLT_BRDSUP, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__TEMP_MCU, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_INPUT_Voltage, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_INPUT_Current, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__VIP_INPUT_Power, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__STAT_BU, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__2__VIP_BP_INPUT_Voltage, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 2)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__2__VIP_BP_INPUT_Current, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 2)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__2__VIP_BP_INPUT_Power, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 2)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__2__STAT_BP, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 2)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__2__VOLT_CELL1, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 2)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__2__VOLT_CELL2, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 2)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__2__VOLT_CELL3, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 2)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__2__VOLT_CELL4, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 2)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__2__BAT_TEMP1, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 2)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__2__BAT_TEMP2, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 2)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__int16__2__BAT_TEMP3, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("int16", data, currentPos, 2)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 56
    
    class struct_ADCS_2:
        def __init__(self, a__uint8__6__adcsState = [], a__uint8__6__adcsState2 = []):
            self.a__uint8__6__adcsState = a__uint8__6__adcsState
            self.a__uint8__6__adcsState2 = a__uint8__6__adcsState2
    
        def serialize(self):
            result = bytearray()
    
            actualLen = len(self.a__uint8__6__adcsState)
            if (actualLen < 6):
                self.a__uint8__6__adcsState = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__uint8__6__adcsState, 6)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("uint8", self.a__uint8__6__adcsState)
            actualLen = len(self.a__uint8__6__adcsState2)
            if (actualLen < 6):
                self.a__uint8__6__adcsState2 = SerDesHelpers.serdesType_basicArray.appendNullToBuff(self.a__uint8__6__adcsState2, 6)
            
            result += SerDesHelpers.serdesType_basicArray.serialize("uint8", self.a__uint8__6__adcsState2)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_ADCS_2()
    
            currentPos = pos
            
            (resultInstance.a__uint8__6__adcsState, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("uint8", data, currentPos, 6)
            currentPos += bytesProcessed
            
            
            (resultInstance.a__uint8__6__adcsState2, bytesProcessed) = SerDesHelpers.serdesType_basicArray.deserialize("uint8", data, currentPos, 6)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 12
    
    class struct_EPS_6:
        def __init__(self, uint16__STAT_CH_ON = 0, uint16__STAT_CH_OCF = 0, uint16__OCF_CNT_CH00 = 0, uint16__OCF_CNT_CH04 = 0, uint16__OCF_CNT_CH06 = 0, uint16__OCF_CNT_CH07 = 0, uint16__OCF_CNT_CH08 = 0, uint16__OCF_CNT_CH09 = 0, uint16__OCF_CNT_CH10 = 0, uint16__OCF_CNT_CH11 = 0):
            self.uint16__STAT_CH_ON = uint16__STAT_CH_ON
            self.uint16__STAT_CH_OCF = uint16__STAT_CH_OCF
            self.uint16__OCF_CNT_CH00 = uint16__OCF_CNT_CH00
            self.uint16__OCF_CNT_CH04 = uint16__OCF_CNT_CH04
            self.uint16__OCF_CNT_CH06 = uint16__OCF_CNT_CH06
            self.uint16__OCF_CNT_CH07 = uint16__OCF_CNT_CH07
            self.uint16__OCF_CNT_CH08 = uint16__OCF_CNT_CH08
            self.uint16__OCF_CNT_CH09 = uint16__OCF_CNT_CH09
            self.uint16__OCF_CNT_CH10 = uint16__OCF_CNT_CH10
            self.uint16__OCF_CNT_CH11 = uint16__OCF_CNT_CH11
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__STAT_CH_ON)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__STAT_CH_OCF)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__OCF_CNT_CH00)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__OCF_CNT_CH04)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__OCF_CNT_CH06)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__OCF_CNT_CH07)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__OCF_CNT_CH08)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__OCF_CNT_CH09)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__OCF_CNT_CH10)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__OCF_CNT_CH11)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_EPS_6()
    
            currentPos = pos
            
            (resultInstance.uint16__STAT_CH_ON, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__STAT_CH_OCF, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__OCF_CNT_CH00, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__OCF_CNT_CH04, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__OCF_CNT_CH06, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__OCF_CNT_CH07, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__OCF_CNT_CH08, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__OCF_CNT_CH09, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__OCF_CNT_CH10, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__OCF_CNT_CH11, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 20
    
    class struct_AOCS_CNTRL_SYS_STATE:
        def __init__(self, uint8__adcsSysState = 0, uint8__adcsSysStateStatus = 0):
            self.uint8__adcsSysState = uint8__adcsSysState
            self.uint8__adcsSysStateStatus = uint8__adcsSysStateStatus
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.uint8__adcsSysState)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.uint8__adcsSysStateStatus)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_AOCS_CNTRL_SYS_STATE()
    
            currentPos = pos
            
            (resultInstance.uint8__adcsSysState, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint8__adcsSysStateStatus, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 2
    
    class struct_EPS_5:
        def __init__(self, uint8__MODE = 0, uint8__RESET_CAUSE = 0, uint32__UPTIME = 0, uint16__ERROR = 0, uint16__RC_CNT_PWRON = 0, uint16__RC_CNT_WDG = 0, uint16__RC_CNT_CMD = 0, uint16__RC_CNT_MCU = 0, uint16__RC_CNT_EMLOPO = 0, uint32__UNIX_TIME = 0, uint32__UNIX_YEAR = 0, uint32__UNIX_MONTH = 0, uint32__UNIX_DAY = 0, uint32__UNIX_HOUR = 0, uint32__UNIX_MINUTE = 0, uint32__UNIX_SECOND = 0):
            self.uint8__MODE = uint8__MODE
            self.uint8__RESET_CAUSE = uint8__RESET_CAUSE
            self.uint32__UPTIME = uint32__UPTIME
            self.uint16__ERROR = uint16__ERROR
            self.uint16__RC_CNT_PWRON = uint16__RC_CNT_PWRON
            self.uint16__RC_CNT_WDG = uint16__RC_CNT_WDG
            self.uint16__RC_CNT_CMD = uint16__RC_CNT_CMD
            self.uint16__RC_CNT_MCU = uint16__RC_CNT_MCU
            self.uint16__RC_CNT_EMLOPO = uint16__RC_CNT_EMLOPO
            self.uint32__UNIX_TIME = uint32__UNIX_TIME
            self.uint32__UNIX_YEAR = uint32__UNIX_YEAR
            self.uint32__UNIX_MONTH = uint32__UNIX_MONTH
            self.uint32__UNIX_DAY = uint32__UNIX_DAY
            self.uint32__UNIX_HOUR = uint32__UNIX_HOUR
            self.uint32__UNIX_MINUTE = uint32__UNIX_MINUTE
            self.uint32__UNIX_SECOND = uint32__UNIX_SECOND
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.uint8__MODE)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.uint8__RESET_CAUSE)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__UPTIME)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__ERROR)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__RC_CNT_PWRON)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__RC_CNT_WDG)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__RC_CNT_CMD)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__RC_CNT_MCU)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__RC_CNT_EMLOPO)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__UNIX_TIME)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__UNIX_YEAR)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__UNIX_MONTH)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__UNIX_DAY)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__UNIX_HOUR)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__UNIX_MINUTE)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__UNIX_SECOND)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_EPS_5()
    
            currentPos = pos
            
            (resultInstance.uint8__MODE, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint8__RESET_CAUSE, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__UPTIME, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__ERROR, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__RC_CNT_PWRON, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__RC_CNT_WDG, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__RC_CNT_CMD, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__RC_CNT_MCU, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__RC_CNT_EMLOPO, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__UNIX_TIME, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__UNIX_YEAR, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__UNIX_MONTH, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__UNIX_DAY, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__UNIX_HOUR, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__UNIX_MINUTE, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__UNIX_SECOND, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 46
    
    class enum_DCDataUpdateStatus:
        DCDATAUPDATESTATUS_ERROR = 0
        DCDATAUPDATESTATUS_OK = 1
    
        ValuesDict = {
            DCDATAUPDATESTATUS_ERROR : 'DCDATAUPDATESTATUS_ERROR', 
            DCDATAUPDATESTATUS_OK : 'DCDATAUPDATESTATUS_OK'
        }
    
        def __init__(self, value = 0):
            self.value = value
    
        def serialize(self):
            result = bytearray()
    
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.value)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.enum_DCDataUpdateStatus()
    
            (resultInstance.value, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, pos)
    
            return (resultInstance, bytesProcessed)
    
        def getSymbolicName(self):
            return FP_API_DATA_CACHE.enum_DCDataUpdateStatus.ValuesDict[self.value]
    
        @staticmethod
        def getValueBySymbolicName(literalName):
            for key, value in FP_API_DATA_CACHE.enum_DCDataUpdateStatus.ValuesDict.items():
                if literalName == value:
                    return key
    
        @staticmethod
        def getSize():
            return 1
    
    class struct_OBC_0:
        def __init__(self, uint8__opMode = 0, uint32__upTime = 0, uint16__totalResetCount = 0, uint16__resetReasonBitField = 0, uint16__payloadModesStatus = 0):
            self.uint8__opMode = uint8__opMode
            self.uint32__upTime = uint32__upTime
            self.uint16__totalResetCount = uint16__totalResetCount
            self.uint16__resetReasonBitField = uint16__resetReasonBitField
            self.uint16__payloadModesStatus = uint16__payloadModesStatus
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("uint8", self.uint8__opMode)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint32", self.uint32__upTime)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__totalResetCount)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__resetReasonBitField)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__payloadModesStatus)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_OBC_0()
    
            currentPos = pos
            
            (resultInstance.uint8__opMode, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint8", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint32__upTime, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint32", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__totalResetCount, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__resetReasonBitField, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__payloadModesStatus, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 11
    
    class struct_SSP_0:
        def __init__(self, uint16__sunDataMain = 0, uint16__sunDataExt = 0, int16__tempMCU = 0, int16__tempMain = 0, int16__tempExt1 = 0, int16__tempExt2 = 0):
            self.uint16__sunDataMain = uint16__sunDataMain
            self.uint16__sunDataExt = uint16__sunDataExt
            self.int16__tempMCU = int16__tempMCU
            self.int16__tempMain = int16__tempMain
            self.int16__tempExt1 = int16__tempExt1
            self.int16__tempExt2 = int16__tempExt2
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__sunDataMain)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__sunDataExt)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__tempMCU)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__tempMain)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__tempExt1)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__tempExt2)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_SSP_0()
    
            currentPos = pos
            
            (resultInstance.uint16__sunDataMain, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__sunDataExt, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__tempMCU, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__tempMain, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__tempExt1, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__tempExt2, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 12
    
    class struct_SSP_1:
        def __init__(self, uint16__sunDataMain = 0, uint16__sunDataExt = 0, int16__tempMCU = 0, int16__tempMain = 0, int16__tempExt1 = 0, int16__tempExt2 = 0):
            self.uint16__sunDataMain = uint16__sunDataMain
            self.uint16__sunDataExt = uint16__sunDataExt
            self.int16__tempMCU = int16__tempMCU
            self.int16__tempMain = int16__tempMain
            self.int16__tempExt1 = int16__tempExt1
            self.int16__tempExt2 = int16__tempExt2
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__sunDataMain)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__sunDataExt)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__tempMCU)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__tempMain)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__tempExt1)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__tempExt2)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_SSP_1()
    
            currentPos = pos
            
            (resultInstance.uint16__sunDataMain, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__sunDataExt, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__tempMCU, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__tempMain, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__tempExt1, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__tempExt2, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 12
    
    class struct_SSP_2:
        def __init__(self, uint16__sunDataMain = 0, uint16__sunDataExt = 0, int16__tempMCU = 0, int16__tempMain = 0, int16__tempExt1 = 0, int16__tempExt2 = 0):
            self.uint16__sunDataMain = uint16__sunDataMain
            self.uint16__sunDataExt = uint16__sunDataExt
            self.int16__tempMCU = int16__tempMCU
            self.int16__tempMain = int16__tempMain
            self.int16__tempExt1 = int16__tempExt1
            self.int16__tempExt2 = int16__tempExt2
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__sunDataMain)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__sunDataExt)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__tempMCU)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__tempMain)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__tempExt1)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__tempExt2)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_SSP_2()
    
            currentPos = pos
            
            (resultInstance.uint16__sunDataMain, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__sunDataExt, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__tempMCU, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__tempMain, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__tempExt1, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__tempExt2, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 12
    
    class struct_SSP_3:
        def __init__(self, uint16__sunDataMain = 0, uint16__sunDataExt = 0, int16__tempMCU = 0, int16__tempMain = 0, int16__tempExt1 = 0, int16__tempExt2 = 0):
            self.uint16__sunDataMain = uint16__sunDataMain
            self.uint16__sunDataExt = uint16__sunDataExt
            self.int16__tempMCU = int16__tempMCU
            self.int16__tempMain = int16__tempMain
            self.int16__tempExt1 = int16__tempExt1
            self.int16__tempExt2 = int16__tempExt2
    
        def serialize(self):
            result = bytearray()
    
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__sunDataMain)
            
            result += SerDesHelpers.serdesType_basic.serialize("uint16", self.uint16__sunDataExt)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__tempMCU)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__tempMain)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__tempExt1)
            
            result += SerDesHelpers.serdesType_basic.serialize("int16", self.int16__tempExt2)
    
            return result
    
        @staticmethod
        def deserialize(data, pos):
            resultInstance = FP_API_DATA_CACHE.struct_SSP_3()
    
            currentPos = pos
            
            (resultInstance.uint16__sunDataMain, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.uint16__sunDataExt, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("uint16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__tempMCU, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__tempMain, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__tempExt1, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
            
            (resultInstance.int16__tempExt2, bytesProcessed) = SerDesHelpers.serdesType_basic.deserialize("int16", data, currentPos)
            currentPos += bytesProcessed
            
    
            # tuple[1] shall contain the total number of bytes processed by the function
            return (resultInstance, currentPos - pos)
    
        @staticmethod
        def getSize():
            return 12
    

    ############################################################################################################
    """
    Request function for FIDL method: get_OBC_0_Data
        - function ID: 00000000
        - description: Requests OBC_0_Data from the data cache
    """
    def req_get_OBC_0_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000000
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000000, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_OBC_0_Data
        - function ID: 00000000
        - description: Requests OBC_0_Data from the data cache
    """
    def resp_get_OBC_0_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000000):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_OBC_0.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_OBC_0_Data
        - function ID: 00000001
        - description: Updates OBC_0_Data to the data cache
    """
    def req_set_OBC_0_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000001
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000001, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_OBC_0_Data
        - function ID: 00000001
        - description: Updates OBC_0_Data to the data cache
    """
    def resp_set_OBC_0_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000001):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_ADCS_0_Data
        - function ID: 00000002
        - description: Requests ADCS_0_Data from the data cache
    """
    def req_get_ADCS_0_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000002
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000002, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_ADCS_0_Data
        - function ID: 00000002
        - description: Requests ADCS_0_Data from the data cache
    """
    def resp_get_ADCS_0_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000002):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_ADCS_0.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_ADCS_0_Data
        - function ID: 00000003
        - description: Updates ADCS_0_Data to the data cache
    """
    def req_set_ADCS_0_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000003
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000003, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_ADCS_0_Data
        - function ID: 00000003
        - description: Updates ADCS_0_Data to the data cache
    """
    def resp_set_ADCS_0_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000003):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_ADCS_1_Data
        - function ID: 00000004
        - description: Requests ADCS_1_Data from the data cache
    """
    def req_get_ADCS_1_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000004
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000004, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_ADCS_1_Data
        - function ID: 00000004
        - description: Requests ADCS_1_Data from the data cache
    """
    def resp_get_ADCS_1_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000004):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_ADCS_1.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_ADCS_1_Data
        - function ID: 00000005
        - description: Updates ADCS_1_Data to the data cache
    """
    def req_set_ADCS_1_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000005
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000005, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_ADCS_1_Data
        - function ID: 00000005
        - description: Updates ADCS_1_Data to the data cache
    """
    def resp_set_ADCS_1_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000005):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_ADCS_2_Data
        - function ID: 00000006
        - description: Requests ADCS_2_Data from the data cache
    """
    def req_get_ADCS_2_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000006
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000006, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_ADCS_2_Data
        - function ID: 00000006
        - description: Requests ADCS_2_Data from the data cache
    """
    def resp_get_ADCS_2_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000006):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_ADCS_2.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_ADCS_2_Data
        - function ID: 00000007
        - description: Updates ADCS_2_Data to the data cache
    """
    def req_set_ADCS_2_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000007
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000007, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_ADCS_2_Data
        - function ID: 00000007
        - description: Updates ADCS_2_Data to the data cache
    """
    def resp_set_ADCS_2_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000007):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_EPS_0_Data
        - function ID: 00000008
        - description: Requests EPS_0_Data from the data cache
    """
    def req_get_EPS_0_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000008
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000008, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_EPS_0_Data
        - function ID: 00000008
        - description: Requests EPS_0_Data from the data cache
    """
    def resp_get_EPS_0_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000008):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_EPS_0.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_EPS_0_Data
        - function ID: 00000009
        - description: Updates EPS_0_Data to the data cache
    """
    def req_set_EPS_0_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000009
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000009, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_EPS_0_Data
        - function ID: 00000009
        - description: Updates EPS_0_Data to the data cache
    """
    def resp_set_EPS_0_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000009):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_SSP_0_Data
        - function ID: 0000000A
        - description: Requests SSP_0_Data from the data cache
    """
    def req_get_SSP_0_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x0000000A
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x0000000A, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_SSP_0_Data
        - function ID: 0000000A
        - description: Requests SSP_0_Data from the data cache
    """
    def resp_get_SSP_0_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x0000000A):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_SSP_0.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_SSP_0_Data
        - function ID: 0000000B
        - description: Updates SSP_0_Data to the data cache
    """
    def req_set_SSP_0_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x0000000B
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x0000000B, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_SSP_0_Data
        - function ID: 0000000B
        - description: Updates SSP_0_Data to the data cache
    """
    def resp_set_SSP_0_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x0000000B):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_SSP_1_Data
        - function ID: 0000000C
        - description: Requests SSP_1_Data from the data cache
    """
    def req_get_SSP_1_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x0000000C
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x0000000C, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_SSP_1_Data
        - function ID: 0000000C
        - description: Requests SSP_1_Data from the data cache
    """
    def resp_get_SSP_1_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x0000000C):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_SSP_1.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_SSP_1_Data
        - function ID: 0000000D
        - description: Updates SSP_1_Data to the data cache
    """
    def req_set_SSP_1_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x0000000D
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x0000000D, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_SSP_1_Data
        - function ID: 0000000D
        - description: Updates SSP_1_Data to the data cache
    """
    def resp_set_SSP_1_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x0000000D):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_SSP_2_Data
        - function ID: 0000000E
        - description: Requests SSP_2_Data from the data cache
    """
    def req_get_SSP_2_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
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
    Response function for FIDL method: get_SSP_2_Data
        - function ID: 0000000E
        - description: Requests SSP_2_Data from the data cache
    """
    def resp_get_SSP_2_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x0000000E):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_SSP_2.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_SSP_2_Data
        - function ID: 0000000F
        - description: Updates SSP_2_Data to the data cache
    """
    def req_set_SSP_2_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x0000000F
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x0000000F, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_SSP_2_Data
        - function ID: 0000000F
        - description: Updates SSP_2_Data to the data cache
    """
    def resp_set_SSP_2_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x0000000F):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_AOCS_CNTRL_TLM_Data
        - function ID: 00000010
        - description: Requests AOCS_CNTRL_TLM_Data from the data cache
    """
    def req_get_AOCS_CNTRL_TLM_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000010
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000010, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_AOCS_CNTRL_TLM_Data
        - function ID: 00000010
        - description: Requests AOCS_CNTRL_TLM_Data from the data cache
    """
    def resp_get_AOCS_CNTRL_TLM_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000010):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_AOCS_CNTRL_TLM.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_AOCS_CNTRL_TLM_Data
        - function ID: 00000011
        - description: Updates AOCS_CNTRL_TLM_Data to the data cache
    """
    def req_set_AOCS_CNTRL_TLM_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000011
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000011, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_AOCS_CNTRL_TLM_Data
        - function ID: 00000011
        - description: Updates AOCS_CNTRL_TLM_Data to the data cache
    """
    def resp_set_AOCS_CNTRL_TLM_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000011):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_EPS_1_Data
        - function ID: 00000012
        - description: Requests EPS_1_Data from the data cache
    """
    def req_get_EPS_1_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
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
    Response function for FIDL method: get_EPS_1_Data
        - function ID: 00000012
        - description: Requests EPS_1_Data from the data cache
    """
    def resp_get_EPS_1_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000012):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_EPS_1.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_EPS_1_Data
        - function ID: 00000013
        - description: Updates EPS_1_Data to the data cache
    """
    def req_set_EPS_1_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000013
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000013, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_EPS_1_Data
        - function ID: 00000013
        - description: Updates EPS_1_Data to the data cache
    """
    def resp_set_EPS_1_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000013):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_EPS_2_Data
        - function ID: 00000014
        - description: Requests EPS_2_Data from the data cache
    """
    def req_get_EPS_2_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000014
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000014, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_EPS_2_Data
        - function ID: 00000014
        - description: Requests EPS_2_Data from the data cache
    """
    def resp_get_EPS_2_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000014):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_EPS_2.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_EPS_2_Data
        - function ID: 00000015
        - description: Updates EPS_2_Data to the data cache
    """
    def req_set_EPS_2_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000015
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000015, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_EPS_2_Data
        - function ID: 00000015
        - description: Updates EPS_2_Data to the data cache
    """
    def resp_set_EPS_2_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000015):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_EPS_3_Data
        - function ID: 00000016
        - description: Requests EPS_3_Data from the data cache
    """
    def req_get_EPS_3_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000016
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000016, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_EPS_3_Data
        - function ID: 00000016
        - description: Requests EPS_3_Data from the data cache
    """
    def resp_get_EPS_3_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000016):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_EPS_3.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_EPS_3_Data
        - function ID: 00000017
        - description: Updates EPS_3_Data to the data cache
    """
    def req_set_EPS_3_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000017
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000017, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_EPS_3_Data
        - function ID: 00000017
        - description: Updates EPS_3_Data to the data cache
    """
    def resp_set_EPS_3_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000017):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_EPS_4_Data
        - function ID: 00000018
        - description: Requests EPS_4_Data from the data cache
    """
    def req_get_EPS_4_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
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
    Response function for FIDL method: get_EPS_4_Data
        - function ID: 00000018
        - description: Requests EPS_4_Data from the data cache
    """
    def resp_get_EPS_4_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000018):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_EPS_4.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_EPS_4_Data
        - function ID: 00000019
        - description: Updates EPS_4_Data to the data cache
    """
    def req_set_EPS_4_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000019
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000019, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_EPS_4_Data
        - function ID: 00000019
        - description: Updates EPS_4_Data to the data cache
    """
    def resp_set_EPS_4_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000019):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_EPS_5_Data
        - function ID: 0000001A
        - description: Requests EPS_5_Data from the data cache
    """
    def req_get_EPS_5_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x0000001A
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x0000001A, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_EPS_5_Data
        - function ID: 0000001A
        - description: Requests EPS_5_Data from the data cache
    """
    def resp_get_EPS_5_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x0000001A):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_EPS_5.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_EPS_5_Data
        - function ID: 0000001B
        - description: Updates EPS_5_Data to the data cache
    """
    def req_set_EPS_5_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x0000001B
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x0000001B, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_EPS_5_Data
        - function ID: 0000001B
        - description: Updates EPS_5_Data to the data cache
    """
    def resp_set_EPS_5_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x0000001B):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_EPS_6_Data
        - function ID: 0000001C
        - description: Requests EPS_6_Data from the data cache
    """
    def req_get_EPS_6_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x0000001C
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x0000001C, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_EPS_6_Data
        - function ID: 0000001C
        - description: Requests EPS_6_Data from the data cache
    """
    def resp_get_EPS_6_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x0000001C):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_EPS_6.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_EPS_6_Data
        - function ID: 0000001D
        - description: Updates EPS_6_Data to the data cache
    """
    def req_set_EPS_6_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x0000001D
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x0000001D, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_EPS_6_Data
        - function ID: 0000001D
        - description: Updates EPS_6_Data to the data cache
    """
    def resp_set_EPS_6_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x0000001D):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_OS_Task_Data
        - function ID: 0000001E
        - description: Requests OS_Task_Data from the data cache
    """
    def req_get_OS_Task_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x0000001E
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x0000001E, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_OS_Task_Data
        - function ID: 0000001E
        - description: Requests OS_Task_Data from the data cache
    """
    def resp_get_OS_Task_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x0000001E):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_TaskStats.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_OS_Task_Data
        - function ID: 0000001F
        - description: Updates OS_Task_Data to the data cache
    """
    def req_set_OS_Task_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x0000001F
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x0000001F, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_OS_Task_Data
        - function ID: 0000001F
        - description: Updates OS_Task_Data to the data cache
    """
    def resp_set_OS_Task_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x0000001F):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_SSP_3_Data
        - function ID: 00000020
        - description: Requests SSP_3_Data from the data cache
    """
    def req_get_SSP_3_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000020
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000020, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_SSP_3_Data
        - function ID: 00000020
        - description: Requests SSP_3_Data from the data cache
    """
    def resp_get_SSP_3_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000020):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_SSP_3.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_SSP_3_Data
        - function ID: 00000021
        - description: Updates SSP_3_Data to the data cache
    """
    def req_set_SSP_3_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000021
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000021, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_SSP_3_Data
        - function ID: 00000021
        - description: Updates SSP_3_Data to the data cache
    """
    def resp_set_SSP_3_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000021):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_ConOpsFlags_Data
        - function ID: 00000022
        - description: Requests ConOpsFlags_Data from the data cache
    """
    def req_get_ConOpsFlags_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000022
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000022, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_ConOpsFlags_Data
        - function ID: 00000022
        - description: Requests ConOpsFlags_Data from the data cache
    """
    def resp_get_ConOpsFlags_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000022):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_ConOpsFlags.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_ConOpsFlags_Data
        - function ID: 00000023
        - description: Updates ConOpsFlags_Data to the data cache
    """
    def req_set_ConOpsFlags_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000023
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000023, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_ConOpsFlags_Data
        - function ID: 00000023
        - description: Updates ConOpsFlags_Data to the data cache
    """
    def resp_set_ConOpsFlags_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000023):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: get_AOCS_CNTRL_SYS_STATE_Data
        - function ID: 00000024
        - description: Requests AOCS_CNTRL_SYS_STATE_Data from the data cache
    """
    def req_get_AOCS_CNTRL_SYS_STATE_Data(self):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000024
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000024, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: get_AOCS_CNTRL_SYS_STATE_Data
        - function ID: 00000024
        - description: Requests AOCS_CNTRL_SYS_STATE_Data from the data cache
    """
    def resp_get_AOCS_CNTRL_SYS_STATE_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000024):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.struct_AOCS_CNTRL_SYS_STATE.deserialize(data, currentPos)
        responseInstance["s__output_data"] = field
        currentPos += bytesProcessed
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataStatus__status"] = field
        currentPos += bytesProcessed
    
        return responseInstance

    ############################################################################################################
    """
    Request function for FIDL method: set_AOCS_CNTRL_SYS_STATE_Data
        - function ID: 00000025
        - description: Updates AOCS_CNTRL_SYS_STATE_Data to the data cache
    """
    def req_set_AOCS_CNTRL_SYS_STATE_Data(self, s__input_data):
        requestBytes = bytearray()
    
        if not self.rawSerDesSupport:
            fpHeaderInstance = SerDesHelpers.struct_FPHeader()
    
            fpHeaderInstance.u16ProtoId = self.const_DATA_CACHE_PROTOCOL_ID
            fpHeaderInstance.u32FuncId = 0x00000025
            fpHeaderInstance.u16seqId = 0
            fpHeaderInstance.u8ErrCode = 0
    
            requestBytes += fpHeaderInstance.serialize()
    
        requestBytes += s__input_data.serialize()
    
        if not self.rawSerDesSupport:
            return requestBytes
        else:
            return (0x00000025, requestBytes)

    ############################################################################################################
    """
    Response function for FIDL method: set_AOCS_CNTRL_SYS_STATE_Data
        - function ID: 00000025
        - description: Updates AOCS_CNTRL_SYS_STATE_Data to the data cache
    """
    def resp_set_AOCS_CNTRL_SYS_STATE_Data(self, data):
        # (key, value) = (output arg name, output arg data)
        responseInstance = {}
    
        if not self.rawSerDesSupport:
            (fpHeaderInstance, headerBytesProcessed) = SerDesHelpers.struct_FPHeader.deserialize(data, 0)
    
            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID) or (fpHeaderInstance.u32FuncId != 0x00000025):
               raise Exception("Protocol ID and/or Function ID do not match to the called response method!")
    
            currentPos = headerBytesProcessed
        else:
            currentPos = 0
    
    
        (field, bytesProcessed) = FP_API_DATA_CACHE.enum_DCDataUpdateStatus.deserialize(data, currentPos)
        responseInstance["e__DCDataUpdateStatus__status"] = field
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

            if (fpHeaderInstance.u16ProtoId != self.const_DATA_CACHE_PROTOCOL_ID):
                raise Exception("Unsupported protocol ID", fpHeaderInstance.u16ProtoId)
        else:
            funcId = functionId

        if funcId in self.responseParsersDict:
            respParserFunc = self.responseParsersDict[funcId]
            return respParserFunc(respBytes) if (respParserFunc != None) else None
        else:
            raise Exception('Unsupported function id', hex(funcId))
    ############################################################################################################
    """
    Returns the Protocol version as a string vM.m
    """
    def get_version(self):
        return f'v{self.versionMajor}.{self.versionMinor}'
    ############################################################################################################

