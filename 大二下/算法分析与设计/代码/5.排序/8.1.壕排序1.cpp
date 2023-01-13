/*壕排序：
题目：壕班学生排队取快递，所有学生要是看到前面学生的钱比自己少就给他1元钱，然后两人交换位置。直到
    所有人都不比前面的人多1元为止。但有时会出现无休止的两人换位置情况。请判断所给序列是否可以在有限
    步数内排好。
输入：第一行输入两个正整数N和K；接下来N行每行输入K个整数，用空格分开。
输出：每组序列是否可以排好。
思路：数组元素向前移-1，向后移+1。无休止的两人换位置情况原因是两人相差1，因此只要将所有元素移至最
    后（加上相应步数）判断是否有元素值相等即可。
*/
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int N,K;
    cin>>N>>K;
    int a[1001]={0};
    for(int i=0;i<N;i++){
        for(int j=0;j<K;j++){
            cin>>a[j];
            a[j]+=(K-j-1);
        }
        sort(a,a+K);
        bool flag=1;
        for(int i=1;i<K;i++){
            if(a[i]==a[i-1]){
                flag=0;
            }
        }
        if(flag){
            cout<<"T"<<endl;
        }
        else{
            cout<<"F"<<endl;
        }
    }

    return 0;
}
