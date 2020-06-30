import time


time0 = time.time()
ns, ms = input().split()
n = int(ns)
m = int(ms)
X = []
y = []
for i in range(n):
    tmp = [int(j) for j in input().split()]
    X.append(tmp[:m])
    X[i].append(1)
    y.append(tmp[m])
#print(X)
w = [0] * (m + 1)

k = 0.001
t = 1
while time.time() - time0 < 36:
    a = [0] * n
    for i in range(n):
        for j in range(m + 1):
            a[i] += X[i][j] * w[j]
        a[i] -= y[i]
    #print(a)
    grad = [0] * (m + 1)
    for i in range(m + 1):
        for j in range(n):
            grad[i] += X[j][i] * a[j]
        grad[i] *= 2 * k / (m * t)
        w[i] -= grad[i]
    t += 1
    #print (w)
for i in range(m + 1):
    print (w[i])