'''爬楼梯问题：
题目:输入n阶楼梯,每次可以爬1或2个台阶,用动态规划判断有多少种不同方法可以爬完楼梯
法二:动态规划,dp[i]=dp[i-1]+dp[i-2]
'''
import time

def climbStairs(n):
    Method=[0 for i in range(n+1)]
    Method[1]=1
    Method[2]=2
    if(n==1):       return 1
    elif(n==2):  return 2
    else:
        for i in range(3,n+1):
            Method[i]=Method[i-1]+Method[i-2]
        return Method[n]

n=int(input())

time_start = time.time()
solution=climbStairs(n)
time_end = time.time()
time_c= time_end - time_start
print("Solution:",solution)
print("Time of DP:",time_c)