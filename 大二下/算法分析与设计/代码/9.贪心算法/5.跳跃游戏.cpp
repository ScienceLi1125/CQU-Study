/*跳跃游戏：
题目：给你一个非负整数数组nums，你最初位于数组的第一个位置。数组中的每个元素代表你在该位置可以跳
    跃的最大长度。你的目标是使用最少的跳跃次数到达数组的最后一个位置。
    假设你总是可以到达数组的最后一个位置。
输入样例1：
5
2 3 1 1 4
输出样例1：
2
输入样例2：
5
2 3 0 1 4
输出样例2：
2
思路：贪心算法，当前跳跃距离为可达到范围内最远距离，即遍历pos~pos+nums[pos]范围内的点，寻找所有
    点可达的最远距离作为当前决策。难点在于结束的控制
*/
#include <iostream>
#include <vector>
using namespace std;

int jump(vector<int>& nums) {
    int cnt=0;
    int pos=0;
    while(pos<nums.size()-1){
        int index=pos;
        int max=0;
        if(pos+nums[pos]>=nums.size()-1)    return cnt+1;   //提前判断
        for(int i=0;i<=nums[pos];i++){
            if((i+pos)>=nums.size()){
                return cnt+1;       //当前pos可以跳出
            }
            else if(pos+i+nums[i+pos]>=nums.size()-1){
                return cnt+2;       //当前pos跳到pos+i，下一次可以跳出
            }
            else if(max<i+nums[i+pos]){
                max=i+nums[i+pos];
                index=i+pos;
            }
        }
        pos=index;
        cnt++;
    }
    return cnt;
}

int main(){
    int n;
    cin>>n;
    vector<int> nums;
    for(int i=0;i<n;i++){
        int tmp;
        cin>>tmp;
        nums.push_back(tmp);
    }
    cout<<jump(nums)<<endl;

    return 0;
}
