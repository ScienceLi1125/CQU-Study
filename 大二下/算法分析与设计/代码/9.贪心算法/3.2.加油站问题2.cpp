/*加油站问题2(leetcode871):
题目:高速公路上设置有n座加油站,位置分别为x1<x2<...<xn,加油站xj的储油量为Bj(1<=j<=n)。车的油箱
    容量足够大,每单位油可以跑1的距离。最开始车在起点x0=0且油箱装有P的油,目的地距离起点L。求从起
    点x0到终点取油次数最少的方法
    题目保证L<=P+(B1+B2+...+Bn)并且xj<=P+(B1+B2+...+Bj-1)
思路:采用贪心策略。由于油箱容量无限制,因此每次若取油则必然全部取出。每次向油箱能够支持的最远地方
    走去,然后没油了,寻找走过加油站中储油量最大的进行加油;重复上述操作。采用优先队列可以简化上述
    操作,先进先出,自动将储油量大的加油站靠前。问题转化为一直向前走,若没油了则取经过的最大油桶,
    持续上述操作,记录使用过的油桶即可
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct Gas_station{
    int NO;     //编号
    int dis;    //离x0距离
    int cap;    //储油量
    Gas_station(int no,int d,int c){
        NO=no;
        dis=d;
        cap=c;
    }
};
struct cmp{     //定义优先队列的比较方式
    bool operator()(Gas_station a, Gas_station b) {
        if(a.cap>b.cap)         return 1;
        else if(a.cap<b.cap)    return 0;
        else{
            if(a.NO<b.NO)       return 1;
            else                return 0;    
        }
    }
};

int main(){
    priority_queue<Gas_station,vector<Gas_station>,cmp> q;      //优先队列存储经过的油桶
    vector<int> v;                          //vector存储使用过的油桶
    int P=18;                               //油箱初始油量
    int L=10;                               //目的地距离
    int dist[5]={10,20,30,60,L};            //起点、加油站及终点间距离
    int capa[4]={60,30,30,40};              //加油站油量
    
    int left=P;                             //剩余油量
    int cnt=0;                              //记录取油次数
    for(int i=0;i<4;i++){
        Gas_station use(i,dist[i],capa[i]);
        q.push(use);
        left-=dist[i];                      //消耗油量
        if(left<dist[i+1]){                 //不够到达下一个加油站
            use=q.top();        //取出优先队列的第一个油桶(油量最大)
            q.pop();
            left+=use.cap;
            v.push_back(use.NO);            //记录使用的油桶的编号
            cnt++;
        }
    }
    sort(v.begin(),v.end());
    cout<<"Minimum times:"<<cnt<<endl<<"Method:"<<endl;
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    
    return 0;
}
