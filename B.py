def calcTP_FP_FN(matrix, c):
    TP = matrix[c][c]
    FP, FN = 0, 0
    for f in matrix[c]:
        FP += f
    FP -= TP
    for f in matrix[:][c]:
        FN += f
    FN -= TP
    C = TP + FN
    return TP, FP, FN, C

def F(P, R):
    return 2 * P * R / (P + R)

k = int(input())
matrix = []
for i in range(k):
    matrix.append([int(j) for j in input().split()])
m = [calcTP_FP_FN(matrix, i) for i in range(k)]
##m = np.fromfunction(calcTP_FP_FN(matrix), k)
#C = [TP + FN for (TP, _, FN) in m
P_macro, R_macro, F_micro, All, TP_micro, FP_micro, FN_micro = 0, 0, 0, 0, 0, 0, 0
for (_, _, _, C) in m:
    All += C
i = 0
for (TP, FP, FN, C) in m:
    P = TP / (TP + FP)
    R = TP / (TP + FN)
    if (TP != 0):
        F_micro += C * F(P, R) / All
    #F_micro += C[i] * P * R / (P + R)
    #F_micro += 2 * TP / (2 * TP + FP + FN)
    #TP_micro += TP * C
    #FP_micro += FP * C
    #FN_micro += FN * C
    P_macro += P * C / All
    R_macro += R * C / All
print(F_micro)
print(F(P_macro, R_macro))
#C1*TP1 / (TP1 + FP1 + TP1 + FN1)

