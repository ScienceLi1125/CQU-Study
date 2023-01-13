/*最少交换次数I：
题目：给出一个序列，序列个数为n，只交换相邻两数，使得序列升序排列，求出最少交换次数。
思路：先把最大的数换到最后，因为是相邻数字交换，所以需要交换的次数为最大数后的数字个数。
    当完成最大数的交换后，可以将最大数从序列中划去不管了，即此时序列个数为n-1了。
    再在剩下n-1个元素的序列中找到一个最大数，进行相同操作，形成回溯。
    所以使整个序列有序的交换次数为,这个序列的所有逆序对总数。
*/
#include <iostream>
#include <vector>
using namespace std;

int num=0;              //全局变量便于函数内修改
vector<int> v;

//允许序列中有重复元素，但每次只去掉一个最大元素，不影响逆序数
void swap(int n){       //n为序列长度
    if(n==1){
        return;
    }
    int max=0;
    int j;              //j为最大数的下标
    for(int i=0;i<n;i++){
        if(max<v[i]){
            max=v[i];
            j=i;
        }
    }
    num+=(n-j-1);       //逆序数增加
    for(vector<int>::iterator it=v.begin();it!=v.end();it++){
        if(*it==max){
            v.erase(it);
            break;      //只删除第一个最大数
        }
    }
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