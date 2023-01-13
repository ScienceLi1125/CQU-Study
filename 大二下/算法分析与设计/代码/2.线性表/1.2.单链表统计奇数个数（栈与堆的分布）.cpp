/*链表（不含头结点）统计奇数个数：
*/
#include <iostream>
using namespace std;

struct Node{
    int elem;
    Node *next;
};

Node* head=NULL;                //Node是结点，结点相连得到链表，head在此处充当表头指针
void InitList(){
    int n;
    Node* current=head;         //current指向当前节点，初值为head
    bool flag=0;
    while(cin>>n && n!=-1){
        //Node node={n,NULL};     //在栈中创建结点会导致下一次循环中旧结点被收回，因此在堆中动态分配内存
        Node* node=new Node{n,NULL};    //在堆中动态分配的指向新的节点的指针
        if(!flag){              //初始化head
            head=node;
            current=head;
            flag=1;
        }
        current->next=node;     //将上一节点指针指向新的节点（因为是指针传递，所以可以直接修改）
        current=node;           //current指向新结点
        //此处node是新结点的指针，因此其本身就可以作为地址赋给current指针
    }
    return;
}
int OddNumber(){
    int sum=0;
    Node* current=head;
    while(current!=NULL){
        if(current->elem%2!=0){
            sum++;
            cout<<current->elem<<endl;
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