def f(x):
    return f(x//2) + ("a" if (x%2) else "b") if x > 0 else ""

print(len(f(60)+f(8)+f(0)+f(2)))