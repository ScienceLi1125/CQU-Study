/*链式队列：为方便操作，增加一个头结点
*/
#include <iostream>
using namespace std;
#define NoExst 999999

struct Node{
    int elem;
    Node *next;
};

void InitLinkQueue(Node* head,Node* tail){
	Node HeadNode={NoExst,NULL};
	head=&HeadNode;						//head指向表头，而不是队列的第一个元素
	Node* current=head;
	tail=current;
	int n;
    while(cin>>n && n!=-1){
        Node* node=new Node{n,NULL};
        current->next=node;
        current=node;
		tail=current;					//tail随时指向current所指位置
    }
}
void push(Node* tail,int it){
	tail->next=new Node{it,NULL};
	tail=tail->next;
}
int pop(Node* head){
	Node* node=head->next;
	int tmp=node->elem;
	head->next=node->next;				//表头指针指向第二个元素
	delete node;
	return tmp;
}
int frontValue(Node* head){
	return head->next->elem;
}
int rearValue(Node* tail){
	return tail->elem;
}

int main(){
	Node* head=NULL;
	Node* tail=NULL;
	InitLinkQueue(head,tail);
	push(tail,527);
	cout<<tail->elem<<endl;
	cout<<pop(head)<<endl;
	cout<<frontValue(head)<<endl;
	cout<<rearValue(tail)<<endl;

	return 0;
}