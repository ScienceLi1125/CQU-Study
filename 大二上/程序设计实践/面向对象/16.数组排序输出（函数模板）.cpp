#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

template <class T>
void sort(T* a,int n){      //输入的第一个形参为T型指针，指代数组
    for(int i=0;i<n;i++){   
        cin>>a[i];          //函数内部也支持输入
    }
    sort(a,a+n);            //调用algorithm中sort函数
}

template <class T>
void display(T* a, int size){
    for(int i=0; i<size-1; i++) cout<<a[i]<<' ';
    cout<<a[size-1]<<endl;
}

int main() {
    const int SIZE=10;
    int a[SIZE];
    char b[SIZE];
    double c[SIZE];
    string d[SIZE];
    int ty, size;
    cin>>ty;
    while(ty>0){
        cin>>size;
        switch(ty){
            case 1:sort(a,size); display(a,size); break;
            case 2:sort(b,size); display(b,size); break;
            case 3:sort(c,size); display(c,size); break;
            case 4:sort(d,size); display(d,size); break;
        }
        cin>>ty;
    }
     return 0;
}
