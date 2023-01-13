/*0-1背包问题的空间复杂度优化：
    二维数组dp空间复杂度较高，采用滚动数组降低动态规划过程中的空间复杂度。由动态规划过程递推关
系式可知，dp[i][j]只与dp[i-1][j],dp[i-1][j-W[i]]+V[i]有关，即上一行的数据。因此我们可以隐藏
阶段数，只保留W限制的列数据，每行数据从上向下不断更新即可
    但该方法只能得出最大利润，无法回溯得到具体操作
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
    int dp[C+1]={0};
    for(int i=0;i<=C;i++){          //初始化
        dp[i]=0;
    }

    for(int i=1;i<=5;i++){          //动态规划求得最大价值
        // for(int j=W[i];j<=C;j++){   //从W[i]遍历即可，遍历不到的无需更改
        for(int j=C;j>=W[i];j--){
        /*必须倒序遍历，因为如果正序遍历，dp[i][j]本该由dp[i-1][j-W[i]]决定，正序遍历使得
        dp[i-1][j-W[i]]被dp[i][j-W[i]]替代，递推出错。若是完全背包问题就可以采用正序遍历*/
            if(dp[j]<dp[j-W[i]]+V[i]){
                dp[j]=dp[j-W[i]]+V[i];
            }
        }
    }
    cout<<"Largest profit: "<<dp[C]<<endl;

    return 0;
}