#迭代法求非线性方程的根
from math import fabs

def Iteration(x):
    return pow(1+x*x,1/3)

epsilon=0.0001
i=0
X=[1.5]
X.append(Iteration(X[i]))
i+=1
while(fabs(X[i]-X[i-1])>epsilon):
    X.append(Iteration(X[i]))
    i+=1
print(X[i])