/*数字三角形问题：
题目：给定一个由n行数字组成的数字三角形如下图所示。试设计一个算法，计算出从三角形的顶至底的一条路
    径，使该路径经过的数字总和最大。对于给定的由n行数字组成的数字三角形，计算从三角形的顶至底的路
    径经过的数字和的最大值。
    7
   3 8
  8 1 0
 2 7 4 4
4 5 2 6 5
输入：数据的第1行是数字三角形的行数n(1≤n≤100)。接下来n行是数字三角形各行中的数字。所有数字在
    0..99之间。
输出：数据只有一个整数，表示计算出的最大值。
输入样例:
5
7
3 8
8 1 0
2 7 4 4
4 5 2 6 5
输出样例:
30
思路：dp[i][j]表示从顶点(1,1)到num[i][j]的最大路径和
*/
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cin>>n;
    int num[101][101];      //存储数据
    int dp[101][101];       //存储最大和
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            cin>>num[i][j];
            dp[i][j]=0;
        }
    }
    dp[1][1]=num[1][1];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            if(j==1){           //最左边只有一个选择
                dp[i][j]=dp[i-1][1]+num[i][j];
            }else if(j==i){     //最右边只有一个选择
                dp[i][j]=dp[i-1][i-1]+num[i][j];
            }else{
                int a=dp[i-1][j-1];
                int b=dp[i-1][j];
                if(a>b){
                    dp[i][j]=a+num[i][j];
                }
                else{
                    dp[i][j]=b+num[i][j];
                }
            }
        }
    }
    int max=0;
    for(int j=1;j<=n;j++){
        if(dp[n][j]>max){
            max=dp[n][j];
        }
    }
    cout<<max<<endl;

    return 0;
}