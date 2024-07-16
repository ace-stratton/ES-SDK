'''
    macaron.py

    Build front-end for the OBC Standard Platform

    It expects to have
     - 'java.exe' in the path or at least ESPF_JAVA_EXE defined in the environment.
     - ESPF_ROOT_BUILD_PATH or it defaults to the parent folder of macaron.py

'''
import ctypes
import pathlib
import sys
import os
import subprocess
import re
import shutil
import argparse
from pathlib import Path
import logging
import time

log = logging.getLogger("macaron_logger")


class config:
    MACARON_VMAJOR: int = 0
    MACARON_VMINOR: int = 3

    LOG_FILE_NAME = "macaron.log"

    JAVA_EXE = "java"
    ESPF_JAVA_EXE_ENV_VAR = "ESPF_JAVA_EXE"

    BUILD_CONFIGURATIONS = [
        'debug',
        'release',
        'noboot_debug',
        'noboot_release',
    ]

    VERSION_FILE = '../version'
    DEFAULT_VERSION_STR = '99.99.99-dev'

    FILES_TO_IGNORE_ON_CMD_CLEAN = [
        'arm_toolchain.cmake',
        'build.py',
        Path(sys.argv[0]).resolve().name,
        LOG_FILE_NAME,
        'CMakeLists.txt',
        'GlobalConfig.h.in',
        'readme.txt',
        'build_options.h.tmpl',
        'espf.cmake',
    ]

    def __new__(cls):
        if not hasattr(cls, 'instance'):
            cls.instance = super(config, cls).__new__(cls)

        return cls.instance

    def __init__(self):
        if not hasattr(self, 'init_done'):
            self.init_done = True

            self.ROOT_BUILD_PATH = config.get_build_root_path()
            self.macchiato_path = self.ROOT_BUILD_PATH / 'other/scripts/gen/macchiato/macchiato.jar'
            self.tools_path = self.ROOT_BUILD_PATH / 'other/tools'
            self.args = None

    def set_args(self, cfg_args) -> None:
        self.args = cfg_args

    def get_args(self):
        return self.args

    @staticmethod
    def get_build_root_path() -> Path:
        # Try to get the root path from the environment variable
        root_build_env_var_name = "ESPF_ROOT_BUILD_PATH"
        env_setting = os.getenv(root_build_env_var_name)

        if env_setting is not None:
            try:
                result = Path(env_setting).resolve(strict=True)
                return result
            except FileNotFoundError as exc:
                raise FileNotFoundError(
                    f'{root_build_env_var_name} environment variable contains an invalid folder `{env_setting}`. Please set it to the build folder of your root CMakeLists.txt file.'
                ) from exc
        else:
            # Return the parent folder as default
            default_path = Path(sys.path[0]).parent.resolve()
            log.warning(
                f'{root_build_env_var_name} environment variable not set. Using default path setting resolving to "{default_path}".'
            )
            return default_path

    @staticmethod
    def get_gs_emulation_exe() -> str:
        bundler_exe_name = 'GSEmulation'

        if os.name == 'nt':
            bundler_exe_name += '.exe'

        return str(Path(config.instance.tools_path, bundler_exe_name).resolve())

    @staticmethod
    def get_bundler_exe() -> str:
        bundler_exe_name = 'bundler-amd64-0.19-rc2'

        if os.name == 'nt':
            bundler_exe_name += '.exe'

        return str(Path(config.instance.tools_path, bundler_exe_name).resolve())

    @staticmethod
    def get_java_exe() -> str:
        java_file_name = config.JAVA_EXE

        if os.name == 'nt':
            java_file_name += '.exe'

        if not os.getenv(config.ESPF_JAVA_EXE_ENV_VAR):
            log.warning(
                f'{config.ESPF_JAVA_EXE_ENV_VAR} environment variable not set. Will use `{java_file_name}` from the system path if available!'
            )
            return java_file_name

        java_exe_user_env = os.getenv(config.ESPF_JAVA_EXE_ENV_VAR)

        if os.path.isfile(java_exe_user_env):
            return java_exe_user_env

        log.warning(
            f'`{java_exe_user_env}` specified by the `{config.ESPF_JAVA_EXE_ENV_VAR}` environment variable is not a valid file path. Will use `{java_file_name}` from the system path if available!'
        )
        return java_file_name

    @staticmethod
    def get_macchiato_base_cmd() -> list[str]:
        macchiato_cmd = [config.get_java_exe(), '-jar', str(config().macchiato_path.resolve())]

        return macchiato_cmd

    @staticmethod
    def get_version() -> str:
        return f'v{config.MACARON_VMAJOR}.{config.MACARON_VMINOR}'


class macaron_utils:
    @staticmethod
    def find_file(root_folder: Path, fname: str) -> list:
        return list(root_folder.rglob(fname))

    @staticmethod
    def fp_common_cleanup(root_folder: Path) -> None:
        fp_common_list = list(root_folder.rglob('FP_Common'))

        for entry in fp_common_list:
            if entry.is_dir:
                shutil.rmtree(entry.resolve(), ignore_errors=True)

    @staticmethod
    def clean_directories_by_name(root_folder: Path, dir_name: str) -> None:
        log.info(f'cleaning up all directories with name "{dir_name}" under "{root_folder.resolve()}"...')

        fs_entries_list = list(root_folder.rglob(dir_name))

        for entry in fs_entries_list:
            if entry.is_dir:
                shutil.rmtree(entry.resolve(), ignore_errors=True)

    crc32_tab : list[int] = [
        0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
    	0xe963a535, 0x9e6495a3,	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
    	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
    	0xf3b97148, 0x84be41de,	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
    	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,	0x14015c4f, 0x63066cd9,
    	0xfa0f3d63, 0x8d080df5,	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
    	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,	0x35b5a8fa, 0x42b2986c,
    	0xdbbbc9d6, 0xacbcf940,	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
    	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
    	0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
    	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,	0x76dc4190, 0x01db7106,
    	0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
    	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
    	0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
    	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
    	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
    	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
    	0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
    	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
    	0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
    	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
    	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
    	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
    	0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
    	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
    	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
    	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
    	0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
    	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
    	0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
    	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
    	0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
    	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
    	0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
    	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
    	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
    	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
    	0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
    	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
    	0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
    	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
    	0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
    	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
    ]

    @staticmethod
    def py_crc32(crc: ctypes.c_uint32, buf: bytes) -> int:
        buf = bytes(buf)
        crc = ctypes.c_uint32(~crc)

        for p in buf:
            crc.value = (macaron_utils.crc32_tab[(crc.value & 0xFF) ^ p] ^ (crc.value >> 8)) & 0xFFFFFFFF

        return ~crc.value & 0xFFFFFFFF

    @staticmethod
    def add_boot_crc_to_bin(bin_path: Path, crc_bin_path: Path) -> None:
        bin_crc: ctypes.c_uint32 = 0

        if bin_path.exists():
            if crc_bin_path.exists():
                os.remove(crc_bin_path.resolve())

            crc_f = open(crc_bin_path.resolve(), "wb")
            # write a dummy CRC which we will update after calculation is finished
            crc_f.write(bytes(4))

            with open(bin_path.resolve(), "rb") as bin_f:
                while True:
                    data = bin_f.read(2048)
                    # directly copy to output file
                    crc_f.write(data)

                    if not data:
                        break

                    bin_crc = macaron_utils.py_crc32(bin_crc, data)

            # update CRC at beginning of file (bootloader expects an Intel byte-order (LE))
            crc_f.seek(0)
            crc_f.write(bin_crc.to_bytes(4, byteorder='little'))
            crc_f.close()
        else:
            log.error(f'File {bin_path} does not exist!')

    @staticmethod
    def bundle_app_binary(bin_path: Path) -> str:
        if bin_path.exists():
            bundle_fname = str(bin_path.resolve()) + '.bun'

            cmd_list = [
                config.get_bundler_exe(),
                '-firmware-file',
                str(bin_path.resolve()),
                '-output-file',
                bundle_fname,
                '-module-type',
                '0',
                '-sub-module',
                '0',
                '-flags',
                '0',
                '-fw-type',
                '1',
                '-fw-ver-maj',
                '0',
                '-fw-ver-min',
                '0'
            ]

            commands.run_cmd(cmd_list)
        else:
            log.error(f'Specified binary file {str(bin_path.resolve())} does not exist! Bundle file was not created!')
            bundle_fname = ''

        return bundle_fname

    @staticmethod
    def bundle_schedule_binary(bin_path: Path) -> str:
        if bin_path.exists():
            bundle_fname = str(bin_path.resolve()) + '.bun'

            cmd_list = [
                config.get_bundler_exe(),
                '-firmware-file',
                str(bin_path.resolve()),
                '-output-file',
                bundle_fname,
                '-module-type',
                '0',
                '-sub-module',
                '2',
                '-flags',
                '256',
            ]

            commands.run_cmd(cmd_list)
        else:
            log.error(f'Specified binary file {str(bin_path.resolve())} does not exist! Bundle file was not created!')
            bundle_fname = ''

        return bundle_fname


class commands:
    CMD_PROMPT = '> '

    @staticmethod
    def print_cmd_info(info: str) -> None:
        log.info(f'{commands.CMD_PROMPT} {info}')

    @staticmethod
    def run_cmd(cmd_list: list[str], working_folder: str = None) -> None:
        ret_code = 0

        if config().get_args().verbose:
            commands.print_cmd_info(f'starting command: "{" ".join(cmd_list)}"...')

        if config().get_args().error_out_only:
            process = subprocess.Popen(
                cmd_list, cwd=working_folder, stdout=subprocess.DEVNULL, stderr=subprocess.PIPE, text=True
            )

            if process.stderr:
                raise Exception(f'Some errors occurred:\n{process.stderr}')
        else:
            process = subprocess.Popen(
                cmd_list, cwd=working_folder, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True
            )

        while True:
            line = process.stdout.readline().replace('\n', '').replace('\r', '')
            if line != '':
                log.debug("\t%s", line)

            ret_code = process.poll()

            if line == '' and ret_code is not None:
                break

        if ret_code == 0:
            commands.print_cmd_info('command finished successfully!')
        else:
            cmd = ' '.join(cmd_list)

            for err in process.stderr:
                log.error("\t%s", err.replace('\n', '').replace('\r', ''))

            raise Exception(f'command "{cmd}" failed with code: {ret_code}')

    @staticmethod
    def clean_build():
        try:
            files = [f for f in os.listdir(os.path.curdir)]

            for f in files:
                if f not in config().FILES_TO_IGNORE_ON_CMD_CLEAN:
                    if os.path.isfile(f):
                        log.info('deleting file: {}'.format(f))
                        os.remove(f)
                    elif os.path.isdir(f):
                        log.info('deleting dir: {}'.format(f))
                        shutil.rmtree(f, ignore_errors=True)
        except Exception as ex:
            log.exception(ex)

    @staticmethod
    def run_build(configuration: str) -> None:
        # Set environment variable to generate compile_commands.json
        os.putenv('CMAKE_EXPORT_COMPILE_COMMANDS', '1')

        cmake_gen = ['cmake', '.', '-G', 'Ninja Multi-Config', '-DCMAKE_TOOLCHAIN_FILE=arm_toolchain.cmake']
        cmake_build = ['cmake', '--build', '.', '--config', configuration]

        with open('build_cfg.cmake', "w") as f:
            f.write(f'set(BUILD_CFG_NAME "{configuration}")')

        commands.run_cmd(cmake_gen)
        commands.run_cmd(cmake_build)

    @staticmethod
    def run_macchiato(macchiato_args: str, fdepl_file: str) -> None:
        if config().macchiato_path.exists():
            fp = Path(fdepl_file)

            if fp.exists():
                macchiato_cmd = config.get_macchiato_base_cmd()
                macchiato_cmd.extend([macchiato_args, str(fp.resolve())])

                log.info('generating sources...')
                commands.run_cmd(macchiato_cmd, str(fp.parent.resolve()))
            else:
                raise Exception(f'Could not find deployment file "{fdepl_file}"!')
        else:
            raise Exception(
                f'macchiato.jar does not seem to be existing at the configured location: "{config().macchiato_path.parent}"!'
            )

    @staticmethod
    def run_macchiato_merge(fdepl_file: Path, fp_base_folder_user: Path) -> None:
        fp_base_folder = fp_base_folder_user.resolve()

        if not fp_base_folder.exists():
            os.mkdir(fp_base_folder)

        macchiato_cmd = config.get_macchiato_base_cmd()
        macchiato_cmd.extend(["--gen-c", str(fdepl_file.resolve()), '--merge', fp_base_folder.resolve()])

        generated_files_folder = fdepl_file.parent.resolve()

        commands.run_cmd(macchiato_cmd, generated_files_folder)

        macaron_utils.fp_common_cleanup(fp_base_folder)

    @staticmethod
    def run_flash_app(in_file: Path, dongle_com_port : str, obc_mac_addr : int, is_simple_binary : bool = False, resume_transfer : bool = False, session_id : int = 1, is_fw_file: bool = False) -> None:
        bundle_name = str(in_file.resolve())

        if (is_simple_binary and is_fw_file):
            # the following steps are performed by the bundler already
            # crc_bin_fname = Path(in_file.parent.resolve(), os.path.basename(in_file) + '.crc')
            # macaron_utils.add_boot_crc_to_bin(in_file, crc_bin_fname)
            bundle_name = macaron_utils.bundle_app_binary(in_file)
        
        
        # Add the port name if we are running on linux
        port_name = None
        if sys.platform in ('linux', 'linux2', 'darwin'):

            port_name_match = re.match(r'(/dev/tty\w+)(\d+)$', dongle_com_port)
            if port_name_match:
                port_name = port_name_match.group(1)
                dongle_com_port = port_name_match.group(2)
            else:
                raise RuntimeError("invalid com port supplied, example com port -> '/dev/ttyXXX'")

        if bundle_name != '':
            gs_emul_cmd_list = [
                config.instance.get_gs_emulation_exe(),
                '--com',
                dongle_com_port,
                '--protocol',
                'FWUPD',
                '--network-type',
                'RS485',
                '--test-type',
                '0',
                '--source-addr',
                '1',
                '--dest-module-addr',
                str(obc_mac_addr),
                '--satellite-id',
                '0',
                '--input-file',
                bundle_name,
                '--verbose',
                '1'
            ]

            if port_name is not None:
                gs_emul_cmd_list.extend(['--com-name', port_name])

            if resume_transfer:
                gs_emul_cmd_list.extend(['--tl_packet-id', str(session_id)])

            log.info(f'starting bundle app flash procedure: "{" ".join(gs_emul_cmd_list)}"')

            commands.run_cmd(gs_emul_cmd_list)


class config_file_updater:
    def __init__(self, version_file: str):
        self.version_file: Path = Path(version_file)

    def create_build_version_file(self, version: str):
        # Overwrite the version file with the new version string
        with open(self.version_file, 'w', encoding='utf-8') as h_version:
            h_version.write(version)

        log.info(f'"{self.version_file.resolve()}" updated!')

    def default_build_version_file(self):
        ''' Update the version file with the return of the command default_build_version_file '''
        git_describe_cmd = ['git', 'describe', '--tags']
        with open(self.version_file, 'w', encoding='utf-8') as h_version:
            try:
                subprocess.run(git_describe_cmd, stdout=h_version, check=True)
            except (subprocess.CalledProcessError, FileNotFoundError):
                log.warning(f'Failed to get version string from git, using default version {config.DEFAULT_VERSION_STR}.')
                h_version.write(config.DEFAULT_VERSION_STR)

    class build_version_action(argparse.Action):
        BUILD_VERSION_REGEX = '^[0-9]{1,2}\\.[0-9]{1,2}\\.[0-9]{1,2}(\\-[a-zA-Z0-9_-]+)?$'

        def __init__(self, option_strings, dest, nargs=None, **kwargs):
            if nargs is not None:
                raise ValueError('multiple version tags not allowed')
            super().__init__(option_strings, dest, **kwargs)

        def __call__(self, parser, namespace, values, option_string=None):
            if re.search(config_file_updater.build_version_action.BUILD_VERSION_REGEX, values):
                setattr(namespace, self.dest, values)
            else:
                raise ValueError(
                    'Release version shall use the following format: \n\t<1/2 digits>.<1/2 digits>.<1/2 digits>[-<alphanumerical text (\'_\' is allowed)>]'
                )


def print_ascii_art():
    print(r"""
   ____ ___  ____ __________ __________  ____
  / __ `__ \/ __ `/ ___/ __ `/ ___/ __ \/ __ \
 / / / / / / /_/ / /__/ /_/ / /  / /_/ / / / /
/_/ /_/ /_/\__,_/\___/\__,_/_/   \____/_/ /_/ """ + str(config.get_version()))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='macaron is a tasty build front-end for OBC SDK which makes life sweeter by automating build and generation tasks for end users leaving more time for star gazing and day dreaming')

    build_args_group = parser.add_argument_group('build-args')
    build_args_group.add_argument('-b', '--build', choices=config.BUILD_CONFIGURATIONS,
                                  help='executes the CMake OBC build')
    build_args_group.add_argument(
        '-rv', '--release-ver', type=str, action=config_file_updater.build_version_action)
    parser.add_argument('-c', '--clean', action='store_true', help='cleans all build artifacts')
    parser.add_argument('--clean-gen-content', type=pathlib.Path,
                        default=Path("."), help='cleans up all macchiato-generated folders in the specified folder')
    parser.add_argument('-fp', '--fp-gen', action='store_true',
                        help='calls macchiato for C generation with merge')
    parser.add_argument('-datacache', '--datacache-gen', action='store_true',
                        help='calls macchiato for DataCache generation; note that if used in combination with the -fp option, it will just be ignored')
    parser.add_argument('-fpa', '--fp-gen-all', action='store_true',
                        help='calls macchiato to perform C code generation for all deployment configurations in the project')
    parser.add_argument('-dc', '--depl-config', type=str,
                               default="", help='provides an fdepl configuration file name to use with macchiato')
    parser.add_argument('-fmr', '--fp-merge-root', type=pathlib.Path,
                        default=Path("."), help='specifies the merge root path used by macchiato to search for generated code to merge with')
    parser.add_argument('-v', '--verbose', action='store_true',
                        help='activates printing of command line being executed')
    parser.add_argument('--error-out-only', action='store_true',
                        help='prints only errors on the command line while any other command output is suppressed')
    parser.add_argument('-rl', '--reset-log', action='store_true',
                        help='starts with a clean trace log file instead of appending to the existing log file')

    flash_args_group = parser.add_argument_group('flash-args')
    flash_args_group.add_argument('--flash-bin', type=pathlib.Path, help='prepares an application flash bundle and transfers it to the OBC board for update')
    flash_args_group.add_argument('--flash-bun', type=pathlib.Path, help='transfers the specified application bundle file to the OBC board for update')
    flash_args_group.add_argument('--upload-bun-file', type=pathlib.Path, help='transfers the specified file to the OBC')
    flash_args_group.add_argument('--session-id', type=int, help='specifies a session id which can be used later to continue an interrupted transfer')
    flash_args_group.add_argument('--dongle-port', type=str, help='specifies the EnduroSat ESPS dongle serial port number to use (for Windows that would be only the port id, e.g. in case of COM6, specify "6" here)')
    flash_args_group.add_argument('--obc-mac-addr', type=int, default = 0x33, help='specifies the OBC ESPS MAC address (default is 0x33)')
    flash_args_group.add_argument('--create-app-bundle', type=pathlib.Path, help='specifies the name of the binary from which to create an application bundle for flashing the OBC')
    flash_args_group.add_argument('--create-schedule-bundle', type=pathlib.Path, help='specifies the name of the binary from which to create a schedule file bundle for uploading to the OBC')

    if len(sys.argv) == 1:
        print_ascii_art()
        parser.print_help(sys.stderr)
        sys.exit(1)

    try:
        args = parser.parse_args()

        fh = logging.FileHandler(f'{config.LOG_FILE_NAME}', mode="a" if not args.reset_log else "w")
        fh.setLevel(logging.DEBUG)
        formatter = logging.Formatter('{asctime} | {levelname:8} | {funcName}:{lineno} | {message}', style='{')
        fh.setFormatter(formatter)

        stream_formatter = logging.Formatter('{message}', style='{')
        ch = logging.StreamHandler()
        ch.setLevel(logging.DEBUG)
        ch.setFormatter(stream_formatter)

        log.addHandler(fh)
        log.addHandler(ch)
        log.setLevel(logging.DEBUG)

        log.info(f'Endurosat -macaron- build front-end [{config.get_version()}]')

        log.debug(f'{Path(sys.argv[0]).resolve().name} started with args: {args}')

        config().set_args(args)

        if args.clean:
            commands.clean_build()

        # FP code generation
        if args.fp_gen or args.datacache_gen:
            if args.depl_config:
                if args.datacache_gen:
                    log.warning("WARN: ignoring -datacache option in combination with -fp option!")

                depl_config = Path(args.depl_config)

                if args.fp_gen and args.fp_merge_root:
                    commands.run_macchiato_merge(depl_config, args.fp_merge_root)
                else:
                    if args.fp_gen:
                        raise Exception(
                            'For C code generation please specify also a root merge path via the -fmr option!'
                        )
                    elif args.datacache_gen:
                        commands.run_macchiato('--gen-dc', depl_config)
                        # copy all generated files to the folder of the deployment configuration file
                        dc_gen_path = os.path.join(depl_config.parent, 'src-gen-dc')

                        for dirpath, dirname, files in os.walk(dc_gen_path):
                            for f in files:
                                target_file_path = os.path.join(depl_config.parent, f)

                                if os.path.isfile(target_file_path):
                                    os.remove(target_file_path)

                                shutil.move(os.path.join(dirpath, f), os.path.join(depl_config.parent.resolve()))

                        shutil.rmtree(dc_gen_path, ignore_errors=True)

            else:
                raise Exception(
                    'If you are using the -fp or -datacache option, then you also have to specify a deployment configuration file via the -dc option!'
                )

        # Build the code
        if args.build:
            # Version update
            cfu = config_file_updater(config.VERSION_FILE)
            if args.release_ver:
                cfu.create_build_version_file(args.release_ver)
            else:
                cfu.default_build_version_file()
            
            # Build command
            start_timestamp = time.time()
            commands.run_build(args.build)
            log.info(f'>>> BUILD OK ({time.time() - start_timestamp:.2f} sec) <<<')
        # FP code generation
        if args.fp_gen_all:
            matches = macaron_utils.find_file(config.get_build_root_path().resolve(), '*.fdepl')

            for fdepl in matches:
                log.info(f'generating {str(fdepl)}...')
                if args.fp_merge_root:
                    commands.run_macchiato_merge(fdepl, args.fp_merge_root)

        # Clean the generated code
        if args.clean_gen_content:
            macaron_utils.clean_directories_by_name(args.clean_gen_content.resolve(), 'src-gen-c')

        # Binary and Bundle updates
        if args.dongle_port and (args.flash_bin or args.flash_bun or args.upload_bun_file) and args.obc_mac_addr:
            if args.flash_bin:
                in_file = args.flash_bin
                is_binary = True
                is_fw_file = True

            if args.flash_bun:
                in_file = args.flash_bun
                is_binary = False
                is_fw_file = True

            if args.upload_bun_file:
                in_file = args.upload_bun_file
                is_binary = False
                is_fw_file = False

            commands.run_flash_app(
                in_file, args.dongle_port, args.obc_mac_addr, is_binary, True if args.session_id else False, args.session_id, is_fw_file)
        else:
            if args.flash_bin or args.flash_bun:
                log.error(
                    'Flashing requires the use of the following parameters together: [--dongle-port, --obc-mac-addr, --flash-bin or --flash-bun]. You are missing one or more of these parameters and the operation cannot be executed.'
                )

        # Bundle generation
        if args.create_app_bundle:
            bundle_name = macaron_utils.bundle_app_binary(args.create_app_bundle)

            if bundle_name != '':
                log.info(f'OBC application bundle created here: "{bundle_name}"')

        if args.create_schedule_bundle:
            bundle_name = macaron_utils.bundle_schedule_binary(args.create_schedule_bundle)

            if bundle_name != '':
                log.info(f'Schedule file bundle created here: "{bundle_name}"')

        sys.exit(0)

    except Exception as exc:
        log.exception(f'Oops: {exc}')
        sys.exit(1)
