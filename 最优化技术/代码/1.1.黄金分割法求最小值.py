#进退法确定搜索区间——>黄金分割法确定最小值
# def function(x):
#     return pow(x,3)-3*pow(x,2)+2*x
def function(x):
    return x+1/x

def Interval_search(start,step):
    step=abs(step)                  #step>0
    a1=start
    a2=a1+step
    f1=function(a1)
    f2=function(a2)
    while(f1!=f2):
        if(f1<f2):                  #确定进 or 退
            tmp=a1
            a1=a2
            a2=tmp
            tmpf=f1
            f1=f2
            f2=tmpf
            step*=(-1)              #反向寻找

        a3=a2+step
        f3=function(a3)
        if(f2<=f3):
            return a1,a3
        else:
            step*=2
            a1=a2
            a2=a3
            f1=f2
            f2=f3

    return a1,a2

def Golden_section(a,b,e):          #a<b,e为精度
    a1=a+0.382*(b-a)
    a2=a+0.618*(b-a)
    f1=function(a1)
    f2=function(a2)
    while(b-a>e):
        if(f1>f2):
            a=a1
            a1=a2
            a2=a+0.618*(b-a)
            f1=f2
            f2=function(a2)
        else:
            b=a2
            a2=a1
            a1=a+0.382*(b-a)
            f2=f1
            f1=function(a1)
    return (a+b)/2.0

# a,b=Interval_search(1,0.1)
# x=Golden_section(a,b,0.0001)
a,b=Interval_search(0.01,0.1)
x=Golden_section(a,b,0.0001)
print('a:%s  b:%s'%(a,b))
print('min:%f'%function(x))