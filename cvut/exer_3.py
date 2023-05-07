def h(s):
    i = 1
    for c in s:
        i = 1 - i
    return 'Y' if i==1 else 'N'

print(h('every') + h('point') + h('counts'))