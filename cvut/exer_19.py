def test(n):

    cnt = 0
    for i in range(70):
        j = i
        while j > 0:
            if j < n:
                cnt += 1
            j -= 1
    return cnt

print(test(4))
