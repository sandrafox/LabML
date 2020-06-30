import math


n = int(input())
p = []
xm, ym = 0, 0
for i in range(n):
    xs, ys = input().split()
    x, y = int(xs), int(ys)
    p.append((x, y))
    xm += x
    ym += y
xm /= n
ym /= n
a, b, c = 0, 0, 0
for (x, y) in p:
    a += (x - xm)*(y - ym)
    b += (x - xm) ** 2
    c += (y - ym) ** 2
if a == 0:
    print(0)
else:
    print(a/math.sqrt(b * c))
