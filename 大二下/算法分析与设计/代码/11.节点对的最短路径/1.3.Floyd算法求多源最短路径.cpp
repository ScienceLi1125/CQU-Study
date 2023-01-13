/*多源最短路径(floyd算法)：
题目:DP算法求解单源最短路径的时间复杂度为O(n^4),效率太低,下采用Floyd-Warshell算法加以优化。
    设L[i][j]表示i与j间的最短路径，则有：
            L[i][j]=min(L[i][k]+L[k][j],L[i][j])    (k=0,1,...)
        但上述递推式不易初始化，因为每个节点都是平等的，没法先借用和其他节点间的最短路径。(类比矩
    阵链乘法，最外层循环为矩阵链长度)，因此考虑以节点作为中间节点(即k)作为最外层循环，内部遍历i,
    j，本质是求解以k作为L[i][j]的中间节点的最短路径。与最终路径比较，如果最外层第一次循环的结果就
    是L[a][b]的最终结果，那么这次循环本质就是查找路径长度为2的情况，后续遍历同理。同时，为了记录最
    短路径，用数组pre[i][j]记录路径倒数第二个节点
思路：当常规i,j遍历没的迭代的时候，不妨考虑最内层的k为最外层
*/
#include <iostream>
#include <vector>
using namespace std;
#define INFINITY 1000

void Printpath(int pre[9][9],int start,int end){
    if(start==pre[start][end]){
        cout<<start<<" "<<end<<" ";
        return;
    }
    int tmp=pre[start][end];
    Printpath(pre,start,tmp);
    cout<<end<<" ";
    return;
}

int main(){
    //初始化
    int Gph[9][9]={{0,4,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,8,INFINITY},
                {4,0,8,INFINITY,INFINITY,INFINITY,INFINITY,11,INFINITY},
                {INFINITY,8,0,7,INFINITY,4,INFINITY,INFINITY,2},
                {INFINITY,INFINITY,7,0,9,14,INFINITY,INFINITY,INFINITY},
                {INFINITY,INFINITY,INFINITY,9,0,10,INFINITY,INFINITY,INFINITY},
                {INFINITY,INFINITY,4,14,10,0,2,INFINITY,INFINITY},
                {INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,2,0,1,6},
                {8,11,INFINITY,INFINITY,INFINITY,INFINITY,1,0,7},
                {INFINITY,INFINITY,2,INFINITY,INFINITY,INFINITY,6,7,0}};
    int L[9][9]={{0,4,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,8,INFINITY},
                {4,0,8,INFINITY,INFINITY,INFINITY,INFINITY,11,INFINITY},
                {INFINITY,8,0,7,INFINITY,4,INFINITY,INFINITY,2},
                {INFINITY,INFINITY,7,0,9,14,INFINITY,INFINITY,INFINITY},
                {INFINITY,INFINITY,INFINITY,9,0,10,INFINITY,INFINITY,INFINITY},
                {INFINITY,INFINITY,4,14,10,0,2,INFINITY,INFINITY},
                {INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,2,0,1,6},
                {8,11,INFINITY,INFINITY,INFINITY,INFINITY,1,0,7},
                {INFINITY,INFINITY,2,INFINITY,INFINITY,INFINITY,6,7,0}};
    int pre[9][9];
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            pre[i][j]=i;    //用pre[i][j]=i表示路径没有中间节点，Printpath中要一致
        }
    }
    //dp
    for(int k=0;k<9;k++){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                int len=L[i][k]+L[k][j];
                if(len<L[i][j]){
                    L[i][j]=len;
                    pre[i][j]=k;
                }
            }
        }
    }
    cout<<"The shortest length between 0 and 8 : "<<L[0][8]<<endl<<"path: ";
    Printpath(pre,0,8);
    // for(int i=0;i<9;i++){
    //     for(int j=0;j<9;j++){
    //         cout<<pre[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    return 0;
}