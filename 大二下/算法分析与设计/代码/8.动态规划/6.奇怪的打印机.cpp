/*奇怪的打印机（Leetcode664）：
题目：有台奇怪的打印机有以下两个特殊要求：
    1.打印机每次只能打印同一个字符的序列
    2.每次可以在任意起始和结束位置打印新字符，并且会覆盖掉该位置原来已有的字符
    给定一个只包含小写英文字母的字符串s（长度不超过100），你的任务是计算这个打印机打印它需要的最
    少次数
样例1：
    输入: "aaabbb"
    输出: 2
    解释: 首先打印 "aaa" 然后打印 "bbb"
样例2：
    输入: "aba"
    输出: 2
    解释: 首先打印 "aaa" 然后在第二个位置打印 "b" 覆盖掉原来的字符 "a"
思路：最值问题首先想到动态规划
    设dp[i][j]表示打印i到j所有字符需要的最少次数，有两种情况：
    （1）如果s[i]==s[j]，说明打印i字符时可以顺带打印j字符，反过来说也是一样的。这种情况不会增
    加次数。即dp[i][j]=dp[i+1][j]或者dp[i][j-1]
    （2）如果s[i]!=s[j]，这时说明i和j位置的字符是无法同时打印的。这个时候需要分段处理，如果
    s[i]==s[k]或者s[j]==s[k] (i<k<j)，那么dp[i][j]=dp[i][k]+dp[k+1][j](s[i]==s[k])或者
    dp[i][k-1]+dp[k][j](s[j]==s[k])。对于多组相同值则取其中最小值即可
*/
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    string s=" aba";
    int len=s.length()-1;       //对数据略作修改，便于从1开始遍历
    int dp[len+1][len+1]={{0}};
    for(int i=1;i<=len;i++){
        dp[i][i]=1;
    }
    for(int l=2;l<=len;l++){
        for(int i=1;i<=len-l+1;i++){
            int j=i+l-1;
            if(s[i]==s[j]){     //不增加打印次数
                dp[i][j]=dp[i+1][j];        //dp[i+1][j]=dp[i][j-1]
                // cout<<"dp["<<i<<"]["<<j<<"]:"<<dp[i][j]<<endl;
            }
            else{
                dp[i][j]=dp[i+1][j]+1;      //增加一次打印次数
                for(int k=i+1;k<j;k++){
                    if(s[i]==s[k] && dp[i][j]>dp[i][k]+dp[k+1][j]){
                        dp[i][j]=dp[i][k]+dp[k+1][j];
                    }
                    else if(s[j]==s[k] && dp[i][j]>dp[i][k]+dp[k+1][j]){
                        dp[i][j]=dp[i][k-1]+dp[k][j];
                    }
                }
                // cout<<"dp["<<i<<"]["<<j<<"]:"<<dp[i][j]<<endl;
            }
        }
    }
    cout<<dp[1][len]<<endl;
    
    return 0;
}