/*诅咒序列的极大值：
题目：当数组A中的元素A[i]满足A[i]>max(A[i?1],A[i+1])时，该元素是A中的一个极大值。现有N个各不相
    同的正整数的数组，你的任务就是从中查找出一个极大值并输出极大值的位置。但不幸的是这个数组被封
    在一个被诅咒的类CursedArray里面，可以用operator[i]去询问第i个元素的值(1≤i≤N)，但查询的总次
    数不能超过3(上去整log(N)+1)，否则无论你找到的值是什么都会被判为任务失败。
函数接口定义：
    int search_maximum (CursedArray& A, const int N);
    其中N的值不超过30000；A是类CursedArray的实例（数组），其中A[0]=A[N+1]=0，0<A[i],A[j]≤1000000 
且A[i]!=A[j] (1≤i<j≤N)。函数须返回A[1]到A[N]中一个极大值的位置。
输入样例：
    第一行给出N, 第二行给出N个正整数，用空格分开
    15
    42 68 35 1 70 25 79 59 63 65 6 46 82 28 62
输出样例：
    41
注：极大值有68,70,79,65,82,62。如果找到其中一个位置且查询次数不超过15，程序会输出(82+1)/2=41
思路：既然限制访问次数，那么必然不能顺序访问，否则最坏情况是从1~N每次访问i-1,i,i+1，即需要3N次
    因此采用二分查找的思想查找极大值的位置，查找次数不大于3?log(N)?+1
    A[middle]>A[middle-1] && A[middle]>A[middle+1]：找到
    A[middle]>A[middle-1] && A[middle]<=A[middle+1]：右半部分
    A[middle]<=A[middle-1] && A[middle]>A[middle+1]：左半部分
    因为限制访问次数，因此每种情况中将A[middle]等赋给常数，以减少访问次数
*/

#include <iostream>
using namespace std; 

int search_maximum (CursedArray& A, const int N){
    int low=1,high=N;
    int middle=(low+high)/2;
    while(low<=high){
        middle=(low+high)/2;
        int a=A[middle-1];
        int b=A[middle];
        int c=A[middle+1];
        if(b>a && b>c){
            return middle;
        }
        else if(b>a){
            low=middle+1;
        }
        else{
            high=middle-1;
        }
    }
    return -1;
}


int main(){
    
    
    return 0;
}
