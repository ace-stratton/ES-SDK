'''
    cli.py

    (C) Copyright Endurosat

    Contents and presentations are protected world-wide.
    Any kind of using, copying etc. is prohibited without prior permission.
    All rights, incl. industrial property rights, are reserved.
'''

from typing import Optional
import typer

from es_sys_config import __app_name__, __version__
from es_sys_config.es_sys_config import return_code
from es_sys_config import es_sys_config

app = typer.Typer(add_completion=False)

ALL_OK_MSG = 'Everything went well.'

@app.command()
def generate(
    obc_version: str = typer.Argument(help="Version of the OBC software for which the configuration is intended (e.g. 4.1.0)."),
    configuration: Optional[str] = typer.Option(None, '--config', '-c', help='Configuration string (e.g. 1cynn).'),
    out_filename: Optional[str] = typer.Option(None, '--output', '-o', help='File name to save the generated configuration.'),
    verbose: Optional[bool] = typer.Option(False ,'--verbose', '-v', is_flag=True),
    ):
    if configuration is None:
        generate_return = es_sys_config.generate_interactive(obc_version, out_filename, verbose=verbose)
    else:
        generate_return = es_sys_config.generate_from_configuration(obc_version, configuration, out_filename, verbose=verbose)
    if generate_return != return_code.SUCCESS:
        typer.secho(f'I had a problem because {generate_return.value}', fg=typer.colors.RED,)
        raise typer.Exit(1)
    # All good
    typer.secho(ALL_OK_MSG, fg=typer.colors.GREEN)


@app.command()
def flash(
    obc_version: str = typer.Argument(help="Version of the OBC software for which the configuration is intended (e.g. 4.1.0)."),
    configuration: Optional[str] = typer.Option(None, '--config', '-c', help='Configuration string (e.g. 1cynn).'),
    in_filename: Optional[str] = typer.Option(None, '--input', '-i', help='Binary configuration file to be flashed. Note that the file has to be generated for the same OBC version as the one provided to the flash command.'),
    out_filename: Optional[str] = typer.Option(None, '--output', '-o', help='File name to save the flashed configuration.'),
    verbose: Optional[bool] = typer.Option(False ,'--verbose', '-v', is_flag=True),
    ):
    if (configuration is None) and (in_filename is None):
        flash_return = es_sys_config.flash_interactive(obc_version, out_filename, verbose=verbose)
    elif configuration is not None:
        flash_return = es_sys_config.flash_config(obc_version, configuration, out_filename, verbose=verbose)
    else:
        flash_return = es_sys_config.flash_file(obc_version, in_filename, verbose=verbose)

    if flash_return != return_code.SUCCESS:
        typer.secho(f'I had a problem because {flash_return.value}', fg=typer.colors.RED,)
        raise typer.Exit(1)
    # All good
    typer.secho(ALL_OK_MSG, fg=typer.colors.GREEN)

@app.command()
def read(
    out_filename: Optional[str] = typer.Option(None, '--output', '-o', help='File name to save the read configuration.'),
    verbose: Optional[bool] = typer.Option(False ,'--verbose', '-v', is_flag=True),
    ):

    read_return = es_sys_config.read_configuration(out_filename, verbose=verbose)
    if read_return != return_code.SUCCESS:
        typer.secho(f'I had a problem because {read_return.value}', fg=typer.colors.RED,)
        raise typer.Exit(1)
    # All good
    typer.secho(ALL_OK_MSG, fg=typer.colors.GREEN)

def _version_callback(value: bool) -> None:
    if value:
        typer.echo(f"{__app_name__} v{__version__}")
        raise typer.Exit()

@app.callback()
def main(
    _: Optional[bool] = typer.Option(
        None,
        "--version",
        help="Show the application's version and exit.",
        is_eager=True,
        callback=_version_callback
    )
) -> None:
    return
