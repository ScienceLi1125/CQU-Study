#include <iostream>
using namespace std;
#define NoExst 999999

struct Node{
    int elem;
    Node *pre;
    Node *next;
};

Node* head=NULL;
Node* tail=NULL;
void InitList(){
    int n;
    Node HeadNode={NoExst,NULL,NULL};       //HeadNode表示表头，不包含结点信息
    Node TailNode={NoExst,NULL,NULL};       //TailNode表示末尾，不包含结点信息
    HeadNode.next=&TailNode;
    TailNode.pre=&HeadNode;
    head=&HeadNode;                         //head为表头指针，指向表头
    tail=&TailNode;                         //tail为尾部指针，指向末尾
    Node* current=head;                     //current指向当前节点，初值为head
    while(cin>>n && n!=-1){
        Node* node=new Node{n,current,&TailNode};
        current->next=node;
        tail->pre=node;
        current=node;
    }
    return;
}

int main(){
    InitList();
    cout<<"Sequential output:";
    Node* tmp1=head->next;
    while(tmp1!=tail){                      //因为有了TailNode，所以不能用NULL判断
        cout<<tmp1->elem<<" ";
        tmp1=tmp1->next;
    }    
    cout<<endl<<"Reverse order output:";
    Node* tmp2=tail->pre;
    while(tmp2!=head){                      //此处会出现输出异常，据说为海森堡bug，一时难以解决
        cout<<tmp2->elem<<" ";
        tmp2=tmp2->pre;
    }
    

    return 0;
}