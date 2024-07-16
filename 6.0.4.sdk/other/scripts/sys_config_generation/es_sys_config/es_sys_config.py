'''
    es_sys_config.py

    (C) Copyright Endurosat

    Contents and presentations are protected world-wide.
    Any kind of using, copying etc. is prohibited without prior permission.
    All rights, incl. industrial property rights, are reserved.
'''

from enum import Enum
import typer

import es_sys_config.es_sys_config_helpers as helpers
from es_sys_config import __version__
from es_sys_config.es_sys_config_configs import ConfigData, ConfigDataRegistry

import es_sys_config.stm32_programmer_cli as stm32

DEF_FILE_NAME = 'output.bin'

class return_code(Enum):
    SUCCESS = 'All good'
    STM32_EXE_NOT_FOUND = 'I could not find the executable for the STM32 Programmer CLI'
    CONNECTION_ERROR = 'ST-Link could not connect to the device'
    READ_DEVICE_ERROR = 'ST-Link could not read from the device'
    FLASH_DEVICE_ERROR = 'ST-Link  could not flash the device'
    OPEN_FILE_ERROR = 'I could not open the file'
    WRITE_FILE_ERROR = 'I could not write a file'
    INCONSISTENT_LAYOUT_ERROR = 'The configuration layout is inconsistent'

def generate_interactive(obc_version:str, filename, verbose=False) -> return_code:
    ''' Generate a configuration file in a dialogue mode '''

    typer.secho(welcome_banner())

    config_data = ConfigDataRegistry.get_config_for_obc_version(obc_version)
    if config_data is None:
        return return_code.INCONSISTENT_LAYOUT_ERROR

    config_string = generate_config_str(config_data)

    # Make sure there is a file name
    if filename is None:
        filename = 'output_' + config_string + '.bin'
    else:
        filename = helpers.validate_input_filename(filename)

    return generate_config_bin(config_string, config_data, filename, verbose)

def generate_from_configuration(obc_version: str, configuration, filename, verbose=False) -> return_code:
    ''' Generate a configuration file from a given configuration string '''

    typer.secho(welcome_banner())

    # Make sure there is a file name
    if filename is None:
        filename = 'output_' + configuration + '.bin'
    else:
        filename = helpers.validate_input_filename(filename)

    config_data = ConfigDataRegistry.get_config_for_obc_version(obc_version)
    if config_data is None:
        return return_code.INCONSISTENT_LAYOUT_ERROR

    return generate_config_bin(configuration, config_data, filename, verbose)

def generate_config_bin(config_str: str, config_data: ConfigData, output_file: str, verbose=False) -> return_code:
    ''' Generate a binary configuration file based on a configuration string and layout data '''

    config = helpers.PackedConfig(config_data)
    config.set_data(config_str)
    config.update_size()
    config.update_crc()

    if verbose:
        print(config)

    try:
        output_bytes = config.save_to_file(output_file)
    except (FileExistsError, FileNotFoundError):
        typer.secho(f'Could not generate the file {output_file}', fg=typer.colors.RED)
        return return_code.WRITE_FILE_ERROR

    if verbose:
        typer.secho(output_bytes.hex())

    typer.secho(f'Generated configuration file as {output_file}', fg=typer.colors.GREEN)

    return return_code.SUCCESS

def flash_interactive(obc_version: str, filename: str, verbose: bool = False) -> return_code:
    ''' Generate and flash a binary configuration file in a dialogue mode. '''

    # Generate first the configuration string
    config_data = ConfigDataRegistry.get_config_for_obc_version(obc_version)
    if config_data is None:
        return return_code.INCONSISTENT_LAYOUT_ERROR
    config_string = generate_config_str(config_data)

    # Make sure there is a file name
    if filename is None:
        filename = 'output_' + config_string + '.bin'
    else:
        helpers.validate_input_filename(filename)

    # Call generate config file
    ret = generate_config_bin(config_string, config_data, filename, verbose)

    # Flash
    if ret == return_code.SUCCESS:
        ret = flash_file(obc_version, filename, verbose)

    return ret

def flash_config(obc_version: str,config_str: str, filename: str, verbose: bool = False) -> return_code:
    ''' Generate and flash a configuration file from a given configuration string '''

    # Make sure there is a file name
    if filename is None:
        filename = 'output_' + config_str + '.bin'
    else:
        helpers.validate_input_filename(filename)

    config_data = ConfigDataRegistry.get_config_for_obc_version(obc_version)
    if config_data is None:
        return return_code.INCONSISTENT_LAYOUT_ERROR
    # Call generate config file
    ret = generate_config_bin(config_str, config_data, filename, verbose)

    # Flash
    if ret == return_code.SUCCESS:
        ret = flash_file(obc_version, filename, verbose)

    return ret

def flash_file(obc_version: str,filename: str, verbose: bool = False) -> return_code:
    ''' Flash an already generated configuration file '''

    if not stm32.is_stm32_cli_installed():
        return return_code.STM32_EXE_NOT_FOUND

    # Connect ot the OBC
    if verbose:
        typer.secho('Connect to the OBC...')

    try:
        stm32.obc_connect(verbose=verbose)
    except stm32.STM32Exception as exc:
        typer.secho(str(exc), fg=typer.colors.RED)
        return return_code.CONNECTION_ERROR

    if verbose:
        typer.secho(f'OBC ready, flash {filename}')

    # Get the configuration version from the file
    file_version = helpers.read_cfg_version_from_file(filename) 

    # Get the configuration version from the configuration for the requested OBC version
    config_data = ConfigDataRegistry.get_config_for_obc_version(obc_version)
    if config_data is None:
        return return_code.INCONSISTENT_LAYOUT_ERROR
    conf_version = int.from_bytes(config_data.version, "big")

    if conf_version == file_version:
        # File was generated for the requested OBC software version. Proceed with flashing.
        try:
            # Connect and flash the configuration binary
            stm32.obc_flash_config(config_binary=filename, verbose=verbose)
        except stm32.STM32Exception as exc:
            typer.secho(str(exc), fg=typer.colors.RED)
            return return_code.FLASH_DEVICE_ERROR
    else:
        # Mismatch of the configuration data versions indicates data layout mismatch
        typer.secho(f"ERROR! File {filename} is not compatible with version {obc_version}. Please, generate the file again.",
                    fg=typer.colors.RED)

    return return_code.SUCCESS

def read_configuration(output_file: str = None, verbose: bool = False) -> return_code:
    ''' Read the configuration from the OBC flash '''

    if not stm32.is_stm32_cli_installed():
        return return_code.STM32_EXE_NOT_FOUND

    # Read the layout version from OBC
    flashed_layout = helpers.read_cfg_version_from_obc()

    # Select layout configuration for the version
    config_data = ConfigDataRegistry.get_config_for_layout_version(flashed_layout)
    if config_data is None:
        return return_code.INCONSISTENT_LAYOUT_ERROR
    config = helpers.PackedConfig(config_data)

    try:
        configuration_bytes = stm32.obc_read_config(size=config.packed_struct.size, log=False, verbose=verbose)
    except stm32.STM32Exception as exc:
        typer.secho(str(exc), fg=typer.colors.RED)
        return return_code.READ_DEVICE_ERROR

    # Verify that we retrieved successfully
    if len(configuration_bytes) != config.packed_struct.size:
        return return_code.READ_DEVICE_ERROR

    if output_file is not None:
        with open(output_file, 'wb') as output:
            output.write(configuration_bytes)

    # Check for validity
    if not config.configuration_validity_check(configuration_bytes):
        typer.secho('The configuration is not valid. Check the output for more information.', fg=typer.colors.YELLOW)

    return return_code.SUCCESS

def welcome_banner():
    ''' Provide contents of the es_sys_config welcome banner '''

    banner = f'''
    System configuration binary generator {__version__}
    '''

    return banner

def generate_config_str(cfg_data: ConfigData) -> str:
    ''' Generate a configuration string '''

    str_tokens = []

    for module in cfg_data.modules:
        prompt = module.get_prompt()
        token = input(prompt)
        variants = module.get_variant_tokens()
        while token.lower() not in variants:
            token = input(prompt)
        str_tokens.append(token)

    return ''.join([str_tok.lower() for str_tok in str_tokens])
