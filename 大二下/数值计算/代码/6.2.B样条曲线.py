#绘制B样条曲线
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

X=[0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1]
Y=[-1,5,6.5,7,7.8,8,7.9,6,3,1,0]
T=np.linspace(0,1,1000)
Xt=[]
Yt=[]
m=3
for i in range(len(T)):
    Xt.append(S(m,T[i],X))
    Yt.append(S(m,T[i],Y))

plt.title('B-spline Curve')
plt.xlabel('t')
plt.ylabel('S')
plt.plot(Xt,Yt,color='orangered',linewidth=3)         #拟合直线
plt.plot(X,Y,color='royalblue',marker='o')   #原散点数据
plt.show()