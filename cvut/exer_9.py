n = 85
sum = 0
iters = 0
for i in range(n,-1,-1):
    for j in range(n,-1,-1):
        iters += 1
        sum += i + j

print(iters)

n = 100
sum = 0
iters = 0
for i in range(n):
    for j in range(i):
        iters += 1
        sum += i + j
print(iters)

n = 110
sum = 0
iters=0
for i in range(n,-1,-1):
    for j in range(i,-1,-1):
        iters += 1
        sum += i + j

print(iters)

n = 75
sum = 0
iters = 0
for i in range(n):
    for j in range(n):
        iters += 1
        sum += i + j
print(iters)