def is_primitive_root(g, n):
    results = set()
    for k in range(1, n):
        results.add((g ** k) % n)
    return len(results) == n - 1

g = 9
n = 17
print(f"Is {g} a primitive root of {n}? {'Yes' if is_primitive_root(g, n) else 'No'}")