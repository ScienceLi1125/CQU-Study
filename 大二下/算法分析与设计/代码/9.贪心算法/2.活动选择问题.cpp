/*活动选择问题：
题目：给定一系列活动的开始和结束时间，问安排最多数量活动的方法
输入：第一行给出待安排的活动数N，接下来N行，每行给出第i个活动的开始和结束时间
输出：安排活动的数量以及序列
输入样例：
10
1 4
3 5
2 6
5 7
4 9
5 9
6 10
8 11
8 12
2 13
输出样例：
3
1 4 8
思路：
贪心算法，优先选择结束时间最短的
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct activity{
    int start;
    int finish;
};
bool cmp(activity a1,activity a2){
    if(a1.finish>a2.finish) return 0;
    else if(a1.finish<a2.finish) return 1;
    else{
        if(a1.start<a2.start)   return 1;
        else return 0;
    }
}

int main(){
    int N;
    cin>>N;
    activity A[100];
    for(int i=0;i<N;i++){
        int s,f;
        cin>>s>>f;
        A[i].start=s;
        A[i].finish=f;
    }
    sort(A,A+N,cmp);        //对活动优先级进行排序

    vector<int> ans;
    int index=0;            //第一个满足start>=finish_current的活动下标
    for(int i=0;i<N;){      //不需要i++，因为i由下一个满足的活动决定
        ans.push_back(index+1);
        int f=A[index].finish;
        bool flag=0;
        for(int j=index;j<N;j++){
            if(A[j].start>=f){
                index=j;
                flag=1;
                break;
            }
        }
        if(flag) i=index;   //找到满足条件的下一个活动
        else    break;      //没有下一个活动满足条件，直接跳出
    }
    cout<<ans.size()<<endl;
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<" ";
    }

    return 0;
}