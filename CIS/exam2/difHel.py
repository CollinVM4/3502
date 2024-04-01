def diffie_hellman_shared_key(q, g, a, b):
    # Alice sends Bob A = g^a mod q
    A = (g**a) % q

    # Bob sends Alice B = g^b mod q
    B = (g**b) % q

    # Alice computes shared key as K = B^a mod q
    K_Alice = (B**a) % q

    # Bob computes shared key as K = A^b mod q
    K_Bob = (A**b) % q

    # Both should be same
    assert K_Alice == K_Bob

    return K_Alice

q = 29 # chosen prime value
g = 10  # chosen prim root
a = 7  # Alice's secret key
b = 4  # Bob's secret key

shared_key = diffie_hellman_shared_key(q, g, a, b)
print(f"The shared key is {shared_key}")