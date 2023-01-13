/*快排序 O(nlogn)：
    寻找轴值（即数组的中位数，不过此处的轴值并不是找到的中位数，只是假定的中位数），然后将大于轴值
的元素放在其右边，小于轴值的放在其左边。然后继续对左右两组数进行快排。
*/
#include <iostream>
#include <time.h>
using namespace std;
/*partition函数将数组的l+1~r-1划分为两个以轴值为分界的部分，并返回轴值的下标（实际上该位元素与最
后一位交换后才是真正的轴值下标）
*/
int partition(int A[],int l,int r,int& pivot){  //l,r为A[]的左右范围，pivot为轴值
    do{
        while(A[++l]<pivot);                    //跳过满足小于轴值的元素，终止在大于轴值的地方
        while((l<r)&&(A[--r]>pivot));
        int tmp=A[r];
        A[r]=A[l];
        A[l]=tmp;
    }while(l<r);
    return l;
}

void qsort(int A[],int i,int j){
    if(i>=j)    return;
    int pivotindex=(i+j)/2;                 //随机选取的轴值
    int pivot=A[pivotindex];
    A[pivotindex]=A[j];
    A[j]=pivot;                             //将轴值与末尾元素互换
    pivotindex=partition(A,i-1,j,A[j]);     //将l+1~r-1按轴值分部，并返回待与轴值交换元素下标
    pivot=A[j];                             //轴值还在末尾等待交换
    A[j]=A[pivotindex];
    A[pivotindex]=pivot;
    qsort(A,i,pivotindex-1);
    qsort(A,pivotindex+1,j);
}
//普通插入排序
void inssort(int A[],int n){
    for(int i=1;i<n;i++){
        for(int j=i;j>0;j--){
            if(A[j]<A[j-1]){
                int tmp=A[j];
                A[j]=A[j-1];
                A[j-1]=tmp;
            }
            else{
                break;
            }
        }
    }
}
int main(){
    int a[10000];
    int b[10000];
    for(int i=0;i<10000;i++){
        int tmp=rand()%20000;
        a[i]=b[i]=tmp;
    }
    clock_t start1,start2,end1,end2;
    start1=clock();
    qsort(a,0,9999);
    end1=clock();
    start2=clock();
    inssort(b,10000);
    end2=clock();
    cout<<"Time cost of qsort:"<<double(end1-start1)/CLOCKS_PER_SEC<<"s"<<endl;
    cout<<"Time cost of inssort:"<<double(end2-start2)/CLOCKS_PER_SEC<<"s"<<endl;
    
    return 0;
}
