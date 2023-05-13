
def plus_one(n):

    n_result = []
    if len(n) == 0:
        return [1]

    carry = 1
    for i in range(len(n)):
        result = carry + n[len(n) - i - 1] % 10
        digit = result % 10
        carry = result // 10
        n_result.append(digit)
    if carry:
        n_result.append(carry)

    n_result.reverse()
    return n_result

def plus_one_2(n):

    if (len(n) == 0):
        return [1]
    
    n[len(n) - 1] += 1
    for i in reversed(range(len(n))):
        el = n[i]
        if el == 10 and i > 0:
            n[i] = 0
            n[i - 1] += 1
        if el == 10 and i == 0:
            n[i] = 1
            n.append(0)
    
    return n

print(plus_one([1,2,9]))
print(plus_one([9,9,9]))
print(plus_one([]))

inputs = [
    [1,2,9],
    [9,9,9],
    []
]

for i in inputs:
    print(plus_one_2(i))