/* 病毒溯源：
题目：病毒容易发生变异。某种病毒可以通过突变产生若干变异的毒株，而这些变异的病毒又可能被诱发突变
    产生第二代变异，如此继续不断变化。现给定一些病毒之间的变异关系，要求你找出其中最长的一条变异
    链。
    在此假设给出的变异都是由突变引起的，不考虑复杂的基因重组变异问题——即每一种病毒都是由唯一的一
    种病毒突变而来，并且不存在循环变异的情况。
输入：在第一行中给出一个正整数N（≤10000），即病毒种类的总数。于是我们将所有病毒从0到N−1进行编号。
    随后 N 行，每行按以下格式描述一种病毒的变异情况：
        k 变异株1 …… 变异株k
    其中k是该病毒产生变异毒株的种类数,后面跟着每种变异株的编号。第i行对应编号为i的病毒(0≤i<N)。
    题目保证病毒源头有且仅有一个。
输出：首先输出从源头开始最长变异链的长度。在第二行中输出从源头开始最长的一条变异链，编号间以1个
    空格分隔，行首尾不得有多余空格。如果最长链不唯一，则输出最小序列。
    注：我们称序列{a1,⋯,an}比序列{b1,⋯,bn} “小”，如果存在1≤k≤n满足ai=bi对所有i<k成立，且ak<bk
输入样例：
10
3 6 4 8
0
0
0
2 5 9
0
1 7
1 2
0
2 3 1
输出样例：
4
0 4 9 1
思路：普通树用vector<int> node[n]解决
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> node[10001];        //存储树
vector<int> ans,tmp;            //最长链
bool flag[10001]={0};

void dfs(int root){
    if(tmp.size()>ans.size()){
        ans=tmp;
    }
    for(int i=0;i<node[root].size();i++){
        tmp.push_back(node[root][i]);
        dfs(node[root][i]);
        tmp.pop_back();
    }
}

int main(){
    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        int K;
        cin>>K;
        for(int j=0;j<K;j++){
            int num;
            cin>>num;
            node[i].push_back(num);
            flag[num]=1;
        }
        sort(node[i].begin(),node[i].end());    //排好序后深搜得结果一定是最小序列
    }
    int root;
    for(int i=0;i<N;i++){
        if(flag[i]==0){
            root=i;
            break;
        }
    }
    tmp.push_back(root);
    dfs(root);
    cout<<ans.size()<<endl;
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<" ";
    }

    return 0;
}