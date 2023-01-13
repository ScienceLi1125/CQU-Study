/*插入排序还是归并排序：
题目：插入排序是迭代算法，逐一获得输入数据，逐步产生有序的输出序列。每步迭代中，算法从输入序列中取出
    一元素，将之插入有序序列中正确的位置。如此迭代直到全部元素有序。
    归并排序进行如下迭代操作：首先将原始序列看成 N 个只包含 1 个元素的有序子序列，然后每次迭代归并
    两个相邻的有序子序列，直到最后只剩下 1 个有序的序列。
    现给定原始序列和由某排序算法产生的中间序列，请你判断该算法究竟是哪种排序算法？
输入：在第一行给出正整数 N (≤100)；随后一行给出原始序列的 N 个整数；最后一行给出由某排序算法产生的
    中间序列。这里假设排序的目标序列是升序。数字间以空格分隔。
输出：首先在第 1 行中输出Insertion Sort表示插入排序、或Merge Sort表示归并排序；然后在第 2 行中输
    出用该排序算法再迭代一轮的结果序列。题目保证每组测试的结果是唯一的。数字间以空格分隔，且行首尾
    不得有多余空格。
注意：此处归并排序不是严格的归并排序，而是两两合并，没有从N二分的过程
    设计过程发现，N不是2的整数指数倍时二分较为繁琐，因此排序前将N扩大到2的整数指数倍方便排序
*/
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int N;                  //N为实际长度
int cmp[101];           //中间序列

bool equal(int a[],int b[],int n){
    bool flag=1;
    for(int i=0;i<n;i++){
        if(a[i]!=b[i]){
            flag=0;
        }
    }
    return flag;
}

int insflag=0;
void inssort(int A[],int A2[],int n){
    for(int i=1;i<n;i++){
        bool flag=0;            //记录该轮循环是否交换
        for(int j=i;j>0;j--){
            if(equal(A,cmp,n)){
                insflag=1;
            }
            if(A[j]<A[j-1]){
                int tmp=A[j];
                A[j]=A[j-1];
                A[j-1]=tmp;
                if(insflag==1){         //记录找到中间序列后下一次执行
                    flag=1;
                }
            }
            // if(insflag==1){          //需要输出的是下一轮执行了的结果，不见换的不算
            //     for(int k=0;k<N;k++){
            //         A2[k]=A[k];
            //     }
            //     insflag++;
            //     return;
            // }
            else{
                break;
            }
            // if(insflag==1){          //需要这一轮交换结束
            //     for(int k=0;k<N;k++){
            //         A2[k]=A[k];
            //     }
            //     insflag++;
            //     return;
            // }
        }
        if(insflag==1 && flag==1){
            for(int k=0;k<N;k++){
                A2[k]=A[k];
            }
            insflag++;                  //使后续循环不再遍历到
            return;
        }
    }
    
}
//此处为了省事，归并排序内部分组排序用sort函数解决
int mrgflag=0;
void mergesort(int A[],int A2[],int n){
    for(int i=2;i<=n;i*=2){
        // for(int j=0;j<n;j++){
        //     cout<<A[j]<<" ";
        // }
        // cout<<endl;
        int tmp[129]={0};       //记录sort前后A是否变化
        for(int j=0;j<N;j++){
            tmp[j]=A[j];
        }
        if(equal(A,cmp,N)){     //不能比较到N0
            mrgflag=1;
        }
        for(int j=0;j<n;j+=i){
            sort(A+j,A+j+i);
        }
        if(mrgflag==1 && !equal(A,tmp,N)){
            for(int k=0;k<N;k++){
                A2[k]=A[k];
            }
            mrgflag++;
        }
    }
}

int main(){
    cin>>N;
    int N0=N;           //N0表示不小于N的2的最小正整数倍
    int cnt=log(N)/log(2);
    if(pow(2,cnt)!=N){
        N0=pow(2,cnt+1);
    }
    int a1[101];        //a1,b1表示待排序数组
    int b1[129];        //N向上取2的最小正整数倍，保证结果不溢出
    int a2[101];        //a2,b2表示输出的下一轮结果
    int b2[129];
    for(int i=0;i<N;i++){
        cin>>a1[i];
        b1[i]=a1[i];
    }
    for(int i=N;i<N0;i++){      //N~N0设为INFI
        b1[i]=9999;
    }
    for(int i=0;i<N;i++){
        cin>>cmp[i];
    }
    inssort(a1,a2,N);
    mergesort(b1,b2,N0);
    // for(int i=0;i<N;i++){
    //     cout<<b[i]<<" ";
    // }
    // cout<<"insflag:"<<insflag<<" mrgflag:"<<mrgflag<<endl;
    if(insflag){
        cout<<"Insertion Sort"<<endl;
        cout<<a2[0];
        for(int i=1;i<N;i++){
            cout<<" "<<a2[i];
        }
    }
    else if(mrgflag){
        cout<<"Merge Sort"<<endl;
        cout<<b2[0];
        for(int i=1;i<N;i++){
            cout<<" "<<b2[i];
        }
    }
    
    return 0;
}
