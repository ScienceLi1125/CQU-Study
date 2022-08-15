'''买卖股票的最佳时机(只允许一次操作)
题目:给定一个数组,它的第i个元素是一支给定股票第i天的价格
    最多只允许完成一笔交易(即买入和卖出一支股票一次),设计一个算法来计算你所能获取的最大利润。
注意：你不能在买入股票前卖出股票。
输入样例:[7,1,5,3,6,4]
输出:5
解释: 在第2天买入,第5天卖出,最大利润=6-1=5
思路:遍历肯定超时,采用动态规划,遍历price。若当前price比价格最小值小,则更新最小值;若当前价格和价
    格最小值的差大于最大收益,则更新最大收益
        min_price=min{prices[i],min_price}
        profit=max{profit,prices[i]-min_price}
'''
price=[]
n=int(input())
for i in range(n):
    p=int(input())
    price.append(p)
min_price=100
profit=0
for i in range(n):
    min_price=min(min_price,price[i])
    profit=max(profit,price[i]-min_price)
print("Max profit:",profit)