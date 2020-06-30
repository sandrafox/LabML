import math


epsilon  = math.ldexp(1.0, -53) # smallest double that 0.5+epsilon != 0.5
maxDouble = float(2**1024 - 2**971)  # From the IEEE 754 standard
minDouble  = math.ldexp(1.0, -1022) # min positive normalized double
smallEpsilon  = math.ldexp(1.0, -1074) # smallest increment for doubles < minFloat
infinity = math.ldexp(1.0, 1023) * 2


def nextafter(x,y):
    """returns the next IEEE double after x in the direction of y if possible"""
    if y==x:
       return y         #if x==y, no increment

    # handle NaN
    if x!=x or y!=y:
        return x + y

    if x >= infinity:
        return infinity

    if x <= -infinity:
        return -infinity

    if -minDouble < x < minDouble:
        if y > x:
            return x + smallEpsilon
        else:
            return x - smallEpsilon

    m, e = math.frexp(x)
    if y > x:
        m += epsilon
    else:
        m -= epsilon

    return math.ldexp(m,e)


def getFirst(val):
    return val[0]


def triangular(u):
    if u >= 1:
        return 0
    return 1 - u


def epanechikov(u):
    if u >= 1:
        return 0
    return 3 * (1 - u ** 2) / 4


def quartic(u):
    if u >= 1:
        return 0
    return 15 * (1 - u ** 2) ** 2 / 16


def triweight(u):
    if u >= 1:
        return 0
    return 35 * (1 - u ** 2) ** 3 / 32


def tricube(u):
    if u >= 1:
        return 0
    return 70 * (1 - u ** 3) ** 3 / 81


def gaussian(u):
    return 1 / math.sqrt(2 * math.pi) * math.exp(-(u ** 2) / 2)


def cosine(u):
    if u >= 1:
        return 0
    return math.pi / 4 * math.cos(u * math.pi / 2)


def logistic(u):
    return 1 / (math.exp(u) + 2 + math.exp(-u))


def sigmoid(u):
    return 2 / math.pi * 1 / (math.exp(u) + math.exp(-u))


def uniform(u):
    if u >= 1:
        return 0
    return 1 / 2


def K(name, r):
    if name == "uniform":
        return uniform(r)
    if name == "triangular":
        return triangular(r)
    if name == "epanechnikov":
        return epanechikov(r)
    if name == "quartic":
        return quartic(r)
    if name == "triweight":
        return triweight(r)
    if name == "tricube":
        return tricube(r)
    if name == "gaussian":
        return gaussian(r)
    if name == "cosine":
        return cosine(r)
    if name == "logistic":
        return logistic(r)
    if name == "sigmoid":
        return sigmoid(r)


ns, ms = input().split()
n = int(ns)
m = int(ms)
objs = []
for i in range(n):
    objs.append([int(j) for j in input().split()])
q = [int(j) for j in input().split()]
distance = input()
dobjs = []
if distance == "manhattan":
    for obj in objs:
        m = obj.pop()
        r, i = 0, 0
        for d in obj:
            r += math.fabs(d - q[i])
            i += 1
        dobjs.append((r, m))
elif distance == "euclidean":
    for obj in objs:
        m = obj.pop()
        r, i = 0, 0
        for d in obj:
            r += (d - q[i]) ** 2
            i += 1
        r = math.sqrt(r)
        dobjs.append((r, m))
else:
    for obj in objs:
        m = obj.pop()
        r, i = 0, 0
        for d in obj:
            ri = math.fabs(d - q[i])
            if ri > r:
                r = ri
            i += 1
        dobjs.append((r, m))
dobjs.sort(key=getFirst)
kernel = input()
window = input()
h = int(input())
a, b = 0, 0

if window == "fixed":
    if h == 0:
        for (r, m) in dobjs:
            if r > 0:
                break
            c = K(kernel, 0)
            a += m * c
            b += c
    else:
        for (r, m) in dobjs:
            c = K(kernel, r / h)
            a += m * c
            b += c
else:
    dist, _ = dobjs[h - 1]
    distn = dist
    hn = h
    for i in range(h, n):
        tmp, _ = dobjs[i]
        if tmp > distn:
            distn = tmp
            h = i
            break
    if not(distn > dist):
        dist = nextafter(dist, dist + 1)
        h = n
    else:
        dist, _ = dobjs[hn]
    if dist == 0:
        for i in range(h):
            (r, m) = dobjs[i]
            if r > 0:
                break
            c = K(kernel, 0)
            a += m * c
            b += c
    else:
        for i in range(h):
            (r, m) = dobjs[i]
            c = K(kernel, r / dist)
            a += m * c
            b += c
if b == 0:
    a, b = 0, 0
    for i in range(n):
        (_, m) = dobjs[i]
        a += m
        b += 1
if a == 0: print(0)
else: print(a / b)
