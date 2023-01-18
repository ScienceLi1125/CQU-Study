'''线性回归:
    通过最小二乘法求得参数以准确预测结果
'''
import numpy as np
from matplotlib import pyplot as plt

def linear_regression(x,y):
    '''线性回归公式:
    w=Σ(yi*(xi-x_mean))/(Σ(xi*xi)-(Σxi)**2/m)
    b=Σ(yi-w*xi))/m
    '''
    x_mean=np.mean(np.array(x),axis=0)
    x_sum=np.sum(np.array(x))
    x_square_sum=0
    y_x=0
    m=len(x)
    for i in range(m):
        y_x+=y[i]*(x[i]-x_mean)
        x_square_sum+=x[i]**2
    w=y_x/(x_square_sum-x_sum**2/m)
    b=0
    for i in range(m):
        b+=y[i]-w*x[i]
    b/=m
    return w,b

x1=[6,8,10,14,18]
y1=[7,9,13,17.5,18]
w,b=linear_regression(x1,y1)

x2=np.linspace(0,25,100)
y2=w*x2+b

plt.figure(figsize=(8,6))
plt.title('Linear Regression')
plt.scatter(x1,y1)
plt.plot(x2,y2)
plt.xlabel("Recall")
plt.ylabel("Precision")
plt.show()