'''一维搜索算法——牛顿法
求解思路:根据牛顿法公式进行迭代,当|ak+1-ak|<e时迭代终止
    对一维牛顿法进行扩展,利用黑塞矩阵求解多维函数最小值
'''
import math
import numpy as np
from matplotlib import pyplot as plt

def function(x1,x2):        #原函数
    return 60-10*x1-4*x2+x1*x1+x2*x2-x1*x2

def derivative1_1(x1,x2):   #fx
    return -10+2*x1-x2
def derivative1_2(x1,x2):   #fy
    return -4+2*x2-x1

def derivative2_11(x1,x2):  #fxx
    return 2
def derivative2_12(x1,x2):  #fxy
    return -1
def derivative2_21(x1,x2):  #fyx
    return -1
def derivative2_22(x1,x2):  #fyy
    return 2
fig=plt.figure()            #绘图
ax1=plt.axes(projection='3d')

x0=float(input())           #迭代初值
y0=float(input())
e=1                         #判断终止条件
eps=0.001                   #阈值
k=0                         #迭代次数
print('初值:(',"{0:.1f}".format(x0),', ',"{0:.1f}".format(y0),')开始迭代')

while e>eps:
    x1=x0+(derivative1_1(x0,y0)*derivative2_22(x0,y0)-derivative1_2(x0,y0)*derivative2_12(x0,y0))/(derivative2_21(x0,y0)*derivative2_12(x0,y0)-derivative2_11(x0,y0)*derivative2_22(x0,y0))
    y1=y0+(derivative1_2(x0,y0)*derivative2_11(x0,y0)-derivative1_1(x0,y0)*derivative2_21(x0,y0))/(derivative2_21(x0,y0)*derivative2_12(x0,y0)-derivative2_11(x0,y0)*derivative2_22(x0,y0))
    e=max(abs(x1-x0),abs(y1-y0))    #取较大的|ak+1-ak|作为e
    x0=x1
    y0=y1
    k=k+1
    ax1.scatter([x0],[y0],[function(x0,y0)])
    print('迭代次数:',"{0:.0f}".format(k),',方程根的近似值为x=', "{0:.10f}".format(x1),',y=',"{0:.10f}".format(y1))
print('函数的极小值点:(',"{0:.10f}".format(x1),',',"{0:.10f}".format(y1),')', "极小值:","{0:.10f}".format(function(x1, y1)))

xx=np.arange(-10,10,0.1)
yy=np.arange(-10,10,0.1)
x,y=np.meshgrid(xx,yy)
z=np.array(60-10*x-4*y+x*x+y*y-x*y)
ax1.plot_surface(x,y,z,rstride=1,cstride=1,cmap='rainbow')
ax1.contour(x,y,z,stride=0.05,zdim='z',offset=-3,cmap='rainbow')
plt.show()