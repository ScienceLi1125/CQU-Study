#对20个随机点(直线加上随机数扰动)采用梯度下降法拟合一条直线
from matplotlib import pyplot as plt
import random

X=[]
Y=[]
for i in range(20):
    X.append(i+1)
    Y.append(2*i+10*random.random())

Theta=[[Y[0]-(Y[19]-Y[0])/19.0,(Y[19]-Y[0])/19.0]]  #以首尾两点连线作为初值
epsilon=0.1                         #允许梯度模
a=0.01                              #搜索步长即学习率，设为定值(a选取不当有可能使得theta发散)

def h_theta_xi(theta0,theta1,x):    #拟合直线方程
    return theta0+theta1*x

def J_theta(theta0,theta1):         #目标函数，要求其最小值
    sum=0.0
    for i in range(20):
        sum+=pow(h_theta_xi(theta0,theta1,X[i])-Y[i],2)
    return sum/40.0
def dJ_theta0(theta0,theta1):       #J_theta对theta0的导数
    sum=0.0
    for i in range(20):
        sum+=h_theta_xi(theta0,theta1,X[i])-Y[i]
    return sum/20.0
def dJ_theta1(theta0,theta1):       #J_theta对theta1的导数
    sum=0.0
    for i in range(20):
        sum+=(h_theta_xi(theta0,theta1,X[i])-Y[i])*X[i]
    return sum/20.0
def J_gradient(theta0,theta1):      #梯度模
    d_theta0=dJ_theta0(theta0,theta1)
    d_theta1=dJ_theta1(theta0,theta1)
    return d_theta0*d_theta0+d_theta1*d_theta1

cnt=0                               #记录迭代次数
gradient=J_gradient(Theta[cnt][0],Theta[cnt][1])
while(gradient>=epsilon*epsilon):   #开始迭代
    theta0=Theta[cnt][0]-a*dJ_theta0(Theta[cnt][0],Theta[cnt][1])
    theta1=Theta[cnt][1]-a*dJ_theta1(Theta[cnt][0],Theta[cnt][1])
    lst=[theta0,theta1]
    Theta.append(lst)
    cnt+=1
    gradient=J_gradient(Theta[cnt][0],Theta[cnt][1])
    # print("theta0:"+str(theta0)+"  theta1:"+str(theta1)+"  gradient:"+str(gradient))

#迭代完成后的theta值
theta0=Theta[cnt][0]-a*dJ_theta0(Theta[cnt][0],Theta[cnt][1])
theta1=Theta[cnt][1]-a*dJ_theta1(Theta[cnt][0],Theta[cnt][1])
print("theta0:"+str(theta0))
print("theta1:"+str(theta1))

Z=[]
for i in range(20):
    Z.append(theta0+theta1*X[i])
plt.title('linear regression')
plt.xlabel('x')
plt.ylabel('y')
plt.plot(X,Z,color='black',linewidth=1)         #拟合直线
plt.scatter(X,Y,color='royalblue',marker='o')   #原散点数据
plt.legend(['fitting line', 'scatter'])
plt.show()