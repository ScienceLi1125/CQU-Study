/*由于5.1中测试点4（最大N和M，连通）答案错误，于是写了一个生成随机边权的N,M拉满的测试样例，但发现
此时编译卡死，原因应该是N=1000时相邻矩阵得开到1000*1000，而边M只有3000，边过于稀疏，采用相邻矩阵
造成资源浪费，于是换成邻接表，如下。
但还是无法成功......
后来发现u,v两个点在两个不同等价类中并不能用mark[u]==0||mark[v]==0表示。例如等价类A1中标记了(1,3)、
(1,4)，等价类A2中标记了(2,5)、(2,6)，如果查找到边(3,5)需要标记，但此时3，5都已经被标记过，则会跳过
这条边，因此判断方法不妥。
*/
#include <iostream>
#include <algorithm>
using namespace std;

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
class Graph{
private:
    LList<Edge>** vertex;
    int numVertex,numEdge;
    int *mark;
public:
    Graph(int num){
        Init(num);
    }
    ~Graph(){
        delete [] mark;
        for(int i=0;i<numVertex;i++){
            delete [] vertex[i];
        }
        delete [] vertex;
    }
    void Init(int n){
        numVertex=n;
        numEdge=0;
        mark=new int[n+1];
        for(int i=0;i<=numVertex;i++){
            mark[i]=0;
        }
        vertex=(LList<Edge>**)new LList<Edge>*[numVertex+1];
        for(int i=0;i<=numVertex;i++){
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
            return numVertex+1;
        }
        vertex[v]->moveToStart();
        Edge it=vertex[v]->getValue();
        return it.vertex();
    }
    int next(int v,int w){
        Edge it;
        if(isEdge(v,w)){
            if(vertex[v]->currPos()+1<vertex[v]->length()){
                vertex[v]->next();
                it=vertex[v]->getValue();
                return it.vertex();
            }
        }
        return numVertex+1; 
    }
    void setEdge(int i,int j,int weight){
        Edge currEdge(j,weight);
        if(isEdge(i,j)){
            vertex[i]->remove();
            vertex[i]->insert(currEdge);
        }
        else{
            numEdge++;
            for(vertex[i]->moveToStart();vertex[i]->currPos()<vertex[i]->length();vertex[i]->next()){
                Edge tmp=vertex[i]->getValue();
                if(tmp.vertex()>j){
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
    return;
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

int main(){
    int N=1000,M=3000;
    Graph gph(N);
    KruskElem E[3002];
    int tmp=0;
    while(tmp<M){
        for(int i=1;i<=N;i++){
            for(int j=i+1;j<=N;j++){
                tmp++;
                int w=rand()%10;
                gph.setEdge(i,j,w);
                E[tmp]=KruskElem(i,j,w);
            }
        }
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
