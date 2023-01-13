#绘制二次B样条曲线
from matplotlib import pyplot as plt
import numpy as np

def Com(n,i):               #组合数
    numerator=1
    denominator=1
    for j in range(n,n-i,-1):
        denominator*=j
        numerator*=(n-j+1)
    return denominator/numerator
def factorial(n):           #阶乘
    ans=1
    for i in range(1,n+1):
        ans*=i
    return ans
def X_plus(x,n):            #n次截幂函数
    if(x>0):
        return pow(x,n)
    else:
        return 0
def M(n,x):                 #n阶B样条函数
    ans=0
    for i in range(n+1):
        ans+=pow(-1,i)*Com(n,i)*X_plus(x+n/2-i,n-1)
    return ans/factorial(n-1)
def S(m,t,P):               #P输入X则输出xi,输入Y则输出yi
    #0<=t<=1
    ans=0
    n=len(P)-1
    for i in range(n+1):
        ans+=P[i]*M(m+1,n*t-i)
    return ans

fig = plt.figure(figsize=(13,6))
plt.title('B-spline Curve(2)')
T=np.linspace(0,1,1000)
def Plot(X,Y,i):
    Xt=[]
    Yt=[]
    m=2
    a=0
    b=2*i
    if  i>3:
        a=2
        b-=8
    for j in range(len(T)):
        Xt.append(S(m,T[j],X))
        Yt.append(S(m,T[j],Y))
    plt.subplot2grid((4,8),(a,b),colspan=2,rowspan=2).set_title("fig%d"%(i+1))
    plt.plot(Xt,Yt,color='orangered',linewidth=3)
    plt.plot(X,Y,color='royalblue',marker='o')

X=[ [0,0.2,0.4,0.6,0.5,0.4,0.6,0.8,0.7,0.6],
    [0.5,0.5,0,0,0.5,0.7,1,1,1,1],
    [0,0,1,1,0,0],
    [0.5,0,1,0.5,1,0,0.5,0],
    [0,0,1,1,0.2,0.2,0.5,0.5,0.8,0.8,0,0],
    [0,1,1,1,0,0,0,1],
    [0,0.6,0.3,0.9],
    [0,0,0.6,0.9,0.3,0,0]   ]
Y=[ [1,1,1,1,0,-1,-1,-1,-0.5,0],
    [-1,0,-1,1,1,1,1,1,0,-1],
    [-1,1,1,-1,-1,1],
    [0,-1,-1,0,1,1,0,-1],
    [0,0,0,0,-1.77,-1.77,1,1,-1.77,-1.77,0,0],
    [-1,-1,-1,1,1,1,-1,-1],
    [-1,-1,1,1],
    [-1,-1,-1,1,1,-1,-1]    ]
for i in range(8):
    Plot(X[i],Y[i],i)

plt.subplots_adjust(0.05,0.05,0.95,0.95,hspace=0.8,wspace=0.8)
plt.show()