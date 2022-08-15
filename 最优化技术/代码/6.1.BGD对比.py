import time
import random

n=100000
X0=[]
X1=[]
Y=[]
for i in range(n):
    r1=random.uniform(1.1,10.4)
    r2=random.uniform(1.1,10.4)
    r3=float(r1+2*r2)
    X0.append(r1)
    X1.append(r2)
    Y.append(r3)

time_start = time.time()
Theta=[[0,0]]                 #以首尾两点连线作为初值
epsilon=0.0001
a=0.01

def h_theta_xi(theta0,theta1,x0,x1):
    return theta0*x0+theta1*x1

def J_theta(theta0,theta1):         #目标函数，要求其最小值
    sum=0.0
    for i in range(n):
        sum+=pow(h_theta_xi(theta0,theta1,X0[i],X1[i])-Y[i],2)
    return sum/(2.0*float(n))
def dJ_theta0(theta0,theta1):       #J_theta对theta0的导数
    sum=0.0
    for i in range(n):
        sum+=(h_theta_xi(theta0,theta1,X0[i],X1[i])-Y[i])*X0[i]
    return sum/float(n)
def dJ_theta1(theta0,theta1):       #J_theta对theta1的导数
    sum=0.0
    for i in range(n):
        sum+=(h_theta_xi(theta0,theta1,X0[i],X1[i])-Y[i])*X1[i]
    return sum/float(n)
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
time_end = time.time()
time_c= time_end - time_start
theta0=Theta[cnt][0]-a*dJ_theta0(Theta[cnt][0],Theta[cnt][1])
theta1=Theta[cnt][1]-a*dJ_theta1(Theta[cnt][0],Theta[cnt][1])
theta=[theta0,theta1]
print('n=',n)
print('迭代次数：%d'%(cnt+1),'theta:',theta)
print('time cost', time_c, 's')