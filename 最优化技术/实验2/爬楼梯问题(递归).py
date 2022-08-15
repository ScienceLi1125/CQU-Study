'''爬楼梯问题：
题目:输入n阶楼梯,每次可以爬1或2个台阶,用动态规划判断有多少种不同方法可以爬完楼梯
法一:递归
'''
import time
def climbStairs(n):
    if(n==1):       return 1
    elif(n==2):  return 2
    else:
        c1=climbStairs(n-1)     #爬1层
        c2=climbStairs(n-2)     #爬2层
        return c1+c2

n=int(input())

time_start = time.time()
solution=climbStairs(n)
time_end = time.time()
time_c= time_end - time_start
print("Solution:",solution)
print("Time of Recursion:",time_c)