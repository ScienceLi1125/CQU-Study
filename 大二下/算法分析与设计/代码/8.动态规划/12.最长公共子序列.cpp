/*LCS问题
题目：给定两个序列X=<x1,x2,…,xn>和Y=<y1,y2,…,ym>。求出这两个序列的最长公共子序列的长度。
输入样例1：
asdf
adfsd
输出样例1：
3
输入样例2：
123abc
abc123abc
输出样例2：
6
输入样例3：
ACCGGTCGAGTGCGCGGAAGCCGGCCGAA
GTCGTTCGGAATGCCGTTGCTCTGTAAA
输出样例3：
GTCGTCGGAAGCCGGCCGAA
思路：寻找LCS最优子结构特征，设Z=<z1,z2,...,zk>为X和Y的任意LCS，则：
        若xn==ym，那么zk=xn=ym，并且Z(k-1)=LCS(X(n-1),Y(m-1))
        若xn!=ym，zk!=xn，那么Z(k)=LCS(X(n-1),Y(m))
        若xn!=ym，zk!=ym，那么Z(k)=LCS(X(n),Y(m-1))
    设c[i][j]表示Xi和Yj的LCS，根据上述分析，可得递推关系式：
       c[i][j]= 0                           (i=0或j=0)
                c[i-1][j-1]+1               (i,j>0并且xi=yj)
                max(c[i][j-1],c[i-1][j])    (i,j>0并且xi!=yj)
*/
#include <iostream>
#include <vector>
using namespace std;

int main(){
    string X="ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    string Y="GTCGTTCGGAATGCCGTTGCTCTGTAAA";
    int n=X.length();
    int m=Y.length();
    int c[n+1][m+1];            //记录Xi和Yj的最长公共子序列长度
    int LCS[n+1][m+1];          //记录Xi和Yj的最长公共子序列：1，2，3分别对应主函数段三种情况
    for(int i=0;i<=n;i++){      //初始化
        for(int j=0;j<=m;j++){
            c[i][j]=0;
            LCS[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(X[i-1]==Y[j-1]){     //注意i和j取值
                c[i][j]=c[i-1][j-1]+1;
                LCS[i][j]=1;        //X[i-1]加入公共子序列
            }
            else if(c[i-1][j]>=c[i][j-1]){
                c[i][j]=c[i-1][j];
                LCS[i][j]=2;
            }
            else{
                c[i][j]=c[i][j-1];
                LCS[i][j]=3;
            }
            // cout<<c[i][j]<<endl;
        }
    }
    cout<<"Length of the longest common subsequence: "<<c[n][m]<<endl;
    vector<char> v;
    cout<<"Longest common subsequence: ";
    int i=n,j=m;
    while(i!=0 && j!=0){
        if(LCS[i][j]==1){
            v.push_back(X[i-1]);
            i--;
            j--;
        }
        else if(LCS[i][j]==2){
            i--;        //c[i][j]=c[i-1][j]，因此i--
        }
        else if(LCS[i][j]==3){
            j--;        //c[i][j]=c[i][j-1]，因此j--
        }
        // else{
        //     cout<<"?"<<endl;
        // }
    }
    for(int k=v.size()-1;k>=0;k--){
        cout<<v[k];
    }

    return 0;
}