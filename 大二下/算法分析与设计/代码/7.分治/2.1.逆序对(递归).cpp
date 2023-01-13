/*逆序对:
题目：求逆序对
输入：第一行是一个整数n，（n<=1000000）表示输入序列的长度，接下来一行是n个整数(每个数的绝对
    值小于10**9)。
输出：一个数，表示逆序对个数(逆序即任意一对数前面的数比后面的数大即为一对逆序对)。
输入样例:
10
1 3 5 7 9 8 4 2 6 10
输出样例:
（逆序对对数可能很大，计数器要用long long）
14
思路：同最少交换次数思路一样，循环查找vector中最大元素，其与后面的数均构成逆序数，然后删除
    该最大数，继续上述操作直至只剩一个元素。为了避免重复最大数的影响，每次操作最后一个最大
    数即可。
    But该思想在n=1000000时，递归超时
*/
#include <iostream>
#include <vector>
using namespace std;

long long num=0;            //全局变量便于函数内修改
vector<int> v;

//允许序列中有重复元素，但每次只去掉最后一个最大元素，不影响逆序数
void swap(int n){           //n为序列长度
    if(n==1){
        return;
    }
    int max=0;
    int index;              //j为最大数的下标
    for(int i=0;i<n;i++){
        if(max<=v[i]){      //挂等号以确保搜索到的是最后一个最大数
            max=v[i];
            index=i;
        }
    }//循环结束后index为当前数组中最大数的下标，index后的数与max均构成逆序数
    num+=(n-index-1);       //逆序数增加
    v.erase(v.begin()+index);
    // cout<<num<<endl;
    // for(int i=0;i<v.size();i++){
    //     cout<<v[i]<<" ";
    // }
    // cout<<endl;

    swap(n-1);
    return;
}

int main(){
    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        int m;
        cin>>m;
        v.push_back(m);
    }
    swap(N);
    cout<<num;

    return 0;
}