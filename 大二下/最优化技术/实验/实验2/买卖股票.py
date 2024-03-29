'''买卖股票:
题目:判定买卖股票的最佳时机。自行给定一个数组,它的第i个元素是一支给定股票第i天价格。设计一个算法
    来计算你所能获取的最大利润。注意你不能在买入股票前卖出股票,不能同一天进行多次交易。
输入样例:
[7,1,3,5,4,6]
输出样例:
6
思路:股票买卖显然需要先买再卖,每天的状态只有手里有股票和无股票两种,设dp[i][0]表示第i天手里没有股
    票可得的最大收益,dp[i][1]表示第i天手里有股票可得的最大收益(手中股票不能折现,第一次买入后手中
    收益为负)。每天的收益均由前一天决定,若当天手中有股票,则可能今天买入或前一天手中有股票;若当天
    手中没有股票,则可能前一天卖出或者前一天手中没股票。显然有递推关系式:
        dp[i][0]=max{dp[i-1][0],dp[i-1][1]+price[i]}    #前一天手里没股票或今天卖了股票
        dp[i][1]=max{dp[i-1][1],dp[i-1][0]-price[i]}    #前一天手中有股票或今天买入
'''
price=[]
def Stock(n):
    dp=[[0 for col in range(2)] for row in range(n)]
    dp[0][0]=0
    dp[0][1]=-1*price[0]
    for i in range(1,n):
        dp[i][0]=max(dp[i-1][0],dp[i-1][1]+price[i])    #前一天手里没股票或今天卖了股票
        dp[i][1]=max(dp[i-1][1],dp[i-1][0]-price[i])    #前一天手中有股票或今天买入
    return dp[n-1][0]                                   #最后一天必须卖出

n=int(input())

for i in range(n):
    p=int(input())
    price.append(p)
profit=Stock(n)

print("profit:",profit)