/*最大流:
思路:利用EK算法实现FordFulkerson方法,pre数组记录当前增广路径,二维数组cap记录残存网络中
    的剩余流量,flow记录节点s到当前节点的流的剩余量。其中搜索增广路径的方法为bfs,这样可
    以最快找到增广路径。算法复杂度为O(V*E^2),适合边较少的稀疏图。
*/
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
int MaxData=0x7fffffff;

int n,m,s,t;
int flow[1201]={0};             //存储每次bfs中s到当前节点的流的剩余量
int cap[1201][1201]={{0}};      //记录残存网络中的容量
int pre[1201]={0};              //记录一次bfs过程中所有遍历过的点的前驱节点

bool bfs(){                     //判断残存网络中是否剩余增广路径
    queue<int> q;
    for(int i=1;i<=n;i++){      //初始化前驱节点(节点从1计数)
        pre[i]=-1;              //此处pre还兼有visit数组的作用,pre[i]=-1对应没访问过的节点
    }
    pre[s]=0;                   //路径初始节点
    q.push(s);
    flow[s]=MaxData;            //标记为INF,便于后续取flow[i]=min(flow[top],cap[top][i])
    while(!q.empty()){          //bfs
        int top=q.front();
        q.pop();                //t入队不停止以保证与t同level的节点都能入队(下一个level就出队结束)
        if(top==t)  break;      //找到增广路径
        for(int i=1;i<=n;i++){
            if(pre[i]==-1&&cap[top][i]>0){
                pre[i]=top;
                q.push(i);      //找到同一level节点
                flow[i]=min(flow[top],cap[top][i]);
            }
        }
    }
    if(pre[t]==-1)  return 0;   //找不到增广路径
    else    return 1;
}   //bfs结束后pre中存储了可以从t溯回到s的路径,flow中存储了s到所有点的可增流量

int MaxFlow(){                  //计算s到t的最大流
    int sum=0;      //最大流
    int inc;        //流量增量
    while(bfs()){   //有增广路径,并且执行bfs后pre和flow数组中存储对应信息
        int p=t;
        inc=flow[t];
        while(p!=s){            //回溯增广路径,增减残存网络中流量
            int tmp=pre[p];
            cap[tmp][p]-=inc;
            cap[p][tmp]+=inc;
            p=tmp;
        }
        sum+=inc;
    }
    return sum;
}

int main(){
    cin>>n>>m>>s>>t;
    for(int i=0;i<m;i++){
        int u,v,c;
        cin>>u>>v>>c;
        if(u!=v){               //防止start==end
            cap[u][v]=c;
        }
    }
    cout<<MaxFlow()<<endl;

    return 0;
}
