/*不含头结点的单链表逆置
*/
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表 */

List Reverse(List L){
    if(L==NULL){        //考虑单链表为空的情况（含有头结点的话就不会出现）
        return NULL;
    }
    List newlist=L;
    List current=L->Next;
    List next;
    newlist->Next=NULL;
    while(current!=NULL){
        next=current->Next;
        current->Next=newlist;
        newlist=current;
        current=next;
    }
    return newlist;
}

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}

