/*堆排序 O(nlogn)：
    将数组按最大堆的数据结构进行存储，每次将堆的最大元素放入数组末尾，重复操作直至堆的元素个数为0
排序完毕后最大值在末尾，若想降序输出，需从n向0遍历
*/
#include <iostream>
#include <time.h>
using namespace std;

class heap{
private:
    int* Heap;
    int maxsize;
    int n;
    void siftdown(int pos){
        while(!isLeaf(pos)){
            int lc=leftchild(pos);
            int rc=rightchild(pos);
            if((rc<n)&&(Heap[rc]>Heap[lc])){
                lc=rc;
            }
            if(Heap[pos]>Heap[lc]){
                return;
            }
            int tmp=Heap[pos];
            Heap[pos]=Heap[lc];
            Heap[lc]=tmp;
            pos=lc;
        }
    }
public:
    heap(int* h,int num,int max){
        Heap=h;
        n=num;
        maxsize=max;
        buildHeap();
    }
    int size(){
        return n;
    }
    bool isLeaf(int pos){
        return (pos>=n/2)&&(pos<n);
    }
    int leftchild(int pos){
        return 2*pos+1;
    }
    int rightchild(int pos){
        return 2*pos+2;
    }
    int parent(int pos){
        return (pos-1)/2;
    }
    void buildHeap(){
        for(int i=n/2-1;i>=0;i--){
            siftdown(i);
        }
    }
    void insert(const int& it){
        int curr=n++;
        Heap[curr]=it;
        while((curr!=0)&&(Heap[curr]>Heap[parent(curr)])){
            int tmp=Heap[curr];
            Heap[curr]=Heap[parent(curr)];
            Heap[parent(curr)]=tmp;
            curr=parent(curr);
        }
    }
    int removefirst(){
        n--;
        int tmp=Heap[0];
        Heap[0]=Heap[n];
        Heap[n]=tmp;
        if(n!=0){
            siftdown(0);
        }
        return Heap[n];
    }
    int remove(int pos){
        if(pos==(n-1)){
            n--;
        }
        else{
            n--;
            int tmp=Heap[pos];
            Heap[pos]=Heap[n];
            Heap[n]=tmp;
            while((pos!=0)&&(Heap[pos]>Heap[parent(pos)])){
                int tmp=Heap[pos];
                Heap[pos]=Heap[parent(pos)];
                Heap[parent(pos)]=tmp;
                pos=parent(pos);
            }
            if(n!=0){
                siftdown(pos);
            }
        }
        return Heap[n];
    }
};
void heapsort(int A[],int n){
    int maxval;
    heap H(A,n,n);
    for(int i=0;i<n;i++){
        maxval=H.removefirst();
    }
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
    heapsort(a,10000);
    end1=clock();
    start2=clock();
    inssort(b,10000);
    end2=clock();
    cout<<"Time cost of heapsort:"<<double(end1-start1)/CLOCKS_PER_SEC<<"s"<<endl;
    cout<<"Time cost of inssort:"<<double(end2-start2)/CLOCKS_PER_SEC<<"s"<<endl;
    // int A[10000];
    // for(int i=0;i<10000;i++){
    //     A[i]=rand()%10000;
    // }
    // heapsort(A,10000);
    // for(int i=0;i<10000;i++){
    //     cout<<A[i]<<" ";
    //     if(i%20==0 && i!=0){
    //         cout<<endl;
    //     }
    // }
    
    return 0;
}
