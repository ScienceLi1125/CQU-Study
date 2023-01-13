#include <iostream>
using namespace std;
template<typename E> class Link{
public:
    E element;
    Link *next;
    Link(const E& ele,Link* nex=NULL){
        element=ele;
        next=nex;
    }
    Link(Link* nex=NULL){
        next=nex;
    }
};
template<typename E> class LList{
private:
    Link<E>* head;
    Link<E>* tail;
    Link<E>* curr;
    int cnt;
    void init(){
        curr=tail=head=new Link<E>;
        cnt=0;
    }
    void removeall(){
        while(head!=NULL){
            curr=head;
            head=head->next;
            delete curr;
        }
    }
public:
    LList(int size=0){init();}
    ~LList(){removeall();}
    void insert(const E& it){
        curr->next=new Link<E>(it,curr->next);
        if(tail==curr){
            tail=curr->next;
        }
        cnt++;
    }
    E remove(){
        E it=curr->next->element;
        Link<E>* ltmp=curr->next;
        if(tail==curr->next){
            tail=curr;
        }
        curr->next=curr->next->next;
        delete ltmp;
        cnt--;
        return it;
    }
    int currPos() const{
        Link<E>* tmp=head;
        int i;
        for(i=0;curr!=tmp;i++){
            tmp=tmp->next;
        }
        return i;
    }
    const E& getValue()const{
        return curr->next->element;
    }
    int length() const{
        return cnt;
    }
    void moveToStart(){
        curr=head;
    }
    void next(){
        if(curr!=tail){
            curr=curr->next;
        }
    }
};

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
class Edge{
    int vert,wght;          //成员变量与成员函数尽量不同名，否则编译器容易报错
public:
    Edge(){
        vert=-1;
        wght=-1;
    }
    Edge(int v,int w){
        vert=v;
        wght=w;
    }
    int vertex(){
        return vert;
    }
    int weight(){
        return wght;
    }
};
class Graphl:public Graph{
private:
    LList<Edge>** vertex;
    int numVertex,numEdge;
    int *mark;          //mark数组描述节点状态，0表示未访问，1表示已访问
public:
    Graphl(int num){
        Init(num);
    }
    ~Graphl(){
        delete [] mark;
        for(int i=0;i<numVertex;i++){
            delete [] vertex[i];
        }
        delete [] vertex;
    }
    void Init(int n){
        int i;
        numVertex=n;
        numEdge=0;
        mark=new int[n];
        for(int i=0;i<numVertex;i++){
            mark[i]=0;
        }
        vertex=(LList<Edge>**)new LList<Edge>*[numVertex];
        for(int i=0;i<numVertex;i++){
            vertex[i]=new LList<Edge>();
        }
    }
    int n(){
        return numVertex;
    }
    int e(){
        return numEdge;
    }
    int first(int v){
        if(vertex[v]->length()==0){
            return numVertex;
        }
        vertex[v]->moveToStart();
        Edge it=vertex[v]->getValue();
        return it.vertex();
    }
    int next(int v,int w){
        Edge it;
        if(isEdge(v,w)){        //调用isEdge(v,w)时vertex[v]链表的curr指针已经指向了w
            if(vertex[v]->currPos()+1<vertex[v]->length()){
                vertex[v]->next();
                it=vertex[v]->getValue();
                return it.vertex();
            }
        }
        return numVertex; 
    }
    void setEdge(int i,int j,int weight){
        Edge currEdge(j,weight);
        if(isEdge(i,j)){        //调用isEdge(v,w)时vertex[v]链表的curr指针已经指向了w
            vertex[i]->remove();            //remove的是v处的节点
            vertex[i]->insert(currEdge);
        }
        else{                               //i,j还不连通
            numEdge++;
            for(vertex[i]->moveToStart();vertex[i]->currPos()<vertex[i]->length();vertex[i]->next()){
                Edge tmp=vertex[i]->getValue();
                if(tmp.vertex()>j){         //找到合适插入位置
                    break;
                }
            }
            vertex[i]->insert(currEdge);
        }
    }
    void delEdge(int i,int j){
        if(isEdge(i,j)){
            vertex[i]->remove();
            numEdge--;
        }
    }
    bool isEdge(int i,int j){
        Edge it;
        for(vertex[i]->moveToStart();vertex[i]->currPos()<vertex[i]->length();vertex[i]->next()){
            Edge tmp=vertex[i]->getValue();
            if(tmp.vertex()==j){
                return 1;
            }
        }
        return 0;
    }
    int weight(int i,int j){
        Edge curedge;
        if(isEdge(i,j)){
            curedge=vertex[i]->getValue();
            return curedge.weight();
        }
        else{
            return 0;
        }
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
