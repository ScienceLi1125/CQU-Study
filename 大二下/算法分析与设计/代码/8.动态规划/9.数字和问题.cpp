/*求解数字和为sum的方法数问题(动态规划法)：
题目：求解数字和为sum的方法数问题。给定一个有n个正整数的数组a和一个整数sum，求选择数组a中部分数字
    和为sum的方案数。若两种选取方案有一个数字的下标不一样，则认为是不同的方案。
输入：第1行为两个正整数n(1≤n≤1000)，sum(1≤sum≤1000)，第2行为n个正整数ai，以空格隔开
输出：方案数
输入样例：
5 15
5 5 10 2 3
输出样例：
4 
思路：和凑零钱思路相同，用dp[i][j]表示前i个数能构成和小于等于j的方案数，sum[i][j]表示前i个数能构
    成和小于等于j的最大和
        sum[i][j]=max{sum[i-1][j],sum[i][j-a[i]]+a[i]}
    dp[i][j]对应dp[i-1][j]或dp[i][j-a[i]]，当sum[i-1][j]=sum[i][j-a[i]]+a[i]时方案数+1
*/
#include <iostream>
using namespace std;
#define MAXN 1001
#define MAXS 1001

int a[MAXN];
long dp[MAXN][MAXS];
int n,sum;
long solve();

int main(){
    cin>>n>>sum;    
    for(int i=1;i<=n;i++)
       cin>>a[i];
    cout<<solve();
    return 0;
}

long solve(){
    int Sum[MAXN][MAXS];
    for(int i=0;i<=MAXN;i++){
        Sum[i][0]=0;
        dp[i][0]=0;
    }
    for(int j=0;j<=MAXS;j++){
        Sum[0][j]=0;
        dp[0][j]=0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=sum;j++){
            if(j>=a[i]&&Sum[i-1][j]<Sum[i][j-a[i]]+a[i]){
                Sum[i][j]=Sum[i][j-a[i]]+a[i];
                dp[i][j]=dp[i][j-a[i]];
            }else if(j>=a[i]&&Sum[i-1][j]==Sum[i][j-a[i]]+a[i]){
                Sum[i][j]=Sum[i][j-a[i]]+a[i];
                dp[i][j]=dp[i][j-a[i]]+1;
            }else{
                Sum[i][j]=Sum[i-1][j];
                dp[i][j]=dp[i-1][j];
            }
        }
    }
//     for(int i=1;i<=n;i++){
//         for(int j=1;j<=sum;j++){
//             cout<<Sum[i][j]<<" ";
//         }
//         cout<<endl;
//     }
//     cout<<endl;
//     for(int i=1;i<=n;i++){
//         for(int j=1;j<=sum;j++){
//             cout<<dp[i][j]<<" ";
//         }
//         cout<<endl;
//     }
    if(Sum[n][sum]==sum){
        return dp[n][sum];
    }
    else{
        return 0;
    }
}