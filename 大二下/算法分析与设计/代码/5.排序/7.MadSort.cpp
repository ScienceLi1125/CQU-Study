/*资深程序员的MadSort
*/
#include <iostream>
#include <time.h>
using namespace std;

void MadSort(int A[],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(A[i]<A[j]){          //看似不可思议，但通过不断交换，可以达到排序效果
                int tmp=A[i];
                A[i]=A[j];
                A[j]=tmp;
            }
        }
    }
}
void BubSort(int A[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=n-1;j>i;j--){
            if(A[j],A[j-1]){
                int tmp=A[j];
                A[j]=A[j-1];
                A[j-1]=tmp;
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
    MadSort(a,10000);
    end1=clock();
    start2=clock();
    BubSort(b,10000);
    end2=clock();
    cout<<"Time cost of MadSort:"<<double(end1-start1)/CLOCKS_PER_SEC<<"s"<<endl;
    cout<<"Time cost of inssort:"<<double(end2-start2)/CLOCKS_PER_SEC<<"s"<<endl;
    cout<<"排序后a[n] :"<<endl;
    for(int i=0;i<10000;i++){
        cout<<a[i]<<" ";
        if(i!=0&&i%20==0){
            cout<<endl;
        }
    }

    return 0;
}