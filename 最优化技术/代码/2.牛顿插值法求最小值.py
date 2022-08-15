#牛顿插值法求最小值，要求传入参数在最小值点附近
def function(x):                    #0<x<130
    # print(x*(350-2*x)*(260-2*x))
    return 4*pow(x,3)-1220*pow(x,2)+91000*x

def derivative1(x):
    return 12*pow(x,2)-2440*x+91000
    
def derivative2(x):
    return 24*x-2440

def recursion(x):                   #递推函数
    return x-derivative1(x)/derivative2(x)

def Newton_interpolation(x,e):      #e为控制误差
    a0=x
    a1=recursion(a0)
    while(abs(a0-a1)>e):
        a0=a1
        a1=recursion(a1)
    return a1

min=function(Newton_interpolation(150,0.01))
print('min:%s'%min)