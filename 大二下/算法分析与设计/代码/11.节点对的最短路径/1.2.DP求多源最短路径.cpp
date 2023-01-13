/*多源最短路径:
思路:其实还可以使用动态规划求解:记D(m)[i][j]表示从i到j包含不多于m条边的最短路径,于是可通过迭
    代d(m)[i][j]=min{d(m-1)[i][k]+w[k][j]}(0<=k<n)得到d(n-1)[i][j],即为i到j的最短路径。
    该算法的时间复杂度为O(n^4),空间复杂度为Theta(n^3)(若只保留相邻两次的结果则为n^2)
*/
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
#define INFINITY 1000

int main(){
    int Gph[9][9]={{0,4,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,8,INFINITY},
                {4,0,8,INFINITY,INFINITY,INFINITY,INFINITY,11,INFINITY},
                {INFINITY,8,0,7,INFINITY,4,INFINITY,INFINITY,2},
                {INFINITY,INFINITY,7,0,9,14,INFINITY,INFINITY,INFINITY},
                {INFINITY,INFINITY,INFINITY,9,0,10,INFINITY,INFINITY,INFINITY},
                {INFINITY,INFINITY,4,14,10,0,2,INFINITY,INFINITY},
                {INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,2,0,1,6},
                {8,11,INFINITY,INFINITY,INFINITY,INFINITY,1,0,7},
                {INFINITY,INFINITY,2,INFINITY,INFINITY,INFINITY,6,7,0}};
    int d0[9][9];               //只保留前后两次的结果,节省空间
    int d1[9][9];
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            d0[i][j]=Gph[i][j];
        }
    }
    for(int n=0;n<9-2;n++){     //d0的初始状态就是D(1),因此只需要迭代n-2次
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                int minedge=d0[i][0]+Gph[0][j];
                for(int k=0;k<9;k++){
                    if(d0[i][k]+Gph[k][j]<minedge){
                        minedge=d0[i][k]+Gph[k][j];
                    }
                }
                if(minedge<d0[i][j])    d1[i][j]=minedge;
                else                    d1[i][j]=d0[i][j];
            }
        }
        for(int i=0;i<9;i++){   //每次循环结束后将d1赋给d0
            for(int j=0;j<9;j++){
                d0[i][j]=d1[i][j];
            }
        }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout<<"The shortest path between "<<i<<" and "<<j<<" is: "<<d1[i][j]<<endl;
        }    
    }

    return 0;
}