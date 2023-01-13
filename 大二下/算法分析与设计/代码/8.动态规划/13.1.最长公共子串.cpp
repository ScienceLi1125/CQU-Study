/*最长公共子串：
题目：给定2个字符串，试求出这2个字符串的最长公共子串的长度。
输入：共2行，每行一个字符串。字符均为小写英文字母。
输出：仅一行，包含一个正整数，表示2个字符串的最长公共子串长度。
输入样例:
ababc
cbaab
输出样例:
2
数据范围与提示:
    对于30%的数据，保证字符串长度不超过10；
    对于60%的数据，保证字符串长度不超过100；
    对于90%的数据，保证字符串长度不超过1000；
    对于100%的数据，保证字符串长度不超过5000
思路：最长公共子串和最长公共子序列不同，要求子序列连续。为了得到连续的子序列，我们设dp[i][j]表示以
    Xi和Yj为结尾的最长公共子串(若Xi!=Yj则不能构成子串，即dp[i][j]=0)，这样不难得到递推关系式：
        dp[i][j] = dp[i-1][j-1]+1               (Xi==Yj)
                   0                            (Xi!=Yj)
*/
#include <iostream>
#include <vector>
using namespace std;

int main(){
    string X,Y;
    getline(cin,X);
    getline(cin,Y);
    int n=X.length();
    int m=Y.length();
    int max_len=0;
    int dp[110][110];           //记录Xi和Yj的最长公共子序列长度
    for(int i=0;i<=n;i++){      //初始化
        for(int j=0;j<=m;j++){
            dp[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(X[i-1]==Y[j-1]){ //注意i和j取值
                dp[i][j]=dp[i-1][j-1]+1;
                if(dp[i][j]>max_len){
                    max_len=dp[i][j];
                }
            }
            else{
                dp[i][j]=0;
            }
        }
    }
    cout<<max_len<<endl;

    return 0;
}