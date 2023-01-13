/*插入排序 O(n*n)：
    先处理前2个元素，比较大小排序即可；接着再处理前3个元素，查看第3个元素的合适位置，寻找插入
方法为 从第3个位置向前遍历，查找到合适位置即停止查找（因为前2个元素已经排好序，因此可以break）；
同理继续处理后续元素。
*/
#include <iostream>
#include <algorithm>
using namespace std;

template<typename E,typename Comp>
void inssort(E A[],int n){
    for(int i=1;i<n;i++){
        for(int j=i;j>0;j--){
            if(Comp::prior(A[j],A[j-1])){       //A[j]<A[j-1](此处小于即排在前面)
                swap(A,j,j-1);
            }
            else{
                break;                          //A[j]已达到正确位置(时间优化)
            }
        }
    }
}

int main(){
    int N,M;
    cin>>N>>M;
    
    return 0;
}
