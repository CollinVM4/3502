def extended_gcd(a, b):
    if a == 0:
        return b, 0, 1
    else:
        gcd, x, y = extended_gcd(b % a, a)
        return gcd, y - (b // a) * x, x

def mod_inverse(a, m):
    gcd, x, _ = extended_gcd(a, m)
    if gcd != 1:
        return None  # modular inverse does not exist
    else:
        return x % m

a = 16
m = 117
inverse = mod_inverse(a, m)
print(f"The modular inverse of {a} modulo {m} is {inverse}")