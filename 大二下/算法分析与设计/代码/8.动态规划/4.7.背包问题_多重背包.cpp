/*背包问题_多重背包:
题目:有N种物品,第i种物品最多有n[i]件可用，每件重量是w[i]，价值是v[i]。求解在容量为C的背包限
    制下如何使价值总和最大。
思路:最基本的思路就是在求解dp[i][j]的时候,当查找到第i行时,添加一个for循环遍历个数查找最大价
    值,转移方程为:
        dp[i][j]=max{dp[i-1][j-k*w[i]]+k*v[i]}(j>=k*w[i],k<=n[i])
*/
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int w[5]={0,10,3,4,5};          //第一个元素是0便于后续操作
    int v[5]={0,3,4,6,7};
    int n[5]={0,5,1,2,1};
    int Choice[5]={0};              //记录选择情况
    int C;
    cin>>C;                         //参考值:10, ans:13
    int dp[5][C+1]={{0}};
    for(int i=0;i<5;i++){           //初始化
        for(int j=0;j<=C;j++){
            dp[i][j]=0;
        }
    }

    for(int i=1;i<5;i++){           //动态规划求得最大价值
        for(int j=1;j<=C;j++){
            int MaxV=0;
            int num=0;
            for(int k=0;k<=n[i];k++){       //遍历最优决策
                if(j-k*w[i]>=0 && k<=n[i]){ //保证k取值有效
                    if(dp[i-1][j-k*w[i]]+k*v[i]>MaxV){
                        MaxV=dp[i-1][j-k*w[i]]+k*v[i];
                        num=k;
                    }
                }
            }
            dp[i][j]=MaxV;
        }
    }
    int j=C;
    for(int i=4;i>=0;i--){          //回溯得取舍方法
        if(dp[i][j]>dp[i-1][j]){
            Choice[i]++;
            j-=w[i];
        }
    }

    cout<<"Largest profit: "<<dp[4][C]<<endl;
    cout<<"Method: ";
    for(int i=0;i<4;i++){
        if(Choice[i]==1){
            cout<<i<<" ";
        }
    }

    return 0;
}