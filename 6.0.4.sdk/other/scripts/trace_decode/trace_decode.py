import argparse
import datetime
import serial
import crc
import cobs_inplace


ENCODING = "utf-8"


class Colors:
    RED = '\033[31m'
    GREEN = '\033[32m'
    YELLOW = '\033[33m'
    BLUE = '\033[34m'
    WHITE = '\033[37m'
    END = '\033[0m'


LVL_STR = {
    "ERROR": {
        "color": Colors.BLUE
    },
    "WARN": {
        "color": Colors.YELLOW
    },
    "INFO": {
        "color": Colors.GREEN
    },
    "FATAL": {
        "color": Colors.RED
    },
    "DEBUG": {
        "color": Colors.WHITE
    }
}


def check_filter(data: str, lvl: str, file: str) -> bool:
    split = data.split(",")
    module = split[0]
    log_lvl = split[2]

    if lvl is not None:
        lvl_ok = True if lvl in log_lvl else False
    else:
        lvl_ok = True

    if file is not None:
        mod_ok = True if file in module else False
    else:
        mod_ok = True

    return mod_ok and lvl_ok


def get_lvl_text_color(lvl: str):
    if lvl is None:
        return Colors.WHITE

    if lvl not in LVL_STR.keys():
        return Colors.WHITE

    return LVL_STR[lvl]["color"]


def log_color_data(data: str):
    lvl = data.split(",")[2]
    print(f"{get_lvl_text_color(lvl)}{data}{Colors.END}")


def convert_log_to_printable_data(raw_log_data: bytearray) -> None | str:
    try:
        decoded = cobs_inplace.decode(raw_log_data, ENCODING)

        if decoded is None:
            return None

        last_comma = decoded.rfind(",")
        split = decoded.split(",")

        # last element is always the CRC value
        received_crc = int(split[-1])

        # calculate crc of the user data
        calculated_crc = crc.crc16_calc(bytearray(decoded[:last_comma], ENCODING))

        # compare both CRC values
        if received_crc == calculated_crc:
            # convert from UNIX time stamp
            tstamp = str(datetime.datetime.utcfromtimestamp(int(split[3])))
            split[3] = tstamp

            printable_data = ",".join(split)
            printable_data = printable_data[:printable_data.rfind(",")]

            return printable_data
        else:
            return None
    except:
        return None


def parse_log_file_data(inf: str, outf: str, lvl: str, file: str) -> None:
    try:
        with open(inf, "rb") as infile:
            with open(outf, "w") as outfile:
                contents = infile.read().split(cobs_inplace.FRAME_DELIMITER)

                for log_bytes in contents:
                    # delimiter was removed by split() - restore it
                    log = bytearray(log_bytes)
                    log.extend(cobs_inplace.FRAME_DELIMITER)

                    data = convert_log_to_printable_data(log)

                    if data is not None:
                        if check_filter(data, lvl, file):
                            data += "\n"
                            outfile.write(data)
    except FileNotFoundError as e:
        print(f"{e}")


def parse_com_port_data(com: str, baud: str, lvl: str, mod: str, file: str) -> None:
    try:
        port = serial.Serial(
            port=com,
            baudrate=int(baud),
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS,
            timeout=1)
    except serial.SerialException as e:
        print(f"{e}")
        return

    f = None

    try:
        if file:
            f = open(file, "w")
        log = bytearray()
        while True:
            log.extend(port.read())
            if log and (log[-1] == cobs_inplace.FRAME_DELIMITER_BYTE):
                data = convert_log_to_printable_data(log)

                if data is not None:
                    if check_filter(data, lvl, mod):
                        log_color_data(data)
                        if f is not None:
                            f.write(data)
                log = bytearray()
    except KeyboardInterrupt:
        if f is not None:
            f.close()
    except Exception as e:
        print(f"{e}")
        if f is not None:
            f.close()
        return


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='script for parsing trace logs')

    parser_group1 = parser.add_argument_group(title='file parser options')
    parser_group1.add_argument("-i", type=str, help='raw log file to be parsed')
    parser_group1.add_argument("-o", type=str, help='output file to be created')

    parser_group2 = parser.add_argument_group(title='com port parser options')
    parser_group2.add_argument("-p", type=str, help='com port')
    parser_group2.add_argument("-b", type=str, default='115200', help='baud rate')
    parser_group2.add_argument("-f", type=str, default=None, help='output file')

    parser_group3 = parser.add_argument_group(title='filter options')
    parser_group3.add_argument("-fl", type=str, choices=LVL_STR, help='log only specified level')
    parser_group3.add_argument("-ff", type=str, help='log only specified file')

    args = parser.parse_args()

    if args.i is not None and args.o is not None:
        parse_log_file_data(args.i, args.o, args.fl, args.ff)
    elif args.p is not None and args.b is not None:
        import os

        # enable ansi colors on Win OS
        if os.name == "nt":
            os.system("color")

        parse_com_port_data(args.p, args.b, args.fl, args.ff, args.f)
    else:
        parser.print_help()
