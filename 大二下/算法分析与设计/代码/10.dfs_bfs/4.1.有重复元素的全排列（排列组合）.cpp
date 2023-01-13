#include <iostream>
using namespace std;

int main(){
    int n;
    cin>>n;
    int a[100]={0};     //a用来存储输入的非重复元素,数组默认值未知，要初始化
    for(int i=0;i<n;i++){
        int m;
        cin>>m;
        a[m]+=1;
    }
    int M=1;
    for(int i=0;i<100;i++){
        if(a[i]>1){
            int p=1;
            for(int j=1;j<=a[i];j++){
                p*=j;
            }           //计算a[i]的阶乘
            M*=p;       //计算阶乘的乘积
        }
    }

    int N=1;
    for(int i=1;i<=n;i++){
        N*=i;
    }
    
    cout<<N/M;          //排列组合思想
    
    return 0;
}