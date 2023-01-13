/*公路村村通：
保留图的数据结构，采用并查集路径压缩判断是否在同一等价类。
*/
#include <iostream>
#include <algorithm>
using namespace std;
class Graph{
private:
    int numVertex,numEdge;
    int **matrix;
    int *mark;
public:
    Graph(int num){
        Init(num);
    }
    ~Graph(){
        delete [] mark;
        for(int i=0;i<=numVertex;i++){
            delete [] matrix[i];
        }
        delete [] matrix;
    }
    void Init(int n){
        numVertex=n;
        numEdge=0;
        mark=new int[n+1];
        for(int i=0;i<=numVertex;i++){
            mark[i]=0;
        }
        matrix=(int**)new int*[numVertex+1];
        for(int i=0;i<=numVertex;i++){
            matrix[i]=new int[numVertex+1];
        }
        for(int i=0;i<=numVertex;i++){
            for(int j=0;j<=numVertex;j++){
                matrix[i][j]=0;
            }
        }
    }
    int n(){
        return numVertex;
    }
    int e(){
        return numEdge;
    }
    int first(int v){
        for(int i=1;i<=numVertex;i++){
            if(matrix[v][i]!=0){
                return i;
            }
        }
        return numVertex+1;
    }
    int next(int v,int w){
        for(int i=w+1;i<=numVertex;i++){
            if(matrix[v][i]!=0){
                return i;
            }
        }
        return numVertex+1;
    }
    void setEdge(int v1,int v2,int w){
        if(matrix[v1][v2]==0){
            numEdge++;
        }
        matrix[v1][v2]=w;
    }
    void delEdge(int v1,int v2){
        if(matrix[v1][v2]!=0){
            numEdge--;
        }
        matrix[v1][v2]=0;
    }
    bool isEdge(int i,int j){
        return matrix[i][j]!=0;
    }
    int weight(int v1,int v2){
        return matrix[v1][v2];
    }
    int getMark(int v){
        return mark[v];
    }
    void setMark(int v,int value){
        mark[v]=value;
    }
    bool isConnected(){
        bool flag=1;
        for(int i=1;i<=numVertex;i++){
            if(mark[i]==0){
                flag=0;
            }
        }
        return flag;
    }
};
void DFS(Graph* G,int v){
    G->setMark(v,1);
    for(int w=G->first(v);w<=G->n();w=G->next(v,w)){
        if(G->getMark(w)==0){
            DFS(G,w);
        }
    }
}
void graphTraverse(Graph* G){
    for(int v=1;v<=G->n();v++){
        G->setMark(v,0);
    }
    DFS(G,1);
}

class KruskElem{
public:
    int from,to,distance;
    KruskElem():from(-1),to(-1),distance(-1){}
    KruskElem(int f,int t,int d):from(f),to(t),distance(d){}
};
bool compare(KruskElem k1,KruskElem k2){
    return k1.distance<k2.distance;
}

int parent[1002];
int find(int x){
    if(parent[x]==x){
        return x;
    }
    return parent[x]=find(parent[x]);
}
void Union(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx==fy){
        return;
    }
    parent[fx]=fy;
}

int main(){
    int N,M;
    cin>>N>>M;
    Graph gph(N);
    KruskElem E[3001];
    for(int i=0;i<M;i++){
        int a,b,w;
        cin>>a>>b>>w;
        gph.setEdge(a,b,w);
        E[i]=KruskElem(a,b,w);
    }
    for(int i=1;i<=N;i++){
        parent[i]=i;
    }
    graphTraverse(&gph);
    if(!gph.isConnected()){
        cout<<-1<<endl;
        return 0;
    }
    sort(E,E+M,compare);
    int price=0;
    int cnt=0;
    for(int i=0;i<M;i++){
        if(cnt>=N-1){
            break;
        }
        /*因为同一等价类的元素parent值有可能还未更新成最新的值，因此先调用find函数，更新了传入参
        数的parent值，再进行判断*/
        if(find(E[i].from)!=find(E[i].to)){
            Union(E[i].from,E[i].to);
            cnt++;
            price+=E[i].distance;
            // cout<<"("<<E[i].from<<","<<E[i].to<<") = "<<E[i].distance<<endl;
            // for(int i=1;i<=N;i++){
            //     cout<<parent[i]<<" ";
            // }
            // cout<<endl;
        }
    }
    cout<<price<<endl;


    return 0;
}
