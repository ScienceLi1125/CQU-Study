'''线性回归:
    一元线性回归只适用于每个样本只有一个属性的情况,当样本属性不止一个时,就需要用到多元线性回归
    多元线性回归涉及矩阵运算,手写代码不太容易,此处调用sklearn包辅助运算
    最终求得的w是一个列向量,由于x是多维向量,绘制f(x)=w.T*x+b有些困难,因此将横坐标改为样本编号
'''
import numpy as np
from matplotlib import pyplot as plt
from sklearn.linear_model import LinearRegression as lr

#训练集
X_train=[[8,11],[9,8.5],[11,15],[16,18],[12,11]]
y_train=[[9.7759],[10.7522],[12.7048],[17.5863],[13.6811]]
model=lr()
model.fit(X_train,y_train)
#测试集
X_test=[[8,2],[9,0],[11,2],[16,2],[12,0]]
y_test=[[11],[8.5],[15],[18],[11]]
prediction=model.predict(X_test)
#绘图(序号为x轴,预测值/真实值为y轴)
plt.figure()
plt.title('Linear Regression')
plt.xlabel('number')
plt.ylabel('prediction & reality')
plt.grid(True)
plt.plot(prediction)
plt.plot(y_test)
plt.legend(['prediction', 'reality'])
plt.show()