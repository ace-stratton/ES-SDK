import struct
from rich import print
from datetime import datetime
import ctypes
import argparse
import sys
import pathlib

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

def py_crc32(crc: ctypes.c_uint32, buf : bytes) -> int:
        buf = bytes(buf)
        crc = ctypes.c_uint32(~crc)

        for p in buf:
            crc.value = (crc32_tab[(
                crc.value & 0xFF) ^ p] ^ (crc.value >> 8)) & 0xFFFFFFFF

        return ~crc.value & 0xFFFFFFFF

def format_reg_str(reg_value : int) -> str:
    return '0x{:08x}'.format(reg_value)

class psr:
    def __init__(self, reg_value : int):
        self.psr = reg_value

        self.psr_bits = {}
        self.psr_bits["ISR_NUMBER"] = self.psr & 0x1FF
        self.psr_bits["ICI/IT[15:10]"] = (self.psr >> 10) & 0x3F
        self.psr_bits["GE[3:0]"] = (self.psr >> 16) & 0x0F
        self.psr_bits["T"] = (self.psr >> 24) & 1
        self.psr_bits["IC/IT[26:25]"] = (self.psr >> 25) & 3
        self.psr_bits["Q"] = (self.psr >> 27) & 1
        self.psr_bits["V"] = (self.psr >> 28) & 1
        self.psr_bits["C"] = (self.psr >> 29) & 1
        self.psr_bits["Z"] = (self.psr >> 30) & 1
        self.psr_bits["N"] = (self.psr >> 31) & 1

        self.isr_name : list[str] = [None] * 16
        self.isr_name[0] = "Thread mode"
        self.isr_name[1] = "Reserved"
        self.isr_name[2] = "NMI"
        self.isr_name[3] = "HardFault"
        self.isr_name[4] = "MemManage"
        self.isr_name[5] = "BusFault"
        self.isr_name[6] = "UsageFault"
        self.isr_name[7] = "Reserved"
        self.isr_name[8] = "Reserved"
        self.isr_name[9] = "Reserved"
        self.isr_name[10] = "Reserved"
        self.isr_name[11] = "SVCall"
        self.isr_name[12] = "Reserved for debug"
        self.isr_name[13] = "Reserved"
        self.isr_name[14] = "PendSV"
        self.isr_name[15] = "SysTick"

        for i in range(16, 257):
            self.isr_name.append(f'IRQ{i - 16}')

        self.psr_bits["ISR_NAME"] = self.isr_name[self.psr_bits["ISR_NUMBER"]] if self.psr_bits["ISR_NUMBER"] < len(self.isr_name) else "Unknown"

    def __repr__(self):
        return f"""{format_reg_str(self.psr)} => {self.psr_bits!r}"""

class abfsr:
    def __init__(self, reg_value : int):
        self.abfsr = reg_value

        self.abfsr_bits = {}
        self.abfsr_bits["ITCM"] = self.abfsr & 1
        self.abfsr_bits["DTCM"] = (self.abfsr >> 1) & 1
        self.abfsr_bits["AHBP"] = (self.abfsr >> 2) & 1
        self.abfsr_bits["AXIM"] = (self.abfsr >> 3) & 1
        self.abfsr_bits["EPPB"] = (self.abfsr >> 4) & 1
        self.abfsr_bits["AXIMTYPE"] = (self.abfsr >> 8) & 3

        self.aximtype : list[str] = [None] * 4
        self.aximtype[0] = "OKAY"
        self.aximtype[1] = "EXOKAY"
        self.aximtype[2] = "SLVERR"
        self.aximtype[3] = "DECERR"

    def __repr__(self):
        return f"""{format_reg_str(self.abfsr)} => {self.abfsr_bits!r} / AXIMTYPE status => {self.aximtype[self.abfsr_bits["AXIMTYPE"]]!r}"""

class fpscr:
    def __init__(self, reg_value : int):
        self.fpscr = reg_value

        self.fpscr_bits = {}
        self.fpscr_bits["IOC"] = self.fpscr & 1
        self.fpscr_bits["DZC"] = (self.fpscr >> 1) & 1
        self.fpscr_bits["OFC"] = (self.fpscr >> 2) & 1
        self.fpscr_bits["UFC"] = (self.fpscr >> 3) & 1
        self.fpscr_bits["IXC"] = (self.fpscr >> 4) & 1
        self.fpscr_bits["IDC"] = (self.fpscr >> 7) & 1
        self.fpscr_bits["RMode"] = (self.fpscr >> 22) & 3
        self.fpscr_bits["FZ"] = (self.fpscr >> 24) & 1
        self.fpscr_bits["DN"] = (self.fpscr >> 25) & 1
        self.fpscr_bits["AHP"] = (self.fpscr >> 26) & 1
        self.fpscr_bits["V"] = (self.fpscr >> 28) & 1
        self.fpscr_bits["C"] = (self.fpscr >> 29) & 1
        self.fpscr_bits["Z"] = (self.fpscr >> 30) & 1
        self.fpscr_bits["N"] = (self.fpscr >> 31) & 1

    def __repr__(self):
        return f"""{format_reg_str(self.fpscr)} => {self.fpscr_bits!r}"""

class hfsr:
    def __init__(self, reg_value : int):
        self.hfsr = reg_value

        self.hfsr_bits = {}
        self.hfsr_bits["VECTTBL"] = (self.hfsr >> 1) & 1
        self.hfsr_bits["FORCED"] = (self.hfsr >> 30) & 1
        self.hfsr_bits["DEBUGEVT"] = (self.hfsr >> 31) & 1

    def __repr__(self):
        return f"""{format_reg_str(self.hfsr)} => {self.hfsr_bits!r}"""

class bfar:
    def __init__(self, reg_value : int):
        self.bfar = reg_value

        self.bfar_bits = {}
        self.bfar_bits["ADDRESS"] = self.bfar

    def __repr__(self):
        return f"""{format_reg_str(self.bfar_bits["ADDRESS"])}"""

class mmfar:
    def __init__(self, reg_value : int):
        self.mmfar = reg_value

        self.mmfar_bits = {}
        self.mmfar_bits["ADDRESS"] = self.mmfar

    def __repr__(self):
        return f"""{format_reg_str(self.mmfar_bits["ADDRESS"])}"""

class cfsr:
    def __init__(self, reg_value : int):
        self.cfsr = reg_value
        self.mmfsr = reg_value & 0xFF
        self.bfsr = (reg_value >> 8) & 0xFF
        self.ufsr = (reg_value >> 16) & 0xFFFF

        self.mmfsr_bits = {}
        self.mmfsr_bits["IACCVIOL"] = self.mmfsr & 1
        self.mmfsr_bits["DACCVIOL"] = (self.mmfsr >> 1) & 1
        self.mmfsr_bits["MUNSTKERR"] = (self.mmfsr >> 3) & 1
        self.mmfsr_bits["MSTKERR"] = (self.mmfsr >> 4) & 1
        self.mmfsr_bits["MLSPERR"] = (self.mmfsr >> 5) & 1
        self.mmfsr_bits["MMARVALID"] = (self.mmfsr >> 7) & 1

        self.bfsr_bits = {}
        self.bfsr_bits["IBUSERR"] = self.bfsr & 1
        self.bfsr_bits["PRECISERR"] = (self.bfsr >> 1) & 1
        self.bfsr_bits["IMPRECISERR"] = (self.bfsr >> 2) & 1
        self.bfsr_bits["UNSTKERR"] = (self.bfsr >> 3) & 1
        self.bfsr_bits["STKERR"] = (self.bfsr >> 4) & 1
        self.bfsr_bits["LSPERR"] = (self.bfsr >> 5) & 1
        self.bfsr_bits["BFARVALID"] = (self.bfsr >> 7) & 1

        self.ufsr_bits = {}
        self.ufsr_bits["UNDEFINSTR"] = self.ufsr & 1
        self.ufsr_bits["INVSTATE"] = (self.ufsr >> 1) & 1
        self.ufsr_bits["INVPC"] = (self.ufsr >> 2) & 1
        self.ufsr_bits["NOCP"] = (self.ufsr >> 3) & 1
        self.ufsr_bits["UNALIGNED"] = (self.ufsr >> 8) & 1
        self.ufsr_bits["DIVBYZERO"] = (self.ufsr >> 9) & 1

    def __repr__(self):
        return f"""{format_reg_str(self.cfsr)} =>
        MFSR: {self.mmfsr_bits!r}
        BFSR: {self.bfsr_bits!r}
        UFSR: {self.ufsr_bits!r}"""

def deserialize_exception(frame_name : str, data : bytes):
    rec_type = struct.unpack("<L", data[:4])[0]

    if ((rec_type >> 8) & 0xFF) == ord('G'):
        return generic_sw_exception_frame(frame_name, data)
    else:
        return arm_fault_frame(frame_name, data)

class base_frame:
    def __init__(self, exception_frame_name : str, data : bytes):
        self.name = exception_frame_name

        self.record_type, self.reserved, self.exception_rtc_ts, self.uptime = struct.unpack(
            "<4s3L", data[:16])

        self.hdr_size = 16
        self.frame_crc = struct.unpack("<L", data[148:152])[0]
        self.crc_valid = (py_crc32(0, data[:len(data) - 4]) == self.frame_crc)

    @staticmethod
    def get_hex_edit_dump(data, bytes_per_row=16):
        result = ""

        for offset in range(0, len(data), bytes_per_row):
            row = data[offset:offset + bytes_per_row]
            hex_values = ' '.join(f'{byte:02X}' for byte in row)
            ascii_values = ''.join(chr(byte) if 32 <= byte <
                                   127 else '.' for byte in row)
            address = f'{offset:06X}'
            result += f'{address}: {hex_values.ljust(47)} | {ascii_values}\n'

        return result

    def __repr__(self):
        return f"""exception: {self.name!r} =>
    rec_type: {self.record_type!r} "{''.join(map(chr, self.record_type))}"
    reserved: {self.reserved!r}
    RTC timestamp: {datetime.utcfromtimestamp(self.exception_rtc_ts).strftime('%Y-%m-%d %H:%M:%S')}
    uptime (ms): {self.uptime!r}"""

class generic_sw_exception_frame(base_frame):
    def __init__(self, exception_frame_name : str, data : bytes):
        super().__init__(exception_frame_name, data)

        self.record_data = struct.unpack("136s", data[self.hdr_size:])[0]

    def __repr__(self):
        return f"""{super().__repr__()}
---------------
raw frame dump:
---------------
{base_frame.get_hex_edit_dump(self.record_data)}
    """

class arm_fault_frame(base_frame):
    def __init__(self, exception_frame_name : str, data : bytes):
        super().__init__(exception_frame_name, data)

        self.cfsr, self.hfsr, self.mmfar, self.bfar ,self.abfsr, self.sp, self.vtor, self.stack_frame_len = struct.unpack("<8L", data[16:48])

        # parse basic regs
        self.r0, self.r1, self.r2, self.r3, self.r12, self.lr, self.pc, self.psr = struct.unpack("<8L", data[48:80])

        # parse fp extended regs
        self.s_reg = struct.unpack("<16L", data[80:144])

        self.fpscr = struct.unpack("<L", data[144:148])[0]

    def __repr__(self):
        return f"""{super().__repr__()}
    CFSR: {cfsr(self.cfsr)}
    HFSR: {hfsr(self.hfsr)}
    MMFAR: {mmfar(self.mmfar)}
    BFAR: {bfar(self.bfar)}
    ABFSR: {abfsr(self.abfsr)}
    SP: {format_reg_str(self.sp)}
    VTOR: {format_reg_str(self.vtor)}
    stack frame len: {self.stack_frame_len} bytes
    STACK FRAME (
        R0 :   {format_reg_str(self.r0)}
        R1 :   {format_reg_str(self.r1)}
        R2 :   {format_reg_str(self.r2)}
        R3 :   {format_reg_str(self.r3)}
        R12:   {format_reg_str(self.r12)}
        LR :   {format_reg_str(self.lr)}
        PC :   {format_reg_str(self.pc)}
        PSR:   {psr(self.psr)}
        fp_ext_reg_s[{','.join(map(str, self.s_reg))}]
        FPSCR: {fpscr(self.fpscr)}
    )
    frame crc: 0x{'{:08x}'.format(self.frame_crc)} {"OK" if self.crc_valid else "NOK"}
    """

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='EnduroSat OBC fault list parser')

    parser.add_argument('-in', '--input', type=pathlib.Path, required=True, help='specifies an OBC fault dump file to parse')
    parser.add_argument('-raw', '--raw-frame-data', action='store_true', help='specify this if the file contains only raw frames (without the initial signature and record size header fields)')

    if len(sys.argv) == 1:
        parser.print_help(sys.stderr)
        sys.exit(1)

    try:
        args = parser.parse_args()

        with open(args.input, 'rb') as file:
            bad_format = False
            file_signature = "FAULT_LST"

            file_data = file.read()

            if not (args.raw_frame_data):
                file_hdr_len = 13
            else:
                file_hdr_len = 0

            if len(file_data) > file_hdr_len:
                if not (args.raw_frame_data):
                    hdr_str = struct.unpack("9s", file_data[:len(file_signature)])[0]
                    record_size = struct.unpack("<L", file_data[len(file_signature):file_hdr_len])[0]
                else:
                    hdr_str = bytes(file_signature, "ascii")
                    record_size = 152

                if (hdr_str.decode("ascii") == file_signature) and (record_size == 152):
                    print(f'record size: {record_size} bytes')

                    # Determine the number of records in the file
                    num_records = (len(file_data) -
                                   file_hdr_len) // record_size
                    records = file_data[file_hdr_len:]

                    if num_records > 0:
                        print(f'parsing {num_records} exception records...\n{"-" * 80}')

                        # Iterate through the records and print the information
                        for i in range(num_records):
                            record_data = records[i * record_size:(i + 1) * record_size]
                            exc_frame = deserialize_exception(f'{i}', record_data)
                            print(exc_frame)
                    else:
                        print(f'error: no exception records found in "{args.input}"')
                else:
                    bad_format = True
            else:
                bad_format = True

            if bad_format:
                print(f'error: bad file format')
    except Exception as exc:
        print(f'Oops: {exc}')
        sys.exit(1)
