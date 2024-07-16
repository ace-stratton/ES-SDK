import struct
import es_crc
import argparse
import pathlib
import sys
import csv
import binascii
from rich import print

class sxband_cmd_list_header:
    def __init__(self, summary_fname : str, sxband_dev_id : int):
        self.summary_fname = summary_fname
        self.sxband_dev_id = sxband_dev_id

    def serialize(self) -> bytes:
        hdr_bytes = bytearray()

        hdr_bytes.extend(struct.pack("<15s?31sH", str.encode("ES_OBC_CMD_LIST", encoding='ascii'),
                         self.summary_fname is not None, str.encode(self.summary_fname, encoding='ascii'), self.sxband_dev_id))

        hdr_crc = es_crc.crc_util.crc16(hdr_bytes)

        hdr_bytes.extend(struct.pack("<H", hdr_crc))

        return hdr_bytes

class sxband_cmd_list_command:
    def __init__(self, cmd : int, cmd_type : int, data : bytes):
        self.cmd = cmd
        self.cmd_type = cmd_type
        self.data = data

    def serialize(self) -> bytes:
        cmd_bytes = bytearray()

        data_len : int = 0
        if self.data is not None:
            data_len = len(self.data)

        cmd_bytes.extend(struct.pack("<BBB", self.cmd, self.cmd_type, data_len))

        if self.data is not None:
            for data_byte in self.data:
                cmd_bytes.append(data_byte)

        cmd_crc = es_crc.crc_util.crc16(cmd_bytes)

        cmd_bytes.extend(struct.pack("<H", cmd_crc))

        return cmd_bytes

class data_importer:
    def __init__(self, fname : pathlib.Path):
        self.fname = fname
        self.sxband_cmd_list : list[sxband_cmd_list_command] = []

    def parse_data(self, data_str : str) -> bytes:
        data_bytes = None

        data_str = data_str.strip()

        try:
            data_bytes = binascii.unhexlify(data_str)
        except Exception:
            # in case of exception, the data is assumed to be a regular string (e.g. file name)
            data_str += '\0'    # add terminating zero
            data_bytes = bytes(data_str, encoding='ascii')

        return data_bytes

    def import_data(self):
        with open(self.fname, newline='') as csv_data:
            data_reader = csv.DictReader(csv_data, delimiter=',')
            for row in data_reader:
                print("importing data: ", row)

                data_bytes = None
                if 'data' in row.keys():
                    data_bytes = self.parse_data(row['data'])

                cmd = sxband_cmd_list_command(
                    int(row['cmd'], base=0), ord(row['type'][0]), data_bytes)

                self.sxband_cmd_list.append(cmd)

    def get_data(self) -> list[sxband_cmd_list_command]:
        return self.sxband_cmd_list

class sxband_sched_file_writer:
    def __init__(self, fname : pathlib.Path, summary_fname : str, sxband_dev_id : int):
        self.fname = fname
        self.summary_fname = summary_fname
        self.sxband_dev_id = sxband_dev_id
        self.fout = None

    def open(self):
        self.fout = open(self.fname, "wb")

    def serialize(self, sxband_list : list[sxband_cmd_list_command]):
        file_hdr = sxband_cmd_list_header(self.summary_fname, self.sxband_dev_id)
        self.fout.write(file_hdr.serialize())

        for cmd in sxband_list:
            self.fout.write(cmd.serialize())

    def close(self):
        self.fout.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='This script converts a CSV list of OBC-formatted SXBand commands to a binary command list file which can be uploaded to the OBC and executed')

    parser.add_argument('-input', '--input-file', type=pathlib.Path,
                        default=None, help='Input CSV file name')

    parser.add_argument('-output', '--output-file', type=pathlib.Path,
                        default=None, help='Output binary file name')

    parser.add_argument('-sfn', '--summary-file-name', type=str,
                        default=None, help='Summary file name to be generated (must be a valid path for the OBC module file system')

    parser.add_argument('-dev-id', '--device-id', type=str,
                        default=None, help='SXBand device ID (decimal or hex format supported, e.g. 4660 or 0x1234')


    if len(sys.argv) == 1:
        parser.print_help(sys.stderr)
        sys.exit(1)

    try:
        args = parser.parse_args()
        print(args)

        csv_importer = data_importer(args.input_file)
        csv_importer.import_data()

        fwriter = sxband_sched_file_writer(
            args.output_file, args.summary_file_name, int(args.device_id, base=0))
        fwriter.open()
        fwriter.serialize(csv_importer.get_data())
        fwriter.close()

        print("All done!")

        sys.exit(0)
    except Exception as e:
        print(
            f'Ooops... This is kind of embarassing. We have an exception:\n\n>>> {e} <<<')
        sys.exit(1)
