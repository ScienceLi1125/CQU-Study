/*基数排序 O(n):
    基数排序为多关键码排序，对数值排序时采用按次位优先(LSD)，先按个位分到10个不同的盒子（直接按给
定数组中元素顺序排列即可），然后再按十位，...直至最高位。若是对字符串排列，一般按高位优先。
*/
#include <iostream>
using namespace std;
//此处以0~999之间数据为例进行排序
void radixsort(int A[],int B[],int n){
    for(int ratio=1;ratio<=100;ratio*=10){
        int cnt[10]={0};
        int tmp[10][1000];          //临时数组表示每个盒中元素，只需要在循环内部声明即可
        for(int i=0;i<n;i++){
            //int a=(A[i]/ratio)%10;    //是对B操作而非A
            int a=(B[i]/ratio)%10;  //关键码位
            int b=cnt[a];
            //tmp[a][b]=A[i];
            tmp[a][b]=B[i];
            cnt[a]++;
        }
        int index=0;
        for(int i=0;i<10;i++){
            for(int j=0;j<cnt[i];j++){
                B[index++]=tmp[i][j];
            }
        }
    }
}

int main(){
    int A[1000];            //A[n]为待排序数组
    int B[1000];            //B[n]为排序后数组
    for(int i=0;i<1000;i++){
        A[i]=rand()%1000;
        B[i]=A[i];
    }
    //int cnt[10]={0};        //cnt[10]存储关键码0~9 10个盒子中各自容量
    //int tmp[10][1000];      //tmp[10][n]为每个盒中元素
    
    radixsort(A,B,1000);
    for(int i=0;i<1000;i++){
        cout<<B[i]<<" ";
        if(i!=0&&i%30==0){
            cout<<endl;
        }
    }
    
    return 0;
}
