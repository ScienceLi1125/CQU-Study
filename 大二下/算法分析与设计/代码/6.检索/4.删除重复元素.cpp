/*删除重复元素：
    题目：排好序的数列A，删除其重复元素，不可以用额外空间
    思路：用size标记数组有效位置，初值为0，从i=1开始，若A[i]!=A[size]，则size++，然后A[size]=A[size]
*/
#include <iostream>
#include <algorithm>
using namespace std;

int removedup(int A[],int n){
    int size=0;
    for(int i=0;i<n;i++){
        if(A[i]!=A[size]){
            A[++size]=A[i];
        }
    }
    return size+1;
}

int main(){
    int a[100];
    for(int i=0;i<100;i++){
        a[i]=rand()%80;
    }
    sort(a,a+100);
    for(int i=0;i<100;i++){
        cout<<a[i]<<" ";
        if(i!=0 && i%20==0){
            cout<<endl;
        } 
    }
    cout<<endl;
    int res=removedup(a,100);
    cout<<"Different number:"<<res<<endl;
    for(int i=0;i<res;i++){
        cout<<a[i]<<" ";
        if(i!=0 && i%20==0){
            cout<<endl;
        } 
    }
    
    return 0;
}
