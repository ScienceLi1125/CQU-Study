//以下均以邻接矩阵为例
#include <iostream>
#include <queue>
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
        for(int i=0;i<numVertex;i++){
            delete [] matrix[i];
        }
        delete [] matrix;
    }
    void Init(int n){
        numVertex=0;
        numEdge=0;
        mark=new int[n];
        for(int i=0;i<numVertex;i++){
            mark[i]=0;
        }
        matrix=(int**)new int*[numVertex];
        for(int i=0;i<numVertex;i++){
            matrix[i]=new int[numVertex];
        }
        for(int i=0;i<numVertex;i++){
            for(int j=0;j<numVertex;j++){
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
        for(int i=0;i<numVertex;i++){
            if(matrix[v][i]!=0){
                return i;
            }
        }
        return numVertex;
    }
    int next(int v,int w){
        for(int i=w+1;i<numVertex;i++){
            if(matrix[v][i]!=0){
                return i;
            }
        }
        return numVertex;
    }
    void setEdge(int v1,int v2,int weight){
        if(matrix[v1][v2]==0){
            numEdge++;
        }
        matrix[v1][v2]=weight;
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
};

void DFS(Graph* G,int v){                       //深搜只能搜索连通图
    //Previsit(G,v);
    G->setMark(v,1);
    for(int w=G->first(v);w<G->n();w=G->next(v,w)){
        if(G->getMark(w)==0){
            DFS(G,w);
        }
    }
    //Postvisit(G,v);
}
void BFS(Graph* G,int start,queue<int>* Q){     //相当于层序遍历
    int v,w;
    Q->push(start);
    G->setMark(start,1);
    while(Q->size()!=0){
        v=Q->front();
        Q->pop();
        //Previsit(G,v);
        for(w=G->first(v);w<G->n();w=G->next(v,w)){
            if(G->getMark(w)==0){
                G->setMark(w,1);
                Q->push(w);
            }
        }
    }
}
void graphTraverse(Graph* G){   //对一个不连通的图，光dfs/bfs无法遍历，因此需要graphTraverse
    int v;
    for(v=0;v<G->n();v++){
        G->setMark(v,0);        //遍历前先初始化
    }
    for(v=0;v<G->n();v++){      //v为点的序号，直接遍历即可
        if(G->getMark(v)==0){
            DFS(G,v);
        }
    }
}

int main(){
    

    return 0;
}
