/*凑零钱：
    采用01背包的相同思路，用dp[i][j]记录前i种货币能凑出j以内的最大面额，若dp[i][j]==j，则表示
能凑出，否则不能
    为了找到最小序列，可以将N种面额降序排列，从而使得面额小的在后面，在选择时如果dp[i-1][j]==
dp[i-1][j-coins[i]]+coins[i]的话，显然选前者，因为字典序更小。上述思路的原理实质上是逆向寻找
序列，找到两组和相同的序列时比较的点即为序列分叉处，因为比较点后面的肯定相同
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(int a,int b){          //降序排列
    return a > b;
}

int main(){
    int N,M;
    cin>>N>>M;
    int coins[105]={0};
    for(int i=1;i<=N;i++){
        cin>>coins[i];
    }
    sort(coins+1,coins+N+1,cmp);
    int dp[105][105];           //记录前i种货币能凑出j以内的最大面额
    int choice[105][105];       //记录决策
    vector<int> sequence;

    for(int i=0;i<105;i++){     //初始化
        for(int j=0;j<105;j++){
            dp[i][j]=0;
            choice[i][j]=0;
        }
    }

    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
            if(j<coins[i]){
                dp[i][j]=dp[i-1][j];
            }
            else if(dp[i-1][j]<=dp[i-1][j-coins[i]]+coins[i]){
                dp[i][j]=dp[i-1][j-coins[i]]+coins[i];
                choice[i][j]=1;
            }
            else{
                dp[i][j]=dp[i-1][j];
            }
        }
    }
    // for(int i=0;i<=N;i++){
    //     for(int j=0;j<=M;j++){
    //         cout<<dp[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    if(dp[N][M]!=M){
        cout<<"No Solution"<<endl;
    }
    else{
        int i=N,j=M;
        while(j>0){
            if(choice[i][j]==1){
                sequence.push_back(coins[i]);
                j-=coins[i];
            }
            i--;
        }
        cout<<sequence[0];
        for(int i=1;i<sequence.size();i++){
            cout<<" "<<sequence[i];
        }
    }
    // cout<<dp[N][M];

    return 0;
}