from math import pi
from math import sin
import numpy as np
from matplotlib import pyplot as plt
from matplotlib.ticker import MultipleLocator,FuncFormatter

def pi_formater(x,idx):
    # "将刻度值x转换成对应的刻度文本"
    # print("inside pi_formater, x=",x,"idx:",idx)
    return "$%.1f\pi$" % (x / np.pi)

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

fig,ax = plt.subplots(figsize=(10,5))
plt.title('Lagrange accuracy')
ax.xaxis.set_major_locator(MultipleLocator(np.pi/2))
ax.xaxis.set_minor_locator(MultipleLocator(np.pi/10))
ax.xaxis.set_major_formatter(FuncFormatter(pi_formater))
X=np.linspace(-2*pi,2*pi,200)
plt.plot(X,np.sin(X),marker='o',markersize=3)
for i in range(2,11):
    plt.plot(X,Lagrange(i,X))

plt.legend(['sin(x)','p2','p3','p4','p5','p6','p7','p8','p9','p10'])
plt.show()