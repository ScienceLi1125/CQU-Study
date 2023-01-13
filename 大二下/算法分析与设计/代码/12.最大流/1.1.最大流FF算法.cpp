/*最大流：
题目:给定n个点，m条边，给定每条边的容量，求从点s到点t的最大流。
输入:第一行四个整数n,m,s,t。接下来的m行，每行三个整数u,v,c，表示从u到v，流量为c的一条边。
    数据保证有1≤n≤1200,1≤m≤120000,1≤c≤2^31−1。保证答案不超过2^31−1。
    常用网络流算法的复杂度为O(n^2*m)，请尽量优化算法。
输出:点s到点t的最大流。
输入样例1:
7 14 1 7
1 2 5
1 3 6
1 4 5
2 3 2
2 5 3
3 2 2
3 4 3
3 5 3
3 6 7
4 6 5
5 6 1
6 5 1
5 7 8
6 7 7
输出样例1:
14
输入样例2:
10 16 1 2
1 3 2
1 4 2
5 2 2
6 2 2
3 5 1
3 6 1
4 5 1
4 6 1
1 7 2147483647
9 2 2147483647
7 8 2147483647
10 9 2147483647
8 5 2
8 6 2
3 10 2
4 10 2
6 7 7
输出样例2:
8
思路:先采用FF算法,pre数组记录当前增广路径,二维数组cap记录残存网络中的剩余流量,flow记录
    节点s到当前节点的流的剩余量。其中搜索增广路径的方法为dfs,算法复杂度为O(E*f)
*/
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
int MaxData=0x7fffffff;

int n,m,s,t;
// int Graph[1201][1201]={{0}}; //记录残存网络中流的剩余量不必用二维数组(因为Graph存储也要取路径中最小)
int flow[1201]={0};             //只存储每次dfs中s到当前节点的流的剩余量即可
int cap[1201][1201]={{0}};      //记录残存网络中的容量
int pre[1201]={0};              //记录一次dfs过程中所有遍历过的点的前驱节点
bool flag=0;
void dfs(int cur){              //判断残存网络中是否剩余增广路径
    if(cur==t){
        flag=1;                 //找到增广路径
        return;
    }
    for(int i=1;i<=n;i++){      //从1开始,因为要找所有与cur相连节点
        if(pre[i]==-1 && cap[cur][i]>0){
            pre[i]=cur;
            flow[i]=min(flow[cur],cap[cur][i]);
            dfs(i);
        }
    }
    return;
}   //dfs结束后pre中存储了可以从t溯回到s的路径,flow中存储了s到所有点的可增流量

int MaxFlow(){                  //计算s到t的最大流
    int sum=0;                  //最大流
    int inc;                    //流量增量
    for(int i=1;i<=n;i++){      //初始化pre
        pre[i]=-1;
    }
    flow[s]=MaxData;            //否则全是0陷入死循环
    dfs(s);
    while(flag){                //有增广路径,并且执行bfs后pre和flow数组中存储对应信息
        int p=t;
        inc=flow[t];            //s->t的最大增量
        while(p!=s){            //回溯增广路径,增减残存网络中流量
            int tmp=pre[p];
            cap[tmp][p]-=inc;
            cap[p][tmp]+=inc;
            p=tmp;
        }
        sum+=inc;
        flag=0;                 //重新开始dfs,flag恢复false
        for(int i=1;i<=n;i++){  //重新开始dfs,路径清零
            pre[i]=-1;
        }
        pre[s]=0;
        dfs(s);
        // cout<<flag;
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
