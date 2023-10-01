import copy
from math import fabs


def F(x):
    return 3*x[0]**2 + x[1]**2 - x[0]*x[1] + x[0]


def sumV(v1, v2):
        return [v1[i]+v2[i] for i in range(len(v1))]


def diffV(v1, v2):
    return [v1[i]-v2[i] for i in range(len(v1))]


def v_multiply_k(v1, k):
    return [i*k for i in v1]


def dF(x):
    h = 0.1**6
    mas = []
    for i in range(len(x)):
        x1 = [x[j] if j!=i else x[j]+h for j in range(len(x))]
        mas.append((F(x1)-F(x))/h)
    return mas


def norma(mas):
    return max([fabs(i) for i in mas])


def ddF(x):                         ###
    h = 0.1**5
    mas = [[0]*len(x) for i in x]
    for i in range(len(mas)):
        x1 = [x[j] if j!=i else x[j]+h for j in range(len(x))]
        x2 = [x[j] if j!=i else x[j]-h for j in range(len(x))]
        mas[i][i] = (F(x1)-2*F(x)+F(x2))/h**2
    x1 = [x[j] if j!=i else x[j]+h for j in range(len(x))]
    x2 = [x[j] if j==i else x[j]+h for j in range(len(x))]
    x3 = [x[j]+h for j in range(len(x))]
    mas[0][1] = mas[1][0] = (F(x3)-F(x2)-F(x1)+F(x))/h**2
    return mas


def inverse(A):
    def minor(A, i, j):
        M = copy.deepcopy(A)
        del M[i]
        for i in range(len(A[0]) - 1):
            del M[i][j]
        return M

    def det(A):
        m = len(A)
        n = len(A[0])
        if m != n:
            return None
        if n == 1:
            return A[0][0]
        signum = 1
        determinant = 0
        for j in range(n):
            determinant += A[0][j] * signum * det(minor(A, 0, j))
            signum *= -1
        return determinant

    def transpose(array):
        res = []
        n = len(array)
        m = len(array[0])
        for j in range(m):
            tmp=[]
            for i in range(n):
                tmp=tmp+[array[i][j]]
            res = res+[tmp]
        return res

    A = transpose(A)
    result = copy.deepcopy(A)
    for i in range(len(A)):
        for j in range(len(A[0])):
            tmp = minor(A, i, j)
            if (i +j) % 2 == 1:
                result[i][j] = -1*det(tmp) / det(A)
            else:
                result[i][j] = 1*det(tmp) / det(A)
    return result


def MVpr(M,V):
    x = [0]*len(V)
    for i in range(len(V)): # for (int i=0, i<len(v), i++)
        for j in range(len(V)):
            x[i] += M[i][j]*V[j]
    return x


# метод наискорейшего спуска
def mns(x0, eps1, eps2, N):
    def pd(x0):
        a, b, eps = -100, 100, 0.1**6
        delta = eps/2    # 0.1**2
        df = dF(x0)
        while True:
            x1 = (a+b-delta)/2
            newargX = [x0[i]-x1*df[i] for i in range(len(x0))]
            y1 = (a+b+delta)/2
            newargY = [x0[i]-y1*df[i] for i in range(len(x0))]
            if F(newargX) < F(newargY):
                b = y1
            else:
                a = x1
            if fabs(b-a) <= 2*eps:
                x1 = (a+b)/2
                return x1

    if norma(dF([1.5, 1.5])) < eps1:
        x_result = x0
    else:
        it = 0
        count = 0
        while True:
            s = v_multiply_k(dF(x0), -1)
            alpha = pd(x0)
            x = sumV(x0, v_multiply_k(s, alpha))
            if norma(diffV(x, x0)) < eps2 and fabs(F(x) - F(x0)) < eps2:
                count += 1
                x_result = x
                if count == 2: break
            x0 = x
            if it >= N:
                x_result = x
                break
            it += 1
    print('method наискорейшего спуска')
    print(f'iteration count: {it} \n{x_result = } \ngradient norm: {norma(dF(x))}')
    print('---------------------\n')


# метод Флетчера - Ривса
def mfr(x0, eps1, eps2, N):
    def pd(x0, s):
        a, b, eps = 0, 1, 0.1**6
        delta = eps/2    # 0.1**2
        df = s
        while True:
            x1 = (a+b-delta)/2
            newargX = [x0[i]+x1*df[i] for i in range(len(x0))]
            y1 = (a+b+delta)/2
            newargY = [x0[i]+y1*df[i] for i in range(len(x0))]
            if F(newargX) < F(newargY):
                b = y1
            else:
                a = x1
            if fabs(b-a) <= 2*eps:
                x1 = (a+b)/2
                return x1


    if norma(dF([1.5, 1.5])) < eps1:
        x_result = x0
    else:
        it = 0
        s = [0*len(x0) for i in x0]                    #
        beta = 0                                        #
        count = 0
        while True:
            s = sumV(v_multiply_k(dF(x0), -1), v_multiply_k(s, beta)) #
            alpha = pd(x0, s)
            x = sumV(x0, v_multiply_k(s, alpha))
            if norma(diffV(x, x0)) < eps2 and fabs(F(x) - F(x0)) < eps2:
                count += 1
                x_result = x
                if count == 2: break
            beta = norma(dF(x))**2 / norma(dF(x0))**2
            #
            x0 = x
            if it >= N:
                x_result = x
                break
            it += 1
    print('method Флетчера - Ривса')
    print(f'iteration count: {it} \n{x_result = } \ngradient norm: {norma(dF(x))}')
    print('---------------------\n')


# метод Ньютона
def mn(x0, eps1, eps2, N):
    def pd(x0, s):
        a, b, eps = -100, 100, 0.1**6
        delta = eps/2
        df = dF(x0)                      #########
        while True:
            x1 = (a+b-delta)/2
            newargX = [x0[i]-x1*df[i] for i in range(len(x0))]
            y1 = (a+b+delta)/2
            newargY = [x0[i]-y1*df[i] for i in range(len(x0))]
            if F(newargX) < F(newargY):
                b = y1
            else:
                a = x1
            if fabs(b-a) <= 2*eps:
                x1 = (a+b)/2
                return x1


    if norma(dF([1.5, 1.5])) < eps1:
        x_result = x0
    else:
        it = 0
        count = 0
        alpha = 1 
        while True:
            s = MVpr(inverse(ddF(x0)), v_multiply_k(dF(x0), -1))                #                                                   #
            x = sumV(x0, v_multiply_k(s, alpha))
            if norma(diffV(x, x0)) < eps2 and fabs(F(x) - F(x0)) < eps2:
                count += 1
                x_result = x
                if count == 2: break
            x0 = x
            if it >= N:
                x_result = x
                break
            it += 1
    print('method Ньютона')
    print(f'iteration count: {it} \n{x_result = } \ngradient norm: {norma(dF(x))}')
    print('---------------------\n')


#метод Ньютона - Рафсона
def mnr(x0, eps1, eps2, N):
    def pd(x0, s):
        a, b, eps = -100, 100, 0.1**6
        delta = eps/2
        df = v_multiply_k(s, -1)                      #########
        while True:
            x1 = (a+b-delta)/2
            newargX = [x0[i]-x1*df[i] for i in range(len(x0))]
            y1 = (a+b+delta)/2
            newargY = [x0[i]-y1*df[i] for i in range(len(x0))]
            if F(newargX) < F(newargY):
                b = y1
            else:
                a = x1
            if fabs(b-a) <= 2*eps:
                x1 = (a+b)/2
                return x1


    if norma(dF([1.5, 1.5])) < eps1:
        x_result = x0
    else:
        it = 0
        count = 0
        while True:
            s = MVpr(inverse(ddF(x0)), v_multiply_k(dF(x0), -1))                #
            alpha = pd(x0, s)                                                   #
            x = sumV(x0, v_multiply_k(s, alpha))
            if norma(diffV(x, x0)) < eps2 and fabs(F(x) - F(x0)) < eps2:
                count += 1
                x_result = x
                if count == 2: break
            x0 = x
            if it >= N:
                x_result = x
                break
            it += 1
    print('method Ньютона-Рафсона')
    print(f'iteration count: {it} \n{x_result = } \ngradient norm: {norma(dF(x))}')
    print('---------------------\n')


N = 1000
x0 = [1.5, 1.5]
eps1, eps2 = 0.1**5, 0.1**5
mns(x0, eps1, eps2, N)
mfr(x0, eps1, eps2, N)
mn(x0, eps1, eps2, N)
mnr(x0, eps1, eps2, N)
