/*图深度优先遍历
题目: 编写程序对给定的有向图（不一定连通）进行深度优先遍历，图中包含n个顶点，编号为0至n-1。本题限定
    在深度优先遍历过程中，如果同时出现多个待访问的顶点，则优先选择编号最小的一个进行访问，以顶点0为
    遍历起点。
输入: 第一行为两个整数n和e，分别表示图的顶点数和边数，其中n不超过20000，e不超过50。接下来e行表示每
    条边的信息，每行为两个整数a、b，表示该边的端点编号，但各边并非按端点编号顺序排列。
输出: 一行整数，每个整数后一个空格，即该有向图的深度优先遍历结点序列。
输入样例1:
3 3
0 1
1 2
0 2
输出样例1:
0 1 2 
输入样例2:
4 4
0 2
0 1
1 2
3 0
输出样例2:
0 1 2 3 
注意: 图的遍历,遍历过程用dfs
*/
#include <iostream>
#include <vector>
using namespace std;

int n,e;
int matrix[20001][20001]={{0}};
bool visit[20001]={0};

int next(int v,int w){  //v的相邻节点中w的后一个
    for(int i=w+1;i<n;i++){
        if(matrix[v][i]>0)  return i;
    }
    return n;           //没找到相邻点
}

void dfs(int v){
    if(v<0||v>=n)   return;
    visit[v]=1;     //标记访问过的点
    cout<<v<<" ";
    for(int w=next(v,-1);w<n;w=next(v,w)){
        if(visit[w]==0){
            dfs(w);
        }
    }
    return;
}

void traverse(){
    for(int i=0;i<n;i++){
        if(visit[i]==0) dfs(i);
    }
}

int main(){
    cin>>n>>e;
    for(int i=0;i<e;i++){
        int a,b;
        cin>>a>>b;
        matrix[a][b]=1;
        // matrix[b][a]=1;
    }
    traverse();

    return 0;
}
