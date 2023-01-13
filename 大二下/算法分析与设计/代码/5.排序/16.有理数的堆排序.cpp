/*有理数的堆排序:
题目：自定义有理数类并用最小堆进行排序
输入：第一行包含一个整数T(1<=T<=100000)；接下来的T行，每一行有两个整数n, d (|n|<103, 0<d<1000)，
    用空格隔开，表示输入的有理数的分子和分母。
输出：第一行输出有理数的最小堆序列，第二行输出从小到大排序后的序列。
    其中输出的每个有理数必须规约，以n/d的形式输出，其中d>0且gcd(n,d)=0；如果d=1或n=0则直接输出n
输入样例：  
5        //有理数个数
3 2      //第1个有理数  3/2
1 3      //第2个有理数  1/3
4 2      //第3个有理数  4/2
12 10    //第4个有理数  12/10
4 6      //第5个有理数  4/6
输出样例：
1/3  2/3  2  6/5  3/2    //第一行 最小堆
1/3  2/3  6/5  3/2  2    //第二行 排序结果
*/
#include <iostream>
#include <algorithm>
using namespace std; 

class Rational{
friend bool operator<(const Rational& r1, const Rational& r2);
friend bool operator<=(const Rational& r1, const Rational& r2);
friend bool operator>(const Rational& r1, const Rational& r2);
friend bool operator>=(const Rational& r1, const Rational& r2);
friend bool operator==(const Rational& r1, const Rational& r2);
friend bool operator!=(const Rational& r1, const Rational& r2);
friend ostream&operator<<(ostream&os,const Rational&r);
public:
    int N; //分子
    int D; //分母大于0
   
    Rational() {                    //default constructor
        N=0;
        D=1;
    }
    Rational(int n){                //constructor for integer value
        N=n;
        D=1;
    }
    Rational(int n, int d) {        //normal constructor
        int gcd=abs(__gcd(n,d));    //约分
        N=n/gcd;
        D=d/gcd;
    }
    Rational(const Rational& r){    //copy constructor
        N=r.N;
        D=r.D;
    }
    Rational& operator=(const Rational& r){// assignment override
        N=r.N;
        D=r.D;
        //return this;
        return *this;
    }
};
bool operator<(const Rational& r1, const Rational& r2){
    return r1.N*r2.D<r1.D*r2.N;
}
bool operator<=(const Rational& r1, const Rational& r2){
    return r1.N*r2.D<=r1.D*r2.N;
}
bool operator>(const Rational& r1, const Rational& r2){
    return r1.N*r2.D>r1.D*r2.N;
}
bool operator>=(const Rational& r1, const Rational& r2){
    return r1.N*r2.D>=r1.D*r2.N;
}
bool operator==(const Rational& r1, const Rational& r2){
    return r1.N*r2.D==r1.D*r2.N;
}
bool operator!=(const Rational& r1, const Rational& r2){
    return r1.N*r2.D!=r1.D*r2.N;
}
ostream&operator<<(ostream&os,const Rational&r){
    if(r.D==1)
        os<<r.N;
    else
        os<<r.N<<"/"<<r.D;
    return os;
}

class heap{
private:
    Rational* Heap;
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
            Rational tmp=Heap[pos];
            Heap[pos]=Heap[j];
            Heap[j]=tmp;
            pos=j;
        }
    }
public:
    heap(Rational* h,int num,int max){
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
    void insert(const Rational& r){
        int curr=n++;
        Heap[curr]=r;
        while((curr!=0)&&(Heap[curr]<Heap[parent(curr)])){
            Rational tmp=Heap[curr];
            Heap[curr]=Heap[parent(curr)];
            Heap[parent(curr)]=tmp;
            curr=parent(curr);
        }
        // for(int i=0;i<n;i++){
        //     cout<<Heap[i]<<" ";
        // }
        // cout<<endl;
    }
    Rational removefirst(){
        n--;
        Rational tmp=Heap[0];
        Heap[0]=Heap[n];
        Heap[n]=tmp;
        if(n!=0){
            siftdown(0);
        }
        return Heap[n];
    }
    Rational remove(int pos){
        if(pos==(n-1)){
            n--;
        }
        else{
            n--;
            Rational tmp=Heap[pos];
            Heap[pos]=Heap[n];
            Heap[n]=tmp;
            while((pos!=0)&&(Heap[pos]<Heap[parent(pos)])){
                Rational tmp=Heap[pos];
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
void heapsort(Rational A[],int n){
    Rational minval;
    heap H(A,n,n);
    for(int i=0;i<n;i++){
        minval=H.removefirst();
    }
}

int main(){
    int n;
    cin>>n;
    Rational rt[100001];
    for(int i=0;i<n;i++){
        int a,b;
        cin>>a>>b;
        Rational r(a,b);
        rt[i]=r;
    }                       //填充完数组再建堆
    heap hp(rt,n,100001);
    for(int i=0;i<n;i++){
        cout<<rt[i]<<" ";
    }
    cout<<endl;
    heapsort(rt,n);
    for(int i=n-1;i>=0;i--){
        cout<<rt[i]<<" ";
    }
    
    return 0;
}
