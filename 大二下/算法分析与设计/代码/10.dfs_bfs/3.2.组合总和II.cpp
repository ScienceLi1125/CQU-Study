/*回溯剪枝法
题目：组合总和II，给定一个无重复元素的数组candidates和一个目标数 target，
    找出candidates中所有可以使数字和为target的组合。
    candidates中的每个数字在每个组合中只能使用一次。
思路：与唯一不同的是递归时start值的限定，需+1
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool equal(vector<int> v1,vector<int> v2){
    if(v1.size()!=v2.size()){
        return 0;
    }
    else{
        for(int i=0;i<v1.size();i++){
            if(v1[i]!=v2[i]){
                return 0;
            }
        }
        return 1;
    }
}

void dfs(vector<int> &c,vector<int> &tmp,vector<vector<int>> &ans,int t,int s,int start){
    if(s>t){
        return;
    }
    if(s==t){
        bool flag=0;
        for(int i=0;i<ans.size();i++){
            if(ans[i]==tmp){
                flag=1;
            }
        }
        if(!flag){                              //保证ans中tmp不重复
            ans.push_back(tmp);
        }
        return;
    }
    if(s<t){
        for(int i=start;i<c.size();i++){
            tmp.push_back(c[i]);
            dfs(c,tmp,ans,t,s+c[i],i+1);        //start赋为i+1保证所取元素不重复
            tmp.pop_back();
        }
    }
    return;
}

void print(vector<int> &v){
    cout<<"[";
    for(int i=0;i<v.size()-1;i++){
        cout<<v[i]<<",";
    }
    cout<<v[v.size()-1]<<"]"<<endl;
}

int main(){
    vector<int> candidates{10,1,2,7,6,1,5};
    int targets=8;
    sort(candidates.begin(),candidates.end());
    vector<int> tmp;
    vector<vector<int>> ans;
    dfs(candidates,tmp,ans,targets,0,0);
    
    cout<<"["<<endl;
    for(int i=0;i<ans.size();i++){
        print(ans[i]);
    }
    cout<<"]"<<endl;

    return 0;
}