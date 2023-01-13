//用回溯剪枝法求解有重复元素的全排列：
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

void dfs(vector<int> &v1,vector<bool> &v2,vector<int> &array,vector<vector<int>> &ans,int n){
//v1为给定数字，v2为数字是否存入排列情况，array为当前排列，n为元素个数
//vector必须加&，否则不会改变！！！
    if(array.size()==n){
        bool flag=0;
        for(int j=0;j<ans.size();j++){
            if(ans[j]==array){
                flag=1;
            }
        }
        if(!flag){          //保证ans中array不重复
            ans.push_back(array);
        }
        return;
    }

    if(array.size()<n){
        for(int i=0;i<n;i++){
            if(!v2[i]){             //对应元素不在排列中
                array.push_back(v1[i]);
                v2[i]=1;
                dfs(v1,v2,array,ans,n);
                array.pop_back();   //还原数组
                v2[i]=0;
            }
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
    int n;
    cin>>n;
    vector<int> v1;
    for(int i=0;i<n;i++){
        int m;
        cin>>m;
        v1.push_back(m);
    }
    vector<bool> v2(n,0);
    vector<int> array;
    vector<vector<int>> ans;
    dfs(v1,v2,array,ans,n);
    
    cout<<ans.size()<<endl;
    for(int i=0;i<ans.size();i++){
        print(ans[i]);
    }

    return 0;
}