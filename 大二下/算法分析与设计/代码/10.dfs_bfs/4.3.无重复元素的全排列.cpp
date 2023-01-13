/*全排列：
题目：给定一个不含重复数字的数组nums，返回其所有可能的全排列。你可以按任意顺序返回答案。
    题目保证1<=nums.length<=6，-10<=nums[i]<=10且nums中的所有整数互不相同
示例1：
输入：nums=[1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
示例2：
输入：nums = [0,1]
输出：[[0,1],[1,0]]
示例3：
输入：nums = [1]
输出：[[1]]
*/
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> permute(vector<int>& nums) {
    vector<bool> flag;      //标记nums[i]是否使用
    for(int i=0;i<nums.size();i++)  flag.push_back(0);
    vector<vector<int>> ans;
    vector<int> tmp;
    dfs(ans,nums,tmp,flag);
    return ans;
}
void dfs(vector<vector<int>>& ans,vector<int>& nums,vector<int>& tmp,vector<bool>& flag){
    if(tmp.size()==nums.size()){
        ans.push_back(tmp);
        return;
    }
    for(int i=0;i<nums.size();i++){
        if(!flag[i]){
            tmp.push_back(nums[i]);
            flag[i]=1;
            dfs(ans,nums,tmp,flag);
            tmp.pop_back();
            flag[i]=0;
        }
    }
}