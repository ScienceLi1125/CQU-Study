/*最小堆排序*/
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
            int j=leftchild(pos);       //下面j表示的是lc和rc中较小值的下标
            int rc=rightchild(pos);
            if((rc<n)&&(Heap[rc]<Heap[j])){
                j=rc;
            }
            if(Heap[pos]<Heap[j]){
                return;
            }
            int tmp=Heap[pos];
            Heap[pos]=Heap[j];
            Heap[j]=tmp;
            pos=j;
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
        while((curr!=0)&&(Heap[curr]<Heap[parent(curr)])){
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
            while((pos!=0)&&(Heap[pos]<Heap[parent(pos)])){
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
    int minval;
    heap H(A,n,n);
    for(int i=0;i<n;i++){
        minval=H.removefirst();
    }
}

int main(){
    int A[10000];
    for(int i=0;i<10000;i++){
        A[i]=rand()%10000;
    }
    heapsort(A,10000);
    for(int i=0;i<10000;i++){
        cout<<A[i]<<" ";
        if(i%20==0 && i!=0){
            cout<<endl;
        }
    }
    
    return 0;
}
