/*单链表逆置:
题目：请编写函数Reverse，将带附加头结点的单链表逆置。
说明：Create 函数用于创建链表，Destroy 函数用于销毁链表。Input 函数用于输入链表：首先输入结点数，
然后输入这些数据元素。Output 函数用于输出单链表，数据元素之间以空格间隔。
注：本题的单链表指带头结点的单链表，如：head->5->3->9->NULL，因此逆置后变成head->9->3->5->NULL
*/
#include <iostream>
using namespace std;

typedef struct _NODE_{
    int data;
    struct _NODE_ *next;
} NODE;

void Reverse(NODE *head){
    NODE* current=head->next;   //此处单链表含有表头，因此从下一位开始取
    NODE* tmp;
    //head不再指原链表的表头，而指向了新链表的第一个结点，同名才能使判定程序重新调用
    head->next=NULL;            //将旧链表的表头与该链表断开，成为新链表的结尾
    while(current!=NULL){       //tmp指向原链表的表头
        tmp=current;            //存储current
        current=current->next;  //current向后移
        //此处新链表仍有表头
        tmp->next=head->next;   //旧链表第一个结点的next指针指向新链表的第一个结点
        head->next=tmp;         //head指针指向新链表的表头
    }
}

int main(){
    NODE *h;
    Create(&h);
    Input(h);
    Reverse(h);
    Output(h);
    putchar('\n');
    Destroy(&h);
    return 0;
}