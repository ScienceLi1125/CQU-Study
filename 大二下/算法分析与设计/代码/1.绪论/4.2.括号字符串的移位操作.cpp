/* 思路：字符串括号移位的实质是前面x位“)”数量多了，因此只需对该数量计数，初值为0，遇到“)”加一，
    遇到“(”减一，寻找计数变量最大的点，即为输出结果
    原先用数组存储各位计数变量，发现1000000级数组太占空间且编译错误，因此用两次循环解决
*/
#include <iostream>
#include <vector>
using namespace std;

int main(){
    string s;
    cin>>s;
    vector<int> v;
    int cnt1=0;
    int max=0;
    for(int i=0;i<s.length()-1;i++){
        if(s[i]==')'){
            cnt1++;
        }
        else{
            cnt1--;
        }
        if(max<cnt1){
            max=cnt1;
        }
    }
    int cnt2=0;
    if(max==0){                         //第二次循环压入元素从1开始，因此单独判断0
        v.push_back(0);
    }
    for(int i=0;i<s.length()-1;i++){    //0和s.length()-1本质是一种情况，尝试发现只输出0
        if(s[i]==')'){
            cnt2++;
        }
        else{
            cnt2--;
        }
        if(max==cnt2){
            v.push_back(i+1);           //压入的是前缀长度，因此需要加一
        }
    }
    cout<<v[0];
    for(int i=1;i<v.size();i++){
        cout<<" "<<v[i];
    }

    return 0;
} 