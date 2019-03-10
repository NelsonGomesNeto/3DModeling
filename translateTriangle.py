size = 8
inc = [0, 0, 0.25]
array = []
for i in range(size):
    array += [list(map(float, input().split()))]

for a in array:
    for j in range(3):
        a[0 + j*3] += inc[0]
        a[1 + j*3] += inc[1]
        a[2 + j*3] += inc[2]

for a in array:
    print(*a)