/*计数排序 O(n):
    前面的几种排序方式均为比较排序，平均复杂度最好也得是nlogn。而计数排序的思想是将待排序数组的值
转化为再开一个数组的下标，用该数组记录每个元素出现的次数，然后叠加得数组中比每一位数字小的数，于是
可以得到各位数字的准确位置。
此处输入A[n]，输出B[n]，辅助空间C[k]
限制：
    1.数组值域必须是非负整数
    2.待排序数组最大值规模尽量与n成比例，如：A=[1,10**9]，数组长度受限
*/
#include <iostream>
#include <time.h>
using namespace std;

void countingsort(int A[],int B[],int n){
    int C[20001]={0};
    int max=0;
    for(int i=0;i<n;i++){
        if(max<A[i])    max=A[i];
    }
    for(int i=0;i<n;i++){
        C[A[i]]++;
    }                       //此时C[i]表示A[n]中i的个数为C[i]
    for(int i=1;i<=max;i++){
        C[i]+=C[i-1];
    }                       //此时C[i]表示A[n]中小于等于i的个数为C[i]
    //从大到小将A[i]赋到B[i]有利于维护数组的稳定性，没有改变A[n]中相等值的顺序
    for(int i=n-1;i>=0;i--){
        B[C[A[i]]]=A[i];
        C[A[i]]--;          //必须更新！！
    }
}

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
    int c[10000];
    for(int i=0;i<10000;i++){
        int tmp=rand()%20000;
        a[i]=b[i]=tmp;
    }
    clock_t start1,start2,end1,end2;
    start1=clock();
    countingsort(a,c,10000);
    end1=clock();
    start2=clock();
    inssort(b,10000);
    end2=clock();
    cout<<"Time cost of countingsort:"<<double(end1-start1)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
    cout<<"Time cost of inssort:"<<double(end2-start2)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
    
    return 0;
}
