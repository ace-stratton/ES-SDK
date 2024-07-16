#!/usr/bin/env python3

import argparse
import os
import sys

VARS = {}

def get_timestamp(path, default=None):
    try:
        stat = os.stat(path)
        return stat.st_mtime
    except OSError:
        if default is None:
            raise FreezeError("cannot stat {}".format(path))
        return default

def mkdir(filename):
    path = os.path.dirname(filename)
    if not os.path.isdir(path):
        os.makedirs(path)

def build(manifest_path, output_path, mpy_cross_path, flags):
    import manifestfile
    import mpy_cross
    
    mpy_files = []

    # Compile the manifest.
    manifest = manifestfile.ManifestFile(manifestfile.MODE_COMPILE, VARS)
    manifest.execute(manifest_path)

    for result in manifest.files():
        print(result)
        # This isn't allowed in micropython-lib anyway.
        if result.file_type != manifestfile.FILE_TYPE_LOCAL:
            print("Non-local file not supported.", file=sys.stderr)
            sys.exit(1)

        if not result.target_path.endswith(".py"):
            print(
                "Target path isn't a .py file:",
                result.target_path,
                file=sys.stderr,
            )
            sys.exit(1)


        for result in manifest.files():
            outfile = "{}/custom_mpy/{}.mpy".format(output_path, result.target_path[:-3])
            ts_outfile = get_timestamp(outfile, 0)
            if result.timestamp >= ts_outfile:
                print("MPY", result.target_path)
                mkdir(outfile)
                # Add __version__ to the end of the file before compiling.
                with manifestfile.tagged_py_file(result.full_path, result.metadata) as tagged_path:
                    try:
                        mpy_cross.compile(
                            tagged_path,
                            dest=outfile,
                            src_path=result.target_path,
                            opt=result.opt,
                            mpy_cross=mpy_cross_path,
                            extra_args=flags.split(),
                        )
                    except mpy_cross.CrossCompileError as ex:
                        print("error compiling {}:".format(result.target_path))
                        print(ex.args[0])
                        raise SystemExit(1)
                ts_outfile = get_timestamp(outfile)
            mpy_files.append(outfile)

def main():
    import argparse

    cmd_parser = argparse.ArgumentParser(description="Compile mpy files based described in manifest.py file")
    cmd_parser.add_argument("--manifestfile", required=True, help="input manifest file")
    cmd_parser.add_argument("--output", required=True, help="output directory")
    cmd_parser.add_argument("--micropython", required=True, help="path to micropython repo")
    cmd_parser.add_argument("-v", "--var", action="append", help="variables to substitute")
    cmd_parser.add_argument("-f", "--mpy-cross-flags", default="", help="flags to pass to mpy-cross")

    args = cmd_parser.parse_args()

    # Extract variables for substitution.
    for var in args.var:
        name, value = var.split("=", 1)
        if os.path.exists(value):
            value = os.path.abspath(value)
        VARS[name] = value

    if "MPY_DIR" not in VARS or "PORT_DIR" not in VARS:
        print("MPY_DIR and PORT_DIR variables must be specified")
        sys.exit(1)

    # Get paths to tools
    MPY_CROSS = VARS["MPY_DIR"] + "/mpy-cross/build/mpy-cross"
    if sys.platform == "win32":
        MPY_CROSS += ".exe"
    MPY_CROSS = os.getenv("MICROPY_MPYCROSS", MPY_CROSS)

    # Ensure mpy-cross is built
    if not os.path.exists(MPY_CROSS):
        print("mpy-cross not found at {}, please build it first".format(MPY_CROSS))
        sys.exit(1)


    if args.micropython:
        sys.path.append(os.path.join(args.micropython, "tools"))  # for manifestfile
        # Always use the mpy-cross from this repo.
        sys.path.insert(0,os.path.join(args.micropython, "mpy-cross"))  # for mpy_cross

    build(args.manifestfile, args.output, MPY_CROSS, args.mpy_cross_flags)


if __name__ == "__main__":
    main()
