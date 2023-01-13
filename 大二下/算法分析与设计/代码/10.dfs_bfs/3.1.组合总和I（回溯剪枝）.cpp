/*回溯剪枝法
题目：组合总和I，给定一个无重复元素的数组candidates和一个目标数 target，
    找出candidates中所有可以使数字和为target的组合。
    candidates 中的数字可以无限制重复被选取。
思路：使用深度优先搜索，图解为一个树形结构，从0作为根节点，来做加法，
    当节点走到7或者大于7的时候回溯。
    如果节点值为7，认为找到一条结果，将其加入结果集，如果大于7，则剪去。
    因为对于candidates做了排序，所以生成序列为升序（此处便为剪枝）。
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
//t表示目标和,s表示当前节点和,c表示candidates,tmp表示当前序列,ans表示最终答案,start表示搜索开始值
    if(s>t){
        //s-=tmp.back();
        //tmp.pop_back();     //不再需要还原，因为s<t中有还原
        return;
    }
    if(s==t){
        bool flag=0;
        for(int i=0;i<ans.size();i++){
            if(ans[i]==tmp){
                flag=1;
            }
        }
        if(!flag){          //保证ans中tmp不重复
            ans.push_back(tmp);
        }
        //s-=tmp.back();
        //tmp.pop_back();
        return;
    }
    //s>t和s=t都来源于s<t
    if(s<t){
        for(int i=start;i<c.size();i++){
            tmp.push_back(c[i]);
            //s+=c[i];      
//s是复制参数，不能随意改动，因为这里改动后进入递归s>t处执行s-=tmp.back()并不会改变当前的s
            dfs(c,tmp,ans,t,s+c[i],i);      //start赋为i实现剪枝
            tmp.pop_back();                 //此处需要还原
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
    sort(candidates.begin(),candidates.end());  //回溯剪枝前先排序
    vector<int> tmp;                            //当前序列初始值为空
    vector<vector<int>> ans;                    //ans用来存储生成序列
    dfs(candidates,tmp,ans,targets,0,0);        //初始状态下节点和为0，开始值为0
    
    cout<<"["<<endl;
    for(int i=0;i<ans.size();i++){
        print(ans[i]);
    }
    cout<<"]"<<endl;

    return 0;
}