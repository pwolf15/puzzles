
def reverse_digits(n):

    n_reverse = 0
    sign = 1 if n > 0 else -1
    n = abs(n)
    digit = 1
    while n:
        n_reverse = (n % 10) + 10 * n_reverse
        n = n // 10

    return sign * n_reverse

print(reverse_digits(42))
print(reverse_digits(-314))