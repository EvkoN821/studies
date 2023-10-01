from tkinter import *
from tkinter import Tk, Label, StringVar, Button, Entry, Scrollbar
import copy
from math import fabs, gcd
from fractions import Fraction
from decimal import Decimal

def fun_open():
    def get_mat():
        matrix = []
        for i in range(int(a1[0])):
            matrix.append([])
            for j in range(int(a1[1])):
                matrix[i].append(text_var[i][j].get())

        def dp12(BA):
            def printres():
                b = 'баз ' + 'Cбаз    ' + 'A0  '
                for i in range(1, len(BAnum[0])):
                    b = b + 'A' + str(i) + '    '
                # print(b)
                BAres=resl()
                r=b+'\n'
                for i in range(len(BAres)):
                    r=r+str(base[i])+str(BAres[i])+'\n'
                return r
            def normal():
                for i in range (len(BAnum)):
                    for j in range (len(BAnum[i])):
                        k=gcd(int(abs(BAnum[i][j])),int(abs(BAden[i][j]))) if gcd(int(abs(BAnum[i][j])),int(abs(BAden[i][j])))!=0 else 1
                        BAnum[i][j]/=k
                        BAden[i][j]/=k
                        if (BAden[i][j]<0):
                            BAden[i][j]*=-1
                            BAnum[i][j]*=-1
                        if (fabs(BAnum[i][j])==0):
                            BAden[i][j], BAnum[i][j]=1, 0

            def resl():
                BAres=[[0]*len(BAnum[0])for i in range (len(BAnum))]
                for i in range (len(BAnum)):
                    for j in range (len(BAnum[0])):
                        BAres[i][j]=str(int(BAnum[i][j]))+'/'+str(int(BAden[i][j])) if BAden[i][j]!=1 else str(int(BAnum[i][j]))
                return BAres

            def res():
                BAres=[[0]*len(BAnum[0])for i in range (len(BAnum))]
                for i in range (len(BAnum)):
                    for j in range (len(BAnum[0])):
                        BAres[i][j]=BAnum[i][j]/BAden[i][j] if BAden[i][j]!=0 else BAnum[i][j]
                return BAres

            def lastline():
                for j in range(len(BAnum[0])):
                    for i in range(len(BAnum) - 1):
                        BAnum[-1][j] = BAnum[-1][j]*BAden[i][j] + base[i][1] * BAnum[i][j]*BAden[-1][j]
                        BAden[-1][j]*=BAden[i][j]
                    if (j > 0):
                        BAnum[-1][j] -= C[j - 1]*BAden[-1][j]

            def line(col):
                BAres1=res()
                x = [BAres1[i][0] / BAres1[i][col] if BAres1[i][col] != 0 else -1000 for i in range(len(BAnum) - 1)]
                x = [x[i] if x[i] > 0 else max(x) + 1 for i in range(len(x))]
                return x.index(min(x))

            def positivelastline(r1):
                BAres1 = res()
                k = min(BAres1[-1])
                while k < 0:
                    col = BAres1[-1].index(k)
                    lin = line(col)
                    d1 = BAnum[lin][col]
                    d2 = BAden[lin][col]
                    for i in range(len(BAnum[0])):
                        BAnum[lin][i] *= d2
                        BAden[lin][i] *= d1
                    base[lin][0] = col
                    base[lin][1] = C[base[lin][0] - 1]
                    for i in range(len(BAnum)):
                        if (i != lin):
                            d1 = BAnum[i][col]
                            d2 = BAden[i][col]
                            for j in range(len(BAnum[0])):
                                num = BAnum[i][j] * d2 * BAden[lin][j] - d1 * BAnum[lin][j] * BAden[i][j]
                                BAnum[i][j] = num
                                den = BAden[i][j] * d2 * BAden[lin][j]
                                den = den if den != 0 else 1
                                BAden[i][j] = den
                    normal()
                    r1=r1+printres()+'\n'
                    BAres1 = res()
                    k = min(BAres1[-1])
                normal()
                return r1

            def Gaus(A):
                n=len(A)
                A1=copy.deepcopy(A)
                for k in range (n):
                    for i in range (n+1):
                        A1[k][i]/=A[k][k]
                    for i in range (k+1,n):
                        d=A1[i][k]/A1[k][k]
                        for j in range(n+1):
                            A1[i][j]-=A1[k][j]*d
                    A=copy.deepcopy(A1)
                for k in range (n-1, -1, -1):
                    for i in range (n,-1, -1):
                        A1[k][i]/=A[k][k]
                    for i in range (k-1,-1,-1):
                        d=A1[i][k]/A1[k][k]
                        for j in range(n,-1, -1):
                            A1[i][j]-=A1[k][j]*d
                x=[0]*len(A)
                for i in range (n):
                    x[i]=A1[i][n]
                return x
            def norm(x):
                for j in range (len(x[0])):
                        k=gcd(int(abs(x[0][j])),int(abs(x[1][j]))) if gcd(int(abs(x[0][j])),int(abs(x[1][j])))!=0 else 1
                        x[0][j]/=k
                        x[1][j]/=k
                        x[0][j]=int(x[0][j])
                        x[1][j]=int(x[1][j])
                return x
            # a=[line.strip() for line in open("12.0.txt")]
            # BA=[a[i].split() for i in range (len(a))]
            for i in range (len(BA)):
                for j in range (len(BA[i])-BA[i].count(' ')):
                    BA[i][j]=int(BA[i][j])

            const=abs(min(map(min,BA)))+1 if min(map(min,BA))<=0 else 0 ##прибавление С если в матрице есть неположительные эл-ты
            if const !=0:
                for i in range (len(BA)):
                    for j in range (len(BA[0])):
                        BA[i][j]+=const

            minLin,maxCol=[],[]
            for i in range (len(BA)):
                minLin.append(min(BA[i]))
            at=[[0]*(len(BA)) for i in range (len(BA[i]))]
            for i in range(len(at)):
                for j in range(len(at[i])):
                    at[i][j]=BA[j][i]
            for i in range (len(at)):
                maxCol.append(max(at[i]))
            alpha, beta=max(minLin), min(maxCol)

            BAnum=copy.deepcopy(BA) #числитель
            x=[0]*(len(BA))
            for i in range (len(BA)):
                x[i]=1
                for j in range (len(x)):
                    BAnum[i].append(x[j])
                x[i]=0
                BAnum[i].insert(0,1)

            atnew=[[0]*(len(BAnum)) for i in range (len(BAnum[i]))]
            for i in range(len(atnew)):
                for j in range(len(atnew[i])):
                    atnew[i][j]=BAnum[j][i]
            atnew.pop(0)


            C = [1 if i<len(BA[0]) else 0 for i in range(len(BAnum[0]))]
            BAden=[[1]*len(BAnum[0]) for i in range (len(BAnum))] #знаменатель

            base = [[0] * 2 for i in range(len(BAnum))]
            normal()
            for i in range(len(base)):
                base[i][0] = len(BA[0])+i+1
                base[i][1] = C[base[i][0] - 1]
            base.append(['-', '-'])
            BAnum.append([0] * len(BAnum[0]))
            BAden.append([1] * len(BAnum[0]))
            lastline()
            r1=''
            r1=r1+printres()+'\n'
            r1=positivelastline(r1)
            l=[int(BAnum[-1][0]),int(BAden[-1][0])] #BAnum[-1][0]/BAden[-1][0]
            r2='\n'+'l = '+str(l[0])+'/'+str(l[1])
            v=[int(BAden[-1][0]),int(BAnum[-1][0])] #BAden[-1][0]/BAnum[-1][0]

            baset=[[0]*(len(base)) for i in range (len(base[i]))]
            for i in range(len(baset)):
                for j in range(len(baset[i])):
                    baset[i][j]=base[j][i]
            qz=[[0]*(len(BAnum[0])-1) for i in range (2)]
            for i in range (len(qz[0])):
                if i+1 in baset[0]:
                    #qz[i]=BAnum[baset[0].index(i+1)][0]/BAden[baset[0].index(i+1)][0]
                    qz[0][i]=BAnum[baset[0].index(i+1)][0]
                    qz[1][i]=BAden[baset[0].index(i+1)][0]
            print(qz)
            q=[[0]*(len(BA[0])) for i in range (2)]
            x=[[0]*(len(BA[0])) for i in range (2)]
            for i in range (len(BA[0])):
                q[0][i]=int(qz[0][i])
                q[1][i]=int(qz[1][i])
                x[0][i]=int(q[0][i]*v[0])
                x[1][i]=int(q[1][i]*v[1])
            qqq,xxx='[','['
            x=norm(x)
            q=norm(q)
            for i in range(len(q[0])):
                if q[1][i]==0:
                    qqq=qqq+str(q[0][i])+', '
                    xxx=xxx+str(x[0][i])+', '
                else:
                    qqq=qqq+str(q[0][i])+'/'+str(q[1][i])+', '
                    xxx=xxx+str(x[0][i])+'/'+str(x[1][i])+', '
            qqq=qqq[:-2]
            xxx=xxx[:-2]
            qqq,xxx=qqq+']', xxx+']'
            r2=r2+'\n'+'q = '+qqq
            P=[]
            for i in range (len(base)-1):
                P.append(atnew[base[i][0]-1])
                if 0 in P[i]: P[i].append(0)
                else: P[i].append(1)
            p=Gaus(P)
            #r2=r2+'\n'+'матрица по p: '+str(P)+'\n'+'p = '+str(p)+'\n'
            y=[round(p[i]*(v[0]/v[1]), 5) for i in range(len(p))]
            v[0]-=const*v[1]
            alpha-=const
            beta-=const
            ppp, yyy='[', '['
            for i in range (len(p)):
                ppp=ppp+str(Fraction.from_decimal(Decimal(str(p[i]))))+', '
                yyy=yyy+str(Fraction.from_decimal(Decimal(str(y[i]))))+', '
            ppp=ppp[:-2]
            yyy=yyy[:-2]
            ppp,yyy=ppp+']', yyy+']'
            r2=r2+'\n'+'матрица по p: '+str(P)+'\n'+'p = '+ppp+'\n'
            vvv=str(v[0])+'/'+str(v[1]) if v[1]!=1 else str(v[0])
            #otv='alpha = '+ str(alpha) + ';  beta = ' + str(beta) +';  c = '+str(const) +'\n'+'v = '+vvv+'\n'+'x = '+xxx+'\n'+'y = '+str(y)+'\n'
            otv='alpha = '+ str(alpha) + ';  beta = ' + str(beta) +';  c = '+str(const) +'\n'+'v = '+vvv+'\n'+'x = '+xxx+'\n'+'y = '+yyy+'\n'
            print (otv)
            return r1+printres()+r2+'\n'+otv

        resaaaaaaa=dp12(matrix)

        scrollbar = Scrollbar(orient="vertical")
        scrollbar.pack(side=RIGHT, fill=Y)
        text=Text(root,yscrollcommand=scrollbar, font=('arial', 10, 'bold'), bg="bisque2")
        text.insert(INSERT, resaaaaaaa)
        text.pack()
        # Label(root, text=resaaaaaaa, font=('arial', 10, 'bold'), bg="bisque2").place(x=200, y=320)


    a = entr.get()
    a1=a.split(' ')
    text_var = []
    entries = []
    Label(root, text="Введите матрицу :", font=('arial', 10, 'bold'),
      bg="bisque2").place(x=20, y=50)
    x2 = 0
    y2 = 50
    rows, cols = (int(a1[0]),int(a1[1]))
    for i in range(rows):
        text_var.append([])
        entries.append([])
        for j in range(cols):
            text_var[i].append(StringVar())
            entries[i].append(Entry(root, textvariable=text_var[i][j],width=3,bg="snow" ))
            entries[i][j].place(x=60 + x2, y=50 + y2)
            x2 += 30
        y2 += 30
        x2 = 0
    button1= Button(root,text="Решить", bg='bisque3', width=15, command=get_mat)
    button1.place(x=58,y=100+y2)


root=Tk()
root.configure(bg='mint cream')
root.title('Решение матричных игр')
root.geometry('700x600+300+225')
button = Button(root,text = 'Ввести', command = fun_open)
entr = Entry(root,bg="snow" )
label11 = Label(text="Введите количество строк и столбцов через пробел",bg="snow" )
label11.pack()
entr.pack(side = TOP)
button.pack(side = TOP)
root.mainloop()
