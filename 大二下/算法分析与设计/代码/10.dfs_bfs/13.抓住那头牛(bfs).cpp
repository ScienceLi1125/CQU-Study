/*抓住那头牛
题目：农夫知道一头牛的位置，想要抓住它。农夫和牛都位于数轴上，农夫起始位于点N(0<=N<=100000)，牛位
    于点K(0<=K<=100000)。农夫有两种移动方式：
        1 从X移动到X-1或X+1，每次移动花费一分钟
        2 从X移动到2*X，每次移动花费一分钟
    假设牛没有意识到农夫的行动，站在原地不动。农夫最少要花多少时间才能抓住牛？
输入：两个整数，N和K
输出：一个整数，农夫抓到牛所要花费的最小分钟数
输入样例:
5 17
输出样例:
4
思路：bfs
*/
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int main(){
    int N,K;
    cin>>N>>K;
    queue<int> q;
    q.push(N);
    int pos[200005]={0};    //标志移动到x所需的最短次数
    while(!q.empty()){
        int top=q.front();
        q.pop();
        if(top+1==K||top-1==K||top*2==K){
            cout<<pos[top]+1<<endl;
            break;
        }
        if(top+1<200005&&top+1>=0&&pos[top+1]==0&&top+1!=N){    //控制范围以防段错误
            pos[top+1]=pos[top]+1;
            q.push(top+1);
        }
        if(top-1<200005&&top-1>=0&&pos[top-1]==0&&top-1!=N){
            pos[top-1]=pos[top]+1;
            q.push(top-1);
        }
        if(top*2<200005&&top*2>=0&&pos[top*2]==0&&top*2!=N){
            pos[top*2]=pos[top]+1;
            q.push(top*2);
        }
        // cout<<"pos["<<top-1<<"]="<<"pos["<<top+1<<"]="<<"pos["<<top*2<<"]="<<pos[top]+1<<endl;
    }
    
    return 0;
}