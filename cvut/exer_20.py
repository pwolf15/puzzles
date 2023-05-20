def f(n):
    x = 2
    for i in range(n):
        if x < 450:
            x = 3 + x
    return x

print(f(-100))
print(f(100))
print(f(1000))