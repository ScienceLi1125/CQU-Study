'''买卖股票的最佳时机(只允许两次操作)
题目:给定一个数组,它的第i个元素是一支给定股票第i天的价格
    只允许完成两笔交易,设计一个算法来计算你所能获取的最大利润。
注意: 你不能同时参与多笔交易(你必须在再次购买前出售掉之前的股票)。
输入样例:[3,3,5,0,0,3,1,4]
输出:6
思路:相当于4层的状态转移图,找出该问题每天的4个状态:一次都没买、买一次、买卖一次、买卖买、买卖买卖,
    分别记为S0[i]、S1[i]、S2[i]、S3[i]、S4[i],且转化关系为S0—>S1—>S2—>S3—>S4,则有递推关系:
        S0[i]=S0[i-1]
        #第i天买一次可能是前一天买的,也可能是前一天没买今天买的
        S1[i]=max(S1[i-1],S0[i-1]-price[i])
        #第i天买卖一次可能是前一天卖的,也可能是前一天买了一次今天卖的
        S2[i]=max(S2[i-1],S1[i-1]+price[i])
        #第i天买卖买可能是前一天买卖买的,也可能是前一天买卖今天买的
        S3[i]=max(S3[i-1],S2[i-1]-price[i])
        #第i天买卖买卖可能是前一天买卖买卖的,也可能是前一天买卖买今天卖的
        S4[i]=max(S4[i-1],S3[i-1]+price[i])
'''
price=[]
n=int(input())
for i in range(n):
    p=int(input())
    price.append(p)
S0=[0 for i in range(n)]
S1=[0 for i in range(n)]
S2=[0 for i in range(n)]
S3=[0 for i in range(n)]
S4=[0 for i in range(n)]
S1[0]=-1*price[0]
S3[0]=-1*price[0]
# print(S0,S1,S2,S3,S4)
for i in range(1,n):
    S0[i]=S0[i-1]
    S1[i]=max(S1[i-1],S0[i-1]-price[i])
    S2[i]=max(S2[i-1],S1[i-1]+price[i])
    S3[i]=max(S3[i-1],S2[i-1]-price[i])
    S4[i]=max(S4[i-1],S3[i-1]+price[i])
    # print(S0,S1,S2,S3,S4)
    
print("Max profit:",S4[n-1])