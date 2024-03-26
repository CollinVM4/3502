def generate_test_file(filename, num_chars):
    with open(filename, 'w') as f:
        for i in range(num_chars):
            f.write('A')  # Write the character 'A'

# Generate a test file for 8 bit checksum
generate_test_file('test_8bit.txt', 8)

# Generate a test file for 16 bit checksum
generate_test_file('test_16bit.txt', 16)