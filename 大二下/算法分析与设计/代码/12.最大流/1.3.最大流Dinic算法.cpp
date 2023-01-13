/*最大流:
思路:利用EK算法实现FordFulkerson方法中,搜索增广路径的方法为bfs,一次复杂的bfs找到了多条
    增广路径却只使用一条增广路径,代价巨大。下采用Dinic算法:bfs+dfs,bfs的过程相当于分层,
    再用dfs搜索增广路径可以达到多路增广的效果,具体操作为dfs中for循环遍历bfs分层后所有可
    行的增广路径,并且同步处理残存网络中的剩余流量。因为dfs本质为递归,流量的增量为从后向前
    取min即可得到最大增量;并且同步处理残存网络中的剩余流量保证了剩余流量可以作为增量的合
    理性;于是dfs的遍历相当于增加了所有可行的增广路径流量。复杂度为O(E*V^2),在处理稠密图
    的情况下明显占优。
*/
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
int MaxData=0x7fffffff;

int n,m,s,t;
// int flow[1201]={0};          //Dinic无需再记录剩余流量,因为dfs时从后向前可以得到增量
int cap[1201][1201]={{0}};      //记录残存网络中的容量
int level[1201];                //记录bfs过程的节点层数
// int pre[1201]={0};           //dfs过程可以直接增流,无需回溯路径

int Min(int a,int b){
    if(a<b) return a;
    else    return b;
}

bool bfs(){                     //判断残存网络中是否剩余增广路径
    queue<int> q;
    q.push(s);
    for(int i=1;i<=n;i++){
        level[i]=-1;            //层数初始化为-1,遍历结束后为-1的即为没有遍历到的
    }
    level[s]=0;                 //s层数为0
    while(!q.empty()){          //bfs
        int top=q.front();
        q.pop();                //t入队不停止以保证与t同level的节点都能入队(下一个level就出队结束)
        if(top==t)  break;      //找到增广路径
        for(int i=1;i<=n;i++){
            if(level[i]==-1&&cap[top][i]>0){
                level[i]=level[top]+1;
                q.push(i);      //找到同一level节点
            }
        }
    }
    if(level[t]==-1)  return 0; //找不到增广路径
    else    return 1;
}

int dfs(int start,int inc){     //遍历增广路径返回增量,start为起始点,inc为s->start的最大流量可增量
/*inc和cap[start][i]取min后传入后面的dfs并不断取min即为最终整条增广路径的流量增量
每个节点经过的增广路径可能不止一条,层数越接近0的节点经过的增广路径越多
每条增广路径通过递归dfs得到,所有增广路径通过for遍历得到,并且随时更新残存网络cap符合流量限制
*/
    if(start==t)    return inc; //到达终点
    int remain=inc;             //记录剩余增量
    for(int i=1;i<=n && remain>=0;i++){             //必须保证剩余增量为正
        if(level[i]==level[start]+1 && cap[start][i]>0){
            int tmp=dfs(i,Min(remain,cap[start][i]));
            //tmp是i->t的增量,也是增广路径s->...->start->i->...->t的增量
            cap[start][i]-=tmp;
            cap[i][start]+=tmp;
            remain-=tmp;
        }
    }
    return inc-remain;
}

int Dinic(){                    //计算s到t的最大流
    int sum=0;                  //最大流
    while(bfs()){               //有增广路径,并且执行bfs后level数组中存储层数
        sum+=dfs(s,MaxData);
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
    cout<<Dinic()<<endl;

    return 0;
}