from jinja2 import Template
import re
import sys

def increment(value):
    value[0] += 1
    return hex(value[0])

eps_bp_fidl_template = """
{%      for eps_bp_instance_id in range(config.eps_bp_count) %}
//
// Global declarations for EPS BP INSTANCE{{eps_bp_instance_id}}
//    
    <** @description: GetBatteryInfo from EPSII_BP_1 interface **>
    struct Eps2Inst{{ eps_bp_instance_id }}BatteryInfoType
    {
        <** @description: [mWh] The capacity of the battery pack.
                         0xFFFFFFFF - Unknown Value
                         0xFFFFFFFE - Error Value**>
        UInt32 Capacity
        <** @description: [mV] Voltage of the battery pack. 
                    Special return values: 
                         0xFFFFFFFF - Unknown Value
                         0xFFFFFFFE - Error Value**>
        UInt16 Voltage
        <** @description: [mA] Negative upon charge, positive upon discharge. 
                    Special return values: 
                         0xFFFF - Unknown Value
                         0xFFFE - Error Value**>

        Int16 Current
        <** @description: [mC] Temperature of the Battery Pack
                    Special return values: 
                         0x7FFF - Unknown Value
                         0x7FFE - Error Value**>
        Int32 Temperature
        <** @description: Current state of the BatteryPack
            0: ROOT - Reserved state
            1: IDENTIFYPREVIOUSSTATE - Reserved state
            2: BATTERY_AVAILABLE - Reserved state
            3: BATTERY - This is the state in which the battery pack is working normally with battery cells attached.
            4: TRANSITION_TO_HIB - This is the state in which the battery pack is working, but in 3 seconds it will switch to HIB(hibernation) mode.
            5: NORMAL - Reserved state
            6: HIB - In this state all consumers are detached and the battery pack tries to charge it's cells and to get back to BATTERY state.
            7: NOHIB - In this state the satellite is working as in Battery state and all SW protection mechanisms are stopped. The only way to leave this mode is to send request "LeaveNoHibMode"
            8: PANEL - At this state the satellite is working only when on sun. The battery cells are detached because of fatal error.
            9: ___HISTORY_BATTERY_AVAILABLE - Reserved state
            **>
        UInt8 bp_mode
    }
    
    <** @description: GetDeviceHealthInfo from EPSII_BP_1 interface **>
    struct Eps2Inst{{ eps_bp_instance_id }}DeviceHealthInfoType
    {
        <** @description: Time after start of the system in seconds.
                    Special return values: 
                         0x7FFFFFFF - Unknown Value
                         0x7FFFFFFE - Error Value**>
        Int32 ActiveCPU_RunningTime
        <** @description: CPU Voltage in [mV]
                    Special return values: 
                         0x7FFFFFFF - Unknown Value
                         0x7FFFFFFE - Error Value**>
        Int32 ActiveCPU_Voltage
        <** @description: CPU temperature in [mC]
                    Special return values: 
                         0x7FFFFFFF - Unknown Value
                         0x7FFFFFFE - Error Value**>
        Int32 ActiveCPU_Temperature
        <** @description: PCB Temperature sensor 1 in [mC]
                    Special return values: 
                         0x7FFFFFFF - Unknown Value
                         0x7FFFFFFE - Error Value**>
        Int32 PCB_Temperature_1
        <** @description: PCB Temperature sensor 2 in [mC]
                    Special return values: 
                         0x7FFFFFFF - Unknown Value
                         0x7FFFFFFE - Error Value**>
        Int32 PCB_Temperature_2
        <** @description: Status of Balancer chip
                    Special return values: 
                         0 - Unknown
                         1 - Online
                         2 - Communication Error
                         3 - Communication Timeout
                         4 - Driver disabled**>
        UInt8 BALANCER_CHIP_1
        <** @description: Status of Primary Input Channel 1
                    Special return values: 
                         0 - Unknown
                         1 - Online
                         2 - Communication Error
                         3 - Communication Timeout
                         4 - Driver disabled**>
        UInt8 LT8491_IC_XP
        <** @description: Status of Redundant Input Channel 1
                    Special return values: 
                         0 - Unknown
                         1 - Online
                         2 - Communication Error
                         3 - Communication Timeout
                         4 - Driver disabled**>
        UInt8 LT8491_IC_XR
        <** @description: Status of Primary Input Channel 2
                    Special return values: 
                         0 - Unknown
                         1 - Online
                         2 - Communication Error
                         3 - Communication Timeout
                         4 - Driver disabled**>
        UInt8 LT8491_IC_YP
        <** @description: Status of Redundant Input Channel 2
                    Special return values: 
                         0 - Unknown
                         1 - Online
                         2 - Communication Error
                         3 - Communication Timeout
                         4 - Driver disabled**>
        UInt8 LT8491_IC_YR
        <** @description: Status of Primary Input Channel 3
                    Special return values: 
                         0 - Unknown
                         1 - Online
                         2 - Communication Error
                         3 - Communication Timeout
                         4 - Driver disabled**>
        UInt8 LT8491_IC_ZP
        <** @description: Status of Redundant Input Channel 3
                    Special return values: 
                         0 - Unknown
                         1 - Online
                         2 - Communication Error
                         3 - Communication Timeout
                         4 - Driver disabled**>
        UInt8 LT8491_IC_ZR
        <** @description: Status of INA sensor 1
                    Special return values: 
                         0 - Unknown
                         1 - Online
                         2 - Communication Error
                         3 - Communication Timeout
                         4 - Driver disabled**>
        UInt8 INA_BAT_OUT_1
        <** @description: Status of INA sensor 2
                    Special return values: 
                         0 - Unknown
                         1 - Online
                         2 - Communication Error
                         3 - Communication Timeout
                         4 - Driver disabled**>
        UInt8 INA_BAT_OUT_2
        <** @description: Status of Temperature sensor 1
                    Special return values: 
                         0 - Unknown
                         1 - Online
                         2 - Communication Error
                         3 - Communication Timeout
                         4 - Driver disabled**>
        UInt8 TMP117_U810
        <** @description: Status of Temperature sensor 2
                    Special return values: 
                         0 - Unknown
                         1 - Online
                         2 - Communication Error
                         3 - Communication Timeout
                         4 - Driver disabled**>
        UInt8 TMP117_U811
        <** @description: Status of GPIO DRIVER 1
                    Special return values: 
                         0 - Unknown
                         1 - Online
                         2 - Communication Error
                         3 - Communication Timeout
                         4 - Driver disabled**>
        UInt8 GPIO_PCA9538_U2001
        <** @description: Status of GPIO DRIVER 2
                    Special return values: 
                         0 - Unknown
                         1 - Online
                         2 - Communication Error
                         3 - Communication Timeout
                         4 - Driver disabled**>
        UInt8 GPIO_PCA9538_U2002
    }

    <** @description: Information provided by INA sensor 1 **>
    struct Eps2Inst{{ eps_bp_instance_id }}InaSensors1Type
    {
        <** @description: Voltage in mV
                    Special return values: 
                         0xFFFF - Unknown Value
                         0xFFFE - Error Value**>
        UInt16 Voltage
        <** @description: Current in mA
                    Special return values: 
                         0x7FFF - Unknown Value
                         0x7FFE - Error Value**>
        Int16 Current
        <** @description: Energy in Watt/h \* 10
                    Special return values: 
                         0x7FFF - Unknown Value
                         0x7FFE - Error Value**>
        Int16 Energy
        <** @description: Temperature in ((degrees in C)\*10)
                    Special return values: 
                         0x7FFF - Unknown Value
                         0x7FFE - Error Value**>
        Int16 Temperature
    }

    <** @description: Information provided by INA sensor 2 **>
    struct Eps2Inst{{ eps_bp_instance_id }}InaSensors2Type
    {
        <** @description: Voltage in mV
                    Special return values: 
                         0xFFFF - Unknown Value
                         0xFFFE - Error Value**>
        UInt16 Voltage
        <** @description: Current in mA
                    Special return values: 
                         0x7FFF - Unknown Value
                         0x7FFE - Error Value**>
        Int16 Current
        <** @description: Energy in Watt/h \* 10
                    Special return values: 
                         0x7FFF - Unknown Value
                         0x7FFE - Error Value**>
        Int16 Energy
        <** @description: Temperature in ((degrees in C)\*10)
                    Special return values: 
                         0x7FFF - Unknown Value
                         0x7FFE - Error Value**>
        Int16 Temperature
    }


    <** @description: Telemetry provided by the Balancer **>
    struct Eps2Inst{{ eps_bp_instance_id }}BalancerInfoType
    {
        <** @description: Voltage in mV
                    Special return values: 
                         0xFFFF - Unknown Value
                         0xFFFE - Error Value**>
        UInt16 Voltage
        <** @description: Current in mA
                    Special return values: 
                         0x7FFF - Unknown Value
                         0x7FFE - Error Value**>
        Int16 Current
        <** @description: Temperature in ((degrees in C)\*10)
                    Special return values: 
                         0x7FFF - Unknown Value
                         0x7FFE - Error Value**>
        Int16 Internal_Temperature
    }    
    
    <** @description: Status provided by the Balancer **>
    struct Eps2Inst{{ eps_bp_instance_id }}BalancerStatusType
    {
        <** @description: Communication state of the charger
                    Return values: 
                         0 - Unknown state
                         1 - Chip Online
                         2 - Error in communication**>
        UInt8 COM_STATE
        <** @description: Description of bits:      
            CUTF (bit7)- The Charge Under-Temperature Fault bit
            COTF (bit6)- The Charge Over-Temperature Fault bit
            DUTF (bit5)- The Discharge Under-Temperature Fault bit
            DOTF (bit4)- The Discharge Over-Temperature Fault bit
            UVLOF(bit3)- The Undervoltage Lockout Fault bit
            UVF  (bit2)- The Undervoltage Fault bit
            OVLOF(bit1)- The Overvoltage Lockout Fault bit
            OVF  (bit0)- The Overvoltage Fault bit **>
            UInt8  status_register_0
            
        <** @description: Description of bits:
            VEOC (bit7)- The Voltage End-of-Charge detection bit
            RSV  (bit6)- Reserved
            OWF  (bit5)- The Open-Wire Fault bit
            CELLF(bit4)- The Cell Fail fault bit
            DSCF (bit3)- The Discharge Short Circuit Fault bit
            DOCF (bit2)- The Discharge Overcurrent Fault bit
            COCF (bit1)- The Charge Overcurrent Fault bit
            IOTF (bit0)- The Internal Over-Temperature Fault bit **>
            UInt8  status_register_1
            
        <** @description: Description of bits:
            LVCHG    (bit7)- The Low Voltage Charge bit
            INT_SCAN (bit6)- The Internal Scan bit
            ECC_FAIL (bit5)- Error Checking/detection/Correction for EEPROM read
            ECC_USED (bit4)- Error Checking/detection/Correction for EEPROM read
            DCHING   (bit3)- The Discharging bit
            CHING    (bit2)- The Charging bit
            CH_PRSNT (bit1)- The Charger Present bit
            LD_PRSNT (bit0)- The Load Present bit **>
            UInt8  status_register_2
            
        <** @description: Description of bits:
            RSV       (bit7)- Reserved
            IN_SLEEP  (bit6)- The In SLEEP Mode bit
            IN_DOZE   (bit5)- The In DOZE Mode bit
            IN_IDLE   (bit4)- The In IDLE Mode bit
            CBUV      (bit3)- The Cell Balance Undervoltage bit
            CBOV      (bit2)- The Cell Balance Overvoltage bit
            CBUTF     (bit1)- The Cell Balance Under-Temperature Fault bit
            CBOTF     (bit0)- The Cell Balance Over-Temperature Fault bit **>
            UInt8  status_register_3
    }

    <** @description: Balancer Cells info **>
    struct Eps2Inst{{ eps_bp_instance_id }}BalancerCellsInfoType
    {
        <** @description: CELL voltage [mV]
                    Special return values: 
                         0xFFFF - Unknown Value
                         0xFFFE - Error Value**>
        UInt16 Cell_1
        <** @description: CELL voltage [mV]
                    Special return values: 
                         0xFFFF - Unknown Value
                         0xFFFE - Error Value**>
        UInt16 Cell_2
        <** @description: CELL voltage [mV]
                    Special return values: 
                         0xFFFF - Unknown Value
                         0xFFFE - Error Value**>
        UInt16 Cell_3
        <** @description: CELL voltage [mV]
                    Special return values: 
                         0xFFFF - Unknown Value
                         0xFFFE - Error Value**>
        UInt16 Cell_4
        <** @description: CELL voltage [mV]
                    Special return values: 
                         0xFFFF - Unknown Value
                         0xFFFE - Error Value**>
        UInt16 Cell_5
        <** @description: CELL voltage [mV]
                    Special return values: 
                         0xFFFF - Unknown Value
                         0xFFFE - Error Value**>
        UInt16 Cell_6
        <** @description: CELL voltage [mV]
                    Special return values: 
                         0xFFFF - Unknown Value
                         0xFFFE - Error Value**>
        UInt16 Cell_7
        <** @description: CELL voltage [mV]
                    Special return values: 
                         0xFFFF - Unknown Value
                         0xFFFE - Error Value**>
        UInt16 Cell_8
    }
    
    
    {% for charger_id in config.charger_ids %}
    <** @description: Charger info **>
    struct Eps2Inst{{ eps_bp_instance_id }}Charger{{charger_id}}Type
    {
        <** @description: Communication state of the charger
                    Return values: 
                         0 - Unknown state
                         1 - Chip Online
                         2 - Error in communication**>
        UInt8 COM_STATE
        <** @description: Raw register value 
        Description of bits:
            RSV         (bit7 - bit 5)- Reserved
            VIN_UVLO    (bit4)- The In SLEEP Mode bit
            PS_OR_SOLAR (bit3)- The In DOZE Mode bit
            SOLAR_STATE (bit0 - bit2)-  101 - Battery Limited
                                        100 - Full Panel Scan
                                        011 - Perturb and Observe
                                        010 - LP Mode and VIN Pulsing
                                        001 - LP Mode and VIN too low
                                        000 - None of the Above **>
        UInt16 STAT_SUPPLY
        <** @description: Calculated power delivered out of the charger. **>
        UInt16 TELE_POUT
        <** @description: Calculated power drawn from the charger's supply. **>
        UInt16 TELE_PIN
        <** @description: Calculated power delivered out of the charger. **>
        UInt16 TELE_IOUT
        <** @description: Input current from VIN. **>
        UInt16 TELE_IIN
        <** @description: The most recently measured VBAT voltage as measured at the FBOR pin. **>
        UInt16 TELE_VBAT
        <** @description: The most recently measured VIN voltage as measured at the VINR pin. **>
        UInt16 TELE_VINR
    }
    {% endfor %}
{%-     endfor %}    
"""

eps_bp_fdepl_template = """
{%      for eps_bp_instance_id in range(config.eps_bp_count) %}
//
// Global declarations for EPS BP INSTANCE{{eps_bp_instance_id}}
//    
    attribute EPS2_BP_INST{{ eps_bp_instance_id }}_BP_INFO_Data { Status_timeout = 30000 }
    attribute EPS2_BP_INST{{ eps_bp_instance_id }}_DEVICE_HEALTH_INFO_Data { Status_timeout = 30000 }
    attribute EPS2_BP_INST{{ eps_bp_instance_id }}_INA_SENSOR1_Data { Status_timeout = 30000 }
    attribute EPS2_BP_INST{{ eps_bp_instance_id }}_INA_SENSOR2_Data { Status_timeout = 30000 }
    attribute EPS2_BP_INST{{ eps_bp_instance_id }}_BALANCER_INFO_Data { Status_timeout = 30000 }
    attribute EPS2_BP_INST{{ eps_bp_instance_id }}_BALANCER_STATUS_Data { Status_timeout = 30000 }
    attribute EPS2_BP_INST{{ eps_bp_instance_id }}_BALANCER_CELLS_INFO_Data { Status_timeout = 30000 }
    attribute EPS2_BP_INST{{ eps_bp_instance_id }}_CHARGER_XP_Data { Status_timeout = 30000 }
    attribute EPS2_BP_INST{{ eps_bp_instance_id }}_CHARGER_XR_Data { Status_timeout = 30000 }
    attribute EPS2_BP_INST{{ eps_bp_instance_id }}_CHARGER_YP_Data { Status_timeout = 30000 }
    attribute EPS2_BP_INST{{ eps_bp_instance_id }}_CHARGER_YR_Data { Status_timeout = 30000 }
    attribute EPS2_BP_INST{{ eps_bp_instance_id }}_CHARGER_ZP_Data { Status_timeout = 30000 }
    attribute EPS2_BP_INST{{ eps_bp_instance_id }}_CHARGER_ZR_Data { Status_timeout = 30000 }
{%-     endfor %}    
"""

eps_bp_datacache_fidl_template = """
{%      for eps_bp_instance_id in range(config.eps_bp_count) %}
//
// Global declarations for EPS BP INSTANCE{{eps_bp_instance_id}}
//
    <** @description: Battery Info
        @details: id = {{ increment(datacache_data_id) }}
    **>
    attribute Eps2Inst{{ eps_bp_instance_id }}BatteryInfoType EPS2_BP_INST{{ eps_bp_instance_id }}_BP_INFO_Data
    
    <** @description: Battery pack device health info
        @details: id = {{ increment(datacache_data_id) }}
    **>
    attribute Eps2Inst{{ eps_bp_instance_id }}DeviceHealthInfoType EPS2_BP_INST{{ eps_bp_instance_id }}_DEVICE_HEALTH_INFO_Data
    
    <** @description: INA Sensor 1 data
        @details: id = {{ increment(datacache_data_id) }}
    **>
    attribute Eps2Inst{{ eps_bp_instance_id }}InaSensors1Type EPS2_BP_INST{{ eps_bp_instance_id }}_INA_SENSOR1_Data
    
    <** @description: INA Sensor 2 data
        @details: id = {{ increment(datacache_data_id) }}
    **>
    attribute Eps2Inst{{ eps_bp_instance_id }}InaSensors2Type EPS2_BP_INST{{ eps_bp_instance_id }}_INA_SENSOR2_Data
    
    <** @description: Balancer info
        @details: id = {{ increment(datacache_data_id) }}
    **>
    attribute Eps2Inst{{ eps_bp_instance_id }}BalancerInfoType EPS2_BP_INST{{ eps_bp_instance_id }}_BALANCER_INFO_Data
    
    <** @description: Balancer status
        @details: id = {{ increment(datacache_data_id) }}
    **>
    attribute Eps2Inst{{ eps_bp_instance_id }}BalancerStatusType EPS2_BP_INST{{ eps_bp_instance_id }}_BALANCER_STATUS_Data
    
    <** @description: Balancer Cells info
        @details: id = {{ increment(datacache_data_id) }}
    **>
    attribute Eps2Inst{{ eps_bp_instance_id }}BalancerCellsInfoType EPS2_BP_INST{{ eps_bp_instance_id }}_BALANCER_CELLS_INFO_Data
    
    {% for charger_id in config.charger_ids %}

    <** @description: Input Charger {{charger_id | upper}} info
        @details: id = {{ increment(datacache_data_id) }}
    **>
    attribute Eps2Inst{{ eps_bp_instance_id }}Charger{{ charger_id }}Type  EPS2_BP_INST{{ eps_bp_instance_id }}_CHARGER_{{charger_id | upper}}_Data
    {% endfor %}
    
{%-     endfor %}    
"""

eps_bp_cfg_code_template = """
//
// Global declarations for EPS BP INSTANCE{{eps_bp_instance_name}}
//
#define EPS_BP_CONFIGURATION \\{% for eps_bp_instance_id in range(config.eps_bp_count) %}
{\\
        .p_address = &eps_bp_mac_address[{{ eps_bp_instance_id }}],\\
        .datacache_cmd_list = { \\
            DC_DID_EPS2_BP_INST{{ eps_bp_instance_id }}_BP_INFO_DATA, \\
            DC_DID_EPS2_BP_INST{{ eps_bp_instance_id }}_DEVICE_HEALTH_INFO_DATA,\\
            DC_DID_EPS2_BP_INST{{ eps_bp_instance_id }}_INA_SENSOR1_DATA,\\
            DC_DID_EPS2_BP_INST{{ eps_bp_instance_id }}_INA_SENSOR2_DATA,\\
            DC_DID_EPS2_BP_INST{{ eps_bp_instance_id }}_BALANCER_INFO_DATA,\\
            DC_DID_EPS2_BP_INST{{ eps_bp_instance_id }}_BALANCER_STATUS_DATA,\\
            DC_DID_EPS2_BP_INST{{ eps_bp_instance_id }}_BALANCER_CELLS_INFO_DATA,\\
            DC_DID_EPS2_BP_INST{{ eps_bp_instance_id }}_CHARGER_XP_DATA,\\
            DC_DID_EPS2_BP_INST{{ eps_bp_instance_id }}_CHARGER_XR_DATA,\\
            DC_DID_EPS2_BP_INST{{ eps_bp_instance_id }}_CHARGER_YP_DATA,\\
            DC_DID_EPS2_BP_INST{{ eps_bp_instance_id }}_CHARGER_YR_DATA,\\
            DC_DID_EPS2_BP_INST{{ eps_bp_instance_id }}_CHARGER_ZP_DATA,\\
            DC_DID_EPS2_BP_INST{{ eps_bp_instance_id }}_CHARGER_ZR_DATA\\
        }\\
}{% if not loop.last %},{% endif %}\\
{%-     endfor %}
"""

obc_fidl_template =  """<** @description: EPS Battery Pack IDs. Here is an extensive list of all possible IDs of the BPs in a system. 
    Depending on count of the EPS BPs in the specific configuration only the first N of those will be used. **>
    enumeration EpsBpIdType
    {
{%      for eps_bp_instance_id in range(config.eps_bp_count) %}    
        <** @description:  EPS Battery Pack ID  **>
        EPS_BP_{{ eps_bp_instance_id }}{% if not loop.last %},{% endif %}
{%-     endfor %}        
    }
"""

j2_fidl_template = Template(eps_bp_fidl_template)
j2_fdepl_template = Template(eps_bp_fdepl_template)
j2_datacache_fidl_template = Template(eps_bp_datacache_fidl_template)
j2_bp_cfg_code_template = Template(eps_bp_cfg_code_template)
j2_obc_fidl_template = Template(obc_fidl_template)
import re

def replace_section_in_file(file_path, new_content):
    # Define the start and end markers for the section to be replaced
    begin_marker = "// begin EPS BP generated code"
    end_marker = "// end EPS BP generated code"

    # Read the content of the file
    with open(file_path, 'r') as file:
        content = file.read()

    # Create the regex pattern to match the section
    pattern = re.compile(f"{begin_marker}.*?{end_marker}", re.DOTALL)

    # Replace the matched section with the new content
    new_section = f"{begin_marker}\n{new_content}\n{end_marker}"
    modified_content = pattern.sub(new_section, content)

    # Write the modified content back to the file
    with open(file_path, 'w') as file:
        file.write(modified_content)

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 5:
        print(f"Usage: {sys.argv[0]} <eps_bp_count> <datacache_folder> <cfg_code_file> <nvm_bp_fidl_file_path>")
        sys.exit(1)

    eps_bp_count = int(sys.argv[1])
    fidl_file_path = sys.argv[2]+"/DataCacheTypes.fidl"
    fdepl_file_path = sys.argv[2]+"/deploy_dc.fdepl"
    datacache_fidl_file_path = sys.argv[2] + "/DataCache.fidl"  
    cfg_code_file = sys.argv[3]
    nvm_bp_fidl_file = sys.argv[4]
    
    data = {
        "config": {"eps_bp_count": eps_bp_count, 
                   "charger_ids" : ["Xp", "Xr", "Yp", "Yr", "Zp", "Zr"]}
        
    }
    
    replace_section_in_file(fidl_file_path, j2_fidl_template.render(data))
    replace_section_in_file(fdepl_file_path, j2_fdepl_template.render(data))
    
    initial_value = [0x100]
    replace_section_in_file(datacache_fidl_file_path, j2_datacache_fidl_template.render(data, datacache_data_id = initial_value, increment=increment))
    
    replace_section_in_file(cfg_code_file, j2_bp_cfg_code_template.render(data))
    replace_section_in_file(nvm_bp_fidl_file, j2_obc_fidl_template.render(data))
