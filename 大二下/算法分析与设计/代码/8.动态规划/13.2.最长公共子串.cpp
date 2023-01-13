/*二维数组内存超限，改为滚动数组
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
    int dp[5005]={0};           //记录Xi和Yj的最长公共子序列长度

    for(int i=1;i<=n;i++){
        for(int j=m;j>=1;j--){
            if(X[i-1]==Y[j-1]){ //注意i和j取值
                dp[j]=dp[j-1]+1;
                if(dp[j]>max_len){
                    max_len=dp[j];
                }
            }
            else    dp[j]=0;    //不能省略！因为此处dp[i][j]是0而不是dp[i-1][j]
        }
    }
    cout<<max_len<<endl;

    return 0;
}