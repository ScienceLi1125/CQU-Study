//https://blog.csdn.net/a15110103117/article/details/82020679
#include <iostream>
#include <string.h>
#include <vector>
#include <list>
#include <queue>
#define INF 0x7fffffff
using namespace std;
struct node{
    int v,cap,index;
};
vector<node> edge[1203];
vector<int> List[1203];
vector<list<int>::iterator> listit;
list<int>dlist[1203];
int highest,highestActive,vis[1203],excess[1203],height[1203];
void insert(int u,int v,int cap){
    edge[u].push_back(node{v,cap,int(edge[v].size())});
    edge[v].push_back(node{u,0,int(edge[u].size()-1)});
}
void globalRelabel(int n,int t){
    int u,i,hp,v,index;
    queue<int>q;
    for(i=0;n>=i;i++)
    {
        height[i]=n;
    }
    height[t]=0;
    memset(vis,0,sizeof(vis));
    q.push(t);
    while(q.empty()==0){
        u=q.front();
        q.pop();
        for(i=0;edge[u].size()>i; i++)
        {
            v=edge[u][i].v;
            index=edge[u][i].index;
            if(height[v]==n&&edge[v][index].cap>0)
            {
                height[v]=height[u]+1;
                vis[height[v]]++;
                q.push(v);
                hp=v;
            }
        }
    }
    for(i=0;n>=i;i++){
        List[i].clear();
        dlist[i].clear();
    }
    for(i=0;n>i;i++){
        if(height[i]<n){
            listit[i]=dlist[height[i]].insert(dlist[height[i]].begin(),i);
            if(excess[i]>0){
                List[height[i]].push_back(i);
            }
        }
    }
    highest=height[hp];
    highestActive=height[hp];
}
void push(int u,node &e){
    int v,df;
    v=e.v;
    df=min(excess[u],e.cap);
    e.cap=e.cap-df;
    edge[v][e.index].cap=edge[v][e.index].cap+df;
    excess[u]=excess[u]-df;
    excess[v]=excess[v]+df;
    if(excess[v]>0&&excess[v]<=df){
        List[height[v]].push_back(v);
    }
}
void discharge(int n,int u){
    int i,nh,v,cap,h;
    nh=n;
    for(i=0;edge[u].size()>i;i++){
        v=edge[u][i].v;
        cap=edge[u][i].cap;
        if(cap>0)
        {
            if(height[u]==height[v]+1)
            {
                push(u,edge[u][i]);
                if(excess[u]==0)
                {
                    return;
                }
            }
            else
            {
                nh=min(nh,height[v]+1);
            }
        }
    }
    h=height[u];
    if(vis[h]==1)
    {
        for(i=h;highest>=i;i++)
        {
            for(list<int>::iterator it=dlist[i].begin();it!=dlist[i].end();it++)
            {
                vis[height[*it]]--;
                height[*it]=n;
            }
            dlist[i].clear();
        }
        highest=h-1;
    }
    else
    {
        vis[h]--;
        listit[u]=dlist[h].erase(listit[u]);
        height[u]=nh;
        if(nh==n)
        {
            return;
        }
        vis[nh]++;
        listit[u]=dlist[nh].insert(dlist[nh].begin(),u);
        highestActive=nh;
        highest=max(highest,highestActive);
        List[nh].push_back(u);
    }
}
int hlpp(int n,int s,int e)
{
    int i,u;
    if(s==e)
    {
        return 0;
    }
    highestActive=0;
    highest=0;
    memset(height,0,sizeof(height));
    height[s]=n;
    listit.resize(n);
    for(i=0;n>i;i++)
    {
        if(i!=s)
        {
            listit[i]=dlist[height[i]].insert(dlist[height[i]].begin(),i);
        }
    }
    memset(vis,0,sizeof(vis));
    vis[0]=n-1;
    memset(excess,0,sizeof(excess));
    excess[s]=INF;
    excess[e]=-INF;
    for(i=0;edge[s].size()>i;i++)
    {
        push(s,edge[s][i]);
    }
    globalRelabel(n,e);
    while(highestActive>=0)
    {
        if(List[highestActive].empty()==1)
        {
            highestActive--;
            continue;
        }
        u=List[highestActive].back();
        List[highestActive].pop_back();
        discharge(n,u);
    }
    return excess[e]+INF;
}
int main(){
    int n, m, s, t;
    cin>>n>>m>>s>>t;
    for (int i = 0, u, v, f; i < m; i++)
    {
        scanf("%d %d %d",&u,&v,&f);
        insert(u,v,f);
    }
    cout<<hlpp(n+1,s,t);
    return 0;
}