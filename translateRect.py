size = 8
inc = [0, 0, 0.25]
array = []
for i in range(8):
    array += [list(map(float, input().split()))]

for a in array:
    a[0] += inc[0]
    a[1] += inc[1]
    a[2] += inc[2]

for a in array:
    print(*a)