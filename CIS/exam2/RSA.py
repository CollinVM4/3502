def rsa_decrypt(ciphertext, d, n):
    return (ciphertext ** d) % n

ciphertext = 2
d = 29
n = 91
plaintext = rsa_decrypt(ciphertext, d, n)
print(f"The decrypted message is {plaintext}")