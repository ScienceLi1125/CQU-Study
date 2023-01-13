/*选择排序 O(n*n)：
    第i次排序选择数组中第i小元素放在第i位。即每次都在未排序数组中选择最小元素放在其开头。
*/
#include <iostream>
#include <algorithm>
using namespace std;

template<typename E,typename Comp>
void selsort(E A[],int n){
    for(int i=0;i<n-1;i++){
        int index=i;
        for(int j=n-1;j>i;j--){
            if(Comp::prior(A[j],A[index])){
                index=j;
            }
        }
        swap(A,i,index);
    }
}

int main(){
    int N,M;
    cin>>N>>M;
    
    return 0;
}
