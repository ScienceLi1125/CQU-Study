'''对数几率回归:
    对于非线性分布的数据,需要用广义线性模型加以变换:g(y)=w.T*x+b
    对于二分类问题,可以使用逻辑回归模型ln(y/(1-y))=wT*x+b,通过梯度下降法或牛顿法等迭代法确定w和b
    该模型并不能在坐标系中绘制出一条曲线将两类样本区分,而是对输入的x,计算出对应的分类值y
    分类值y越接近1,正类的可能性越大;y越接近0,负类的可能性越大
    为了方便矩阵运算,令beta=(w1,w2,...,wd,b),x_new=(x1,x2,...,xd,1),则w.T*x+b变成beta.T*x_new
    由于训练时读取到的data是m个x_new的集合,维数m*(d+1),因此计算beta.T*x_new时需要将data转置
'''
import numpy as np
from matplotlib import pyplot as plt

def load_dataset():
    file = open(r'ML\data\melon3_dataset.txt')
    data = []
    label = []
    for line in file.readlines():
        lineArr = line.strip().split()  #先移除首尾空格再切割
        data.append([float(lineArr[0]), float(lineArr[1]), 1.0])
        label.append(int(lineArr[2]))
    return data, label

def sigmoid(X):
    return 1/(1+np.exp(-X))

def lbeta(X,y,beta):        #目标函数求最小值,结果是一个单值
    '''args:
        X:x_new的集合,m*(d+1)
        y:标签的集合,1*m
        beta:待求参数,1*(d+1)
    '''
    beta_x=beta*X.transpose()           #beta*X.T
    ln_beta_x=np.log(1+np.exp(beta_x))  #ln(1+e**beta*X.T)
    lb=0.0
    for i in range(len(y)):
        lb+=-y[i]*beta_x[i]+ln_beta_x[i]
    return lb

def lbeta_1stderivative(X,y,beta):      #lbeta的一阶导
    beta_x=beta*X.transpose()
    p1=np.exp(beta_x)/(1+np.exp(beta_x))
    #ubfinished


def mat_plot(dataMatrix, labelMatrix, weights):
    fig = plt.figure()
    ax = fig.add_subplot(111)
    n = np.shape(dataMatrix)[0]
    for i in range(n):
        if labelMatrix[i] == 1:
            ax.scatter(dataMatrix[i, 1], dataMatrix[i, 2], c='r')
        else:
            ax.scatter(dataMatrix[i, 1], dataMatrix[i, 2], c='b')
    x = np.arange(0, 1, 0.01)
    y = (-weights[0] - weights[1] * x) / weights[2]
    ax.plot(x, y)
    plt.xlim(0, 1)
    plt.ylim(0, 0.5)
    plt.show()


def model():
    data, label = load_dataset()
    dataMatrix = np.mat(data).transpose()   # 数组转换成矩阵并作转置(m*(d+1)->(d+1)*m)
    labelMatrix = np.mat(label)
    d, m = np.shape(dataMatrix)             # m为样本个数,d为样本属性数(实际上只有d-1个属性,因为有一个1)
    alpha = 0.001
    maxCycles = 500                         # 梯度下降法求beta
    beta = np.ones((1, d))                  # beta初始化为全1数组
    for i in range(maxCycles):
        h = sigmoid(beta*dataMatrix)        #预测值->分类标签
        error = (labelMatrix - h)           #误差值
        gradient = dataMatrix * error.transpose()
        beta += alpha * gradient
    mat_plot(dataMatrix, labelMatrix, beta)


if __name__ == '__main__':
    model()
