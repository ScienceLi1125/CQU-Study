#幂法计算矩阵主特征值
import math
import copy
def MatrixCal(A,v):     #A为n*n矩阵,v为n*1矩阵,计算A*v
    ans=[]
    for i in range(len(v)):
        tmp=0.0
        for j in range(len(v)):
            tmp+=A[i][j]*v[j]
        ans.append(tmp)
    return ans
def max_v(V):           #V为n*1矩阵,计算按模最大分量并返回最大值、下标和最大值符号
    index=0
    value=0
    sign=1
    for i in range(len(V)):
        if(math.fabs(V[i])>value):
            index=i
            value=math.fabs(V[i])
    if(V[index]<0):
        sign=-1
    return index,value,sign

# A=[[7,3,-2],[3,4,-1],[-2,-1,3]]
A=[[3,-4,3],[-4,6,3],[3,3,1]]
v0=[1,1,1]
# A=[[-1,3],[3,-1]]
# v0=[1,1]
eps=0.0001              #迭代终止条件
V=[]                    #存储特征向量
lam=[]                  #存储特征值
b0=1                    #按模最大特征值
b1=10                   #能进入循环即可
while(math.fabs(b1-b0)>=eps):
    b0=b1
    v1=MatrixCal(A,v0)
    index,b1,sign=max_v(v1)
    a=sign*b1           #b1为按模最大特征值，a为b1实际特征值(含符号)
    v0=v1.copy()        #注意拷贝而不是赋值
    v0=[v0[i]/b1 for i in range(len(v0))]
    lam.append(b1)
    V.append(v0)

for i in range(len(lam)):
    print("lam=",lam[i]," v=",V[i])
print("Final ans:\nlam1=",lam[len(lam)-1])
print("x1=",V[len(V)-1])