/*希尔排序 O(n**1.5)：
    希尔排序将数组分治（分的方法不同于归并），然后合并，对数组内排序时使用插入排序。
    直接来看希尔排序的复杂度好像比插入排序还高，但对数组分治的处理大大减少了插入排序的比较和交换次数，
从而降低了复杂度。
*/
#include <iostream>
#include <time.h>
using namespace std;
int cnt1=0;
int cnt2=0;
//普通插入排序
void inssort(int A[],int n){
    for(int i=1;i<n;i++){
        for(int j=i;j>0;j--){
            if(A[j]<A[j-1]){
                int tmp=A[j];
                A[j]=A[j-1];
                A[j-1]=tmp;
                cnt2++;
            }
            else{
                break;
            }
        }
    }
}
//希尔排序
void inssort2(int A[],int n,int incr){      //n为传入数组长度，incr为数组内元素间隔
    for(int i=incr;i<n;i+=incr){            //incr相当于第1位元素，+incr相当于间隔
        for(int j=i;(j>=incr)&&(A[j]<A[j-incr]);j-=incr){
            int tmp=A[j];
            A[j]=A[j-incr];
            A[j-incr]=tmp;
            cnt1++;
        }
    }
}
void shellsort(int A[],int n){
    for(int i=n/2;i>2;i/=2){            //i表示组数或者间隔
        for(int j=0;j<i;j++){           //j表示有i组数据时从0到i遍历
            inssort2(&A[j],n-j,i);      //对第j组数据进行插入排序（起始位置，长度，间隔）
        //第j组数据在A中下标:j,j+i,j+2i...用inssort2中传入参数表示为:&A[j],&A[j]+i,&A[j]+2i...
        }
    }
    inssort2(A,n,1);                    //对整个数组插入排序
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
    shellsort(a,10000);
    end1=clock();
    start2=clock();
    inssort(b,10000);
    end2=clock();
    cout<<"Time cost of shellsort:"<<double(end1-start1)/CLOCKS_PER_SEC<<"s"<<endl;
    cout<<"Times of swap:"<<cnt1<<endl;
    cout<<"Time cost of inssort:"<<double(end2-start2)/CLOCKS_PER_SEC<<"s"<<endl;
    cout<<"Times of swap:"<<cnt2<<endl;
    // for(int i=0;i<10000;i++){
    //     cout<<a[i]<<" ";
    //     if(i!=0&&i%20==0){
    //         cout<<endl;
    //     }
    // }
    
    return 0;
}
