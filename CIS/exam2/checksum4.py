def compute_checksum(message):
    # Step 1: Convert the hexadecimal message to binary
    binary_values = [bin(int(chunk, 16))[2:].zfill(4) for chunk in message]
    
    # Step 2: Add the binary numbers and discard overflow bits
    total = sum(int(b, 2) for b in binary_values) & 0xF
    
    # Step 3: Perform two's complement
    total = (~total + 1) & 0xF
    
    # Step 4: Convert back to hexadecimal
    checksum = hex(total)[2:].upper()
    
    return checksum

message = "12345"
checksum = compute_checksum(message)
print(f"The checksum is {checksum}.")
print(f"The final message with the checksum is {message}{checksum}.")