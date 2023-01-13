/*顺序表统计奇数个数：
题目：本题要求实现一个函数，要求返回顺序表中奇数的个数，空表返回0。
函数接口定义：int OddNumber(SqList L)
输入：数据有1行，给出以-1结束的顺序表元素（都是整数，且-1不属于顺序表元素），所有数据之间用空格分隔。
*/
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int ElemType;
typedef struct{
    ElemType *elem;             //int型指针，表示int型数组，支持下标运算
    int length;
}SqList;
void InitList(SqList &L);
int OddNumber(SqList L);
//写入函数
int OddNumber(SqList L){
    int sum=0;
    for(int i=0;i<L.length;i++){
        if(L.elem[i]%2!=0){     //负数取模可能+-1（也可以L.elem[i]+10000000000)%2==1）（不加2分，8个0 6分）
            sum+=1;
        }
    }
    return sum;
}

int main()
{
    SqList L;
    InitList(L);
    printf("The number of odd numbers is %d.\n", OddNumber(L));
    return 0;
}