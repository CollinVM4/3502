def compute_checksum(message):
    # Step 1: Break the hexadecimal message into 8-bit chunks
    chunks = [message[i:i+2] for i in range(0, len(message), 2)]
    
    # Step 2: Convert each chunk into binary
    binary_values = [bin(int(chunk, 16))[2:].zfill(8) for chunk in chunks]
    
    # Step 3: Sum all the binary values and discard overflow bits
    total = sum(int(b, 2) for b in binary_values) & 0xFF
    
    # Step 4: Perform two's complement
    total = (~total + 1) & 0xFF
    
    # Step 5: Convert back to hexadecimal
    checksum = hex(total)[2:].upper().zfill(2)
    
    return checksum

message = "C8C093"
checksum = compute_checksum(message)
print(f"8-bit checksum is {checksum}.")
print(f"The final message with the checksum is {message}{checksum}.")