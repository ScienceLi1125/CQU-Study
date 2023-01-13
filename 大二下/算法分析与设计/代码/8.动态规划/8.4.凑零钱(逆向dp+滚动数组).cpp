/*凑零钱：
    由于原题要求N<=10000，因此原本数组开到dp[10005][105]，但数组太大导致溢出（段错误），因此
采用滚动数组解决
（注：去在线编译，VSCode不支持10005*105内存）
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
    int coins[10005]={0};
    for(int i=1;i<=N;i++){
        cin>>coins[i];
    }
    sort(coins+1,coins+N+1,cmp);
    int dp[105]={0};              //滚动数组记录前i种货币能凑出j以内的最大面额
    int choice[10005][105];       //记录决策
    vector<int> sequence;
    for(int i=0;i<10005;i++){
        for(int j=0;j<105;j++){
            choice[i][j]=0;
        }
    }

    for(int i=1;i<=N;i++){
        for(int j=M;j>=coins[i];j--){
            if(dp[j]<=dp[j-coins[i]]+coins[i]){
                dp[j]=dp[j-coins[i]]+coins[i];
                choice[i][j]=1;
            }
        }
    }
    if(dp[M]!=M){
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
        for(int i=0;i<sequence.size();i++){
            if(i!=0){
                cout<<" ";
            }
            cout<<sequence[i];
        }
    }
    // cout<<dp[N][M];

    return 0;
}