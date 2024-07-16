SENTINEL_VALUE = 0x5A
SAFE_BUFFER_SIZE = 256
FRAME_DELIMITER = b'\x00'
FRAME_DELIMITER_BYTE = FRAME_DELIMITER[0]
FRAME_DELIMITER_STR = '\x00'


def decode(data: bytearray, encoding: str) -> str | None:

    if len(data) < 2:
        return None

    cur = 0
    ofs = data[cur]

    while (cur < len(data)) and (ofs != FRAME_DELIMITER_BYTE):
        ofs = data[cur]
        data[cur] = FRAME_DELIMITER_BYTE

        for i in range(1, ofs):
            try:
                if data[cur + i] == FRAME_DELIMITER_BYTE:
                    return None
            except IndexError:
                return None

        cur += ofs

    if cur != len(data) - 1:
        return None

    data[0] = SENTINEL_VALUE
    data[len(data) - 1] = SENTINEL_VALUE


    return data[1:len(data) - 1].decode(encoding)
