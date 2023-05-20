a = [4,4,5,5,6,6,6,7,7,7,7,8,8]
count=0
j=0
for i in range(len(a) - 1):
    if a[i+1] == a[i]:
        j = j+1
    else:
        if count < j:
            count = j
        j = 0
print(count)