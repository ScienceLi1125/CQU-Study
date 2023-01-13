#include <iostream>
using namespace std;
#define NoExst 999999

struct Node{
    int elem;
    Node *next;
};

Node* head=NULL;
void InitList(){
    int n;
    Node HeadNode={NoExst,NULL};        //HeadNode表示表头，不包含结点信息，只作为开头使用
    head=&HeadNode;                     //head为表头指针，指向表头
    Node* current=head;
    while(cin>>n && n!=-1){
        Node* node=new Node{n,NULL};
        current->next=node;             //将上一结点的next指针指向新的节点
        current=node;                   //current指向新结点
    }
    return;
}
int OddNumber(){
    int sum=0;
    Node* current=head;
    while(current->next!=NULL){
        if(current->next->elem%2!=0){
            sum++;
        }
        current=current->next;
    }
    return sum;
}

int main(){
    InitList();
    printf("The number of odd numbers is %d.\n", OddNumber());
    return 0;
}