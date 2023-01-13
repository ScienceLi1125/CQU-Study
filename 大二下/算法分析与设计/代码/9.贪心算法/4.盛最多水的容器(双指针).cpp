/*盛最多水的容器：
题目：给定一个长度为n的整数数组height。有n条垂线，第i条线的两个端点是(i,0)和(i,height[i])。
    找出其中的两条线，使得它们与x轴共同构成的容器可以容纳最多的水。
说明：你不能倾斜容器。
输入样例：
9
1 8 6 2 5 4 8 3 7
输出样例：
49
思路：暴力搜索显然不可取，采用贪心。用双指针left和right分别指向容器的左右端，每次left++或right--
    并不改变容器的底，因此高度较低的一侧指针进行移动
*/
#include <iostream>
#include <vector>
using namespace std;

int min(int a,int b){
    return a<b?a:b;
}

int main(){
    int n;
    cin>>n;
    vector<int> height;
    for(int i=0;i<n;i++){
        int tmp;
        cin>>tmp;
        height.push_back(tmp);
    }
    int left=0;
    int right=n-1;
    int max_v=(right-left)*min(height[left],height[right]);
    while(left<right){
        if(height[left]<height[right]){
            left++;
        }else{
            right--;
        }
        if(max_v<(right-left)*min(height[left],height[right])){
            max_v=(right-left)*min(height[left],height[right]);
        }
    }
    cout<<max_v<<endl;

    return 0;
}
