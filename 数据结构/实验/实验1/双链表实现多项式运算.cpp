/*双链表的实际应用
1.编写使用freelist 的带头、尾结点的双向链表类的定义，实现双向链表的基本操作。
2.利用双向链表实现2个一元多项式的加法和乘法运算，运算结果得到的链表要求按照指数降序排列的多项式。
*/
#include <iostream>
using namespace std;

template<typename E> class DLLNode{     //双链表节点
private:
    static DLLNode<E>* freelist;
public:
    E ratio;                            //系数
    E index;                            //指数
    DLLNode* prev;
    DLLNode* next;
    DLLNode(E r,E i,DLLNode* prevp,DLLNode* nextp){
        ratio=r;
        index=i;
        prev=prevp;
        next=nextp;
    }
    DLLNode(DLLNode* prevp=NULL,DLLNode* nextp=NULL){
        prev=prevp;
        next=nextp;
    }
    void* operator new(size_t){
        if(freelist==NULL){
            return ::new DLLNode;
        }
        DLLNode<E>* tmp=freelist;
        freelist=freelist->next;
        return tmp;
    }
    void operator delete(void* ptr){
        ((DLLNode<E>*)ptr)->next=freelist;
        freelist=(DLLNode<E>*)ptr;
    }
};

template <typename E>
DLLNode<E>* DLLNode<E>::freelist = NULL;

template <typename E> class DLList{     //双链表
public:
    DLLNode<E>* head;                   //不是继承，而是调用
    DLLNode<E>* tail;
    DLLNode<E>* current;
    int cnt;
    //辅助函数
    void InitList(){
        head=new DLLNode<E>();
        tail=new DLLNode<E>();
        current=head;
        head->next=tail;
        tail->prev=head;
        cnt=0;
    }
    void RemoveAll(){
        while(head!=NULL){
            current=head;
            head=head->next;
            delete current;
        }
    }

    DLList(){
        InitList();
    }
    ~DLList(){                          //析构函数一定一定写好！！！否则程序无法结束
        RemoveAll();
    }
    void clear(){
        RemoveAll();
        InitList();
    }
    void prev(){
        if(current!=head){
            current=current->prev;
        } 
    }
    void next(){
        if(current!=tail){
            current=current->next;
        }
    }
    E getRatio(){
        return current->ratio;
    }
    E getIndex(){
        return current->index;
    }
    void insert(E r,E i){                   //在current指针所指位置后插入元素
        DLLNode<E>* node=new DLLNode<E>(r,i,current,current->next);
        current->next->prev=node;            //注意赋值先后顺序
        current->next=node;
        cnt++;
    }
    void append(E r,E i){                   //添加至末尾
        DLLNode<E>* node=new DLLNode<E>(r,i,tail->prev,tail);
        tail->prev->next=node;
        tail->prev=node;
        cnt++; 
    }
    void remove(){                          //删除current所指元素
        if(current->next!=tail){
            return;
        }
        DLLNode<E>* tmp=current->next;
        current->next->next->prev=current;
        current->next=current->next->next;
        delete tmp;
        cnt--;
    }
    void MoveToStart(){                     //指向头结点
        current=head;
    }
    void MoveToEnd(){                       //指向尾结点
        current=tail;
    }
    void moveToPos(int pos){
        current=head;
        for(int i=0;i<pos;i++){
            current=current->next;
        }
    }
    void getBegin(){                        //指向第一个元素
        current=head->next;
    }
    int length(){
        return cnt;
    }
    int currPos(){
        DLLNode<E>* tmp=head;
        int i;                      //放在循环外可以返回
        for(i=0;tmp!=current;i++){
            tmp=tmp->next;
        }      
        return i;
    }
    void addRatio(E r){
        current->ratio+=r;
    }
};

DLList<int> add(DLList<int> &A,DLList<int> &B){
    DLList<int> List;
    A.getBegin();
    B.getBegin();
    while(1){
        if(A.getIndex()==B.getIndex()){
            if(A.getRatio()+B.getRatio()!=0)
                List.append(A.getRatio()+B.getRatio(),A.getIndex());
            A.next();
            B.next(); 
        }
        else if(A.getIndex()>B.getIndex()){
            List.append(A.getRatio(),A.getIndex());
            A.next();
        }
        else{
            List.append(B.getRatio(),B.getIndex());
            B.next();
        }
        if(A.currPos()>A.length() || B.currPos()>B.length()){     //其中一个双链表遍历完，结束循环
            break;
        }
    }
    //将另外一个没有遍历完的双链表剩余结点添加到L3的尾部
    if(A.currPos()>A.length()){         //B没读完
        while(1){
            List.append(B.getRatio(),B.getIndex());
            B.next();
            if(B.currPos()>B.length()){
                break;
            }
        }
    }
    else{                               //A没读完
        while(1){
            List.append(A.getRatio(),A.getIndex());
            A.next();
            if(A.currPos()>A.length()){
                break;
            }
        }
    }
    return List;
}

DLList<int> mult(DLList<int> &C,DLList<int> &D){
    DLList<int> List;
    bool flag=0;
    C.getBegin();
    while(C.currPos()<=C.length()){
        D.getBegin();                               //D归位
        while(D.currPos()<=D.length()){
            List.getBegin();
            int r=C.getRatio()*D.getRatio();      //系数相乘
            int i=C.getIndex()+D.getIndex();      //指数相加
            if(flag){
                for(int j=0;j<List.length();j++){
                    if(i<List.getIndex()&&j!=List.length()-1)       //指数小于当前结点指数且没到最后一个结点，则指向下一个结点
                        List.next();
                    else if(i<List.getIndex()&&j==List.length()-1){ //指数小于当前结点指数且到了最后一个结点，则把该结点加到末尾
                        List.append(r,i);
                        break;
                    }
                    else if(i==List.getIndex()){           //指数相同，则系数相加，得到新的结点同时删掉原本的结点
                        if(r+List.getRatio()!=0)
                            List.addRatio(r);
                        else
                            List.remove();
                        break;
                    }
                    else{                                   //指数大于当前节点指数，则插入该结点
                        List.insert(r,i);
                        break;
                    }       
                }
            }
            else{                           //第一次运算直接将所有结果加到L中，无需比较
                List.append(r,i);
            }
            flag=1;
            D.next();
        }
        C.next();
    }
    return List;
}

void print(DLList<int> E){
    E.getBegin();
    cout<<E.length()<<endl;
    for(int i=0;i<E.length();i++){
        cout<<E.getRatio()<<" "<<E.getIndex()<<endl;
        E.next();
    }
}


int main(){
    int N,M;
    cin>>N>>M;
    DLList<int> List1,List2;
    for(int i=0;i<N;i++){
        int a,b;
        cin>>a>>b;
        List1.append(a,b);
    }
    for(int j=0;j<M;j++){
        int c,d;
        cin>>c>>d;
        List2.append(c,d);
    }
    print(add(List1,List2));
    print(mult(List1,List2));
    
    // List1.next();
    // List1.next();
    // List1.prev();
    // List1.getBegin();
    // List1.next();
    // while(List1.current!=List1.tail){
    //     cout<<List1.getRatio()<<" ";
    //     List1.next();
    // }
    // cout<<List1.currPos();
    return 0;
}
/*3 2
5 4
-3 2
1 0
6 2
-3 1 */