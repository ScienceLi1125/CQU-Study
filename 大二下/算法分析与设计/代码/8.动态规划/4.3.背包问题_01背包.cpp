/*背包问题_01背包：
题目：有N个物体，重量分别为wi，价值为vi，在总重量不超过容量C的情况下让总价值最高，但不允许只取
    走部分物体，要拿走只能整个拿走
思路：动态规划，用dp[i][j]表示前i件物品可以放入容量为j的袋子的最大价值，用W[i]表示第i件物品的
重量，V[i]表示第i件物品的价。因为j的取值是从0到C，所以不必担心超出C，只用考虑是否非负
    当i=i+1时，
        若j<W[i+1](即第i+1件物品重量大于袋子所剩容量)，那么无法放入，dp[i+1][j]=dp[i][j]
        若j>=W[i+1]，那么可以选择放或者不放：
            放的话，dp[i+1][j]=dp[i][j-W[i+1]]+V[i+1]
            不放的话，dp[i+1][j]=dp[i][j]
            取较大者即可
    由此得到状态转移方程：
        if(j>=W[i]){
            dp[i][j]=max{dp[i-1][j],dp[i-1][j-W[i]]+V[i]}
        }
        else{
            dp[i][j]=dp[i-1][j]
        }
    最后回溯可得最大价值的方法：从dp[N][C]开始，若dp[i][C]>dp[i-1][C]，则i号物品被装入袋中，
j-=W[i]，然后i--继续循环
*/
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int W[6]={0,6,1,2,5,4};         //第一个元素是0用以同步dp
    int V[6]={0,67,11,22,57,45};
    bool Choice[6]={0};
    int C;
    cin>>C;                         //参考值：8，ans：90
    int dp[6][C+1]={{0}};
    for(int i=0;i<=5;i++){          //初始化
        for(int j=0;j<=C;j++){
            dp[i][j]=0;
        }
    }

    for(int i=1;i<=5;i++){          //动态规划求得最大价值
        for(int j=1;j<=C;j++){
            if(j>=W[i]){
                if(dp[i-1][j]>dp[i-1][j-W[i]]+V[i]){
                    dp[i][j]=dp[i-1][j];
                }
                else{
                    dp[i][j]=dp[i-1][j-W[i]]+V[i];
                }
            }
            else{
                dp[i][j]=dp[i-1][j];
            }
        }
    }
    int j=C;
    for(int i=5;i>=0;i--){          //回溯得取舍方法
        if(dp[i][j]>dp[i-1][j]){
            Choice[i]=1;
            j-=W[i];
        }
    }

    cout<<"Largest profit: "<<dp[5][C]<<endl;
    cout<<"Method: ";
    for(int i=0;i<6;i++){
        if(Choice[i]==1){
            cout<<i<<" ";
        }
    }

    return 0;
}