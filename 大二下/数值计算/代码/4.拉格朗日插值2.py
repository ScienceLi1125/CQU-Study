from math import pi
from math import sin
import numpy as np
from matplotlib import pyplot as plt

def Lagrange(n,x):      #n次插值
    X=[]
    Y=[]
    for i in range(n+1):
        t=-2*pi+i*4*pi/n
        X.append(t)
        Y.append(sin(t))
    result=0.0
    for i in range(n+1):
        tmp0=1.0
        for j in range(n+1):
            if(j==i):
                continue
            else:
                tmp0*=(x-X[j])/(X[i]-X[j])
        tmp0*=Y[i]
        result+=tmp0
    return result

fig = plt.figure(figsize=(9,6))
plt.title('Lagrange accuracy')
X=np.linspace(-2*pi,2*pi,200)
plt.subplot2grid((4,10),(0,0),colspan=2,rowspan=2).set_title("sin(x)")
plt.plot(X,np.sin(X),'r')
plt.ylim(-2,2)
for i in range(2,11):
    a=0
    b=2*(i-1)
    if(i>5):
        a=2
        b=2*(i-6)
    plt.subplot2grid((4,10),(a,b),colspan=2,rowspan=2).set_title("p%d(x)"%i)
    plt.plot(X,Lagrange(i,X))
    plt.ylim(-2,2)      #设置范围
    A=[]
    for j in range(i+1):
        t=-2*pi+j*4*pi/(i)
        A.append(t)
    plt.scatter(A,np.sin(A))
plt.subplots_adjust(0.05,0.05,0.95,0.95,hspace=0.8,wspace=0.8)
plt.show()