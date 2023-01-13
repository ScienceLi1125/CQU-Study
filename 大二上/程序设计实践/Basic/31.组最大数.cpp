/*组最大数：
题目：设有n个正整数，将他们连接成一排，组成一个最大的多位整数。
    如:n=3时，3个整数13,312,343连成的最大整数为34331213。
    如:n=4时，4个整数7,13,4,246连接成的最大整数为7424613。
输入：有多组测试样例，每组测试样例包含两行，第一行为一个整数N（N<=100），第二行包含N个数(每个
    数不超过1000，空格分开)。
输出：每组数据输出一个表示最大的整数。
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool compare(string s1,string s2){
    if(s1+s2>s2+s1){        //题目要组成最大数，因此不是比较s1和s2的大小，而是串起来
        return true;        //比如：742>74，但74274<74742
    }
    else{
        return false;
    }
}

int main(){
    int N;
    while(cin>>N){
        vector<string> v;
        for(int i=0;i<N;i++){
            string s;
            cin>>s;
            v.push_back(s);
        }
        sort(v.begin(),v.end(),compare);
        for(int i=0;i<N;i++){
            cout<<v[i];
        }
        cout<<endl;
    }

    return 0;
}