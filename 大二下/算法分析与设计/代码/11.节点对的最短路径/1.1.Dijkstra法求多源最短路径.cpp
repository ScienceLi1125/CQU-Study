/*多源最短路径:
题目：题目给定一个图,求解所有节点对之间的最短路径。首先想到的就是求解单源最短路径的Dijkstra
    算法:每次不断搜寻与初始点相邻的最近的未加入的节点,直到所有节点被加入path。重复上述过程n
    次,即将所有节点作一次初始点即可得到所有节点对之间的最短路径
*/
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
#define INFINITY 1000

int Gph[9][9]={{0,4,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,8,INFINITY},
               {4,0,8,INFINITY,INFINITY,INFINITY,INFINITY,11,INFINITY},
               {INFINITY,8,0,7,INFINITY,4,INFINITY,INFINITY,2},
               {INFINITY,INFINITY,7,0,9,14,INFINITY,INFINITY,INFINITY},
               {INFINITY,INFINITY,INFINITY,9,0,10,INFINITY,INFINITY,INFINITY},
               {INFINITY,INFINITY,4,14,10,0,2,INFINITY,INFINITY},
               {INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,2,0,1,6},
               {8,11,INFINITY,INFINITY,INFINITY,INFINITY,1,0,7},
               {INFINITY,INFINITY,2,INFINITY,INFINITY,INFINITY,6,7,0}};
int d[9][9];
int pre[9][9];
bool flag[9]={0};

int minVertex(int start){
    int index;
    int min=100;
    for(int i=0;i<9;i++){
        if(flag[i]==0 && d[start][i]<min){     //限制条件：i未被加入最短路径
            min=d[start][i];
            index=i;
        }
    }
    return index;
}
bool isEnd(){
    bool flag2=1;
    for(int i=0;i<9;i++){
        if(flag[i]==0){
            flag2=0;
        }
    }
    return flag2;
}
void Dijkstra(int start){
    for(int i=0;i<9;i++){
        d[start][i]=INFINITY;
        pre[start][i]=-1;
        flag[i]=0;
    }
    d[start][start]=0;
    while(!isEnd()){
        int index=minVertex(start);
        //cout<<index<<endl;
        flag[index]=1;
        for(int i=0;i<9;i++){
            if(Gph[i][index]>0 && Gph[i][index]<INFINITY && flag[i]==0){   //相邻且未标记
                if(d[start][i]>d[start][index]+Gph[index][i]){
                    d[start][i]=d[start][index]+Gph[index][i];
                    pre[start][i]=index;
                }
            }
        }
    }
}

int main(){
    for(int i=0;i<9;i++){
        Dijkstra(i);
        for(int j=0;j<9;j++){
            cout<<"The shortest path between "<<i<<" and "<<j<<" is: "<<d[i][j]<<endl;
        }    
    }

    return 0;
}