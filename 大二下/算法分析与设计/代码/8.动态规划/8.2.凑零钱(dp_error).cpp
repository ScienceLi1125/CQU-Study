/*凑零钱：
    dfs容易超时，下采用dp
    用bool dp[i][j]表示采用前i种货币能否凑出面额为j的零钱。若j<coins[i]，即第i种面值太大，无法
加入j，此时dp[i][j]=dp[i-1][j]；若j>=coins[i]，那么只要dp[i-1][j]或者dp[i-1][j-coins[i]非零，
则dp[i][j]=1，否则为零。
    易得出递推关系式：
        dp[i][j]=   dp[i-1][j]  (j<=coins[i])
                    1 (if dp[i-1][j]!=0 || dp[i-1][j-coins[i]]!=0) else 0
    为了记录凑零钱最小序列，x需要开一个二维数组记录上述判断时dp[i-1][j]和dp[i-1][j-coins[i]都
为0时两种情况的较小序列，判断起来相当麻烦
    （鉴于VSCode编译不了太大的二维数组(段错误)，先用105*105写）
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int N,M;
    cin>>N>>M;
    int coins[105]={0};
    for(int i=1;i<=N;i++){
        cin>>coins[i];
    }
    sort(coins+1,coins+N+1);
    bool dp[105][105];        //记录前i种货币能否凑出面额为j的零钱
    int choice[105][105];     //记录决策，0-无解，1~2-dp[i-1][j]/dp[i-1][j-coins[i]]，3-开头

    for(int i=0;i<105;i++){   //初始化
        for(int j=0;j<105;j++){
            dp[i][j]=0;
            choice[i][j]=0;
            if(i>0 && j>0 && j==coins[i]){
                dp[i][j]=1;
                choice[i][j]=3; //表示序列开头
            }
        }
    }

    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
            if(j<coins[i]){
                dp[i][j]=dp[i-1][j];
                choice[i][j]=1;
            }
            else if(dp[i-1][j-coins[i]]!=0){
                dp[i][j]=1;
                choice[i][j]=2;
            }
            else if(dp[i-1][j]!=0){
                dp[i][j]=1;
                choice[i][j]=1;
            }
            else if(j==coins[i]){
                dp[i][j]=1;
                choice[i][j]=3;
            }
            else{
                dp[i][j]=0;
                choice[i][j]=0;
            }
        }
    }
    for(int i=0;i<=N;i++){
        for(int j=0;j<=M;j++){
            cout<<choice[i][j]<<" ";
        }
        cout<<endl;
    }
    // if(dp[N][M]){
    //     vector<int> v;
    //     int i=N,j=M;
    //     while(choice[i][j]!=3){
    //         
    //     }
    // }
    // else{
    //     cout<<"No Solution"<<endl;
    // }

    return 0;
}