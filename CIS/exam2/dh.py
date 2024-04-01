def crc_remainder(input_bitstring, polynomial_bitstring, initial_filler):
    polynomial_len = len(polynomial_bitstring)
    input_padded_array = list(input_bitstring + initial_filler)
    while '1' in input_padded_array[:len(input_bitstring)]:
        cur_shift = input_padded_array.index('1')
        for i in range(polynomial_len):
            input_padded_array[cur_shift + i] = str(int(polynomial_bitstring[i] != input_padded_array[cur_shift + i]))
    return ''.join(input_padded_array)[len(input_bitstring):]

input_data = '101011001110'  # ACE in binary
polynomial = '1101'  # X^3 + X^2 + 1
initial_filler = '0000'  # For CRC-3

print(crc_remainder(input_data, polynomial, initial_filler))