data=[4,4,5,5,6,6,6,7,7,7,7,8,8]
count = 0
for i in range(1,len(data)):
    if data[i] == data[i-1]:
        count = count+1
print(count)