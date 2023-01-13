/*背包问题_部分背包：
题目：有N个物体，重量分别为wi，价值为vi，在总重量不超过容量C的情况下让总价值最高，每个物体可以
    只取走一部分，若取走部分物体则价值也会等比例减少
思路：根据性价比取走物体即可
*/
#include <iostream>
#include <algorithm>
using namespace std;

class Stuff{        //需要同步多个变量进行排序的时候自定义类
public:
    int w;
    int v;
    double ratio;
    // //重载><==可以进行sort函数排序
    // bool operator>(const Stuff &s){
    //     if(this->ratio > s.ratio){
    //         return 1;
    //     }
    //     else{
    //         return 0;
    //     }
    // }
    // bool operator<(const Stuff &s){
    //     if(this->ratio < s.ratio){
    //         return 1;
    //     }
    //     else{
    //         return 0;
    //     }
    // }
    // bool operator==(const Stuff &s){
    //     if(this->ratio == s.ratio){
    //         return 1;
    //     }
    //     else{
    //         return 0;
    //     }
    // }
};
bool cmp(Stuff s1,Stuff s2){
    return s1.ratio>s2.ratio;
}

int main(){
    int N;
    int C;
    cin>>N>>C;
    Stuff S[N];
    for(int i=0;i<N;i++){
        cin>>S[i].v;
        cin>>S[i].w;
        S[i].ratio=double(S[i].v)/double(S[i].w);
    }
    sort(S,S+N,cmp);        //对ratio降序排列 
    double val=0;           //总价值
    int wgh=0;              //总重量
    // for(int i=0;i<N;i++){
    //     cout<<S[i].ratio<<endl;
    // }
    for(int i=0;i<N;i++){
        wgh+=S[i].w;
        if(wgh<=C){
            val+=S[i].v;
        }
        else{
            val+=(S[i].w-wgh+C)*double(S[i].ratio);
            break;
        }
    }
    cout<<val<<endl;

    return 0;
}