#Romberg法求积分I=∫(0,1)e^x*dx,要求精度10^(-6)
#终止条件为|Rn+1-Rn|<10^(-6)
from math import exp
import numpy as np
def funct(x):
    return exp(x)
def T(n):
    ans=funct(0)+funct(1)
    for i in range(1,n):
        ans+=2*funct(i/n)
    ans/=(2*n)
    print("T(%d)=%.10f"%(n,ans))
    return ans
def S(n):
    ans=(4*T(2*n)-T(n))/3.0
    print("S(%d)=%.10f"%(n,ans))
    return ans
def C(n):
    ans=(16*S(2*n)-S(n))/15.0
    print("C(%d)=%.10f"%(n,ans))
    return ans
def R(n):
    ans=(64*C(2*n)-C(n))/63.0
    print("R(%d)=%.10f"%(n,ans))
    return ans
for i in range(1,100):
    if(R(i+1)-R(i)<10**(-6)):
        print("R(%d)=%.10f"%(i,R(i)))
        break
