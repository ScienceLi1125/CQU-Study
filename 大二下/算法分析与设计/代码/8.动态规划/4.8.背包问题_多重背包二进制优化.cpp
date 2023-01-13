/*背包问题_多重背包二进制优化:
题目:有N种物品,第i种物品最多有n[i]件可用，每件重量是w[i]，价值是v[i]。求解在容量为C的背包限
    制下如何使价值总和最大。
思路:for循环遍历k相当于将N种物品扩展成Σni种物品,复杂度大大上升,因此需要优化。其实如果ni都够
    大,即任意ni*wi>C,那么该多重背包问题等价于完全背包,因为所能取的数量<C;如果ni都为1,则该问
    题为01背包;而介于二者之间的问题才是标准的多重背包问题。因此考虑把多个相同物品组合成若干
    个该物品的小集合(如3个物品1组合成一个新的物品),但问题的关键在于如何巧妙组合不影响最终结
    果。
    考虑二-十进制的转换:15D=1111B、10D=1010B,因此可以将一个十进制数分解为多个2^i的数相加,
    (最后剩余的可能不是2^i)即可凑出所有可能的组合。如10用1、2、4、3, 21用1、2、4、8、6...
    在此编码情况下, 通过01背包决策方式可以穷举所有情况
*/
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int w[5]={0,2,4,4,5};
    int v[5]={0,1,2,3,4};
    int n[5]={0,3,1,3,2};
    int C=10;

    int dp[101][C+1]={{0}};
    int w_new[101]={0};
    int v_new[101]={0};
    int cnt=0;
    for(int i=1;i<5;i++){           //二-十进制转换
        int tmp=n[i];
        for(int j=1;j<=tmp;j*=2){
            cnt++;
            w_new[cnt]=w[i]*j;
            v_new[cnt]=v[i]*j;
            tmp-=j;
        }
        if(tmp){                    //10=1+2+4+3, 在4后便会退出循环, 因此需要加上剩余数量
            cnt++;
            w_new[cnt]=w[i]*tmp;
            v_new[cnt]=v[i]*tmp;
        }
    }
    // cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++)   cout<<w_new[i]<<" "<<v_new[i]<<endl;
    //此时有cnt个物品供选择, 下面即可采用0-1背包解决问题
    for(int i=0;i<=C;i++)   dp[0][i]=0;
    for(int i=0;i<=cnt;i++) dp[i][0]=0;

    for(int i=1;i<=cnt;i++){
        for(int j=1;j<=C;j++){
            if(j>=w_new[i] && dp[i-1][j]<dp[i-1][j-w_new[i]]+v_new[i]){
                dp[i][j]=dp[i-1][j-w_new[i]]+v_new[i];
            }
            else{
                dp[i][j]=dp[i-1][j];
            }
        }
    }
    cout<<"Largest profit: "<<dp[cnt][C]<<endl;

    return 0;
}