'''
    stm32_programmer_cli.py

    (C) Copyright Endurosat

    Contents and presentations are protected world-wide.
    Any kind of using, copying etc. is prohibited without prior permission.
    All rights, incl. industrial property rights, are reserved.
'''

import subprocess
import typer

# STM32_Programmer executable
CLI_EXE = 'STM32_Programmer_CLI'
CONNECT_CMD = '--connect port=SWD'
LOG_CMD = '--log stm32_programmer.log'
START_CMD = '--start 0x08000000'

# Default values
CONFIG_ADDRESS = '0x081C0000'


def obc_connect(log: bool = False, verbose: bool = False) -> bool:
    ''' Try  to connect to the OBC just to check for availability '''

    cmd = f'{CLI_EXE} {get_connect_command(log)}'
    if verbose:
        typer.secho(f'Calling: {cmd}')

    # Run the command and check the result
    cmd_return = subprocess.run(
        cmd, capture_output=True, shell=True, text=True, check=False, encoding="unicode_escape")

    if 'Error' in cmd_return.stdout:
        # Find the error line in the output
        for line in cmd_return.stdout.split('\n'):
            if 'Error' in line:
                raise STM32Exception(line)
    if cmd_return.returncode != 0:
        raise STM32Exception('Failed to run the connect ST-LINK command')

    # Print out the output form the ST-LINK
    typer.secho(cmd_return.stdout)


def obc_flash_config(config_binary: str, log: bool = False, verbose: bool = False) -> bool:
    ''' Flash a configuration file in the OBC '''

    cmd = f'{CLI_EXE} {get_connect_command(log)} {get_write_command(file=config_binary)} {START_CMD}'

    if verbose:
        typer.secho(f'Calling: {cmd}')

    # Run the command and check the result
    cmd_return = subprocess.run(
        cmd, capture_output=True, shell=True, text=True, check=False, encoding="unicode_escape")

    if 'Error' in cmd_return.stdout:
        # Find the error line in the output
        for line in cmd_return.stdout.split('\n'):
            if 'Error' in line:
                raise STM32Exception(line)
    if cmd_return.returncode != 0:
        raise STM32Exception('Failed to run the flash ST-LINK command')

    # Print out the output form the ST-LINK
    typer.secho(cmd_return.stdout)


def obc_read_config(size: int, log: bool = False, verbose: bool = False) -> bytes:
    ''' Read the configuration memory from the OBC and keep it in a file '''

    cmd = f'{CLI_EXE} {get_connect_command(log)} {get_read_command(size=size)} {START_CMD}'

    if verbose:
        typer.secho(f'Calling: {cmd}')

    # Run the command and check the result
    cmd_return = subprocess.run(
        cmd, capture_output=True, shell=True, text=True, check=False, encoding="unicode_escape")

    if 'Error' in cmd_return.stdout:
        # Find the error line in the output
        for line in cmd_return.stdout.split('\n'):
            if 'Error' in line:
                raise STM32Exception(line)
    if cmd_return.returncode != 0:
        raise STM32Exception('Failed to run the read ST-LINK command')

    # Print out the output form the ST-LINK
    typer.secho(cmd_return.stdout)

    return parse_stm32_read_output(cmd_return.stdout)


def parse_stm32_read_output(output_txt: str) -> bytes:
    ''' Parse the ST-LINK output to obtain the configuration bytes '''

    data = ''
    in_data = False
    for line in output_txt.split('\n'):
        # Data starts like this "0x081C0000 : xx xx ..."
        if CONFIG_ADDRESS in line:
            in_data = True
        # It is over with an empty line
        elif line == '':
            in_data = False
        # Collect data ignoring the address (before the ':')
        if in_data:
            data += line.split(':')[-1].strip()

    return bytes.fromhex(data)


def is_stm32_cli_installed(verbose = False) -> bool:
    ''' Verify that STM32_Programmer_CLI can be called '''
    cmd = f'{CLI_EXE} --version'

    if verbose:
        typer.secho(f'Calling {cmd}')
    ret = subprocess.run(cmd,
                    capture_output=True, shell=True, text=True, check=False, encoding="unicode_escape")
    if verbose:
        typer.secho(f'{ret.stdout.strip()}')
        typer.secho(f'{ret.stderr.strip()}', fg=typer.colors.YELLOW)

    return 0 == ret.returncode


def get_connect_command(log: bool = False) -> str:
    ''' Try and connect to a device using SWD port '''

    return f'{CONNECT_CMD} {LOG_CMD}' if log else CONNECT_CMD


def get_write_command(addr: str = CONFIG_ADDRESS, file: str = 'input.bin') -> str:
    ''' Flash in the device's address a binary file '''

    return f'-w {file} {addr}'


def get_upload_command(size: int, addr: str = CONFIG_ADDRESS, file: str = 'output.bin') -> str:
    ''' Read a size of bytes from the memory address and write it in a file '''

    return f'--upload {addr} {size} {file}'


def get_read_command(size: int, addr: str = CONFIG_ADDRESS) -> str:
    ''' Read from the device's address a certain size of bytes '''
    
    return f'-r8 {addr} {size}'


class STM32Exception(Exception):
    pass


if __name__ == '__main__':
    # Expected size 21
    # print(str(obc_read_config(21)))
    # print(obc_flash_config(config_binary='output_ieyyy.bin'))
    verify_stm32_cli_installed()
