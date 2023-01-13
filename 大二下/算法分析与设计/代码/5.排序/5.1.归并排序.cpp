/*归并排序 O(nlogn)：
    将n元素数组不断二分至每组只有1个元素，然后开始合并集合。二分比较容易，合并时对两个待合并数组从
首位开始比较，将较小的放入排序后的集合即可。为了不额外占用过多空间，只使用两个数组轮换排序。
*/
#include <iostream>
#include <time.h>
using namespace std;

void mergesort(int A[],int tmp[],int left,int right){//left表示A[0]下标，right表示A[n-1]下标
    if(left==right) return;
    int mid=(left+right)/2;
    mergesort(A,tmp,left,mid);      //向下递归，二分集合并排序
    mergesort(A,tmp,mid+1,right);
    for(int i=left;i<=right;i++){
        tmp[i]=A[i];
    }
    int i1=left,i2=mid+1;           //i1,i2表示两个待合并数组（各自都已排序）首个未排序元素下标
    for(int curr=left;curr<=right;curr++){
        if(curr==mid+1){            //left数组已完成合并
            A[curr]=tmp[i2++];
        }
        else if(i2>right){          //right数组已完成合并
            A[curr]=tmp[i1++];
        }
        else if(tmp[i1]<tmp[i2]){
            A[curr]=tmp[i1++];
        }
        else{
            A[curr]=tmp[i2++];
        }
    }
}

int main(){
    int a[10000];
    int tmp[10000];
    for(int i=0;i<10000;i++){
        int tmp=rand()%20000;
        a[i]=tmp;
    }
    clock_t start,end;
    start=clock();
    mergesort(a,tmp,0,9999);
    end=clock();
    cout<<"Time cost of shellsort:"<<double(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
    //cout<<start<<" "<<end<<endl;
    
    return 0;
}
