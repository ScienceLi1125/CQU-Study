'''一维搜索算法——黄金分割法
求解思路:黄金分割法确定最小值,给定初始值a和b,比较f(a)和f(b),
    若f1>f2,则最小值必在[a1,b]中,另a=a1,继续迭代
    若f1<f2,则最小值必在[a,a2]中,另b=a2,继续迭代
    终止条件是b-a<e
'''
import math
import numpy as np
from matplotlib import pyplot as plt

def function(x):                    #原函数待寻找最小值,注意此处x>0
    return 8*math.exp(1-x)+7*math.log(x)

fig0=plt.figure(figsize=(7,5))
X=np.linspace(0.1,3,2000)
Y=[]
for i in range(len(X)):
    Y.append(function(X[i]))
plt.plot(X,np.array(Y))             #绘出图像
plt.title("Golden Section Method")
plt.legend(["f(x)=8e^(1-x)+7log(x)"])

def Golden_section(a,b,e):          #黄金分割法求最小值,注意输入满足a<b
    a1=a+0.382*(b-a)
    a2=a+0.618*(b-a)
    f1=function(a1)
    f2=function(a2)
    while(b-a>e):                   #e为精度,当|a-b|<e时搜索停止
        print('Internal value:[a:%s  b:%s]'%(a,b))      #输出中间结果
        plt.scatter([a,b],[function(a),function(b)])    #在图上绘制中间结果
        if(f1>f2):                  #若f1>f2,则最小值必在[a1,b]中,另a=a1,继续迭代
            a=a1
            a1=a2
            a2=a+0.618*(b-a)
            f1=f2
            f2=function(a2)
        else:                       #若f1<f2,则最小值必在[a,a2]中,另b=a2,继续迭代
            b=a2
            a2=a1
            a1=a+0.382*(b-a)
            f2=f1
            f1=function(a1)
    plt.scatter([a,b],[function(a),function(b)])
    return a,b,(a+b)/2.0

a=float(input())
b=float(input())
e=0.23
a,b,x=Golden_section(a,b,e)
print('Final answer:[a:%s  b:%s]'%(a,b))
print('min:%f'%function(x))
plt.show()