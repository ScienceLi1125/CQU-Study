/*凑零钱：
题目：韩梅梅喜欢满宇宙到处逛街。现在她逛到了一家火星店里，发现这家店有个特别的规矩：你可以用任何
    星球的硬币付钱，但是绝不找零，当然也不能欠债。韩梅梅手边有10000枚来自各个星球的硬币，需要请
    你帮她盘算一下，是否可能精确凑出要付的款额。
输入：第一行给出两个正整数：N（≤10000）是硬币的总个数，M（≤100）是韩梅梅要付的款额。第二行给出
    N枚硬币的正整数面值。数字间以空格分隔。
输出：在一行中输出硬币的面值 V1≤V2≤⋯≤Vk，满足条件V1+V2+...+Vk=M。数字间以 1 个空格分隔，行首
    尾不得有多余空格。若解不唯一，则输出最小序列。若无解，则输出 No Solution。
注：我们说序列{A[1],A[2],⋯}比{B[1],B[2],⋯}“小”，是指存在 k≥1 使得 A[i]=B[i] 对所有i<k成立，
    并且 A[k]<B[k]。
输入样例 1：
8 9
5 9 8 7 2 3 4 1
输出样例 1：
1 3 5
输入样例 2：
4 8
7 2 4 3
输出样例 2：
No Solution
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int coins[10005]={0};
int N,M;
bool flag=0;            //存放是否含可行解
vector<int> ans;        //存放结果

void search_quota(int sum,int tmp){
    if(sum==M||flag==1){
        flag=1;
        return;
    }
    for(int i=tmp;i<N;i++){
        sum+=coins[i];
        ans.push_back(coins[i]);
        if(sum<=M){
            search_quota(sum,i+1);
            if(flag==1){    //已经找到ans且序列必为最小
                break;
            }
        }
        else{               //后面的都比M大
            sum-=coins[i];
            ans.pop_back();
            break;
        }
        sum-=coins[i];
        ans.pop_back();
    }
    return;
}

int main(){
    cin>>N>>M;
    int sum=0;
    for(int i=0;i<N;i++){
        cin>>coins[i];
        sum+=coins[i];
    }
    if(sum<M){              //特殊处理，否则超时
        cout<<"No Solution"<<endl;
        return 0;
    }
    sort(coins,coins+N);
    search_quota(0,0);
    if(flag){
        cout<<ans[0];
        for(int i=1;i<ans.size();i++){
            cout<<" "<<ans[i];
        }
        cout<<endl;
    }
    else{
        cout<<"No Solution"<<endl;
    }

    return 0;
}