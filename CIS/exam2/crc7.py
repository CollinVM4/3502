def crc7(hex_data, polynomial):
    # Convert hex data and polynomial to binary
    data = bin(int(hex_data, 16))[2:].zfill(8)
    poly = polynomial  # Polynomial X7 + X5 + X3 + X2 in binary

    # Append 7 zeros to the end of the data
    data += '0000000'

    for i in range(len(data) - 7):
        if data[i] == '1':
            for j in range(len(poly)):
                # Perform XOR operation
                data = data[:i+j] + str(int(data[i+j]) ^ int(poly[j])) + data[i+j+1:]

    # The remaining data is the CRC
    crc = data[-7:]

    return crc

hex_data = 'B0DE'
crc = crc7(hex_data, '10101101')
print(f"CRC7 is {crc}.")