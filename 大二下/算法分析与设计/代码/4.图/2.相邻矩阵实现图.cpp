#include <iostream>
using namespace std;

class Graph{
public:
    Graph(){}
    virtual ~Graph(){}
    virtual void Init(int n)=0;
    virtual int n()=0;
    virtual int e()=0;
    virtual int first(int v)=0;
    virtual int next(int v,int w)=0;
    virtual void setEdge(int v1,int v2,int weight)=0;
    virtual void delEdge(int v1,int v2)=0;
    virtual bool isEdge(int i,int j)=0;
    virtual int weight(int v1,int v2)=0;
    virtual int getMark(int v)=0;
    virtual void setMark(int v,int value)=0;
};
class Graphm:public Graph{
private:
    int numVertex,numEdge;
    int **matrix;
    int *mark;          //mark数组描述节点状态，0表示未访问，1表示已访问
public:
    Graphm(int num){
        Init(num);
    }
    ~Graphm(){
        delete [] mark;
        for(int i=0;i<numVertex;i++){
            delete [] matrix[i];
        }
        delete [] matrix;
    }
    void Init(int n){
        numVertex=n;
        numEdge=0;
        mark=new int[n];                    //初始化mark
        for(int i=0;i<numVertex;i++){       //给mark赋初值
            mark[i]=0;
        }
        matrix=(int**)new int*[numVertex];  //初始化matrix
        for(int i=0;i<numVertex;i++){
            matrix[i]=new int[numVertex];   //初始化matrix每一行
        }
        for(int i=0;i<numVertex;i++){
            for(int j=0;j<numVertex;j++){
                matrix[i][j]=0;             //给matrix赋初值
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

int main(){
    

    return 0;
}
