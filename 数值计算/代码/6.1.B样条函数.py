#B样条函数(分段n-1次多项式)
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
    if x > 0:
        return pow(x,n)
    else:
        return 0
def M(n,x):                 #n阶B样条函数
    ans=0
    for i in range(n+1):
        ans+=pow(-1,i)*Com(n,i)*X_plus(x+n/2-i,n-1)
    return ans/factorial(n-1)

X=np.linspace(-10,10,1000)
Y=[]
n=4
for i in range(len(X)):
    Y.append(M(n,X[i]))

plt.title('B-spline Function')
plt.xlabel('x')
plt.ylabel('M')
plt.plot(X,Y,linewidth=1)
plt.show()