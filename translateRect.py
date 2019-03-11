size = 10
inc = [0, 0, -5]
array = []
for i in range(size):
    array += [list(map(float, input().split()))]

for a in array:
    a[0] += inc[0]
    a[1] += inc[1]
    a[2] += inc[2]
    a[-1] = int(a[-1])
    a[-2] = int(a[-2])
    a[-3] = int(a[-3])
    a[-4] = int(a[-4])
    a[-5] = int(a[-5])

for a in array:
    print(*a)