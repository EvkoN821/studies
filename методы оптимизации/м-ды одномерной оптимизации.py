from math import fabs, sqrt


def f(x):
    return 2*x**2+2*x+7/2


# метод половинного деления (дихотомии)
def pd(a, b, eps):
    delta = float(input('input delta '))    # 0.1**2
    it = 0
    while True:
        it += 1
        x = (a+b-delta)/2
        y = (a+b+delta)/2
        # print (f' {it = } ', x, y, f(x), f(y))
        if f(x) < f(y):
            b = y
        else:
            a = x
        # print (f' {it = } ', a, b)
        if fabs(b-a) <= 2*eps:
            x = (a+b)/2
            print(f'result Dichotomy algorithm: {x = }')
            print(f'iteration count: {it} \n')
            return x


# метод фибоначи
def fib2(a, b, eps):
    alpha = float(input('input alpha '))
    fib1, fib2, fib3 = 1, 1, 1+1
    N = 2
    while fib3<(b-a)/(2*eps):
        N += 1
        fib1, fib2, fib3 = fib2, fib3, fib2+fib3
    print(f'{N = }')
    x = a + fib1/fib3*(b-a)
    y = a + b - x
    k = 1
    fx, fy = f(x), f(y)
    while k != (N-2):
        if fx > fy:
            a = x
            x = y
            y = a + b - x
            fx = fy
            fy = f(y)
        else:
            b = y
            y = x
            x = a + b - y
            fy = fx
            fx = f(x)
        k += 1
    y = y + alpha
    if f(x) < f(y):
        b = y
    else:
        a = x
    x = (a+b)/2
    print(f'result Fibonacci algorithm: {x = } \n')
    return x


# метод золотого сечения
def golden_section(a, b, eps):
    resphi = (3 - sqrt(5)) / 2
    x = a + resphi * (b - a)
    y = a + b - x
    fx, fy = f(x), f(y)
    it = 0
    while True:
        it += 1
        if fx < fy:
            b, y, fy = y, x, fx
            x = a + b - y
            fx = f(x)
        else:
            a, x, fx = x, y, fy
            y = b + a - x
            fy = f(y)
        if fabs(b - a) < 2*eps:
            x = (x+y) / 2
            print(f'result Golden Section algorithm: {x = }')
            print(f'iteration count: {it} \n')
            return x


a1 = int(input('input a '))              # -3
b1 = int(input('input b '))              # 7
eps1 = float(input('input eps '))         # 0.1**6
# pd(a1, b1, eps1)
fib2(a1, b1, eps1)
golden_section(a1, b1, eps1)
