def crc16_calc(data: bytearray) -> int:
    """
    CRC-16-CCITT Algorithm
    """
    crc = 0xFFFF
    poly = 0x1021

    for b in data:
        crc ^= b << 8

        for _ in range(0, 8):
            if crc & 0x8000:
                crc = (crc << 1) ^ poly
            else:
                crc = (crc << 1)

    return int(hex(crc & 0xffff), 16)
