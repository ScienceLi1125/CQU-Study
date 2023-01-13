/*查找不大于N的所有素数：
    题目：给定正整数N(N<=10000)，求不大于N的所有素数
    思路：开长度为N的数组，初值为1，从2开始，遍历不大于N的2的倍数标记为0，继续向后遍历未被标记为
0的数值，并将其后面小于N的数中其整数倍下标的数值标记为0，直到N
*/
#include <iostream>
#include <algorithm>
using namespace std;

int N;
void markPrime(int A[],int start){
    for(int i=2;i*start<=N;i++){
        A[i*start]=0;
    }
}

int main(){
    cin>>N;
    int Prime[10001]={0};
    for(int i=2;i<=N;i++){
        Prime[i]=1;
    }
    for(int i=2;i<=N/2;i++){
        markPrime(Prime,i);
    }
    int cnt=0;
    for(int i=2;i<=N;i++){
        if(Prime[i]){
            cout<<i<<" ";
            cnt++;
        }
    }
    cout<<endl<<"Total number:"<<cnt<<endl;
    
    return 0;
}
