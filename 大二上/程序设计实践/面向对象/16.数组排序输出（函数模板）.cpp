#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

template <typename T>		//普通函数模板 
void sortT(T* arr,int n){   	//输入的第一个形参为T型指针，指代数组
    for(int i=0;i<n;i++){
    	cin>>arr[i];
	}
    sort(arr,arr+n);
}

template <class T>
void display(T* arr, int size){
    for(int i=0; i<size-1; i++) cout<<arr[i]<<' ';
    cout<<arr[size-1]<<endl;
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
        if(size>SIZE){
        	cout<<"Too large array!"<<endl;
        	exit(-1);
		}
        switch(ty){
            case 1:sortT<int>(a,size); display(a,size); break;
            case 2:sortT<char>(b,size); display(b,size); break;
            case 3:sortT<double>(c,size); display(c,size); break;
            case 4:sortT<string>(d,size); display(d,size); break;
            default:cout<<"Wrong Input!"<<endl; break;
        }
        cin>>ty;
    }
     return 0;
}