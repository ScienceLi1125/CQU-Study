/*背包问题_最优装配：
题目：给出N个物体，重量分别为wi，使总重量不超过容量C的情况下选择数量尽量多的物体
思路：只要求数量多就可以，因此我们对重量进行排序然后贪心选择就好
*/
#include <iostream>
#include <algorithm>
using namespace std;


int main(){
    int N=10;
    int W[N]={1,5,6,4,9,2,8,7,3,4};
    int C=20;
    sort(W,W+N);
    int cnt=0;
    int sum=0;
    for(int i=0;i<N;i++){
        sum+=W[i];
        if(sum<C){
            cnt++;
        }
    }
    cout<<cnt<<endl;

    return 0;
}