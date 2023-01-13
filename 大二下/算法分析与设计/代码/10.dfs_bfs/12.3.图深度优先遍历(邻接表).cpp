/*图深度优先遍历
    递归超时的原因是图的点数较多但边数较少，不宜采用相邻矩阵，下采用邻接表
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n,e;
vector<int> Graph[20001];   //邻接表存图
bool visit[20001]={0};

void dfs(int v){
    if(v<0||v>=n)   return;
    visit[v]=1;     //标记访问过的点
    cout<<v<<" ";
    for(int i=0;i<Graph[v].size();i++){
        if(visit[Graph[v][i]]==0){
            dfs(Graph[v][i]);
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
        Graph[a].push_back(b);
    }
    for(int i=0;i<n;i++){   //对每个节点的相邻节点顺序排列
        sort(Graph[i].begin(),Graph[i].end());
    }
    traverse();

    return 0;
}
