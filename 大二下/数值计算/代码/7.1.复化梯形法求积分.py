#复化梯形法求积分I=∫(0,1)e^x*dx,要求精度10^(-6)
#根据余项计算可知n取476,h=1/476,xk=k/476
from math import exp
import numpy as np
I=0.0
n=476
X=np.linspace(0,1,n+1)  #n等分是分成n个区间,实际上有n+1个节点
I+=(exp(X[0])+exp(X[n]))/2.0
for i in range(1,n):
    I+=exp(X[i])
I/=n
print(I)