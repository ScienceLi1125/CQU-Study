/*冒泡排序 O(n*n)：
    从末尾开始比较相邻元素大小并不断交换直至开头，下一次只用交换到第二个元素（因为最小元素经过
第一次交换一定达到开头）。
注：交换最大值至末尾/最小值至开头都可行，纯属写法问题
Comparison：插入排序的本质是将一个未知元素插入到已经排好序的序列中，冒泡排序的本质是将最值放在
    合适位置，两者本质不同。
*/
#include <iostream>
#include <algorithm>
using namespace std;

template<typename E,typename Comp>
void bubsort(E A[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=n-1;j>i;j--){
            if(Comp::prior(A[j],A[j-1])){
                swap(A,j,j-1);
            }
        }
    }
}

int main(){
    int N,M;
    cin>>N>>M;
    
    return 0;
}
