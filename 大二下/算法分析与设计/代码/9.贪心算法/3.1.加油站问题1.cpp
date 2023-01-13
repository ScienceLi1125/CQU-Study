/*加油站问题1:
题目:高速公路上设置有n座加油站,位置分别为x1<x2<...<xn,加油站xj的每单位油价为Bj(1<=j<=n)。车的
    油箱容量为P,每单位油可以跑1的距离。最开始车在加油站x1且油箱为空,为了到达加油站xn,需在途中的
    加油站加油,求支付的油价总额最少的加油方法。
    题目保证每两个加油站之间的距离|xj+1-xi|<P
思路:采用贪心策略。由于油箱限制容量为P,因此每次在xi处搜索xi+P范围内最便宜的加油站xj。若Bj<=Bi,则
    只加能够到达xj的油量,即xj=xi;若Bj>Bi,则在Bi处加满,到达xj后再继续决策。
*/
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int dis[8]={0,5,8,13,24,33,45,57};      //加油站距离x1的距离
    int pri[8]={30,50,40,60,20,70,90,30};   //加油站的油价
    int P=18;                               //油箱容量

    bool sta[8]={0};    //记录加油情况
    int quan[8]={0};    //记录加油数量
    int cost=0;         //记录加油费用
    int len=0;          //记录走过的距离
    int cur=0;          //当前所在加油站
    int next=0;         //下一个加油站
    int left=0;         //剩余油量

    while(len<dis[7]){
        len+=dis[next]-dis[cur];            //cur——>next
        left-=(dis[next]-dis[cur]);         //耗费一定的油
        cur=next;
        if(len==dis[7]) break;
        // cout<<"left:"<<left<<"  len:"<<len;

        int min=100;                        //最低油价
        for(int i=cur+1;(dis[i]-dis[cur]<=P)&&(i<8);i++){
            if(pri[i]<min){
                min=pri[i];
                next=i;
            }
        }                                   //找到P范围内最优加油站
        // cout<<"  cur:"<<cur<<"  next:"<<next<<"  ";
        
        if(min<=pri[cur]){                  //next处更划算
            sta[cur]=1;
            //quan[cur]=dis[next]-dis[cur];   //只加够到next的油即可
            quan[cur]=dis[next]-dis[cur]-left;
            //油箱中有可能还有剩余(不可能为负,否则上一次找到的next就应该是当前的next而不是cur)
            cost+=(dis[next]-dis[cur]-left)*pri[cur];
            left=dis[next]-dis[cur];       //加油
        }else{                              //cur更划算
            sta[cur]=1;
            quan[cur]=P-left;               //加满
            cost+=(P-left)*pri[cur];
            left=P;
        }
        // cout<<"left:"<<left<<endl;
    }
    cout<<"Minimum cost:"<<cost<<endl<<"Solution:"<<endl;
    for(int i=0;i<8;i++){
        if(sta[i]){
            cout<<"sta"<<i<<":"<<quan[i]<<endl;
        }
    }
    
    return 0;
}
