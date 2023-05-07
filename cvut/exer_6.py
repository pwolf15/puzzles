def f(x,y):
    if x>0:
        return f(x-1,y) + 1
    if y<=0:
        return 0
    return f(x,y-1)-1

print(f(133,123)+f(10,-5)+f(-10,5)+f(-1,-2))