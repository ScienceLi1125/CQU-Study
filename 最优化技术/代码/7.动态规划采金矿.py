'''
    一个国家发现4座金矿,每座金矿黄金储量为200,300,350,400,500,需参与挖掘的工人数为3,4,3,5,5人。
现有10人可用,每座金矿要么挖要么不挖。求如何开采使得收益最大
'''
people=[0,3,4,3,5,5]            #调整从1开始
gold=[0,200,300,350,400,500]
N=5                             #金矿数量
M=10                            #工人数量
choice=[False for raw in range(N+1)]
dp=[[0 for col in range(M+1)]for row in range(N+1)]
def Gold_DP(n,m):
    for i in range(1,n+1):
        for j in range(1,m+1):
            dp[i][j]=dp[i-1][j]
            if j>=people[i] and dp[i-1][j-people[i]]+gold[i]>dp[i-1][j]:
                dp[i][j]=dp[i-1][j-people[i]]+gold[i]
    j=m
    for i in range(n,0,-1):
        if dp[i][j]>dp[i-1][j]:
            choice[i]=True
            j=j-people[i]
    Mv=dp[n][m]
    return Mv
# print(Gold_DP(N,M))
# for i in range(N+1):
#     for j in range(M+1):
#         print(dp[i][j],end=" ")
#     print()
print('最大价值为：',Gold_DP(N,M))
print('挖掘金矿：',choice[1:])