/*矩阵链乘法：
题目：给定N个矩阵的序列，p[N+1]表示N个矩阵的大小（其中第i个矩阵的列数必等于i+1个的行数），计算
    它们的乘积。问用何种办法，使得计算次数最少
分析：矩阵序列的乘积顺序会影响计算的次数，比如A1(2*5),A2(5*3),A3(3*7)，则(A1*A2)*A3需要计算
    2*5*3*2*3*7=1260次，A1*(A2*A3)需要计算5*3*7*2*5*7=7350次。设m[i][j]表示计算矩阵链Ai...j
    需要的最少乘法次数，则题目要求m[1][n]。设i<=k<j，k为分割i~j的最优子结构，即Ai...j可分割为
    Ai...k和Ak+1...j，因此m[i][j]=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j]，即：
        m[i][j]= 0 (i=j)
                min(m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j])(i<=k<j) (i<j)
    但上述思路是一个递归过程，有着相当多的重复子问题，此时该问题的递归已经具备了动态规划的两个标
    识：最优子结构和子问题重叠。因此采用自底向上表格法代替递归。
思路：动态规划的本质是先求子问题再合并成大问题，因此考虑从m[i][j]的|i-j|最小开始，即矩阵链长度。
    算法按矩阵链长度递增的顺序，遍历该长度下矩阵的不同分割，求解该分割的最优解
    同时为了记录分割情况，用s[i][j]表示Ai...j的分割情况
*/
#include <iostream>
#include <algorithm>
using namespace std;

void optimal_solution(int s[][7],int i,int j){  //多维数组传参必须指定列宽，不能传入int **s
    if(i==j){
        cout<<"A"<<i;
    }
    else{
        cout<<"(";
        optimal_solution(s,i,s[i][j]);
        optimal_solution(s,s[i][j]+1,j);
        cout<<")";
    }
}

int main(){
    int N=6;
    int p[N+1]={30,35,15,5,10,20,25};   //N个矩阵的大小
    int m[N+1][N+1]={{0}};              //记录最少乘法次数
    int s[N+1][7]={{0}};                //记录分割情况
    for(int i=1;i<N+1;i++){
        m[i][i]=0;
    }
    for(int l=2;l<=N;l++){              //矩阵链长度
        for(int i=1;i<=N-l+1;i++){      //矩阵序列长度为l时的不同分割(1..l),(2..l+1)等等
            int j=l+i-1;                //Ai...j链
            m[i][j]=10000000000;        //无穷(一开始开10000000不够大)
            for(int k=i;k<=j-1;k++){    //遍历i~j之间的不同分割求解m[i][j]
                int cnt=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if(cnt<m[i][j]){
                    m[i][j]=cnt;
                    s[i][j]=k;
                }
                //cout<<cnt<<endl;
            }
        }
    }
    cout<<"Minimum number of calculations: "<<m[1][N]<<endl;
    optimal_solution(s,1,N);
    
    return 0;
}