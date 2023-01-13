/*Dijkstra算法：
    求给定图中0到其余各点的最短路径
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
int d[9]={0,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY};
int pre[9]={0};
bool flag[9]={0};

int minVertex(){
    int index;
    int min=100;
    for(int i=0;i<9;i++){
        if(flag[i]==0 && d[i]<min){     //限制条件：i未被加入最短路径
            min=d[i];
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
void Dijkstra(){
    while(!isEnd()){
        int index=minVertex();
        //cout<<index<<endl;
        flag[index]=1;
        for(int i=0;i<9;i++){
            if(Gph[i][index]>0 && Gph[i][index]!=INFINITY && flag[i]==0){   //相邻且未标记
                if(d[i]>d[index]+Gph[index][i]){
                    d[i]=d[index]+Gph[index][i];
                    pre[i]=index;
                }
            }
        }
    }
}

int main(){
    Dijkstra();
    for(int i=1;i<9;i++){
        cout<<"0到"<<i<<"的最短路径长度为"<<d[i]<<endl;
    }

    return 0;
}