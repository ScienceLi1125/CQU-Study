#矩阵的LU分解求解方程

#输入增广矩阵
print("请输入矩阵的行列数")     #行列数必须相同才能解方程
n=int(input())
print("请输入系数矩阵A")
A=[]
for i in range(n):
    Ai=[]
    for j in range(n):
        a=float(input())
        Ai.append(a)
    A.append(Ai)
print("请输入向量b")
b=[]
for i in range(n):
    bi=float(input())
    b.append(bi)

#初始化L和U，注意要用float
L=[]            #对角线为1，上三角为0
for i in range(n):
    Li=[]
    for j in range(n):
        if(i==j):
            Li.append(1.0)
        elif(i<j):
            Li.append(0.0)
        else:
            Li.append(-1.0)
    L.append(Li)
U=[]            #下三角为0
for i in range(n):
    Ui=[]
    for j in range(n):
        if(i>j):
            Ui.append(0.0)
        else:
            Ui.append(-1.0)
    U.append(Ui)

#求解L和U
for i in range(n):
    for j in range(i,n):    #计算第i行
        sum=0.0
        for k in range(i):  #需要i个相加，所以不能是i-1!!!(此处卡bug一天...)
            sum+=L[i][k]*U[k][j]
        u=A[i][j]-sum
        U[i][j]=u
    for j in range(i+1,n):  #计算第i列
        sum=0.0
        for k in range(i):
            sum+=L[j][k]*U[k][i]
        l=float((A[j][i]-sum)/U[i][i])
        # if(i==0):
        #     print(str(A[j][i]-sum)+str(U[i][i])+str(l))
        L[j][i]=l
# print(L)
# print(U)

#通过方程Ly=b求y
Y=[]
for i in range(n):
    sum=0.0
    for j in range(i):
        sum+=L[i][j]*Y[j]
    y=b[i]-sum
    Y.append(y)
print(Y)
X=[]
#X是从n-1位向0位求解的，因此不能直接append，否则index out of range
# for i in range(n-1,-1,-1):
#     sum=0
#     for j in range(i+1,n):
#         sum+=U[i][j]*X[j]
#     x=(Y[i]-sum)/U[i][i]
#     X.append(x)
#采用先初始化再修改
for i in range(n):
    X.append(-1)
for i in range(n-1,-1,-1):
    sum=0.0
    for j in range(i+1,n):
        sum+=U[i][j]*X[j]
    x=float((Y[i]-sum)/U[i][i])
    X[i]=x
print(X)

'''
测试用例:
输入
4
15
7
0
10
6
18
15
9
0
10
28
7
5
0
6
35
8
6
4
2
输出
[35.0, -79.5, 12.42857142857143, -28.507575757575758]
[-2.4494837924349664, 3.007799468013164, -0.04557955006537176, 1.0178982011631574]
'''