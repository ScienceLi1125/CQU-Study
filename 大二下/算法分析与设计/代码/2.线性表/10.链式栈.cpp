/*链式栈（不需要表头结点）
注：以链式栈栈顶作为第一个元素，即为栈的top。因为栈不断压入元素同时top也在变，因此不需要current指针
*/
#include <iostream>
using namespace std;

typedef int ElemType;
struct Node{
    ElemType elem;
    Node *next;
};
typedef struct Node* LinkStack;         //Node是结点，结点相连得到链式栈

void InitStack(LinkStack &top){          //top表示栈顶，这里代指整个链式栈
    int n;
    while(cin>>n && n!=-1){
        Node* node=new Node{n,top};     //新结点的next指针指向栈顶
        top=node;                       //更新栈顶
    }
    return;
}
void push(LinkStack &top,ElemType it){
	//Node n={it,top};                  //在栈中分配内存只在函数中有效，main函数运行时会出错
    Node* node=new Node{it,top};
	top=node;
}
ElemType pop(LinkStack &top){
	Node* node=top;
    top=top->next;
    ElemType tmp=node->elem;
    delete node;
    return tmp;
}
ElemType topValue(LinkStack &top){
	//使用前需判断非空
	return top->elem;
}
int size(LinkStack &top){
    if(top==NULL){
        return 0;
    }
    int cnt=1;
    while(top->next!=NULL){
        cnt++;
        top=top->next;
    }
	return cnt;
}

int main(){
    LinkStack top=NULL;
    InitStack(top);
    push(top,100);
    push(top,98);
    cout<<pop(top)<<endl;
    cout<<topValue(top)<<endl;
    cout<<size(top)<<endl;

    return 0;
}