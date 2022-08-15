#绘制Bezier曲线
from matplotlib import pyplot as plt
import numpy as np

def Com(n,i):               #组合数
    numerator=1
    denominator=1
    for j in range(n,n-i,-1):
        denominator*=j
        numerator*=(n-j+1)
    return denominator/numerator
def B_polynomial(k,n,t):    #n次Bernstein多项式基函数
    #参数要求：k<n,0<=t<=1
    return Com(n,k)*pow(t,k)*pow(1-t,n-k)
def B_curve(Z,t):           #n次Bezier曲线(输入X返回xi,输入Y返回yi)
    sum=0.0
    n=len(Z)-1
    for i in range(len(Z)):
        sum+=B_polynomial(i,n,t)*Z[i]
    return sum

X=[0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1]
Y=[-1,5,6.5,7,7.8,8,7.9,6,3,1,0]
T=np.linspace(0,1,1000)

plt.title('Bezier Curve')
plt.xlabel('t')
plt.ylabel('P')
plt.plot(B_curve(X,T),B_curve(Y,T),color='black',linewidth=1)         #拟合直线
plt.plot(X,Y,color='royalblue',marker='o')   #原散点数据
# plt.legend(['fitting line', 'scatter'])
plt.show()