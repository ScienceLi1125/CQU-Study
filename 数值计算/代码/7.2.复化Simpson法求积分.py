#复化Simpson法求积分I=∫(0,1)e^x*dx,要求精度10^(-6)
#根据余项计算可知n取6,h=1/6,xk=k/6
from math import exp
import numpy as np
I=0.0
n=6
I+=(exp(0)+exp(1))
for i in range(0,n):
    I+=4*exp((i+0.5)/n)
for i in range(1,n):
    I+=2*exp(i/n)
I/=(6*n)
print(I)