#*- ***************************************************************************************
# * @file     __main__.py
# * @author
# * @brief    RP To-Do entry point script.
# *****************************************************************************************
# * @copyright         (C) Copyright Endurosat
# *
# *          Contents and presentations are protected world-wide.
# *          Any kind of using, copying etc. is prohibited without prior permission.
# *          All rights, incl. industrial property rights, are reserved.
#-* ***************************************************************************************

from es_sys_config import cli, __app_name__

def main():
    ''' To be called from the command line command '''
    cli.app(prog_name=__app_name__)

if __name__ == "__main__":
    main()
