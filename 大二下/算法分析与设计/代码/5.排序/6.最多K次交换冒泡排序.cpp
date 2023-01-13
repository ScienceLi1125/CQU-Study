/*最多K次交换冒泡排序：
题目：冒泡排序(bubble sort)通过在序列中不断比较和交换相邻的两个元素，最终把所有元素按升序排列。规
    定相邻元素的交换次数不超过K, 比较次数没有限制，求冒泡排序能生成的字典序最小序列。
输入：第一行输入两个正整数N和K (1<N≤1000, 1≤K≤N(N?1)/2)；接下来一行输入N个整数，用空格分开。所有
    整数值都在区间[0,100000]内。
输出：在一行中输出排序后的N个整数，用空格分开，末尾的数值后面没有空格。
思路：在0~K个元素中找最小值，记录交换次数，此时第0个排好序，剩余k1次交换次数；再在1~k1个元素中寻找
    最小值，记录交换次数，此时0~1个排好序，剩余k2次交换次数；以此类推，终止条件为k=0或序列排好序
*/
#include <iostream>
using namespace std;

int main(){
    int N,K;
    cin>>N>>K;
    int a[1001]={0};
    for(int i=0;i<N;i++){
        int b;
        cin>>b;
        a[i]=b;
    }
    int finished=0;         //表示前x位已排好序
    while(K>0){
        // cout<<"K还剩"<<K<<":";
        // for(int i=0;i<N;i++){
        //     cout<<a[i]<<" ";
        // }
        int cnt=0;          //交换次数
        int index;          //最小元素下标
        int min=100001;     //最小值
        //冒泡排序交换次数为n-1
        for(int i=finished;i<=K+finished&&i<N;i++){ //i不能越界，别遗漏i<N条件；慎用逗号!!!
            if(a[i]<min){
                index=i;
                min=a[i];
            }
        }                   //找到前K+1个中最小元素
        for(int i=index;i>finished;i--){
            if(a[i]<a[i-1]){
                int tmp=a[i];
                a[i]=a[i-1];
                a[i-1]=tmp;
                cnt++;
            }
        }
        finished++;
        K-=cnt;
    }
    for(int i=0;i<N-1;i++){
        cout<<a[i]<<" ";
    }
    cout<<a[N-1];
    //cout<<endl<<K<<endl;


    return 0;
}
