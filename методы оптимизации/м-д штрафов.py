from math import fabs


def f(x):
    return 5*x[0]**2+x[1]**2-x[0]*x[1]+x[0]
    # return x[0]**2+x[1]**2

def g(x):
    return x[0]+x[1]-1
    # return x[0]+x[1]-2
def P(x, r):
    return r/2*g(x)**2


def F(x, r):
    return f(x)+P(x, r)


# метод наискорейшего спуска
def mns(x0, r, eps1=0.1**4, eps2=0.1**4, N=1000):
    def diffV(v1, v2):
        return [v1[i] - v2[i] for i in range(len(v1))]

    def v_multiply_k(v1, k):
        return [i * k for i in v1]

    def dF(x):
        h = 0.1 ** 6
        mas = []
        for i in range(len(x)):
            x1 = [x[j] if j != i else x[j] + h for j in range(len(x))]
            mas.append((F(x1, r) - F(x, r)) / h)
        return mas

    def norma(mas):
        return max([fabs(i) for i in mas])

    def sumV(v1, v2):
        return [v1[i] + v2[i] for i in range(len(v1))]


    def pd(x0):
        a, b, eps = -100, 100, 0.1 ** 6
        delta = eps / 2  # 0.1**2
        df = dF(x0)
        while True:
            x1 = (a + b - delta) / 2
            newargX = [x0[i] - x1 * df[i] for i in range(len(x0))]
            y1 = (a + b + delta) / 2
            newargY = [x0[i] - y1 * df[i] for i in range(len(x0))]
            if F(newargX, r) < F(newargY, r):
                b = y1
            else:
                a = x1
            if fabs(b - a) <= 2 * eps:
                x1 = (a + b) / 2
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
            if norma(diffV(x, x0)) < eps2 and fabs(F(x, r) - F(x0, r)) < eps2:
                count += 1
                x_result = x
                if count == 2: break
            x0 = x
            if it >= N:
                x_result = x
                break
            it += 1
    # print('method наискорейшего спуска')
    # print(f'iteration count: {it} \n{x_result = } \ngradient norm: {norma(dF(x))}')
    # print('---------------------\n')
    return x_result


x0, r0, c, eps, k = [1, 1], 1, 2, 0.1**4, 0
while True:
    x_new=mns(x0,r0)
    if fabs(P(x_new, r0))<=eps:
        break
    else:
        r0 = c*r0
        x0 = x_new
        k+=1
print(f'точка минимума: {x_new}')
print(f'значение в точке минимума = {f(x_new)}')
print(f'{g(x_new) = }')