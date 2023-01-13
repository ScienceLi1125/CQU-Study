/*公路村村通：
题目：现有村落间道路的统计数据表中，列出了有可能建设成标准公路的若干条道路的成本，求使每个村落都有
    公路连通所需要的最低成本。
输入：数据包括城镇数目正整数N（≤1000）和候选道路数目M（≤3N）；随后的M行对应M条道路，每行给出3个正
    整数，分别是该条道路直接连通的两个城镇的编号以及该道路改建的预算成本。为简单起见，城镇从1到N编
    号。
输出：村村通需要的最低成本。如果输入数据不足以保证畅通，则输出?1，表示需要建设更多公路。
注意：此处从1计数，因此构造函数中数组要开到n+1。但初始化时都要初始化，否则会出错
    本题为无向图，为方便起见，只使用上三角矩阵
思路：此处采用Kruskal算法，因为Kruskal算法基于边权，但从图中不断搜索边太过耗时，因此定义KruskElem
    类存储边权以及边的节点。对边权进行排序，检验是否在同一个等价类。其中u,v两个点在两个不同等价类
    中可以用mark[u]==0||mark[v]==0表示（误）
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
        mark=new int[n+1];                  //从1计数
        for(int i=0;i<=numVertex;i++){
            mark[i]=0;
        }
        matrix=(int**)new int*[numVertex+1];
        for(int i=0;i<=numVertex;i++){      //用不到的也要初始化
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
void graphTraverse(Graph* G){       //从1开始遍历，判断是否连通
    for(int v=1;v<=G->n();v++){
        G->setMark(v,0);
    }
    DFS(G,1);
}

class KruskElem{                //Kruskal算法基于边，若每次都通过图的遍历实现太费时
public:
    int from,to,distance;       //基于上述假设，默认from<to
    KruskElem():from(-1),to(-1),distance(-1){}
    KruskElem(int f,int t,int d):from(f),to(t),distance(d){}
};
bool compare(KruskElem k1,KruskElem k2){    //比较两个KruskElem中边的大小
    return k1.distance<k2.distance;
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
        //gph.setEdge(b,a,w);       //为方便起见，只写入一条边
        E[i]=KruskElem(a,b,w);
    }
    graphTraverse(&gph);            //遍历图判断是否连通
    if(!gph.isConnected()){
        cout<<-1<<endl;
        return 0;
    }
    sort(E,E+M,compare);            //对边权升序排列
    for(int v=1;v<=gph.n();v++){    //重置mark数组
        gph.setMark(v,0);
    }
    int price=0;                    //修路成本，即边权之和
    int cnt=0;                      //记录选中边数之和
    for(int i=0;i<M;i++){           //按边权升序遍历边
        if(cnt>=N-1){
            break;
        }
        if(gph.getMark(E[i].from)==0||gph.getMark(E[i].to)==0){ //边连接的点至少一个未被访问
            gph.setMark(E[i].from,1);
            gph.setMark(E[i].to,1);
            cnt++;
            price+=E[i].distance;
        }
    }
    cout<<price<<endl;

    return 0;
}
