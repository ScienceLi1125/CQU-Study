'''买卖股票的最佳时机(允许无限次操作)
题目:给定一个数组,它的第i个元素是一支给定股票第i天的价格
    允许完成无数笔交易,设计一个算法来计算你所能获取的最大利润。
注意：你不能在买入股票前卖出股票。
输入样例:[1,2,3,5,2]
输出:4
思路:比较相邻的值,只要赚就买(同刘大师买股票)
'''
price=[]
n=int(input())
for i in range(n):
    p=int(input())
    price.append(p)
profit=0
for i in range(n-1):
    if(price[i+1]>price[i]):
        profit+=price[i+1]-price[i]
print("Max profit:",profit)