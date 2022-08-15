#黄金分割法求最大值
def function(x):                    #0<x<130
    return 4*pow(x,3)-1220*pow(x,2)+91000*x

def Interval_search(start,step):
    step=abs(step)
    a1=start
    a2=a1+step
    f1=function(a1)
    f2=function(a2)
    while(f1!=f2):
        if(f1>f2):                  #确定进 or 退
            tmp=a1
            a1=a2
            a2=tmp
            tmpf=f1
            f1=f2
            f2=tmpf
            step*=(-1)              #反向寻找

        a3=a2+step
        f3=function(a3)
        if(f2>=f3):
            return a1,a3
        else:
            step*=2
            a1=a2
            a2=a3
            f1=f2
            f2=f3

    return a1,a2

def Golden_section(a,b,e):          #a<b
    a1=a+0.382*(b-a)
    a2=a+0.618*(b-a)
    f1=function(a1)
    f2=function(a2)
    while(b-a>e):
        if(f1>f2):                  #与求最小值相反
            b=a2
            a2=a1
            a1=a+0.382*(b-a)
            f2=f1
            f1=function(a1)
        else:
            a=a1
            a1=a2
            a2=a+0.618*(b-a)
            f1=f2
            f2=function(a2)
    return (a+b)/2.0

a,b=Interval_search(0,10)
x=Golden_section(a,b,0.001)
print('a:%s  b:%s'%(a,b))
print('x:%s'%x)
print('min:%f'%function(x))